// MySurfer.cpp: implementation of the MySurfer class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"

#include "MySurfer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MySurfer::MySurfer()
{

}

MySurfer::~MySurfer()
{
	SurferOleRelease();
}

bool MySurfer::alert = true; 
bool MySurfer::skip_next_alert = false; 

bool MySurfer::SurferOleLoad()
{
	TRACE("Entering MySurfer::SurferOleLoad()\n");
	CLSID clsid;
	//  BeginWaitCursor();
	//  from registry	
	if (::CLSIDFromProgID(OLESTR("Surfer.Application"), &clsid) != NOERROR)
	{
		if (MySurfer::alert) AfxMessageBox("Surfer.Application not found in registry");
		if (MySurfer::skip_next_alert) MySurfer::alert = false;
		return false;// FALSE;
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

	got_active_Surfer_window = false;
	if (GetActiveObject(clsid, NULL, &pUnk) == NOERROR)
	{
		HRESULT hr = pUnk->QueryInterface(IID_IDispatch,
			(LPVOID*)&pApp);
		pUnk->Release();
		if (hr == NOERROR)
		{
			TRACE("hr == NOERROR\n");
			m_app.AttachDispatch(pApp);
			got_active_Surfer_window = true;
		}
		else
		{
			TRACE("hr != NOERROR\n");
		}
	}
	else
	{
		TRACE("GetActiveObject(clsid, NULL, &pUnk) != NOERROR\n");
	}
		
	
	TRACE("m_app.m_lpDispatch = %x\n", m_app.m_lpDispatch);


	COleException e;
	// if not dispatch ptr attached yet, need to create one
	if (m_app.m_lpDispatch == NULL &&
		!m_app.CreateDispatch(clsid, &e))
	{
		TRACE("!m_app.CreateDispatch(clsid, &e)\n");

		if(!m_app.CreateDispatch("Surfer.Application")) 
		{
			if (MySurfer::alert) AfxMessageBox("Surfer program not found");
			if (MySurfer::skip_next_alert) MySurfer::alert = false;
			return false;// FALSE;
		}
		//		AfxMessageBox(IDP_UNABLE_TO_CREATE);
//		EndDialog(IDABORT);
	}

	//m_app.SetVisible(TRUE);

	//   EndWaitCursor();	
	return true;
}

BOOL CALLBACK EnumSurferWndProc( HWND hWnd, LPARAM lParam );

class Surfer_searcher
{
public:
	HWND found;	
	void Find()
	{
		found = NULL;
		EnumDesktopWindows(NULL, (WNDENUMPROC)EnumSurferWndProc, (LPARAM) this );	
	}
};
BOOL CALLBACK EnumSurferWndProc( HWND hWnd, LPARAM lParam )
{
	static char szWindowName[9];
    // Получить имя окна
    //...................................
    GetWindowText( hWnd, szWindowName, 7 );
	if (!strncmp(szWindowName, "Surfer", 6))
	{
		Surfer_searcher * as = reinterpret_cast<Surfer_searcher *>(lParam);
		if (as)
		{
			as->found = hWnd;
		}
		return FALSE;
	}
    return TRUE;
}
void MySurfer::SurferOleExecute(const char * file)
{
	Surfer_searcher as;
	as.Find();
	if (as.found)
	{
		TRACE("Surfer window found\n");
		ShowWindow(as.found, SW_SHOWNORMAL);
		UpdateWindow(as.found);
		BringWindowToTop(as.found);
	}
	else
	{
		TRACE("Surfer window not found\n");	
	}
    
	LPDISPATCH pDocuments;

	VERIFY(pDocuments = m_app.GetDocuments());
	m_documents.AttachDispatch(pDocuments);

	LPDISPATCH pDocument;	
	if (file)
	{
		if (pDocument = m_documents.Open(file, ""))
			m_document.AttachDispatch(pDocument);
	}
	else
	{
		bool to_add_doc =  true;
		if (got_active_Surfer_window)
			to_add_doc = true;

		if (to_add_doc)
		{
			if (pDocument = m_documents.Add(1))
				m_document.AttachDispatch(pDocument);
		}
		else
		{
			if (pDocument = m_app.GetActiveDocument())
				m_document.AttachDispatch(pDocument);
		}
	}


//	LPDISPATCH pWorkbook = NULL;
	
	// Add returns a Workbook pointer, but we
	//  don't have a Workbook class
	// pWorkbook = m_workbooks.Add(); // Save the pointer for
/*	VARIANT a_template = m_workbooks.Open(COleVariant(file)); // Save the pointer for
	pWorkbook = m_workbooks.Add(a_template);

	
	LPDISPATCH pWorksheets = m_app.GetWorksheets();
	ASSERT(pWorksheets != NULL);
	m_worksheets.AttachDispatch(pWorksheets);	

	LPDISPATCH pWorksheet = m_worksheets.GetItem(COleVariant((short) 1));
	
	m_worksheet.AttachDispatch(pWorksheet);
	m_worksheet.Select();
	
	if (pWorkbook != NULL)
	{
		m_workbook.AttachDispatch(pWorkbook);
	}*/	
}

bool MySurfer::IsApplicationDispatch()
{
	return m_app.m_lpDispatch != NULL;
}

void MySurfer::SurferOleRelease()
{	
	/*for (int i = 0; i < 5; i++)
	{
		this->m_range[i].ReleaseDispatch();
	}*/

//	m_worksheet.ReleaseDispatch();
//	m_worksheets.ReleaseDispatch();

	m_document.ReleaseDispatch();
	m_documents.ReleaseDispatch();

	//m_app.Quit();
	m_app.ReleaseDispatch();
}
