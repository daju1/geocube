// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Graphs.h"
#include "GraphsDoc.h"
#include "Wavelet.h"

#include "MainFrm.h"

UINT g_comPortMessage,
	g_comPortErrorMessage;
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

Wavelets g_Wav[8];
extern void WriteRaporto(LPCTSTR s);

/////////////////////////////////////////////////////////////////////////////
// CMainFrame


IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_COMMAND(ID_COM_CONNECT, OnComConnect)
	ON_WM_CREATE()
	ON_UPDATE_COMMAND_UI(ID_COM_CONNECT, OnUpdateComConnect)
	ON_COMMAND(ID_COM_READ, OnComRead)
	ON_UPDATE_COMMAND_UI(ID_COM_READ, OnUpdateComRead)
	ON_COMMAND(ID_COM_DISCONNECT, OnComDisconnect)
	ON_UPDATE_COMMAND_UI(ID_COM_DISCONNECT, OnUpdateComDisconnect)
	ON_COMMAND(ID_COM_SET_FILENAME, OnComSetFilename)
	ON_UPDATE_COMMAND_UI(ID_COM_SET_FILENAME, OnUpdateComSetFilename)
	ON_WM_DESTROY()
	ON_REGISTERED_MESSAGE(g_comPortMessage, OnPumpingMsg)
	ON_REGISTERED_MESSAGE(g_comPortErrorMessage, OnComPortErrorMessage)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, CMDIFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, CMDIFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CMDIFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CMDIFrameWnd::OnHelpFinder)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// событие - "Ready" - сигнальное
	m_bToWriteTextFile = false;	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	g_comPortErrorMessage = ::RegisterWindowMessage(_T("Tezey_Com_Port_Error_Message"));
	g_comPortMessage = ::RegisterWindowMessage(_T("Tezey_Com_Port_Message"));
	m_comPort.SetWindowOwner(this, GetSafeHwnd());


	g_Wav[0].name = "HAAR";
	g_Wav[0].minOrder = 1;
	g_Wav[0].maxOrder = 1;

	g_Wav[1].name = "DAUBECHIES";
	g_Wav[1].minOrder = 1;
	g_Wav[1].maxOrder = 10;

	g_Wav[2].name = "SYMLETS";
	g_Wav[2].minOrder = 1;
	g_Wav[2].maxOrder = 8;

	g_Wav[3].name = "COIFLETS";
	g_Wav[3].minOrder = 1;
	g_Wav[3].maxOrder = 5;

	g_Wav[4].name = "BIORTOGONAL";
	g_Wav[4].minOrder = 1;
	g_Wav[4].maxOrder = 1;

	g_Wav[5].name = "MY_BIORTOGONAL";
	g_Wav[5].minOrder = 1;
	g_Wav[5].maxOrder = 1;

	g_Wav[6].name = "BIORTOGONAL_NONSTANDART";
	g_Wav[6].minOrder = 1;
	g_Wav[6].maxOrder = 1;

	g_Wav[7].name = "DISCRETE_MEYER";
	g_Wav[7].minOrder = 1;
	g_Wav[7].maxOrder = 1;

	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

LRESULT CMainFrame::OnComPortErrorMessage(WPARAM wParam, LPARAM lParam)
{
	if (this->m_bToWriteTextFile)
	{

		CString current_time_str =  CTime::GetCurrentTime().Format("%d:%m:%Y,%H:%M:%S");
		FILE *stream;
		if ((stream = fopen(m_sTextFilePath,"at")) == NULL)
		{
			AfxMessageBox("Cannot open file.\n");
			return 0;
		}
		CString s, err_str;
		m_comPort.m_XYZBuffer.ReadErrorString(err_str);
		s.Format("%s,%s\n",current_time_str, err_str);
		fprintf(stream,s);
		fclose(stream);
	}

	return 0;
}

LRESULT CMainFrame::OnPumpingMsg(WPARAM wParam, LPARAM lParam)
{
WriteRaporto("OnPumpingMsg 1\n");
	DWORD wt = WaitForSingleObject(m_comPort.m_hEventFrameReady, 0);
WriteRaporto("OnPumpingMsg WaitForSingleObject\n");
	if (wt != WAIT_OBJECT_0 || wt == WAIT_TIMEOUT)
	{
WriteRaporto("OnPumpingMsg                       return wt != WAIT_OBJECT_0\n");
		return 0;
	}
	ResetEvent(m_comPort.m_hEventFrameReady);
//	AfxMessageBox("OnPumpingMsg");
//	int x,y,z;
//	CString _time_str;

	XYZ xyz;
	size_t sz = sizeof(XYZ);
	POSITION posDoc;
	CGraphsDoc* pDoc;
	int iDoc;
	int iVal = 0;
	while (!this->m_comPort.m_queue.empty())
	{
WriteRaporto("OnPumpingMsg while\n");
		iVal++;
		if (this->m_comPort.m_queue.Copy(&xyz, sz))
		{
			iDoc = 0;
			posDoc = ((CGraphsApp*)AfxGetApp())->m_pDocTemplate->GetFirstDocPosition();
			while (posDoc !=NULL)
			{
				iDoc++;
				pDoc = (CGraphsDoc*)((CGraphsApp*)AfxGetApp())->m_pDocTemplate->GetNextDoc(posDoc);
				switch (iDoc)
				{
				case 1:
					{
						pDoc->OnTick(xyz.x);
					}
					break;
				case 2:
					{
						pDoc->OnTick(xyz.y);
					}
					break;
				case 3:
					{
						pDoc->OnTick(xyz.z);
					}
					break;
				}
			}
		}
		else
		{
			SetEvent(m_comPort.m_hEventFrameReady);
WriteRaporto("OnPumpingMsg ! Copy\n");
			return 0;
		}
	}
	if (iVal==1)
	{
WriteRaporto("OnPumpingMsg if (iVal==1)\n");
//		Sleep(1000);// имитация долгой обработки

		iDoc = 0;
		posDoc = ((CGraphsApp*)AfxGetApp())->m_pDocTemplate->GetFirstDocPosition();
		while (posDoc !=NULL)
		{
			iDoc++;
			pDoc = (CGraphsDoc*)((CGraphsApp*)AfxGetApp())->m_pDocTemplate->GetNextDoc(posDoc);
			switch (iDoc)
			{
			case 1:
				{
					//pDoc->WaveletApply();
					pDoc->WaveletEpsilonApply();
				}
				break;
			case 2:
				{
					//pDoc->WaveletApply();
					pDoc->WaveletEpsilonApply();
				}
				break;
			case 3:
				{
					//pDoc->WaveletApply();
					pDoc->WaveletEpsilonApply();
				}
				break;
			}
		}
	}	
	SetEvent(m_comPort.m_hEventFrameReady);
WriteRaporto("OnPumpingMsg end\n");
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnComConnect() 
{
	((CGraphsApp*)AfxGetApp())->OnFileNew();
	((CGraphsApp*)AfxGetApp())->OnFileNew();
	POSITION posDoc;
	CGraphsDoc* pDoc;
	
	int iDoc = 0;
	posDoc = ((CGraphsApp*)AfxGetApp())->m_pDocTemplate->GetFirstDocPosition();
	while (posDoc !=NULL)
	{
		iDoc++;
		pDoc = (CGraphsDoc*)((CGraphsApp*)AfxGetApp())->m_pDocTemplate->GetNextDoc(posDoc);
		switch (iDoc)
		{
		case 1:
			{
				pDoc->SetTime();
			}
			break;
		case 2:
			{
				pDoc->SetTime();
			}
			break;
		case 3:
			{
				pDoc->SetTime();
			}
			break;
		}
	}
	if (m_comPort.DoConnect())
		OnComSetFilename();
	
}

void CMainFrame::OnUpdateComConnect(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	// TODO: Add your command update UI handler code here
	
}

void CMainFrame::OnComRead() 
{
	// TODO: Add your command handler code here
	m_comPort.ReadFromCOM();
	
}

void CMainFrame::OnUpdateComRead(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	// TODO: Add your command update UI handler code here
	
}

void CMainFrame::OnComDisconnect() 
{
	// TODO: Add your command handler code here
	m_comPort.CloseConnection();
}

void CMainFrame::OnUpdateComDisconnect(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMainFrame::OnComSetFilename() 
{
	// TODO: Add your command handler code here
	CFileDialog dlg(false);
	CString str, name, ext, path;

	str += "Coma Separated Values (*.csv)";
	str += (TCHAR)NULL;
	str += "*.csv";
	str += (TCHAR)NULL;

	str += "All files (*.*)";
	str += (TCHAR)NULL;
	str += "*.*";
	str += (TCHAR)NULL;

	dlg.m_ofn.lpstrFilter = str;
	dlg.m_ofn.nFilterIndex = 0;
	dlg.m_ofn.lpstrTitle = "Экспорт...";

	if(dlg.DoModal() == IDOK)
	{
		m_sTextFilePath = dlg.GetPathName();
		name = dlg.GetFileName();
		ext = dlg.GetFileExt();
		if (m_sTextFilePath.Find(".") < 0)
		{
			if (dlg.m_ofn.nFilterIndex == 1)
				m_sTextFilePath += ".csv";
		}
		m_bToWriteTextFile = true;
	}
	else
	{
		m_bToWriteTextFile = false;
		//если пользователь выбрал отмена - выходим
		return;
	}

	
}

void CMainFrame::OnUpdateComSetFilename(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here

}

void CMainFrame::OnDestroy() 
{
	CMDIFrameWnd::OnDestroy();

}

void CMainFrame::OnClose() 
{
	if (!m_comPort.m_bTerminatedCOMThread)
	{
		if (IDCANCEL == ::MessageBox(
			NULL,
			"Идёт процесс записи\nВы уверены, что хотите прервать работу программы?", 
			"Завершение работы",
			MB_OKCANCEL))
		{
			return;
		}
	}

	if (m_comPort.m_bIsConnected)
		m_comPort.CloseConnection();
	
	CMDIFrameWnd::OnClose();
}
