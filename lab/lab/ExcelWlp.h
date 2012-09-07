// ExcelWLP.h: interface for the ExcelWLP class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WLPEXCEL_H__55327066_7977_4EAB_9367_D36F2C0F0168__INCLUDED_)
#define AFX_WLPEXCEL_H__55327066_7977_4EAB_9367_D36F2C0F0168__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseExcel.h"

class ExcelWLP : public BaseExcel  
{
	virtual bool virCompute(bool = false);
	virtual void virSaveToDB();
	virtual void InitExt();
public:
	ExcelWLP();
	virtual ~ExcelWLP();

};

#endif // !defined(AFX_WLPEXCEL_H__55327066_7977_4EAB_9367_D36F2C0F0168__INCLUDED_)
