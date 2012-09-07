// DBTablePtStZond.h: interface for the DBTablePtStZond class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBTABLEPTSTZOND_H__1D8BC6CA_182D_4675_8B9B_AC9D68BD0AE5__INCLUDED_)
#define AFX_DBTABLEPTSTZOND_H__1D8BC6CA_182D_4675_8B9B_AC9D68BD0AE5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBTable.h"

class DBTablePtStZond : public DBTable  
{
public:
	DBTablePtStZond(const char * tbnm);
	virtual ~DBTablePtStZond();
	void EnumCallBack(CRecordset * pRecordset);

};

#endif // !defined(AFX_DBTABLEPTSTZOND_H__1D8BC6CA_182D_4675_8B9B_AC9D68BD0AE5__INCLUDED_)
