// DBTableUmPoz.h: interface for the DBTableUmPoz class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBTABLEUMPOZ_H__EB20BC25_E7DD_42CC_B503_CF51D94E3DD7__INCLUDED_)
#define AFX_DBTABLEUMPOZ_H__EB20BC25_E7DD_42CC_B503_CF51D94E3DD7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBTable.h"

class DBTableUmPoz : public DBTable  
{
public:
	DBTableUmPoz(const char * tbnm);
	virtual ~DBTableUmPoz();
	virtual void EnumCallBack(CRecordset * pRecordset);

};

#endif // !defined(AFX_DBTABLEUMPOZ_H__EB20BC25_E7DD_42CC_B503_CF51D94E3DD7__INCLUDED_)
