// ExcelTSZList.h: interface for the ExcelTSZList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXCELTSZLIST_H__C2EE6082_4742_4EF3_8853_CCFBF3791AE4__INCLUDED_)
#define AFX_EXCELTSZLIST_H__C2EE6082_4742_4EF3_8853_CCFBF3791AE4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseExcel.h"

#include "ExcelStatZondList.h"

class ExcelTSZList : public BaseExcel  
{

	ExcelStatZondList m_excel_stat_zond;
	void SaveTSZList(long ID_OBJ, long ID_KT, CString dir, CString fn);
	

	virtual bool virFill();
	virtual bool virCompute(bool = false){return true;}
	virtual void virSaveToDB();
	virtual void InitExt();
public:
	void UpdateSaveToDB(CCmdUI* pCmdUI) 
	{
		pCmdUI->Enable(this->m_excel.IsApplicationDispatch());	
	}
	void Init(CLabView * view, CLabDoc * doc, CDatabase * database)
	{
		this->BaseExcel::Init(view, doc, database);
		m_excel_stat_zond.Init(view, doc, database);
	}

	ExcelTSZList();
	virtual ~ExcelTSZList();
};

#endif // !defined(AFX_EXCELTSZLIST_H__C2EE6082_4742_4EF3_8853_CCFBF3791AE4__INCLUDED_)
