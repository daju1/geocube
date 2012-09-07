// DBTableGenezis.h: interface for the DBTableGenezis class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBTABLEGENEZIS_H__EB20BC25_E7DD_42CC_B503_CF51D94E3DD7__INCLUDED_)
#define AFX_DBTABLEGENEZIS_H__EB20BC25_E7DD_42CC_B503_CF51D94E3DD7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBTable.h"

class DBTableGenezis : public DBTable  
{
public:
	DBTableGenezis(const char * tbnm);
	virtual ~DBTableGenezis();
	virtual void EnumCallBack(CRecordset * pRecordset);

};

#endif // !defined(AFX_DBTABLEGENEZIS_H__EB20BC25_E7DD_42CC_B503_CF51D94E3DD7__INCLUDED_)
