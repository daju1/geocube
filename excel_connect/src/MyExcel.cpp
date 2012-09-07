// MyExcel.cpp: implementation of the MyExcel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyExcel.h"

void DeleteEndZeros(wchar_t * str)
{
	if (wcschr(str, '.'))
	{
		while (str[wcslen(str)-1] == '0')
			str[wcslen(str)-1] = '\0';
		if (str[wcslen(str)-1] == '.')
			str[wcslen(str)-1] = '\0';
	}
}

void DeleteEndZeros(char * str)
{
	if (strchr(str, '.'))
	{
		while (str[strlen(str)-1] == '0')
			str[strlen(str)-1] = '\0';
		if (str[strlen(str)-1] == '.')
			str[strlen(str)-1] = '\0';
	}
}

void DeleteEndZeros(CString & str)
{
	DeleteEndZeros(str.GetBuffer(str.GetLength()));
}

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
bool ExcelRange_GetValue(MyExcel & m_excel, const char * S, double & val)
{
	LPDISPATCH pRange; 
	Range10    m_range;

	VARIANT var_val;
	var_val.vt = VT_EMPTY;
	try
	{
		VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
		m_range.AttachDispatch(pRange);	
		var_val = m_range.GetValue();
		m_range.ReleaseDispatch();	
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();

		return false;
	}


	//val = 0.0;
	if (var_val.vt == VT_R8)
	{
		val = var_val.dblVal;
		return true;
	}
	else
	{
		if (var_val.vt != VT_EMPTY)
		{
			CString str;
			CString s = "";
			if (var_val.vt == VT_BSTR)
			{
				s = var_val.bstrVal;

				str.Format("Внимание в ячейке %s содержится нечисловое значение %s!!!\n",
					S, s);

				int n_points = 0;
				int i_point = -1;
				int i_comma = -1;
				bool may_convert = true;
				for (int i = 0; i < s.GetLength(); i++)
				{
					if (s.Mid(i,1).FindOneOf("0123456789") > -1)
					{
					} 
					else if (s.Mid(i,1).FindOneOf(",") > -1)
					{
						i_comma = i;
						n_points ++;
					} 
					else if (s.Mid(i,1).FindOneOf(".") > -1)
					{
						i_point = i;
						n_points ++;
					}
					else
					{
						may_convert = false;
					}
				}
				if (n_points > 1)
					may_convert = false;

				if (may_convert)
				{
					str += "Преобразовать в число?";
					if (IDYES == AfxMessageBox(str, MB_YESNO))
					{
						CString s2;
						if (i_comma > -1)
						{
							s2 = s.Mid(0, i_comma) + "." + s.Mid(i_comma+1);
						}
						else
						{
							s2 = s;
						}
						val = atof(s2);

						str.Format("Преобразовано в %f", val);
						DeleteEndZeros(str);

						AfxMessageBox(str);

						return true;
					}
				}
				else
				{
					AfxMessageBox(str);
				}
			}
			else
			{
				str.Format("Внимание в ячейке %s содержится нечисловое значение vt = %d!!!\n",
					S, var_val.vt);
				AfxMessageBox(str);
			}
		}

		return false;
	}
}
bool ExcelRange_GetDateValue(MyExcel & m_excel, const char * S, CTime & time)
{
	LPDISPATCH pRange; 
	Range10    m_range;

	VARIANT var_val;
	try
	{
		VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
		m_range.AttachDispatch(pRange);	
		var_val = m_range.GetValue();
		m_range.ReleaseDispatch();	
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();

		return false;
	}



	bool result = false;
	if (var_val.vt == VT_DATE)
	{
		COleDateTime ole_time = var_val;
		SYSTEMTIME st;ole_time.GetAsSystemTime(st);
		CTime t(st);
		time = t;
		result = true;
	}			


	return result;

}			



bool ExcelRange_GetStringValue(MyExcel & m_excel, const char * S, CString & str)
{
	LPDISPATCH pRange; 
	Range10    m_range;

	VARIANT var_val;
	try
	{
		VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
		m_range.AttachDispatch(pRange);	
		var_val = m_range.GetValue();
		m_range.ReleaseDispatch();	
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();

		return false;
	}



	bool result = false;
	if (var_val.vt == VT_R8)
	{
		double val = var_val.dblVal;
		str.Format("%f", val);
		DeleteEndZeros(str);
		result = true;
	}			
	else if (var_val.vt == VT_BSTR)
	{
		str = var_val.bstrVal;
		result = true;
	}

	return result;

}			



void ExcelRange_SetValue(MyExcel & m_excel, const char * S, VARIANT var, bool border)
{
	LPDISPATCH pRange; 
	Range10    m_range;

	try
	{
		VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
		m_range.AttachDispatch(pRange);			   
		m_range.SetValue(var);
		if (border)
			m_range.BorderAround(COleVariant(long(1)), 2, -4105);
		m_range.ReleaseDispatch();	
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();
	}
}

void ExcelRange_Delete_xlUp(MyExcel & m_excel, const char * S)
{
	LPDISPATCH pRange; 
	Range10    m_range;

	try
	{
		VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
		m_range.AttachDispatch(pRange);			   
		m_range.Delete(COleVariant(long(-4162)));//xlUp = -4162
		m_range.ReleaseDispatch();	
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();
	}
}
void ExcelRange_CenterVerticalAlignment(MyExcel & m_excel, const char * S)
{
	LPDISPATCH pRange; 
	Range10    m_range;

	try
	{
		VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
		m_range.AttachDispatch(pRange);			   
		m_range.SetVerticalAlignment(COleVariant(long(-4108)));//xlCenter '-4108 xlBottom '-4107
		m_range.ReleaseDispatch();	
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();
	}
}

void ExcelRange_LeftHorizontalAlignment(MyExcel & m_excel, const char * S)
{
	LPDISPATCH pRange; 
	Range10    m_range;
/*
Const xlCenter = -4108 (&HFFFFEFF4)
Const xlLeft = -4131 (&HFFFFEFDD)
Const xlRight = -4152 (&HFFFFEFC8)
*/
	try
	{
		VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
		m_range.AttachDispatch(pRange);			   
		m_range.SetHorizontalAlignment(COleVariant(long(-4131)));//xlCenter '-4108 xlBottom '-4107
		m_range.ReleaseDispatch();	
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();
	}
}

void ExcelRange_RightHorizontalAlignment(MyExcel & m_excel, const char * S)
{
	LPDISPATCH pRange; 
	Range10    m_range;
/*
Const xlCenter = -4108 (&HFFFFEFF4)
Const xlLeft = -4131 (&HFFFFEFDD)
Const xlRight = -4152 (&HFFFFEFC8)
*/
	try
	{
		VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
		m_range.AttachDispatch(pRange);			   
		m_range.SetHorizontalAlignment(COleVariant(long(-4152)));//xlCenter '-4108 xlBottom '-4107
		m_range.ReleaseDispatch();	
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();
	}
}

void ExcelRange_CenterHorizontalAlignment(MyExcel & m_excel, const char * S)
{
	LPDISPATCH pRange; 
	Range10    m_range;

	try
	{
		VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
		m_range.AttachDispatch(pRange);			   
		m_range.SetHorizontalAlignment(COleVariant(long(-4108)));//xlCenter '-4108 xlBottom '-4107
		m_range.ReleaseDispatch();	
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();
	}
}

void ExcelRange_WrapText(MyExcel & m_excel, const char * S)
{
	LPDISPATCH pRange; 
	Range10    m_range;

	try
	{
		VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
		m_range.AttachDispatch(pRange);			   
		m_range.SetWrapText(COleVariant(long(TRUE)));
		m_range.ReleaseDispatch();	
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();
	}
}

bool ExcelRange_SetNumberFormat(MyExcel & m_excel, const char * S, const char * Format, bool msg_if_catch)
{
	bool result = false;

	LPDISPATCH pRange; 
	Range10    m_range;

	try
	{
		VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
		m_range.AttachDispatch(pRange);	
		try
		{
			m_range.SetNumberFormat(COleVariant(Format));
			result = true;
		}
		catch (CException* pe)
		{
			// catch errors from WinINet 
			TCHAR szErr[4098]; 
			pe->GetErrorMessage(szErr, 4098); 
			if (msg_if_catch)
				AfxMessageBox(szErr);
			pe->Delete();
			result = false;
		}
		m_range.ReleaseDispatch();	
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		if (msg_if_catch)
			AfxMessageBox(szErr);
		pe->Delete();
		result = false;

	}
	return result;
}

bool ExcelRange_GetMergeCells(MyExcel & m_excel, const char * S)
{
	LPDISPATCH pRange; 
	Range10    m_range;
	VARIANT var_is_merged;

	try
	{
		VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
		m_range.AttachDispatch(pRange);			   
		var_is_merged = m_range.GetMergeCells();
		m_range.ReleaseDispatch();	
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();

		return false;
	}

	if(var_is_merged.vt == VT_BOOL)
	{
		return bool(var_is_merged.boolVal);			
	}
	return false;
}
CString ExcelRange_GetMergeArea(MyExcel & m_excel, const char * S, bool use_xlR1C1_style )
{
	LPDISPATCH pRange; 
	Range10    m_range;
	VARIANT var_is_merged;

	try
	{
		VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
		m_range.AttachDispatch(pRange);			   
		var_is_merged = m_range.GetMergeCells();
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();

		m_range.ReleaseDispatch();
		return "";
	}
	LPDISPATCH pRange2; 
	Range10    m_range2;
	CString adress = "";

	try
	{
		VERIFY(pRange2 = m_range.GetMergeArea());
		m_range2.AttachDispatch(pRange2);	

		//ReferenceStyle:=xlR1C1  = -4150
		//ReferenceStyle:=xlA1 = 1
		
		long ReferenceStyle = 1; //default 
		if (use_xlR1C1_style)
			ReferenceStyle = -4150;

		//adress = m_range2.GetAddress();// default ReferenceStyle:=xlA1 = 1
		//adress = m_range2.GetAddress(ReferenceStyle);// Эта функция перегружена с нарушением порядка параметров
		adress = m_range2.GetAddress(COleVariant(long(TRUE)), COleVariant(long(TRUE)), ReferenceStyle);

		m_range2.ReleaseDispatch();	
		m_range.ReleaseDispatch();
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();
	}

	return adress;
}
bool ExcelRange_GetMergeArea_and_parse_adress(MyExcel & m_excel, const char * S,
												 CString & letter1, int & row1,
												 CString & letter2, int & row2)
{
	bool is_merged = ExcelRange_GetMergeCells(m_excel, S);
	if (is_merged)
	{
		bool use_xlR1C1_style = false;
		CString adress = ExcelRange_GetMergeArea(m_excel, S, use_xlR1C1_style);
		
		int i2p = adress.Find(':');

		CString left = adress.Mid(1, i2p-1);
		int ils = left.Find('$');
		CString left_letter = left.Left(ils);
		CString left_row = left.Mid(ils+1);
		letter1 = left_letter;
		row1 = atoi(left_row);

		CString right = adress.Mid(i2p+1+1);
		int irs = right.Find('$');
		CString right_letter = right.Left(irs);
		CString right_row = right.Mid(irs+1);
		letter2 = right_letter;
		row2 = atoi(right_row);

		return true;
	}
	return false;
}

bool ExcelRange_GetMergeArea_and_parse_adress(MyExcel & m_excel, const char * S,
											  int & row1, int & col1,
											  int & row2, int & col2)
{
	bool is_merged = ExcelRange_GetMergeCells(m_excel, S);
	if (is_merged)
	{
		bool use_xlR1C1_style = true;
		CString adress = ExcelRange_GetMergeArea(m_excel, S, use_xlR1C1_style);
		
		//"R3C6:R3C7"
		
		int i2p = adress.Find(':');

		CString left = adress.Mid(1, i2p-1);
		int ils = left.Find('C');
		CString left_row = left.Left(ils);
		CString left_col = left.Mid(ils+1);
		row1 = atoi(left_row);
		col1 = atoi(left_col);

		CString right = adress.Mid(i2p+1+1);
		int irs = right.Find('C');
		CString right_row = right.Left(irs);
		CString right_col = right.Mid(irs+1);
		row2 = atoi(right_row);
		col2 = atoi(right_col);

		return true;
	}
	return false;
}
void ExcelRange_SetMerge(MyExcel & m_excel, const char * S1, const char * S2, bool Across)
{
	// Across   Optional Variant. 
	// True to merge cells in each row of the specified range as separate merged cells. 
	// The default value is False.

	LPDISPATCH pRange; 
	Range10    m_range;

	try
	{
		VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S1), COleVariant(S2)));
		m_range.AttachDispatch(pRange);			   
		m_range.Merge(COleVariant(long(Across)));
		m_range.ReleaseDispatch();
	}
	catch (COleDispatchException* pe)//
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();
	}
	catch (CException* pe)//COleDispatchException
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();
	}
}

void ExcelRange_SetMerge(MyExcel & m_excel, const char * S, bool Across)
{
	// Across   Optional Variant. 
	// True to merge cells in each row of the specified range as separate merged cells. 
	// The default value is False.

	LPDISPATCH pRange; 
	Range10    m_range;

	try
	{
		VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
		m_range.AttachDispatch(pRange);			   
		m_range.Merge(COleVariant(long(Across)));
		m_range.ReleaseDispatch();
	}
	catch (COleDispatchException* pe)//
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();
	}
	catch (CException* pe)//COleDispatchException
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();
	}
}

void ExcelRange_SetThinContinuousBorders(MyExcel & m_excel, const char * S)
{
	LPDISPATCH pRange; 
	Range10    m_range;

	LPDISPATCH pBorder; 
	Borders11  m_borders;

	try
	{
		VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
		m_range.AttachDispatch(pRange);			   

		VERIFY(pBorder = m_range.GetBorders());
		m_borders.AttachDispatch(pBorder);	

		m_borders.SetLineStyle(COleVariant(long(1)));//xlContinuous
		m_borders.SetWeight(COleVariant(long(2)));//xlThin
		m_borders.SetColorIndex(COleVariant(long(-4105)));//xlAutomatic
		
		m_borders.ReleaseDispatch();	
		m_range.ReleaseDispatch();
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();
	}

}
void ExcelRange_SetBold(MyExcel & m_excel, const char * S)
{
	LPDISPATCH pRange; 
	Range10    m_range;
	LPDISPATCH pFont; 
	Font  m_font;

	try
	{
		VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
		m_range.AttachDispatch(pRange);			   
		VERIFY(pFont = m_range.GetFont());
		m_font.AttachDispatch(pFont);

		m_font.SetBold(COleVariant(long(TRUE)));
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();
	}
	m_font.ReleaseDispatch();	
	m_range.ReleaseDispatch();	
}
void ExcelRange_SetFont(MyExcel & m_excel, const char * S, LOGFONT * logfont, COLORREF color)
{
	LPDISPATCH pRange; 
	Range10    m_range;
	LPDISPATCH pFont; 
	Font  m_font;

	try
	{
		VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
		m_range.AttachDispatch(pRange);			   
		VERIFY(pFont = m_range.GetFont());
		m_font.AttachDispatch(pFont);

		

		if (logfont->lfItalic)
			m_font.SetItalic(COleVariant(long(TRUE)));
		if (logfont->lfWeight > 200)
			m_font.SetBold(COleVariant(long(TRUE)));
		if (logfont->lfUnderline)
			m_font.SetUnderline(COleVariant(long(TRUE)));


		//m_font.SetSize(COleVariant(long(logfont->lfHeight)));
		m_font.SetColor(COleVariant(long(color)));
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();
	}
	m_font.ReleaseDispatch();	
	m_range.ReleaseDispatch();	
}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MyExcel::MyExcel()
{
	got_active_object = false;
}

MyExcel::~MyExcel()
{
	ExcelOleRelease();

}

BOOL CALLBACK EnumThreadProc( HWND hWnd, LPARAM lParam )
{
	static char szWindowName[31];
    GetWindowText( hWnd, (LPTSTR)szWindowName, 30 );
    //MessageBox( hWnd, (LPTSTR)szWindowName, "Window Name", MB_OK );

	if (strncmp("lab", szWindowName, 3) == 0)
	{
		RECT rc;
		SystemParametersInfo(SPI_GETWORKAREA, 0, &rc, 0); 
		SetWindowPos(hWnd, HWND_NOTOPMOST, rc.left, rc.top, rc.right - rc.left, (rc.bottom - rc.top)/2, SWP_SHOWWINDOW);

		return (FALSE);
	}

    return( TRUE );
}
double MyExcel::w = 0.0;
double MyExcel::h = 0.0;
void MyExcel::ExcelOleLoad()
{
	got_active_object = false;
	TRACE("Entering MyExcel::ExcelOleLoad()\n");
	CLSID clsid;
	//  BeginWaitCursor();
	//::CLSIDFromProgID(L"Excel.Application", &clsid); // from registry
	
	if (::CLSIDFromProgID(OLESTR("Excel.Application"), &clsid) != NOERROR)
	{
		///AfxMessageBox(IDP_UNABLE_TO_CREATE);
		//EndDialog(IDABORT);
		return;// FALSE;
	}
	
	TRACE ("%u-%u-%u-%u%u%u%u%u%u%u%u\n", 
		clsid.Data1, clsid.Data2, clsid.Data3, 
		clsid.Data4[0], 
		clsid.Data4[1], 
		clsid.Data4[2], 
		clsid.Data4[3], 
		clsid.Data4[4], 
		clsid.Data4[5], 
		clsid.Data4[6], 
		clsid.Data4[7]); 
	
	LPDISPATCH pApp;
	LPUNKNOWN pUnk;

	if (GetActiveObject(clsid, NULL, &pUnk) == NOERROR)
	{
		HRESULT hr = pUnk->QueryInterface(IID_IDispatch,
			(LPVOID*)&pApp);
		pUnk->Release();
		if (hr == NOERROR)
		{
			TRACE("hr == NOERROR\n");
			m_app.AttachDispatch(pApp);
			got_active_object = true;
		}
		else
		{
			TRACE("hr != NOERROR\n");
		}
	}
	else
		TRACE("GetActiveObject(clsid, NULL, &pUnk) != NOERROR\n");
		
	
	TRACE("m_app.m_lpDispatch = %x\n", m_app.m_lpDispatch);


	COleException e;
	// if not dispatch ptr attached yet, need to create one
	if (m_app.m_lpDispatch == NULL &&
		!m_app.CreateDispatch(clsid, &e))
	{
		TRACE("!m_app.CreateDispatch(clsid, &e)\n");

		if(!m_app.CreateDispatch("Excel.Application")) 
		{
			AfxMessageBox("Excel program not found");
			return;// FALSE;
		}
		//		AfxMessageBox(IDP_UNABLE_TO_CREATE);
//		EndDialog(IDABORT);
	}
	
	DWORD dwAppThreadID = GetCurrentThreadId();
	EnumThreadWindows( dwAppThreadID,
		(WNDENUMPROC)EnumThreadProc,
		(LPARAM)(LPTSTR)0 );

	if (int (MyExcel::h) == 0 || int (MyExcel::w) == 0)
	{
		m_app.SetVisible(FALSE);
		m_app.SetWindowState(SW_SHOWMAXIMIZED);//xlMaximized
		MyExcel::w = m_app.GetWidth();
		MyExcel::h = m_app.GetHeight();
	}

	m_app.SetWindowState(SW_SHOWNORMAL);//xlNormal

	m_app.SetLeft(0);
	m_app.SetTop(0.5*MyExcel::h);
	m_app.SetWidth(w);
	m_app.SetHeight(0.5*MyExcel::h);

	m_app.SetVisible(TRUE);

	//   EndWaitCursor();	
}
#if 0
void MyExcel::ExcelOleExecute()
{
   LPDISPATCH pRange, pWorkbooks;
    
   CWnd* pWnd = CWnd::FindWindow("XLMAIN", NULL);
   if (pWnd != NULL) {
     TRACE("Excel window found\n");
     pWnd->ShowWindow(SW_SHOWNORMAL);
     pWnd->UpdateWindow();
     pWnd->BringWindowToTop();
   }
   else
     TRACE("Excel window not found\n");

#if USE_EXCEL_10
	m_app.SetSheetsInNewWorkbook((long) 1);
#else
#if USE_EXCEL_8
	m_app.SetSheetsInNewWorkbook(1);
#else
	m_app.SetSheetsInNewWorkbook(COleVariant((long) 1));
#endif
#endif
   
   VERIFY(pWorkbooks = m_app.GetWorkbooks());
   m_workbooks.AttachDispatch(pWorkbooks);

   LPDISPATCH pWorkbook = NULL;
   /*
#if USE_EXCEL_10
  if (m_workbooks.GetCount() == 0) 
#else
#if USE_EXCEL_8
  if (m_workbooks.GetCount() == 0) 
#else
   if (m_workbooks.GetCountLong() == 0) 
#endif
#endif*/
   {
      // Add returns a Workbook pointer, but we
      //  don't have a Workbook class
      pWorkbook = m_workbooks.Add(); // Save the pointer for
                                     //  later release
	   if (pWorkbook != NULL)
	   {
		   m_workbook.AttachDispatch(pWorkbook);
	   }
   
   }
   LPDISPATCH pWorksheets = m_app.GetWorksheets();
   ASSERT(pWorksheets != NULL);
   m_worksheets.AttachDispatch(pWorksheets);
   LPDISPATCH pWorksheet = m_worksheets.GetItem(COleVariant((short) 1));

   m_worksheet.AttachDispatch(pWorksheet);
   m_worksheet.Select();

   VERIFY(pRange = m_worksheet.GetRange(COleVariant("A1")));
   m_range[0].AttachDispatch(pRange);

   VERIFY(pRange = m_worksheet.GetRange(COleVariant("A2")));
   m_range[1].AttachDispatch(pRange);
   
   VERIFY(pRange = m_worksheet.GetRange(COleVariant("A3")));
   m_range[2].AttachDispatch(pRange);

   VERIFY(pRange = m_worksheet.GetRange(COleVariant("A3"), 
	   COleVariant("C5")));
   m_range[3].AttachDispatch(pRange);

   VERIFY(pRange = m_worksheet.GetRange(COleVariant("A6")));
   m_range[4].AttachDispatch(pRange);
   
   m_range[4].SetValue(COleVariant(COleDateTime(1998, 4, 24, 15, 47, 8)));
   // retrieve the stored date and print it as a string
   COleVariant vaTimeDate = m_range[4].GetValue();
   TRACE("returned date type = %d\n", vaTimeDate.vt);
   COleVariant vaTemp;
   vaTemp.ChangeType(VT_BSTR, &vaTimeDate);
   CString str = vaTemp.bstrVal;
   TRACE("date = %s\n", (const char*) str);

   m_range[0].SetValue(COleVariant("test string"));
   
   COleVariant vaResult0 = m_range[0].GetValue();
   if (vaResult0.vt == VT_BSTR) {
     CString str = vaResult0.bstrVal;
     TRACE("vaResult0 = %s\n", (const char*) str);
   }

   m_range[1].SetValue(COleVariant(3.14159));
   
   COleVariant vaResult1 = m_range[1].GetValue();
   if (vaResult1.vt == VT_R8) {
     TRACE("vaResult1 = %f\n", vaResult1.dblVal);
   }
   
   m_range[2].SetFormula(COleVariant("=$A2*2.0"));
   
   COleVariant vaResult2 = m_range[2].GetValue();
   if (vaResult2.vt == VT_R8) {
     TRACE("vaResult2 = %f\n", vaResult2.dblVal);
   }

   COleVariant vaResult2a = m_range[2].GetFormula();
   if (vaResult2a.vt == VT_BSTR) {
     CString str = vaResult2a.bstrVal;
     TRACE("vaResult2a = %s\n", (const char*) str);
   }
   
   m_range[3].FillRight();
   m_range[3].FillDown();

}

#endif

void MyExcel::ExcelOleExecute(const char * file)
{
	LPDISPATCH pRange, pWorkbooks;
	
	CWnd* pWnd = CWnd::FindWindow("XLMAIN", NULL);
	if (pWnd != NULL) {
		TRACE("Excel window found\n");
		pWnd->ShowWindow(SW_SHOWNORMAL);
		pWnd->UpdateWindow();
		pWnd->BringWindowToTop();
	}
	else
		TRACE("Excel window not found\n");

#if USE_EXCEL_10
	m_app.SetSheetsInNewWorkbook(1);
#else
#if USE_EXCEL_8
	m_app.SetSheetsInNewWorkbook(1);
#else
	m_app.SetSheetsInNewWorkbook(COleVariant((long) 1));
#endif
#endif     

	VERIFY(pWorkbooks = m_app.GetWorkbooks());
	m_workbooks.AttachDispatch(pWorkbooks);
	
	LPDISPATCH pWorkbook = NULL;
	
	if (file)
	{
#if USE_EXCEL_10
		pWorkbook = m_workbooks.Open(file); // Save the pointer for
#else
#if USE_EXCEL_8
		pWorkbook = m_workbooks.Open(file); // Save the pointer for
#else
		VARIANT a_template = m_workbooks.Open(COleVariant(file)); // Save the pointer for
		pWorkbook = m_workbooks.Add(a_template);
#endif
#endif
	}
	else
	{
		// Add returns a Workbook pointer, but we
		//  don't have a Workbook class
		pWorkbook = m_workbooks.Add(); // Save the pointer for
	}

	
	LPDISPATCH pWorksheets = m_app.GetWorksheets();
	ASSERT(pWorksheets != NULL);
	m_worksheets.AttachDispatch(pWorksheets);	

	LPDISPATCH pWorksheet = m_worksheets.GetItem(COleVariant((short) 1));
	
	m_worksheet.AttachDispatch(pWorksheet);
	m_worksheet.Select();
	
	if (pWorkbook != NULL)
	{
		m_workbook.AttachDispatch(pWorkbook);
	}	
}
void MyExcel::AddWorkSheet(LPCTSTR name)
{
	m_worksheet.ReleaseDispatch();
	LPDISPATCH pWorksheet = m_worksheets.Add();
	m_worksheet.AttachDispatch(pWorksheet);
	if (name != NULL) m_worksheet.SetName(name);
	m_worksheet.Select();
}
bool MyExcel::IsApplicationDispatch()
{
	return m_app.m_lpDispatch != NULL;
}

void MyExcel::ExcelOleRelease()
{	
	/*for (int i = 0; i < 5; i++)
	{
		this->m_range[i].ReleaseDispatch();
	}*/

	m_worksheet.ReleaseDispatch();
	m_worksheets.ReleaseDispatch();

	m_workbook.ReleaseDispatch();
	m_workbooks.ReleaseDispatch();

	//m_app.Quit();
	m_app.ReleaseDispatch();
}
