// GraphsView.cpp : implementation of the CGraphsView class
//

#include "stdafx.h"
#include "Graphs.h"

#include "GraphsDoc.h"
#include "GraphsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern void WriteRaporto(LPCTSTR s);

/////////////////////////////////////////////////////////////////////////////
// CGraphsView

IMPLEMENT_DYNCREATE(CGraphsView, CScrollView)

BEGIN_MESSAGE_MAP(CGraphsView, CScrollView)
	//{{AFX_MSG_MAP(CGraphsView)
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_MOVE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphsView construction/destruction

CGraphsView::CGraphsView()
{
	// событие - "Ready" - сигнальное
	m_hEventDrawReady = CreateEvent( NULL, TRUE, TRUE, "DrawReadyEvent" );
}

CGraphsView::~CGraphsView()
{
}

BOOL CGraphsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGraphsView drawing

void CGraphsView::OnDraw(CDC* pDC)
{
	AfxMessageBox("OnDraw 1\n");

WriteRaporto("OnDraw 1\n");
	DWORD wt = WaitForSingleObject( m_hEventDrawReady, 0);
	if (wt != WAIT_OBJECT_0 || wt == WAIT_TIMEOUT){
WriteRaporto("                                OnDraw return 1\n" );
		return;
	}
	ResetEvent(m_hEventDrawReady);


	TData DataX, 
		DataY;
	CGraphsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);


	int a = 65,
		b = 132;

	int len = pDoc->m_vpPoints1[0].py->Length();
	CString s;
	s.Format("%d",len);
	CGraph(pDoc->m_vpPoints1, "Сигнал для Лаггер - обработки", 
		"t",s,a-6*b, m_SizeTotal).Draw(pDC,DataX, DataY);
	for (int g = 0; g < pDoc->m_vpPoints.Size(); g++)
	{
		int len = pDoc->m_vpPoints[g][0].py->Length();
		CString s;
		s.Format("%d",len);
		if (pDoc->m_vpPoints[g].Size()>0)
			CGraph(pDoc->m_vpPoints[g], "","t",s,a-(5-g)*b, m_SizeTotal).Draw(pDC,DataX, DataY, pDoc->m_vpPoints[g][0].toScaleX, pDoc->m_vpPoints[g][0].toScaleY);
	}
	SetEvent(m_hEventDrawReady);
WriteRaporto("OnDraw end\n");

}

void CGraphsView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = 50;
	sizeTotal.cy = 700*2 + 200;
	SetScrollSizes(MM_TEXT, sizeTotal);
	m_SizeTotal = sizeTotal;
}

/////////////////////////////////////////////////////////////////////////////
// CGraphsView printing

BOOL CGraphsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGraphsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGraphsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CGraphsView diagnostics

#ifdef _DEBUG
void CGraphsView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CGraphsView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CGraphsDoc* CGraphsView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraphsDoc)));
	return (CGraphsDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGraphsView message handlers

void CGraphsView::OnSetFocus(CWnd* pOldWnd) 
{
	CScrollView::OnSetFocus(pOldWnd);
	
	// TODO: Add your message handler code here
	
}

void CGraphsView::OnKillFocus(CWnd* pNewWnd) 
{
	CScrollView::OnKillFocus(pNewWnd);
	
	// TODO: Add your message handler code here
	
}

void CGraphsView::OnMove(int x, int y) 
{
	CScrollView::OnMove(x, y);
	
	// TODO: Add your message handler code here
	
}

BOOL CGraphsView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
	return CScrollView::OnEraseBkgnd(pDC);
}
