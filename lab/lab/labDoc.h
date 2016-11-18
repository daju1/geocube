// labDoc.h : interface of the CLabDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LABDOC_H__44F01642_11FC_42A9_B768_4C364943A433__INCLUDED_)
#define AFX_LABDOC_H__44F01642_11FC_42A9_B768_4C364943A433__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <map>
#include <vector>
using namespace std;


#define table_key_Objects		1
#define table_key_KT			2
#define table_key_ProbGr		3
#define table_key_Granular		4
#define table_key_FizMeh		5
#define table_key_Zriz			6
#define table_key_Compress		7
#define table_key_TSZ			8
#define table_key_Palja			9
#define table_key_IGE			10
#define table_key_Litho			11
#define table_key_Voda			12

#define table_key_Genezis		13
#define table_key_GranSklad		14
#define table_key_GrMain		15
#define table_key_Grunty		16
#define table_key_PodTypyGr		17


class CLabView;
class CLabDoc;
class CMyList;
class CMyListCtrl;
struct ATable
{
	friend class CMyListCtrl;
	friend class CMyList;
	CString m_table_name;

	CLabDoc * m_lab_doc;
	CRecordset* m_pRecordset;
	int m_nFields;
 	int m_nRowCount;
	ATable(CLabDoc * lab_doc, const char * table_name);
	~ATable();
	void Open_Recordset(CMyListCtrl * my_list_ctrl, CString where, CString order_by);
	
protected:

};


#if INCLUDE_3D
#include "../../wintools/src/utility.h"
#include "../../wintools/src/win32_app.h"
#include "../../wintools/src/win32_project.h"
#endif

#include "../../geocube_module/geocube_module.h"


#define USE_GET_LAB_DOC 0

class CDlgProbGrunt;
struct CubeSize;
struct surface_blank_order_list_item;
#include <lab_numbers_reset_items.h>

class CLabDoc : public CDocument
{
	friend class CLabView;
private:
	virtual bool OpenOdbc(const char * connect_str, bool to_rewrite_list) = 0;
public:

	static CString s_strConnect;
	static CString s_strDatabase;
	static CString s_strWorkDir;
	static CString s_strDBPassword;
	static CString s_strExportDatabaseTemplate;
	static CString GetWorkDir(bool write_registry = false);
	//void GetQuery();
	//void PutQuery();
	virtual void EnumTables(bool to_rewrite_list) = 0;
	virtual void OnDisconnect() = 0;
	
	void FirstOdbcConnect();

	virtual bool AddNewObject(const char * contract, const char * object_name);
	virtual bool AddNewProbGrunt(CDlgProbGrunt * dlg, long ID_OBJ);
	virtual bool EditProbGrunt(CDlgProbGrunt * dlg, long ID_OBJ);

	bool ClearGridData(long ID_OBJ);
	bool ClearGridData(long ID_OBJ, long ID_SURF);
	bool ClearGridDataPoint(long ID_OBJ, long ID_SURF, long ID_POINT);
	bool ReNameGridDataSurface(long ID_OBJ, long ID_SURF, CString NAZVA);
	bool AddGridDataSurface(long ID_OBJ, long ID_SURF, CString	NAZVA, BYTE PODOSHVA, COLORREF rgb, long ID_UMPOZ);
	bool AddGridData(long ID_OBJ, long ID_SURF, long ID_POINT, double X, double Y, double Z);
	bool EditGridData(long ID_OBJ, long ID_SURF, long ID_POINT, double X, double Y, double Z);
	void ProbgrIGEautoFill(bool to_msg_box, long ID_OBJ, long ID_KT);

	long AddKT(long ID_OBJ, long ID_TYP, const char * nazva, double X, double Y, double Z);
	bool ClearLito(bool bUnEdited, long ID_OBJ, long ID_KT);
	bool EditLito(bool bUnEdited, long ID_OBJ, long ID_KT, CString IGE, double H0, double H1);
	bool AddLito(bool bUnEdited, long ID_OBJ, long ID_KT, CString IGE, double H0, double H1);
	bool EditLito(long ID_OBJ, long ID_KT, double key_H0, double H0, double H1, bool edit_H0, bool edit_H1);

	void AddSurfIgeMappingItem(long ID_OBJ, long ID_SURF, long ID_IGE);
	void AddSurfLitoMappingItem(long ID_OBJ, long ID_SURF, long ID_IGE);
	bool ClearSurfIgeMappingItem(long ID_OBJ, long ID_SURF);
	bool ClearSurfLitoMappingItem(long ID_OBJ, long ID_SURF);

	bool ClearSurfIgeMapping(long ID_OBJ);
	bool ClearSurfLitoMapping(long ID_OBJ);

	bool ClearSurfacesOrder(long ID_OBJ);
	bool ClearSurfacesBlankOrder(long ID_OBJ);
	bool ClearSurfacesOrderItem(long ID_OBJ, long ID_SURF);
	bool ClearSurfacesBlankOrderItem(long ID_OBJ, long ID_SURF);
	bool AddSurfacesOrderItem(long ID_OBJ, long NPP, BYTE check, long ID_SURF, BYTE podoshva, BYTE check2);
	bool AddSurfacesBlankOrderItem(long ID_OBJ, long NPP, long ID_SURF, BYTE podoshva, surface_blank_order_list_item * soli);
	bool DeleteSurfacesBlankFunctionsItem(long ID_OBJ, long ID_SURF_OBJ, long ID_SURF_PARAM, BYTE id_blank_fun);

	bool SurfaceOrderList_UpdateChecking(long ID_OBJ, long ID_SURF, BYTE check);
	bool SurfaceBlankOrderList_UpdateChecking(long ID_OBJ, long ID_SURF, surface_blank_order_list_item *);
	

	bool AddSurfacesBlankFunctionsItem(long ID_OBJ, long ID_SURF_OBJ, long ID_SURF_PARAM, BYTE id_blank_fun);
	void SurfaceBlankFunctionsList_SwapItemSurfaces(long ID_OBJ, long ID_SURF_OBJ, long ID_SURF_PARAM, BYTE id_blank_fun);
	void SurfaceBlankFunctionsList_SwapItemMethod(long ID_OBJ, long ID_SURF_OBJ, long ID_SURF_PARAM, BYTE id_blank_fun);

	bool SurfaceOrderList_MoveItemUp(long ID_OBJ, long NPP);
	bool SurfaceBlankOrderList_MoveItemUp(long ID_OBJ, long NPP);

	bool SurfaceOrderList_MoveItemDown(long ID_OBJ, long NPP);
	bool SurfaceBlankOrderList_MoveItemDown(long ID_OBJ, long NPP);

	bool DefineZoom(long ID_OBJ, double zoomCoefXYZ, double zoomCoefXY);
	bool UnDefineCubeSize(long ID_OBJ);
	bool DefineCubeSize(long ID_OBJ, const CubeSize & cube_size);
	bool DefineGridDataUsedAlgorothm(long ID_OBJ, long ID_SURF, BYTE /*USE_SURFER*/ DRIDDATA_APP, long ID_ALG);
	bool DefineGridDataZflag(long ID_OBJ, long ID_SURF, short zflag);

	
	bool ClearGridDataUsedAlgorothms(long ID_OBJ);
	bool ClearGridDataUsedAlgorothm(long ID_OBJ, long ID_SURF);

	void LabNumberResetting(vector<lab_numbers_reset_item> lab_numbers_reset_items);

	long AddNewRozriz(long ID_OBJ, CString NOMER, CString fn_dxf, 
		bool m_acad_yscale_loaded,
		double z1w, double y1a, double z2w, double y2a,
		bool dxf_x_defined, vector<double> * v_xProfile, 
		vector<long> v_ID_KT);
	void DeleteRozriz(long ID_OBJ, long ID_ROZRIZ);

	void GridDataSurfacesSetPodoshva(long ID_OBJ, long ID_SURF, BYTE podoshva);


	CDatabase m_database;
	

#if INCLUDE_3D
	win_app * app;
	singleton_cleaner<win_app> app_cleaner;
	win_project * w_project;
#endif

	dll_win_project * dll_w_project;



	map<long, ATable *> m_tables;


	CString m_strDatabaseName;
	CString m_strConnect;
	CString m_strQuery;
	BOOL m_bConnected;


protected: // create from serialization only
	CLabDoc();
#if USE_GET_LAB_DOC
	DECLARE_DYNCREATE(CLabDoc)
#endif

// Attributes
public:
//	CStringArray m_dao_arrayFieldName;
//	CWordArray m_dao_arrayFieldSize;
//	int m_dao_nFields;
// 	int m_dao_nRowCount;
//	BOOL m_dao_bConnected;
//	enum {UNK, MDB, ISAM, ODBC} m_dao_nDatabaseType;

	void ImportObject();

//	void OnFileDaoOpenMdb();
//	void OnFileDaoOpenOdbc();

// Operations
public:
	//void daoGetQuery();
	//void daoPutQuery();
	//void daoGetFieldSpecs();
	//void daoOpenRecordset();
private:
	//void DaoOpenMdb();
	void DaoOpenOdbc();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLabDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLabDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLabDoc)
	afx_msg void OnFileOdbcConnect();
	afx_msg void OnUpdateFileOdbcConnect(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileOdbcDisconnect(CCmdUI* pCmdUI);
	afx_msg void OnFileOdbcDisconnect();
	afx_msg void OnUpdateFile3d(CCmdUI* pCmdUI);
	afx_msg void OnUpdateObjectsInsertto3d(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CLabDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LABDOC_H__44F01642_11FC_42A9_B768_4C364943A433__INCLUDED_)
