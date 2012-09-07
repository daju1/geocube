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

#ifndef _DXF2VRML_LAYERDATA_H_
#define _DXF2VRML_LAYERDATA_H_

#include "../configure.h"

#include <dime/util/Linear.h>
#include <dime/util/Array.h>
#include <dime/util/BSPTree.h>


#if DFX_LAYER_FROM_OBJECT
#include "../stdafx.h"
#include "../surfdoc/src/object.h"
#else
#include <stdio.h>
#endif

class DIME_DLL_API dxfLayerData 
#if DFX_LAYER_FROM_OBJECT
	: public Object
#endif

{
public:
  dxfLayerData(const int colidx);
  ~dxfLayerData();

  void setFillmode(const bool fillmode);
  
  void addLine(const dimeVec3f &v0, const dimeVec3f &v1,
	  const char * layername,
	  const dimeMatrix * const matrix = NULL);

  void addPoint(const dimeVec3f &v,
	  const char * layername,
		const dimeMatrix * const matrix = NULL);

  void addTriangle(const dimeVec3f &v0,
		   const dimeVec3f &v1,
		   const dimeVec3f &v2,
		   const char * layername,
		   const dimeMatrix * const matrix = NULL);
  void addQuad(const dimeVec3f &v0,
	       const dimeVec3f &v1,
	       const dimeVec3f &v2,
	       const dimeVec3f &v3,
		   const char * layername,
	       const dimeMatrix * const matrix = NULL);
  
  void writeWrl(FILE *fp, int indent, const bool vrml1,
                const bool only2d);

//private:
public: // 20011001 thammer - please don't kill me for this ;-)

  friend class dime2So;
  friend class dime2Profit;

  bool fillmode;
  int colidx;

  dimeBSPTree facebsp;
  dimeArray <int> faceindices;
  dimeArray <const char *> facelayernames;
  
  dimeBSPTree linebsp;
  dimeArray <int> lineindices;
  dimeArray <const char *> linelayernames;

  dimeArray <dimeVec3f> points;
  dimeArray <const char *> pointlayernames;
#if DFX_LAYER_FROM_OBJECT

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
	dxfLayerData& dxfLayerData::operator=(const dxfLayerData& bp);
	dxfLayerData(const dxfLayerData & bp);
	dxfLayerData(SurfDoc* pSurfDoc);

	void Init(const dxfLayerData& ob);
	virtual void SetLayer(const Layer* layer);
	virtual void CutAndDisvisible(bool positive, double a, double b, double c, double d);
	virtual void CutXYZandDisvisible(int subcube_number, double X, double Y, double Z);
	virtual HTREEITEM AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s = "");
	void OnCreate();

	void Drawing();
	void DrawingPoints();
	void DrawingLines();
	void DrawingFaces();

    //dimeArray <dimeVec3f> view_points;
	//dimeBSPTree view_facebsp;
	//dimeBSPTree view_linebsp;

	double m_zoomX;
	double m_zoomY;
	double m_zoomZ;
	double m_x_mean;
	double m_y_mean; 
	double m_z_mean;
#endif /*DFX_LAYER_FROM_OBJECT*/

};

#endif // _DXF2VRML_LAYERDATA_H_
