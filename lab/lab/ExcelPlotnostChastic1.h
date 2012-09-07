// ExcelPlotnostChastic1.h: interface for the ExcelPlotnostChastic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLOTNOSTCHASTICEXCEL1_H__B8506374_5686_4911_8320_9E644B75483D__INCLUDED_)
#define AFX_PLOTNOSTCHASTICEXCEL1_H__B8506374_5686_4911_8320_9E644B75483D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseExcel.h"

class ExcelPlotnostChastic1 : public BaseExcel  
{
	virtual bool virCompute(bool = false){return true;}
	virtual void virSaveToDB();
	virtual void InitExt();
public:
	void UpdateSaveToDB(CCmdUI* pCmdUI) 
	{
		pCmdUI->Enable(this->m_excel.IsApplicationDispatch());	
	}
	ExcelPlotnostChastic1();
	virtual ~ExcelPlotnostChastic1();

};

#endif // !defined(AFX_PLOTNOSTCHASTICEXCEL1_H__B8506374_5686_4911_8320_9E644B75483D__INCLUDED_)
