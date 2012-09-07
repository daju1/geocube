// DBTablePtPalja.h: interface for the DBTablePtPalja class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBTABLEPTPALJA_H__E4ABDCD0_63D6_4ECA_8605_91B1A60B178A__INCLUDED_)
#define AFX_DBTABLEPTPALJA_H__E4ABDCD0_63D6_4ECA_8605_91B1A60B178A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBTable.h"

class DBTablePtPalja : public DBTable  
{
public:
	DBTablePtPalja(const char * tbnm);
	virtual ~DBTablePtPalja();
	virtual void EnumCallBack(CRecordset * pRecordset);

};

#endif // !defined(AFX_DBTABLEPTPALJA_H__E4ABDCD0_63D6_4ECA_8605_91B1A60B178A__INCLUDED_)
