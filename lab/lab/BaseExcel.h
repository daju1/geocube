// BaseExcel.h: interface for the BaseExcel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASEEXCEL_H__F0B1F280_9C94_47F7_9F2B_61695B326A87__INCLUDED_)
#define AFX_BASEEXCEL_H__F0B1F280_9C94_47F7_9F2B_61695B326A87__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../../excel_connect/src/myexcel.h"
#include <string>
using namespace std;


#define AUTO_NEW_PAGE_ON_ARCHIVES_WHEN_SAVE 0


class CLabDoc;
class CLabView;
class BaseExcel  
{
	bool was_new_form_loaded;
	bool can_save_to_db;
protected:
	virtual void InitExt() = 0;
	virtual bool virFill(){return false;}
	virtual bool virCompute(bool) = 0;
	virtual void virSaveToDB(){}
	string ext;
	string xl_filter_name;
	string xl_form;
	string xl_forms_dir;

	string xl_file;

	CLabView * m_lab_view;
	CLabDoc * m_lab_doc;
	CDatabase * p_database;

	bool use_compute_for_save;



public:
	static string s_xl_forms_dir;
	static bool to_disconnect_exels_when_load_form;
	static bool to_automatic_save_when_disconnect;

	bool save_different_vyprob;

	MyExcel m_excel;
	BaseExcel();
	virtual ~BaseExcel();
	CString LoadFormNew(const char * dir, const char * fn);
	CString LoadFormNew(const char * initial_fn = "");
	void UpdateLoadFormNew(CCmdUI* pCmdUI);
	void LoadFormExisting(const char * fn = NULL);
	void UpdateLoadFormExisting(CCmdUI* pCmdUI);
	void Fill();
	void UpdateFill(CCmdUI* pCmdUI, bool may_fill_only_new_form);
	void Compute();
	void UpdateCompute(CCmdUI* pCmdUI);
	void SaveToDB();
	void UpdateSaveToDB(CCmdUI* pCmdUI);
	void DisconnectExcel();
	void UpdateDisconnectExcel(CCmdUI* pCmdUI);

	virtual void Init(CLabView * view, CLabDoc * doc, CDatabase * database);
};

#endif // !defined(AFX_BASEEXCEL_H__F0B1F280_9C94_47F7_9F2B_61695B326A87__INCLUDED_)
