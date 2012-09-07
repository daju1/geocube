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
#include <dime/convert/layerdata.h>
#include "linesegment.h"
#include <dime/entities/LWPolyline.h>
#include <dime/util/Linear.h>
#include <dime/State.h>
#include <dime/convert/convert.h>

void 
convert_lwpolyline(const dimeEntity *entity, const dimeState *state, 
		   dxfLayerData *layerData, dxfConverter *)
{
  dimeLWPolyline *pline = (dimeLWPolyline*)entity;

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

  float elev = pline->getElevation();
  if (!dime_finite(elev)) elev = 0.0f;
  
  int n = pline->getNumVertices();
  if (n <= 0) return;
  
  dxfdouble constantWidth = pline->getConstantWidth();
  const dxfdouble *x = pline->getXCoords();
  const dxfdouble *y = pline->getYCoords();
  const dxfdouble *sw = pline->getStartingWidths();
  const dxfdouble *ew = pline->getEndWidths();
  dimeVec3f v0, v1;
  
#define SET_SEGMENT(s, i0, i1) \
  s.set(dimeVec3f(x[i0], y[i0], elev), \
        dimeVec3f(x[i1], y[i1], elev), \
        sw ? sw[i0] : constantWidth, \
        ew ? ew[i0] : constantWidth, \
        thickness)

  dxfLineSegment segment, nextseg, prevseg;

  bool closed = pline->getFlags() & 1;
  int stop = closed ? n : n-1;
  int next, next2;

  for (int i = 0; i < stop; i++) {
    next = (i+1) % n;
    
    if (i == 0) {
      SET_SEGMENT(segment, i, next);
      if (closed) {
	SET_SEGMENT(prevseg, n-1, 0);
      }
    }
    
    next2 = (i+2) % n;
    SET_SEGMENT(nextseg, next, next2);
    
    segment.convert(i > 0 || closed ? &prevseg : NULL, 
		    i < (stop-1) ? &nextseg : NULL, 
			layerData, &matrix, entity->getLayerName());
    
    prevseg = segment;
    segment = nextseg;
  }
#undef SET_SEGMENT
}


#include "./../surfdoc/src/BlnProfile3D.h"

void 
profile_lwpolyline(const dimeEntity *entity, const dimeState *state, 
		   BlnProfile3D *profile, dxfConverter *)
{
  dimeLWPolyline *pline = (dimeLWPolyline*)entity;

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

  float elev = pline->getElevation();
  if (!dime_finite(elev)) elev = 0.0f;
  
  int n = pline->getNumVertices();
  if (n <= 0) return;
  
  dxfdouble constantWidth = pline->getConstantWidth();
  const dxfdouble *x = pline->getXCoords();
  const dxfdouble *y = pline->getYCoords();
  const dxfdouble *sw = pline->getStartingWidths();
  const dxfdouble *ew = pline->getEndWidths();
  dimeVec3f v0, v1;
  
#define SET_SEGMENT(s, i0, i1) \
  s.set(dimeVec3f(x[i0], y[i0], elev), \
        dimeVec3f(x[i1], y[i1], elev), \
        sw ? sw[i0] : constantWidth, \
        ew ? ew[i0] : constantWidth, \
        thickness)

  dxfLineSegment segment, nextseg, prevseg;

  bool closed = pline->getFlags() & 1;
  int stop = closed ? n : n-1;
  int next, next2;

  for (int i = 0; i < stop; i++) {
    next = (i+1) % n;
    
    if (i == 0) {
      SET_SEGMENT(segment, i, next);
      if (closed) {
	SET_SEGMENT(prevseg, n-1, 0);
      }
    }
    
    next2 = (i+2) % n;
    SET_SEGMENT(nextseg, next, next2);
    
    segment.convert(i > 0 || closed ? &prevseg : NULL, 
		    i < (stop-1) ? &nextseg : NULL, 
			profile, &matrix, entity->getLayerName(), entity->getColorNumber());
    
    prevseg = segment;
    segment = nextseg;
  }
#undef SET_SEGMENT
}






#if DXF_Y_SCALE


void 
yscale_lwpolyline(const dimeEntity *entity, const dimeState *state, 
		   dxfLayerData *, dxfConverter * converter)
{
  dimeLWPolyline *pline = (dimeLWPolyline*)entity;
  
  int n = pline->getNumVertices();
  if (n <= 0) return;
  
  const dxfdouble *x = pline->getXCoords();
  const dxfdouble *y = pline->getYCoords();

  for (int i = 0; i < n; i++) {
	// ������������ �� �������:
	// z = z1w + ((y - y1a) / (y2a - y1a)) * (z2w - z1w)
	// double mu = (converter->m_z2w - converter->m_z1w) / (converter->m_y2a - converter->m_y1a); 
	pline->setYCoord(i, converter->m_z1w + converter->m_mu * (y[i] - converter->m_y1a));
  }
}



void 
xyscale_lwpolyline(const dimeEntity *entity, const dimeState *state, 
		   dxfLayerData *, dxfConverter * converter)
{
  dimeLWPolyline *pline = (dimeLWPolyline*)entity;
  
  int n = pline->getNumVertices();
  if (n <= 0) return;
  
  const dxfdouble *x = pline->getXCoords();
  const dxfdouble *y = pline->getYCoords();

  for (int i = 0; i < n; i++) {
	// ������������ �� �������:
	// z = z1w + ((y - y1a) / (y2a - y1a)) * (z2w - z1w)
	// double mu = (converter->m_z2w - converter->m_z1w) / (converter->m_y2a - converter->m_y1a); 
	pline->setXCoord(i, converter->m__x1w + converter->m__xmu * (x[i] - converter->m__x1a));
	pline->setYCoord(i, converter->m__y1w + converter->m__ymu * (y[i] - converter->m__y1a));
  }
}



#endif