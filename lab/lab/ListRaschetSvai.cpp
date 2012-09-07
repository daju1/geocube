// RaschetSvaiList.cpp: implementation of the RaschetSvaiList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "ListRaschetSvai.h"

#include "../../surfdoc/src/well_3d.h"


void DeleteEndZeros(char * str);
void DeleteEndZeros(CString & str);

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CListRaschetSvai::CListRaschetSvai(CDatabase * database, Well_3D * well)
{
	this->p_database = database;
	p_well = well;
	this->ID_KT = -1;
	this->ID_OBJ = -1;
}
	


CListRaschetSvai::~CListRaschetSvai()
{

}

BEGIN_MESSAGE_MAP(CListRaschetSvai, CListCtrl)
	//{{AFX_MSG_MAP(CListRaschetSvai)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CListRaschetSvai::InitHeaders()
{
	CString str = "";
	CRect           rect;
	this->GetWindowRect(&rect);			
	this->DeleteAllItemsAndColomns();

	for(int i = 0; i < 11; i++) 
	{
		str = "";
		switch (i)
		{		
		case 0:
			{
				str = "Àëüò.îñòðèÿ ñâàè, ì";
			}
			break;		
		case 1:
			{
				str = "Ãëóáèíà, ì";
			}
			break;		
		case 2:
			{
				str = "qc,ÌÏà";
			}
			break;		
		case 3:
			{
				str = "beta1";
			}
			break;		
		case 4:
			{
				str = "Rs, ÌÏà";
			}
			break;		
		case 5:
			{
				str = "fs, êÏà";
			}
			break;		
		case 6:
			{
				str = "beta2";
			}
			break;		
		case 7:
			{
				str = "f, êÏà";
			}
			break;		
		case 8:
			{
				str = "RsA, êÍ";
			}
			break;		
		case 9:
			{
				str = "fhu, êÍ";
			}
			break;
		case 10:
			{
				str = "Fu, êÍ";
			}
			break;
		default:
			str = "---";
		}
		LVCOLUMN col;

		col.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		col.fmt = LVCFMT_LEFT;
		col.cx = rect.Width() / 10;
		col.pszText = str.GetBuffer(str.GetLength());
		col.iSubItem = -1;

		this->InsertColumn(i, &col);
	}
}
void CListRaschetSvai::AddString(int & iActualItem, int iSubItem, CString & str)
{
	InSertTheItem(str, iActualItem, iSubItem);
}

void CListRaschetSvai::FillCtrlList()
{
	CString str = "";
	int npp = 1, iSubItem;
	int iActualItem = 0;
	for (vector<PaljaData1>::iterator it = this->p_well->m_palja.data1.begin();
		it != this->p_well->m_palja.data1.end(); it++)
	{	

		iSubItem = 0;

		str.Format("%f", this->p_well->m_palja.data2.pz - (*it).h);
		DeleteEndZeros(str);
		InSertTheItem(str, iActualItem, iSubItem++);

		str.Format("%f", (*it).h);
		DeleteEndZeros(str);
		InSertTheItem(str, iActualItem, iSubItem++);

		str.Format("%f", (*it).qc);
		DeleteEndZeros(str);
		InSertTheItem(str, iActualItem, iSubItem++);

		str.Format("%f", (*it).beta1);
		DeleteEndZeros(str);
		InSertTheItem(str, iActualItem, iSubItem++);

		str.Format("%f", (*it).Rs);
		DeleteEndZeros(str);
		InSertTheItem(str, iActualItem, iSubItem++);

		str.Format("%f", (*it).fs);
		DeleteEndZeros(str);
		InSertTheItem(str, iActualItem, iSubItem++);

		str.Format("%f", (*it).beta2);
		DeleteEndZeros(str);
		InSertTheItem(str, iActualItem, iSubItem++);

		str.Format("%f", (*it).f);
		DeleteEndZeros(str);
		InSertTheItem(str, iActualItem, iSubItem++);

		str.Format("%f", (*it).RsA);
		DeleteEndZeros(str);
		InSertTheItem(str, iActualItem, iSubItem++);

		str.Format("%f", (*it).fhu);
		DeleteEndZeros(str);
		InSertTheItem(str, iActualItem, iSubItem++);

		str.Format("%f", (*it).Fu);
		DeleteEndZeros(str);
		InSertTheItem(str, iActualItem, iSubItem++);

	}
}

void CListRaschetSvai::InSertTheItem(CString & str, int & iActualItem, int iSubItem)
{
	LV_ITEM         lvitem;
	lvitem.mask = LVIF_TEXT;// | (iSubItem == 0 ? LVIF_IMAGE : 0);
	lvitem.iItem = (iSubItem == 0) ? this->GetItemCount( ) : iActualItem;
	lvitem.iSubItem = iSubItem;

	// calculate the main and sub-item strings for the current item
	lvitem.pszText = str.GetBuffer(str.GetLength());

	//lvitem.iImage = iIcon;
	lvitem.iImage = 0;
	if (iSubItem == 0)
		iActualItem = this->InsertItem(&lvitem); // insert new item
	else
		this->SetItem(&lvitem); // modify existing item (the sub-item text)
}


void CListRaschetSvai::OnSize(UINT nType, int cx, int cy) 
{
	CMyListCtrl::OnSize(nType, cx, cy);
	
	m_cxClient = cx;	
}

