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

#include <dime/convert/layerdata.h>
#include <dime/Layer.h>

/*!
  \class dxfLayerData layerdata.h
  \brief The dxfLayerData class handles all geometry for a given color index.
  DXF geometry is grouped into different colors, as this is a normal way
  to group geometry data, and especially vrml data.

  The geometry can be either points, lines or polygons.
*/

/*!
  Constructor
*/
dxfLayerData::dxfLayerData(const int colidx)
{
  this->fillmode = true;
  this->colidx = colidx;

#if DFX_LAYER_FROM_OBJECT
  this->OnCreate();
#endif
}

/*!
  Destructor.
*/
dxfLayerData::~dxfLayerData()
{
}

/*!
  Sets the fillmode for this layer. If fillmode is set (the default)
  polylines with width and/or height will be converter to polygons
  and not lines. The same goes for the SOLID and TRACE entities.
*/
void 
dxfLayerData::setFillmode(const bool fillmode)
{
  this->fillmode = fillmode;
}

/*!
  Adds a line to this layer's geometry. If \a matrix != NULL, the
  points will be transformed by this matrix before they are added.
*/
void 
dxfLayerData::addLine(const dimeVec3f &v0, const dimeVec3f &v1,
					  const char * layername,
		      const dimeMatrix * const matrix)
{
/*printf("dxfLayerData::addLine() v0 = [%f %f %f] v1 = [%f %f %f] matrix = %08x\n", 
	   v0[0], v0[1], v0[2], v1[0], v1[1], v1[2], matrix);
*/
	
  int i0, i1;
  
  if (matrix) {
    dimeVec3f t0, t1;
    matrix->multMatrixVec(v0, t0);
    matrix->multMatrixVec(v1, t1);
    i0 = linebsp.addPoint(t0);
    i1 = linebsp.addPoint(t1);  
  }
  else {
    i0 = linebsp.addPoint(v0);
    i1 = linebsp.addPoint(v1);
  }
  
  //
  // take care of line strips (more effective than single lines)
  //
  if (lineindices.count() && lineindices[lineindices.count()-1] == i0) {
    lineindices.append(i1);
	linelayernames.append(layername);
	//cout << "AddLine layername = " << layername << endl;
	//cout << linelayernames[linelayernames.count()-1] << endl;
//	printf("%x\n", layername);
  }
  else {
	  if (lineindices.count()) 
	  {
		  lineindices.append(-1);
		  linelayernames.append(layername);
	  }
	  lineindices.append(i0);
	  lineindices.append(i1);
	  linelayernames.append(layername);
	  linelayernames.append(layername);
  }
}

/*!
  Adds a point to this layer's geometry. If \a matrix != NULL, the
  point will be transformed by this matrix before they are added.
*/
void 
dxfLayerData::addPoint(const dimeVec3f &v,
					   const char * layername,
		       const dimeMatrix * const matrix)
{
//printf("dxfLayerData::addPoint() v = [%f %f %f] matrix = %08x\n", v[0], v[1], v[2], matrix);
  if (matrix) {
    dimeVec3f t;
    matrix->multMatrixVec(v, t);
    points.append(t);
	pointlayernames.append(layername);
  }
  else {
    points.append(v);
	pointlayernames.append(layername);
  }
}

/*!
  Adds a triangle to this layer's geometry. If \a matrix != NULL, the
  points will be transformed by this matrix before they are added.
*/
void 
dxfLayerData::addTriangle(const dimeVec3f &v0,
			  const dimeVec3f &v1,
			  const dimeVec3f &v2,
			  const char * layername,
			  const dimeMatrix * const matrix)
{
  if (this->fillmode) {
    if (matrix) {
      dimeVec3f t0, t1, t2;
      matrix->multMatrixVec(v0, t0);
      matrix->multMatrixVec(v1, t1);
      matrix->multMatrixVec(v2, t2);
      faceindices.append(facebsp.addPoint(t0));
      faceindices.append(facebsp.addPoint(t1));
      faceindices.append(facebsp.addPoint(t2));
      faceindices.append(-1);
    }
    else {
      faceindices.append(facebsp.addPoint(v0));
      faceindices.append(facebsp.addPoint(v1));
      faceindices.append(facebsp.addPoint(v2));
      faceindices.append(-1);
    }
	facelayernames.append(layername);
	facelayernames.append(layername);
	facelayernames.append(layername);
	facelayernames.append(layername);
  }
  else {
    this->addLine(v0, v1, layername, matrix);
    this->addLine(v1, v2, layername, matrix);
    this->addLine(v2, v0, layername, matrix);
  }
}

/*!
  Adds a quad to this layer's geometry. If \a matrix != NULL, the
  points will be transformed by this matrix before they are added.
*/
void 
dxfLayerData::addQuad(const dimeVec3f &v0,
		      const dimeVec3f &v1,
		      const dimeVec3f &v2,
		      const dimeVec3f &v3,
			  const char * layername,
		      const dimeMatrix * const matrix)
{
/*
printf("dxfLayerData::addQuad this->fillmode = %d()\n", this->fillmode);
printf("v = [%f %f %f]\n", v0[0], v0[1], v0[2]);
printf("v = [%f %f %f]\n", v1[0], v1[1], v1[2]);
printf("v = [%f %f %f]\n", v2[0], v2[1], v2[2]);
printf("v = [%f %f %f]\n", v3[0], v3[1], v3[2]);
printf("matrix = %08x\n", matrix);

FILE * stream;
char filename[1024];
sprintf(filename, "dxfLayerData_addQuad_%d.dat",this->colidx);
stream = fopen(filename,"at");
fprintf(stream, "%f,%f,%f\n", v0[0], v0[1], v0[2]);
fprintf(stream, "%f,%f,%f\n", v1[0], v1[1], v1[2]);
fprintf(stream, "%f,%f,%f\n", v2[0], v2[1], v2[2]);
fprintf(stream, "%f,%f,%f\n", v3[0], v3[1], v3[2]);
fclose(stream);
*/



  if (this->fillmode) {
    if (matrix) {
      dimeVec3f t0, t1, t2, t3;
      matrix->multMatrixVec(v0, t0);
      matrix->multMatrixVec(v1, t1);
      matrix->multMatrixVec(v2, t2);
      matrix->multMatrixVec(v3, t3);
      faceindices.append(facebsp.addPoint(t0));
      faceindices.append(facebsp.addPoint(t1));
      faceindices.append(facebsp.addPoint(t2));
      faceindices.append(facebsp.addPoint(t3));
      faceindices.append(-1);
    }
    else {
      faceindices.append(facebsp.addPoint(v0));
      faceindices.append(facebsp.addPoint(v1));
      faceindices.append(facebsp.addPoint(v2));
      faceindices.append(facebsp.addPoint(v3));
      faceindices.append(-1);
    }
	facelayernames.append(layername);
	facelayernames.append(layername);
	facelayernames.append(layername);
	facelayernames.append(layername);
	facelayernames.append(layername);
  }
  else {
    this->addLine(v0, v1, layername, matrix);
    this->addLine(v1, v2, layername, matrix);
    this->addLine(v2, v3, layername, matrix);
    this->addLine(v3, v0, layername, matrix);
  }
}

/*!
  Exports this layer's geometry as vrml nodes.
*/
void 
dxfLayerData::writeWrl(FILE *fp, int indent, const bool vrml1,
                       const bool only2d)
{
#ifndef NOWRLEXPORT
  if (!faceindices.count() && !lineindices.count() && !points.count()) return;

  int i, n;

  dxfdouble r,g,b;
  
  dimeLayer::colorToRGB(this->colidx, r, g, b);

  if (vrml1) {
    fprintf(fp, 
            "Separator {\n");
  }
  else {
    fprintf(fp, 
            "Group {\n"
            "  children [\n");
  }
  if (faceindices.count()) {
    if (vrml1) {
      fprintf(fp,
              "  Separator {\n"
              "    Material {\n"
              "      diffuseColor %g %g %g\n"
              "    }\n"
              "    ShapeHints {\n"
              "      creaseAngle 0.5\n"
              "      vertexOrdering COUNTERCLOCKWISE\n"
              "      shapeType UNKNOWN_SHAPE_TYPE\n"
              "      faceType UNKNOWN_FACE_TYPE\n"
              "    }\n"
              "    Coordinate3 {\n"
              "      point [\n", r, g, b);
    }
    else {
      fprintf(fp, 
              "    Shape {\n"
              "      appearance Appearance {\n"
              "        material Material {\n"
              "          diffuseColor %g %g %g\n"
              "        }\n"
              "      }\n"
              "      geometry IndexedFaceSet {\n"
              "        convex FALSE\n"
              "        solid FALSE\n"
              "        creaseAngle 0.5\n" // a good value for most cases
              "        coord Coordinate {\n"
              "          point [\n", r, g, b);
    }
    dimeVec3f v;
    n = facebsp.numPoints();
    for (i = 0; i < n ; i++) {
      facebsp.getPoint(i, v);
      if (only2d) v[2] = 0.0f;
      if (i < n-1)
	fprintf(fp, "            %.8g %.8g %.8g,\n", v[0], v[1], v[2]);
      else 
	fprintf(fp, "            %.8g %.8g %.8g\n", v[0], v[1], v[2]);
    }
    fprintf(fp, 
	    "          ]\n"
	    "        }\n");
    if (vrml1) {
      fprintf(fp,
              "    IndexedFaceSet {\n"
              "      coordIndex [\n          ");
    }
    else {
      fprintf(fp,
              "        coordIndex [\n          ");
    }
    n = faceindices.count();
    int cnt = 1;
    for (i = 0; i < n; i++) {
      if ((cnt & 7) && i < n-1) // typical case
	fprintf(fp, "%d,", faceindices[i]);
      else if (!(cnt & 7) && i < n-1)
	fprintf(fp, "%d,\n          ", faceindices[i]);
      else
	fprintf(fp, "%d\n", faceindices[i]);
      cnt++;
    }
    fprintf(fp,
	    "        ]\n"
	    "      }\n"
	    "    }\n");
  }
  if (lineindices.count()) {
    // make sure line indices has a -1 at the end
    if (lineindices[lineindices.count()-1] != -1) {
      lineindices.append(-1);
    }
    if (vrml1) {
      fprintf(fp,
              "  Separator {\n"
              "    Material {\n"
              "      diffuseColor %g %g %g\n"
              "    }\n"
              "    Coordinate3 {\n"
              "      point [\n", r, g, b);
    }
    else {
      fprintf(fp, 
              "    Shape {\n"
              "      appearance Appearance {\n"
              "        material Material {\n"
              "          emissiveColor %g %g %g\n"
              "        }\n"
              "      }\n"
              "      geometry IndexedLineSet {\n"
              "        coord Coordinate {\n"
              "          point [\n", r, g, b);
    }
    dimeVec3f v;
    n = linebsp.numPoints();
    for (i = 0; i < n ; i++) {
      linebsp.getPoint(i, v);
      if (only2d) v[2] = 0.0f;
      if (i < n-1)
	fprintf(fp, "            %.8g %.8g %.8g,\n", v[0], v[1], v[2]);
      else 
	fprintf(fp, "            %.8g %.8g %.8g\n", v[0], v[1], v[2]);
    }
    fprintf(fp, 
	    "          ]\n"
	    "        }\n");
    if (vrml1) {
      fprintf(fp,
              "    IndexedLineSet {\n"
              "      coordIndex [\n          ");
    }
    else {
      fprintf(fp, "        coordIndex [\n          ");
    }
    
    n = lineindices.count();
    int cnt = 1;
    for (i = 0; i < n; i++) {
      if ((cnt & 7) && i < n-1) // typical case
	fprintf(fp, "%d,", lineindices[i]);
      else if (!(cnt & 7) && i < n-1)
	fprintf(fp, "%d,\n          ", lineindices[i]);
      else
	fprintf(fp, "%d\n", lineindices[i]);
      cnt++;
    }
    fprintf(fp,
	    "        ]\n"
	    "      }\n"
	    "    }\n");
  }


  if (points.count() && 0) { // FIXME disabled, suspect bug. pederb, 2001-12-11 
    if (vrml1) {
      fprintf(fp,
              "  Separator {\n"
              "    Material {\n"
              "      diffuseColor %g %g %g\n"
              "    }\n"
              "    Coordinate3 {\n"
              "      point [\n", r, g, b);
    }
    else {
      fprintf(fp, 
              "    Shape {\n"
              "      appearance Appearance {\n"
              "        material Material {\n"
              "          emissiveColor %g %g %g\n"
              "        }\n"
              "      \n"
              "      geometry PointSet {\n"
              "        coord Coordinate {\n"
              "          point [\n", r, g, b);
    }
    dimeVec3f v;
    n = points.count();
    for (i = 0; i < n ; i++) {
      v = points[i];
      if (only2d) v[2] = 0.0f;
      if (i < n-1)
	fprintf(fp, "            %g %g %g,\n", v[0], v[1], v[2]);
      else 
	fprintf(fp, "            %g %g %g\n", v[0], v[1], v[2]);
    }
    fprintf(fp, 
	    "          ]\n"
	    "        }\n");
    if (vrml1) {
      fprintf(fp,
              "    PointSet {\n"
              "      numPoints %d\n"
              "    }\n"  
              "  }\n", points.count());
    }
    else {
      fprintf(fp,
              "      }\n"
              "    }\n");
    
    }
  }
    
  if (vrml1) {
    fprintf(fp, "}\n");
  }
  else {
    fprintf(fp, 
            "  ]\n"
            "}\n");
  }
#endif // NOWRLEXPORT
}

#if DFX_LAYER_FROM_OBJECT
#include "./../surfdoc/src/surfdoc.h"

void dxfLayerData::PropertiesDialog()
{
	MessageBox(0, "PropertiesDialog", "dxfLayerData" , 0);

}

bool dxfLayerData::ColorDialog(void)
{
	return false;
}

COLORREF dxfLayerData::GetColor(void)
{
	return COLORREF();
}

void dxfLayerData::SetColor(COLORREF color)
{
}
void dxfLayerData::CutAndDisvisible(bool positive, double a, double b, double c, double d)
{
}
void dxfLayerData::CutXYZandDisvisible(int subcube_number, double X, double Y, double Z)
{
}
void dxfLayerData::Draw()
{
	m_nglListNumber = DrawListArray::glNewList();
printf("dxfLayerData::Draw() m_nglListNumber = %u\n", m_nglListNumber);
	Drawing();
	glEndList();
}

void dxfLayerData::ReDraw(void)
{
	if(this->m_pSurfDoc) this->ReDrawItem_OnTree(this->m_pSurfDoc->hwndTV);

	if (m_nglListNumber > 0)
	{
		::glDeleteLists(m_nglListNumber,1);
		::glNewList(m_nglListNumber, GL_COMPILE);
	}
	else
		m_nglListNumber = DrawListArray::glNewList();

	Drawing();
	glEndList();
}
void dxfLayerData::DrawingPoints()
{
	dxfdouble r,g,b;    
	dimeLayer::colorToRGB(this->colidx, r, g, b);
	COLORREF color = RGB(255*r,255*g,255*b);

	dimeVec3f d;
	dimeVec3f v;
	int n = points.count();
	glPointSize(3.0); glLineWidth(1.0);
	for (int i = 0; i < n ; i++) 
	{
		d = this->points[i];
//printf("dxfLayerData::Drawing(points) i = %d\n", i);
		//glPushName(GLNAME_MD_TYPE1); glPushName((i32u) & (* it1));
		v.z = m_zoomZ * (d.z - m_z_mean);
		v.y = m_zoomY * (d.y - m_y_mean);
		v.x = m_zoomX * (d.x - m_x_mean);
		glBegin(GL_POINTS);
		//SetColor(gv->colormode, & (* it1), do_bw);
		glColor3ub (GetRValue(color),GetGValue(color),GetBValue(color)); 
		//glVertex3fv((* it1).GetCRD(n1));
		glVertex3d (v.x, 
					v.y, 
					v.z);
		glEnd();
		
		//glPopName(); glPopName();
	}
}
void dxfLayerData::DrawingLines()
{
	dxfdouble r,g,b;    
	dimeLayer::colorToRGB(this->colidx, r, g, b);
	COLORREF color = RGB(255*r,255*g,255*b);
	
	glColor3ub (GetRValue(color),GetGValue(color),GetBValue(color)); 
	
	dimeVec3f d;
	dimeVec3f v;
    
	int n = linebsp.numPoints();
    for (int i = 0; i < n ; i++) {
		//printf("dxfLayerData::Drawing(linebsp) i = %d\n", i);
		linebsp.getPoint(i, d);
		//glPushName(GLNAME_MD_TYPE1); glPushName((i32u) & (* it1));
		v.z = m_zoomZ * (d.z - m_z_mean);
		v.y = m_zoomY * (d.y - m_y_mean);
		v.x = m_zoomX * (d.x - m_x_mean);
		
		glBegin(GL_POINTS);
		//SetColor(gv->colormode, & (* it1), do_bw);
		//glColor3ub (GetRValue(color),GetGValue(color),GetBValue(color)); 
		//glVertex3fv((* it1).GetCRD(n1));
		glVertex3d (v.x, 
					v.y, 
					v.z);
		glEnd();
		
		//glPopName(); glPopName();
	}

	dimeVec3f d1;
	dimeVec3f v1;
	dimeVec3f d2;
	dimeVec3f v2;
		
	
	bool start_line = true;

	for (int j = 0; j < lineindices.count(); j++)
	{
		int i = lineindices[j];
		if(i > -1)
		{
			if (start_line)
			{
				this->linebsp.getPoint(i, d1);

				v1.z = m_zoomZ * (d1.z - m_z_mean);
				v1.y = m_zoomY * (d1.y - m_y_mean);
				v1.x = m_zoomX * (d1.x - m_x_mean);
				
				start_line = false;
			}
			else
			{
				this->linebsp.getPoint(i, d2);

				v2.z = m_zoomZ * (d2.z - m_z_mean);
				v2.y = m_zoomY * (d2.y - m_y_mean);
				v2.x = m_zoomX * (d2.x - m_x_mean);		       				

				glLineWidth(1.0);
				Line3(
					v1.x, 
					v1.y, 
					v1.z,
					v2.x, 
					v2.y,	
					v2.z);

				d1 = d2;
				v1 = v2;
			}
		}
		else
		{
			start_line = true;
		}
	}
    /*
		for (i = 0; i < n-1 ; i++)
	{
		//printf("dxfLayerData::Drawing(facebsp) i = %d\n", i);
		this->facebsp.getPoint(i, d1);
		this->facebsp.getPoint(i+1, d2);
		//glPushName(GLNAME_MD_TYPE1); glPushName((i32u) & (* it1));
		v1.z = m_zoomZ * (d1.z - m_z_mean);
		v1.y = m_zoomY * (d1.y - m_y_mean);
		v1.x = m_zoomX * (d1.x - m_x_mean);

		v2.z = m_zoomZ * (d2.z - m_z_mean);
		v2.y = m_zoomY * (d2.y - m_y_mean);
		v2.x = m_zoomX * (d2.x - m_x_mean);
       				
		printf("%f %f %f %f %f %f\n", v1.x, 
				v1.y, 
				v1.z,
				v2.x, 
				v2.y,	
				v2.z) ;
		glLineWidth(1.0);
			Line3(
				v1.x, 
				v1.y, 
				v1.z,
				v2.x, 
				v2.y,	
				v2.z);
		
		//glPopName(); glPopName();
	}	*/
}
void dxfLayerData::DrawingFaces()
{
	dxfdouble r,g,b;    
	dimeLayer::colorToRGB(this->colidx, r, g, b);
	COLORREF color = RGB(255*r,255*g,255*b);
	
	dimeVec3f d;
	dimeVec3f v;

	int n = this->facebsp.numPoints();
    for (int i = 0; i < n ; i++)
	{
		//printf("dxfLayerData::Drawing(facebsp) i = %d\n", i);
		this->facebsp.getPoint(i, d);

//		fprintf(stream, "%f,%f,%f\n", d.x, d.y, d.z);

		//glPushName(GLNAME_MD_TYPE1); glPushName((i32u) & (* it1));
		v.z = m_zoomZ * (d.z - m_z_mean);
		v.y = m_zoomY * (d.y - m_y_mean);
		v.x = m_zoomX * (d.x - m_x_mean);

		glBegin(GL_POINTS);
		//SetColor(gv->colormode, & (* it1), do_bw);
		glColor3ub (GetRValue(color),GetGValue(color),GetBValue(color)); 
		//glVertex3fv((* it1).GetCRD(n1));
		glVertex3d (v.x, 
					v.y, 
					v.z);
		glEnd();
		
		//glPopName(); glPopName();
	}

	dimeVec3f d0;
	dimeVec3f v0;
	dimeVec3f d1;
	dimeVec3f v1;
	dimeVec3f d2;
	dimeVec3f v2;
		
	
	bool start_face = true;

	for (int j = 0; j < faceindices.count(); j++)
	{
		int i = faceindices[j];
		if(i > -1)
		{
			if (start_face)
			{
				this->facebsp.getPoint(i, d0);

				v0.z = m_zoomZ * (d0.z - m_z_mean);
				v0.y = m_zoomY * (d0.y - m_y_mean);
				v0.x = m_zoomX * (d0.x - m_x_mean);

				d1 = d0;
				v1 = v0;
				
				start_face = false;
			}
			else
			{
				this->facebsp.getPoint(i, d2);

				v2.z = m_zoomZ * (d2.z - m_z_mean);
				v2.y = m_zoomY * (d2.y - m_y_mean);
				v2.x = m_zoomX * (d2.x - m_x_mean);		       				

				glLineWidth(1.0);
				Line3(
					v1.x, 
					v1.y, 
					v1.z,
					v2.x, 
					v2.y,	
					v2.z);

				d1 = d2;
				v1 = v2;
			}
		}
		else
		{
			if (!start_face)
			{
				glLineWidth(1.0);
				Line3(
					v2.x, 
					v2.y, 
					v2.z,
					v0.x, 
					v0.y,	
					v0.z);
			}
			start_face = true;
		}
	}

	if (m_pSurfDoc)
	{
		//====== Установка режима заполнения
		//====== внутренних точек полигонов
		GLint oldPolygonMode[2];
		glGetIntegerv(GL_POLYGON_MODE, oldPolygonMode);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//double d_1[3],d_2[3],norm[3];
		//double norm_center[3];
			
		
#if 1
		bool start_face = true;
		for (int j = 0; j < faceindices.count(); j++)
		{
			int i = faceindices[j];
			if(i > -1)
			{
				if (start_face)
				{
					this->facebsp.getPoint(i, d0);

					v0.z = m_zoomZ * (d0.z - m_z_mean);
					v0.y = m_zoomY * (d0.y - m_y_mean);
					v0.x = m_zoomX * (d0.x - m_x_mean);

					d1 = d0;
					v1 = v0;

					glBegin(GL_POLYGON);

					glVertex3d (v0.x, v0.y, v0.z);
					
					start_face = false;
				}
				else
				{
					this->facebsp.getPoint(i, d2);

					v2.z = m_zoomZ * (d2.z - m_z_mean);
					v2.y = m_zoomY * (d2.y - m_y_mean);
					v2.x = m_zoomX * (d2.x - m_x_mean);		       				

					glVertex3d (v2.x, v2.y, v2.z);

					d1 = d2;
					v1 = v2;
				}
			}
			else
			{
				glEnd();
				start_face = true;
			}
		}


#else

		for (size_t i = 0; i < len; i++)
		{
			//====== Обход вершин осуществляется
			//====== в направлении против часовой стрелки
			int i_minus_1 = i-1;
			int i_plus_1  = i+1;

			if(i == 0)
			{
				i_minus_1 = len-1;
			}
			if (i == len-1)
			{
				i_plus_1  = 0;
			}
			if (!(m_vvPoints[i].flag & CPOINT3_FLAG_NONORMAL))
			{
				d_1[0] = m_vvPoints[i_minus_1].x-m_vvPoints[i].x;
				d_1[1] = m_vvPoints[i_minus_1].y-m_vvPoints[i].y;
				d_1[2] = m_vvPoints[i_minus_1].z-m_vvPoints[i].z;

				d_2[0] = m_vvPoints[i].x-m_vvPoints[i_plus_1].x;
				d_2[1] = m_vvPoints[i].y-m_vvPoints[i_plus_1].y;
				d_2[2] = m_vvPoints[i].z-m_vvPoints[i_plus_1].z;

				getNorm(d_1,d_2,norm);
			}
			//====== Задание вектора нормали

			if (m_vvPoints[i].bVisible)
			{
				glNormal3dv (norm);
				if (m_pSurface)
				{
					COLORREF color = m_pSurface->GetColor(m_vdPoints[i].z);
	//				glColor4ub (GetRValue(color), GetGValue(color), GetBValue(color), (GLubyte)m_pSurface->m_alpha); 
					glColor4ub (GetRValue(color), GetGValue(color), GetBValue(color), (GLubyte)m_pSurfDoc->m_alpha); 
				}
				else
				{
	//				glColor4ub (GetRValue(m_color), GetGValue(m_color), GetBValue(m_color), (GLubyte)m_pSurfDoc->m_alpha); 
					glColor4ub (GetRValue(m_color), GetGValue(m_color), GetBValue(m_color), (GLubyte)m_pSurfDoc->m_alpha_plane); 
	//				glColor4ub (GetRValue(m_color), GetGValue(m_color), GetBValue(m_color), (GLubyte)m_alpha); 
				}
				glVertex3d (m_vvPoints[i].x, m_vvPoints[i].y, m_vvPoints[i].z);

			}
		}
#endif
		

		glPolygonMode(GL_FRONT_AND_BACK, oldPolygonMode[1]);

	}


}
void dxfLayerData::Drawing()
{
	DrawingPoints();
	DrawingLines();
	DrawingFaces();
}
void dxfLayerData::Init(const dxfLayerData& ob)
{	
	/*
	//bool fillmode;
	this->fillmode		= ob.fillmode;
	//int colidx;
	this->colidx		= ob.colidx;
	//dimeBSPTree facebsp;
	this->facebsp		= ob.facebsp;
//	this->view_facebsp	= ob.view_facebsp;
    //dimeArray <int> faceindices;
	this->faceindices	= ob.faceindices;
    //dimeBSPTree linebsp;
	this->linebsp		= ob.linebsp;
//	this->view_linebsp	= ob.view_linebsp;
	//dimeArray <int> lineindices;
	this->lineindices	= ob.lineindices;
	//dimeArray <dimeVec3f> points;
	this->points		= ob.points;
//	this->view_points	= ob.view_points;
*/
}
dxfLayerData& dxfLayerData::operator=(const dxfLayerData& ob)
{
	if (this == &ob)
		return *this;
	this->Init(ob);
	return *this;
}
dxfLayerData::dxfLayerData(const dxfLayerData & ob)
{
	this->Init(ob);
}

void dxfLayerData::OnCreate(void)
{
	this->m_object_type = Object::object_type::dfx_layerdata;
	this->m_object_version = 1;
	this->m_max_object_version = 1;
}
dxfLayerData::dxfLayerData(SurfDoc* pSurfDoc)
{
	this->m_pSurfDoc				= pSurfDoc;

	this->fillmode = true;
	this->colidx = colidx;

	this->OnCreate();
}
void dxfLayerData::EnumObjects(WPARAM wParam, LPARAM lParam, void * p,
		bool (Object::* condition_fun)(),
		void (* callback_fun)(Object*, WPARAM , LPARAM, void * ) )
{
	if ((this->*condition_fun)())
	{
		(* callback_fun)(this, wParam, lParam, p);
	}
}
void dxfLayerData::SetLayer(const Layer* layer)
{
	this->Object::SetLayer_NonVirtual(layer);
}
HTREEITEM dxfLayerData::AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s)
{
    char szItemText[128]; // label text of tree-view item 
	sprintf(szItemText, "dxfLayerData colidx = %d",colidx);
	Object * pObject = dynamic_cast<Object *> (this);
	return AddItemToTree(hwndTV, szItemText, pObject, h1);
}
bool dxfLayerData::UpdateExtremums()
{
	dimeVec3f v;
	int n = points.count();
	bool start = true;
	for (int i = 0; i < n ; i++) 
	{
		v = points[i];
		if (start)
		{
			start = false;
			// real x
			m_ptMax.x = v.x;
			m_ptMin.x = v.x;
			// real y
			m_ptMax.y = v.y;
			m_ptMin.y = v.y;
			// real z
			m_ptMax.z = v.z;
			m_ptMin.z = v.z;
		}
		else
		{
			// real x
			if (m_ptMax.x < v.x) m_ptMax.x = v.x;
			if (m_ptMin.x > v.x) m_ptMin.x = v.x;
			// real y
			if (m_ptMax.y < v.y) m_ptMax.y = v.y;
			if (m_ptMin.y > v.y) m_ptMin.y = v.y;
			// real z
			if (m_ptMax.z < v.z) m_ptMax.z = v.z;
			if (m_ptMin.z > v.z) m_ptMin.z = v.z;
		}
	}
	n = linebsp.numPoints();
	for (int i = 0; i < n ; i++) 
	{
		linebsp.getPoint(i, v);
		if (start)
		{
			start = false;
			// real x
			m_ptMax.x = v.x;
			m_ptMin.x = v.x;
			// real y
			m_ptMax.y = v.y;
			m_ptMin.y = v.y;
			// real z
			m_ptMax.z = v.z;
			m_ptMin.z = v.z;
		}
		else
		{
			// real x
			if (m_ptMax.x < v.x) m_ptMax.x = v.x;
			if (m_ptMin.x > v.x) m_ptMin.x = v.x;
			// real y
			if (m_ptMax.y < v.y) m_ptMax.y = v.y;
			if (m_ptMin.y > v.y) m_ptMin.y = v.y;
			// real z
			if (m_ptMax.z < v.z) m_ptMax.z = v.z;
			if (m_ptMin.z > v.z) m_ptMin.z = v.z;
		}
	}
	n = facebsp.numPoints();
	for (int i = 0; i < n ; i++) 
	{
		facebsp.getPoint(i, v);
		if (start)
		{
			start = false;
			// real x
			m_ptMax.x = v.x;
			m_ptMin.x = v.x;
			// real y
			m_ptMax.y = v.y;
			m_ptMin.y = v.y;
			// real z
			m_ptMax.z = v.z;
			m_ptMin.z = v.z;
		}
		else
		{
			// real x
			if (m_ptMax.x < v.x) m_ptMax.x = v.x;
			if (m_ptMin.x > v.x) m_ptMin.x = v.x;
			// real y
			if (m_ptMax.y < v.y) m_ptMax.y = v.y;
			if (m_ptMin.y > v.y) m_ptMin.y = v.y;
			// real z
			if (m_ptMax.z < v.z) m_ptMax.z = v.z;
			if (m_ptMin.z > v.z) m_ptMin.z = v.z;
		}
	}
	/*printf("dxfLayerData::UpdateExtremums()\nmin = [ %f %f %f ]\nmax = [ %f %f %f]\n", 
		m_ptMin.x, 
		m_ptMin.y, 
		m_ptMin.z,
		m_ptMax.x, 
		m_ptMax.y,	
		m_ptMax.z);*/
	
	return !start;
}

void dxfLayerData::Zoom(double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean)
{
/*printf("dxfLayerData::Zoom()\n");

printf("Zoom() [%f %f %f %f %f %f]\n",
				zoomX,zoomY,zoomZ, 
				x_mean,
				y_mean,
				z_mean
				);*/

	this->m_x_mean = x_mean;
	this->m_y_mean = y_mean;
	this->m_z_mean = z_mean;
	this->m_zoomX = zoomX;
	this->m_zoomY = zoomY;
	this->m_zoomZ = zoomZ;
	/*dimeVec3f v;
	int n = points.count();
	this->view_points.resize(n);
	for (int i = 0; i < n ; i++) 
	{
		v = points[i];	
		this->view_points[i].z = zoomZ * (v.z - z_mean);
		this->view_points[i].y = zoomY * (v.y - y_mean);
		this->view_points[i].x = zoomX * (v.x - x_mean);
	}*/
}
#endif /*DFX_LAYER_FROM_OBJECT*/
