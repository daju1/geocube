// DlgSoilName.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "DlgSoilName.h"
#include "LabView.h"
#include "SetProbGr.h"


#include <map>
using namespace std;
#include "../../laboratory/src/lab.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSoilName dialog


CDlgSoilName::CDlgSoilName(CLabView * lab_view, LabNumber * lab_number,
						   CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSoilName::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSoilName)
	m_edit_soil_name = _T("");
	//}}AFX_DATA_INIT

	m_lab_view = lab_view;
	m_lab_number = lab_number;
}


void CDlgSoilName::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSoilName)
	DDX_Text(pDX, IDC_EDIT_SOIL_NAME, m_edit_soil_name);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSoilName, CDialog)
	//{{AFX_MSG_MAP(CDlgSoilName)
	ON_BN_CLICKED(IDC_BUTTON_GENERATE_SOIL_NAME, OnButtonGenerateSoilName)
	ON_BN_CLICKED(IDC_BUTTON_SOIL_NAME_FROM_DB, OnButtonSoilNameFromDb)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSoilName message handlers
void SetGruntName(CDatabase * database, long id_obj, long id_kt, long id_prob, CString name)
{
	SetProbGr setProbGr(database);
	setProbGr.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d and ID_PROB = %d", id_obj, id_kt, id_prob);
	setProbGr.m_strSort.Format("ID_KT, ID_PROB");
	if ( !setProbGr.Open(CRecordset::dynaset) )
		return;

	if (!setProbGr.IsBOF()) 
	{
		setProbGr.MoveFirst();
		if(!setProbGr.IsEOF()) 
		{
			setProbGr.Edit();
			setProbGr.m_GRUNT_NAME = name;
			setProbGr.Update();
		}
	}
}
CString GetGruntName(CDatabase * database, long id_obj, long id_kt, long id_prob)
{
	SetProbGr setProbGr(database);
	setProbGr.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d and ID_PROB = %d", 
		id_obj, id_kt, id_prob);
	setProbGr.m_strSort.Format("ID_KT, ID_PROB");
	if ( !setProbGr.Open(CRecordset::dynaset) )
		return "";

	if (!setProbGr.IsBOF()) 
	{
		setProbGr.MoveFirst();
		if(!setProbGr.IsEOF()) 
		{
			return setProbGr.m_GRUNT_NAME;
		}
	}
	return "";
}


void CDlgSoilName::OnOK() 
{
	this->UpdateData(true);
	SetGruntName(&this->m_lab_view->GetLabDoc()->m_database, 
		m_lab_number->id_obj, 
		m_lab_number->id_kt, 
		m_lab_number->id_prob,
		this->m_edit_soil_name);

	CString where;
	this->m_lab_view->GetSetProbGrFilterStr(m_lab_number->id_obj, where);
	this->m_lab_view->UpdateProbGruntListCtrl(where,"ID_KT, ID_PROB");

	CDialog::OnOK();

}

void CDlgSoilName::OnButtonGenerateSoilName() 
{
	this->m_edit_soil_name = this->m_lab_number->GetSoilDescription(false).c_str();
	this->UpdateData(false);
	
}

void CDlgSoilName::OnButtonSoilNameFromDb() 
{
	this->m_edit_soil_name = GetGruntName(&this->m_lab_view->GetLabDoc()->m_database, 
		m_lab_number->id_obj, 
		m_lab_number->id_kt, 
		m_lab_number->id_prob);
	this->UpdateData(false);
}

BOOL CDlgSoilName::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	this->m_edit_soil_name = GetGruntName(&this->m_lab_view->GetLabDoc()->m_database, 
		m_lab_number->id_obj, 
		m_lab_number->id_kt, 
		m_lab_number->id_prob);
	this->UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
