// PolyotyNnetDlg.h: interface for the PolyotyNnetDlg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POLYOTYNNETDLG_H__DE99B0CB_C734_4929_BA45_8ED0234DF8C7__INCLUDED_)
#define AFX_POLYOTYNNETDLG_H__DE99B0CB_C734_4929_BA45_8ED0234DF8C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../../kohonen/src/kohonendlg.h"
#include "../../array/src/sorting.h"
#include "./generic.h"


class PolyotyNnetDlg  
{
	POLYOTYFILEDLGDATA		* m_lpPolyotyDlgData;
	vector<vector<double> >	* pvectors, 
									* pdrills;
	vector<cut_of_line>		* pline_cutting_vector_sorted;
	vector<string>			* pnames;
	int ix,iy;
	int n_profiles;
	KohonenDlg				* khd;
	HWND					hDlg;
public:
	int m_extremums_filter_type;
	void OnButtonKohonen4();
	void OnButtonKohonen3();
	void OnDestroy();
	void OnButtonOK();
	void OnButtonProfileSumming(WPARAM wParam, LPARAM lParam);
	void Test();
	void OnButtonKohonen(int type = 0);
	void OnButtonKohonen2(int type = 0);
	void SortProfiles();
	void OnButtonVisualProfiles(WPARAM wParam, LPARAM lParam);
	void OnButtonVisualAllProfiles(WPARAM wParam, LPARAM lParam);
	void OnButtonMovingAverange(WPARAM wParam, LPARAM lParam);
	void OnInitDialog();
	PolyotyNnetDlg(LPPOLYOTYFILEDLGDATA lpPolyotyDlgData);
	virtual ~PolyotyNnetDlg();
	friend LRESULT CALLBACK DlgProcPolyotyForNnet( HWND hDlg, UINT uMsg,
								  WPARAM wParam, LPARAM lParam );
};

#endif // !defined(AFX_POLYOTYNNETDLG_H__DE99B0CB_C734_4929_BA45_8ED0234DF8C7__INCLUDED_)
