#if !defined(AFX_SETGRANULAR_H__E20C45A3_0E3B_4200_B0E9_1B72897DD2AA__INCLUDED_)
#define AFX_SETGRANULAR_H__E20C45A3_0E3B_4200_B0E9_1B72897DD2AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetGranular.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// SetGranular recordset

#include <float.h>
#include "../../laboratory/src/prop_value.h"

class SetGranular : public CRecordset
{
public:
	SetGranular(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetGranular)

// Field/Param Data
	//{{AFX_FIELD(SetGranular, CRecordset)
	long	m_ID_OBJ;
	long	m_ID_KT;
	long	m_ID_PROB;
	long	m_ID_GRAN;
	double	m_VAL;
	//}}AFX_FIELD

	void AddNewRow(long ID_OBJ, long ID_KT, long ID_PROB, long ID_GRAN, double val);
	int ReplaceGranContent(long ID_OBJ, long ID_KT, long ID_PROB, long LAB_N, 
		GranVyprob & gran_vyprob);

	int GetGran(long ID_OBJ, long ID_KT, long ID_PROB, long ID_GRAN,
		double &val);

	int ReplaceGran(long ID_OBJ, long ID_KT, long ID_PROB, long LAB_N, 
		long ID_GRAN, 
		double val);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetGranular)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETGRANULAR_H__E20C45A3_0E3B_4200_B0E9_1B72897DD2AA__INCLUDED_)
