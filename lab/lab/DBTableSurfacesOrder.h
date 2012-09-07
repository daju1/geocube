// DBTableSurfacesOrder.h: interface for the DBTableSurfacesOrder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBTABLESURFACESORDER_H__7231AE9C_AFDA_443A_90AC_219450E4CA88__INCLUDED_)
#define AFX_DBTABLESURFACESORDER_H__7231AE9C_AFDA_443A_90AC_219450E4CA88__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBTable.h"

class DBTableSurfacesOrder : public DBTable  
{
public:
	DBTableSurfacesOrder(const char * tbnm);
	virtual ~DBTableSurfacesOrder();
	virtual void EnumCallBack(CRecordset * pRecordset);

};

#endif // !defined(AFX_DBTABLESURFACESORDER_H__7231AE9C_AFDA_443A_90AC_219450E4CA88__INCLUDED_)
