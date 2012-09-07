// DBTableZriz.h: interface for the DBTableZriz class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBTABLEZRIZ0_H__8B1BE4F3_C2A2_4E9F_BDF4_51D0F59C49B0__INCLUDED_)
#define AFX_DBTABLEZRIZ0_H__8B1BE4F3_C2A2_4E9F_BDF4_51D0F59C49B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBTable.h"

class DBTableZriz0 : public DBTable  
{
public:
	DBTableZriz0(const char * tbnm);
	virtual ~DBTableZriz0();
	void EnumCallBack(CRecordset * pRecordset);

};

#endif // !defined(AFX_DBTABLEZRIZ0_H__8B1BE4F3_C2A2_4E9F_BDF4_51D0F59C49B0__INCLUDED_)
