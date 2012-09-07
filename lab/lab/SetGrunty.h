#if !defined(AFX_SETGRUNTY_H__544735DD_25CF_4091_8881_F32DFB83D7AC__INCLUDED_)
#define AFX_SETGRUNTY_H__544735DD_25CF_4091_8881_F32DFB83D7AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetGrunty.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetGrunty recordset

class SetGrunty : public CRecordset
{
public:
	SetGrunty(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SetGrunty)

// Field/Param Data
	//{{AFX_FIELD(SetGrunty, CRecordset)
	long	m_ID_OBJ;
	long	m_ID_GR;
	CString	m_NAZVA_U;
	CString	m_NAZVA_R;
	long	m_TYPGR;
	long	m_TYPGR_PCK;
	long	m_ID_NORMATYV;
	long	m_ID_GRCONS;
	long	m_ID_UKLAD;
	long	m_ID_NJU;
	long	m_ID_GRMAIN;
	long	m_ID_UMPOZ;
	long	m_ID_GENEZIS;
	//}}AFX_FIELD

	void AddNewRow(long ID_OBJ, long ID_GR, CString NAZVA_U, CString NAZVA_R, long TYPGR, long TYPGR_PCK, long ID_NORMATYV, long ID_GRCONS, long ID_UKLAD, long ID_NJU, long ID_GRMAIN, long ID_UMPOZ, long ID_GENEZIS);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetGrunty)
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

#endif // !defined(AFX_SETGRUNTY_H__544735DD_25CF_4091_8881_F32DFB83D7AC__INCLUDED_)
