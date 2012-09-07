#if !defined(AFX_COMPRESSLISTLAB_H__C250FF85_3406_451C_9DF3_37C162FB41FB__INCLUDED_)
#define AFX_COMPRESSLISTLAB_H__C250FF85_3406_451C_9DF3_37C162FB41FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GranularList.h : header file
//
#include "LabListCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CompressListLab window

class CompressListLab : public CLabListCtrl
{
// Construction
public:
	CompressListLab();

// Attributes
public:
	void FillCtrlList(CRecordset * pRecordset);
	void DrawDataRow(CRecordset * pRecordset);
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CompressListLab)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CompressListLab();

	// Generated message map functions
protected:
	//{{AFX_MSG(CompressListLab)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMPRESSLISTLAB_H__C250FF85_3406_451C_9DF3_37C162FB41FB__INCLUDED_)
