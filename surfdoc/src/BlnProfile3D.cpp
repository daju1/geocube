// BlnProfile3D.cpp: implementation of the BlnProfile3D class.
//
//////////////////////////////////////////////////////////////////////
#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>			// MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#include "stdafx.h"
#include "BlnProfile3D.h"
#include "..\..\commonOG.h"
#include "SurfDoc.h"
#include ".\blnprofile3d.h"
#include ".\Archive.h"
#include ".\whatselected.h"
#include "winsurftree.h"
#include "../mylicense.h"
#include "../../lab/lab/labdoc.h"
#define TEXT_LEN 1024

extern HINSTANCE hInst;   // текущий экземпляр

int GetVerticalPlaneFromTwoPoints(
								  CPoint2 &pt1, CPoint2 &pt2, //input
								  double &a, double &b, double &c, double &d);//output
SSaveProfData BlnProfile3D::sprData;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BlnProfile3D::BlnProfile3D()
{
	m_pSurfDoc = NULL;
	OnCreate();
}

BlnProfile3D::BlnProfile3D(SurfDoc* pSurfDoc)
{
	m_pSurfDoc = pSurfDoc;
	OnCreate();
}

void BlnProfile3D::OnCreate(void)
{
	this->m_object_type = Object::object_type::bln_profile3d;
	this->m_object_version = 4;
	this->m_max_object_version = 4;

//	m_vBlnProfiles.OnCreate(0);

	//для DrawGDIplus
	m_broken_plane.InitDoc(this->m_pSurfDoc);
	m_broken_plane.InitPrifile3D(this);


	m_grid.faultSection.nTraces = 0; 
	m_grid.faultSection.nVertices = 0; 
	m_grid.faultSection.traces = NULL; 
	m_grid.faultSection.vertexes = NULL; 

	m_grid.gridSection.BlankValue = BLANK_VALUE;
	m_grid.gridSection.Rotation = 0.0;
	m_grid.gridSection.z = NULL;


	m_bln_lines.OnCreate();
//	m_bln_polygones.OnCreate();
	m_plane.OnCreate();

	m_brkn_poligons.OnCreate();

	this->id_rozriz = -1;

}

BlnProfile3D::BlnProfile3D(const BlnProfile3D & bp)
{
	dynamic_cast<Object*>(this)->Init(bp);
	this->Init(bp);
}
BlnProfile3D& BlnProfile3D::operator=(const BlnProfile3D& bp)
{
	if (this == &bp)
	{
		return *this;
	}

	dynamic_cast<Object*>(this)->Init(bp);
	this->Init(bp);

	return *this;
}
BlnProfile3D::~BlnProfile3D()
{

}
int BlnProfile3D::ReadBln(const char *lpstrFile)
{
	FILE *stream;
	const unsigned int n = 1023;
	char szBuff[n];
	if ((stream = fopen(lpstrFile,"rt")) == NULL)
	{
		MessageBox(0, "Cannot open input file.\n", "Import", 
			MB_OK | MB_ICONINFORMATION);
		return -1;
	}
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	//m_vBlnProfiles.CreateNewVect();
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	int len = 0;
	double X,Y;
	char name[255];
	while (!feof(stream))
	{
		char * ch;
		ch = fgets(szBuff,n,stream);
		if( ch != NULL && strlen(szBuff) > 1)
		{
			//len = atoi(ch);
			int inside;
			name[0] = '\0';
			int rez = sscanf(szBuff,"%d,%d \"%s\"",
									&len, &inside, name);
			switch(rez)
			{
			case 3:
				{
					size_t last = strlen(name)-1;
					if (last > 0 && name[last] == '\"')
						name[last] = '\0';
				}
				break;
			case 2:
				{
					name[0] = '\0';
				}
				break;
			case EOF:
			default:
				{
					fclose(stream);
					return -1;
				}
			}

			if (rez != 3 || rez == EOF || len == 0)
			{

			}
		}
		else
		{
			break;
		}
		if (len == 0)
		{
			/*
			fclose(stream);
			//m_vBlnProfiles.DeleteLastVect();
			return -1;
			*/
			continue;
		}

		int i = 0;

//		m_vBlnProfiles.AddMsg(len);
//		CPoint2 * pt2 = m_vBlnProfiles.GetLastMsgPtr();

		this->m_vectorBlnProfiles.push_back(vector<CPoint2>());

		
		while (!feof(stream) && i < len)
		{
			char * ch;
			ch = fgets(szBuff,n,stream);
			if( ch != NULL && strlen(szBuff) > 1)
			{
				int rez = sscanf(szBuff,"%lf,%lf",
								&X, &Y);
				if (i < len)
				{
					if (rez == 2 && rez != EOF)
					{
						//pt2[i].x = X;
						//pt2[i].y = Y;
						//pt2[i].bVisible  = true;

						m_vectorBlnProfiles.back().push_back(CPoint2(X,Y, true));

						i++;
					}
					else
					{
						rez = sscanf(szBuff,"%lf\t%lf",
										&X, &Y);
						if (rez == 2 && rez != EOF)
						{
							//pt2[i].x = X;
							//pt2[i].y = Y;
							//pt2[i].bVisible  = true;

							m_vectorBlnProfiles.back().push_back(CPoint2(X,Y, true));

							i++;
						}
					}
				}
			}
		}
		this->m_names.push_back(name);
		m_colors.push_back(0);
	}
	fclose(stream);
	return 0;
}

#include <dime/Layer.h>
#include <dime/Model.h>

/*!
  Sets the fillmode for this layer. If fillmode is set (the default)
  polylines with width and/or height will be converter to polygons
  and not lines. The same goes for the SOLID and TRACE entities.
*/
void 
BlnProfile3D::setFillmode(const bool fillmode)
{
  this->fillmode = fillmode;
}
/*!
  Adds a line to this layer's geometry. If \a matrix != NULL, the
  points will be transformed by this matrix before they are added.
*/
void 
BlnProfile3D::addLine(const dimeVec3f &v0, const dimeVec3f &v1,
					  const char * layername, const int colidx,
		      const dimeMatrix * const matrix)
{
/*printf("BlnProfile3D::addLine() v0 = [%f %f %f] v1 = [%f %f %f] matrix = %08x\n", 
	   v0[0], v0[1], v0[2], v1[0], v1[1], v1[2], matrix);
*/
#if 1

	/*CPoint2 * pp = new CPoint2[2];
		
	pp[0].x = v0.x;
	pp[0].y = v0.y;
	pp[0].bVisible = true;

	pp[1].x = v1.x;
	pp[1].y = v1.y;
	pp[1].bVisible = true;

	m_vBlnProfiles.AddMsg(pp,2);
	delete [] pp;*/

	// make color
	dxfdouble r,g,b;    
	dimeLayer::colorToRGB(colidx, r, g, b);
	COLORREF color = RGB(255*r,255*g,255*b);

	// проверяем 
	bool test = false;

	for (size_t n = 0; n < this->m_colors.size() && n < this->m_names.size() && n < this->m_vectorBlnProfiles.size(); n++)
	{
		this->m_colors[n];
		this->m_names[n];
		this->m_vectorBlnProfiles[n];

		if (0 == strcmp(layername, this->m_names[n].c_str()) && this->m_colors[n] == color)
		{
			if ( this->m_vectorBlnProfiles[n].size() > 1)
			{
				if (this->m_vectorBlnProfiles[n][0].x == v1.x && this->m_vectorBlnProfiles[n][0].y == v1.y)
				{
					this->m_vectorBlnProfiles[n].insert(this->m_vectorBlnProfiles[n].begin(), CPoint2(v0.x,v0.y, true));
					return;
				}
				if (this->m_vectorBlnProfiles[n][0].x == v0.x && this->m_vectorBlnProfiles[n][0].y == v0.y)
				{
					this->m_vectorBlnProfiles[n].insert(this->m_vectorBlnProfiles[n].begin(), CPoint2(v1.x,v1.y, true));
					return;
				}
				if (this->m_vectorBlnProfiles[n].back().x == v0.x && this->m_vectorBlnProfiles[n].back().y == v0.y)
				{
					this->m_vectorBlnProfiles[n].push_back(CPoint2(v1.x,v1.y, true));
					return;
				}
				if (this->m_vectorBlnProfiles[n].back().x == v1.x && this->m_vectorBlnProfiles[n].back().y == v1.y)
				{
					this->m_vectorBlnProfiles[n].push_back(CPoint2(v0.x,v0.y, true));
					return;
				}
			}
		}
	}

	if (!test)
	{			
		this->m_vectorBlnProfiles.push_back(vector<CPoint2>());
		
		m_vectorBlnProfiles.back().push_back(CPoint2(v0.x, v0.y, true));
		m_vectorBlnProfiles.back().push_back(CPoint2(v1.x, v1.y, true));

		this->m_names.push_back(layername);
		this->m_colors.push_back(color);
	}

#else
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
#endif
}

/*!
  Adds a point to this layer's geometry. If \a matrix != NULL, the
  point will be transformed by this matrix before they are added.
*/
void 
BlnProfile3D::addPoint(const dimeVec3f &v,
					   const char * layername, const int colidx,
		       const dimeMatrix * const matrix)
{
//printf("BlnProfile3D::addPoint() v = [%f %f %f] matrix = %08x\n", v[0], v[1], v[2], matrix);
#if 1
#else
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
#endif
}

/*!
  Adds a triangle to this layer's geometry. If \a matrix != NULL, the
  points will be transformed by this matrix before they are added.
*/
void 
BlnProfile3D::addTriangle(const dimeVec3f &v0,
			  const dimeVec3f &v1,
			  const dimeVec3f &v2,
			  const char * layername,
			  const int colidx,
			  const dimeMatrix * const matrix)
{
#if 1
	/*CPoint2 * pp = new CPoint2[3];
		
	pp[0].x = v0.x;
	pp[0].y = v0.y;
	pp[0].bVisible = true;

	pp[1].x = v1.x;
	pp[1].y = v1.y;
	pp[1].bVisible = true;

	pp[2].x = v2.x;
	pp[2].y = v2.y;
	pp[2].bVisible = true;

	m_vBlnProfiles.AddMsg(pp,3);
	delete [] pp;*/

	this->m_vectorBlnProfiles.push_back(vector<CPoint2>());
	m_vectorBlnProfiles.back().push_back(CPoint2(v0.x, v0.y, true));
	m_vectorBlnProfiles.back().push_back(CPoint2(v1.x, v1.y, true));
	m_vectorBlnProfiles.back().push_back(CPoint2(v2.x, v2.y, true));

	this->m_names.push_back(layername);

	dxfdouble r,g,b;    
	dimeLayer::colorToRGB(colidx, r, g, b);
	COLORREF color = RGB(255*r,255*g,255*b);
	this->m_colors.push_back(color);

#else
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
#endif
}

/*!
  Adds a quad to this layer's geometry. If \a matrix != NULL, the
  points will be transformed by this matrix before they are added.
*/
void 
BlnProfile3D::addQuad(const dimeVec3f &v0,
		      const dimeVec3f &v1,
		      const dimeVec3f &v2,
		      const dimeVec3f &v3,
			  const char * layername,
			  const int colidx,
		      const dimeMatrix * const matrix)
{
/*
printf("BlnProfile3D::addQuad this->fillmode = %d()\n", this->fillmode);
printf("v = [%f %f %f]\n", v0[0], v0[1], v0[2]);
printf("v = [%f %f %f]\n", v1[0], v1[1], v1[2]);
printf("v = [%f %f %f]\n", v2[0], v2[1], v2[2]);
printf("v = [%f %f %f]\n", v3[0], v3[1], v3[2]);
printf("matrix = %08x\n", matrix);

FILE * stream;
char filename[1024];
sprintf(filename, "BlnProfile3D_addQuad_%d.dat",this->colidx);
stream = fopen(filename,"at");
fprintf(stream, "%f,%f,%f\n", v0[0], v0[1], v0[2]);
fprintf(stream, "%f,%f,%f\n", v1[0], v1[1], v1[2]);
fprintf(stream, "%f,%f,%f\n", v2[0], v2[1], v2[2]);
fprintf(stream, "%f,%f,%f\n", v3[0], v3[1], v3[2]);
fclose(stream);
*/

#if 1
	/*CPoint2 * pp = new CPoint2[4];
		
	pp[0].x = v0.x;
	pp[0].y = v0.y;
	pp[0].bVisible = true;

	pp[1].x = v1.x;
	pp[1].y = v1.y;
	pp[1].bVisible = true;

	pp[2].x = v2.x;
	pp[2].y = v2.y;
	pp[2].bVisible = true;

	pp[3].x = v3.x;
	pp[3].y = v3.y;
	pp[3].bVisible = true;

	m_vBlnProfiles.AddMsg(pp,4);
	delete [] pp;*/

	this->m_vectorBlnProfiles.push_back(vector<CPoint2>());
	m_vectorBlnProfiles.back().push_back(CPoint2(v0.x, v0.y, true));
	m_vectorBlnProfiles.back().push_back(CPoint2(v1.x, v1.y, true));
	m_vectorBlnProfiles.back().push_back(CPoint2(v2.x, v2.y, true));
	m_vectorBlnProfiles.back().push_back(CPoint2(v3.x, v3.y, true));

	this->m_names.push_back(layername);

	dxfdouble r,g,b;    
	dimeLayer::colorToRGB(colidx, r, g, b);
	COLORREF color = RGB(255*r,255*g,255*b);
	this->m_colors.push_back(color);

#else

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
#endif
}
bool BlnProfile3D::YScaling()
{
	// масштабирование по вертикальной координате для приведения автокадовских профилей к мировым альтитудам
	// y1a - нижняя коррдината в автокаде
	// z1w - соответствующая ей мировая альтитуда
	// y2a - верхняя коррдината в автокаде
	// z2w - соответствующая ей мировая альтитуда
	// масштабируем по правилу:
	// z = m_z1w + ((y - m_y1a) / (m_y2a - m_y1a)) * (m_z2w - m_z1w)
	double mu = (m_z2w - m_z1w) / (m_y2a - m_y1a); 
	// z = m_z1w + mu * (y - m_y1a) 
	
	//vect<CPoint2> m_vBlnProfiles;//массив двумерных линий оцифрованных на разрезе в координатах разреза

	/*if (m_vBlnProfiles.SetCurrentMsgOnFirst())
	{
		do
		{
			size_t len = m_vBlnProfiles.GetCurrentMsgLen();
			CPoint2 *pt2;
			pt2 = m_vBlnProfiles.GetCurrentMsgPtr();
			for(size_t i = 0; i < len; i++)
			{
				//double x = pt2[i].x;
				//double y = pt2[i].y;
				pt2[i].y = m_z1w + mu * (pt2[i].y - m_y1a);
			}
		}
		while(m_vBlnProfiles.IncrementCurrentMsg() );
	}*/

	for (size_t n = 0; n < m_vectorBlnProfiles.size(); n++)
	{
		size_t m = m_vectorBlnProfiles[n].size();
		for (size_t i = 0; i < m; i++)
		{
			//pt2[i].y = m_z1w + mu * (pt2[i].y - m_y1a);
			m_vectorBlnProfiles[n][i].y = m_z1w + mu * (m_vectorBlnProfiles[n][i].y - m_y1a);
		}
	}

	return true;
}
int BlnProfile3D::ReadDxf(const char *lpstrFile)
{
	printf("BlnProfile3D::ReadDxf(char *lpstrFile = %s)\n", lpstrFile);
	dimeModel model;
	dxfConverter converter;
	dxfConverter::Loading(model, lpstrFile);

/*
	if(this->Profile3D::GetVcadYscaleLoaded())
		converter.YScaling(model, m_z1w, m_y1a, m_z2w, m_y2a);
		*/

#if 1		

	converter.doProfileConvert(model, this);
#else
	
	converter.Converting(model);
					
	char name[1048];
	for (int i = 0; i < 255; i++) 
	{
		if (converter.layerData[i]) 
		{
	printf("if (converter.layerData[%d])\n\tconverter.layerData[i]->lineindices.count() %d\n", i, converter.layerData[i]->lineindices.count());

			dxfdouble r,g,b;    
			dimeLayer::colorToRGB(converter.layerData[i]->colidx, r, g, b);
			COLORREF color = RGB(255*r,255*g,255*b);



			vector<CPoint2> vp;
			vp.clear();
			dimeVec3f d;
			char * layername = NULL;
			for (int j = 0; j <= converter.layerData[i]->lineindices.count(); j++)
			{
				printf( "j = %d ii = %d\n", j, converter.layerData[i]->lineindices[j]);

				int ii;
				if (j == converter.layerData[i]->lineindices.count()
					|| (ii = converter.layerData[i]->lineindices[j]) < 0)
				{
					CPoint2 * pp = new CPoint2[vp.size()];
					for(size_t jj = 0; jj < vp.size(); jj++)
						pp[jj] = vp[jj];
					//start_line = true;
					m_vBlnProfiles.AddMsg(pp,vp.size());
					delete [] pp;

					sprintf(name, "%s", layername);
					printf("layername = %s\n", layername);

					this->m_names.push_back(name);
					this->m_colors.push_back(color);
					vp.clear();
				}
				else
				{
					layername = (char *)converter.layerData[i]->linelayernames[j];
					converter.layerData[i]->linebsp.getPoint(ii, d);
					vp.push_back(CPoint2(d.x,d.y));
					cout << layername << endl;
				}
			}
		}
	}
#endif

	return 0;
}

int BlnProfile3D::AddBlnProfile(const char *lpstrFile, const char * name, vector<long> * pv_ID_KT, vector<double> &xMap, vector<double> &yMap, vector<double> &xProfile, bool acad_yscale_loaded, double z1w, double y1a, double z2w, double y2a)
{

	if(acad_yscale_loaded)
	{
		if(!this->Profile3D::GetAcadYscaleLoaded())
		{
			this->Profile3D::SetAcadYscale(z1w, y1a, z2w, y2a);
		}
	}

	const char *p = NULL;
	char ext[255];

	if (lpstrFile) p = strrchr(lpstrFile,'.');
	if (p)
		strcpy(ext, p+1);

	if (p && strcmp(ext, "bln") == 0)
	{
		if (0 != this->ReadBln(lpstrFile))
			return -1;
	}
	else if (p && strcmp(ext, "dxf") == 0)
	{
		if (0 != this->ReadDxf(lpstrFile))
			return -1;
	}
	/*else
	{
		MessageBox(0, ext, "File extension is not correct",0);
		return -1;
	}*/
	if(this->Profile3D::GetAcadYscaleLoaded())
		this->YScaling();


	if (name) this->SetName(name);
	m_broken_plane.InitDoc(this->m_pSurfDoc);
	int res = -1;
	if (m_broken_plane.Init_broken_plane(pv_ID_KT, xMap, yMap))
	{
		res = this->CreateAttaches(xMap, yMap, xProfile);
		m_broken_plane.Cutting();
	}
	return res;
}
int BlnProfile3D::AddBlnProfile(const char *lpstrFile, const char * name, int ProfileDirection, double f)
{
printf("AddBlnProfile(char *lpstrFile = %s\n", lpstrFile);
	const char *p;
	char ext[255];

	p = strrchr(lpstrFile,'.');
	if (p)
		strcpy(ext, p+1);

	if (p && strcmp(ext, "bln") == 0)
	{
		if (0 != this->ReadBln(lpstrFile))
			return -1;
	}
	else if (p && strcmp(ext, "dxf") == 0)
	{
		if (0 != this->ReadDxf(lpstrFile))
			return -1;
	}
	/*else
	{
		MessageBox(0, ext, "File extension is not correct",0);
		return -1;
	}*/	
	// ищем минимум и максимум в двумерных координатах для каждого разреза
	double 
		xmin,
		xmax,
		ymin,
		ymax;
	
	// профиль из линий блн файлов
	if(this->GetExtremums2D(false, xmin, xmax, ymin, ymax, ProfileDirection))
	{
		vector<double> xMap,yMap,xProfile;
		xMap.resize(2);
		yMap.resize(2);
		xProfile.resize(2);

		switch (ProfileDirection)
		{
		case GRID_POFILE_DIRECTION_NORTH:
			{
				xMap[0]		= f;
				xMap[1]		= f;

				yMap[0]		= xmin;
				yMap[1]		= xmax;

				xProfile[0] = xmin;
				xProfile[1] = xmax;
			}
			break;
		case GRID_POFILE_DIRECTION_EAST:
			{
				xMap[0]		= xmin;
				xMap[1]		= xmax;

				yMap[0]		= f;
				yMap[1]		= f;

				xProfile[0] = xmin;
				xProfile[1] = xmax;
			}
			break;
		}
		

		if (name) this->SetName(name);
		m_broken_plane.InitDoc(this->m_pSurfDoc);
		int res = -1;
		if (m_broken_plane.Init_broken_plane(NULL, xMap, yMap))
		{
			res = this->CreateAttaches(xMap, yMap, xProfile);
			m_broken_plane.Cutting();
		}
		return res;
	}

	return -1;
}

bool BlnProfile3D::GetExtremums2D( bool useAttaches, double& minx, double& maxx, double& miny, double& maxy, int ProfileDirection)
{
	//printf("BlnProfile3D::GetExtremums2D(useAttaches = %d ProfileDirection = %d)\n", useAttaches, ProfileDirection);
	bool start_x = true;
	bool start_y = true;
	/*if (m_vBlnProfiles.SetCurrentMsgOnFirst())
	{
		do
		{
			size_t len = m_vBlnProfiles.GetCurrentMsgLen();
			CPoint2 *pt2;
			pt2 = m_vBlnProfiles.GetCurrentMsgPtr();
			for(size_t i = 0; i < len; i++)
			{
				double x = pt2[i].x;
				double y = pt2[i].y;
				if (start_x)
				{
					minx = maxx = x;
					start_x = false;
				}
				else
				{
					if (minx > x) minx = x;
					if (maxx < x) maxx = x;
				}

				if (start_y)
				{
					miny = maxy = y;
					start_y = false;
				}
				else
				{
					if (miny > y) miny = y;
					if (maxy < y) maxy = y;
				}
			}
		}
		while(m_vBlnProfiles.IncrementCurrentMsg() );
	}*/

	for (size_t n = 0; n < m_vectorBlnProfiles.size(); n++)
	{
		size_t m = m_vectorBlnProfiles[n].size();
		for (size_t i = 0; i < m; i++)
		{
			double x = m_vectorBlnProfiles[n][i].x;
			double y = m_vectorBlnProfiles[n][i].y;

			if (start_x)
			{
				minx = maxx = x;
				start_x = false;
			}
			else
			{
				if (minx > x) minx = x;
				if (maxx < x) maxx = x;
			}

			if (start_y)
			{
				miny = maxy = y;
				start_y = false;
			}
			else
			{
				if (miny > y) miny = y;
				if (maxy < y) maxy = y;
			}
		}
	}


	if(this->m_pSurfDoc)
	{
		if(start_y)
		{
			if (this->m_pSurfDoc->UpdateExtremums())
			{
				maxy = this->m_pSurfDoc->GetMax().z;
				miny = this->m_pSurfDoc->GetMin().z;
				start_y = false;
			}
		}
		else
		{
			if (this->m_pSurfDoc->UpdateExtremums())
			{
				double maxy_doc = this->m_pSurfDoc->GetMax().z;
				double miny_doc = this->m_pSurfDoc->GetMin().z;
					
				if (miny > miny_doc) miny = miny_doc;
				if (maxy < maxy_doc) maxy = maxy_doc;
			}
		}
	}

	if (useAttaches)
	{
		size_t len = m_vProfileMapAttaches.size();
		for(size_t i = 0; i < len; i++)
		{
			double x = m_vProfileMapAttaches[i].xProfile;
			if (start_x)
			{
				minx = maxx = x;
				start_x = false;
			}
			else
			{
				if (minx > x) minx = x;
				if (maxx < x) maxx = x;
			}
		}
		if (len >= 2)
		{
			if(this->m_pSurfDoc)
			{
				size_t i0 = 0;
				size_t i1 = 1;

				if (this->m_pSurfDoc->UpdateExtremums())
				{
					double maxx_doc_map = this->m_pSurfDoc->GetMax().x;
					double minx_doc_map = this->m_pSurfDoc->GetMin().x;

					double maxy_doc_map = this->m_pSurfDoc->GetMax().y;
					double miny_doc_map = this->m_pSurfDoc->GetMin().y;


					double part_x1 = (minx_doc_map - m_vProfileMapAttaches[i0].xMap) / (m_vProfileMapAttaches[i1].xMap - m_vProfileMapAttaches[i0].xMap);
					double part_x2 = (maxx_doc_map - m_vProfileMapAttaches[i0].xMap) / (m_vProfileMapAttaches[i1].xMap - m_vProfileMapAttaches[i0].xMap);
					int found_x = 0;
					if (m_vProfileMapAttaches[i1].xMap - m_vProfileMapAttaches[i0].xMap != 0)
					{
						if (part_x1 <= 0) found_x = 1;
						if (part_x2 <= 0) found_x = 2;
					}
					
					double part_y1 = (miny_doc_map - m_vProfileMapAttaches[i0].yMap) / (m_vProfileMapAttaches[i1].yMap - m_vProfileMapAttaches[i0].yMap);
					double part_y2 = (maxy_doc_map - m_vProfileMapAttaches[i0].yMap) / (m_vProfileMapAttaches[i1].yMap - m_vProfileMapAttaches[i0].yMap);
					int found_y = 0;
					if (m_vProfileMapAttaches[i1].yMap - m_vProfileMapAttaches[i0].yMap != 0)
					{
						if (part_y1 <= 0) found_y = 1;
						if (part_y2 <= 0) found_y = 2;
					}	

					if (found_x || found_y)
					{
						double part = 0.0;
						double part_x = 0.0;
						double part_y = 0.0;
						
						if (found_x) part_x = found_x == 1 ? part_x1 : part_x2;						
						if (found_y) part_y = found_y == 1 ? part_y1 : part_y2;

						if (found_x && found_y)
						{
							part = max(part_x, part_y);
						}
						else
						{
							if (found_x) part = part_x;						
							if (found_y) part = part_y;
						}

						double xp = m_vProfileMapAttaches[i0].xProfile + part * (m_vProfileMapAttaches[i1].xProfile - m_vProfileMapAttaches[i0].xProfile);
						
						if (start_x)
						{
							minx = maxx = xp;
							start_x = false;
						}
						else
						{
							if (minx > xp) minx = xp;
							if (maxx < xp) maxx = xp;
						}
					}
				}								
			}
			if(this->m_pSurfDoc)
			{
				size_t i0 = len-2;
				size_t i1 = len-1;
				if (this->m_pSurfDoc->UpdateExtremums())
				{
					double maxx_doc_map = this->m_pSurfDoc->GetMax().x;
					double minx_doc_map = this->m_pSurfDoc->GetMin().x;

					double maxy_doc_map = this->m_pSurfDoc->GetMax().y;
					double miny_doc_map = this->m_pSurfDoc->GetMin().y;

					double part_x1 = (minx_doc_map - m_vProfileMapAttaches[i0].xMap) / (m_vProfileMapAttaches[i1].xMap - m_vProfileMapAttaches[i0].xMap);
					double part_x2 = (maxx_doc_map - m_vProfileMapAttaches[i0].xMap) / (m_vProfileMapAttaches[i1].xMap - m_vProfileMapAttaches[i0].xMap);
					
					int found_x = 0;
					if (m_vProfileMapAttaches[i1].xMap - m_vProfileMapAttaches[i0].xMap != 0)
					{
						if (part_x1 >= 1.0) found_x = 1;
						if (part_x2 >= 1.0) found_x = 2;
					}
					
					double part_y1 = (miny_doc_map - m_vProfileMapAttaches[i0].yMap) / (m_vProfileMapAttaches[i1].yMap - m_vProfileMapAttaches[i0].yMap);
					double part_y2 = (maxy_doc_map - m_vProfileMapAttaches[i0].yMap) / (m_vProfileMapAttaches[i1].yMap - m_vProfileMapAttaches[i0].yMap);
					
					int found_y = 0;
					if (m_vProfileMapAttaches[i1].yMap - m_vProfileMapAttaches[i0].yMap != 0)
					{
						if (part_y1 >= 1.0) found_y = 1;
						if (part_y2 >= 1.0) found_y = 2;
					}
					if (found_x || found_y)
					{
						double part = 1.0;
						double part_x = 1.0;
						double part_y = 1.0;
						
						if (found_x) part_x = found_x == 1 ? part_x1 : part_x2;						
						if (found_y) part_y = found_y == 1 ? part_y1 : part_y2;

						if (found_x && found_y)
						{
							part = min(part_x, part_y);
						}
						else
						{
							if (found_x) part = part_x;						
							if (found_y) part = part_y;
						}
						double xp = m_vProfileMapAttaches[i0].xProfile + part * (m_vProfileMapAttaches[i1].xProfile - m_vProfileMapAttaches[i0].xProfile);
					
						if (start_x)
						{
							minx = maxx = xp;
							start_x = false;
						}
						else
						{
							if (minx > xp) minx = xp;
							if (maxx < xp) maxx = xp;
						}
					}
				}		
			}
		}
	}
	else
	{
		switch (ProfileDirection)
		{
		case GRID_POFILE_DIRECTION_NORTH:
			{
				if(this->m_pSurfDoc)
				{
					if(start_x)
					{
						if (this->m_pSurfDoc->UpdateExtremums())
						{
							maxx = this->m_pSurfDoc->GetMax().y;
							minx = this->m_pSurfDoc->GetMin().y;
							start_x = false;
						}
					}
					else
					{
						if (this->m_pSurfDoc->UpdateExtremums())
						{
							double maxx_doc = this->m_pSurfDoc->GetMax().y;
							double minx_doc = this->m_pSurfDoc->GetMin().y;
								
							if (minx > minx_doc) minx = minx_doc;
							if (maxx < maxx_doc) maxx = maxx_doc;
						}
					}
				}
			}
			break;
		case GRID_POFILE_DIRECTION_EAST:
			{
				if(this->m_pSurfDoc)
				{
					if(start_x)
					{
						if (this->m_pSurfDoc->UpdateExtremums())
						{
							maxx = this->m_pSurfDoc->GetMax().x;
							minx = this->m_pSurfDoc->GetMin().x;
							start_x = false;
						}
					}
					else
					{
						if (this->m_pSurfDoc->UpdateExtremums())
						{
							double maxx_doc = this->m_pSurfDoc->GetMax().x;
							double minx_doc = this->m_pSurfDoc->GetMin().x;
								
							if (minx > minx_doc) minx = minx_doc;
							if (maxx < maxx_doc) maxx = maxx_doc;
						}
					}
				}
			}
			break;
		}	
	}

	/*printf("BlnProfile3D::GetExtremums2D ret = %d minx %f , maxx %f, miny %f, maxy %f\n",
		((!start_x) && (!start_y)),
		minx, maxx, miny, maxy);*/

	return ((!start_x) && (!start_y));
}
void BlnProfile3D::ConvertBlnProfilesTo3D(bool create_layers)
{	
	printf("BlnProfile3D::ConvertBlnProfilesTo3D()\n");

	this->m_plane.clear();
	this->m_bln_lines.clear();
	this->m_bln_lines_ObjectList.clear();

//	this->m_bln_polygones.clear();
//	this->m_bln_polygones_ObjectList.clear();

	this->m_brkn_poligons.clear();
	this->m_brkn_poligons_ObjectList.clear();

	// ищем минимум и максимум в двумерных координатах для каждого разреза
	double 
		minx,
		maxx,
		miny,
		maxy;
	
	// профиль из линий блн файлов
	if(this->GetExtremums2D(true, minx,	maxx, miny,	maxy, -1)
		)
	{
		printf("maxx = %f minx = %f\n", maxx, minx);
		printf("maxy = %f miny = %f\n", maxy, miny);

		int lenMapAttach = (int)m_vProfileMapAttaches.size();

		vector<string>::iterator iter_s = this->m_names.begin();
		vector<COLORREF>::iterator iter_c = this->m_colors.begin();
		
		{
			int ipoint = 0;
			int iprepoint;
			for(size_t n = 0; n < m_vectorBlnProfiles.size(); n++ )
			{
				size_t len = m_vectorBlnProfiles[n].size();
				//CPoint2 *pt2;
				//pt2 = m_vBlnProfiles.GetCurrentMsgPtr();
				//CPoint3 *pt3;
				//pt3 = (CPoint3*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, len*sizeof(CPoint3));
				vector<CPoint3> vpt3;
				vpt3.clear();
				CPoint3 pt3;

				vector<int> indexes_of_attach;
				vector<int> indexes_of_points;
				indexes_of_attach.clear();
				indexes_of_points.clear();
				////////////////////////////////////////
				// номер интервала в массиве привязок профиля к карте
				for(size_t i = 0; i < len; i++)
				{
					// берём горизонтальную координату профиля из блн файла
					double xProfile = m_vectorBlnProfiles[n][i].x;
					// преобразовываем эту координату в горизонтальные координаты xMap yMap в системе координат карты 
					iprepoint = ipoint;

					ProfileAttaching(xProfile, ipoint, *ptpa, pt3.x, pt3.y );

					// глубину берём без всяких преобразований из блн файла
					pt3.z = m_vectorBlnProfiles[n][i].y;
					pt3.bVisible = m_vectorBlnProfiles[n][i].bVisible;

					//  здесь добавляем точку на изломе профиля, если надо
					{
						if (i > 0 &&
							ipoint != iprepoint &&
							ipoint >= 0 &&
							iprepoint >= 0 &&
							ipoint < lenMapAttach - 1 &&
							iprepoint < lenMapAttach - 1)
						{
							CPoint3 pt_3;
							if (ipoint > iprepoint)
							{
								for(int j = iprepoint + 1; j <= ipoint; j++)
								{
									pt_3.x = (*ptpa)[j].xMap;
									pt_3.y = (*ptpa)[j].yMap;
									double part = ((*ptpa)[j].xProfile - m_vectorBlnProfiles[n][i-1].x) / (m_vectorBlnProfiles[n][i].x - m_vectorBlnProfiles[n][i-1].x);
									pt_3.z = m_vectorBlnProfiles[n][i-1].y + part*(m_vectorBlnProfiles[n][i].y - m_vectorBlnProfiles[n][i-1].y);
									pt_3.bVisible = m_vectorBlnProfiles[n][i].bVisible;
									vpt3.push_back(pt_3);
									//this->m_pSurfDoc->AddSphere(pt_3, RGB(0,0,255));
									indexes_of_attach.push_back(j);
									indexes_of_points.push_back(int(vpt3.size())-1);
								}
							}
							else
							{
								for(int j = iprepoint; j > ipoint; j--)
								{
									pt_3.x = (*ptpa)[j].xMap;
									pt_3.y = (*ptpa)[j].yMap;
									double part = ((*ptpa)[j].xProfile - m_vectorBlnProfiles[n][i-1].x) / (m_vectorBlnProfiles[n][i].x - m_vectorBlnProfiles[n][i-1].x);
									pt_3.z = m_vectorBlnProfiles[n][i-1].y + part*(m_vectorBlnProfiles[n][i].y - m_vectorBlnProfiles[n][i-1].y);
									pt_3.bVisible = m_vectorBlnProfiles[n][i].bVisible;
									vpt3.push_back(pt_3);
									//this->m_pSurfDoc->AddSphere(pt_3, RGB(0,255,0));
									indexes_of_attach.push_back(j);
									indexes_of_points.push_back(int(vpt3.size())-1);
								}
							}
						}
					}
					vpt3.push_back(pt3);
				}
				// add line
				Line3D line(this->m_pSurfDoc);
				this->m_bln_lines.AddMsg(&line);
				this->m_bln_lines.GetLastMsg().InitPoints(vpt3, 0);
				if( iter_s != this->m_names.end())
				{
					this->m_bln_lines.GetLastMsg().SetName((*iter_s));
					
					if( create_layers && this->m_pSurfDoc )
					{
						Layer * layer = this->m_pSurfDoc->FindLayer((char *)(*iter_s).c_str());
						if (layer == NULL)
							layer = this->m_pSurfDoc->AddNewLayer((char *)(*iter_s).c_str());
						this->m_bln_lines.GetLastMsg().SetLayer(layer);
					}
					
					iter_s++;
				}				
				if( iter_c != this->m_colors.end())
				{
					this->m_bln_lines.GetLastMsg().SetColor((*iter_c));
					iter_c++;
				}


				if(len > 2 
					&& m_vectorBlnProfiles[n][0].x == m_vectorBlnProfiles[n][len-1].x
					&& m_vectorBlnProfiles[n][0].y == m_vectorBlnProfiles[n][len-1].y
					)
				{
					//add polygon
					vpt3.pop_back();
					Poligon3D poly(this->m_pSurfDoc);
//					this->m_bln_polygones.AddMsg(&poly);

					BrokenPoligon_3D brkn_poly(this->m_pSurfDoc);
					this->m_brkn_poligons.AddMsg(&brkn_poly);
					this->m_brkn_poligons.GetLastMsg().m_poligones.AddMsg(&poly);
					this->m_brkn_poligons.GetLastMsg().m_poligones.GetLastMsg().InitPoints(vpt3, RGB(255,255,0));

//					this->m_bln_polygones.GetLastMsg().InitPoints(vpt3, RGB(255,255,255));
				}
				//if(pt3) HeapFree(GetProcessHeap(), 0, pt3);
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			}
			
		}
		// теперь формируем трёхмерное изображение плоскости разреза
		this->m_plane.Build(CPoint2(minx,miny), CPoint2(maxx,maxy), *ptpa);				
	}
//	this->m_bln_polygones_ObjectList.Init(this->m_bln_polygones, this);
	this->m_bln_lines_ObjectList.Init(this->m_bln_lines, this);
	this->m_brkn_poligons_ObjectList.Init(this->m_brkn_poligons, this);
}


bool BlnProfile3D::UpdateExtremums()
{
	vector<CPoint3> vptmax,vptmin;

	if (this->m_bln_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			if (this->m_bln_lines.GetCurrentMsg().UpdateExtremums())
			{
				vptmax.push_back(this->m_bln_lines.GetCurrentMsg().GetMax());
				vptmin.push_back(this->m_bln_lines.GetCurrentMsg().GetMin());
			}
		}
		while(this->m_bln_lines.IncrementCurrentMsg());
	}

	if (this->m_brkn_poligons.SetCurrentMsgOnFirst())
	{
		do
		{
			if (this->m_brkn_poligons.GetCurrentMsg().UpdateExtremums())
			{
				vptmax.push_back(this->m_brkn_poligons.GetCurrentMsg().GetMax());
				vptmin.push_back(this->m_brkn_poligons.GetCurrentMsg().GetMin());
			}
		}
		while(this->m_brkn_poligons.IncrementCurrentMsg());
	}
	return this->Object::UpdateExtremums(vptmax,vptmin);
}
void BlnProfile3D::CutAndDisvisible(bool positive, double a, double b, double c, double d)
{
	if (this->m_bln_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_bln_lines.GetCurrentMsg().CutAndDisvisible(positive, a, b, c, d);
		}
		while(this->m_bln_lines.IncrementCurrentMsg());
	}

	if (this->m_brkn_poligons.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_brkn_poligons.GetCurrentMsg().CutAndDisvisible(positive, a, b, c, d);
		}
		while(this->m_brkn_poligons.IncrementCurrentMsg());
	}

	this->m_plane.CutAndDisvisible(positive, a, b, c, d);
}
void BlnProfile3D::CutXYZandDisvisible(int subcube_number, double X, double Y, double Z)
{
	if (this->m_bln_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_bln_lines.GetCurrentMsg().CutXYZandDisvisible(subcube_number, X, Y, Z);
		}
		while(this->m_bln_lines.IncrementCurrentMsg());
	}

	if (this->m_brkn_poligons.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_brkn_poligons.GetCurrentMsg().CutXYZandDisvisible(subcube_number, X, Y, Z);
		}
		while(this->m_brkn_poligons.IncrementCurrentMsg());
	}

	this->m_plane.CutXYZandDisvisible(subcube_number, X, Y, Z);
}
void BlnProfile3D::Zoom(double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean)
{
	if (this->m_bln_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_bln_lines.GetCurrentMsg().Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,
				y_mean,
				z_mean
				);
		}
		while(this->m_bln_lines.IncrementCurrentMsg());
	}

	if (this->m_brkn_poligons.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_brkn_poligons.GetCurrentMsg().Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,
				y_mean,
				z_mean
				);
		}
		while(this->m_brkn_poligons.IncrementCurrentMsg());
	}

	this->m_plane.Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,
				y_mean,
				z_mean
				);

	m_broken_plane.Zoom(
		zoomX,zoomY,zoomZ, 
		x_mean,
		y_mean,
		z_mean);

}

bool BlnProfile3D::IsSelected(CPoint3 selected_view_pt, 
		double search_radius,
		WhatSelected& ws)
{
	search_radius = fabs(search_radius);
	if (this->m_bln_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			if(this->m_bln_lines.GetCurrentMsg().IsSelected(
				selected_view_pt, search_radius, ws	))
			{
				return true;
			}
		}
		while(this->m_bln_lines.IncrementCurrentMsg());
	}

	if (this->m_brkn_poligons.SetCurrentMsgOnFirst())
	{
		do
		{
			if(this->m_brkn_poligons.GetCurrentMsg().IsSelected(
				selected_view_pt, search_radius, ws	))
			{
				return true;
			}
		}
		while(this->m_brkn_poligons.IncrementCurrentMsg());
	}

	if(this->m_plane.IsSelected(
		selected_view_pt, search_radius, ws	))
	{
		return true;
	}

	return false;
}
bool BlnProfile3D::IsSelectedDoc(CPoint3 selected_doc_pt, 
		double search_radius,
		double & dist_to_object,
		WhatSelected& ws)
{
	bool result = false;
	search_radius = fabs(search_radius);
	if (this->m_bln_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			if(this->m_bln_lines.GetCurrentMsg().IsSelectedDoc(
				selected_doc_pt, search_radius, dist_to_object, ws	))
			{
				result = true;
			}
		}
		while(this->m_bln_lines.IncrementCurrentMsg());
	}
	return result;
}
bool BlnProfile3D::IsSelectedLine(gdiplus_map_view * gv, int mouse_x, int mouse_y, double & dist_to_line, WhatSelected& ws)
{
	bool result = false;
	if (this->m_bln_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			if(this->m_bln_lines.GetCurrentMsg().IsSelectedLine(gv, this, mouse_x, mouse_y, dist_to_line, ws))
			{
				result = true;
			}
		}
		while(this->m_bln_lines.IncrementCurrentMsg());
	}
	return result;
}

bool BlnProfile3D::IsSelectedGridDataPoint(gdiplus_map_view * gv, int mouse_x, int mouse_y, double & dist_to_point, WhatSelected& ws, GridData *&pGridData)
{
	bool result = false;
	pGridData = NULL;

	if(this->m_pSurfDoc)
	{
		if(this->m_pSurfDoc->m_grid_data.SetCurrentMsgOnFirst())
		{
			do
			{
				if (
					this->m_pSurfDoc->m_grid_data.GetCurrentMsg().IsCheckedEx() && 
					this->m_pSurfDoc->m_grid_data.GetCurrentMsg().IsSelectedGridDataPoint(gv, this, mouse_x, mouse_y, dist_to_point, ws)
					)
					{
						result = true;
						pGridData = &this->m_pSurfDoc->m_grid_data.GetCurrentMsg();
					}			
			}
			while(this->m_pSurfDoc->m_grid_data.IncrementCurrentMsg());
		}
	}

	return result;

}

bool BlnProfile3D::IsSelectedWell(gdiplus_map_view * gv, int mouse_x, int mouse_y, double & dist_to_well, WhatSelected& ws)
{
	bool result = false;

	if(this->m_pSurfDoc)
	{
		if(this->m_pSurfDoc->m_drills.SetCurrentMsgOnFirst())
		{
			do
			{
				if (
					this->m_pSurfDoc->m_drills.GetCurrentMsg().IsCheckedEx() && 
					this->m_pSurfDoc->m_drills.GetCurrentMsg().OnProfile(this) && 
					this->m_pSurfDoc->m_drills.GetCurrentMsg().IsSelectedWell(gv, this, mouse_x, mouse_y, dist_to_well, ws)
					)
					{
						result = true;
					}			
			}
			while(this->m_pSurfDoc->m_drills.IncrementCurrentMsg());
		}
	}

	return result;
}

HTREEITEM BlnProfile3D::AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s)
{
    char szItemText[TEXT_LEN]; // label text of tree-view item 
	Object * pObject = dynamic_cast<Object *> (this);
	//====== Размеры изображаемого объекта
	sprintf_s(szItemText, TEXT_LEN, "BlnProfile \"%s\"", GetName().c_str());
	//=============================================================
	// Add the item to the tree-view control. 
	HTREEITEM h2 = AddItemToTree(hwndTV, szItemText, pObject, h1); 
	//=============================================================
	{
		// Add the item to the tree-view control
		sprintf_s(szItemText, TEXT_LEN, "Lines");
		pObject = dynamic_cast<Object *> (&this->m_bln_lines_ObjectList);
		HTREEITEM h3 = AddItemToTree(hwndTV, szItemText, pObject, h2);
		//
		if (this->m_bln_lines.SetCurrentMsgOnFirst())
		{
			do
			{
				this->m_bln_lines.GetCurrentMsg().AddItem_ToTree(hwndTV, h3);
			}
			while(this->m_bln_lines.IncrementCurrentMsg());
		}

		// Add the item to the tree-view control
		sprintf_s(szItemText, TEXT_LEN, "Broken Polygones");
		pObject = dynamic_cast<Object *> (&this->m_brkn_poligons_ObjectList);
		h3 = AddItemToTree(hwndTV, szItemText, pObject, h2);
		//
		if (this->m_brkn_poligons.SetCurrentMsgOnFirst())
		{
			do
			{
				this->m_brkn_poligons.GetCurrentMsg().AddItem_ToTree(hwndTV, h3);
			}
			while(this->m_brkn_poligons.IncrementCurrentMsg());
		}
		
		this->m_plane.AddItem_ToTree(hwndTV, h2);

		this->m_broken_plane.AddItem_ToTree(hwndTV, h2);
	}
	return h2;

	//=============================================================
}

void BlnProfile3D::Draw()
{
	printf("BlnProfile3D::Draw()\n");
	if (this->m_bln_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_bln_lines.GetCurrentMsg().Draw();
		}
		while(this->m_bln_lines.IncrementCurrentMsg());
	}

	if (this->m_brkn_poligons.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_brkn_poligons.GetCurrentMsg().Draw();
		}
		while(this->m_brkn_poligons.IncrementCurrentMsg());
	}

	this->m_plane.InitDoc(this->m_pSurfDoc);
	this->m_plane.Draw();
		
	m_broken_plane.InitDoc(this->m_pSurfDoc);
	m_broken_plane.Draw();

}
void BlnProfile3D::ReDraw()
{
	if(this->m_pSurfDoc) this->ReDrawItem_OnTree(this->m_pSurfDoc->hwndTV);
	if (this->m_bln_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_bln_lines.GetCurrentMsg().ReDraw();
		}
		while(this->m_bln_lines.IncrementCurrentMsg());
	}

	if (this->m_brkn_poligons.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_brkn_poligons.GetCurrentMsg().ReDraw();
		}
		while(this->m_brkn_poligons.IncrementCurrentMsg());
	}

	this->m_plane.InitDoc(this->m_pSurfDoc);
	this->m_plane.ReDraw();

	m_broken_plane.InitDoc(this->m_pSurfDoc);
	m_broken_plane.ReDraw();

}
void BlnProfile3D::EnumObjects(WPARAM wParam, LPARAM lParam, void * p,
		bool (Object::* condition_fun)(),
		void (* callback_fun)(Object*, WPARAM , LPARAM, void * ) )
{

	if (this->m_bln_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_bln_lines.GetCurrentMsg().EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		}
		while(this->m_bln_lines.IncrementCurrentMsg());
	}

	if (this->m_brkn_poligons.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_brkn_poligons.GetCurrentMsg().EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		}
		while(this->m_brkn_poligons.IncrementCurrentMsg());
	}
	this->m_plane.EnumObjects(wParam,lParam,p,condition_fun, callback_fun);

	if ((this->*condition_fun)())
	{
		(* callback_fun)(this, wParam, lParam, p);
	}
}
void BlnProfile3D::SetLayer(const Layer* layer)
{
	this->Object::SetLayer_NonVirtual(layer);
	if (this->m_bln_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_bln_lines.GetCurrentMsg().SetLayer(layer);
		}
		while(this->m_bln_lines.IncrementCurrentMsg());
	}

	if (this->m_brkn_poligons.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_brkn_poligons.GetCurrentMsg().SetLayer(layer);
		}
		while(this->m_brkn_poligons.IncrementCurrentMsg());
	}
	this->m_plane.SetLayer(layer);
}


size_t BlnProfile3D::GetPointsNumber()
{
	return (size_t)this->m_bln_lines.msgSize();
}

void BlnProfile3D::PropertiesDialog()
{
	MessageBox(0, "PropertiesDialog", "BlnProfile3D" , 0);
}

bool BlnProfile3D::ColorDialog(void)
{
	return false;
}

COLORREF BlnProfile3D::GetColor(void)
{
	return COLORREF();
}

void BlnProfile3D::SetColor(COLORREF color)
{
}

void BlnProfile3D::FillContextMenu(HMENU& hMenu)
{
	this->Object::FillContextMenu(hMenu);
#if !VIEW_ONLY_VERSION
	AppendMenu( hMenu, MFT_SEPARATOR, 0, NULL );
	AppendMenu( hMenu, MFT_STRING, ID_TREE_BLNPROFILE_CREATEEMPTYLINEOBJECT, "Create empty Line Object" );
	AppendMenu( hMenu, MFT_STRING, ID_TREE_BLNPROFILE_EDITATTACHES, "Edit Attaches (plane)" );
	AppendMenu( hMenu, MFT_STRING, ID_TREE_BLNPROFILE_PRINTATTACHES, "Print Attaches" );
	AppendMenu( hMenu, MFT_STRING, ID_TREE_BLNPROFILE_MAP, "Produce map" );	
#endif /*!VIEW_ONLY_VERSION*/
	AppendMenu( hMenu, MFT_SEPARATOR, 0, NULL );
	AppendMenu( hMenu, MFT_STRING, ID_TREE_BLNPROFILE_GDIMAP, /*"Produce GDI map"*/ "2D ПРОФИЛЬ" );
	AppendMenu( hMenu, MFT_STRING, ID_TREE_BLNPROFILE_NONSTRETCHEDGDIVIEW, "Non Stretched GDI view" );
	AppendMenu( hMenu, MFT_STRING, ID_TREE_BLNPROFILE_STRETCHEDGDIVIEW, "Stretched GDI view" );
	AppendMenu( hMenu, MFT_SEPARATOR, 0, NULL );
	AppendMenu( hMenu, MFT_STRING, ID_TREE_BLNPROFILE_SAVEASCUBEPROJECTIONGRIDS, "Save as cube projection grids" );
	AppendMenu( hMenu, MFT_STRING, ID_TREE_BLNPROFILE_ADDBROKEPOINTSTOLINES, "Add Broke Points To Lines" );
	AppendMenu( hMenu, MFT_SEPARATOR, 0, NULL );
	AppendMenu( hMenu, MFT_STRING, ID_TREE_BLNPROFILE_CUTTING, "Cutting" );
	AppendMenu( hMenu, MFT_STRING, ID_TREE_BLNPROFILE_SAVEASRAZREZ, "Save As Razrez" );
	AppendMenu( hMenu, MFT_STRING, ID_TREE_BLNPROFILE_DXFRAZREZ, "AutoCAD Razrez" );	
}

void BlnProfile3D::AddBrokePointsToLines()
{
	if (this->m_bln_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			if(this->m_bln_lines.GetCurrentMsg().AddBrokePoints(this))
			{
				if (this->m_pSurfDoc)
				{
					this->m_bln_lines.GetCurrentMsg().Zoom(
						this->m_pSurfDoc->m_zoomX, 
						this->m_pSurfDoc->m_zoomY, 
						this->m_pSurfDoc->m_zoomZ,
						this->m_pSurfDoc->m_xd_zoom_center,
						this->m_pSurfDoc->m_yd_zoom_center,
						this->m_pSurfDoc->m_zd_zoom_center);	
				}
				this->m_bln_lines.GetCurrentMsg().ReDraw();
			}
		}
		while(this->m_bln_lines.IncrementCurrentMsg());
	}
}

Line3D* BlnProfile3D::AddLine()
{
	if(this->m_pSurfDoc)
	{
		Line3D line(this->m_pSurfDoc);
		line.SetColor(RGB(0,0,0));

		m_bln_lines.AddMsg(&line);
		m_bln_lines_ObjectList.Init(m_bln_lines, this);

		if (m_bln_lines.SetCurrentMsgOnLast())
		{	
			HTREEITEM& h1 = m_bln_lines_ObjectList.myTreeItem; 
			if (h1 == NULL)
				h1 = AddObjectListItem(this->m_pSurfDoc->hwndTV, "Lines", &m_bln_lines_ObjectList); 
			m_bln_lines.GetCurrentMsg().AddItem_ToTree(this->m_pSurfDoc->hwndTV,h1);
			return &m_bln_lines.GetCurrentMsg();
		}
	}
	return NULL;
}


#include "../../wintools\src\project.h"
#include "../../wintools\src\win32_map_views.h"


VOID Example_AddMetafileComment(HDC hdc)
{
   Graphics graphics(hdc);

   // Create a Metafile object for recording.
   Metafile metaFile(L"SampleMeta.emf", hdc);

   {
	   Graphics metaGraphics(&metaFile);
	   // Draw a rectangle in metaFile.
	   Pen pen(Color(255, 0, 0, 0));
	   metaGraphics.DrawRectangle(&pen, 0, 0, 100, 100);
	   
	   // Create a comment, and add it to metaFile.
	   BYTE metaComment[] = "Test";
	   metaGraphics.AddMetafileComment(metaComment, 4);
   }

   // Draw metaFile.
   graphics.DrawImage(&metaFile, Point(0, 0));
}
VOID Example_BeginContainer(HDC hdc)
{
   Graphics graphics(hdc);

   // Set the clipping region for the Graphics object.
   graphics.SetClip(Rect(10, 10, 150, 150));

   // Begin a graphics container.
   GraphicsContainer container = graphics.BeginContainer();

   // Set an additional clipping region for the container.
   graphics.SetClip(Rect(100, 50, 100, 75));

   // Fill a red rectangle in the container.
   SolidBrush redBrush(Color(255, 255, 0, 0));
   graphics.FillRectangle(&redBrush, 0, 0, 400, 400);

   // End the container, and fill the same rectangle with blue. 
   graphics.EndContainer(container);
   SolidBrush blueBrush(Color(128, 0, 0, 255));
   graphics.FillRectangle(&blueBrush, 0, 0, 400, 400);

   // Set the clipping region to infinite, and draw the outlines 
   // of the two previous clipping regions.
   graphics.ResetClip();
   Pen blackPen(Color(255, 0, 0, 0), 2.0f);
   graphics.DrawRectangle(&blackPen, 10, 10, 150, 150);
   graphics.DrawRectangle(&blackPen, 100, 50, 100, 75);
}
VOID Example_BeginContainer2(HDC hdc)
{
   Graphics graphics(hdc);

   // Define a translation and scale transformation for the container.
   Rect srcRect(0, 0, 200, 100);
   Rect destRect(100, 100, 200, 200);

   // Create a graphics container with a (100, 100) translation 
   // and (1, 2) scale.
   GraphicsContainer container;
   container = graphics.BeginContainer(destRect, srcRect, UnitPixel);

   // Fill an ellipse in the container.
   SolidBrush redBrush(Color(255, 255, 0, 0));
   graphics.FillEllipse(&redBrush, 0, 0, 100, 60);

   // End the container.
   graphics.EndContainer(container);

   // Fill the same ellipse outside the container.
   SolidBrush blueBrush(Color(255, 0, 0, 255));
   graphics.FillEllipse(&blueBrush, 0, 0, 100, 60);
}
VOID Example_BeginContainer3(HDC hdc)
{
   Graphics graphics(hdc);

   // Define a translation and scale transform for the container.
   RectF srcRect(0, 0, 200, 100);
   RectF destRect(100, 100, 200, 200);

   // Create a graphics container with a (100, 100) translation 
   // and (1, 2) scale.
   GraphicsContainer container;
   container = graphics.BeginContainer(destRect, srcRect, UnitPixel);

   // Fill a rectangle in the container.
   SolidBrush redBrush(Color(255, 255, 0, 0));
   graphics.FillEllipse(&redBrush, 0, 0, 100, 60);

   // End the container.
   graphics.EndContainer(container);

   // Fill a rectangle outside the container.
   SolidBrush blueBrush(Color(255, 0, 0, 255));
   graphics.FillEllipse(&blueBrush, 0, 0, 100, 60);
}
VOID Example_Clear(HDC hdc)
{
   Graphics graphics(hdc);

   // Create a Color object.
   Color blueColor(255, 0, 0, 255);

   // Clear the screen with a blue background.
   graphics.Clear(blueColor);
}
//
//Hit Testing with a Region 

//--------------------------------------------------------------------------------

//The purpose of hit testing is to determine whether the cursor is over a given object, 
//such as an icon or a button. The following example creates a plus-shaped region by 
//forming the union of two rectangular regions. Assume that the variable point holds 
//the location of the most recent click. The code checks to see whether point is in 
//the plus-shaped region. If point is in the region (a hit), the region is filled 
//with an opaque red brush. Otherwise, the region is filled with a semitransparent red brush.


void Example_HitTest(HDC hdc)
{
	Graphics graphics(hdc);
	Point point(60, 10);
	// Assume that the variable "point" contains the location
	// of the most recent click.
	// To simulate a hit, assign (60, 10) to point.
	// To simulate a miss, assign (0, 0) to point.
	//SolidBrush solidBrush(Color());
	Color color = Color();
	SolidBrush solidBrush(color);
	Region region1(Rect(50, 0, 50, 150));
	Region region2(Rect(0, 50, 150, 50));
	// Create a plus-shaped region by forming the union of region1 and region2.
	// The union replaces region1.
	region1.Union(&region2);
	if(region1.IsVisible(point, &graphics))
	{
		// The point is in the region. Use an opaque brush.
		solidBrush.SetColor(Color(255, 255, 0, 0));
	}
	else
	{
		// The point is not in the region. Use a semitransparent brush.
		solidBrush.SetColor(Color(64, 255, 0, 0));
	}
	graphics.FillRegion(&solidBrush, &region1);
}
void BlnProfile3D::DrawGDIplus(Graphics ** select_buffer, Graphics& graphics, map_view * v )
{	
	//Example_AddMetafileComment(v->GetHDC());
	//Example_BeginContainer(v->GetHDC());
	//Example_BeginContainer3(v->GetHDC());
	//Example_Clear(v->GetHDC());

	//Example_HitTest(v->GetHDC());
	int alpha_surf = 255;
		
	for (int isurf = 0; isurf < m_broken_plane.m_polySloi.Size(); isurf++)
	{
#if USE_UNVISIBLE_CUTTING
		for (int icutting = 0; icutting < m_broken_plane.m_polySloi[isurf].m_poligones.size(); icutting++)
		{
			for (int i = 0; i < m_broken_plane.m_polySloi[isurf].m_poligones[icutting].Size(); i++)
			{
				Poligon3D * pPoligon = &m_broken_plane.m_polySloi[isurf].m_poligones[icutting][i];
				if (pPoligon && pPoligon->IsCheckedEx())
					pPoligon->DrawGDIplus(select_buffer, graphics, v, this);
			}

		}
#else
		for (int icutting = 0; icutting < m_broken_plane.m_polySloi[isurf].m_poligones.Size(); icutting++)
		{
			Poligon3D * pPoligon = &m_broken_plane.m_polySloi[isurf].m_poligones[icutting];
			if (pPoligon && pPoligon->IsCheckedEx())
				pPoligon->DrawGDIplus(select_buffer, graphics, v, this);

		}
#endif
	}
	for (int isurf = 0; isurf < m_broken_plane.m_broken_lines.Size(); isurf++)
	{
		for (int icutting = 0; icutting < m_broken_plane.m_broken_lines[isurf].m_lines.Size(); icutting++)
		{
			Line3D * pline = &m_broken_plane.m_broken_lines[isurf].m_lines[icutting];
			if (pline && pline->IsCheckedEx())
				pline->DrawGDIplus(select_buffer, graphics, v, this, alpha_surf);

		}
	}
	for (int isurf = 0; isurf < m_broken_plane.m_broken_fault_lines.Size(); isurf++)
	{
		for (int icutting = 0; icutting < m_broken_plane.m_broken_fault_lines[isurf].m_lines.Size(); icutting++)
		{
			Line3D * pline = &m_broken_plane.m_broken_fault_lines[isurf].m_lines[icutting];
			if (pline && pline->IsCheckedEx())
				pline->DrawGDIplus(select_buffer, graphics, v, this, alpha_surf);

		}
	}
	for (int isurf = 0; isurf < m_broken_plane.m_broken_catch_lines.Size(); isurf++)
	{
		for (int icutting = 0; icutting < m_broken_plane.m_broken_catch_lines[isurf].m_lines.Size(); icutting++)
		{
			Line3D * pline = &m_broken_plane.m_broken_catch_lines[isurf].m_lines[icutting];
			if (pline && pline->IsCheckedEx())
				pline->DrawGDIplus(select_buffer, graphics, v, this, alpha_surf);

		}
	}

	//broken_plane.SaveAsRazres();
#if 0
	if(this->m_pSurfDoc)
	{
		if(this->m_pSurfDoc->m_surfaces.SetCurrentMsgOnFirst())
		{
			do
			{
				if (this->m_pSurfDoc->m_surfaces.GetCurrentMsg().IsCheckedEx())
					this->DrawGDIplus(select_buffer, graphics, v, &this->m_pSurfDoc->m_surfaces.GetCurrentMsg() );
			}
			while(this->m_pSurfDoc->m_surfaces.IncrementCurrentMsg());
		}
	}
#endif
	int alpha = this->m_pSurfDoc ? this->m_pSurfDoc->m_alpha_plane : 255;

	if (this->m_bln_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			Line3D * pObject = &this->m_bln_lines.GetCurrentMsg();
			//if (pObject && pObject->m_bChecked && (!pObject->GetLayer() || (pObject->GetLayer() && pObject->GetLayer()->bChecked)))
			if (pObject && pObject->IsCheckedEx())
				pObject->DrawGDIplus(select_buffer, graphics, v, this, alpha);
		}
		while(this->m_bln_lines.IncrementCurrentMsg());
	}

	if (this->m_brkn_poligons.SetCurrentMsgOnFirst())
	{
		do
		{
			BrokenPoligon_3D * pObject = &this->m_brkn_poligons.GetCurrentMsg();
			if (pObject && pObject->IsCheckedEx())
				pObject->DrawGDIplus(select_buffer, graphics, v, this);
		}
		while(this->m_brkn_poligons.IncrementCurrentMsg());
	}

	if (this->m_plane.IsCheckedEx())
	{
		this->m_plane.InitDoc(this->m_pSurfDoc);
		this->m_plane.DrawGDIplus(select_buffer, graphics, v, this);
	}

	if(this->m_pSurfDoc)
	{
		if(this->m_pSurfDoc->m_drills.SetCurrentMsgOnFirst())
		{
			do
			{
				if (this->m_pSurfDoc->m_drills.GetCurrentMsg().IsCheckedEx())
					this->m_pSurfDoc->m_drills.GetCurrentMsg().DrawGDIplus(select_buffer, graphics, v, this);
			}
			while(this->m_pSurfDoc->m_drills.IncrementCurrentMsg());
		}
	}

	if(this->m_pSurfDoc)
	{
		if(this->m_pSurfDoc->m_cubes.SetCurrentMsgOnFirst())
		{
			do
			{
				if (this->m_pSurfDoc->m_cubes.GetCurrentMsg().IsCheckedEx())
					this->DrawGDIplus(select_buffer, graphics, v, &this->m_pSurfDoc->m_cubes.GetCurrentMsg() );
			}
			while(this->m_pSurfDoc->m_cubes.IncrementCurrentMsg());
		}
	}



	if(this->m_pSurfDoc)
	{
		if(this->m_pSurfDoc->m_grid_data.SetCurrentMsgOnFirst())
		{
			do
			{
				if (this->m_pSurfDoc->m_grid_data.GetCurrentMsg().IsCheckedEx())
					this->m_pSurfDoc->m_grid_data.GetCurrentMsg().DrawGDIplus(select_buffer, graphics, v, this);
			}
			while(this->m_pSurfDoc->m_grid_data.IncrementCurrentMsg());
		}
	}

	int n_cut, n_surf, n_drill, n_point, n_fault, n_catch;
	for (n_point = 0; n_point < m_broken_plane.m_pointsDrillSloi.PLANE_MEMBERS_VECTOR_SIZE(); n_point++)
	{
		for (n_surf = 0; n_surf < m_broken_plane.m_pointsDrillSloi[n_point].PLANE_MEMBERS_VECTOR_SIZE(); n_surf++)
		{
			if (m_broken_plane.m_pointsDrillSloi[n_point][n_surf].IsCheckedEx())
				m_broken_plane.m_pointsDrillSloi[n_point][n_surf].DrawGDIplus(select_buffer, graphics, v, this);
		}
	}

	for (n_point = 0; n_point < m_broken_plane.m_pointsDrillSloi_right.PLANE_MEMBERS_VECTOR_SIZE(); n_point++)
	{
		for (n_surf = 0; n_surf < m_broken_plane.m_pointsDrillSloi_right[n_point].PLANE_MEMBERS_VECTOR_SIZE(); n_surf++)
		{
			if (m_broken_plane.m_pointsDrillSloi_right[n_point][n_surf].IsCheckedEx())
				m_broken_plane.m_pointsDrillSloi_right[n_point][n_surf].DrawGDIplus(select_buffer, graphics, v, this);
		}
	}

	for (n_point = 0; n_point < m_broken_plane.m_pointsDrillSloi_left.PLANE_MEMBERS_VECTOR_SIZE(); n_point++)
	{
		for (n_surf = 0; n_surf < m_broken_plane.m_pointsDrillSloi_left[n_point].PLANE_MEMBERS_VECTOR_SIZE(); n_surf++)
		{
			if (m_broken_plane.m_pointsDrillSloi_left[n_point][n_surf].IsCheckedEx())
				m_broken_plane.m_pointsDrillSloi_left[n_point][n_surf].DrawGDIplus(select_buffer, graphics, v, this);
		}
	}

	for (n_cut = 0; n_cut < m_broken_plane.m_SurfLineIntersectPoints.size(); n_cut++)
	{
		for (n_point = 0; n_point < m_broken_plane.m_SurfLineIntersectPoints[n_cut].size(); n_point++)
		{
			if (m_broken_plane.m_SurfLineIntersectPoints[n_cut][n_point].point.IsCheckedEx())
				m_broken_plane.m_SurfLineIntersectPoints[n_cut][n_point].point.DrawGDIplus(select_buffer, graphics, v, this);
		}
	}

	
}

bool BlnProfile3D::UpdateExtremums(CPoint2 & profile_min, CPoint2 & profile_max)
{
	//printf("BlnProfile3D::UpdateExtremums(CPoint2 & profile_min, CPoint2 & profile_max)\n");
	bool start = true;

	vector<CPoint3> vptmax,vptmin;

	if (this->m_bln_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			if (this->m_bln_lines.GetCurrentMsg().UpdateExtremums(this, start, profile_min, profile_max))
			{
			}
		}
		while(this->m_bln_lines.IncrementCurrentMsg());
	}

	if (this->m_brkn_poligons.SetCurrentMsgOnFirst())
	{
		do
		{
			if (this->m_brkn_poligons.GetCurrentMsg().UpdateExtremums(this, start, profile_min, profile_max))
			{
			}
		}
		while(this->m_brkn_poligons.IncrementCurrentMsg());
	}
	if (this->m_plane.UpdateExtremums(this, start, profile_min, profile_max))
	{
	}
	return !start;
}

void BlnProfile3D::Cutting()
{
	TreeView_DeleteMyItem(this->m_pSurfDoc->hwndTV, this->m_broken_plane.myTreeItem);
	
	this->m_broken_plane.clear();
	this->m_broken_plane.InitDoc(this->m_pSurfDoc);
	this->m_broken_plane.Cutting();

	this->m_broken_plane.Zoom(
						this->m_pSurfDoc->m_zoomX, 
						this->m_pSurfDoc->m_zoomY, 
						this->m_pSurfDoc->m_zoomZ,
						this->m_pSurfDoc->m_xd_zoom_center,
						this->m_pSurfDoc->m_yd_zoom_center,
						this->m_pSurfDoc->m_zd_zoom_center);

	this->m_broken_plane.AddItem_ToTree(this->m_pSurfDoc->hwndTV, this->myTreeItem);
}

void BlnProfile3D::ProduceGDIMap()
{

	project * prj = dynamic_cast<project *>(this->m_pSurfDoc);
	if (prj)
	{
		const char * s1 = "frame(num)"; const char * sv = "distance (nm)";
		map_view * v = prj->AddGDIMapView(this, true);
	}
}

#if 1
void BlnProfile3D::ProduceMap()
{
	//printf("BlnProfile3D::Produce2Dview\n");

	project * prj = dynamic_cast<project *>(this->m_pSurfDoc);
	if (prj)
	{
		const char * s1 = "frame(num)"; const char * sv = "distance (nm)";
		map_view * plot = prj->AddMapView(this, true);

		for (size_t n = 0; n < m_vectorBlnProfiles.size(); n++)
		{
			size_t len = m_vectorBlnProfiles[n].size();
			for(size_t i = 0; i < len; i++)
			{
				double x = m_vectorBlnProfiles[n][i].x;
				double y = m_vectorBlnProfiles[n][i].y;

//printf("x = %f y = %f\n", x,y);

					void * udata = NULL;
//					plot->AddData(x, y, udata);

			}
		}
		
		// the "eng" object is the setup->current_eng object, so there's no need to delete it...
//		plot->SetCenterAndScale();
//		plot->Update();
	}
}
#else
void BlnProfile3D::ProduceMap()
{
	//printf("BlnProfile3D::Produce2Dview\n");

	project * prj = dynamic_cast<project *>(this->m_pSurfDoc);
	if (prj)
	{
		const char * s1 = "frame(num)"; const char * sv = "distance (nm)";
		plot1d_view * plot = prj->AddPlot1DView(PLOT_USERDATA_STRUCTURE, s1, sv, true);

		for (size_t n = 0; n < m_vectorBlnProfiles.size(); n++)
		{
			size_t len = m_vectorBlnProfiles[n].size();
			for(size_t i = 0; i < len; i++)
			{
				double x = m_vectorBlnProfiles[n][i].x;
				double y = m_vectorBlnProfiles[n][i].y;

//printf("x = %f y = %f\n", x,y);

					void * udata = NULL;
					plot->AddData(x, y, udata);

			}
		}
		
		// the "eng" object is the setup->current_eng object, so there's no need to delete it...
		plot->SetCenterAndScale();
		plot->Update();
	}
}
#endif
void SaveAsDat(const char *fn, vector<CPoint3> v)
{
	FILE *stream = fopen(fn, "wt");
	if (stream)
	{
		for(size_t i = 0; i < v.size(); i++)
		{
			fprintf(stream, "%lf, %lf, %lf\n", 
				v[i].x, 
				v[i].y,
				v[i].z);
				
		}
		fclose(stream);
	}
}

char * SelectNameFromPath(const char * path, char * name, size_t len)
{
	sprintf_s(name, len, "%s\0", path);
	char * p = strrchr(name,'.');
	if (p) (*p) = '\0';
	char * p1 = strrchr(name,'\\');
	char * p2 = strrchr(name,'/');
	if (p1 && !p2)
		p = p1+1;
	else if (!p1 && p2)
		p = p2+1;
	else if (p1 && p2)
		p = p1 > p2 ? p1 : p2;
	else if (!p1 && !p2)
		p = (char *)name;

	return p;
}
	
void ReplaceSymbols(const char * name, const char in, const char out)
{
	char * p = NULL;
	while ( (p = (char *)strchr(name, in)) != NULL)
	{
		*p = out;
	}
}

void PrintDoProfileScript(FILE * bas)
{
	if (bas)
	{
		fprintf(bas, "Sub DoProfile( directory As String, profilename As String, filename_lvl As String,  filenames_grd() As String, useXLimits As Boolean, xMin As Double, xMax As Double)\n");
		fprintf(bas, "\t'Declares SurferApp as an object\n");
		fprintf(bas, "\tDim SurferApp As Object\n");
		fprintf(bas, "\t'Creates an instance of the Surfer Application object and assigns it to\n");
		fprintf(bas, "\t'the variable named \"SurferApp\"\n");
		fprintf(bas, "\tSet SurferApp = CreateObject(\"Surfer.Application\")\n");
		fprintf(bas, "\tSet SurferApp = GetObject(,\"Surfer.Application\")\n");
		fprintf(bas, "\tIf Err.Number<>0 Then\n");
		fprintf(bas, "\t\tSet SurferApp = CreateObject(\"Surfer.Application\")\n");
		fprintf(bas, "\tEnd If\n");
		fprintf(bas, "\t'Makes Surfer visible\n");
		fprintf(bas, "\tSurferApp.Visible = True\n");
		fprintf(bas, "\t'Declares Plot as an object\n");
		fprintf(bas, "\tDim Plot As Object\n");
		fprintf(bas, "\t'Creates a plot document in Surfer and assigns it to the variable named\n");
		fprintf(bas, "\t'\"Plot\"\n");
		fprintf(bas, "\tSet Plot = SurferApp.Documents.Add(srfDocPlot)\n");		
		fprintf(bas, "\t'Declares Shapes as an object\n");		
		fprintf(bas, "\tDim Shapes As Object\n");		
		fprintf(bas, "\t'Assigns the Shapes collection to the variable named \"Shapes\"\n");		
		fprintf(bas, "\tSet Shapes = Plot.Shapes\n");		
		fprintf(bas, "\t'Declares MapFrame as an object\n");		
		fprintf(bas, "\tDim MapFrame As Object\n");		
		fprintf(bas, "\t'Creates a contour map and assigns the map coordinate system to the\n");		
		fprintf(bas, "\t'variable named \"MapFrame\"\n");		
		fprintf(bas, "\t' Open an existing grid\n");		
		fprintf(bas, "\tPlot.Selection.DeselectAll\n");		
		fprintf(bas, "\tFor J = LBound(filenames_grd) To UBound(filenames_grd)\n");		
		fprintf(bas, "\t\tSet MapFrame = Shapes.AddContourMap(filenames_grd(J))\n");		
		fprintf(bas, "\t\t'Declares ContourMap as an object\n");		
		fprintf(bas, "\t\tDim ContourMap As Object\n");		
		fprintf(bas, "\t\t'Assigns the contour map properties to the variable named \"ContourMap\"\n");		
		fprintf(bas, "\t\tSet ContourMap = MapFrame.Overlays(1)\n");		
		fprintf(bas, "\t\tContourMap.Levels.LoadFile(filename_lvl)\n");		
		fprintf(bas, "\t\tContourMap.FillContours = True\n");		
		fprintf(bas, "\t\tContourMap.SmoothContours = srfConSmoothMed\n");		
		fprintf(bas, "\t\tContourMap.LabelFont.Face = \"Times New Roman\"\n");		
		fprintf(bas, "\t\tContourMap.LabelFont.Italic = True\n");		
		fprintf(bas, "\t\tContourMap.LabelFont.Size = 6\n");		
		fprintf(bas, "\t\tMapFrame.Selected = True\n");	
		fprintf(bas, "\tNext J\n");	
		fprintf(bas, "\t' Overlay the selected maps\n");	
		fprintf(bas, "\tDim MapFrame2 As Object\n");	
		fprintf(bas, "\tSet MapFrame2 = Plot.Selection.OverlayMaps\n");	
		fprintf(bas, "\tMapFrame2.xMapPerPU = 2\n");
		fprintf(bas, "\tMapFrame2.yMapPerPU = 2\n");
		fprintf(bas, "\tIf useXLimits Then\n");	
		fprintf(bas, "\t\tDim yMin As Double\n");
		fprintf(bas, "\t\tDim yMax As Double\n");
		fprintf(bas, "\t\tyMin = MapFrame2.yMin\n");
		fprintf(bas, "\t\tyMax = MapFrame2.yMax\n");
		fprintf(bas, "\t\tMapFrame2.SetLimits( xMin, xMax, yMin, yMax )\n");
		fprintf(bas, "\tEnd If\n");
		fprintf(bas, "\tFor I = 1 To MapFrame2.Axes.Count\n");
		fprintf(bas, "\t\tMapFrame2.Axes(I).Visible = False\n");
		fprintf(bas, "\tNext I\n");
		fprintf(bas, "\t' Save the active document using its current name\n");
		fprintf(bas, "\tDim filename_srf As String\n");
		fprintf(bas, "\tfilename_srf = directory + \"\\srf\\\" + profilename + \".srf\"\n");
		fprintf(bas, "\tPlot.SaveAs filename_srf\n");
		fprintf(bas, "\t'Export into DXF\n");
		fprintf(bas, "\t\n");
		fprintf(bas, "\t'Option 				Action 												Default\n");
		fprintf(bas, "\t'Defaults=1   			Set all options to their default values 			No\n");
		fprintf(bas, "\t'ForgetOptions=1  		Don't remember options for later use 				No\n");
		fprintf(bas, "\t'FileCompatibility=14	DXF file compatible with ACAD R14 (or later)\n");
		fprintf(bas, "\t'FileCompatibility=13	DXF file compatible with ACAD R13 (or earlier)  	14\n");
		fprintf(bas, "\t'FormatASCII=1			DXF file will be written in ASCII format        	Yes\n");
		fprintf(bas, "\t'FormatASCII=0			DXF file will be written in Binary format			No\n");
		fprintf(bas, "\t'ScalingSourceApp=1		Use application-supplied scaling parameters     	Yes\n");
		fprintf(bas, "\t'ScalingSourceApp=0		Use saved scaling parameters						No\n");
		fprintf(bas, "\t'SaveScalingInfo=1		Save scaling parameters for later use				No\n");
		fprintf(bas, "\t'AllColorsSame=1		All colors converted to default color				No\n");
		fprintf(bas, "\t'AllStylesSame=1		All line styles converted to default line style 	Yes\n");
		fprintf(bas, "\t'AllWidthsSame=1		All line widths converted to default line width 	No\n");
		fprintf(bas, "\t'AllTextToAreas=1		All text converted to solid areas					Yes\n");
		fprintf(bas, "\t'FillSolidAreas=1		Solid area interiors are filled						Yes\n");
		fprintf(bas, "\t'UseSpatialInfo=1		Use only spatial information						No\n");
		fprintf(bas, "\t'APPLowerLeftX=N.N		Set application page rectangle lower left X value	N/A\n");
		fprintf(bas, "\t'APPLowerLeftY=N.N		Set application page rectangle lower left Y value	N/A\n");	
		fprintf(bas, "\t'APPUpperRightX=N.N		Set application page rectangle upper right X value	N/A\n");
		fprintf(bas, "\t'APPUpperRightY=N.N		Set application page rectangle upper right Y value	N/A\n");
		fprintf(bas, "\t'DXFLowerLeftX=N.N		Set DXF scaling rectangle lower left X value		N/A\n");
		fprintf(bas, "\t'DXFLowerLeftY=N.N		Set DXF scaling rectangle lower left Y value		N/A\n");
		fprintf(bas, "\t'DXFUpperRightX=N.N		Set DXF scaling rectangle upper right X value		N/A\n");
		fprintf(bas, "\t'DXFUpperRightY=N.N		Set DXF scaling rectangle upper right Y value		N/A\n");
		fprintf(bas, "\tDim filename_dxf As String\n");
		fprintf(bas, "\tfilename_dxf = directory + \"\\dxf\\\" + profilename + \".dxf\"\n");
		fprintf(bas, "\tPlot.Export(FileName:=filename_dxf, _\n");
		fprintf(bas, "\tOptions:= \"FormatASCII=0, AllColorsSame=1, AllStylesSame=1, AllWidthsSame=1, AllTextToAreas=1, FillSolidAreas=1\")\n");
		fprintf(bas, "End Sub\n");
	}
}
void PrintProfileScript(FILE * bas, const char * outdir, char * _prof, vector<string> & names, char * prof_name_in_fun, size_t prof_name_len, bool useXLimits, double xMin, double xMax )
{

	sprintf_s(prof_name_in_fun, prof_name_len, "%s\0", _prof);
	ReplaceSymbols(prof_name_in_fun, '-', '_');
	ReplaceSymbols(prof_name_in_fun, '+', '_');
	ReplaceSymbols(prof_name_in_fun, '*', '_');
	ReplaceSymbols(prof_name_in_fun, '/', '_');
	ReplaceSymbols(prof_name_in_fun, '\\', '_');
	ReplaceSymbols(prof_name_in_fun, '\'', '_');



	//sprintf(script_fn, "%s\\%s.bas\0", script_dir, _prof);
	//FILE * bas = fopen(script_fn, "wt");
	if (bas)
	{
		fprintf(bas, "Sub Do_%s (filename_lvl As String)\n", prof_name_in_fun);

		fprintf(bas, "\tDim directory As String\n");
		fprintf(bas, "\tDim profilename As String\n");
		fprintf(bas, "\tDim filenames_grd () As String\n");

		fprintf(bas, "\tDim useXLimits As Boolean\n");
		fprintf(bas, "\tDim xMin As Double\n");
		fprintf(bas, "\tDim xMax As Double\n");

		if (useXLimits)
		{
			fprintf(bas, "\tuseXLimits = True\n");
			fprintf(bas, "\txMin = %f\n", xMin);
			fprintf(bas, "\txMax = %f\n", xMax);
		}
		else
		{
			fprintf(bas, "\tuseXLimits = False\n");
		}

		fprintf(bas, "\tdirectory = \"%s\"\n", outdir);
		fprintf(bas, "\tprofilename = \"%s\"\n", _prof);

		fprintf(bas, "\tReDim Preserve filenames_grd (%d)\n", int(names.size())-1);
		for (size_t i = 0; i < names.size(); i++)
			fprintf(bas, "\tfilenames_grd (%d) = \"%s\"\n", int(i), names[i].c_str());

		fprintf(bas, "\tDoProfile directory, profilename, filename_lvl, filenames_grd, useXLimits, xMin, xMax\n");

		fprintf(bas, "End Sub\n");

	}
}
void PrintMainProfileScript(FILE * bas, char * prof_name_in_fun)
{
	if (bas)	
	{
		fprintf(bas, "Sub Main\n");
		fprintf(bas, "\tDim filename_lvl As String\n");
		fprintf(bas, "\tfilename_lvl = GetFilePath(,\"LVL\")\n");
		fprintf(bas, "\tDo_%s (filename_lvl)\n", prof_name_in_fun);
		fprintf(bas, "End Sub\n");
	}
}
void PrintMainProfilesScript(FILE * bas, vector<string> & prof_names_in_fun)
{
	if (bas)	
	{
		fprintf(bas, "Sub Main\n");
		fprintf(bas, "\tDim filename_lvl As String\n");
		fprintf(bas, "\tfilename_lvl = GetFilePath(,\"LVL\")\n");
		for (size_t i = 0; i < prof_names_in_fun.size(); i++)
			fprintf(bas, "\tDo_%s (filename_lvl)\n", prof_names_in_fun[i].c_str());
		fprintf(bas, "End Sub\n");
	}
}
void BlnProfile3D::SavingOfCubeProjectionGrid(const char * outdir, int index_cub, int make_grids_vnahljost, bool convert_to_acad_yscale, bool non_stretched_xscale)
{
	const size_t slen = 4096;
	char out_dir[slen];
	sprintf_s(out_dir, slen, "%s\\scripts\0", outdir);

	char script_dir[slen];
	char script_fn[slen];
	char srf_dir[slen];
	char dxf_dir[slen];

	sprintf_s(script_dir, slen, "%s\\scripts\0", outdir);
	if (CheckMyLicense()) CreateDirectory(script_dir,NULL);

	sprintf_s(srf_dir, slen, "%s\\srf\0", outdir);
	if (CheckMyLicense()) CreateDirectory(srf_dir,NULL);

	sprintf_s(dxf_dir, slen, "%s\\dxf\0", outdir);
	if (CheckMyLicense()) CreateDirectory(dxf_dir,NULL);


	char profname[slen];
	char * _prof = SelectNameFromPath(this->GetName().c_str(), profname, slen);
	
	sprintf(script_fn, "%s\\%s.bas\0", script_dir, _prof);

	FILE * bas = fopen(script_fn, "wt");				
	PrintDoProfileScript(bas);
	char prof_name_in_fun[slen];
	this->SavingOfCubeProjectionGrid(bas, outdir, index_cub, make_grids_vnahljost, convert_to_acad_yscale, non_stretched_xscale, prof_name_in_fun, slen);
	PrintMainProfileScript(bas, prof_name_in_fun);
	if (bas) fclose(bas);
}

void BlnProfile3D::DrawGDIplus(Graphics ** select_buffer, Graphics& graphics, map_view * v, Cube4D * cube)
{
	int make_grids_vnahljost = 0;
	/*if (cube->draw_as_one_isosurface)
		DrawGDIplusOfOneIsoSurface(v, cube);
	if (cube->draw_as_many_isosurfaces)
		DrawGDIplusOfManyIsoSurfaces(v, cube);
	if (cube->draw_as_scatter_plot)
		DrawGDIplusAsScatterPlot(v, cube);*/
	char str[256];
	wchar_t wstr[256];

	fGL x1; fGL y1;
//	fGL x2; fGL y2;

	//double dist_to_plane;
	CPoint2 profile;


	v->PreConvertingFromWorldToScreen();


	size_t len = m_vProfileMapAttaches.size();
	//printf("Attach Len = %d\n", len);
	vector<ProfileAttachPoint> * ppt2 = ptpa; 

	//m_grid.gridSection.z = NULL;

	for(size_t i = 0; i < len-1; i++)
	{
		//printf("attach N(%d) xProfile = %lf xMap = %lf yMap = %lf\n", i, pt2[i].xProfile, pt2[i].xMap, pt2[i].yMap);
		
		double plane[4];
		CPoint2 p1, p2; //input

		p1.x = (*ppt2)[i].xMap;
		p1.y = (*ppt2)[i].yMap;

		p2.x = (*ppt2)[i+1].xMap;
		p2.y = (*ppt2)[i+1].yMap;

		if (0 == GetVerticalPlaneFromTwoPoints(p1,p2,plane[0],plane[1],plane[2],plane[3]))
		{
			int dir = cube->Produce3DSurferGrid7(plane, m_grid.gridSection);
			// определяем преимущественное направление вектора нормали к плоскости
			switch(dir)
			{
			case 1:
				{
					// доминирует направление вектора нормали вдоль оси X
					// this->Produce3DSurferGrid7_YZ(plane, grid);
					double xLL = m_grid.gridSection.xLL;
					double xSize = m_grid.gridSection.xSize;

					double mu = ((*ppt2)[i+1].xProfile - (*ppt2)[i].xProfile) / ((*ppt2)[i+1].yMap - (*ppt2)[i].yMap);

					m_grid.gridSection.xLL = (*ppt2)[i].xProfile + mu * (xLL - (*ppt2)[i].yMap);
					m_grid.gridSection.xSize = mu * xSize;				
				}
				break;
			case 2:
				{
					// доминирует направление вектора нормали вдоль оси Y
					// this->Produce3DSurferGrid7_XZ(plane, grid);
					double xLL = m_grid.gridSection.xLL;
					double xSize = m_grid.gridSection.xSize;

					double mu = ((*ppt2)[i+1].xProfile - (*ppt2)[i].xProfile) / ((*ppt2)[i+1].xMap - (*ppt2)[i].xMap);

					m_grid.gridSection.xLL = (*ppt2)[i].xProfile + mu * (xLL - (*ppt2)[i].xMap);
					m_grid.gridSection.xSize = mu * xSize;
				}
				break;
			}
			// теперь надо отрезать левый и правый край грида, 
			// если они вылазят за точку излома

			long c0, c2;

			switch (make_grids_vnahljost)
			{
			case 0:
				{
					c0 = long(ceil(((*ppt2)[i].xProfile - m_grid.gridSection.xLL) / m_grid.gridSection.xSize));
					c2 = long(ceil((m_grid.gridSection.xLL + (m_grid.gridSection.nCol - 1) * m_grid.gridSection.xSize - (*ppt2)[i+1].xProfile) / m_grid.gridSection.xSize));
				}
				break;
			case 1:
				{
					c0 = long(ceil(((*ppt2)[i].xProfile - m_grid.gridSection.xLL) / m_grid.gridSection.xSize));
					c2 = long(floor((m_grid.gridSection.xLL + (m_grid.gridSection.nCol - 1) * m_grid.gridSection.xSize - (*ppt2)[i+1].xProfile) / m_grid.gridSection.xSize));
				}
			case 2:
				{
					c0 = long(floor(((*ppt2)[i].xProfile - m_grid.gridSection.xLL) / m_grid.gridSection.xSize));
					c2 = long(floor((m_grid.gridSection.xLL + (m_grid.gridSection.nCol - 1) * m_grid.gridSection.xSize - (*ppt2)[i+1].xProfile) / m_grid.gridSection.xSize));
				}
			}
			
			
			if (i == 0) c0 = 0;
			if (i + 1 == len - 1) c2 = 0;

			for (long rr = 0; rr < m_grid.gridSection.nRow; rr++)
			{
				for (long cc = c0; cc < m_grid.gridSection.nCol - c2; cc++)
				{
					//grid2.gridSection.z[rr][cc-c0] = m_grid.gridSection.z[rr][cc];
					
					//grid2.gridSection.z[rr][cc-c0] = m_grid.gridSection.yLL + rr * m_grid.gridSection.ySize;
					//grid2.gridSection.z[rr][cc-c0] = grid2.gridSection.xLL + (cc-c0) * grid2.gridSection.xSize;
					
					if (m_grid.gridSection.z[rr][cc] != BLANK_VALUE)
					{

						profile.x = m_grid.gridSection.xLL + cc * m_grid.gridSection.xSize;
						profile.y = m_grid.gridSection.yLL + rr * m_grid.gridSection.ySize;

						COLORREF color = RGB(0, 255, 0);
						double r = 1;
						Color gdi_color(255, GetRValue(color),GetGValue(color),GetBValue(color));
						Pen      pen(gdi_color);
						//Convert3D_To_2D
						//	on->Projection(CPoint3(x,y,z), profile, dist_to_plane);
						v->ConvertingFromWorldToScreen(profile.x, profile.y, x1, y1);
						//if (to_fill_circles&& !(m_vdPoints[0].flag & CPOINT3_FLAG_HIDE)) 
							FillCircle(&graphics, x1, y1, r, gdi_color);

						SolidBrush  brush(Color(255, 0, 0, 255));
						FontFamily  fontFamily(L"Times New Roman");
						Font        font(&fontFamily, 9, FontStyleRegular, UnitPixel);
						
						sprintf(str, "%0.2f\0", m_grid.gridSection.z[rr][cc]);	
						sprintf(str, "%f\0", m_grid.gridSection.z[rr][cc]);	
						while (str[strlen(str)-1] == '0') str[strlen(str)-1] = '\0';
						if (str[strlen(str)-1] == '.') str[strlen(str)-1] = '\0';
						MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, str, -1, wstr, 2*strlen(str)+2 );
						PointF      pointF(x1 /*- 0.5*font.GetHeight(&graphics) * strlen(str)*/, y1 - font.GetHeight(&graphics)/2);                                    
						graphics.DrawString(wstr, -1, &font, pointF, &brush);
					}
				}
			}
		}
	}
}

void BlnProfile3D::SavingOfCubeProjectionGrid(FILE * bas, const char * outdir, int index_cub, int make_grids_vnahljost, bool convert_to_acad_yscale, bool non_stretched_xscale, char * prof_name_in_fun, size_t prof_name_len)
{
	if (index_cub < 0) return;
	if (!this->m_pSurfDoc) return;

	Cube4D * cube = NULL;
	int index_c = -1;
	if (this->m_pSurfDoc->m_cubes.SetCurrentMsgOnFirst())
	{
		do
		{
			index_c++;
			if (index_c == index_cub)
			{
				cube = &this->m_pSurfDoc->m_cubes.GetCurrentMsg();
				break;
			}
		}
		while (this->m_pSurfDoc->m_cubes.IncrementCurrentMsg());
	}

	if (!cube) 
	{
		printf("!cube\n");
		return;
	}

	//vector<CPoint3> dat;

	char profname[4096];
	char * _prof = SelectNameFromPath(this->GetName().c_str(), profname, 4096);
	char prof_dir[4096];
	sprintf(prof_dir, "%s\\%s\0", outdir, _prof);
	if (CheckMyLicense())
		CreateDirectory(prof_dir,NULL);

	vector<string> names;

	Grid grid;// грид для построения и сохранения разреза куба
	grid.gridSection.z = NULL;

	size_t len = m_vProfileMapAttaches.size();
	//printf("Attach Len = %d\n", len);
	vector<ProfileAttachPoint> * ppt2; 
	if (non_stretched_xscale)
	{
		CalculateProfileMapAttachesNonStretched();
		ppt2 = &m_vProfileMapAttachesNonStretched;
	}
	else
	{
		ppt2 = &m_vProfileMapAttaches;
	}

	for(size_t i = 0; i < len-1; i++)
	{
//printf("attach N(%d) xProfile = %lf xMap = %lf yMap = %lf\n", i, pt2[i].xProfile, pt2[i].xMap, pt2[i].yMap);
		
		double plane[4];
		CPoint2 p1, p2; //input

		p1.x = (*ppt2)[i].xMap;
		p1.y = (*ppt2)[i].yMap;

		p2.x = (*ppt2)[i+1].xMap;
		p2.y = (*ppt2)[i+1].yMap;

		if (0 == GetVerticalPlaneFromTwoPoints(p1,p2,plane[0],plane[1],plane[2],plane[3]))
		{
			int dir = cube->Produce3DSurferGrid7(plane, grid.gridSection);
			// определяем преимущественное направление вектора нормали к плоскости

			bool to_flip = false;
			switch(dir)
			{
			case 1:
				{
					if (((*ppt2)[i+1].yMap     - (*ppt2)[i].yMap) < 0)
					{
						to_flip = true;
					}
				}
				break;
			case 2:
				{
					if (((*ppt2)[i+1].xMap     - (*ppt2)[i].xMap) < 0)
					{
						to_flip = true;
					}
				}
				break;
			}

			if (to_flip)
			{
				double val;
				for (long rr = 0; rr < grid.gridSection.nRow; rr++)
				{
					for (long cc = 0; cc < grid.gridSection.nCol/2; cc++)
					{
						val = grid.gridSection.z[rr][cc];
						grid.gridSection.z[rr][cc] = grid.gridSection.z[rr][grid.gridSection.nCol - cc - 1];
						grid.gridSection.z[rr][grid.gridSection.nCol - cc - 1] = val;
					}
				}
				grid.gridSection.xLL += (grid.gridSection.nCol - 1) * grid.gridSection.xSize;
				grid.gridSection.xSize *= -1;
			}


			switch(dir)
			{
			case 1:
				{
					// доминирует направление вектора нормали вдоль оси X
					// this->Produce3DSurferGrid7_YZ(plane, grid);
					double xLL = grid.gridSection.xLL;
					double xSize = grid.gridSection.xSize;
					double mu = ((*ppt2)[i+1].xProfile - (*ppt2)[i].xProfile) / 
						        ((*ppt2)[i+1].yMap     - (*ppt2)[i].yMap);

					grid.gridSection.xLL = (*ppt2)[i].xProfile + mu * (xLL - (*ppt2)[i].yMap);
					grid.gridSection.xSize = mu * xSize;				
				}
				break;
			case 2:
				{
					// доминирует направление вектора нормали вдоль оси Y
					// this->Produce3DSurferGrid7_XZ(plane, grid);
					double xLL = grid.gridSection.xLL;
					double xSize = grid.gridSection.xSize;

					double mu = ((*ppt2)[i+1].xProfile - (*ppt2)[i].xProfile) 
						      / ((*ppt2)[i+1].xMap     - (*ppt2)[i].xMap);

					grid.gridSection.xLL = (*ppt2)[i].xProfile + mu * (xLL - (*ppt2)[i].xMap);
					grid.gridSection.xSize = mu * xSize;
				}
				break;
			}
			// теперь надо отрезать левый и правый край грида, 
			// если они вылазят за точку излома

			long c0, c2;

			switch (make_grids_vnahljost)
			{
			case 0:
				{
					c0 = long(ceil(((*ppt2)[i].xProfile - grid.gridSection.xLL) / grid.gridSection.xSize));
					c2 = long(ceil((grid.gridSection.xLL + (grid.gridSection.nCol - 1) * grid.gridSection.xSize - (*ppt2)[i+1].xProfile) / grid.gridSection.xSize));
				}
				break;
			case 1:
				{
					c0 = long(ceil(((*ppt2)[i].xProfile - grid.gridSection.xLL) / grid.gridSection.xSize));
					c2 = long(floor((grid.gridSection.xLL + (grid.gridSection.nCol - 1) * grid.gridSection.xSize - (*ppt2)[i+1].xProfile) / grid.gridSection.xSize));
				}
				break;
			case 2:
				{
					c0 = long(floor(((*ppt2)[i].xProfile - grid.gridSection.xLL) / grid.gridSection.xSize));
					c2 = long(floor((grid.gridSection.xLL + (grid.gridSection.nCol - 1) * grid.gridSection.xSize - (*ppt2)[i+1].xProfile) / grid.gridSection.xSize));
				}
				break;
			}
			
			
			if (i == 0) c0 = 0;
			if (i + 1 == len - 1) c2 = 0;
			
			Grid grid2;
			grid2.faultSection.nTraces = 0; 
			grid2.faultSection.nVertices = 0; 
			grid2.faultSection.traces = NULL; 
			grid2.faultSection.vertexes = NULL; 

			grid2.gridSection.BlankValue = BLANK_VALUE;
			grid2.gridSection.Rotation = 0.0;

			grid2.gridSection.nRow = grid.gridSection.nRow;
			grid2.gridSection.nCol = grid.gridSection.nCol - c0 - c2;
			if (grid2.gridSection.nCol <= 0)
				continue;

			grid2.gridSection.z = AllocDoubleMat(grid2.gridSection.nRow, grid2.gridSection.nCol);

			grid2.gridSection.xLL = grid.gridSection.xLL + c0 * grid.gridSection.xSize;
			
			if (convert_to_acad_yscale)
				grid2.gridSection.yLL = this->m_y1a + this->m_acad_scale_y * (grid.gridSection.yLL - this->m_z1w);
			else                
				grid2.gridSection.yLL = grid.gridSection.yLL;

			grid2.gridSection.xSize = grid.gridSection.xSize;
						
			if (convert_to_acad_yscale)
				grid2.gridSection.ySize = this->m_acad_scale_y * grid.gridSection.ySize;
			else
				grid2.gridSection.ySize = grid.gridSection.ySize;

			grid2.gridSection.zMin = DBL_MAX;
			grid2.gridSection.zMax = -DBL_MAX;
			
			for (long rr = 0; rr < grid.gridSection.nRow; rr++)
			{
				for (long cc = c0; cc < grid.gridSection.nCol - c2; cc++)
				{
					grid2.gridSection.z[rr][cc-c0] = grid.gridSection.z[rr][cc];
					
					//grid2.gridSection.z[rr][cc-c0] = grid.gridSection.yLL + rr * grid.gridSection.ySize;
					//grid2.gridSection.z[rr][cc-c0] = grid2.gridSection.xLL + (cc-c0) * grid2.gridSection.xSize;
					
					if (grid.gridSection.z[rr][cc] != BLANK_VALUE)
					{
						if (grid2.gridSection.zMin > grid2.gridSection.z[rr][cc-c0])
							grid2.gridSection.zMin = grid2.gridSection.z[rr][cc-c0];

						if (grid2.gridSection.zMax < grid2.gridSection.z[rr][cc-c0])
							grid2.gridSection.zMax = grid2.gridSection.z[rr][cc-c0];

//						dat.push_back(CPoint3(grid.gridSection.xLL + cc * grid.gridSection.xSize, grid.gridSection.yLL + rr * grid.gridSection.ySize, grid.gridSection.z[rr][cc]));
					}
				}
			}




			if (grid2.gridSection.zMin != DBL_MAX && grid2.gridSection.zMax != -DBL_MAX)
			{
				char cubename[4096];
				char * pcub = SelectNameFromPath(cube->GetName().c_str(), cubename, 4096);

				char filename[4096];
				if (convert_to_acad_yscale)
					sprintf(filename, "%s\\cub_%s_on_ay_pr_%s_proj_%d.grd", prof_dir, pcub, _prof, i);
				else
					sprintf(filename, "%s\\cub_%s_on_pr_%s_proj_%d.grd", prof_dir, pcub, _prof, i);



				//if (CheckMyLicense())
					SaveAsSurfer7Grid(filename, &grid2);


				names.push_back(filename);
			}

			FreeDoubleMat(grid2.gridSection.z);
		}
	}

	bool useXLimits = this->m_xLimits_CubeProjection_loaded;
	double xMin, xMax;
	if (non_stretched_xscale)
	{
		xMin = m_xMin_CubeProjection_NonStretched;
		xMax = m_xMax_CubeProjection_NonStretched;
	}
	else
	{
		xMin = m_xMin_CubeProjection;
		xMax = m_xMax_CubeProjection;
	}

	PrintProfileScript(bas, outdir, _prof, names, prof_name_in_fun, prof_name_len, useXLimits, xMin, xMax);
}


BOOL CALLBACK BlnProfile3D::DlgProcSavingOfCubeProjectionGrid( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static BlnProfile3D * me;
	static int index_cub;

	static int make_grids_vnahljost;
	static bool convert_to_acad_yscale;
	static bool non_stretched_xscale;
				
	static char dir[4096];

	switch( uMsg )
	{
    case WM_INITDIALOG :
		{
			GetCurrentDirectory(4098, dir);
			SetDlgItemText(hDlg, IDC_EDIT_DIRECTORY, dir);

			index_cub = -1;

			make_grids_vnahljost = 1;
			convert_to_acad_yscale = false;
			non_stretched_xscale = true;

			CheckRadioButton( hDlg,
				IDC_RADIO_NAHLJOST_0,
				IDC_RADIO_NAHLJOST_2,
				IDC_RADIO_NAHLJOST_1);

			CheckDlgButton(hDlg, IDC_CHECK_CONVERT_TO_ACAD_YSCALE,	convert_to_acad_yscale);
			CheckDlgButton(hDlg, IDC_CHECK_NON_STRETCHED_X_SCALE,	non_stretched_xscale);

			me = (BlnProfile3D *)lParam;

			ShowWindow(GetDlgItem(hDlg, IDC_CHECK_CONVERT_TO_ACAD_YSCALE), me->GetAcadYscaleLoaded());
			ShowWindow(GetDlgItem(hDlg, IDC_STATIC_X_MIN_CUBE_PROJECTION), me->GetXLimitsCubeProjectionLoaded());
			ShowWindow(GetDlgItem(hDlg, IDC_STATIC_X_MAX_CUBE_PROJECTION), me->GetXLimitsCubeProjectionLoaded());

			if (me->GetXLimitsCubeProjectionLoaded())
			{
				char str[64];
				sprintf(str, "%f\0", me->m_xMin_CubeProjection);
				SetDlgItemText(hDlg,IDC_STATIC_X_MIN_CUBE_PROJECTION,str);

				sprintf(str, "%f\0", me->m_xMax_CubeProjection);
				SetDlgItemText(hDlg,IDC_STATIC_X_MAX_CUBE_PROJECTION,str);
			}

			SendMessage(hDlg,WM_COMMAND,IDC_INIT_INITIAL_PARAMETERS,0);
		
		
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE, CB_RESETCONTENT,0,0);
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"Select cube");
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			if (me->m_pSurfDoc->m_cubes.SetCurrentMsgOnFirst())
			{
				do
				{
					SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE, CB_ADDSTRING, 0,
						(LPARAM)(LPCTSTR)me->m_pSurfDoc->m_cubes.GetCurrentMsg().GetName().c_str());
				}
				while (me->m_pSurfDoc->m_cubes.IncrementCurrentMsg());
			}
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE, CB_SETCURSEL,
				index_cub+1, (LPARAM)0 );
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		}
		break;
	case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{
		case IDC_BUTTON_LOAD_ACAD_Y_SCALE:
			{
				char lpstrFile[4096];
				lpstrFile[0] = '\0';
				if (OpenFileDlg(hDlg, "Y Scale (*.bln)\0*.bln\0All files \0*.*\0", lpstrFile) == S_OK)
				{	
					vdouble xAcadYscale,yAcadYscale;
					int _inside;
					if (ReadBlnFile( lpstrFile, xAcadYscale, yAcadYscale, _inside ) == 0)
					{
						char str[255];
						sprintf(str, "%d yscale points\n",  xAcadYscale.Length(), yAcadYscale.Length());
						//MessageBox(0, str, "", 0);
						//SetDlgItemText(hDlg, IDC_STATIC_ACAD_YSCALE, str);
						printf(str);

						if (xAcadYscale.Length() == 2 && yAcadYscale.Length() == 2)
						{
							double z1w = xAcadYscale(0), y1a = yAcadYscale(0);
							double z2w = xAcadYscale(1), y2a = yAcadYscale(1);
							me->SetAcadYscale(z1w, y1a, z2w, y2a);
							ShowWindow(GetDlgItem(hDlg, IDC_CHECK_CONVERT_TO_ACAD_YSCALE), me->GetAcadYscaleLoaded());
						}
					}
				}
			}
			break;
		case IDC_BUTTON_LOAD_X_LIMITS:
			{
				char lpstrFile[4096];
				lpstrFile[0] = '\0';
				if (OpenFileDlg(hDlg, "X Limits (*.dat)\0*.dat\0All files \0*.*\0", lpstrFile) == S_OK)
				{	
					vdouble minXLimit, maxXLimit;
					if (ReadDatFile( lpstrFile, minXLimit, maxXLimit) == 0)
					{
						char str[255];
						sprintf(str, "%d XLimit points\n",  minXLimit.Length(), maxXLimit.Length());
						//MessageBox(0, str, "", 0);
						//SetDlgItemText(hDlg, IDC_STATIC_ACAD_YSCALE, str);
						printf(str);

						if (minXLimit.Length() >= 1 && maxXLimit.Length() >= 1)
						{
							double xMin = minXLimit(0), xMax = maxXLimit(0);
							me->SetXLimitsCubeProjection(xMin, xMax);
							ShowWindow(GetDlgItem(hDlg, IDC_STATIC_X_MIN_CUBE_PROJECTION), me->GetXLimitsCubeProjectionLoaded());
							ShowWindow(GetDlgItem(hDlg, IDC_STATIC_X_MAX_CUBE_PROJECTION), me->GetXLimitsCubeProjectionLoaded());
							if (me->GetXLimitsCubeProjectionLoaded())
							{
								sprintf(str, "%f\0", me->m_xMin_CubeProjection);
								SetDlgItemText(hDlg,IDC_STATIC_X_MIN_CUBE_PROJECTION,str);

								sprintf(str, "%f\0", me->m_xMax_CubeProjection);
								SetDlgItemText(hDlg,IDC_STATIC_X_MAX_CUBE_PROJECTION,str);
							}						
						}
					}
				}
			}
			break;
		case IDC_RADIO_NAHLJOST_0:
			{
				make_grids_vnahljost = 0;
			}
			break;
		case IDC_RADIO_NAHLJOST_1:
			{
				make_grids_vnahljost = 1;
			}
			break;
		case IDC_RADIO_NAHLJOST_2:
			{
				make_grids_vnahljost = 2;
			}
			break;
		case IDC_CHECK_CONVERT_TO_ACAD_YSCALE:
			{
				convert_to_acad_yscale = IsDlgButtonChecked( hDlg, IDC_CHECK_CONVERT_TO_ACAD_YSCALE) == BST_CHECKED;
			}
			break;
		case IDC_CHECK_NON_STRETCHED_X_SCALE:
			{
				non_stretched_xscale = IsDlgButtonChecked( hDlg, IDC_CHECK_NON_STRETCHED_X_SCALE) == BST_CHECKED;
			}
			break;
		case IDC_INIT_INITIAL_PARAMETERS:
			{
				/*char str[1023];
				sprintf(str,"%d",Karotazh::slices);
				SetDlgItemText(hDlg, IDC_EDIT_SPHERE_SLICES, str);

				sprintf(str,"%d",Karotazh::stacks);
				SetDlgItemText(hDlg, IDC_EDIT_SPHERE_STACKS, str);	

				sprintf(str,"%d",Karotazh::s_alpha);
				SetDlgItemText(hDlg, IDC_EDIT_KAROTAZH_ALPHA, str);

				sprintf(str,"%lf",Karotazh::s_scale);
				SetDlgItemText(hDlg, IDC_STATIC_SURF_SPHERE_RADIUS_VALUE, str);


				CheckDlgButton( hDlg, IDC_CHECK_KAROTAZH_SCALE_LOGARITHMIC,
					Karotazh::s_logarithmic_scale ? BST_CHECKED : BST_UNCHECKED );

				CheckDlgButton( hDlg, IDC_CHECK_KAROTAZH_SCALE_FROM_ZERO,
					Karotazh::s_scale_from_zero? BST_CHECKED : BST_UNCHECKED );

				CheckDlgButton( hDlg, IDC_CHECK_KAROTAZH_ON_OFF,
					Karotazh::s_checked? BST_CHECKED : BST_UNCHECKED );*/
			}
			break;

		case IDC_COMBO_SELECT_CUBE:
			{
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				index_cub = -1 + (int)SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE, CB_GETCURSEL,
							0,(LPARAM)0 );
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@							
			}
			break;
		case IDC_BUTTON_BROSE_DIRECTORY:
			{
				GetDlgItemText(hDlg, IDC_EDIT_DIRECTORY, dir, 4097);
				if (BroseDirDlg(hDlg, dir))
				{
					SetDlgItemText(hDlg, IDC_EDIT_DIRECTORY, dir);
				}
			}
			break;
		case IDOK :
			{
				Cube4D * cube = NULL;
				int index_c = -1;
				if (me->m_pSurfDoc->m_cubes.SetCurrentMsgOnFirst())
				{
					do
					{
						index_c++;
						if (index_c == index_cub)
						{
							cube = &me->m_pSurfDoc->m_cubes.GetCurrentMsg();
							break;
						}
					}
					while (me->m_pSurfDoc->m_cubes.IncrementCurrentMsg());
				}
				
				if(cube)
				{
					char cubename[4096];
					char * pcub = SelectNameFromPath(cube->GetName().c_str(), cubename, 4096);

					GetDlgItemText(hDlg, IDC_EDIT_DIRECTORY, dir, 4097);

					char dir_out[4098];
					sprintf(dir_out, "%s\\%s\0", dir, pcub);
					CreateDirectory(dir_out, NULL);

					me->SavingOfCubeProjectionGrid(dir_out, index_cub, make_grids_vnahljost, convert_to_acad_yscale, non_stretched_xscale);

				}
			}
			break;
			
		case IDCANCEL :
			EndDialog( hDlg, IDCANCEL );
			break;
		}
		break;
		
		default :
			
			return( FALSE );
	}
	return( TRUE );
}

void BlnProfile3D::SavingOfCubeProjectionGrid()
{
	HANDLE hDialog = LoadResource( hInst,
					FindResource( hInst, MAKEINTRESOURCE(IDD_DIALOG_KAROTAZH_CUBE_PROJECTION_ON_PROFILE),
									RT_DIALOG ) );

	LPVOID lpDialog = LockResource( hDialog );

	HWND hDlg = CreateDialogIndirectParam( hInst, (DLGTEMPLATE *)lpDialog, this->m_pSurfDoc ? this->m_pSurfDoc->hSurfWnd : NULL,
						(DLGPROC)BlnProfile3D::DlgProcSavingOfCubeProjectionGrid,
						(LPARAM)this );
	ShowWindow(hDlg, SW_SHOW);
}
#if 0
void BlnProfile3D::PrintAttaches()
{
	printf("BlnProfile3D::PrintAttaches\n");

	size_t len = m_vProfileMapAttaches.size();
	printf("Attach Len = %d\n", len);
	vector<ProfileAttachPoint> & pt2 = m_vProfileMapAttaches;
	for(size_t i = 0; i < len; i++)
	{
		printf("attach N(%d) xProfile = %lf xMap = %lf yMap = %lf\n", i, pt2[i].xProfile, pt2[i].xMap, pt2[i].yMap);
	}

	printf("BlnProfile3D::Print Plane Attaches\n");

	if ( 
		this->m_plane.m_vvplaneBlnProfiles.SetCurrentMsgOnFirst() 
		&&
		this->m_plane.m_vdplaneBlnProfiles.SetCurrentMsgOnFirst()
		)
	{
		do
		{
			size_t len = this->m_plane.m_vvplaneBlnProfiles.GetCurrentMsgLen();
		
			printf("Plane Attach Len = %d\n", len);

			CPoint3 *ptv;
			CPoint3 *ptd;
			ptv = this->m_plane.m_vvplaneBlnProfiles.GetCurrentMsgPtr();
			ptd = this->m_plane.m_vdplaneBlnProfiles.GetCurrentMsgPtr();
			//=============================================
			for (size_t i = 0; i+1 /*+ 2*/ < len; i+=2)
			{	
				printf("i   = %d x = %f y = %f z = %f\n", i,  ptd[i  ].x, ptd[i].y, ptd[i].z);
				printf("i+1 = %d x = %f y = %f z = %f\n", i+1,ptd[i+1].x, ptd[i+1].y, ptd[i+1].z);
				//printf("i+2 = %d x = %f y = %f z = %f\n", i+2,ptd[i+2].x, ptd[i+2].y, ptd[i+2].z);
				//printf("i+3 = %d x = %f y = %f z = %f\n", i+3,ptd[i+3].x, ptd[i+3].y, ptd[i+3].z);
			}
		}
		while( 
			this->m_plane.m_vvplaneBlnProfiles.IncrementCurrentMsg()
			&&
			this->m_plane.m_vdplaneBlnProfiles.IncrementCurrentMsg()
			);
	}
	//return NULL;
}
bool BlnProfile3D::EditAttaches()
{

	size_t len = m_vProfileMapAttaches.size();
	printf("Attach Len = %d\n", len);
	vector<ProfileAttachPoint> & pt2 = m_vProfileMapAttaches;
	for(size_t i = 0; i < len; i++)
	{
	}
	this->CalculateProfileMapAttachesNonStretched();

	bool result = false;

	if ( 
		this->m_plane.m_vvplaneBlnProfiles.SetCurrentMsgOnFirst() 
		&&
		this->m_plane.m_vdplaneBlnProfiles.SetCurrentMsgOnFirst()
		)
	{
		do
		{
			size_t len = this->m_plane.m_vvplaneBlnProfiles.GetCurrentMsgLen();
		
			printf("Plane Attach Len = %d\n", len);

			CPoint3 *ptv;
			CPoint3 *ptd;
			ptv = this->m_plane.m_vvplaneBlnProfiles.GetCurrentMsgPtr();
			ptd = this->m_plane.m_vdplaneBlnProfiles.GetCurrentMsgPtr();
			//=============================================
			for (size_t i = 0; i+1 < len; i+=2)
			{	
				printf("i   = %d x = %f y = %f z = %f\n", i,  ptd[i  ].x, ptd[i].y, ptd[i].z);
				printf("i+1 = %d x = %f y = %f z = %f\n", i+1,ptd[i+1].x, ptd[i+1].y, ptd[i+1].z);

				cout << "Do you want to correct this? (y/n)" << endl << ends;
				char yn;
				cin >> yn;
				if (yn == 'y' || yn == 'Y')
				{
					cout << "What coordinate do you want to correct? (x/y/z)" << endl << ends;
					char xyz;
					cin >> xyz;
					if (xyz == 'x' || xyz == 'X')
					{
						cout << "Enter new X coordinate" << endl << ends;
						double x;
						cin >> x;
						ptd[i  ].x = x;
						ptd[i+1].x = x;
						result = true;
					}

					if (xyz == 'y' || xyz == 'Y')
					{
						cout << "Enter new Y coordinate" << endl << ends;
						double y;
						cin >> y;
						ptd[i  ].y = y;
						ptd[i+1].y = y;
						result = true;
					}

					if (xyz == 'z' || xyz == 'Z')
					{
						printf("i   = %d x = %f y = %f z = %f\n", i,  ptd[i  ].x, ptd[i].y, ptd[i].z);
						cout << "Do you want to correct this Y coordinate? (y/n)" << endl << ends;
						cin >> yn;
						if (yn == 'y' || yn == 'Y')
						{
							cout << "Enter new Z coordinate" << endl << ends;
							double z;
							cin >> z;
							ptd[i  ].z = z;
							result = true;
						}
						printf("i+1 = %d x = %f y = %f z = %f\n", i+1,ptd[i+1].x, ptd[i+1].y, ptd[i+1].z);
						cout << "Do you want to correct this Y coordinate? (y/n)" << endl << ends;
						cin >> yn;
						if (yn == 'y' || yn == 'Y')
						{
							cout << "Enter new Z coordinate" << endl << ends;
							double z;
							cin >> z;
							ptd[i+1].z = z;
							result = true;
						}					
					}
				}
			}
		}
		while( 
			this->m_plane.m_vvplaneBlnProfiles.IncrementCurrentMsg()
			&&
			this->m_plane.m_vdplaneBlnProfiles.IncrementCurrentMsg()
			);
	}
	if (result)
	{
		this->PrintAttaches();
		this->m_plane.Zooming();
		this->m_plane.ReDraw();
	}
	return result;
}

#endif
// DIME: needed include files.
#include <dime/Model.h>
#include <dime/sections/BlocksSection.h>
#include <dime/tables/LayerTable.h>
#include <dime/dxfwriter.h>

bool BlnProfile3D::SaveAsDxf(dimeModel * model,  dimeBlock * block, CrdTranslator * translator)
{
	if (!model) return false;
	bool status = false;	

	if(this->m_bln_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			print_line(&this->m_bln_lines.GetCurrentMsg(), model, block, translator); 
			status = true;
		}
		while(this->m_bln_lines.IncrementCurrentMsg());
	}
	return status;
}

bool BlnProfile3D::SaveAsBln(char * outfile, CrdTranslator * translator)
{
	bool status = false;
	FILE * stream = fopen(outfile, "wt");
	if(!stream)
	{
		return false;
	}
	if(this->m_bln_lines.SetCurrentMsgOnFirst())
	{
		do
		{			
			if(translator)
				status = this->m_bln_lines.GetCurrentMsg().SaveAsBln(stream, *translator); 
			else
				status = this->m_bln_lines.GetCurrentMsg().SaveAsBln(stream); 
		}
		while(this->m_bln_lines.IncrementCurrentMsg());
	}
	fclose(stream);
	return status;
}

bool BlnProfile3D::SaveAsManyBlnFiles(char * outfile, CrdTranslator * translator)
{
	bool status = false;
	TCHAR lpstrFile[1048];

	if(this->m_bln_lines.SetCurrentMsgOnFirst())
	{
		do
		{			
			sprintf(lpstrFile, "%s\\%s.bln", 
				directory, 
				this->m_bln_lines.GetCurrentMsg().GetName().c_str());
			FILE * stream = fopen(lpstrFile,"wt");
			if(translator)
				status = this->m_bln_lines.GetCurrentMsg().SaveAsBln(stream, *translator); 
			else
				status = this->m_bln_lines.GetCurrentMsg().SaveAsBln(stream); 
			fclose (stream);
		}
		while(this->m_bln_lines.IncrementCurrentMsg());
	}
	return status;
}

bool BlnProfile3D::SaveAs()
{
	bool status = false;
	TCHAR lpstrFile[1048]; lpstrFile[0] = '\0';
	sprintf(lpstrFile, "%s\0", this->GetName().c_str());
	
	TCHAR filter[] =     
		TEXT("AutoCAD DXF(*.dxf)\0*.dxf\0")
		TEXT("Golden Software Blanking(*.bln)\0*.bln\0")
		TEXT("Golden Software Blanking Many Files(*.bln)\0*.bln\0")
		TEXT("All Files (*.*)\0*.*\0");

	{
		DWORD nFilterIndex = 0;
		if (SaveProfDlg(0, lpstrFile, filter, nFilterIndex, BlnProfile3D::sprData) != S_OK)
			return status;

		CrdTranslator translator;

		if (!InitTranslator(translator, BlnProfile3D::sprData))
		{
			MessageBox(0, "Can not save this projection\nSelect another", "BlnProfile3D SaveAs", 0);
			return false;
		}

		switch (nFilterIndex)
		{
		case 1:
			status = this->Object::SaveAsDxf(lpstrFile, &translator);
			break;
		case 2:
			status = this->SaveAsBln(lpstrFile, &translator);
			break;
		case 3:
			status = this->SaveAsManyBlnFiles(lpstrFile, &translator);
			break;
		}
		return status;
	}
}

bool BlnProfile3D::BuildIntersection(BlnProfile3D * profile)
{
	printf("BlnProfile3D( %s )::BuildIntersection(BlnProfile3D * profile %s)\n", 
		this->GetName().c_str(),
		profile->GetName().c_str());

	//this->m_plane.m_intersections.clear();

	if (m_pSurfDoc && profile)
	{
		if ( 
			this->m_plane.m_vvplaneBlnProfiles.SetCurrentMsgOnFirst() 
			&&
			this->m_plane.m_vdplaneBlnProfiles.SetCurrentMsgOnFirst()
			)
		{
			do
			{
				size_t len = this->m_plane.m_vvplaneBlnProfiles.GetCurrentMsgLen();

				CPoint3 *ptv;
				CPoint3 *ptd;
				ptv = this->m_plane.m_vvplaneBlnProfiles.GetCurrentMsgPtr();
				ptd = this->m_plane.m_vdplaneBlnProfiles.GetCurrentMsgPtr();
				//=============================================
				for (size_t i = 0; i + 3 < len; i+=2)
				{	
					double A,B,C,D;
					CPoint2 p1,p2;
					p1.x = ptd[i].x;   p1.y = ptd[i].y;
					p2.x = ptd[i+2].x; p2.y = ptd[i+2].y;
					if (0 == GetVerticalPlaneFromTwoPoints(p1,p2,A,B,C,D))
					{
						double 
							min_x = min(ptd[i].x,ptd[i+2].x),
							max_x = max(ptd[i].x,ptd[i+2].x),

							min_y = min(ptd[i].y,ptd[i+2].y),
							max_y = max(ptd[i].y,ptd[i+2].y),

							min_z = min(ptd[i].z,ptd[i+1].z),
							max_z = max(ptd[i].z,ptd[i+1].z);

						if ( 
							profile->m_plane.m_vvplaneBlnProfiles.SetCurrentMsgOnFirst() 
							&&
							profile->m_plane.m_vdplaneBlnProfiles.SetCurrentMsgOnFirst()
							)
						{
							do
							{
								size_t plen = profile->m_plane.m_vvplaneBlnProfiles.GetCurrentMsgLen();

								CPoint3 *pptv;
								CPoint3 *pptd;
								pptv = profile->m_plane.m_vvplaneBlnProfiles.GetCurrentMsgPtr();
								pptd = profile->m_plane.m_vdplaneBlnProfiles.GetCurrentMsgPtr();
								//=============================================
								for (size_t pi = 0; pi + 3 < plen; pi+=2)
								{	
									double pA,pB,pC,pD;
									CPoint2 pp1,pp2;
									pp1.x = pptd[pi].x;   pp1.y = pptd[pi].y;
									pp2.x = pptd[pi+2].x; pp2.y = pptd[pi+2].y;
									if (0 == GetVerticalPlaneFromTwoPoints(pp1,pp2,pA,pB,pC,pD))
									{
										double 
											pmin_x = min(pptd[pi].x,pptd[pi+2].x),
											pmax_x = max(pptd[pi].x,pptd[pi+2].x),

											pmin_y = min(pptd[pi].y,pptd[pi+2].y),
											pmax_y = max(pptd[pi].y,pptd[pi+2].y),

											pmin_z = min(pptd[pi].z,pptd[pi+1].z),
											pmax_z = max(pptd[pi].z,pptd[pi+1].z);										
										
										// проводим вертикальную линию

										// ищем линию пересечения нашей плоскости 
										//  A*x + B*y + C*z + D = 0
										// с плоскостью 
										//  pA*x + pB*y + pC*z + pD = 0
										// решаем систему уравнений 
										// а теперь решаем систему уравнений с целью найти точку пересечения прямых на которых лежат эти два отрезка
										vdouble M;
										M.resize(2,2);
										vdouble b;
										b.resize(2);

										M(0,0) =  A;	M(0,1) =  B;
										M(1,0) = pA;	M(1,1) = pB;

										b[0] = - D;
										b[1] = -pD;

										vdouble xy;
										double det;

										M.sls_det(b,xy,det);
										// проверяем прямые на параллельность
										if (det != 0.0)
										{
											// координаты точки пересечения двух отрезков
											double x = xy[0];
											double y = xy[1];  

											// флаг того,что точка пересечения режет текущий отрезок
											bool thisCutting = 
												(x >= min_x && 
												x <= max_x && 

												y >= min_y && 
												y <= max_y)
												&&
												(x >= pmin_x && 
												x <= pmax_x && 

												y >= pmin_y && 
												y <= pmax_y);

											if (thisCutting)
											{
												// границы пересечения профилей по высоте

												double min__z = max(min_z, pmin_z);
												double max__z = min(max_z, pmax_z);

												// переводим в координаты вида

												double 
													xv = m_pSurfDoc->m_zoomX * (x - m_pSurfDoc->m_xd_zoom_center), 
													yv = m_pSurfDoc->m_zoomY * (y - m_pSurfDoc->m_yd_zoom_center), 
													min_zv = m_pSurfDoc->m_zoomZ * (min__z - m_pSurfDoc->m_zd_zoom_center),
													max_zv = m_pSurfDoc->m_zoomZ * (max__z - m_pSurfDoc->m_zd_zoom_center);
												
												// добавляем объект пересечения
												
												ProfileIntersection intersection;
												this->m_plane.m_intersections.AddMsg(&intersection);
												this->m_plane.m_intersections.GetLastMsg().x = x;
												this->m_plane.m_intersections.GetLastMsg().y = y;

												this->m_plane.m_intersections.GetLastMsg().xv = xv;
												this->m_plane.m_intersections.GetLastMsg().yv = yv;

												this->m_plane.m_intersections.GetLastMsg().min_z = min__z;
												this->m_plane.m_intersections.GetLastMsg().max_z = max__z;

												this->m_plane.m_intersections.GetLastMsg().min_zv = min_zv;
												this->m_plane.m_intersections.GetLastMsg().max_zv = max_zv;

												this->m_plane.m_intersections.GetLastMsg().name = 
													profile->GetName().c_str();

												// вычисляем пересечения с линиями профиля

												if(true)
												{
													if (profile->m_bln_lines.SetCurrentMsgOnFirst())
													{
														do
														{
															size_t line_len = profile->m_bln_lines.GetCurrentMsg().GetPointsNumber();
															CPoint3 pt, pt_pre;
															double r, r_pre;
															for (size_t j = 0; j < line_len; j++)
															{															
																pt = profile->m_bln_lines.GetCurrentMsg().GetDocumentPoint(j);
																r = A*pt.x + B*pt.y + C*pt.z + D;
																if ( j > 0)
																{
																	if (r*r_pre <=0)
																	{
																		// растояние между точками
																		/*double rij = sqrt( 
																			(pt.x-pt_pre.x)*(pt.x-pt_pre.x) + 
																			(pt.y-pt_pre.y)*(pt.y-pt_pre.y) + 
																			(pt.z-pt_pre.z)*(pt.z-pt_pre.z) 
																			);*/
																		// гипотенуза
																		double ci_j = /*rij **/ fabs(r) / (fabs(r) + fabs(r_pre));
																		//X = pt.x + (pt_pre.x-pt.x)*ci_j/*/rij*/;
																		//Y = pt.y + (pt_pre.y-pt.y)*ci_j/*/rij*/;
																		double Z = pt.z + (pt_pre.z-pt.z)*ci_j/*/rij*/;
																		double Zv = m_pSurfDoc->m_zoomZ * (Z - m_pSurfDoc->m_zd_zoom_center);

																		m_plane.m_intersections.GetLastMsg().z.push_back(Z);
																		m_plane.m_intersections.GetLastMsg().zv.push_back(Zv);
																		m_plane.m_intersections.GetLastMsg().names.push_back(profile->m_bln_lines.GetCurrentMsg().GetName());
																		m_plane.m_intersections.GetLastMsg().colors.push_back(profile->m_bln_lines.GetCurrentMsg().m_color);
																	}
																}
																pt_pre = pt;
																r_pre = r;

															}
														}
														while(profile->m_bln_lines.IncrementCurrentMsg());
													}												
												}
												//
											}
										}											
									}	
								}
							}
							while( 
								profile->m_plane.m_vvplaneBlnProfiles.IncrementCurrentMsg()
								&&
								profile->m_plane.m_vdplaneBlnProfiles.IncrementCurrentMsg()
								);
						}						
					}	
				}
			}
			while( 
				this->m_plane.m_vvplaneBlnProfiles.IncrementCurrentMsg()
				&&
				this->m_plane.m_vdplaneBlnProfiles.IncrementCurrentMsg()
				);
		}
	}
	return false;
}

int BlnProfile3D::ClearFromDB(bool msg)
{
	int ans = IDYES;
	if (this->m_pSurfDoc && this->m_pSurfDoc->GetLabDoc())
	{
		bool to_clear = true;
		if (msg)
		{
			ans = MessageBox(0, "Удалить профиль также и из базы?", "BlnProfile3D::ClearFromDB", MB_YESNOCANCEL);
			to_clear = IDYES == ans;
		}
		if (to_clear)
		{
			long id_obj = this->m_pSurfDoc->Get_ID_OBJ();
			this->m_pSurfDoc->GetLabDoc()->DeleteRozriz(id_obj, this->id_rozriz);
		}
	}
	return ans;
}


DWORD BlnProfile3D::Serialize(Archive& ar)
{
	if (ar.IsStoring())
	{
		ar << *this;
	}
	else
	{
		ar >> *this;
	}
	return 0;
}
Archive& operator <<(Archive& ar, BlnProfile3D& ob)
{
//	ar << *dynamic_cast<Object *>(&ob);
	DWORD version = ob.Object::Serialize(ar);
//printf("Archive& operator <<(Archive& ar, BlnProfile3D& ob) version = %d\n", version);
	switch (version)
	{
	case 4:
		{
			ar << ob.m_broken_plane;
		}
	case 3:
		{
			ob.Profile3D::Serialize(ar);

			ar << ob.m_plane;
			ar << ob.m_alpha_plane;
			// Objects' vectors
			ar << ob.m_bln_lines;			ar << ob.m_bln_lines_ObjectList;
			ar << ob.m_brkn_poligons;		ar << ob.m_brkn_poligons_ObjectList;

			ar << ob.m_vectorBlnProfiles;
			ar << ob.m_names;
		}
		break;	
	case 2:
		{
			ob.Profile3D::Serialize(ar);

			ar << ob.m_plane;
			ar << ob.m_alpha_plane;
			// Objects' vectors
			ar << ob.m_bln_lines;			ar << ob.m_bln_lines_ObjectList;
			ar << ob.m_brkn_poligons;		ar << ob.m_brkn_poligons_ObjectList;

			vect<CPoint2> vectBlnProfiles; vectBlnProfiles.OnCreate(0);
			BlnProfiles_vector2vect(ob.m_vectorBlnProfiles, vectBlnProfiles);
			ar << vectBlnProfiles;
			ar << ob.m_names;
		}
		break;	
	case 1:
		{
			ar << ob.m_plane;
			ar << ob.m_alpha_plane;
			// Objects' vectors
			ar << ob.m_bln_lines;			ar << ob.m_bln_lines_ObjectList;
			ar << ob.m_brkn_poligons;		ar << ob.m_brkn_poligons_ObjectList;


			vect<ProfileAttachPoint> vBlnProfileMapAttaches;
			vBlnProfileMapAttaches.OnCreate(0);
			ProfileMapAttaches_vector2vect(ob.m_vProfileMapAttaches, vBlnProfileMapAttaches);
			ar << vBlnProfileMapAttaches;

			vect<CPoint2> vectBlnProfiles; vectBlnProfiles.OnCreate(0);
			BlnProfiles_vector2vect(ob.m_vectorBlnProfiles, vectBlnProfiles);
			ar << vectBlnProfiles;
			ar << ob.m_names;
		}
		break;
	default:
		{
			throw VersionException(version, VersionException::cannot_store, ob.m_object_type);
		}
		break;
	}
	return ar;
}
Archive& operator >>(Archive& ar, BlnProfile3D& ob)
{
	//ar >> *dynamic_cast<Object *>(&ob);
	ob.Object::Serialize(ar);

	DWORD object_version = ob.m_object_version;
//printf("Archive& operator >>(Archive& ar, BlnProfile3D& ob) ob.m_object_version = %d\n", ob.m_object_version);
	switch (ob.m_object_version)
	{
	case 4:
		{
			ar >> ob.m_broken_plane;
		}
	case 3:
		{
			ob.m_object_version = 4;
			ob.Profile3D::Serialize(ar);

			ar >> ob.m_plane;
			ob.m_plane.SetParent(&ob);

			ar >> ob.m_alpha_plane;

			// Objects' vectors
			ar >> ob.m_bln_lines;			ar >> ob.m_bln_lines_ObjectList;
			ob.m_bln_lines_ObjectList.Init(ob.m_bln_lines, &ob);

			ar >> ob.m_brkn_poligons;		ar >> ob.m_brkn_poligons_ObjectList;
			ob.m_brkn_poligons_ObjectList.Init(ob.m_brkn_poligons, &ob);

			ar >> ob.m_vectorBlnProfiles;
			ar >> ob.m_names;
		}
		break;
	case 2:
		{
			ob.m_object_version = 4;

			ob.Profile3D::Serialize(ar);

			ar >> ob.m_plane;
			ob.m_plane.SetParent(&ob);

			ar >> ob.m_alpha_plane;

			// Objects' vectors
			ar >> ob.m_bln_lines;			ar >> ob.m_bln_lines_ObjectList;
			ob.m_bln_lines_ObjectList.Init(ob.m_bln_lines, &ob);

			ar >> ob.m_brkn_poligons;		ar >> ob.m_brkn_poligons_ObjectList;
			ob.m_brkn_poligons_ObjectList.Init(ob.m_brkn_poligons, &ob);

			vect<CPoint2> vectBlnProfiles; vectBlnProfiles.OnCreate(0);
			ar >> vectBlnProfiles;
			BlnProfiles_vect2vector(vectBlnProfiles, ob.m_vectorBlnProfiles);

			ar >> ob.m_names;
		}
		break;
	case 1:
		{
			ob.m_object_version = 4;


			ar >> ob.m_plane;
			ob.m_plane.SetParent(&ob);

			ar >> ob.m_alpha_plane;

			// Objects' vectors
			ar >> ob.m_bln_lines;			ar >> ob.m_bln_lines_ObjectList;
			ob.m_bln_lines_ObjectList.Init(ob.m_bln_lines, &ob);

			ar >> ob.m_brkn_poligons;		ar >> ob.m_brkn_poligons_ObjectList;
			ob.m_brkn_poligons_ObjectList.Init(ob.m_brkn_poligons, &ob);
	


			vect<ProfileAttachPoint> vBlnProfileMapAttaches;
			vBlnProfileMapAttaches.OnCreate(0);
			ar >> vBlnProfileMapAttaches;
			ProfileMapAttaches_vect2vector(vBlnProfileMapAttaches, ob.m_vProfileMapAttaches);
			ob.CalculateProfileMapAttachesNonStretched();


			vect<CPoint2> vectBlnProfiles; vectBlnProfiles.OnCreate(0);
			ar >> vectBlnProfiles;
			BlnProfiles_vect2vector(vectBlnProfiles, ob.m_vectorBlnProfiles);
			ar >> ob.m_names;
		}
		break;
	default:
		{
			throw VersionException(ob.m_object_version, VersionException::cannot_load, ob.m_object_type);
		}
		break;
	}

	if (object_version < 4)
	{
		vector<double> xMap, yMap;

		for (vector<ProfileAttachPoint>::iterator it = ob.m_vProfileMapAttaches.begin();
			it != ob.m_vProfileMapAttaches.end(); it++)
		{
			xMap.push_back((*it).xMap);
			yMap.push_back((*it).yMap);
		}
		ob.m_broken_plane.Init_broken_plane(NULL, xMap, yMap);
	}
//printf("Archive& operator >>(Archive& ar, BlnProfile3D& ob) ob.m_object_version = %d  end\n", ob.m_object_version);

	return ar;
}

