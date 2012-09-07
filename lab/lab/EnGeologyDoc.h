// EnGeologyDoc.h: interface for the CEnGeologyDoc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENGEOLOGYDOC_H__CA5C967F_3187_4B65_9EFF_BE145FE18942__INCLUDED_)
#define AFX_ENGEOLOGYDOC_H__CA5C967F_3187_4B65_9EFF_BE145FE18942__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "labDoc.h"

class CEnGeologyView;

class CEnGeologyDoc : public CLabDoc  
{
protected: // create from serialization only
	CEnGeologyDoc();
	DECLARE_DYNCREATE(CEnGeologyDoc)
public:
	virtual ~CEnGeologyDoc();
	virtual bool OpenOdbc(const char * connect_str, bool to_rewrite_list);
	void EnumTables(bool to_rewrite_list);
	CEnGeologyView * GetEnGeologyView();
	virtual void OnDisconnect();
};

#endif // !defined(AFX_ENGEOLOGYDOC_H__CA5C967F_3187_4B65_9EFF_BE145FE18942__INCLUDED_)
