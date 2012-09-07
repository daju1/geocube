// DBTableCompress.h: interface for the DBTableCompress class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBTABLECOMPRESS_H__9723914A_2165_4158_B607_0FD8380BD772__INCLUDED_)
#define AFX_DBTABLECOMPRESS_H__9723914A_2165_4158_B607_0FD8380BD772__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBTable.h"

class DBTableCompress : public DBTable  
{
public:
	DBTableCompress(const char * tbnm);
	virtual ~DBTableCompress();
	void EnumCallBack(CRecordset * pRecordset);

};

#endif // !defined(AFX_DBTABLECOMPRESS_H__9723914A_2165_4158_B607_0FD8380BD772__INCLUDED_)
