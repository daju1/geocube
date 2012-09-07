// ex31bView.cpp : implementation of the CEx31bView class
//

#include "stdafx.h"
#include "ex31b.h"

#include "ex31bSet.h"
#include "ex31bDoc.h"
#include "ex31bView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx31bView

IMPLEMENT_DYNCREATE(CEx31bView, CRecordView)

BEGIN_MESSAGE_MAP(CEx31bView, CRecordView)
	//{{AFX_MSG_MAP(CEx31bView)
	ON_COMMAND(ID_RECORD_ADD, OnRecordAdd)
	ON_COMMAND(ID_RECORD_CLEARFIELDS, OnRecordClearfields)
	ON_COMMAND(ID_RECORD_DELETE, OnRecordDelete)
	ON_UPDATE_COMMAND_UI(ID_RECORD_DELETE, OnUpdateRecordDelete)
	ON_COMMAND(ID_RECORD_UPDATE, OnRecordUpdate)
	ON_UPDATE_COMMAND_UI(ID_RECORD_UPDATE, OnUpdateRecordUpdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx31bView construction/destruction

CEx31bView::CEx31bView()
	: CRecordView(CEx31bView::IDD)
{
	//{{AFX_DATA_INIT(CEx31bView)
	m_pSet = NULL;
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CEx31bView::~CEx31bView()
{
}

void CEx31bView::DoDataExchange(CDataExchange* pDX)
{
	CRecordView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEx31bView)
	DDX_FieldText(pDX, IDC_ID, m_pSet->m_InstructorID, m_pSet);
	DDX_FieldText(pDX, IDC_NAME, m_pSet->m_Name, m_pSet);
	DDX_FieldText(pDX, IDC_ROOM, m_pSet->m_RoomNo, m_pSet);
	//}}AFX_DATA_MAP
}

BOOL CEx31bView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CRecordView::PreCreateWindow(cs);
}

void CEx31bView::OnInitialUpdate()
{
	m_pSet = &GetDocument()->m_ex31bSet;
	CRecordView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}

/////////////////////////////////////////////////////////////////////////////
// CEx31bView diagnostics

#ifdef _DEBUG
void CEx31bView::AssertValid() const
{
	CRecordView::AssertValid();
}

void CEx31bView::Dump(CDumpContext& dc) const
{
	CRecordView::Dump(dc);
}

CEx31bDoc* CEx31bView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx31bDoc)));
	return (CEx31bDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx31bView database support
CRecordset* CEx31bView::OnGetRecordset()
{
	return m_pSet;
}


/////////////////////////////////////////////////////////////////////////////
// CEx31bView message handlers

BOOL CEx31bView::OnMove(UINT nIDMoveCommand) 
{
    switch (nIDMoveCommand)
	{
    case ID_RECORD_PREV:
        m_pSet->MovePrev();
        if (!m_pSet->IsBOF())
            break;

    case ID_RECORD_FIRST:
        m_pSet->MoveFirst();
        break;

    case ID_RECORD_NEXT:
        m_pSet->MoveNext();
        if (!m_pSet->IsEOF())
            break;
        if (!m_pSet->CanScroll()) {
            // Clear screen since we’re sitting on EOF
            m_pSet->SetFieldNull(NULL);
            break;
        }

     case ID_RECORD_LAST:
        m_pSet->MoveLast();
        break;

    default:
        // unexpected case value
        ASSERT(FALSE);
    }

    // Show results of Move operation
    UpdateData(FALSE);
    return TRUE;
}

void CEx31bView::OnRecordAdd() 
{
	m_pSet->AddNew();
	UpdateData(TRUE);
	if (m_pSet->CanUpdate())  {
	  m_pSet->Update();
	}
	if (!m_pSet->IsEOF())
	{
		m_pSet->MoveLast();
	}
	m_pSet->Requery(); // for sorted sets
	UpdateData(FALSE);
}

void CEx31bView::OnRecordClearfields() 
{
    m_pSet->SetFieldNull(NULL);
    UpdateData(FALSE);
}

void CEx31bView::OnRecordDelete() 
{
	CRecordsetStatus status;
    try {
        m_pSet->Delete();
    }
    catch(CDBException* e) {
        AfxMessageBox(e->m_strError);
        e->Delete();
        m_pSet->MoveFirst(); // lost our place!
        UpdateData(FALSE);
        return;
    }
    m_pSet->GetStatus(status);
	if (status.m_lCurrentRecord == 0) {
		// We deleted last of 2 records
		m_pSet->MoveFirst();
	}
	else {
		m_pSet->MoveNext();
	}
    UpdateData(FALSE);
}

void CEx31bView::OnUpdateRecordDelete(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable(!m_pSet->IsEOF());
}

void CEx31bView::OnRecordUpdate() 
{
    m_pSet->Edit();
    UpdateData(TRUE);
    if (m_pSet->CanUpdate()){
      m_pSet->Update();
    }
// should requery if key field changed
}

void CEx31bView::OnUpdateRecordUpdate(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable(!m_pSet->IsEOF());
}
