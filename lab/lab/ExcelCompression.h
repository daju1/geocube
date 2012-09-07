// ExcelCompression.h: interface for the ExcelCompression class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMPRESSIONEXCEL_H__201DBF31_0107_4DC5_B1D9_8EE29A3B573E__INCLUDED_)
#define AFX_COMPRESSIONEXCEL_H__201DBF31_0107_4DC5_B1D9_8EE29A3B573E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseExcel.h"

class ExcelCompression : public BaseExcel  
{
	virtual bool virFill();
	virtual bool virCompute(bool toSavetoDB);
	virtual void InitExt();
public:
	ExcelCompression();
	virtual ~ExcelCompression();

};

#endif // !defined(AFX_COMPRESSIONEXCEL_H__201DBF31_0107_4DC5_B1D9_8EE29A3B573E__INCLUDED_)
