// DlgStatZond.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "DlgStatZond.h"

#include "LabView.h"
#include "EnGeologyView.h"

#include "SetKT.h"
#include "SetObject.h"
#include "SetPtStZond.h"
#include "SetUstanovka.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgStatZond dialog


CDlgStatZond::CDlgStatZond(CLabView * lab_view, CLabDoc * lab_doc, CDatabase * database, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgStatZond::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgStatZond)
	m_edit_bf = _T("");
	m_edit_bg = _T("");
	m_edit_kf = _T("");
	m_edit_kg = _T("");
	m_edit_zong_type = _T("");
	m_edit_tsz = _T("");
	m_edit_object = _T("");
	//}}AFX_DATA_INIT

	this->m_lab_view = lab_view;
	this->m_lab_doc = lab_doc;
	this->p_database = database;

	id_ust_selected = -1;
	ok_pressed = false;




}


void CDlgStatZond::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgStatZond)
	DDX_Control(pDX, IDC_COMBO_UST, m_combo_ust);
	DDX_Text(pDX, IDC_EDIT_BF, m_edit_bf);
	DDX_Text(pDX, IDC_EDIT_BG, m_edit_bg);
	DDX_Text(pDX, IDC_EDIT_KF, m_edit_kf);
	DDX_Text(pDX, IDC_EDIT_KG, m_edit_kg);
	DDX_Text(pDX, IDC_EDIT_ZOND_TYPE, m_edit_zong_type);
	DDX_Text(pDX, IDC_EDIT_TSZ, m_edit_tsz);
	DDX_Text(pDX, IDC_EDIT_OBJECT, m_edit_object);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgStatZond, CDialog)
	//{{AFX_MSG_MAP(CDlgStatZond)
	ON_CBN_SELCHANGE(IDC_COMBO_UST, OnSelchangeComboUst)
	ON_BN_CLICKED(IDC_BUTTON_TO_EXCEL, OnButtonToExcel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgStatZond message handlers

void CDlgStatZond::OnSelchangeComboUst() 
{
	int index = this->m_combo_ust.GetCurSel();
	long id_ust = long(this->m_combo_ust.GetItemData(index));
	id_ust_selected = id_ust;

	SetUstanovka setUstanovka(this->p_database);
	setUstanovka.m_strFilter.Format("");
	setUstanovka.m_strSort.Format("");
	if ( !setUstanovka.Open(CRecordset::dynaset) )
		return;

	if (!setUstanovka.IsBOF()) 
	{
		setUstanovka.MoveFirst( );
		while(!setUstanovka.IsEOF()) 
		{
			if (id_ust == setUstanovka.m_ID_UST)
			{
				this->m_edit_bf.Format("%f", setUstanovka.m_Bf);
				this->m_edit_bg.Format("%f", setUstanovka.m_Bg);
				this->m_edit_kg.Format("%f", setUstanovka.m_Kg);
				this->m_edit_kf.Format("%f", setUstanovka.m_Kf);
				this->m_edit_zong_type.Format("%d", setUstanovka.m_TYP_ZOND);
			}
			setUstanovka.MoveNext();
		}
	}
	this->UpdateData(false);
}

BOOL CDlgStatZond::OnInitDialog() 
{
	CDialog::OnInitDialog();

	int nObItem = this->m_lab_view->GetObjectItem();

	if (nObItem < 0)
	{
		AfxMessageBox("Не выбрано ни одного объекта");
		CDialog::OnOK();
		return FALSE;
	}

	int nKTItem = this->m_lab_view->GetKTItem();

	if (nKTItem < 0)
	{
		AfxMessageBox("Не выбрано ни одной KT");
		CDialog::OnOK();
		return FALSE;
	}
	try
	{
		SetObject setObject(this->p_database);

		if ( !setObject.Open(CRecordset::dynaset) )
			return false;

		setObject.SetAbsolutePosition(nObItem + 1);        
		long ID_OBJ = setObject.m_ID_OBJ;

		this->m_edit_object = setObject.m_NAZVA;
			
		SetKT setKT(this->p_database);
		setKT.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
		setKT.m_strSort.Format(CEnGeologyView::str_kt_list_order_by);
		if ( !setKT.Open(CRecordset::dynaset) )
			return false;

		setKT.SetAbsolutePosition(nKTItem + 1);        
		long ID_KT = setKT.m_ID_KT;

		this->m_edit_tsz = setKT.m_NAZVA;

		long ID_UST = -1;

		SetPtStZond setPtStZond(this->p_database);
		setPtStZond.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d", ID_OBJ, ID_KT);
		setPtStZond.m_strSort.Format("");
		if ( !setPtStZond.Open(CRecordset::dynaset) )
			return false;
		if (!setPtStZond.IsBOF()) 
		{
			setPtStZond.MoveFirst( );
			while(!setPtStZond.IsEOF()) 
			{
				ID_UST = setPtStZond.m_ID_UST;
				id_ust_selected = ID_UST;
				setPtStZond.MoveNext();
			}
		}

		SetUstanovka setUstanovka(this->p_database);
		setUstanovka.m_strFilter.Format("");
		setUstanovka.m_strSort.Format("");
		if ( !setUstanovka.Open(CRecordset::dynaset) )
			return false;

		int i_ust = 0;
		if (!setUstanovka.IsBOF()) 
		{
			setUstanovka.MoveFirst( );
			while(!setUstanovka.IsEOF()) 
			{
				this->m_combo_ust.AddString(setUstanovka.m_NAZVA);
				this->m_combo_ust.SetItemData(i_ust, setUstanovka.m_ID_UST);

				if (ID_UST == setUstanovka.m_ID_UST)
				{
					this->m_edit_bf.Format("%f", setUstanovka.m_Bf);
					this->m_edit_bg.Format("%f", setUstanovka.m_Bg);
					this->m_edit_kg.Format("%f", setUstanovka.m_Kg);
					this->m_edit_kf.Format("%f", setUstanovka.m_Kf);
					this->m_edit_zong_type.Format("%d", setUstanovka.m_TYP_ZOND);
					this->m_combo_ust.SetCurSel(i_ust);
				}

				setUstanovka.MoveNext();
				i_ust++;
			}
		}

	}
	catch (CDBException* pe) 
	{
		AfxMessageBox(pe->m_strError);
		pe->Delete();
		return false;
	}

	this->UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgStatZond::OnOK() 
{
	this->ok_pressed = true;
	
	CDialog::OnOK();
}

void CDlgStatZond::OnButtonToExcel() 
{	
	CEnGeologyView * en_geo_view = dynamic_cast<CEnGeologyView *>(this->m_lab_view);
	if (en_geo_view)
	{
		en_geo_view->m_excel_stat_zond_output.LoadFormNew(this->m_edit_tsz);
		en_geo_view->m_excel_stat_zond_output.Fill();
	}	
}
