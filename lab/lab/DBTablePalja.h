// DBTablePalja.h: interface for the DBTablePalja class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBTABLEPALJA_H__576E0842_713F_4471_A49D_CF11D8E04AE7__INCLUDED_)
#define AFX_DBTABLEPALJA_H__576E0842_713F_4471_A49D_CF11D8E04AE7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBTable.h"

class DBTablePalja : public DBTable  
{
public:
	DBTablePalja(const char * tbnm);
	virtual ~DBTablePalja();
	virtual void EnumCallBack(CRecordset * pRecordset);

};

#endif // !defined(AFX_DBTABLEPALJA_H__576E0842_713F_4471_A49D_CF11D8E04AE7__INCLUDED_)
