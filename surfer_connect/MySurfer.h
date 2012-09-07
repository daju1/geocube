// MySurfer.h: interface for the MySurfer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYSURFER_H__438EF4E5_D73F_4333_822D_6995BFC0E248__INCLUDED_)
#define AFX_MYSURFER_H__438EF4E5_D73F_4333_822D_6995BFC0E248__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Surfer.h"

class MySurfer  
{
	bool got_active_Surfer_window;
public:

	IApplication	m_app;
	IDocuments		m_documents;
	IDocument		m_document;
public:

	bool GotActiveSurferWindow(){return got_active_Surfer_window;}
	MySurfer();
	virtual ~MySurfer();

	void SurferOleRelease();
	bool IsApplicationDispatch();
	//void SurferOleExecute_2();
	//void SurferOleExecute();
	void SurferOleExecute(const char * file);
	bool SurferOleLoad();

	static bool alert;
	static bool skip_next_alert;

};

#endif // !defined(AFX_MYSURFER_H__438EF4E5_D73F_4333_822D_6995BFC0E248__INCLUDED_)
