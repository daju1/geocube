// DlgCopyGrunty.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "DlgCopyGrunty.h"
#include "LabView.h"

#include "SetObject.h"
#include "SetGrunty.h"
#include "SetIGE.h"
#include "SetCubeSize.h"
#include "../../surfdoc/src/grid.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgCopyGrunty dialog


DlgCopyGrunty::DlgCopyGrunty(CLabView * lab_view, CLabDoc *	lab_doc, CDatabase * database, CWnd* pParent /*=NULL*/)
	: CDialog(DlgCopyGrunty::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgCopyGrunty)
	m_check_also_ige = FALSE;
	m_check_also_cube_size = FALSE;
	m_edit_source_object = _T("");
	//}}AFX_DATA_INIT
	this->m_lab_view = lab_view;
	this->m_lab_doc = lab_doc;
	this->p_database = database;
	ID_OBJ = -1;
	id_dest_obj = -1;
}


void DlgCopyGrunty::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgCopyGrunty)
	DDX_Control(pDX, IDC_COMBO_DEST_OBJECT, m_combo_dest_object);
	DDX_Check(pDX, IDC_CHECK_ALSO_IGE, m_check_also_ige);
	DDX_Check(pDX, IDC_CHECK_ALSO_CUBE_SIZE, m_check_also_cube_size);
	DDX_Text(pDX, IDC_EDIT_SOURCE_OBJECT, m_edit_source_object);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgCopyGrunty, CDialog)
	//{{AFX_MSG_MAP(DlgCopyGrunty)
	ON_CBN_SELCHANGE(IDC_COMBO_DEST_OBJECT, OnSelchangeComboDestObject)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgCopyGrunty message handlers



BOOL DlgCopyGrunty::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	int nObItem = this->m_lab_view->GetObjectItem();

	if (nObItem < 0)
	{
		AfxMessageBox("Не выбрано ни одного объекта");
		return FALSE;
	}


	try
	{
		SetObject setObject(this->p_database);
		if ( !setObject.Open(CRecordset::dynaset) )
			return false;

		setObject.SetAbsolutePosition(nObItem + 1);        
		ID_OBJ = setObject.m_ID_OBJ;
		this->m_edit_source_object = setObject.m_NAZVA;
			
		int i_obj = 0;
		if (!setObject.IsBOF()) 
		{
			setObject.MoveFirst( );
			while(!setObject.IsEOF()) 
			{
				setObject.m_ID_OBJ;
				setObject.m_NAZVA;

				this->m_combo_dest_object.AddString(setObject.m_NAZVA);
				this->m_combo_dest_object.SetItemData(i_obj, setObject.m_ID_OBJ);

				setObject.MoveNext();
				i_obj++;
			}
		}
	}
	catch (CDBException* pe) 
	{
		AfxMessageBox(pe->m_strError);
		pe->Delete();
		return false;
	}

	
	this->UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CopyIGE(bool bUnEdited, CDatabase * database, long ID_OBJ, long id_dest_obj)
{
	SetIGE setIGE_dest(bUnEdited, database);
	setIGE_dest.m_strFilter.Format("ID_OBJ = %d", id_dest_obj);
	setIGE_dest.m_strSort.Format("");
	if ( !setIGE_dest.Open(CRecordset::dynaset) )
		return;
	if (!setIGE_dest.IsBOF()) 
	{
		setIGE_dest.MoveFirst( );
		while(!setIGE_dest.IsEOF()) 
		{
			setIGE_dest.Delete();
			setIGE_dest.MoveNext();
		}
	}

	SetIGE setIGE(bUnEdited, database);
	setIGE.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
	setIGE.m_strSort.Format("");
	if ( !setIGE.Open(CRecordset::dynaset) )
		return;

	if (!setIGE.IsBOF()) 
	{
		setIGE.MoveFirst( );
		while(!setIGE.IsEOF()) 
		{
			setIGE_dest.AddNewRow(id_dest_obj, setIGE.m_ID_IGE, setIGE.m_ID_GR, setIGE.m_IGE, setIGE.m_mk, setIGE.m_mkz, setIGE.m_strat, setIGE.m_desc0);
			setIGE.MoveNext();
		}
	}
}

void CopyCubeSize(CDatabase * database, long ID_OBJ, long id_dest_obj)
{
	SetCubeSize setCubeSize_dest(database);
	setCubeSize_dest.m_strFilter.Format("ID_OBJ = %d", id_dest_obj);
	setCubeSize_dest.m_strSort.Format("");
	if ( !setCubeSize_dest.Open(CRecordset::dynaset) )
		return;
	if (!setCubeSize_dest.IsBOF()) 
	{
		setCubeSize_dest.MoveFirst( );
		while(!setCubeSize_dest.IsEOF()) 
		{
			setCubeSize_dest.Delete();
			setCubeSize_dest.MoveNext();
		}
	}

	SetCubeSize setCubeSize(database);
	setCubeSize.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
	setCubeSize.m_strSort.Format("");
	if ( !setCubeSize.Open(CRecordset::dynaset) )
		return;

	if (!setCubeSize.IsBOF()) 
	{
		setCubeSize.MoveFirst( );
		while(!setCubeSize.IsEOF()) 
		{
			CubeSize cube_size;
			setCubeSize.InitStruct(cube_size);

			setCubeSize_dest.AddNew();
			setCubeSize_dest.m_ID_OBJ = ID_OBJ;
			setCubeSize_dest.Init(cube_size);
			setCubeSize_dest.Update();
			setCubeSize.MoveNext();
		}
	}
}

void DlgCopyGrunty::OnOK() 
{
	this->UpdateData(true);


	SetGrunty setGrunty_dest(this->p_database);
	setGrunty_dest.m_strFilter.Format("ID_OBJ = %d", id_dest_obj);
	setGrunty_dest.m_strSort.Format("");
	if ( !setGrunty_dest.Open(CRecordset::dynaset) )
		return;
	if (!setGrunty_dest.IsBOF()) 
	{
		setGrunty_dest.MoveFirst( );
		while(!setGrunty_dest.IsEOF()) 
		{
			setGrunty_dest.Delete();
			setGrunty_dest.MoveNext();
		}
	}

	SetGrunty setGrunty(this->p_database);
	setGrunty.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
	setGrunty.m_strSort.Format("");
	if ( !setGrunty.Open(CRecordset::dynaset) )
		return;

	if (!setGrunty.IsBOF()) 
	{
		setGrunty.MoveFirst( );
		while(!setGrunty.IsEOF()) 
		{
			setGrunty_dest.AddNewRow(id_dest_obj, setGrunty.m_ID_GR, setGrunty.m_NAZVA_U, setGrunty.m_NAZVA_R, setGrunty.m_TYPGR, setGrunty.m_TYPGR_PCK, setGrunty.m_ID_NORMATYV, setGrunty.m_ID_GRCONS, setGrunty.m_ID_UKLAD, setGrunty.m_ID_NJU, setGrunty.m_ID_GRMAIN, setGrunty.m_ID_UMPOZ, setGrunty.m_ID_GENEZIS);
			setGrunty.MoveNext();
		}
	}

	if (this->m_check_also_ige)
	{
		CopyIGE(true, this->p_database, ID_OBJ, id_dest_obj);
		CopyIGE(false, this->p_database, ID_OBJ, id_dest_obj);
	}

	if (this->m_check_also_cube_size)
	{
		CopyCubeSize(this->p_database, ID_OBJ, id_dest_obj);
	}

	CDialog::OnOK();
}

void DlgCopyGrunty::OnSelchangeComboDestObject() 
{
	// TODO: Add your control notification handler code here
	int index = this->m_combo_dest_object.GetCurSel();
	id_dest_obj = long(this->m_combo_dest_object.GetItemData(index));
	
}
