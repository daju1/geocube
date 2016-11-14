// DBTableGridDataSurfaces.h: interface for the DBTableGridDataSurfaces class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBTABLEGRIDDATASURFACES_H__7231AE9C_AFDA_443A_90AC_219450E4CA88__INCLUDED_)
#define AFX_DBTABLEGRIDDATASURFACES_H__7231AE9C_AFDA_443A_90AC_219450E4CA88__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBTable.h"

class DBTableGridDataSurfaces : public DBTable
{
public:
	DBTableGridDataSurfaces(const char * tbnm);
	virtual ~DBTableGridDataSurfaces();
	virtual void EnumCallBack(CRecordset * pRecordset);

};

#endif // !defined(AFX_DBTABLEGRIDDATASURFACES_H__7231AE9C_AFDA_443A_90AC_219450E4CA88__INCLUDED_)
