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
#include <dime/entities/3DFace.h>
#include <dime/util/Linear.h>
#include <dime/State.h>
#include <dime/convert/convert.h>

#include "./../surfdoc/src/BlnProfile3D.h"


void 
convert_3dface(const dimeEntity *entity, const dimeState *state, 
	       dxfLayerData *layerData, dxfConverter *)
{
  dimeMatrix matrix;
  state->getMatrix(matrix);
  dime3DFace *face = (dime3DFace*)entity;
  
  dimeVec3f v0, v1, v2, v3;
  face->getVertices(v0, v1, v2, v3);

  if (v2 == v3) {
    layerData->addTriangle(v0, v1, v2, entity->getLayerName(), &matrix);
  }
  else {
    layerData->addQuad(v0, v1, v2, v3, entity->getLayerName(), &matrix);
  }
}

void 
profile_3dface(const dimeEntity *entity, const dimeState *state, 
	       BlnProfile3D * profile, dxfConverter *)
{
  dimeMatrix matrix;
  state->getMatrix(matrix);
  dime3DFace *face = (dime3DFace*)entity;
  
  dimeVec3f v0, v1, v2, v3;
  face->getVertices(v0, v1, v2, v3);

  if (v2 == v3) {
    profile->addTriangle(v0, v1, v2, entity->getLayerName(), entity->getColorNumber(), &matrix);
  }
  else {
    profile->addQuad(v0, v1, v2, v3, entity->getLayerName(), entity->getColorNumber(), &matrix);
  }
}

void 
yscale_3dface(const dimeEntity *entity, const dimeState *state, 
	       dxfLayerData *, dxfConverter * converter)
{
  dimeMatrix matrix;
  state->getMatrix(matrix);
  dime3DFace *face = (dime3DFace*)entity;
  
  dimeVec3f v0, v1, v2, v3;
  face->getVertices(v0, v1, v2, v3);

  // масштабируем по правилу:
  // z = z1w + ((y - y1a) / (y2a - y1a)) * (z2w - z1w)
  //  double mu = (converter->m_z2w - converter->m_z1w) / (converter->m_y2a - converter->m_y1a); 

  v0.y = converter->m_z1w + converter->m_mu * (v0.y - converter->m_y1a);
  v1.y = converter->m_z1w + converter->m_mu * (v1.y - converter->m_y1a);
  v2.y = converter->m_z1w + converter->m_mu * (v2.y - converter->m_y1a);
  v3.y = converter->m_z1w + converter->m_mu * (v3.y - converter->m_y1a);

  face->setVertex(0,v0);
  face->setVertex(1,v1);
  face->setVertex(2,v2);
  face->setVertex(3,v3);
}

void 
xyscale_3dface(const dimeEntity *entity, const dimeState *state, 
	       dxfLayerData *, dxfConverter * converter)
{
  dimeMatrix matrix;
  state->getMatrix(matrix);
  dime3DFace *face = (dime3DFace*)entity;
  
  dimeVec3f v0, v1, v2, v3;
  face->getVertices(v0, v1, v2, v3);

  // масштабируем по правилу:
  // z = z1w + ((y - y1a) / (y2a - y1a)) * (z2w - z1w)
  //  double mu = (converter->m_z2w - converter->m_z1w) / (converter->m_y2a - converter->m_y1a); 

  v0.x = converter->m__x1w + converter->m__xmu * (v0.x - converter->m__x1a);
  v1.x = converter->m__x1w + converter->m__xmu * (v1.x - converter->m__x1a);
  v2.x = converter->m__x1w + converter->m__xmu * (v2.x - converter->m__x1a);
  v3.x = converter->m__x1w + converter->m__xmu * (v3.x - converter->m__x1a);

  v0.y = converter->m__y1w + converter->m__ymu * (v0.y - converter->m__y1a);
  v1.y = converter->m__y1w + converter->m__ymu * (v1.y - converter->m__y1a);
  v2.y = converter->m__y1w + converter->m__ymu * (v2.y - converter->m__y1a);
  v3.y = converter->m__y1w + converter->m__ymu * (v3.y - converter->m__y1a);

  face->setVertex(0,v0);
  face->setVertex(1,v1);
  face->setVertex(2,v2);
  face->setVertex(3,v3);
}