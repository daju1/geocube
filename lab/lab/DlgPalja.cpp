// DlgPalja.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "EnGeologyView.h"
#include "DlgPalja.h"
#include "LabView.h"
#include "SetKT.h"
#include "SetObject.h"


#include "SetUmPoz.h"
#include "SetGenezis.h"
#include "SetGrunty.h"
#include "SetIGE.h"
//#include "SetIGE0.h"

#include "..\..\array\src\ap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPalja dialog

void DeleteEndZeros(CString & str);

CDlgPalja::CDlgPalja(CLabView * lab_view, CLabDoc *	lab_doc, CDatabase * database, bool do_all, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPalja::IDD, pParent), m_SurfDoc(false), my_palja(database, &this->m_SurfDoc) , m_list_svai(database, &this->my_palja.m_well)
{
	//{{AFX_DATA_INIT(CDlgPalja)
	m_edit_contract = _T("");
	m_edit_object = _T("");
	m_edit_zond_type = _T("");
	m_edit_tsz = _T("");
	m_radio_svai_sech = -1;
	m_radio_rostverk_h = -1;
	m_radio_snip1 = -1;
	m_radio_method_find_mean_pck = -1;
	m_radio_typ_grunt_1_zond_type = -1;
	//}}AFX_DATA_INIT
	this->m_lab_view = lab_view;
	this->m_lab_doc = lab_doc;
	this->p_database = database;
	m_do_all = do_all;

	ID_OBJ = -1;


}
void CDlgPalja::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPalja)
	DDX_Control(pDX, IDC_EDIT_STEP, m_edit_step);
	DDX_Control(pDX, IDC_BUTTON_TO_EXCEL, m_button_to_excel);
	DDX_Control(pDX, IDC_STATIC_GRUNT_TYPE_1_ZT, m_static_grunt_type_1zt);
	DDX_Control(pDX, IDC_RADIO_TYP_GRUNT_1, m_radio_type_grunt_1zt1);
	DDX_Control(pDX, IDC_RADIO_TYP_GRUNT_2, m_radio_type_grunt_1zt2);
	DDX_Control(pDX, IDC_RADIO_TYP_GRUNT_3, m_radio_type_grunt_1zt3);
	DDX_Control(pDX, IDC_RADIO_TYP_GRUNT_4, m_radio_type_grunt_1zt4);
	DDX_Control(pDX, IDC_EDIT_ROSTVERK_H, m_edit_rostverk_H);
	DDX_Control(pDX, IDC_CHECK_1_ZOND_TYPE_RAZBIVKA_NA_TOLSCHI, m_check_razbivka_na_tolschi);
	DDX_Control(pDX, IDC_LIST_SVAI, m_list_svai);
	DDX_Control(pDX, IDC_EDIT_SECH_Y, m_edit_sech_Y);
	DDX_Control(pDX, IDC_EDIT_SECH_X, m_edit_sech_X);
	DDX_Control(pDX, IDC_EDIT_R_SVAI, m_edit_r_svai);
	DDX_Control(pDX, IDC_COMBO_SVAI_STORONA_KVADRATA, m_combo_svai_storona_kvadrata);
	DDX_Text(pDX, IDC_EDIT_CONTRACT, m_edit_contract);
	DDX_Text(pDX, IDC_EDIT_OBJECT, m_edit_object);
	DDX_Text(pDX, IDC_EDIT_ZOND_TYPE, m_edit_zond_type);
	DDX_Text(pDX, IDC_EDIT_TSZ, m_edit_tsz);
	DDX_Radio(pDX, IDC_RADIO_SVAI_SECH_1, m_radio_svai_sech);
	DDX_Radio(pDX, IDC_RADIO_ROSTVERK_H_1, m_radio_rostverk_h);
	DDX_Radio(pDX, IDC_RADIO_SNIP1, m_radio_snip1);
	DDX_Radio(pDX, IDC_RADIO_METHOD_FIND_MEAN_PCK_1, m_radio_method_find_mean_pck);
	DDX_Radio(pDX, IDC_RADIO_TYP_GRUNT_1, m_radio_typ_grunt_1_zond_type);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPalja, CDialog)
	//{{AFX_MSG_MAP(CDlgPalja)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_TO_DB, OnButtonSaveToDb)
	ON_BN_CLICKED(IDC_BUTTON_TO_EXCEL, OnButtonToExcel)
	ON_WM_DRAWITEM()
	ON_BN_CLICKED(IDC_RADIO_SVAI_SECH_1, OnRadioSvaiSech1)
	ON_BN_CLICKED(IDC_RADIO_SVAI_SECH_2, OnRadioSvaiSech2)
	ON_BN_CLICKED(IDC_RADIO_SVAI_SECH_3, OnRadioSvaiSech3)
	ON_BN_CLICKED(IDC_RADIO_ROSTVERK_H_1, OnRadioRostverkH1)
	ON_BN_CLICKED(IDC_RADIO_ROSTVERK_H_2, OnRadioRostverkH2)
	ON_BN_CLICKED(IDC_RADIO_SNIP1, OnRadioSnip1)
	ON_BN_CLICKED(IDC_RADIO_SNIP2, OnRadioSnip2)
	ON_BN_CLICKED(IDC_RADIO_TYP_GRUNT_1, OnRadioTypGrunt1)
	ON_BN_CLICKED(IDC_RADIO_TYP_GRUNT_2, OnRadioTypGrunt2)
	ON_BN_CLICKED(IDC_CHECK_1_ZOND_TYPE_RAZBIVKA_NA_TOLSCHI, OnCheck1ZondTypeRazbivkaNaTolschi)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

bool CDlgPalja::InitDoc()
{
	SetUmPoz setUmPoz(this->p_database);	
	setUmPoz.m_strFilter.Format("");
	setUmPoz.m_strSort.Format("");
	if ( !setUmPoz.Open(CRecordset::dynaset) )
		return false;

	if (!setUmPoz.IsBOF()) 
	{
		setUmPoz.MoveFirst( );
		while(!setUmPoz.IsEOF()) 
		{
			this->m_SurfDoc.UmPoz(setUmPoz.m_ID_UMPOZ,
				setUmPoz.m_UMPOZ,
				setUmPoz.m_HATCHACAD,
				setUmPoz.m_Angle,
				setUmPoz.m_Scale);

			setUmPoz.MoveNext();
		}
	}



	SetGenezis setGenezis(this->p_database);	
	setGenezis.m_strFilter.Format("");
	setGenezis.m_strSort.Format("");
	if ( !setGenezis.Open(CRecordset::dynaset) )
		return false;

	if (!setGenezis.IsBOF()) 
	{
		setGenezis.MoveFirst( );
		while(!setGenezis.IsEOF()) 
		{
			this->m_SurfDoc.Genezis(setGenezis.m_ID_GENEZIS,
				setGenezis.m_NAZVA_U,
				setGenezis.m_NAZVA_R,
				setGenezis.m_ID_NORMATYV,
				setGenezis.m_ID_GRMAIN,
				setGenezis.m_INDEX,
				setGenezis.m_R,
				setGenezis.m_G,
				setGenezis.m_B);

			setGenezis.MoveNext();
		}
	}


	SetGrunty setGrunty(this->p_database);	
	setGrunty.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
	setGrunty.m_strSort.Format("");
	if ( !setGrunty.Open(CRecordset::dynaset) )
		return false;

	if (!setGrunty.IsBOF()) 
	{
		setGrunty.MoveFirst( );
		while(!setGrunty.IsEOF()) 
		{
			this->m_SurfDoc.Grunty(setGrunty.m_ID_GR,
				setGrunty.m_NAZVA_U,
				setGrunty.m_NAZVA_R,
				setGrunty.m_TYPGR,
				setGrunty.m_TYPGR_PCK,
				setGrunty.m_ID_NORMATYV,
				setGrunty.m_ID_GRCONS,
				setGrunty.m_ID_UKLAD,
				setGrunty.m_ID_NJU,
				setGrunty.m_ID_GRMAIN,
				setGrunty.m_ID_UMPOZ,
				setGrunty.m_ID_GENEZIS);

			setGrunty.MoveNext();
		}
	}


	//bUnEdited = true;
	SetIGE setIGE0(true, this->p_database);	
	setIGE0.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
	setIGE0.m_strSort.Format("");
	if ( !setIGE0.Open(CRecordset::dynaset) )
		return false;

	if (!setIGE0.IsBOF()) 
	{
		setIGE0.MoveFirst( );
		while(!setIGE0.IsEOF()) 
		{
			this->m_SurfDoc.IGE0(setIGE0.m_ID_IGE,
				setIGE0.m_ID_GR,
				setIGE0.m_IGE,
				setIGE0.m_mk,
				setIGE0.m_mkz,
				setIGE0.m_strat,
				setIGE0.m_desc0);

			setIGE0.MoveNext();
		}
	}


	//bUnEdited = false;
	SetIGE setIGE(false, this->p_database);	
	setIGE.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
	setIGE.m_strSort.Format("");
	if ( !setIGE.Open(CRecordset::dynaset) )
		return false;

	if (!setIGE.IsBOF()) 
	{
		setIGE.MoveFirst( );
		while(!setIGE.IsEOF()) 
		{
			this->m_SurfDoc.IGE(setIGE.m_ID_IGE,
				setIGE.m_ID_GR,
				setIGE.m_IGE,
				setIGE.m_mk,
				setIGE.m_mkz,
				setIGE.m_strat,
				setIGE.m_desc0);

			setIGE.MoveNext();
		}
	}

	this->m_SurfDoc.ApplyLito();
}

BOOL CDlgPalja::OnInitDialog() 
{
	CDialog::OnInitDialog();
	

	int nObItem = this->m_lab_view->GetObjectItem();

	if (nObItem < 0)
	{
		AfxMessageBox("Ќе выбрано ни одного объекта");
		CDialog::OnOK();
		return FALSE;
	}

	int nKTItem = -1;

	if (!this->m_do_all)
	{
		nKTItem = this->m_lab_view->GetKTItem();

		if (nKTItem < 0)
		{
			AfxMessageBox("Ќе выбрано ни одной KT");
			CDialog::OnOK();
			return FALSE;
		}
	}


	try
	{
		SetObject setObject(this->p_database);

		if ( !setObject.Open(CRecordset::dynaset) )
			return false;

		setObject.SetAbsolutePosition(nObItem + 1); 
		ID_OBJ = setObject.m_ID_OBJ;

		this->m_edit_object = setObject.m_NAZVA;
		m_edit_contract = setObject.m_CONTRACT;
			
		this->InitDoc();
			
		this->m_list_svai.OnInitCtrl();
		this->m_list_svai.InitHeaders();


		SetKT setKT(this->p_database);
		setKT.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
		setKT.m_strSort.Format(CEnGeologyView::str_kt_list_order_by);
		if ( !setKT.Open(CRecordset::dynaset) )
			return false;
		

		if (this->m_do_all)
		{
			if (!setKT.IsBOF()) 
			{
				setKT.MoveFirst( );
				while(!setKT.IsEOF()) 
				{
					this->v_my_palja.push_back(MyPalja(this->p_database, &this->m_SurfDoc));
					this->v_my_palja.back().KT_nazva = setKT.m_NAZVA;

					this->v_my_palja.back().ID_KT = setKT.m_ID_KT;
					this->v_my_palja.back().ID_OBJ = ID_OBJ;
					this->v_my_palja.back().InitWell();

					this->m_list_svai.p_well = &this->v_my_palja.back().m_well;
					this->m_list_svai.ID_KT = setKT.m_ID_KT;
					this->m_list_svai.ID_OBJ = ID_OBJ;

					this->FillPaljaHeader(this->v_my_palja.back());

					this->m_list_svai.FillCtrlList();

					setKT.MoveNext();
				}
			}
		}
		else
		{
			setKT.SetAbsolutePosition(nKTItem + 1);        
			this->m_edit_tsz = setKT.m_NAZVA;

			this->my_palja.ID_KT = setKT.m_ID_KT;
			this->my_palja.ID_OBJ = ID_OBJ;
			this->my_palja.InitWell();

			this->m_list_svai.ID_KT = my_palja.ID_KT;
			this->m_list_svai.ID_OBJ = ID_OBJ;

			this->m_list_svai.FillCtrlList();
		}




		for (int i_storona_kvadrata = 0; i_storona_kvadrata < 5; i_storona_kvadrata++)
		{
			int storona = 20 + i_storona_kvadrata * 5;
			CString s;
			s.Format("%dx%d см", storona, storona);
			this->m_combo_svai_storona_kvadrata.AddString(s);
			this->m_combo_svai_storona_kvadrata.SetItemData(i_storona_kvadrata, storona);
		}	

		if (this->my_palja.m_well.m_palja.data2_filled)
		{
			m_radio_svai_sech = this->my_palja.m_well.m_palja.data2.id_typ - 1;
			switch (this->my_palja.m_well.m_palja.data2.id_typ)
			{
			case 1:
				{
					// кругла€ сва€
					this->OnRadioSvaiSech1();
					CString s;
					s.Format("%f",  100 * this->my_palja.m_well.m_palja.data2.pereriz_x); 
					DeleteEndZeros(s);
					this->m_edit_r_svai.SetWindowText(s);
				}
				break;
			case 2:
				{
					// квадратна€ сва€
					this->OnRadioSvaiSech2();
					int i_storona_kvadrata = ap::round(100 * this->my_palja.m_well.m_palja.data2.pereriz_x / 5.0) - 4;
					int res = m_combo_svai_storona_kvadrata.SetCurSel(i_storona_kvadrata);
				}
				break;
			case 3:
				{
					// пр€моугольна€ сва€
					this->OnRadioSvaiSech3();
					CString s;
					s.Format("%f",  100 * this->my_palja.m_well.m_palja.data2.pereriz_x); 
					DeleteEndZeros(s);
					this->m_edit_sech_X.SetWindowText(s);

					s.Format("%f",  100 * this->my_palja.m_well.m_palja.data2.pereriz_y); 
					DeleteEndZeros(s);
					this->m_edit_sech_Y.SetWindowText(s);
				}
				break;
			}

			m_radio_snip1 = this->my_palja.m_well.m_palja.data2.id_snip - 1;
			switch (this->my_palja.m_well.m_palja.data2.id_snip)
			{
			case 1:
				{
					this->OnRadioSnip1();
				}
				break;
			case 2:
				{
					this->OnRadioSnip2();
				}
				break;
			}
		}
		else
		{
			m_radio_svai_sech = 1;
			this->OnRadioSvaiSech2();
				int i_storona_kvadrata = 1;
				int res = m_combo_svai_storona_kvadrata.SetCurSel(i_storona_kvadrata);

			m_radio_snip1 = 0;
			this->OnRadioSnip1();
		}

		this->m_radio_rostverk_h = 0;
		this->OnRadioRostverkH1();

		this->m_radio_method_find_mean_pck = 1;
		this->m_radio_typ_grunt_1_zond_type = 0;

		this->m_edit_step.SetWindowText(CString("1"));


		if (this->my_palja.m_well.m_stat_zond.data2_filled)
		{
			//long typ_zond = this->m_well.m_stat_zond.data2.typ_zond;
			this->m_edit_zond_type.Format("%d", my_palja.typ_zond);
		}

	}
	catch (CDBException* pe) 
	{
		AfxMessageBox(pe->m_strError);
		pe->Delete();
		return false;
	}


	if (this->m_do_all)
		this->m_button_to_excel.EnableWindow(0);



	this->UpdateData(false);



	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPalja::FillPaljaHeader(MyPalja & mp)
{
	int iActualItem = 0;

	CString s = " ";

	this->m_list_svai.AddString(iActualItem, 0, s);
	this->m_list_svai.AddString(iActualItem, 0, s);
	this->m_list_svai.AddString(iActualItem, 1, mp.KT_nazva);

	s = "ростверк:";
	this->m_list_svai.AddString(iActualItem, 2, s);
	s = "глубина";
	this->m_list_svai.AddString(iActualItem, 3, s);
	if (mp.ustje_defined && mp.m_well.m_palja.data2_filled)
		s.Format("%f", mp.ustje - mp.m_well.m_palja.data2.pz);
	else
		s = " ";
	DeleteEndZeros(s);
	this->m_list_svai.AddString(iActualItem, 4, s);
	s = "альтитуда";
	this->m_list_svai.AddString(iActualItem, 5, s);
	if (mp.m_well.m_palja.data2_filled)
		s.Format("%f",mp.m_well.m_palja.data2.pz);
	else
		s = " ";
	DeleteEndZeros(s);
	this->m_list_svai.AddString(iActualItem, 6, s);
	s = "";
	this->m_list_svai.AddString(iActualItem, 0, s);
}
/////////////////////////////////////////////////////////////////////////////
// CDlgPalja message handlers
void CDlgPalja::OnOK() 
{
	this->UpdateData(true);

	long id_method_find_mean_pck = m_radio_method_find_mean_pck + 1;
	long id_typ	= m_radio_svai_sech + 1;
	double pereriz_x = 0.0, pereriz_y = 0.0;
	switch (id_typ)
	{
	case 1:
		{
			// кругла€ сва€
			CString s;
			this->m_edit_r_svai.GetWindowText(s);
			pereriz_x = pereriz_y = atof(s) / 100;
		}
		break;
	case 2:
		{
			// квадратна€ сва€
			int i_storona_kvadrata = m_combo_svai_storona_kvadrata.GetCurSel();
			pereriz_x = pereriz_y = 5.0 * (i_storona_kvadrata + 4.0) / 100.0;
		}
		break;
	case 3:
		{
			// пр€моугольна€ сва€
			CString s;
			this->m_edit_sech_X.GetWindowText(s);
			pereriz_x = atof(s) / 100;

			this->m_edit_sech_Y.GetWindowText(s);
			pereriz_y = atof(s) / 100;
		}
		break;
	}

	double glubina_rostverka = 0.0;
	if (this->m_do_all)
	{
	}
	else
	{
		switch (this->m_radio_rostverk_h)
		{
		case 0:
			{
				if (this->my_palja.m_well.m_palja.data2_filled)
				{             
					CString s;
					this->m_edit_rostverk_H.GetWindowText(s);
					glubina_rostverka = atof(s);
				}
			}
			break;
		case 1:
			{
				if (this->my_palja.ustje_defined && this->my_palja.m_well.m_palja.data2_filled)
				{				
					CString s;
					this->m_edit_rostverk_H.GetWindowText(s);
					glubina_rostverka = this->my_palja.ustje - atof(s);
				}
			}
		}
	}

	long id_snip = m_radio_snip1 + 1;


	bool razbivka_na_tolschi = BST_CHECKED == this->m_check_razbivka_na_tolschi.GetCheck();
	long typ_grunt_1_zond_type = this->m_radio_typ_grunt_1_zond_type + 1;

	this->m_list_svai.InitHeaders();

	CString s;
	this->m_edit_step.GetWindowText(s);
	double step = atof(s);

	if (step == 0.0)
		step = 1.0;

	if (this->m_do_all)
	{
		for (vector<MyPalja>::iterator it = this->v_my_palja.begin();
			it != this->v_my_palja.end(); it++)
		{
			switch (this->m_radio_rostverk_h)
			{
			case 0:
				{
					if ((*it).m_well.m_palja.data2_filled)
					{             
						CString s;
						this->m_edit_rostverk_H.GetWindowText(s);
						glubina_rostverka = atof(s);
					}
				}
				break;
			case 1:
				{
					if ((*it).ustje_defined && (*it).m_well.m_palja.data2_filled)
					{				
						CString s;
						this->m_edit_rostverk_H.GetWindowText(s);
						glubina_rostverka = (*it).ustje - atof(s);
					}
				}
			}


//			(*it).p_SurfDoc = &this->m_SurfDoc;
			


			(*it).m_well.CalcPalja(id_typ, pereriz_x, pereriz_y,
				glubina_rostverka, 
				id_snip, 
				razbivka_na_tolschi, 
				typ_grunt_1_zond_type, 
				id_method_find_mean_pck, step);



			this->m_list_svai.p_well = &(*it).m_well;
			this->m_list_svai.ID_KT = (*it).ID_KT;
			this->m_list_svai.ID_OBJ = (*it).ID_OBJ;

			this->FillPaljaHeader((*it));
			this->m_list_svai.FillCtrlList();

		}
	}
	else
	{
		this->my_palja.m_well.CalcPalja(id_typ, pereriz_x, pereriz_y, glubina_rostverka, id_snip, razbivka_na_tolschi, typ_grunt_1_zond_type, id_method_find_mean_pck, step);
			
		this->m_list_svai.FillCtrlList();
	}
}


void CDlgPalja::OnButtonSaveToDb() 
{
	if (this->m_do_all)
	{
		for (vector<MyPalja>::iterator it = this->v_my_palja.begin();
			it != this->v_my_palja.end(); it++)
		{
			(*it).DeleteFromDB();
			(*it).SaveToDB();
		}
	}
	else
	{
		this->my_palja.DeleteFromDB();
		this->my_palja.SaveToDB();	
	}

}

void CDlgPalja::OnButtonToExcel() 
{
	if (this->m_do_all)
	{
	}
	else
	{
		TCHAR filter[] =
							TEXT("Excel files (*.xls)\0*.xls\0")
							TEXT("All Files (*.*)\0*.*\0");
		char fn_xls[4098];

		sprintf(fn_xls, "%s\0", this->m_edit_tsz);
		

		char * p = NULL;
		while (p = strchr(fn_xls, '*'))
			*p = 'x';

		DWORD nFilterIndex = 0;
		if (S_OK == SaveFileDlg(NULL, fn_xls, filter, nFilterIndex))
		{
			switch (nFilterIndex)
			{
			case 1:
				{
					char * p = NULL;
					if (p = strrchr(fn_xls, '.'))
						*p = '\0';
					this->my_palja.Passport(fn_xls);
				}
				break;
			}			
		}	
	}
}


void CDlgPalja::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nIDCtl)
	{
	case IDC_LIST_SVAI:
		this->m_list_svai.OnDrawItem(nIDCtl, lpDrawItemStruct);
		break;
	}
	
	//CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CDlgPalja::OnRadioSvaiSech1() 
{
	this->m_edit_r_svai.EnableWindow(1);

	m_combo_svai_storona_kvadrata.EnableWindow(0);

	m_edit_sech_X.EnableWindow(0);
	m_edit_sech_Y.EnableWindow(0);	
}

void CDlgPalja::OnRadioSvaiSech2() 
{
	this->m_edit_r_svai.EnableWindow(0);

	m_combo_svai_storona_kvadrata.EnableWindow(1);

	m_edit_sech_X.EnableWindow(0);
	m_edit_sech_Y.EnableWindow(0);	
}

void CDlgPalja::OnRadioSvaiSech3() 
{
	this->m_edit_r_svai.EnableWindow(0);

	m_combo_svai_storona_kvadrata.EnableWindow(0);

	m_edit_sech_X.EnableWindow(1);
	m_edit_sech_Y.EnableWindow(1);	
}

void CDlgPalja::OnRadioRostverkH1() 
{
	if (this->m_do_all)
	{
		// устанавливаем ростверк по первой скважине
		for (vector<MyPalja>::iterator it = this->v_my_palja.begin();
			it != this->v_my_palja.end(); it++)
		{
			if ((*it).ustje_defined && (*it).m_well.m_palja.data2_filled)
			{
				double rostverk_h = (*it).ustje - (*it).m_well.m_palja.data2.pz;

				CString s;
				s.Format("%f", rostverk_h);
				DeleteEndZeros(s);

				this->m_edit_rostverk_H.SetWindowText(s);

				return;
			}
		}

		// или устанавливаем ростверк в нуль
		CString s;
		s.Format("0");
		this->m_edit_rostverk_H.SetWindowText(s);
	}
	else
	{
		if (this->my_palja.ustje_defined && this->my_palja.m_well.m_palja.data2_filled)
		{
			double rostverk_h = this->my_palja.ustje - this->my_palja.m_well.m_palja.data2.pz;

			CString s;
			s.Format("%f", rostverk_h);
			DeleteEndZeros(s);

			this->m_edit_rostverk_H.SetWindowText(s);
		}
		else
		{
			CString s;
			s.Format("0");
			this->m_edit_rostverk_H.SetWindowText(s);
		}
	}	
}

void CDlgPalja::OnRadioRostverkH2() 
{
	if (this->m_do_all)
	{
		// устанавливаем альтитуду ростверка по минимальному устью 
		double min_rostverk = DBL_MAX;

		for (vector<MyPalja>::iterator it = this->v_my_palja.begin();
			it != this->v_my_palja.end(); it++)
		{
			if ((*it).ustje_defined)
			{
				double rostverk_h = (*it).ustje;
				if (min_rostverk > rostverk_h)
					min_rostverk = rostverk_h;
			}
		}

		CString s = "";
		if (min_rostverk != DBL_MAX)
			s.Format("%f", min_rostverk);
		DeleteEndZeros(s);

		this->m_edit_rostverk_H.SetWindowText(s);
	}
	else
	{
		if (this->my_palja.m_well.m_palja.data2_filled)
		{
			double rostverk_h = this->my_palja.m_well.m_palja.data2.pz;

			CString s;
			s.Format("%f", rostverk_h);
			DeleteEndZeros(s);

			this->m_edit_rostverk_H.SetWindowText(s);
		}
	}
}

void CDlgPalja::OnRadioSnip1() 
{
	bool have_typ_zond_1 = false;
	if (this->m_do_all)
	{
		for (vector<MyPalja>::iterator it = this->v_my_palja.begin();
			it != this->v_my_palja.end(); it++)
		{
			if ((*it).typ_zond == 1)
				have_typ_zond_1 = true;
		}

	}
	else
	{
		have_typ_zond_1 = my_palja.typ_zond == 1;
	}

	if (have_typ_zond_1)
	{
		this->m_check_razbivka_na_tolschi.EnableWindow(1);	
		if (this->m_check_razbivka_na_tolschi.GetCheck() == BST_CHECKED)
		{
			this->m_radio_type_grunt_1zt1.EnableWindow(0);
			this->m_radio_type_grunt_1zt2.EnableWindow(0);
			this->m_radio_type_grunt_1zt3.EnableWindow(0);
			this->m_radio_type_grunt_1zt4.EnableWindow(0);
			this->m_static_grunt_type_1zt.EnableWindow(0);
		}
		else
		{
			this->m_radio_type_grunt_1zt1.EnableWindow(1);
			this->m_radio_type_grunt_1zt2.EnableWindow(1);
			this->m_radio_type_grunt_1zt3.EnableWindow(1);
			this->m_radio_type_grunt_1zt4.EnableWindow(1);
			this->m_static_grunt_type_1zt.EnableWindow(1);
		}
	}
	else
	{
		this->m_check_razbivka_na_tolschi.EnableWindow(0);

		this->m_radio_type_grunt_1zt1.EnableWindow(0);
		this->m_radio_type_grunt_1zt2.EnableWindow(0);
		this->m_radio_type_grunt_1zt3.EnableWindow(0);
		this->m_radio_type_grunt_1zt4.EnableWindow(0);
		this->m_static_grunt_type_1zt.EnableWindow(0);

	}

}

void CDlgPalja::OnRadioSnip2() 
{
	this->m_check_razbivka_na_tolschi.EnableWindow(0);

	this->m_radio_type_grunt_1zt1.EnableWindow(0);
	this->m_radio_type_grunt_1zt2.EnableWindow(0);
	this->m_radio_type_grunt_1zt3.EnableWindow(0);
	this->m_radio_type_grunt_1zt4.EnableWindow(0);
	this->m_static_grunt_type_1zt.EnableWindow(0);
}

void CDlgPalja::OnRadioTypGrunt1() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgPalja::OnRadioTypGrunt2() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgPalja::OnCheck1ZondTypeRazbivkaNaTolschi() 
{
	if (this->m_check_razbivka_na_tolschi.GetCheck() == BST_CHECKED)
	{
		this->m_radio_type_grunt_1zt1.EnableWindow(0);
		this->m_radio_type_grunt_1zt2.EnableWindow(0);
		this->m_radio_type_grunt_1zt3.EnableWindow(0);
		this->m_radio_type_grunt_1zt4.EnableWindow(0);
		this->m_static_grunt_type_1zt.EnableWindow(0);
	}
	else
	{
		this->m_radio_type_grunt_1zt1.EnableWindow(1);
		this->m_radio_type_grunt_1zt2.EnableWindow(1);
		this->m_radio_type_grunt_1zt3.EnableWindow(1);
		this->m_radio_type_grunt_1zt4.EnableWindow(1);
		this->m_static_grunt_type_1zt.EnableWindow(1);
	}
}
