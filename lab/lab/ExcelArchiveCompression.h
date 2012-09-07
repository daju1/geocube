// ExcelArchiveCompression.h: interface for the ExcelPlotnostChastic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARCHIVECOMPRESSEXCEL_H__B8506374_5686_4911_8320_9E644B75483D__INCLUDED_)
#define AFX_ARCHIVECOMPRESSEXCEL_H__B8506374_5686_4911_8320_9E644B75483D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseExcel.h"
class SetCilce;
class ExcelArchiveCompression : public BaseExcel  
{
	long rows_per_page;
	long cols_per_page;
	char first_letter;

    int npar;
	long id_params[7];
	long param_rows[7];

	void FillSetCompress(SetCilce & setCilce, int & n, int & fr, char & letter, int & p);
	void FillProbGrKT(long ID_OBJ, long ID_KT, long ID_PROB, int & n, int & fr, char & letter, bool use_2_colomns, long id_compress_vyprob);
	void FillIncrement(int & n, int & fr, char & letter, bool use_2_colomns);
	void FillReList(int & n, int & fr, char & letter, bool use_2_colomns);


	virtual bool virCompute(bool = false){return true;}
	virtual bool virFill();
	virtual void virSaveToDB();
	virtual void InitExt();
public:
	bool m_to_fill_all_lab_numbers_as_2_vyprob;
	bool m_to_fill_all_lab_numbers;
	bool m_to_save_also_physical;

	void UpdateSaveToDB(CCmdUI* pCmdUI) 
	{
		pCmdUI->Enable(this->m_excel.IsApplicationDispatch());	
	}
	ExcelArchiveCompression();
	virtual ~ExcelArchiveCompression();

};

#endif // !defined(AFX_ARCHIVECOMPRESSEXCEL_H__B8506374_5686_4911_8320_9E644B75483D__INCLUDED_)
