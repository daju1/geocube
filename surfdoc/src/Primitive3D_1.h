// Primitive3D.h: interface for the Primitive3D class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRIMITIVE3D_H__2B120F8F_F432_4517_8B3B_DC4629ABEFDC__INCLUDED_)
#define AFX_PRIMITIVE3D_H__2B120F8F_F432_4517_8B3B_DC4629ABEFDC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../../surfdefs.h"
#include "Object.h"

#include "points.h"
#include "../../tools/src/filedlg.h"
#include ".\archive.h"

extern int ChooseSurfColor(HWND hwndOwner, COLORREF& color);

extern char directory[];
class Profile3D;
template <class T> class Primitive3D : public Object
{
	friend class FastCollection;
	friend class Surface3D;
	friend class Cube4D;
	GLenum  m_FillMode;  // Режим заполнения полигонов
	size_t m_nPoints;
	virtual void Drawing() = 0;
public:
	DWORD m_primitive_version;
	int m_alpha;
	//T * m_vdPoints;
	//T * m_vvPoints;
	//	vector<T> m_vdPoints;
	//	vector<T> m_vvPoints;
	PRIMITIVE_POINTS_TYPE(T) m_vdPoints;
	PRIMITIVE_POINTS_TYPE(T) m_vvPoints;
	COLORREF m_color;
	void Init(Primitive3D& ob)
	{
		this->m_alpha		= ob.m_alpha;
		this->m_color		= ob.m_color;
		this->m_FillMode	= ob.m_FillMode;
		this->m_nPoints		= ob.m_nPoints;
		this->m_primitive_version = ob.m_primitive_version;

		PRIMITIVE_POINTS_ALLOC(this->m_vdPoints, this->m_nPoints, T);
		PRIMITIVE_POINTS_ALLOC(this->m_vvPoints, this->m_nPoints, T);

		PRIMITIVE_POINTS_PTR(T) ptv, ob_ptv;
		PRIMITIVE_POINTS_PTR(T) ptd, ob_ptd;

		ptv		= this->m_vvPoints PRIMITIVE_POINTS_PTR_BEGIN;
		ptd		= this->m_vdPoints PRIMITIVE_POINTS_PTR_BEGIN;

		ob_ptv	= ob.	m_vvPoints PRIMITIVE_POINTS_PTR_BEGIN;
		ob_ptd	= ob.	m_vdPoints PRIMITIVE_POINTS_PTR_BEGIN;

		for(size_t i = 0; i < this->m_nPoints; i++)
		{
			ptv[i] = ob_ptv[i];
			ptd[i] = ob_ptd[i];
		}
	}
public:
	Primitive3D(Primitive3D& ob)
	{
		dynamic_cast<Object*>(this)->Init(ob);
		this->Init(ob);
	}
	//====== Операция присвоения
	Primitive3D& operator=(Primitive3D& ob)
	{
		if (this == &ob)
			return *this;

		dynamic_cast<Object*>(this)->Init(ob);
		this->Init(ob);

		return *this;
	}
	Primitive3D()
	{
		// if we have the class derived from Primitive<CPoint3>
		this->m_bIsPrimitive3 = true;
		this->m_bIsPrimitive4 = false;
		// but if we will build class derived from Primitive<CPoint4>
		// than in that class on constructor do so:
		// this->m_bIsPrimitive = false;
		// this->m_bIsPrimitive4 = true;
		m_alpha = 255;
		m_FillMode = GL_FILL;
		m_nPoints	= 0;
		this->m_object_type = Object::object_type::primitive3d;
		this->m_primitive_version = 1;
	}
	GLenum  GetFillMode()
	{
		return m_FillMode;
	}
	void SetFillMode(GLenum FillMode)
	{
		m_FillMode = FillMode;
	}
	void AllocPoints(size_t nPoints)
	{
		PRIMITIVE_POINTS_ALLOC(m_vvPoints,nPoints,T);
		PRIMITIVE_POINTS_ALLOC(m_vdPoints,nPoints,T);

		m_nPoints = nPoints;
	}

	virtual void SetColor(COLORREF color)
	{
		m_color = color;
	}
	void SetAlpha(int alpha)
	{
		m_alpha = alpha;
	}
	virtual void Draw();/*
	{
		if (m_pSurfDoc)
		{
			m_nglListNumber = m_pSurfDoc->m_DrawListArray.glNewList();
			Drawing();
			glEndList();
		}
	}*/
	virtual void ReDraw(void);
	/*{
		if (m_pSurfDoc)
		{
			::glDeleteLists(m_nglListNumber,1);
			::glNewList(m_nglListNumber, GL_COMPILE);
			Drawing();
			glEndList();
		}
	}*/

	virtual void EnumObjects(WPARAM wParam, LPARAM lParam, void * p,
		bool (Object::* condition_fun)(),
		void (* callback_fun)(Object* , WPARAM, LPARAM, void * ) )
	{
//printf("Primitive3D::EnumObjects type = %s\n", Object::ObjectTypeToString(this->GetObjectType()));

		if ((this->*condition_fun)())
		{
//printf("Primitive3D::EnumObjects type = %s if ((this->*condition_fun)())\n", Object::ObjectTypeToString(this->GetObjectType()));
			(* callback_fun)(this, wParam, lParam, p);
		}
	}
	void SetLayer(const Layer* layer)
	{
		this->SetLayer_NonVirtual(layer);
	}
	void Primitive_Serialize(Archive& ar)
	{
		//printf("void Primitive_Serialize(Archive& ar)\n");
		if (ar.IsStoring())
		{
			DWORD version = ar.m_use_primitive_version ? ar.m_use_primitive_version : this->m_primitive_version;
			ar << version;
			switch (version)
			{
			case 1:
				{
		//printf("Archive& operator <<(Archive& ar, Primitive3D<T>& primitive) 1\n");
					ar << this->m_alpha;
					ar << this->m_color;
					ar << this->m_FillMode;

					ar << this->m_nPoints;
					ar << this->m_vdPoints;
				}
				break;
			default:
				{
					throw VersionException(version, VersionException::cannot_store, this->m_object_type);
				}
				break;
			}
		}
		else
		{
			ar >> this->m_primitive_version;
			//printf("this->primitive_version = %d\n", this->m_primitive_version);

			switch (this->m_primitive_version)
			{
			case 1:
				{
		//printf("Archive& operator >>(Archive& ar, Primitive3D<T>& primitive) 1\n");
					this->Free();
					ar >> this->m_alpha;
					ar >> this->m_color;
					ar >> this->m_FillMode;

					ar >> this->m_nPoints;
					//printf("this->m_nPoints = %d\n", this->m_nPoints);
					this->AllocPoints(this->m_nPoints);
					ar >> this->m_vdPoints;
				}
				break;
			default:
				{
					printf("Primitive_Serialize(Archive& ar) throw!!!\n");
					throw VersionException(this->m_primitive_version, VersionException::cannot_load, this->m_object_type);
				}
				break;
			}
		}
		//printf("void Primitive_Serialize(Archive& ar) end\n");
	}
	void PushBack(T pt)
	{
		m_vvPoints.push_back(pt);
		m_vdPoints.push_back(pt);
		m_nPoints++;
	}
	void Reverse()
	{
		// Reverse the elements in the vector 
		reverse (m_vvPoints.begin( ), m_vvPoints.end( ) );
		reverse (m_vdPoints.begin( ), m_vdPoints.end( ) );
	}




	void Insert(size_t i_where, T pt)
	{
		printf("Insert(size_t i_where = %u, T pt [%f %f %f])", i_where, pt.x, pt.y, pt.z);
		if (i_where > 0 && i_where <= this->m_nPoints)
		{
		
			printf("Insert(if (i_where %u > 0 && i_where <= this->m_nPoints %u))", i_where, this->m_nPoints);
			vector<T>::iterator iter_v = m_vvPoints.begin();
			vector<T>::iterator iter_d = m_vdPoints.begin();
			m_vvPoints.insert(iter_v+i_where, pt);
			m_vdPoints.insert(iter_d+i_where, pt);
			m_nPoints++;
		}
	}

	void ErasePoint(size_t i)
	{
		if (i < m_nPoints && i >= 0)
		{
			vector<T>::iterator iter_v;
			vector<T>::iterator iter_d;
			size_t j = 0;
			for(iter_v = m_vvPoints.begin(), iter_d = m_vdPoints.begin(); 
				iter_v != m_vvPoints.end() && iter_d != m_vdPoints.end(); 
				iter_v++, iter_d++,j++)
			{
				if (i == j)
				{
					m_nPoints--;
					m_vvPoints.erase(iter_v);
					m_vdPoints.erase(iter_d);
					break;
				}
			}
		}
	}
	virtual void FreeMiddlePoints()
	{
		vector<T>::iterator iter_v;
		vector<T>::iterator iter_d;
		size_t i = 0;
		for(iter_v = m_vvPoints.begin()+1, iter_d = m_vdPoints.begin()+1; 
			iter_v != m_vvPoints.end() && iter_d != m_vdPoints.end() && i+2 < this->m_nPoints; 
			iter_v++, iter_d++, i++)
		{
			m_vvPoints.erase(iter_v);
			m_vdPoints.erase(iter_d);
			this->m_nPoints--;
		}
	}
	virtual void Close()
	{
		vector<T>::iterator iter_v;
		vector<T>::iterator iter_d;
		
		iter_v = m_vvPoints.begin();
		iter_d = m_vdPoints.begin(); 

		if (iter_v != m_vvPoints.end() && iter_d != m_vdPoints.end() ) 
		{
			if ( (*iter_d) != m_vdPoints.back())
			{
				m_vvPoints.push_back(*iter_v);
				m_vdPoints.push_back(*iter_d);
				m_nPoints++;
			}
		}
	}
	void EraseAllUnvisible()
	{
		vector<T>::iterator iter_v = m_vvPoints.begin();
		vector<T>::iterator iter_d = m_vdPoints.begin();
		while (iter_v != m_vvPoints.end() && iter_d != m_vdPoints.end())
		{
			if (!(*iter_d).bVisible)
			{
				m_nPoints--;
				iter_v = m_vvPoints.erase(iter_v);
				iter_d = m_vdPoints.erase(iter_d);
			}
			else
			{
				iter_v++;
				iter_d++;
			}
		}
	}
	bool SaveAs()
	{
		bool status = false;
		TCHAR lpstrFile[256];
		TCHAR filter[] =    TEXT("Golden Software Blanking (*.bln)\0*.bln\0")
							TEXT("Golden Software Data (*.dat)\0*.dat\0")
							TEXT("All Files (*.*)\0*.*\0");

		sprintf(lpstrFile, "%s\\1", directory);
		sprintf(lpstrFile, "\0");
		DWORD nFilterIndex;
		if (SaveFileDlg(0, lpstrFile, filter, nFilterIndex) != S_OK)
			return status;
		FILE *stream;
		stream = fopen(lpstrFile,"wt");
		if (!stream)
		{
			return status;
		}
		switch (nFilterIndex)
		{
		case 1:
			status = SaveAsBln(stream);
			break;
		case 2:
			status = SaveAsDat(stream);
			break;
		}
		fclose (stream);
		return status;
	}
	bool SaveAsBln(FILE * stream)
	{
		if (stream)
		{
			size_t len = GetPointsNumber();
			if (len)
				fprintf(stream, "%d, %d \"%s\"\n", len, 0, this->GetName().c_str());

			PRIMITIVE_POINTS_PTR(T) ptd	= this->m_vdPoints PRIMITIVE_POINTS_PTR_BEGIN;
			
			for (size_t i = 0; i < len; i++)
			{			
				fprintf(stream, "%lf, %lf, %lf\n", 
					ptd[i].x, 
					ptd[i].y, 
					ptd[i].z);
			}
			return true;
		}
		return false;
	}
	bool SaveAsBln_XZ(FILE * stream)
	{
		if (stream)
		{
			size_t len = GetPointsNumber();
			if (len)
				fprintf(stream, "%d, %d \"%s\"\n", len, 0, this->GetName().c_str());

			PRIMITIVE_POINTS_PTR(T) ptd	= this->m_vdPoints PRIMITIVE_POINTS_PTR_BEGIN;
			
			for (size_t i = 0; i < len; i++)
			{			
				fprintf(stream, "%lf, %lf\n", 
					ptd[i].x, 
					ptd[i].z);
			}
			return true;
		}
		return false;
	}
	bool SaveAsBln_YZ(FILE * stream)
	{
		if (stream)
		{
			size_t len = GetPointsNumber();
			if (len)
				fprintf(stream, "%d, %d \"%s\"\n", len, 0, this->GetName().c_str());

			PRIMITIVE_POINTS_PTR(T) ptd	= this->m_vdPoints PRIMITIVE_POINTS_PTR_BEGIN;
			
			for (size_t i = 0; i < len; i++)
			{			
				fprintf(stream, "%lf, %lf\n", 
					ptd[i].y, 
					ptd[i].z);
			}
			return true;
		}
		return false;
	}
	bool SaveAsDat(FILE * stream)
	{
		if (stream)
		{
			PRIMITIVE_POINTS_PTR(T) ptd	= this->m_vdPoints PRIMITIVE_POINTS_PTR_BEGIN;
			for(size_t i = 0; i < this->m_nPoints; i++)
			{
				fprintf(stream, "%lf, %lf, %lf\n", 
					ptd[i].x, 
					ptd[i].y, 
					ptd[i].z);
			}
			return true;
		}
		return false;
	}
	void Free()
	{
		PRIMITIVE_POINTS_FREE(m_vvPoints);
		PRIMITIVE_POINTS_FREE(m_vdPoints);
		m_nPoints	= 0;
	}
	void InitPoints(T *pts, int len, COLORREF color)
	{
		Free();
		AllocPoints(len);
		m_color = color;
		bool start = true;
		// складываем данные в документ
		for(size_t i = 0; i < GetPointsNumber(); i++)
		{
			m_vdPoints[i] = pts[i];
			m_vvPoints[i] = pts[i];
			if (start)
			{
				m_ptMax = pts[i];
				m_ptMin = pts[i];
				start = false;
			}
			else
			{
				if(m_ptMax.x < pts[i].x) m_ptMax.x = pts[i].x;
				if(m_ptMin.x > pts[i].x) m_ptMin.x = pts[i].x;

				if(m_ptMax.y < pts[i].y) m_ptMax.y = pts[i].y;
				if(m_ptMin.y > pts[i].y) m_ptMin.y = pts[i].y;

				if(m_ptMax.z < pts[i].z) m_ptMax.z = pts[i].z;
				if(m_ptMin.z > pts[i].z) m_ptMin.z = pts[i].z;
			}
		}
	}		
	void InitPoints(vector<T> pts, COLORREF color)
	{
		Free();
		AllocPoints(pts.size());
		m_color = color;
		bool start = true;
		// складываем данные в документ
		for(size_t i = 0; i < GetPointsNumber(); i++)
		{
			m_vdPoints[i] = pts[i];
			m_vvPoints[i] = pts[i];
			if (start)
			{
				m_ptMax = pts[i];
				m_ptMin = pts[i];
				start = false;
			}
			else
			{
				if(m_ptMax.x < pts[i].x) m_ptMax.x = pts[i].x;
				if(m_ptMin.x > pts[i].x) m_ptMin.x = pts[i].x;

				if(m_ptMax.y < pts[i].y) m_ptMax.y = pts[i].y;
				if(m_ptMin.y > pts[i].y) m_ptMin.y = pts[i].y;

				if(m_ptMax.z < pts[i].z) m_ptMax.z = pts[i].z;
				if(m_ptMin.z > pts[i].z) m_ptMin.z = pts[i].z;
			}
		}
	}	
	void InitPoints(vector<double>& x, vector<double>& y, vector<double>& z, COLORREF color)
	{
		if (x.size() == y.size() && y.size() == z.size())
		{
			Free();
			AllocPoints(z.size());
			m_color = color;
			bool start = true;
			T pt;
			pt.bVisible = true;
			// складываем данные в документ
			for(size_t i = 0; i < GetPointsNumber(); i++)
			{
				pt.x = x[i];
				pt.y = y[i];
				pt.z = z[i];
				m_vdPoints[i] = pt;
				m_vvPoints[i] = pt;
				if (start)
				{
					m_ptMax = pt;
					m_ptMin = pt;
					start = false;
				}
				else
				{
					if(m_ptMax.x < pt.x) m_ptMax.x = pt.x;
					if(m_ptMin.x > pt.x) m_ptMin.x = pt.x;

					if(m_ptMax.y < pt.y) m_ptMax.y = pt.y;
					if(m_ptMin.y > pt.y) m_ptMin.y = pt.y;

					if(m_ptMax.z < pt.z) m_ptMax.z = pt.z;
					if(m_ptMin.z > pt.z) m_ptMin.z = pt.z;
				}
			}
		}
	}	
	void InitPoint(T& pt, COLORREF color)
	{
		Free();
		AllocPoints(1);
		m_color = color;
		bool start = true;
		// складываем данные в документ

		m_vdPoints[0] = pt;
		m_vvPoints[0] = pt;

		m_ptMax = pt;
		m_ptMin = pt;

	}
	void OnDestroy()
	{
		Free();
		m_nPoints	= 0;
	}
	virtual ~Primitive3D()
	{
		OnDestroy();
	}
	size_t GetPointsNumber()
	{
		return m_nPoints;
	}
	T& GetDocumentPoint( size_t i )
	{
		return m_vdPoints[i];
	}
	T& GetFirstDocumentPoint()
	{
		return m_vdPoints[0];
	}
	T& GetLastDocumentPoint()
	{
		return m_vdPoints[m_nPoints-1];
	}
	T& GetViewPoint( size_t i )
	{
		return m_vvPoints[i];
	}
	virtual bool UpdateExtremums(Profile3D * on, bool & start, CPoint2 & profile_min, CPoint2 & profile_max);

	virtual bool UpdateExtremums()
	{
		bool start = true;
		for (size_t ipoint = 0; ipoint < m_nPoints; ipoint++)
		{							
			if (m_vdPoints[ipoint].bVisible)
			{
				if (start)
				{
					m_ptMin.x = m_ptMax.x = m_vdPoints[ipoint].x;
					m_ptMin.y = m_ptMax.y = m_vdPoints[ipoint].y;
					m_ptMin.z = m_ptMax.z = m_vdPoints[ipoint].z;
					start = false;
				}
				else
				{
					if (m_ptMin.x > m_vdPoints[ipoint].x) m_ptMin.x = m_vdPoints[ipoint].x;
					if (m_ptMax.x < m_vdPoints[ipoint].x) m_ptMax.x = m_vdPoints[ipoint].x;

					if (m_ptMin.y > m_vdPoints[ipoint].y) m_ptMin.y = m_vdPoints[ipoint].y;
					if (m_ptMax.y < m_vdPoints[ipoint].y) m_ptMax.y = m_vdPoints[ipoint].y;

					if (m_ptMin.z > m_vdPoints[ipoint].z) m_ptMin.z = m_vdPoints[ipoint].z;
					if (m_ptMax.z < m_vdPoints[ipoint].z) m_ptMax.z = m_vdPoints[ipoint].z;
				}
			}
		}
		return !start;
	}
	void Zoom(double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean)
	{
		for (size_t ipoint = 0; ipoint < m_nPoints; ipoint++)
		{							
			m_vvPoints[ipoint].bVisible = m_vdPoints[ipoint].bVisible;

			m_vvPoints[ipoint].z = 
				zoomZ * (m_vdPoints[ipoint].z - z_mean);
			m_vvPoints[ipoint].y = 
				zoomY * (m_vdPoints[ipoint].y - y_mean);
			m_vvPoints[ipoint].x = 
				zoomX * (m_vdPoints[ipoint].x - x_mean);
		}
	}
	void Zoom(size_t ipoint, double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean)
	{
		if (ipoint < m_nPoints && ipoint >= 0 )
		{							
			m_vvPoints[ipoint].bVisible = m_vdPoints[ipoint].bVisible;

			m_vvPoints[ipoint].z = 
				zoomZ * (m_vdPoints[ipoint].z - z_mean);
			m_vvPoints[ipoint].y = 
				zoomY * (m_vdPoints[ipoint].y - y_mean);
			m_vvPoints[ipoint].x = 
				zoomX * (m_vdPoints[ipoint].x - x_mean);
		}
	}
	void ZoomInv(double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean)
	{
		for (size_t ipoint = 0; ipoint < m_nPoints; ipoint++)
		{							
			m_vdPoints[ipoint].bVisible = m_vvPoints[ipoint].bVisible;
			m_vdPoints[ipoint].z = z_mean + m_vvPoints[ipoint].z / zoomZ;
			m_vdPoints[ipoint].y = y_mean + m_vvPoints[ipoint].y / zoomY;
			m_vdPoints[ipoint].x = x_mean + m_vvPoints[ipoint].x / zoomX;
		}
	}
	void ZoomInv(size_t ipoint, double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean)
	{
		if (ipoint < m_nPoints && ipoint >= 0 )
		{							
			m_vdPoints[ipoint].bVisible = m_vvPoints[ipoint].bVisible;
			m_vdPoints[ipoint].z = z_mean + m_vvPoints[ipoint].z / zoomZ;
			m_vdPoints[ipoint].y = y_mean + m_vvPoints[ipoint].y / zoomY;
			m_vdPoints[ipoint].x = x_mean + m_vvPoints[ipoint].x / zoomX;
		}
	}
	void SetZeroIfBlanked()
	{
		for (size_t ipoint = 0; ipoint < m_nPoints; ipoint++)
		{
			if (!m_vdPoints[ipoint].bVisible)
			{
				m_vdPoints[ipoint].bVisible = true;
				m_vdPoints[ipoint].z = 0.0;
			}
		}
	}
	void CutAndDisvisible(bool positive, double a, double b, double c, double d)
	{
		for (size_t ipoint = 0; ipoint < m_nPoints; ipoint++)
		{
			// растояние от точки до плоскости
			double r = 
				a*m_vdPoints[ipoint].x+
				b*m_vdPoints[ipoint].y+
				c*m_vdPoints[ipoint].z+
				d; 

			if (positive)
			{
				if (r > 0.0)
					m_vvPoints[ipoint].bVisible = false;
				else
					m_vvPoints[ipoint].bVisible = m_vdPoints[ipoint].bVisible;

			}
			else
			{
				if (r < 0.0)
					m_vvPoints[ipoint].bVisible = false;
				else
					m_vvPoints[ipoint].bVisible = m_vdPoints[ipoint].bVisible;
			}
		}
	}
	void CutXYZandDisvisible(int subcube_number, double X, double Y, double Z)
	{
		double x,y,z;
							
		for (size_t ipoint = 0; ipoint < m_nPoints; ipoint++)
		{
			x = m_vdPoints[ipoint].x;
			y = m_vdPoints[ipoint].y;
			z = m_vdPoints[ipoint].z;

			//bool bi = m_vdPoints[ipoint].bVisible;


			switch (subcube_number)
			{
			case 1:
				if (x > X  && y > Y && z > Z)
					m_vvPoints[ipoint].bVisible = false;
				else
					m_vvPoints[ipoint].bVisible = m_vdPoints[ipoint].bVisible;
				break;
			case 2:
				if (x > X  && y < Y && z > Z)
					m_vvPoints[ipoint].bVisible = false;
				else
					m_vvPoints[ipoint].bVisible = m_vdPoints[ipoint].bVisible;
				break;
			case 3:
				if (x < X  && y < Y && z > Z)
					m_vvPoints[ipoint].bVisible = false;
				else
					m_vvPoints[ipoint].bVisible = m_vdPoints[ipoint].bVisible;
				break;
			case 4:
				if (x < X  && y > Y && z > Z)
					m_vvPoints[ipoint].bVisible = false;
				else
					m_vvPoints[ipoint].bVisible = m_vdPoints[ipoint].bVisible;
				break;
			case 5:
				if (x > X  && y > Y && z < Z)
					m_vvPoints[ipoint].bVisible = false;
				else
					m_vvPoints[ipoint].bVisible = m_vdPoints[ipoint].bVisible;
				break;
			case 6:
				if (x > X  && y < Y && z < Z)
					m_vvPoints[ipoint].bVisible = false;
				else
					m_vvPoints[ipoint].bVisible = m_vdPoints[ipoint].bVisible;
				break;
			case 7:
				if (x < X  && y < Y && z < Z)
					m_vvPoints[ipoint].bVisible = false;
				else
					m_vvPoints[ipoint].bVisible = m_vdPoints[ipoint].bVisible;
				break;
			case 8:
				if (x < X  && y > Y && z < Z)
					m_vvPoints[ipoint].bVisible = false;
				else
					m_vvPoints[ipoint].bVisible = m_vdPoints[ipoint].bVisible;
				break;
			}
		}
	}

	virtual bool ColorDialog(void)
	{
		return ChooseSurfColor(NULL, m_color) == 0;
	}

	bool SetColorFromCurrentWellsSloj();

	virtual COLORREF GetColor(void)
	{		
		return this->m_color;
	}
};
typedef Primitive3D <CPoint3> * PRIMITIVE_PTR;

#endif // !defined(AFX_PRIMITIVE3D_H__2B120F8F_F432_4517_8B3B_DC4629ABEFDC__INCLUDED_)
