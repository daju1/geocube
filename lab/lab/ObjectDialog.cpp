// ObjectDialog.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "ObjectDialog.h"
#include "LabDoc.h"
#include "LabView.h"
#include "SetObject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgObject dialog


CDlgObject::CDlgObject(CLabView * view, CLabDoc * doc, bool new_object, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgObject::IDD, pParent)
{
	this->m_view = view;
	this->m_doc = doc;
	this->m_new_object = new_object;
	//{{AFX_DATA_INIT(CDlgObject)
	m_contract = _T("");
	m_object_name = _T("");
	//}}AFX_DATA_INIT
}


void CDlgObject::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgObject)
	DDX_Text(pDX, IDC_EDIT_CONTRACT, m_contract);
	DDX_Text(pDX, IDC_EDIT_OBJECT_NAME, m_object_name);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgObject, CDialog)
	//{{AFX_MSG_MAP(CDlgObject)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgObject message handlers

void CDlgObject::OnOK() 
{
	this->UpdateData(true);

	if(this->m_new_object)
	{
		if (!this->m_doc->AddNewObject(this->m_contract, this->m_object_name))
			MessageBox("!AddNewObect","",0);
	}
	else
	{
		if (!this->m_view->EditObject(this->m_contract, this->m_object_name))
			MessageBox("!EditObect","",0);
	}

	this->m_view->UpdateObjectsListCtrl("","");
	
	CDialog::OnOK();

}

BOOL CDlgObject::OnInitDialog() 
{
	if(this->m_new_object)
	{
	}
	else
	{
		int nObItem = this->m_view->GetObjectItem();
		if (nObItem < 0)
		{
			AfxMessageBox("Не выбран объект");
			return  TRUE;
		}

		SetObject setObject(&this->m_doc->m_database);
		if ( !setObject.Open(CRecordset::dynaset) )
			return TRUE;
		setObject.SetAbsolutePosition(nObItem + 1);        
		long ID_OBJ = setObject.m_ID_OBJ;	

		this->m_contract = setObject.m_CONTRACT;
		this->m_object_name = setObject.m_NAZVA;
	}	

	CDialog::OnInitDialog();
	

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
