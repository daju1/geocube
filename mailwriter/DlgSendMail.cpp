// DlgSendMail.cpp : implementation file
//

#include "stdafx.h"
#include "mailwriter.h"
#include "mailwriterDoc.h"
#include "mailwriterView.h"
#include "DlgSendMail.h"

/*void WriteRaporto(LPCTSTR s)
{
	FILE *stream;

	if ((stream = fopen("raporto.log","at")) == NULL)
	{
//		AfxMessageBox("Cannot open file for write.\n");
		return;
	}
	fprintf(stream, s);

	fclose(stream);
}*/
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgSendMail dialog


DlgSendMail::DlgSendMail(CWnd* pParent /*=NULL*/)
	: CDialog(DlgSendMail::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgSendMail)
	m_edit_from = _T("");
	m_edit_smtp_server = _T("mail.ru");
	m_check_authentication = TRUE;
	m_edit_excel_colomn = _T("A");
	m_edit_subject = _T("");
	//}}AFX_DATA_INIT

	m_pView = NULL;
}


void DlgSendMail::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgSendMail)
	DDX_Control(pDX, IDC_LIST_VIEW_OF_RECIPIENTS, m_list_view_of_recipients);
	DDX_Control(pDX, IDC_STATIC_PASSWORD, m_static_password);
	DDX_Control(pDX, IDC_STATIC_LOGIN, m_static_login);
	DDX_Control(pDX, IDC_CHECK_REQUIRE_AUTHENTICATION, m_button_check_authentication);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_edit_password);
	DDX_Control(pDX, IDC_EDIT_LOGIN, m_edit_login);
	DDX_Control(pDX, IDC_LIST_OF_RECIPIENTS, m_list_of_recipients);
	DDX_Control(pDX, IDC_LIST_OF_ATTACHES, m_list_of_attaches);
	DDX_Text(pDX, IDC_EDIT_FROM, m_edit_from);
	DDX_Text(pDX, IDC_EDIT_SMTP_SERVER, m_edit_smtp_server);
	DDX_Check(pDX, IDC_CHECK_REQUIRE_AUTHENTICATION, m_check_authentication);
	DDX_Text(pDX, IDC_EDIT_EXCEL_COLOMN, m_edit_excel_colomn);
	DDX_Text(pDX, IDC_EDIT_SUBJECT, m_edit_subject);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgSendMail, CDialog)
	//{{AFX_MSG_MAP(DlgSendMail)
	ON_BN_CLICKED(IDC_BUTTON_ADD_FILE, OnButtonAddFile)
	ON_BN_CLICKED(IDC_BUTTON_LOAD_ADRESSES, OnButtonLoadAdresses)
	ON_BN_CLICKED(IDC_BUTTON_SEND, OnButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_RECIPIENT, OnButtonDeleteRecipient)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_FILE, OnButtonDeleteFile)
	ON_BN_CLICKED(IDC_BUTTON_SEND2, OnButtonSend2)
	ON_BN_CLICKED(IDC_BUTTON_SEND3, OnButtonSend3)
	ON_BN_CLICKED(IDC_CHECK_REQUIRE_AUTHENTICATION, OnCheckRequireAuthentication)
	ON_BN_CLICKED(IDC_BUTTON_LOAD_ADRESSES_TXT, OnButtonLoadAdressesTxt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgSendMail message handlers

BOOL DlgSendMail::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	///////

	this->m_list_view_of_recipients.OnInitCtrl();
	this->m_list_view_of_recipients.FillCtrlList();

	this->UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void DlgSendMail::OnButtonAddFile() 
{
	// TODO: Add your control notification handler code here

	CFileDialog dlg(TRUE);
	if (dlg.DoModal() == IDOK)
	{		
		this->m_list_of_attaches.AddString(dlg.GetPathName());
	}
	
}

void DlgSendMail::OnButtonDeleteFile() 
{
	int count = this->m_list_of_attaches.GetCount();

	for (int i = count - 1; i >= 0; i--)
	{
		if (this->m_list_of_attaches.GetSel(i) > 0)
		{
			this->m_list_of_attaches.DeleteString(i);

		}
	}
	
}
void DeleteEndZeros(char * str)
{
	if (strchr(str, '.'))
	{
		while (str[strlen(str)-1] == '0')
			str[strlen(str)-1] = '\0';
		if (str[strlen(str)-1] == '.')
			str[strlen(str)-1] = '\0';
	}
}
void DeleteEndZeros(CString & str)
{
	DeleteEndZeros(str.GetBuffer(str.GetLength()));
}
#include "./../excel_connect/src/myexcel.h"

bool ExcelRange_GetStringValue(MyExcel & m_excel, const char * S, CString & str)
{
	LPDISPATCH pRange; 
	Range10    m_range;

	VARIANT var_val;
	try
	{
		VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
		m_range.AttachDispatch(pRange);	
		var_val = m_range.GetValue();
		m_range.ReleaseDispatch();	
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();

		return false;
	}



	bool result = false;
	if (var_val.vt == VT_R8)
	{
		double val = var_val.dblVal;
		str.Format("%f", val);
		DeleteEndZeros(str);
		result = true;
	}			
	else if (var_val.vt == VT_BSTR)
	{
		str = var_val.bstrVal;
		result = true;
	}

	return result;
}

void DlgSendMail::OnButtonLoadAdressesTxt() 
{
	CFileDialog dlg(TRUE, ".txt", "*.txt");
	if (dlg.DoModal() == IDCANCEL) return;
	CString fn = dlg.GetPathName();

	FILE *stream;
	const unsigned int n = 1023;
	char szBuff[n];

	if ((stream = fopen(fn, "rt")) == NULL)
	{
		MessageBox("Cannot open input file.\n", "Import", 
			MB_OK | MB_ICONINFORMATION);
		return;
	}
	while (!feof(stream))
	{
		char * ch;
		ch = fgets(szBuff,n,stream);
		if( ch != NULL && strlen(szBuff) > 1)
		{
			char * p = strrchr(szBuff,'\n');
			if (p) *p = '\0';

			p = strrchr(szBuff,'\r');
			if (p) *p = '\0';

			p = strrchr(szBuff,'\t');
			if (p) *p = '\0';

			this->m_list_of_recipients.AddString(szBuff);
			this->m_list_view_of_recipients.AddRow("", szBuff);
		}
	}
	fclose(stream);	
}
void DlgSendMail::OnButtonLoadAdresses() 
{
	CFileDialog dlg(TRUE, ".xls", "*.xls");
	if (dlg.DoModal() == IDCANCEL) return;
	CString fn_xls = dlg.GetPathName();

	MyExcel m_excel;
	m_excel.ExcelOleLoad();
	if (m_excel.IsApplicationDispatch())
	{
		try
		{
			m_excel.ExcelOleExecute(fn_xls);

			int r = 1;

			char S[64];
			while (true)
			{
				CString str;
				sprintf(S, "%s%d", this->m_edit_excel_colomn, r++);
				if (!ExcelRange_GetStringValue(m_excel, S, str))
				{
					if (r > 2)
						break;
				}
				this->m_list_of_recipients.AddString(str);
			}
			//m_excel.m_workbook.Save();
			m_excel.m_workbook.Close();
			if (!m_excel.got_active_object)
				m_excel.m_app.Quit();
		}

		catch (CException* pe)
		{
			// catch errors from WinINet 
			TCHAR szErr[4098]; 
			pe->GetErrorMessage(szErr, 4098); 
			AfxMessageBox(szErr);
			pe->Delete();

			printf("catched\n");
			m_excel.ExcelOleRelease();
		}
		m_excel.ExcelOleRelease();
	}
	else
		printf("!!!!! m_excel.IsApplicationDispatch()\n");
}


void DlgSendMail::OnButtonDeleteRecipient() 
{
	int count = this->m_list_of_recipients.GetCount();

	for (int i = count - 1; i >= 0; i--)
	{
		if (this->m_list_of_recipients.GetSel(i) > 0)
		{
			this->m_list_of_recipients.DeleteString(i);

		}
	}	
}


BOOL DlgSendMail::Connecting()
{
	//Connect to the server
	CString server = "smtp." + this->m_edit_smtp_server;
	if (!smtp.Connect(_T(server)))
	{
		DWORD dwError = ::GetLastError();
		CString sResponse = smtp.GetLastCommandResponse();
		TRACE(_T("Failed to connect to SMTP server\n"));
		TRACE(sResponse);
		return FALSE;
	}

	if (this->m_check_authentication)
	{
		CString login = "";
		CString password = "";

		this->m_edit_login.GetWindowText(login);
		this->m_edit_password.GetWindowText(password);

		if (!smtp.Autorization(_T(login),  _T(password)))
		{
			DWORD dwError = ::GetLastError();
			CString sResponse = smtp.GetLastCommandResponse();
			TRACE(_T("Failed to connect to SMTP server\n"));
			TRACE(sResponse);
			return FALSE;
		}
	}
	return TRUE;
}
void DlgSendMail::AddingBody(CSMTPMessage & m)
{
WriteRaporto("DlgSendMail::AddingBody() 1\n");
	if (this->m_pView)
	{
		int txt_len = this->m_pView->GetWindowTextLength()+1;
		char * text = new char[txt_len];
		this->m_pView->GetWindowText(text, txt_len);
		m.AddBody(_T(text));
	}
	else
		AfxMessageBox("!this->m_pView\nBody not Added");
WriteRaporto("DlgSendMail::AddingBody() end\n");
}
void DlgSendMail::Attaching(CSMTPMessage & m)
{
WriteRaporto("DlgSendMail::Attaching() 1\n");
	//Testing Reply To support
	//m.m_ReplyTo = CSMTPAddress(_T("Another PJ"), _T("pj.naughter@softech-telecom.com"));

	int count = this->m_list_of_attaches.GetCount();

	//for (int i = count - 1; i >= 0; i--)
	for (int i = 0; i < count; i++)
	{
		CString str;
		this->m_list_of_attaches.GetText(i, str);

		//Testing attachment support
		CSMTPAttachment * attachment = new CSMTPAttachment;
		if (attachment)
		{
			attachment->Attach(_T(str));
			m.AddAttachment(attachment);
		}
	}
WriteRaporto("DlgSendMail::Attaching() end\n");
}
/*void DlgSendMail::FillingMessage(CSMTPMessage & m, LPCTSTR szFriendlyFrom, LPCTSTR szFrom,  LPCTSTR szFriendlyTo,  LPCTSTR szTo)
{
WriteRaporto("DlgSendMail::FillMessage() 1\n");
	//Create a test message
	CSMTPAddress From(_T(szFriendlyFrom), _T(szFrom));	 //Change these values to your settings
	m.m_From = From;

	CSMTPAddress To(_T(szFriendlyTo), _T(szTo)); //Change these values to your settings
	m.AddRecipient(To);

	m.m_sSubject = _T(this->m_edit_subject);
	this->AddingBody(m);
	this->Attaching(m);
WriteRaporto("DlgSendMail::FillMessage() end\n");
}*/

void DlgSendMail::FillingMessage(CSMTPMessage & m, LPCTSTR szFriendlyFrom, LPCTSTR szFrom, bool to_add_all_recipients)
{
WriteRaporto("DlgSendMail::FillMessage(CSMTPMessage & m, LPCTSTR szFrom) 1\n");
	//Create a test message
	CSMTPAddress From(_T(szFriendlyFrom), _T(szFrom));	 //Change these values to your settings
	m.m_From = From;

	if (to_add_all_recipients)
	{
		int count = this->m_list_of_recipients.GetCount();
		for (int i = 0; i < count; i++)
		{
			CString str;
			this->m_list_of_recipients.GetText(i, str);

			CSMTPAddress To(_T(""), _T(str)); //Change these values to your settings
			m.AddRecipient(To);
		}
	}

	m.m_sSubject = _T(this->m_edit_subject);
	this->AddingBody(m);
	this->Attaching(m);
WriteRaporto("DlgSendMail::FillMessage(CSMTPMessage & m, LPCTSTR szFrom) end\n");
}

BOOL DlgSendMail::Sending(CSMTPMessage & m)
{	
WriteRaporto("DlgSendMail::Sending(CSMTPMessage & m) 1\n");
	//Sent the message
	if (!smtp.SendMessage(m))
	{
		DWORD dwError = ::GetLastError();
		CString sResponse = smtp.GetLastCommandResponse();
		TRACE(_T("Failed to send the SMTP message\n"));
		TRACE(_T(sResponse));
	/*
	//sResponse
	"503 Administrative prohibition -- authorization required.  Users in your domain are not allowed to send email without authorization.  See http://www.mail.ru/pages/help/261.html for details."
	
	SMTP-авторизация 

При отправке писем через наши серверы из почтовых программ, 
в которых предусмотрена возможность авторизации пользователя 
при отправке письма (поддержка расширения SMTP, описанного в RFC2554), 
нужно производить дополнительные настройки: в настройках 
почтовой программы необходимо указать то, что сервер исходящей 
почты (или сервер SMTP) требует авторизации.  
Некоторые почтовые программы (например, Microsoft 
Mail для Microsoft Outlook версии ниже 2000) не имеют возможности 
производить аутентификацию через SMTP сервер. Поэтому для отправки 
письма Вам необходимо произвести авторизацию на сервере через POP3 
сервер, то есть сначала забрать письма с сервера, затем отправить 
написанные письма.

При отправке писем через наш SMTP-сервер содержимое поля From: 
должно совпадать с именем почтового ящика, в котором была осуществлена 
SMTP-авторизация. Т.е. если в настройках почтовой программы указан 
почтовый ящик mailinboxbklist@mail.ru (mailinboxbklist@list.ru, 
mailinboxbklist@bk.ru, или mailinboxbklist@inbox.ru), то 
именно это имя почтового ящика должно указываться в поле From:.

*/
WriteRaporto("DlgSendMail::Sending(CSMTPMessage & m) return FALSE;\n");
		return FALSE;
	}
WriteRaporto("DlgSendMail::Sending(CSMTPMessage & m) return TRUE;\n");
	return TRUE;
}
void WriteUnsentFile(CString & unsent)
{
	FILE * stream = fopen ("unsent.txt", "wt");
	if (stream)
	{
		fprintf(stream, unsent);
		fclose(stream);
	}
}
void DlgSendMail::OnButtonSend() 
{
WriteRaporto("DlgSendMail::OnButtonSend() 1\n");

CString unsent = "Список неотправленных адресатов:\n";

	this->UpdateData(true);

	bool res_and = true;
	bool res_or = false;

	CString login = "";
	this->m_edit_login.GetWindowText(login);
	CString from; 
	from.Format("%s@%s", login, this->m_edit_smtp_server);
	CSMTPMessage m;
	this->FillingMessage(m, this->m_edit_from, from, false);

	if (this->Connecting())
	{
WriteRaporto("DlgSendMail::OnButtonSend() if (this->Connecting())\n");
		int count = this->m_list_of_recipients.GetCount();
		for (int i = 0; i < count; i++)
		{
			CString str;
			this->m_list_of_recipients.GetText(i, str);
			
WriteRaporto("DlgSendMail::OnButtonSend() this->m_list_of_recipients.GetText(i, str);\n");
WriteRaporto(str);
WriteRaporto("\n");
			CSMTPAddress To(_T(""), _T(str)); //Change these values to your settings
			m.SetRecipient(To);

			bool res = this->Sending(m);
WriteRaporto("DlgSendMail::OnButtonSend() this->Sending(m)\n");
			res_and &= res;
			res_or |= res;

			if (!res)
			{
				unsent += str;
				unsent += "\n";
			}
		}	
		//Disconnect from the server
		smtp.Disconnect();
	}
	else res_and = false;


	if(res_and)
	{
		AfxMessageBox("Сообщение отправлено всем адресатам!!!");
	}
	else if (res_or)
	{
		AfxMessageBox("Сообщение отправлено НЕ ВСЕМ адресатам");
		AfxMessageBox(unsent);
		WriteUnsentFile(unsent);
	}
	else 
	{
		AfxMessageBox("Сообщение НЕ отправлено НИКОМУ");
	}
WriteRaporto("DlgSendMail::OnButtonSend() end\n");
	
}


void DlgSendMail::OnButtonSend2() 
{
	this->UpdateData(true);
CString unsent = "Список неотправленных адресатов:\n";

	bool res_and = true;
	bool res_or = false;

	CString login = "";
	this->m_edit_login.GetWindowText(login);
	CString from; 
	from.Format("%s@%s", login, this->m_edit_smtp_server);
	CSMTPMessage m;
	this->FillingMessage(m, this->m_edit_from, from, false);

	int count = this->m_list_of_recipients.GetCount();

	for (int i = 0; i < count; i++)
	{
		if (this->Connecting())
		{
			CString str;
			this->m_list_of_recipients.GetText(i, str);
			
			CSMTPAddress To(_T(""), _T(str)); //Change these values to your settings
			m.SetRecipient(To);

			bool res = this->Sending(m);

			res_and &= res;
			res_or |= res;
			//Disconnect from the server
			smtp.Disconnect();

			if (!res)
			{
				unsent += str;
				unsent += "\n";
			}
		}
		else
		{
			res_and = false;
			break;
		}
			
		Sleep(2000);

	}	
	if(res_and)
	{
		AfxMessageBox("Сообщение отправлено всем адресатам!!!");
	}
	else if (res_or)
	{
		AfxMessageBox("Сообщение отправлено НЕ ВСЕМ адресатам");
		AfxMessageBox(unsent);
		WriteUnsentFile(unsent);
	}
	else 
	{
		AfxMessageBox("Сообщение НЕ отправлено НИКОМУ");
	}
	
}

void DlgSendMail::OnButtonSend3() 
{
	this->UpdateData(true);

	bool res_and = true;
	bool res_or = false;
		
	CString login = "";
	this->m_edit_login.GetWindowText(login);
	CString from; 
	from.Format("%s@%s", login, this->m_edit_smtp_server);
	CSMTPMessage m;
	this->FillingMessage(m, this->m_edit_from, from, true);

	if (this->Connecting())
	{
		bool res = this->Sending(m);

		res_and &= res;
		res_or |= res;
		//Disconnect from the server
		smtp.Disconnect();
	}
	else
	{
		res_and = false;
	}

	if(res_and)
	{
		AfxMessageBox("Сообщение отправлено!!!");
	}
	else if (res_or)
	{
		AfxMessageBox("Сообщение отправлено");
	}
	else 
	{
		AfxMessageBox("Сообщение НЕ отправлено");
	}	
}

void DlgSendMail::OnCheckRequireAuthentication() 
{
/*	if (this->m_button_check_authentication.GetCheck() == BST_CHECKED)
	{
		this->m_edit_login.ShowWindow(1);
		this->m_edit_password.ShowWindow(1);
		this->m_static_login.ShowWindow(1);
		this->m_static_password.ShowWindow(1);
	}
	else
	{
		this->m_edit_login.ShowWindow(0);
		this->m_edit_password.ShowWindow(0);
		this->m_static_login.ShowWindow(0);
		this->m_static_password.ShowWindow(0);
	}*/
	
}

