// GridDataDailog.cpp : implementation file
//

#include "stdafx.h"
#include "..\..\generic.h"
#include "griddatadailog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GridDataDailog dialog


GridDataDailog::GridDataDailog(CWnd* pParent /*=NULL*/)
	: CDialog(GridDataDailog::IDD, pParent)
{
	//{{AFX_DATA_INIT(GridDataDailog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void GridDataDailog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GridDataDailog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GridDataDailog, CDialog)
	//{{AFX_MSG_MAP(GridDataDailog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GridDataDailog message handlers
