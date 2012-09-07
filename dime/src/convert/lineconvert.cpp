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
#include <dime/entities/Line.h>
#include <dime/util/Linear.h>
#include <dime/State.h>
#include <dime/convert/convert.h>

#include "./../surfdoc/src/BlnProfile3D.h"


void 
convert_line(const dimeEntity *entity, const dimeState *state, 
	     dxfLayerData *layerData, dxfConverter *)
{
  dimeLine *line = (dimeLine*)entity;
  
  dxfdouble thickness;
  dimeVec3f v0, v1;

  dimeMatrix matrix;
  state->getMatrix(matrix);
 
  v0 = line->getCoords(0);
  v1 = line->getCoords(1);

  dimeParam param;
  if (line->getRecord(38, param)) {
    v0[2] = param.double_data;
    v1[2] = param.double_data;
  }

  thickness = line->getThickness();

  if (thickness != 0.0) {
    dimeVec3f v2, v3;
    dimeVec3f e = line->getExtrusionDir();
    v2 = v0 + e * thickness;
    v3 = v1 + e * thickness;

    layerData->addQuad(v0, v1, v3, v2, entity->getLayerName(), &matrix);
  }
  else {
    layerData->addLine(v0, v1, entity->getLayerName(), &matrix);
  }
}


void 
profile_line(const dimeEntity *entity, const dimeState *state, 
	     BlnProfile3D *profile, dxfConverter *)
{
  dimeLine *line = (dimeLine*)entity;
  
  dxfdouble thickness;
  dimeVec3f v0, v1;

  dimeMatrix matrix;
  state->getMatrix(matrix);
 
  v0 = line->getCoords(0);
  v1 = line->getCoords(1);

  dimeParam param;
  if (line->getRecord(38, param)) {
    v0[2] = param.double_data;
    v1[2] = param.double_data;
  }

  thickness = line->getThickness();

  if (thickness != 0.0) {
    dimeVec3f v2, v3;
    dimeVec3f e = line->getExtrusionDir();
    v2 = v0 + e * thickness;
    v3 = v1 + e * thickness;

	profile->addQuad(v0, v1, v3, v2, entity->getLayerName(), entity->getColorNumber(), &matrix);
  }
  else {
    profile->addLine(v0, v1, entity->getLayerName(), entity->getColorNumber(), &matrix);
  }
}


void 
yscale_line(const dimeEntity *entity, const dimeState *state, 
	     dxfLayerData *, dxfConverter * converter)
{
  dimeLine *line = (dimeLine*)entity;
  
//  dxfdouble thickness;
  dimeVec3f v0, v1;

  dimeMatrix matrix;
  state->getMatrix(matrix);
 
  v0 = line->getCoords(0);
  v1 = line->getCoords(1);
  // масштабируем по правилу:
  // z = z1w + ((y - y1a) / (y2a - y1a)) * (z2w - z1w)
  // double mu = (converter->m_z2w - converter->m_z1w) / (converter->m_y2a - converter->m_y1a); 

  v0.y = converter->m_z1w + converter->m_mu * (v0.y - converter->m_y1a);
  v1.y = converter->m_z1w + converter->m_mu * (v1.y - converter->m_y1a);

  line->setCoords(0,v0);
  line->setCoords(1,v1);

/*
  dimeParam param;
  if (line->getRecord(38, param)) {
    v0[2] = param.double_data;
    v1[2] = param.double_data;
  }

  thickness = line->getThickness();

  if (thickness != 0.0) {
    dimeVec3f v2, v3;
    dimeVec3f e = line->getExtrusionDir();
    v2 = v0 + e * thickness;
    v3 = v1 + e * thickness;

    layerData->addQuad(v0, v1, v3, v2, entity->getLayerName(), &matrix);
  }
  else {
    layerData->addLine(v0, v1, entity->getLayerName(), &matrix);
  }*/
}


void 
xyscale_line(const dimeEntity *entity, const dimeState *state, 
	     dxfLayerData *, dxfConverter * converter)
{
  dimeLine *line = (dimeLine*)entity;
  
//  dxfdouble thickness;
  dimeVec3f v0, v1;

  dimeMatrix matrix;
  state->getMatrix(matrix);
 
  v0 = line->getCoords(0);
  v1 = line->getCoords(1);
  // масштабируем по правилу:
  // z = z1w + ((y - y1a) / (y2a - y1a)) * (z2w - z1w)
  // double mu = (converter->m_z2w - converter->m_z1w) / (converter->m_y2a - converter->m_y1a); 

  v0.x = converter->m__x1w + converter->m__xmu * (v0.x - converter->m__x1a);
  v1.x = converter->m__x1w + converter->m__xmu * (v1.x - converter->m__x1a);

  v0.y = converter->m__y1w + converter->m__ymu * (v0.y - converter->m__y1a);
  v1.y = converter->m__y1w + converter->m__ymu * (v1.y - converter->m__y1a);

  line->setCoords(0,v0);
  line->setCoords(1,v1);

/*
  dimeParam param;
  if (line->getRecord(38, param)) {
    v0[2] = param.double_data;
    v1[2] = param.double_data;
  }

  thickness = line->getThickness();

  if (thickness != 0.0) {
    dimeVec3f v2, v3;
    dimeVec3f e = line->getExtrusionDir();
    v2 = v0 + e * thickness;
    v3 = v1 + e * thickness;

    layerData->addQuad(v0, v1, v3, v2, entity->getLayerName(), &matrix);
  }
  else {
    layerData->addLine(v0, v1, entity->getLayerName(), &matrix);
  }*/
}
