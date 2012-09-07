// labView.cpp : implementation of the CLabView class
//

#include "stdafx.h"
#include "lab.h"

#include "labDoc.h"
#include "labView.h"

#include "DlgSoilName.h"
#include "DlgLabElements.h"

#include "SetObject.h"
#include "SetZriz0.h"
#include "SetZriz.h"
#include "SetZriz_tbl.h"
#include "SetProbGr.h"
#include "SetKT.h"
#include "SetFizMeh.h"
#include "SetGranular.h"
#include "SetCompress.h"
#include "SetCilce.h"
#include "SetCilce0.h"
#include "SetPtStZond.h"
#include "SetStZond.h"

#include "../../wintools/src/project.h"
#include "../../tools/src/filedlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern HINSTANCE hInst;

/////////////////////////////////////////////////////////////////////////////
// CLabView

/////////////////////////////////////////////////////////////////////////////
// CLabView construction/destruction

CLabView::CLabView() : 
	

	m_DBTableCilce0("Cilce0"),
	m_DBTableCilce("Cilce"),
	m_DBTableCompress("Compress"),

	m_DBTableZriz0("Zriz0"),
	m_DBTableZriz("Zriz"),
	m_DBTableZriz_tbl("Zriz_tbl"),

	m_DBTableProp("FizMeh"),
	m_DBTableGranular("Granular"),
	m_DBTableSoils("ProbGr"),

	m_DBTableKT("KT"),

	m_DBTableRozrizy("Rozrizy"),
	m_DBTableRozriz("Rozriz"),

	m_DBTableLito0("Lito0"),
	m_DBTableIGE0("IGE0"),
	m_DBTableLito("Lito"),
	m_DBTableIGE("IGE"),
	m_DBTableGrunty("Grunty"),
	m_DBTableVoda("Voda"),
	m_DBTableGenezis("Genezis"),
	m_DBTableUmPoz("Umpoz"),

	m_DBTableCubeSize("CubeSize"),
	m_DBTableGridDataUsedAlg("GridDataUsedAlgorothms"),

	m_DBTableGridData("Griddata"),
	m_DBTableGridDataSurfaces("GriddataSurfaces"),

	m_DBTableSurfacesOrder("SurfacesOrder"),
	m_DBTableSurfacesBlankOrder("SurfacesBlankOrder"),
	m_DBTableSurfacesBlankFunctions("SurfacesBlankFunctions"),

	m_DBTableSurfIgeMapping("SurfIgeMapping"),
	m_DBTableSurfLitoMapping("SurfLitoMapping"),

	m_DBTablePCK2Fiz_Params("PCK2Fiz_CalcParams"),
	m_DBTablePCK2Fiz_Results("PCK2FizResults"),

	m_DBTablePtStZond("PtStZond"),
	m_DBTableStZond("StZond"),

	m_DBTablePtPalja("PtPalja"),
	m_DBTablePalja("Palja")

{
	//{{AFX_DATA_INIT(CLabView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here

	m_lab_layer = NULL;

	otnosit_def_on_graph = true;
}

CLabView::~CLabView()
{
	m_ID_OBJ = -1;
}


/////////////////////////////////////////////////////////////////////////////
// CLabView diagnostics

#ifdef _DEBUG


#if USE_GET_LAB_DOC
CLabDoc* CLabView::GetDocument() // non-debug version is inline
{
//	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLabDoc)));
	//return (CLabDoc*)m_pDocument;

	return dynamic_cast<CLabDoc*>(m_pDocument);

}
#endif
#endif //_DEBUG

CString GetKTName(CDatabase * database, long id_obj, long id_kt);
CString GetFizMehParamName(CDatabase * database, long id_param);
long GetKTIDType(CDatabase * database, long id_obj, long id_kt);
CString GetGruntName(CDatabase * database, long id_obj, long id_gr);
CString GetGranularFraction(CDatabase * database, long id_gran);
bool GetUstanovka(CDatabase * database, 
				  long id_ust, 

				  CString & ust_name,
				  long & typ_zond,
				  long & n_shema,

				  double & Kg,
				  double & Kf,

				  double & Bg,
				  double & Bf,

				  double & shtanga_d
				  );

bool FillLabNumber(LabNumber * lab_number, CDatabase * database, 
				   long ID_OBJ, long ID_KT, long ID_GR, long ID_PROB, long LAB_N, double H, long ID_KODPROB, CString & grunt_name, long id_ige,
				   bool add_fizmeh_from_db, bool add_granular_from_db, bool add_cut_from_db, int nCutItem, bool add_compress_from_db, int nCompItem, bool add_stat_zond_from_db)
{
	try
	{
		//AddPrGrunt
		CString kt_name = GetKTName(database, ID_OBJ, ID_KT);
		long kt_idtyp = GetKTIDType(database, ID_OBJ, ID_KT);
		CString soil_name = GetGruntName(database, ID_OBJ, ID_GR);
		if (lab_number)
		{
			lab_number->AddPrGrunt(ID_OBJ, ID_KT, kt_name, kt_idtyp, ID_PROB, H,
						 LAB_N, ID_KODPROB, ID_GR, soil_name, grunt_name, id_ige);
		}

		if (add_fizmeh_from_db)
		{
			//AddProp
			SetFizMeh setFizMeh(database);
			setFizMeh.m_strFilter.Format(
				//"ID_OBJ = %d and ID_KT = %d and ID_PROB = %d and ID_VYPROB = %d", 
				"ID_OBJ = %d and ID_KT = %d and ID_PROB = %d", 
				ID_OBJ, ID_KT, ID_PROB/*, ID_VYPROB*/);

			if ( !setFizMeh.Open(CRecordset::dynaset) )
				return false;
			if (!setFizMeh.IsBOF()) 
			{
				setFizMeh.MoveFirst( );

				while(!setFizMeh.IsEOF()) 
				{
					lab_number->AddProp(setFizMeh.m_ID_VYPROB, 
						setFizMeh.m_ID_PARAM, 
						GetFizMehParamName(database, setFizMeh.m_ID_PARAM), 
						setFizMeh.m_VAL);
					setFizMeh.MoveNext(); // to validate record count
				}
			}
			lab_number->ApplyParams();
		}

		if (add_granular_from_db)
		{
			SetGranular setGranular(database);
			setGranular.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d and ID_PROB = %d", ID_OBJ, ID_KT, ID_PROB);
			if ( !setGranular.Open(CRecordset::dynaset) )
				return false;

			if (!setGranular.IsBOF()) 
			{
				setGranular.MoveFirst( );

				while(!setGranular.IsEOF()) 
				{

					lab_number->AddGranular(setGranular.m_ID_GRAN, 
						GetGranularFraction(database, setGranular.m_ID_GRAN), 
						setGranular.m_VAL);

					setGranular.MoveNext(); // to validate record count
				}
			}
			lab_number->ApplyGranular();
		}

		if (add_cut_from_db)
		{
			SetZriz_tbl setZriz_tbl(database);
			setZriz_tbl.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d and ID_PROB = %d", ID_OBJ, ID_KT, ID_PROB);
			if ( !setZriz_tbl.Open(CRecordset::dynaset) )
				return false;

			if (!setZriz_tbl.IsBOF()) 
			{
				setZriz_tbl.MoveFirst( );

				while(!setZriz_tbl.IsEOF()) 
				{
					lab_number->AddZriz_tbl(setZriz_tbl.m_ID_VYPROB, 
						setZriz_tbl.m_ID_KOLCA,
						setZriz_tbl.m_SIGMA, 
						setZriz_tbl.m_TAU, 
						setZriz_tbl.m_W_do, 
						setZriz_tbl.m_Ro_do, 
						setZriz_tbl.m_W_po_upl, 
						setZriz_tbl.m_Ro_po_upl, 
						setZriz_tbl.m_W_after, 
						setZriz_tbl.m_Ro_after, 
						setZriz_tbl.m_bSTAT);
					setZriz_tbl.MoveNext(); // to validate record count
				}
			}

			SetZriz0 setZriz0(database);
			setZriz0.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d and ID_PROB = %d", 
				ID_OBJ, ID_KT, ID_PROB);
			if ( !setZriz0.Open(CRecordset::dynaset) )
				return NULL;

			if (!setZriz0.IsBOF()) 
			{
				setZriz0.MoveFirst( );

				while(!setZriz0.IsEOF()) 
				{
					lab_number->AddZriz0(setZriz0.m_ID_VYPROB, 
						setZriz0.m_ID_KOLCA, 
						setZriz0.m_ID_PHYS_VYPROB, 
						10*setZriz0.m_H, 
						10*setZriz0.m_D, 
						setZriz0.m_DH_PO_UPL, 
						setZriz0.m_M_KOLCA, 
						setZriz0.m_M_GRUNTA, 
						setZriz0.m_M_GRUNTA_ZAMOCH, 
						setZriz0.m_M_GRUNTA_POSLE_UPLOT, 
						setZriz0.m_M_GRUNTA_POSLE, 
						setZriz0.m_M_GRUNTA_VYSUSH);

					setZriz0.MoveNext(); // to validate record count
				}
				
			}

			SetZriz setZriz(database);
			setZriz.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d and ID_PROB = %d", 
				ID_OBJ, ID_KT, ID_PROB);
			if ( !setZriz.Open(CRecordset::dynaset) )
				return NULL;

			if (!setZriz.IsBOF()) 
			{
				setZriz.MoveFirst( );

				while(!setZriz.IsEOF()) 
				{
					lab_number->AddZriz(setZriz.m_ID_VYPROB, 
						setZriz.m_ID_HID, 
						setZriz.m_ID_SHEMA, 
						setZriz.m_ID_STAN, 
						setZriz.m_tgFi, 
						setZriz.m_C, 
						10*setZriz.m_D, 
						10*setZriz.m_H, 
						setZriz.m_bSTAT);

					setZriz.MoveNext(); // to validate record count
				}
				
			}
			lab_number->ApplyZriz(nCutItem);
		}

		if (add_compress_from_db)
		{
			SetCompress setCompress(database);
			setCompress.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d and ID_PROB = %d", 
				ID_OBJ, ID_KT, ID_PROB);
			if ( !setCompress.Open(CRecordset::dynaset) )
				return NULL;

			if (!setCompress.IsBOF()) 
			{
				setCompress.MoveFirst( );

				while(!setCompress.IsEOF()) 
				{
					lab_number->AddCompress(setCompress.m_ID_VYPROB, 
						setCompress.m_SIGMA,
						10*setCompress.m_DH1,
						10*setCompress.m_DH2,
						setCompress.m_VODA,
						setCompress.m_bSTAT);
					setCompress.MoveNext(); // to validate record count
				}
			}


			SetCilce0 setCilce0(database);
			setCilce0.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d and ID_PROB = %d", 
				ID_OBJ, ID_KT, ID_PROB);
			if ( !setCilce0.Open(CRecordset::dynaset) )
				return NULL;

			if (!setCilce0.IsBOF()) 
			{
				setCilce0.MoveFirst( );

				while(!setCilce0.IsEOF()) 
				{
					lab_number->AddCilce0(setCilce0.m_ID_VYPROB, 
						setCilce0.m_ID_KOLCA,
						setCilce0.m_ID_PHYS_VYPROB,
						10*setCilce0.m_H,
						10*setCilce0.m_D,
						setCilce0.m_M_KOLCA,
						setCilce0.m_M_GRUNTA,
						setCilce0.m_M_GRUNTA_ZAMOCH,
						setCilce0.m_M_GRUNTA_POSLE,
						setCilce0.m_M_GRUNTA_VYSUSH);

					setCilce0.MoveNext(); // to validate record count
				}				
			}


			SetCilce setCilce(database);
			setCilce.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d and ID_PROB = %d", 
				ID_OBJ, ID_KT, ID_PROB);
			if ( !setCilce.Open(CRecordset::dynaset) )
				return NULL;

			if (!setCilce.IsBOF()) 
			{
				setCilce.MoveFirst( );

				while(!setCilce.IsEOF()) 
				{
					lab_number->AddCompress(setCilce.m_ID_VYPROB, 
						10*setCilce.m_H,
						10*setCilce.m_D,
						setCilce.m_ES_L1,
						setCilce.m_ES_R1,
						setCilce.m_ES_L2,
						setCilce.m_ES_R2,
						setCilce.m_nju,
						setCilce.m_nju_z,
						setCilce.m_m01,
						setCilce.m_E1,
						setCilce.m_m02,
						setCilce.m_E2,
						setCilce.m_m01v,
						setCilce.m_E1v,
						setCilce.m_m02v,
						setCilce.m_E2v,
						setCilce.m_ID_METHOD,
						setCilce.m_bSTAT,
						setCilce.m_bStatV);

					setCilce.MoveNext(); // to validate record count
				}				
			}
			lab_number->ApplyCompress(true, nCompItem);
		}
		if (add_stat_zond_from_db)
		{
			long typ_zond = -1;

			SetPtStZond setPtStZond(database);
			setPtStZond.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d", 
				ID_OBJ, ID_KT);
			if ( !setPtStZond.Open(CRecordset::dynaset) )
				return NULL;

			if (!setPtStZond.IsBOF()) 
			{
				setPtStZond.MoveFirst( );

				while(!setPtStZond.IsEOF()) 
				{

					CString ust_name;
					long n_shema;
					double  Kg, Kf, Bg, Bf;
					double shtanga_d;
					
					GetUstanovka(database,
						setPtStZond.m_ID_UST, 
						ust_name,
						typ_zond,
						n_shema,
						Kg,Kf,Bg,Bf,  
						shtanga_d);

					lab_number->AddPtStZond(setPtStZond.m_ID_UST,
						setPtStZond.m_GLYB,
						ust_name,
						typ_zond,
						n_shema,
						Kg, Kf, Bg, Bf, shtanga_d);
					
					setPtStZond.m_ID_UST;

					setPtStZond.MoveNext(); 
				}				
			}

			SetStZond setStZond(database);
			setStZond.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d", 
				ID_OBJ, ID_KT);
			if ( !setStZond.Open(CRecordset::dynaset) )
				return NULL;

			StatZondData1 data;
			StatZondData1 data_pre;
			bool has_data_pre = false;

			if (!setStZond.IsBOF()) 
			{
				setStZond.MoveFirst( );

				while(!setStZond.IsEOF()) 
				{
					data.Init(
						setStZond.m_NPP, 
						setStZond.m_TYPGR, 
						setStZond.m_H, 
						setStZond.m_q0, 
						setStZond.m_f0, 
						setStZond.m_dH, 
						setStZond.m_fsr, 
						setStZond.m_bSTAT);

					if (setStZond.m_H == H)
					{
						lab_number->m_stat_zond.Add(data);
					}
					else if (has_data_pre)
					{
						if (H > data_pre.h && H < data.h)
						{
							lab_number->m_stat_zond.Add(data_pre);
							lab_number->m_stat_zond.Add(data);
						}
					}

					data_pre = data;
					has_data_pre = true;

					setStZond.MoveNext(); 
				}
			}
			lab_number->ApplyStZond();
		}
	}
	catch (CDBException* pe) 
	{
		AfxMessageBox(pe->m_strError);
		pe->Delete();
		return false;
	}
	return true;
}

/////////////////////////////////////////////////////////////////////////////
// CLabView message handlers
LabNumber * CLabView::CreateLabNumber(long lab_n, bool add_cut_from_db, int nCutItem, bool add_compress_from_db, int nCompItem, bool add_stat_zond_from_db)
{
	int nObItem = this->GetObjectItem();
	if (nObItem < 0)
	{
		AfxMessageBox("Не выбран объект");
		return NULL;
	}

	int i_prob_gr = GetProbGrItem();
	if (i_prob_gr < 0 && lab_n < 0)
	{
		AfxMessageBox("Не выбрана проба грунта");
		return NULL;
	}
	try
	{
		SetObject setObject(&this->GetLabDoc()->m_database);
		if ( !setObject.Open(CRecordset::dynaset) )
			return NULL;
		setObject.SetAbsolutePosition(nObItem + 1);        
		long ID_OBJ = setObject.m_ID_OBJ;

		SetProbGr setProbGr(&this->GetLabDoc()->m_database);
		if (lab_n < 0)
		{
			if(!GetSetProbGrFilterStr(ID_OBJ, setProbGr.m_strFilter))
			{
				return NULL;
			}
		}
		else
		{
			setProbGr.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
		}

		setProbGr.m_strSort.Format("ID_KT, ID_PROB");
		if ( !setProbGr.Open(CRecordset::dynaset) )
			return NULL;

		long ID_KT = -1;
		long ID_PROB = -1;
		double H = 0.0;
		long LAB_N;
		long ID_KODPROB, ID_GR;
		CString grunt_name;
		long ID_IGE = -1;
		
		if (lab_n < 0)
		{
			setProbGr.SetAbsolutePosition(i_prob_gr + 1);  

			LAB_N = setProbGr.m_LAB_N;
			ID_KT = setProbGr.m_ID_KT;
			ID_PROB = setProbGr.m_ID_PROB;
			H = setProbGr.m_H;
			ID_KODPROB = setProbGr.m_ID_KODPROB;
			ID_GR = setProbGr.m_ID_GR;
			grunt_name = setProbGr.m_GRUNT_NAME;
			ID_IGE = setProbGr.m_ID_IGE;
	
		}
		else
		{
			if (!setProbGr.IsBOF()) 
			{
				setProbGr.MoveFirst();
				while(!setProbGr.IsEOF()) 
				{
					if (lab_n == setProbGr.m_LAB_N)
					{
						LAB_N = setProbGr.m_LAB_N;
						ID_KT = setProbGr.m_ID_KT;
						ID_PROB = setProbGr.m_ID_PROB;
						H = setProbGr.m_H;
						ID_KODPROB = setProbGr.m_ID_KODPROB;
						ID_GR = setProbGr.m_ID_GR;
						grunt_name = setProbGr.m_GRUNT_NAME;
						ID_IGE = setProbGr.m_ID_IGE;

						break;
					}

					setProbGr.MoveNext();
				}
			}

			if (LAB_N < 0)
			{
				CString s;
				s.Format("Лабораторный номер %d не найден в базе", lab_n);
				AfxMessageBox(s);
				return NULL;
			}

		}

		if (ID_KT < 0)
		{
			CString s;
			s.Format("Не найдена выработка");
			AfxMessageBox(s);
		}
		if (ID_PROB < 0)
		{
			CString s;
			s.Format("Не найдена проба грунта");
			AfxMessageBox(s);
		}

		if (ID_KT < 0 || ID_PROB < 0)
			return NULL;

		double _pressure_interval_01_02_0 = 0.1;


		Laboratory * lab = new Laboratory(NULL, _pressure_interval_01_02_0);
		lab->id_obj = ID_OBJ;
		lab->contract = (LPCSTR)setObject.m_CONTRACT;
		lab->object_name = (LPCSTR)setObject.m_NAZVA;
		LabLayer * lab_layer = new LabLayer(lab, "DataBase");
		LabNumber * lab_number = new LabNumber(lab_layer);

		bool add_fizmeh_from_db = true;
		bool add_granular_from_db = true;
		
		if (FillLabNumber(lab_number, &this->GetLabDoc()->m_database, 
					ID_OBJ, ID_KT, ID_GR, ID_PROB, LAB_N, H, ID_KODPROB, grunt_name, ID_IGE, 
					add_fizmeh_from_db, add_granular_from_db, add_cut_from_db, nCutItem, add_compress_from_db, nCompItem, add_stat_zond_from_db))
		{
			return lab_number;
		}
	}
	catch (CDBException* pe) 
	{
		AfxMessageBox(pe->m_strError);
		pe->Delete();
		return NULL;
	}
	return NULL;
}
LabLayer * CLabView::CreateLabLayer(bool add_cut_from_db, bool add_compress_from_db, bool add_stat_zond_from_db)
{
	bool add_fizmeh_from_db = true;
	bool add_granular_from_db = true;

	int nObItem = this->GetObjectItem();
	if (nObItem < 0)
	{
		AfxMessageBox("Не выбран объект");
		return NULL;
	}
	try
	{
		SetObject setObject(&this->GetLabDoc()->m_database);
		if ( !setObject.Open(CRecordset::dynaset) )
			return NULL;
		setObject.SetAbsolutePosition(nObItem + 1);        
		long ID_OBJ = setObject.m_ID_OBJ;

		SetProbGr setProbGr(&this->GetLabDoc()->m_database);			
		setProbGr.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
		setProbGr.m_strSort.Format("ID_KT, ID_PROB");
		if ( !setProbGr.Open(CRecordset::dynaset) )
			return NULL;

		long ID_KT = -1;
		long ID_PROB = -1;
		double H = 0.0;
		long LAB_N;
		long ID_KODPROB, ID_GR;
		CString grunt_name;	
		long ID_IGE = -1;

		double _pressure_interval_01_02_0 = 0.1;
		
		Laboratory * lab = new Laboratory(NULL, _pressure_interval_01_02_0);
		lab->id_obj = ID_OBJ;
		lab->contract = (LPCSTR)setObject.m_CONTRACT;
		lab->object_name = (LPCSTR)setObject.m_NAZVA;

		LabLayer * lab_layer = new LabLayer(lab, "DataBase");
		

		if (!setProbGr.IsBOF()) 
		{
			setProbGr.MoveFirst();
			while(!setProbGr.IsEOF()) 
			{

				LAB_N = setProbGr.m_LAB_N;
				ID_KT = setProbGr.m_ID_KT;
				ID_PROB = setProbGr.m_ID_PROB;
				H = setProbGr.m_H;
				ID_KODPROB = setProbGr.m_ID_KODPROB;
				ID_GR = setProbGr.m_ID_GR;
				grunt_name = setProbGr.m_GRUNT_NAME;
				ID_IGE = setProbGr.m_ID_IGE;

				LabNumber * lab_number = lab_layer->AddNewLabNumber();
				int nCutItem = 0;
				int nCompItem = 0;
				if (!FillLabNumber(lab_number, &this->GetLabDoc()->m_database, 
							ID_OBJ, ID_KT, ID_GR, ID_PROB, LAB_N, H, ID_KODPROB, grunt_name, ID_IGE,
							add_fizmeh_from_db, add_granular_from_db, add_cut_from_db, nCutItem, add_compress_from_db, nCompItem, add_stat_zond_from_db))
				{
				}
				setProbGr.MoveNext();
			}
		}
		return lab_layer;
	}
	catch (CDBException* pe) 
	{
		AfxMessageBox(pe->m_strError);
		pe->Delete();
		return NULL;
	}
	return NULL;
}
void CLabView::ProbgrPasportAllpossible() 
{
	bool add_cut_from_db = true;
	bool add_compress_from_db = true;
	int nCutItem = 0;
	int nCompItem = 0;
	bool add_stat_zond_from_db = false;

	LabNumber * lab_number = this->CreateLabNumber(-1, add_cut_from_db, nCutItem, add_compress_from_db, nCompItem, add_stat_zond_from_db);
	if (!lab_number) return;
	lab_number->CalcProperties();

	TCHAR filter[] =
						TEXT("Excel files (*.xls)\0*.xls\0")
						TEXT("All Files (*.*)\0*.*\0");
	char fn_xls[4098];

	char s[128];
	sprintf(s, "\0", lab_number->GetLabLayer()->layer_number.c_str());
/*#if !CHAR_LAYER_NUMBER_ID
	OemToChar(s,s);
#endif*/
	
	sprintf(fn_xls, "lab_layer_%s_number_%s\0", s, lab_number->ID.c_str());

	char * p = NULL;
	while (p = strchr(fn_xls, '*'))
		*p = 'x';

	DWORD nFilterIndex = 0;
	if (S_OK == SaveFileDlg(NULL, fn_xls, filter, nFilterIndex))
	{
		switch (nFilterIndex)
		{
		case 1:
			lab_number->Passport(fn_xls);
			break;
		}			
	}
}
int CLabView::GetCompressType(int nCompItem)
{
	bool add_cut_from_db = false;
	bool add_compress_from_db = true;
	bool add_stat_zond_from_db = false;
	LabNumber * lab_number = this->CreateLabNumber(-1, add_cut_from_db, -1, add_compress_from_db, nCompItem, add_stat_zond_from_db);
	if (!lab_number) return 0;
	return lab_number->GetCompressType(nCompItem);
}
void CLabView::ProbgrPasportCompress(int nCompItem, int compression_passport_type) 
{
	bool add_cut_from_db = true;
	bool add_compress_from_db = true;
	bool add_stat_zond_from_db = false;
	LabNumber * lab_number = this->CreateLabNumber(-1, add_cut_from_db, -1, add_compress_from_db, nCompItem, add_stat_zond_from_db);
	if (!lab_number) return;
	lab_number->CalcProperties();

	TCHAR filter[] =
						TEXT("Excel files (*.xls)\0*.xls\0")
						TEXT("All Files (*.*)\0*.*\0");
	char fn_xls[4098];

	char s[128];
	sprintf(s, "\0", lab_number->GetLabLayer()->layer_number.c_str());
	
	sprintf(fn_xls, "lab_layer_%s_number_%s\0", s, lab_number->ID.c_str());

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
				lab_number->PassportCompress(fn_xls, -1, compression_passport_type, this->otnosit_def_on_graph);
			}
			break;
		}			
	}
}
void CLabView::SoilPropertyWindow(int nSoilItem)
{
	int nCutItem = 0;// -1;
	int nCompItem = 0;
	bool add_cut_from_db = true;
	bool add_compress_from_db = true;
	bool add_stat_zond_from_db = false;
	LabNumber * lab_number = this->CreateLabNumber(-1, add_cut_from_db, nCutItem, add_compress_from_db, nCompItem, add_stat_zond_from_db);
	if (!lab_number) return;
	lab_number->CalcProperties();


	project::InitFonts();


	this->PropertyWindow(
		Laboratory::context_with_plot, 	// Здесь - значение статических членов в простанстве адресов модуля lab.exe
		NULL/*this->m_pLabView->GetWindow()*/, 
		lab_number);

}

void CLabView::ProbgrPasportCut(int nCutItem, int cut_passport_type) 
{
	bool add_cut_from_db = true;
	bool add_compress_from_db = true;
	bool add_stat_zond_from_db = false;
	LabNumber * lab_number = this->CreateLabNumber(-1, add_cut_from_db, nCutItem, add_compress_from_db, -1, add_stat_zond_from_db);
	if (!lab_number) return;
	lab_number->CalcProperties();

	TCHAR filter[] =
						TEXT("Excel files (*.xls)\0*.xls\0")
						TEXT("All Files (*.*)\0*.*\0");
	char fn_xls[4098];

	char s[128];
	sprintf(s, "\0", lab_number->GetLabLayer()->layer_number.c_str());
	
	sprintf(fn_xls, "lab_layer_%s_number_%s\0", s, lab_number->ID.c_str());

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
				lab_number->PassportCut(fn_xls, -1, cut_passport_type);
			}
			break;
		}			
	}
}

void CLabView::ProbgrPasportGranular(int granular_passport_type) 
{
	bool add_cut_from_db = true;
	bool add_compress_from_db = true;
	bool add_stat_zond_from_db = false;
	LabNumber * lab_number = this->CreateLabNumber(-1, add_cut_from_db, -1, add_compress_from_db, -1, add_stat_zond_from_db);
	if (!lab_number) return;
	lab_number->CalcProperties();

	TCHAR filter[] =
						TEXT("Excel files (*.xls)\0*.xls\0")
						TEXT("All Files (*.*)\0*.*\0");
	char fn_xls[4098];

	char s[128];
	sprintf(s, "\0", lab_number->GetLabLayer()->layer_number.c_str());
	
	sprintf(fn_xls, "lab_layer_%s_number_%s\0", s, lab_number->ID.c_str());

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
				lab_number->PassportGranular(fn_xls, granular_passport_type);
			}
			break;
		}			
	}
}

void CLabView::ProbgrSoilname() 
{
	bool add_cut_from_db = true;
	bool add_compress_from_db = true;
	int nCutItem = 0;
	int nCompItem = 0;
	bool add_stat_zond_from_db = false;
	LabNumber * lab_number = this->CreateLabNumber(-1, add_cut_from_db, nCutItem, add_compress_from_db, nCompItem, add_stat_zond_from_db);
	if (!lab_number) return;
	lab_number->ReCalcProperties(false);

	CDlgSoilName dialog(this, lab_number);
	dialog.DoModal();	
}


bool CLabView::EditObject(const char * contract, const char * object_name)
{
	int nObItem = this->GetObjectItem();
	if (nObItem < 0)
	{
		AfxMessageBox("Не выбран объект");
		return false;
	}

	SetObject setObject(&this->GetLabDoc()->m_database);
	if ( !setObject.Open(CRecordset::dynaset) )
		return false;
	setObject.SetAbsolutePosition(nObItem + 1);        
	long ID_OBJ = setObject.m_ID_OBJ;

	setObject.Edit();

	setObject.m_ID_OBJ = ID_OBJ;
	setObject.m_CONTRACT = contract;
	setObject.m_NAZVA = object_name;

	setObject.Update();

		
	return true;
}	
void CLabView::ProbgrClassification()
{
	bool add_cut_from_db = true;
	bool add_compress_from_db = true;
	bool add_stat_zond_from_db = true;

	if (m_lab_layer) delete m_lab_layer;
		
	m_lab_layer = this->CreateLabLayer(add_cut_from_db, add_compress_from_db, add_stat_zond_from_db);
	if (!m_lab_layer) return;

	m_lab_layer->ReCalcProperties(false, false);


	m_lab_layer->GetSoilDescription(vsd);

	this->m_lab_elements.Init(vsd);

	CDlgLabElements dialog(this, &this->m_lab_elements);
	dialog.DoModal();	

	//CDlgSoilName dialog(this, lab_number);
}
//bool CLabView::context_with_plot = true;

HWND CLabView::hPropertyWindow = NULL; 

tagPOINT CLabView::property_window_pt;
LRESULT CALLBACK LabViewPropertyWndProc_1( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	PAINTSTRUCT ps;
	HDC hdc;

	static HWND hwndButton;

	static vector<fmtstr> text;
	static SIZE text_size;

	static RECT margin; 


	static bool		m_bCaptured;		// Признак захвата мыши
	static tagPOINT		m_pt;				// Текущая позиция мыши

	switch (message) 
	{
	case WM_CREATE :
		{
			text.clear();
			text_size.cx = 0;
			text_size.cy = 0;
			//##################################################
			margin.left = 10;
			margin.right = 10;
			margin.top = 10;
			margin.bottom = 10;
			//##################################################
			CREATESTRUCT *pcs = (CREATESTRUCT *)lParam;
			SetWindowLong(hWnd,	GWL_USERDATA,(LONG)pcs->lpCreateParams);
			//##################################################
			//##################################################
			BaseObject * selected_object = (BaseObject *)GetWindowLong(hWnd, GWL_USERDATA);
			if (selected_object)
				selected_object->PrintfProperties(text);
			hdc = GetWindowDC(hWnd);
			if (selected_object)
				selected_object->Paint(text, hWnd, hdc, margin, text_size, true);

			if (1)
			{
				RECT rect;
				GetWindowRect(hWnd, &rect);
				hwndButton = CreateWindow( 
					"BUTTON",   // predefined class 
					"X",       // button text 
					WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // styles 				 
					// Size and position values are given explicitly, because 
					// the CW_USEDEFAULT constant gives zero values for buttons. 
					rect.right - rect.left - 15,         // starting x position 
					3,         // starting y position 
					10,        // button width 
					10,        // button height 
					hWnd,       // parent window 
					(HMENU)IDCANCEL,       // menu 
					hInst,//(HINSTANCE) GetWindowLong(hWnd, GWL_HINSTANCE), 
					NULL);      // pointer not needed 

			   ShowWindow( hwndButton, SW_SHOW );
			}
		}
		break;

		case WM_PAINT:
			{
				hdc = BeginPaint(hWnd, &ps);
				BaseObject * selected_object = (BaseObject *)GetWindowLong(hWnd, GWL_USERDATA);
				if (selected_object)
					selected_object->Paint(text, hWnd, hdc, margin, text_size, false);
				EndPaint(hWnd, &ps);
			}
			break;
		case WM_LBUTTONDOWN :
			{
				GetCursorPos(&m_pt);
				ScreenToClient(hWnd, &m_pt);

				//====== Захватываем сообщения мыши,
				//====== направляя их в свое окно
				SetCapture(hWnd);
				//====== Запоминаем факт захвата
				m_bCaptured = true;
				//====== Запоминаем координаты курсора
				SetFocus(hWnd);
			}
			break;
		case WM_LBUTTONUP :
			{
				if (m_bCaptured)
				{
					//====== Снимаем флаг захвата мыши
					m_bCaptured = false;
					//====== Отпускаем сообщения мыши
					ReleaseCapture();
				}
			}
			break;
//#if (_WIN32_WINNT >= 0x0400) || (_WIN32_WINDOWS > 0x0400)
		case WM_MOUSEWHEEL :
			{
				float yDelta = (float)(int) wParam; // wheel rotation 
				yDelta /= 300000.f;

				RECT rect;
				GetWindowRect(hWnd,&rect);

				rect.top -= (long)yDelta;

				SetWindowPos(hWnd, HWND_TOP, 
					rect.left, 
					rect.top, 
					0, 0, SWP_NOSIZE);

				//GetClientRect(hWnd,&rect);
				//InvalidateRect(hWnd,&rect, true);
			}
			break;
//#endif
		case WM_MOUSEMOVE :
			{
				if( wParam &  MK_LBUTTON)
				{
					if (m_bCaptured)		// Если был захват,
					{
						POINT pt;
						GetCursorPos(&pt);	

						CLabView::property_window_pt.x = pt.x - m_pt.x;
						CLabView::property_window_pt.y = pt.y - m_pt.y - 1;

						SetWindowPos(hWnd, HWND_TOP, 
							CLabView::property_window_pt.x, 
							CLabView::property_window_pt.y, 
							0, 0, SWP_NOSIZE);

						//RECT rect;
						//GetClientRect(hWnd,&rect);
						//InvalidateRect(hWnd,&rect, true);
					}
				}
			}
			break;
/*		case WM_RBUTTONDOWN:
			{
				Object * selected_object = (Object *)GetWindowLong(hWnd, GWL_USERDATA);
				if (selected_object)
					selected_object->CreateMyPopupMenu(hWnd);
			}
			break;*/

		case WM_CHAR :
			{
				if (wParam == 27)//Esc
				{
					DestroyWindow(hWnd);
				}
			}
			break;
		case WM_COMMAND :
			{
			switch( LOWORD( wParam ) )
			{
			case IDCANCEL :
				{
					DestroyWindow(hWnd);
				}
				break;
			default:
				SendMessage(::GetParent(hWnd), message, wParam, lParam);
			}
         }
         break;
		case WM_DESTROY:
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}
LRESULT CALLBACK LabViewPropertyWndProc_2( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	PAINTSTRUCT ps;
	HDC hdc;

	static HWND hwndButton;

	static vector<LabData> labdata;
	static SIZE text_size;
	static bool text_size_do_not_determined;

	static RECT margin;  

	static bool		m_bCaptured;		// Признак захвата мыши
	static tagPOINT		m_pt;				// Текущая позиция мыши

	switch (message) 
	{
	case WM_CREATE :
		{
			labdata.clear();
			text_size.cx = 0;
			text_size.cy = 0;
			text_size_do_not_determined = true;
			//##################################################
			margin.left = 10;
			margin.right = 10;
			margin.top = 10;
			margin.bottom = 10;
			//##################################################
			CREATESTRUCT *pcs = (CREATESTRUCT *)lParam;
			SetWindowLong(hWnd,	GWL_USERDATA,(LONG)pcs->lpCreateParams);
			//##################################################
			//##################################################
			BaseObject * selected_object = (BaseObject *)GetWindowLong(hWnd, GWL_USERDATA);
			if (selected_object)
				selected_object->PrintfProperties(labdata);

			hdc = GetWindowDC(hWnd);
			if (selected_object)
				selected_object->Paint(labdata, hWnd, hdc, margin, text_size, true);

			if (1)
			{
				RECT rect;
				GetWindowRect(hWnd, &rect);
				hwndButton = CreateWindow( 
					"BUTTON",   // predefined class 
					"X",       // button text 
					WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // styles 				 
					// Size and position values are given explicitly, because 
					// the CW_USEDEFAULT constant gives zero values for buttons. 
					rect.right - rect.left - 15,         // starting x position 
					3,         // starting y position 
					10,        // button width 
					10,        // button height 
					hWnd,       // parent window 
					(HMENU)IDCANCEL,       // menu 
					hInst,//(HINSTANCE) GetWindowLong(hWnd, GWL_HINSTANCE), 
					NULL);      // pointer not needed 

			   ShowWindow( hwndButton, SW_SHOW );
			}
		}
		break;

		case WM_PAINT:
			{
				hdc = BeginPaint(hWnd, &ps);
				BaseObject * selected_object = (BaseObject *)GetWindowLong(hWnd, GWL_USERDATA);
				if (selected_object)
					selected_object->Paint(labdata, hWnd, hdc, margin, text_size, false);
				EndPaint(hWnd, &ps);
			}
			break;
		case WM_LBUTTONDOWN :
			{
				GetCursorPos(&m_pt);
				ScreenToClient(hWnd, &m_pt);
				//====== Захватываем сообщения мыши,
				//====== направляя их в свое окно
				SetCapture(hWnd);
				//====== Запоминаем факт захвата
				m_bCaptured = true;
				//====== Запоминаем координаты курсора
				SetFocus(hWnd);
			}
			break;
		case WM_LBUTTONUP :
			{
				if (m_bCaptured)
				{
					//====== Снимаем флаг захвата мыши
					m_bCaptured = false;
					//====== Отпускаем сообщения мыши
					ReleaseCapture();
				}
			}
			break;
//#if (_WIN32_WINNT >= 0x0400) || (_WIN32_WINDOWS > 0x0400)
		case WM_MOUSEWHEEL :
			{
				float yDelta = (float)(int) wParam; // wheel rotation 
				yDelta /= 300000.f;

				RECT rect;
				GetWindowRect(hWnd,&rect);

				rect.top -= (long)yDelta;

				SetWindowPos(hWnd, HWND_TOP, 
					rect.left, 
					rect.top, 
					0, 0, SWP_NOSIZE);

				//GetClientRect(hWnd,&rect);
				//InvalidateRect(hWnd,&rect, true);
			}
			break;
//#endif
		case WM_MOUSEMOVE :
			{
				if( wParam &  MK_LBUTTON)
				{
					if (m_bCaptured)		// Если был захват,
					{
						POINT pt;
						GetCursorPos(&pt);				
					
						CLabView::property_window_pt.x = pt.x - m_pt.x;
						CLabView::property_window_pt.y = pt.y - m_pt.y - 1;

						SetWindowPos(hWnd, HWND_TOP, 
							CLabView::property_window_pt.x, 
							CLabView::property_window_pt.y,  
							0, 0, SWP_NOSIZE);

						//RECT rect;
						//GetClientRect(hWnd,&rect);
						//InvalidateRect(hWnd,&rect, true);
					}
				}
			}
			break;

/*		case WM_RBUTTONDOWN:
			{
				Object * selected_object = (Object *)GetWindowLong(hWnd, GWL_USERDATA);
				if (selected_object)
					selected_object->CreateMyPopupMenu(hWnd);
			}
			break;*/
		case WM_CHAR :
			{
				if (wParam == 27)//Esc
				{
					DestroyWindow(hWnd);
				}
			}
			break;
		case WM_COMMAND :
			{
				switch( LOWORD( wParam ) )
				{
				case IDCANCEL :
					{
						DestroyWindow(hWnd);
					}
					break;
				default:
					SendMessage(::GetParent(hWnd), message, wParam, lParam);
				}
			}
			break;
		case WM_DESTROY:
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}
LPCTSTR lpszLabViewPropertyWindow_1   = "LabViewPropertyWindow_1";
LPCTSTR lpszLabViewPropertyWindow_2   = "LabViewPropertyWindow_2";
bool RegisterLabViewPropertyWindowClass(int type)
{
	WNDCLASSEX wc;
	// Регистрация класса главного окна приложения.
	//............................................
	wc.style         = CS_HREDRAW | CS_VREDRAW;
	switch(type)
	{
	case 1:
		{
			wc.lpfnWndProc   = (WNDPROC)LabViewPropertyWndProc_1;
			wc.lpszClassName = lpszLabViewPropertyWindow_1;
		}
		break;
	case 2:
		{
			wc.lpfnWndProc   = (WNDPROC)LabViewPropertyWndProc_2;
			wc.lpszClassName = lpszLabViewPropertyWindow_2;
		}
		break;
	}
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hInst;
	wc.hIcon         = NULL;//LoadIcon( hInst, lpszWinGeoidName );
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszMenuName  = NULL;
	wc.cbSize        = sizeof(WNDCLASSEX);
	wc.hIconSm       = NULL;

	if ( !RegisterClassEx( &wc ) )
	{
		if(1410 != GetLastError())// класс уже существует
		{
			MessageBox(0,"!RegisterClassEx","ProrertyWindow",0);
			return( FALSE );
		}
	}
	return true;
}
//HWND Object::hPropertyWindow = NULL; 

bool CLabView::PropertyWindow(bool context_with_plot, HWND hWndParent, BaseObject * pOb)
{					
	//printf("CLabView::PropertyWindow\n");

	long x = CLabView::property_window_pt.x;
	long y = CLabView::property_window_pt.y; 

	if (x < 0)	x = 0;
	if (y < 0)	y = 0;

	if (hPropertyWindow)
	{
		DestroyWindow(hPropertyWindow);
		hPropertyWindow = NULL;
	}

	if (!hPropertyWindow)
	{
		//printf("CLabView::PropertyWindow if (!hPropertyWindow)\n");

		hPropertyWindow = CreateWindow(context_with_plot ? lpszLabViewPropertyWindow_2 : lpszLabViewPropertyWindow_1,
			"",//    LPCTSTR lpWindowName,
			WS_POPUP | WS_BORDER,
			x,y,
			1,//int nWidth,
			1,//   int nHeight,
			hWndParent,
			NULL,//    HMENU hMenu,
			hInst,//HINSTANCE hInstance,
			LPVOID(pOb)//LPVOID lpParam
			);

		ShowWindow(hPropertyWindow, SW_SHOW);
	}

	return true;
}
void CLabView::ReCreatePropertyWindow(bool context_with_plot /*BaseObject * pOb*/)
{
	HWND hWndParent = ::GetParent(hPropertyWindow);
	RECT rect;
	GetWindowRect(hPropertyWindow, &rect);
			
	BaseObject * pOb = (BaseObject *)GetWindowLong(hPropertyWindow, GWL_USERDATA);

	DestroyWindow(hPropertyWindow);
	hPropertyWindow = CreateWindow(context_with_plot ? lpszLabViewPropertyWindow_2 : lpszLabViewPropertyWindow_1,
		"",//    LPCTSTR lpWindowName,
		WS_POPUP | WS_BORDER, //DWORD dwStyle,
		rect.left,
		rect.top,
		1,//int nWidth,
		1,//   int nHeight,
		hWndParent,//this->hSurfWnd,//HWND hWndParent,
		NULL,//    HMENU hMenu,
		hInst,//HINSTANCE hInstance,
		LPVOID(pOb)//LPVOID lpParam
		);

	ShowWindow(hPropertyWindow, 1);
}
