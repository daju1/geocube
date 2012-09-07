// TableFrm.cpp : implementation of the CTableFrame class
//

#include "stdafx.h"
#include "lab.h"

#include "TableFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTableFrame

IMPLEMENT_DYNCREATE(CTableFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CTableFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CTableFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTableFrame construction/destruction

CTableFrame::CTableFrame()
{
	// TODO: add member initialization code here
	
}

CTableFrame::~CTableFrame()
{
}

BOOL CTableFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTableFrame diagnostics

#ifdef _DEBUG
void CTableFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CTableFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTableFrame message handlers

int CTableFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
/*	if (!m_wndQueryBar.Create(this, IDD_QUERY_BAR, CBRS_TOP, IDD_QUERY_BAR))
	{
		TRACE("Failed to create query bar\n");
		return -1;		// fail to create
	}*/
	
	return 0;
}
