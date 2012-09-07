// DBTablePCK2Fiz_Params.h: interface for the DBTablePCK2Fiz_Params class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBTABLEPCK2FIZ_PARAMS_H__0C8FF270_A4E6_4F63_AAEF_0223971D2ACF__INCLUDED_)
#define AFX_DBTABLEPCK2FIZ_PARAMS_H__0C8FF270_A4E6_4F63_AAEF_0223971D2ACF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBTable.h"

class DBTablePCK2Fiz_Params : public DBTable  
{
public:
	DBTablePCK2Fiz_Params(const char * tbnm);
	virtual ~DBTablePCK2Fiz_Params();
	virtual void EnumCallBack(CRecordset * pRecordset);

};

#endif // !defined(AFX_DBTABLEPCK2FIZ_PARAMS_H__0C8FF270_A4E6_4F63_AAEF_0223971D2ACF__INCLUDED_)
