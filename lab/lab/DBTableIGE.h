// DBTableIGE.h: interface for the DBTableIGE class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBTABLEIGE_H__7231AE9C_AFDA_443A_90AC_219450E4CA88__INCLUDED_)
#define AFX_DBTABLEIGE_H__7231AE9C_AFDA_443A_90AC_219450E4CA88__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBTable.h"

class DBTableIGE : public DBTable  
{
public:
	DBTableIGE(const char * tbnm);
	virtual ~DBTableIGE();
	virtual void EnumCallBack(CRecordset * pRecordset);

};

#endif // !defined(AFX_DBTABLEIGE_H__7231AE9C_AFDA_443A_90AC_219450E4CA88__INCLUDED_)
