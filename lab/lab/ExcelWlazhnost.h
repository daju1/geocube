// ExcelWlazhnost.h: interface for the ExcelWlazhnost class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WLAZHNOSTEXCEL_H__6210FC46_7DE9_47D6_B0A5_8B33D05E208E__INCLUDED_)
#define AFX_WLAZHNOSTEXCEL_H__6210FC46_7DE9_47D6_B0A5_8B33D05E208E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseExcel.h"

class ExcelWlazhnost : public BaseExcel  
{
	virtual bool virCompute(bool = false);
	virtual void virSaveToDB();
	virtual void InitExt();
public:
	ExcelWlazhnost();
	virtual ~ExcelWlazhnost();

};

#endif // !defined(AFX_WLAZHNOSTEXCEL_H__6210FC46_7DE9_47D6_B0A5_8B33D05E208E__INCLUDED_)
