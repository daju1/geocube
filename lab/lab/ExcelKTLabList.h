// ExcelKTLabList.h: interface for the ExcelKTLabList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXCELKTLIST_H__C2EE6082_4742_4EF3_8853_CCFBF3791AE4__INCLUDED_)
#define AFX_EXCELKTLIST_H__C2EE6082_4742_4EF3_8853_CCFBF3791AE4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseExcel.h"

class ExcelKTLabList : public BaseExcel  
{
	virtual bool virCompute(bool = false){return true;}
	virtual bool virFill();
	virtual void virSaveToDB();
	virtual void InitExt();
public:
	bool to_rename_kt;
	void UpdateSaveToDB(CCmdUI* pCmdUI) 
	{
		pCmdUI->Enable(this->m_excel.IsApplicationDispatch());	
	}
	ExcelKTLabList();
	virtual ~ExcelKTLabList();
};

#endif // !defined(AFX_EXCELKTLIST_H__C2EE6082_4742_4EF3_8853_CCFBF3791AE4__INCLUDED_)
