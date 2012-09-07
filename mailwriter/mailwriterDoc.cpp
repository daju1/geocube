// mailwriterDoc.cpp : implementation of the CMailwriterDoc class
//

#include "stdafx.h"
#include "mailwriter.h"

#include "mailwriterDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMailwriterDoc

IMPLEMENT_DYNCREATE(CMailwriterDoc, CDocument)

BEGIN_MESSAGE_MAP(CMailwriterDoc, CDocument)
	//{{AFX_MSG_MAP(CMailwriterDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMailwriterDoc construction/destruction

CMailwriterDoc::CMailwriterDoc()
{
	// TODO: add one-time construction code here

}

CMailwriterDoc::~CMailwriterDoc()
{
}

BOOL CMailwriterDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	((CEditView*)m_viewList.GetHead())->SetWindowText(NULL);

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMailwriterDoc serialization

void CMailwriterDoc::Serialize(CArchive& ar)
{
	// CEditView contains an edit control which handles all serialization
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CMailwriterDoc diagnostics

#ifdef _DEBUG
void CMailwriterDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMailwriterDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMailwriterDoc commands
