// DlgPCK2Fiz.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "EnGeologyView.h"
#include "DlgPCK2Fiz.h"
#include "LabView.h"
#include "SetKT.h"
#include "SetObject.h"
#include "SetPCK2Fiz_CalcParams.h"
#include "SetPCK2Fiz_CalcMode.h"
#include "SetPCK2FizResults.h"

#include "SetPCK2Fiz_CalcModes.h"
#include "SetPodTypyGr.h"
#include "SetPCK2FizTable.h"

#include "SetGrunty.h"
#include "SetStZond.h"
#include "SetUstanovka.h"
#include "SetPtStZond.h"


#include "SetIGE.h"
#include "../../tools/src/filedlg.h"
#include "../../excel_connect/src/ExcelColChar.h"
#include <math.h>

#include <algorithm>
#include <map>
#include <vector>
using namespace std;


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPCK2Fiz dialog

void DeleteEndZeros(CString & str);
CString GetIGE(bool bUnEdited, CDatabase * database, long ID_OBJ, long ID_IGE);
bool GetPCK2FizResult(CDatabase * database, long ID_OBJ, long ID_KT, long NPP, long ID_CALC_PARAM, double & param);
CString GetKTName(CDatabase * database, long ID_OBJ, long ID_KT);

CDlgPCK2Fiz::CDlgPCK2Fiz(CLabView * lab_view, CLabDoc *	lab_doc, CDatabase * database, bool do_all, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPCK2Fiz::IDD, pParent), m_list_pck2fiz(database)
{
	//{{AFX_DATA_INIT(CDlgPCK2Fiz)
	m_edit_contract = _T("");
	m_edit_object = _T("");
	m_radio_method = -1;
	m_vnutr_trenie = -1;
	m_radio_tab = -1;
	//}}AFX_DATA_INIT
	this->m_lab_view = lab_view;
	this->m_lab_doc = lab_doc;
	this->p_database = database;
	m_do_all = do_all;

	m_ID_OBJ = -1;
	m_ID_IGE = -1;
	m_ID_CALC_PARAM = -1;
	m_ID_CALC_METHOD = -1;

	this->m_ID_METHODY = 0;
	m_TAB = -1;
}


void CDlgPCK2Fiz::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPCK2Fiz)
	DDX_Control(pDX, IDC_LIST_PCK2FIZ, m_list_pck2fiz);
	DDX_Control(pDX, IDC_CHECK_SHOW_ONLY_SUITABLE_METHODS, m_check_show_only_suitable_methods);
	DDX_Control(pDX, IDC_STATIC_VID_FORMULY, m_static_vid_formuly);
	DDX_Control(pDX, IDC_RADIO_FORMULA_OR_TAB_1, m_button_tab_1);
	DDX_Control(pDX, IDC_RADIO_FORMULA_OR_TAB_2, m_button_tab_2);
	DDX_Control(pDX, IDC_RADIO_FORMULA_OR_TAB_3, m_button_tab_3);
	DDX_Control(pDX, IDC_STATIC_PCK, m_static_pck);
	DDX_Control(pDX, IDC_STATIC_PCB, m_static_pcb);
	DDX_Control(pDX, IDC_STATIC_PAR, m_static_par);
	DDX_Control(pDX, IDC_STATIC_KL, m_static_KL);
	DDX_Control(pDX, IDC_STATIC_K1, m_static_K1);
	DDX_Control(pDX, IDC_STATIC_K0, m_static_K0);
	DDX_Control(pDX, IDC_EDIT_TAB_ROW_PCK, m_edit_tab_row_pck);
	DDX_Control(pDX, IDC_EDIT_TAB_ROW_PCB, m_edit_tab_row_pcb);
	DDX_Control(pDX, IDC_EDIT_TAB_ROW_PAR, m_edit_tab_row_par);
	DDX_Control(pDX, IDC_BUTTON_SAVE_USER_DEFINED_METHOD, m_button_save_user_defined_method);
	DDX_Control(pDX, IDC_STATIC_VNUTR_TRENIE, m_static_vnutr_trenie);
	DDX_Control(pDX, IDC_RADIO_VNUTR_TRENIE_1, m_button_vnutr_trenie_1);
	DDX_Control(pDX, IDC_RADIO_VNUTR_TRENIE_2, m_button_vnutr_trenie_2);
	DDX_Control(pDX, IDC_EDIT_FOR_TYPZOND, m_edit_for_typzonds);
	DDX_Control(pDX, IDC_COMBO_IGE, m_combo_IGE);
	DDX_Control(pDX, IDC_COMBO_CALC_METHODS, m_combo_calc_methods);
	DDX_Control(pDX, IDC_EDIT_KLOG, m_edit_KLOG);
	DDX_Control(pDX, IDC_EDIT_K1, m_edit_K1);
	DDX_Control(pDX, IDC_EDIT_K0, m_edit_K0);
	DDX_Control(pDX, IDC_EDIT_FORMULA, m_edit_formula);
	DDX_Control(pDX, IDC_COMBO_CALC_PARAMS, m_combo_calc_params);
	DDX_Text(pDX, IDC_EDIT_CONTRACT, m_edit_contract);
	DDX_Text(pDX, IDC_EDIT_OBJECT, m_edit_object);
	DDX_Radio(pDX, IDC_RADIO_METHOD_1, m_radio_method);
	DDX_Radio(pDX, IDC_RADIO_VNUTR_TRENIE_1, m_vnutr_trenie);
	DDX_Radio(pDX, IDC_RADIO_FORMULA_OR_TAB_1, m_radio_tab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPCK2Fiz, CDialog)
	//{{AFX_MSG_MAP(CDlgPCK2Fiz)
	ON_CBN_SELCHANGE(IDC_COMBO_CALC_PARAMS, OnSelchangeComboCalcParams)
	ON_CBN_SELCHANGE(IDC_COMBO_IGE, OnSelchangeComboIge)
	ON_CBN_SELCHANGE(IDC_COMBO_CALC_METHODS, OnSelchangeComboCalcMethods)
	ON_BN_CLICKED(IDC_BUTTON_SET_METHOD_FOR_IGE, OnButtonSetMethodForIge)
	ON_WM_DRAWITEM()
	ON_BN_CLICKED(IDC_RADIO_METHOD_1, OnRadioMethod1)
	ON_BN_CLICKED(IDC_RADIO_METHOD_2, OnRadioMethod2)
	ON_BN_CLICKED(IDC_BUTTON_UNSET_METHOD_FOR_IGE, OnButtonUnsetMethodForIge)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_USER_DEFINED_METHOD, OnButtonSaveUserDefinedMethod)
	ON_BN_CLICKED(IDC_RADIO_FORMULA_OR_TAB_1, OnRadioFormulaOrTab1)
	ON_BN_CLICKED(IDC_RADIO_FORMULA_OR_TAB_2, OnRadioFormulaOrTab2)
	ON_BN_CLICKED(IDC_RADIO_FORMULA_OR_TAB_3, OnRadioFormulaOrTab3)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_RESULTS, OnButtonDeleteResults)
	ON_BN_CLICKED(IDC_CHECK_SHOW_ONLY_SUITABLE_METHODS, OnCheckShowOnlySuitableMethods)
	ON_BN_CLICKED(IDC_BUTTON_EXPORT_TO_EXCEL, OnButtonExportToExcel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

long GetTypeGrunt(bool pck, bool bUnEdited, CDatabase * database, long ID_OBJ, long ID_IGE)
{
	long TYPGR = 0;

	long ID_GR = -1;

	SetIGE setIGE(bUnEdited, database);
	setIGE.m_strFilter.Format("ID_OBJ = %d and ID_IGE = %d", ID_OBJ, ID_IGE);
	setIGE.m_strSort.Format("");
	if ( !setIGE.Open(CRecordset::dynaset) )
		return 0;
	if (!setIGE.IsBOF()) 
	{
		setIGE.MoveFirst( );
		if(!setIGE.IsEOF()) 
		{
			ID_GR = setIGE.m_ID_GR;
		}
	}

	SetGrunty setGrunty(database);
	setGrunty.m_strFilter.Format("ID_OBJ = %d and ID_GR = %d", ID_OBJ, ID_GR);
	setGrunty.m_strSort.Format("");
	if ( !setGrunty.Open(CRecordset::dynaset) )
		return 0;
	if (!setGrunty.IsBOF()) 
	{
		setGrunty.MoveFirst( );
		if(!setGrunty.IsEOF()) 
		{
			if (pck)
				TYPGR = setGrunty.m_TYPGR_PCK;
			else
				TYPGR = setGrunty.m_TYPGR;
		}
	}

	return TYPGR;
}


long GetTypeGrunt(bool pck, bool bUnEdited, CDatabase * database, long ID_OBJ, long ID_KT, double H, long & ID_IGE);

bool GetTypGrDesc(bool bUserDefined, CDatabase * database, long TYPGR_PCK, long PODTYPGR, CString & desc)
{
	SetPodTypyGr setPodTypyGr(bUserDefined, database);
	setPodTypyGr.m_strFilter.Format("TYPGR_PCK = %d and PODTYPGR = %d", TYPGR_PCK, PODTYPGR);
	setPodTypyGr.m_strSort.Format("");
	if ( !setPodTypyGr.Open(CRecordset::dynaset) )
		return false;

	int nIndex = 0;
	if (!setPodTypyGr.IsBOF()) 
	{
		setPodTypyGr.MoveFirst( );
		if(!setPodTypyGr.IsEOF()) 
		{
			desc = setPodTypyGr.m_desc;
			return true;
		}
	}
	return false;
}



bool GetIDCalcMethod(CDatabase * database, long ID_OBJ, long ID_IGE, long ID_CALC_PARAM, BYTE & ID_METHODY, long & ID_CALC_METHOD)
{
	SetPCK2Fiz_CalcMode setPCK2Fiz_CalcMode(database);
	setPCK2Fiz_CalcMode.m_strFilter.Format("ID_OBJ = %d and ID_IGE = %d and ID_CALC_PARAM = %d", ID_OBJ, ID_IGE, ID_CALC_PARAM);
	setPCK2Fiz_CalcMode.m_strSort.Format("ID_CALC_METHOD");
	if ( !setPCK2Fiz_CalcMode.Open(CRecordset::dynaset) )
		return false;

	int nIndex = 0;
	if (!setPCK2Fiz_CalcMode.IsBOF()) 
	{
		setPCK2Fiz_CalcMode.MoveFirst( );
		if(!setPCK2Fiz_CalcMode.IsEOF()) 
		{
			ID_METHODY = setPCK2Fiz_CalcMode.m_ID_METHODY;
			ID_CALC_METHOD = setPCK2Fiz_CalcMode.m_ID_CALC_METHOD;
			return true;
		}
	}
	return false;
}

bool GetCalcMethod(bool bUserDefined, CDatabase * database, long ID_CALC_PARAM, long ID_CALC_METHOD, 
				   BYTE & TAB, BYTE & VNUTR_TRENIE, CString & FORMULA, CString & FOR_TYPZONDS, double & K0, double & K1, double & KLOG,
				   long & TYPGR_PCK, long & PODTYPGR)
{
	SetPCK2Fiz_CalcModes setPCK2Fiz_CalcModes(bUserDefined, database);
	setPCK2Fiz_CalcModes.m_strFilter.Format("ID_CALC_PARAM = %d and ID_CALC_METHOD = %d", ID_CALC_PARAM, ID_CALC_METHOD);
	setPCK2Fiz_CalcModes.m_strSort.Format("");
	if ( !setPCK2Fiz_CalcModes.Open(CRecordset::dynaset) )
		return false;

	int nIndex = 0;
	if (!setPCK2Fiz_CalcModes.IsBOF()) 
	{
		setPCK2Fiz_CalcModes.MoveFirst( );
		if(!setPCK2Fiz_CalcModes.IsEOF()) 
		{
			FORMULA = setPCK2Fiz_CalcModes.m_FORMULA;	
			FOR_TYPZONDS = setPCK2Fiz_CalcModes.m_FOR_TYPZONDS;	

			K0 = setPCK2Fiz_CalcModes.m_K0;
			K1 = setPCK2Fiz_CalcModes.m_K1;
			KLOG = setPCK2Fiz_CalcModes.m_KLOG;

			TYPGR_PCK = setPCK2Fiz_CalcModes.m_TYPGR_PCK;
			PODTYPGR = setPCK2Fiz_CalcModes.m_PODTYPGR;

			VNUTR_TRENIE = setPCK2Fiz_CalcModes.m_VNUTR_TRENIE;
			TAB = setPCK2Fiz_CalcModes.m_TAB;

			return true;
		}
	}
	return false;
}

/////////////////////////////////////////////////////////////////////////////
// CDlgPCK2Fiz message handlers
void CDlgPCK2Fiz::FillCalcMode()
{
	m_ID_CALC_METHOD = -1;
	m_ID_METHODY = 0;


	SetPCK2Fiz_CalcMode setPCK2Fiz_CalcMode(this->p_database);
	setPCK2Fiz_CalcMode.m_strFilter.Format("ID_OBJ = %d and ID_IGE = %d and ID_CALC_PARAM = %d", m_ID_OBJ, m_ID_IGE, m_ID_CALC_PARAM);
	setPCK2Fiz_CalcMode.m_strSort.Format("ID_CALC_METHOD");
	if ( !setPCK2Fiz_CalcMode.Open(CRecordset::dynaset) )
		return;

	int nIndex = 0;
	if (!setPCK2Fiz_CalcMode.IsBOF()) 
	{
		setPCK2Fiz_CalcMode.MoveFirst( );
		if(!setPCK2Fiz_CalcMode.IsEOF()) 
		{
			this->m_ID_METHODY = setPCK2Fiz_CalcMode.m_ID_METHODY;
			this->m_ID_CALC_METHOD = setPCK2Fiz_CalcMode.m_ID_CALC_METHOD;
		}
	}

	ApplyTabRadio();// uses this->m_TAB
	switch(this->m_ID_METHODY)
	{
	case 1:
		{
			this->m_radio_method = 0;
			this->OnRadioMethod1();
		}
		break;
	case 2:
		{
			this->m_radio_method = 1;
			this->OnRadioMethod2();
		}
		break;
	default:
		{
			//this->m_radio_method = -1;
			//this->OnRadioMethod0();
			this->m_radio_method = 0;
			this->OnRadioMethod1();
		}
		break;
	}

	this->FillCalcMethod();
}

void CDlgPCK2Fiz::FillCalcModes()
{
	this->m_combo_calc_methods.ResetContent();

	if (!this->m_ID_METHODY)
		return;

	bool bUserDefined = this->m_ID_METHODY == 2;

	//для вычислений параметров от рск тип грунта берём редактируемый из редактируемой лито-колонки
	bool bUnEdited = false;

	long TYPGR_PCK = GetTypeGrunt(true, bUnEdited, this->p_database, m_ID_OBJ, m_ID_IGE);	

	SetPCK2Fiz_CalcModes setPCK2Fiz_CalcModes(bUserDefined, this->p_database);
	setPCK2Fiz_CalcModes.m_strFilter.Format("ID_CALC_PARAM = %d", m_ID_CALC_PARAM);
	if (TYPGR_PCK && m_ID_CALC_PARAM != 4 && BST_CHECKED == this->m_check_show_only_suitable_methods.GetCheck()) 
		setPCK2Fiz_CalcModes.m_strFilter.Format("TYPGR_PCK = %d and ID_CALC_PARAM = %d", TYPGR_PCK, m_ID_CALC_PARAM);

	setPCK2Fiz_CalcModes.m_strSort.Format("ID_CALC_METHOD");
	if ( !setPCK2Fiz_CalcModes.Open(CRecordset::dynaset) )
		return;

	int nIndex = 0;
	if (!setPCK2Fiz_CalcModes.IsBOF()) 
	{
		setPCK2Fiz_CalcModes.MoveFirst( );
		while(!setPCK2Fiz_CalcModes.IsEOF()) 
		{
			long ID_CALC_METHOD = setPCK2Fiz_CalcModes.m_ID_CALC_METHOD;

			long TYPGR_PCK = setPCK2Fiz_CalcModes.m_TYPGR_PCK;
			long PODTYPGR = setPCK2Fiz_CalcModes.m_PODTYPGR;

			CString desc;
			if (GetTypGrDesc(bUserDefined, this->p_database, TYPGR_PCK, PODTYPGR, desc))
			{
				this->m_combo_calc_methods.AddString(desc);
				this->m_combo_calc_methods.SetItemData(nIndex++, ID_CALC_METHOD);
			}

			setPCK2Fiz_CalcModes.MoveNext();
		}
	}
}
void CDlgPCK2Fiz::ApplyVnutrTrenieRadio(BYTE VNUTR_TRENIE)
{
	switch(VNUTR_TRENIE)
	{
	case 0:
		{
			this->m_static_vnutr_trenie.ShowWindow(0);
			this->m_button_vnutr_trenie_1.ShowWindow(0);
			this->m_button_vnutr_trenie_2.ShowWindow(0);
		}
		break;
	case 1:
		{
			this->m_static_vnutr_trenie.ShowWindow(1);
			this->m_button_vnutr_trenie_1.ShowWindow(1);
			this->m_button_vnutr_trenie_2.ShowWindow(1);

			this->m_vnutr_trenie = 0;
		}
		break;
	case 2:
		{
			this->m_static_vnutr_trenie.ShowWindow(1);
			this->m_button_vnutr_trenie_1.ShowWindow(1);
			this->m_button_vnutr_trenie_2.ShowWindow(1);
			
			this->m_vnutr_trenie = 1;
		}
		break;
	case 3:
		{
			this->m_static_vnutr_trenie.ShowWindow(1);
			this->m_button_vnutr_trenie_1.ShowWindow(1);
			this->m_button_vnutr_trenie_2.ShowWindow(1);
			
			this->m_vnutr_trenie = -1;
		}
		break;
	}
}
void CDlgPCK2Fiz::ApplyTabRadio()
{
	switch(this->m_TAB)
	{
	case 0:
		{
			this->m_radio_tab = 0;
			this->OnRadioFormulaOrTab1();
		}
		break;
	case 1:
		{
			this->m_radio_tab = 1;
			this->OnRadioFormulaOrTab2();
		}
		break;
	case 2:
		{
			this->m_radio_tab = 2;
			this->OnRadioFormulaOrTab3();
		}
		break;
	default:
		{
			this->m_radio_tab = 0;
			this->OnRadioFormulaOrTab1();
		}
		break;
	}

}
void CDlgPCK2Fiz::FreeCalcMethod()
{
	CString s = "";
	this->m_edit_K0.SetWindowText(s);
	this->m_edit_K1.SetWindowText(s);
	this->m_edit_KLOG.SetWindowText(s);
	this->m_edit_formula.SetWindowText(s);
	this->m_edit_for_typzonds.SetWindowText(s);
}
void CDlgPCK2Fiz::FillCalcMethod()
{
	FreeCalcMethod();

	CString FORMULA;
	CString FOR_TYPZONDS;

	double K0, K1, KLOG;
	long TYPGR, PODTYPGR;

	BYTE VNUTR_TRENIE = m_ID_CALC_PARAM == 2 ? 3 : 0;

	bool bUserDefined = this->m_ID_METHODY == 2;

	if (GetCalcMethod(bUserDefined, this->p_database, m_ID_CALC_PARAM, m_ID_CALC_METHOD, m_TAB, VNUTR_TRENIE, FORMULA, FOR_TYPZONDS, K0, K1, KLOG, TYPGR, PODTYPGR))
	{
		m_edit_for_typzonds.SetWindowText(FOR_TYPZONDS);
		this->m_edit_formula.SetWindowText(FORMULA);

		switch(this->m_TAB)
		{
		case 0:
			{
				CString s;
				s.Format("%f", K0); DeleteEndZeros(s);
				this->m_edit_K0.SetWindowText(s);

				s.Format("%f", K1); DeleteEndZeros(s);
				this->m_edit_K1.SetWindowText(s);

				s.Format("%f", KLOG); DeleteEndZeros(s);
				this->m_edit_KLOG.SetWindowText(s);
			}
			break;
		case 1:
		case 2:
			{
				SetPCK2FizTable setPCK2FizTable(bUserDefined, this->p_database);
				setPCK2FizTable.m_strFilter.Format("ID_CALC_METHOD = %d", m_ID_CALC_METHOD);

				setPCK2FizTable.m_strSort.Format("");
				if ( !setPCK2FizTable.Open(CRecordset::dynaset) )
					return;

				string S_pck = "";
				string S_pcb = "";
				string S_par = "";

						CString s_pck = "";
						CString s_pcb = "";
						CString s_par = "";

				int nIndex = 0;
				if (!setPCK2FizTable.IsBOF()) 
				{
					setPCK2FizTable.MoveFirst( );
					while(!setPCK2FizTable.IsEOF()) 
					{
						double	PCK = setPCK2FizTable.m_PCK;
						double	PCB = setPCK2FizTable.m_PCB;
						double	PAR = setPCK2FizTable.m_PAR;


						s_pck.Format("%f", PCK); DeleteEndZeros(s_pck);
						if (this->m_TAB == 2)
							s_pcb.Format("%f", PCB); DeleteEndZeros(s_pcb);
						s_par.Format("%f", PAR); DeleteEndZeros(s_par);

						if(S_pck.size())
						{
							S_pck += ", ";
							if (this->m_TAB == 2)
								S_pcb += ", ";
							S_par += ", ";
						}

						S_pck += s_pck;
						if (this->m_TAB == 2)
							S_pcb += s_pcb;
						S_par += s_par;

						setPCK2FizTable.MoveNext();
					}
				}

				this->m_edit_tab_row_pck.SetWindowText(S_pck.c_str());
				this->m_edit_tab_row_pcb.SetWindowText(S_pcb.c_str());
				this->m_edit_tab_row_par.SetWindowText(S_par.c_str());
			}
			break;
		}
	}

	ApplyTabRadio();// uses this->m_TAB
	ApplyVnutrTrenieRadio(VNUTR_TRENIE);

	this->m_combo_calc_methods.SetCurSel(-1);

	for (int i = 0; i < this->m_combo_calc_methods.GetCount(); i++)
	{
		if (this->m_combo_calc_methods.GetItemData(i) == this->m_ID_CALC_METHOD)
		{
			this->m_combo_calc_methods.SetCurSel(i);
		}
	}

}


BOOL CDlgPCK2Fiz::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	int nObItem = this->m_lab_view->GetObjectItem();

	if (nObItem < 0)
	{
		AfxMessageBox("Не выбрано ни одного объекта");
		CDialog::OnOK();
		return FALSE;
	}

	int nKTItem = -1;

	if (!this->m_do_all)
	{
		nKTItem = this->m_lab_view->GetKTItem();

		if (nKTItem < 0)
		{
			AfxMessageBox("Не выбрано ни одной KT");
			CDialog::OnOK();
			return FALSE;
		}
	}

	m_radio_method = -1;
	OnRadioMethod0();

	this->ApplyVnutrTrenieRadio(0);

	this->m_check_show_only_suitable_methods.SetCheck(BST_CHECKED);


	try
	{
		SetObject setObject(this->p_database);

		if ( !setObject.Open(CRecordset::dynaset) )
			return false;

		setObject.SetAbsolutePosition(nObItem + 1); 
		m_ID_OBJ = setObject.m_ID_OBJ;

		this->m_edit_object = setObject.m_NAZVA;
		m_edit_contract = setObject.m_CONTRACT;
			
		//this->InitDoc();
			
		this->m_list_pck2fiz.OnInitCtrl();
		this->m_list_pck2fiz.InitHeaders();
		this->m_list_pck2fiz.m_ID_OBJ = m_ID_OBJ;


		bool bUnEdited = false;

		SetIGE setIGE(bUnEdited, this->p_database);
		setIGE.m_strFilter.Format("ID_OBJ = %d", m_ID_OBJ);
		setIGE.m_strSort.Format("ID_IGE");
		if ( !setIGE.Open(CRecordset::dynaset) )
			return false;

		int nIndex = 0;
		if (!setIGE.IsBOF()) 
		{
			setIGE.MoveFirst( );
			while(!setIGE.IsEOF()) 
			{
				CString s;
				s.Format("%s   %s", setIGE.m_IGE, setIGE.m_desc0);
				this->m_combo_IGE.AddString(s);
				this->m_combo_IGE.SetItemData(nIndex++, setIGE.m_ID_IGE);
				setIGE.MoveNext();
			}
		}

		SetPCK2Fiz_CalcParams setPCK2Fiz_CalcParams(this->p_database);
		setPCK2Fiz_CalcParams.m_strSort.Format("ID_CALC_PARAM");
		if ( !setPCK2Fiz_CalcParams.Open(CRecordset::dynaset) )
			return false;

		nIndex = 0;
		if (!setPCK2Fiz_CalcParams.IsBOF()) 
		{
			setPCK2Fiz_CalcParams.MoveFirst( );
			while(!setPCK2Fiz_CalcParams.IsEOF()) 
			{
				this->m_combo_calc_params.AddString(setPCK2Fiz_CalcParams.m_desc);
				this->m_combo_calc_params.SetItemData(nIndex++, setPCK2Fiz_CalcParams.m_ID_CALC_PARAM);
				setPCK2Fiz_CalcParams.MoveNext();
			}
		}

		FillCalcModes();

#if 0
		SetKT setKT(this->p_database);
		setKT.m_strFilter.Format("ID_OBJ = %d", m_ID_OBJ);
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
					//this->v_my_palja.push_back(MyPalja(this->p_database, &this->m_SurfDoc));
					//this->v_my_palja.back().KT_nazva = setKT.m_NAZVA;

					//this->v_my_palja.back().ID_KT = setKT.m_ID_KT;
					//this->v_my_palja.back().ID_OBJ = ID_OBJ;
					//this->v_my_palja.back().InitWell();

					//this->m_list_svai.p_well = &this->v_my_palja.back().m_well;
					//this->m_list_svai.ID_KT = setKT.m_ID_KT;
					//this->m_list_svai.ID_OBJ = ID_OBJ;

					//this->FillPaljaHeader(this->v_my_palja.back());

					//this->m_list_svai.FillCtrlList();

					setKT.MoveNext();
				}
			}
		}
		else
		{
			setKT.SetAbsolutePosition(nKTItem + 1);        
			//this->m_edit_tsz = setKT.m_NAZVA;

			//this->my_palja.ID_KT = setKT.m_ID_KT;
			//this->my_palja.ID_OBJ = ID_OBJ;
			//this->my_palja.InitWell();

			//this->m_list_svai.ID_KT = my_palja.ID_KT;
			//this->m_list_svai.ID_OBJ = ID_OBJ;

			//this->m_list_svai.FillCtrlList();
		}




		//this->m_radio_rostverk_h = 0;
		//this->OnRadioRostverkH1();

		//this->m_radio_method_find_mean_pck = 1;
		//this->m_radio_typ_grunt_1_zond_type = 0;

		//this->m_edit_step.SetWindowText(CString("1"));


		//if (this->my_palja.m_well.m_stat_zond.data2_filled)
		//{
		//	long typ_zond = this->m_well.m_stat_zond.data2.typ_zond;
		//	this->m_edit_zond_type.Format("%d", my_palja.typ_zond);
		//}
#endif
		this->m_list_pck2fiz.FillCtrlList();

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

void CDlgPCK2Fiz::OnRadioMethod0() 
{
	this->m_radio_method = -1;
	this->m_ID_METHODY = 0;
	this->m_edit_K0.EnableWindow(0);
	this->m_edit_K1.EnableWindow(0);
	this->m_edit_KLOG.EnableWindow(0);
	this->m_edit_formula.EnableWindow(0);	
	m_edit_for_typzonds.EnableWindow(0);

	this->m_button_vnutr_trenie_1.EnableWindow(0);
	this->m_button_vnutr_trenie_2.EnableWindow(0);

	this->m_button_save_user_defined_method.ShowWindow(0);

	FillCalcModes();
	FreeCalcMethod();
}

void CDlgPCK2Fiz::OnRadioMethod1() 
{
	this->m_radio_method = 0;
	this->m_ID_METHODY = 1;
	this->m_edit_K0.EnableWindow(0);
	this->m_edit_K1.EnableWindow(0);
	this->m_edit_KLOG.EnableWindow(0);
	this->m_edit_formula.EnableWindow(0);	
	m_edit_for_typzonds.EnableWindow(0);

	this->m_button_vnutr_trenie_1.EnableWindow(0);
	this->m_button_vnutr_trenie_2.EnableWindow(0);

	this->m_button_tab_1.EnableWindow(0);
	this->m_button_tab_2.EnableWindow(0);
	this->m_button_tab_3.EnableWindow(0);


	this->m_button_save_user_defined_method.ShowWindow(0);

	FillCalcModes();
	FreeCalcMethod();
}

void CDlgPCK2Fiz::OnRadioMethod2() 
{
	this->m_radio_method = 1;
	this->m_ID_METHODY = 2;
	this->m_edit_K0.EnableWindow(1);
	this->m_edit_K1.EnableWindow(1);
	this->m_edit_KLOG.EnableWindow(1);
	this->m_edit_formula.EnableWindow(1);
	m_edit_for_typzonds.EnableWindow(1);

	this->m_button_vnutr_trenie_1.EnableWindow(1);
	this->m_button_vnutr_trenie_2.EnableWindow(1);

	this->m_button_tab_1.EnableWindow(1);
	this->m_button_tab_2.EnableWindow(1);
	this->m_button_tab_3.EnableWindow(1);

	this->m_button_save_user_defined_method.ShowWindow(1);

	FillCalcModes();
	FreeCalcMethod();
}

void CDlgPCK2Fiz::OnRadioFormulaOrTab1() 
{
	this->m_TAB = 0;
	this->m_radio_tab = 0;

	this->m_edit_K0.ShowWindow(1);
	this->m_edit_K1.ShowWindow(1);
	this->m_edit_KLOG.ShowWindow(1);
	this->m_edit_formula.ShowWindow(1);

	this->m_static_K0.ShowWindow(1);
	this->m_static_K1.ShowWindow(1);
	this->m_static_KL.ShowWindow(1);
	this->m_static_vid_formuly.ShowWindow(1);


	this->m_edit_tab_row_pck.ShowWindow(0);
	this->m_edit_tab_row_pcb.ShowWindow(0);
	this->m_edit_tab_row_par.ShowWindow(0);

	this->m_static_pck.ShowWindow(0);
	this->m_static_pcb.ShowWindow(0);
	this->m_static_par.ShowWindow(0);
}
void CDlgPCK2Fiz::OnRadioFormulaOrTab2() 
{
	this->m_TAB = 1;
	this->m_radio_tab = 1;

	this->m_edit_K0.ShowWindow(0);
	this->m_edit_K1.ShowWindow(0);
	this->m_edit_KLOG.ShowWindow(0);
	this->m_edit_formula.ShowWindow(1);	

	this->m_static_K0.ShowWindow(0);
	this->m_static_K1.ShowWindow(0);
	this->m_static_KL.ShowWindow(0);
	this->m_static_vid_formuly.ShowWindow(0);

	this->m_edit_tab_row_pck.ShowWindow(1);
	this->m_edit_tab_row_pcb.ShowWindow(0);
	this->m_edit_tab_row_par.ShowWindow(1);

	this->m_static_pck.ShowWindow(1);
	this->m_static_pcb.ShowWindow(0);
	this->m_static_par.ShowWindow(1);

}

void CDlgPCK2Fiz::OnRadioFormulaOrTab3() 
{
	this->m_TAB = 2;
	this->m_radio_tab = 2;

	this->m_edit_K0.ShowWindow(0);
	this->m_edit_K1.ShowWindow(0);
	this->m_edit_KLOG.ShowWindow(0);
	this->m_edit_formula.ShowWindow(1);	

	this->m_static_K0.ShowWindow(0);
	this->m_static_K1.ShowWindow(0);
	this->m_static_KL.ShowWindow(0);
	this->m_static_vid_formuly.ShowWindow(0);

	this->m_edit_tab_row_pck.ShowWindow(1);
	this->m_edit_tab_row_pcb.ShowWindow(1);
	this->m_edit_tab_row_par.ShowWindow(1);

	this->m_static_pck.ShowWindow(1);
	this->m_static_pcb.ShowWindow(1);
	this->m_static_par.ShowWindow(1);
	
}

void CDlgPCK2Fiz::OnSelchangeComboCalcParams() 
{
	int index = this->m_combo_calc_params.GetCurSel();
	this->m_ID_CALC_PARAM = long(this->m_combo_calc_params.GetItemData(index));

	FillCalcModes();
	FillCalcMode();
	this->UpdateData(false);
}

void CDlgPCK2Fiz::OnSelchangeComboIge() 
{
	int index = this->m_combo_IGE.GetCurSel();
	this->m_ID_IGE = long(this->m_combo_IGE.GetItemData(index));

	FillCalcMode();
	this->UpdateData(false);
}

void CDlgPCK2Fiz::OnSelchangeComboCalcMethods() 
{
	int index = this->m_combo_calc_methods.GetCurSel();
	this->m_ID_CALC_METHOD = long(this->m_combo_calc_methods.GetItemData(index));

	FillCalcMethod();	
	this->UpdateData(false);
}

void CDlgPCK2Fiz::OnCheckShowOnlySuitableMethods() 
{
	FillCalcMode();
	this->UpdateData(false);	
}
void CDlgPCK2Fiz::OnButtonSetMethodForIge() 
{
	SetPCK2Fiz_CalcMode setPCK2Fiz_CalcMode(this->p_database);
	setPCK2Fiz_CalcMode.m_strFilter.Format("ID_OBJ = %d and ID_IGE = %d and ID_CALC_PARAM = %d", m_ID_OBJ, m_ID_IGE, m_ID_CALC_PARAM);
	setPCK2Fiz_CalcMode.m_strSort.Format("ID_CALC_METHOD");
	if ( !setPCK2Fiz_CalcMode.Open(CRecordset::dynaset) )
		return;


	bool edited = false;
	if (!setPCK2Fiz_CalcMode.IsBOF()) 
	{
		setPCK2Fiz_CalcMode.MoveFirst( );
		if(!setPCK2Fiz_CalcMode.IsEOF()) 
		{
			setPCK2Fiz_CalcMode.Edit();
			setPCK2Fiz_CalcMode.m_ID_OBJ = this->m_ID_OBJ;
			setPCK2Fiz_CalcMode.m_ID_IGE = this->m_ID_IGE;
			setPCK2Fiz_CalcMode.m_ID_CALC_PARAM = this->m_ID_CALC_PARAM;
			setPCK2Fiz_CalcMode.m_ID_METHODY = this->m_ID_METHODY;
			setPCK2Fiz_CalcMode.m_ID_CALC_METHOD = this->m_ID_CALC_METHOD;
			setPCK2Fiz_CalcMode.Update();
			edited = true;
		}
	}
	if(!edited)
	{
		setPCK2Fiz_CalcMode.AddNew();
		setPCK2Fiz_CalcMode.m_ID_OBJ = this->m_ID_OBJ;
		setPCK2Fiz_CalcMode.m_ID_IGE = this->m_ID_IGE;
		setPCK2Fiz_CalcMode.m_ID_CALC_PARAM = this->m_ID_CALC_PARAM;
		setPCK2Fiz_CalcMode.m_ID_METHODY = this->m_ID_METHODY;
		setPCK2Fiz_CalcMode.m_ID_CALC_METHOD = this->m_ID_CALC_METHOD;
		setPCK2Fiz_CalcMode.Update();
	}	
}

void CDlgPCK2Fiz::OnButtonUnsetMethodForIge() 
{
	SetPCK2Fiz_CalcMode setPCK2Fiz_CalcMode(this->p_database);
	setPCK2Fiz_CalcMode.m_strFilter.Format("ID_OBJ = %d and ID_IGE = %d and ID_CALC_PARAM = %d", m_ID_OBJ, m_ID_IGE, m_ID_CALC_PARAM);
	setPCK2Fiz_CalcMode.m_strSort.Format("ID_CALC_METHOD");
	if ( !setPCK2Fiz_CalcMode.Open(CRecordset::dynaset) )
		return;

	if (!setPCK2Fiz_CalcMode.IsBOF()) 
	{
		setPCK2Fiz_CalcMode.MoveFirst( );
		if(!setPCK2Fiz_CalcMode.IsEOF()) 
		{
			setPCK2Fiz_CalcMode.Delete();
		}
	}	
	FillCalcMode();
}
void ParseString(CString s, vector<double> &v)
{
	v.clear();

	int ic;
	while ((ic = s.Find(',')) != -1)
	{
		CString left = s.Mid(0, ic);
		CString right = s.Mid(ic + 1);

		double val = atof(left);
		v.push_back(val);
		s = right;
	}

	if (s.GetLength())
	{
		double val = atof(s);
		v.push_back(val);
	}
}

void CDlgPCK2Fiz::OnButtonSaveUserDefinedMethod() 
{
	this->UpdateData(true);
	// TODO: Add your control notification handler code here
	bool bUserDefined = this->m_ID_METHODY == 2;
	if (!bUserDefined)
		return;

	SetPCK2Fiz_CalcModes setPCK2Fiz_CalcModes(bUserDefined, this->p_database);
	setPCK2Fiz_CalcModes.m_strFilter.Format("ID_CALC_PARAM = %d", m_ID_CALC_PARAM);
	setPCK2Fiz_CalcModes.m_strSort.Format("ID_CALC_METHOD");
	if ( !setPCK2Fiz_CalcModes.Open(CRecordset::dynaset) )
		return;

	long ID_CALC_METHOD = setPCK2Fiz_CalcModes.GetNewCalcMethodID();
	//для вычислений параметров от рск тип грунта берём из редактируемой лито-колонки
	bool bUnEdited = false;
	long TYPGR_PCK = GetTypeGrunt(true, bUnEdited, this->p_database, m_ID_OBJ, m_ID_IGE);
	
	SetPodTypyGr setPodTypyGr(bUserDefined, this->p_database);
	setPodTypyGr.m_strFilter.Format("TYPGR_PCK = %d", TYPGR_PCK);
	setPodTypyGr.m_strSort.Format("");
	if ( !setPodTypyGr.Open(CRecordset::dynaset) )
		return;

	long PODTYPGR = setPodTypyGr.GetNewPodTypyGr();

	BYTE VNUTR_TRENIE = m_ID_CALC_PARAM == 2 ? this->m_vnutr_trenie + 1 : 0;
	BYTE TAB = this->m_TAB;

	CString desc;
	this->m_combo_calc_methods.GetWindowText(desc);

	if (desc.GetLength() == 0)
	{
		AfxMessageBox("Введите характеристику грунтов, для которых вы сохраняете метод расчёта");
		return;
	}

	CString FORMULA;
	CString FOR_TYPZONDS;
	this->m_edit_formula.GetWindowText(FORMULA);
	this->m_edit_for_typzonds.GetWindowText(FOR_TYPZONDS);
		
	double K0 = 0.0, K1 = 0.0, KLOG = 0.0;
	switch(TAB)
	{
	case 0:
		{
			CString s;
			this->m_edit_K0.GetWindowText(s);	K0 = atof(s);
			this->m_edit_K1.GetWindowText(s);	K1 = atof(s);
			this->m_edit_KLOG.GetWindowText(s);	KLOG = atof(s);
		}
		break;
	case 1:
	case 2:
		{
			vector<double> v_pck;
			vector<double> v_pcb;
			vector<double> v_par;

			CString s_pck = "";
			CString s_pcb = "";
			CString s_par = "";

			this->m_edit_tab_row_pck.GetWindowText(s_pck);
			this->m_edit_tab_row_pcb.GetWindowText(s_pcb);
			this->m_edit_tab_row_par.GetWindowText(s_par);

			ParseString(s_pck, v_pck);
			if (TAB == 2)
				ParseString(s_pcb, v_pcb);
			ParseString(s_par, v_par);




			SetPCK2FizTable setPCK2FizTable(bUserDefined, this->p_database);
			setPCK2FizTable.m_strFilter.Format("ID_CALC_METHOD = %d", ID_CALC_METHOD);

			setPCK2FizTable.m_strSort.Format("");
			if ( !setPCK2FizTable.Open(CRecordset::dynaset) )
				return;

			if (v_pck.size() != v_par.size())
			{
				CString serr;
				serr.Format("Число значений РСК = %d\n Не равно числу значений параметра = %d", v_pck.size(), v_par.size());
				AfxMessageBox(serr);

				return;
			}			
			if (TAB == 2)
			{
				if (v_pcb.size() != v_par.size())
				{
					CString serr;
					serr.Format("Число значений РСB = %d\n Не равно числу значений параметра = %d", v_pcb.size(), v_par.size());
					AfxMessageBox(serr);

					return;
				}
			}

			for (size_t i = 0; i < v_par.size(); i++)
			{
				setPCK2FizTable.AddNew();
				setPCK2FizTable.m_ID_CALC_METHOD = ID_CALC_METHOD;
				setPCK2FizTable.m_PCK = v_pck[i];
				if (TAB == 2)
					setPCK2FizTable.m_PCB = v_pcb[i];
				else
					setPCK2FizTable.m_PCB = 0.0;

				setPCK2FizTable.m_PAR = v_par[i];

				setPCK2FizTable.Update();
			}

		}
		break;
	}


	setPodTypyGr.AddNewRow(TYPGR_PCK, PODTYPGR, desc);

	setPCK2Fiz_CalcModes.AddNewRow(TYPGR_PCK, PODTYPGR,
		m_ID_CALC_PARAM, ID_CALC_METHOD, TAB,
		VNUTR_TRENIE, FORMULA, FOR_TYPZONDS,
		K0, K1, KLOG);	

	FillCalcModes();
}
struct pck_par
{
	double m_pck, m_par;
	pck_par (double pck, double par)
	{
		this->m_pck = pck;
		this->m_par = par;
	}
	bool operator<(pck_par & r)
	{
		return this->m_pck < r.m_pck;
	}
};
bool linterp(vector<double> & vx, vector<double> & vy, double x, double &y)
{
	//LINTERP Linear interpolation.
	//
	// YY = LINTERP(X,Y,XX) does a linear interpolation for the given
	//      data:
	//
	//           py: given Y-Axis data
	//           px: given X-Axis data
	//
	//          x: point on X-Axis to be interpolated
	//
	//      output:
	//
	//          y: interpolated value at point "x"


	if (vx.size() != vy.size())
	{
		CString serr;
		serr.Format("В функции linterp длины входных векторов %d %d\nдолжны быть равными", vx.size(), vy.size());
		AfxMessageBox(serr);
		return false;
	}

	int n = vx.size();

	if (n < 2)
	{
		CString serr;
		serr.Format("В функции linterp длины входных векторов %d %d\nдолжны быть не менее 2", vx.size(), vy.size());
		AfxMessageBox(serr);
		return false;
	}

	int j = 1;
	while (j < n-1 && vx[j] < x)
	{
			j++;
	}
	double mu = (x-vx[j-1])/(vx[j]-vx[j-1]);
	y = vy[j-1]+mu*(vy[j]-vy[j-1]);

	return true;
}


bool CDlgPCK2Fiz::CalcKT(long ID_KT)
{
	SetPtStZond setPtStZond(this->p_database);
	setPtStZond.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d", m_ID_OBJ, ID_KT);
	setPtStZond.m_strSort.Format("");
	if ( !setPtStZond.Open(CRecordset::dynaset) )
		return false;
	if (!setPtStZond.IsBOF()) 
	{
		setPtStZond.MoveFirst( );
		while(!setPtStZond.IsEOF()) 
		{
			setPtStZond.MoveNext();
		}
	}
	long rec = setPtStZond.GetRecordCount();

	// в этой KT нет статзондирования
	if (!rec) return false;

	long ID_UST = -1;


	if (!setPtStZond.IsBOF()) 
	{
		setPtStZond.MoveFirst( );
		if(!setPtStZond.IsEOF()) 
		{
			ID_UST = setPtStZond.m_ID_UST;
		}
	}



	SetUstanovka setUstanovka(this->p_database);
	setUstanovka.m_strFilter.Format("");
	setUstanovka.m_strSort.Format("");
	if ( !setUstanovka.Open(CRecordset::dynaset) )
		return false;

	// определяем тип зонда и параметры установки

	double Kg = 0.0;
	double Kf = 0.0;
	double Bg = 0.0;
	double Bf = 0.0;

	long TYP_ZOND = 0;

	if (!setUstanovka.IsBOF()) 
	{
		setUstanovka.MoveFirst( );
		while(!setUstanovka.IsEOF()) 
		{
			if (ID_UST == setUstanovka.m_ID_UST)
			{
				TYP_ZOND = setUstanovka.m_TYP_ZOND;
				
				Kg = setUstanovka.m_Kg;
				Kf = setUstanovka.m_Kf;
				Bg = setUstanovka.m_Bg;
				Bf = setUstanovka.m_Bf;	
			}

			setUstanovka.MoveNext();
		}
	}

	SetPCK2FizResults setPCK2FizResults(this->p_database);
	setPCK2FizResults.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d and ID_CALC_PARAM = %d", m_ID_OBJ, ID_KT, this->m_ID_CALC_PARAM);
	setPCK2FizResults.m_strSort.Format("NPP");
	if ( !setPCK2FizResults.Open(CRecordset::dynaset) )
		return false;

	// сперва очистим таблицу от старых результатов потекущему параметру
	if (!setPCK2FizResults.IsBOF()) 
	{
		setPCK2FizResults.MoveFirst( );
		while(!setPCK2FizResults.IsEOF()) 
		{
			setPCK2FizResults.Delete();
			setPCK2FizResults.MoveNext();
		}
	}


	SetStZond setStZond(this->p_database);
	setStZond.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d", m_ID_OBJ, ID_KT);
	setStZond.m_strSort.Format("NPP");
	if ( !setStZond.Open(CRecordset::dynaset) )
		return false;

	//

	bool not_realized_msg = true;

	if (!setStZond.IsBOF()) 
	{
		setStZond.MoveFirst( );
		while(!setStZond.IsEOF()) 
		{
			double H = setStZond.m_H;
			double q0 = setStZond.m_q0;
			long NPP = setStZond.m_NPP;

			// 1 тип зонда = "Qo";
			// 2,3 тип зонда = "fo";
			double f0 = setStZond.m_f0;	

			//pck
			double qs = setStZond.m_q0 * Kg + Bg;

			// 1 тип зонда = "Qs, кН";
			// 2,3 тип зонда = "f,кПа"; pcb
			double f = setStZond.m_f0 * Kf + Bf;	

			// начинаем расчёт
			if (true)
			{
				// сперва пересчитываем ID_IGE, к которой принадлежит данная точка
				long ID_IGE;
				//для вычислений параметров от рск тип грунта берём из редактируемой лито-колонки
				bool bUnEdited = false;
				long TYPGR_PCK = GetTypeGrunt(true, bUnEdited, this->p_database, m_ID_OBJ, ID_KT, H, ID_IGE);

				setStZond.Edit();
				setStZond.m_ID_IGE = ID_IGE;
				setStZond.m_pck = qs;

				BYTE ID_METHODY;
				long ID_CALC_METHOD;


				if ( GetIDCalcMethod(this->p_database, m_ID_OBJ, ID_IGE, this->m_ID_CALC_PARAM, ID_METHODY, ID_CALC_METHOD))
				{
					BYTE TAB, VNUTR_TRENIE;
					CString FORMULA, FOR_TYPZONDS;
					double K0, K1, KLOG;
					long TYPGR_PCK, PODTYPGR;

					bool bUserDefined = ID_METHODY == 2;

					if (GetCalcMethod(bUserDefined, this->p_database, this->m_ID_CALC_PARAM, ID_CALC_METHOD, 
						TAB, VNUTR_TRENIE, FORMULA, FOR_TYPZONDS, K0, K1, KLOG,
						TYPGR_PCK, PODTYPGR))
					{

						double param = 0.0;
						bool calculed = false;

						switch (TAB)
						{
						case 0:
							{
								param = K0 + K1 * qs + KLOG * log10(qs);
								calculed = true;
							}
							break;
						case 1:
							{
								double pck, pcb, par;

								vector<pck_par> v_pck_par;


								SetPCK2FizTable setPCK2FizTable(bUserDefined, this->p_database);
								setPCK2FizTable.m_strFilter.Format("ID_CALC_METHOD = %d", ID_CALC_METHOD);

								setPCK2FizTable.m_strSort.Format("");
								if ( !setPCK2FizTable.Open(CRecordset::dynaset) )
									return false;

								if (!setPCK2FizTable.IsBOF()) 
								{
									setPCK2FizTable.MoveFirst( );
									while(!setPCK2FizTable.IsEOF()) 
									{
										setPCK2FizTable.m_ID_CALC_METHOD;

										pck = setPCK2FizTable.m_PCK;
										pcb = setPCK2FizTable.m_PCB;
										par = setPCK2FizTable.m_PAR;


										v_pck_par.push_back(pck_par(pck,par));

										setPCK2FizTable.MoveNext();
									}
								}

								std::sort(v_pck_par.begin(), v_pck_par.end());

								vector<double> v_pck;
								vector<double> v_par;
								for (vector<pck_par>::iterator it = v_pck_par.begin();
									it != v_pck_par.end(); it++)
								{									
									v_pck.push_back((*it).m_pck);
									v_par.push_back((*it).m_par);
								}

								if (linterp(v_pck, v_par, qs, param))
								{
									calculed = true;
								}
							}
							break;
						case 2:
							{
								//bool inline linterp2(int nx, double* vx, int ny, double* vy, double ** zz, double x, double y, double &z);
								if (not_realized_msg)
								{
									AfxMessageBox("Режим расчёта параметра от PCK и PCB пока не реализован");
									not_realized_msg = false;
								}
							}
							break;
						case 3:
							{
								switch (this->m_ID_CALC_METHOD)
								{
								case 27:
									{
										//ЕСЛИ (PCB / PCK) < K0=0.01 ТО песок (1) ИНАЧЕ связные (2)
										if ((f*1000/qs) < K0)
										{
											param = 1; 
										}
										else
										{
											param = 2;
										}
										calculed = true;
									}
									break;
								case 28:
									{
										//ЕСЛИ (PCK) >= K0=2 МПа ТО песок (1) ИНАЧЕ связные (2)
										if (qs >= K0) 
										{
											param = 1; 
										}
										else
										{
											param = 2;
										}
										calculed = true;
									}
									break;
								}
							}
							break;
						}
						if (calculed)
						{
							switch (this->m_ID_CALC_PARAM)
							{
							case 1://E
								{
									//setStZond.m_E_def = param;
									setPCK2FizResults.AddNewRow(m_ID_OBJ, ID_KT, NPP, this->m_ID_CALC_PARAM, param);
								}
								break;
							case 2://fi
								{
									switch(VNUTR_TRENIE)
									{
									case 1:
										{
											double fi = atan (param) * 180.0 / PI;
											//setStZond.m_fi = fi;
											setPCK2FizResults.AddNewRow(m_ID_OBJ, ID_KT, NPP, this->m_ID_CALC_PARAM, fi);
										}
										break;
									case 2:
										{
											//setStZond.m_fi = param;
											setPCK2FizResults.AddNewRow(m_ID_OBJ, ID_KT, NPP, this->m_ID_CALC_PARAM, param);
										}
										break;
									}
								}
								break;
							case 3://c
								{
									//setStZond.m_c = param;
									setPCK2FizResults.AddNewRow(m_ID_OBJ, ID_KT, NPP, this->m_ID_CALC_PARAM, param);
								}
								break;
							case 4://isSand
								{
									//setStZond.m_isSand = (BYTE)param;
									setPCK2FizResults.AddNewRow(m_ID_OBJ, ID_KT, NPP, this->m_ID_CALC_PARAM, param);
								}
								break;
							case 5://IL
								{
									//setStZond.m_IL = param;
									setPCK2FizResults.AddNewRow(m_ID_OBJ, ID_KT, NPP, this->m_ID_CALC_PARAM, param);
								}
								break;
							case 6://e
								{
									//setStZond.m_e = param;
									setPCK2FizResults.AddNewRow(m_ID_OBJ, ID_KT, NPP, this->m_ID_CALC_PARAM, param);
								}
								break;	
							}
						}
					}
				}
				setStZond.Update();
			}


			setStZond.MoveNext();
		}
	}
	return true;

}

void CDlgPCK2Fiz::OnOK() 
{		
	SetKT setKT(this->p_database);
	setKT.m_strFilter.Format("ID_OBJ = %d", m_ID_OBJ);
	setKT.m_strSort.Format(CEnGeologyView::str_kt_list_order_by);
	if ( !setKT.Open(CRecordset::dynaset) )
		return;

	if (!setKT.IsBOF()) 
	{
		setKT.MoveFirst( );
		while(!setKT.IsEOF()) 
		{

			long ID_KT = setKT.m_ID_KT;
			
			if(this->CalcKT(ID_KT))
			{
			}

			setKT.MoveNext();
		}
	}
	this->m_list_pck2fiz.FillCtrlList();
}

void CDlgPCK2Fiz::OnButtonDeleteResults() 
{
	SetPCK2FizResults setPCK2FizResults(this->p_database);
	setPCK2FizResults.m_strFilter.Format("ID_OBJ = %d and ID_CALC_PARAM = %d", m_ID_OBJ, this->m_ID_CALC_PARAM);
	setPCK2FizResults.m_strSort.Format("NPP");
	if ( !setPCK2FizResults.Open(CRecordset::dynaset) )
		return;

	// очистим таблицу от старых результатов потекущему параметру
	if (!setPCK2FizResults.IsBOF()) 
	{
		setPCK2FizResults.MoveFirst( );
		while(!setPCK2FizResults.IsEOF()) 
		{
			setPCK2FizResults.Delete();
			setPCK2FizResults.MoveNext();
		}
	}	
	this->m_list_pck2fiz.FillCtrlList();
}


void CDlgPCK2Fiz::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	switch(nIDCtl)
	{
	case IDC_LIST_PCK2FIZ:
		this->m_list_pck2fiz.OnDrawItem(nIDCtl, lpDrawItemStruct);
		break;
	}
	
	//CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CDlgPCK2Fiz::OnButtonExportToExcel() 
{
#if 1
	this->Passport(NULL);
#else
	TCHAR filter[] =
		TEXT("Excel files (*.xls)\0*.xls\0")
		TEXT("All Files (*.*)\0*.*\0");

	char fn_xls[4098];
	sprintf(fn_xls, "\0");
	

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
				this->Passport(fn_xls);
			}
			break;
		}			
	}	
#endif
}

void CDlgPCK2Fiz::InSertTheItem(MyExcel & m_excel, CString & str, int & iActualItem, int iSubItem)
{
	if (iSubItem == 0)
		iActualItem++; // insert new item

	char S[64];
	ExcelColChar ecc('A');

	sprintf(S, "%s%d", ecc.Get(iSubItem), iActualItem);
	ExcelRange_SetValue(m_excel, S, COleVariant(str));
}


bool CDlgPCK2Fiz::IsPtStZond(long ID_KT)
{
	long rec = 0;
	
	SetPtStZond setPtStZond(p_database);
	setPtStZond.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d", m_ID_OBJ, ID_KT);
	setPtStZond.m_strSort.Format("");
	if ( setPtStZond.Open(CRecordset::dynaset) )
	{
		if (!setPtStZond.IsBOF()) 
		{
			setPtStZond.MoveFirst( );
			while(!setPtStZond.IsEOF()) 
			{
				setPtStZond.MoveNext();
			}
		}
	}
	rec = setPtStZond.GetRecordCount();

	return rec > 0;
}
bool CDlgPCK2Fiz::FillKT_or_IGE(MyExcel & m_excel, int & iActualItem, long ID, bool ige)
{
	CString str;


	SetStZond setStZond(p_database);
	if (ige)
	{
		setStZond.m_strFilter.Format("ID_OBJ = %d and ID_IGE = %d", m_ID_OBJ, ID);
		setStZond.m_strSort.Format("ID_KT, NPP");
	}
	else
	{
		setStZond.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d", m_ID_OBJ, ID);
		setStZond.m_strSort.Format("NPP");
	}
	if ( setStZond.Open(CRecordset::dynaset) )
	{
		if (!setStZond.IsBOF()) 
		{
			setStZond.MoveFirst( );
			while(!setStZond.IsEOF()) 
			{
				long ID_KT = setStZond.m_ID_KT;
				CString KT_NAME = GetKTName(this->p_database, m_ID_OBJ, ID_KT);

				int iSubItem = 0;

				str = KT_NAME;
				InSertTheItem(m_excel, str, iActualItem, iSubItem++);

				str.Format("%f", setStZond.m_H);
				DeleteEndZeros(str);
				InSertTheItem(m_excel, str, iActualItem, iSubItem++);

				bool bUnEdited = false;
					
				str = GetIGE(bUnEdited, p_database, m_ID_OBJ, setStZond.m_ID_IGE);
				InSertTheItem(m_excel, str, iActualItem, iSubItem++);

				str.Format("%f", setStZond.m_pck);
				DeleteEndZeros(str);
				InSertTheItem(m_excel, str, iActualItem, iSubItem++);


				long NPP = setStZond.m_NPP;

				SetPCK2Fiz_CalcParams setPCK2Fiz_CalcParams(this->p_database);
				setPCK2Fiz_CalcParams.m_strSort.Format("ID_CALC_PARAM");
				if (setPCK2Fiz_CalcParams.Open(CRecordset::dynaset) )
				{
					if (!setPCK2Fiz_CalcParams.IsBOF()) 
					{
						setPCK2Fiz_CalcParams.MoveFirst( );
						while(!setPCK2Fiz_CalcParams.IsEOF()) 
						{
							double param;

							str = "";

							if (GetPCK2FizResult(p_database, 
								m_ID_OBJ, ID_KT, NPP, setPCK2Fiz_CalcParams.m_ID_CALC_PARAM, param))
							{
								str.Format("%f", param);
								DeleteEndZeros(str);
							}
							InSertTheItem(m_excel, str, iActualItem, iSubItem++);
							setPCK2Fiz_CalcParams.MoveNext();
						}
					}
				}
				setStZond.MoveNext();
			}
		}
	}

	return true;

}



void CDlgPCK2Fiz::Passport_all_KT(MyExcel & m_excel)
{
	int iSubItem = 0;
	int iActualItem = 0;

	InSertHeader(m_excel, iActualItem, iSubItem);


	SetKT setKT(this->p_database);
	setKT.m_strFilter.Format("ID_OBJ = %d", m_ID_OBJ);
	setKT.m_strSort.Format(CEnGeologyView::str_kt_list_order_by);
	if ( !setKT.Open(CRecordset::dynaset) )
		return;

	if (!setKT.IsBOF()) 
	{
		setKT.MoveFirst( );
		while(!setKT.IsEOF()) 
		{
			long ID_KT = setKT.m_ID_KT;
			iSubItem = 0;
			if (this->IsPtStZond(ID_KT))
			{
				if(FillKT_or_IGE(m_excel, iActualItem, ID_KT, false))
				{
				}
			}

			setKT.MoveNext();
		}
	}
}



void CDlgPCK2Fiz::Passport_every_KT(MyExcel & m_excel)
{
	SetKT setKT(this->p_database);
	setKT.m_strFilter.Format("ID_OBJ = %d", m_ID_OBJ);
	setKT.m_strSort.Format(CEnGeologyView::str_kt_list_order_by);
	if ( !setKT.Open(CRecordset::dynaset) )
		return;

	if (!setKT.IsBOF()) 
	{
		setKT.MoveFirst( );
		while(!setKT.IsEOF()) 
		{
			long ID_KT = setKT.m_ID_KT;
			if (this->IsPtStZond(ID_KT))
			{		
				m_excel.AddWorkSheet(setKT.m_NAZVA);
			
				int iSubItem = 0;
				int iActualItem = 0;
				InSertHeader(m_excel, iActualItem, iSubItem);			
				if(FillKT_or_IGE(m_excel, iActualItem, ID_KT, false))
				{
				}
			}

			setKT.MoveNext();
		}
	}
}



void CDlgPCK2Fiz::Passport_every_IGE(MyExcel & m_excel)
{
	bool bUnEdited = false;

	SetIGE setIGE(bUnEdited, this->p_database);
	setIGE.m_strFilter.Format("ID_OBJ = %d", m_ID_OBJ);
	setIGE.m_strSort.Format("");
	if ( !setIGE.Open(CRecordset::dynaset) )
		return;


	if (!setIGE.IsBOF()) 
	{
		setIGE.MoveFirst( );
		while(!setIGE.IsEOF()) 
		{
			long ID_IGE = setIGE.m_ID_IGE;
		
			m_excel.AddWorkSheet(setIGE.m_IGE);
		
			int iSubItem = 0;
			int iActualItem = 0;
			InSertHeader(m_excel, iActualItem, iSubItem);			
			if(FillKT_or_IGE(m_excel, iActualItem, ID_IGE, true))
			{
			}

			InSertMeans(m_excel, iActualItem, iSubItem);



			setIGE.MoveNext();
		}
	}
}



void CDlgPCK2Fiz::InSertHeader(MyExcel & m_excel, int & iActualItem, int iSubItem)
{
	CString str;

	iSubItem = 0;
	str = "KT";
	InSertTheItem(m_excel, str, iActualItem, iSubItem++);
	str = "H";
	InSertTheItem(m_excel, str, iActualItem, iSubItem++);
	str = "ИГЭ";
	InSertTheItem(m_excel, str, iActualItem, iSubItem++);
	str = "ПСК";
	InSertTheItem(m_excel, str, iActualItem, iSubItem++);
	str = "E";
	InSertTheItem(m_excel, str, iActualItem, iSubItem++);
	str = "fi";
	InSertTheItem(m_excel, str, iActualItem, iSubItem++);
	str = "c";
	InSertTheItem(m_excel, str, iActualItem, iSubItem++);
	str = "isSand";
	InSertTheItem(m_excel, str, iActualItem, iSubItem++);
	str = "IL";
	InSertTheItem(m_excel, str, iActualItem, iSubItem++);
	str = "e";
	InSertTheItem(m_excel, str, iActualItem, iSubItem++);
}
/*
bool NormativesCallBack(LabTrialValueType & vt, int sign)
{
	// Знак для коэффициента надёжности
	//int sign = vt.GetSignForReliabilityK();

	char str[4098];
	trial_got_value v;
	vector<trial_got_value> vv;

	sprintf (str, "%s:", vt.GetValueTypeString());

	bool got = false;
	for (vector<LabNumber*>::iterator it = this->lab_numbers.begin();
		it != this->lab_numbers.end(); it++)
	{
		if (*it)
		{
			if ((*it)->GetValue(vt, v))
			{
				v.lab_number = (*it);
				vv.push_back(v);
				got = true;	
			}
		}
	}


	trial_value vn;
	double S;
	double V;
	int n = -1;
	if (got && CalcNormative(vt, vv, n, vn, S, V))
	{
//		if (!vt.IsChecked(this)) text = NULL;
//
//		if (text) text->push_back(fmtstr(str, NULL, false, true));
//
//		sprintf (str, "%d", n);
//		if (text) text->push_back(fmtstr(str, NULL, false, true));
//
//		sprintf (str, "%f", vn.v);
//		DeleteEndZeros(str);
//		if (text) text->push_back(fmtstr(str, NULL, false, true));
//
//		sprintf (str, "%f", S);
//		DeleteEndZeros(str);
//		if (text) text->push_back(fmtstr(str, NULL, false, true));
//
//		sprintf (str, "%f", V);
//		DeleteEndZeros(str);
//		if (text) text->push_back(fmtstr(str, NULL, false, true));


		int K = n - 1;
		double t_alpha;
		trial_value ro_85; //bool calculed_ro_85 = false;
		trial_value ro_95; //bool calculed_ro_95 = false;
		trial_value ro_99; //bool calculed_ro_99 = false;

		alpha_value av = av_085;
		if (Get_t_alpha(av, K, t_alpha))
		{
			ro_85 = t_alpha * V / sqrt(double(n));
//			calculed_ro_85 = true;
		}

		av = av_095;
		if (Get_t_alpha(av, K, t_alpha))
		{
			ro_95 = t_alpha * V / sqrt(double(n));
//			calculed_ro_95 = true;
		}

		av = av_099;
		if (Get_t_alpha(av, K, t_alpha))
		{
			ro_99 = t_alpha * V / sqrt(double(n));
//			calculed_ro_99 = true;
		}


		trial_value v85; bool calculed_v85 = false;
		if (ro_85.f && sign)
		{
			v85 = vn * (1.0 + sign * ro_85);
			sprintf (str, "%f", v85.v);
			DeleteEndZeros(str);
//			if (text) text->push_back(fmtstr(str, NULL, false, true));
			calculed_v85 = true;
		}
		else
		{
//			if (text) text->push_back(fmtstr("", NULL, false, true));
		}

		trial_value v95; bool calculed_v95 = false;
		if (ro_95.f && sign)
		{
			v95 = vn * (1.0 + sign * ro_95);
			sprintf (str, "%f", v95.v);
			DeleteEndZeros(str);
//			if (text) text->push_back(fmtstr(str, NULL, false, true));
			calculed_v95 = true;
		}
		else
		{
//			if (text) text->push_back(fmtstr("", NULL, false, true));
		}

		trial_value v99; bool calculed_v99 = false;
		if (ro_99.f && sign)
		{
			v99 = vn * (1.0 + sign * ro_99);
			sprintf (str, "%f", v99.v);
			DeleteEndZeros(str);
///			if (text) text->push_back(fmtstr(str, NULL, false, true));
			calculed_v99 = true;
		}
		else
		{
//			if (text) text->push_back(fmtstr("", NULL, false, true));
		}

//		if (text) text->push_back(fmtstr("", NULL, true, true));

		if (vt.vt_CutLabTrialResults == CutLabTrialResults::value_type::vt_tgfi)
		{
			trial_value fi_n, fi_85, fi_95, fi_99;

			sprintf (str, "Угол внутреннего трения:");
			if (text) text->push_back(fmtstr(str, NULL, false, true));

			sprintf (str, "%d", n);
			if (text) text->push_back(fmtstr(str, NULL, false, true));

			fi_n = atan(vn.v)/PI*180.;
			sprintf (str, "%f", fi_n.v);
			DeleteEndZeros(str);
			if (text) text->push_back(fmtstr(str, NULL, false, true));

			if (text) text->push_back(fmtstr("", NULL, false, true));
			if (text) text->push_back(fmtstr("", NULL, false, true));
			
			
			if (calculed_v85)
			{
				fi_85 = atan(v85.v)/PI*180.;
				sprintf (str, "%f", fi_85.v);
				DeleteEndZeros(str);
				if (text) text->push_back(fmtstr(str, NULL, false, true));
			}
			else
			{
				if (text) text->push_back(fmtstr("", NULL, false, true));
			}

			if (calculed_v95)
			{
				fi_95 = atan(v95.v)/PI*180.;
				sprintf (str, "%f", fi_95.v);
				DeleteEndZeros(str);
				if (text) text->push_back(fmtstr(str, NULL, false, true));
			}
			else
			{
				if (text) text->push_back(fmtstr("", NULL, false, true));
			}


			if (calculed_v99)
			{
				fi_99 = atan(v99.v)/PI*180.;
				sprintf (str, "%f", fi_99.v);
				DeleteEndZeros(str);
				if (text) text->push_back(fmtstr(str, NULL, false, true));
			}
			else
			{
				if (text) text->push_back(fmtstr("", NULL, false, true));
			}

			if (text) text->push_back(fmtstr("", NULL, true, true));

			LabTrialValueType vt_fi = vt;
			vt_fi.vt_CutLabTrialResults = CutLabTrialResults::value_type::vt_fi;

			if (this->lab_normatives)
				this->lab_normatives->values.insert(map<LabTrialValueType, 
				normative_value>::value_type(vt_fi, 
				normative_value(n, fi_n, fi_85, fi_95, fi_99, S, V, ro_85, ro_95, ro_99)));
		}

		//добавить нормативное значение в склад нормативных значений текущего слоя

		if (this->lab_normatives)
			this->lab_normatives->values.insert(map<LabTrialValueType, normative_value>::value_type(vt, normative_value(n, vn, v85, v95, v99, S, V, ro_85, ro_95, ro_99)));

		return true;
	}	
	else
	{
		switch (vt.m_indication)
		{
		case LabTrial::indication::physical:
			{
				if (vt.is_result)
				{
					if (vt.vt_PhysicalLabTrialResults == PhysicalLabTrialResults::value_type::vt_ground_type)
					{
						bool res = false;
						int norm;
						if (this->CalcNormative(vv, norm))
						{	
							if (vt.IsChecked(this))
							{
								sprintf (str, "%s (by freq):", vt.GetValueTypeString());
								if (text) text->push_back(fmtstr(str, NULL, false, true));

								CGround::ground_type gt = (CGround::ground_type) norm;
								CGround::s_Quantity = CGround::Quantity::singular;
								sprintf (str, "%s", CGround::GrountTypeToStringRus(gt));
								
								if (text) text->push_back(fmtstr(str, NULL, false, true));

								if (text) text->push_back(fmtstr("", NULL, true, true));
								//добавить нормативное значение в склад нормативных значений текущего слоя
								vn = norm;
								//if (this->lab_normatives)
								//	this->lab_normatives->values.insert(map<LabTrialValueType, normative_value>::value_type(vt, normative_value(n, vn, vn, vn, vn)));

								res = true;	
							}
						}
						if (this->lab_normatives)
						{
							// определяем тип грунта
							CGround::ground_type gt = CGround::ground_type::Undefined_ground;
							
							LabTrialValueType vtp;
							vtp.clear();
							vtp.m_indication = LabTrial::indication::physical;
							vtp.is_result = true;
							vtp.vt_PhysicalLabTrialResults = PhysicalLabTrialResults::value_type::vt_plasticity_index;
							vtp.m_lablayer = this;
							
							map<LabTrialValueType, normative_value>::iterator itmp = this->lab_normatives->values.find(vtp);
							if (itmp != this->lab_normatives->values.end())
							{
								// определяем тип грунта
								gt = DefineGroundType((*itmp).second.v_n.v);

								sprintf (str, "%s (by IP):", vt.GetValueTypeString());
								if (text) text->push_back(fmtstr(str, NULL, false, true));

								CGround::s_Quantity = CGround::Quantity::singular;
								sprintf (str, "%s", CGround::GrountTypeToStringRus(gt));
								
								if (text) text->push_back(fmtstr(str, NULL, false, true));

								if (text) text->push_back(fmtstr("", NULL, true, true));
								//добавить нормативное значение в склад нормативных значений текущего слоя
								vn = gt;
								if (this->lab_normatives)
									this->lab_normatives->values.insert(map<LabTrialValueType, normative_value>::value_type(vt, normative_value(n, vn, vn, vn, vn)));

								res = true;	
							}
							else
							{
								if (n >= 6)
								{
									// определяем тип грунта
									gt = CGround::ground_type::Sand;

									sprintf (str, "%s (by no IP):", vt.GetValueTypeString());
									if (text) text->push_back(fmtstr(str, NULL, false, true));

									CGround::s_Quantity = CGround::Quantity::singular;
									sprintf (str, "%s", CGround::GrountTypeToStringRus(gt));
									
									if (text) text->push_back(fmtstr(str, NULL, false, true));

									if (text) text->push_back(fmtstr("", NULL, true, true));
									//добавить нормативное значение в склад нормативных значений текущего слоя
									vn = gt;
									if (this->lab_normatives)
										this->lab_normatives->values.insert(map<LabTrialValueType, normative_value>::value_type(vt, normative_value(n, vn, vn, vn, vn)));

									res = true;	
								}
							}
						}

						return res;
					}
					if (vt.vt_PhysicalLabTrialResults == PhysicalLabTrialResults::value_type::vt_vlazhnost)
					{
						int norm;
						if (this->CalcNormative(vv, norm))
						{	
							if (vt.IsChecked(this))
							{
								sprintf (str, "%s:", vt.GetValueTypeString());
								if (text) text->push_back(fmtstr(str, NULL, false, true));

								PhysicalLabTrialResults::SandVlazhnost vzh = (PhysicalLabTrialResults::SandVlazhnost) norm;
								sprintf (str, "%s", PhysicalLabTrialResults::SandVlazhnostToString(vzh));
								
								if (text) text->push_back(fmtstr(str, NULL, false, true));

								if (text) text->push_back(fmtstr("", NULL, true, true));
								//добавить нормативное значение в склад нормативных значений текущего слоя
								vn = norm;
								if (this->lab_normatives)
									this->lab_normatives->values.insert(map<LabTrialValueType, normative_value>::value_type(vt, normative_value(n, vn, vn, vn, vn)));

								return true;	
							}
						}
					}
					if (vt.vt_PhysicalLabTrialResults == PhysicalLabTrialResults::value_type::vt_Consistencia_nature)
					{
						bool res = false;
						int norm;
						if (this->CalcNormative(vv, norm))
						{	
							if (vt.IsChecked(this))
							{
								sprintf (str, "%s (by freq):", vt.GetValueTypeString());
								if (text) text->push_back(fmtstr(str, NULL, false, true));

								PhysicalLabTrialResults::Consistencia con = (PhysicalLabTrialResults::Consistencia) norm;
								sprintf (str, "%s", PhysicalLabTrialResults::ConsistenciaToString(con));
								
								if (text) text->push_back(fmtstr(str, NULL, false, true));

								if (text) text->push_back(fmtstr("", NULL, true, true));
								//добавить нормативное значение в склад нормативных значений текущего слоя
								vn = norm;
								//if (this->lab_normatives)
								//	this->lab_normatives->values.insert(map<LabTrialValueType, normative_value>::value_type(vt, normative_value(n, vn, vn, vn, vn)));

								res = true;	
							}
						}
						if (this->lab_normatives)
						{
							// определяем IL
							
							LabTrialValueType vtf;
							vtf.clear();
							vtf.m_indication = LabTrial::indication::physical;
							vtf.is_result = true;
							vtf.vt_PhysicalLabTrialResults = PhysicalLabTrialResults::value_type::vt_fluidity_index_nature;
							vtf.m_lablayer = this;							
							map<LabTrialValueType, normative_value>::iterator itmf = this->lab_normatives->values.find(vtf);
							
							// определяем тип грунта by IP
							CGround::ground_type gt = CGround::ground_type::Undefined_ground;
							
							LabTrialValueType vtp;
							vtp.clear();
							vtp.m_indication = LabTrial::indication::physical;
							vtp.is_result = true;
							vtp.vt_PhysicalLabTrialResults = PhysicalLabTrialResults::value_type::vt_plasticity_index;
							vtp.m_lablayer = this;
							
							map<LabTrialValueType, normative_value>::iterator itmp = this->lab_normatives->values.find(vtp);
							
							if (itmp != this->lab_normatives->values.end() && itmf != this->lab_normatives->values.end())
							{
								// определяем тип грунта
								gt = DefineGroundType((*itmp).second.v_n.v);	

								PhysicalLabTrialResults::Consistencia consistencia_nature = PhysicalLabTrialResults::Consistencia::undefined_cons;



								switch (gt)
								{
								case CGround::ground_type::SandyLoam:
									{
										consistencia_nature = 
											Define_SandyLoam_Consistencia((*itmf).second.v_n.v);
									}
									break;
								case CGround::ground_type::Loam:
								case CGround::ground_type::Clay:
									{
										consistencia_nature = 
											Define_ClayAndLoam_Consistencia((*itmf).second.v_n.v);
									}
									break;
								}

								sprintf (str, "%s (by IL):", vt.GetValueTypeString());
								if (text) text->push_back(fmtstr(str, NULL, false, true));

								sprintf (str, "%s", PhysicalLabTrialResults::ConsistenciaToString(consistencia_nature));
								
								if (text) text->push_back(fmtstr(str, NULL, false, true));

								if (text) text->push_back(fmtstr("", NULL, true, true));
								//добавить нормативное значение в склад нормативных значений текущего слоя
								vn = consistencia_nature;
								if (this->lab_normatives)
									this->lab_normatives->values.insert(map<LabTrialValueType, normative_value>::value_type(vt, normative_value(n, vn, vn, vn, vn)));

								res = true;	
							}
						}

						return res;
					}				
					if (vt.vt_PhysicalLabTrialResults == PhysicalLabTrialResults::value_type::vt_Consistencia_water_saturated)
					{
						bool res = false;
						int norm;
						if (this->CalcNormative(vv, norm))
						{	
							if (vt.IsChecked(this))
							{
								sprintf (str, "%s (by freq):", vt.GetValueTypeString());
								if (text) text->push_back(fmtstr(str, NULL, false, true));

								PhysicalLabTrialResults::Consistencia con = (PhysicalLabTrialResults::Consistencia) norm;
								sprintf (str, "%s", PhysicalLabTrialResults::ConsistenciaToString(con));
								
								if (text) text->push_back(fmtstr(str, NULL, false, true));

								if (text) text->push_back(fmtstr("", NULL, true, true));
								//добавить нормативное значение в склад нормативных значений текущего слоя
								vn = norm;
								//if (this->lab_normatives)
								//	this->lab_normatives->values.insert(map<LabTrialValueType, normative_value>::value_type(vt, normative_value(n, vn, vn, vn, vn)));

								res = true;	
							}
						}
						if (this->lab_normatives)
						{
							// определяем IL
							
							LabTrialValueType vtf;
							vtf.clear();
							vtf.m_indication = LabTrial::indication::physical;
							vtf.is_result = true;
							vtf.vt_PhysicalLabTrialResults = PhysicalLabTrialResults::value_type::vt_fluidity_index_water_saturated;
							vtf.m_lablayer = this;							
							map<LabTrialValueType, normative_value>::iterator itmf = this->lab_normatives->values.find(vtf);
							
							// определяем тип грунта by IP
							CGround::ground_type gt = CGround::ground_type::Undefined_ground;
							
							LabTrialValueType vtp;
							vtp.clear();
							vtp.m_indication = LabTrial::indication::physical;
							vtp.is_result = true;
							vtp.vt_PhysicalLabTrialResults = PhysicalLabTrialResults::value_type::vt_plasticity_index;
							vtp.m_lablayer = this;
							
							map<LabTrialValueType, normative_value>::iterator itmp = this->lab_normatives->values.find(vtp);
							
							if (itmp != this->lab_normatives->values.end() && itmf != this->lab_normatives->values.end())
							{
								// определяем тип грунта
								gt = DefineGroundType((*itmp).second.v_n.v);	

								PhysicalLabTrialResults::Consistencia consistencia_water_saturated = PhysicalLabTrialResults::Consistencia::undefined_cons;

								switch (gt)
								{
								case CGround::ground_type::SandyLoam:
									{
										consistencia_water_saturated = 
											Define_SandyLoam_Consistencia((*itmf).second.v_n.v);
									}
									break;
								case CGround::ground_type::Loam:
								case CGround::ground_type::Clay:
									{
										consistencia_water_saturated = 
											Define_ClayAndLoam_Consistencia((*itmf).second.v_n.v);
									}
									break;
								}

								sprintf (str, "%s (by IL):", vt.GetValueTypeString());
								if (text) text->push_back(fmtstr(str, NULL, false, true));

								sprintf (str, "%s", PhysicalLabTrialResults::ConsistenciaToString(consistencia_water_saturated));
								
								if (text) text->push_back(fmtstr(str, NULL, false, true));

								if (text) text->push_back(fmtstr("", NULL, true, true));
								//добавить нормативное значение в склад нормативных значений текущего слоя
								vn = consistencia_water_saturated;
								if (this->lab_normatives)
									this->lab_normatives->values.insert(map<LabTrialValueType, normative_value>::value_type(vt, normative_value(n, vn, vn, vn, vn)));

								res = true;	
							}
						}

						return res;
					}				
				}
			}
			break;

		case LabTrial::indication::fractions:
			{
				if (vt.is_result)
				{
					if (vt.vt_FractionsLabTrialResults == FractionsLabTrialResults::value_type::vt_sand_soil_class)
					{
						int norm;
						if (this->CalcNormative(vv, norm))
						{	
							if (vt.IsChecked(this))
							{
								sprintf (str, "%s:", vt.GetValueTypeString());
								if (text) text->push_back(fmtstr(str, NULL, false, true));

								FractionsLabTrialResults::SandSoilsClass sand_soil_class = (FractionsLabTrialResults::SandSoilsClass) norm;
								sprintf (str, "%s", FractionsLabTrialResults::SandSoilsClassToStringSmall(sand_soil_class));
								
								if (text) text->push_back(fmtstr(str, NULL, false, true));

								if (text) text->push_back(fmtstr("", NULL, true, true));

								//добавить нормативное значение в склад нормативных значений текущего слоя
								vn = norm;
								if (this->lab_normatives)
									this->lab_normatives->values.insert(map<LabTrialValueType, normative_value>::value_type(vt, normative_value(n, vn, vn, vn, vn)));

								return true;
							}
						}
					}
					if (vt.vt_FractionsLabTrialResults == FractionsLabTrialResults::value_type::vt_neodnorodnost)
					{
						int norm;
						if (this->CalcNormative(vv, norm))
						{	
							if (vt.IsChecked(this))
							{
								sprintf (str, "%s:", vt.GetValueTypeString());
								if (text) text->push_back(fmtstr(str, NULL, false, true));

								FractionsLabTrialResults::Neodnorodnost no = (FractionsLabTrialResults::Neodnorodnost) norm;
								sprintf (str, "%s", FractionsLabTrialResults::NeodnorodnostToString(no));
								
								if (text) text->push_back(fmtstr(str, NULL, false, true));

								if (text) text->push_back(fmtstr("", NULL, true, true));

								//добавить нормативное значение в склад нормативных значений текущего слоя
								vn = norm;
								if (this->lab_normatives)
									this->lab_normatives->values.insert(map<LabTrialValueType, normative_value>::value_type(vt, normative_value(n, vn, vn, vn, vn)));

								return true;
							}
						}
					}
				}
			}
			break;
		}
	}
	return false;
}

*/
short f = TRIAL_VALUE_DEFINED_CANNOT_EXCLUDED;
		
void CDlgPCK2Fiz::GetValuesFromExcelColomn(LabLayer * lab_layer, MyExcel & m_excel, char col, int sign, LabTrialValueType & vt, vector<trial_got_value> & vv, int rows)
{
	int iActualItem_n  = rows+1;
	int iActualItem_85 = rows+1+1;
	int iActualItem_95 = rows+1+2;
	int iActualItem_99 = rows+1+3;

	CString str;
	double val;
	char S[64];
	trial_got_value v;
	for (int i = 2; i < rows; i++)
	{
		sprintf(S, "%c%d", col, i);
		if (ExcelRange_GetValue(m_excel, S, val))
		{
			v.v = val;
			v.pf = &f;
			v.lab_number = NULL;
			vv.push_back(v);
		}
	}
	lab_layer->NormativesCallBack_body(sign, true, vv, vt, NULL, NULL);

	map<LabTrialValueType, normative_value>::iterator it = lab_layer->lab_normatives->values.find(vt);
	if (it != lab_layer->lab_normatives->values.end())
	{
		if ((*it).second.v_n.f)
		{
			str.Format("%f", (*it).second.v_n.v);
			sprintf(S, "%c%d", col, iActualItem_n);
			ExcelRange_SetValue(m_excel, S, COleVariant(str));
		}

		if ((*it).second.v_85.f)
		{
			str.Format("%f", (*it).second.v_85.v);
			sprintf(S, "%c%d", col, iActualItem_85);
			ExcelRange_SetValue(m_excel, S, COleVariant(str));
		}

		if ((*it).second.v_95.f)
		{
			str.Format("%f", (*it).second.v_95.v);
			sprintf(S, "%c%d", col, iActualItem_95);
			ExcelRange_SetValue(m_excel, S, COleVariant(str));
		}

		if ((*it).second.v_99.f)
		{
			str.Format("%f", (*it).second.v_99.v);//"E";
			sprintf(S, "%c%d", col, iActualItem_99);
			ExcelRange_SetValue(m_excel, S, COleVariant(str));
		}
	}
}

void CDlgPCK2Fiz::InSertMeans(MyExcel & m_excel, int & iActualItem, int iSubItem)
{
	iActualItem++;

	int iActualItem_n = iActualItem;
	int iActualItem_85 = iActualItem+1;
	int iActualItem_95 = iActualItem+2;
	int iActualItem_99 = iActualItem+3;

	CString str;
	iSubItem = 0;

	str = "Нормативные:";
	InSertTheItem(m_excel, str, iActualItem_n, iSubItem);

	str = "Расчётные 85%:";
	InSertTheItem(m_excel, str, iActualItem_85, iSubItem);

	str = "Расчётные 95%:";
	InSertTheItem(m_excel, str, iActualItem_95, iSubItem);

	str = "Расчётные 99%:";
	InSertTheItem(m_excel, str, iActualItem_99, iSubItem);

	iSubItem++;

	iActualItem++;

	// восстанавливаем значения
	iActualItem_n = iActualItem;
	iActualItem_85 = iActualItem+1;
	iActualItem_95 = iActualItem+2;
	iActualItem_99 = iActualItem+3;



	iSubItem++;// = "H";
	iSubItem++;// = "ИГЭ";

	str.Format("=СРЗНАЧ(D2:D%d)", iActualItem - 1);//"ПСК";
	InSertTheItem(m_excel, str, iActualItem, iSubItem++);

	LabLayer * lab_layer = new LabLayer(NULL, "");

	LabTrialValueType vtE;
	vtE.is_result = true;
	vtE.m_indication = LabTrial::indication::compression_3;
	vtE.vt_Compression_3.com_type = CompressionLabTrial::type::nature_condition;
	vtE.vt_Compression_3.vt_Compression_nature.n_compression_value_type = 2;
	vtE.vt_Compression_3.vt_Compression_nature.com_type = CompressionLabTrial::type::nature_condition;
	vtE.vt_Compression_3.vt_Compression_nature.vt_CompressionLabTrialResults_2 = CompressionLabTrialResults::value_type_2::vt_deformation_module_e_in_01_02_interval_mk;

	vector<trial_got_value> vE;
	GetValuesFromExcelColomn(lab_layer, m_excel, 'E',  -1, vtE, vE, iActualItem - 1);
	

	LabTrialValueType vtfi;
	vtfi.is_result = true;
	vtfi.m_indication = LabTrial::indication::cut_resistance_nature_condition;
	vtfi.vt_CutLabTrialResults = CutLabTrialResults::value_type::vt_fi;

	vector<trial_got_value> vfi;
	GetValuesFromExcelColomn(lab_layer, m_excel, 'F',  -1, vtfi, vfi, iActualItem - 1);

	LabTrialValueType vtc;
	vtc.is_result = true;
	vtc.m_indication = LabTrial::indication::cut_resistance_nature_condition;
	vtc.vt_CutLabTrialResults = CutLabTrialResults::value_type::vt_c;

	vector<trial_got_value> vc;
	GetValuesFromExcelColomn(lab_layer, m_excel, 'G',  -1, vtc, vc, iActualItem - 1);


	LabTrialValueType vtIL;
	vtIL.is_result = true;
	vtIL.m_indication = LabTrial::indication::physical;
	vtIL.vt_PhysicalLabTrialResults = PhysicalLabTrialResults::value_type::vt_fluidity_index_nature;

	vector<trial_got_value> vIL;
	GetValuesFromExcelColomn(lab_layer, m_excel, 'I',  0, vtIL, vIL, iActualItem - 1);

	LabTrialValueType vte;
	vte.is_result = true;
	vte.m_indication = LabTrial::indication::physical;
	vte.vt_PhysicalLabTrialResults = PhysicalLabTrialResults::value_type::vt_e;

	vector<trial_got_value> ve;
	GetValuesFromExcelColomn(lab_layer, m_excel, 'J',  1, vte, ve, iActualItem - 1);



/*
	str.Format("=СРЗНАЧ(F2:F%d)", iActualItem - 1);//"fi";
	InSertTheItem(m_excel, str, iActualItem, iSubItem++);
	str.Format("=СРЗНАЧ(G2:G%d)", iActualItem - 1);//"c";
	InSertTheItem(m_excel, str, iActualItem, iSubItem++);
	str.Format("=СРЗНАЧ(H2:H%d)", iActualItem - 1);//"isSand";
	InSertTheItem(m_excel, str, iActualItem, iSubItem++);
	str.Format("=СРЗНАЧ(I2:I%d)", iActualItem - 1);//"IL";
	InSertTheItem(m_excel, str, iActualItem, iSubItem++);
	str.Format("=СРЗНАЧ(J2:J%d)", iActualItem - 1);//"e";
	InSertTheItem(m_excel, str, iActualItem, iSubItem++);*/
}

void CDlgPCK2Fiz::Passport(const char * fn)
{
	MyExcel m_excel;
	m_excel.ExcelOleLoad();
	if (m_excel.IsApplicationDispatch())
	{
		try
		{
			m_excel.ExcelOleExecute(NULL);

			this->Passport_all_KT(m_excel);
			this->Passport_every_KT(m_excel);
			this->Passport_every_IGE(m_excel);

			//m_excel.m_workbook.Save();
		}
		catch (CException* pe)
		{
			// catch errors from WinINet 
			TCHAR szErr[4098]; 
			pe->GetErrorMessage(szErr, 4098); 
			AfxMessageBox(szErr);
			pe->Delete();
		}
		m_excel.ExcelOleRelease();
	}
	else
	{
		printf("!!!!! m_excel.IsApplicationDispatch()\n");
		AfxMessageBox("!!!!! m_excel.IsApplicationDispatch()\n");
	}
}

