#include "../../surfer_connect/StdAfx.h"
#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>			// MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#include "stdafx.h"
#include "../../wintools/src/appdefine.h"
#include "WellElement.h"
#include "winsurftree.h"
#include "surfdoc.h"
#include "../../tools/src/errorexit.h"

#include "gdiplus.h"
//#include <Gdipluseffects.h>
	

#include "../../wintools\src\project.h"
#include "../../wintools\src\win32_map_views.h"

#include "../../lab/lab/labdoc.h"

#include "../acad_connect/MyAcad.h"
void AddText(MyAcad & m_acad, LPCTSTR TextString, CPoint2 pt2, double Height, COLORREF color, double v_scale, double g_scale);
void AddText(MyAcad & m_acad, LPCTSTR TextString, CPoint2 pt2, CPoint3 pt3, double Height, COLORREF color, double v_scale, double g_scale);
void AddPolyLine(MyAcad & m_acad, vector<CPoint2> & vpt2, bool to_close, COLORREF color, double v_scale, double g_scale);
void AddPolyLine(MyAcad & m_acad, short export_coordinate_type, vector<CPoint3> & vpt3, bool to_close, COLORREF color, double v_scale, double g_scale);
void AddPolyLine(MyAcad & m_acad, vector<CPoint2> & vpt2, vector<CPoint3> & vpt3, bool to_close, COLORREF color, double v_scale, double g_scale);
void AddHatchPolyLine(MyAcad & m_acad, vector<CPoint2> & vpt2, COLORREF color, string hatchacad, double angle, double scale, double v_scale, double g_scale);
void AddHatchPolyLine(MyAcad & m_acad, short export_coordinate_type, vector<CPoint3> & vpt3, COLORREF color, string hatchacad, double angle, double scale, double v_scale, double g_scale);




Well_Laboratory_Analize::label_type Well_Laboratory_Analize::s_label_type = Well_Laboratory_Analize::label_type::lab_number_id;

CString GetIGEName(CDatabase * database, long id_obj, long id_ige);

WellColomn::WellColomn()
{
	this->Init();
}
WellColomn::~WellColomn()
{

}

WellColomn::WellColomn(WellElement::type t, Well_3D * well, wells_draw_list_item * wdli)
{
	this->Init(); 
	w_type = t; 
	m_pWell = well; 
	this->InitDoc(well ? (SurfDoc*)well->GetDoc() : NULL); 
	m_wdli = wdli;
	if (wdli) m_wdli_id = wdli->id; else m_wdli_id = -1;

}

void WellColomn::Init()
{
//	m_nglListNumber = 0;

//	this->m_object_type = Object::object_type::well_colomn;
//	this->m_object_version = 1;
//	this->m_max_object_version = 1;

	well_colomn_version = 2;

	w_type = WellElement::type::undefined_well_element;
	m_pWell = NULL;
	m_pSurfDoc = NULL;
	m_wdli = NULL;
	m_wdli_id = -1;
}
WellElement::WellElement()
{
	m_nglListNumber = 0;
}
WellElement::~WellElement()
{
	if (m_nglListNumber > 0)
	{
		::glDeleteLists(m_nglListNumber,1);
	}
	m_nglListNumber = 0;

}
#define BASE_WELLELEMENT_VERSION 3
void WellElement::Init()
{
	this->nameID = "";
	this->well_colomn = NULL;

	m_base_wellelement_version = BASE_WELLELEMENT_VERSION;
	m_this_wellelement_version = 1;

	this->w_type = WellElement::type::undefined_well_element;

}
void WellElement::Draw(Well_3D * well)
{
	m_nglListNumber = DrawListArray::glNewList();
	Drawing(well);
	glEndList();
}
void WellElement::ReDraw(Well_3D * well)
{
//	if(this->m_pSurfDoc) this->ReDrawItem_OnTree(this->m_pSurfDoc->hwndTV);

	if (m_nglListNumber > 0)
	{
		::glDeleteLists(m_nglListNumber,1);
		::glNewList(m_nglListNumber, GL_COMPILE);
	}
	else
		m_nglListNumber = DrawListArray::glNewList();

	Drawing(well);
	glEndList();
}
void WellElement::OnPaint()
{
	if (m_nglListNumber > 0)
	{
		::glCallList(m_nglListNumber);
	}
}
#define LITHO_PODOSHVA_WELLELEMENT_VERSION 2
Well_Litho_Podoshva::Well_Litho_Podoshva()
{
	this->WellElement::Init();
	key = "";
	id_ige = -1;
	color = RGB(255,255,255);

	this->w_type = WellElement::type::litho_podoshva;
	m_this_wellelement_version = LITHO_PODOSHVA_WELLELEMENT_VERSION;

	id_umpoz = 0;
	umpoz = "";
	hatchacad = "";
	angle = 0.0;
	scale = 0.0;
}

Well_Litho_Podoshva::~Well_Litho_Podoshva()
{
}

void Well_Litho_Podoshva::PrintfProperties()
{
	printf("Well_Litho_Podoshva ID = \"%s\" \tzk = %f\tzp = %f\tcolor = [%d %d %d]\tkey = \"%s\"\n", 
		this->nameID.c_str(), 
		this->zk, 
		this->zp, 
		GetRValue(this->color),
		GetGValue(this->color),
		GetBValue(this->color),
		this->key.c_str());
}

void Well_Litho_Podoshva::PrintfProperties(vector<fmtstr> & text)
{
	char str[4098];

	sprintf(str, "Well_Litho_Podoshva ID");
	text.push_back(fmtstr(str, NULL, false, true));
	sprintf(str, "\"%s\"", this->nameID.c_str());
	text.push_back(fmtstr(str, NULL, true, true));

	sprintf(str, "zk");
	text.push_back(fmtstr(str, NULL, false, true));
	sprintf(str, "%f", this->zk);
	text.push_back(fmtstr(str, NULL, true, true));

	sprintf(str, "zp");
	text.push_back(fmtstr(str, NULL, false, true));
	sprintf(str, "%f", this->zp);
	text.push_back(fmtstr(str, NULL, true, true));

	sprintf(str, "color");
	text.push_back(fmtstr(str, NULL, false, true));
	sprintf(str, "[%d %d %d]", 
		GetRValue(this->color),
		GetGValue(this->color),
		GetBValue(this->color));
	text.push_back(fmtstr(str, NULL, true, true));

	sprintf(str, "key");
	text.push_back(fmtstr(str, NULL, false, true));
	sprintf(str, "\"%s\"", this->key.c_str());
	text.push_back(fmtstr(str, NULL, true, true));


}
#define IGE_PODOSHVA_WELLELEMENT_VERSION 2
Well_IGE_Podoshva::Well_IGE_Podoshva()
{
	this->WellElement::Init();
	key = "";
	id_ige = -1;
	color = RGB(255,255,255);

	this->w_type = WellElement::type::IGE_podoshva;
	m_this_wellelement_version = IGE_PODOSHVA_WELLELEMENT_VERSION;

	id_umpoz = 0;
	umpoz = "";
	hatchacad = "";
	angle = 0.0;
	scale = 0.0;
}

Well_IGE_Podoshva::~Well_IGE_Podoshva()
{
}

void Well_IGE_Podoshva::PrintfProperties()
{
	printf("Well_IGE_Podoshva ID = \"%s\" \tzk = %f\tzp = %f\tcolor = [%d %d %d]\tkey = \"%s\"\n", 
		this->nameID.c_str(), 
		this->zk, 
		this->zp, 
		GetRValue(this->color),
		GetGValue(this->color),
		GetBValue(this->color),
		this->key.c_str());
}

void Well_IGE_Podoshva::PrintfProperties(vector<fmtstr> & text)
{
	char str[4098];

	sprintf(str, "Well_IGE_Podoshva ID");
	text.push_back(fmtstr(str, NULL, false, true));
	sprintf(str, "\"%s\"", this->nameID.c_str());
	text.push_back(fmtstr(str, NULL, true, true));

	sprintf(str, "zk");
	text.push_back(fmtstr(str, NULL, false, true));
	sprintf(str, "%f", this->zk);
	text.push_back(fmtstr(str, NULL, true, true));

	sprintf(str, "zp");
	text.push_back(fmtstr(str, NULL, false, true));
	sprintf(str, "%f", this->zp);
	text.push_back(fmtstr(str, NULL, true, true));


	sprintf(str, "color");
	text.push_back(fmtstr(str, NULL, false, true));
	sprintf(str, "[%d %d %d]", 
		GetRValue(this->color),
		GetGValue(this->color),
		GetBValue(this->color));
	text.push_back(fmtstr(str, NULL, true, true));

	sprintf(str, "key");
	text.push_back(fmtstr(str, NULL, false, true));
	sprintf(str, "\"%s\"", this->key.c_str());
	text.push_back(fmtstr(str, NULL, true, true));

}

Well_IsSand_Podoshva::Well_IsSand_Podoshva()
{
	this->WellElement::Init();
	zk = 0.0;//альтитуда кровли 
	zp = 0.0;//альтитуда подошвы 
	isSand = 0;// песок или пылеватоглинистый грунт

	this->w_type = WellElement::type::isSand_podoshva;
	m_this_wellelement_version = 1;
}

Well_IsSand_Podoshva::~Well_IsSand_Podoshva()
{
}

void Well_IsSand_Podoshva::PrintfProperties()
{
	printf("Well_IsSand_Podoshva ID = \"%s\" \tzp = %f\tisSand = \"%d\"\n", 
		this->nameID.c_str(), 
		this->zp, 
		this->isSand);
}

void Well_IsSand_Podoshva::PrintfProperties(vector<fmtstr> & text)
{
	char str[4098];

	sprintf(str, "Well_IsSand_Podoshva ID");
	text.push_back(fmtstr(str, NULL, false, true));
	sprintf(str, "\"%s\"", this->nameID.c_str());
	text.push_back(fmtstr(str, NULL, true, true));

	sprintf(str, "zp");
	text.push_back(fmtstr(str, NULL, false, true));
	sprintf(str, "%f", this->zp);
	text.push_back(fmtstr(str, NULL, true, true));


	sprintf(str, "isSand");
	text.push_back(fmtstr(str, NULL, false, true));
	sprintf(str, "%d", this->isSand);
	text.push_back(fmtstr(str, NULL, true, true));
}

Well_Hydro_Projavlenie::Well_Hydro_Projavlenie()
{
	this->WellElement::Init();
	zp = 0.0;//альтитуда гидропроявления 
	ustanovlen = 0;// установившийся ли уровень

	this->w_type = WellElement::type::hydro_projavlenie;
	m_this_wellelement_version = 1;
}

Well_Hydro_Projavlenie::~Well_Hydro_Projavlenie()
{
}

void Well_Hydro_Projavlenie::PrintfProperties()
{
	printf("Well_Hydro_Projavlenie ID = \"%s\" \tz = %f\tustanovlen = \"%d\"\n", 
		this->nameID.c_str(), 
		this->zp, 
		this->ustanovlen);
}


void Well_Hydro_Projavlenie::PrintfProperties(vector<fmtstr> & text)
{
	char str[4098];

	sprintf(str, "Well_Hydro_Projavlenie ID");
	text.push_back(fmtstr(str, NULL, false, true));
	sprintf(str, "\"%s\"", this->nameID.c_str());
	text.push_back(fmtstr(str, NULL, true, true));

	sprintf(str, "z");
	text.push_back(fmtstr(str, NULL, false, true));
	sprintf(str, "%f", this->zp);
	text.push_back(fmtstr(str, NULL, true, true));

	sprintf(str, "ustanovlen");
	text.push_back(fmtstr(str, NULL, false, true));
	sprintf(str, "%d", this->ustanovlen);
	text.push_back(fmtstr(str, NULL, true, true));
}

Well_Laboratory_Analize::Well_Laboratory_Analize()
{
	this->WellElement::Init();
	zp = 0.0;//альтитуда
	lab_number = NULL;

	this->w_type = WellElement::type::laboratory_analizes;
	m_this_wellelement_version = 1;
}

Well_Laboratory_Analize::~Well_Laboratory_Analize()
{
}


void Well_Laboratory_Analize::InitByLabNumber(LabNumber * ln, double ustje_z)
{
	this->lab_number = ln;
	if (this->lab_number)
	{
		this->zp = ustje_z - this->lab_number->depth;

		this->Lab_Layer_ID = this->lab_number->GetLabLayer() ? this->lab_number->GetLabLayer()->ID : "" ;
		this->Lab_Layer_Number = this->lab_number->GetLabLayer() ? this->lab_number->GetLabLayer()->layer_number : "" ;

		this->Lab_Number_ID = this->lab_number->ID;

	}
}
void Well_Laboratory_Analize::ReInitByOwnLabNumber()
{
	if (this->lab_number)
	{
		this->Lab_Layer_ID = this->lab_number->GetLabLayer() ? this->lab_number->GetLabLayer()->ID : "" ;
		this->Lab_Layer_Number = this->lab_number->GetLabLayer() ? this->lab_number->GetLabLayer()->layer_number : "" ;
		this->Lab_Number_ID = this->lab_number->ID;
	}
}
bool Well_Laboratory_Analize::LabLayerCheckDraw()
{
	if (this->lab_number && this->lab_number->GetLabLayer())
		return this->lab_number->GetLabLayer()->check_draw;
	return false;
}

void Well_Laboratory_Analize::PrintfProperties()
{
	printf("Well_Laboratory_Analize ID = \"%s\" \tz = %f\n", 
		this->nameID.c_str(), 
		this->zp);

	printf("Lab_Layer_ID = %s\n", Lab_Layer_ID.c_str());
	printf("Lab_Layer_Number = %s\n", Lab_Layer_Number.c_str());
	printf("Lab_Number_ID = %s\n", Lab_Number_ID.c_str());

	if(this->lab_number)
	{
		this->lab_number->PrintfProperties();
	}
}
void Well_Laboratory_Analize::Properties()
{
	if(this->lab_number)
	{
		this->lab_number->Properties();
	}
}
void Well_Laboratory_Analize::PrintfProperties(vector<LabData> & labdata)
{
	labdata.push_back(LabData());

	char str[4098];

//	sprintf(str, "Элемент лабораторной колонки ID = \"%s\"   z = %f", 
//		this->nameID.c_str(), 
//		this->z);
//	while (str[strlen(str)-1] == '0')
//		str[strlen(str)-1] = '\0';
//	if (str[strlen(str)-1] == '.')
//		str[strlen(str)-1] = '\0';
//	labdata.back().text.push_back(str);

//	sprintf(str, "Идент. номер лаб. слоя %s", Lab_Layer_ID.c_str());
//	labdata.back().text.push_back(str);

	sprintf(str, "Номер лаб. слоя %s", Lab_Layer_Number.c_str());
	labdata.back().text.push_back(fmtstr(str, NULL, true, false));

//	sprintf(str, "ID лабораторного номера %s", Lab_Number_ID.c_str());
//	labdata.back().text.push_back(str);

	if(this->lab_number)
	{
		this->lab_number->PrintfProperties(labdata);
	}
}
void Well_Laboratory_Analize::PrintfProperties(vector<fmtstr> & text)
{
	char str[4098];

//	sprintf(str, "Элемент лабораторной колонки ID = \"%s\"   z = %f", 
//		this->nameID.c_str(), 
//		this->z);
//	while (str[strlen(str)-1] == '0')
//		str[strlen(str)-1] = '\0';
//	if (str[strlen(str)-1] == '.')
//		str[strlen(str)-1] = '\0';
//	text.push_back(str);

//	sprintf(str, "Идент. номер лаб. слоя %s", Lab_Layer_ID.c_str());
//	text.push_back(str);

	sprintf(str, "Номер лаб. слоя %s", Lab_Layer_Number.c_str());
	text.push_back(fmtstr(str, NULL, true, false));

//	sprintf(str, "ID лабораторного номера %s", Lab_Number_ID.c_str());
//	text.push_back(str);

	if(this->lab_number)
	{
		this->lab_number->PrintfProperties(text);
	}
}



void Well_Laboratory_Analize::SetSizeAndPosOfContextWindow(HWND hWnd, int CX, int CY)
{
	int shift = 1;

	HWND hWndParent = ::GetParent(hWnd);
	RECT rectParentClient;
	GetClientRect(hWndParent, &rectParentClient);
	
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWndParent, &pt);


	if (pt.x + CX + shift > rectParentClient.right)
	{
		if (pt.x - CX - shift > rectParentClient.left + shift/2)
			pt.x -= CX + shift;
		else
			pt.x = rectParentClient.left + shift/2;
	}
	else
	{
		pt.x += shift;
	}

	if (pt.y + CY + shift > rectParentClient.bottom)
	{
		if (pt.y - CY - shift > rectParentClient.top+shift/2)
		{
			pt.y -= CY + shift;
		}
		else
			pt.y = rectParentClient.top+shift/2;
	}
	else
	{
		pt.y += shift;
	}
	SetWindowPos(hWnd, HWND_TOP, 0,0, CX, CY, SWP_NOMOVE);
	ClientToScreen(hWndParent, &pt);
	SetWindowPos(hWnd, HWND_TOP, pt.x, pt.y, 0, 0, SWP_NOSIZE);
}



void Well_Laboratory_Analize::PropSave(bool context_with_plot)
{
	TCHAR filter[] =
						TEXT("Metafiles (*.emf)\0*.emf\0")
						TEXT("All Files (*.*)\0*.*\0");
	char fn_emf[4098];

	char s[128];
	sprintf(s, "%s\0", this->Lab_Layer_Number.c_str());
#if !CHAR_LAYER_NUMBER_ID
	OemToChar(s,s);
#endif

	switch (context_with_plot)
	{
	case false:
		sprintf(fn_emf, "lab_layer_%s_number_%s\0", s, this->Lab_Number_ID.c_str());
		break;
	case true:
		sprintf(fn_emf, "lab_layer_%s_number_%s_plot\0", s, this->Lab_Number_ID.c_str());
		break;
	}
	char * p = NULL;
	while (p = strchr(fn_emf, '*'))
		*p = 'x';

	DWORD nFilterIndex = 0;
	if (S_OK == SaveFileDlg(NULL, fn_emf, filter, nFilterIndex))
	{
		switch (nFilterIndex)
		{
		case 1:
			this->PropSaveEmf(context_with_plot, fn_emf);
			break;
		}			
	}
}

void Well_Laboratory_Analize::Passport()
{
	TCHAR filter[] =
						TEXT("Excel files (*.xls)\0*.xls\0")
						TEXT("All Files (*.*)\0*.*\0");
	char fn_xls[4098];

	char s[128];
	sprintf(s, "%s\0", this->Lab_Layer_Number.c_str());
#if !CHAR_LAYER_NUMBER_ID
	OemToChar(s,s);
#endif


		sprintf(fn_xls, "lab_layer_%s_number_%s\0", s, this->Lab_Number_ID.c_str());

	char * p = NULL;
	while (p = strchr(fn_xls, '*'))
		*p = 'x';

	DWORD nFilterIndex = 0;
	if (S_OK == SaveFileDlg(NULL, fn_xls, filter, nFilterIndex))
	{
		switch (nFilterIndex)
		{
		case 1:
			this->Passport(fn_xls);
			break;
		}			
	}
}

void Well_Laboratory_Analize::Passport(const char * fn)
{
	if(this->lab_number)
	{
		this->lab_number->Passport(fn);
	}
}

void Well_Laboratory_Analize::CreateMyPopupMenu(HWND hWnd)
{
	HMENU hMenu = CreatePopupMenu();
	HMENU hSubMenu = NULL;
	HMENU hSubMenu2 = NULL;
	Well_Laboratory_Analize::FillPopupMenu(hMenu, hSubMenu, hSubMenu2);

	POINT point;
	GetCursorPos(&point);
	
	TrackPopupMenu( hMenu, TPM_RIGHTBUTTON | 
		TPM_TOPALIGN |
		TPM_LEFTALIGN, 
		point.x,
		point.y, 0, hWnd, NULL );
	
	DestroyMenu( hMenu );
	if(hSubMenu)
		DestroyMenu( hSubMenu );
	if(hSubMenu2)
		DestroyMenu( hSubMenu2 );
}
void FillPopupSubMenu2(HMENU & hMenu)
{
	MENUITEMINFO   mii;				
	mii.cbSize = sizeof( MENUITEMINFO );

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	mii.fMask  = MIIM_ID | MIIM_TYPE;
	mii.fType  = MFT_STRING;
	mii.wID    = ID_TREE_LAB_WELLELEMENTCONTEXTFONT_PLOT_TITLE;
	mii.dwTypeData = "Title";
	InsertMenuItem( hMenu, SC_MAXIMIZE, FALSE, &mii );
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	mii.fMask  = MIIM_ID | MIIM_TYPE;
	mii.fType  = MFT_STRING;
	mii.wID    = ID_TREE_LAB_WELLELEMENTCONTEXTFONT_PLOT_XLABEL;
	mii.dwTypeData = "X Label";
	InsertMenuItem( hMenu, SC_MAXIMIZE, FALSE, &mii );
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	mii.fMask  = MIIM_ID | MIIM_TYPE;
	mii.fType  = MFT_STRING;
	mii.wID    = ID_TREE_LAB_WELLELEMENTCONTEXTFONT_PLOT_YLABEL;
	mii.dwTypeData = "Y Label";
	InsertMenuItem( hMenu, SC_MAXIMIZE, FALSE, &mii );
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	mii.fMask  = MIIM_ID | MIIM_TYPE;
	mii.fType  = MFT_STRING;
	mii.wID    = ID_TREE_LAB_WELLELEMENTCONTEXTFONT_PLOT_XAXES;
	mii.dwTypeData = "X Axes";
	InsertMenuItem( hMenu, SC_MAXIMIZE, FALSE, &mii );
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	mii.fMask  = MIIM_ID | MIIM_TYPE;
	mii.fType  = MFT_STRING;
	mii.wID    = ID_TREE_LAB_WELLELEMENTCONTEXTFONT_PLOT_YAXES;
	mii.dwTypeData = "Y Axes";
	InsertMenuItem( hMenu, SC_MAXIMIZE, FALSE, &mii );
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


}
void FillPopupSubMenu(HMENU & hMenu, HMENU & hSubMenu2)
{
	MENUITEMINFO   mii;				
	mii.cbSize = sizeof( MENUITEMINFO );
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	/*//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	mii.fMask  = MIIM_ID | MIIM_TYPE;
	mii.fType  = MFT_STRING;
	mii.wID    = ID_TREE_LAB_WELLELEMENTCONTEXTFONT;
	mii.dwTypeData = "На графиках";
	InsertMenuItem( hMenu, SC_MAXIMIZE, FALSE, &mii );
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	mii.fMask  = MIIM_ID | MIIM_TYPE;
	mii.fType  = MFT_STRING;
	mii.wID    = ID_TREE_LAB_WELLELEMENTCONTEXTFONT0;
	mii.dwTypeData = "Названия";
	InsertMenuItem( hMenu, SC_MAXIMIZE, FALSE, &mii );
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	mii.fMask  = MIIM_ID | MIIM_TYPE;
	mii.fType  = MFT_STRING;
	mii.wID    = ID_TREE_LAB_WELLELEMENTCONTEXTFONT1;
	mii.dwTypeData = "Значения неисключённые";
	InsertMenuItem( hMenu, SC_MAXIMIZE, FALSE, &mii );
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	mii.fMask  = MIIM_ID | MIIM_TYPE;
	mii.fType  = MFT_STRING;
	mii.wID    = ID_TREE_LAB_WELLELEMENTCONTEXTFONT2;
	mii.dwTypeData = "Значения исключённые, но включённые оператором";
	InsertMenuItem( hMenu, SC_MAXIMIZE, FALSE, &mii );
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	mii.fMask  = MIIM_ID | MIIM_TYPE;
	mii.fType  = MFT_STRING;
	mii.wID    = ID_TREE_LAB_WELLELEMENTCONTEXTFONT3;
	mii.dwTypeData = "Значения исключённые";
	InsertMenuItem( hMenu, SC_MAXIMIZE, FALSE, &mii );
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	
	hSubMenu2 = CreatePopupMenu();
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	mii.fMask  = MIIM_TYPE | MIIM_SUBMENU;
	mii.fType  = MFT_STRING;
	mii.wID    = ID_TREE_LAB_WELLELEMENTCONTEXTFONT;
	mii.hSubMenu = hSubMenu2;
	mii.dwTypeData = "На графиках";
	InsertMenuItem( hMenu, SC_MAXIMIZE, FALSE, &mii );
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	FillPopupSubMenu2(hSubMenu2);
}
void Well_Laboratory_Analize::FillPopupMenu(HMENU & hMenu, HMENU & hSubMenu, HMENU & hSubMenu2)
{
	MENUITEMINFO   mii;				
	mii.cbSize = sizeof( MENUITEMINFO );
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	mii.fMask  = MIIM_ID | MIIM_TYPE;
	mii.fType  = MFT_STRING;
	mii.wID    = ID_TREE_LAB_WELLELEMENTPROP;
	mii.dwTypeData = "&Lab prop";
	InsertMenuItem( hMenu, SC_MAXIMIZE, FALSE, &mii );
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	mii.fMask  = MIIM_ID | MIIM_TYPE;
	mii.fType  = MFT_STRING;
	mii.wID    = ID_TREE_LAB_WELLELEMENTPROPSAVE;
	mii.dwTypeData = "Сохранить лабораторные свойства";
	InsertMenuItem( hMenu, SC_MAXIMIZE, FALSE, &mii );
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	mii.fMask  = MIIM_ID | MIIM_TYPE;
	mii.fType  = MFT_STRING;
	mii.wID    = ID_TREE_LAB_PASSPORT;
	mii.dwTypeData = "Паспорт";
	InsertMenuItem( hMenu, SC_MAXIMIZE, FALSE, &mii );
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	hSubMenu = CreatePopupMenu();
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	mii.fMask  = MIIM_TYPE | MIIM_SUBMENU;
	mii.fType  = MFT_STRING;
	mii.wID    = ID_TREE_LAB_WELLELEMENTCONTEXTFONT;
	mii.hSubMenu = hSubMenu;
	mii.dwTypeData = "Шрифты лабораторных свойств";
	InsertMenuItem( hMenu, SC_MAXIMIZE, FALSE, &mii );
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	FillPopupSubMenu(hSubMenu, hSubMenu2);

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	mii.fMask  = MIIM_ID | MIIM_TYPE;
	mii.fType  = MFT_STRING;
	mii.wID    = ID_TREE_LAB_WELLELEMENTCONTEXTPLOTHEIGHT;
	mii.dwTypeData = "Высота графиков лабораторных свойств";
	InsertMenuItem( hMenu, SC_MAXIMIZE, FALSE, &mii );
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	mii.fMask  = MIIM_ID | MIIM_TYPE;
	mii.fType  = MFT_STRING;
	mii.wID    = ID_TREE_LAB_LABLAYER_COMPRESSION_PRESSURE_INTERVAL;
	mii.dwTypeData = "Интервал давлений для вычисления компрессионного модуля";
	InsertMenuItem( hMenu, SC_MAXIMIZE, FALSE, &mii );
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	mii.fMask  = MIIM_ID | MIIM_TYPE;
	mii.fType  = MFT_STRING;
	mii.wID    = ID_TREE_LAB_LABLAYER_COMPRESSION_PRESSURE;
	mii.dwTypeData = "Давление для вычисления модуля деформации";
	InsertMenuItem( hMenu, SC_MAXIMIZE, FALSE, &mii );
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	mii.fMask  = MIIM_ID | MIIM_TYPE;
	mii.fType  = MFT_STRING;
	mii.wID    = ID_TREE_LAB_GURVICH_Y_SECOND_DERIVATIVE_LIMIT;
	mii.dwTypeData = "Предел второй производной кривой осадки после замачивания";
	InsertMenuItem( hMenu, SC_MAXIMIZE, FALSE, &mii );
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	mii.fMask  = MIIM_ID | MIIM_TYPE;
	mii.fType  = MFT_STRING;
	mii.wID    = ID_TREE_LAB_E_SECOND_DERIVATIVE_LIMIT;
	mii.dwTypeData = "Предел второй производной компрессионной кривой";
	InsertMenuItem( hMenu, SC_MAXIMIZE, FALSE, &mii );
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	mii.fMask  = MIIM_ID | MIIM_TYPE;
	mii.fType  = MFT_STRING;
	mii.wID    = ID_TREE_LAB_WATERSATURATEDPARTOFFULLWATERCAPACITY;
	mii.dwTypeData = "Степень влажности водонасыщенного грунта";
	InsertMenuItem( hMenu, SC_MAXIMIZE, FALSE, &mii );
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
}
const char * WellElement::WellElementTypeToString(WellElement::type t)
{
	switch (t)
	{
	case undefined_well_element:
		return "undefined";
	case primitive_ref:
		return "primitive_ref";
	case litho_podoshva:
		return "litho_podoshva";
	case IGE_podoshva:
		return "IGE_podoshva";
	case isSand_podoshva:
		return "isSand_podoshva";
	case hydro_projavlenie:
		return "hydro_projavlenie";
	case laboratory_analizes:
		return "laboratory_analizes";
	default:
		return "";
	}
	return "";
}

void * WellElement::operator new  (size_t size, WellElement::type t)
{
	//printf("WellElement::operator new (size_t size = %d, WellElement::type(%d) = %s\n", size, int(t), WellElement::WellElementTypeToString(t));

	switch (t)
	{
	case undefined_well_element:
		return NULL;
	case litho_podoshva:
		return reinterpret_cast<void*>(new Well_Litho_Podoshva);
	case IGE_podoshva:
		return reinterpret_cast<void*>(new Well_IGE_Podoshva);
	case isSand_podoshva:
		return reinterpret_cast<void*>(new Well_IsSand_Podoshva);
	case hydro_projavlenie:
		return reinterpret_cast<void*>(new Well_Hydro_Projavlenie);
	case laboratory_analizes:
		return reinterpret_cast<void*>(new Well_Laboratory_Analize);
	default:
		return NULL;
	}
	return NULL;
}

void WellElement::operator delete(void * p, WellElement::type t)
{
	switch (t)
	{
	case undefined_well_element:
		return;
	case litho_podoshva:
		::operator delete(reinterpret_cast<Well_Litho_Podoshva*>(p));
		break;
	case IGE_podoshva:
		::operator delete(reinterpret_cast<Well_IGE_Podoshva*>(p));
		break;
	case isSand_podoshva:
		::operator delete(reinterpret_cast<Well_IsSand_Podoshva*>(p));
		break;
	case hydro_projavlenie:
		::operator delete(reinterpret_cast<Well_Hydro_Projavlenie*>(p));
		break;
	case laboratory_analizes:
		::operator delete(reinterpret_cast<Well_Laboratory_Analize*>(p));
		break;
	default:
		return;
	}
}
WellColomn::WellColomn(const WellColomn& ob)
{
	this->Init(ob);
}

WellColomn& WellColomn::operator=(const WellColomn& ob)
{
	if (this == &ob)
		return *this;

	this->Init(ob);

	return *this;
}

WellElement * WellColomn::CreateNewWellElement(WellElement::type t)
{
	return (WellElement*)WellElement::operator new (sizeof(WellElement),t);
}
bool WellColomn::IsWellElement(const WellElement * p1)
{
	for (vector<WellElement*>::iterator it = this->well_elements.begin();
		it != this->well_elements.end(); it++)
	{
		if ((*it) == p1)
		{
			return true;
		}
	}
	return false;
}
WellElement * WellColomn::FindWellElement(string ID)
{
	for (vector<WellElement*>::iterator it = this->well_elements.begin();
		it != this->well_elements.end(); it++)
	{
		if ((*it) && ID == (*it)->nameID)
		{
			return (*it);
		}
	}
	return NULL;
}
WellElement * WellColomn::AddNewWellElement(string ID, WellElement * well_element)
{
	//if(this->FindWellElement(ID) != NULL)
	//	return NULL;

	this->well_elements.push_back(well_element);	
	this->well_elements.back()->SetNameID(ID);
	this->well_elements.back()->SetWellColomn(this);
	return this->well_elements.back();
}
WellElement * WellColomn::AddNewWellElement(string ID)
{
	WellElement * well_element = this->CreateNewWellElement(this->w_type);
printf("WellElement * %x WellColomn::AddNewWellElement(string ID %s) this->w_type %d \n", well_element, ID.c_str(), (int)this->w_type);
	if (well_element) 
	{
		this->AddNewWellElement(ID, well_element);
//		this->ReDrawItem_OnTree(this->m_pSurfDoc ? this->m_pSurfDoc->hwndTV : NULL);
	}
	return well_element;
}
void LithoWellElement::Init()
{
}
void WellColomn::PropertiesDialog()
{
}
void WellColomn::PrintfProperties(vector<fmtstr> & text)
{
	char str[4098];

	sprintf(str, "WellColomn of %d well elements  type", this->well_elements.size());
	text.push_back(fmtstr(str, NULL, false, true));
	sprintf(str, "\"%s\"", WellElement::WellElementTypeToString(this->w_type));
	text.push_back(fmtstr(str, NULL, true, true));
	
	for (vector<WellElement*>::iterator it = this->well_elements.begin();
		it != this->well_elements.end(); it++)
	{
		if ((*it))
		{
			(*it)->PrintfProperties(text);
		}		
	}
}
void WellColomn::PrintfProperties()
{
	printf("WellColomn::PrintfProperties() type = %s\n", WellElement::WellElementTypeToString(this->w_type));
	
	for (vector<WellElement*>::iterator it = this->well_elements.begin();
		it != this->well_elements.end(); it++)
	{
		if ((*it))
		{
			(*it)->PrintfProperties();
		}		
	}
}

HTREEITEM WellColomn::AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s)
{
    char szItemText[1024]; // label text of tree-view item 
	//====== Тип изображаемого объекта

	sprintf(szItemText, "WellColomn of type %d",int(this->w_type) );
	Object * pObject = dynamic_cast<Object *> (this);
	//=============================================================
	// Add the item to the tree-view control. 
	HTREEITEM h2 = AddItemToTree(hwndTV, szItemText, pObject, h1); 
	//=============================================================
	return h2;
}

void FillRectWithImage(Graphics& graphics, Image &image, RectF &rectf)
{
	RectF image_rect;
	Unit image_Unit;
	image.GetBounds(&image_rect, &image_Unit);

	image_rect.X;
	image_rect.Y;
	image_rect.Width;
	image_rect.Height;
	
	// Set up the location for the image and the portion of the source to draw.
#if 0
	Unit srcunit = UnitPixel;
#else
	Unit srcunit = image_Unit;
#endif

	int rows = int(ceil(rectf.Width/image_rect.Width));
	int cols = int(ceil(rectf.Height/image_rect.Height));

	REAL srcx = 0;
	REAL srcy = 0;

	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			// Draw the image.
			REAL x0 = rectf.X + r * image_rect.Width;
			REAL y0 = rectf.Y + c * image_rect.Height;

			REAL srcwidth = rectf.Width - r * image_rect.Width;
			REAL srcheight = rectf.Height - c * image_rect.Height;

			graphics.DrawImage(&image, x0, y0, srcx, srcy, srcwidth, srcheight, srcunit);
		}
	}	
}

#if !WELL_ELEMENT_DRAW_GDI_PLUS
void WellColomn::DrawGDIplus_Litho(Graphics ** select_buffer, Graphics& graphics, map_view * v, Profile3D * on, Well_3D * well, wells_draw_list_item * wdli)
{
	float width = wdli ? wdli->draw_width : 2.0;
//printf("WellColomn::DrawGDIplus_IGE well = %s\n", well->GetIDString());
	double dist_to_plane;
	CPoint2 profile;

	fGL x1; fGL y1;
	fGL x2; fGL y2;

	fGL r = v->lines_points_radius;

	double z_pre;
	CPoint3 ustje, pt;
	if (well->GetUstje(ustje))
	{
		//printf("WellColomn::DrawGDIplus_IGE well->GetUstje() this->well_elements.size() = %u\n", this->well_elements.size());
		z_pre = ustje.z;
		pt = ustje;
		for (vector<WellElement*>::iterator it = this->well_elements.begin();
			it != this->well_elements.end(); it++)
		{
//printf("WellColomn::DrawGDIplus_IGE for\n");
			if ((*it))
			{
//printf("WellColomn::DrawGDIplus_IGE if\n");
				Well_Litho_Podoshva * wegep = dynamic_cast<Well_Litho_Podoshva *>((*it));
				if (wegep)
				{
					//wegep->key;
					COLORREF color = wegep->GetColor();
					//printf("z_pre = %f wegep->GetZ() = %f color = %d\n", z_pre, wegep->GetZ(), color);

					Color gdi_color(this->m_pSurfDoc->m_alpha_gdiplus_profiles, GetRValue(color),GetGValue(color),GetBValue(color));


					//Convert3D_To_2D
					pt.z = z_pre;
					on->Projection(pt, profile, dist_to_plane);
					v->ConvertingFromWorldToScreen(profile.x, profile.y, x1, y1);

					//Convert3D_To_2D
					pt.z = wegep->GetZp();
					on->Projection(pt, profile, dist_to_plane);
					v->ConvertingFromWorldToScreen(profile.x, profile.y, x2, y2);

					Pen   pen(gdi_color);

					double x_sloj_name = x2;
						
					if (!wdli)
					{
						pen.SetWidth(width);
						graphics.DrawLine(&pen, x1, y1, x2, y2);
						x_sloj_name = x2;
					}
					else
					{
						string fn = string("C:\\Laboratory\\Img\\") + wegep->umpoz;

						const int wlen = 2 + 2 * (int)strlen(fn.c_str());
						WCHAR * wfn = new WCHAR[wlen];
						MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, fn.c_str(), -1, wfn, wlen );
						Image image(wfn);
						delete wfn;



						Color border_color(255, GetRValue(wdli->border_color),GetGValue(wdli->border_color),GetBValue(wdli->border_color));
						Pen   pen_border(border_color);
						switch(wdli->m_draw_mode_2d)
						{
						case wells_draw_list_item::left:
							{
								RectF rectf(x1-0.5*width, y1, 0.5*width, (y2-y1));
								FillRectWithImage(graphics, image, rectf);

								pen.SetWidth(0.5*width);	
								graphics.DrawLine(&pen, x1-0.25*width, y1, x2-0.25*width, y2);	
								if(wdli->draw2d_border)
								{
									graphics.DrawLine(&pen_border, x1-0.5*width, y1, x2-0.5*width, y2);	
									graphics.DrawLine(&pen_border, x1-0.5*width, y1, x1, y1);	
								}
								x_sloj_name = x2-width
									// TODO temporary decision while font is not used									
									-0.5*width;
							}
							break;
						case wells_draw_list_item::draw_mode_2d::right:
							{
								RectF rectf(x1, y1, 0.5*width, (y2-y1));
								FillRectWithImage(graphics, image, rectf);

								pen.SetWidth(0.5*width);	
								graphics.DrawLine(&pen, x1+0.25*width, y1, x2+0.25*width, y2);	
								if(wdli->draw2d_border)
								{
									graphics.DrawLine(&pen_border, x1+0.5*width, y1, x2+0.5*width, y2);	
									graphics.DrawLine(&pen_border, x1+0.5*width, y1, x1, y1);	
								}
								x_sloj_name = x2+0.5*width;
							}
							break;
						case wells_draw_list_item::draw_mode_2d::both:
							{
								RectF rectf(x1-0.5*width, y1, width, (y2-y1));
								FillRectWithImage(graphics, image, rectf);


								pen.SetWidth(width);	
								graphics.DrawLine(&pen, x1, y1, x2, y2);	
								if(wdli->draw2d_border)
								{
									graphics.DrawLine(&pen_border, x1-0.5*width, y1, x2-0.5*width, y2);	
									graphics.DrawLine(&pen_border, x1+0.5*width, y1, x2+0.5*width, y2);	
									graphics.DrawLine(&pen_border, x1+0.5*width, y1, x1-0.5*width, y1);	
								}
								x_sloj_name = x2+0.5*width;
							}
							break;
						}
					}



					if (//i_sphere == Well_3D::s_sloj_number_to_save || 
						Well_3D::s_show_all_sloi)// или если показываем все слои
					{
						//отметим слой для сохранения в виде шариков

						COLORREF sphereColor = color;
						Color sphere_color(255, GetRValue(sphereColor),GetGValue(sphereColor),GetBValue(sphereColor));
						Pen      sphere_pen(gdi_color);								

						FillCircle(&graphics, x2, y2, r, sphere_color);							
						DrawCircle(&graphics, x2, y2, r, Color(255, 0,0,0));							
					}

					if (Well_3D::s_use_sloj_names && wdli->draw2d_label)
					{				
						char str[128];
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//====== Наносим цифровую метку устья
						SolidBrush  brush(Color(255, 0, 0, 255));
						FontFamily  fontFamily(L"Times New Roman");
						Font        font(&fontFamily, 10, FontStyleRegular, UnitPixel);

						if (wdli->draw2d_sloj_name)
						{
							if (this->m_pSurfDoc && this->m_pSurfDoc->GetLabDoc())
							{
								long id_ige = wegep->Get_ID_IGE();
								long id_obj = this->m_pSurfDoc->Get_ID_OBJ();								
								CString ige = GetIGEName(&this->m_pSurfDoc->GetLabDoc()->m_database, id_obj, id_ige);
								sprintf(str, "%s\0", ige);
							}
							else
							{
								sprintf(str, "%s\0", wegep->nameID.c_str());
							}
						}
						else
						{
							sprintf(str, "%f\0", wegep->zp);
							DeleteEndZeros(str);
						}

						const int wlen = 2 + 2 * (int)strlen(str);
						WCHAR * wb = new WCHAR[wlen];
						MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, str, -1, wb, wlen );
						graphics.DrawString(wb, -1, &font, PointF(x_sloj_name, y2), &brush);
						delete wb;
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

					}									
					z_pre = pt.z;
				}
			}
		}
	}
}



void WellColomn::DrawAcad_Litho(MyAcad & m_acad, double xProfile, double w, double Height_lin, COLORREF color, double v_scale, double g_scale, double well_hatch_scale, Well_3D * well, wells_draw_list_item * wdli)
{
}
	

void WellColomn::DrawGDIplus_IGE(Graphics ** select_buffer, Graphics& graphics, map_view * v, Profile3D * on, Well_3D * well, wells_draw_list_item * wdli)
{
	float width = wdli ? wdli->draw_width : 2.0;
//printf("WellColomn::DrawGDIplus_IGE well = %s\n", well->GetIDString());
	double dist_to_plane;
	CPoint2 profile;

	fGL x1; fGL y1;
	fGL x2; fGL y2;

	fGL r = v->lines_points_radius;

	double z_pre;
	CPoint3 ustje, pt;
	if (this->m_pSurfDoc && well->GetUstje(ustje))
	{
		//printf("WellColomn::DrawGDIplus_IGE well->GetUstje() this->well_elements.size() = %u\n", this->well_elements.size());
		z_pre = ustje.z;
		pt = ustje;
		for (vector<WellElement*>::iterator it = this->well_elements.begin();
			it != this->well_elements.end(); it++)
		{
//printf("WellColomn::DrawGDIplus_IGE for\n");
			if ((*it))
			{
//printf("WellColomn::DrawGDIplus_IGE if\n");
				Well_IGE_Podoshva * wegep = dynamic_cast<Well_IGE_Podoshva *>((*it));
				if (wegep)
				{
					//wegep->key;
					COLORREF color = wegep->GetColor();
					//printf("z_pre = %f wegep->GetZ() = %f color = %d\n", z_pre, wegep->GetZ(), color);

					Color gdi_color(255, GetRValue(color),GetGValue(color),GetBValue(color));


					//Convert3D_To_2D
					pt.z = z_pre;
					on->Projection(pt, profile, dist_to_plane);
					v->ConvertingFromWorldToScreen(profile.x, profile.y, x1, y1);

					//Convert3D_To_2D
					pt.z = wegep->GetZp();
					on->Projection(pt, profile, dist_to_plane);
					v->ConvertingFromWorldToScreen(profile.x, profile.y, x2, y2);

					Pen   pen(gdi_color);
					double x_sloj_name = x2;
						
					if (!wdli)
					{
						pen.SetWidth(width);
						graphics.DrawLine(&pen, x1, y1, x2, y2);
						x_sloj_name = x2;
					}
					else
					{

						
						Color border_color(255, GetRValue(wdli->border_color),GetGValue(wdli->border_color),GetBValue(wdli->border_color));
						Pen   pen_border(border_color);
						switch(wdli->m_draw_mode_2d)
						{
						case wells_draw_list_item::left:
							{

								pen.SetWidth(0.5*width);	
								graphics.DrawLine(&pen, x1-0.25*width, y1, x2-0.25*width, y2);	
								if(wdli->draw2d_border)
								{
									graphics.DrawLine(&pen_border, x1-0.5*width, y1, x2-0.5*width, y2);	
									graphics.DrawLine(&pen_border, x1-0.5*width, y1, x1, y1);	
								}
								x_sloj_name = x2-width
									// TODO temporary decision while font is not used									
									-0.5*width;

							}
							break;
						case wells_draw_list_item::draw_mode_2d::right:
							{
								pen.SetWidth(0.5*width);	
								graphics.DrawLine(&pen, x1+0.25*width, y1, x2+0.25*width, y2);	
								if(wdli->draw2d_border)
								{
									graphics.DrawLine(&pen_border, x1+0.5*width, y1, x2+0.5*width, y2);	
									graphics.DrawLine(&pen_border, x1+0.5*width, y1, x1, y1);	
								}
								x_sloj_name = x2+0.5*width;
							}
							break;
						case wells_draw_list_item::draw_mode_2d::both:
							{
								pen.SetWidth(width);	
								graphics.DrawLine(&pen, x1, y1, x2, y2);	
								if(wdli->draw2d_border)
								{
									graphics.DrawLine(&pen_border, x1-0.5*width, y1, x2-0.5*width, y2);	
									graphics.DrawLine(&pen_border, x1+0.5*width, y1, x2+0.5*width, y2);	
									graphics.DrawLine(&pen_border, x1+0.5*width, y1, x1-0.5*width, y1);	
								}
								x_sloj_name = x2+0.5*width;
							}
							break;
						}
					}



					if (//i_sphere == Well_3D::s_sloj_number_to_save || 
						Well_3D::s_show_all_sloi)// или если показываем все слои
					{
						//отметим слой для сохранения в виде шариков

						COLORREF sphereColor = color;
						Color sphere_color(255, GetRValue(sphereColor),GetGValue(sphereColor),GetBValue(sphereColor));
						Pen      sphere_pen(gdi_color);								

						FillCircle(&graphics, x2, y2, r, sphere_color);							
						DrawCircle(&graphics, x2, y2, r, Color(255, 0,0,0));							
					}

					if (Well_3D::s_use_sloj_names && wdli->draw2d_label)
					{		
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//====== Наносим цифровую метку устья
						SolidBrush  brush(Color(255, 0, 0, 255));
						FontFamily  fontFamily(L"Times New Roman");
						Font        font(&fontFamily, 10, FontStyleRegular, UnitPixel);

						CPoint3 ustje;
						if (well->GetUstje(ustje))
						{
							char str[128];
							if (wdli->draw2d_sloj_name)
							{
								if (this->m_pSurfDoc && this->m_pSurfDoc->GetLabDoc())
								{
									long id_ige = wegep->Get_ID_IGE();
									long id_obj = this->m_pSurfDoc->Get_ID_OBJ();								
									CString ige = GetIGEName(&this->m_pSurfDoc->GetLabDoc()->m_database, id_obj, id_ige);
									sprintf(str, "%s\0", ige);
								}
								else
								{
									sprintf(str, "%s\0", wegep->nameID.c_str());
								}
							}
							else
							{
								sprintf(str, "%f\0", ustje.z - wegep->zp);
								DeleteEndZeros(str);
							}


							const int wlen = 2 + 2 * (int)strlen(str);
							WCHAR * wb = new WCHAR[wlen];
							MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, str, -1, wb, wlen );
							graphics.DrawString(wb, -1, &font, PointF(x_sloj_name, y2), &brush);
							delete wb;
							//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
							//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						}

					}									
					z_pre = pt.z;
				}
			}
		}
	}
}
void WellColomn::DrawAcad_IGE(MyAcad & m_acad, double xProfile, double w, double Height_lin, COLORREF color, double v_scale, double g_scale, double well_hatch_scale, Well_3D * well, wells_draw_list_item * wdli)
{
	double init_g_scale = 1.0;
	double g = w ;//* init_g_scale/g_scale;

	double z_pre;
	CPoint3 ustje, pt3;
	if (this->m_pSurfDoc && well->GetUstje(ustje))
	{
		z_pre = ustje.z;
		pt3 = ustje;
		for (vector<WellElement*>::iterator it = this->well_elements.begin();
			it != this->well_elements.end(); it++)
		{
			if ((*it))
			{
				Well_IGE_Podoshva * wegep = dynamic_cast<Well_IGE_Podoshva *>((*it));
				if (wegep)
				{
					COLORREF color = wegep->GetColor();

					// here we will put 2D points
					vector<CPoint2> vpt2;
					// here we will put 3D points
					vector<CPoint3> vpt3;


					vpt2.clear();
					vpt3.clear();

					//Convert3D_To_2D
					pt3.z = z_pre;
					//on->Projection(pt, profile, dist_to_plane);
					//v->ConvertingFromWorldToScreen(profile.x, profile.y, x1, y1);

					vpt2.push_back(CPoint2(xProfile+g, pt3.z));
					vpt3.push_back(CPoint3(pt3.x+g, pt3.y+g, pt3.z));
					vpt2.push_back(CPoint2(xProfile-g, pt3.z));
					vpt3.push_back(CPoint3(pt3.x-g, pt3.y-g, pt3.z));
							

					//Convert3D_To_2D
					pt3.z = wegep->GetZp();
					//on->Projection(pt, profile, dist_to_plane);
					//v->ConvertingFromWorldToScreen(profile.x, profile.y, x2, y2);

					vpt2.push_back(CPoint2(xProfile-g, pt3.z));
					vpt3.push_back(CPoint3(pt3.x-g, pt3.y-g, pt3.z));
					vpt2.push_back(CPoint2(xProfile+g, pt3.z));
					vpt3.push_back(CPoint3(pt3.x+g, pt3.y+g, pt3.z));

					//AddPolyLine(m_acad, vpt2, vpt3, to_close, color, param.v_scale, param.g_scale);
					enum Typ_Strihovki
					{
						ts_unknown = 0,
						ts_4_1,
						ts_4_2,
						ts_4_3,
						ts_4_4,
						ts_4_5,
						ts_4_6,
						ts_4_7
					};
					
					Typ_Strihovki m_ts = ts_unknown;


					EngineerGeoElement * eng = this->m_pSurfDoc->FindEngineerGeoElement(wegep->GetKey());
					if(eng)
					{
						CGround::ground_type _ground_type = eng->GetGroungType();

						// показатель текучести
						double fluidity_index; bool ws = false; 
						bool fluidity_index_defined = false;
						if (eng->GetNormativeFluidityIndex(ws, fluidity_index))
						{
							fluidity_index_defined = true;
						}

						// степень влажности 
						double degree_of_moisture;
						bool degree_of_moisture_defined = false;
						if (eng->GetNormativeDegreeOfMoisture(degree_of_moisture))
						{
							degree_of_moisture_defined = true;
						}

						switch (_ground_type)
						{
						case CGround::ground_type::Sand:
							{
								if (degree_of_moisture_defined)
								{
									if (degree_of_moisture >= 0.0 && degree_of_moisture < 0.5)//маловлажный
									{
										m_ts = ts_4_1;
									}
									else if (degree_of_moisture >= 0.5 && degree_of_moisture < 0.8) //влажный
									{
										m_ts = ts_4_4;
									}
									else if (degree_of_moisture >= 0.8 && degree_of_moisture < 1.0) //насыщенный водой
									{
										m_ts = ts_4_7;
									}
								}
							}
							break;
						case CGround::ground_type::Clay://глина
						case CGround::ground_type::Loam://суглинок
							{
								if (fluidity_index_defined)
								{
									if (fluidity_index < 0.0)//твёрдый
									{
										m_ts = ts_4_1;
									}
									else if (fluidity_index >= 0.0 && fluidity_index < 0.25)//полутвёрдый
									{
										m_ts = ts_4_2;
									}
									else if (fluidity_index >= 0.25 && fluidity_index < 0.5)//тугопластичный
									{
										m_ts = ts_4_3;
									}								
									else if (fluidity_index >= 0.5 && fluidity_index < 0.75)//мягкопластичный
									{
										m_ts = ts_4_5;
									}
									else if (fluidity_index >= 0.75 && fluidity_index < 1.0)//текучепластичный
									{
										m_ts = ts_4_6;
									}
									else if (fluidity_index >= 1.0)//текучий
									{
										m_ts = ts_4_7;
									}
								}
							}
							break;
						case CGround::ground_type::SandyLoam:// супесь
							{
								if (fluidity_index_defined)
								{
									if (fluidity_index < 0)//твёрдый
									{
										m_ts = ts_4_1;
									}
									else if (fluidity_index >= 0 && fluidity_index < 1.0)//пластичный
									{
										m_ts = ts_4_4;
									}
									else if (fluidity_index >= 1.0)//текучий
									{
										m_ts = ts_4_7;
									}
								}
							}
							break;
						}
					}					

					// TODO это не та штриховка - для скважин должна быть штриховка в соответствии с консистенцией
					string hatchacad = "LINE";
					double angle = 0.0;
					double scale = 0.0;
					switch (m_ts)
					{
					case ts_4_1:
						{
							angle = 0.0;
							scale = 1.5;
						}
						break;
					case ts_4_2:
						{
							angle = 0.0;
							scale = 3.0;
						}
						break;
					case ts_4_3:
						{
							angle = 90;
							scale = 1.0;
						}
						break;
					case ts_4_4:
						{
							angle = 45;
							scale = 1.5;
						}
						break;
					case ts_4_5:
						{
							angle = 135;
							scale = 3.0;
						}
						break;
					case ts_4_6:
						{
							angle = 135;
							scale = 1.5;
						}
						break;
					case ts_4_7:
						{
							hatchacad = "SOLID";
							color = RGB(50,50,50);
						}
						break;
					}

					scale *= well_hatch_scale;
					
		
					if (m_ts != ts_unknown)
						AddHatchPolyLine(m_acad, vpt2, color, hatchacad, angle, scale, v_scale, g_scale);
					else
					{
						bool to_close = true;
						AddPolyLine(m_acad, vpt2, vpt3, to_close, color, v_scale, g_scale);
					}



							char str[128];
							sprintf(str, "4.%d", m_ts);
							AddText(m_acad, str, 
								CPoint2(xProfile, pt3.z), 
								Height_lin, color, v_scale, g_scale);



					if (Well_3D::s_use_sloj_names && wdli->draw2d_label)
					{									
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//====== Наносим цифровую метку устья
						//SolidBrush  brush(Color(255, 0, 0, 255));
						//FontFamily  fontFamily(L"Times New Roman");
						//Font        font(&fontFamily, 10, FontStyleRegular, UnitPixel);

						CPoint3 ustje;
						if (well->GetUstje(ustje))
						{
							char str[128];

							if (wdli->draw2d_sloj_name)
							{
								if (this->m_pSurfDoc && this->m_pSurfDoc->GetLabDoc())
								{
									long id_ige = wegep->Get_ID_IGE();
									long id_obj = this->m_pSurfDoc->Get_ID_OBJ();								
									CString ige = GetIGEName(&this->m_pSurfDoc->GetLabDoc()->m_database, id_obj, id_ige);
									sprintf(str, "%s\0", ige);
								}
								else
								{
									sprintf(str, "%s\0", wegep->nameID.c_str());
								}
							}
							else
							{
								// глубина
								sprintf(str, "%f\0", ustje.z - wegep->zp);
								DeleteEndZeros(str);
							}							
							
							int len = strlen(str);
												
							AddText(m_acad, 
								str, //well->m_vstrSloiNames[i_sloj].c_str(), 
								CPoint2(Height_lin + xProfile+w, pt3.z), 
								Height_lin, color, v_scale, g_scale);


							// абс.отметка
							sprintf(str, "%f\0", wegep->zp);
							DeleteEndZeros(str);

							len = strlen(str);
												
							AddText(m_acad, 
								str, 
								CPoint2(xProfile-w-Height_lin-0.9*double(len)*Height_lin, pt3.z), 
								Height_lin, color, v_scale, g_scale);

							//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
							//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						}

					}									
					z_pre = pt3.z;
				}
			}
		}
	}

}



void WellColomn::DrawGDIplus_Hydro(Graphics ** select_buffer, Graphics& graphics, map_view * v, Profile3D * on, Well_3D * well, wells_draw_list_item * wdli)
{
	float width = wdli ? wdli->draw_width : 2.0;
//printf("WellColomn::DrawGDIplus_Hydro() well = %s\n", well->GetIDString());
	double dist_to_plane;
	CPoint2 profile;

	//fGL x1; fGL y1;
	fGL x2; fGL y2;

	//fGL r = 2*v->lines_points_radius;
	fGL r = width/2;


	//double z_pre;
	CPoint3 ustje, pt;
	if (well->GetUstje(ustje))
	{
		//z_pre = ustje.z;
		pt = ustje;
		for (vector<WellElement*>::iterator it = this->well_elements.begin();
			it != this->well_elements.end(); it++)
		{
			if ((*it))
			{
				Well_Hydro_Projavlenie * whydrop = dynamic_cast<Well_Hydro_Projavlenie *>((*it));
				if (whydrop)
				{
					//wegep->key;

					COLORREF color = RGB(0,0,255);
					Color gdi_color(128, GetRValue(color),GetGValue(color),GetBValue(color));
					Pen      pen(gdi_color);							
					//pen.SetWidth(1.0);	

					//Convert3D_To_2D
					//pt.z = z_pre;
					//on->Projection(pt, profile, dist_to_plane);
					//v->ConvertingFromWorldToScreen(profile.x, profile.y, x1, y1);

					//Convert3D_To_2D
					pt.z = whydrop->GetZp();
					on->Projection(pt, profile, dist_to_plane);
					v->ConvertingFromWorldToScreen(profile.x, profile.y, x2, y2);

					graphics.DrawLine(&pen, x2-r, y2, x2+r, y2);
#if 0
					//if (//i_sphere == Well_3D::s_sloj_number_to_save || 
					//	Well_3D::s_show_all_sloi)// или если показываем все слои
					{
						//отметим слой для сохранения в виде шариков

						COLORREF sphereColor = color;
						Color sphere_color(255, GetRValue(sphereColor),GetGValue(sphereColor),GetBValue(sphereColor));
						Pen      sphere_pen(gdi_color);								

						FillCircle(&graphics, x2, y2, r, sphere_color);							
						DrawCircle(&graphics, x2, y2, r, Color(255, 0,0,0));							
					}
#endif
					/*if (Well_3D::s_use_sloj_names && wdli->draw2d_sloj_name)
					{									
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//====== Наносим цифровую метку устья
						SolidBrush  brush(Color(255, 0, 0, 255));
						FontFamily  fontFamily(L"Times New Roman");
						Font        font(&fontFamily, 10, FontStyleRegular, UnitPixel);

						const int wlen = 2 + 2 * (int)strlen(whydrop->nameID.c_str());
						WCHAR * wb = new WCHAR[wlen];
						MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, whydrop->nameID.c_str(), -1, wb, wlen );
						graphics.DrawString(wb, -1, &font, PointF(x2, y2), &brush);
						delete wb;
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

					}	*/								
				}
			}
		}
	}							

}



void WellColomn::DrawAcad_Hydro(MyAcad & m_acad, double xProfile, double w, double Height_lin, COLORREF color, double v_scale, double g_scale, double well_hatch_scale, Well_3D * well, wells_draw_list_item * wdli)
{
}

void WellColomn::DrawGDIplus_IsSand(Graphics ** select_buffer, Graphics& graphics, map_view * v, Profile3D * on, Well_3D * well, wells_draw_list_item * wdli)
{
	float width = wdli ? wdli->draw_width : 2.0;

	double dist_to_plane;
	CPoint2 profile;

	fGL x1; fGL y1;
	fGL x2; fGL y2;

	fGL r = v->lines_points_radius;


	double z_pre;
	CPoint3 ustje, pt;
	if (well->GetUstje(ustje))
	{
		z_pre = ustje.z;
		pt = ustje;
		for (vector<WellElement*>::iterator it = this->well_elements.begin();
			it != this->well_elements.end(); it++)
		{
			if ((*it))
			{
				Well_IsSand_Podoshva * wegep = dynamic_cast<Well_IsSand_Podoshva *>((*it));
				if (wegep)
				{
					//wegep->key;

					COLORREF color = wegep->GetColor();
					Color gdi_color(255, GetRValue(color),GetGValue(color),GetBValue(color));


					//Convert3D_To_2D
					pt.z = z_pre;
					on->Projection(pt, profile, dist_to_plane);
					v->ConvertingFromWorldToScreen(profile.x, profile.y, x1, y1);

					//Convert3D_To_2D
					pt.z = wegep->GetZp();
					on->Projection(pt, profile, dist_to_plane);
					v->ConvertingFromWorldToScreen(profile.x, profile.y, x2, y2);

					Pen   pen(gdi_color);
						
					if (!wdli)
					{
						pen.SetWidth(width);
						graphics.DrawLine(&pen, x1, y1, x2, y2);
					}
					else
					{
						Color border_color(255, GetRValue(wdli->border_color),GetGValue(wdli->border_color),GetBValue(wdli->border_color));
						Pen   pen_border(border_color);
						switch(wdli->m_draw_mode_2d)
						{
						case wells_draw_list_item::left:
							{
								pen.SetWidth(0.5*width);	
								graphics.DrawLine(&pen, x1-0.25*width, y1, x2-0.25*width, y2);	
								if(wdli->draw2d_border)
									graphics.DrawLine(&pen_border, x1-0.5*width, y1, x2-0.5*width, y2);	
							}
							break;
						case wells_draw_list_item::draw_mode_2d::right:
							{
								pen.SetWidth(0.5*width);	
								graphics.DrawLine(&pen, x1+0.25*width, y1, x2+0.25*width, y2);	
								if(wdli->draw2d_border)
									graphics.DrawLine(&pen_border, x1+0.5*width, y1, x2+0.5*width, y2);	
							}
							break;
						case wells_draw_list_item::draw_mode_2d::both:
							{
								pen.SetWidth(width);	
								graphics.DrawLine(&pen, x1, y1, x2, y2);	
								if(wdli->draw2d_border)
								{
									graphics.DrawLine(&pen_border, x1-0.5*width, y1, x2-0.5*width, y2);	
									graphics.DrawLine(&pen_border, x1+0.5*width, y1, x2+0.5*width, y2);	
								}
							}
							break;
						}
					}



					if (//i_sphere == Well_3D::s_sloj_number_to_save || 
						Well_3D::s_show_all_sloi)// или если показываем все слои
					{
						//отметим слой для сохранения в виде шариков

						COLORREF sphereColor = color;
						Color sphere_color(255, GetRValue(sphereColor),GetGValue(sphereColor),GetBValue(sphereColor));
						Pen      sphere_pen(gdi_color);								

						FillCircle(&graphics, x2, y2, r, sphere_color);							
						DrawCircle(&graphics, x2, y2, r, Color(255, 0,0,0));							
					}

					if (Well_3D::s_use_sloj_names && wdli->draw2d_sloj_name)
					{									
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//====== Наносим цифровую метку устья
						SolidBrush  brush(Color(255, 0, 0, 255));
						FontFamily  fontFamily(L"Times New Roman");
						Font        font(&fontFamily, 10, FontStyleRegular, UnitPixel);

						const int wlen = 2 + 2 * (int)strlen(wegep->nameID.c_str());
						WCHAR * wb = new WCHAR[wlen];
						MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, wegep->nameID.c_str(), -1, wb, wlen );
						graphics.DrawString(wb, -1, &font, PointF(x2, y2), &brush);
						delete wb;
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

					}									
					z_pre = pt.z;
				}
			}
		}
	}		

}




void WellColomn::DrawAcad_IsSand(MyAcad & m_acad, double xProfile, double w, double Height_lin, COLORREF color, double v_scale, double g_scale, double well_hatch_scale, Well_3D * well, wells_draw_list_item * wdli)
{
}

void WellColomn::DrawGDIplus_LaboratoryAnalizes(Graphics ** select_buffer, Graphics& graphics, map_view * v, Profile3D * on, Well_3D * well, wells_draw_list_item * wdli)
{
	float width = wdli ? wdli->draw_width : 2.0;
//printf("WellColomn::DrawGDIplus_Hydro() well = %s\n", well->GetIDString());
	double dist_to_plane;
	CPoint2 profile;

	//fGL x1; fGL y1;
	fGL x2; fGL y2;

	//fGL r = 2*v->lines_points_radius;
	fGL r = width/2;


	//double z_pre;
	CPoint3 ustje, pt;
	if (well->GetUstje(ustje))
	{
		//z_pre = ustje.z;
		pt = ustje;
		for (vector<WellElement*>::iterator it = this->well_elements.begin();
			it != this->well_elements.end(); it++)
		{
			if ((*it))
			{
				Well_Laboratory_Analize * wlab = dynamic_cast<Well_Laboratory_Analize *>((*it));
				if (wlab && wlab->LabLayerCheckDraw())
				{
					//wegep->key;

					COLORREF color = RGB(0,255,0);
					Color gdi_color(128, GetRValue(color),GetGValue(color),GetBValue(color));
					Pen      pen(gdi_color);							
					//pen.SetWidth(1.0);	

					//Convert3D_To_2D
					//pt.z = z_pre;
					//on->Projection(pt, profile, dist_to_plane);
					//v->ConvertingFromWorldToScreen(profile.x, profile.y, x1, y1);

					//Convert3D_To_2D
					pt.z = wlab->GetZp();
					on->Projection(pt, profile, dist_to_plane);
					v->ConvertingFromWorldToScreen(profile.x, profile.y, x2, y2);

					graphics.DrawLine(&pen, x2-r, y2, x2+r, y2);
#if 1
					//if (//i_sphere == Well_3D::s_sloj_number_to_save || 
					//	Well_3D::s_show_all_sloi)// или если показываем все слои
					{
						//отметим слой для сохранения в виде шариков

						COLORREF sphereColor = color;
						Color sphere_color(255, GetRValue(sphereColor),GetGValue(sphereColor),GetBValue(sphereColor));
						Pen      sphere_pen(gdi_color);	

						FractionsLabTrialResults::SandSoilsClass ssc;
						FractionsLabTrialResults::ClaySoilsClass csc;

						CGround::ground_type gt = wlab->lab_number->GetGroundType(ssc, csc);
						switch(gt)
						{
						case CGround::ground_type::Sand:
							{
								Color foreColor = Color(0,0,0);
								Color backColor = Color(255,255,0);
								switch(ssc)
								{
								case FractionsLabTrialResults::SandSoilsClass::undefined_sand_soil:
									{
										FillCircle(&graphics, x2, y2, r, backColor);
									}
									break;		
								//Крупнообломочный
								case FractionsLabTrialResults::SandSoilsClass::valunnyj_or_glubovuj:
									{
										FillCircle(&graphics, x2, y2, r, backColor);
									}
									break;
								case FractionsLabTrialResults::SandSoilsClass::galechnikovyj_or_schebenistyj:
									{
										HatchFillCircle(&graphics, x2, y2, r, HatchStyleSphere, foreColor, backColor);
									}
									break;
								case FractionsLabTrialResults::SandSoilsClass::gravijnyj_or_dresvyanyj:
									{
										HatchFillCircle(&graphics, x2, y2, r, HatchStyleDivot, foreColor, backColor);
									}
									break;
								// Песчаный
								case FractionsLabTrialResults::SandSoilsClass::gravelistyj:
									{
										HatchFillCircle(&graphics, x2, y2, r, HatchStyleLargeConfetti, foreColor, backColor);
									}
									break;
								case FractionsLabTrialResults::SandSoilsClass::krupnyj:
									{
										HatchFillCircle(&graphics, x2, y2, r, HatchStyle05Percent, foreColor, backColor);
									}
									break;
								case FractionsLabTrialResults::SandSoilsClass::srednej_krupnosti:
									{
										HatchFillCircle(&graphics, x2, y2, r, HatchStyle10Percent, foreColor, backColor);
									}
									break;
								case FractionsLabTrialResults::SandSoilsClass::melkij:
									{
										HatchFillCircle(&graphics, x2, y2, r, HatchStyle20Percent, foreColor, backColor);
									}
									break;
								case FractionsLabTrialResults::SandSoilsClass::pylevatyj:
									{
										HatchFillCircle(&graphics, x2, y2, r, HatchStyle25Percent, foreColor, backColor);
									}
									break;
								}								
							}
							break;
						case CGround::ground_type::SandyLoam:
							{
								Color foreColor = Color(0,0,0);
								Color backColor = Color(232,205,131);
								HatchFillCircle(&graphics, x2, y2, r, HatchStyleDashedUpwardDiagonal, foreColor, backColor);
							}
							break;
						case CGround::ground_type::Loam:
							{
								Color foreColor = Color(0,0,0);
								Color backColor = Color(255,128,0);
								HatchFillCircle(&graphics, x2, y2, r, HatchStyleBackwardDiagonal, foreColor, backColor);
							}
							break;
						case CGround::ground_type::Clay:
							{
								Color foreColor = Color(0,0,0);
								Color backColor = Color(128,64,0);
								HatchFillCircle(&graphics, x2, y2, r, HatchStyleLightHorizontal, foreColor, backColor);
							}
							break;
						default:
							{
								FillCircle(&graphics, x2, y2, r, sphere_color);
							}
							break;

						}						


						//							
						DrawCircle(&graphics, x2, y2, r, Color(255, 0,0,0));

						// Filling Select_buffer

								
						COLORREF selectColor = COLORREF(wlab);
						//Color select_color(GetAValue(selectColor), GetRValue(selectColor),GetGValue(selectColor),GetBValue(selectColor));
						Color select_color1(255, GetRValue(selectColor),GetGValue(selectColor),GetBValue(selectColor));
						Color select_color2(255, GLNAME_MD_TYPE_WELL_ELEMENT, 1, GetAValue(selectColor));
						//Color select_color(0, GetRValue(selectColor),GetGValue(selectColor),GetBValue(selectColor));
						FillCircle(select_buffer[0], x2, y2, r, select_color1);	
						FillCircle(select_buffer[1], x2, y2, r, select_color2);	

						//printf("wlab = %x\n", wlab);
						//printf("selectColor = %x\n", selectColor);

						//BYTE r = GetRValue(selectColor);
						//BYTE g = GetGValue(selectColor);
						//BYTE b = GetBValue(selectColor);
						//BYTE a = GetAValue(selectColor);

						//printf("GetRValue(selectColor) = %x\n", r);
						//printf("GetGValue(selectColor) = %x\n", g);
						//printf("GetBValue(selectColor) = %x\n", b);
						//printf("GetAValue(selectColor) = %x\n", a);

						//printf("RGBA(r,g,b,a) = %x\n", RGBA(r,g,b,a));

						//printf("RGBA(r,g,b,a) = %x\n", RGBA(select_color1.GetRed(),select_color1.GetGreen(),select_color1.GetBlue(),select_color2.GetBlue()));
						

					}



#endif

					string s = wlab->GetLabel(Well_Laboratory_Analize::s_label_type);
					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					//====== Наносим цифровую метку устья
					SolidBrush  brush(Color(255, 0, 0, 255));
					FontFamily  fontFamily(L"Times New Roman");
					Font        font(&fontFamily, 11, FontStyleRegular, UnitPixel);

					const int wlen = 2 + 2 * (int)strlen(s.c_str());
					WCHAR * wb = new WCHAR[wlen];
					MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, s.c_str(), -1, wb, wlen );
					graphics.DrawString(wb, -1, &font, PointF(x2 + r, y2-font.GetHeight(&graphics)), &brush);
					delete wb;
					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

					/*if (Well_3D::s_use_sloj_names)
					{
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//====== Наносим цифровую метку устья
						SolidBrush  brush(Color(255, 0, 0, 255));
						FontFamily  fontFamily(L"Times New Roman");
						Font        font(&fontFamily, 10, FontStyleRegular, UnitPixel);

						const int wlen = 2 + 2 * (int)strlen(whydrop->nameID.c_str());
						WCHAR * wb = new WCHAR[wlen];
						MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, whydrop->nameID.c_str(), -1, wb, wlen );
						graphics.DrawString(wb, -1, &font, PointF(x2, y2), &brush);
						delete wb;
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

					}	//*/								
				}
			}
		}
	}		
}




void WellColomn::DrawAcad_LaboratoryAnalizes(MyAcad & m_acad, double xProfile, double w, double Height_lin, COLORREF color, double v_scale, double g_scale, double well_hatch_scale, Well_3D * well, wells_draw_list_item * wdli)
{

	w /= 4.0;
	double init_g_scale = 1.0;

	//double z_pre;
	CPoint3 ustje, pt3;
	if (well->GetUstje(ustje))
	{
		//z_pre = ustje.z;
		pt3 = ustje;
		for (vector<WellElement*>::iterator it = this->well_elements.begin();
			it != this->well_elements.end(); it++)
		{
			if ((*it))
			{
				Well_Laboratory_Analize * wlab = dynamic_cast<Well_Laboratory_Analize *>((*it));
				if (wlab && wlab->LabLayerCheckDraw())
				{
					//wegep->key;

					COLORREF color = 0;// RGB(0,255,0);
					//Color gdi_color(128, GetRValue(color),GetGValue(color),GetBValue(color));
					//Pen      pen(gdi_color);							
					//pen.SetWidth(1.0);	

					//Convert3D_To_2D
					//pt.z = z_pre;
					//on->Projection(pt, profile, dist_to_plane);
					//v->ConvertingFromWorldToScreen(profile.x, profile.y, x1, y1);

					//Convert3D_To_2D
					pt3.z = wlab->GetZp();

					// Код пробы грунта             
					//1 - Бюкс,                      
					//2 - Монолит,                           
					//3 - Нарушенная структура, 
					//4 - Кольцо

					switch (wlab->lab_number->id_kodprob)
					{
					case 1://1 - Бюкс
					case 2://2 - Монолит
					case 4://4 - Кольцо
						{
                            // square

							// here we will put 2D points
							vector<CPoint2> vpt2;
							// here we will put 3D points
							vector<CPoint3> vpt3;

							double v = w;
							double g = w * init_g_scale/g_scale;

							vpt2.clear();
							vpt3.clear();							

							vpt2.push_back(CPoint2(xProfile+g, pt3.z+v));
							vpt3.push_back(CPoint3(pt3.x+g, pt3.y+g, pt3.z+v));

							vpt2.push_back(CPoint2(xProfile-g, pt3.z+v));
							vpt3.push_back(CPoint3(pt3.x-g, pt3.y-g, pt3.z+v));
									

						
							vpt2.push_back(CPoint2(xProfile-g, pt3.z-v));
							vpt3.push_back(CPoint3(pt3.x-g, pt3.y-g, pt3.z-v));

							vpt2.push_back(CPoint2(xProfile+g, pt3.z-v));
							vpt3.push_back(CPoint3(pt3.x+g, pt3.y+g, pt3.z-v));


							string hatchacad = "SOLID";
							double angle = 0.0;
							double scale = 1.0;
								
							AddHatchPolyLine(m_acad, vpt2, color, hatchacad, angle, scale, v_scale, g_scale);
						}
						break;
					case 3://3 - Нарушенная структура
						{
							//triangle

							// here we will put 2D points
							vector<CPoint2> vpt2;
							// here we will put 3D points
							vector<CPoint3> vpt3;


							vpt2.clear();
							vpt3.clear();							


							double R = 2*w/sqrt(3.0);//радиус описанной окружности вокруг правильного треугольника со стороной 2*w
							double d = 2*w*(sqrt(0.75) - 1.0 / sqrt(3.0));


							double g = w * init_g_scale/g_scale;

							vpt2.push_back(CPoint2(xProfile, pt3.z+R));
							vpt3.push_back(CPoint3(pt3.x, pt3.y, pt3.z+R));
									

						
							vpt2.push_back(CPoint2(xProfile-g, pt3.z-d));
							vpt3.push_back(CPoint3(pt3.x-g, pt3.y-g, pt3.z-d));

							vpt2.push_back(CPoint2(xProfile+g, pt3.z-d));
							vpt3.push_back(CPoint3(pt3.x+g, pt3.y+g, pt3.z-d));


							string hatchacad = "SOLID";
							double angle = 0.0;
							double scale = 1.0;
								
							AddHatchPolyLine(m_acad, vpt2, color, hatchacad, angle, scale, v_scale, g_scale);
						}
						break;
					}

//					on->Projection(pt, profile, dist_to_plane);
//					v->ConvertingFromWorldToScreen(profile.x, profile.y, x2, y2);

//					graphics.DrawLine(&pen, x2-r, y2, x2+r, y2);


					string s = wlab->GetLabel(Well_Laboratory_Analize::s_label_type);
					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					//====== Наносим цифровую метку устья
					//SolidBrush  brush(Color(255, 0, 0, 255));
					//FontFamily  fontFamily(L"Times New Roman");
					//Font        font(&fontFamily, 11, FontStyleRegular, UnitPixel);

					//const int wlen = 2 + 2 * (int)strlen(s.c_str());
					//WCHAR * wb = new WCHAR[wlen];
					//MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, s.c_str(), -1, wb, wlen );
					//graphics.DrawString(wb, -1, &font, PointF(x2 + r, y2-font.GetHeight(&graphics)), &brush);
					//delete wb;
					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

					/*if (Well_3D::s_use_sloj_names)
					{
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//====== Наносим цифровую метку устья
						SolidBrush  brush(Color(255, 0, 0, 255));
						FontFamily  fontFamily(L"Times New Roman");
						Font        font(&fontFamily, 10, FontStyleRegular, UnitPixel);

						const int wlen = 2 + 2 * (int)strlen(whydrop->nameID.c_str());
						WCHAR * wb = new WCHAR[wlen];
						MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, whydrop->nameID.c_str(), -1, wb, wlen );
						graphics.DrawString(wb, -1, &font, PointF(x2, y2), &brush);
						delete wb;
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

					}	//*/								
				}
			}
		}
	}
}
#else
void Well_Litho_Podoshva::DrawGDIplus(Graphics ** select_buffer, Graphics& graphics, map_view * v, Profile3D * on, Well_3D * well, wells_draw_list_item * wdli)
{
	float width = wdli ? wdli->draw_width : 2.0;
//printf("WellColomn::DrawGDIplus_IGE well = %s\n", well->GetIDString());
	double dist_to_plane;
	CPoint2 profile;

	fGL x1; fGL y1;
	fGL x2; fGL y2;

	fGL r = v->lines_points_radius;

	CPoint3 ustje, pt;
	if (well->GetUstje(ustje))
	{
		//printf("WellColomn::DrawGDIplus_IGE well->GetUstje() this->well_elements.size() = %u\n", this->well_elements.size());
		static double z_pre = ustje.z;
		pt = ustje;
//		for (vector<WellElement*>::iterator it = this->well_elements.begin();
//			it != this->well_elements.end(); it++)
		{
//printf("WellColomn::DrawGDIplus_IGE for\n");
//			if ((*it))
			{
//printf("WellColomn::DrawGDIplus_IGE if\n");
				Well_Litho_Podoshva * wegep = this;
				if (wegep)
				{
					//wegep->key;
					COLORREF color = wegep->GetColor();
					//printf("z_pre = %f wegep->GetZ() = %f color = %d\n", z_pre, wegep->GetZ(), color);

					Color gdi_color(255, GetRValue(color),GetGValue(color),GetBValue(color));


					//Convert3D_To_2D
					pt.z = z_pre;
					on->Projection(pt, profile, dist_to_plane);
					v->ConvertingFromWorldToScreen(profile.x, profile.y, x1, y1);

					//Convert3D_To_2D
					pt.z = wegep->GetZ();
					on->Projection(pt, profile, dist_to_plane);
					v->ConvertingFromWorldToScreen(profile.x, profile.y, x2, y2);

					Pen   pen(gdi_color);
						
					if (!wdli)
					{
						pen.SetWidth(width);
						graphics.DrawLine(&pen, x1, y1, x2, y2);
					}
					else
					{
						Color border_color(255, GetRValue(wdli->border_color),GetGValue(wdli->border_color),GetBValue(wdli->border_color));
						Pen   pen_border(border_color);
						switch(wdli->m_draw_mode_2d)
						{
						case wells_draw_list_item::left:
							{
								pen.SetWidth(0.5*width);	
								graphics.DrawLine(&pen, x1-0.25*width, y1, x2-0.25*width, y2);	
								if(wdli->draw2d_border)
									graphics.DrawLine(&pen_border, x1-0.5*width, y1, x2-0.5*width, y2);	
							}
							break;
						case wells_draw_list_item::draw_mode_2d::right:
							{
								pen.SetWidth(0.5*width);	
								graphics.DrawLine(&pen, x1+0.25*width, y1, x2+0.25*width, y2);	
								if(wdli->draw2d_border)
									graphics.DrawLine(&pen_border, x1+0.5*width, y1, x2+0.5*width, y2);	
							}
							break;
						case wells_draw_list_item::draw_mode_2d::both:
							{
								pen.SetWidth(width);	
								graphics.DrawLine(&pen, x1, y1, x2, y2);	
								if(wdli->draw2d_border)
								{
									graphics.DrawLine(&pen_border, x1-0.5*width, y1, x2-0.5*width, y2);	
									graphics.DrawLine(&pen_border, x1+0.5*width, y1, x2+0.5*width, y2);	
								}
							}
							break;
						}
					}



					if (//i_sphere == Well_3D::s_sloj_number_to_save || 
						Well_3D::s_show_all_sloi)// или если показываем все слои
					{
						//отметим слой для сохранения в виде шариков

						COLORREF sphereColor = color;
						Color sphere_color(255, GetRValue(sphereColor),GetGValue(sphereColor),GetBValue(sphereColor));
						Pen      sphere_pen(gdi_color);								

						FillCircle(&graphics, x2, y2, r, sphere_color);							
						DrawCircle(&graphics, x2, y2, r, Color(255, 0,0,0));							
					}

					if (Well_3D::s_use_sloj_names)
					{									
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//====== Наносим цифровую метку устья
						SolidBrush  brush(Color(255, 0, 0, 255));
						FontFamily  fontFamily(L"Times New Roman");
						Font        font(&fontFamily, 10, FontStyleRegular, UnitPixel);

						const int wlen = 2 + 2 * (int)strlen(wegep->nameID.c_str());
						WCHAR * wb = new WCHAR[wlen];
						MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, wegep->nameID.c_str(), -1, wb, wlen );
						graphics.DrawString(wb, -1, &font, PointF(x2, y2), &brush);
						delete wb;
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

					}									
					z_pre = pt.z;
				}
			}
		}
	}
}



void Well_IGE_Podoshva::DrawGDIplus(Graphics ** select_buffer, Graphics& graphics, map_view * v, Profile3D * on, Well_3D * well, wells_draw_list_item * wdli)
{
	float width = wdli ? wdli->draw_width : 2.0;
//printf("WellColomn::DrawGDIplus_IGE well = %s\n", well->GetIDString());
	double dist_to_plane;
	CPoint2 profile;

	fGL x1; fGL y1;
	fGL x2; fGL y2;

	fGL r = v->lines_points_radius;

	CPoint3 ustje, pt;
	if (well->GetUstje(ustje))
	{
		//printf("WellColomn::DrawGDIplus_IGE well->GetUstje() this->well_elements.size() = %u\n", this->well_elements.size());
		static double z_pre = ustje.z;
		pt = ustje;
//		for (vector<WellElement*>::iterator it = this->well_elements.begin();
//			it != this->well_elements.end(); it++)
		{
//printf("WellColomn::DrawGDIplus_IGE for\n");
//			if ((*it))
			{
//printf("WellColomn::DrawGDIplus_IGE if\n");
				Well_IGE_Podoshva * wegep = this;
				if (wegep)
				{
					//wegep->key;
					COLORREF color = wegep->GetColor();
					//printf("z_pre = %f wegep->GetZ() = %f color = %d\n", z_pre, wegep->GetZ(), color);

					Color gdi_color(255, GetRValue(color),GetGValue(color),GetBValue(color));


					//Convert3D_To_2D
					pt.z = z_pre;
					on->Projection(pt, profile, dist_to_plane);
					v->ConvertingFromWorldToScreen(profile.x, profile.y, x1, y1);

					//Convert3D_To_2D
					pt.z = wegep->GetZ();
					on->Projection(pt, profile, dist_to_plane);
					v->ConvertingFromWorldToScreen(profile.x, profile.y, x2, y2);

					Pen   pen(gdi_color);
						
					if (!wdli)
					{
						pen.SetWidth(width);
						graphics.DrawLine(&pen, x1, y1, x2, y2);
					}
					else
					{
						Color border_color(255, GetRValue(wdli->border_color),GetGValue(wdli->border_color),GetBValue(wdli->border_color));
						Pen   pen_border(border_color);
						switch(wdli->m_draw_mode_2d)
						{
						case wells_draw_list_item::left:
							{
								pen.SetWidth(0.5*width);	
								graphics.DrawLine(&pen, x1-0.25*width, y1, x2-0.25*width, y2);	
								if(wdli->draw2d_border)
									graphics.DrawLine(&pen_border, x1-0.5*width, y1, x2-0.5*width, y2);	
							}
							break;
						case wells_draw_list_item::draw_mode_2d::right:
							{
								pen.SetWidth(0.5*width);	
								graphics.DrawLine(&pen, x1+0.25*width, y1, x2+0.25*width, y2);	
								if(wdli->draw2d_border)
									graphics.DrawLine(&pen_border, x1+0.5*width, y1, x2+0.5*width, y2);	
							}
							break;
						case wells_draw_list_item::draw_mode_2d::both:
							{
								pen.SetWidth(width);	
								graphics.DrawLine(&pen, x1, y1, x2, y2);	
								if(wdli->draw2d_border)
								{
									graphics.DrawLine(&pen_border, x1-0.5*width, y1, x2-0.5*width, y2);	
									graphics.DrawLine(&pen_border, x1+0.5*width, y1, x2+0.5*width, y2);	
								}
							}
							break;
						}
					}



					if (//i_sphere == Well_3D::s_sloj_number_to_save || 
						Well_3D::s_show_all_sloi)// или если показываем все слои
					{
						//отметим слой для сохранения в виде шариков

						COLORREF sphereColor = color;
						Color sphere_color(255, GetRValue(sphereColor),GetGValue(sphereColor),GetBValue(sphereColor));
						Pen      sphere_pen(gdi_color);								

						FillCircle(&graphics, x2, y2, r, sphere_color);							
						DrawCircle(&graphics, x2, y2, r, Color(255, 0,0,0));							
					}

					if (Well_3D::s_use_sloj_names)
					{									
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//====== Наносим цифровую метку устья
						SolidBrush  brush(Color(255, 0, 0, 255));
						FontFamily  fontFamily(L"Times New Roman");
						Font        font(&fontFamily, 10, FontStyleRegular, UnitPixel);

						const int wlen = 2 + 2 * (int)strlen(wegep->nameID.c_str());
						WCHAR * wb = new WCHAR[wlen];
						MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, wegep->nameID.c_str(), -1, wb, wlen );
						graphics.DrawString(wb, -1, &font, PointF(x2, y2), &brush);
						delete wb;
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

					}									
					z_pre = pt.z;
				}
			}
		}
	}
}



void Well_Hydro_Projavlenie::DrawGDIplus(Graphics ** select_buffer, Graphics& graphics, map_view * v, Profile3D * on, Well_3D * well, wells_draw_list_item * wdli)
{
	float width = wdli ? wdli->draw_width : 2.0;
//printf("WellColomn::DrawGDIplus_Hydro() well = %s\n", well->GetIDString());
	double dist_to_plane;
	CPoint2 profile;

	//fGL x1; fGL y1;
	fGL x2; fGL y2;

	//fGL r = 2*v->lines_points_radius;
	fGL r = width/2;


	//double z_pre;
	CPoint3 ustje, pt;
	if (well->GetUstje(ustje))
	{
		//z_pre = ustje.z;
		pt = ustje;
//		for (vector<WellElement*>::iterator it = this->well_elements.begin();
//			it != this->well_elements.end(); it++)
		{
//			if ((*it))
			{
				Well_Hydro_Projavlenie * const  whydrop = this;
				if (whydrop)
				{
					//wegep->key;

					COLORREF color = RGB(0,0,255);
					Color gdi_color(128, GetRValue(color),GetGValue(color),GetBValue(color));
					Pen      pen(gdi_color);							
					//pen.SetWidth(1.0);	

					//Convert3D_To_2D
					//pt.z = z_pre;
					//on->Projection(pt, profile, dist_to_plane);
					//v->ConvertingFromWorldToScreen(profile.x, profile.y, x1, y1);

					//Convert3D_To_2D
					pt.z = whydrop->GetZ();
					on->Projection(pt, profile, dist_to_plane);
					v->ConvertingFromWorldToScreen(profile.x, profile.y, x2, y2);

					graphics.DrawLine(&pen, x2-r, y2, x2+r, y2);
#if 0
					//if (//i_sphere == Well_3D::s_sloj_number_to_save || 
					//	Well_3D::s_show_all_sloi)// или если показываем все слои
					{
						//отметим слой для сохранения в виде шариков

						COLORREF sphereColor = color;
						Color sphere_color(255, GetRValue(sphereColor),GetGValue(sphereColor),GetBValue(sphereColor));
						Pen      sphere_pen(gdi_color);								

						FillCircle(&graphics, x2, y2, r, sphere_color);							
						DrawCircle(&graphics, x2, y2, r, Color(255, 0,0,0));							
					}
#endif
					/*if (Well_3D::s_use_sloj_names)
					{									
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//====== Наносим цифровую метку устья
						SolidBrush  brush(Color(255, 0, 0, 255));
						FontFamily  fontFamily(L"Times New Roman");
						Font        font(&fontFamily, 10, FontStyleRegular, UnitPixel);

						const int wlen = 2 + 2 * (int)strlen(whydrop->nameID.c_str());
						WCHAR * wb = new WCHAR[wlen];
						MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, whydrop->nameID.c_str(), -1, wb, wlen );
						graphics.DrawString(wb, -1, &font, PointF(x2, y2), &brush);
						delete wb;
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

					}	*/								
				}
			}
		}
	}							

}



void Well_IsSand_Podoshva::DrawGDIplus(Graphics ** select_buffer, Graphics& graphics, map_view * v, Profile3D * on, Well_3D * well, wells_draw_list_item * wdli)
{
	float width = wdli ? wdli->draw_width : 2.0;

	double dist_to_plane;
	CPoint2 profile;

	fGL x1; fGL y1;
	fGL x2; fGL y2;

	fGL r = v->lines_points_radius;


	//double z_pre;
	CPoint3 ustje, pt;
	if (well->GetUstje(ustje))
	{
		static double z_pre = ustje.z;
		pt = ustje;
//		for (vector<WellElement*>::iterator it = this->well_elements.begin();
//			it != this->well_elements.end(); it++)
		{
//			if ((*it))
			{
				Well_IsSand_Podoshva * const wegep = this;
				if (wegep)
				{
					//wegep->key;

					COLORREF color = wegep->GetColor();
					Color gdi_color(255, GetRValue(color),GetGValue(color),GetBValue(color));


					//Convert3D_To_2D
					pt.z = z_pre;
					on->Projection(pt, profile, dist_to_plane);
					v->ConvertingFromWorldToScreen(profile.x, profile.y, x1, y1);

					//Convert3D_To_2D
					pt.z = wegep->GetZ();
					on->Projection(pt, profile, dist_to_plane);
					v->ConvertingFromWorldToScreen(profile.x, profile.y, x2, y2);

					Pen   pen(gdi_color);
						
					if (!wdli)
					{
						pen.SetWidth(width);
						graphics.DrawLine(&pen, x1, y1, x2, y2);
					}
					else
					{
						Color border_color(255, GetRValue(wdli->border_color),GetGValue(wdli->border_color),GetBValue(wdli->border_color));
						Pen   pen_border(border_color);
						switch(wdli->m_draw_mode_2d)
						{
						case wells_draw_list_item::left:
							{
								pen.SetWidth(0.5*width);	
								graphics.DrawLine(&pen, x1-0.25*width, y1, x2-0.25*width, y2);	
								if(wdli->draw2d_border)
									graphics.DrawLine(&pen_border, x1-0.5*width, y1, x2-0.5*width, y2);	
							}
							break;
						case wells_draw_list_item::draw_mode_2d::right:
							{
								pen.SetWidth(0.5*width);	
								graphics.DrawLine(&pen, x1+0.25*width, y1, x2+0.25*width, y2);	
								if(wdli->draw2d_border)
									graphics.DrawLine(&pen_border, x1+0.5*width, y1, x2+0.5*width, y2);	
							}
							break;
						case wells_draw_list_item::draw_mode_2d::both:
							{
								pen.SetWidth(width);	
								graphics.DrawLine(&pen, x1, y1, x2, y2);	
								if(wdli->draw2d_border)
								{
									graphics.DrawLine(&pen_border, x1-0.5*width, y1, x2-0.5*width, y2);	
									graphics.DrawLine(&pen_border, x1+0.5*width, y1, x2+0.5*width, y2);	
								}
							}
							break;
						}
					}



					if (//i_sphere == Well_3D::s_sloj_number_to_save || 
						Well_3D::s_show_all_sloi)// или если показываем все слои
					{
						//отметим слой для сохранения в виде шариков

						COLORREF sphereColor = color;
						Color sphere_color(255, GetRValue(sphereColor),GetGValue(sphereColor),GetBValue(sphereColor));
						Pen      sphere_pen(gdi_color);								

						FillCircle(&graphics, x2, y2, r, sphere_color);							
						DrawCircle(&graphics, x2, y2, r, Color(255, 0,0,0));							
					}

					if (Well_3D::s_use_sloj_names)
					{									
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//====== Наносим цифровую метку устья
						SolidBrush  brush(Color(255, 0, 0, 255));
						FontFamily  fontFamily(L"Times New Roman");
						Font        font(&fontFamily, 10, FontStyleRegular, UnitPixel);

						const int wlen = 2 + 2 * (int)strlen(wegep->nameID.c_str());
						WCHAR * wb = new WCHAR[wlen];
						MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, wegep->nameID.c_str(), -1, wb, wlen );
						graphics.DrawString(wb, -1, &font, PointF(x2, y2), &brush);
						delete wb;
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

					}									
					z_pre = pt.z;
				}
			}
		}
	}		

}




void Well_Laboratory_Analize::DrawGDIplus(Graphics ** select_buffer, Graphics& graphics, map_view * v, Profile3D * on, Well_3D * well, wells_draw_list_item * wdli)
{
	float width = wdli ? wdli->draw_width : 2.0;
//printf("WellColomn::DrawGDIplus_Hydro() well = %s\n", well->GetIDString());
	double dist_to_plane;
	CPoint2 profile;

	//fGL x1; fGL y1;
	fGL x2; fGL y2;

	//fGL r = 2*v->lines_points_radius;
	fGL r = width/2;


	//double z_pre;
	CPoint3 ustje, pt;
	if (well->GetUstje(ustje))
	{
		//z_pre = ustje.z;
		pt = ustje;
//		for (vector<WellElement*>::iterator it = this->well_elements.begin();
//			it != this->well_elements.end(); it++)
		{
			//if ((*it))
			{
				Well_Laboratory_Analize * wlab = this;
				if (wlab && wlab->LabLayerCheckDraw())
				{
					//wegep->key;

					COLORREF color = RGB(0,255,0);
					Color gdi_color(128, GetRValue(color),GetGValue(color),GetBValue(color));
					Pen      pen(gdi_color);							
					//pen.SetWidth(1.0);	

					//Convert3D_To_2D
					//pt.z = z_pre;
					//on->Projection(pt, profile, dist_to_plane);
					//v->ConvertingFromWorldToScreen(profile.x, profile.y, x1, y1);

					//Convert3D_To_2D
					pt.z = wlab->GetZ();
					on->Projection(pt, profile, dist_to_plane);
					v->ConvertingFromWorldToScreen(profile.x, profile.y, x2, y2);

					graphics.DrawLine(&pen, x2-r, y2, x2+r, y2);
#if 1
					//if (//i_sphere == Well_3D::s_sloj_number_to_save || 
					//	Well_3D::s_show_all_sloi)// или если показываем все слои
					{
						//отметим слой для сохранения в виде шариков

						COLORREF sphereColor = color;
						Color sphere_color(255, GetRValue(sphereColor),GetGValue(sphereColor),GetBValue(sphereColor));
						Pen      sphere_pen(gdi_color);								

						FillCircle(&graphics, x2, y2, r, sphere_color);							
						DrawCircle(&graphics, x2, y2, r, Color(255, 0,0,0));

						// Filling Select_buffer

								
						COLORREF selectColor = COLORREF(wlab);
						//Color select_color(GetAValue(selectColor), GetRValue(selectColor),GetGValue(selectColor),GetBValue(selectColor));
						Color select_color1(255, GetRValue(selectColor),GetGValue(selectColor),GetBValue(selectColor));
						Color select_color2(255, GLNAME_MD_TYPE_WELL_ELEMENT, 1, GetAValue(selectColor));
						//Color select_color(0, GetRValue(selectColor),GetGValue(selectColor),GetBValue(selectColor));
						FillCircle(select_buffer[0], x2, y2, r, select_color1);	
						FillCircle(select_buffer[1], x2, y2, r, select_color2);	

						//printf("wlab = %x\n", wlab);
						//printf("selectColor = %x\n", selectColor);

						//BYTE r = GetRValue(selectColor);
						//BYTE g = GetGValue(selectColor);
						//BYTE b = GetBValue(selectColor);
						//BYTE a = GetAValue(selectColor);

						//printf("GetRValue(selectColor) = %x\n", r);
						//printf("GetGValue(selectColor) = %x\n", g);
						//printf("GetBValue(selectColor) = %x\n", b);
						//printf("GetAValue(selectColor) = %x\n", a);

						//printf("RGBA(r,g,b,a) = %x\n", RGBA(r,g,b,a));

						//printf("RGBA(r,g,b,a) = %x\n", RGBA(select_color1.GetRed(),select_color1.GetGreen(),select_color1.GetBlue(),select_color2.GetBlue()));
						

					}
#endif

					string s = wlab->GetLabel(Well_Laboratory_Analize::s_label_type);


					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					//====== Наносим цифровую метку устья
					SolidBrush  brush(Color(255, 0, 0, 255));
					FontFamily  fontFamily(L"Times New Roman");
					Font        font(&fontFamily, 11, FontStyleRegular, UnitPixel);

					const int wlen = 2 + 2 * (int)strlen(s.c_str());
					WCHAR * wb = new WCHAR[wlen];
					MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, s.c_str(), -1, wb, wlen );
					graphics.DrawString(wb, -1, &font, PointF(x2 + r, y2-font.GetHeight(&graphics)), &brush);
					delete wb;
					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

					/*if (Well_3D::s_use_sloj_names)
					{
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//====== Наносим цифровую метку устья
						SolidBrush  brush(Color(255, 0, 0, 255));
						FontFamily  fontFamily(L"Times New Roman");
						Font        font(&fontFamily, 10, FontStyleRegular, UnitPixel);

						const int wlen = 2 + 2 * (int)strlen(whydrop->nameID.c_str());
						WCHAR * wb = new WCHAR[wlen];
						MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, whydrop->nameID.c_str(), -1, wb, wlen );
						graphics.DrawString(wb, -1, &font, PointF(x2, y2), &brush);
						delete wb;
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

					}	//*/								
				}
			}
		}
	}							

}




#endif
void WellColomn::DrawGDIplus(Graphics ** select_buffer, Graphics& graphics, map_view * v, Profile3D * on, Well_3D * well)
{
//printf("WellColomn::DrawGDIplus() well = %s\n", well->GetIDString());
	if (this->m_wdli && this->m_wdli->check_draw)
	{
#if !WELL_ELEMENT_DRAW_GDI_PLUS
		switch(this->w_type)
		{
		case WellElement::type::primitive_ref:
//			well->DrawGDIplus_Primitive(select_buffer, graphics, v, on, this->m_wdli);
			break;
		case WellElement::type::litho_podoshva:
			this->DrawGDIplus_Litho(select_buffer, graphics, v, on, well, this->m_wdli);
			break;
		case WellElement::type::IGE_podoshva:
			this->DrawGDIplus_IGE(select_buffer, graphics, v, on, well, this->m_wdli);
			break;
		case WellElement::type::isSand_podoshva:
			this->DrawGDIplus_IsSand(select_buffer, graphics, v, on, well, this->m_wdli);
			break;
		case WellElement::type::hydro_projavlenie:
			this->DrawGDIplus_Hydro(select_buffer, graphics, v, on, well, this->m_wdli);
			break;
		case WellElement::type::laboratory_analizes:
			this->DrawGDIplus_LaboratoryAnalizes(select_buffer, graphics, v, on, well, this->m_wdli);
			break;
		}
#else
		switch(this->w_type)
		{
		case WellElement::type::primitive_ref:
//				well->DrawGDIplus_Primitive(select_buffer, graphics, v, on, this->m_wdli);
			break;
		default:
			for (vector<WellElement*>::iterator it = this->well_elements.begin();
				it != this->well_elements.end(); it++)
			{
				if ((*it))
				{
					//(*it)->Draw(well);
					(*it)->DrawGDIplus(select_buffer, graphics, v, on, well, this->m_wdli);
				}
			}
		}
#endif
	}
}



void WellColomn::DrawAcad(MyAcad & m_acad, double xProfile, double w, double Height_lin, COLORREF color, double v_scale, double g_scale, double well_hatch_scale, Well_3D * well)
{
	if (this->m_wdli && this->m_wdli->check_draw)
	{
#if !WELL_ELEMENT_DRAW_GDI_PLUS
		switch(this->w_type)
		{
		case WellElement::type::primitive_ref:
//			well->DrawAcad_Primitive(select_buffer, graphics, v, on, this->m_wdli);
			break;
		case WellElement::type::litho_podoshva:
			this->DrawAcad_Litho             (m_acad, xProfile, w, Height_lin, color, v_scale, g_scale, well_hatch_scale, well, this->m_wdli);
			break;
		case WellElement::type::IGE_podoshva:
			this->DrawAcad_IGE               (m_acad, xProfile, w, Height_lin, color, v_scale, g_scale, well_hatch_scale, well, this->m_wdli);
			break;
		case WellElement::type::isSand_podoshva:
			this->DrawAcad_IsSand            (m_acad, xProfile, w, Height_lin, color, v_scale, g_scale, well_hatch_scale, well, this->m_wdli);
			break;
		case WellElement::type::hydro_projavlenie:
			this->DrawAcad_Hydro             (m_acad, xProfile, w, Height_lin, color, v_scale, g_scale, well_hatch_scale, well, this->m_wdli);
			break;
		case WellElement::type::laboratory_analizes:
			this->DrawAcad_LaboratoryAnalizes(m_acad, xProfile, w, Height_lin, color, v_scale, g_scale, well_hatch_scale, well, this->m_wdli);
			break;
		}
#else
		switch(this->w_type)
		{
		case WellElement::type::primitive_ref:
//				well->DrawGDIplus_Primitive(select_buffer, graphics, v, on, this->m_wdli);
			break;
		default:
			for (vector<WellElement*>::iterator it = this->well_elements.begin();
				it != this->well_elements.end(); it++)
			{
				if ((*it))
				{
					//(*it)->Draw(well);
					(*it)->DrawGDIplus(select_buffer, graphics, v, on, well, this->m_wdli);
				}
			}
		}
#endif
	}
}

void Well_Litho_Podoshva::Drawing(Well_3D * well)
{
#if 1
#else
	float width = wdli ? wdli->draw_width : 2.0;
//printf("WellColomn::DrawGDIplus_IGE well = %s\n", well->GetIDString());
	double dist_to_plane;
	CPoint2 profile;

	fGL x1; fGL y1;
	fGL x2; fGL y2;

	Graphics graphics(v->GetHDC());
	fGL r = v->lines_points_radius;

	double z_pre;
	CPoint3 ustje, pt;
	if (well->GetUstje(ustje))
	{
		//printf("WellColomn::DrawGDIplus_IGE well->GetUstje() this->well_elements.size() = %u\n", this->well_elements.size());
		z_pre = ustje.z;
		pt = ustje;
		for (vector<WellElement*>::iterator it = this->well_elements.begin();
			it != this->well_elements.end(); it++)
		{
//printf("WellColomn::DrawGDIplus_IGE for\n");
			if ((*it))
			{
//printf("WellColomn::DrawGDIplus_IGE if\n");
				Well_Litho_Podoshva * wegep = dynamic_cast<Well_Litho_Podoshva *>((*it));
				if (wegep)
				{
					//wegep->key;
					COLORREF color = wegep->GetColor();
					//printf("z_pre = %f wegep->GetZ() = %f color = %d\n", z_pre, wegep->GetZ(), color);

					Color gdi_color(255, GetRValue(color),GetGValue(color),GetBValue(color));


					//Convert3D_To_2D
					pt.z = z_pre;
					on->Projection(pt, profile, dist_to_plane);
					v->ConvertingFromWorldToScreen(profile.x, profile.y, x1, y1);

					//Convert3D_To_2D
					pt.z = wegep->GetZ();
					on->Projection(pt, profile, dist_to_plane);
					v->ConvertingFromWorldToScreen(profile.x, profile.y, x2, y2);

					Pen   pen(gdi_color);
						
					if (!wdli)
					{
						pen.SetWidth(width);
						graphics.DrawLine(&pen, x1, y1, x2, y2);
					}
					else
					{
						Color border_color(255, GetRValue(wdli->border_color),GetGValue(wdli->border_color),GetBValue(wdli->border_color));
						Pen   pen_border(border_color);
						switch(wdli->m_draw_mode_2d)
						{
						case wells_draw_list_item::left:
							{
								pen.SetWidth(0.5*width);	
								graphics.DrawLine(&pen, x1-0.25*width, y1, x2-0.25*width, y2);	
								if(wdli->draw2d_border)
									graphics.DrawLine(&pen_border, x1-0.5*width, y1, x2-0.5*width, y2);	
							}
							break;
						case wells_draw_list_item::draw_mode_2d::right:
							{
								pen.SetWidth(0.5*width);	
								graphics.DrawLine(&pen, x1+0.25*width, y1, x2+0.25*width, y2);	
								if(wdli->draw2d_border)
									graphics.DrawLine(&pen_border, x1+0.5*width, y1, x2+0.5*width, y2);	
							}
							break;
						case wells_draw_list_item::draw_mode_2d::both:
							{
								pen.SetWidth(width);	
								graphics.DrawLine(&pen, x1, y1, x2, y2);	
								if(wdli->draw2d_border)
								{
									graphics.DrawLine(&pen_border, x1-0.5*width, y1, x2-0.5*width, y2);	
									graphics.DrawLine(&pen_border, x1+0.5*width, y1, x2+0.5*width, y2);	
								}
							}
							break;
						}
					}



					if (//i_sphere == Well_3D::s_sloj_number_to_save || 
						Well_3D::s_show_all_sloi)// или если показываем все слои
					{
						//отметим слой для сохранения в виде шариков

						COLORREF sphereColor = color;
						Color sphere_color(255, GetRValue(sphereColor),GetGValue(sphereColor),GetBValue(sphereColor));
						Pen      sphere_pen(gdi_color);								

						FillCircle(&graphics, x2, y2, r, sphere_color);							
						DrawCircle(&graphics, x2, y2, r, Color(255, 0,0,0));							
					}

					if (Well_3D::s_use_sloj_names)
					{									
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//====== Наносим цифровую метку устья
						SolidBrush  brush(Color(255, 0, 0, 255));
						FontFamily  fontFamily(L"Times New Roman");
						Font        font(&fontFamily, 10, FontStyleRegular, UnitPixel);

						const int wlen = 2 + 2 * (int)strlen(wegep->nameID.c_str());
						WCHAR * wb = new WCHAR[wlen];
						MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, wegep->nameID.c_str(), -1, wb, wlen );
						graphics.DrawString(wb, -1, &font, PointF(x2, y2), &brush);
						delete wb;
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

					}									
					z_pre = pt.z;
				}
			}
		}
	}
#endif
}



void Well_IGE_Podoshva::Drawing(Well_3D * well)
{
#if 1
#else
	float width = wdli ? wdli->draw_width : 2.0;
//printf("WellColomn::DrawGDIplus_IGE well = %s\n", well->GetIDString());
	double dist_to_plane;
	CPoint2 profile;

	fGL x1; fGL y1;
	fGL x2; fGL y2;

	Graphics graphics(v->GetHDC());
	fGL r = v->lines_points_radius;

	double z_pre;
	CPoint3 ustje, pt;
	if (well->GetUstje(ustje))
	{
		//printf("WellColomn::DrawGDIplus_IGE well->GetUstje() this->well_elements.size() = %u\n", this->well_elements.size());
		z_pre = ustje.z;
		pt = ustje;
		for (vector<WellElement*>::iterator it = this->well_elements.begin();
			it != this->well_elements.end(); it++)
		{
//printf("WellColomn::DrawGDIplus_IGE for\n");
			if ((*it))
			{
//printf("WellColomn::DrawGDIplus_IGE if\n");
				Well_IGE_Podoshva * wegep = dynamic_cast<Well_IGE_Podoshva *>((*it));
				if (wegep)
				{
					//wegep->key;
					COLORREF color = wegep->GetColor();
					//printf("z_pre = %f wegep->GetZ() = %f color = %d\n", z_pre, wegep->GetZ(), color);

					Color gdi_color(255, GetRValue(color),GetGValue(color),GetBValue(color));


					//Convert3D_To_2D
					pt.z = z_pre;
					on->Projection(pt, profile, dist_to_plane);
					v->ConvertingFromWorldToScreen(profile.x, profile.y, x1, y1);

					//Convert3D_To_2D
					pt.z = wegep->GetZ();
					on->Projection(pt, profile, dist_to_plane);
					v->ConvertingFromWorldToScreen(profile.x, profile.y, x2, y2);

					Pen   pen(gdi_color);
						
					if (!wdli)
					{
						pen.SetWidth(width);
						graphics.DrawLine(&pen, x1, y1, x2, y2);
					}
					else
					{
						Color border_color(255, GetRValue(wdli->border_color),GetGValue(wdli->border_color),GetBValue(wdli->border_color));
						Pen   pen_border(border_color);
						switch(wdli->m_draw_mode_2d)
						{
						case wells_draw_list_item::left:
							{
								pen.SetWidth(0.5*width);	
								graphics.DrawLine(&pen, x1-0.25*width, y1, x2-0.25*width, y2);	
								if(wdli->draw2d_border)
									graphics.DrawLine(&pen_border, x1-0.5*width, y1, x2-0.5*width, y2);	
							}
							break;
						case wells_draw_list_item::draw_mode_2d::right:
							{
								pen.SetWidth(0.5*width);	
								graphics.DrawLine(&pen, x1+0.25*width, y1, x2+0.25*width, y2);	
								if(wdli->draw2d_border)
									graphics.DrawLine(&pen_border, x1+0.5*width, y1, x2+0.5*width, y2);	
							}
							break;
						case wells_draw_list_item::draw_mode_2d::both:
							{
								pen.SetWidth(width);	
								graphics.DrawLine(&pen, x1, y1, x2, y2);	
								if(wdli->draw2d_border)
								{
									graphics.DrawLine(&pen_border, x1-0.5*width, y1, x2-0.5*width, y2);	
									graphics.DrawLine(&pen_border, x1+0.5*width, y1, x2+0.5*width, y2);	
								}
							}
							break;
						}
					}



					if (//i_sphere == Well_3D::s_sloj_number_to_save || 
						Well_3D::s_show_all_sloi)// или если показываем все слои
					{
						//отметим слой для сохранения в виде шариков

						COLORREF sphereColor = color;
						Color sphere_color(255, GetRValue(sphereColor),GetGValue(sphereColor),GetBValue(sphereColor));
						Pen      sphere_pen(gdi_color);								

						FillCircle(&graphics, x2, y2, r, sphere_color);							
						DrawCircle(&graphics, x2, y2, r, Color(255, 0,0,0));							
					}

					if (Well_3D::s_use_sloj_names)
					{									
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//====== Наносим цифровую метку устья
						SolidBrush  brush(Color(255, 0, 0, 255));
						FontFamily  fontFamily(L"Times New Roman");
						Font        font(&fontFamily, 10, FontStyleRegular, UnitPixel);

						const int wlen = 2 + 2 * (int)strlen(wegep->nameID.c_str());
						WCHAR * wb = new WCHAR[wlen];
						MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, wegep->nameID.c_str(), -1, wb, wlen );
						graphics.DrawString(wb, -1, &font, PointF(x2, y2), &brush);
						delete wb;
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

					}									
					z_pre = pt.z;
				}
			}
		}
	}
#endif
}



void Well_Hydro_Projavlenie::Drawing(Well_3D * well)
{
#if 1
#else
	float width = wdli ? wdli->draw_width : 2.0;
//printf("WellColomn::DrawGDIplus_Hydro() well = %s\n", well->GetIDString());
	double dist_to_plane;
	CPoint2 profile;

	//fGL x1; fGL y1;
	fGL x2; fGL y2;

	Graphics graphics(v->GetHDC());
	//fGL r = 2*v->lines_points_radius;
	fGL r = width/2;


	//double z_pre;
	CPoint3 ustje, pt;
	if (well->GetUstje(ustje))
	{
		//z_pre = ustje.z;
		pt = ustje;
		for (vector<WellElement*>::iterator it = this->well_elements.begin();
			it != this->well_elements.end(); it++)
		{
			if ((*it))
			{
				Well_Hydro_Projavlenie * whydrop = dynamic_cast<Well_Hydro_Projavlenie *>((*it));
				if (whydrop)
				{
					//wegep->key;

					COLORREF color = RGB(0,0,255);
					Color gdi_color(128, GetRValue(color),GetGValue(color),GetBValue(color));
					Pen      pen(gdi_color);							
					//pen.SetWidth(1.0);	

					//Convert3D_To_2D
					//pt.z = z_pre;
					//on->Projection(pt, profile, dist_to_plane);
					//v->ConvertingFromWorldToScreen(profile.x, profile.y, x1, y1);

					//Convert3D_To_2D
					pt.z = whydrop->GetZ();
					on->Projection(pt, profile, dist_to_plane);
					v->ConvertingFromWorldToScreen(profile.x, profile.y, x2, y2);

					graphics.DrawLine(&pen, x2-r, y2, x2+r, y2);
#if 0
					//if (//i_sphere == Well_3D::s_sloj_number_to_save || 
					//	Well_3D::s_show_all_sloi)// или если показываем все слои
					{
						//отметим слой для сохранения в виде шариков

						COLORREF sphereColor = color;
						Color sphere_color(255, GetRValue(sphereColor),GetGValue(sphereColor),GetBValue(sphereColor));
						Pen      sphere_pen(gdi_color);								

						FillCircle(&graphics, x2, y2, r, sphere_color);							
						DrawCircle(&graphics, x2, y2, r, Color(255, 0,0,0));							
					}
#endif
					/*if (Well_3D::s_use_sloj_names)
					{									
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//====== Наносим цифровую метку устья
						SolidBrush  brush(Color(255, 0, 0, 255));
						FontFamily  fontFamily(L"Times New Roman");
						Font        font(&fontFamily, 10, FontStyleRegular, UnitPixel);

						const int wlen = 2 + 2 * (int)strlen(whydrop->nameID.c_str());
						WCHAR * wb = new WCHAR[wlen];
						MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, whydrop->nameID.c_str(), -1, wb, wlen );
						graphics.DrawString(wb, -1, &font, PointF(x2, y2), &brush);
						delete wb;
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

					}	*/								
				}
			}
		}
	}							
#endif
}



void Well_IsSand_Podoshva::Drawing(Well_3D * well)
{
#if 1
#else
	float width = wdli ? wdli->draw_width : 2.0;

	double dist_to_plane;
	CPoint2 profile;

	fGL x1; fGL y1;
	fGL x2; fGL y2;

	Graphics graphics(v->GetHDC());
	fGL r = v->lines_points_radius;


	double z_pre;
	CPoint3 ustje, pt;
	if (well->GetUstje(ustje))
	{
		z_pre = ustje.z;
		pt = ustje;
		for (vector<WellElement*>::iterator it = this->well_elements.begin();
			it != this->well_elements.end(); it++)
		{
			if ((*it))
			{
				Well_IsSand_Podoshva * wegep = dynamic_cast<Well_IsSand_Podoshva *>((*it));
				if (wegep)
				{
					//wegep->key;

					COLORREF color = wegep->GetColor();
					Color gdi_color(255, GetRValue(color),GetGValue(color),GetBValue(color));


					//Convert3D_To_2D
					pt.z = z_pre;
					on->Projection(pt, profile, dist_to_plane);
					v->ConvertingFromWorldToScreen(profile.x, profile.y, x1, y1);

					//Convert3D_To_2D
					pt.z = wegep->GetZ();
					on->Projection(pt, profile, dist_to_plane);
					v->ConvertingFromWorldToScreen(profile.x, profile.y, x2, y2);

					Pen   pen(gdi_color);
						
					if (!wdli)
					{
						pen.SetWidth(width);
						graphics.DrawLine(&pen, x1, y1, x2, y2);
					}
					else
					{
						Color border_color(255, GetRValue(wdli->border_color),GetGValue(wdli->border_color),GetBValue(wdli->border_color));
						Pen   pen_border(border_color);
						switch(wdli->m_draw_mode_2d)
						{
						case wells_draw_list_item::left:
							{
								pen.SetWidth(0.5*width);	
								graphics.DrawLine(&pen, x1-0.25*width, y1, x2-0.25*width, y2);	
								if(wdli->draw2d_border)
									graphics.DrawLine(&pen_border, x1-0.5*width, y1, x2-0.5*width, y2);	
							}
							break;
						case wells_draw_list_item::draw_mode_2d::right:
							{
								pen.SetWidth(0.5*width);	
								graphics.DrawLine(&pen, x1+0.25*width, y1, x2+0.25*width, y2);	
								if(wdli->draw2d_border)
									graphics.DrawLine(&pen_border, x1+0.5*width, y1, x2+0.5*width, y2);	
							}
							break;
						case wells_draw_list_item::draw_mode_2d::both:
							{
								pen.SetWidth(width);	
								graphics.DrawLine(&pen, x1, y1, x2, y2);	
								if(wdli->draw2d_border)
								{
									graphics.DrawLine(&pen_border, x1-0.5*width, y1, x2-0.5*width, y2);	
									graphics.DrawLine(&pen_border, x1+0.5*width, y1, x2+0.5*width, y2);	
								}
							}
							break;
						}
					}



					if (//i_sphere == Well_3D::s_sloj_number_to_save || 
						Well_3D::s_show_all_sloi)// или если показываем все слои
					{
						//отметим слой для сохранения в виде шариков

						COLORREF sphereColor = color;
						Color sphere_color(255, GetRValue(sphereColor),GetGValue(sphereColor),GetBValue(sphereColor));
						Pen      sphere_pen(gdi_color);								

						FillCircle(&graphics, x2, y2, r, sphere_color);							
						DrawCircle(&graphics, x2, y2, r, Color(255, 0,0,0));							
					}

					if (Well_3D::s_use_sloj_names)
					{									
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//====== Наносим цифровую метку устья
						SolidBrush  brush(Color(255, 0, 0, 255));
						FontFamily  fontFamily(L"Times New Roman");
						Font        font(&fontFamily, 10, FontStyleRegular, UnitPixel);

						const int wlen = 2 + 2 * (int)strlen(wegep->nameID.c_str());
						WCHAR * wb = new WCHAR[wlen];
						MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, wegep->nameID.c_str(), -1, wb, wlen );
						graphics.DrawString(wb, -1, &font, PointF(x2, y2), &brush);
						delete wb;
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

					}									
					z_pre = pt.z;
				}
			}
		}
	}		
#endif
}




void Well_Laboratory_Analize::Drawing(Well_3D * well)
{
	CPoint3 ustje, pt;
	if (well->GetUstje(ustje))
	{
		pt = ustje;
		pt.z = this->GetZp();
		if (this->lab_number && this->lab_number->GetLabLayer())
		{
			LabLayer * ll = (LabLayer *)this->lab_number->GetLabLayer();
			if (ll)
			{
				Laboratory * lab = (Laboratory *)ll->GetLaboratory();
				if (lab)
				{
					SurfDoc * m_pSurfDoc = (SurfDoc *)lab->GetDoc();
					if (m_pSurfDoc)
					{

						double vz = m_pSurfDoc->m_zoomZ * (pt.z - m_pSurfDoc->m_zd_zoom_center);
						double vy = m_pSurfDoc->m_zoomY * (pt.y - m_pSurfDoc->m_yd_zoom_center);
						double vx = m_pSurfDoc->m_zoomX * (pt.x - m_pSurfDoc->m_xd_zoom_center);

						//glPushName(GLNAME_MD_TYPE_LAB_ANALIZ); glPushName((i32u) wlab);
						glPushName(GLNAME_MD_TYPE_WELL_ELEMENT); glPushName((i32u) this);

						//отметим слой для сохранения в виде шариков

						COLORREF sphereColor = RGB(0,255,0);
					
						glColor3ub (GetRValue(sphereColor),GetGValue(sphereColor),GetBValue(sphereColor)); 

						GLUquadricObj* pSphere = gluNewQuadric();
						gluQuadricDrawStyle(pSphere, GLU_FILL);
						glPushMatrix();//перейдём к новым координатам, сохранив старые
						
						glTranslated(
							vx, 
							vy, 
							vz
							);

						gluSphere(pSphere, 
							m_pSurfDoc->m_sphere_radius, 
							m_pSurfDoc->m_sphere_slices, //The number of subdivisions around the z-axis (similar to lines of longitude). 					
							m_pSurfDoc->m_sphere_stacks  //The number of subdivisions along the z-axis (similar to lines of latitude). 
							) ;//рисуем сферу 
						glPopMatrix(); //возвращаемся к старым координатам 
						gluDeleteQuadric(pSphere);	

						glPopName(); glPopName();
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//====== Наносим цифровую метку анализа
						// sprintf(str, "X %s", spower);
						// move 
						glRasterPos3d(vx + m_pSurfDoc->m_sphere_radius, vy + m_pSurfDoc->m_sphere_radius, vz + m_pSurfDoc->m_sphere_radius ); 
						// set up for a string-drawing display List call 
						// Display a string 
						glListBase(FIRST_FONT_LIST_BITMAPS); // Indicates the start of display lists for the glyphs 
						// Draw the characters in a string 
						string s = this->GetLabel(Well_Laboratory_Analize::s_label_type);
						glCallLists(strlen(s.c_str()), GL_UNSIGNED_BYTE, s.c_str()); 

						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						glListBase(0);
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

					}							
				}
			}
		}
	}			
}
string Well_Laboratory_Analize::GetLabel(Well_Laboratory_Analize::label_type lt)
{
	string s = "";
	switch (lt)
	{
	case Well_Laboratory_Analize::label_type::lab_layer_id:
		s = this->Lab_Layer_ID; 
		break;
	case Well_Laboratory_Analize::label_type::lab_layer_number:
		s = this->Lab_Layer_Number; 
		break;
	case Well_Laboratory_Analize::label_type::lab_number_id:
		s = this->Lab_Number_ID; 
		break;
	case Well_Laboratory_Analize::label_type::soils_description:
		s = this->lab_number->GetSoilDescription(false); 
		break;
	}
	return s;

}
const char * Well_Laboratory_Analize::LabelTypeToString(Well_Laboratory_Analize::label_type lt)
{
	switch (lt)
	{
	case Well_Laboratory_Analize::label_type::lab_layer_id:
		return "Lab_Layer_ID"; 
	case Well_Laboratory_Analize::label_type::lab_layer_number:
		return "Lab_Layer_Number"; 
	case Well_Laboratory_Analize::label_type::lab_number_id:
		return "Lab_Number_ID"; 
	case Well_Laboratory_Analize::label_type::soils_description:
		return "SoilDescription"; 
	}
	return "";
}

void Well_Laboratory_Analize::OnPaint()
{
	if (this->LabLayerCheckDraw())
		this->WellElement::OnPaint();
}
void WellColomn::OnPaint(Well_3D * well)
{
	switch(this->w_type)
	{
	case WellElement::type::primitive_ref:
		well->OnPaintPrimitive();
		break;
	default:
		for (vector<WellElement*>::iterator it = this->well_elements.begin();
			it != this->well_elements.end(); it++)
		{
			if ((*it))
			{
				(*it)->OnPaint();
			}
		}
	}
}
void WellColomn::Draw(Well_3D * well)
{
	switch(this->w_type)
	{
	case WellElement::type::primitive_ref:
		well->Draw_Primitive(this->m_wdli);
		break;
	default:
		for (vector<WellElement*>::iterator it = this->well_elements.begin();
			it != this->well_elements.end(); it++)
		{
			if ((*it))
			{
				(*it)->Draw(well);
			}
		}
	}
}

void WellColomn::ReDraw(Well_3D * well)
{
	switch(this->w_type)
	{
	case WellElement::type::primitive_ref:
		well->ReDraw_Primitive(this->m_wdli);
		break;
	default:
		for (vector<WellElement*>::iterator it = this->well_elements.begin();
			it != this->well_elements.end(); it++)
		{
			if ((*it))
			{
				(*it)->ReDraw(well);
			}
		}
	}
}
void WellColomn::SaveIGEToDB(long ID_KT, double ustje_z)
{
	for (vector<WellElement*>::iterator it = this->well_elements.begin();
		it != this->well_elements.end(); it++)
	{
		if ((*it))
		{
			Well_IGE_Podoshva * wigep = dynamic_cast<Well_IGE_Podoshva *>((*it));
			if (wigep)
			{
				string key;//IGE
				if (this->m_pSurfDoc && this->m_pSurfDoc->GetLabDoc() && this->m_pSurfDoc->GetIGEkey(wigep->nameID, key))
				{
					CString IGE = key.c_str();

					//wigep->SetKey(key);
					double H0 = ustje_z - wigep->zk;
					double H1 = ustje_z - wigep->zp;
					if (H0 == H1)
					{
						CString s;
						s.Format("Warning H0 %f == H1 %f\nID_KT = %d IGE = %s", H0, H1, ID_KT, IGE);
						MessageBox(0, s, "SaveIGEToDB", 0);
					}
					bool bUnEdited = false;
					this->m_pSurfDoc->GetLabDoc()->AddLito(bUnEdited, this->m_pSurfDoc->Get_ID_OBJ(), ID_KT, IGE, H0, H1);
				}
			}
		}
	}
}
void WellColomn::SaveLitoToDB(long ID_KT, double ustje_z)
{
	for (vector<WellElement*>::iterator it = this->well_elements.begin();
		it != this->well_elements.end(); it++)
	{
		if ((*it))
		{
			Well_Litho_Podoshva * wlitp = dynamic_cast<Well_Litho_Podoshva *>((*it));
			if (wlitp)
			{
				string key;
				if (this->m_pSurfDoc && this->m_pSurfDoc->GetLabDoc() && this->m_pSurfDoc->GetLithoKey(wlitp->nameID, key))
				{
					CString IGE = key.c_str();
					//wlitp->SetKey(key);
					double H0 = ustje_z - wlitp->zk;
					double H1 = ustje_z - wlitp->zp;
					if (H0 == H1)
					{
						CString s;
						s.Format("Warning H0 %f == H1 %f\nID_KT = %d IGE = %s", H0, H1, ID_KT, IGE);
						MessageBox(0, s, "SaveLitoToDB", 0);
					}
					bool bUnEdited = true;
					this->m_pSurfDoc->GetLabDoc()->AddLito(bUnEdited, this->m_pSurfDoc->Get_ID_OBJ(), ID_KT, IGE, H0, H1);
				}
			}
		}
	}
}
void WellElement::EditLitoInDB(SurfDoc * pSurfDoc, long ID_KT, double ustje_z, double key_H0, bool edit_H0, bool edit_H1)
{
	//Well_Litho_Podoshva * wlitp = dynamic_cast<Well_Litho_Podoshva *>(this);
	WellElement * wlitp = this;
	if (wlitp)
	{
//		string key;
		if (pSurfDoc && pSurfDoc->GetLabDoc() 
//			&& this->m_pSurfDoc->GetLithoKey(wlitp->nameID, key)
			)
		{
//			CString IGE = wlitp->GetKey().c_str();
			//wlitp->SetKey(key);
			double H0 = ustje_z - wlitp->zk;
			double H1 = ustje_z - wlitp->zp;
			if (H0 == H1)
			{
				CString s;
				s.Format("Warning H0 %f == H1 %f\nID_KT = %d", H0, H1, ID_KT);
				MessageBox(0, s, "EditLitoInDB", 0);
			}
			pSurfDoc->GetLabDoc()->EditLito(pSurfDoc->Get_ID_OBJ(), ID_KT, key_H0, H0, H1, edit_H0, edit_H1);
		}
	}
}






void WellColomn::SetWellElementsIGEkeys()
{
	printf("WellColomn::SetWellElementsIGEkeys()\n");
	printf("list of well Element:\n");

	for (vector<WellElement*>::iterator it = this->well_elements.begin();
		it != this->well_elements.end(); it++)
	{
		if ((*it))
		{
			Well_IGE_Podoshva * wigep = dynamic_cast<Well_IGE_Podoshva *>((*it));
			if (wigep)
			{
				printf("nameID = %s key = %s zk = %f zp = %f\n", 
					wigep->nameID.c_str(),
					wigep->GetKey().c_str(),
					wigep->GetZk(),
					wigep->GetZp()
					);

				string key;
				if (this->m_pSurfDoc && this->m_pSurfDoc->GetIGEkey(wigep->nameID, key))
				{
					wigep->SetKey(key);
				}
			}
		}
	}
}

void WellColomn::SetColorFromIGE()
{
	for (vector<WellElement*>::iterator it = this->well_elements.begin();
		it != this->well_elements.end(); it++)
	{
		if ((*it))
		{
			Well_IGE_Podoshva * wigep = dynamic_cast<Well_IGE_Podoshva *>((*it));
			if (wigep)
			{
				if (this->m_pSurfDoc)
				{
					EngineerGeoElement * eng = this->m_pSurfDoc->FindEngineerGeoElement(wigep->GetKey());
					if(eng)
					{
						wigep->SetColor(eng->GetColor());
					}
				}
			}
		}
	}
}

void WellColomn::SetWellElementsLithoKeys()
{
	for (vector<WellElement*>::iterator it = this->well_elements.begin();
		it != this->well_elements.end(); it++)
	{
		if ((*it))
		{
			Well_Litho_Podoshva * wlitp = dynamic_cast<Well_Litho_Podoshva *>((*it));
			if (wlitp)
			{
				string key;
				if (this->m_pSurfDoc && this->m_pSurfDoc->GetLithoKey(wlitp->nameID, key))
				{
					wlitp->SetKey(key);
				}
			}
		}
	}
}
void To_GridData(WellColomn * pWellColomn, WellElement * pWellElem, GridData * pData, BYTE podoshva)
{
	if (pWellElem)
	{
		CPoint3 pt3;
		if (pWellColomn 
			&& pWellColomn->GetWell()
			&& pWellColomn->GetWell()->GetUstje(pt3))
		{
			if (pData)
			{
				COLORREF color = 0;
				string name = pWellElem->GetNameID();
				switch(pWellElem->w_type)
				{
				case WellElement::type::undefined_well_element:
					{
					}
					break;
				case WellElement::type::primitive_ref:
					{
					}
					break;
				case WellElement::type::litho_podoshva:
					{
						Well_Litho_Podoshva * wlitp = dynamic_cast<Well_Litho_Podoshva *>(pWellElem);
						if(wlitp)
						{
							name = wlitp->GetKey();
							color = wlitp->GetColor();
						}
					}
					break;
				case WellElement::type::IGE_podoshva:
					{
						Well_IGE_Podoshva * wigep = dynamic_cast<Well_IGE_Podoshva *>(pWellElem);
						if(wigep)
						{
							name = wigep->GetKey();
							color = wigep->GetColor();
						}
					}
					break;
				case WellElement::type::isSand_podoshva:
					{						
						Well_IsSand_Podoshva * wissp = dynamic_cast<Well_IsSand_Podoshva *>(pWellElem);
						if(wissp)
						{
							if(wissp->IsSand())
							{
								name = "подошва песчаных грунтов";
								color = RGB(255,255,0);
							}
							else
							{
								name = "подошва пылевато-глинистых грунтов";
								color = RGB(128, 64, 0);
							}
						}
					}
					break;
				case WellElement::type::hydro_projavlenie:
					{						
						Well_Hydro_Projavlenie * wigep = dynamic_cast<Well_Hydro_Projavlenie *>(pWellElem);
						if(wigep)
						{
							name = wigep->Ustanovlen() ? "вода установилась" : "вода появилась";
							color = RGB(0, 0, 255);
						}					
					}
					break;
				case WellElement::type::laboratory_analizes:
					{
					}
					break;
				}

				pt3.z = podoshva == 2 ? pWellElem->GetZk() : pWellElem->GetZp();
				ThePoint3D * the_point = pData->AddInput(pt3, color);
				pData->SetName(name.c_str());
				
				if (podoshva == 2)
				{
					pWellElem->grid_data_point_zk.id_surf = pData->id_surf;
					pWellElem->grid_data_point_zk.id_point = the_point->id_point;
				}
				else
				{
					pWellElem->grid_data_point_zp.id_surf = pData->id_surf;
					pWellElem->grid_data_point_zp.id_point = the_point->id_point;
				}
			}		
		}
	}
}					
int WellColomn::LithoPodoshvaHowMany(string geo_element_key)
{
	int n = 0;
	for (int i = 0; i < int(this->well_elements.size()) - 1; i++)
		// отличаем забой от подошвы - забой не включаем в расчёт
	{
		Well_Litho_Podoshva * wlitp = dynamic_cast<Well_Litho_Podoshva *>(this->well_elements[i]);
		if (wlitp)
		{
			if (!strcmp(wlitp->key.c_str(), geo_element_key.c_str()))
			{
				n++;
			}
		}
	}
	return n;
}


int WellColomn::IGEPodoshvaHowMany(string geo_element_key)
{
	int n = 0;
	for (int i = 0; i < int(this->well_elements.size()) - 1; i++)
		// отличаем забой от подошвы - забой не включаем в расчёт
	{
		Well_IGE_Podoshva * wlitp = dynamic_cast<Well_IGE_Podoshva *>(this->well_elements[i]);
		if (wlitp)
		{
			if (!strcmp(wlitp->key.c_str(), geo_element_key.c_str()))
			{
				n++;
			}
		}
	}
	return n;
}

void WellColomn::HydroProjavlenieHowMany(map<long, long> &gorizonts, bool ust)
{
	for (vector<WellElement*>::iterator it = this->well_elements.begin();
		it != this->well_elements.end(); it++)
	{
		if ((*it))
		{
			Well_Hydro_Projavlenie * wlitp = dynamic_cast<Well_Hydro_Projavlenie *>((*it));
			if (wlitp)
			{
				if (wlitp->Ustanovlen() == ust)
				{
					gorizonts.insert(map<long, long>::value_type(wlitp->Horizont(), wlitp->Horizont()));
				}
			}
		}
	}
}

void WellColomn::LithoPodoshvaToGridData(int isurf, BYTE podoshva, string geo_element_key, GridData * pData, bool reverse)
{
	int i_surf = 0;
	if (reverse)
	{
		for (int i = int(this->well_elements.size()) - 2; i >= 0; i--)
			// отличаем забой от подошвы - забой не включаем в расчёт
		{
			Well_Litho_Podoshva * wlitp = dynamic_cast<Well_Litho_Podoshva *>(this->well_elements[i]);
			if (wlitp)
			{
				if (!strcmp(wlitp->key.c_str(), geo_element_key.c_str()))
				{
					if (isurf == i_surf)
						To_GridData(this, wlitp, pData, podoshva);
					i_surf++;
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < int(this->well_elements.size()) - 1; i++)
			// отличаем забой от подошвы - забой не включаем в расчёт
		{
			Well_Litho_Podoshva * wlitp = dynamic_cast<Well_Litho_Podoshva *>(this->well_elements[i]);
			if (wlitp)
			{
				if (!strcmp(wlitp->key.c_str(), geo_element_key.c_str()))
				{
					if (isurf == i_surf)
						To_GridData(this, wlitp, pData, podoshva);
					i_surf++;
				}
			}
		}
	}
}


void WellColomn::IGEZabojToGridData(string geo_element_key, GridData * pData)
{
	int i = int(this->well_elements.size()) - 1; 

	if (i >= 0 && i < this->well_elements.size())
	{
		Well_IGE_Podoshva * wlitp = dynamic_cast<Well_IGE_Podoshva *>(this->well_elements[i]);
		if (wlitp)
		{
			if (!strcmp(wlitp->key.c_str(), geo_element_key.c_str()))
			{					
				To_GridData(this, wlitp, pData, 255);
			}
		}
	}
}

void WellColomn::IGEPodoshvaToGridData(int isurf, BYTE podoshva, string geo_element_key, GridData * pData, bool reverse)
{
	int i_surf = 0;
	if (reverse)
	{
		for (int i = int(this->well_elements.size()) - 2; i >= 0; i--)
			// отличаем забой от подошвы - забой не включаем в расчёт
		{
			Well_IGE_Podoshva * wlitp = dynamic_cast<Well_IGE_Podoshva *>(this->well_elements[i]);
			if (wlitp)
			{
				if (!strcmp(wlitp->key.c_str(), geo_element_key.c_str()))
				{					
					if (isurf == i_surf)
						To_GridData(this, wlitp, pData, podoshva);
					i_surf++;
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < int(this->well_elements.size()) - 1; i++)
			// отличаем забой от подошвы - забой не включаем в расчёт
		{
			Well_IGE_Podoshva * wlitp = dynamic_cast<Well_IGE_Podoshva *>(this->well_elements[i]);
			if (wlitp)
			{
				if (!strcmp(wlitp->key.c_str(), geo_element_key.c_str()))
				{
					if (isurf == i_surf)
						To_GridData(this, wlitp, pData, podoshva);
					i_surf++;
				}
			}
		}
	}
}

void WellColomn::HydroProjavlenieToGridData(long horizont, bool ust, GridData * pData)
{
	for (vector<WellElement*>::iterator it = this->well_elements.begin();
		it != this->well_elements.end(); it++)
	{
		if ((*it))
		{
			Well_Hydro_Projavlenie * wlitp = dynamic_cast<Well_Hydro_Projavlenie *>((*it));
			if (wlitp)
			{
				if (wlitp->Ustanovlen() == ust && horizont == wlitp->Horizont() )
				{
					To_GridData(this, wlitp, pData, 1);
				}
			}
		}
	}
}
void WellColomn::SetColorFromLitho()
{
	for (vector<WellElement*>::iterator it = this->well_elements.begin();
		it != this->well_elements.end(); it++)
	{
		if ((*it))
		{
			Well_Litho_Podoshva * wlitp = dynamic_cast<Well_Litho_Podoshva *>((*it));
			if (wlitp)
			{
				if (this->m_pSurfDoc)
				{
					LithoGeoElement * lith = this->m_pSurfDoc->FindLithoGeoElement(wlitp->GetKey());
					if(lith)
					{
						wlitp->SetColor(lith->GetColor());
					}
				}
			}
		}
	}
}

void wells_draw_list_item::Serialize(Archive& ar)
{
	if (ar.IsStoring())
	{
		ar << version;

		switch (version)
		{
		case 3:
			{
				//ar << ???;
				ar << draw2d_sloj_name;
			}
		case 2:
			{
				//ar << ???;
				int ob_m_draw_mode_2d = m_draw_mode_2d;
				ar << ob_m_draw_mode_2d;

				ar << draw2d_border;
				ar << border_color;
			}
		case 1:
			{
				ar << this->id;
				ar << this->w_type;
				ar << this->check_draw;
				ar << this->draw_width;
				ar << this->my_name;
			}
			break;
		default:
			{
				throw VersionException(version, VersionException::cannot_store, Object::object_type::undefined);
			}
			break;
		}
	}
	else
	{
		ar >> version;
		switch (version)
		{
		case 3:
			{
				//ar >> ???;
				ar >> draw2d_sloj_name;
			}
		case 2:
			{
				int ob_m_draw_mode_2d;
				ar >> ob_m_draw_mode_2d;
				m_draw_mode_2d = wells_draw_list_item::draw_mode_2d(ob_m_draw_mode_2d);
				
				ar >> draw2d_border;
				ar >> border_color;		
			}
		case 1:
			{
				ar >> this->id;
				ar >> this->w_type;
				ar >> this->check_draw;
				ar >> this->draw_width;
				ar >> this->my_name;
				version = WELLS_DRAW_LIST_ITEM_VERSION;
			}
			break;
		default:
			{
				throw VersionException(version, VersionException::cannot_load, Object::object_type::undefined);
			}
			break;
		}
	}
}


Archive& operator <<(Archive& ar, wells_draw_list_item * it)
{
	bool allocated = false;

	if (it)
	{
		allocated = true;
		ar << allocated;
		if (it) it->Serialize(ar);
	}
	else
	{
		ar << allocated;
	}
	return ar;
}
Archive& operator >>(Archive& ar, wells_draw_list_item *& it)
{
	bool allocated = false;

	ar >> allocated;
	if (allocated)
	{
		it = new wells_draw_list_item;
		if (it) it->Serialize(ar);
	}
	else
	{
		it = NULL;
	}
	return ar;
}




void WellElement::WellElement_Serialize(Archive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_base_wellelement_version;
		switch (m_base_wellelement_version)
		{
		case 3:
			{
				ar << this->grid_data_point_zk.id_surf;
				ar << this->grid_data_point_zk.id_point;

				ar << this->grid_data_point_zp.id_surf;
				ar << this->grid_data_point_zp.id_point;
			}
		case 2:
			{
				ar << zk;
			}
		case 1:
			{
				ar << nameID;
				ar << zp;
			}
			break;
		default:
			{
				throw VersionException(m_base_wellelement_version, VersionException::cannot_store, Object::object_type::undefined);
			}
			break;
		}
	}
	else
	{
		ar >> m_base_wellelement_version;
		switch (m_base_wellelement_version)
		{
		case 3:
			{
				ar >> this->grid_data_point_zk.id_surf;
				ar >> this->grid_data_point_zk.id_point;

				ar >> this->grid_data_point_zp.id_surf;
				ar >> this->grid_data_point_zp.id_point;
			}
		case 2:
			{
				ar >> zk;
			}
		case 1:
			{
				ar >> nameID;
				ar >> zp;

				m_base_wellelement_version = BASE_WELLELEMENT_VERSION;
			}
			break;
		default:
			{
				throw VersionException(m_base_wellelement_version, VersionException::cannot_load, Object::object_type::undefined);
			}
			break;
		}
	}
}

void Well_Litho_Podoshva::WellElementSerialize(Archive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_this_wellelement_version;

		switch (m_this_wellelement_version)
		{
		case 3:
			{
				//ar << ???;
			}
		case 2:
			{
				ar << this->id_umpoz;
				ar << this->umpoz;
				ar << this->hatchacad;
				ar << this->angle;
				ar << this->scale;
			}
		case 1:
			{
				ar << this->color;
				ar << this->key;
			}
			break;
		default:
			{
				throw VersionException(m_this_wellelement_version, VersionException::cannot_store, Object::object_type::undefined);
			}
			break;
		}
	}
	else
	{
		ar >> m_this_wellelement_version;
		switch (m_this_wellelement_version)
		{
		case 3:
			{
				//ar >> ???;
			}
		case 2:
			{
				ar >> this->id_umpoz;
				ar >> this->umpoz;
				ar >> this->hatchacad;
				ar >> this->angle;
				ar >> this->scale;
			}
		case 1:
			{
				ar >> this->color;
				ar >> this->key;
				m_this_wellelement_version = LITHO_PODOSHVA_WELLELEMENT_VERSION;
			}
			break;
		default:
			{
				throw VersionException(m_this_wellelement_version, VersionException::cannot_load, Object::object_type::undefined);
			}
			break;
		}
	}
}








void Well_IGE_Podoshva::WellElementSerialize(Archive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_this_wellelement_version;

		switch (m_this_wellelement_version)
		{
		case 3:
			{
				//ar << ???;
			}
		case 2:
			{
				ar << this->id_umpoz;
				ar << this->umpoz;
				ar << this->hatchacad;
				ar << this->angle;
				ar << this->scale;
			}
		case 1:
			{
				ar << this->color;
				ar << this->key;
			}
			break;
		default:
			{
				throw VersionException(m_this_wellelement_version, VersionException::cannot_store, Object::object_type::undefined);
			}
			break;
		}
	}
	else
	{
		ar >> m_this_wellelement_version;
		switch (m_this_wellelement_version)
		{
		case 3:
			{
				//ar >> ???;
			}
		case 2:
			{
				ar >> this->id_umpoz;
				ar >> this->umpoz;
				ar >> this->hatchacad;
				ar >> this->angle;
				ar >> this->scale;
			}
		case 1:
			{
				ar >> this->color;
				ar >> this->key;
				m_this_wellelement_version = IGE_PODOSHVA_WELLELEMENT_VERSION;
			}
			break;
		default:
			{
				throw VersionException(m_this_wellelement_version, VersionException::cannot_load, Object::object_type::undefined);
			}
			break;
		}
	}
}







void Well_IsSand_Podoshva::WellElementSerialize(Archive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_this_wellelement_version;

		switch (m_this_wellelement_version)
		{
		case 3:
			{
				//ar << ???;
			}
		case 2:
			{
				//ar << ???;
			}
		case 1:
			{
				ar << this->isSand;
			}
			break;
		default:
			{
				throw VersionException(m_this_wellelement_version, VersionException::cannot_store, Object::object_type::undefined);
			}
			break;
		}
	}
	else
	{
		ar >> m_this_wellelement_version;
		switch (m_this_wellelement_version)
		{
		case 3:
			{
				//ar >> ???;
			}
		case 2:
			{
				//ar >> ???;
			}
		case 1:
			{
				ar >> this->isSand;
				m_this_wellelement_version = 1;
			}
			break;
		default:
			{
				throw VersionException(m_this_wellelement_version, VersionException::cannot_load, Object::object_type::undefined);
			}
			break;
		}
	}
}








void Well_Hydro_Projavlenie::WellElementSerialize(Archive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_this_wellelement_version;

		switch (m_this_wellelement_version)
		{
		case 3:
			{
				//ar << ???;
			}
		case 2:
			{
				//ar << ???;
			}
		case 1:
			{
				ar << this->ustanovlen;
			}
			break;
		default:
			{
				throw VersionException(m_this_wellelement_version, VersionException::cannot_store, Object::object_type::undefined);
			}
			break;
		}
	}
	else
	{
		ar >> m_this_wellelement_version;
		switch (m_this_wellelement_version)
		{
		case 3:
			{
				//ar >> ???;
			}
		case 2:
			{
				//ar >> ???;
			}
		case 1:
			{
				ar >> this->ustanovlen;
				m_this_wellelement_version = 1;
			}
			break;
		default:
			{
				throw VersionException(m_this_wellelement_version, VersionException::cannot_load, Object::object_type::undefined);
			}
			break;
		}
	}
}


void Well_Laboratory_Analize::WellElementSerialize(Archive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_this_wellelement_version;

		switch (m_this_wellelement_version)
		{
		case 3:
			{
				//ar << ???;
			}
		case 2:
			{
				//ar << ???;
			}
		case 1:
			{					
				ar << this->Lab_Layer_ID;
				ar << this->Lab_Layer_Number;
				ar << this->Lab_Number_ID;
			}
			break;
		default:
			{
				throw VersionException(m_this_wellelement_version, VersionException::cannot_store, Object::object_type::undefined);
			}
			break;
		}
	}
	else
	{
		ar >> m_this_wellelement_version;
		switch (m_this_wellelement_version)
		{
		case 3:
			{
				//ar >> ???;
			}
		case 2:
			{
				//ar >> ???;
			}
		case 1:
			{
				ar >> this->Lab_Layer_ID;
				ar >> this->Lab_Layer_Number;
				ar >> this->Lab_Number_ID;
				m_this_wellelement_version = 1;
			}
			break;
		default:
			{
				throw VersionException(m_this_wellelement_version, VersionException::cannot_load, Object::object_type::undefined);
			}
			break;
		}
	}
}


Archive& operator <<(Archive& ar, WellElement * e)
{
	bool allocated = false;

	if (e)
	{
		allocated = true;
		ar << allocated;
		ar << e->w_type;
		if (e) e->WellElement_Serialize(ar);
		if (e) e->WellElementSerialize(ar);
	}
	else
	{
		ar << allocated;
	}
	return ar;
}
Archive& operator >>(Archive& ar, WellElement *&e)
{
	bool allocated = false;

	ar >> allocated;
	if (allocated)
	{
		WellElement::type we_type;
		ar >> we_type;
		e = reinterpret_cast<WellElement *> (WellElement::operator new (sizeof(WellElement), we_type));
		if (e) e->WellElement_Serialize(ar);
		if (e) e->WellElementSerialize(ar);
	}
	else
	{
		e = NULL;
	}
	return ar;
}



Archive& operator <<(Archive& ar, WellElement::type & tp)
{
	int t = int  (tp);
	ar << t;

	return ar;
}
Archive& operator >>(Archive& ar, WellElement::type & tp)
{
	int t;
	ar >> t;

	tp = (WellElement::type) t;

	return ar;
}

Archive& operator <<(Archive& ar, WellColomn& ob)
{
	ar << ob.well_colomn_version;

	switch (ob.well_colomn_version)
	{
	case 2:
		{
			ar << ob.m_wdli_id;
		}
	case 1:
		{
			ar << ob.w_type;
			ar << ob.well_elements;
		}
		break;
	default:
		{
			throw VersionException(ob.well_colomn_version, VersionException::cannot_store, Object::object_type::well_colomn);
		}
		break;
	}
	return ar;
}
Archive& operator >>(Archive& ar, WellColomn& ob)
{
	ar >> ob.well_colomn_version;

	switch (ob.well_colomn_version)
	{
	case 2:
		{
			ar >> ob.m_wdli_id;
		}
	case 1:
		{
			ar >> ob.w_type;
			ar >> ob.well_elements;

			for (vector<WellElement*>::iterator it = ob.well_elements.begin();
				it != ob.well_elements.end(); it++)
			{
				if ((*it))
				{
					(*it)->SetWellColomn(&ob);
				}
			}
			ob.well_colomn_version = 2;
		}
		break;
	default:
		{
			throw VersionException(ob.well_colomn_version, VersionException::cannot_load, Object::object_type::well_colomn);
		}
		break;
	}
	return ar;
}


