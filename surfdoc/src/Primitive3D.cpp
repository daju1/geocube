// Primitive3D.cpp: implementation of the Primitive3D class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Primitive3D.h"
#include "surfdoc.h"

#pragma warning (disable:4005)
#define MY_CPOINT CPoint3
#include "Primitive3D_members.h"
#define MY_CPOINT CPoint4
#include "Primitive3D_members.h"
#pragma warning (default:4005)

void Primitive3D<CPoint3>::Draw()
{
	m_nglListNumber = DrawListArray::glNewList();
	Drawing();
	glEndList();
}
void Primitive3D<CPoint3>::ReDrawWithoutTree(void)
{
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


void Primitive3D<CPoint4>::ReDrawWithoutTree(void)
{
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


void Primitive3D<CPoint3>::ReDraw(void)
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


void Primitive3D<CPoint4>::Draw()
{
	m_nglListNumber = DrawListArray::glNewList();
	Drawing();
	glEndList();
}

void Primitive3D<CPoint4>::ReDraw(void)
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







bool Primitive3D<CPoint3>::SetColorFromCurrentWellsSloj()
{
	printf("Well_3D::s_sloj_number_to_save = %d\n", Well_3D::s_sloj_number_to_save);
	if (this->m_pSurfDoc && this->m_pSurfDoc->m_drills.SetCurrentMsgOnFirst())
	{
		do
		{
			int i = Well_3D::s_sloj_number_to_save;
			if (i >=0 && i < (int)this->m_pSurfDoc->m_drills.GetCurrentMsg().GetPointsNumber())
			{
				CPoint3 pt			= this->m_pSurfDoc->m_drills.GetCurrentMsg().GetDocumentPoint(i);
				COLORREF color		= this->m_pSurfDoc->m_drills.GetCurrentMsg().GetColor(i);
				string sloj_name	= this->m_pSurfDoc->m_drills.GetCurrentMsg().GetSlojName(i);
				string well_id		= this->m_pSurfDoc->m_drills.GetCurrentMsg().GetWellID();
                
				if (pt.bVisible)
				{
					printf("%s\t%s\t[%lf, %lf, %lf] color = %d\n", 
					well_id.c_str(), 
					sloj_name.c_str(),
					pt.x, 
					pt.y, 
					pt.z, color);

					this->m_color = color;
					return true;
				}
			}
		}
		while (this->m_pSurfDoc->m_drills.IncrementCurrentMsg());
	}
	return false;


}

bool Primitive3D<CPoint4>::UpdateExtremums(Profile3D * on, bool & start, CPoint2 & profile_min, CPoint2 & profile_max)
{
	double dist_to_plane;		CPoint2 profile;
	for (size_t ipoint = 0; ipoint < m_nPoints; ipoint++)
	{							
		if (m_vdPoints[ipoint].bVisible)
		{
			on->Projection(m_vdPoints[ipoint], profile, dist_to_plane);
			if (start)
			{
				profile_max.x = profile_min.x = profile.x;
				profile_max.y = profile_min.y = profile.y;
				start = false;
			}
			else
			{
				if (profile_min.x > profile.x) profile_min.x = profile.x;
				if (profile_max.x < profile.x) profile_max.x = profile.x;

				if (profile_min.y > profile.y) profile_min.y = profile.y;
				if (profile_max.y < profile.y) profile_max.y = profile.y;

			}
		}
	}
	return !start;
}

bool Primitive3D<CPoint3>::UpdateExtremums(Profile3D * on, bool & start, CPoint2 & profile_min, CPoint2 & profile_max)
{
	double dist_to_plane;		
	CPoint2 profile;
	for (size_t ipoint = 0; ipoint < m_nPoints; ipoint++)
	{							
		if (m_vdPoints[ipoint].bVisible)
		{
			on->Projection(m_vdPoints[ipoint], profile, dist_to_plane);
			if (start)
			{
				profile_max.x = profile_min.x = profile.x;
				profile_max.y = profile_min.y = profile.y;
				start = false;
			}
			else
			{
				if (profile_min.x > profile.x) profile_min.x = profile.x;
				if (profile_max.x < profile.x) profile_max.x = profile.x;

				if (profile_min.y > profile.y) profile_min.y = profile.y;
				if (profile_max.y < profile.y) profile_max.y = profile.y;

			}
		}
	}
	return !start;
}
