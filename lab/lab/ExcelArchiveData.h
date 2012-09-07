// ExcelArchiveData.h: interface for the ExcelPlotnostChastic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARCHIVEDATAEXCEL_H__B8506374_5686_4911_8320_9E644B75483D__INCLUDED_)
#define AFX_ARCHIVEDATAEXCEL_H__B8506374_5686_4911_8320_9E644B75483D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseExcel.h"

class ExcelArchiveData : public BaseExcel  
{

    int npar;
	long id_params[12];

	char first_letter;
	long rows_per_page;

	virtual bool virCompute(bool = false){return true;}
	virtual bool virFill();
	virtual void virSaveToDB();
	virtual void InitExt();
public:
	void UpdateSaveToDB(CCmdUI* pCmdUI) 
	{
		pCmdUI->Enable(this->m_excel.IsApplicationDispatch());	
	}
	ExcelArchiveData();
	virtual ~ExcelArchiveData();

};

#endif // !defined(AFX_ARCHIVEDATAEXCEL_H__B8506374_5686_4911_8320_9E644B75483D__INCLUDED_)
