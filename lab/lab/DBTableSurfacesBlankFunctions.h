// DBTableSurfacesBlankFunctions.h: interface for the DBTableSurfacesBlankFunctions class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBTABLESURFACESBLANKFunctions_H__7231AE9C_AFDA_443A_90AC_219450E4CA88__INCLUDED_)
#define AFX_DBTABLESURFACESBLANKFunctions_H__7231AE9C_AFDA_443A_90AC_219450E4CA88__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBTable.h"

class DBTableSurfacesBlankFunctions : public DBTable  
{
public:
	DBTableSurfacesBlankFunctions(const char * tbnm);
	virtual ~DBTableSurfacesBlankFunctions();
	virtual void EnumCallBack(CRecordset * pRecordset);

};

#endif // !defined(AFX_DBTABLESURFACESBLANKFunctions_H__7231AE9C_AFDA_443A_90AC_219450E4CA88__INCLUDED_)
