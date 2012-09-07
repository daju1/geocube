#if !defined(AFX_DLGSENDMAIL_H__8F443B6D_FD66_4961_9216_125F563B1A51__INCLUDED_)
#define AFX_DLGSENDMAIL_H__8F443B6D_FD66_4961_9216_125F563B1A51__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSendMail.h : header file
//
#include "smtp.h"
#include "MyListCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// DlgSendMail dialog
class CMailwriterView;
class DlgSendMail : public CDialog
{
// Construction
public:
	DlgSendMail(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgSendMail)
	enum { IDD = IDD_DIALOG_SEND_MAIL };
	CMyListCtrl	m_list_view_of_recipients;
	CStatic	m_static_password;
	CStatic	m_static_login;
	CButton	m_button_check_authentication;
	CEdit	m_edit_password;
	CEdit	m_edit_login;
	CListBox	m_list_of_recipients;
	CListBox	m_list_of_attaches;
	CString	m_edit_from;
	CString	m_edit_smtp_server;
	BOOL	m_check_authentication;
	CString	m_edit_excel_colomn;
	CString	m_edit_subject;
	//}}AFX_DATA

	//Create the SMTP connection
	CSMTPConnection smtp;

	BOOL Connecting();
	//void FillingMessage(CSMTPMessage & m, LPCTSTR szFriendlyFrom, LPCTSTR szFrom,  LPCTSTR szFriendlyTo,  LPCTSTR szTo);
	void FillingMessage(CSMTPMessage & m, LPCTSTR szFriendlyFrom, LPCTSTR szFrom, bool to_add_all_recipients);
	void AddingBody(CSMTPMessage & m);
	void Attaching(CSMTPMessage & m);

	BOOL Sending(CSMTPMessage & m);
	CMailwriterView * m_pView;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgSendMail)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgSendMail)
	afx_msg void OnButtonAddFile();
	afx_msg void OnButtonLoadAdresses();
	afx_msg void OnButtonSend();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonDeleteRecipient();
	afx_msg void OnButtonDeleteFile();
	afx_msg void OnButtonSend2();
	afx_msg void OnButtonSend3();
	afx_msg void OnCheckRequireAuthentication();
	afx_msg void OnButtonLoadAdressesTxt();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSENDMAIL_H__8F443B6D_FD66_4961_9216_125F563B1A51__INCLUDED_)
