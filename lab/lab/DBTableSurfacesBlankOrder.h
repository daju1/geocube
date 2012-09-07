// DBTableSurfacesBlankOrder.h: interface for the DBTableSurfacesBlankOrder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBTABLESURFACESBLANKORDER_H__7231AE9C_AFDA_443A_90AC_219450E4CA88__INCLUDED_)
#define AFX_DBTABLESURFACESBLANKORDER_H__7231AE9C_AFDA_443A_90AC_219450E4CA88__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBTable.h"

class DBTableSurfacesBlankOrder : public DBTable  
{
public:
	DBTableSurfacesBlankOrder(const char * tbnm);
	virtual ~DBTableSurfacesBlankOrder();
	virtual void EnumCallBack(CRecordset * pRecordset);

};

#endif // !defined(AFX_DBTABLESURFACESBLANKORDER_H__7231AE9C_AFDA_443A_90AC_219450E4CA88__INCLUDED_)
