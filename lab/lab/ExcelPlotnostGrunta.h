// ExcelPlotnostGrunta.h: interface for the ExcelPlotnostGrunta class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLOTNOSTGRUNTAEXCEL_H__0F539567_685D_4370_992A_6629AD418657__INCLUDED_)
#define AFX_PLOTNOSTGRUNTAEXCEL_H__0F539567_685D_4370_992A_6629AD418657__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseExcel.h"

class ExcelPlotnostGrunta : public BaseExcel  
{
	virtual bool virCompute(bool = false);
	virtual void virSaveToDB();
	virtual void InitExt();
public:
	ExcelPlotnostGrunta();
	virtual ~ExcelPlotnostGrunta();

};

#endif // !defined(AFX_PLOTNOSTGRUNTAEXCEL_H__0F539567_685D_4370_992A_6629AD418657__INCLUDED_)
