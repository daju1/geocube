// DBTableVoda.h: interface for the DBTableVoda class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBTABLEVODA_H__7231AE9C_AFDA_443A_90AC_219450E4CA88__INCLUDED_)
#define AFX_DBTABLEVODA_H__7231AE9C_AFDA_443A_90AC_219450E4CA88__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBTable.h"

class DBTableVoda : public DBTable  
{
public:
	DBTableVoda(const char * tbnm);
	virtual ~DBTableVoda();
	virtual void EnumCallBack(CRecordset * pRecordset);

};

#endif // !defined(AFX_DBTABLEVODA_H__7231AE9C_AFDA_443A_90AC_219450E4CA88__INCLUDED_)
