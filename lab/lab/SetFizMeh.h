#if !defined(AFX_SETFIZMEH_H__52462CE2_C5F5_4D5F_A92B_2917FA152236__INCLUDED_)
#define AFX_SETFIZMEH_H__52462CE2_C5F5_4D5F_A92B_2917FA152236__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetFizMeh.h : header file
//
class MyExcel;
/////////////////////////////////////////////////////////////////////////////
// SetFizMeh recordset

#define FILL_VAL_FROM_DB 1

class SetFizMeh : public CRecordset
{
public:
	SetFizMeh(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetFizMeh)

// Field/Param Data
	//{{AFX_FIELD(SetFizMeh, CRecordset)
	long	m_ID_OBJ;
	long	m_ID_KT;
	long	m_ID_PROB;
	long	m_ID_VYPROB;
	long	m_ID_PARAM;
	double	m_VAL;
	BYTE	m_bSTAT;
	//}}AFX_FIELD

	void AddNewRow(long ID_OBJ, long ID_KT, long ID_PROB, long ID_VYPROB, long ID_PARAM, double val);
	int GetMeanParam(long ID_OBJ, long ID_KT, long ID_PROB, long ID_PARAM, double &val_from_db, double &mean_of_vyprob);
	int GetParam(long ID_OBJ, long ID_KT, long ID_PROB, long ID_PARAM, long ID_VYPROB, double &val);
	int ReplaceParam(long ID_OBJ, long ID_KT, long ID_PROB, long LAB_N, 
							long ID_PARAM, long ID_VYPROB, 
							double val);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetFizMeh)
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
long GetFizMehVyprobForCut(CDatabase* database, long ID_OBJ, long ID_KT, long ID_PROB, long id_cut_vyprob, long id_kolca);
long GetFizMehVyprobForCompress(CDatabase* database, long ID_OBJ, long ID_KT, long ID_PROB, long id_compress_vyprob, long id_kolca);
const char * GetPhysicalVyprobString(CDatabase* database, long ID_OBJ, long ID_KT, long ID_PROB, long id_phys_vyprob);
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETFIZMEH_H__52462CE2_C5F5_4D5F_A92B_2917FA152236__INCLUDED_)
