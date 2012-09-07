// DBTableGridDataUsedAlg.h: interface for the DBTableGridDataUsedAlg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBTABLEGRIDDATAUSEDALG_H__7231AE9C_AFDA_443A_90AC_219450E4CA88__INCLUDED_)
#define AFX_DBTABLEGRIDDATAUSEDALG_H__7231AE9C_AFDA_443A_90AC_219450E4CA88__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBTable.h"

class DBTableGridDataUsedAlg : public DBTable  
{
public:
	DBTableGridDataUsedAlg(const char * tbnm);
	virtual ~DBTableGridDataUsedAlg();
	virtual void EnumCallBack(CRecordset * pRecordset);

};

#endif // !defined(AFX_DBTABLEGRIDDATAUSEDALG_H__7231AE9C_AFDA_443A_90AC_219450E4CA88__INCLUDED_)
