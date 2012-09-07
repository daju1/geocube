// DBTableSoils.h: interface for the DBTableSoils class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBTABLESOILS_H__5C28B9CB_94C3_4A98_84A0_64D5643CC91B__INCLUDED_)
#define AFX_DBTABLESOILS_H__5C28B9CB_94C3_4A98_84A0_64D5643CC91B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBTable.h"

class DBTableSoils : public DBTable  
{
public:
	DBTableSoils(const char * tbnm);
	virtual ~DBTableSoils();
	virtual void EnumCallBack(CRecordset * pRecordset);

};

#endif // !defined(AFX_DBTABLESOILS_H__5C28B9CB_94C3_4A98_84A0_64D5643CC91B__INCLUDED_)
