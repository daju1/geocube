// DBTableGranular.h: interface for the DBTableGranular class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBTABLEGRANULAR_H__E81403B2_74B4_40CC_B057_52C05108C561__INCLUDED_)
#define AFX_DBTABLEGRANULAR_H__E81403B2_74B4_40CC_B057_52C05108C561__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBTable.h"

class DBTableGranular : public DBTable  
{
public:
	DBTableGranular(const char * tbnm);
	virtual ~DBTableGranular();
	virtual void EnumCallBack(CRecordset * pRecordset);

};

#endif // !defined(AFX_DBTABLEGRANULAR_H__E81403B2_74B4_40CC_B057_52C05108C561__INCLUDED_)
