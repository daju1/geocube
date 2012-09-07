/**************************************************************************\
 *
 *  This source file is part of DIME.
 *  Copyright (C) 1998-2001 by Systems In Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License, version 2, as
 *  published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  General Public License (the accompanying file named COPYING) for more
 *  details.
 *
 **************************************************************************
 *
 *  If you need DIME for a non-GPL project, contact Systems In Motion
 *  to acquire a Professional Edition License:
 *
 *  Systems In Motion                                   http://www.sim.no/
 *  Prof. Brochs gate 6                                       sales@sim.no
 *  N-7030 Trondheim                                   Voice: +47 22114160
 *  NORWAY                                               Fax: +47 22207097
 *
\**************************************************************************/

#include "convert_funcs.h"
#include <dime/convert/convert.h>
#include <dime/convert/layerdata.h>
#include "linesegment.h"
#include <dime/entities/Polyline.h>
#include <dime/util/Linear.h>
#include <dime/entities/Vertex.h>
#include <dime/entities/Arc.h>
#include <dime/State.h>


static void convert_line_3d(dimePolyline *pline, const dimeState *state,
			    dxfLayerData *layerData, dxfConverter *);

static void convert_line(dimePolyline *pline, const dimeState *state,
			 dxfLayerData *layerData, dxfConverter *);
static void convert_mesh(dimePolyline *pline, const dimeState *state,
			 dxfLayerData *layerData, dxfConverter *);
static void convert_face(dimePolyline *pline, const dimeState *state,
			 dxfLayerData *layerData, dxfConverter *);


#if DXF_Y_SCALE

static void yscale_line_3d(dimePolyline *pline, const dimeState *state,
			    dxfLayerData *, dxfConverter *);

static void yscale_spline(dimePolyline *pline, const dimeState *state,
			    dxfLayerData *, dxfConverter *);

static void xyscale_line_3d(dimePolyline *pline, const dimeState *state,
			    dxfLayerData *, dxfConverter *);

static void xyscale_spline(dimePolyline *pline, const dimeState *state,
			    dxfLayerData *, dxfConverter *);

#endif

void 
convert_polyline(const dimeEntity *entity, const dimeState *state, 
		 dxfLayerData *layerData, dxfConverter *converter)
{
  dimePolyline *pline = (dimePolyline*) entity;
  
  if (pline->getFlags() & 16)
    convert_mesh(pline, state, layerData, converter);
  else if (pline->getFlags() & 64)
    convert_face(pline, state, layerData, converter);
  else if (pline->getFlags() & 8)
    convert_line_3d(pline, state, layerData, converter);
  else
    convert_line(pline, state, layerData, converter);
}

#include "./../surfdoc/src/BlnProfile3D.h"

static void profile_line_3d(dimePolyline *pline, const dimeState *state,
			    BlnProfile3D *profile, dxfConverter *);

static void profile_line(dimePolyline *pline, const dimeState *state,
			 BlnProfile3D *profile, dxfConverter *);
static void profile_mesh(dimePolyline *pline, const dimeState *state,
			 BlnProfile3D *profile, dxfConverter *);
static void profile_face(dimePolyline *pline, const dimeState *state,
			 BlnProfile3D *profile, dxfConverter *);
void 
profile_polyline(const dimeEntity *entity, const dimeState *state, 
		 BlnProfile3D *profile, dxfConverter *converter)
{
  dimePolyline *pline = (dimePolyline*) entity;
  
  if (pline->getFlags() & 16)
    profile_mesh(pline, state, profile, converter);
  else if (pline->getFlags() & 64)
    profile_face(pline, state, profile, converter);
  else if (pline->getFlags() & 8)
    profile_line_3d(pline, state, profile, converter);
  else
    profile_line(pline, state, profile, converter);
}




#if DXF_Y_SCALE

void 
yscale_polyline(const dimeEntity *entity, const dimeState *state, 
		 dxfLayerData *layerData, dxfConverter *converter)
{
  dimePolyline *pline = (dimePolyline*) entity;
  yscale_line_3d(pline, state, layerData, converter);
  yscale_spline(pline, state, layerData, converter);
}


void 
xyscale_polyline(const dimeEntity *entity, const dimeState *state, 
		 dxfLayerData *layerData, dxfConverter *converter)
{
  dimePolyline *pline = (dimePolyline*) entity;
  xyscale_line_3d(pline, state, layerData, converter);
  xyscale_spline(pline, state, layerData, converter);
}




#endif
static void
set_segment_data(dxfLineSegment* segment,
		 dimeVertex *v, dimeVertex *next,
		 dimePolyline *pline)
{
  dimeParam param;
  dxfdouble w0, w1;
  if (v->getRecord(40, param)) w0 = param.double_data;
  else if (pline->getRecord(40, param)) w0 = param.double_data;
  else w0 = 0.0;
  
  if (v->getRecord(41, param)) w1 = param.double_data;
  else if (pline->getRecord(41, param)) w1 = param.double_data;
  else w1 = 0.0;

  dimeVec3f v0,v1;
  v0 = v->getCoords();
  if (next) v1 = next->getCoords();
  else v1 = v0 + dimeVec3f(1,0,0); // just set a dummy value

  v0[2] = pline->getElevation()[2];
  v1[2] = pline->getElevation()[2];
  
  segment->set(v0, v1, w0, w1, 
	       pline->getThickness());
}


static void 
convert_line(dimePolyline *pline, const dimeState *state,
	     dxfLayerData *layerData, dxfConverter *converter)
{
  // respect the value in the $FILLMODE header variable
  layerData->setFillmode(converter->getFillmode());

  int i, n = pline->getNumCoordVertices();
  if (n == 0) return;

  dimeMatrix matrix;
  state->getMatrix(matrix);

  dimeVec3f e = pline->getExtrusionDir();
  dxfdouble thickness = pline->getThickness();
  
  if (e != dimeVec3f(0,0,1)) {
    dimeMatrix m;
    dimeEntity::generateUCS(e, m);
    matrix.multRight(m);
  }
  e = dimeVec3f(0,0,1) * thickness;

  float elev = pline->getElevation()[2];
  
  dxfLineSegment prevseg, nextseg, segment;

  dimeVertex *v = NULL;
  dimeVertex *next = NULL;
  dimeVec3f v0, v1;
  
  bool closed = pline->getFlags() & 1;
  if (n <= 2) closed = false;
  int stop = closed ? n : n-1;
  
  for (i = 0; i < stop; i++) {
    v = pline->getCoordVertex(i);

    next = pline->getCoordVertex((i+1)%n);
    
    if (i == 0) {
      set_segment_data(&segment, v, next, pline);
      if (closed) {
	set_segment_data(&prevseg, 
			 pline->getCoordVertex(n-1),
			 v,
			 pline);
      }
    }
    
    dimeVertex *next2 = pline->getCoordVertex((i+2)%n);
    set_segment_data(&nextseg, next, next2, pline); 

    dimeParam param;

    //
    // FIXME: need to figure out what to do if elev != 0 and the bulge
    // factor != 0. Right now we don't bulge those line segments.
    // Maybe we should push the state, and make a new matrix???

    if (elev == 0.0f && v->getRecord(42, param) && param.double_data != 0.0) {
      dxfdouble A = param.double_data;
      dxfdouble alpha = 4.0*atan(A);
      dimeVec3f dir = next->getCoords() - v->getCoords();
      dxfdouble L = dir.length();
      dir.normalize();
      dxfdouble H = A*L/2.0;
      dxfdouble R = L / (2.0*sin(alpha/2.0));
      
      dimeVec3f rdir = A > 0.0 ? dir.cross(dimeVec3f(0,0,1)) : 
	dir.cross(dimeVec3f(0,0,-1));
      rdir.normalize();
      dimeVec3f center = v->getCoords() + dir*(L/2.0) - rdir*(R-H);

#if 0
      fprintf(stderr,"A: %g, L: %g, H: %g, R:%g\n",
	      A, L, H, R);
#endif
#if 0
      fprintf(stderr,"dir: %g %g %g, rdir: %g %g %g\n",
	      dir[0], dir[1], dir[2], rdir[0], rdir[1], rdir[2]);
#endif 

      dimeVec3f t = v->getCoords() - center;
      t.normalize();
      dxfdouble a0 = dimeVec3f(1,0,0).angle(t);
      if (t[1] < 0.0) a0 = 2*M_PI-a0;

      t = next->getCoords() - center;
      t.normalize();
      dxfdouble a1 = dimeVec3f(1,0,0).angle(t);
      if (t[1] < 0.0) a1 = 2*M_PI-a1;

      dimeArc arc;
      arc.setLayer(v->getLayer());
      arc.setColorNumber(v->getColorNumber());
      arc.setExtrusionDir(pline->getExtrusionDir());
      arc.setCenter(center);
      arc.setRadius(R);
      arc.setStartAngle(DXFRAD2DEG(a0));
      arc.setEndAngle(DXFRAD2DEG(a1));
      
//        if (elev != 0.0f) {
//          dimeParam param;
//          param.double_data = elev;
//          arc.setRecord(38, param);
//        }

      convert_arc(&arc, state, converter->getLayerData(v), converter);
    }
    else {
      segment.convert(i > 0 || closed ? &prevseg : NULL, 
		      i < (stop-1) ? &nextseg : NULL, 
		      converter->getLayerData(v), &matrix, pline->getLayerName());
    }
    // prepare for next iteration
    prevseg = segment;
    segment = nextseg;
  }
}

static void 
convert_line_3d(dimePolyline *pline, const dimeState *state,
		dxfLayerData *layerData, dxfConverter *converter)
{
  int i, n = pline->getNumCoordVertices();
  if (n == 0) return;

  dimeMatrix matrix;
  state->getMatrix(matrix);
  
  dimeVertex *v = NULL;
  dimeVertex *next = NULL;
  dimeVec3f v0, v1;

  int stop = pline->getFlags() & 1 ? n : n-1;

  for (i = 0; i < stop; i++) {
    v = pline->getCoordVertex(i);
    layerData = converter->getLayerData(v);
    next = i+1 >= n ? pline->getCoordVertex(0) : pline->getCoordVertex(i+1);

    v0 = v->getCoords();
    v1 = next->getCoords();
    layerData->addLine(v0, v1, pline->getLayerName(), &matrix);
  }
}

static void 
convert_mesh(dimePolyline *pline, const dimeState *state,
		dxfLayerData *layerData, dxfConverter *)
{
  int i;
  int m = pline->getPolymeshCountM();
  int n = pline->getPolymeshCountN();

  int m2 = 0;
  int n2 = 0;

  int coordCnt = pline->getNumCoordVertices();

  if (pline->getSurfaceType() && pline->getSmoothSurfaceMdensity() && 
      pline->getSmoothSurfaceNdensity()) {
      m2 = pline->getSmoothSurfaceMdensity();
      n2 = pline->getSmoothSurfaceNdensity();
  }
    
  if (m*n + m2*n2 != coordCnt) {
    // FIXME: quick bugfix for stehlen.dxf... file is probably invalid...
    if ((m-1)*n + m2*n2 == coordCnt) m--;
    else {
      if (m*n == coordCnt) {
	m2 = n2 = 0;
      }
      else if (m2*n2 == coordCnt) {
	m = n = 0;
      }
      else { // give up... can't find the dimensions
	fprintf(stderr,"Error: Unable to find polymesh dimensions.\n");
	return;
      }
    }
  }

  
//  int idx;
  int idxadd = m2*n2;
  int nexti, nextj;
  int endm = (pline->getFlags() & 1) ? m : m-1;
  int endn = (pline->getFlags() & 32) ? n : n-1;

  dimeMatrix matrix;
  state->getMatrix(matrix);

  for (i = 0; i < endm; i++) {
    nexti = i+1;
    if (nexti == m) nexti = 0;
    for (int j = 0; j < endn; j++) {
      nextj = j+1;
      if (nextj == n) nextj = 0;
      
      layerData->addQuad(pline->getCoordVertex(idxadd+i*n+j)->getCoords(),
			 pline->getCoordVertex(idxadd+i*n+nextj)->getCoords(),
			 pline->getCoordVertex(idxadd+nexti*n+nextj)->getCoords(),
			 pline->getCoordVertex(idxadd+nexti*n+j)->getCoords(), 
			 pline->getLayerName(),
			 &matrix);
    }
  }

  idxadd = 0;
  // copied code from above. I'm too lazy to write a loop or
  // a separate function :)
  m = m2;
  n = n2;
  endm = (pline->getFlags() & 1) ? m : m-1;
  endn = (pline->getFlags() & 32) ? n : n-1;
  
  for (i = 0; i < endm; i++) {
    nexti = i+1;
    if (nexti == m) nexti = 0;
    for (int j = 0; j < endn; j++) {
      nextj = j+1;
      if (nextj == n) nextj = 0;

      layerData->addQuad(pline->getCoordVertex(idxadd+i*n+j)->getCoords(),
			 pline->getCoordVertex(idxadd+i*n+nextj)->getCoords(),
			 pline->getCoordVertex(idxadd+nexti*n+nextj)->getCoords(),
			 pline->getCoordVertex(idxadd+nexti*n+j)->getCoords(), 
			 pline->getLayerName(),
			 &matrix);
    }
  }
}

static void 
convert_face(dimePolyline *pline, const dimeState *state,
	     dxfLayerData *layerData, dxfConverter *converter)
{
  dimeMatrix matrix;
  state->getMatrix(matrix);

  int i, n = pline->getNumIndexVertices();

  for (i = 0; i < n; i++) {
    dimeVertex *v = pline->getIndexVertex(i);
    layerData = converter->getLayerData(v);
    dimeVec3f c[4];
    int num = v->numIndices();
    int idx;
    for (int j = 0; j < num; j++) {
      idx = v->getIndex(j);
      if (idx < 0) { // negative means hidden edge
	idx = -idx;
      }
      c[j] = pline->getCoordVertex(idx-1)->getCoords();
    }
    if (num == 3) layerData->addTriangle(c[0], c[1], c[2], pline->getLayerName(), &matrix);
    else layerData->addQuad(c[0], c[1], c[2], c[3], pline->getLayerName(), &matrix);
  }
}





static void 
profile_line(dimePolyline *pline, const dimeState *state,
	     BlnProfile3D *profile, dxfConverter *converter)
{
  // respect the value in the $FILLMODE header variable
  profile->setFillmode(converter->getFillmode());

  int i, n = pline->getNumCoordVertices();
  if (n == 0) return;

  dimeMatrix matrix;
  state->getMatrix(matrix);

  dimeVec3f e = pline->getExtrusionDir();
  dxfdouble thickness = pline->getThickness();
  
  if (e != dimeVec3f(0,0,1)) {
    dimeMatrix m;
    dimeEntity::generateUCS(e, m);
    matrix.multRight(m);
  }
  e = dimeVec3f(0,0,1) * thickness;

  float elev = pline->getElevation()[2];
  
  dxfLineSegment prevseg, nextseg, segment;

  dimeVertex *v = NULL;
  dimeVertex *next = NULL;
  dimeVec3f v0, v1;
  
  bool closed = pline->getFlags() & 1;
  if (n <= 2) closed = false;
  int stop = closed ? n : n-1;
  
  for (i = 0; i < stop; i++) {
    v = pline->getCoordVertex(i);

    next = pline->getCoordVertex((i+1)%n);
    
    if (i == 0) {
      set_segment_data(&segment, v, next, pline);
      if (closed) {
	set_segment_data(&prevseg, 
			 pline->getCoordVertex(n-1),
			 v,
			 pline);
      }
    }
    
    dimeVertex *next2 = pline->getCoordVertex((i+2)%n);
    set_segment_data(&nextseg, next, next2, pline); 

    dimeParam param;

    //
    // FIXME: need to figure out what to do if elev != 0 and the bulge
    // factor != 0. Right now we don't bulge those line segments.
    // Maybe we should push the state, and make a new matrix???

    if (elev == 0.0f && v->getRecord(42, param) && param.double_data != 0.0) {
      dxfdouble A = param.double_data;
      dxfdouble alpha = 4.0*atan(A);
      dimeVec3f dir = next->getCoords() - v->getCoords();
      dxfdouble L = dir.length();
      dir.normalize();
      dxfdouble H = A*L/2.0;
      dxfdouble R = L / (2.0*sin(alpha/2.0));
      
      dimeVec3f rdir = A > 0.0 ? dir.cross(dimeVec3f(0,0,1)) : 
	dir.cross(dimeVec3f(0,0,-1));
      rdir.normalize();
      dimeVec3f center = v->getCoords() + dir*(L/2.0) - rdir*(R-H);

#if 0
      fprintf(stderr,"A: %g, L: %g, H: %g, R:%g\n",
	      A, L, H, R);
#endif
#if 0
      fprintf(stderr,"dir: %g %g %g, rdir: %g %g %g\n",
	      dir[0], dir[1], dir[2], rdir[0], rdir[1], rdir[2]);
#endif 

      dimeVec3f t = v->getCoords() - center;
      t.normalize();
      dxfdouble a0 = dimeVec3f(1,0,0).angle(t);
      if (t[1] < 0.0) a0 = 2*M_PI-a0;

      t = next->getCoords() - center;
      t.normalize();
      dxfdouble a1 = dimeVec3f(1,0,0).angle(t);
      if (t[1] < 0.0) a1 = 2*M_PI-a1;

      dimeArc arc;
      arc.setLayer(v->getLayer());
      arc.setColorNumber(v->getColorNumber());
      arc.setExtrusionDir(pline->getExtrusionDir());
      arc.setCenter(center);
      arc.setRadius(R);
      arc.setStartAngle(DXFRAD2DEG(a0));
      arc.setEndAngle(DXFRAD2DEG(a1));
      
//        if (elev != 0.0f) {
//          dimeParam param;
//          param.double_data = elev;
//          arc.setRecord(38, param);
//        }

      convert_arc(&arc, state, converter->getLayerData(v), converter);
    }
    else {
      segment.convert(i > 0 || closed ? &prevseg : NULL, 
		      i < (stop-1) ? &nextseg : NULL, 
		      profile, &matrix, pline->getLayerName(), pline->getColorNumber());
    }
    // prepare for next iteration
    prevseg = segment;
    segment = nextseg;
  }
}

static void 
profile_line_3d(dimePolyline *pline, const dimeState *state,
		BlnProfile3D *profile, dxfConverter *converter)
{
  int i, n = pline->getNumCoordVertices();
  if (n == 0) return;

  dimeMatrix matrix;
  state->getMatrix(matrix);
  
  dimeVertex *v = NULL;
  dimeVertex *next = NULL;
  dimeVec3f v0, v1;

  int stop = pline->getFlags() & 1 ? n : n-1;

  for (i = 0; i < stop; i++) {
    v = pline->getCoordVertex(i);
//    layerData = converter->getLayerData(v);
    next = i+1 >= n ? pline->getCoordVertex(0) : pline->getCoordVertex(i+1);

    v0 = v->getCoords();
    v1 = next->getCoords();
    profile->addLine(v0, v1, pline->getLayerName(), pline->getColorNumber(), &matrix);
  }
}

static void 
profile_mesh(dimePolyline *pline, const dimeState *state,
		BlnProfile3D *profile, dxfConverter *)
{
  int i;
  int m = pline->getPolymeshCountM();
  int n = pline->getPolymeshCountN();

  int m2 = 0;
  int n2 = 0;

  int coordCnt = pline->getNumCoordVertices();

  if (pline->getSurfaceType() && pline->getSmoothSurfaceMdensity() && 
      pline->getSmoothSurfaceNdensity()) {
      m2 = pline->getSmoothSurfaceMdensity();
      n2 = pline->getSmoothSurfaceNdensity();
  }
    
  if (m*n + m2*n2 != coordCnt) {
    // FIXME: quick bugfix for stehlen.dxf... file is probably invalid...
    if ((m-1)*n + m2*n2 == coordCnt) m--;
    else {
      if (m*n == coordCnt) {
	m2 = n2 = 0;
      }
      else if (m2*n2 == coordCnt) {
	m = n = 0;
      }
      else { // give up... can't find the dimensions
	fprintf(stderr,"Error: Unable to find polymesh dimensions.\n");
	return;
      }
    }
  }

  
//  int idx;
  int idxadd = m2*n2;
  int nexti, nextj;
  int endm = (pline->getFlags() & 1) ? m : m-1;
  int endn = (pline->getFlags() & 32) ? n : n-1;

  dimeMatrix matrix;
  state->getMatrix(matrix);

  for (i = 0; i < endm; i++) {
    nexti = i+1;
    if (nexti == m) nexti = 0;
    for (int j = 0; j < endn; j++) {
      nextj = j+1;
      if (nextj == n) nextj = 0;
      
      profile->addQuad(pline->getCoordVertex(idxadd+i*n+j)->getCoords(),
			 pline->getCoordVertex(idxadd+i*n+nextj)->getCoords(),
			 pline->getCoordVertex(idxadd+nexti*n+nextj)->getCoords(),
			 pline->getCoordVertex(idxadd+nexti*n+j)->getCoords(), 
			 pline->getLayerName(), pline->getColorNumber(),
			 &matrix);
    }
  }

  idxadd = 0;
  // copied code from above. I'm too lazy to write a loop or
  // a separate function :)
  m = m2;
  n = n2;
  endm = (pline->getFlags() & 1) ? m : m-1;
  endn = (pline->getFlags() & 32) ? n : n-1;
  
  for (i = 0; i < endm; i++) {
    nexti = i+1;
    if (nexti == m) nexti = 0;
    for (int j = 0; j < endn; j++) {
      nextj = j+1;
      if (nextj == n) nextj = 0;

      profile->addQuad(pline->getCoordVertex(idxadd+i*n+j)->getCoords(),
			 pline->getCoordVertex(idxadd+i*n+nextj)->getCoords(),
			 pline->getCoordVertex(idxadd+nexti*n+nextj)->getCoords(),
			 pline->getCoordVertex(idxadd+nexti*n+j)->getCoords(), 
			 pline->getLayerName(), pline->getColorNumber(),
			 &matrix);
    }
  }
}

static void 
profile_face(dimePolyline *pline, const dimeState *state,
	     BlnProfile3D *profile, dxfConverter *converter)
{
  dimeMatrix matrix;
  state->getMatrix(matrix);

  int i, n = pline->getNumIndexVertices();

  for (i = 0; i < n; i++) {
    dimeVertex *v = pline->getIndexVertex(i);
//    layerData = converter->getLayerData(v);
    dimeVec3f c[4];
    int num = v->numIndices();
    int idx;
    for (int j = 0; j < num; j++) {
      idx = v->getIndex(j);
      if (idx < 0) { // negative means hidden edge
	idx = -idx;
      }
      c[j] = pline->getCoordVertex(idx-1)->getCoords();
    }
    if (num == 3) profile->addTriangle(c[0], c[1], c[2], pline->getLayerName(), pline->getColorNumber(), &matrix);
    else profile->addQuad(c[0], c[1], c[2], c[3], pline->getLayerName(), pline->getColorNumber(), &matrix);
  }
}





















#if DXF_Y_SCALE

static void 
yscale_line_3d(dimePolyline *pline, const dimeState *state,
		dxfLayerData *, dxfConverter *converter)
{
  int i, n = pline->getNumCoordVertices();
  if (n == 0) return;
  
  dimeVertex *v = NULL;
  dimeVec3f v0;

  for (i = 0; i < n; i++) {
    v = pline->getCoordVertex(i); 
    v0 = v->getCoords();
	// масштабируем по правилу:
	// z = z1w + ((y - y1a) / (y2a - y1a)) * (z2w - z1w)
	// double mu = (converter->m_z2w - converter->m_z1w) / (converter->m_y2a - converter->m_y1a); 
	v0.y = converter->m_z1w + converter->m_mu * (v0.y - converter->m_y1a);
	v->setCoords(v0);
  }
}



static void 
yscale_spline(dimePolyline *pline, const dimeState *state,
		dxfLayerData *, dxfConverter *converter)
{
  int i, n = pline->getNumSplineFrameControlPoints();
  if (n == 0) return;
  
  dimeVertex *v = NULL;
  dimeVec3f v0;

  for (i = 0; i < n; i++) {
    v = pline->getSplineFrameControlPoint(i); 
    v0 = v->getCoords();
	// масштабируем по правилу:
	// z = z1w + ((y - y1a) / (y2a - y1a)) * (z2w - z1w)
	// double mu = (converter->m_z2w - converter->m_z1w) / (converter->m_y2a - converter->m_y1a); 
	v0.y = converter->m_z1w + converter->m_mu * (v0.y - converter->m_y1a);
	v->setCoords(v0);
  }
}


static void 
xyscale_line_3d(dimePolyline *pline, const dimeState *state,
		dxfLayerData *, dxfConverter *converter)
{
  int i, n = pline->getNumCoordVertices();
  if (n == 0) return;
  
  dimeVertex *v = NULL;
  dimeVec3f v0;

  for (i = 0; i < n; i++) {
    v = pline->getCoordVertex(i); 
    v0 = v->getCoords();
	// масштабируем по правилу:
	// z = z1w + ((y - y1a) / (y2a - y1a)) * (z2w - z1w)
	// double mu = (converter->m_z2w - converter->m_z1w) / (converter->m_y2a - converter->m_y1a); 
	v0.x = converter->m__x1w + converter->m__xmu * (v0.x - converter->m__x1a);
	v0.y = converter->m__y1w + converter->m__ymu * (v0.y - converter->m__y1a);
	v->setCoords(v0);
  }
}



static void 
xyscale_spline(dimePolyline *pline, const dimeState *state,
		dxfLayerData *, dxfConverter *converter)
{
  int i, n = pline->getNumSplineFrameControlPoints();
  if (n == 0) return;
  
  dimeVertex *v = NULL;
  dimeVec3f v0;

  for (i = 0; i < n; i++) {
    v = pline->getSplineFrameControlPoint(i); 
    v0 = v->getCoords();
	// масштабируем по правилу:
	// z = z1w + ((y - y1a) / (y2a - y1a)) * (z2w - z1w)
	// double mu = (converter->m_z2w - converter->m_z1w) / (converter->m_y2a - converter->m_y1a); 
	v0.x = converter->m__x1w + converter->m__xmu * (v0.x - converter->m__x1a);
	v0.y = converter->m__y1w + converter->m__ymu * (v0.y - converter->m__y1a);
	v->setCoords(v0);
  }
}


#endif