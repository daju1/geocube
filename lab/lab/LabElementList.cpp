// LabElementList.cpp: implementation of the LabElementList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "LabElementList.h"

#include <map>
using namespace std;
#include "../../laboratory/src/lab.h"
#include "../../laboratory/src/LabElement.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

void DeleteEndZeros(CString & str);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLabElementList::CLabElementList()
{
	this->m_lab_element = NULL;

}
	
void CLabElementList::SetLabElement(LabElement * lab_element)
{
	this->m_lab_element = lab_element;
}

CLabElementList::~CLabElementList()
{

}

BEGIN_MESSAGE_MAP(CLabElementList, CListCtrl)
	//{{AFX_MSG_MAP(CLabElementList)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CLabElementList::FillCtrlList()
{
	CString str = "";
	CRect           rect;
	this->GetWindowRect(&rect);			
	this->DeleteAllItemsAndColomns();
	if (this->m_lab_element)
	{
		switch (this->m_lab_element->m_type)
		{
		case LabElement::type::undivided:
		case LabElement::type::with_undefined_svyaznost:
			{
				for(int i = 0; i < 16; i++) 
				{
					str = "";
					switch (i)
					{		
					case 0:
						{
							str = "Лабораторный номер";
						}
						break;		
					case 1:
						{
							str = "Глубина";
						}
						break;		
					case 2:
						{
							str = "Тип грунта";
						}
						break;
					case 3:
						{
							str = "Тип зонда";
						}
						break;
					case 4:
						{
							str = "pck";
						}
						break;
					case 5:
						{
							str = "pcb";
						}
						break;
					case 6:
						{
							str = "Удельное сцепление";
						}
						break;
					case 7:
						{
							str = "Угол внутреннего трения";
						}
						break;
					case 8:
						{
							str = "Компрессионный Модуль 01 02";
						}
						break;
					case 9:
						{
							str = "Модуль деформации 01 02";
						}
						break;
					case 10:
						{
							str = "Компрессионный Модуль defined";
						}
						break;
					case 11:
						{
							str = "Модуль деформации defined";
						}
						break;
					case 12:
						{
							str = "Модуль деформации 01 02 гурвич штамп прогноз";
						}
						break;
					case 13:
						{
							str = "Модуль деформации defined гурвич штамп прогноз";
						}
						break;
					case 14:
						{
							str = "Модуль деформации * Kp 01 02 гурвич штамп прогноз";
						}
						break;
					case 15:
						{
							str = "Модуль деформации * Kp defined гурвич штамп прогноз";
						}
						break;
					default:
						str = "---";
					}
					LVCOLUMN col;

					col.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
					col.fmt = LVCFMT_LEFT;
					col.cx = rect.Width() / 3;
					col.pszText = str.GetBuffer(str.GetLength());
					col.iSubItem = -1;

					this->InsertColumn(i, &col);
				}

			}
			break;
		case LabElement::type::nesvyaznye:
			{
				for(int i = 0; i < 16; i++) 
				{
					str = "";
					switch (i)
					{		
					case 0:
						{
							str = "Лабораторный номер";
						}
						break;		
					case 1:
						{
							str = "Глубина";
						}
						break;
					case 2:
						{
							str = "Тип грунта";
						}
						break;
					case 3:
						{
							str = "Тип несвязного грунта";
						}
						break;
					case 4:
						{
							str = "minimum_krupnosti_chastic";							
						}
						break;
					case 5:
						{
							str = "t - t_alpha";
						}
						break;
					case 6:
						{
							str = "soderzhanie_chastic";							
						}
						break;
					case 7:
						{
							str = "t - t_alpha";
						}
						break;
					case 8:
						{	
							str = "neodnorodnost";
						}
						break;		
					case 9:
						{
							str = "C_u";							
						}
						break;
					case 10:
						{
							str = "t - t_alpha";
						}
						break;
					case 11:
						{
							str = "e";
						}
						break;		
					case 12:
						{								
							str = "t - t_alpha";
						}
						break;		
					case 13:
						{	
							str = "sand_vlazhnost";
						}
						break;		
					case 14:
						{
							str = "S";							
						}
						break;
					case 15:
						{
							str = "t - t_alpha";
						}
						break;
					default:
						str = "---";
					}
					LVCOLUMN col;

					col.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
					col.fmt = LVCFMT_LEFT;
					col.cx = rect.Width() / 4;
					col.pszText = str.GetBuffer(str.GetLength());
					col.iSubItem = -1;

					this->InsertColumn(i, &col);
				}

			}
			break;
		case LabElement::type::svyaznye:
			{
				for(int i = 0; i < 22; i++) 
				{
					str = "";
					switch (i)
					{		
					case 0:
						{
							str = "Лабораторный номер";
						}
						break;		
					case 1:
						{
							str = "Глубина";
						}
						break;
					case 2:
						{
							str = "Тип грунта";
						}
						break;
					case 3:
						{
							str = "Число пластичности";
						}
						break;
					case 4:
						{
							str = "t - t_alpha";
						}
						break;
					case 5:
						{
							str = "Consistencia_nature";
						}
						break;		
					case 6:
						{
							str = "fluidity_index_nature";
						}
						break;		
					case 7:
						{								
							str = "t - t_alpha";
						}
						break;		
					case 8:
						{
							str = "Consistencia_water_saturated";
						}
						break;		
					case 9:
						{
							str = "fluidity_index_water_saturated";
						}
						break;		
					case 10:
						{								
							str = "t - t_alpha";
						}
						break;		
					case 11:
						{
							str = "e";
						}
						break;		
					case 12:
						{								
							str = "t - t_alpha";
						}
						break;		
					case 13:
						{
							str = "zatorfovannost";
						}
						break;		
					case 14:
						{
							str = "organic";
						}
						break;		
					case 15:
						{								
							str = "t - t_alpha";
						}
						break;		
					case 16:
						{
							str = "prosadochnost";
						}
						break;		
					case 17:
						{
							str = "nachalnoe_prosadochnoe_davlenie";
						}
						break;		
					case 18:
						{								
							str = "t - t_alpha";
						}
						break;		
					case 19:
						{
							str = "nabuhanie";
						}
						break;		
					case 20:
						{
							str = "svobodnoe_otnositelnoe_nabuhanie";
						}
						break;		
					case 21:
						{								
							str = "t - t_alpha";
						}
						break;		
					default:
						str = "---";
					}
					LVCOLUMN col;

					col.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
					col.fmt = LVCFMT_LEFT;
					col.cx = rect.Width() / 6;
					col.pszText = str.GetBuffer(str.GetLength());
					col.iSubItem = -1;

					this->InsertColumn(i, &col);
				}

			}
			break;
		}

		for (vector<SoilDescriptionPtr>::iterator it = this->m_lab_element->vsdp.begin();
			it != this->m_lab_element->vsdp.end(); it++)
		{
			this->DrawDataRow(it);
		}
	}
}

void CLabElementList::InSertTheItem(CString & str, int & iActualItem, int iSubItem)
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
void DrawSubItem(CString & str, trial_t_value & val)
{
	if (val.f)
	{
		str.Format("%f", val.v); DeleteEndZeros(str);
	}
	else
		str = "---";							
}
void CLabElementList::DrawDataRow(vector<SoilDescriptionPtr>::iterator & it)
{	 
	SoilDescriptionPtr sdp = (*it);

	CString str;
	int iActualItem = 0;
	if (this->m_lab_element)
	{
		switch (this->m_lab_element->m_type)
		{
		case LabElement::type::undivided:
		case LabElement::type::with_undefined_svyaznost:
			{
				for (int iSubItem = 0; iSubItem < 16; iSubItem++) 
				{
					str = "";

					switch (iSubItem)
					{		
					case 0:
						{
							str.Format("%d", sdp.psd->lab_n);
						}
						break;		
					case 1:
						{
							//str.Format("%0.2f", sdp.psd->lab_number->depth);
							str.Format("%f", sdp.psd->lab_number->depth); DeleteEndZeros(str);
						}
						break;		
					case 2:
						{
							str = CGround::GrountTypeToStringRus(sdp.psd->m_ground_type);
						}
						break;		
					case 3:
						{
							str.Format("%d", sdp.psd->zond_type.v);
						}
						break;
					case 4:
						{
							str.Format("%f", sdp.psd->pck.v); DeleteEndZeros(str);
						}
						break;
					case 5:
						{
							//str = "pcb";
							str.Format("%f", sdp.psd->pcb.v); DeleteEndZeros(str);
						}
						break;
					case 6:
						{
							//str = "Удельное сцепление";
							str.Format("%f", sdp.psd->c.v); DeleteEndZeros(str);
						}
						break;
					case 7:
						{
							//str = "Угол внутреннего трения";
							str.Format("%f", sdp.psd->fi.v); DeleteEndZeros(str);
						}
						break;
					case 8:
						{
							//str = "Компрессионный Модуль 01 02";
							str.Format("%f", sdp.psd->compression_module_e_in_01_02_interval.v); DeleteEndZeros(str);
						}
						break;
					case 9:
						{
							//str = "Модуль деформации 01 02";
							str.Format("%f", sdp.psd->deformation_module_e_in_01_02_interval.v); DeleteEndZeros(str);
						}
						break;
					case 10:
						{
							//str = "Компрессионный Модуль defined";
							str.Format("%f", sdp.psd->compression_module_e_in_defined_interval.v); DeleteEndZeros(str);
						}
						break;
					case 11:
						{
							//str = "Модуль деформации defined";
							str.Format("%f", sdp.psd->deformation_module_e_in_defined_interval.v); DeleteEndZeros(str);
						}
						break;
					case 12:
						{
							//str = "Модуль деформации 01 02 гурвич штамп прогноз";
							str.Format("%f", sdp.psd->gurvich_shtamp_deformation_module_in_01_02_interval.v); DeleteEndZeros(str);
						}
						break;
					case 13:
						{
							//str = "Модуль деформации defined гурвич штамп прогноз";
							str.Format("%f", sdp.psd->gurvich_shtamp_deformation_module_in_defined_interval.v); DeleteEndZeros(str);
						}
						break;
					case 14:
						{
							//str = "Модуль деформации * Kp 01 02 гурвич штамп прогноз";
							str.Format("%f", sdp.psd->gurvich_shtamp_deformation_module_in_01_02_interval_Kp.v); DeleteEndZeros(str);
						}
						break;
					case 15:
						{
							//str = "Модуль деформации * Kp defined гурвич штамп прогноз";
							str.Format("%f", sdp.psd->gurvich_shtamp_deformation_module_in_defined_interval_Kp.v); DeleteEndZeros(str);
						}
						break;
					}
					InSertTheItem(str, iActualItem, iSubItem);
				}
			}
			break;
		case LabElement::type::nesvyaznye:
			{
				for (int iSubItem = 0; iSubItem < 16; iSubItem++) 
				{
					str = "";

					switch (iSubItem)
					{		
					case 0:
						{
							str.Format("%d", sdp.psd->lab_n);
						}
						break;		
					case 1:
						{
							str.Format("%0.2f", sdp.psd->lab_number->depth);
						}
						break;		
					case 2:
						{
							str = CGround::GrountTypeToStringRus(sdp.psd->m_ground_type);
						}
						break;		
					case 3:
						{	
							str = FractionsLabTrialResults::SandSoilsClassToString(sdp.psd->m_sand_soil_class);
						}
						break;		
					//case :
					//	{	
					//		str = FractionsLabTrialResults::ClaySoilsClassToString(sdp.psd->m_clay_soil_class);
					//	}
					//	break;		
					case 4:
						{
							if (sdp.psd->m_minimum_krupnosti_chastic.f)
								str.Format("%0.3f", sdp.psd->m_minimum_krupnosti_chastic.v);
							else
								str = "---";							
						}
						break;
					case 5:
						{
							if (sdp.psd->m_minimum_krupnosti_chastic.f)
								str.Format("%0.3f", sdp.psd->m_minimum_krupnosti_chastic.t);
							else
								str = "---";							
						}
						break;
					case 6:
						{
							if (sdp.psd->m_soderzhanie_chastic.f)
								str.Format("%0.3f", sdp.psd->m_soderzhanie_chastic.v);
							else
								str = "---";							
						}
						break;
					case 7:
						{
							if (sdp.psd->m_soderzhanie_chastic.f)
								str.Format("%0.3f", sdp.psd->m_soderzhanie_chastic.t);
							else
								str = "---";							
						}
						break;
					case 8:
						{	
							str = FractionsLabTrialResults::NeodnorodnostToString(sdp.psd->m_neodnorodnost);
						}
						break;		
					case 9:
						{
							if (sdp.psd->C_u.f)
								str.Format("%0.3f", sdp.psd->C_u.v);
							else
								str = "---";							
						}
						break;
					case 10:
						{
							if (sdp.psd->C_u.f)
								str.Format("%0.3f", sdp.psd->C_u.t);
							else
								str = "---";							
						}
						break;
					case 11:
						{
							if (sdp.psd->e.f)
								str.Format("%0.3f", sdp.psd->e.v);
							else
								str = "---";
						}
						break;		
					case 12:
						{								
							if (sdp.psd->e.f)
								str.Format("%0.3f", sdp.psd->e.t);
							else
								str = "---";
						}
						break;		
					case 13:
						{	
							str = PhysicalLabTrialResults::SandVlazhnostToString(sdp.psd->m_sand_vlazhnost);
						}
						break;		
					case 14:
						{
							if (sdp.psd->S.f)
								str.Format("%0.3f", sdp.psd->S.v);
							else
								str = "---";							
						}
						break;
					case 15:
						{
							if (sdp.psd->S.f)
								str.Format("%0.3f", sdp.psd->S.t);
							else
								str = "---";							
						}
						break;
					}
					InSertTheItem(str, iActualItem, iSubItem);
				}
			}
			break;
		case LabElement::type::svyaznye:
			{
				for (int iSubItem = 0; iSubItem < 22; iSubItem++) 
				{
					str = "";

					switch (iSubItem)
					{		
					case 0:
						{
							str.Format("%d", sdp.psd->lab_n);
						}
						break;		
					case 1:
						{
							str.Format("%0.2f", sdp.psd->lab_number->depth);
						}
						break;		
					case 2:
						{
							str = CGround::GrountTypeToStringRus(sdp.psd->m_ground_type);
						}
						break;		
					case 3:
						{
							if (sdp.psd->plasticity_index.f)
								str.Format("%0.3f", sdp.psd->plasticity_index.v);
							else
								str = "---";
						}
						break;		
					case 4:
						{								
							str.Format("%0.3f", sdp.psd->plasticity_index.t);
						}
						break;		
					case 5:
						{
							str = PhysicalLabTrialResults::ConsistenciaToString(sdp.psd->m_Consistencia_nature);
						}
						break;		
					case 6:
						{
							if (sdp.psd->fluidity_index_nature.f)
								str.Format("%0.3f", sdp.psd->fluidity_index_nature.v);
							else
								str = "---";
						}
						break;		
					case 7:
						{								
							str.Format("%0.3f", sdp.psd->fluidity_index_nature.t);
						}
						break;		
					case 8:
						{
							str = PhysicalLabTrialResults::ConsistenciaToString(sdp.psd->m_Consistencia_water_saturated);
						}
						break;		
					case 9:
						{
							if (sdp.psd->fluidity_index_water_saturated.f)
								str.Format("%0.3f", sdp.psd->fluidity_index_water_saturated.v);
							else
								str = "---";
						}
						break;		
					case 10:
						{								
							str.Format("%0.3f", sdp.psd->fluidity_index_water_saturated.t);
						}
						break;		
					case 11:
						{
							if (sdp.psd->e.f)
								str.Format("%0.3f", sdp.psd->e.v);
							else
								str = "---";
						}
						break;		
					case 12:
						{								
							str.Format("%0.3f", sdp.psd->e.t);
						}
						break;		
					case 13:
						{
							str = ChemicalLabTrialResults::ZatorfovannostToString(sdp.psd->m_zatorfovannost);
						}
						break;		
					case 14:
						{
							if (sdp.psd->organic.f)
								str.Format("%0.3f", sdp.psd->organic.v);
							else
								str = "---";
						}
						break;		
					case 15:
						{								
							str.Format("%0.3f", sdp.psd->organic.t);
						}
						break;		
					case 16:
						{
							str = CompressionLabTrialResults3::ProsadochnostToString(sdp.psd->m_prosadochnost);
						}
						break;		
					case 17:
						{
							if (sdp.psd->nachalnoe_prosadochnoe_davlenie.f)
								str.Format("%0.3f", sdp.psd->nachalnoe_prosadochnoe_davlenie.v);
							else
								str = "---";
						}
						break;		
					case 18:
						{								
							str.Format("%0.3f", sdp.psd->nachalnoe_prosadochnoe_davlenie.t);
						}
						break;		
					case 19:
						{
							str = CompressionLabTrialResults3::NabuhanieToString(sdp.psd->m_nabuhanie);
						}
						break;		
					case 20:
						{
							if (sdp.psd->svobodnoe_otnositelnoe_nabuhanie.f)
								str.Format("%0.3f", sdp.psd->svobodnoe_otnositelnoe_nabuhanie.v);
							else
								str = "---";
						}
						break;		
					case 21:
						{								
							str.Format("%0.3f", sdp.psd->svobodnoe_otnositelnoe_nabuhanie.t);
						}
						break;		
					}
					InSertTheItem(str, iActualItem, iSubItem);
				}
			}
			break;
		}
	}
}

void CLabElementList::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	/*LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE) pNMHDR;
	
	int r = lpnmitem->iItem;
	int c = lpnmitem->iSubItem;

	char str[1024];
	sprintf(
		str, 
		"OnDblclk\n"
		"pNMHDR->code = %u\n"
		"pNMHDR->hwndFrom = %x\n"
		"pNMHDR->idFrom = %d\n"
		"r = %d c = %d"
		,
		pNMHDR->code,
		pNMHDR->hwndFrom,
		pNMHDR->idFrom,
		r,c
		);*/
	//AfxMessageBox(str);

//	CDlgObject dialog(m_geo_view, m_geo_view->GetDocument(), false);
//	dialog.DoModal();

	*pResult = 0;
}

void CLabElementList::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE) pNMHDR;
	
	int r = lpnmitem->iItem;
	if (r < 0) return;


	*pResult = 0;
}


void CLabElementList::OnSize(UINT nType, int cx, int cy) 
{
	CMyListCtrl::OnSize(nType, cx, cy);
	
	m_cxClient = cx;
	
}

