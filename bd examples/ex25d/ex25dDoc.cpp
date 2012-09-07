// ex25dDoc.cpp : implementation of the CEx25dDoc class
//

#include "stdafx.h"
#include "ex25d.h"

#include "ex25dDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx25dDoc

IMPLEMENT_DYNCREATE(CEx25dDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx25dDoc, CDocument)
	//{{AFX_MSG_MAP(CEx25dDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx25dDoc construction/destruction

CEx25dDoc::CEx25dDoc()
{
	// TODO: add one-time construction code here

}

CEx25dDoc::~CEx25dDoc()
{
}

BOOL CEx25dDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx25dDoc serialization

void CEx25dDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CEx25dDoc diagnostics

#ifdef _DEBUG
void CEx25dDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx25dDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx25dDoc commands
