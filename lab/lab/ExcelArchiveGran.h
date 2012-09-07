// ExcelArchiveGran.h: interface for the ExcelPlotnostChastic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARCHIVEGRANEXCEL_H__B8506374_5686_4911_8320_9E644B75483D__INCLUDED_)
#define AFX_ARCHIVEGRANEXCEL_H__B8506374_5686_4911_8320_9E644B75483D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <map>
using namespace std;

#include "BaseExcel.h"
class SetGranular;
struct gran_row
{
	int row1;
	int row2;
	gran_row(int r)
	{
		row1 = r;
		row2 = 0;
	}
	gran_row(int r1, int r2)
	{
		row1 = r1;
		row2 = r2;
	}
};
class ExcelArchiveGran : public BaseExcel  
{
	long rows_per_page;
	long cols_per_page;
	char first_letter;

    int npar;
	long id_params[9];
	long param_rows[9];

	void FillGranRowsMap(map<long, gran_row> & gran_rows);
	void FillSetGran(map<long, gran_row> & gran_rows, SetGranular & setGranular, int & n, int & fr, char & letter, int & p);
	void FillProbGrKT(long ID_OBJ, long ID_KT, long ID_PROB, int & n, int & fr, char & letter);
	void FillIncrement(int & n, int & fr, char & letter);


	virtual bool virCompute(bool = false){return true;}
	virtual bool virFill();
	virtual void virSaveToDB();
	virtual void InitExt();
public:
	bool m_to_fill_all_lab_numbers;
	void UpdateSaveToDB(CCmdUI* pCmdUI) 
	{
		pCmdUI->Enable(this->m_excel.IsApplicationDispatch());	
	}
	ExcelArchiveGran();
	virtual ~ExcelArchiveGran();

};

#endif // !defined(AFX_ARCHIVEGRANEXCEL_H__B8506374_5686_4911_8320_9E644B75483D__INCLUDED_)
