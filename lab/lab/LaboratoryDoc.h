// LaboratoryDoc.h: interface for the CLaboratoryDoc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LABORATORYDOC_H__41AE8BD2_1BBC_4F90_957F_85FFC82F962E__INCLUDED_)
#define AFX_LABORATORYDOC_H__41AE8BD2_1BBC_4F90_957F_85FFC82F962E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "labDoc.h"

class CLaboratoryView;

class CLaboratoryDoc : public CLabDoc  
{
protected: // create from serialization only
	CLaboratoryDoc();
	DECLARE_DYNCREATE(CLaboratoryDoc)
public:
	virtual ~CLaboratoryDoc();
	virtual bool OpenOdbc(const char * connect_str, bool to_rewrite_list);
	void EnumTables(bool to_rewrite_list);
	CLaboratoryView * GetLaboratoryView();
	virtual void OnDisconnect();
};

#endif // !defined(AFX_LABORATORYDOC_H__41AE8BD2_1BBC_4F90_957F_85FFC82F962E__INCLUDED_)
