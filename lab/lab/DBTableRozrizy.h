// DBTableRozrizy.h: interface for the DBTableRozrizy class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBTABLEROZRIZY_H__0C8FF270_A4E6_4F63_AAEF_0223971D2ACF__INCLUDED_)
#define AFX_DBTABLEROZRIZY_H__0C8FF270_A4E6_4F63_AAEF_0223971D2ACF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBTable.h"

class DBTableRozrizy : public DBTable  
{
public:
	DBTableRozrizy(const char * tbnm);
	virtual ~DBTableRozrizy();
	virtual void EnumCallBack(CRecordset * pRecordset);

};

#endif // !defined(AFX_DBTABLEROZRIZY_H__0C8FF270_A4E6_4F63_AAEF_0223971D2ACF__INCLUDED_)
