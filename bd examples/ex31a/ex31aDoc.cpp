// ex31aDoc.cpp : implementation of the CEx31aDoc class
//

#include "stdafx.h"
#include "ex31a.h"
#include "ex31aSet.h"
#include "ex31aDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx31aDoc

IMPLEMENT_DYNCREATE(CEx31aDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx31aDoc, CDocument)
	//{{AFX_MSG_MAP(CEx31aDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx31aDoc construction/destruction

CEx31aDoc::CEx31aDoc()
{
	// TODO: add one-time construction code here

}

CEx31aDoc::~CEx31aDoc()
{
}

BOOL CEx31aDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx31aDoc serialization

void CEx31aDoc::Serialize(CArchive& ar)
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
// CEx31aDoc diagnostics

#ifdef _DEBUG
void CEx31aDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx31aDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx31aDoc commands
