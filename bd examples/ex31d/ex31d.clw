; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAboutDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ex31d.h"
LastPage=0

ClassCount=9
Class1=CChildFrame
Class2=CEx31dApp
Class3=CAboutDlg
Class4=CEx31dDoc
Class5=CEx31dView
Class6=CMainFrame
Class7=CRowView
Class8=CTableSelect
Class9=CTables

ResourceCount=10
Resource1=IDD_ABOUTBOX
Resource2=IDR_EX31DTYPE
Resource3=IDD_QUERY_BAR
Resource4=IDR_MAINFRAME
Resource5=IDD_TABLE_SELECT
Resource6=IDD_ABOUTBOX (English (U.S.))
Resource7=IDD_QUERY_BAR (English (U.S.))
Resource8=IDR_EX31DTYPE (English (U.S.))
Resource9=IDR_MAINFRAME (English (U.S.))
Resource10=IDD_TABLE_SELECT (English (U.S.))

[CLS:CChildFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=Childfrm.h
ImplementationFile=CHILDFRM.CPP

[CLS:CEx31dApp]
Type=0
BaseClass=CWinApp
HeaderFile=ex31d.h
ImplementationFile=ex31d.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=ex31d.cpp
ImplementationFile=ex31d.cpp
LastObject=CAboutDlg

[CLS:CEx31dDoc]
Type=0
BaseClass=CDocument
HeaderFile=ex31ddoc.h
ImplementationFile=ex31ddoc.cpp

[CLS:CEx31dView]
Type=0
BaseClass=CRowView
HeaderFile=ex31dview.h
ImplementationFile=ex31dview.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CMDIFrameWnd
HeaderFile=Mainfrm.h
ImplementationFile=MAINFRM.CPP

[CLS:CRowView]
Type=0
BaseClass=CScrollView
HeaderFile=ROWVIEW.H
ImplementationFile=ROWVIEW.CPP

[CLS:CTableSelect]
Type=0
BaseClass=CDialog
HeaderFile=TABLESEL.H
ImplementationFile=TABLESEL.CPP

[CLS:CTables]
Type=0
HeaderFile=TABLESET.H
ImplementationFile=TABLESET.CPP

[DB:CTables]
DB=1

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_TABLE_SELECT]
Type=1
Class=CTableSelect
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST1,listbox,1352728835

[TB:IDR_MAINFRAME]
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

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_EX31DTYPE]
Type=1
Class=?
Command1=ID_FILE_BOGUS
Command2=ID_FILE_NEW
Command3=ID_FILE_OPEN
Command4=ID_FILE_CLOSE
Command5=ID_FILE_SAVE
Command6=ID_FILE_SAVE_AS
Command7=ID_FILE_PRINT
Command8=ID_FILE_PRINT_PREVIEW
Command9=ID_FILE_PRINT_SETUP
Command10=ID_FILE_ODBCCONNECT
Command11=ID_FILE_ODBCDISCONNECT
Command12=ID_FILE_MRU_FILE1
Command13=ID_APP_EXIT
Command14=ID_EDIT_UNDO
Command15=ID_EDIT_CUT
Command16=ID_EDIT_COPY
Command17=ID_EDIT_PASTE
Command18=ID_VIEW_TOOLBAR
Command19=ID_VIEW_STATUS_BAR
Command20=ID_WINDOW_NEW
Command21=ID_WINDOW_CASCADE
Command22=ID_WINDOW_TILE_HORZ
Command23=ID_WINDOW_ARRANGE
Command24=ID_APP_ABOUT
CommandCount=24

[ACL:IDR_MAINFRAME]
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

[DLG:IDD_QUERY_BAR]
Type=1
Class=?
ControlCount=3
Control1=IDC_REQUERY,button,1342242817
Control2=IDC_QUERY,edit,1352728644
Control3=IDC_STATIC,static,1342308352

[MNU:IDR_EX31DTYPE (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_BOGUS
Command2=ID_FILE_NEW
Command3=ID_FILE_OPEN
Command4=ID_FILE_CLOSE
Command5=ID_FILE_SAVE
Command6=ID_FILE_SAVE_AS
Command7=ID_FILE_PRINT
Command8=ID_FILE_PRINT_PREVIEW
Command9=ID_FILE_PRINT_SETUP
Command10=ID_FILE_ODBCCONNECT
Command11=ID_FILE_ODBCDISCONNECT
Command12=ID_FILE_MRU_FILE1
Command13=ID_APP_EXIT
Command14=ID_EDIT_UNDO
Command15=ID_EDIT_CUT
Command16=ID_EDIT_COPY
Command17=ID_EDIT_PASTE
Command18=ID_VIEW_TOOLBAR
Command19=ID_VIEW_STATUS_BAR
Command20=ID_WINDOW_NEW
Command21=ID_WINDOW_CASCADE
Command22=ID_WINDOW_TILE_HORZ
Command23=ID_WINDOW_ARRANGE
Command24=ID_APP_ABOUT
CommandCount=24

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
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
CommandCount=8

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
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_QUERY_BAR (English (U.S.))]
Type=1
Class=?
ControlCount=3
Control1=IDC_REQUERY,button,1342242817
Control2=IDC_QUERY,edit,1352728644
Control3=IDC_STATIC,static,1342308352

[DLG:IDD_TABLE_SELECT (English (U.S.))]
Type=1
Class=?
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST1,listbox,1352728835

