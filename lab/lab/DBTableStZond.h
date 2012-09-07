// DBTableStZond.h: interface for the DBTableStZond class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBTABLESTZOND_H__3C47163C_73D4_403C_A898_5D70C4A906C9__INCLUDED_)
#define AFX_DBTABLESTZOND_H__3C47163C_73D4_403C_A898_5D70C4A906C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBTable.h"

class DBTableStZond : public DBTable  
{
public:
	DBTableStZond(const char * tbnm);
	virtual ~DBTableStZond();
	void EnumCallBack(CRecordset * pRecordset);

};

#endif // !defined(AFX_DBTABLESTZOND_H__3C47163C_73D4_403C_A898_5D70C4A906C9__INCLUDED_)
