// DlgProxy.cpp : implementation file
//

#include "stdafx.h"
#include "consumebiblio.h"
#include "DlgProxy.h"
#include "consumebiblioDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConsumebiblioDlgAutoProxy

IMPLEMENT_DYNCREATE(CConsumebiblioDlgAutoProxy, CCmdTarget)

CConsumebiblioDlgAutoProxy::CConsumebiblioDlgAutoProxy()
{
	EnableAutomation();
	
	// To keep the application running as long as an automation 
	//	object is active, the constructor calls AfxOleLockApp.
	AfxOleLockApp();

	// Get access to the dialog through the application's
	//  main window pointer.  Set the proxy's internal pointer
	//  to point to the dialog, and set the dialog's back pointer to
	//  this proxy.
	ASSERT (AfxGetApp()->m_pMainWnd != NULL);
	ASSERT_VALID (AfxGetApp()->m_pMainWnd);
	ASSERT_KINDOF(CConsumebiblioDlg, AfxGetApp()->m_pMainWnd);
	m_pDialog = (CConsumebiblioDlg*) AfxGetApp()->m_pMainWnd;
	m_pDialog->m_pAutoProxy = this;
}

CConsumebiblioDlgAutoProxy::~CConsumebiblioDlgAutoProxy()
{
	// To terminate the application when all objects created with
	// 	with automation, the destructor calls AfxOleUnlockApp.
	//  Among other things, this will destroy the main dialog
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CConsumebiblioDlgAutoProxy::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CConsumebiblioDlgAutoProxy, CCmdTarget)
	//{{AFX_MSG_MAP(CConsumebiblioDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CConsumebiblioDlgAutoProxy, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CConsumebiblioDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IConsumebiblio to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {486A1B85-0D94-11D2-8CAA-DF2C53524146}
static const IID IID_IConsumebiblio =
{ 0x486a1b85, 0xd94, 0x11d2, { 0x8c, 0xaa, 0xdf, 0x2c, 0x53, 0x52, 0x41, 0x46 } };

BEGIN_INTERFACE_MAP(CConsumebiblioDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CConsumebiblioDlgAutoProxy, IID_IConsumebiblio, Dispatch)
END_INTERFACE_MAP()

// The IMPLEMENT_OLECREATE2 macro is defined in StdAfx.h of this project
// {486A1B83-0D94-11D2-8CAA-DF2C53524146}
IMPLEMENT_OLECREATE2(CConsumebiblioDlgAutoProxy, "Consumebiblio.Application", 0x486a1b83, 0xd94, 0x11d2, 0x8c, 0xaa, 0xdf, 0x2c, 0x53, 0x52, 0x41, 0x46)

/////////////////////////////////////////////////////////////////////////////
// CConsumebiblioDlgAutoProxy message handlers
