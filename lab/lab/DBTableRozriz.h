// DBTableRozriz.h: interface for the DBTableRozriz class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBTABLEROZRIZ_H__0C8FF270_A4E6_4F63_AAEF_0223971D2ACF__INCLUDED_)
#define AFX_DBTABLEROZRIZ_H__0C8FF270_A4E6_4F63_AAEF_0223971D2ACF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBTable.h"

class DBTableRozriz : public DBTable  
{
public:
	DBTableRozriz(const char * tbnm);
	virtual ~DBTableRozriz();
	virtual void EnumCallBack(CRecordset * pRecordset);

};

#endif // !defined(AFX_DBTABLEROZRIZ_H__0C8FF270_A4E6_4F63_AAEF_0223971D2ACF__INCLUDED_)
