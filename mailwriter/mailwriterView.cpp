// mailwriterView.cpp : implementation of the CMailwriterView class
//

#include "stdafx.h"
#include "mailwriter.h"

#include "mailwriterDoc.h"
#include "mailwriterView.h"
#include "DlgSendMail.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMailwriterView

IMPLEMENT_DYNCREATE(CMailwriterView, CEditView)

BEGIN_MESSAGE_MAP(CMailwriterView, CEditView)
	//{{AFX_MSG_MAP(CMailwriterView)
	ON_COMMAND(ID_MAIL_SEND, OnMailSend)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMailwriterView construction/destruction

CMailwriterView::CMailwriterView()
{

	dlg = new DlgSendMail;
	if (dlg)
	{
		dlg->Create(IDD_DIALOG_SEND_MAIL);

	}

}

CMailwriterView::~CMailwriterView()
{
	dlg->DestroyWindow();
	delete dlg;
}

BOOL CMailwriterView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping

	return bPreCreated;
}

/////////////////////////////////////////////////////////////////////////////
// CMailwriterView drawing

void CMailwriterView::OnDraw(CDC* pDC)
{
	CMailwriterDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMailwriterView printing

BOOL CMailwriterView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default CEditView preparation
	return CEditView::OnPreparePrinting(pInfo);
}

void CMailwriterView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView begin printing.
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CMailwriterView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView end printing
	CEditView::OnEndPrinting(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CMailwriterView diagnostics

#ifdef _DEBUG
void CMailwriterView::AssertValid() const
{
	CEditView::AssertValid();
}

void CMailwriterView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CMailwriterDoc* CMailwriterView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMailwriterDoc)));
	return (CMailwriterDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMailwriterView message handlers

void CMailwriterView::OnMailSend() 
{
	if (dlg)
	{
		if (dlg->m_pView == NULL)
			dlg->m_pView = this;
		dlg->ShowWindow(SW_SHOW);

	}
}
