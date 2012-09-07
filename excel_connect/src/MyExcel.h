// MyExcel.h: interface for the MyExcel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYEXCEL_H__9699CEDC_80CE_4554_A940_47739A4D99FC__INCLUDED_)
#define AFX_MYEXCEL_H__9699CEDC_80CE_4554_A940_47739A4D99FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define USE_EXCEL_10 1
#define USE_EXCEL_8 1

#if USE_EXCEL_10
#include "excel.h"
#else
#if USE_EXCEL_8
#include "excel8.h"
#else
#include "xl5en32.h"
#endif
#endif

class MyExcel  
{
public:
#if USE_EXCEL_10
   _Application10 m_app;
   Workbooks10   m_workbooks;
   Worksheets10   m_worksheets;
   _Worksheet10   m_worksheet;
   //Range10    m_range[5];
   _Workbook10   m_workbook;


#else

#if USE_EXCEL_8
   _Application m_app;
   Range    m_range[5];
   _Worksheet   m_worksheet;
   Workbooks   m_workbooks;
   Worksheets   m_worksheets;

#else

   _Application5 m_app;
   Workbooks5   m_workbooks;
   Worksheets5   m_worksheets;
   _Worksheet5   m_worksheet;
   Range5    m_range[5];

#endif
#endif

   	bool got_active_object;


public:
	void ExcelOleRelease();
	bool IsApplicationDispatch();
	//void ExcelOleExecute_2();
	//void ExcelOleExecute();
	void ExcelOleExecute(const char * file);
	void ExcelOleLoad();
	MyExcel();
	virtual ~MyExcel();

	void AddWorkSheet(LPCTSTR name);

	static double h,w;

};
bool ExcelRange_GetStringValue(MyExcel & m_excel, const char * S, CString & str);
bool ExcelRange_GetDateValue(MyExcel & m_excel, const char * S, CTime & time);

bool ExcelRange_GetValue(MyExcel & m_excel, const char * S, double & val);
void ExcelRange_SetValue(MyExcel & m_excel, const char * S, VARIANT var, bool border = false);

void ExcelRange_Delete_xlUp(MyExcel & m_excel, const char * S);

bool ExcelRange_GetMergeCells(MyExcel & m_excel, const char * S);
CString ExcelRange_GetMergeArea(MyExcel & m_excel, const char * S, bool use_xlR1C1_style = false);
bool ExcelRange_GetMergeArea_and_parse_adress(MyExcel & m_excel, const char * S,
												 CString & letter1, int & row1,
												 CString & letter2, int & row2);
bool ExcelRange_GetMergeArea_and_parse_adress(MyExcel & m_excel, const char * S,
											  int & row1, int & col1,
											  int & row2, int & col2);
void ExcelRange_SetMerge(MyExcel & m_excel, const char * S, bool Across = false);
void ExcelRange_SetMerge(MyExcel & m_excel, const char * S1, const char * S2, bool Across = false);
void ExcelRange_SetThinContinuousBorders(MyExcel & m_excel, const char * S);

void ExcelRange_CenterVerticalAlignment(MyExcel & m_excel, const char * S);
void ExcelRange_LeftHorizontalAlignment(MyExcel & m_excel, const char * S);
void ExcelRange_RightHorizontalAlignment(MyExcel & m_excel, const char * S);
void ExcelRange_CenterHorizontalAlignment(MyExcel & m_excel, const char * S);
void ExcelRange_WrapText(MyExcel & m_excel, const char * S);

bool ExcelRange_SetNumberFormat(MyExcel & m_excel, const char * S, const char * Format, bool msg_if_catch = true);
void ExcelRange_SetBold(MyExcel & m_excel, const char * S);
void ExcelRange_SetFont(MyExcel & m_excel, const char * S, LOGFONT * logfont, COLORREF color);

#endif // !defined(AFX_MYEXCEL_H__9699CEDC_80CE_4554_A940_47739A4D99FC__INCLUDED_)
