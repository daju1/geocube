// DBTableProp.h: interface for the DBTableProp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBTABLEPROP_H__AAD2ED2F_20B4_4B0F_B218_62A7AA17E3BF__INCLUDED_)
#define AFX_DBTABLEPROP_H__AAD2ED2F_20B4_4B0F_B218_62A7AA17E3BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBTable.h"

class DBTableProp : public DBTable  
{
public:
	DBTableProp(const char * tbnm);
	virtual ~DBTableProp();
	virtual void EnumCallBack(CRecordset * pRecordset);

};

#endif // !defined(AFX_DBTABLEPROP_H__AAD2ED2F_20B4_4B0F_B218_62A7AA17E3BF__INCLUDED_)
