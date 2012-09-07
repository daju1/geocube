// ex31cDoc.cpp : implementation of the CEx31cDoc class
//

#include "stdafx.h"
#include "ex31c.h"

#include "ex31cSet.h"
#include "ex31cDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx31cDoc

IMPLEMENT_DYNCREATE(CEx31cDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx31cDoc, CDocument)
	//{{AFX_MSG_MAP(CEx31cDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx31cDoc construction/destruction

CEx31cDoc::CEx31cDoc()
{
	m_pEx31cSet = NULL;
}

CEx31cDoc::~CEx31cDoc()
{
}

BOOL CEx31cDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	if(m_pEx31cSet == NULL) {
		m_pEx31cSet = new CEx31cSet(&m_database);
		CString strConnect = m_pEx31cSet->GetDefaultConnect();
		m_database.Open(NULL, FALSE, FALSE, strConnect, FALSE);
	}
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CEx31cDoc diagnostics

#ifdef _DEBUG
void CEx31cDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx31cDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx31cDoc commands
