// ExcelArchiveCut.h: interface for the ExcelPlotnostChastic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARCHIVECUTEXCEL_H__B8506374_5686_4911_8320_9E644B75483D__INCLUDED_)
#define AFX_ARCHIVECUTEXCEL_H__B8506374_5686_4911_8320_9E644B75483D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseExcel.h"
class SetZriz;
class ExcelArchiveCut : public BaseExcel  
{
	char first_letter;
	long rows_per_page;
	long cols_per_page;

    int npar;
	long id_params[7];
	long param_rows[7];

	void FillReList(int & n, int & fr, char & letter);
	void FillProbGrKT(long ID_OBJ, long ID_KT, long ID_PROB, int & n, int & fr, char & letter, long id_cut_vyprob);
	void FillZriz_tbl(SetZriz & setZriz, int & n, int & fr, char & letter, int & p);

	void FillIncrement(int & n, int & fr, char & letter);

	virtual bool virCompute(bool = false){return true;}
	virtual bool virFill();
	virtual void virSaveToDB();
	virtual void InitExt();
public:
	bool m_to_fill_all_lab_numbers_as_2_colomns;// если мы хотим в каждом лабораторном номере давать свои вертикальные нагрузки 
	bool m_to_fill_all_lab_numbers_as_3_vyprob;// если мы хотим каждое кольцо отобразить отдельно со своими физсвойствами
	bool m_to_fill_all_lab_numbers;
	bool m_to_save_also_physical;

	void UpdateSaveToDB(CCmdUI* pCmdUI) 
	{
		pCmdUI->Enable(this->m_excel.IsApplicationDispatch());	
	}
	ExcelArchiveCut();
	virtual ~ExcelArchiveCut();

};

#endif // !defined(AFX_ARCHIVECUTEXCEL_H__B8506374_5686_4911_8320_9E644B75483D__INCLUDED_)
