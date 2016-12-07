// LaboratoryView.cpp: implementation of the CLaboratoryView class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "LaboratoryView.h"


#include "ObjectDialog.h"
#include "DlgProbGrunt.h"
#include "DlgLanguage.h"
#include "DlgProbGr_DblClickMode.h"
#include "DlgRepeatings.h"



#include "SetGeoTables.h"
#include "SetObject.h"
#include "SetProbGr.h"
#include "SetCilce.h"
#include "SetCompress.h"
#include "SetZriz.h"
#include "SetZriz_tbl.h"

#include "ObjectRecordset.h"
#include "KtSet.h"

#include "../../laboratory/src/lab.h"
#include "../../tools/src/filedlg.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CString CLaboratoryView::str_kt_list_order_by = "ID_KT";
CString CLaboratoryView::str_kt_list_where = "ID_OBJ = -1";

void DaoErrorMsg(CDaoException* e);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(CLaboratoryView, CFormView)


BEGIN_MESSAGE_MAP(CLaboratoryView, CFormView)
	//{{AFX_MSG_MAP(CLaboratoryView)
	ON_WM_DRAWITEM()
	ON_COMMAND(ID_LABORATORY_SANDGRANULAR_LOADFORM_NEW, OnLaboratorySandGranularLoadFormNew)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_SANDGRANULAR_LOADFORM_NEW, OnUpdateLaboratorySandGranularLoadFormNew)
	ON_COMMAND(ID_LABORATORY_SANDGRANULAR_LOADFORM_EXISTING, OnLaboratorySandGranularLoadFormExisting)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_SANDGRANULAR_LOADFORM_EXISTING, OnUpdateLaboratorySandGranularLoadFormExisting)
	ON_COMMAND(ID_LABORATORY_SANDGRANULAR_COMPUTE, OnLaboratorySandGranularCompute)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_SANDGRANULAR_COMPUTE, OnUpdateLaboratorySandGranularCompute)
	ON_COMMAND(ID_LABORATORY_SANDGRANULAR_SAVETODB, OnLaboratorySandGranularSaveToDB)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_SANDGRANULAR_SAVETODB, OnUpdateLaboratorySandGranularSaveToDB)
	ON_COMMAND(ID_LABORATORY_SANDGRANULAR_DISCONNECTEXCEL, OnLaboratorySandgranularDisconnectExcel)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_SANDGRANULAR_DISCONNECTEXCEL, OnUpdateLaboratorySandGranularDisconnectExcel)
	ON_COMMAND(ID_FILE_NEW, OnFileNewObject)
	ON_COMMAND(ID_FILE_DELETEOBJECT, OnFileDeleteObject)
	ON_UPDATE_COMMAND_UI(ID_FILE_DELETEOBJECT, OnUpdateFileDeleteObject)
	ON_COMMAND(ID_LABORATORY_AREOMETRGRANULAR_LOADFORM_NEW, OnLaboratoryAreometrGranularLoadFormNew)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_AREOMETRGRANULAR_LOADFORM_NEW, OnUpdateLaboratoryAreometrGranularLoadFormNew)
	ON_COMMAND(ID_LABORATORY_AREOMETRGRANULAR_LOADFORM_EXISTING, OnLaboratoryAreometrGranularLoadFormExisting)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_AREOMETRGRANULAR_LOADFORM_EXISTING, OnUpdateLaboratoryAreometrGranularLoadFormExisting)
	ON_COMMAND(ID_LABORATORY_AREOMETRGRANULAR_COMPUTE, OnLaboratoryAreometrGranularCompute)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_AREOMETRGRANULAR_COMPUTE, OnUpdateLaboratoryAreometrGranularCompute)
	ON_COMMAND(ID_LABORATORY_AREOMETRGRANULAR_SAVETODB, OnLaboratoryAreometrGranularSaveToDB)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_AREOMETRGRANULAR_SAVETODB, OnUpdateLaboratoryAreometrGranularSaveToDB)
	ON_COMMAND(ID_LABORATORY_AREOMETRGRANULAR_DISCONNECTEXCEL, OnLaboratoryAreometrGranularDisconnectExcel)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_AREOMETRGRANULAR_DISCONNECTEXCEL, OnUpdateLaboratoryAreometrGranularDisconnectExcel)
	ON_COMMAND(ID_LABORATORY_VEGETABLEREMAINS_LOADFORM_NEW, OnLaboratoryVegetableRemainsLoadFormNew)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_VEGETABLEREMAINS_LOADFORM_NEW, OnUpdateLaboratoryVegetableRemainsLoadFormNew)
	ON_COMMAND(ID_LABORATORY_VEGETABLEREMAINS_LOADFORM_EXISTING, OnLaboratoryVegetableRemainsLoadFormExisting)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_VEGETABLEREMAINS_LOADFORM_EXISTING, OnUpdateLaboratoryVegetableRemainsLoadFormExisting)
	ON_COMMAND(ID_LABORATORY_VEGETABLEREMAINS_COMPUTE, OnLaboratoryVegetableRemainsCompute)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_VEGETABLEREMAINS_COMPUTE, OnUpdateLaboratoryVegetableRemainsCompute)
	ON_COMMAND(ID_LABORATORY_VEGETABLEREMAINS_SAVETODB, OnLaboratoryVegetableRemainsSavetodb)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_VEGETABLEREMAINS_SAVETODB, OnUpdateLaboratoryVegetableRemainsSavetodb)
	ON_COMMAND(ID_LABORATORY_VEGETABLEREMAINS_DISCONNECTEXCEL, OnLaboratoryVegetableRemainsDisconnectExcel)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_VEGETABLEREMAINS_DISCONNECTEXCEL, OnUpdateLaboratoryVegetableRemainsDisconnectExcel)
	ON_COMMAND(ID_LABORATORY_PLOTNOSTCHASTIC_LOADFORM_NEW, OnLaboratoryPlotnostChasticLoadFormNew)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_PLOTNOSTCHASTIC_LOADFORM_NEW, OnUpdateLaboratoryPlotnostChasticLoadFormNew)
	ON_COMMAND(ID_LABORATORY_PLOTNOSTCHASTIC_LOADFORM_EXISTING, OnLaboratoryPlotnostChasticLoadFormExisting)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_PLOTNOSTCHASTIC_LOADFORM_EXISTING, OnUpdateLaboratoryPlotnostChasticLoadFormExisting)
	ON_COMMAND(ID_LABORATORY_PLOTNOSTCHASTIC_COMPUTE, OnLaboratoryPlotnostChasticCompute)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_PLOTNOSTCHASTIC_COMPUTE, OnUpdateLaboratoryPlotnostChasticCompute)
	ON_COMMAND(ID_LABORATORY_PLOTNOSTCHASTIC_SAVETODB, OnLaboratoryPlotnostChasticSavetodb)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_PLOTNOSTCHASTIC_SAVETODB, OnUpdateLaboratoryPlotnostChasticSavetodb)
	ON_COMMAND(ID_LABORATORY_PLOTNOSTCHASTIC_DISCONNECTEXCEL, OnLaboratoryPlotnostChasticDisconnectExcel)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_PLOTNOSTCHASTIC_DISCONNECTEXCEL, OnUpdateLaboratoryPlotnostChasticDisconnectExcel)
	ON_COMMAND(ID_LABORATORY_PLOTNOSTGRUNTA_LOADFORM_NEW, OnLaboratoryPlotnostGruntaLoadFormNew)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_PLOTNOSTGRUNTA_LOADFORM_NEW, OnUpdateLaboratoryPlotnostGruntaLoadFormNew)
	ON_COMMAND(ID_LABORATORY_PLOTNOSTGRUNTA_LOADFORM_EXISTING, OnLaboratoryPlotnostGruntaLoadFormExisting)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_PLOTNOSTGRUNTA_LOADFORM_EXISTING, OnUpdateLaboratoryPlotnostGruntaLoadFormExisting)
	ON_COMMAND(ID_LABORATORY_PLOTNOSTGRUNTA_COMPUTE, OnLaboratoryPlotnostGruntaCompute)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_PLOTNOSTGRUNTA_COMPUTE, OnUpdateLaboratoryPlotnostGruntaCompute)
	ON_COMMAND(ID_LABORATORY_PLOTNOSTGRUNTA_SAVETODB, OnLaboratoryPlotnostGruntaSavetodb)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_PLOTNOSTGRUNTA_SAVETODB, OnUpdateLaboratoryPlotnostGruntaSavetodb)
	ON_COMMAND(ID_LABORATORY_PLOTNOSTGRUNTA_DISCONNECTEXCEL, OnLaboratoryPlotnostGruntaDisconnectExcel)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_PLOTNOSTGRUNTA_DISCONNECTEXCEL, OnUpdateLaboratoryPlotnostGruntaDisconnectExcel)
	ON_COMMAND(ID_LABORATORY_W_LOADFORM_NEW, OnLaboratoryWLoadformNew)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_W_LOADFORM_NEW, OnUpdateLaboratoryWLoadformNew)
	ON_COMMAND(ID_LABORATORY_W_LOADFORM_EXISTING, OnLaboratoryWLoadformExisting)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_W_LOADFORM_EXISTING, OnUpdateLaboratoryWLoadformExisting)
	ON_COMMAND(ID_LABORATORY_W_COMPUTE, OnLaboratoryWCompute)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_W_COMPUTE, OnUpdateLaboratoryWCompute)
	ON_COMMAND(ID_LABORATORY_W_SAVETODB, OnLaboratoryWSavetodb)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_W_SAVETODB, OnUpdateLaboratoryWSavetodb)
	ON_COMMAND(ID_LABORATORY_W_DISCONNECTEXCEL, OnLaboratoryWDisconnectexcel)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_W_DISCONNECTEXCEL, OnUpdateLaboratoryWDisconnectexcel)
	ON_COMMAND(ID_LABORATORY_WL_LOADFORM_NEW, OnLaboratoryWlLoadformNew)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_WL_LOADFORM_NEW, OnUpdateLaboratoryWlLoadformNew)
	ON_COMMAND(ID_LABORATORY_WL_LOADFORM_EXISTING, OnLaboratoryWlLoadformExisting)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_WL_LOADFORM_EXISTING, OnUpdateLaboratoryWlLoadformExisting)
	ON_COMMAND(ID_LABORATORY_WL_COMPUTE, OnLaboratoryWlCompute)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_WL_COMPUTE, OnUpdateLaboratoryWlCompute)
	ON_COMMAND(ID_LABORATORY_WL_SAVETODB, OnLaboratoryWlSavetodb)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_WL_SAVETODB, OnUpdateLaboratoryWlSavetodb)
	ON_COMMAND(ID_LABORATORY_WL_DISCONNECTEXCEL, OnLaboratoryWlDisconnectexcel)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_WL_DISCONNECTEXCEL, OnUpdateLaboratoryWlDisconnectexcel)
	ON_COMMAND(ID_LABORATORY_WLP_LOADFORM_NEW, OnLaboratoryWlpLoadformNew)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_WLP_LOADFORM_NEW, OnUpdateLaboratoryWlpLoadformNew)
	ON_COMMAND(ID_LABORATORY_WLP_LOADFORM_EXISTING, OnLaboratoryWlpLoadformExisting)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_WLP_LOADFORM_EXISTING, OnUpdateLaboratoryWlpLoadformExisting)
	ON_COMMAND(ID_LABORATORY_WLP_COMPUTE, OnLaboratoryWlpCompute)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_WLP_COMPUTE, OnUpdateLaboratoryWlpCompute)
	ON_COMMAND(ID_LABORATORY_WLP_SAVETODB, OnLaboratoryWlpSavetodb)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_WLP_SAVETODB, OnUpdateLaboratoryWlpSavetodb)
	ON_COMMAND(ID_LABORATORY_WLP_DISCONNECTEXCEL, OnLaboratoryWlpDisconnectexcel)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_WLP_DISCONNECTEXCEL, OnUpdateLaboratoryWlpDisconnectexcel)
	ON_COMMAND(ID_LABORATORY_CUT_LOADFORM_NEW, OnLaboratoryCutLoadformNew)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_CUT_LOADFORM_NEW, OnUpdateLaboratoryCutLoadformNew)
	ON_COMMAND(ID_LABORATORY_CUT_LOADFORM_EXISTING, OnLaboratoryCutLoadformExisting)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_CUT_LOADFORM_EXISTING, OnUpdateLaboratoryCutLoadformExisting)
	ON_COMMAND(ID_LABORATORY_CUT_COMPUTE, OnLaboratoryCutCompute)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_CUT_COMPUTE, OnUpdateLaboratoryCutCompute)
	ON_COMMAND(ID_LABORATORY_CUT_SAVETODB, OnLaboratoryCutSavetodb)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_CUT_SAVETODB, OnUpdateLaboratoryCutSavetodb)
	ON_COMMAND(ID_LABORATORY_CUT_DISCONNECTEXCEL, OnLaboratoryCutDisconnectexcel)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_CUT_DISCONNECTEXCEL, OnUpdateLaboratoryCutDisconnectexcel)
	ON_COMMAND(ID_LABORATORY_COMPRESSION_LOADFORM_NEW, OnLaboratoryCompressionLoadformNew)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_COMPRESSION_LOADFORM_NEW, OnUpdateLaboratoryCompressionLoadformNew)
	ON_COMMAND(ID_LABORATORY_COMPRESSION_LOADFORM_EXISTING, OnLaboratoryCompressionLoadformExisting)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_COMPRESSION_LOADFORM_EXISTING, OnUpdateLaboratoryCompressionLoadformExisting)
	ON_COMMAND(ID_LABORATORY_COMPRESSION_COMPUTE, OnLaboratoryCompressionCompute)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_COMPRESSION_COMPUTE, OnUpdateLaboratoryCompressionCompute)
	ON_COMMAND(ID_LABORATORY_COMPRESSION_SAVETODB, OnLaboratoryCompressionSavetodb)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_COMPRESSION_SAVETODB, OnUpdateLaboratoryCompressionSavetodb)
	ON_COMMAND(ID_LABORATORY_COMPRESSION_DISCONNECTEXCEL, OnLaboratoryCompressionDisconnectexcel)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_COMPRESSION_DISCONNECTEXCEL, OnUpdateLaboratoryCompressionDisconnectexcel)
	ON_COMMAND(ID_PROBGR_NEWLABNUMBER, OnProbgrNewlabnumber)
	ON_UPDATE_COMMAND_UI(ID_PROBGR_NEWLABNUMBER, OnUpdateProbgrNewlabnumber)
	ON_COMMAND(ID_KT_KTLIST_LOADFORM_NEW, OnKtKtlistLoadformNew)
	ON_UPDATE_COMMAND_UI(ID_KT_KTLIST_LOADFORM_NEW, OnUpdateKtKtlistLoadformNew)
	ON_COMMAND(ID_KT_KTLIST_LOADFORM_EXISTING, OnKtKtlistLoadformExisting)
	ON_UPDATE_COMMAND_UI(ID_KT_KTLIST_LOADFORM_EXISTING, OnUpdateKtKtlistLoadformExisting)
	ON_COMMAND(ID_KT_KTLIST_SAVETODB, OnKtKtlistSavetodb)
	ON_UPDATE_COMMAND_UI(ID_KT_KTLIST_SAVETODB, OnUpdateKtKtlistSavetodb)
	ON_COMMAND(ID_KT_KTLIST_DISCONNECTEXCEL, OnKtKtlistDisconnectexcel)
	ON_UPDATE_COMMAND_UI(ID_KT_KTLIST_DISCONNECTEXCEL, OnUpdateKtKtlistDisconnectexcel)
	ON_COMMAND(ID_PROBGR_PASPORT_ALLPOSSIBLE, OnProbgrPasportAllpossible)
	ON_COMMAND(ID_PROBGR_SOILNAME, OnProbgrSoilname)
	ON_COMMAND(ID__EXPORTOBJECT, OnExportobject)
	ON_COMMAND(ID___LANGUAGE, OnLanguage)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, OnUpdateFileOpen)
	ON_COMMAND(ID_PROBYGRUNTA_DBLCLICKMODE, OnProbygruntaDblclickmode)
	ON_COMMAND(ID_LABORATORY_REPEATINGS, OnLaboratoryRepeatings)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_COMPRESS, OnKeydownListCompress)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_COMPRESS, OnRclickListCompress)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_ZRIZ, OnRclickListZriz)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_ZRIZ, OnKeydownListZriz)
	ON_COMMAND(ID_LABORATORY_PLOTNOSTCHASTIC1_LOADFORM_NEW, OnLaboratoryPlotnostchastic1LoadformNew)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_PLOTNOSTCHASTIC1_LOADFORM_NEW, OnUpdateLaboratoryPlotnostchastic1LoadformNew)
	ON_COMMAND(ID_LABORATORY_PLOTNOSTCHASTIC1_SAVETODB, OnLaboratoryPlotnostchastic1Savetodb)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_PLOTNOSTCHASTIC1_SAVETODB, OnUpdateLaboratoryPlotnostchastic1Savetodb)
	ON_COMMAND(ID_LABORATORY_PLOTNOSTCHASTIC1_DISCONNECTEXCEL, OnLaboratoryPlotnostchastic1Disconnectexcel)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_PLOTNOSTCHASTIC1_DISCONNECTEXCEL, OnUpdateLaboratoryPlotnostchastic1Disconnectexcel)
	ON_COMMAND(ID_LABORATORY_PLOTNOSTCHASTIC1_LOADFORM_EXISTING, OnLaboratoryPlotnostchastic1LoadformExisting)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_PLOTNOSTCHASTIC1_LOADFORM_EXISTING, OnUpdateLaboratoryPlotnostchastic1LoadformExisting)
	ON_COMMAND(ID_LABORATORY_PLOTNOSTGRUNTA_SAVETODB_DIFFERENT_VYPROB, OnLaboratoryPlotnostgruntaSavetodbDifferentVyprob)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_PLOTNOSTGRUNTA_SAVETODB_DIFFERENT_VYPROB, OnUpdateLaboratoryPlotnostgruntaSavetodbDifferentVyprob)
	ON_COMMAND(ID_LABORATORY_W_SAVETODB_DIFFERENT_VYPROB, OnLaboratoryWSavetodbDifferentVyprob)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_W_SAVETODB_DIFFERENT_VYPROB, OnUpdateLaboratoryWSavetodbDifferentVyprob)
	ON_COMMAND(ID_LABORATORY_COMPRESSION_FILL, OnLaboratoryCompressionFill)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_COMPRESSION_FILL, OnUpdateLaboratoryCompressionFill)
	ON_COMMAND(ID_PROBYGRUNTA_LABNUMBERS_LOADFORM_NEW, OnProbygruntaLabnumbersLoadformNew)
	ON_UPDATE_COMMAND_UI(ID_PROBYGRUNTA_LABNUMBERS_LOADFORM_NEW, OnUpdateProbygruntaLabnumbersLoadformNew)
	ON_COMMAND(ID_PROBYGRUNTA_LABNUMBERS_LOADFORM_EXISTING, OnProbygruntaLabnumbersLoadformExisting)
	ON_UPDATE_COMMAND_UI(ID_PROBYGRUNTA_LABNUMBERS_LOADFORM_EXISTING, OnUpdateProbygruntaLabnumbersLoadformExisting)
	ON_COMMAND(ID_PROBYGRUNTA_LABNUMBERS_FILL, OnProbygruntaLabnumbersFill)
	ON_UPDATE_COMMAND_UI(ID_PROBYGRUNTA_LABNUMBERS_FILL, OnUpdateProbygruntaLabnumbersFill)
	ON_COMMAND(ID_PROBYGRUNTA_LABNUMBERS_SAVETODB, OnProbygruntaLabnumbersSavetodb)
	ON_UPDATE_COMMAND_UI(ID_PROBYGRUNTA_LABNUMBERS_SAVETODB, OnUpdateProbygruntaLabnumbersSavetodb)
	ON_COMMAND(ID_PROBYGRUNTA_LABNUMBERS_DISCONNECTEXCEL, OnProbygruntaLabnumbersDisconnectexcel)
	ON_UPDATE_COMMAND_UI(ID_PROBYGRUNTA_LABNUMBERS_DISCONNECTEXCEL, OnUpdateProbygruntaLabnumbersDisconnectexcel)
	ON_COMMAND(ID_KT_KTLIST_FILL, OnKtKtlistFill)
	ON_UPDATE_COMMAND_UI(ID_KT_KTLIST_FILL, OnUpdateKtKtlistFill)
	ON_COMMAND(ID_EXCEL_KILL, OnExcelKill)
	ON_COMMAND(ID_LABORATORY_CUT_FILL, OnLaboratoryCutFill)
	ON_UPDATE_COMMAND_UI(ID_LABORATORY_CUT_FILL, OnUpdateLaboratoryCutFill)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_GRANULAR, OnRclickListGranular)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_SOIL, OnItemchangedListSoil)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_EN_GEO_OBJECTS, OnItemchangedListEnGeoObjects)
	ON_COMMAND(ID_KT_KTLIST_SAVEANDRENAME, OnKtKtlistSaveandrename)
	ON_UPDATE_COMMAND_UI(ID_KT_KTLIST_SAVEANDRENAME, OnUpdateKtKtlistSaveandrename)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_KT, OnColumnclickListKt)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_SOIL, OnRclickListSoil)
	ON_UPDATE_COMMAND_UI(ID_PROBYGRUNTA_PASSPORTS_OTNOSITDEFONGRAPH, OnUpdateProbygruntaPassportsOtnositdefongraph)
	ON_COMMAND(ID_PROBYGRUNTA_PASSPORTS_OTNOSITDEFONGRAPH, OnProbygruntaPassportsOtnositdefongraph)
	ON_COMMAND(ID_EXCEL_TODISSCONNECTWHENLOADFORM_L, OnExcelTodissconnectwhenloadform)
	ON_UPDATE_COMMAND_UI(ID_EXCEL_TODISSCONNECTWHENLOADFORM_L, OnUpdateExcelTodissconnectwhenloadformL)
	ON_COMMAND(ID_EXCEL_AUTOMATICSAVEWHENDISSCONNECTL, OnExcelAutomaticsavewhendissconnectl)
	ON_UPDATE_COMMAND_UI(ID_EXCEL_AUTOMATICSAVEWHENDISSCONNECTL, OnUpdateExcelAutomaticsavewhendissconnectl)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()



CLaboratoryView::CLaboratoryView() : CFormView(CLaboratoryView::IDD) 
{
	m_LabObjectsList.m_lab_view = this;
//	m_DataBaseTablesList.m_lab_view = this;
	m_KTLabList.m_lab_view = this;
//	m_ListView.m_lab_view = this;
	m_SoilsList.m_lab_view = this;
	m_ZrizListLab.m_lab_view = this;
	m_CompressListLab.m_lab_view = this;
	m_FizMehListLab.m_lab_view = this;
	m_GranularListLab.m_lab_view = this;
//	m_PropList.m_lab_view = this;
}

CLaboratoryView::~CLaboratoryView()
{

}

void CLaboratoryView::DisconnectAllExcels() 
{
	OnKtKtlistDisconnectexcel();
	OnProbygruntaLabnumbersDisconnectexcel();
	// TODO: Add your specialized code here and/or call the base class
	this->OnLaboratorySandgranularDisconnectExcel();
	this->OnLaboratoryAreometrGranularDisconnectExcel();

	this->OnLaboratoryVegetableRemainsDisconnectExcel();

	OnLaboratoryPlotnostchastic1Disconnectexcel();
	this->OnLaboratoryPlotnostChasticDisconnectExcel();
	this->OnLaboratoryPlotnostGruntaDisconnectExcel();

	this->OnLaboratoryWDisconnectexcel();
	this->OnLaboratoryWlDisconnectexcel();
	this->OnLaboratoryWlpDisconnectexcel();

	OnLaboratoryCutDisconnectexcel();
	OnLaboratoryCompressionDisconnectexcel();
}
void CLaboratoryView::PostNcDestroy() 
{
	DisconnectAllExcels() ;	
	CFormView::PostNcDestroy();
}

void CLaboratoryView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLaboratoryView)
	DDX_Control(pDX, IDC_LIST_ZRIZ, m_ZrizListLab);
	DDX_Control(pDX, IDC_LIST_COMPRESS, m_CompressListLab);
	DDX_Control(pDX, IDC_LIST_PROP, m_FizMehListLab);
	DDX_Control(pDX, IDC_LIST_GRANULAR, m_GranularListLab);
	DDX_Control(pDX, IDC_LIST_SOIL, m_SoilsList);
	DDX_Control(pDX, IDC_LIST_KT, m_KTLabList);
//	DDX_Control(pDX, IDC_LIST_VIEW, m_ListView);
//	DDX_Control(pDX, IDC_LIST_DB_TABLES, m_DataBaseTablesList);
	DDX_Control(pDX, IDC_LIST_EN_GEO_OBJECTS, m_LabObjectsList);
	//}}AFX_DATA_MAP
}

BOOL CLaboratoryView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CLaboratoryView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	ResizeParentToFit();

//	this->m_LabObjectsList.OnInitialUpdate();

	this->m_LabObjectsList.OnInitCtrl();
//	this->m_DataBaseTablesList.OnInitCtrl();
//	this->m_ListView.OnInitCtrl();
	this->m_SoilsList.OnInitCtrl();
	this->m_ZrizListLab.OnInitCtrl();
	this->m_CompressListLab.OnInitCtrl();
	this->m_FizMehListLab.OnInitCtrl();
	this->m_GranularListLab.OnInitCtrl();
	this->m_KTLabList.OnInitCtrl();

	CLabDoc * lab_doc = this->GetDocument();
	if (lab_doc)
	{
		lab_doc->FirstOdbcConnect();

		this->m_DBTableCilce0.Init(lab_doc, &lab_doc->m_database);
		this->m_DBTableCilce.Init(lab_doc, &lab_doc->m_database);
		this->m_DBTableCompress.Init(lab_doc, &lab_doc->m_database);

		this->m_DBTableZriz0.Init(lab_doc, &lab_doc->m_database);
		this->m_DBTableZriz.Init(lab_doc, &lab_doc->m_database);
		this->m_DBTableZriz_tbl.Init(lab_doc, &lab_doc->m_database);

		this->m_DBTableProp.Init(lab_doc, &lab_doc->m_database);
		this->m_DBTableGranular.Init(lab_doc, &lab_doc->m_database);
		this->m_DBTableSoils.Init(lab_doc, &lab_doc->m_database);

		this->m_DBTableKT.Init(lab_doc, &lab_doc->m_database);

		this->m_DBTableRozrizy.Init(lab_doc, &lab_doc->m_database);
		this->m_DBTableRozriz.Init(lab_doc, &lab_doc->m_database);

		this->m_DBTableLito0.Init(lab_doc, &lab_doc->m_database);
		this->m_DBTableIGE0.Init(lab_doc, &lab_doc->m_database);
		this->m_DBTableLito.Init(lab_doc, &lab_doc->m_database);
		this->m_DBTableIGE.Init(lab_doc, &lab_doc->m_database);
		this->m_DBTableGrunty.Init(lab_doc, &lab_doc->m_database);
		this->m_DBTableVoda.Init(lab_doc, &lab_doc->m_database);
		this->m_DBTableGenezis.Init(lab_doc, &lab_doc->m_database);
		this->m_DBTableUmPoz.Init(lab_doc, &lab_doc->m_database);

		this->m_DBTableCubeSize.Init(lab_doc, &lab_doc->m_database);
		this->m_DBTableGridDataUsedAlg.Init(lab_doc, &lab_doc->m_database);

		this->m_DBTableGridData.Init(lab_doc, &lab_doc->m_database);
		this->m_DBTableGridDataSurfaces.Init(lab_doc, &lab_doc->m_database);

		this->m_DBTableSurfIgeMapping.Init(lab_doc, &lab_doc->m_database);
		this->m_DBTableSurfLitoMapping.Init(lab_doc, &lab_doc->m_database);

		this->m_DBTableSurfacesOrder.Init(lab_doc, &lab_doc->m_database);
		this->m_DBTableSurfacesBlankOrder.Init(lab_doc, &lab_doc->m_database);
		this->m_DBTableSurfacesBlankFunctions.Init(lab_doc, &lab_doc->m_database);

		this->m_DBTablePCK2Fiz_Params.Init(lab_doc, &lab_doc->m_database);
		this->m_DBTablePCK2Fiz_Results.Init(lab_doc, &lab_doc->m_database);

		this->m_DBTablePtStZond.Init(lab_doc, &lab_doc->m_database);
		this->m_DBTableStZond.Init(lab_doc, &lab_doc->m_database);

		this->m_DBTablePtPalja.Init(lab_doc, &lab_doc->m_database);
		this->m_DBTablePalja.Init(lab_doc, &lab_doc->m_database);
	}

	this->m_excel_sand_granular.Init(this, lab_doc, &lab_doc->m_database);
	this->m_excel_areometr_granular.Init(this, lab_doc, &lab_doc->m_database);
	this->m_excel_vegetable_remains.Init(this, lab_doc, &lab_doc->m_database);
	this->m_excel_plotnost_chastic.Init(this, lab_doc, &lab_doc->m_database);
	this->m_excel_plotnost_chastic1.Init(this, lab_doc, &lab_doc->m_database);
	this->m_excel_plotnost_grunta.Init(this, lab_doc, &lab_doc->m_database);
	this->m_excel_wlazhnost.Init(this, lab_doc, &lab_doc->m_database);
	this->m_excel_WL.Init(this, lab_doc, &lab_doc->m_database);
	this->m_excel_WLP.Init(this, lab_doc, &lab_doc->m_database);
	this->m_excel_cut.Init(this, lab_doc, &lab_doc->m_database);
	this->m_excel_compression.Init(this, lab_doc, &lab_doc->m_database);
	this->m_excel_ktlist.Init(this, lab_doc, &lab_doc->m_database);
	this->m_excel_labnlist.Init(this, lab_doc, &lab_doc->m_database);
}

/////////////////////////////////////////////////////////////////////////////
// CLabView printing

BOOL CLaboratoryView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLaboratoryView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLaboratoryView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CLaboratoryView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

#ifdef _DEBUG
void CLaboratoryView::AssertValid() const
{
	CFormView::AssertValid();
}

void CLaboratoryView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CLaboratoryDoc* CLaboratoryView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLaboratoryDoc)));
	//return (CLabDoc*)m_pDocument;

	return dynamic_cast<CLaboratoryDoc*>(m_pDocument);

}
#endif //_DEBUG

CLabDoc * CLaboratoryView::GetLabDoc()
{
	return this->GetDocument();
}

void CLaboratoryView::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	switch(nIDCtl)
	{
	case IDC_LIST_ZRIZ:
		this->m_ZrizListLab.OnDrawItem(nIDCtl, lpDrawItemStruct);
		break;
	case IDC_LIST_COMPRESS:
		this->m_CompressListLab.OnDrawItem(nIDCtl, lpDrawItemStruct);
		break;
	case IDC_LIST_PROP:
		this->m_FizMehListLab.OnDrawItem(nIDCtl, lpDrawItemStruct);
		break;
	case IDC_LIST_GRANULAR:
		this->m_GranularListLab.OnDrawItem(nIDCtl, lpDrawItemStruct);
		break;
	case IDC_LIST_SOIL:
		this->m_SoilsList.OnDrawItem(nIDCtl, lpDrawItemStruct);
		break;
	case IDC_LIST_KT:
		this->m_KTLabList.OnDrawItem(nIDCtl, lpDrawItemStruct);
		break;
//	case IDC_LIST_VIEW:
//		this->m_ListView.OnDrawItem(nIDCtl, lpDrawItemStruct);
//		break;
//	case IDC_LIST_DB_TABLES:
//		this->m_DataBaseTablesList.OnDrawItem(nIDCtl, lpDrawItemStruct);
//		break;
	case IDC_LIST_EN_GEO_OBJECTS:
		this->m_LabObjectsList.OnDrawItem(nIDCtl, lpDrawItemStruct);
		break;
	}
}


bool CLaboratoryView::GetSetProbGrFilterStr(long ID_OBJ, CString & strFilter)
{
	strFilter.Format("ID_OBJ = %d", ID_OBJ);
	return true;
}


void CLaboratoryView::OnLaboratorySandGranularLoadFormNew() 
{
	m_excel_sand_granular.LoadFormNew(m_ObjectNazva);
}

void CLaboratoryView::OnUpdateLaboratorySandGranularLoadFormNew(CCmdUI* pCmdUI) 
{
	m_excel_sand_granular.UpdateLoadFormNew(pCmdUI);
}

void CLaboratoryView::OnLaboratorySandGranularLoadFormExisting() 
{
	m_excel_sand_granular.LoadFormExisting();
}

void CLaboratoryView::OnUpdateLaboratorySandGranularLoadFormExisting(CCmdUI* pCmdUI) 
{
	m_excel_sand_granular.UpdateLoadFormExisting(pCmdUI);
}
void CLaboratoryView::OnLaboratorySandGranularCompute() 
{
	m_excel_sand_granular.Compute();
}

void CLaboratoryView::OnUpdateLaboratorySandGranularCompute(CCmdUI* pCmdUI) 
{
	this->m_excel_sand_granular.UpdateCompute(pCmdUI);
}

void CLaboratoryView::OnLaboratorySandGranularSaveToDB() 
{
	this->m_excel_sand_granular.SaveToDB();
}

void CLaboratoryView::OnUpdateLaboratorySandGranularSaveToDB(CCmdUI* pCmdUI) 
{
	this->m_excel_sand_granular.UpdateSaveToDB(pCmdUI);
}

void CLaboratoryView::OnLaboratorySandgranularDisconnectExcel() 
{
	m_excel_sand_granular.DisconnectExcel();
}

void CLaboratoryView::OnUpdateLaboratorySandGranularDisconnectExcel(CCmdUI* pCmdUI) 
{
	this->m_excel_sand_granular.UpdateDisconnectExcel(pCmdUI);
}

void CLaboratoryView::OnFileNewObject() 
{
	CDlgObject dialog(this, this->GetDocument(), true);
	dialog.DoModal();	
}

void CLaboratoryView::OnFileOpen() 
{
	CDlgObject dialog(this, this->GetDocument(), false);
	dialog.DoModal();
}

void CLaboratoryView::OnUpdateFileOpen(CCmdUI* pCmdUI) 
{
	int nItem = this->GetObjectItem();
    pCmdUI->Enable(nItem > -1);		
}

void CLaboratoryView::UpdateObjectsListCtrl(CString where, CString order_by)
{
	this->m_LabObjectsList.Fill_Ctrl_List(this->GetDocument()->m_tables[table_key_Objects], where, order_by);
}

void CLaboratoryView::UpdateProbGruntListCtrl(CString where, CString order_by)
{
	this->m_SoilsList.Fill_Ctrl_List(this->GetDocument()->m_tables[table_key_ProbGr], where, order_by);
}
void CLaboratoryView::UpdateLitoListCtrl(CString where, CString order_by)
{
}
void CLaboratoryView::UpdateKTListCtrl(CString where, CString order_by)
{
	this->m_KTLabList.Fill_Ctrl_List(this->GetDocument()->m_tables[table_key_KT], where, order_by);
}
void CLaboratoryView::UpdateIGEListCtrl(CString where, CString order_by)
{
}
void CLaboratoryView::UpdateVodaListCtrl(CString where, CString order_by)
{
}
void CLaboratoryView::UpdateTSZListCtrl(CString where, CString order_by)
{
}
void CLaboratoryView::UpdatePaljaListCtrl(CString where, CString order_by)
{
}

void CLaboratoryView::UpdateCompressListCtrl(CString where, CString order_by)
{
	this->m_CompressListLab.Fill_Ctrl_List(this->GetDocument()->m_tables[table_key_Compress], where, order_by);
}
void CLaboratoryView::UpdateCutListCtrl(CString where, CString order_by)
{
	this->m_ZrizListLab.Fill_Ctrl_List(this->GetDocument()->m_tables[table_key_Zriz], where, order_by);
}
void CLaboratoryView::UpdateFizMehListCtrl(CString where, CString order_by)
{
	this->m_FizMehListLab.Fill_Ctrl_List(this->GetDocument()->m_tables[table_key_FizMeh], where, order_by);
}
void CLaboratoryView::UpdateGranularListCtrl(CString where, CString order_by)
{
	this->m_GranularListLab.Fill_Ctrl_List(this->GetDocument()->m_tables[table_key_Granular], where, order_by);
}

void CLaboratoryView::EnableObjectList(BOOL bEnable)
{
	this->m_LabObjectsList.EnableWindow(bEnable);
}
int CLaboratoryView::GetObjectItem()
{
	return this->m_LabObjectsList.GetSelected();
}
int CLaboratoryView::GetKTItem()
{
	return this->m_KTLabList.GetSelected();
}
int CLaboratoryView::GetProbGrItem()
{
	return this->m_SoilsList.GetSelected();
}
bool g_OnFileDeleteObject(int nItem, CDatabase * database);
void CLaboratoryView::OnFileDeleteObject() 
{
	int nItem = this->GetObjectItem();
	if (g_OnFileDeleteObject(nItem, &this->GetDocument()->m_database))
	{
		this->UpdateObjectsListCtrl("","");
		this->UpdateKTListCtrl("ID_OBJ = -1","");
		this->UpdateProbGruntListCtrl("ID_OBJ = -1","");
	}
}

void CLaboratoryView::OnUpdateFileDeleteObject(CCmdUI* pCmdUI) 
{
	int nItem = this->GetObjectItem();
    pCmdUI->Enable(nItem > -1);	
}

void CLaboratoryView::OnProbgrNewlabnumber() 
{
	CDlgProbGrunt dialog(this, this->GetDocument(), true);
	dialog.is_lab = true;
	dialog.i_kt = GetKTItem();
	dialog.DoModal();	
}

void CLaboratoryView::OnUpdateProbgrNewlabnumber(CCmdUI* pCmdUI) 
{
	int nItem = this->GetObjectItem();
    pCmdUI->Enable(nItem > -1);		
}

void CLaboratoryView::OnLaboratoryAreometrGranularLoadFormNew() 
{
	m_excel_areometr_granular.LoadFormNew(m_ObjectNazva);
}

void CLaboratoryView::OnUpdateLaboratoryAreometrGranularLoadFormNew(CCmdUI* pCmdUI) 
{
	this->m_excel_areometr_granular.UpdateLoadFormNew(pCmdUI);
}

void CLaboratoryView::OnLaboratoryAreometrGranularLoadFormExisting() 
{
	m_excel_areometr_granular.LoadFormExisting();
}

void CLaboratoryView::OnUpdateLaboratoryAreometrGranularLoadFormExisting(CCmdUI* pCmdUI) 
{
	this->m_excel_areometr_granular.UpdateLoadFormExisting(pCmdUI);
}

void CLaboratoryView::OnLaboratoryAreometrGranularCompute() 
{
	this->m_excel_areometr_granular.Compute();
}

void CLaboratoryView::OnUpdateLaboratoryAreometrGranularCompute(CCmdUI* pCmdUI) 
{
	this->m_excel_areometr_granular.UpdateCompute(pCmdUI);
}

void CLaboratoryView::OnLaboratoryAreometrGranularSaveToDB() 
{
	m_excel_areometr_granular.SaveToDB();	
}

void CLaboratoryView::OnUpdateLaboratoryAreometrGranularSaveToDB(CCmdUI* pCmdUI) 
{
	m_excel_areometr_granular.UpdateSaveToDB(pCmdUI);
}

void CLaboratoryView::OnLaboratoryAreometrGranularDisconnectExcel() 
{
	m_excel_areometr_granular.DisconnectExcel();
}

void CLaboratoryView::OnUpdateLaboratoryAreometrGranularDisconnectExcel(CCmdUI* pCmdUI) 
{
	this->m_excel_areometr_granular.UpdateDisconnectExcel(pCmdUI);
}

void CLaboratoryView::OnLaboratoryVegetableRemainsLoadFormNew() 
{
	m_excel_vegetable_remains.LoadFormNew(m_ObjectNazva);
}

void CLaboratoryView::OnUpdateLaboratoryVegetableRemainsLoadFormNew(CCmdUI* pCmdUI) 
{
	this->m_excel_vegetable_remains.UpdateLoadFormNew(pCmdUI);
}

void CLaboratoryView::OnLaboratoryVegetableRemainsLoadFormExisting() 
{
	this->m_excel_vegetable_remains.LoadFormExisting();
}

void CLaboratoryView::OnUpdateLaboratoryVegetableRemainsLoadFormExisting(CCmdUI* pCmdUI) 
{
	this->m_excel_vegetable_remains.UpdateLoadFormExisting(pCmdUI);
}

void CLaboratoryView::OnLaboratoryVegetableRemainsCompute() 
{
	m_excel_vegetable_remains.Compute();
}

void CLaboratoryView::OnUpdateLaboratoryVegetableRemainsCompute(CCmdUI* pCmdUI) 
{
	this->m_excel_vegetable_remains.UpdateCompute(pCmdUI);
}

void CLaboratoryView::OnLaboratoryVegetableRemainsSavetodb() 
{
	m_excel_vegetable_remains.SaveToDB();	
}

void CLaboratoryView::OnUpdateLaboratoryVegetableRemainsSavetodb(CCmdUI* pCmdUI) 
{
	this->m_excel_vegetable_remains.UpdateSaveToDB(pCmdUI);
}

void CLaboratoryView::OnLaboratoryVegetableRemainsDisconnectExcel() 
{
	this->m_excel_vegetable_remains.DisconnectExcel();
}

void CLaboratoryView::OnUpdateLaboratoryVegetableRemainsDisconnectExcel(CCmdUI* pCmdUI) 
{
	this->m_excel_vegetable_remains.UpdateDisconnectExcel(pCmdUI);
}

void CLaboratoryView::OnLaboratoryPlotnostchastic1LoadformNew() 
{
	m_excel_plotnost_chastic1.LoadFormNew(m_ObjectNazva);	
}

void CLaboratoryView::OnUpdateLaboratoryPlotnostchastic1LoadformNew(CCmdUI* pCmdUI) 
{
	this->m_excel_plotnost_chastic1.UpdateLoadFormNew(pCmdUI);	
}

void CLaboratoryView::OnLaboratoryPlotnostchastic1LoadformExisting() 
{
	m_excel_plotnost_chastic1.LoadFormExisting();	
}

void CLaboratoryView::OnUpdateLaboratoryPlotnostchastic1LoadformExisting(CCmdUI* pCmdUI) 
{
	m_excel_plotnost_chastic1.UpdateLoadFormExisting(pCmdUI);	
}

void CLaboratoryView::OnLaboratoryPlotnostchastic1Savetodb() 
{
	m_excel_plotnost_chastic1.SaveToDB();		
}

void CLaboratoryView::OnUpdateLaboratoryPlotnostchastic1Savetodb(CCmdUI* pCmdUI) 
{
	this->m_excel_plotnost_chastic1.UpdateSaveToDB(pCmdUI);	
}

void CLaboratoryView::OnLaboratoryPlotnostchastic1Disconnectexcel() 
{
	m_excel_plotnost_chastic1.DisconnectExcel();	
}
void CLaboratoryView::OnUpdateLaboratoryPlotnostchastic1Disconnectexcel(CCmdUI* pCmdUI) 
{
	m_excel_plotnost_chastic1.UpdateDisconnectExcel(pCmdUI);	
}

void CLaboratoryView::OnLaboratoryPlotnostChasticLoadFormNew() 
{
	m_excel_plotnost_chastic.LoadFormNew(m_ObjectNazva);
}

void CLaboratoryView::OnUpdateLaboratoryPlotnostChasticLoadFormNew(CCmdUI* pCmdUI) 
{
	this->m_excel_plotnost_chastic.UpdateLoadFormNew(pCmdUI);
}



void CLaboratoryView::OnLaboratoryPlotnostChasticLoadFormExisting() 
{
	m_excel_plotnost_chastic.LoadFormExisting();
}

void CLaboratoryView::OnUpdateLaboratoryPlotnostChasticLoadFormExisting(CCmdUI* pCmdUI) 
{
	m_excel_plotnost_chastic.UpdateLoadFormExisting(pCmdUI);
}

void CLaboratoryView::OnLaboratoryPlotnostChasticCompute() 
{
	m_excel_plotnost_chastic.Compute();
}

void CLaboratoryView::OnUpdateLaboratoryPlotnostChasticCompute(CCmdUI* pCmdUI) 
{
	m_excel_plotnost_chastic.UpdateCompute(pCmdUI);
}

void CLaboratoryView::OnLaboratoryPlotnostChasticSavetodb() 
{
	m_excel_plotnost_chastic.SaveToDB();	
}

void CLaboratoryView::OnUpdateLaboratoryPlotnostChasticSavetodb(CCmdUI* pCmdUI) 
{
	this->m_excel_plotnost_chastic.UpdateSaveToDB(pCmdUI);
}

void CLaboratoryView::OnLaboratoryPlotnostChasticDisconnectExcel() 
{
	m_excel_plotnost_chastic.DisconnectExcel();
}

void CLaboratoryView::OnUpdateLaboratoryPlotnostChasticDisconnectExcel(CCmdUI* pCmdUI) 
{
	m_excel_plotnost_chastic.UpdateDisconnectExcel(pCmdUI);
}

void CLaboratoryView::OnLaboratoryPlotnostGruntaLoadFormNew() 
{
	m_excel_plotnost_grunta.LoadFormNew(m_ObjectNazva);
}

void CLaboratoryView::OnUpdateLaboratoryPlotnostGruntaLoadFormNew(CCmdUI* pCmdUI) 
{
	this->m_excel_plotnost_grunta.UpdateLoadFormNew(pCmdUI);
}

void CLaboratoryView::OnLaboratoryPlotnostGruntaLoadFormExisting() 
{
	this->m_excel_plotnost_grunta.LoadFormExisting();
}

void CLaboratoryView::OnUpdateLaboratoryPlotnostGruntaLoadFormExisting(CCmdUI* pCmdUI) 
{
	this->m_excel_plotnost_grunta.UpdateLoadFormExisting(pCmdUI);
}

void CLaboratoryView::OnLaboratoryPlotnostGruntaCompute() 
{
	this->m_excel_plotnost_grunta.Compute();
}

void CLaboratoryView::OnUpdateLaboratoryPlotnostGruntaCompute(CCmdUI* pCmdUI) 
{
	this->m_excel_plotnost_grunta.UpdateCompute(pCmdUI);
}

void CLaboratoryView::OnLaboratoryPlotnostGruntaSavetodb() 
{
	m_excel_plotnost_grunta.save_different_vyprob = false;
	m_excel_plotnost_grunta.SaveToDB();	
}

void CLaboratoryView::OnUpdateLaboratoryPlotnostGruntaSavetodb(CCmdUI* pCmdUI) 
{
	this->m_excel_plotnost_grunta.UpdateSaveToDB(pCmdUI);
}
void CLaboratoryView::OnLaboratoryPlotnostgruntaSavetodbDifferentVyprob() 
{
	m_excel_plotnost_grunta.save_different_vyprob = true;
	m_excel_plotnost_grunta.SaveToDB();		
}

void CLaboratoryView::OnUpdateLaboratoryPlotnostgruntaSavetodbDifferentVyprob(CCmdUI* pCmdUI) 
{
	this->m_excel_plotnost_grunta.UpdateSaveToDB(pCmdUI);	
}

void CLaboratoryView::OnLaboratoryPlotnostGruntaDisconnectExcel() 
{
	m_excel_plotnost_grunta.DisconnectExcel();
}

void CLaboratoryView::OnUpdateLaboratoryPlotnostGruntaDisconnectExcel(CCmdUI* pCmdUI) 
{
	this->m_excel_plotnost_grunta.UpdateDisconnectExcel(pCmdUI);
}

void CLaboratoryView::OnLaboratoryWLoadformNew() 
{
	m_excel_wlazhnost.LoadFormNew(m_ObjectNazva);	
}

void CLaboratoryView::OnUpdateLaboratoryWLoadformNew(CCmdUI* pCmdUI) 
{
	m_excel_wlazhnost.UpdateLoadFormNew(pCmdUI);	
}

void CLaboratoryView::OnLaboratoryWLoadformExisting() 
{
	m_excel_wlazhnost.LoadFormExisting();	
}

void CLaboratoryView::OnUpdateLaboratoryWLoadformExisting(CCmdUI* pCmdUI) 
{
	m_excel_wlazhnost.UpdateLoadFormExisting(pCmdUI);	
}

void CLaboratoryView::OnLaboratoryWCompute() 
{
	m_excel_wlazhnost.Compute();	
}

void CLaboratoryView::OnUpdateLaboratoryWCompute(CCmdUI* pCmdUI) 
{
	m_excel_wlazhnost.UpdateCompute(pCmdUI);	
}

void CLaboratoryView::OnLaboratoryWSavetodb() 
{
	m_excel_wlazhnost.save_different_vyprob = false;
	m_excel_wlazhnost.SaveToDB();
}

void CLaboratoryView::OnUpdateLaboratoryWSavetodb(CCmdUI* pCmdUI) 
{
	m_excel_wlazhnost.UpdateSaveToDB(pCmdUI);
}

void CLaboratoryView::OnLaboratoryWSavetodbDifferentVyprob() 
{
	m_excel_wlazhnost.save_different_vyprob = true;
	m_excel_wlazhnost.SaveToDB();
}

void CLaboratoryView::OnUpdateLaboratoryWSavetodbDifferentVyprob(CCmdUI* pCmdUI) 
{
	m_excel_wlazhnost.UpdateSaveToDB(pCmdUI);	
}

void CLaboratoryView::OnLaboratoryWDisconnectexcel() 
{
	m_excel_wlazhnost.DisconnectExcel();	
}

void CLaboratoryView::OnUpdateLaboratoryWDisconnectexcel(CCmdUI* pCmdUI) 
{
	m_excel_wlazhnost.UpdateDisconnectExcel(pCmdUI);	
}


void CLaboratoryView::OnLaboratoryWlLoadformNew() 
{
	m_excel_WL.LoadFormNew(m_ObjectNazva);	
}

void CLaboratoryView::OnUpdateLaboratoryWlLoadformNew(CCmdUI* pCmdUI) 
{
	m_excel_WL.UpdateLoadFormNew(pCmdUI);	
}

void CLaboratoryView::OnLaboratoryWlLoadformExisting() 
{
	m_excel_WL.LoadFormExisting();	
}

void CLaboratoryView::OnUpdateLaboratoryWlLoadformExisting(CCmdUI* pCmdUI) 
{
	m_excel_WL.UpdateLoadFormExisting(pCmdUI);	
}

void CLaboratoryView::OnLaboratoryWlCompute() 
{
	m_excel_WL.Compute();	
}

void CLaboratoryView::OnUpdateLaboratoryWlCompute(CCmdUI* pCmdUI) 
{
	m_excel_WL.UpdateCompute(pCmdUI);	
}

void CLaboratoryView::OnLaboratoryWlSavetodb() 
{
	m_excel_WL.SaveToDB();	
}

void CLaboratoryView::OnUpdateLaboratoryWlSavetodb(CCmdUI* pCmdUI) 
{
	m_excel_WL.UpdateSaveToDB(pCmdUI);	
}

void CLaboratoryView::OnLaboratoryWlDisconnectexcel() 
{
	m_excel_WL.DisconnectExcel();	
}

void CLaboratoryView::OnUpdateLaboratoryWlDisconnectexcel(CCmdUI* pCmdUI) 
{
	m_excel_WL.UpdateDisconnectExcel(pCmdUI);	
}

void CLaboratoryView::OnLaboratoryWlpLoadformNew() 
{
	m_excel_WLP.LoadFormNew(m_ObjectNazva);	
}

void CLaboratoryView::OnUpdateLaboratoryWlpLoadformNew(CCmdUI* pCmdUI) 
{
	m_excel_WLP.UpdateLoadFormNew(pCmdUI);	
}

void CLaboratoryView::OnLaboratoryWlpLoadformExisting() 
{
	m_excel_WLP.LoadFormExisting();	
}

void CLaboratoryView::OnUpdateLaboratoryWlpLoadformExisting(CCmdUI* pCmdUI) 
{
	m_excel_WLP.UpdateLoadFormExisting(pCmdUI);	
}

void CLaboratoryView::OnLaboratoryWlpCompute() 
{
	m_excel_WLP.Compute();	
}

void CLaboratoryView::OnUpdateLaboratoryWlpCompute(CCmdUI* pCmdUI) 
{
	m_excel_WLP.UpdateCompute(pCmdUI);	
}

void CLaboratoryView::OnLaboratoryWlpSavetodb() 
{
	m_excel_WLP.SaveToDB();	
}

void CLaboratoryView::OnUpdateLaboratoryWlpSavetodb(CCmdUI* pCmdUI) 
{
	m_excel_WLP.UpdateSaveToDB(pCmdUI);	
}

void CLaboratoryView::OnLaboratoryWlpDisconnectexcel() 
{
	m_excel_WLP.DisconnectExcel();	
}

void CLaboratoryView::OnUpdateLaboratoryWlpDisconnectexcel(CCmdUI* pCmdUI) 
{
	m_excel_WLP.UpdateDisconnectExcel(pCmdUI);	
}

void CLaboratoryView::OnLaboratoryCutLoadformNew() 
{
	m_excel_cut.LoadFormNew(m_ObjectNazva);	
	m_excel_cut.Fill();
}

void CLaboratoryView::OnUpdateLaboratoryCutLoadformNew(CCmdUI* pCmdUI) 
{
	m_excel_cut.UpdateLoadFormNew(pCmdUI);	
}

void CLaboratoryView::OnLaboratoryCutLoadformExisting() 
{
	m_excel_cut.LoadFormExisting();	
}

void CLaboratoryView::OnUpdateLaboratoryCutLoadformExisting(CCmdUI* pCmdUI) 
{
	m_excel_cut.UpdateLoadFormExisting(pCmdUI);	
}

void CLaboratoryView::OnLaboratoryCutFill() 
{
	m_excel_cut.Fill();	
}

void CLaboratoryView::OnUpdateLaboratoryCutFill(CCmdUI* pCmdUI) 
{
	m_excel_cut.UpdateFill(pCmdUI, false);	
}

void CLaboratoryView::OnLaboratoryCutCompute() 
{
	m_excel_cut.Compute();	
}

void CLaboratoryView::OnUpdateLaboratoryCutCompute(CCmdUI* pCmdUI) 
{
	m_excel_cut.UpdateCompute(pCmdUI);	
}

void CLaboratoryView::OnLaboratoryCutSavetodb() 
{
	m_excel_cut.SaveToDB();	
}

void CLaboratoryView::OnUpdateLaboratoryCutSavetodb(CCmdUI* pCmdUI) 
{
	m_excel_cut.UpdateSaveToDB(pCmdUI);	
}

void CLaboratoryView::OnLaboratoryCutDisconnectexcel() 
{
	m_excel_cut.DisconnectExcel();	
}

void CLaboratoryView::OnUpdateLaboratoryCutDisconnectexcel(CCmdUI* pCmdUI) 
{
	m_excel_cut.UpdateDisconnectExcel(pCmdUI);	
}

void CLaboratoryView::OnLaboratoryCompressionLoadformNew() 
{
	m_excel_compression.LoadFormNew(m_ObjectNazva);	
	m_excel_compression.Fill();
}

void CLaboratoryView::OnUpdateLaboratoryCompressionLoadformNew(CCmdUI* pCmdUI) 
{
	m_excel_compression.UpdateLoadFormNew(pCmdUI);	
}

void CLaboratoryView::OnLaboratoryCompressionLoadformExisting() 
{
	m_excel_compression.LoadFormExisting();	
}

void CLaboratoryView::OnUpdateLaboratoryCompressionLoadformExisting(CCmdUI* pCmdUI) 
{
	m_excel_compression.UpdateLoadFormExisting(pCmdUI);	
}

void CLaboratoryView::OnLaboratoryCompressionFill() 
{
	m_excel_compression.Fill();		
}

void CLaboratoryView::OnUpdateLaboratoryCompressionFill(CCmdUI* pCmdUI) 
{
	m_excel_compression.UpdateFill(pCmdUI, false);	
}


void CLaboratoryView::OnLaboratoryCompressionCompute() 
{
	m_excel_compression.Compute();	
}

void CLaboratoryView::OnUpdateLaboratoryCompressionCompute(CCmdUI* pCmdUI) 
{
	m_excel_compression.UpdateCompute(pCmdUI);	
}


void CLaboratoryView::OnLaboratoryCompressionSavetodb() 
{
	m_excel_compression.SaveToDB();	
}

void CLaboratoryView::OnUpdateLaboratoryCompressionSavetodb(CCmdUI* pCmdUI) 
{
	m_excel_compression.UpdateSaveToDB(pCmdUI);	
}

void CLaboratoryView::OnLaboratoryCompressionDisconnectexcel() 
{
	m_excel_compression.DisconnectExcel();	
}

void CLaboratoryView::OnUpdateLaboratoryCompressionDisconnectexcel(CCmdUI* pCmdUI) 
{
	m_excel_compression.UpdateDisconnectExcel(pCmdUI);	
}

void CLaboratoryView::OnKtKtlistLoadformNew() 
{
	m_excel_ktlist.LoadFormNew(m_ObjectNazva);	
	m_excel_ktlist.Fill();	
}

void CLaboratoryView::OnUpdateKtKtlistLoadformNew(CCmdUI* pCmdUI) 
{
	m_excel_ktlist.UpdateLoadFormNew(pCmdUI);	
}

void CLaboratoryView::OnKtKtlistLoadformExisting() 
{
	m_excel_ktlist.LoadFormExisting();	
}

void CLaboratoryView::OnUpdateKtKtlistLoadformExisting(CCmdUI* pCmdUI) 
{
	m_excel_ktlist.UpdateLoadFormExisting(pCmdUI);	
}

void CLaboratoryView::OnKtKtlistFill() 
{
	//m_excel_ktlist.Fill();	
}

void CLaboratoryView::OnUpdateKtKtlistFill(CCmdUI* pCmdUI) 
{
	m_excel_ktlist.UpdateFill(pCmdUI, false);	
}

void CLaboratoryView::OnKtKtlistSavetodb() 
{
	m_excel_ktlist.to_rename_kt = false;
	m_excel_ktlist.SaveToDB();	
}

void CLaboratoryView::OnUpdateKtKtlistSavetodb(CCmdUI* pCmdUI) 
{
	m_excel_ktlist.UpdateSaveToDB(pCmdUI);	
}

void CLaboratoryView::OnKtKtlistSaveandrename() 
{
	m_excel_ktlist.to_rename_kt = true;
	m_excel_ktlist.SaveToDB();		
}

void CLaboratoryView::OnUpdateKtKtlistSaveandrename(CCmdUI* pCmdUI) 
{
	m_excel_ktlist.UpdateSaveToDB(pCmdUI);		
}

void CLaboratoryView::OnKtKtlistDisconnectexcel() 
{
	m_excel_ktlist.DisconnectExcel();	
}

void CLaboratoryView::OnUpdateKtKtlistDisconnectexcel(CCmdUI* pCmdUI) 
{
	m_excel_ktlist.UpdateDisconnectExcel(pCmdUI);	
}

void CLaboratoryView::OnProbgrPasportAllpossible() 
{
	this->ProbgrPasportAllpossible();
}

void CLaboratoryView::OnProbgrSoilname() 
{
	this->ProbgrSoilname();
}
COleVariant GetOleVariant(CDBVariant & var)
{

	//CString s;
	//s.Format("var.m_dwType = %d",var.m_dwType);
	//AfxMessageBox(s);


	COleVariant ole_var;
	switch (var.m_dwType) 
	{
	case DBVT_STRING:
		ole_var = *var.m_pstring; // narrow characters
		break;
	case DBVT_SHORT:
		ole_var = var.m_iVal;
		break;
	case DBVT_LONG:
		ole_var = var.m_lVal;
		break;
	case DBVT_SINGLE:
		ole_var = var.m_fltVal;
		break;
	case DBVT_DOUBLE:
		ole_var = var.m_dblVal;
		break;
	case DBVT_DATE:
		ole_var = COleDateTime(var.m_pdate->year, var.m_pdate->month, var.m_pdate->day, var.m_pdate->hour, var.m_pdate->minute, var.m_pdate->second);
		break;
	case DBVT_BOOL:
		ole_var = short(var.m_boolVal);
		break;
	case DBVT_UCHAR:
		ole_var = var.m_chVal;
		break;

	case DBVT_ASTRING:
		{
		//string s = (*var.m_pstringW).GetBuffer((*var.m_pstringW).GetLength());
		//return COleVariant(s.c_str());
		//AfxMessageBox(*var.m_pstringA);
//		wchar_t * str = new wchar_t[(*var.m_pstringW).GetLength()+2];
//		wsprintfW(str, L"%s\0", (*var.m_pstringW).GetBuffer((*var.m_pstringW).GetLength()));
//		ole_var =  str; // narrow characters
//		AfxMessageBox(str);

		//ole_var = *var.m_pstringW;
		}
		break;	
	case DBVT_WSTRING:
		//ole_var =  *var.m_pstringW; // narrow characters
		ole_var =  *var.m_pstring;
		break;

	case DBVT_NULL:
		ole_var = short(NULL);
		break;
	}
	//s.Format("return ole_var var.m_dwType = %d",var.m_dwType);
	//AfxMessageBox(s);
	return ole_var;
}
#define USE_DAO_1 1
void CLaboratoryView::OnExportobject() 
{

	int nObItem = this->GetObjectItem();
	if (nObItem < 0)
	{
		AfxMessageBox("Не выбран объект");
		return;
	}

	SetObject setObject(&this->GetLabDoc()->m_database);
	if ( !setObject.Open(CRecordset::dynaset) )
		return;
	setObject.SetAbsolutePosition(nObItem + 1);        
	long ID_OBJ = setObject.m_ID_OBJ;

		
	// TODO: Add your command handler code here
	TCHAR filter[4098];
	sprintf_s(filter, 4098, TEXT("Acces files (*.mdb)%%*.mdb%%All Files (*.*)%%*.*%%\0"));

	// Replace occurrences of '%' string separator 
	// with '\0'. 

	for (int i=0; filter[i]!='\0'; i++) 
	{
		if (filter[i] == '%') 
				filter[i] = '\0'; 
	}

	char dir[4098];		
	char path_xls[4098];		
	char fn[4098];		
	sprintf(path_xls, "\0");

	char * p = NULL;

	DWORD nFilterIndex = 0;
	if (S_OK == SaveFileDlg(NULL, path_xls, filter, nFilterIndex))
	{
		switch (nFilterIndex)
		{
		case 1:
			break;
		}	

		strcpy(dir, path_xls);

		p = NULL;
		if (p = strrchr(dir, '/'))
			*p = '\0';
		else if (p = strrchr(dir, '\\'))
			*p = '\0';

		if (p)
		{
			strcpy(fn, p+1);
		}

		char file1[4098];
		sprintf(file1, "%s", CLabDoc::s_strExportDatabaseTemplate);
		char file2[4098];
		sprintf(file2, "%s\\%s", dir, fn);

		if (!CopyFile(file1, file2, FALSE))
		{
			char str[4098];
			sprintf(str, "Can not copy\n%s\nto\n%s", file1, file2);
			AfxMessageBox(str);
		}
		BeginWaitCursor();
#if USE_DAO_1
		CString m_dao_strConnect_1;
		m_dao_strConnect_1.Format(";PWD=%s\0", CLabDoc::s_strDBPassword);
		CDaoDatabase m_dao_database_1;
		try {
			// nonexclusive, read-only
			m_dao_database_1.Open(
				CLabDoc::s_strDatabase, 
				FALSE, TRUE, m_dao_strConnect_1);
		}
		catch (CDaoException* e) {
			::DaoErrorMsg(e);
			EndWaitCursor();
			e->Delete();
			return;
		}
#endif
		CString m_dao_strDatabase_2 = file2;
		CDaoDatabase m_dao_database_2;
		//BOOL m_dao_bConnected;

		try {
			// nonexclusive
			m_dao_database_2.Open(m_dao_strDatabase_2);
		}
		catch (CDaoException* e) {
			::DaoErrorMsg(e);
			EndWaitCursor();
			e->Delete();
			return;
		}

		//m_dao_strDatabase_2 = m_dao_database_2.GetName();


		SetGeoTables setGeoTables(&this->GetLabDoc()->m_database);
		if (!setGeoTables.Open())
		{
			return;
		}
		if (!setGeoTables.IsBOF()) 
		{
			setGeoTables.MoveFirst( );
			while(!setGeoTables.IsEOF()) 
			{
				long ID = setGeoTables.m_ID;
				CString table_nazva = setGeoTables.m_NAZVA;
				//MessageBox(table_nazva, "table_nazva", 0);

				if (true)
				{
#if USE_DAO_1
					CString m_strQuery_1;
					m_strQuery_1.Format("select * from [%s]", table_nazva);

					CDaoRecordset* m_pRecordset_1;					
					m_pRecordset_1 = new CDaoRecordset(&m_dao_database_1);

					try {
						m_pRecordset_1->m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
						m_pRecordset_1->Open(dbOpenDynaset, m_strQuery_1, dbReadOnly);
					}
					catch (CDaoException* pe) {
						::DaoErrorMsg(pe);
						pe->Delete();
						EndWaitCursor();
						m_pRecordset_1->Close();
						delete m_pRecordset_1;
						return ;
					}
					
					int m_nFields_1 = (int) m_pRecordset_1->GetFieldCount();
					CDaoFieldInfo fi_1;
					CStringArray m_arrayFieldName_1;
					CWordArray m_arrayFieldSize_1;
					m_arrayFieldName_1.SetSize(m_nFields_1);
					m_arrayFieldSize_1.SetSize(m_nFields_1);
					for(int i = 0; i < m_nFields_1; i++) {
						m_pRecordset_1->GetFieldInfo(i, fi_1);
						m_arrayFieldName_1[i] = fi_1.m_strName;
						m_arrayFieldSize_1[i] = (short) max(min(fi_1.m_lSize, 250),
							fi_1.m_strName.GetLength());
						TRACE("field name = %s\n", fi_1.m_strName);
					}
#else
					CString m_strQuery;
					m_strQuery.Format("select * from [%s]", table_nazva);

					CRecordset* m_pRecordset;					
					m_pRecordset = new CRecordset(&this->GetLabDoc()->m_database);

					try {
						m_pRecordset->m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
						m_pRecordset->Open(CRecordset::dynaset, m_strQuery, CRecordset::readOnly);
					}
					catch (CDBException* pe) {
						AfxMessageBox(pe->m_strError);
						pe->Delete();
						EndWaitCursor();
						m_pRecordset->Close();
						delete m_pRecordset;
						return ;
					}
					
					int m_nFields = (int) m_pRecordset->GetODBCFieldCount();
					CODBCFieldInfo m_fi;
					CStringArray m_arrayFieldName;
					CWordArray m_arrayFieldSize;
					m_arrayFieldName.SetSize(m_nFields);
					m_arrayFieldSize.SetSize(m_nFields);
					for(int i = 0; i < m_nFields; i++) {
						m_pRecordset->GetODBCFieldInfo(i, m_fi);
						m_arrayFieldName[i] = m_fi.m_strName;
						m_arrayFieldSize[i] = (short) max(min(m_fi.m_nPrecision, 250),
							m_fi.m_strName.GetLength());
						TRACE("field name = %s\n", m_fi.m_strName);
					}
#endif


					CString m_dao_strQuery_2;
					m_dao_strQuery_2.Format("select * from [%s]", table_nazva);

					CDaoRecordset* m_dao_pRecordset_2;					
					m_dao_pRecordset_2 = new CDaoRecordset(&m_dao_database_2);
					try {	
						m_dao_pRecordset_2->Open(dbOpenDynaset, m_dao_strQuery_2, dbDenyWrite);
					}
					catch (CDaoException* e) {
						::DaoErrorMsg(e);
						EndWaitCursor();
						e->Delete();
						return;
					}

#if 0
					int m_dao_nFields = (int) m_dao_pRecordset->GetFieldCount();
					//m_dao_arrayFieldName.SetSize(m_dao_nFields);
					//m_dao_arrayFieldSize.SetSize(m_dao_nFields);
					CDaoFieldInfo fi;
					for(int i = 0; i < m_dao_nFields; i++) {
						m_dao_pRecordset->GetFieldInfo(i, fi);
						//m_dao_arrayFieldName[i] = fi.m_strName;
						//m_dao_arrayFieldSize[i] = (short) max(min(fi.m_lSize, 50),
						//	fi.m_strName.GetLength());
						TRACE("field name = %s\n", fi.m_strName);

						//MessageBox(fi.m_strName, "field name", 0);
					}
#endif
					if (!m_pRecordset_1->IsBOF())
					{
						m_pRecordset_1->MoveFirst();
						while (!m_pRecordset_1->IsEOF())
						{      
							m_dao_pRecordset_2->AddNew();

							for(int i = 0; i < m_nFields_1; i++) {
#if USE_DAO_1
								COleVariant m_var; // must declare this inside the loop
								m_pRecordset_1->GetFieldValue(m_arrayFieldName_1[i], m_var);
								m_dao_pRecordset_2->SetFieldValue(m_arrayFieldName_1[i], m_var);
#else
								CDBVariant m_var; // must declare this inside the loop
								m_pRecordset->GetFieldValue(m_arrayFieldName[i], m_var);
								m_dao_pRecordset_2->SetFieldValue(m_arrayFieldName[i], GetOleVariant(m_var));
#endif
								
							}
							m_dao_pRecordset_2->Update();								
							m_pRecordset_1->MoveNext();

						}
					}

					m_pRecordset_1->Close();
					delete m_pRecordset_1;

					m_dao_pRecordset_2->Close();
					delete m_dao_pRecordset_2;



				}

				setGeoTables.MoveNext(); // to validate record count
			}
		}
		m_dao_database_1.Close();
		m_dao_database_2.Close();
	}


	EndWaitCursor();

}

void CLaboratoryView::OnLanguage() 
{
	CDlgLanguage dialog;
	dialog.DoModal();	
}

void CLaboratoryView::OnProbygruntaDblclickmode() 
{
	CDlgProbGr_DblClickMode dialog;
	dialog.DoModal();	
}

void CLaboratoryView::OnLaboratoryRepeatings() 
{
	CDlgRepeatings dialog;
	dialog.DoModal();	
}

void DeleteCutAndCompressRelatedDataFrom(CRecordset * set, long ID_OBJ, long ID_KT, long ID_PROB, long ID_VYPROB)
{
	// удаляем связанные с данным объектом данные из других таблиц
	set->m_strFilter.Format(
		"ID_OBJ = %d and ID_KT = %d and ID_PROB = %d and ID_VYPROB = %d", 
		ID_OBJ, ID_KT, ID_PROB, ID_VYPROB);

	if (set->Open(CRecordset::dynaset) )
	{
		while ( !set->IsEOF( ) )
		{
			set->Delete( );
			set->MoveNext( );
		}
	}
}
bool g_DeleteCompression(CLabView * lab_view, int nObjectItem, int nSoilsItem, int nCompressionItem, CDatabase * database)
{
	SetObject setObject(database);
	if ( !setObject.Open(CRecordset::dynaset) )
		return false;
	setObject.SetAbsolutePosition(nObjectItem+1);
	long ID_OBJ = setObject.m_ID_OBJ;

	SetProbGr setProbGr(database);
	if(!lab_view->GetSetProbGrFilterStr(ID_OBJ, setProbGr.m_strFilter))
	{
		return false;
	}
	setProbGr.m_strSort.Format("ID_KT, ID_PROB");
	if ( !setProbGr.Open(CRecordset::dynaset) )
		return false;
	setProbGr.SetAbsolutePosition(nSoilsItem+1);

	SetCilce setCilce(database);
	setCilce.m_strFilter.Format(
		"ID_OBJ = %d and ID_KT = %d and ID_PROB = %d", 
		ID_OBJ, setProbGr.m_ID_KT, setProbGr.m_ID_PROB);
	if ( !setCilce.Open(CRecordset::dynaset) )
		return false;
	setCilce.SetAbsolutePosition(nCompressionItem+1);

	char str[1024];
	sprintf(str, 
		"Вы действительно хотите удалить компрессию\n"
		"ID_OBJ = %d\n"
		"CONTRACT = %s\n"
		"NAZVA = %s\n"
		"ID_KT = %d\n"
		"ID_PROB = %d\n"
		"ID_VYPROB = %d\n"
		, 
		ID_OBJ, 
		setObject.m_CONTRACT, 
		setObject.m_NAZVA,
		setProbGr.m_ID_KT, 
		setProbGr.m_ID_PROB,
		setCilce.m_ID_VYPROB
		);
	
	if (IDYES != MessageBox(0, str, "g_DeleteCompression", MB_YESNO))
		return false;


	SetCompress setCompress(database);
	DeleteCutAndCompressRelatedDataFrom(&setCompress, ID_OBJ, setProbGr.m_ID_KT, setProbGr.m_ID_PROB, setCilce.m_ID_VYPROB);
	setCilce.Delete();

	CString where;
	where.Format("ID_OBJ = %d and ID_KT = %d and ID_PROB = %d", 
		ID_OBJ, setProbGr.m_ID_KT, setProbGr.m_ID_PROB);

	lab_view->UpdateCompressListCtrl(where, "ID_VYPROB");
	return true;
}


bool g_DeleteCut(CLabView * lab_view, int nObjectItem, int nSoilsItem, int nCutItem, CDatabase * database)
{
	SetObject setObject(database);
	if ( !setObject.Open(CRecordset::dynaset) )
		return false;
	setObject.SetAbsolutePosition(nObjectItem+1);
	long ID_OBJ = setObject.m_ID_OBJ;

	SetProbGr setProbGr(database);
	if(!lab_view->GetSetProbGrFilterStr(ID_OBJ, setProbGr.m_strFilter))
	{
		return false;
	}
	setProbGr.m_strSort.Format("ID_KT, ID_PROB");
	if ( !setProbGr.Open(CRecordset::dynaset) )
		return false;
	setProbGr.SetAbsolutePosition(nSoilsItem+1);

	SetZriz setZriz(database);
	setZriz.m_strFilter.Format(
		"ID_OBJ = %d and ID_KT = %d and ID_PROB = %d", 
		ID_OBJ, setProbGr.m_ID_KT, setProbGr.m_ID_PROB);
	if ( !setZriz.Open(CRecordset::dynaset) )
		return false;
	setZriz.SetAbsolutePosition(nCutItem+1);

	char str[1024];
	sprintf(str, 
		"Вы действительно хотите удалить срез\n"
		"ID_OBJ = %d\n"
		"CONTRACT = %s\n"
		"NAZVA = %s\n"
		"ID_KT = %d\n"
		"ID_PROB = %d\n"
		"ID_VYPROB = %d\n"
		, 
		ID_OBJ, 
		setObject.m_CONTRACT, 
		setObject.m_NAZVA,
		setProbGr.m_ID_KT, 
		setProbGr.m_ID_PROB,
		setZriz.m_ID_VYPROB
		);
	
	if (IDYES != MessageBox(0, str, "g_DeleteCut", MB_YESNO))
		return false;


	SetZriz_tbl setZriz_tbl(database);
	DeleteCutAndCompressRelatedDataFrom(&setZriz_tbl, ID_OBJ, setProbGr.m_ID_KT, setProbGr.m_ID_PROB, setZriz.m_ID_VYPROB);
	setZriz.Delete();

	CString where;
	where.Format("ID_OBJ = %d and ID_KT = %d and ID_PROB = %d", 
		ID_OBJ, setProbGr.m_ID_KT, setProbGr.m_ID_PROB);

	lab_view->UpdateCutListCtrl(where, "ID_VYPROB");
	return true;
}


void CLaboratoryView::OnKeydownListCompress(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;

	switch(pLVKeyDow->wVKey)
	{
	case VK_DELETE:
		{
			int nCompressionItem = m_CompressListLab.GetSelected();
			int nSoilsItem = m_SoilsList.GetSelected();
			int nObjectItem = this->GetObjectItem();
			
			if (g_DeleteCompression(this, nObjectItem, nSoilsItem, nCompressionItem, &this->GetDocument()->m_database))
			{
			}

		}
		break;
	}
	
	*pResult = 0;
}

void CLaboratoryView::OnRclickListSoil(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE) pNMHDR;

	int r = lpnmitem->iItem;
	int c = lpnmitem->iSubItem;
	m_nSoilItem = r;

	CPoint point = lpnmitem->ptAction;
	this->m_SoilsList.ClientToScreen(&point);

	CMenu menu;
	menu.CreatePopupMenu();
	menu.AppendMenu(MF_STRING, ID_SOIL_PROPERTYWINDOW, "Окно свойств");
	menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	
	*pResult = 0;
}

void CLaboratoryView::OnRclickListCompress(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE) pNMHDR;
	int r = lpnmitem->iItem;
	int c = lpnmitem->iSubItem;
	m_nCompItem = r;

	CPoint point = lpnmitem->ptAction;
	this->m_CompressListLab.ClientToScreen(&point);

	int compr_type = this->GetCompressType(m_nCompItem);

	CMenu menu;
	menu.CreatePopupMenu();
	
	switch(compr_type)
	{
	case 3:
	case 2:
		{
			menu.AppendMenu(MF_STRING, ID_COMPRESSION_PASPORT, "Паспорт (старый)");
			//menu.AppendMenu(MF_STRING, ID_COMPRESSION_PASPORT2AS1, "Паспорт каждого кольца отдельно");
			menu.AppendMenu(MF_STRING, ID_COMPRESSION_PASSPORT2ASMEAN, "Паспорт 2 кривых с усреднёнными физсвойствами");
			menu.AppendMenu(MF_STRING, ID_COMPRESSION_PASPORT2ASDIFFVYPROB, "Паспорт 2 кривых с отдельными физсвойствами");
		}
		break;
	case 1:
		{
			menu.AppendMenu(MF_STRING, ID_COMPRESSION_PASPORT, "Паспорт (старый)");
			menu.AppendMenu(MF_STRING, ID_COMPRESSION_PASSPORT1, "Паспорт 1-ой кривой");
		}
		break;	
	default:
		{
			menu.AppendMenu(MF_STRING, ID_COMPRESSION_PASPORT, "Паспорт (старый)");
		}
		break;
	}



	menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);


	*pResult = 0;
}

BOOL CLaboratoryView::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	if (pHandlerInfo == NULL)
	{
		switch (nID)
		{
		case ID_COMPRESSION_PASPORT:
			{
				if (nCode == CN_COMMAND)
				{
					this->ProbgrPasportCompress(this->m_nCompItem, 0);
				}
				else if (nCode == CN_UPDATE_COMMAND_UI)
				{
					CCmdUI* pCmdUI = (CCmdUI*)pExtra;
					pCmdUI->SetCheck(1);
					pCmdUI->Enable(TRUE);
				}
			}
			break;
		case ID_COMPRESSION_PASSPORT1:
		case ID_COMPRESSION_PASPORT2AS1:
			{
				if (nCode == CN_COMMAND)
				{
					this->ProbgrPasportCompress(this->m_nCompItem, 1);
				}
				else if (nCode == CN_UPDATE_COMMAND_UI)
				{
					CCmdUI* pCmdUI = (CCmdUI*)pExtra;
					pCmdUI->SetCheck(1);
					pCmdUI->Enable(TRUE);
				}
			}
			break;
		case ID_COMPRESSION_PASSPORT2ASMEAN:
			{
				if (nCode == CN_COMMAND)
				{
					this->ProbgrPasportCompress(this->m_nCompItem, 2);
				}
				else if (nCode == CN_UPDATE_COMMAND_UI)
				{
					CCmdUI* pCmdUI = (CCmdUI*)pExtra;
					pCmdUI->SetCheck(1);
					pCmdUI->Enable(TRUE);
				}
			}
			break;
		case ID_COMPRESSION_PASPORT2ASDIFFVYPROB:
			{
				if (nCode == CN_COMMAND)
				{
					this->ProbgrPasportCompress(this->m_nCompItem, 3);
				}
				else if (nCode == CN_UPDATE_COMMAND_UI)
				{
					CCmdUI* pCmdUI = (CCmdUI*)pExtra;
					pCmdUI->SetCheck(1);
					pCmdUI->Enable(TRUE);
				}
			}
			break;
		case ID_SOIL_PROPERTYWINDOW:
			{
				if (nCode == CN_COMMAND)
				{
					this->SoilPropertyWindow(this->m_nSoilItem);
				}
				else if (nCode == CN_UPDATE_COMMAND_UI)
				{
					CCmdUI* pCmdUI = (CCmdUI*)pExtra;
					pCmdUI->SetCheck(1);
					pCmdUI->Enable(TRUE);
				}
			}
			break;
		case ID_CUT_PASPORT:
			{
				if (nCode == CN_COMMAND)
				{
					this->ProbgrPasportCut(this->m_nCutItem, 0);
				}
				else if (nCode == CN_UPDATE_COMMAND_UI)
				{
					CCmdUI* pCmdUI = (CCmdUI*)pExtra;
					pCmdUI->SetCheck(1);
					pCmdUI->Enable(TRUE);
				}
			}
			break;
		case ID_CUT_PASSPORTNEW:
			{
				if (nCode == CN_COMMAND)
				{
					this->ProbgrPasportCut(this->m_nCutItem, 1);
				}
				else if (nCode == CN_UPDATE_COMMAND_UI)
				{
					CCmdUI* pCmdUI = (CCmdUI*)pExtra;
					pCmdUI->SetCheck(1);
					pCmdUI->Enable(TRUE);
				}
			}
			break;
		case ID_GRANULAR_PASPORT:
			{
				if (nCode == CN_COMMAND)
				{
					this->ProbgrPasportGranular(0);
				}
				else if (nCode == CN_UPDATE_COMMAND_UI)
				{
					CCmdUI* pCmdUI = (CCmdUI*)pExtra;
					pCmdUI->SetCheck(1);
					pCmdUI->Enable(TRUE);
				}
			}
			break;
		case ID_GRANULAR_PASSPORTNEW:
			{
				if (nCode == CN_COMMAND)
				{
					this->ProbgrPasportGranular(1);
				}
				else if (nCode == CN_UPDATE_COMMAND_UI)
				{
					CCmdUI* pCmdUI = (CCmdUI*)pExtra;
					pCmdUI->SetCheck(1);
					pCmdUI->Enable(TRUE);
				}
			}
			break;
		}
	}
	
	return CFormView::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CLaboratoryView::OnRclickListZriz(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE) pNMHDR;

	int r = lpnmitem->iItem;
	int c = lpnmitem->iSubItem;
	m_nCutItem = r;

	CPoint point = lpnmitem->ptAction;
	this->m_ZrizListLab.ClientToScreen(&point);

	CMenu menu;
	menu.CreatePopupMenu();
	menu.AppendMenu(MF_STRING, ID_CUT_PASPORT, "Паспорт (старый)");
	menu.AppendMenu(MF_STRING, ID_CUT_PASSPORTNEW, "Паспорт");
	menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	
	*pResult = 0;
}

void CLaboratoryView::OnKeydownListZriz(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;

	switch(pLVKeyDow->wVKey)
	{
	case VK_DELETE:
		{
			int nCutItem = m_ZrizListLab.GetSelected();
			int nSoilsItem = m_SoilsList.GetSelected();
			int nObjectItem = this->GetObjectItem();
			
			if (g_DeleteCut(this, nObjectItem, nSoilsItem, nCutItem, &this->GetDocument()->m_database))
			{
			}

		}
		break;
	}
	
	*pResult = 0;
}



void CLaboratoryView::OnProbygruntaLabnumbersLoadformNew() 
{
	m_excel_labnlist.LoadFormNew(m_ObjectNazva);	
	m_excel_labnlist.Fill();	
}

void CLaboratoryView::OnUpdateProbygruntaLabnumbersLoadformNew(CCmdUI* pCmdUI) 
{
	m_excel_labnlist.UpdateLoadFormNew(pCmdUI);	
}

void CLaboratoryView::OnProbygruntaLabnumbersLoadformExisting() 
{
	m_excel_labnlist.LoadFormExisting();	
}

void CLaboratoryView::OnUpdateProbygruntaLabnumbersLoadformExisting(CCmdUI* pCmdUI) 
{
	m_excel_labnlist.UpdateLoadFormExisting(pCmdUI);	
}

void CLaboratoryView::OnProbygruntaLabnumbersFill() 
{
	m_excel_labnlist.Fill();	
}

void CLaboratoryView::OnUpdateProbygruntaLabnumbersFill(CCmdUI* pCmdUI) 
{
	m_excel_labnlist.UpdateFill(pCmdUI, false);	
}

void CLaboratoryView::OnProbygruntaLabnumbersSavetodb() 
{
	m_excel_labnlist.SaveToDB();	
}

void CLaboratoryView::OnUpdateProbygruntaLabnumbersSavetodb(CCmdUI* pCmdUI) 
{
	m_excel_labnlist.UpdateSaveToDB(pCmdUI);	
}

void CLaboratoryView::OnProbygruntaLabnumbersDisconnectexcel() 
{
	m_excel_labnlist.DisconnectExcel();	
}

void CLaboratoryView::OnUpdateProbygruntaLabnumbersDisconnectexcel(CCmdUI* pCmdUI) 
{
	m_excel_labnlist.UpdateDisconnectExcel(pCmdUI);	
}

void enum_all_processes_and_TerminateExcel( );
void CLaboratoryView::OnExcelKill() 
{
	if (IDYES == AfxMessageBox("Вы уверены, что хотите завершить процессы Excel?", MB_YESNO, 0))
		enum_all_processes_and_TerminateExcel( );	
}



void CLaboratoryView::OnRclickListGranular(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE) pNMHDR;

	CPoint point = lpnmitem->ptAction;
	this->m_GranularListLab.ClientToScreen(&point);

	CMenu menu;
	menu.CreatePopupMenu();
	menu.AppendMenu(MF_STRING, ID_GRANULAR_PASPORT, "Паспорт (старый)");
	menu.AppendMenu(MF_STRING, ID_GRANULAR_PASSPORTNEW, "Паспорт");
	menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	
	*pResult = 0;
}
void CLaboratoryView::UpdateObjectRelatedLists(int iItem)
{
	int nObItem = iItem;
	int pos = nObItem + 1;

	SetObject setObject(&this->GetLabDoc()->m_database);
	if ( !setObject.Open(CRecordset::dynaset) )
		return;
	setObject.SetAbsolutePosition(pos);        
	m_ID_OBJ = setObject.m_ID_OBJ;

	m_ObjectNazva = setObject.m_NAZVA;

	CString where;
	where.Format("ID_OBJ = %d", m_ID_OBJ);

	CLaboratoryView::str_kt_list_where = where;

	UpdateKTListCtrl			(where, CLaboratoryView::str_kt_list_order_by);
	UpdateIGEListCtrl			(where, "ID_IGE");
	UpdateProbGruntListCtrl		(where, "ID_KT, ID_PROB");

	UpdateLitoListCtrl			("ID_OBJ = -1", "");
	UpdateFizMehListCtrl		("ID_OBJ = -1", "");
	UpdateVodaListCtrl			("ID_OBJ = -1", "");
	UpdateTSZListCtrl			("ID_OBJ = -1", "");
	UpdatePaljaListCtrl			("ID_OBJ = -1", "");
	UpdateGranularListCtrl		("ID_OBJ = -1", "");
	UpdateCutListCtrl			("ID_OBJ = -1", "");
	UpdateCompressListCtrl		("ID_OBJ = -1", "");
}

void CLaboratoryView::UpdateKTRelatedLists(int iItem)
{
}

void CLaboratoryView::UpdateSoilRelatedLists(int iItem)
{
	int nObItem = this->GetObjectItem();
	SetObject setObject(&this->GetLabDoc()->m_database);
	if ( !setObject.Open(CRecordset::dynaset) )
		return;
	setObject.SetAbsolutePosition(nObItem + 1);        
	long ID_OBJ = setObject.m_ID_OBJ;

	int nProbGrItem = iItem;
	SetProbGr setProbGr(&this->GetLabDoc()->m_database);
	setProbGr.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
	setProbGr.m_strSort.Format("ID_KT, ID_PROB");
	if ( !setProbGr.Open(CRecordset::dynaset) )
		return;
	setProbGr.SetAbsolutePosition(nProbGrItem + 1);        
	long ID_PROB = setProbGr.m_ID_PROB;
	long ID_KT = setProbGr.m_ID_KT;


	CString where;
	where.Format("ID_OBJ = %d and ID_KT = %d and ID_PROB = %d", ID_OBJ, ID_KT, ID_PROB);

	UpdateFizMehListCtrl		(where, "");
	UpdateGranularListCtrl		(where, "");
	UpdateCutListCtrl			(where, "");
	UpdateCompressListCtrl		(where, "");

}








void CLaboratoryView::OnItemchangedListSoil(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (pNMListView->uNewState)
	{
		this->UpdateSoilRelatedLists(pNMListView->iItem);
	}
	
	*pResult = 0;
}

void CLaboratoryView::OnItemchangedListEnGeoObjects(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (pNMListView->uNewState)
	{
		this->UpdateObjectRelatedLists(pNMListView->iItem);
	}
	
	*pResult = 0;
}

void CLaboratoryView::OnColumnclickListKt(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	switch(pNMListView->iSubItem)
	{
	case 0:
		{
			CLaboratoryView::str_kt_list_order_by = "ID_KT";
			this->UpdateKTListCtrl(CLaboratoryView::str_kt_list_where, CLaboratoryView::str_kt_list_order_by);
		}
		break;
	case 1:
		{
			CLaboratoryView::str_kt_list_order_by = "NAZVA";
			this->UpdateKTListCtrl(CLaboratoryView::str_kt_list_where, CLaboratoryView::str_kt_list_order_by);
		}
		break;
	}
	
	*pResult = 0;
}



void CLaboratoryView::OnUpdateProbygruntaPassportsOtnositdefongraph(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	pCmdUI->SetCheck(otnosit_def_on_graph);
}

void CLaboratoryView::OnProbygruntaPassportsOtnositdefongraph() 
{
	if (otnosit_def_on_graph)
		otnosit_def_on_graph = false;
	else
		otnosit_def_on_graph = true;	
}



void CLaboratoryView::OnExcelTodissconnectwhenloadform() 
{
	if (BaseExcel::to_disconnect_exels_when_load_form)
	{
		BaseExcel::to_disconnect_exels_when_load_form = false;
	}
	else
	{
		BaseExcel::to_disconnect_exels_when_load_form = true;
	}
}

void CLaboratoryView::OnUpdateExcelTodissconnectwhenloadformL(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(BaseExcel::to_disconnect_exels_when_load_form);	
}

void CLaboratoryView::OnExcelAutomaticsavewhendissconnectl() 
{
	if (BaseExcel::to_automatic_save_when_disconnect)
	{
		BaseExcel::to_automatic_save_when_disconnect = false;
	}
	else
	{
		BaseExcel::to_automatic_save_when_disconnect = true;
	}	
}

void CLaboratoryView::OnUpdateExcelAutomaticsavewhendissconnectl(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(BaseExcel::to_automatic_save_when_disconnect);	
}
