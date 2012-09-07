// DBTableIGE.h: interface for the DBTableIGE class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBTABLEIGE0_H__7231AE9C_AFDA_443A_90AC_219450E4CA88__INCLUDED_)
#define AFX_DBTABLEIGE0_H__7231AE9C_AFDA_443A_90AC_219450E4CA88__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBTable.h"

class DBTableIGE0 : public DBTable  
{
public:
	DBTableIGE0(const char * tbnm);
	virtual ~DBTableIGE0();
	virtual void EnumCallBack(CRecordset * pRecordset);

};

#endif // !defined(AFX_DBTABLEIGE0_H__7231AE9C_AFDA_443A_90AC_219450E4CA88__INCLUDED_)
