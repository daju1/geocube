; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CEx31bView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ex31b.h"
LastPage=0

ClassCount=6
Class1=CEx31bApp
Class2=CEx31bDoc
Class3=CEx31bView
Class4=CMainFrame
Class6=CAboutDlg

ResourceCount=7
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class5=CEx31bSet
Resource7=IDD_EX31B_FORM

[CLS:CEx31bApp]
Type=0
HeaderFile=ex31b.h
ImplementationFile=ex31b.cpp
Filter=N

[CLS:CEx31bDoc]
Type=0
HeaderFile=ex31bDoc.h
ImplementationFile=ex31bDoc.cpp
Filter=N

[CLS:CEx31bView]
Type=0
HeaderFile=ex31bView.h
ImplementationFile=ex31bView.cpp
Filter=D
LastObject=ID_RECORD_UPDATE
BaseClass=CRecordView
VirtualFilter=RVWC


[CLS:CEx31bSet]
Type=0
HeaderFile=ex31bSet.h
ImplementationFile=ex31bSet.cpp
Filter=N

[DB:CEx31bSet]
DB=1
DBType=ODBC
ColumnCount=3
Column1=[InstructorID], 12, 8
Column2=[Name], 12, 40
Column3=[RoomNo], 12, 10


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
HeaderFile=ex31b.cpp
ImplementationFile=ex31b.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_APP_EXIT
Command2=ID_EDIT_UNDO
Command3=ID_EDIT_CUT
Command4=ID_EDIT_COPY
Command5=ID_EDIT_PASTE
Command6=ID_RECORD_FIRST
Command7=ID_RECORD_PREV
Command8=ID_RECORD_NEXT
Command9=ID_RECORD_LAST
Command10=ID_RECORD_ADD
Command11=ID_RECORD_CLEARFIELDS
Command12=ID_RECORD_DELETE
Command13=ID_RECORD_UPDATE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_APP_ABOUT
CommandCount=16

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_EDIT_UNDO
Command2=ID_EDIT_CUT
Command3=ID_EDIT_COPY
Command4=ID_EDIT_PASTE
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_NEXT_PANE
Command10=ID_PREV_PANE
CommandCount=10

[DLG:IDD_EX31B_FORM]
Type=1
Class=CEx31bView
ControlCount=7
Control1=IDC_STATIC,button,1342177287
Control2=IDC_ID,edit,1350631552
Control3=IDC_NAME,edit,1350631552
Control4=IDC_ROOM,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_EDIT_CUT
Command2=ID_EDIT_COPY
Command3=ID_EDIT_PASTE
Command4=ID_FILE_PRINT
Command5=ID_RECORD_FIRST
Command6=ID_RECORD_PREV
Command7=ID_RECORD_NEXT
Command8=ID_RECORD_LAST
Command9=ID_APP_ABOUT
CommandCount=9

