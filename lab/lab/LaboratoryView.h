// LaboratoryView.h: interface for the CLaboratoryView class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LABORATORYVIEW_H__664982FF_B603_4562_BC33_16AD5AAFB3A3__INCLUDED_)
#define AFX_LABORATORYVIEW_H__664982FF_B603_4562_BC33_16AD5AAFB3A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "labView.h"
#include "LaboratoryDoc.h"
#include "LabObjectsList.h"
#include "CompressListLab.h"
#include "ZrizListLab.h"
#include "FizMehListLab.h"
#include "GranularListLab.h"
#include "SoilsListLab.h"
#include "KTLabList.h"

#include "../../excel_connect/src/myexcel.h"

#include "ExcelSandGranular.h"
#include "ExcelAreometrGranular.h"
#include "ExcelVegetableRemains.h"
#include "ExcelPlotnostChastic.h"
#include "ExcelPlotnostChastic1.h"
#include "ExcelPlotnostGrunta.h"
#include "ExcelWlazhnost.h"
#include "ExcelWL.h"
#include "ExcelWLP.h"
#include "ExcelCut.h"
#include "ExcelCompression.h"
#include "ExcelKTLabList.h"
#include "ExcelLabNList.h"




class CLaboratoryView : public CFormView, public CLabView    
{

	ExcelSandGranular m_excel_sand_granular;
	ExcelAreometrGranular m_excel_areometr_granular;

	ExcelVegetableRemains m_excel_vegetable_remains;

	ExcelPlotnostChastic m_excel_plotnost_chastic;
	ExcelPlotnostChastic1 m_excel_plotnost_chastic1;
	ExcelPlotnostGrunta m_excel_plotnost_grunta;

	ExcelWlazhnost m_excel_wlazhnost;
	ExcelWL m_excel_WL;
	ExcelWLP m_excel_WLP;

	ExcelCut m_excel_cut;
	ExcelCompression m_excel_compression;

	ExcelKTLabList m_excel_ktlist;
	ExcelLabNList m_excel_labnlist;

	virtual void DisconnectAllExcels();

public:
	CLaboratoryView();
	DECLARE_DYNCREATE(CLaboratoryView)
	virtual ~CLaboratoryView();
public:
	//{{AFX_DATA(CLaboratoryView)
	enum { IDD = IDD_LAB_FORM };
//	CPropList	m_PropList;
	ZrizListLab	m_ZrizListLab;
	CompressListLab	m_CompressListLab;
	FizMehListLab	m_FizMehListLab;
	GranularListLab	m_GranularListLab;
	CSoilsListLab	m_SoilsList;
//	CDBViewList	m_ListView;
	CKTLabList	m_KTLabList;
//	CDataBaseTalblesList	m_DataBaseTablesList;
	CLabObjectsList	    m_LabObjectsList;
	//}}AFX_DATA
// Attributes
public:
	CLaboratoryDoc * GetDocument();
// Operations
public:
	virtual void UpdateObjectRelatedLists(int iItem);
	virtual void UpdateKTRelatedLists(int iItem);
	virtual void UpdateSoilRelatedLists(int iItem);

	static CString str_kt_list_order_by;
	static CString str_kt_list_where;

	virtual void UpdateObjectsListCtrl(CString where, CString order_by);
	virtual void UpdateProbGruntListCtrl(CString where, CString order_by);
	virtual void UpdateLitoListCtrl(CString where, CString order_by);
	virtual void UpdateKTListCtrl(CString where, CString order_by);
	virtual void UpdateIGEListCtrl(CString where, CString order_by);
	virtual void UpdateVodaListCtrl(CString where, CString order_by);
	virtual void UpdateTSZListCtrl(CString where, CString order_by);
	virtual void UpdatePaljaListCtrl(CString where, CString order_by);
	virtual void UpdateCompressListCtrl(CString where, CString order_by);
	virtual void UpdateCutListCtrl(CString where, CString order_by);
	virtual void UpdateFizMehListCtrl(CString where, CString order_by);
	virtual void UpdateGranularListCtrl(CString where, CString order_by);

	virtual void EnableObjectList(BOOL bEnable);


	virtual int GetObjectItem();
	virtual int GetKTItem();
	virtual int GetProbGrItem();
	virtual CLabDoc * GetLabDoc();
	virtual bool GetSetProbGrFilterStr(long ID_OBJ, CString & strFilter);

	int m_nCompItem;
	int m_nCutItem;
	int m_nSoilItem;

	virtual HWND GetWindow(){return this->GetWindow();}

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLaboratoryView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


// Generated message map functions
protected:
	//{{AFX_MSG(CLaboratoryView)
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnLaboratorySandGranularLoadFormNew();
	afx_msg void OnUpdateLaboratorySandGranularLoadFormNew(CCmdUI* pCmdUI);
	afx_msg void OnLaboratorySandGranularLoadFormExisting();
	afx_msg void OnUpdateLaboratorySandGranularLoadFormExisting(CCmdUI* pCmdUI);
	afx_msg void OnLaboratorySandGranularCompute();
	afx_msg void OnUpdateLaboratorySandGranularCompute(CCmdUI* pCmdUI);
	afx_msg void OnLaboratorySandGranularSaveToDB();
	afx_msg void OnUpdateLaboratorySandGranularSaveToDB(CCmdUI* pCmdUI);
	afx_msg void OnLaboratorySandgranularDisconnectExcel();
	afx_msg void OnUpdateLaboratorySandGranularDisconnectExcel(CCmdUI* pCmdUI);
	afx_msg void OnFileNewObject();
	afx_msg void OnFileDeleteObject();
	afx_msg void OnUpdateFileDeleteObject(CCmdUI* pCmdUI);
	afx_msg void OnLaboratoryAreometrGranularLoadFormNew();
	afx_msg void OnUpdateLaboratoryAreometrGranularLoadFormNew(CCmdUI* pCmdUI);
	afx_msg void OnLaboratoryAreometrGranularLoadFormExisting();
	afx_msg void OnUpdateLaboratoryAreometrGranularLoadFormExisting(CCmdUI* pCmdUI);
	afx_msg void OnLaboratoryAreometrGranularCompute();
	afx_msg void OnUpdateLaboratoryAreometrGranularCompute(CCmdUI* pCmdUI);
	afx_msg void OnLaboratoryAreometrGranularSaveToDB();
	afx_msg void OnUpdateLaboratoryAreometrGranularSaveToDB(CCmdUI* pCmdUI);
	afx_msg void OnLaboratoryAreometrGranularDisconnectExcel();
	afx_msg void OnUpdateLaboratoryAreometrGranularDisconnectExcel(CCmdUI* pCmdUI);
	afx_msg void OnLaboratoryVegetableRemainsLoadFormNew();
	afx_msg void OnUpdateLaboratoryVegetableRemainsLoadFormNew(CCmdUI* pCmdUI);
	afx_msg void OnLaboratoryVegetableRemainsLoadFormExisting();
	afx_msg void OnUpdateLaboratoryVegetableRemainsLoadFormExisting(CCmdUI* pCmdUI);
	afx_msg void OnLaboratoryVegetableRemainsCompute();
	afx_msg void OnUpdateLaboratoryVegetableRemainsCompute(CCmdUI* pCmdUI);
	afx_msg void OnLaboratoryVegetableRemainsSavetodb();
	afx_msg void OnUpdateLaboratoryVegetableRemainsSavetodb(CCmdUI* pCmdUI);
	afx_msg void OnLaboratoryVegetableRemainsDisconnectExcel();
	afx_msg void OnUpdateLaboratoryVegetableRemainsDisconnectExcel(CCmdUI* pCmdUI);
	afx_msg void OnLaboratoryPlotnostChasticLoadFormNew();
	afx_msg void OnUpdateLaboratoryPlotnostChasticLoadFormNew(CCmdUI* pCmdUI);
	afx_msg void OnLaboratoryPlotnostChasticLoadFormExisting();
	afx_msg void OnUpdateLaboratoryPlotnostChasticLoadFormExisting(CCmdUI* pCmdUI);
	afx_msg void OnLaboratoryPlotnostChasticCompute();
	afx_msg void OnUpdateLaboratoryPlotnostChasticCompute(CCmdUI* pCmdUI);
	afx_msg void OnLaboratoryPlotnostChasticSavetodb();
	afx_msg void OnUpdateLaboratoryPlotnostChasticSavetodb(CCmdUI* pCmdUI);
	afx_msg void OnLaboratoryPlotnostChasticDisconnectExcel();
	afx_msg void OnUpdateLaboratoryPlotnostChasticDisconnectExcel(CCmdUI* pCmdUI);
	afx_msg void OnLaboratoryPlotnostGruntaLoadFormNew();
	afx_msg void OnUpdateLaboratoryPlotnostGruntaLoadFormNew(CCmdUI* pCmdUI);
	afx_msg void OnLaboratoryPlotnostGruntaLoadFormExisting();
	afx_msg void OnUpdateLaboratoryPlotnostGruntaLoadFormExisting(CCmdUI* pCmdUI);
	afx_msg void OnLaboratoryPlotnostGruntaCompute();
	afx_msg void OnUpdateLaboratoryPlotnostGruntaCompute(CCmdUI* pCmdUI);
	afx_msg void OnLaboratoryPlotnostGruntaSavetodb();
	afx_msg void OnUpdateLaboratoryPlotnostGruntaSavetodb(CCmdUI* pCmdUI);
	afx_msg void OnLaboratoryPlotnostGruntaDisconnectExcel();
	afx_msg void OnUpdateLaboratoryPlotnostGruntaDisconnectExcel(CCmdUI* pCmdUI);
	afx_msg void OnLaboratoryWLoadformNew();
	afx_msg void OnUpdateLaboratoryWLoadformNew(CCmdUI* pCmdUI);
	afx_msg void OnLaboratoryWLoadformExisting();
	afx_msg void OnUpdateLaboratoryWLoadformExisting(CCmdUI* pCmdUI);
	afx_msg void OnLaboratoryWCompute();
	afx_msg void OnUpdateLaboratoryWCompute(CCmdUI* pCmdUI);
	afx_msg void OnLaboratoryWSavetodb();
	afx_msg void OnUpdateLaboratoryWSavetodb(CCmdUI* pCmdUI);
	afx_msg void OnLaboratoryWDisconnectexcel();
	afx_msg void OnUpdateLaboratoryWDisconnectexcel(CCmdUI* pCmdUI);
	afx_msg void OnLaboratoryWlLoadformNew();
	afx_msg void OnUpdateLaboratoryWlLoadformNew(CCmdUI* pCmdUI);
	afx_msg void OnLaboratoryWlLoadformExisting();
	afx_msg void OnUpdateLaboratoryWlLoadformExisting(CCmdUI* pCmdUI);
	afx_msg void OnLaboratoryWlCompute();
	afx_msg void OnUpdateLaboratoryWlCompute(CCmdUI* pCmdUI);
	afx_msg void OnLaboratoryWlSavetodb();
	afx_msg void OnUpdateLaboratoryWlSavetodb(CCmdUI* pCmdUI);
	afx_msg void OnLaboratoryWlDisconnectexcel();
	afx_msg void OnUpdateLaboratoryWlDisconnectexcel(CCmdUI* pCmdUI);
	afx_msg void OnLaboratoryWlpLoadformNew();
	afx_msg void OnUpdateLaboratoryWlpLoadformNew(CCmdUI* pCmdUI);
	afx_msg void OnLaboratoryWlpLoadformExisting();
	afx_msg void OnUpdateLaboratoryWlpLoadformExisting(CCmdUI* pCmdUI);
	afx_msg void OnLaboratoryWlpCompute();
	afx_msg void OnUpdateLaboratoryWlpCompute(CCmdUI* pCmdUI);
	afx_msg void OnLaboratoryWlpSavetodb();
	afx_msg void OnUpdateLaboratoryWlpSavetodb(CCmdUI* pCmdUI);
	afx_msg void OnLaboratoryWlpDisconnectexcel();
	afx_msg void OnUpdateLaboratoryWlpDisconnectexcel(CCmdUI* pCmdUI);
	afx_msg void OnLaboratoryCutLoadformNew();
	afx_msg void OnUpdateLaboratoryCutLoadformNew(CCmdUI* pCmdUI);
	afx_msg void OnLaboratoryCutLoadformExisting();
	afx_msg void OnUpdateLaboratoryCutLoadformExisting(CCmdUI* pCmdUI);
	afx_msg void OnLaboratoryCutCompute();
	afx_msg void OnUpdateLaboratoryCutCompute(CCmdUI* pCmdUI);
	afx_msg void OnLaboratoryCutSavetodb();
	afx_msg void OnUpdateLaboratoryCutSavetodb(CCmdUI* pCmdUI);
	afx_msg void OnLaboratoryCutDisconnectexcel();
	afx_msg void OnUpdateLaboratoryCutDisconnectexcel(CCmdUI* pCmdUI);
	afx_msg void OnLaboratoryCompressionLoadformNew();
	afx_msg void OnUpdateLaboratoryCompressionLoadformNew(CCmdUI* pCmdUI);
	afx_msg void OnLaboratoryCompressionLoadformExisting();
	afx_msg void OnUpdateLaboratoryCompressionLoadformExisting(CCmdUI* pCmdUI);
	afx_msg void OnLaboratoryCompressionCompute();
	afx_msg void OnUpdateLaboratoryCompressionCompute(CCmdUI* pCmdUI);
	afx_msg void OnLaboratoryCompressionSavetodb();
	afx_msg void OnUpdateLaboratoryCompressionSavetodb(CCmdUI* pCmdUI);
	afx_msg void OnLaboratoryCompressionDisconnectexcel();
	afx_msg void OnUpdateLaboratoryCompressionDisconnectexcel(CCmdUI* pCmdUI);
	afx_msg void OnProbgrNewlabnumber();
	afx_msg void OnUpdateProbgrNewlabnumber(CCmdUI* pCmdUI);
	afx_msg void OnKtKtlistLoadformNew();
	afx_msg void OnUpdateKtKtlistLoadformNew(CCmdUI* pCmdUI);
	afx_msg void OnKtKtlistLoadformExisting();
	afx_msg void OnUpdateKtKtlistLoadformExisting(CCmdUI* pCmdUI);
	afx_msg void OnKtKtlistSavetodb();
	afx_msg void OnUpdateKtKtlistSavetodb(CCmdUI* pCmdUI);
	afx_msg void OnKtKtlistDisconnectexcel();
	afx_msg void OnUpdateKtKtlistDisconnectexcel(CCmdUI* pCmdUI);
	afx_msg void OnProbgrPasportAllpossible();
	afx_msg void OnProbgrSoilname();
	afx_msg void OnExportobject();
	afx_msg void OnLanguage();
	afx_msg void OnFileOpen();
	afx_msg void OnUpdateFileOpen(CCmdUI* pCmdUI);
	afx_msg void OnProbygruntaDblclickmode();
	afx_msg void OnLaboratoryRepeatings();
	afx_msg void OnKeydownListCompress(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickListCompress(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickListZriz(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydownListZriz(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLaboratoryPlotnostchastic1LoadformNew();
	afx_msg void OnUpdateLaboratoryPlotnostchastic1LoadformNew(CCmdUI* pCmdUI);
	afx_msg void OnLaboratoryPlotnostchastic1Savetodb();
	afx_msg void OnUpdateLaboratoryPlotnostchastic1Savetodb(CCmdUI* pCmdUI);
	afx_msg void OnLaboratoryPlotnostchastic1Disconnectexcel();
	afx_msg void OnUpdateLaboratoryPlotnostchastic1Disconnectexcel(CCmdUI* pCmdUI);
	afx_msg void OnLaboratoryPlotnostchastic1LoadformExisting();
	afx_msg void OnUpdateLaboratoryPlotnostchastic1LoadformExisting(CCmdUI* pCmdUI);
	afx_msg void OnLaboratoryPlotnostgruntaSavetodbDifferentVyprob();
	afx_msg void OnUpdateLaboratoryPlotnostgruntaSavetodbDifferentVyprob(CCmdUI* pCmdUI);
	afx_msg void OnLaboratoryWSavetodbDifferentVyprob();
	afx_msg void OnUpdateLaboratoryWSavetodbDifferentVyprob(CCmdUI* pCmdUI);
	afx_msg void OnLaboratoryCompressionFill();
	afx_msg void OnUpdateLaboratoryCompressionFill(CCmdUI* pCmdUI);
	afx_msg void OnProbygruntaLabnumbersLoadformNew();
	afx_msg void OnUpdateProbygruntaLabnumbersLoadformNew(CCmdUI* pCmdUI);
	afx_msg void OnProbygruntaLabnumbersLoadformExisting();
	afx_msg void OnUpdateProbygruntaLabnumbersLoadformExisting(CCmdUI* pCmdUI);
	afx_msg void OnProbygruntaLabnumbersFill();
	afx_msg void OnUpdateProbygruntaLabnumbersFill(CCmdUI* pCmdUI);
	afx_msg void OnProbygruntaLabnumbersSavetodb();
	afx_msg void OnUpdateProbygruntaLabnumbersSavetodb(CCmdUI* pCmdUI);
	afx_msg void OnProbygruntaLabnumbersDisconnectexcel();
	afx_msg void OnUpdateProbygruntaLabnumbersDisconnectexcel(CCmdUI* pCmdUI);
	afx_msg void OnKtKtlistFill();
	afx_msg void OnUpdateKtKtlistFill(CCmdUI* pCmdUI);
	afx_msg void OnExcelKill();
	afx_msg void OnLaboratoryCutFill();
	afx_msg void OnUpdateLaboratoryCutFill(CCmdUI* pCmdUI);
	afx_msg void OnRclickListGranular(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedListSoil(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedListEnGeoObjects(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKtKtlistSaveandrename();
	afx_msg void OnUpdateKtKtlistSaveandrename(CCmdUI* pCmdUI);
	afx_msg void OnColumnclickListKt(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickListSoil(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnUpdateProbygruntaPassportsOtnositdefongraph(CCmdUI* pCmdUI);
	afx_msg void OnProbygruntaPassportsOtnositdefongraph();
	afx_msg void OnExcelTodissconnectwhenloadform();
	afx_msg void OnUpdateExcelTodissconnectwhenloadformL(CCmdUI* pCmdUI);
	afx_msg void OnExcelAutomaticsavewhendissconnectl();
	afx_msg void OnUpdateExcelAutomaticsavewhendissconnectl(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in labView.cpp
inline CLaboratoryDoc* CLaboratoryView::GetDocument()
   { return (CLaboratoryDoc*)m_pDocument; }
#endif


#endif // !defined(AFX_LABORATORYVIEW_H__664982FF_B603_4562_BC33_16AD5AAFB3A3__INCLUDED_)
