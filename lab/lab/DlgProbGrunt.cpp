// DlgProbGrunt.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "DlgProbGrunt.h"
#include "labDoc.h"
#include "labView.h"

#include "SetObject.h"
#include "SetKT.h"
#include "SetProbGr.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgProbGrunt dialog

CString GetKodProbyGrunta(long val); //id_kodprob

CDlgProbGrunt::CDlgProbGrunt(CLabView * view, CLabDoc * doc, bool new_prob, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgProbGrunt::IDD, pParent)
{
	this->m_view = view;
	this->m_doc = doc;
	this->m_new_prob = new_prob;
	//{{AFX_DATA_INIT(CDlgProbGrunt)
	m_lab_n = _T("");
	m_prob_gr_h = _T("");
	//}}AFX_DATA_INIT

	id_kt = -1;
	r_SoilsList = -1;
	r_SoilsListLab = -1;
	id_prob = -1;
	i_kod_prob = -1;
	is_geo = false;
	is_lab = false;

	i_kt = -1;
}


void CDlgProbGrunt::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgProbGrunt)
	DDX_Control(pDX, IDC_COMBO_KOD_PROB_GR, m_combo_kod_proby_grunta);
	DDX_Control(pDX, IDC_COMBO_KT, m_combo_prob_gr_kt);
	DDX_Text(pDX, IDC_EDIT_LAB_N, m_lab_n);
	DDX_Text(pDX, IDC_EDIT_PROB_GR_H, m_prob_gr_h);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgProbGrunt, CDialog)
	//{{AFX_MSG_MAP(CDlgProbGrunt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgProbGrunt message handlers

void CDlgProbGrunt::OnOK() 
{
	CDialog::OnOK();

	i_kod_prob = this->m_combo_kod_proby_grunta.GetCurSel();
	if (i_kod_prob < 0)
	{
		//AfxMessageBox("Не выбран код пробы грунта");
		//return;
	}

	int i = this->m_combo_prob_gr_kt.GetCurSel();
	if (i < 0)
	{
		AfxMessageBox("Не выбранa выработка");
		return;
	}
	id_kt = this->m_combo_prob_gr_kt.GetItemData(i);

	int nObItem = this->m_view->GetObjectItem();
	if (nObItem < 0)
	{
		AfxMessageBox("Не выбран объект");
		return;
	}

	SetObject setObject(&this->m_doc->m_database);
	if ( !setObject.Open(CRecordset::dynaset) )
		return;
	setObject.SetAbsolutePosition(nObItem + 1);        
	long ID_OBJ = setObject.m_ID_OBJ;

	if(this->m_new_prob)
	{
		if (!this->m_doc->AddNewProbGrunt(this, ID_OBJ))
		{
			//MessageBox("!AddNewProbGrunt","",0);
			return;
		}
	}
	else
	{
		if (!this->m_doc->EditProbGrunt(this, ID_OBJ))
		{
			//MessageBox("!EditProbGrunt","",0);
			return;
		}
	}





	CString where;
	where.Format("ID_OBJ = %d", ID_OBJ);

	if (this->is_geo)
		where.Format("ID_OBJ = %d and ID_KT = %d", ID_OBJ, id_kt);
		
	if (this->is_lab)
		where.Format("ID_OBJ = %d", ID_OBJ);
	this->m_view->UpdateProbGruntListCtrl(where, "ID_KT, ID_PROB");	


}



BOOL CDlgProbGrunt::OnInitDialog() 
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
	
	if(this->m_new_prob)
	{

	}
	else
	{
		if (this->r_SoilsList >= 0)
		{
			SetProbGr setProbGr(&this->m_doc->m_database);
			setProbGr.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d", ID_OBJ, id_kt);
			setProbGr.m_strSort.Format("ID_KT, ID_PROB");
			if ( !setProbGr.Open(CRecordset::dynaset) )
				return TRUE;
			setProbGr.SetAbsolutePosition(this->r_SoilsList+1);

			id_kt = setProbGr.m_ID_KT;
			id_prob = setProbGr.m_ID_PROB;
			i_kod_prob = setProbGr.m_ID_KODPROB - 1;

			long lab_n = setProbGr.m_LAB_N;
			double H = setProbGr.m_H;

			m_lab_n.Format("%d", lab_n);
			m_prob_gr_h.Format("%f", H);
		}

		if (this->r_SoilsListLab >= 0)
		{
			SetProbGr setProbGr(&this->m_doc->m_database);
			setProbGr.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
			setProbGr.m_strSort.Format("ID_KT, ID_PROB");
			if ( !setProbGr.Open(CRecordset::dynaset) )
				return TRUE;
			setProbGr.SetAbsolutePosition(this->r_SoilsListLab+1);

			id_kt = setProbGr.m_ID_KT;
			id_prob = setProbGr.m_ID_PROB;
			i_kod_prob = setProbGr.m_ID_KODPROB - 1;

			long lab_n = setProbGr.m_LAB_N;
			double H = setProbGr.m_H;

			m_lab_n.Format("%d", lab_n);
			m_prob_gr_h.Format("%f", H);
		}

	}

	CDialog::OnInitDialog();
	// TODO: Add extra initialization here

	this->m_combo_prob_gr_kt.ResetContent();

	SetKT setKT(&this->m_doc->m_database);
	setKT.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
	setKT.m_strSort.Format("ID_KT");
	if ( !setKT.Open(CRecordset::dynaset) )
		return TRUE;

	int n_kt = -1, i = 0;

	CString str;
	if (!setKT.IsBOF()) 
	{
		setKT.MoveFirst( );
		while(!setKT.IsEOF()) 
		{
			str.Format(_T("%s"), setKT.m_NAZVA);
			this->m_combo_prob_gr_kt.AddString( str );
			int i = m_combo_prob_gr_kt.GetCount() - 1;
			this->m_combo_prob_gr_kt.SetItemData(i, setKT.m_ID_KT);
			if(id_kt == setKT.m_ID_KT) n_kt = i;
			setKT.MoveNext(); // to validate record count
			i++;
		}
	}

	if (n_kt >= 0)
	{
		this->m_combo_prob_gr_kt.SetCurSel(n_kt);
		this->m_combo_prob_gr_kt.EnableWindow(FALSE);
	}	
	else if (i_kt >= 0)
	{
		this->m_combo_prob_gr_kt.SetCurSel(i_kt);
//		this->m_combo_prob_gr_kt.EnableWindow(FALSE);
	}

	for (i = 0; i < 4; i++)
	{
		this->m_combo_kod_proby_grunta.AddString(GetKodProbyGrunta(i+1));
	}
	this->m_combo_kod_proby_grunta.SetCurSel(i_kod_prob);

	return TRUE;  // return TRUE unless you set the focus to a control
	        // EXCEPTION: OCX Property Pages should return FALSE
}
