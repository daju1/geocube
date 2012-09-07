// tableDoc.cpp : implementation of the CTableDoc class
//

#include "stdafx.h"
#include "lab.h"

#include "tableDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTableDoc

IMPLEMENT_DYNCREATE(CTableDoc, CDocument)

BEGIN_MESSAGE_MAP(CTableDoc, CDocument)
	//{{AFX_MSG_MAP(CTableDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTableDoc construction/destruction

CTableDoc::CTableDoc()
{
	// TODO: add one-time construction code here

}

CTableDoc::~CTableDoc()
{
}

BOOL CTableDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTableDoc serialization

void CTableDoc::Serialize(CArchive& ar)
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
// CTableDoc diagnostics

#ifdef _DEBUG
void CTableDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTableDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTableDoc commands
