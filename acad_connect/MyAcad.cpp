// MyAcad.cpp: implementation of the MyAcad class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"

#include "MyAcad.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MyAcad::MyAcad()
{

}

MyAcad::~MyAcad()
{
	AcadOleRelease();
}
void MyAcad::AcadOleLoad()
{
	TRACE("Entering MyAcad::AcadOleLoad()\n");
	CLSID clsid;
	//  BeginWaitCursor();
	//  from registry	
	if (::CLSIDFromProgID(OLESTR("AutoCAD.Application"), &clsid) != NOERROR)
	{
		AfxMessageBox("AutoCAD.Application not found in registry");
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

	got_active_acad_window = false;
	if (GetActiveObject(clsid, NULL, &pUnk) == NOERROR)
	{
		HRESULT hr = pUnk->QueryInterface(IID_IDispatch,
			(LPVOID*)&pApp);
		pUnk->Release();
		if (hr == NOERROR)
		{
			TRACE("hr == NOERROR\n");
			m_app.AttachDispatch(pApp);
			got_active_acad_window = true;
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

		if(!m_app.CreateDispatch("AutoCAD.Application")) 
		{
			AfxMessageBox("Acad program not found");
			return;// FALSE;
		}
		//		AfxMessageBox(IDP_UNABLE_TO_CREATE);
//		EndDialog(IDABORT);
	}

	m_app.SetVisible(TRUE);

	//   EndWaitCursor();	
}

BOOL CALLBACK EnumAcadWndProc( HWND hWnd, LPARAM lParam );

class AutoCAD_searcher
{
public:
	HWND found;	
	void Find()
	{
		found = NULL;
		EnumDesktopWindows(NULL, (WNDENUMPROC)EnumAcadWndProc, (LPARAM) this );	
	}
};
BOOL CALLBACK EnumAcadWndProc( HWND hWnd, LPARAM lParam )
{
	static char szWindowName[9];
    // Получить имя окна
    //...................................
    GetWindowText( hWnd, szWindowName, 8 );
	if (!strncmp(szWindowName, "AutoCAD", 7))
	{
		AutoCAD_searcher * as = reinterpret_cast<AutoCAD_searcher *>(lParam);
		if (as)
		{
			as->found = hWnd;
		}
		return FALSE;
	}
    return TRUE;
}
void MyAcad::AcadOleExecute(const char * file)
{
	AutoCAD_searcher as;
	as.Find();
	if (as.found)
	{
		TRACE("Acad window found\n");
		ShowWindow(as.found, SW_SHOWNORMAL);
		UpdateWindow(as.found);
		BringWindowToTop(as.found);
	}
	else
	{
		TRACE("Acad window not found\n");	
	}
    
	LPDISPATCH pDocuments;

	VERIFY(pDocuments = m_app.GetDocuments());
	m_documents.AttachDispatch(pDocuments);

	LPDISPATCH pDocument;	
	if (file)
	{
		if (pDocument = m_documents.Open(file, COleVariant(long(0))))
			m_document.AttachDispatch(pDocument);
	}
	else
	{
		bool to_add_doc = false;
		if (got_active_acad_window)
			to_add_doc = true;

		if (to_add_doc)
		{
			if (pDocument = m_documents.Add(COleVariant("")))
				m_document.AttachDispatch(pDocument);
		}
		else
		{
			if (pDocument = m_app.GetActiveDocument())
				m_document.AttachDispatch(pDocument);
		}
	}

	m_document.SendCommand("");

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

	LPDISPATCH pLayers = m_document.GetLayers(); 
	if(pLayers)
	{
		VERIFY(pLayers);				
		m_layers.AttachDispatch(pLayers);		
	}
	LPDISPATCH pModelSpace = m_document.GetModelSpace(); 
	if(pModelSpace)
	{
		VERIFY(pModelSpace);		
		m_model_space.AttachDispatch(pModelSpace);
	}

	LPDISPATCH pPaperSpace = m_document.GetPaperSpace(); 
	if(pPaperSpace)
	{
		VERIFY(pPaperSpace);
		m_paper_space.AttachDispatch(pPaperSpace);		
	}

	LPDISPATCH pLayouts = m_document.GetLayouts();
	if (pLayouts)
	{
		VERIFY(pLayouts);
		m_layouts.AttachDispatch(pLayouts);
	}

	LPDISPATCH pDatabase = m_document.GetDatabase();
	if (pDatabase)
	{
		VERIFY(pDatabase);
		m_database.AttachDispatch(pDatabase);
	}

	LPDISPATCH pViewports = m_database.GetViewports();
	if (pViewports)
	{
		VERIFY(pViewports);
		m_viewports.AttachDispatch(pViewports);
	}


}

bool MyAcad::IsApplicationDispatch()
{
	return m_app.m_lpDispatch != NULL;
}

void MyAcad::AcadOleRelease()
{	
	m_viewports.ReleaseDispatch();
	m_database.ReleaseDispatch();
	m_layouts.ReleaseDispatch();
	m_paper_space.ReleaseDispatch();
	m_model_space.ReleaseDispatch();
	m_layers.ReleaseDispatch();	
	m_document.ReleaseDispatch();
	m_documents.ReleaseDispatch();
	m_app.ReleaseDispatch();
}
