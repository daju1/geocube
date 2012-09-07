// ex31aView.cpp : implementation of the CEx31aView class
//

#include "stdafx.h"
#include "ex31a.h"
#include "ex31aSet.h"
#include "ex31aDoc.h"
#include "ex31aView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx31aView

IMPLEMENT_DYNCREATE(CEx31aView, CScrollView)

BEGIN_MESSAGE_MAP(CEx31aView, CScrollView)
	//{{AFX_MSG_MAP(CEx31aView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx31aView construction/destruction

CEx31aView::CEx31aView()
{
	// TODO: add construction code here

}

CEx31aView::~CEx31aView()
{
}

BOOL CEx31aView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx31aView drawing

void CEx31aView::OnDraw(CDC* pDC)
{
	TEXTMETRIC tm;
	pDC->GetTextMetrics(&tm);
	int nLineHeight=tm.tmHeight+tm.tmExternalLeading;
	CPoint pText(0,0);

	int y = 0;
    CString str;
    if (m_pSet->IsBOF()) { // detects empty recordset
      return;
    }
    m_pSet->MoveFirst();   // fails if recordset is empty
    while (!m_pSet->IsEOF()) {
	  str.Format("%ld", m_pSet->m_StudentID);
      pDC->TextOut(pText.x, pText.y, str);
      pDC->TextOut(pText.x+1000, pText.y, m_pSet->m_Name);
      str.Format("%d", m_pSet->m_GradYear);
      pDC->TextOut(pText.x+4000, pText.y, str);
      m_pSet->MoveNext();
	  pText.y -= nLineHeight;

    }
}

void CEx31aView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	CSize sizeTotal(8000, 10500);

    SetScrollSizes(MM_HIENGLISH, sizeTotal);
    
    m_pSet = &GetDocument()->m_ex31aSet;
	// Remember that documents/views are reused in SDI applications!
	m_pSet->m_strFilter="";
    
    if (m_pSet->IsOpen()) {
		m_pSet->Close();
    }
    m_pSet->Open();
}

/////////////////////////////////////////////////////////////////////////////
// CEx31aView printing

BOOL CEx31aView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CEx31aView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CEx31aView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CEx31aView diagnostics

#ifdef _DEBUG
void CEx31aView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CEx31aView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CEx31aDoc* CEx31aView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx31aDoc)));
	return (CEx31aDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx31aView message handlers
