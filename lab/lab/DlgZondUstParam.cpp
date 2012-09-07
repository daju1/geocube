// DlgZondUstParam.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "DlgZondUstParam.h"
#include "SetUstanovka.h"


void DeleteEndZeros(char * str);
void DeleteEndZeros(CString & str);

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgZondUstParam dialog


CDlgZondUstParam::CDlgZondUstParam(CLabView * lab_view, CLabDoc *	lab_doc, CDatabase * database, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgZondUstParam::IDD, pParent) , m_ust_list(database)
{
	//{{AFX_DATA_INIT(CDlgZondUstParam)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	this->m_lab_view = lab_view;
	this->m_lab_doc = lab_doc;
	this->p_database = database;
}


void CDlgZondUstParam::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgZondUstParam)
	DDX_Control(pDX, IDC_LIST_UST, m_ust_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgZondUstParam, CDialog)
	//{{AFX_MSG_MAP(CDlgZondUstParam)
	ON_WM_DRAWITEM()
	ON_NOTIFY(NM_CLICK, IDC_LIST_UST, OnClickListUst)
	ON_NOTIFY(LVN_BEGINLABELEDIT, IDC_LIST_UST, OnBeginlabeleditListUst)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LIST_UST, OnEndlabeleditListUst)
	ON_EN_KILLFOCUS(IDC_EDIT1, OnKillfocusEdit1)
	ON_BN_CLICKED(IDC_BUTTON_ADD_UST, OnButtonAddUst)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgZondUstParam message handlers

BOOL CDlgZondUstParam::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_ust_list.OnInitCtrl();
	// TODO: Add extra initialization here
	m_ust_list.FillCtrlList();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgZondUstParam::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nIDCtl)
	{
	case IDC_LIST_UST:
		this->m_ust_list.OnDrawItem(nIDCtl, lpDrawItemStruct);
		break;
	}
	
	//CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CDlgZondUstParam::OnClickListUst(NMHDR* pNMHDR, LRESULT* pResult) 
{
    Invalidate();
    HWND hWnd1 =  ::GetDlgItem (m_hWnd, IDC_LIST_UST);
    LPNMITEMACTIVATE temp = (LPNMITEMACTIVATE) pNMHDR;
    RECT rect;
    //get the row number

    nItem = temp->iItem;
    //get the column number

    nSubItem = temp->iSubItem;
    if(nSubItem == 0 || nSubItem == -1 || nItem < 7)
        return ;

    //Retrieve the text of the selected subItem 

    //from the list
	// set edit box text to what that field's value is
	SetUstanovka setUstanovka(this->p_database);
	setUstanovka.m_strFilter.Format("");
	setUstanovka.m_strSort.Format("");
	CString str;
	if ( setUstanovka.Open(CRecordset::dynaset) )
	{	
		try
		{
			setUstanovka.SetAbsolutePosition(temp->iItem + 1);
					
			switch (temp->iSubItem)
			{		
			case 0:
				{
					str.Format("%d", setUstanovka.m_ID_UST);
				}
				break;		
			case 1:
				{
					str.Format("%s", setUstanovka.m_NAZVA);
				}
				break;		
			case 2:
				{
					str.Format("%d", setUstanovka.m_TYP_ZOND);
				}
				break;
			case 3:
				{
					str.Format("%d", setUstanovka.m_N_SHEMA);
				}
				break;
			case 4:
				{
					//str = "Kg";
					str.Format("%f", setUstanovka.m_Kg);
					DeleteEndZeros(str);
				}
				break;
			case 5:
				{
					//str = "Kf";
					str.Format("%f", setUstanovka.m_Kf);
					DeleteEndZeros(str);
				}
				break;
			case 6:
				{
					//str = "Bg";
					str.Format("%f", setUstanovka.m_Bg);
					DeleteEndZeros(str);
				}
				break;
			case 7:
				{
					//str = "Bf";
					str.Format("%f", setUstanovka.m_Bf);
					DeleteEndZeros(str);
				}
				break;
			case 8:
				{
					//str = "shtanga_d";
					str.Format("%f", setUstanovka.m_Shtanga_d);
					DeleteEndZeros(str);
				}
				break;
			default:
				str = "---";
			}
	
		}
		catch (CDBException* pe)
		{
			AfxMessageBox(pe->m_strError);
			pe->Delete();
			return;
		}

	}
	this->m_ust_list.SetItemState(-1, 0, LVIS_SELECTED);
    RECT rect1,rect2;
    // this macro is used to retrieve the Rectanle 

    // of the selected SubItem

    RECT rect0, rect_h;
	ListView_GetViewRect(hWnd1, &rect0);
    ::GetWindowRect(ListView_GetHeader(hWnd1),&rect_h);

    ListView_GetSubItemRect(hWnd1,temp->iItem,
        temp->iSubItem,LVIR_BOUNDS,&rect);
    //Get the Rectange of the listControl

    ::GetWindowRect(temp->hdr.hwndFrom,&rect1);
    //Get the Rectange of the Dialog

    ::GetWindowRect(m_hWnd,&rect2);

    int x=rect1.left-rect2.left;
    int y=rect1.top-rect2.top;
    
    if(nItem != -1) 
    ::SetWindowPos(::GetDlgItem(m_hWnd,IDC_EDIT1),
        HWND_TOP,
		rect.left+x+4,//+x,
		rect.top + y -27,//+4, 
        rect.right-rect.left - 5,
        rect.bottom-rect.top - 1, SWP_SHOWWINDOW);
    ::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT1),SW_SHOW);
    ::SetFocus(::GetDlgItem(m_hWnd,IDC_EDIT1));
    //Draw a Rectangle around the SubItem

 //   ::Rectangle(::GetDC(temp->hdr.hwndFrom),
   //     rect.left+4,rect.top,rect.right-5,rect.bottom-1);
    //Set the listItem text in the EditBox

    ::SetWindowText(::GetDlgItem(m_hWnd,IDC_EDIT1),str);

	
	*pResult = 0;
}

void CDlgZondUstParam::OnBeginlabeleditListUst(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void CDlgZondUstParam::OnEndlabeleditListUst(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void CDlgZondUstParam::OnKillfocusEdit1() 
{
    CString str;

    GetDlgItemText(IDC_EDIT1,str);

    //set the value in the listContorl with the

    //specified Item & SubItem values

    SetCell(::GetDlgItem (m_hWnd, IDC_LIST_UST),
        str,nItem,nSubItem);

    ::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT1),
        SW_HIDE);	
}

void CDlgZondUstParam::OnButtonAddUst() 
{
	SetUstanovka setUstanovka(this->p_database);
	setUstanovka.m_strFilter.Format("");
	setUstanovka.m_strSort.Format("");
	if ( !setUstanovka.Open(CRecordset::dynaset) )
		return;

	long ID_UST = 0;
	if (!setUstanovka.IsBOF()) 
	{
		setUstanovka.MoveFirst( );
		while(!setUstanovka.IsEOF()) 
		{
			//setGrunty.Edit();
			ID_UST = setUstanovka.m_ID_UST;
			//setGrunty.Update();

			setUstanovka.MoveNext();
		}
	}
	ID_UST++;

	CString	NAZVA = "new";
	long TYP_ZOND = 1;// or 2
	long N_SHEMA = 1; // or 2
	double Kg = 1.0;
	double Kf = 1.0;
	double Bg = 0.0;
	double Bf = 0.0;
	double Shtanga_d = 0.036;
 
	setUstanovka.AddNewRow(ID_UST, 
		NAZVA, 
		TYP_ZOND,
		N_SHEMA, 
		Kg, Kf,
		Bg, Bf, 
		Shtanga_d);

	this->m_ust_list.FillCtrlList();

}

void CDlgZondUstParam::SetCell(HWND hWnd1, 
        CString value, int nRow, int nCol)
{
    TCHAR     szString [256];
    wsprintf(szString,value ,0);

    //Fill the LVITEM structure with the 

    //values given as parameters.

    LVITEM lvItem;
    lvItem.mask = LVIF_TEXT;
    lvItem.iItem = nRow;
    lvItem.pszText = szString;
    lvItem.iSubItem = nCol;
    if(nCol >0)
	{
        //set the value of listItem

        ::SendMessage(hWnd1,LVM_SETITEM, 
            (WPARAM)0,(WPARAM)&lvItem);



		SetUstanovka setUstanovka(this->p_database);
		setUstanovka.m_strFilter.Format("");
		setUstanovka.m_strSort.Format("");
		if ( setUstanovka.Open(CRecordset::dynaset) )
		{	
			try
			{
				setUstanovka.SetAbsolutePosition(nRow + 1);
				switch(nCol) 
				{			
				case 0://первая колонка
					break;
				case 1://вторая колонка
					{
						setUstanovka.Edit();
						setUstanovka.m_NAZVA = value;
						setUstanovka.Update();
					}
					break;
				case 2://третья колонка
					{
						setUstanovka.Edit();
						setUstanovka.m_TYP_ZOND = atol(value);
						setUstanovka.Update();
					}
					break;
				case 3://4-я колонка
					{
						setUstanovka.Edit();
						setUstanovka.m_N_SHEMA = atol(value);
						setUstanovka.Update();
					}
					break;
				case 4://5-я колонка
					{
						setUstanovka.Edit();
						setUstanovka.m_Kg = atof(value);
						setUstanovka.Update();
					}
					break;
				case 5://6-я колонка
					{
						setUstanovka.Edit();
						setUstanovka.m_Kf = atof(value);
						setUstanovka.Update();
					}
					break;
				case 6://7-я колонка
					{
						setUstanovka.Edit();
						setUstanovka.m_Bg = atof(value);
						setUstanovka.Update();
					}
					break;
				case 7://8-я колонка
					{
						setUstanovka.Edit();
						setUstanovka.m_Bf = atof(value);
						setUstanovka.Update();
					}
					break;
				case 8://9-я колонка
					{
						setUstanovka.Edit();
						setUstanovka.m_Shtanga_d = atof(value);
						setUstanovka.Update();
					}
					break;
				}	
			}
			catch (CDBException* pe)
			{
				AfxMessageBox(pe->m_strError);
				pe->Delete();
			}	
		}
	}
}
