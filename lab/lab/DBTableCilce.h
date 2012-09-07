// DBTableCilce.h: interface for the DBTableCilce class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBTABLECILCE_H__8ABF1664_E726_4DBA_8B12_DE6568002DD6__INCLUDED_)
#define AFX_DBTABLECILCE_H__8ABF1664_E726_4DBA_8B12_DE6568002DD6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBTable.h"

class DBTableCilce : public DBTable  
{
public:
	DBTableCilce(const char * tbnm);
	virtual ~DBTableCilce();
	void EnumCallBack(CRecordset * pRecordset);

};

#endif // !defined(AFX_DBTABLECILCE_H__8ABF1664_E726_4DBA_8B12_DE6568002DD6__INCLUDED_)
