// ExcelPlotnostChastic.h: interface for the ExcelPlotnostChastic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLOTNOSTCHASTICEXCEL_H__B8506374_5686_4911_8320_9E644B75483D__INCLUDED_)
#define AFX_PLOTNOSTCHASTICEXCEL_H__B8506374_5686_4911_8320_9E644B75483D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseExcel.h"

class ExcelPlotnostChastic : public BaseExcel  
{
	virtual bool virCompute(bool = false);
	virtual void virSaveToDB();
	virtual void InitExt();
public:
	ExcelPlotnostChastic();
	virtual ~ExcelPlotnostChastic();

};

#endif // !defined(AFX_PLOTNOSTCHASTICEXCEL_H__B8506374_5686_4911_8320_9E644B75483D__INCLUDED_)
