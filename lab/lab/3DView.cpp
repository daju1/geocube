// 3DView.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "3DView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// C3DView

IMPLEMENT_DYNCREATE(C3DView, CView)

C3DView::C3DView()
{
}

C3DView::~C3DView()
{
}


BEGIN_MESSAGE_MAP(C3DView, CView)
	//{{AFX_MSG_MAP(C3DView)
	ON_COMMAND(ID_EXCEL_LOAD, OnExcelLoad)
	ON_UPDATE_COMMAND_UI(ID_EXCEL_LOAD, OnUpdateExcelLoad)
	ON_COMMAND(ID_EXCEL_RELEASE, OnExcelRelease)
	ON_UPDATE_COMMAND_UI(ID_EXCEL_RELEASE, OnUpdateExcelRelease)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C3DView drawing

void C3DView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// C3DView diagnostics

#ifdef _DEBUG
void C3DView::AssertValid() const
{
	CView::AssertValid();
}

void C3DView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// C3DView message handlers

void C3DView::OnExcelLoad() 
{
	BeginWaitCursor();
	this->m_excel.ExcelOleLoad();
	EndWaitCursor();	
}

void C3DView::OnUpdateExcelLoad(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable(!this->m_excel.IsApplicationDispatch());
//   pCmdUI->Enable(true);
}









void C3DView::OnExcelRelease() 
{
	this->m_excel.ExcelOleRelease();
}

void C3DView::OnUpdateExcelRelease(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable(this->m_excel.IsApplicationDispatch());	
	
}


