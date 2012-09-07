// DBTableZriz_tbl.h: interface for the DBTableZriz_tbl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBTABLEZRIZ_TBL_H__6C742FE9_39AF_48D4_9720_895A5B54B32B__INCLUDED_)
#define AFX_DBTABLEZRIZ_TBL_H__6C742FE9_39AF_48D4_9720_895A5B54B32B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBTable.h"

class DBTableZriz_tbl : public DBTable  
{
public:
	DBTableZriz_tbl(const char * tbnm);
	virtual ~DBTableZriz_tbl();
	void EnumCallBack(CRecordset * pRecordset);

};

#endif // !defined(AFX_DBTABLEZRIZ_TBL_H__6C742FE9_39AF_48D4_9720_895A5B54B32B__INCLUDED_)
