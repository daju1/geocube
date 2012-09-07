// DBTableCubeSize.h: interface for the DBTableCubeSize class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBTABLECUBESIZE_H__7231AE9C_AFDA_443A_90AC_219450E4CA88__INCLUDED_)
#define AFX_DBTABLECUBESIZE_H__7231AE9C_AFDA_443A_90AC_219450E4CA88__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBTable.h"

class DBTableCubeSize : public DBTable  
{
public:
	DBTableCubeSize(const char * tbnm);
	virtual ~DBTableCubeSize();
	virtual void EnumCallBack(CRecordset * pRecordset);

};

#endif // !defined(AFX_DBTABLECUBESIZE_H__7231AE9C_AFDA_443A_90AC_219450E4CA88__INCLUDED_)
