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
#include <dime/entities/Point.h>
#include <dime/util/Linear.h>
#include <dime/State.h>
#include <dime/convert/convert.h>

#include "./../surfdoc/src/BlnProfile3D.h"


void 
convert_point(const dimeEntity *entity, const dimeState *state, 
	      dxfLayerData *layerData, dxfConverter *)
{
  dimePoint *point = (dimePoint*)entity;
  dimeVec3f v0 = point->getCoords();

  dimeParam param;
  if (point->getRecord(38, param)) {
    v0[2] = param.double_data;
  }
  
  dimeMatrix matrix;
  state->getMatrix(matrix);
  
  dxfdouble thickness = point->getThickness();
  if (thickness != 0.0) { // line
    dimeVec3f e = point->getExtrusionDir();
    layerData->addLine(v0, v0 + thickness * e, entity->getLayerName());
  }
  else { // point
    layerData->addPoint(v0, entity->getLayerName());
  }
}




void 
profile_point(const dimeEntity *entity, const dimeState *state, 
	      BlnProfile3D *profile, dxfConverter *)
{
  dimePoint *point = (dimePoint*)entity;
  dimeVec3f v0 = point->getCoords();

  dimeParam param;
  if (point->getRecord(38, param)) {
    v0[2] = param.double_data;
  }
  
  dimeMatrix matrix;
  state->getMatrix(matrix);
  
  dxfdouble thickness = point->getThickness();
  if (thickness != 0.0) { // line
    dimeVec3f e = point->getExtrusionDir();
    profile->addLine(v0, v0 + thickness * e, entity->getLayerName(), entity->getColorNumber());
  }
  else { // point
    profile->addPoint(v0, entity->getLayerName(), entity->getColorNumber());
  }
}



void 
yscale_point(const dimeEntity *entity, const dimeState *state, 
	      dxfLayerData *, dxfConverter * converter)
{
  dimePoint *point = (dimePoint*)entity;
  dimeVec3f v0 = point->getCoords();

  // масштабируем по правилу:
  // z = z1w + ((y - y1a) / (y2a - y1a)) * (z2w - z1w)
  // double mu = (converter->m_z2w - converter->m_z1w) / (converter->m_y2a - converter->m_y1a); 

  v0.y = converter->m_z1w + converter->m_mu * (v0.y - converter->m_y1a);

  point->setCoords(v0);
  /*
  dimeParam param;
  if (point->getRecord(38, param)) {
    v0[2] = param.double_data;
  }
  
  dimeMatrix matrix;
  state->getMatrix(matrix);
  
  dxfdouble thickness = point->getThickness();
  if (thickness != 0.0) { // line
    dimeVec3f e = point->getExtrusionDir();
    layerData->addLine(v0, v0 + thickness * e, entity->getLayerName());
  }
  else { // point
    layerData->addPoint(v0, entity->getLayerName());
  }*/
}



void 
xyscale_point(const dimeEntity *entity, const dimeState *state, 
	      dxfLayerData *, dxfConverter * converter)
{
  dimePoint *point = (dimePoint*)entity;
  dimeVec3f v0 = point->getCoords();

  // масштабируем по правилу:
  // z = z1w + ((y - y1a) / (y2a - y1a)) * (z2w - z1w)
  // double mu = (converter->m_z2w - converter->m_z1w) / (converter->m_y2a - converter->m_y1a); 

  v0.x = converter->m__x1w + converter->m__xmu * (v0.x - converter->m__x1a);
  v0.y = converter->m__y1w + converter->m__ymu * (v0.y - converter->m__y1a);

  point->setCoords(v0);
  /*
  dimeParam param;
  if (point->getRecord(38, param)) {
    v0[2] = param.double_data;
  }
  
  dimeMatrix matrix;
  state->getMatrix(matrix);
  
  dxfdouble thickness = point->getThickness();
  if (thickness != 0.0) { // line
    dimeVec3f e = point->getExtrusionDir();
    layerData->addLine(v0, v0 + thickness * e, entity->getLayerName());
  }
  else { // point
    layerData->addPoint(v0, entity->getLayerName());
  }*/
}


