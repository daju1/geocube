// ExcelSandGranular.h: interface for the ExcelSandGranular class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SANDGRANULAREXCEL_H__CF9B5D68_D488_460B_A72E_F6D2F733FAB7__INCLUDED_)
#define AFX_SANDGRANULAREXCEL_H__CF9B5D68_D488_460B_A72E_F6D2F733FAB7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseExcel.h"

class ExcelSandGranular : public BaseExcel  
{
	virtual bool virCompute(bool = false);
	virtual void virSaveToDB();
	virtual void InitExt();
public:
	ExcelSandGranular();
	virtual ~ExcelSandGranular();

};

#endif // !defined(AFX_SANDGRANULAREXCEL_H__CF9B5D68_D488_460B_A72E_F6D2F733FAB7__INCLUDED_)
