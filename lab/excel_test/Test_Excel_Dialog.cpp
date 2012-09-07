// Test_Excel_Dialog.cpp : implementation file
//

#include "stdafx.h"
#include "excel_test.h"
#include "Test_Excel_Dialog.h"
#include <afxpriv.h>

    // From Mfc\Src\StdAfx.h.
    #ifndef _AFX_OLD_EXCEPTIONS
        #define DELETE_EXCEPTION(e) do { e->Delete(); } while (0)
    #else   //!_AFX_OLD_EXCEPTIONS
        #define DELETE_EXCEPTION(e)
    #endif  //_AFX_OLD_EXCEPTIONS
    // XMN: Includes and defines needed to compile DoModal().

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Test_Excel_Dialog dialog


Test_Excel_Dialog::Test_Excel_Dialog(CWnd* pParent /*=NULL*/)
	: CDialog(Test_Excel_Dialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(Test_Excel_Dialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Test_Excel_Dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Test_Excel_Dialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Test_Excel_Dialog, CDialog)
	//{{AFX_MSG_MAP(Test_Excel_Dialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Test_Excel_Dialog message handlers

void Test_Excel_Dialog::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}



#if 0



BOOL CDialog::Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
{
	ASSERT(IS_INTRESOURCE(lpszTemplateName) ||
		AfxIsValidString(lpszTemplateName));

	m_lpszTemplateName = lpszTemplateName;  // used for help
	if (IS_INTRESOURCE(m_lpszTemplateName) && m_nIDHelp == 0)
		m_nIDHelp = LOWORD((DWORD_PTR)m_lpszTemplateName);

#ifdef _DEBUG
	if (!_AfxCheckDialogTemplate(lpszTemplateName, FALSE))
	{
		ASSERT(FALSE);          // invalid dialog template name
		PostNcDestroy();        // cleanup if Create fails too soon
		return FALSE;
	}
#endif //_DEBUG

	HINSTANCE hInst = AfxFindResourceHandle(lpszTemplateName, RT_DIALOG);
	HRSRC hResource = ::FindResource(hInst, lpszTemplateName, RT_DIALOG);
	HGLOBAL hTemplate = LoadResource(hInst, hResource);
	BOOL bResult = CreateIndirect(hTemplate, pParentWnd, hInst);
	FreeResource(hTemplate);

	return bResult;
}

// for backward compatibility
BOOL CDialog::CreateIndirect(HGLOBAL hDialogTemplate, CWnd* pParentWnd)
{
	return CreateIndirect(hDialogTemplate, pParentWnd, NULL);
}

BOOL CDialog::CreateIndirect(HGLOBAL hDialogTemplate, CWnd* pParentWnd,
	HINSTANCE hInst)
{
	ASSERT(hDialogTemplate != NULL);

	LPCDLGTEMPLATE lpDialogTemplate = (LPCDLGTEMPLATE)LockResource(hDialogTemplate);
	BOOL bResult = CreateIndirect(lpDialogTemplate, pParentWnd, NULL, hInst);
	UnlockResource(hDialogTemplate);

	return bResult;
}

// for backward compatibility
BOOL CDialog::CreateIndirect(LPCDLGTEMPLATE lpDialogTemplate, CWnd* pParentWnd,
	void* lpDialogInit)
{
	return CreateIndirect(lpDialogTemplate, pParentWnd, lpDialogInit, NULL);
}

BOOL CDialog::CreateIndirect(LPCDLGTEMPLATE lpDialogTemplate, CWnd* pParentWnd,
	void* lpDialogInit, HINSTANCE hInst)
{
	ASSERT(lpDialogTemplate != NULL);

	if (pParentWnd == NULL)
		pParentWnd = AfxGetMainWnd();
	m_lpDialogInit = lpDialogInit;

	return CreateDlgIndirect(lpDialogTemplate, pParentWnd, hInst);
}

BOOL CWnd::CreateDlg(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
{
	// load resource
	LPCDLGTEMPLATE lpDialogTemplate = NULL;
	HGLOBAL hDialogTemplate = NULL;
	HINSTANCE hInst = AfxFindResourceHandle(lpszTemplateName, RT_DIALOG);
	HRSRC hResource = ::FindResource(hInst, lpszTemplateName, RT_DIALOG);
	hDialogTemplate = LoadResource(hInst, hResource);
	if (hDialogTemplate != NULL)
		lpDialogTemplate = (LPCDLGTEMPLATE)LockResource(hDialogTemplate);
	ASSERT(lpDialogTemplate != NULL);

	// create a modeless dialog
	BOOL bSuccess = CreateDlgIndirect(lpDialogTemplate, pParentWnd, hInst);

	// free resource
	UnlockResource(hDialogTemplate);
	FreeResource(hDialogTemplate);

	return bSuccess;
}

BOOL CWnd::CreateDlgIndirect(LPCDLGTEMPLATE lpDialogTemplate,
	CWnd* pParentWnd, HINSTANCE hInst)
{
	ASSERT(lpDialogTemplate != NULL);
	if (pParentWnd != NULL)
		ASSERT_VALID(pParentWnd);

	if(!hInst)
		hInst = AfxGetResourceHandle();

#ifndef _AFX_NO_OCC_SUPPORT
	_AFX_OCC_DIALOG_INFO occDialogInfo;
	COccManager* pOccManager = afxOccManager;
#endif

	HGLOBAL hTemplate = NULL;

	HWND hWnd = NULL;
#ifdef _DEBUG
	DWORD dwError = 0;
#endif

	TRY
	{
		VERIFY(AfxDeferRegisterClass(AFX_WNDCOMMCTLS_REG));
		AfxDeferRegisterClass(AFX_WNDCOMMCTLSNEW_REG);

#ifndef _AFX_NO_OCC_SUPPORT
		// separately create OLE controls in the dialog template
		if (pOccManager != NULL)
		{
			if (!SetOccDialogInfo(&occDialogInfo))
				return FALSE;

			lpDialogTemplate = pOccManager->PreCreateDialog(&occDialogInfo,
				lpDialogTemplate);
		}

		if (lpDialogTemplate == NULL)
			return FALSE;
#endif //!_AFX_NO_OCC_SUPPORT

		// If no font specified, set the system font.
		CString strFace;
		WORD wSize = 0;
		BOOL bSetSysFont = !CDialogTemplate::GetFont(lpDialogTemplate, strFace,
			wSize);

		if (afxData.bWin95 && !bSetSysFont && GetSystemMetrics(SM_DBCSENABLED))
		{
			bSetSysFont = (strFace == _T("MS Shell Dlg"));
			if (bSetSysFont && (wSize == 8))
				wSize = 0;
		}

		if (bSetSysFont)
		{
			CDialogTemplate dlgTemp(lpDialogTemplate);
			dlgTemp.SetSystemFont(wSize);
			hTemplate = dlgTemp.Detach();
		}

		if (hTemplate != NULL)
			lpDialogTemplate = (DLGTEMPLATE*)GlobalLock(hTemplate);

		// setup for modal loop and creation
		m_nModalResult = -1;
		m_nFlags |= WF_CONTINUEMODAL;

		// create modeless dialog
		AfxHookWindowCreate(this);
		hWnd = ::CreateDialogIndirect(hInst, lpDialogTemplate,
			pParentWnd->GetSafeHwnd(), AfxDlgProc);
#ifdef _DEBUG
		dwError = ::GetLastError();
#endif
	}
	CATCH_ALL(e)
	{
		DELETE_EXCEPTION(e);
		m_nModalResult = -1;
	}
	END_CATCH_ALL

#ifndef _AFX_NO_OCC_SUPPORT
	if (pOccManager != NULL)
	{
		pOccManager->PostCreateDialog(&occDialogInfo);
		if (hWnd != NULL)
			SetOccDialogInfo(NULL);
	}
#endif //!_AFX_NO_OCC_SUPPORT

	if (!AfxUnhookWindowCreate())
		PostNcDestroy();        // cleanup if Create fails too soon

	// handle EndDialog calls during OnInitDialog
#ifdef _DEBUG
#ifndef _AFX_NO_OCC_SUPPORT
	DWORD dwOldFlags = m_nFlags;
#endif
#endif
	if (hWnd != NULL && !(m_nFlags & WF_CONTINUEMODAL))
	{
		::DestroyWindow(hWnd);
		hWnd = NULL;
	}

	if (hTemplate != NULL)
	{
		GlobalUnlock(hTemplate);
		GlobalFree(hTemplate);
	}

	// help with error diagnosis (only if WM_INITDIALOG didn't EndDialog())
	if (hWnd == NULL)
	{
#ifdef _DEBUG
#ifndef _AFX_NO_OCC_SUPPORT
		if (dwOldFlags & WF_CONTINUEMODAL)
		{
			if (afxOccManager == NULL)
			{
				TRACE(traceAppMsg, 0, ">>> If this dialog has OLE controls:\n");
				TRACE(traceAppMsg, 0, ">>> AfxEnableControlContainer has not been called yet.\n");
				TRACE(traceAppMsg, 0, ">>> You should call it in your app's InitInstance function.\n");
			}
			else if (dwError != 0)
			{
				TRACE(traceAppMsg, 0, "Warning: Dialog creation failed!  GetLastError returns 0x%8.8X\n", dwError);
			}
		}
#endif //!_AFX_NO_OCC_SUPPORT
#endif //_DEBUG
		return FALSE;
	}

	ASSERT(hWnd == m_hWnd);
	return TRUE;
}

void AFXAPI AfxHookWindowCreate(CWnd* pWnd)
{
	_AFX_THREAD_STATE* pThreadState = _afxThreadState.GetData();
	if (pThreadState->m_pWndInit == pWnd)
		return;

	if (pThreadState->m_hHookOldCbtFilter == NULL)
	{
		pThreadState->m_hHookOldCbtFilter = ::SetWindowsHookEx(WH_CBT,
			_AfxCbtFilterHook, NULL, ::GetCurrentThreadId());
		if (pThreadState->m_hHookOldCbtFilter == NULL)
			AfxThrowMemoryException();
	}
	ASSERT(pThreadState->m_hHookOldCbtFilter != NULL);
	ASSERT(pWnd != NULL);
	ASSERT(pWnd->m_hWnd == NULL);   // only do once

	//ASSERT(pThreadState->m_pWndInit == NULL);   // hook not already in progress
	pThreadState->m_pWndInit = pWnd;
}

BOOL AFXAPI AfxUnhookWindowCreate()
{
	_AFX_THREAD_STATE* pThreadState = _afxThreadState.GetData();
#ifndef _AFXDLL
	if (afxContextIsDLL && pThreadState->m_hHookOldCbtFilter != NULL)
	{
		::UnhookWindowsHookEx(pThreadState->m_hHookOldCbtFilter);
		pThreadState->m_hHookOldCbtFilter = NULL;
	}
#endif
	if (pThreadState->m_pWndInit != NULL)
	{
		pThreadState->m_pWndInit = NULL;
		return FALSE;   // was not successfully hooked
	}
	return TRUE;
}
#endif
HWND Test_Excel_Dialog::PreModal()
{
	// cannot call DoModal on a dialog already constructed as modeless
//	ASSERT(m_hWnd == NULL);

	// allow OLE servers to disable themselves
	CWinApp* pApp = AfxGetApp();
	if (pApp != NULL)
		pApp->EnableModeless(FALSE);

	// find parent HWND
	HWND hWnd = NULL;//CWnd::GetSafeOwner_(m_pParentWnd->GetSafeHwnd(), &m_hWndTop);

	// hook for creation of dialog
//	AfxHookWindowCreate(this);

	// return window to use as parent for dialog
	return hWnd;
}

int Test_Excel_Dialog::DoModal()
{
	// can be constructed with a resource template or InitModalIndirect
	ASSERT(m_lpszTemplateName != NULL || m_hDialogTemplate != NULL ||
		m_lpDialogTemplate != NULL);

	// load resource as necessary
	LPCDLGTEMPLATE lpDialogTemplate = m_lpDialogTemplate;
	HGLOBAL hDialogTemplate = m_hDialogTemplate;
	HINSTANCE hInst = AfxGetResourceHandle();
	if (m_lpszTemplateName != NULL)
	{
		hInst = AfxFindResourceHandle(m_lpszTemplateName, RT_DIALOG);
		HRSRC hResource = ::FindResource(hInst, m_lpszTemplateName, RT_DIALOG);
		hDialogTemplate = LoadResource(hInst, hResource);
	}
	if (hDialogTemplate != NULL)
		lpDialogTemplate = (LPCDLGTEMPLATE)LockResource(hDialogTemplate);

	// return -1 in case of failure to load the dialog template resource
	if (lpDialogTemplate == NULL)
		return -1;

	// disable parent (before creating dialog)
	HWND hWndParent = PreModal();
	AfxUnhookWindowCreate();
	BOOL bEnableParent = FALSE;
	if (hWndParent && hWndParent != ::GetDesktopWindow() && ::IsWindowEnabled(hWndParent))
	{
		::EnableWindow(hWndParent, FALSE);
		bEnableParent = TRUE;
	}

	TRY
	{
		// create modeless dialog
		//AfxHookWindowCreate(this);
		if (CreateDlgIndirect(lpDialogTemplate,
						CWnd::FromHandle(hWndParent), hInst))
		{
			if (m_nFlags & WF_CONTINUEMODAL)
			{
				// enter modal loop
				DWORD dwFlags = MLF_SHOWONIDLE;
				if (GetStyle() & DS_NOIDLEMSG)
					dwFlags |= MLF_NOIDLEMSG;
				VERIFY(RunModalLoop(dwFlags) == m_nModalResult);
			}

			// hide the window before enabling the parent, etc.
			if (m_hWnd != NULL)
				SetWindowPos(NULL, 0, 0, 0, 0, SWP_HIDEWINDOW|
					SWP_NOSIZE|SWP_NOMOVE|SWP_NOACTIVATE|SWP_NOZORDER);
		}
	}
	CATCH_ALL(e)
	{
		DELETE_EXCEPTION(e);
		m_nModalResult = -1;
	}
	END_CATCH_ALL

	if (bEnableParent)
		::EnableWindow(hWndParent, TRUE);
	if (hWndParent != NULL && ::GetActiveWindow() == m_hWnd)
		::SetActiveWindow(hWndParent);

	// destroy modal window
	DestroyWindow();
	PostModal();

	// unlock/free resources as necessary
	if (m_lpszTemplateName != NULL || m_hDialogTemplate != NULL)
		UnlockResource(hDialogTemplate);
	if (m_lpszTemplateName != NULL)
		FreeResource(hDialogTemplate);

	return m_nModalResult;
}

/*
void CMyWnd::OnSomeAction()
{
   //pDialog initialized to NULL in the constructor of CMyWnd class
   pDialog = new CMyDialog();
   //Check if new succeeded and we got a valid pointer to a dialog object
   if(pDialog != NULL)
   {
      BOOL ret = pDialog->Create(IDD_MYDIALOG,this);
      if(!ret)   //Create failed.
         AfxMessageBox("Error creating Dialog");
      pDialog->ShowWindow(SW_SHOW);
   }
   else
      AfxMessageBox("Error Creating Dialog Object");
}*/
void OnSomeAction()
{
   //pDialog initialized to NULL in the constructor of CMyWnd class
   Test_Excel_Dialog * pDialog = new Test_Excel_Dialog();
   //Check if new succeeded and we got a valid pointer to a dialog object
   if(pDialog != NULL)
   {
      BOOL ret = pDialog->Create(IDD_DIALOG_TEST_EXCEL,NULL);
      if(!ret)   //Create failed.
         AfxMessageBox("Error creating Dialog");
      pDialog->ShowWindow(SW_SHOW);

	  pDialog->DoModal();
   }
   else
      AfxMessageBox("Error Creating Dialog Object");
}


/*
BOOL CWnd::CreateDlg(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
{
	// load resource
	LPCDLGTEMPLATE lpDialogTemplate = NULL;
	HGLOBAL hDialogTemplate = NULL;
	HINSTANCE hInst = AfxFindResourceHandle(lpszTemplateName, RT_DIALOG);
	HRSRC hResource = ::FindResource(hInst, lpszTemplateName, RT_DIALOG);
	hDialogTemplate = LoadResource(hInst, hResource);
	if (hDialogTemplate != NULL)
		lpDialogTemplate = (LPCDLGTEMPLATE)LockResource(hDialogTemplate);
	ASSERT(lpDialogTemplate != NULL);

	// create a modeless dialog
	BOOL bSuccess = CreateDlgIndirect(lpDialogTemplate, pParentWnd, hInst);

	// free resource
	UnlockResource(hDialogTemplate);
	FreeResource(hDialogTemplate);

	return bSuccess;
}*/

//DEL void Test_Excel_Dialog::OnButton1() 
//DEL {
//DEL 	// TODO: Add your control notification handler code here
//DEL 	
//DEL }
