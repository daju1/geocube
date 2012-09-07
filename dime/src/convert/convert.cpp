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

#include <dime/convert/convert.h>
#include <dime/convert/layerdata.h>
#include "convert_funcs.h"

#include <dime/entities/Insert.h>
#include <dime/sections/HeaderSection.h>
#include <dime/Model.h>
#include <dime/State.h>
#include <dime/Layer.h>

#include <dime/entities/UnknownEntity.h>

/*!
  \class dxfConverter convert.h
  \brief The dxfConverter class offers a simple interface for dxf converting.
  It makes it possible to extract all geometry from dxf files, and store
  it in internal geometry sturctures, which again can be exported as 
  vrml.
*/


/*!
  \fn void dxfConverter::setNumSub(const int num)
  Sets the number of subdivisions for a circle or ellipse. 
  This overrides the value set in dxfConverter::setMaxerr() and 
  should normally not be used

  \sa dxfConverter::getNumSub()
*/

/*!
  \fn int dxfConverter::getNumSub() const
  Returns the numner of subdivisions set by dxfConverter::setNumSub()
*/

/*!
  \fn void dxfConverter::setMaxerr(const dxfdouble maxerr)
  Sets the maximum error allowed when converting circles, arcs
  and ellipses into lines/polygons.
*/

/*!
  \fn dxfdouble dxfConverter::getMaxerr() const
  Returns the maximum allowed error when converting circles, arcs
  ellipses.
*/
  
/*!
  \fn void dxfConverter::setFillmode(const bool fill)
  Sets whether polylines with width and SOLID and TRACE should be filled.
*/

/*!
  \fn bool dxfConverter::getFillmode() const
  Returns whether polylines with width and SOLID and TRACE should be filled.
*/

/*!
  \fn bool dxfConverter::getLayercol() const
  Returns whether only layers should be used (and not color index) when
  converting
*/
  
/*!
  \fn void dxfConverter::setLayercol(const bool v)
  Sets whether only layer (and not color index) should be used when converting.
  This method should normally no be used.
*/

/*!
  \fn int dxfConverter::getCurrentInsertColorIndex() const
  Returns the color index of the current INSERT entity. If no INSERT
  entity is current, the color index 7 (white) will be returned.
*/

/*!
  Constructor
 */
dxfConverter::dxfConverter()
{
	
  this->maxerr = 0.1f;
  this->numsub = -1;
  this->fillmode = true;
  this->layercol = false;
  this->currentInsertColorIndex =  7;
  this->currentPolyline = NULL;
  for (int i = 0; i < 255; i++) layerData[i] = NULL;


#if DFX_LAYER_FROM_OBJECT
  this->OnCreate();
#endif
}

/*!
  Destructor
*/
dxfConverter::~dxfConverter()
{
  for (int i = 0; i < 255; i++) {
    if (layerData[i]) delete layerData[i];
  }
}

/*!
  Returns a dxfLayerData instance for the color with color index \a colidx.
*/
dxfLayerData *
dxfConverter::getLayerData(const int colidx)
{
  assert(colidx >= 1 && colidx <= 255);
  if (layerData[colidx-1] == NULL) {
    layerData[colidx-1] = new dxfLayerData(colidx);
  }
  return layerData[colidx-1];
}

/*!
  Finds the color index for \a entity, and returns the dxfLayerData for it.
*/
dxfLayerData *
dxfConverter::getLayerData(const dimeEntity *entity)
{
	// special case for VERTEX
  if (this->currentPolyline && entity->typeId() == dimeBase::dimeVertexType) {
    if (!(entity->getEntityFlags() & FLAG_COLOR_NUMBER))
      return getLayerData(this->currentPolyline);
  }

  int colidx = getColorIndex(entity);
  if (colidx == 0) { // BYBLOCK
    colidx = this->currentInsertColorIndex;
  }

  // we don't care if layer is turned off (negative color)
  if (colidx < 0) colidx = -colidx;

  if (colidx < 1 || colidx > 255) { // just in case
    fprintf(stderr,"Illegal color number %d. Changed to 7 (white)\n",
	    colidx);
    colidx = 7;
  }

  return getLayerData(colidx);
}

/*!
  Returns a pointer to the dxfLayerData array.
*/
dxfLayerData **
dxfConverter::getLayerData()
{
  return layerData;
}


/*!
  Converts \a model to the internal geometry structures.
  \sa dxfConverter::writeWrl()
*/
bool 
dxfConverter::doConvert(dimeModel &model)
{  
  //
  // remove these 6 lines, and you may merge several dxf
  // files into a single vrml file by calling doConvert() several
  // times before calling writeVrml
  //
  for (int i = 0; i < 255; i++) {
    if (layerData[i]) {
      delete layerData[i];
      layerData[i] = NULL;
    }
  }

  return model.traverseEntities(dime_callback, this, 
				false, true, false);


}

bool 
dxfConverter::doProfileConvert(dimeModel &model, BlnProfile3D * profile)
{  
	this->m_profile = profile;

	if (this->m_profile)
	{
        return model.traverseEntities(dime_profile_callback, this, 
			false, true, false);
	}
	else
		return false;
}

/*!
  Writes the internal geometry structures to \a out.
*/
bool
dxfConverter::writeVrml(FILE *out, const bool vrml1,
                        const bool only2d)
{
#ifndef NOWRLEXPORT
  //
  // write header
  //
  
  if (vrml1) {
    fprintf(out, 
            "#VRML V1.0 ascii\n\n");    
  }
  else {
    fprintf(out, 
            "#VRML V2.0 utf8\n\n");
  }

  //
  // write each used layer/color
  //
  for (int i = 0; i < 255; i++) {
    if (layerData[i] != NULL) {
      layerData[i]->writeWrl(out, 0, vrml1, only2d);
      delete layerData[i]; layerData[i] = NULL;
    }
  }
#endif // NOWRLEXPORT
  return true;
}

/*!
  Finds the correct color index for \a entity. Handles the BYLAYER case.
*/
int
dxfConverter::getColorIndex(const dimeEntity *entity)
{
  int colnum = entity->getColorNumber();
  if (this->layercol || colnum == 256) {
    const dimeLayer *layer = entity->getLayer();
    colnum = layer->getColorNumber();
  }
  return colnum;
}

//
// forward the call to the correct class instance
//
bool 
dxfConverter::dime_callback(const dimeState * const state, 
			    dimeEntity *entity, void *data)
{
//printf("dxfConverter::dime_callback()\n");
	//return ((dxfConverter*)data)->private_callback(state, entity);
	//return ((dxfConverter*)data)->private_callback2(state, entity);
	return ((dxfConverter*)data)->private_callback3(state, entity);
}

#if DXF_Y_SCALE

bool 
dxfConverter::dime_xyscale_callback(const dimeState * const state, 
			    dimeEntity *entity, void *data)
{
	return ((dxfConverter*)data)->private_xyscale_callback(state, entity);
}

bool 
dxfConverter::dime_yscale_callback(const dimeState * const state, 
			    dimeEntity *entity, void *data)
{
	return ((dxfConverter*)data)->private_yscale_callback(state, entity);
}

#endif

bool 
dxfConverter::dime_profile_callback(const dimeState * const state, 
			    dimeEntity *entity, void *data)
{
	return ((dxfConverter*)data)->private_profile_callback(state, entity);
}
bool 
dxfConverter::private_callback3(const dimeState * const state, 
			       dimeEntity *entity)
{ 
//printf("dxfConverter::private_callback()\n");

  if (entity->typeId() == dimeBase::dimePolylineType) {
    this->currentPolyline = entity;
  }

  if (state->getCurrentInsert()) {
    this->currentInsertColorIndex = 
      getColorIndex((dimeEntity*)state->getCurrentInsert());
  }
  else {
    this->currentInsertColorIndex = 7;
  }

  dxfLayerData *ld = getLayerData(entity);


const char * layer_name = entity->getLayerName();
if (!(strcmp(layer_name,"wells") == 0 || strcmp(layer_name,"WELLS") == 0))
return true;

  printf("%s\n", entity->getLayerName());
  // fillmode on by default. entities which will not fill its polygons
  // should turn it off (layerData::addQuad() will create polygons,
  // not lines)
  //
  ld->setFillmode(true);
  
  switch (entity->typeId()) { 
  case dimeBase::dime3DFaceType:
printf("dxfConverter::private_callback(1)\n");
    convert_3dface(entity, state, ld, this);
    break;
  case dimeBase::dimeSolidType:
printf("dxfConverter::private_callback(2)\n");
    convert_solid(entity, state, ld, this);
    break;
  case dimeBase::dimeTraceType:
printf("dxfConverter::private_callback(3)\n");
    convert_solid(entity, state, ld, this);
    break;
  case dimeBase::dimeArcType:
printf("dxfConverter::private_callback(4)\n");
    convert_arc(entity, state, ld, this);
    break;
  case dimeBase::dimeCircleType:
printf("dxfConverter::private_callback(5)\n");
    convert_circle(entity, state, ld, this);
    break;
  case dimeBase::dimeEllipseType:
printf("dxfConverter::private_callback(6)\n");
    convert_ellipse(entity, state, ld, this);
    break;
  case dimeBase::dimeInsertType:
printf("dxfConverter::private_callback(7)\n");
    // handled in traverseEntities
    break;
  case dimeBase::dimeBlockType:
printf("dxfConverter::private_callback(8)\n");
    // handled in traverseEntities
    break;
  case dimeBase::dimeLineType:
printf("dxfConverter::private_callback(9)\n");
    convert_line(entity, state, ld, this);
    break;
  case dimeBase::dimeLWPolylineType:
printf("dxfConverter::private_callback(10)\n");
    convert_lwpolyline(entity, state, ld, this);
    break;
  case dimeBase::dimePointType:
printf("dxfConverter::private_callback(11)\n");
    convert_point(entity, state, ld, this);
    break;
  case dimeBase::dimePolylineType:
 printf("dxfConverter::private_callback(12)\n");
   convert_polyline(entity, state, ld, this);
    break;
  case dimeBase::dimeSplineType:
 printf("dxfConverter::private_callback(13)\n");
   // go for it Raphael! :-)
    break;
  default:
    break;
  }
  return true;
}

//
// handles the callback from the dime-library
//
bool 
dxfConverter::private_callback2(const dimeState * const state, 
			       dimeEntity *entity)
{ 
//printf("dxfConverter::private_callback()\n");

  if (entity->typeId() == dimeBase::dimePolylineType) {
    this->currentPolyline = entity;
  }

  if (state->getCurrentInsert()) {
    this->currentInsertColorIndex = 
      getColorIndex((dimeEntity*)state->getCurrentInsert());
  }
  else {
    this->currentInsertColorIndex = 7;
  }

  dxfLayerData *ld = getLayerData(entity);

  printf("%s\n", entity->getLayerName());

  // fillmode on by default. entities which will not fill its polygons
  // should turn it off (layerData::addQuad() will create polygons,
  // not lines)
  //
  ld->setFillmode(true);
  
  switch (entity->typeId()) { 
  case dimeBase::dime3DFaceType:
printf("dxfConverter::private_callback(1)\n");
    convert_3dface(entity, state, ld, this);
    break;
  case dimeBase::dimeSolidType:
printf("dxfConverter::private_callback(2)\n");
    convert_solid(entity, state, ld, this);
    break;
  case dimeBase::dimeTraceType:
printf("dxfConverter::private_callback(3)\n");
    convert_solid(entity, state, ld, this);
    break;
  case dimeBase::dimeArcType:
printf("dxfConverter::private_callback(4)\n");
    convert_arc(entity, state, ld, this);
    break;
  case dimeBase::dimeCircleType:
printf("dxfConverter::private_callback(5)\n");
    convert_circle(entity, state, ld, this);
    break;
  case dimeBase::dimeEllipseType:
printf("dxfConverter::private_callback(6)\n");
    convert_ellipse(entity, state, ld, this);
    break;
  case dimeBase::dimeInsertType:
printf("dxfConverter::private_callback(7)\n");
    // handled in traverseEntities
    break;
  case dimeBase::dimeBlockType:
printf("dxfConverter::private_callback(8)\n");
    // handled in traverseEntities
    break;
  case dimeBase::dimeLineType:
printf("dxfConverter::private_callback(9)\n");
    convert_line(entity, state, ld, this);
    break;
  case dimeBase::dimeLWPolylineType:
printf("dxfConverter::private_callback(10)\n");
    convert_lwpolyline(entity, state, ld, this);
    break;
  case dimeBase::dimePointType:
printf("dxfConverter::private_callback(11)\n");
    convert_point(entity, state, ld, this);
    break;
  case dimeBase::dimePolylineType:
 printf("dxfConverter::private_callback(12)\n");
   convert_polyline(entity, state, ld, this);
    break;
  case dimeBase::dimeSplineType:
 printf("dxfConverter::private_callback(13)\n");
   // go for it Raphael! :-)
    break;
  default:
    break;
  }
  return true;
}

bool 
dxfConverter::private_callback(const dimeState * const state, 
			       dimeEntity *entity)
{ 
//printf("dxfConverter::private_callback()\n");

  if (entity->typeId() == dimeBase::dimePolylineType) {
    this->currentPolyline = entity;
  }

  if (state->getCurrentInsert()) {
    this->currentInsertColorIndex = 
      getColorIndex((dimeEntity*)state->getCurrentInsert());
  }
  else {
    this->currentInsertColorIndex = 7;
  }

  dxfLayerData *ld = getLayerData(entity);

  // fillmode on by default. entities which will not fill its polygons
  // should turn it off (layerData::addQuad() will create polygons,
  // not lines)
  //
  ld->setFillmode(true);
  
  switch (entity->typeId()) { 
  case dimeBase::dime3DFaceType:
printf("dxfConverter::private_callback(1)\n");
    convert_3dface(entity, state, ld, this);
    break;
  case dimeBase::dimeSolidType:
printf("dxfConverter::private_callback(2)\n");
    convert_solid(entity, state, ld, this);
    break;
  case dimeBase::dimeTraceType:
printf("dxfConverter::private_callback(3)\n");
    convert_solid(entity, state, ld, this);
    break;
  case dimeBase::dimeArcType:
printf("dxfConverter::private_callback(4)\n");
    convert_arc(entity, state, ld, this);
    break;
  case dimeBase::dimeCircleType:
printf("dxfConverter::private_callback(5)\n");
    convert_circle(entity, state, ld, this);
    break;
  case dimeBase::dimeEllipseType:
printf("dxfConverter::private_callback(6)\n");
    convert_ellipse(entity, state, ld, this);
    break;
  case dimeBase::dimeInsertType:
printf("dxfConverter::private_callback(7)\n");
    // handled in traverseEntities
    break;
  case dimeBase::dimeBlockType:
printf("dxfConverter::private_callback(8)\n");
    // handled in traverseEntities
    break;
  case dimeBase::dimeLineType:
printf("dxfConverter::private_callback(9)\n");
    convert_line(entity, state, ld, this);
    break;
  case dimeBase::dimeLWPolylineType:
printf("dxfConverter::private_callback(10)\n");
    convert_lwpolyline(entity, state, ld, this);
    break;
  case dimeBase::dimePointType:
printf("dxfConverter::private_callback(11)\n");
    convert_point(entity, state, ld, this);
    break;
  case dimeBase::dimePolylineType:
 printf("dxfConverter::private_callback(12)\n");
   convert_polyline(entity, state, ld, this);
    break;
  case dimeBase::dimeSplineType:
 printf("dxfConverter::private_callback(13)\n");
   // go for it Raphael! :-)
    break;
  default:
    break;
  }
  return true;
}

bool 
dxfConverter::private_profile_callback(const dimeState * const state, 
			       dimeEntity *entity)
{ 
//printf("dxfConverter::private_callback()\n");

  if (entity->typeId() == dimeBase::dimePolylineType) {
    this->currentPolyline = entity;
  }

  if (state->getCurrentInsert()) {
    this->currentInsertColorIndex = 
      getColorIndex((dimeEntity*)state->getCurrentInsert());
  }
  else {
    this->currentInsertColorIndex = 7;
  }

  //dxfLayerData *ld = getLayerData(entity);
  BlnProfile3D * ld = this->m_profile;

  // fillmode on by default. entities which will not fill its polygons
  // should turn it off (layerData::addQuad() will create polygons,
  // not lines)
  //
  //ld->setFillmode(true);
  
  switch (entity->typeId()) { 
  case dimeBase::dime3DFaceType:
printf("dxfConverter::private_callback(1)\n");
    profile_3dface(entity, state, ld, this);
    break;
  case dimeBase::dimeSolidType:
printf("dxfConverter::private_callback(2)\n");
    profile_solid(entity, state, ld, this);
    break;
  case dimeBase::dimeTraceType:
printf("dxfConverter::private_callback(3)\n");
    profile_solid(entity, state, ld, this);
    break;
  case dimeBase::dimeArcType:
printf("dxfConverter::private_callback(4)\n");
    profile_arc(entity, state, ld, this);
    break;
  case dimeBase::dimeCircleType:
printf("dxfConverter::private_callback(5)\n");
    profile_circle(entity, state, ld, this);
    break;
  case dimeBase::dimeEllipseType:
printf("dxfConverter::private_callback(6)\n");
    profile_ellipse(entity, state, ld, this);
    break;
  case dimeBase::dimeInsertType:
printf("dxfConverter::private_callback(7)\n");
    // handled in traverseEntities
    break;
  case dimeBase::dimeBlockType:
printf("dxfConverter::private_callback(8)\n");
    // handled in traverseEntities
    break;
  case dimeBase::dimeLineType:
//printf("dxfConverter::private_callback(9)\n");
    profile_line(entity, state, ld, this);
    break;
  case dimeBase::dimeLWPolylineType:
printf("dxfConverter::private_callback(10)\n");
    profile_lwpolyline(entity, state, ld, this);
    break;
  case dimeBase::dimePointType:
printf("dxfConverter::private_callback(11)\n");
    profile_point(entity, state, ld, this);
    break;
  case dimeBase::dimePolylineType:
 printf("dxfConverter::private_callback(12)\n");
    profile_polyline(entity, state, ld, this);
    break;
  case dimeBase::dimeSplineType:
 printf("dxfConverter::private_callback(13)\n");
   // go for it Raphael! :-)
    break;
  case dimeBase::dimeUnknownEntityType:
	  {
		  printf("dxfConverter::private_callback(default = %d name = %s)\n", entity->typeId(), ((dimeUnknownEntity*)entity)->getEntityName());
		  if (strcmp("TEXT", ((dimeUnknownEntity*)entity)->getEntityName()) == 0)
		  {
			  dimeParam param;
			  if (((dimeUnknownEntity*)entity)->getRecord(20, param)) 
			  {
				  double y = param.double_data;
					// масштабируем по правилу:
					// z = z1w + ((y - y1a) / (y2a - y1a)) * (z2w - z1w)
					// double mu = (converter->m_z2w - converter->m_z1w) / (converter->m_y2a - converter->m_y1a); 

					y = this->m_z1w + this->m_mu * (y - this->m_y1a);
					param.double_data = y;
					((dimeUnknownEntity*)entity)->setRecord(20, param); 
			  }
		  }
	  }
    break;
  default:
 printf("dxfConverter::private_callback(default = %d)\n", entity->typeId());
    break;
  }
  return true;
}






#if DXF_Y_SCALE
bool 
dxfConverter::private_xyscale_callback(const dimeState * const state, 
			       dimeEntity *entity)
{ 
//printf("dxfConverter::private_callback()\n");

  if (entity->typeId() == dimeBase::dimePolylineType) {
    this->currentPolyline = entity;
  }

  if (state->getCurrentInsert()) {
    this->currentInsertColorIndex = 
      getColorIndex((dimeEntity*)state->getCurrentInsert());
  }
  else {
    this->currentInsertColorIndex = 7;
  }

  //dxfLayerData *ld = getLayerData(entity);
  dxfLayerData *ld = NULL;

  // fillmode on by default. entities which will not fill its polygons
  // should turn it off (layerData::addQuad() will create polygons,
  // not lines)
  //
  //ld->setFillmode(true);
  
  switch (entity->typeId()) { 
  case dimeBase::dime3DFaceType:
printf("dxfConverter::private_callback(1)\n");
    xyscale_3dface(entity, state, ld, this);
    break;
  case dimeBase::dimeSolidType:
printf("dxfConverter::private_callback(2)\n");
    xyscale_solid(entity, state, ld, this);
    break;
  case dimeBase::dimeTraceType:
printf("dxfConverter::private_callback(3)\n");
    xyscale_solid(entity, state, ld, this);
    break;
  case dimeBase::dimeArcType:
printf("dxfConverter::private_callback(4)\n");
    xyscale_arc(entity, state, ld, this);
    break;
  case dimeBase::dimeCircleType:
printf("dxfConverter::private_callback(5)\n");
    xyscale_circle(entity, state, ld, this);
    break;
  case dimeBase::dimeEllipseType:
printf("dxfConverter::private_callback(6)\n");
    xyscale_ellipse(entity, state, ld, this);
    break;
  case dimeBase::dimeInsertType:
printf("dxfConverter::private_callback(7)\n");
    // handled in traverseEntities
    break;
  case dimeBase::dimeBlockType:
printf("dxfConverter::private_callback(8)\n");
    // handled in traverseEntities
    break;
  case dimeBase::dimeLineType:
//printf("dxfConverter::private_callback(9)\n");
    xyscale_line(entity, state, ld, this);
    break;
  case dimeBase::dimeLWPolylineType:
printf("dxfConverter::private_callback(10)\n");
    xyscale_lwpolyline(entity, state, ld, this);
    break;
  case dimeBase::dimePointType:
printf("dxfConverter::private_callback(11)\n");
    xyscale_point(entity, state, ld, this);
    break;
  case dimeBase::dimePolylineType:
 printf("dxfConverter::private_callback(12)\n");
    xyscale_polyline(entity, state, ld, this);
    break;
  case dimeBase::dimeSplineType:
 printf("dxfConverter::private_callback(13)\n");
   // go for it Raphael! :-)
    break;
  case dimeBase::dimeUnknownEntityType:
	  {
		  printf("dxfConverter::private_callback(default = %d name = %s)\n", entity->typeId(), ((dimeUnknownEntity*)entity)->getEntityName());
		  if (strcmp("TEXT", ((dimeUnknownEntity*)entity)->getEntityName()) == 0)
		  {
			  dimeParam param;
			  if (((dimeUnknownEntity*)entity)->getRecord(10, param)) 
			  {
				  double x = param.double_data;
					// масштабируем по правилу:
					// z = z1w + ((y - y1a) / (y2a - y1a)) * (z2w - z1w)
					// double mu = (converter->m_z2w - converter->m_z1w) / (converter->m_y2a - converter->m_y1a); 

					x = this->m__x1w + this->m__xmu * (x - this->m__x1a);
					param.double_data = x;
					((dimeUnknownEntity*)entity)->setRecord(10, param); 
			  }
			  if (((dimeUnknownEntity*)entity)->getRecord(20, param)) 
			  {
				  double y = param.double_data;
					// масштабируем по правилу:
					// z = z1w + ((y - y1a) / (y2a - y1a)) * (z2w - z1w)
					// double mu = (converter->m_z2w - converter->m_z1w) / (converter->m_y2a - converter->m_y1a); 

					y = this->m__y1w + this->m__ymu * (y - this->m__y1a);
					param.double_data = y;
					((dimeUnknownEntity*)entity)->setRecord(20, param); 
			  }
		  }
	  }
    break;
  default:
 printf("dxfConverter::private_callback(default = %d)\n", entity->typeId());
    break;
  }
  return true;
}





bool 
dxfConverter::private_yscale_callback(const dimeState * const state, 
			       dimeEntity *entity)
{ 
//printf("dxfConverter::private_callback()\n");

  if (entity->typeId() == dimeBase::dimePolylineType) {
    this->currentPolyline = entity;
  }

  if (state->getCurrentInsert()) {
    this->currentInsertColorIndex = 
      getColorIndex((dimeEntity*)state->getCurrentInsert());
  }
  else {
    this->currentInsertColorIndex = 7;
  }

  //dxfLayerData *ld = getLayerData(entity);
  dxfLayerData *ld = NULL;

  // fillmode on by default. entities which will not fill its polygons
  // should turn it off (layerData::addQuad() will create polygons,
  // not lines)
  //
  //ld->setFillmode(true);
  
  switch (entity->typeId()) { 
  case dimeBase::dime3DFaceType:
printf("dxfConverter::private_callback(1)\n");
    yscale_3dface(entity, state, ld, this);
    break;
  case dimeBase::dimeSolidType:
printf("dxfConverter::private_callback(2)\n");
    yscale_solid(entity, state, ld, this);
    break;
  case dimeBase::dimeTraceType:
printf("dxfConverter::private_callback(3)\n");
    yscale_solid(entity, state, ld, this);
    break;
  case dimeBase::dimeArcType:
printf("dxfConverter::private_callback(4)\n");
    yscale_arc(entity, state, ld, this);
    break;
  case dimeBase::dimeCircleType:
printf("dxfConverter::private_callback(5)\n");
    yscale_circle(entity, state, ld, this);
    break;
  case dimeBase::dimeEllipseType:
printf("dxfConverter::private_callback(6)\n");
    yscale_ellipse(entity, state, ld, this);
    break;
  case dimeBase::dimeInsertType:
printf("dxfConverter::private_callback(7)\n");
    // handled in traverseEntities
    break;
  case dimeBase::dimeBlockType:
printf("dxfConverter::private_callback(8)\n");
    // handled in traverseEntities
    break;
  case dimeBase::dimeLineType:
//printf("dxfConverter::private_callback(9)\n");
    yscale_line(entity, state, ld, this);
    break;
  case dimeBase::dimeLWPolylineType:
printf("dxfConverter::private_callback(10)\n");
    yscale_lwpolyline(entity, state, ld, this);
    break;
  case dimeBase::dimePointType:
printf("dxfConverter::private_callback(11)\n");
    yscale_point(entity, state, ld, this);
    break;
  case dimeBase::dimePolylineType:
 printf("dxfConverter::private_callback(12)\n");
    yscale_polyline(entity, state, ld, this);
    break;
  case dimeBase::dimeSplineType:
 printf("dxfConverter::private_callback(13)\n");
   // go for it Raphael! :-)
    break;
  case dimeBase::dimeUnknownEntityType:
	  {
		  printf("dxfConverter::private_callback(default = %d name = %s)\n", entity->typeId(), ((dimeUnknownEntity*)entity)->getEntityName());
		  if (strcmp("TEXT", ((dimeUnknownEntity*)entity)->getEntityName()) == 0)
		  {
			  dimeParam param;
			  if (((dimeUnknownEntity*)entity)->getRecord(20, param)) 
			  {
				  double y = param.double_data;
					// масштабируем по правилу:
					// z = z1w + ((y - y1a) / (y2a - y1a)) * (z2w - z1w)
					// double mu = (converter->m_z2w - converter->m_z1w) / (converter->m_y2a - converter->m_y1a); 

					y = this->m_z1w + this->m_mu * (y - this->m_y1a);
					param.double_data = y;
					((dimeUnknownEntity*)entity)->setRecord(20, param); 
			  }
		  }
	  }
    break;
  default:
 printf("dxfConverter::private_callback(default = %d)\n", entity->typeId());
    break;
  }
  return true;
}




#endif
/*!
  Finds the state of supported header variables in \a model. This
  method should be called before dxfxConverter::doConvert()
*/
void 
dxfConverter::findHeaderVariables(dimeModel &model)
{
  dimeHeaderSection *hs = (dimeHeaderSection*)
    model.findSection("HEADER");

  if (hs) {
    dimeParam param;
    int groupcode;

    if (hs->getVariable("$FILLMODE", &groupcode, &param, 1) == 1) {
      if (groupcode == 70)
	this->fillmode = (bool) param.int16_data;
    }
  }
}


#if DFX_LAYER_FROM_OBJECT
#include <dime/Input.h>
#include <dime/Output.h>
#include "./../tools/src/filedlg.h"
#include "./../surfdoc/src/surfdoc.h"
bool dxfConverter::XYScaling(dimeModel & model, 
							 double x1w, double x1a, double x2w, double x2a,
							 double y1w, double y1a, double y2w, double y2a)
{
	// масштабирование по XY координатам для приведения автокадовских карт к мировым координатам
	// x1a - меньшая X коррдината в автокаде
	// x1w - соответствующая ей мировая X координата
	// x2a - большая X коррдината в автокаде
	// x2w - соответствующая ей мировая X координата

	// y1a - меньшая Y коррдината в автокаде
	// y1w - соответствующая ей мировая Y координата
	// y2a - большая Y коррдината в автокаде
	// y2w - соответствующая ей мировая Y координата
	// масштабируем по правилу:
	// xw = x1w + ((xa - x1a) / (x2a - x1a)) * (x2w - x1w)
	// yw = y1w + ((ya - y1a) / (y2a - y1a)) * (y2w - y1w)
	m__x1w = x1w;
	m__x1a = x1a;
	m__x2w = x2w;
	m__x2a = x2a;

	m__y1w = y1w;
	m__y1a = y1a;
	m__y2w = y2w;
	m__y2a = y2a;
	m__xmu = (m__x2w - m__x1w) / (m__x2a - m__x1a); 
	m__ymu = (m__y2w - m__y1w) / (m__y2a - m__y1a); 
	// z = z1w + m_mu * ((y - y1a) 

	return model.traverseEntities(dime_xyscale_callback, this, 
		false, true, false);

}
bool dxfConverter::YScaling(dimeModel & model, double z1w, double y1a, double z2w, double y2a)
{
	// масштабирование по вертикальной координате для приведения автокадовских профилей к мировым альтитудам
	// y1a - нижняя коррдината в автокаде
	// z1w - соответствующая ей мировая альтитуда
	// y2a - верхняя коррдината в автокаде
	// z2w - соответствующая ей мировая альтитуда
	// масштабируем по правилу:
	// z = z1w + ((y - y1a) / (y2a - y1a)) * (z2w - z1w)
	m_z1w = z1w;
	m_y1a = y1a;
	m_z2w = z2w;
	m_y2a = y2a;
	m_mu = (m_z2w - m_z1w) / (m_y2a - m_y1a); 
	// z = z1w + m_mu * ((y - y1a) 

	return model.traverseEntities(dime_yscale_callback, this, 
		false, true, false);

}
bool dxfConverter::Saving(dimeModel & model, const char * outfile)
{
	bool result = true;
  // DIME: initialize output file
  dimeOutput out;
  if (!outfile || !out.setFilename(outfile)) {
    out.setFileHandle(stdout);
	result = false;
  }
  // DIME: write the model to file  
  model.write(&out);
  return result;
}
bool dxfConverter::Loading(dimeModel & model, const char * infile)
{
	dimeInput in;

//	in.binary = true;
	//
	// open file for reading (or use stdin) 
	//
	if (infile == NULL) {
		if (!in.setFileHandle(stdin)) {
			fprintf(stderr,"Unexpected error opening file from stdin\n");
			return false;
		}
	}
	else {
		if (!in.setFile(infile)) {
			//fprintf(stderr,"First Error opening file for reading: %s\n", infile);
			//_ASSERTE(_osfile(filedes) & FOPEN);
			if (!in.setFile(infile)) {
				fprintf(stderr,"Error opening file for reading: %s\n", infile);
				return false;
			}
		}
	}
	//
	// try reading the file
	//
	
    
	if (!model.read(&in)) {
		fprintf(stderr,"DXF read error in line: %d\n", in.getFilePosition());
		return false;
	}
	else
	{
		fprintf(stderr,"DXF read: %s\n", infile);
	}
	return true;
}
bool dxfConverter::Converting(dimeModel & model)
{
  	/*TCHAR filter[] =     
		TEXT("Geo Surf File (*.vrml)\0*.vrml\0")
		TEXT("All Files (*.*)\0*.*\0");
	sprintf(fileNameBuf, "\0");
	DWORD nFilterIndex = 0;
	if (SaveFileDlg(0, fileNameBuf, filter, nFilterIndex) == S_OK)*/
	//{
		//char * outfile = fileNameBuf;
	float maxerr = 0.1f;
	int sub = -1;  
	//int i = 1;

	int fillmode = 0;
	int layercol = 0;
	//  bool vrml1 = true;
	bool only2d = false;
	//
	// open output file (or use stdout)
	//
	/*FILE *out = stdout;
	if (outfile != NULL) {
	out = fopen(outfile, "wb");
	if (!out) {
	fprintf(stderr,"Error opening file for writing: %s\n", outfile);
	return -1;
	}
	}*/

	//dxfConverter converter;
	//converter.setUserData((void *) pSurfDoc);
	this->findHeaderVariables(model);
	this->setMaxerr(maxerr);
	if (sub > 0) this->setNumSub(sub);

	//
	// override $FILLMODE header variable unless user tells us not to.
	// The $FILLMODE variable just specifies if AutoCAD was in fillmode 
	// when the user saved the DXF file, and may therefore not be what
	// we want when converting files.
	//
	if (fillmode == 0) this->setFillmode(true);

	if (layercol) this->setLayercol(true);

	//  dxfConverter::m_dfx_Convert_mode = dxfConverter::dfx_Convert_mode::convert_to_SurfDoc;


	if (!this->doConvert(model)) {
		fprintf(stderr,"Error during conversion\n");
		//    if (out && out != stdout) fclose(out);
		return false;
	}

	//  converter.writeVrml(out, vrml1, only2d);

	//  if (out != stdout) fclose(out);

	return true;
}
bool dxfConverter::Load()
{
	char lpstrFile[1024];
	if (OpenFileDlg(0, "AutoCAD DXF (*.dxf)\0*.dxf\0All files \0*.*\0", lpstrFile) == S_OK)
	{
		dimeModel model; 
		if( dxfConverter::Loading(model, lpstrFile))
			return this->Converting(model);
	}
	return false;
}

void dxfConverter::PropertiesDialog()
{
	MessageBox(0, "PropertiesDialog", "dxfConverter" , 0);

}

bool dxfConverter::ColorDialog(void)
{
	return false;
}

COLORREF dxfConverter::GetColor(void)
{
	return COLORREF();
}

void dxfConverter::SetColor(COLORREF color)
{
}
void dxfConverter::CutAndDisvisible(bool positive, double a, double b, double c, double d)
{
}
void dxfConverter::CutXYZandDisvisible(int subcube_number, double X, double Y, double Z)
{
}
void dxfConverter::Draw()
{
	for (int i = 0; i < 255; i++) {
		if (layerData[i]) layerData[i]->Draw();
	}
}

void dxfConverter::ReDraw(void)
{
	for (int i = 0; i < 255; i++) {
		if (layerData[i]) layerData[i]->ReDraw();
	}
}
void dxfConverter::Init(const dxfConverter& ob)
{	
  for (int i = 0; i < 255; i++) {
    if (layerData[i]) {
      delete layerData[i];
      layerData[i] = NULL;
    }
  }
  for (int i = 0; i < 255; i++) {
    if (ob.layerData[i]) {
      this->layerData[i] = new dxfLayerData(*ob.layerData[i]);
    }
  }  
}
dxfConverter& dxfConverter::operator=(const dxfConverter& ob)
{
	if (this == &ob)
		return *this;
	this->Init(ob);
	return *this;
}
dxfConverter::dxfConverter(const dxfConverter & ob)
{
	this->Init(ob);
}
void dxfConverter::OnCreate(void)
{
	this->m_object_type = Object::object_type::dfx_converter;
	this->m_object_version = 1;
	this->m_max_object_version = 1;
}
dxfConverter::dxfConverter(SurfDoc* pSurfDoc)
{
	this->m_pSurfDoc				= pSurfDoc;

	this->maxerr = 0.1f;
	this->numsub = -1;
	this->fillmode = true;
	this->layercol = false;
	this->currentInsertColorIndex =  7;
	this->currentPolyline = NULL;
	for (int i = 0; i < 255; i++) layerData[i] = NULL;

	this->OnCreate();
}
void dxfConverter::EnumObjects(WPARAM wParam, LPARAM lParam, void * p,
		bool (Object::* condition_fun)(),
		void (* callback_fun)(Object*, WPARAM , LPARAM, void * ) )
{
	for (int i = 0; i < 255; i++) {
		if (this->layerData[i]) {
			this->layerData[i]->EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		}
	} 
	if ((this->*condition_fun)())
	{
		(* callback_fun)(this, wParam, lParam, p);
	}
}
void dxfConverter::SetLayer(const Layer* layer)
{
	this->Object::SetLayer_NonVirtual(layer);
	for (int i = 0; i < 255; i++) {
		if (this->layerData[i]) {
			this->layerData[i]->SetLayer(layer);
		}
	} 
}
bool dxfConverter::UpdateExtremums()
{
//printf("dxfConverter::UpdateExtremums()\n");
	vector<CPoint3> vptmax,vptmin;
	for (int i = 0; i < 255; i++) {
		if (this->layerData[i]) {
			this->layerData[i]->UpdateExtremums();
			vptmax.push_back(this->layerData[i]->GetMax());
			vptmin.push_back(this->layerData[i]->GetMin());
		}
	} 
	return this->Object::UpdateExtremums(vptmax,vptmin);
}

void dxfConverter::Zoom(double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean)
{
//printf("dxfConverter::Zoom()\n");
	for (int i = 0; i < 255; i++) {
		if (this->layerData[i]) {
			this->layerData[i]->Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,
				y_mean,
				z_mean
				);
		}
	} 
}

HTREEITEM dxfConverter::AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s)
{
printf("dxfConverter::AddItem_ToTree()\n");
    char szItemText[128]; // label text of tree-view item 
	//====== Размеры изображаемого объекта
	sprintf(szItemText, "dxfConverter");
	Object * pObject = dynamic_cast<Object *> (this);
	//=============================================================
	// Add the item to the tree-view control. 
	HTREEITEM h2 = AddItemToTree(hwndTV, szItemText, pObject, h1); 
	//=============================================================
	//HTREEITEM h3 = AddObjectListItem(hwndTV, szItemText, &this->m_dxfLayerData_ObjectList, h2); 

	for (int i = 0; i < 255; i++) {
		if (this->layerData[i]) {
			this->layerData[i]->AddItem_ToTree(hwndTV,	h2);
			//this->layerData[i]->AddItem_ToTree(hwndTV,	h3);
		}
	} 
	return NULL;
}
#endif /*DFX_LAYER_FROM_OBJECT*/
