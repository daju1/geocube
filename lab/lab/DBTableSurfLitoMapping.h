// DBTableSurfLitoMapping.h: interface for the DBTableSurfLitoMapping class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBTABLESURFLITOMAPPING_H__7231AE9C_AFDA_443A_90AC_219450E4CA88__INCLUDED_)
#define AFX_DBTABLESURFLITOMAPPING_H__7231AE9C_AFDA_443A_90AC_219450E4CA88__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBTable.h"

class DBTableSurfLitoMapping : public DBTable  
{
public:
	DBTableSurfLitoMapping(const char * tbnm);
	virtual ~DBTableSurfLitoMapping();
	virtual void EnumCallBack(CRecordset * pRecordset);

};

#endif // !defined(AFX_DBTABLESURfLITOMAPPING_H__7231AE9C_AFDA_443A_90AC_219450E4CA88__INCLUDED_)
