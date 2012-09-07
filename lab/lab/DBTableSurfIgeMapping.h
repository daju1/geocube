// DBTableSurfIgeMapping.h: interface for the DBTableSurfIgeMapping class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBTABLESURFIGEMAPPING_H__7231AE9C_AFDA_443A_90AC_219450E4CA88__INCLUDED_)
#define AFX_DBTABLESURFIGEMAPPING_H__7231AE9C_AFDA_443A_90AC_219450E4CA88__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBTable.h"

class DBTableSurfIgeMapping : public DBTable  
{
public:
	DBTableSurfIgeMapping(const char * tbnm);
	virtual ~DBTableSurfIgeMapping();
	virtual void EnumCallBack(CRecordset * pRecordset);

};

#endif // !defined(AFX_DBTABLESURfIGEMAPPING_H__7231AE9C_AFDA_443A_90AC_219450E4CA88__INCLUDED_)
