// labView.h : interface of the CLabView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LABVIEW_H__A2E8DFE3_FC2E_48AA_8C39_20E359BC4D31__INCLUDED_)
#define AFX_LABVIEW_H__A2E8DFE3_FC2E_48AA_8C39_20E359BC4D31__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EnGeoObjectsList.h"
#include "DataBaseTalblesList.h"
#include "KTListCtrl.h"
#include "TSZList.h"
#include "PaljaList.h"
#include "IGEList.h"
#include "LithoList.h"
#include "VodaList.h"
#include "DBViewList.h"
#include "SoilsList.h"
#include "ZrizList.h"
#include "CompressList.h"
#include "FizMehList.h"
#include "GranularList.h"
#include "PropList.h"
#include "labDoc.h"


#include "DBTableCilce0.h"
#include "DBTableCilce.h"
#include "DBTableCompress.h"

#include "DBTableZriz0.h"
#include "DBTableZriz.h"
#include "DBTableZriz_tbl.h"

#include "DBTableProp.h"
#include "DBTableGranular.h"
#include "DBTableSoils.h"

#include "DBTableKT.h"
#include "DBTableRozrizy.h"
#include "DBTableRozriz.h"

#include "DBTableLito0.h"
#include "DBTableIGE0.h"
#include "DBTableLito.h"
#include "DBTableIGE.h"
#include "DBTableGrunty.h"
#include "DBTableVoda.h"
#include "DBTableGenezis.h"
#include "DBTableUmpoz.h"

#include "DBTableCubeSize.h"
#include "DBTableGridDataUsedAlg.h"

#include "DBTableGridData.h"
#include "DBTableGridDataSurfaces.h"

#include "DBTableSurfIgeMapping.h"
#include "DBTableSurfLitoMapping.h"

#include "DBTableSurfacesOrder.h"
#include "DBTableSurfacesBlankOrder.h"
#include "DBTableSurfacesBlankFunctions.h"

#include "DBTablePCK2Fiz_Results.h"
#include "DBTablePCK2Fiz_Params.h"

#include "DBTablePtStZond.h"
#include "DBTableStZond.h"

#include "DBTablePtPalja.h"
#include "DBTablePalja.h"

#include <map>
using namespace std;
#include "../../laboratory/src/lab.h"
#include "../../laboratory/src/LabElement.h"

class LabNumber;
class LabLayer;
class BaseObject;

class CLabView
{
protected: // create from serialization only
	CLabView();

	bool otnosit_def_on_graph;


public:

	DBTableCilce0		m_DBTableCilce0;
	DBTableCilce		m_DBTableCilce;
	DBTableCompress		m_DBTableCompress;

	DBTableZriz0		m_DBTableZriz0;
	DBTableZriz			m_DBTableZriz;
	DBTableZriz_tbl		m_DBTableZriz_tbl;

	DBTableProp			m_DBTableProp;
	DBTableGranular		m_DBTableGranular;
	DBTableSoils		m_DBTableSoils;
	DBTableKT			m_DBTableKT;

	DBTableRozrizy		m_DBTableRozrizy;
	DBTableRozriz		m_DBTableRozriz;

	DBTableLito0		m_DBTableLito0;
	DBTableIGE0			m_DBTableIGE0;
	DBTableLito			m_DBTableLito;
	DBTableIGE			m_DBTableIGE;
	DBTableGrunty		m_DBTableGrunty;
	DBTableVoda			m_DBTableVoda;
	DBTableGenezis		m_DBTableGenezis;
	DBTableUmPoz		m_DBTableUmPoz;

	DBTableCubeSize			m_DBTableCubeSize;
	DBTableGridDataUsedAlg	m_DBTableGridDataUsedAlg;

	DBTableGridData			m_DBTableGridData;
	DBTableGridDataSurfaces m_DBTableGridDataSurfaces;

	DBTableSurfIgeMapping		m_DBTableSurfIgeMapping;
	DBTableSurfLitoMapping		m_DBTableSurfLitoMapping;

	DBTableSurfacesOrder		m_DBTableSurfacesOrder;
	DBTableSurfacesBlankOrder	m_DBTableSurfacesBlankOrder;
	DBTableSurfacesBlankFunctions	m_DBTableSurfacesBlankFunctions;

	DBTablePCK2Fiz_Params		m_DBTablePCK2Fiz_Params;
	DBTablePCK2Fiz_Results		m_DBTablePCK2Fiz_Results;

	DBTablePtStZond		m_DBTablePtStZond;
	DBTableStZond		m_DBTableStZond;


	DBTablePtPalja		m_DBTablePtPalja;
	DBTablePalja		m_DBTablePalja;

	vector<SoilDescription> vsd;
	LabElements m_lab_elements;
	LabLayer * m_lab_layer;

	virtual HWND GetWindow() = 0;
	virtual void DisconnectAllExcels() = 0;

// Attributes
public:
#if USE_GET_LAB_DOC
	CLabDoc * GetDocument();
#endif
// Implementation
public:
	virtual ~CLabView();
	CString m_ObjectNazva;
	long    m_ID_OBJ;
	virtual void UpdateObjectRelatedLists(int iItem) = 0;
	virtual void UpdateKTRelatedLists(int iItem) = 0;
	virtual void UpdateSoilRelatedLists(int iItem) = 0;

	virtual void UpdateObjectsListCtrl(CString where, CString order_by) = 0;
	virtual void UpdateProbGruntListCtrl(CString where, CString order_by) = 0;
	virtual void UpdateLitoListCtrl(CString where, CString order_by) = 0;
	virtual void UpdateKTListCtrl(CString where, CString order_by) = 0;
	virtual void UpdateIGEListCtrl(CString where, CString order_by) = 0;
	virtual void UpdateVodaListCtrl(CString where, CString order_by) = 0;
	virtual void UpdateTSZListCtrl(CString where, CString order_by) = 0;
	virtual void UpdatePaljaListCtrl(CString where, CString order_by) = 0;
	virtual void UpdateCompressListCtrl(CString where, CString order_by) = 0;
	virtual void UpdateCutListCtrl(CString where, CString order_by) = 0;
	virtual void UpdateFizMehListCtrl(CString where, CString order_by) = 0;
	virtual void UpdateGranularListCtrl(CString where, CString order_by) = 0;

	virtual void EnableObjectList(BOOL bEnable) = 0;

	virtual int GetObjectItem() = 0;
	virtual int GetKTItem() = 0;
	virtual int GetProbGrItem() = 0;

	virtual CLabDoc * GetLabDoc() = 0;
	virtual bool GetSetProbGrFilterStr(long ID_OBJ, CString & strFilter) = 0;

	LabNumber * CreateLabNumber(long lab_n, bool add_cut_from_db, int nCutItem, bool add_compress_from_db, int nCompItem, bool add_stat_zond_from_db);
	LabLayer * CreateLabLayer(bool add_cut_from_db, bool add_compress_from_db, bool add_stat_zond_from_db);

	void ProbgrPasportAllpossible();
	void ProbgrPasportCompress(int nCompItem, int compression_passport_type);
	void ProbgrPasportCut(int nCompItem, int cut_passport_type);
	void ProbgrPasportGranular(int granular_passport_type);
	void SoilPropertyWindow(int nSoilItem);

	// virtual void LabLayerPasport(int nItem) = 0;

	int GetCompressType(int nCompItem);


	void ProbgrSoilname(); 
	bool EditObject(const char * contract, const char * object_name); 
	void ProbgrClassification();
	
	//static bool context_with_plot;
	static tagPOINT property_window_pt;
	bool PropertyWindow(bool context_with_plot, HWND hWndParent, BaseObject * pOb);
	void ReCreatePropertyWindow(bool context_with_plot/*BaseObject * pOb*/);
	static HWND hPropertyWindow; 
	virtual void PrintfProperties(vector<fmtstr> & text){}// = 0;
	virtual void PrintfProperties(vector<LabData> & labdata){}// = 0;

protected:

};

#if USE_GET_LAB_DOC

#ifndef _DEBUG  // debug version in labView.cpp
inline CLabDoc* CLabView::GetDocument()
   { return (CLabDoc*)m_pDocument; }
#endif

#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LABVIEW_H__A2E8DFE3_FC2E_48AA_8C39_20E359BC4D31__INCLUDED_)
