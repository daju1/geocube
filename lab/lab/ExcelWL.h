// ExcelWL.h: interface for the ExcelWL class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WLEXCEL_H__F607B400_ED6F_476F_B6AD_A00ED0033976__INCLUDED_)
#define AFX_WLEXCEL_H__F607B400_ED6F_476F_B6AD_A00ED0033976__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseExcel.h"

class ExcelWL : public BaseExcel  
{
	virtual bool virCompute(bool = false);
	virtual void virSaveToDB();
	virtual void InitExt();
public:
	ExcelWL();
	virtual ~ExcelWL();

};

#endif // !defined(AFX_WLEXCEL_H__F607B400_ED6F_476F_B6AD_A00ED0033976__INCLUDED_)
