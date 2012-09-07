// ExcelStatZondList.h: interface for the ExcelStatZondList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXCELSTATZONDLIST_H__C2EE6082_4742_4EF3_8853_CCFBF3791AE4__INCLUDED_)
#define AFX_EXCELSTATZONDLIST_H__C2EE6082_4742_4EF3_8853_CCFBF3791AE4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseExcel.h"

class ExcelStatZondList : public BaseExcel  
{
	friend class ExcelTSZList;
	virtual bool virFill();
	virtual bool virCompute(bool = false);
	virtual void virSaveToDB();
	virtual void InitExt();
public:
	bool output;

	void UpdateSaveToDB(CCmdUI* pCmdUI) 
	{
		pCmdUI->Enable(this->m_excel.IsApplicationDispatch());	
	}
	void Save(long ID_OBJ, long ID_KT);

	ExcelStatZondList();
	virtual ~ExcelStatZondList();

};

#endif // !defined(AFX_EXCELSTATZONDLIST_H__C2EE6082_4742_4EF3_8853_CCFBF3791AE4__INCLUDED_)
