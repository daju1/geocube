// ex31bDoc.cpp : implementation of the CEx31bDoc class
//

#include "stdafx.h"
#include "ex31b.h"

#include "ex31bSet.h"
#include "ex31bDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx31bDoc

IMPLEMENT_DYNCREATE(CEx31bDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx31bDoc, CDocument)
	//{{AFX_MSG_MAP(CEx31bDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx31bDoc construction/destruction

CEx31bDoc::CEx31bDoc()
{
	// TODO: add one-time construction code here

}

CEx31bDoc::~CEx31bDoc()
{
}

BOOL CEx31bDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx31bDoc diagnostics

#ifdef _DEBUG
void CEx31bDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx31bDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx31bDoc commands
