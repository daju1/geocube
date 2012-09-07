// ExcelArchiveData.h: interface for the ExcelPlotnostChastic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARCHIVECASPGEOEXCEL_H__B8506374_5686_4911_8320_9E644B75483D__INCLUDED_)
#define AFX_ARCHIVECASPGEOEXCEL_H__B8506374_5686_4911_8320_9E644B75483D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseExcel.h"

class ExcelArchiveCaspGeo : public BaseExcel  
{

    int npar;
	size_t letter_cols[9];
	long id_params[9];

	int ngran;
	size_t letter_cols_grans[11];
	long id_grans[11];

	char first_letter;

	virtual bool virCompute(bool = false){return true;}
	virtual bool virFill();
	virtual void virSaveToDB();
	virtual void InitExt();
public:
	void UpdateSaveToDB(CCmdUI* pCmdUI) 
	{
		pCmdUI->Enable(this->m_excel.IsApplicationDispatch());	
	}
	ExcelArchiveCaspGeo();
	virtual ~ExcelArchiveCaspGeo();

};

#endif // !defined(AFX_ARCHIVECASPGEOEXCEL_H__B8506374_5686_4911_8320_9E644B75483D__INCLUDED_)
