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

#ifndef _DXF2VRML_CONVERT_H_
#define _DXF2VRML_CONVERT_H_

#include <stdio.h>
#include <dime/Basic.h>

class dimeModel;
class dxfLayerData;
class dimeState;
class dimeEntity;
class BlnProfile3D;

#include "layerdata.h"

#if DFX_LAYER_FROM_OBJECT
#include "../stdafx.h"
#include "../surfdoc/src/Object.h"
#endif

class DIME_DLL_API dxfConverter

#if DFX_LAYER_FROM_OBJECT
	: public Object
#endif
{
public:
  dxfConverter();
  ~dxfConverter();

  //void setUserData(void *data){m_userdata = data;}
  //void *getUserData(){return m_userdata;}
  
  void setMaxerr(const dxfdouble maxerr) {
    this->maxerr = maxerr;
  }
  void findHeaderVariables(dimeModel &model);
  bool doConvert(dimeModel &model);
  bool doProfileConvert(dimeModel &model,  BlnProfile3D * m_profile);
  bool writeVrml(FILE *out, const bool vrml1 = false,
                 const bool only2d = false);

  void setNumSub(const int num) {
    this->numsub = num;
  }
  int getNumSub() const {
    return numsub;
  }
  dxfdouble getMaxerr() const {
    return this->maxerr;
  }

  void setFillmode(const bool fill) {
    this->fillmode = fill;
  }
  bool getFillmode() const {
    return this->fillmode;
  }

  bool getLayercol() const {
    return this->layercol;
  }
  
  void setLayercol(const bool v) {
    this->layercol = v;
  }

  dxfLayerData *getLayerData(const int colidx);
  dxfLayerData *getLayerData(const dimeEntity *entity);
  dxfLayerData ** getLayerData();
  int getColorIndex(const dimeEntity *entity);
  int getCurrentInsertColorIndex() const {
    return currentInsertColorIndex;
  }

private:
  friend class dime2Profit;
  friend class dime2So;
  friend class BlnProfile3D;

  dxfLayerData *layerData[255];
  int dummy[4];
  dxfdouble maxerr;
  int currentInsertColorIndex;
  dimeEntity *currentPolyline;
  int numsub;
  bool fillmode;
  bool layercol;
  
  bool private_callback(const dimeState * const state, 
			dimeEntity *entity);  
  bool private_callback2(const dimeState * const state, 
			dimeEntity *entity);
  bool private_callback3(const dimeState * const state, 
			dimeEntity *entity);
  static bool dime_callback(const dimeState * const state, 
			    dimeEntity *entity, void *);

  static bool dime_profile_callback(const dimeState * const state, 
			    dimeEntity *entity, void *);

  bool private_profile_callback(const dimeState * const state, 
			dimeEntity *entity);

  BlnProfile3D * m_profile;

#if DXF_Y_SCALE

  static bool dime_xyscale_callback(const dimeState * const state, 
			    dimeEntity *entity, void *);

  bool private_xyscale_callback(const dimeState * const state, 
			dimeEntity *entity);

  static bool dime_yscale_callback(const dimeState * const state, 
			    dimeEntity *entity, void *);

  bool private_yscale_callback(const dimeState * const state, 
			dimeEntity *entity);
#endif




#if DFX_LAYER_FROM_OBJECT
public:
	//##################################################################3
	// virtual functions
	virtual void Draw();
	virtual void ReDraw();
	virtual void EnumObjects(WPARAM wParam, LPARAM lParam, void * p,
		bool (Object::* condition_fun)(),
		void (* callback_fun)(Object* , WPARAM, LPARAM, void * ) );
	virtual void Zoom(double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean);
	virtual bool UpdateExtremums();

	virtual bool SaveAs(){return false;}
	virtual bool SaveAsDat(FILE * stream){return false;}
	virtual bool SaveAsBln(FILE * stream){return false;}
	virtual bool IsSelected(CPoint3 selected_view_pt, 
			double search_radius,
			WhatSelected& ws){return false;}

	virtual void PropertiesDialog();
	virtual bool ColorDialog(void);
	virtual COLORREF GetColor(void);
	virtual void SetColor(COLORREF color);

	dxfConverter& dxfConverter::operator=(const dxfConverter& bp);
	dxfConverter(const dxfConverter & bp);
	dxfConverter(SurfDoc* pSurfDoc);
	void Init(const dxfConverter& ob);
	virtual void SetLayer(const Layer* layer);
	virtual void CutAndDisvisible(bool positive, double a, double b, double c, double d);
	virtual void CutXYZandDisvisible(int subcube_number, double X, double Y, double Z);
	virtual HTREEITEM AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s = "");
	void OnCreate();


	bool Load();
	static bool Loading(dimeModel & model, const char * infile);
	bool Converting(dimeModel & model);
	static bool Saving(dimeModel & model, const char * outfile);
	bool XYScaling(dimeModel & model, 
		double x1w, double x1a, double x2w, double x2a, 
		double y1w, double y1a, double y2w, double y2a);
	bool YScaling(dimeModel & model, double z1w, double y1a, double z2w, double y2a);

	double m_z1w;
	double m_y1a;
	double m_z2w;
	double m_y2a;
	double m_mu;

	double m__y1w;
	double m__y1a;
	double m__y2w;
	double m__y2a;
	double m__ymu;

	double m__x1w;
	double m__x1a;
	double m__x2w;
	double m__x2a;
	double m__xmu;

#endif /*DFX_LAYER_FROM_OBJECT*/

};

#endif // _DXF2VRML_CONVERT_H_
