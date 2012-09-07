// ExcelHydroList.h: interface for the ExcelHydroList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXCELKTHYDROLIST_H__C2EE6082_4742_4EF3_8853_CCFBF3791AE4__INCLUDED_)
#define AFX_EXCELKTHYDROLIST_H__C2EE6082_4742_4EF3_8853_CCFBF3791AE4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseExcel.h"

class ExcelHydroList : public BaseExcel  
{
	char fc;
	virtual bool virFill();
	virtual bool virCompute(bool = false){return true;}
	virtual void virSaveToDB();
	virtual void InitExt();
public:

	void UpdateSaveToDB(CCmdUI* pCmdUI) 
	{
		pCmdUI->Enable(this->m_excel.IsApplicationDispatch());	
	}

	ExcelHydroList();
	virtual ~ExcelHydroList();

};

#endif // !defined(AFX_EXCELKTHYDROLIST_H__C2EE6082_4742_4EF3_8853_CCFBF3791AE4__INCLUDED_)
