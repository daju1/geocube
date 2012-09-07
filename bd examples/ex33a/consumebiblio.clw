; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CConsumebiblioDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "consumebiblio.h"
ODLFile=consumebiblio.odl

ClassCount=5
Class1=CConsumebiblioApp
Class2=CConsumebiblioDlg
Class3=CAboutDlg
Class4=CConsumebiblioDlgAutoProxy

ResourceCount=4
Resource1=IDD_CONSUMEBIBLIO_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Class5=CUseAuthors
Resource4=IDD_USEAUTHORS

[CLS:CConsumebiblioApp]
Type=0
HeaderFile=consumebiblio.h
ImplementationFile=consumebiblio.cpp
Filter=N

[CLS:CConsumebiblioDlg]
Type=0
HeaderFile=consumebiblioDlg.h
ImplementationFile=consumebiblioDlg.cpp
Filter=D
LastObject=IDC_DOIT
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=consumebiblioDlg.h
ImplementationFile=consumebiblioDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[CLS:CConsumebiblioDlgAutoProxy]
Type=0
HeaderFile=DlgProxy.h
ImplementationFile=DlgProxy.cpp
BaseClass=CCmdTarget
Filter=N

[DLG:IDD_CONSUMEBIBLIO_DIALOG]
Type=1
Class=CConsumebiblioDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_DOIT,button,1342242816

[DLG:IDD_USEAUTHORS]
Type=1
Class=CUseAuthors
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_NEXT,button,1342242816
Control4=IDC_STATIC,static,1342308352
Control5=IDC_AUTHOR,edit,1350631552

[CLS:CUseAuthors]
Type=0
HeaderFile=UseAuthors.h
ImplementationFile=UseAuthors.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_NEXT
VirtualFilter=dWC

