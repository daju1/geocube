// OGFrm.cpp : implementation of the COGFrame class
//

#include "stdafx.h"
//#include "OG.h"

#include "OGFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COGFrame

IMPLEMENT_DYNCREATE(COGFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(COGFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(COGFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COGFrame construction/destruction

COGFrame::COGFrame()
{
	// TODO: add member initialization code here
	
}

COGFrame::~COGFrame()
{
}

BOOL COGFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// COGFrame diagnostics

#ifdef _DEBUG
void COGFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void COGFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COGFrame message handlers
