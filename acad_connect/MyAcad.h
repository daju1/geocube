// MyAcad.h: interface for the MyAcad class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYACAD_H__438EF4E5_D73F_4333_822D_6995BFC0E248__INCLUDED_)
#define AFX_MYACAD_H__438EF4E5_D73F_4333_822D_6995BFC0E248__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "acad.h"

class MyAcad  
{
	bool got_active_acad_window;
public:

	IAcadApplication	m_app;
	IAcadDocuments		m_documents;
	IAcadDocument		m_document;
	IAcadLayers			m_layers;
	IAcadModelSpace		m_model_space;				
	IAcadPaperSpace     m_paper_space;

	IAcadLayouts		m_layouts;
	IAcadDatabase		m_database;
	IAcadViewports		m_viewports;

public:
	MyAcad();
	virtual ~MyAcad();

	void AcadOleRelease();
	bool IsApplicationDispatch();
	//void AcadOleExecute_2();
	//void AcadOleExecute();
	void AcadOleExecute(const char * file);
	void AcadOleLoad();

};

#endif // !defined(AFX_MYACAD_H__438EF4E5_D73F_4333_822D_6995BFC0E248__INCLUDED_)
