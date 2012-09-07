; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=DlgSendMail
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "mailwriter.h"
LastPage=0

ClassCount=6
Class1=CMailwriterApp
Class2=CMailwriterDoc
Class3=CMailwriterView
Class4=CMainFrame

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class5=CAboutDlg
Resource3=IDD_ABOUTBOX (English (U.S.))
Resource4=IDD_DIALOG_SEND_MAIL
Class6=DlgSendMail
Resource5=IDR_MAINFRAME (English (U.S.))

[CLS:CMailwriterApp]
Type=0
HeaderFile=mailwriter.h
ImplementationFile=mailwriter.cpp
Filter=N
LastObject=CMailwriterApp

[CLS:CMailwriterDoc]
Type=0
HeaderFile=mailwriterDoc.h
ImplementationFile=mailwriterDoc.cpp
Filter=N

[CLS:CMailwriterView]
Type=0
HeaderFile=mailwriterView.h
ImplementationFile=mailwriterView.cpp
Filter=C
BaseClass=CEditView
VirtualFilter=VWC
LastObject=CMailwriterView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=CMainFrame




[CLS:CAboutDlg]
Type=0
HeaderFile=mailwriter.cpp
ImplementationFile=mailwriter.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
CommandCount=16
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command16=ID_APP_ABOUT

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
CommandCount=14
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE


[DLG:IDD_DIALOG_SEND_MAIL]
Type=1
Class=DlgSendMail
ControlCount=28
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT_SMTP_SERVER,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_CHECK_REQUIRE_AUTHENTICATION,button,1342242819
Control6=IDC_EDIT_LOGIN,edit,1350631552
Control7=IDC_STATIC_LOGIN,static,1342308352
Control8=IDC_EDIT_PASSWORD,edit,1350631584
Control9=IDC_STATIC_PASSWORD,static,1342308352
Control10=IDC_STATIC,button,1342177287
Control11=IDC_EDIT_FROM,edit,1350631552
Control12=IDC_STATIC,static,1342308352
Control13=IDC_LIST_OF_RECIPIENTS,listbox,1353779457
Control14=IDC_LIST_OF_ATTACHES,listbox,1353779457
Control15=IDC_BUTTON_LOAD_ADRESSES,button,1342242816
Control16=IDC_BUTTON_ADD_FILE,button,1342242816
Control17=IDC_BUTTON_SEND,button,1342242816
Control18=IDC_BUTTON_DELETE_FILE,button,1342242816
Control19=IDC_STATIC,button,1342177287
Control20=IDC_STATIC,button,1342177287
Control21=IDC_BUTTON_DELETE_RECIPIENT,button,1342242816
Control22=IDC_EDIT_EXCEL_COLOMN,edit,1350631552
Control23=IDC_EDIT_SUBJECT,edit,1350631552
Control24=IDC_STATIC,static,1342308352
Control25=IDC_BUTTON_SEND2,button,1342242816
Control26=IDC_BUTTON_SEND3,button,1342242816
Control27=IDC_BUTTON_LOAD_ADRESSES_TXT,button,1342251008
Control28=IDC_LIST_VIEW_OF_RECIPIENTS,SysListView32,1082195968

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_APP_ABOUT
Command17=ID_MAIL_SEND
CommandCount=17

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[CLS:DlgSendMail]
Type=0
HeaderFile=DlgSendMail.h
ImplementationFile=DlgSendMail.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_LIST_VIEW_OF_RECIPIENTS
VirtualFilter=dWC

