#if !defined(AFX_DLGLABELEMENTS_H__E5230058_FB09_4922_8108_22F914A3183E__INCLUDED_)
#define AFX_DLGLABELEMENTS_H__E5230058_FB09_4922_8108_22F914A3183E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLabElements.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLabElements dialog
#include "LabElementsList.h"
#include "LabElementList.h"

class LabElements;
class CLabView;

#include "../../laboratory/src/Lab.h"
#include "../../laboratory/src/LabElement.h"

struct PckKorrelationItem
{
	double m_pck;
	trial_value m_tv;
	LabNumber * m_lab_number;

	PckKorrelationItem(double pck, double val, LabNumber * lab_number)
	{
		this->m_pck = pck;
		this->m_tv = val;
		this->m_lab_number = lab_number;
	}
};

class PckKorrelationObject : public BaseObject
{
public:
	int work_mode;
	SoilDescriptionPtr::compare_mode m_cm;

	void SetSizeAndPosOfContextWindow(HWND hWnd, int CX, int CY);
	virtual void PrintfProperties(vector<fmtstr> & text);
	virtual void PrintfProperties(vector<LabData> & labdata);

	vector<PckKorrelationItem> v_pck_val;

	vector<PckKorrelationItem> v_pck_E;
	vector<PckKorrelationItem> v_pck_C;
	vector<PckKorrelationItem> v_pck_Fi;
	vector<PckKorrelationItem> v_pck_tgFi;
	void clear()
	{
		v_pck_E.clear();
		v_pck_C.clear();
		v_pck_Fi.clear();
		v_pck_tgFi.clear();

		v_pck_val.clear();
	}
	bool MinSqLinearStat(LabTrialValueType & vt, vector<x_compression> & x, vector<trial_got_value> & y, bool donot_shift, trial_value & a0, trial_value & a1, int & m, trial_value & Sy, MinSqLinearStatParameters & param);
	void Correlation(vector<fmtstr> *& text, vector<LabData> * labdata, const char * title, vector<PckKorrelationItem> & vpckkorr);

};

class CDlgLabElements : public CDialog
{
	LabElements * m_lab_elements;
	CLabView   * m_pLabView;
// Construction
public:
	CDlgLabElements(CLabView * pLabView, LabElements * lab_elements, CWnd* pParent = NULL);   // standard constructor
	PckKorrelationObject my_object;

// Dialog Data
	//{{AFX_DATA(CDlgLabElements)
	enum { IDD = IDD_DIALOG_LAB_ELEMENTS };
	CComboBox	m_combo_soil_description_sort_mode;
	CLabElementsList m_list_lab_elements;
	CLabElementList m_list_lab_element;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLabElements)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLabElements)
	virtual BOOL OnInitDialog();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnButtonDivideLabElementBySvyaznost();
	afx_msg void OnButtonDivideLabElement();
	afx_msg void OnButtonPrepareDivideLabElement();
	afx_msg void OnButtonSortLabElement();
	afx_msg void OnButtonPrepareDivideLabElementAll();
	afx_msg void OnButtonPckKorrelation1();
	afx_msg void OnButtonPckKorrelation2();
	afx_msg void OnEndlabeleditListLabElements(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLABELEMENTS_H__E5230058_FB09_4922_8108_22F914A3183E__INCLUDED_)
