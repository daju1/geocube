// EnGeologyView.h: interface for the CEnGeologyView class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENGEOLOGYVIEW_H__CA204BD9_9E93_427D_957D_1935F104FBDD__INCLUDED_)
#define AFX_ENGEOLOGYVIEW_H__CA204BD9_9E93_427D_957D_1935F104FBDD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "labView.h"
#include "EnGeologyDoc.h"
#include "ExcelStatZondList.h"
#include "ExcelPaljaList.h"
#include "ExcelKTEnGeoList.h"
#include "ExcelHydroList.h"
#include "ExcelArchiveCaspGeo.h"
#include "ExcelArchiveData.h"
#include "ExcelArchiveCompression.h"
#include "ExcelArchiveGran.h"
#include "ExcelArchiveCut.h"
#include "ExcelRozrizList.h"
#include "ExcelDxfRozrizList.h"
#include "ExcelTSZList.h"
#include "ExcelLabNIGEList.h"


class CEnGeologyView : public CFormView, public CLabView  
{
	friend class CDlgStatZond;

	ExcelArchiveCaspGeo m_excel_casp_geo_archive;
	ExcelArchiveData m_excel_lab_archive;
	ExcelArchiveCompression m_excel_compression_archive;
	ExcelArchiveGran m_excel_gran_archive;
	ExcelArchiveCut m_excel_cut_archive;
	ExcelKTEnGeoList m_excel_ktlist;
	ExcelHydroList m_excel_hydro_list;
	ExcelStatZondList m_excel_stat_zond;
	ExcelStatZondList m_excel_stat_zond_output;
	ExcelPaljaList m_excel_palja;
	ExcelRozrizList m_excel_rozriz_list;
	ExcelDxfRozrizList m_excel_dxf_rozriz_list;
	ExcelTSZList m_excel_tsz_list;

	ExcelLabNIGEList m_excel_labnlist;

public:
	CEnGeologyView();
	DECLARE_DYNCREATE(CEnGeologyView)

	virtual ~CEnGeologyView();
	//{{AFX_DATA(CEnGeologyView)
	enum { IDD = IDD_ENGEO_FORM };
	FizMehList	m_FizMehList;
	CompressList	m_CompressList;
	ZrizList	m_ZrizList;
	CGranularList	m_GranularList;
	CSoilsList	m_SoilsList;
	CDBViewList	m_ListView;
	CKTList	m_KTList;
	CIGEList	m_IGEList;
	CLithoList	m_LithoList;
	CVodaList	m_VodaList;
	CTSZList	m_TSZList;
	CPaljaList	m_PaljaList;
	CDataBaseTalblesList	m_DataBaseTablesList;
	CEnGeoObjectsList	    m_EnGeoObjectsList;
	//}}AFX_DATA
// Attributes
public:
	CEnGeologyDoc * GetDocument();
	virtual void DisconnectAllExcels();
// Operations
public:
	virtual void UpdateObjectRelatedLists(int iItem);
	virtual void UpdateKTRelatedLists(int iItem);
	virtual void UpdateSoilRelatedLists(int iItem);

	long m_ID_IGE;
	/*virtual*/ void UpdateIGERelatedLists(int iItem);
	/*virtual*/ void UpdateDBTablesRelatedLists(int iItem);

	void LabLayerChastnye(long id_ige);
	void LabLayerNormatives(int type, long id_ige);
	void LabLayerPropertyWindow(long id_ige);

	static CString str_kt_list_order_by;
	static CString str_kt_list_where;

	virtual void UpdateObjectsListCtrl(CString where, CString order_by);
	virtual void UpdateLitoListCtrl(CString where, CString order_by);
	virtual void UpdateProbGruntListCtrl(CString where, CString order_by);
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
	/*virtual*/ int GetIGEItem();
	virtual int GetKTItem();
	virtual int GetProbGrItem();
	virtual CLabDoc * GetLabDoc();
	virtual bool GetSetProbGrFilterStr(long ID_OBJ, CString & strFilter);

	//void OnFile3d();

	int m_nSoilItem;
	int m_nCompItem;
	int m_nCutItem;
	//int m_nIGEItem;
	int m_nObjectItem;

	bool DefineZoom(long ID_OBJ);


	void ObjectsInsertto3d();


	bool to_draw;

	enum soil_list_type
	{
		by_kt,
		by_ige
	};

	soil_list_type m_soil_list_type;

	virtual HWND GetWindow(){return this->GetWindow();}

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEnGeologyView)
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
	//{{AFX_MSG(CEnGeologyView)
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnFileNewObject();
	afx_msg void OnFileDeleteObject();
	afx_msg void OnUpdateFileDeleteObject(CCmdUI* pCmdUI);
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
	afx_msg void OnObjectsImportobject();
	afx_msg void OnProbgrPasportAllpossible();
	afx_msg void OnProbgrSoilname();
	afx_msg void OnProbgrPasportLanguage();
	afx_msg void OnFileOpen();
	afx_msg void OnUpdateFileOpen(CCmdUI* pCmdUI);
	afx_msg void OnProbygruntaDblclickmode();
	afx_msg void OnProbgrClassification();
	afx_msg void OnRclickListCompress(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydownListCompress(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickListZriz(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydownListZriz(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnArchiveLaboratoryLoadformNew();
	afx_msg void OnUpdateArchiveLaboratoryLoadformNew(CCmdUI* pCmdUI);
	afx_msg void OnArchiveLaboratoryFill();
	afx_msg void OnUpdateArchiveLaboratoryFill(CCmdUI* pCmdUI);
	afx_msg void OnArchiveLaboratorySavetodb();
	afx_msg void OnUpdateArchiveLaboratorySavetodb(CCmdUI* pCmdUI);
	afx_msg void OnArchiveLaboratoryDisconnectexcel();
	afx_msg void OnUpdateArchiveLaboratoryDisconnectexcel(CCmdUI* pCmdUI);
	afx_msg void OnArchiveLaboratoryLoadformExisting();
	afx_msg void OnUpdateArchiveLaboratoryLoadformExisting(CCmdUI* pCmdUI);
	afx_msg void OnKtKtlistFill();
	afx_msg void OnUpdateKtKtlistFill(CCmdUI* pCmdUI);
	afx_msg void OnArchiveCompressionLoadformNew();
	afx_msg void OnUpdateArchiveCompressionLoadformNew(CCmdUI* pCmdUI);
	afx_msg void OnArchiveCompressionLoadformExisting();
	afx_msg void OnUpdateArchiveCompressionLoadformExisting(CCmdUI* pCmdUI);
	afx_msg void OnArchiveCompressionFill();
	afx_msg void OnUpdateArchiveCompressionFill(CCmdUI* pCmdUI);
	afx_msg void OnArchiveCompressionSavetodb();
	afx_msg void OnUpdateArchiveCompressionSavetodb(CCmdUI* pCmdUI);
	afx_msg void OnArchiveCompressionDisconnectexcel();
	afx_msg void OnUpdateArchiveCompressionDisconnectexcel(CCmdUI* pCmdUI);
	afx_msg void OnArchiveCompressionFill2();
	afx_msg void OnUpdateArchiveCompressionFill2(CCmdUI* pCmdUI);
	afx_msg void OnArchiveCompressionFillalllabn();
	afx_msg void OnUpdateArchiveCompressionFillalllabn(CCmdUI* pCmdUI);
	afx_msg void OnArchiveCompressionFillalllabn2();
	afx_msg void OnUpdateArchiveCompressionFillalllabn2(CCmdUI* pCmdUI);
	afx_msg void OnArchiveCompressionFillAlllabnIf2then2();
	afx_msg void OnUpdateArchiveCompressionFillAlllabnIf2then2(CCmdUI* pCmdUI);
	afx_msg void OnArchiveCutLoadformNew();
	afx_msg void OnUpdateArchiveCutLoadformNew(CCmdUI* pCmdUI);
	afx_msg void OnArchiveCutLoadformExisting();
	afx_msg void OnUpdateArchiveCutLoadformExisting(CCmdUI* pCmdUI);
	afx_msg void OnArchiveCutFillCut();
	afx_msg void OnUpdateArchiveCutFillCut(CCmdUI* pCmdUI);
	afx_msg void OnArchiveCutFillAlllabn();
	afx_msg void OnUpdateArchiveCutFillAlllabn(CCmdUI* pCmdUI);
	afx_msg void OnArchiveCutSavetodb();
	afx_msg void OnUpdateArchiveCutSavetodb(CCmdUI* pCmdUI);
	afx_msg void OnArchiveCutDisconnectexcel();
	afx_msg void OnUpdateArchiveCutDisconnectexcel(CCmdUI* pCmdUI);
	afx_msg void OnArchiveCutFillAlllabn2();
	afx_msg void OnUpdateArchiveCutFillAlllabn2(CCmdUI* pCmdUI);
	afx_msg void OnArchiveGranLoadformNew();
	afx_msg void OnUpdateArchiveGranLoadformNew(CCmdUI* pCmdUI);
	afx_msg void OnArchiveGranLoadformExisting();
	afx_msg void OnUpdateArchiveGranLoadformExisting(CCmdUI* pCmdUI);
	afx_msg void OnArchiveGranFillGran();
	afx_msg void OnUpdateArchiveGranFillGran(CCmdUI* pCmdUI);
	afx_msg void OnArchiveGranFillAlllabn();
	afx_msg void OnUpdateArchiveGranFillAlllabn(CCmdUI* pCmdUI);
	afx_msg void OnArchiveGranSavetodb();
	afx_msg void OnUpdateArchiveGranSavetodb(CCmdUI* pCmdUI);
	afx_msg void OnArchiveGranDisconnectexcel();
	afx_msg void OnUpdateArchiveGranDisconnectexcel(CCmdUI* pCmdUI);
	afx_msg void OnExcelKill();
	afx_msg void OnRclickListGranular(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnObjectsSetnaborgruntov();
	afx_msg void OnKtStatzond();
	afx_msg void OnUpdateKtStatzond(CCmdUI* pCmdUI);
	afx_msg void OnKtPalja();
	afx_msg void OnUpdateKtPalja(CCmdUI* pCmdUI);
	afx_msg void OnKtStatzondLoadformNew();
	afx_msg void OnUpdateKtStatzondLoadformNew(CCmdUI* pCmdUI);
	afx_msg void OnKtStatzondLoadformExisting();
	afx_msg void OnUpdateKtStatzondLoadformExisting(CCmdUI* pCmdUI);
	afx_msg void OnKtStatzondFill();
	afx_msg void OnUpdateKtStatzondFill(CCmdUI* pCmdUI);
	afx_msg void OnKtStatzondSavetodb();
	afx_msg void OnUpdateKtStatzondSavetodb(CCmdUI* pCmdUI);
	afx_msg void OnKtStatzondDisconnectexcel();
	afx_msg void OnUpdateKtStatzondDisconnectexcel(CCmdUI* pCmdUI);
	afx_msg void OnKtPaljaLoadformNew();
	afx_msg void OnUpdateKtPaljaLoadformNew(CCmdUI* pCmdUI);
	afx_msg void OnKtPaljaLoadformExisting();
	afx_msg void OnUpdateKtPaljaLoadformExisting(CCmdUI* pCmdUI);
	afx_msg void OnKtPaljaFill();
	afx_msg void OnUpdateKtPaljaFill(CCmdUI* pCmdUI);
	afx_msg void OnKtPaljaCompute();
	afx_msg void OnUpdateKtPaljaCompute(CCmdUI* pCmdUI);
	afx_msg void OnKtPaljaSavetodb();
	afx_msg void OnUpdateKtPaljaSavetodb(CCmdUI* pCmdUI);
	afx_msg void OnKtPaljaDisconnectexcel();
	afx_msg void OnUpdateKtPaljaDisconnectexcel(CCmdUI* pCmdUI);
	afx_msg void OnKtStatzondCompute();
	afx_msg void OnUpdateKtStatzondCompute(CCmdUI* pCmdUI);
	afx_msg void OnKtZondustparam();
	afx_msg void OnObjectsCopygrunty();
	afx_msg void OnArchiveCutFillCutas2colomns();
	afx_msg void OnUpdateArchiveCutFillCutas2colomns(CCmdUI* pCmdUI);
	afx_msg void OnArchiveCutFillAlllabnas2colomns();
	afx_msg void OnUpdateArchiveCutFillAlllabnas2colomns(CCmdUI* pCmdUI);
	afx_msg void OnKtAllpalja();
	afx_msg void OnArchiveDeleteallcuts();
	afx_msg void OnArchiveDeleteallcompressions();
	afx_msg void OnKtRozrizlistLoadformNew();
	afx_msg void OnUpdateKtRozrizlistLoadformNew(CCmdUI* pCmdUI);
	afx_msg void OnKtRozrizlistLoadformExisting();
	afx_msg void OnUpdateKtRozrizlistLoadformExisting(CCmdUI* pCmdUI);
	afx_msg void OnKtRozrizlistFill();
	afx_msg void OnUpdateKtRozrizlistFill(CCmdUI* pCmdUI);
	afx_msg void OnKtRozrizlistSavetodb();
	afx_msg void OnUpdateKtRozrizlistSavetodb(CCmdUI* pCmdUI);
	afx_msg void OnKtRozrizlistDisconnectexcel();
	afx_msg void OnUpdateKtRozrizlistDisconnectexcel(CCmdUI* pCmdUI);
	afx_msg void OnArchiveDeleteallgranulars();
	afx_msg void OnArchiveDeleteallfizmeh();
	afx_msg void OnKeydownListEnGeoObjects(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedListEnGeoObjects(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedListKt(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedListSoil(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKtPck2fiz();
	afx_msg void OnKtTszlistLoadformNew();
	afx_msg void OnUpdateKtTszlistLoadformNew(CCmdUI* pCmdUI);
	afx_msg void OnKtTszlistLoadformExisting();
	afx_msg void OnUpdateKtTszlistLoadformExisting(CCmdUI* pCmdUI);
	afx_msg void OnKtTszlistFill();
	afx_msg void OnUpdateKtTszlistFill(CCmdUI* pCmdUI);
	afx_msg void OnKtTszlistSavetodb();
	afx_msg void OnUpdateKtTszlistSavetodb(CCmdUI* pCmdUI);
	afx_msg void OnKtTszlistDisconnectexcel();
	afx_msg void OnUpdateKtTszlistDisconnectexcel(CCmdUI* pCmdUI);
	afx_msg void OnKtDxfrozrizlistLoadformNew();
	afx_msg void OnUpdateKtDxfrozrizlistLoadformNew(CCmdUI* pCmdUI);
	afx_msg void OnKtDxfrozrizlistLoadformExisting();
	afx_msg void OnUpdateKtDxfrozrizlistLoadformExisting(CCmdUI* pCmdUI);
	afx_msg void OnKtDxfrozrizlistFill();
	afx_msg void OnUpdateKtDxfrozrizlistFill(CCmdUI* pCmdUI);
	afx_msg void OnKtDxfrozrizlistSavetodb();
	afx_msg void OnUpdateKtDxfrozrizlistSavetodb(CCmdUI* pCmdUI);
	afx_msg void OnKtDxfrozrizlistDisconnectexcel();
	afx_msg void OnUpdateKtDxfrozrizlistDisconnectexcel(CCmdUI* pCmdUI);
	afx_msg void OnKtHydrolistLoadformNew();
	afx_msg void OnUpdateKtHydrolistLoadformNew(CCmdUI* pCmdUI);
	afx_msg void OnKtHydrolistLoadformExisting();
	afx_msg void OnUpdateKtHydrolistLoadformExisting(CCmdUI* pCmdUI);
	afx_msg void OnKtHydrolistSavetodb();
	afx_msg void OnUpdateKtHydrolistSavetodb(CCmdUI* pCmdUI);
	afx_msg void OnKtHydrolistDisconnectexcel();
	afx_msg void OnUpdateKtHydrolistDisconnectexcel(CCmdUI* pCmdUI);
	afx_msg void OnKtKtlistSaveandrename();
	afx_msg void OnUpdateKtKtlistSaveandrename(CCmdUI* pCmdUI);
	afx_msg void OnItemchangedListDbTables(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickListIge(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedListIge(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnProbgrIgeautofill();
	afx_msg void OnColumnclickListKt(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickListSoil(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnViewPropertywindowwithPlot();
	afx_msg void OnUpdateViewPropertywindowwithPlot(CCmdUI* pCmdUI);
	afx_msg void OnViewPropertywindowwithResults();
	afx_msg void OnUpdateViewPropertywindowwithResults(CCmdUI* pCmdUI);
	afx_msg void OnViewPropertywindowwithLabnumbertriallist();
	afx_msg void OnUpdateViewPropertywindowwithLabnumbertriallist(CCmdUI* pCmdUI);
	afx_msg void OnViewPropertywindowwithNormatives();
	afx_msg void OnUpdateViewPropertywindowwithNormatives(CCmdUI* pCmdUI);
	afx_msg void OnViewPropertywindowwithCorrelation();
	afx_msg void OnUpdateViewPropertywindowwithCorrelation(CCmdUI* pCmdUI);
	afx_msg void OnViewPropertywindowwithNormativesbyallexperiences();
	afx_msg void OnUpdateViewPropertywindowwithNormativesbyallexperiences(CCmdUI* pCmdUI);
	afx_msg void OnUpdateProbgrPasportOtnositdefongraph(CCmdUI* pCmdUI);
	afx_msg void OnProbgrPasportOtnositdefongraph();
	afx_msg void OnObjectsNaborige();
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
	afx_msg void OnProbgrExcludedtriallist();
	afx_msg void OnProbgrSoilautonames();
	afx_msg void OnExcelTodissconnectwhenloadform();
	afx_msg void OnUpdateExcelTodissconnectwhenloadformG(CCmdUI* pCmdUI);
	afx_msg void OnExcelAutomaticsavewhendisconnect();
	afx_msg void OnUpdateExcelAutomaticsavewhendisconnect(CCmdUI* pCmdUI);
	afx_msg void OnFile3d();
	afx_msg void OnUpdateFile3d(CCmdUI* pCmdUI);
	afx_msg void OnArchiveCaspgeoLoadformNew();
	afx_msg void OnUpdateArchiveCaspgeoLoadformNew(CCmdUI* pCmdUI);
	afx_msg void OnArchiveCaspgeoLoadformExisting();
	afx_msg void OnUpdateArchiveCaspgeoLoadformExisting(CCmdUI* pCmdUI);
	afx_msg void OnArchiveCaspgeoFill();
	afx_msg void OnUpdateArchiveCaspgeoFill(CCmdUI* pCmdUI);
	afx_msg void OnArchiveCaspgeoSavetodb();
	afx_msg void OnUpdateArchiveCaspgeoSavetodb(CCmdUI* pCmdUI);
	afx_msg void OnArchiveCaspgeoDisconnectexcel();
	afx_msg void OnUpdateArchiveCaspgeoDisconnectexcel(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

#ifndef _DEBUG  // debug version in labView.cpp
inline CEnGeologyDoc* CEnGeologyView::GetDocument()
   { return (CEnGeologyDoc*)m_pDocument; }
#endif


#endif // !defined(AFX_ENGEOLOGYVIEW_H__CA204BD9_9E93_427D_957D_1935F104FBDD__INCLUDED_)
