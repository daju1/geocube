// ex31dvw.cpp : implementation of the CEx31dView class
//

#include "stdafx.h"
#include "ex31d.h"

#include "ex31ddoc.h"
#include "ex31dView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CEx31dView

IMPLEMENT_DYNCREATE(CEx31dView, CRowView)

BEGIN_MESSAGE_MAP(CEx31dView, CRowView)
    //{{AFX_MSG_MAP(CEx31dView)
    ON_WM_SETFOCUS()
    ON_WM_MOUSEACTIVATE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
    // Standard printing commands
    ON_COMMAND(ID_FILE_PRINT, CRowView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, CRowView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx31dView construction/destruction

CEx31dView::CEx31dView()
{
	m_pSet = NULL;
	m_nSelectedRow = -1;
}

CEx31dView::~CEx31dView()
{
}
										
/////////////////////////////////////////////////////////////////////////////
void CEx31dView::OnUpdate(CView*, LPARAM lHint, CObject* pHint)
{
    // called when the user executes a new query
    // can't set m_pSet in OnInitialUpdate because it's NULL then
    ScrollToPosition(CPoint(0, 0));
    Invalidate(TRUE);
    m_nSelectedRow = -1;
	CEx31dDoc* pDoc = GetDocument();
	if((m_pSet = pDoc->m_pRecordset) != NULL) {
		UpdateScrollSizes();
	}
}

/////////////////////////////////////////////////////////////////////////////
// CRowView overrides

/////////////////////////////////////////////////////////////////////////////
void CEx31dView::OnDrawRow(CDC* pDC, int nRow, int y, BOOL bSelected)
{
//	TRACE("OnDrawRow -- %d\n", nRow);
    int x = 0;
    int i;
    CEx31dDoc* pDoc = GetDocument();
    if (m_pSet == NULL) return;
	
    if (nRow == 0) {    // title row
      for (i = 0; i < pDoc->m_nFields; i++) {
        pDC->TextOut(x, y, pDoc->m_arrayFieldName[i]);
        x += pDoc->m_arrayFieldSize[i] * m_nCharWidth;
      }	
    }
    else {
      try {
		// view rows are 0-based, records are 1-based, 0 row is title row
        m_pSet->SetAbsolutePosition(nRow);
		// IsDeleted won't work, must trap exception for deleted rows
        DrawDataRow(pDC, y);
      }
      catch (CDBException* pe) {
		if(!_strnicmp(pe->m_strError, "RECORD IS DELETED", 17)) {
			pDC->TextOut(0, y, "**RECORD DELETED**");
		}
		else {
			AfxMessageBox(pe->m_strError);
		}
		pe->Delete();
      }
    }
}

void CEx31dView::DrawDataRow(CDC* pDC, int y)
{
	int x = 0;
	CString strTime, str;
	CEx31dDoc* pDoc = GetDocument();
	for (int i = 0; i < pDoc->m_nFields; i++) {
	  CDBVariant var; // must declare this inside the loop
	  m_pSet->GetFieldValue(i, var);
	  switch (var.m_dwType) {
	  case DBVT_STRING:
		str = *var.m_pstring; // narrow characters
		break;
	  case DBVT_SHORT:
		str.Format("%d", (int) var.m_iVal);
		break;
	  case DBVT_LONG:
		str.Format("%d", var.m_lVal);
		break;
	  case DBVT_SINGLE:
		str.Format("%10.2f", (double) var.m_fltVal);
		break;
	  case DBVT_DOUBLE:
		str.Format("%10.2f", var.m_dblVal);
		break;
	  case DBVT_DATE:
		str.Format("%d/%d/%d", var.m_pdate->month, var.m_pdate->day, var.m_pdate->year);
		break;
	  case DBVT_BOOL:
		str = (var.m_boolVal == 0) ? "FALSE" : "TRUE";
		break;
	  case DBVT_NULL:
		str =  "----";
		break;
	  default:
		str.Format("Unk type %d\n", var.m_dwType);
		TRACE("Unknown type %d\n", var.m_dwType);
	  }
	  pDC->TextOut(x, y, str);
	  x += pDoc->m_arrayFieldSize[i] * m_nCharWidth;
	}
}

/////////////////////////////////////////////////////////////////////////////
void CEx31dView::GetRowWidthHeight(CDC* pDC, int& nRowWidth,
         int& nRowHeight, int& nCharWidth)
{
    TEXTMETRIC tm;

    CEx31dDoc* pDoc = GetDocument();
	pDC->GetTextMetrics(&tm);
    nCharWidth = tm.tmAveCharWidth + 1;
    nRowWidth = 0;
	for(int i = 0; i < pDoc->m_nFields; i++) {
	    nRowWidth += pDoc->m_arrayFieldSize[i];
	}
    nRowWidth *= nCharWidth;
    nRowHeight = tm.tmHeight;
}

/////////////////////////////////////////////////////////////////////////////
int CEx31dView::GetActiveRow()
{
    return m_nSelectedRow;
}

/////////////////////////////////////////////////////////////////////////////
int CEx31dView::GetRowCount()
{
    return GetDocument()->m_nRowCount;
}

/////////////////////////////////////////////////////////////////////////////
void CEx31dView::ChangeSelectionNextRow(BOOL bNext)
{
    if (bNext && (m_nSelectedRow < min(GetRowCount() - 1,
                LastViewableRow() - 2))) {
        m_nSelectedRow++;
    }
    if (!bNext && m_nSelectedRow) {
        m_nSelectedRow--;
    }
    UpdateRow(m_nSelectedRow);
}

/////////////////////////////////////////////////////////////////////////////
void CEx31dView::ChangeSelectionToRow(int nRow)
{
    if ((nRow >= 0) && (nRow < min(GetRowCount(), LastViewableRow() - 1))) {
        m_nSelectedRow = nRow;
    }
    UpdateRow(m_nSelectedRow);
}

/////////////////////////////////////////////////////////////////////////////
// CEx31dView diagnostics

#ifdef _DEBUG
void CEx31dView::AssertValid() const
{
    CRowView::AssertValid();
}

void CEx31dView::Dump(CDumpContext& dc) const
{
    CRowView::Dump(dc);
}

/////////////////////////////////////////////////////////////////////////////
CEx31dDoc* CEx31dView::GetDocument() // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx31dDoc)));
    return (CEx31dDoc*) m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx31dView message handlers

/////////////////////////////////////////////////////////////////////////////
void CEx31dView::OnSetFocus(CWnd* pOldWnd)
{
    // updates dialog bar query strings
	GetDocument()->PutQuery();
	CRowView::OnSetFocus(pOldWnd);
}

/////////////////////////////////////////////////////////////////////////////
int CEx31dView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// resets the focus from the dialog bar
    SetFocus(); 
    return CRowView::OnMouseActivate(pDesktopWnd, nHitTest, message);
}


void CEx31dView::OnInitialUpdate() 
{
//	SetTimer(1, 5000, NULL); // every 5 seconds
	CRowView::OnInitialUpdate();
}

void CEx31dView::OnTimer(UINT nIDEvent) 
{
	Invalidate(); // update view from database
}
