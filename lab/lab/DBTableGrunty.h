// DBTableGrunty.h: interface for the DBTableGrunty class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBTABLEGRUNTY_H__EB20BC25_E7DD_42CC_B503_CF51D94E3DD7__INCLUDED_)
#define AFX_DBTABLEGRUNTY_H__EB20BC25_E7DD_42CC_B503_CF51D94E3DD7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBTable.h"

class DBTableGrunty : public DBTable  
{
public:
	DBTableGrunty(const char * tbnm);
	virtual ~DBTableGrunty();
	virtual void EnumCallBack(CRecordset * pRecordset);

};

#endif // !defined(AFX_DBTABLEGRUNTY_H__EB20BC25_E7DD_42CC_B503_CF51D94E3DD7__INCLUDED_)
