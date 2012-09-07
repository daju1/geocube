// UseAuthors.cpp : implementation file
//

#include "stdafx.h"
#include "consumebiblio.h"
#include "UseAuthors.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUseAuthors dialog


CUseAuthors::CUseAuthors(CWnd* pParent /*=NULL*/)
	: CDialog(CUseAuthors::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUseAuthors)
	m_strAuthor = _T("");
	//}}AFX_DATA_INIT
}


void CUseAuthors::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUseAuthors)
	DDX_Text(pDX, IDC_AUTHOR, m_strAuthor);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUseAuthors, CDialog)
	//{{AFX_MSG_MAP(CUseAuthors)
	ON_BN_CLICKED(IDC_NEXT, OnNext)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUseAuthors message handlers


void CUseAuthors::OnNext() 
{
	// TODO: Add your control notification handler code here
	m_authors.MoveNext();
	m_strAuthor = m_authors.m_Author;
	UpdateData(FALSE);
}

BOOL CUseAuthors::OnInitDialog() 
{
	// Note 
	// Assumes the bibio.mdb file is in c:\

	CDialog::OnInitDialog();
	
	m_authors.Open();	
	m_authors.MoveFirst();
	m_strAuthor = m_authors.m_Author;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
