// DBTableLito.h: interface for the DBTableLito class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBTABLELITO_H__0C8FF270_A4E6_4F63_AAEF_0223971D2ACF__INCLUDED_)
#define AFX_DBTABLELITO_H__0C8FF270_A4E6_4F63_AAEF_0223971D2ACF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBTable.h"

class DBTableLito : public DBTable  
{
public:
	DBTableLito(const char * tbnm);
	virtual ~DBTableLito();
	virtual void EnumCallBack(CRecordset * pRecordset);

};

#endif // !defined(AFX_DBTABLELITO_H__0C8FF270_A4E6_4F63_AAEF_0223971D2ACF__INCLUDED_)
