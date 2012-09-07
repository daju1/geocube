// 3DDoc.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "3DDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// C3DDoc

IMPLEMENT_DYNCREATE(C3DDoc, CDocument)

C3DDoc::C3DDoc()
{
}

BOOL C3DDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

C3DDoc::~C3DDoc()
{
}


BEGIN_MESSAGE_MAP(C3DDoc, CDocument)
	//{{AFX_MSG_MAP(C3DDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C3DDoc diagnostics

#ifdef _DEBUG
void C3DDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void C3DDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// C3DDoc serialization

void C3DDoc::Serialize(CArchive& ar)
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
// C3DDoc commands
