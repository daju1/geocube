// DBTableGridData.h: interface for the DBTableGridData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBTABLEGRIDDATA_H__7231AE9C_AFDA_443A_90AC_219450E4CA88__INCLUDED_)
#define AFX_DBTABLEGRIDDATA_H__7231AE9C_AFDA_443A_90AC_219450E4CA88__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBTable.h"

class DBTableGridData : public DBTable  
{
public:
	DBTableGridData(const char * tbnm);
	virtual ~DBTableGridData();
	virtual void EnumCallBack(CRecordset * pRecordset);

};

#endif // !defined(AFX_DBTABLEGRIDDATA_H__7231AE9C_AFDA_443A_90AC_219450E4CA88__INCLUDED_)
