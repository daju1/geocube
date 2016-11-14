#include "stdafx.h"
#include "GeoElement.h"
#include "winsurftree.h"
#include "surfdoc.h"
#include "../../tools/src/errorexit.h"
#include "../../wintools/src/project.h"
#include "DrawScene.h"

extern HINSTANCE hInst;								// current instance

const char * GeoElement::GeoElementTypeToString(GeoElement::type t)
{
	switch (t)
	{
	case undefined_geo_element:
		return "undefined";
	case stratigrafical:
		return "stratigrafical";
	case lithological:
		return "lithological";
	case engineer_geological:
		return "engineer_geological";
	case hydro_geological:
		return "hydro_geological";
	case laboratory_exploration:
		return "laboratory_exploration";
	case field_exploration:
		return "field_exploration";
	case faults:
		return "faults";
	default:
		return "";
	}
	return "";
}
void * GeoElement::operator new  (size_t size, GeoElement::type t, long id_key)
{
	//printf("Object::operator new(size_t size = %d, GeoElement::type = %s\n", size, GeoElement::GeoElementTypeToString(t));

	switch (t)
	{
	case GeoElement::type::undefined_geo_element:
		return NULL;
	case GeoElement::type::stratigrafical:
		return reinterpret_cast<void*>(new StratigraficalGeoElement(id_key));
	case GeoElement::type::lithological:
		return reinterpret_cast<void*>(new LithoGeoElement(id_key));
	case GeoElement::type::engineer_geological:
		return reinterpret_cast<void*>(new EngineerGeoElement(id_key));
	case GeoElement::type::hydro_geological:
		return reinterpret_cast<void*>(new HydroGeoElement(id_key));
	case GeoElement::type::laboratory_exploration:
		return reinterpret_cast<void*>(new LabGeoElement(id_key));
	case GeoElement::type::field_exploration:
		return reinterpret_cast<void*>(new FieldGeoElement(id_key));
	case GeoElement::type::faults:
		return reinterpret_cast<void*>(new FaultGeoElement(id_key));
	default:
		return NULL;
	}
	return NULL;
}
void GeoElement::operator delete(void * p, GeoElement::type t, long key_id)
{
	switch (t)
	{
	case GeoElement::type::undefined_geo_element:
		return;
	case GeoElement::type::stratigrafical:
		::operator delete(reinterpret_cast<StratigraficalGeoElement*>(p));
		break;
	case GeoElement::type::lithological:
		::operator delete(reinterpret_cast<LithoGeoElement*>(p));
		break;
	case GeoElement::type::engineer_geological:
		::operator delete(reinterpret_cast<EngineerGeoElement*>(p));
		break;
	case GeoElement::type::hydro_geological:
		::operator delete(reinterpret_cast<HydroGeoElement*>(p));
		break;
	case GeoElement::type::laboratory_exploration:
		::operator delete(reinterpret_cast<LabGeoElement*>(p));
		break;
	case GeoElement::type::field_exploration:
		::operator delete(reinterpret_cast<FieldGeoElement*>(p));
		break;
	case GeoElement::type::faults:
		::operator delete(reinterpret_cast<FaultGeoElement*>(p));
		break;
	default:
		return;
	}
}

#define GEOELEMENT_VERSION 3

void GeoElement::Init(long id_key)
{
	this->Object::Init();
	this->my_key_read = false;
	this->my_geo_colomn = NULL;
	this->my_id_key = id_key;


	m_geoelement_version = GEOELEMENT_VERSION;

	this->id_umpoz = 0;


}

void StratigraficalGeoElement::Init(long id_key)
{
	this->GeoElement::Init(id_key);
	this->m_type = GeoElement::type::stratigrafical;
	this->m_object_version = 1;
	this->m_max_object_version = 1;
}
void LithoGeoElement::Init(long id_key)
{
	this->GeoElement::Init(id_key);

	this->m_type				= GeoElement::type::lithological;
	this->m_litho_geoelement_version = LITHO_GEO_ELEMENT_VERSION;
	this->m_object_version = 1;
	this->m_max_object_version = 1;


	this->lith_color = RGB(255,255,255);

	this->m_ground_type			= CGround::ground_type::Undefined_ground;
//	this->m_sand_type			= sand_type::undefined_sand_type;
//	this->m_sand_strength		= sand_strength::undefined_sand_strength;
//	this->m_clay_solidity		= clay_solidity::undefined_clay_solidity;
//	this->m_irrigation_type		= irrigation_type::undefined_irrigation_type;
}
void EngineerGeoElement::Init(long id_key)
{
	WaterSaturation_Checked = false;

	this->GeoElement::Init(id_key);
	this->m_type = GeoElement::type::engineer_geological;
	m_ground = NULL;
	this->m_object_version = ENG_GEO_ELEMENT_VERSION;
	this->m_max_object_version = ENG_GEO_ELEMENT_VERSION;

	this->lith_color = RGB(255,255,255);

	to_print_if_any = false;
	this->m_lablayer = NULL;
}
void HydroGeoElement::Init(long id_key)
{
	this->GeoElement::Init(id_key);
	this->m_type = GeoElement::type::hydro_geological;
	this->m_object_version = 1;
	this->m_max_object_version = 1;
	this->ustanovlen = false;

	switch(id_key)
	{
	case 1://з'явився
		this->ustanovlen = false;
		break;
	case 2://встановився
		this->ustanovlen = true;
		break;
	}
}
void LabGeoElement :: Init(long id_key)
{
	this->GeoElement::Init(id_key);
	this->m_type = GeoElement::type::laboratory_exploration;
	this->m_object_version = 1;
	this->m_max_object_version = 1;
}
void FieldGeoElement :: Init(long id_key)
{
	this->GeoElement::Init(id_key);
	this->m_type = GeoElement::type::field_exploration;
	this->m_object_version = 1;
	this->m_max_object_version = 1;
}

void FaultGeoElement :: Init(long id_key)
{
	this->GeoElement::Init(id_key);
	this->m_type = GeoElement::type::faults;
	this->m_object_version = 1;
	this->m_max_object_version = 1;
}


void GeoColomn::Init()
{
	this->m_object_type = Object::object_type::geo_colomn;
	this->m_object_version = 1;
	this->m_max_object_version = 1;
}

void GeoElement::PropertiesDialog()
{
	this->PrintfProperties();
}
/*
void StratigraficalGeoElement::PropertiesDialog()
{
	this->PrintfProperties();
}
void LithoGeoElement::PropertiesDialog()
{
	this->PrintfProperties();
}
void EngineerGeoElement::PropertiesDialog()
{
	this->PrintfProperties();
}
void HydroGeoElement::PropertiesDialog()
{
	this->PrintfProperties();
}
void LabGeoElement::PropertiesDialog()
{
	this->PrintfProperties();
}
void FieldGeoElement::PropertiesDialog()
{
	this->PrintfProperties();
}
*/


void GeoColomn::PropertiesDialog()
{
	printf("GeoColomn of %s type\n", GeoElement::GeoElementTypeToString(this->m_type));
	printf("Number of geo elements %d\n", geo_elements.size());

	for (map<string, GeoElement*>::iterator it = geo_elements.begin(); it != geo_elements.end(); it++)
	{		
		if (it->second)
		{
			GeoElement::type t = it->second->m_type;
			
			if (t != this->m_type)
			{
				printf("warning: element type  = \"%s\" (%d) not eqial colomn type = \"%s\"(%d)\n",
					GeoElement::GeoElementTypeToString(t), int(t),
					GeoElement::GeoElementTypeToString(this->m_type), int(this->m_type)
					);
			}

			printf("%s\n", it->first.c_str());

			it->second->PrintfProperties();
		}
	}
}

GeoElement * GeoColomn::CreateNewGeoElement(GeoElement::type t, long id_key)
{
	return (GeoElement*)GeoElement::operator new (sizeof(GeoElement), t, id_key);
}

GeoElement * GeoColomn::FindGeoElement(string key)
{
	if(this->geo_elements.find(key) != this->geo_elements.end())
		return this->geo_elements[key];

	return NULL;
}
GeoElement * GeoColomn::AddNewGeoElement(string key, GeoElement * geo_element)
{
	if(this->geo_elements.find(key) != this->geo_elements.end())
		return NULL;

	this->geo_elements.insert(map<string, GeoElement*>::value_type(key, geo_element));	
	this->geo_elements[key]->SetGeoColomn(this);
	return this->geo_elements[key];
}
void GeoColomn::AddNewGeoElement()
{
	TCHAR lpstrFile[4098];
	if (OpenFileDlg(this->m_pSurfDoc ? this->m_pSurfDoc->hSurfWnd : NULL, 
		"Geo Element File (*.*)\0*.*\0All files \0*.*\0", lpstrFile) == S_OK)
	{
		
		GeoElement * geo_element = this->CreateNewGeoElement(this->m_type, this->GetNewKeyID());
		if (geo_element) geo_element->SetGeoColomn(this);
		if (geo_element && 
			geo_element->ReadFile(lpstrFile) && 
			geo_element->KeyRead() && 
			this->geo_elements.find(geo_element->GetKey()) == this->geo_elements.end() &&
			this->AddNewGeoElement(geo_element->GetKey(), geo_element))
		{
			this->ReDrawItem_OnTree(this->m_pSurfDoc ? this->m_pSurfDoc->hwndTV : NULL);
		}
		else
		{
			// мы боимся, чтобы при удалении геоэлемента случайно не удалилась колонка
			// поэтому обнуляем указатель на колонку в геоэлементе
			geo_element->SetGeoColomn(NULL);
			long key_id = geo_element->GetKeyID();
			// а затем удаляем геоэлемент
			GeoElement::operator delete (geo_element, this->m_type, key_id);
		}

	}
}
LRESULT CALLBACK DlgProcAddEmptyGeoElement(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static GeoColomn * lpColomn;
	static int index_ground_type;
	static CGround::ground_type s_ground_type;

	int wmId, wmEvent;

	switch (message) 
	{
		case WM_INITDIALOG :
			{
				index_ground_type = -1;
				s_ground_type = CGround::ground_type::Undefined_ground;

				lpColomn = (GeoColomn *)lParam;
				//**************************************
				// #############################################################
				// #############################################################
				if (lpColomn)
				{
				}				 
				// #############################################################
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				SendDlgItemMessage( hDlg, IDC_COMBO_GROUND_TYPE, CB_RESETCONTENT,0,0);
				SendDlgItemMessage( hDlg, IDC_COMBO_GROUND_TYPE, CB_ADDSTRING, 0,
					(LPARAM)(LPCTSTR)"Select type of ground");

				for( CGround::ground_type gt = CGround::ground_type::Sand; 
					gt <= CGround::ground_type::Clay;
					gt++ )
				{
						SendDlgItemMessage( hDlg, IDC_COMBO_GROUND_TYPE, CB_ADDSTRING, 0,
							(LPARAM)(LPCTSTR)CGround::GrountTypeToStringRus(gt));
				}
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				SendDlgItemMessage( hDlg, IDC_COMBO_GROUND_TYPE, CB_SETCURSEL,
					index_ground_type+1, (LPARAM)0 );
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				// #############################################################
				// #############################################################
			}
			break;

		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
			case IDC_COMBO_GROUND_TYPE:
				{
					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					index_ground_type = -1 + (int)SendDlgItemMessage( hDlg, IDC_COMBO_GROUND_TYPE, CB_GETCURSEL,
								0,(LPARAM)0 );
					if (index_ground_type > -1)
					{
						s_ground_type = (CGround::ground_type) (20*(index_ground_type+1));

					}
					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@							
				}
				break;
			case IDOK:
				{
					if(lpColomn)
					{
						char key [1024];
						GetDlgItemText(hDlg,IDC_EDIT_GEO_ELEMENT_KEY, key, 1023);
						if (strlen(key))
						{
							lpColomn->AddEmptyGeoElement(key, s_ground_type, lpColomn->GetNewKeyID());
							EndDialog( hDlg, IDCANCEL );
						}
					}
				}
				break;
			case IDCANCEL :
				EndDialog( hDlg, IDCANCEL );
				break;
			}
			break;
		case WM_CLOSE:
			{
				return DefWindowProc(hDlg, message, wParam, lParam);
			}
			break;
   }
   return 0;
}

LRESULT CALLBACK DlgProcEngGeoElementGroundType(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static EngineerGeoElement * lpIGE;
	static int index_ground_type;
	static CGround::ground_type s_ground_type;

	int wmId, wmEvent;

	switch (message) 
	{
		case WM_INITDIALOG :
			{
				index_ground_type = -1;
				s_ground_type = CGround::ground_type::Undefined_ground;

				lpIGE = (EngineerGeoElement *)lParam;
				//**************************************
				// #############################################################
				// #############################################################
				if (lpIGE)
				{
					SetDlgItemText(hDlg,IDC_EDIT_GEO_ELEMENT_KEY, lpIGE->GetKey().c_str());
					EnableWindow(GetDlgItem(hDlg, IDC_EDIT_GEO_ELEMENT_KEY), FALSE);
				}				 
				// #############################################################
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				SendDlgItemMessage( hDlg, IDC_COMBO_GROUND_TYPE, CB_RESETCONTENT,0,0);
				SendDlgItemMessage( hDlg, IDC_COMBO_GROUND_TYPE, CB_ADDSTRING, 0,
					(LPARAM)(LPCTSTR)"Select type of ground");

				for( CGround::ground_type gt = CGround::ground_type::Sand; 
					gt <= CGround::ground_type::Clay;
					gt++ )
				{
						SendDlgItemMessage( hDlg, IDC_COMBO_GROUND_TYPE, CB_ADDSTRING, 0,
							(LPARAM)(LPCTSTR)CGround::GrountTypeToStringRus(gt));
				}
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				SendDlgItemMessage( hDlg, IDC_COMBO_GROUND_TYPE, CB_SETCURSEL,
					index_ground_type+1, (LPARAM)0 );
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				// #############################################################
				// #############################################################
				if (lpIGE)
				{
                    if (lpIGE->GetGround())
					{
						index_ground_type = s_ground_type/20 - 1;
						SendDlgItemMessage( hDlg, IDC_COMBO_GROUND_TYPE, CB_SETCURSEL,
							index_ground_type+1, (LPARAM)0 );
						//EnableWindow(GetDlgItem(hDlg, IDC_COMBO_GROUND_TYPE), FALSE);
					}
				}

			}
			break;

		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
			case IDC_COMBO_GROUND_TYPE:
				{
					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					index_ground_type = -1 + (int)SendDlgItemMessage( hDlg, IDC_COMBO_GROUND_TYPE, CB_GETCURSEL,
								0,(LPARAM)0 );
					if (index_ground_type > -1)
					{
						s_ground_type = (CGround::ground_type) (20*(index_ground_type+1));

					}
					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@							
				}
				break;
			case IDOK:
				{
					if(lpIGE)
					{
						if (!lpIGE->GetGround())
							lpIGE->SetGround(s_ground_type);
						else
						{
							lpIGE->ResetGround(s_ground_type);
						}
						EndDialog( hDlg, IDCANCEL );
					}
				}
				break;
			case IDCANCEL :
				EndDialog( hDlg, IDCANCEL );
				break;
			}
			break;
		case WM_CLOSE:
			{
				return DefWindowProc(hDlg, message, wParam, lParam);
			}
			break;
   }
   return 0;
}

void EngineerGeoElement::SetGround(CGround::ground_type gt)
{
	m_ground = (CGround*) CGround::operator new(sizeof(CGround), gt);
}
void EngineerGeoElement::ResetGround(CGround::ground_type gt)
{
	if (m_ground) delete m_ground;

	m_ground = (CGround*) CGround::operator new(sizeof(CGround), gt);
}
bool EngineerGeoElement::ColorDialog()
{
	bool res = ChooseSurfColor(NULL, lith_color) == 0;
	if (res && this->m_pSurfDoc)
	{
		this->m_pSurfDoc->set_well_elements_ige_keys_show_error_message_box = true;
//		this->m_pSurfDoc->SetWellElementsIGEkeys();
		this->m_pSurfDoc->SetColorFromIGE();

		project* pproject = dynamic_cast <project*>(this->m_pSurfDoc);
		if (pproject) pproject->UpdateAllViews();
	}
	return false;
}
bool GetReverse(int nsurf, string my_key, const char * s)
{
	bool reverse = true;
	if (nsurf > 1)
	{
		char str[2048];
		sprintf(str, "В %s-геологическом элементе %s\n"
			"насчитывается как минимум %d наслаиваний\n"
			"Програма предпримет попытку их разделения\n"
			"путём отнесения подошв этого элемента\n"
			"неоднократно повторяющихся в скважине\n"
			"к разным поверхностям\n"
			"Выберите направление перебора\n"
			"YES - снизу вверх или NO - сверху вниз\n"
			, 
			s, 	my_key.c_str(), nsurf);
		reverse = IDYES == MessageBox(0, str, "ToGridData", MB_YESNO);
	}
	return reverse;
}

void EngineerGeoElement::ToGridData(BYTE podoshva)
{
	char ssurf[32];
	char sname[512];
	if (this->m_pSurfDoc)
	{
		this->m_pSurfDoc->set_well_elements_ige_keys_show_error_message_box = true;
//		this->m_pSurfDoc->SetWellElementsIGEkeys();
		if (podoshva == 255)
		{
				GridData * pGridData = this->m_pSurfDoc->CreateNewGridData();
				long id_surf = pGridData->id_surf;
				this->m_pSurfDoc->IGEZabojToGridData(this->my_key, pGridData);
				pGridData->SetColor(this->lith_color);
				pGridData->id_umpoz = this->id_umpoz;

				pGridData->id_ige = this->my_id_key;

				

				sprintf(sname, "забой ИГЭ %s", this->GetKey().c_str());
				pGridData->SetName(sname);


				pGridData->GrDtSaveToDB(1);

				this->m_pSurfDoc->AddSurfIgeMappingItem(id_surf, 1, sname, this->GetKey().c_str());
				this->m_pSurfDoc->AddSurfIgeMappingItemToDB(id_surf, this->GetKey().c_str());
		}
		else
		{
			int nsurf = this->m_pSurfDoc->IGEPodoshvaHowMany(this->my_key);
			bool reverse = GetReverse(nsurf, this->my_key, "инженерно");

			for (int isurf = 0; isurf < nsurf; isurf++)
			{
				GridData * pGridData = this->m_pSurfDoc->CreateNewGridData();
				long id_surf = pGridData->id_surf;
				this->m_pSurfDoc->IGEPodoshvaToGridData(isurf, podoshva, this->my_key, pGridData, reverse);
				pGridData->SetColor(this->lith_color);
				pGridData->id_umpoz = this->id_umpoz;
				pGridData->id_ige = this->my_id_key;

				sprintf(ssurf, " %d", isurf + 1);			
				sprintf(sname, "%s%s ИГЭ %s", podoshva == 2 ? "кровля" : "подошва", nsurf > 1 ? ssurf : "", this->GetKey().c_str());
				pGridData->SetName(sname);


				pGridData->GrDtSaveToDB(podoshva);

				this->m_pSurfDoc->AddSurfIgeMappingItem(id_surf, podoshva, sname, this->GetKey().c_str());
				this->m_pSurfDoc->AddSurfIgeMappingItemToDB(id_surf, this->GetKey().c_str());
			}
		}

		project * prj = dynamic_cast<project *>(this->m_pSurfDoc);
		if (prj)
		{
			prj->Zoom<GridData>(prj->m_grid_data);
			ReDrawGridData(prj);
			prj->UpdateAllViews();
		}
	}
}
void EngineerGeoElement::AddEmptyGridData(BYTE podoshva)
{
	char ssurf[32];
	char sname[512];
	if (this->m_pSurfDoc)
	{
		//this->m_pSurfDoc->set_well_elements_ige_keys_show_error_message_box = true;

		int nsurf = 1;
		int isurf = 0;
	
		GridData * pGridData = this->m_pSurfDoc->CreateNewGridData();
		long id_surf = pGridData->id_surf;
		//this->m_pSurfDoc->IGEPodoshvaToGridData(isurf, podoshva, this->my_key, pGridData, reverse);
		pGridData->SetColor(this->lith_color);
		pGridData->id_umpoz = this->id_umpoz;

		sprintf(ssurf, " %d", isurf + 1);			
		sprintf(sname, "%s%s ИГЭ %s ID_SURF = %d", 
			podoshva == 2 ? "кровля" : "подошва", 
			nsurf > 1 ? ssurf : "", 
			this->GetKey().c_str(),
			id_surf);
		pGridData->SetName(sname);


		pGridData->GrDtSaveToDB(podoshva);

		this->m_pSurfDoc->AddSurfIgeMappingItem(id_surf, podoshva, sname, this->GetKey().c_str());
		this->m_pSurfDoc->AddSurfIgeMappingItemToDB(id_surf, this->GetKey().c_str());


		project * prj = dynamic_cast<project *>(this->m_pSurfDoc);
		if (prj)
		{
			prj->Zoom<GridData>(prj->m_grid_data);
			ReDrawGridData(prj);
			prj->UpdateAllViews();
		}
	}
}
void HydroGeoElement::AddEmptyGridData(BYTE podoshva)
{
	if (this->m_pSurfDoc)
	{
		map<long, long> gorizonts;
		this->m_pSurfDoc->HydroProjavlenieHowMany(gorizonts, this->ustanovlen);

		char sname[512];
	
		long horizont = 1;
		for (map<long, long>::iterator it = gorizonts.begin(); it != gorizonts.end(); it++)
		{
			horizont = (*it).first + 1;
		}

		GridData * pGridData = this->m_pSurfDoc->CreateNewGridData();
		//this->m_pSurfDoc->HydroProjavlenieToGridData(horizont, this->ustanovlen, pGridData);
		pGridData->SetColor(RGB(0,0,255));
		pGridData->id_umpoz = this->id_umpoz;
						
		
		const char * ssurf = this->ustanovlen ? "вода установилась" : "вода появилась";
		sprintf(sname, "горизонт %d %s ", horizont, ssurf);
		pGridData->SetName(sname);

		pGridData->GrDtSaveToDB(3);




		project * prj = dynamic_cast<project *>(this->m_pSurfDoc);
		if (prj)
		{
			prj->Zoom<GridData>(prj->m_grid_data);
			ReDrawGridData(prj);
			prj->UpdateAllViews();
		}
	}
}
void FaultGeoElement::AddEmptyGridData(BYTE podoshva)
{
	if (this->m_pSurfDoc)
	{
		char sname[512];

		GridData * pGridData = this->m_pSurfDoc->CreateNewGridData();
		long id_surf = pGridData->id_surf;
		pGridData->SetColor(RGB(255,0,0));
		pGridData->id_umpoz = this->id_umpoz;						
		
		sprintf(sname, "Разлом ID_SURF = %d", id_surf);
		pGridData->SetName(sname);

		pGridData->GrDtSaveToDB(4);

		project * prj = dynamic_cast<project *>(this->m_pSurfDoc);
		if (prj)
		{
			prj->Zoom<GridData>(prj->m_grid_data);
			ReDrawGridData(prj);
			prj->UpdateAllViews();
		}
	}
}
void HydroGeoElement::ToGridData(BYTE podoshva)
{
	if (this->m_pSurfDoc)
	{
		map<long, long> gorizonts;
		this->m_pSurfDoc->HydroProjavlenieHowMany(gorizonts, this->ustanovlen);

		char sname[512];
		for (map<long, long>::iterator it = gorizonts.begin(); it != gorizonts.end(); it++)
		{
			long horizont = (*it).first;

			GridData * pGridData = this->m_pSurfDoc->CreateNewGridData();
			this->m_pSurfDoc->HydroProjavlenieToGridData(horizont, this->ustanovlen, pGridData);
			pGridData->SetColor(RGB(0,0,255));
			pGridData->id_umpoz = this->id_umpoz;
			pGridData->id_umpoz = -2;// voda - blue line
							
			
			const char * ssurf = this->ustanovlen ? "вода установилась" : "вода появилась";
			sprintf(sname, "горизонт %d %s ", horizont, ssurf);
			pGridData->SetName(sname);

			pGridData->GrDtSaveToDB(3);
		}





		project * prj = dynamic_cast<project *>(this->m_pSurfDoc);
		if (prj)
		{
			prj->Zoom<GridData>(prj->m_grid_data);
			ReDrawGridData(prj);
			prj->UpdateAllViews();
		}
	}
}
void GeoColomn::AddEmptyGeoElement()
{
		// modal dialog
	if (IDOK == DialogBoxParam(hInst, 
			MAKEINTRESOURCE(IDD_DIALOG_ADD_EMPTY_GEO_ELEMENT), 
			(HWND)NULL, (DLGPROC)DlgProcAddEmptyGeoElement, (LPARAM) this)==IDOK) 
	{
	}
}
void EngineerGeoElement::GroundType()
{
	if (IDOK == DialogBoxParam(hInst, 
			MAKEINTRESOURCE(IDD_DIALOG_ADD_EMPTY_GEO_ELEMENT), 
			(HWND)NULL, (DLGPROC)DlgProcEngGeoElementGroundType, (LPARAM) this)==IDOK) 
	{
	}
}

void GeoColomn::ToGridData(BYTE podoshva)
{
	map <long, GeoElement*> temp_geo_elements;
	for (map<string, GeoElement*>::iterator it = geo_elements.begin(); it != geo_elements.end(); it++)
	{	
		if (it->second)
		{
			temp_geo_elements.insert(map <long, GeoElement*>::value_type(it->second->GetKeyID(), it->second));
		}
	}
#if 1
	for (map<long, GeoElement*>::iterator it = temp_geo_elements.begin(); it != temp_geo_elements.end(); it++)
	{	
		if (it->second)
		{
			it->second->ToGridData(podoshva);
		}
	}
#else
	for (map<string, GeoElement*>::iterator it = geo_elements.begin(); it != geo_elements.end(); it++)
	{	
		if (it->second)
		{
			it->second->ToGridData();
		}
	}
#endif

	project * prj = dynamic_cast<project *>(this->m_pSurfDoc);
	if (prj)
	{
		prj->Zoom<GridData>(prj->m_grid_data);
		ReDrawGridData(prj);
		prj->UpdateAllViews();
	}
}
GeoElement * GeoColomn::AddEmptyGeoElement(const char * key, CGround::ground_type gt, long id_key)
{
	GeoElement * geo_element = this->CreateNewGeoElement(this->m_type, id_key);
	geo_element->SetGeoColomn(this);
	geo_element->SetKey(key);
	EngineerGeoElement * eng = dynamic_cast<EngineerGeoElement *>(geo_element);
	if(eng)	
		eng->SetGround(gt);
	else
	{
		LithoGeoElement * lith = dynamic_cast<LithoGeoElement *>(geo_element);
		if (lith)
			lith->SetGrountType(gt);
	}
	this->AddNewGeoElement(geo_element->GetKey(), geo_element);
	this->ReDrawItem_OnTree(this->m_pSurfDoc ? this->m_pSurfDoc->hwndTV : NULL);

	/*if (geo_element && 
		geo_element->ReadFile(lpstrFile) && 
		geo_element->KeyRead() && 
		this->geo_elements.find(geo_element->GetKey()) == this->geo_elements.end() &&
		
	{
		
	}
	else
	{
		// мы боимся, чтобы при удалении геоэлемента случайно не удалилась колонка
		// поэтому обнуляем указатель на колонку в геоэлементе
		geo_element->SetGeoColomn(NULL);
		// а затем удаляем геоэлемент
		GeoElement::operator delete (geo_element, this->m_type);
	}*/

	return geo_element;

}

HTREEITEM LithoGeoElement::AddItem_ToTree(HWND hwndTV, HTREEITEM h1)
{
    char szItemText[1024]; // label text of tree-view item 
	//====== Тип изображаемого объекта

	sprintf(szItemText, "LITHO %s", 
		this->my_key.c_str() 
		);
	Object * pObject = dynamic_cast<Object *> (this);
	//=============================================================
	// Add the item to the tree-view control. 
	HTREEITEM h2 = AddItemToTree(hwndTV, szItemText, pObject, h1); 
	return h2;
}
HTREEITEM EngineerGeoElement::AddItem_ToTree(HWND hwndTV, HTREEITEM h1)
{
    char szItemText[1024]; // label text of tree-view item 
	//====== Тип изображаемого объекта

	sprintf(szItemText, "IGE %s", 
		this->my_key.c_str() 
		);
	Object * pObject = dynamic_cast<Object *> (this);
	//=============================================================
	// Add the item to the tree-view control. 
	HTREEITEM h2 = AddItemToTree(hwndTV, szItemText, pObject, h1); 
	return h2;
}
HTREEITEM GeoElement::AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s)
{
    char szItemText[1024]; // label text of tree-view item 
	//====== Тип изображаемого объекта

	sprintf(szItemText, "%s GeoElement %s", 
		GeoElement::GeoElementTypeToString(this->m_type), 
		this->my_key.c_str() 
		);
	Object * pObject = dynamic_cast<Object *> (this);
	//=============================================================
	// Add the item to the tree-view control. 
	HTREEITEM h2 = AddItemToTree(hwndTV, szItemText, pObject, h1); 
	return h2;
}
HTREEITEM GeoColomn::AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s)
{
    char szItemText[1024]; // label text of tree-view item 
	//====== Тип изображаемого объекта

	sprintf(szItemText, "%s GeoColomn", GeoElement::GeoElementTypeToString(this->m_type) );
	Object * pObject = dynamic_cast<Object *> (this);
	//=============================================================
	// Add the item to the tree-view control. 
	HTREEITEM h2 = AddItemToTree(hwndTV, szItemText, pObject, h1); 
	//=============================================================
	map <long, GeoElement*> temp_geo_elements;

	for (map<string, GeoElement*>::iterator it = geo_elements.begin(); it != geo_elements.end(); it++)
	{	
		if (it->second)
		{
			temp_geo_elements.insert(map <long, GeoElement*>::value_type(it->second->GetKeyID(), it->second));
		}
	}
#if 1
	for (map<long, GeoElement*>::iterator it = temp_geo_elements.begin(); it != temp_geo_elements.end(); it++)
	{	
		if (it->second)
		{
			GeoElement::type t = it->second->m_type;			
			if (t != this->m_type)
			{
				printf("warning: element type  = \"%s\" (%d) not eqial colomn type = \"%s\"(%d)\n",
					GeoElement::GeoElementTypeToString(t), int(t),
					GeoElement::GeoElementTypeToString(this->m_type), int(this->m_type)
					);
			}
			it->second->AddItem_ToTree(hwndTV, h2);

		}
	}
#else
	for (map<string, GeoElement*>::iterator it = geo_elements.begin(); it != geo_elements.end(); it++)
	{		
		if (it->second)
		{
			GeoElement::type t = it->second->m_type;
			
			if (t != this->m_type)
			{
				printf("warning: element type  = \"%s\" (%d) not eqial colomn type = \"%s\"(%d)\n",
					GeoElement::GeoElementTypeToString(t), int(t),
					GeoElement::GeoElementTypeToString(this->m_type), int(this->m_type)
					);
			}
#if 1
			it->second->AddItem_ToTree(hwndTV, h2);
#else
			sprintf(szItemText, "%s\0", it->first.c_str());


			BOOL fCheck = TRUE;
			LPARAM lParam = 0;
			HTREEITEM h3 = AddItemToTree(hwndTV, szItemText, fCheck, lParam, h2);
#endif
		}
	}
#endif
	return h2;
}
long GeoColomn::GetNewKeyID()
{
	long id = 0;
	for (map<string, GeoElement*>::iterator it = geo_elements.begin(); it != geo_elements.end(); it++)
	{		
		if (it->second)
		{
			if (it->second->GetKeyID() > id)
				id = it->second->GetKeyID();
		}
	}

	id++;

	return id;
}


void GeoElement::FillContextMenu(HMENU& hMenu)
{
	this->Object::FillContextMenu(hMenu);
	AppendMenu( hMenu, MFT_SEPARATOR, 0, NULL );
	
	AppendMenu( hMenu, MFT_STRING, ID_TREE_GEOELEMENT_ADDEMPTYGRIDDATA, "Add Empty GridData" );
	AppendMenu( hMenu, MFT_STRING, ID_TREE_GEOELEMENT_TOGRIDDATA, "To GridData" );
	AppendMenu( hMenu, MFT_STRING, ID_TREE_GEOELEMENT_MINALTITUDETOGRIDDATA, "Zaboj To GridData" );
	AppendMenu( hMenu, MFT_STRING, ID_TREE_GEOELEMENT_GROUNDTYPE, "Тип грунта" );	
}
void GeoColomn::FillContextMenu(HMENU& hMenu)
{
	this->Object::FillContextMenu(hMenu);
	AppendMenu( hMenu, MFT_SEPARATOR, 0, NULL );

	switch (this->m_type)
	{
	case GeoElement::type::engineer_geological:
		AppendMenu( hMenu, MFT_STRING, ID_TREE_GEOCOLOMN_ADDNEWGEOELEMENT, "Add new Geo Element" );
		AppendMenu( hMenu, MFT_STRING, ID_TREE_GEOCOLOMN_ADDEMPTYGEOELEMENT, "Add Empty Geo Element" );
		break;
	case GeoElement::type::lithological:
		AppendMenu( hMenu, MFT_STRING, ID_TREE_GEOCOLOMN_ADDEMPTYGEOELEMENT, "Add Empty Geo Element" );
		break;
	}
	AppendMenu( hMenu, MFT_STRING, ID_TREE_GEOCOLOMN_TOGRIDDATA, "To GridData" );
	AppendMenu( hMenu, MFT_STRING, ID_TREE_GEOCOLOMN_TOGRIDDATASURFANDCUTTING, "To GridData and Surf Profile Cutting" );
	
}


void LithoGeoElement::PrintfProperties()
{
	//printf("LithoGeoElement::PrintfProperties()\n");
	char str[1024];
	sprintf(str, "my_key = \"%s\"\n\0", this->my_key.c_str());
	CharToOem(str,str);
	printf(str);

	printf("Ground type = %s\n", CGround::GrountTypeToString(m_ground_type));
}

void LithoGeoElement::AddEmptyGridData(BYTE podoshva)
{
	if (this->m_pSurfDoc)
	{
		//this->m_pSurfDoc->set_well_elements_litho_keys_show_error_message_box = true;
		//this->m_pSurfDoc->SetWellElementsLithoKeys();

		int nsurf = 1;
		//bool reverse = GetReverse(nsurf, this->my_key, "лито");

		char ssurf[32];
		char sname[512];
		int isurf = 0; 
		{
			GridData * pGridData = this->m_pSurfDoc->CreateNewGridData();
			long id_surf = pGridData->id_surf;

			//this->m_pSurfDoc->LithoPodoshvaToGridData(isurf, podoshva, this->my_key, pGridData, reverse);
			pGridData->SetColor(this->lith_color);
			pGridData->id_umpoz = this->id_umpoz;

			sprintf(ssurf, " %d", isurf + 1);			
			sprintf(sname, "%s%s литоГЭ %s", podoshva == 2 ? "кровля" : "подошва", nsurf > 1 ? ssurf : "", this->GetKey().c_str());
			pGridData->SetName(sname);

			pGridData->GrDtSaveToDB(podoshva);

			this->m_pSurfDoc->AddSurfLitoMappingItem(id_surf, podoshva, sname, this->GetKey().c_str());
			this->m_pSurfDoc->AddSurfLitoMappingItemToDB(id_surf, this->GetKey().c_str());
		}

		project * prj = dynamic_cast<project *>(this->m_pSurfDoc);
		if (prj)
		{
			prj->Zoom<GridData>(prj->m_grid_data);
			ReDrawGridData(prj);
			prj->UpdateAllViews();
		}
	}
}

void LithoGeoElement::ToGridData(BYTE podoshva)
{
	if (this->m_pSurfDoc)
	{
		this->m_pSurfDoc->set_well_elements_litho_keys_show_error_message_box = true;
		this->m_pSurfDoc->SetWellElementsLithoKeys();

		int nsurf = this->m_pSurfDoc->LithoPodoshvaHowMany(this->my_key);
		bool reverse = GetReverse(nsurf, this->my_key, "лито");

		char ssurf[32];
		char sname[512];
		for (int isurf = 0; isurf < nsurf; isurf++)
		{
			GridData * pGridData = this->m_pSurfDoc->CreateNewGridData();
			long id_surf = pGridData->id_surf;

			this->m_pSurfDoc->LithoPodoshvaToGridData(isurf, podoshva, this->my_key, pGridData, reverse);
			pGridData->SetColor(this->lith_color);
			pGridData->id_umpoz = this->id_umpoz;

			sprintf(ssurf, " %d", isurf + 1);			
			sprintf(sname, "%s%s литоГЭ %s", podoshva == 2 ? "кровля" : "подошва", nsurf > 1 ? ssurf : "", this->GetKey().c_str());
			pGridData->SetName(sname);

			pGridData->GrDtSaveToDB(podoshva);

			this->m_pSurfDoc->AddSurfLitoMappingItem(id_surf, podoshva, sname, this->GetKey().c_str());
			this->m_pSurfDoc->AddSurfLitoMappingItemToDB(id_surf, this->GetKey().c_str());
		}

		project * prj = dynamic_cast<project *>(this->m_pSurfDoc);
		if (prj)
		{
			prj->Zoom<GridData>(prj->m_grid_data);
			ReDrawGridData(prj);
			prj->UpdateAllViews();
		}
	}
}
bool LithoGeoElement::ColorDialog()
{
	bool res = ChooseSurfColor(NULL, lith_color) == 0;
	if (res && this->m_pSurfDoc)
	{
		this->m_pSurfDoc->set_well_elements_litho_keys_show_error_message_box = true;
		this->m_pSurfDoc->SetWellElementsLithoKeys();
		this->m_pSurfDoc->SetColorFromLitho();

		project* pproject = dynamic_cast <project*>(this->m_pSurfDoc);
		if (pproject) pproject->UpdateAllViews();
	}
	return false;
}

LPARAM CreateLParam(EngineerGeoElement::ValueType value_type,
					EngineerGeoElement::GroundDescriptionType ground_description_type,
					EngineerGeoElement::StrengthDescriptionType strength_description_type)
{
    BYTE bLow1 = BYTE(ground_description_type);
    BYTE bHigh1 = BYTE(strength_description_type);
	WORD wLow = MAKEWORD(bLow1, bHigh1);


    BYTE bLow2 = BYTE(value_type);
    BYTE bHigh2 = BYTE(1);
    WORD wHigh = MAKEWORD(bLow2, bHigh2);

	LPARAM lParam = MAKELPARAM(wLow,wHigh);
	return lParam;
}
bool ParseLParam(LPARAM lParam,
				 EngineerGeoElement::ValueType & value_type,
				 EngineerGeoElement::GroundDescriptionType & ground_description_type,
				 EngineerGeoElement::StrengthDescriptionType & strength_description_type)
{
	if (lParam == 0)
		return false;

	WORD wLow  = LOWORD(lParam);
    WORD wHigh = HIWORD(lParam);

	BYTE bLow1  = LOBYTE(wLow);
	BYTE bHigh1 = HIBYTE(wLow);

	BYTE bLow2  = LOBYTE(wHigh);
	BYTE bHigh2 = HIBYTE(wHigh);

	if (bHigh2)
	{
		ground_description_type = EngineerGeoElement::GroundDescriptionType( bLow1 );
		strength_description_type = EngineerGeoElement::StrengthDescriptionType( bHigh1 );
		value_type = EngineerGeoElement::ValueType( bLow2 );	
		return true;
	}
	return false;
}

void EngineerGeoElement::UpdateProps()
{
	printf("EngineerGeoElement::UpdateProps() %u\n", this->m_ListViewTab.Rows());
	for (size_t r = 0;	r < this->m_ListViewTab.Rows(); r++)
	{
		LPARAM lParam = this->m_ListViewTab.GetLParam(r);
		
		EngineerGeoElement::ValueType value_type;
		EngineerGeoElement::GroundDescriptionType ground_description_type;
		EngineerGeoElement::StrengthDescriptionType strength_description_type;
		if (ParseLParam(lParam, value_type, ground_description_type, strength_description_type))
		{
			string s = this->m_ListViewTab.GetItemString(r,0);
			if (ISNUM(s.c_str()))
			{
				double v = atof(s.c_str());
				double v0;
				if (this->GetValue(value_type, ground_description_type, strength_description_type, v0) && v != v0)
				{
					printf("r = %u v0 = %f v = %f\n", r, v0, v);
				}
				this->SetValue(value_type, ground_description_type, strength_description_type, v);
			}
		}
	}
	printf("EngineerGeoElement::UpdateProps() end\n");
}

void EngineerGeoElement::FillListViewTab(bool to_resize)
{
	// set colomns number = 3
	if (to_resize)
		this->m_ListViewTab.SetCols(3);
	else
		this->m_ListViewTab.clear();

	char str[1024];
	LPARAM lPar = CreateLParam(EngineerGeoElement::ValueType::name,EngineerGeoElement::GroundDescriptionType::normative,EngineerGeoElement::StrengthDescriptionType::simple);
	this->m_ListViewTab.AddRow(lPar, NULL);
	size_t r = this->m_ListViewTab.Rows()-1;

	sprintf(str, "Инженерно-геологический элемент");	
	this->m_ListViewTab.SetItemString(r,1,str);
	sprintf(str, "\"%s\"", this->my_key.c_str());	
	this->m_ListViewTab.SetItemString(r,2,str);

	if (this->m_ground) 
	{	
		this->m_ground->FillListViewTab(this->m_ListViewTab);
	}


	for( EngineerGeoElement::GroundDescriptionType ground_description_type = EngineerGeoElement::GroundDescriptionType::normative;
		ground_description_type <= EngineerGeoElement::GroundDescriptionType::calculated_on_carry_ability;
		ground_description_type++)
	{
		this->m_ListViewTab.AddRow(LPARAM(0), NULL);
		r = this->m_ListViewTab.Rows()-1;
		this->m_ListViewTab.SetItemString(r,1,EngineerGeoElement::GroundDescriptionTypeToString(ground_description_type));

		for( EngineerGeoElement::ValueType value_type = EngineerGeoElement::ValueType(EngineerGeoElement::ValueType::name+1); 
			value_type <= EngineerGeoElement::ValueType::specific_cohesion;
			value_type++ )
		{
			for ( EngineerGeoElement::StrengthDescriptionType strength_description_type = EngineerGeoElement::StrengthDescriptionType::simple;
				strength_description_type <= (EngineerGeoElement::ValueTypeIsStrength(value_type) ? EngineerGeoElement::StrengthDescriptionType::in_nature_condition : EngineerGeoElement::StrengthDescriptionType::simple);
				strength_description_type++)
			{
				double v;
				if(this->GetValue(value_type, ground_description_type, strength_description_type, v))
				{
					LPARAM lParam = CreateLParam(value_type,ground_description_type,strength_description_type);
					this->m_ListViewTab.AddRow(lParam, NULL);
					r = this->m_ListViewTab.Rows()-1;
					if (EngineerGeoElement::ValueTypeIsStrength(value_type))
					{
						this->m_ListViewTab.SetItemString(r,2,EngineerGeoElement::StrengthDescriptionTypeToString(strength_description_type));
					}
					this->m_ListViewTab.SetItemString(r,1,EngineerGeoElement::ValueTypeToStringRus(value_type));
					sprintf(str, "%f\0", v);
					this->m_ListViewTab.SetItemString(r,0,str);
				}
			}
		}
	}
}

LRESULT CALLBACK DlgProcEngineerGeoElementProp(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static EngineerGeoElement * lpEngGeoElem;
	static HWND hwndList   = NULL;
	int wmId, wmEvent;

	static int index_value_type;
	static int index_combo;
	static EngineerGeoElement::ValueType s_value_type;
	static EngineerGeoElement::GroundDescriptionType s_ground_description_type;
	static EngineerGeoElement::StrengthDescriptionType s_strength_description_type;

	switch (message) 
	{
		case WM_INITDIALOG :
			{
				index_value_type = -1;
				index_combo = -1;

				s_value_type = EngineerGeoElement::ValueType::name;
				s_ground_description_type = EngineerGeoElement::GroundDescriptionType::normative;
				s_strength_description_type = EngineerGeoElement::StrengthDescriptionType::simple;
				lpEngGeoElem = (EngineerGeoElement *)lParam;
				//**************************************
				// #############################################################
				// #############################################################
				if (lpEngGeoElem)
				{
					if (lpEngGeoElem->m_ListViewTab.Init(hDlg, (LPVOID)lpEngGeoElem, 0.0, 0.0, 0.4, 0.0, true))
					{
						hwndList = lpEngGeoElem->m_ListViewTab.GetWnd();
						lpEngGeoElem->FillListViewTab(true);
					}
				}
				// #############################################################
				// #############################################################
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_GEO_CUBE_TYPE, CB_RESETCONTENT,0,0);
				SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_GEO_CUBE_TYPE, CB_ADDSTRING, 0,
					(LPARAM)(LPCTSTR)"Select type of geo cube");

				for( EngineerGeoElement::ValueType value_type = EngineerGeoElement::ValueType::name; 
					value_type <= EngineerGeoElement::ValueType::specific_cohesion;
					value_type++ )
				{
						SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_GEO_CUBE_TYPE, CB_ADDSTRING, 0,
							(LPARAM)(LPCTSTR)EngineerGeoElement::ValueTypeToStringRus(value_type));
				}
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_GEO_CUBE_TYPE, CB_SETCURSEL,
					index_value_type+1, (LPARAM)0 );
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				
				CheckRadioButton( hDlg,
					IDC_RADIO_GROUND_DESCRIPTION_NORMATIVE,
					IDC_RADIO_GROUND_DESCRIPTION_CALCULATED_ON_CARRY_ABILITY,
					IDC_RADIO_GROUND_DESCRIPTION_NORMATIVE);

				CheckRadioButton( hDlg,
					IDC_RADIO_STRENGTH_DESCRIPTION_SIMPLE,
					IDC_RADIO_STRENGTH_DESCRIPTION_IN_NATURE_CONDITION,
					IDC_RADIO_STRENGTH_DESCRIPTION_SIMPLE);
			}
			break;
#if !USE_LISTVIEW_STANDART_GE
		case WM_USER + 3:
			{
				printf("WM_USER + 3\n");
				if (lpEngGeoElem)
				{
					lpEngGeoElem->m_ListViewTab.OnEndEdit();
					lpEngGeoElem->UpdateProps();
				}
			}
			break; 
#endif
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
			case IDC_BUTTON_GET_VALUE:
				{
					ShowWindow(GetDlgItem(hDlg, IDC_RADIO_STRENGTH_DESCRIPTION_SIMPLE), EngineerGeoElement::ValueTypeIsStrength(s_value_type));
					ShowWindow(GetDlgItem(hDlg, IDC_RADIO_STRENGTH_DESCRIPTION_ON_SNIP), EngineerGeoElement::ValueTypeIsStrength(s_value_type));
					ShowWindow(GetDlgItem(hDlg, IDC_RADIO_STRENGTH_DESCRIPTION_WATER_SATURETED), EngineerGeoElement::ValueTypeIsStrength(s_value_type));
					ShowWindow(GetDlgItem(hDlg, IDC_RADIO_STRENGTH_DESCRIPTION_IN_TASK_CONDITION), EngineerGeoElement::ValueTypeIsStrength(s_value_type));
					ShowWindow(GetDlgItem(hDlg, IDC_RADIO_STRENGTH_DESCRIPTION_IN_NATURE_CONDITION), EngineerGeoElement::ValueTypeIsStrength(s_value_type));
					ShowWindow(GetDlgItem(hDlg, IDC_STATIC_STRENGTH_DESCRIPTION), EngineerGeoElement::ValueTypeIsStrength(s_value_type));

					ShowWindow(GetDlgItem(hDlg, IDC_EDIT_GEO_ELEMENT_PROP_VALUE), EngineerGeoElement::ValueTypeIsNumeric(s_value_type));
					ShowWindow(GetDlgItem(hDlg, IDC_COMBO_COMBO), !EngineerGeoElement::ValueTypeIsNumeric(s_value_type));
	
					if (!EngineerGeoElement::ValueTypeIsNumeric(s_value_type))
					{
						SendDlgItemMessage( hDlg, IDC_COMBO_COMBO, CB_RESETCONTENT,0,0);
						ShowWindow(GetDlgItem(hDlg, IDC_COMBO_COMBO), false);
						switch (s_value_type)
						{
						case EngineerGeoElement::ValueType::name:
							{
								//return "Имя инженерно-геологического элемента";
								ShowWindow(GetDlgItem(hDlg, IDC_EDIT_GEO_ELEMENT_PROP_VALUE), false);
								ShowWindow(GetDlgItem(hDlg, IDC_COMBO_COMBO), false);
							}
							break;
						case EngineerGeoElement::ValueType::ground_type:
							{
								//return "тип грунта";
								ShowWindow(GetDlgItem(hDlg, IDC_EDIT_GEO_ELEMENT_PROP_VALUE), false);
								ShowWindow(GetDlgItem(hDlg, IDC_COMBO_COMBO), false);
							}
							break;
						case EngineerGeoElement::ValueType::irrigation_type:
							{
								//return "тип обводнения";
								//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
								if (lpEngGeoElem && lpEngGeoElem->GetGround())
								{		
									ShowWindow(GetDlgItem(hDlg, IDC_COMBO_COMBO), true);
									SendDlgItemMessage( hDlg, IDC_COMBO_COMBO, CB_RESETCONTENT,0,0);
									for( CGround::irrigation_type irr_type = CGround::irrigation_type::undefined_irrigation_type; 
										irr_type <= CGround::irrigation_type::water_saturated;
										irr_type++ )
									{
											SendDlgItemMessage( hDlg, IDC_COMBO_COMBO, CB_ADDSTRING, 0,
												(LPARAM)(LPCTSTR)CGround::IrrigationTypeToStringRus(irr_type));
									}
									//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
									CGround::irrigation_type irr_type2 = lpEngGeoElem->GetGround()->GetIrrigationType();
									index_combo = int(irr_type2 - CGround::irrigation_type::undefined_irrigation_type)/20;
									//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
									SendDlgItemMessage( hDlg, IDC_COMBO_COMBO, CB_SETCURSEL,
										index_combo, (LPARAM)0 );
									//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
								}
							}
							break;
						case EngineerGeoElement::ValueType::sand_type:
							{
								//return "тип песка по зернистости";
								if (lpEngGeoElem && lpEngGeoElem->GetGround())
								{	
									CSand * sand = lpEngGeoElem->GetSand();
									if (sand)
									{
										//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
										ShowWindow(GetDlgItem(hDlg, IDC_COMBO_COMBO), true);
										SendDlgItemMessage( hDlg, IDC_COMBO_COMBO, CB_RESETCONTENT,0,0);
										for( CSandGround::sand_type snd_type = CSandGround::sand_type::undefined_sand_type; 
											snd_type <= CSandGround::sand_type::powdered;
											snd_type++ )
										{
												SendDlgItemMessage( hDlg, IDC_COMBO_COMBO, CB_ADDSTRING, 0,
													(LPARAM)(LPCTSTR)CSandGround::SandTypeToStringRus(snd_type));
										}
										CSandGround::sand_type snd_type2 = sand->GetSandType();
										index_combo = int(snd_type2 - CSandGround::sand_type::undefined_sand_type)/10;
										//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
										SendDlgItemMessage( hDlg, IDC_COMBO_COMBO, CB_SETCURSEL,
											index_combo, (LPARAM)0 );
										//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
									}
								}
							}
							break;
						case EngineerGeoElement::ValueType::sand_strength:
							{
								//return "плотность песка";
								if (lpEngGeoElem && lpEngGeoElem->GetGround())
								{	
									CSand * sand = lpEngGeoElem->GetSand();
									if (sand)
									{
										//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
										ShowWindow(GetDlgItem(hDlg, IDC_COMBO_COMBO), true);
										SendDlgItemMessage( hDlg, IDC_COMBO_COMBO, CB_RESETCONTENT,0,0);
										for( CSandGround::sand_strength snd_strength = CSandGround::sand_strength::undefined_sand_strength; 
											snd_strength <= CSandGround::sand_strength::looses;
											snd_strength++ )
										{
												SendDlgItemMessage( hDlg, IDC_COMBO_COMBO, CB_ADDSTRING, 0,
													(LPARAM)(LPCTSTR)CSandGround::SandStrengthToStringRus(snd_strength));
										}
										CSandGround::sand_strength snd_strength2 = sand->GetSandStrength();
										index_combo = int(snd_strength2 - CSandGround::sand_strength::undefined_sand_strength)/20;
										//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
										SendDlgItemMessage( hDlg, IDC_COMBO_COMBO, CB_SETCURSEL,
											index_combo, (LPARAM)0 );
										//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
									}
								}
							}
							break;
						case EngineerGeoElement::ValueType::clay_solidity:
							{
								//return "твёрдость глинистого грунта";
								if (lpEngGeoElem && lpEngGeoElem->GetGround())
								{	
									CClayGround * clayground = lpEngGeoElem->GetClayGround();
									if (clayground)
									{
										//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
										ShowWindow(GetDlgItem(hDlg, IDC_COMBO_COMBO), true);
										SendDlgItemMessage( hDlg, IDC_COMBO_COMBO, CB_RESETCONTENT,0,0);
										for( CClayGround::clay_solidity cl_solidity = CClayGround::clay_solidity::undefined_clay_solidity; 
											cl_solidity <= CClayGround::clay_solidity::fliud;
											cl_solidity++ )
										{
												SendDlgItemMessage( hDlg, IDC_COMBO_COMBO, CB_ADDSTRING, 0,
													(LPARAM)(LPCTSTR)CClayGround::ClaySolidityToStringRus(cl_solidity));
										}
										CClayGround::clay_solidity cl_solidity2 = clayground->GetClaySolidity();
										index_combo = int(cl_solidity2 - CClayGround::clay_solidity::undefined_clay_solidity)/20;
										//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
										SendDlgItemMessage( hDlg, IDC_COMBO_COMBO, CB_SETCURSEL,
											index_combo, (LPARAM)0 );
										//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
									}
								}
							}
							break;
						}
					}
					else
					{
						SetDlgItemText(hDlg,IDC_EDIT_GEO_ELEMENT_PROP_VALUE, "");
						double v;
						if (lpEngGeoElem && lpEngGeoElem->GetValue(s_value_type, s_ground_description_type, s_strength_description_type, v))
						{
							char str[1024];
							sprintf(str, "%f", v);
							SetDlgItemText(hDlg,IDC_EDIT_GEO_ELEMENT_PROP_VALUE, str);
						}
					}
				}
				break;
			case IDC_RADIO_STRENGTH_DESCRIPTION_SIMPLE:
				{
					s_strength_description_type 
						= EngineerGeoElement::StrengthDescriptionType::simple;
					SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_GET_VALUE,0), 0);
				}
				break;		
			case IDC_RADIO_STRENGTH_DESCRIPTION_ON_SNIP:
				{
					s_strength_description_type 
						= EngineerGeoElement::StrengthDescriptionType::on_snip;
					SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_GET_VALUE,0), 0);
				}
				break;	
			case IDC_RADIO_STRENGTH_DESCRIPTION_WATER_SATURETED:
				{
					s_strength_description_type 
						= EngineerGeoElement::StrengthDescriptionType::water_saturated;
					SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_GET_VALUE,0), 0);
				}
				break;	
			case IDC_RADIO_STRENGTH_DESCRIPTION_IN_TASK_CONDITION:
				{
					s_strength_description_type 
						= EngineerGeoElement::StrengthDescriptionType::in_task_condition;
					SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_GET_VALUE,0), 0);
				}
				break;	
			case IDC_RADIO_STRENGTH_DESCRIPTION_IN_NATURE_CONDITION:
				{
					s_strength_description_type 
						= EngineerGeoElement::StrengthDescriptionType::in_nature_condition;
					SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_GET_VALUE,0), 0);
				}
				break;		
			case IDC_RADIO_GROUND_DESCRIPTION_NORMATIVE:
				{
					s_ground_description_type = EngineerGeoElement::GroundDescriptionType
						::normative;
					SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_GET_VALUE,0), 0);
				}
				break;
			case IDC_RADIO_GROUND_DESCRIPTION_CALCULATED_ON_DEFORMATIONS:
				{
					s_ground_description_type = EngineerGeoElement::GroundDescriptionType
						::calculated_on_deformations;
					SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_GET_VALUE,0), 0);
				}
				break;
			case IDC_RADIO_GROUND_DESCRIPTION_CALCULATED_ON_CARRY_ABILITY:
				{
					s_ground_description_type = EngineerGeoElement::GroundDescriptionType
						::calculated_on_carry_ability;
					SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_GET_VALUE,0), 0);
				}
				break;
			case IDC_COMBO_SELECT_GEO_CUBE_TYPE:
				{
					if (HIWORD(wParam) == CBN_SELCHANGE) 
					{
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						index_value_type = -1 + (int)SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_GEO_CUBE_TYPE, CB_GETCURSEL,
									0,(LPARAM)0 );
						if (index_value_type > -1)
						{
							s_value_type = (EngineerGeoElement::ValueType) (index_value_type);
							SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_GET_VALUE,0), 0);
						}
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@	
					}
				}
				break;
			case IDC_COMBO_COMBO:
				{
					printf("IDC_COMBO_COMBO wmEvent = %x\n", wmEvent);
					if (HIWORD(wParam) == CBN_SELCHANGE) 
					{
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						index_combo = (int)SendDlgItemMessage( hDlg, IDC_COMBO_COMBO, CB_GETCURSEL,
								0,(LPARAM)0 );

						if (!EngineerGeoElement::ValueTypeIsNumeric(s_value_type))
						{
							switch (s_value_type)
							{
							case EngineerGeoElement::ValueType::name:
								{
									//return "Имя инженерно-геологического элемента";
									//ShowWindow(GetDlgItem(hDlg, IDC_EDIT_GEO_ELEMENT_PROP_VALUE), false);
									//ShowWindow(GetDlgItem(hDlg, IDC_COMBO_COMBO), false);
								}
								break;
							case EngineerGeoElement::ValueType::ground_type:
								{
									//return "тип грунта";
									///ShowWindow(GetDlgItem(hDlg, IDC_EDIT_GEO_ELEMENT_PROP_VALUE), false);
									///ShowWindow(GetDlgItem(hDlg, IDC_COMBO_COMBO), false);
								}
								break;
							case EngineerGeoElement::ValueType::irrigation_type:
								{
									//return "тип обводнения";
									//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
									if (lpEngGeoElem && lpEngGeoElem->GetGround())
									{		
										//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
										CGround::irrigation_type irr_type = CGround::irrigation_type(index_combo*20);
										lpEngGeoElem->SetIrrigationType(irr_type);
										lpEngGeoElem->FillListViewTab(false);
										//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
									}
								}
								break;
							case EngineerGeoElement::ValueType::sand_type:
								{
									//return "тип песка по зернистости";
									if (lpEngGeoElem && lpEngGeoElem->GetGround())
									{	
										CSand * sand = lpEngGeoElem->GetSand();
										if (sand)
										{
											//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
											CSandGround::sand_type snd_type = CSandGround::sand_type(index_combo*10);
											sand->SetSandType(snd_type);
											lpEngGeoElem->FillListViewTab(false);
											//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
										}
									}
								}
								break;
							case EngineerGeoElement::ValueType::sand_strength:
								{
									//return "плотность песка";
									if (lpEngGeoElem && lpEngGeoElem->GetGround())
									{	
										CSand * sand = lpEngGeoElem->GetSand();
										if (sand)
										{
											//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
											CSandGround::sand_strength snd_strength = CSandGround::sand_strength(index_combo*20);
											sand->SetSandStrength(snd_strength);
											lpEngGeoElem->FillListViewTab(false);
											//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
										}
									}
								}
								break;
							case EngineerGeoElement::ValueType::clay_solidity:
								{
									//return "твёрдость глинистого грунта";
									if (lpEngGeoElem && lpEngGeoElem->GetGround())
									{	
										CClayGround * clayground = lpEngGeoElem->GetClayGround();
										if (clayground)
										{
											//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
											CClayGround::clay_solidity cl_solidity = CClayGround::clay_solidity(index_combo*20);
											clayground->SetClaySolidity(cl_solidity);
											lpEngGeoElem->FillListViewTab(false);
											//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
										}
									}
								}
								break;
							}
						}

						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@		
					}
				}
				break;
			case IDC_BUTTON_SET_VALUE :
				{
					if (index_value_type > -1)
					{
						char str[1024];
						GetDlgItemText(hDlg,IDC_EDIT_GEO_ELEMENT_PROP_VALUE, str, 1023);
						if (ISNUM(str))
						{
							double v = atof(str);
							if (lpEngGeoElem && lpEngGeoElem->SetValue(s_value_type, s_ground_description_type, s_strength_description_type, v))
							{
								lpEngGeoElem->FillListViewTab(false);
							}
						}
					}
				}
				break;
			case IDC_BUTTON_UNSET_VALUE:
				{
					if (lpEngGeoElem)
					{
						if (index_value_type > -1)
						{
							char str[1024];
							GetDlgItemText(hDlg,IDC_EDIT_GEO_ELEMENT_PROP_VALUE, str, 1023);
							if (ISNUM(str))
							{
								double v = atof(str);
								char str[4098];
								sprintf(str, 
									"Вы действительно хотите удалить из инженерно-геологического элемента \"%s\"\n"
									"из набора характеристик \"%s\"\n"
									"значение типа \"%s\" %s, равное %f?", 
									lpEngGeoElem->GetKey().c_str(),
									EngineerGeoElement::GroundDescriptionTypeToString(s_ground_description_type),
									EngineerGeoElement::ValueTypeToStringRus(s_value_type),
									EngineerGeoElement::ValueTypeIsStrength(s_value_type) 
									? EngineerGeoElement::StrengthDescriptionTypeToString(s_strength_description_type) : "",
									v);
								
								if (IDNO != MessageBox(0, str, "Unset Value", MB_YESNO))
								{
									if (lpEngGeoElem && lpEngGeoElem->SetValue(s_value_type, s_ground_description_type, s_strength_description_type, v, false))
									{
										lpEngGeoElem->FillListViewTab(false);
									}
								}
							}
						}
					}
				}
				break;
				
			case IDCANCEL :
				EndDialog( hDlg, IDCANCEL );
				break;

			}
			break;

        case WM_MEASUREITEM: 
			{
				LPMEASUREITEMSTRUCT lpmis = (LPMEASUREITEMSTRUCT) lParam; 
				// Set the height of the list box items. 
				lpmis->itemHeight = YBITMAP3; 	/// А здесь сработало!!!!!!!!!			
				lpmis->itemWidth = 100; 				

				return TRUE; 
			}
			break;

#if !USE_LISTVIEW_STANDART_GE 
        case WM_DRAWITEM: 
			{	
				LPDRAWITEMSTRUCT lpdis = (LPDRAWITEMSTRUCT) lParam; 				
				// If there are no list box items, skip this message. 
				if (lpdis->itemID == -1) 
				{ 
					break; 
				} 
				if (lpdis->hwndItem == hwndList)
				{
					//LONG_PTR userdata = GetWindowLongPtr(hWnd,GWLP_USERDATA);
					//win_project* pwin_project = (win_project*)userdata;
					if (lpEngGeoElem)
					{
						lpEngGeoElem->m_ListViewTab.OnDrawItem(lpdis);
					}
				}
			}
			break;
#endif
		case WM_NOTIFY:
			{
				if (((LPNMHDR) lParam)->hwndFrom == hwndList)
				{
					if (lpEngGeoElem)
					{
						lpEngGeoElem->m_ListViewTab.OnNotify(lParam);
#if USE_LISTVIEW_STANDART_GE 
						if (((LPNMHDR) lParam)->code == LVN_ENDLABELEDIT)
							lpEngGeoElem->UpdateProps();
#endif
						if (((LPNMHDR) lParam)->code == NM_CLICK || ((LPNMHDR) lParam)->code == LVN_ITEMACTIVATE )
						{
							LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE) lParam;
							
							int r = lpnmitem->iItem;
							int c = lpnmitem->iSubItem;

							LPARAM lPar = lpEngGeoElem->m_ListViewTab.GetLParam(size_t(r));
							
							EngineerGeoElement::ValueType value_type;
							EngineerGeoElement::GroundDescriptionType ground_description_type;
							EngineerGeoElement::StrengthDescriptionType strength_description_type;
							if (ParseLParam(lPar, value_type, ground_description_type, strength_description_type))
							{
								s_value_type = value_type;
								s_ground_description_type = ground_description_type;
								s_strength_description_type = strength_description_type;
								SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_GET_VALUE,0), 0);

								CheckRadioButton( hDlg,
									IDC_RADIO_GROUND_DESCRIPTION_NORMATIVE,
									IDC_RADIO_GROUND_DESCRIPTION_CALCULATED_ON_CARRY_ABILITY,
									IDC_RADIO_GROUND_DESCRIPTION_NORMATIVE + s_ground_description_type - EngineerGeoElement::GroundDescriptionType::normative);

								CheckRadioButton( hDlg,
									IDC_RADIO_STRENGTH_DESCRIPTION_SIMPLE,
									IDC_RADIO_STRENGTH_DESCRIPTION_IN_NATURE_CONDITION,
									IDC_RADIO_STRENGTH_DESCRIPTION_SIMPLE + s_strength_description_type - EngineerGeoElement::StrengthDescriptionType::simple);

								//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
								index_value_type = s_value_type - EngineerGeoElement::ValueType::name;
								SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_GEO_CUBE_TYPE, CB_SETCURSEL,
									index_value_type+1, (LPARAM)0 );
								//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
							}
						}
					}
				}
			}
			break;
		case WM_CLOSE:
			{
				return DefWindowProc(hDlg, message, wParam, lParam);
			}
			break;
   }
   return 0;
}



void EngineerGeoElement::PrintfProperties()
{
	this->LithoGeoElement::PrintfProperties();

	if (this->m_ground) 
		this->m_ground->PrintfProperties();
	else
		printf("this->m_ground = NULL\n");

	if (IDOK == DialogBoxParam(hInst, 
			MAKEINTRESOURCE(IDD_DIALOG_ENGINEER_GEO_ELEMENT_PROP), 
			(HWND)NULL, (DLGPROC)DlgProcEngineerGeoElementProp, (LPARAM) this)==IDOK) 
	{
	}	
}

void EngineerGeoElement_PrintfProperties(EngineerGeoElement * ob, vector<fmtstr> & text)
{
	char str[4098];

	sprintf(str, "EngineerGeoElement");
	text.push_back(fmtstr(str, NULL, true, true));

	sprintf(str, "id_umpoz = %d", ob->id_umpoz);
	text.push_back(fmtstr(str, NULL, true, true));

	sprintf(str, "lith_color = %d %d %d"
		, GetRValue(ob->GetColor())
		, GetGValue(ob->GetColor())
		, GetBValue(ob->GetColor())
		);
	text.push_back(fmtstr(str, NULL, true, true));

	sprintf(str, "my_id_key = %d", ob->GetKeyID());
	text.push_back(fmtstr(str, NULL, true, true));

	sprintf(str, "my_key = %s", ob->GetKey().c_str());
	text.push_back(fmtstr(str, NULL, true, true));

	sprintf(str, "\"%s\"", ob->GetName().c_str());
	text.push_back(fmtstr(str, NULL, true, true));

	sprintf(str, "Typ_Shtrihovki = 4.%d", ob->Get_Typ_Shtrihovki());
	text.push_back(fmtstr(str, NULL, true, true));

	CGround::ground_type _ground_type = ob->GetGroungType();
	sprintf(str, "_ground_type = %d", _ground_type);
	text.push_back(fmtstr(str, NULL, true, true));

	// показатель текучести
	double fluidity_index; bool ws = false; 
	bool fluidity_index_defined = false;
	if (ob->GetNormativeFluidityIndex(ws, fluidity_index))
	{
		fluidity_index_defined = true;
	}

	sprintf(str, "показатель текучести fluidity_index_defined = %d fluidity_index = %f", 
		fluidity_index_defined, fluidity_index);
	text.push_back(fmtstr(str, NULL, true, true));

	// степень влажности 
	double degree_of_moisture;
	bool degree_of_moisture_defined = false;
	if (ob->GetNormativeDegreeOfMoisture(degree_of_moisture))
	{
		degree_of_moisture_defined = true;
	}

	sprintf(str, "степень влажности degree_of_moisture_defined = %d degree_of_moisture = %f", 
		degree_of_moisture_defined, degree_of_moisture);
	text.push_back(fmtstr(str, NULL, true, true));
}

void EngineerGeoElement::PrintfProperties(vector<fmtstr> & text)
{
	EngineerGeoElement_PrintfProperties(this, text);
}

void EngineerGeoElement::PrintfProperties(vector<LabData> & labdata)
{
	labdata.push_back(LabData());
	EngineerGeoElement_PrintfProperties(this, labdata.back().text);
}


bool EngineerGeoElement::ValueTypeIsStrength(EngineerGeoElement::ValueType value_type)
{
	switch (value_type)
	{
	case deformation_modulus:
		return true;
	case internal_friction_angle:
		return true;
	case specific_cohesion:
		return true;
	default:
		return false;
	}
	return false;
}
const char * EngineerGeoElement::ValueTypeToStringRus(EngineerGeoElement::ValueType value_type)
{
	switch (value_type)
	{
	case name:
		return "Имя инженерно-геологического элемента";
	case ground_type:
		return "тип грунта";
	case irrigation_type:
		return "тип обводнения";
	case sand_type:
		return "тип песка по зернистости";
	case sand_strength:
		return "плотность песка";
	case clay_solidity:
		return "твёрдость глинистого грунта";
	case specific_gravity_of_ground_particles:
		return "удельный вес частиц грунта,кн/м3";
	case specific_gravity_of_ground:
		return "удельный вес грунта,кн/м3";
	case specific_gravity_of_dry_ground:
		return "удельный вес сухого грунта,кн/м3";
	case specific_gravity_of_water_saturated_ground:
		return "удельный вес водонасыщенного грунта,кн/м3";
	case specific_gravity_of_suspended_in_water_ground:
		return "удельный вес взвешенного в воде грунта,кн/м3";
	case porosity:
		return "пористость (доли ед.)";
	case natural_constitution_porosity_factor:
		return "коэффициент пористости природного слож.доли ед.";
	case natural_moisture:
		return "влажность природная (доли ед.)";
	case water_saturated_moisture:
		return "влажность водонасыщения (доли ед.)";
	case degree_of_moisture:
		return "степень влажности";
	case lack_of_water_saturating:
		return "недостаток водонасыщения(доли ед.)";
	case full_moisture_capacity:
		return "полная влагоемкость";
	case fluidity_index:
		return "показатель текучести";
	case fluidity_index_of_water_saturated_ground:
		return "показатель текучести водонасыщ.грунта";
	case plasticity_index:
		return "число пластичности";
	case moisture_on_fluidity_border:
		return "влажность на границе текучести (доли ед.)";
	case moisture_on_plasticity_border:
		return " влажность на границе пластичности (доли ед.)";
	case deformation_modulus:
		return "модуль деформации грунта";
	case internal_friction_angle:
		return "угол внутреннего трения";
	case specific_cohesion:
		return "удельное сцепление грунта";
	default:
		return "";
	}
	return "";
}


const char * EngineerGeoElement::ValueTypeToString(EngineerGeoElement::ValueType value_type)
{
	switch (value_type)
	{
	case name:
		return "eng geo elem name";
	case ground_type:
		return "ground_type";
	case irrigation_type:
		return "irrigation_type";
	case sand_type:
		return "sand_type";
	case sand_strength:
		return "sand_strength";
	case clay_solidity:
		return "clay_solidity";
	case specific_gravity_of_ground_particles:
		return "specific_gravity_of_ground_particles";
	case specific_gravity_of_ground:
		return "specific_gravity_of_ground";
	case specific_gravity_of_dry_ground:
		return "specific_gravity_of_dry_ground";
	case specific_gravity_of_water_saturated_ground:
		return "specific_gravity_of_water_saturated_ground";
	case specific_gravity_of_suspended_in_water_ground:
		return "specific_gravity_of_suspended_in_water_ground";
	case porosity:
		return "porosity";
	case natural_constitution_porosity_factor:
		return "natural_constitution_porosity_factor";
	case natural_moisture:
		return "natural_moisture";
	case water_saturated_moisture:
		return "water_saturated_moisture";
	case degree_of_moisture:
		return "degree_of_moisture";
	case lack_of_water_saturating:
		return "lack_of_water_saturating";
	case full_moisture_capacity:
		return "full_moisture_capacity";
	case fluidity_index:
		return "fluidity_index";
	case fluidity_index_of_water_saturated_ground:
		return "fluidity_index_of_water_saturated_ground";
	case plasticity_index:
		return "plasticity_index";
	case moisture_on_fluidity_border:
		return "moisture_on_fluidity_border";
	case moisture_on_plasticity_border:
		return "moisture_on_plasticity_border";
	case deformation_modulus:
		return "deformation_modulus";
	case internal_friction_angle:
		return "internal_friction_angle";
	case specific_cohesion:
		return "specific_cohesion";
	default:
		return "";
	}
	return "";
}


bool EngineerGeoElement::ValueTypeIsNumeric(EngineerGeoElement::ValueType value_type)
{
	switch (value_type)
	{
	case specific_gravity_of_ground_particles:
		return true;
	case specific_gravity_of_ground:
		return true;
	case specific_gravity_of_dry_ground:
		return true;
	case specific_gravity_of_water_saturated_ground:
		return true;
	case specific_gravity_of_suspended_in_water_ground:
		return true;
	case porosity:
		return true;
	case natural_constitution_porosity_factor:
		return true;
	case natural_moisture:
		return true;
	case water_saturated_moisture:
		return true;
	case degree_of_moisture:
		return true;
	case lack_of_water_saturating:
		return true;
	case full_moisture_capacity:
		return true;
	case fluidity_index:
		return true;
	case fluidity_index_of_water_saturated_ground:
		return true;
	case plasticity_index:
		return true;
	case moisture_on_fluidity_border:
		return true;
	case moisture_on_plasticity_border:
		return true;
	case deformation_modulus:
		return true;
	case internal_friction_angle:
		return true;
	case specific_cohesion:
		return true;
	default:
		return false;
	}
	return false;
}


const char * EngineerGeoElement::GroundDescriptionTypeToString(EngineerGeoElement::GroundDescriptionType gdt)
{
	switch (gdt)
	{
	case normative:
		return "нормативные значения характеристик";
	case calculated_on_deformations:
		return "по деформациям расчетные значения характеристик";
	case calculated_on_carry_ability:
		return "по несущей способности расчетные значения характеристик";
	default:
		return "";
	}
	return "";
}


const char * EngineerGeoElement::StrengthDescriptionTypeToString(EngineerGeoElement::StrengthDescriptionType sdt)
{
	switch (sdt)
	{
	case simple:
		return "simple";
	case on_snip:
		return "on_snip";
	case water_saturated:
		return "water_saturated";
	case in_task_condition:
		return "in_task_condition";
	case in_nature_condition:
		return "in_nature_condition";
	case any:
		return "any";
	default:
		return "";
	}
	return "";
}

CSand * EngineerGeoElement::GetSand ()
{
	if (!this->m_ground) return NULL;
	CSand * sand = dynamic_cast<CSand *>(this->m_ground);
	return sand;
}

CClayGround * EngineerGeoElement::GetClayGround ()
{
	if (!this->m_ground) return NULL;
	CClayGround * clayground = dynamic_cast<CClayGround *>(this->m_ground);
	return clayground;
}

bool EngineerGeoElement::GetValue(EngineerGeoElement::ValueType value_type,
								  EngineerGeoElement::GroundDescriptionType ground_description_type,
								  EngineerGeoElement::StrengthDescriptionType strength_description_type, 
								  double & v)
{
	if (strength_description_type == EngineerGeoElement::StrengthDescriptionType::any)
	{
		
		for (EngineerGeoElement::StrengthDescriptionType sdt = simple;
			sdt <= in_nature_condition; sdt++)
		{
			if( Get_Value(value_type, ground_description_type, sdt, v) )
			{
				if(to_print_if_any)
				{
					char str[1024];
					sprintf(str, "my_key = \"%s\"\t\0", this->my_key.c_str());
					CharToOem(str,str);
					printf(str);
					cout << "StrengthDescriptionType = " << StrengthDescriptionTypeToString(sdt) << endl;

					to_print_if_any = false;
				}
				return true;
			}
		}

	}
	else
	{
		return Get_Value(value_type, ground_description_type, strength_description_type, v);
	}
	return false;

}
bool EngineerGeoElement::GetValue(LabTrialValueType & vt, LabNormatives::type lab_normatives_type,
								  double & v)
{
	if (!this->m_lablayer) return false;

	map<LabTrialValueType, normative_value>::iterator it = m_lablayer->lab_normatives->values.find(vt);
	if (it != m_lablayer->lab_normatives->values.end())
	{
		switch(lab_normatives_type)
		{
		case LabNormatives::type::normative:
			{
				if ((*it).second.v_n.f)
				{
					v = (*it).second.v_n.v;
					return true;
				}
			}
			break;
		case LabNormatives::type::raschotn_85:
			{
				if ((*it).second.v_85.f)
				{
					v = (*it).second.v_85.v;
					return true;
				}
			}
			break;
		case LabNormatives::type::raschotn_95:
			{
				if ((*it).second.v_95.f)
				{
					v = (*it).second.v_95.v;
					return true;
				}
			}
			break;
		case LabNormatives::type::raschotn_99:
			{
				if ((*it).second.v_99.f)
				{
					v = (*it).second.v_99.v;
					return true;
				}
			}
			break;
		}
	}
	return false;
}
CGround::ground_type EngineerGeoElement::GetGroungType()
{
	CGround::ground_type current_ground_type = CGround::ground_type::Undefined_ground;
	if (this->GetGround())
	{
		current_ground_type = this->GetGround()->GetGroungType();
	}
	else if (this->GetLabLayer())
	{
		if (this->GetLabLayer()->lab_normatives)
		{
			LabTrialValueType vt;
			vt.clear();
			vt.m_indication = LabTrial::indication::physical;
			vt.is_result = true;
			vt.vt_PhysicalLabTrialResults = PhysicalLabTrialResults::value_type::vt_ground_type;
			vt.m_lablayer = this->GetLabLayer();
			map<LabTrialValueType, normative_value>::iterator it = 
				this->GetLabLayer()->lab_normatives->values.find(vt);
			if (it != this->GetLabLayer()->lab_normatives->values.end())
			{
				current_ground_type = CGround::ground_type(int((*it).second.v_n.v));
			}
		}
	}
	if (current_ground_type == CGround::ground_type::Undefined_ground)
	{
		if (this->to_print_repeating_warning)
		{
			char str[1024];
			sprintf(str, "Warning: ИГЭ %s тип грунта не определён!!!\n", 
				this->GetKey().c_str());
			MessageBox(0, str, "GetGroungType", 0);
			this->to_print_repeating_warning = false;
		}
	}
	return current_ground_type;
}
FractionsLabTrialResults::SandSoilsClass EngineerGeoElement::GetSandSoilClass()
{
	FractionsLabTrialResults::SandSoilsClass sand_soil_class = FractionsLabTrialResults::SandSoilsClass::undefined_sand_soil;

	if (this->GetLabLayer() && this->GetLabLayer()->lab_normatives)
	{
		LabTrialValueType vt;
		vt.clear();
		vt.m_indication = LabTrial::indication::fractions;
		vt.is_result = true;
		vt.vt_FractionsLabTrialResults = FractionsLabTrialResults::value_type::vt_sand_soil_class;
		vt.m_lablayer = this->GetLabLayer();
		map<LabTrialValueType, normative_value>::iterator it = 
			this->GetLabLayer()->lab_normatives->values.find(vt);
		if (it != this->GetLabLayer()->lab_normatives->values.end())
		{
			sand_soil_class = 
				FractionsLabTrialResults::SandSoilsClass(int((*it).second.v_n.v));
		}
	}
	return sand_soil_class;
}


FractionsLabTrialResults::ClaySoilsClass EngineerGeoElement::GetClaySoilClass()
{
	FractionsLabTrialResults::ClaySoilsClass clay_soil_class = FractionsLabTrialResults::ClaySoilsClass::undefined_clay_soil;

	if (this->GetLabLayer() && this->GetLabLayer()->lab_normatives)
	{
		LabTrialValueType vt;
		vt.clear();
		vt.m_indication = LabTrial::indication::fractions;
		vt.is_result = true;
		vt.vt_FractionsLabTrialResults = FractionsLabTrialResults::value_type::vt_clay_soil_class;
		vt.m_lablayer = this->GetLabLayer();
		map<LabTrialValueType, normative_value>::iterator it = 
			this->GetLabLayer()->lab_normatives->values.find(vt);
		if (it != this->GetLabLayer()->lab_normatives->values.end())
		{
			clay_soil_class = 
				FractionsLabTrialResults::ClaySoilsClass(int((*it).second.v_n.v));
		}
	}
	return clay_soil_class;
}



bool EngineerGeoElement::GetNormativePorostyFactor(double & e)
{
	bool e_determined = false;												
	if (this->GetLabLayer() && this->GetLabLayer()->lab_normatives)
	{
		LabTrialValueType vte;
		vte.clear();
		vte.m_indication = LabTrial::indication::physical;
		vte.is_result = true;
		vte.vt_PhysicalLabTrialResults = PhysicalLabTrialResults::value_type::vt_e;
		vte.m_lablayer = this->GetLabLayer();
		
		e_determined = this->GetValue(vte, LabNormatives::type::normative, e);
	}
	if (!e_determined)
	{
		e_determined = this->GetValue(EngineerGeoElement::ValueType::natural_constitution_porosity_factor,
			EngineerGeoElement::GroundDescriptionType::normative,
			EngineerGeoElement::StrengthDescriptionType::simple, 
			e);
	}
	if (!e_determined)
	{
		if (this->to_print_repeating_warning)
		{
			char str[1024];
			sprintf(str, "Warning: ИГЭ %s нормативное значение коэффициента пористости не определено!!!\n", 
				this->GetKey().c_str());
			MessageBox(0, str, "GetNormativePorostyFactor", 0);
			this->to_print_repeating_warning = false;
		}
	}
			
	return e_determined;
}
bool EngineerGeoElement::GetNormativeDegreeOfMoisture(double & degree_of_moisture)
{
	// степень влажности 
	bool determined = false;
	if (this->GetLabLayer() && this->GetLabLayer()->lab_normatives)
	{
		LabTrialValueType vt;
		vt.clear();
		vt.m_indication = LabTrial::indication::physical;
		vt.is_result = true;
		vt.vt_PhysicalLabTrialResults = PhysicalLabTrialResults::value_type::vt_S;
		vt.m_lablayer = this->GetLabLayer();
		
		determined = this->GetValue(vt, LabNormatives::type::normative, degree_of_moisture);

	}
	if (!determined)
	{
		if (this->GetValue(EngineerGeoElement::ValueType::degree_of_moisture,
			EngineerGeoElement::GroundDescriptionType::normative,
			EngineerGeoElement::StrengthDescriptionType::simple, 
			degree_of_moisture))
		{
			determined = true;
		}
	}
	if (!determined)
	{
		if (this->to_print_repeating_warning)
		{
			char str[1024];
			sprintf(str, "Warning: ИГЭ %s нормативное значение степени влажности не определено!!!\n", 
				this->GetKey().c_str());
			MessageBox(0, str, "GetNormativeDegreeOfMoisture", 0);
			this->to_print_repeating_warning = false;
		}
	}
	return determined;
}
bool EngineerGeoElement::GetNormativeFluidityIndex(bool ws, double & IL)
{
	LabTrialValueType vtIL;
	vtIL.clear();
	vtIL.m_indication = LabTrial::indication::physical;
	vtIL.is_result = true;
	if (ws)
		vtIL.vt_PhysicalLabTrialResults = PhysicalLabTrialResults::value_type::vt_fluidity_index_water_saturated;
	else
		vtIL.vt_PhysicalLabTrialResults = PhysicalLabTrialResults::value_type::vt_fluidity_index_nature;
	vtIL.m_lablayer = this->GetLabLayer();
	
	bool IL_determined = this->GetValue(vtIL, LabNormatives::type::normative, IL);

	if (!IL_determined)
	{
		if (ws)
		{
			IL_determined = this->GetValue(EngineerGeoElement::ValueType::fluidity_index_of_water_saturated_ground,
				EngineerGeoElement::GroundDescriptionType::normative,
				EngineerGeoElement::StrengthDescriptionType::simple, 
				IL);
		}
		else
		{
			IL_determined = this->GetValue(EngineerGeoElement::ValueType::fluidity_index,
				EngineerGeoElement::GroundDescriptionType::normative,
				EngineerGeoElement::StrengthDescriptionType::simple, 
				IL);
		}
	}
	if (!IL_determined)
	{
		if (this->to_print_repeating_warning)
		{
			char str[1024];
			sprintf(str, "Warning: ИГЭ %s показатель текучести %s(нормативное значение) не определён!!!\n", 
				this->GetKey().c_str(),
				ws ? "водонасыщенного грунта " : "");
			MessageBox(0, str, "GetNormativeFluidityIndex", 0);
			this->to_print_repeating_warning = false;
		}
	}
	return IL_determined;
}
bool EngineerGeoElement::Get_Value(EngineerGeoElement::ValueType value_type,
								  EngineerGeoElement::GroundDescriptionType ground_description_type,
								  EngineerGeoElement::StrengthDescriptionType strength_description_type, 
								  double & v)
{
	GroundDescription  * ground_description = NULL;
	if (!this->m_ground) return false;
	/*
	//нормативные значения характеристик 
	GroundDescription normative_description;
	//расчетные значения характеристик
	// при расчетах оснований:          
	// по деформациям:
	GroundDescription calculated_on_deformations_description;
	// по несущей способности   
	GroundDescription calculated_on_carry_ability_description;
*/
	switch( ground_description_type )
	{
	case normative:
		{
			//нормативные значения характеристик 
			ground_description = &this->m_ground->normative_description;
		}
		break;
		//расчетные значения характеристик
		// при расчетах оснований:          
	case calculated_on_deformations:
		{
			// по деформациям:
			ground_description = &this->m_ground->calculated_on_deformations_description;
		}
		break;
	case calculated_on_carry_ability:
		{
			// по несущей способности   
			ground_description = &this->m_ground->calculated_on_carry_ability_description;
		}
		break;		
	};

	if (!ground_description) return false;

	StrengthDescription * strength_description = NULL;
	switch ( strength_description_type )
	{
	case simple:
		{
			strength_description = &ground_description->strength_description;
		}
		break;
	case on_snip:
		{
			strength_description = &ground_description->strength_description_on_snip;
		}
		break;
	case water_saturated:
		{
			strength_description = &ground_description->strength_description_water_saturated;
		}
		break;
	case in_task_condition:
		{
			strength_description = &ground_description->strength_description_in_task_condition;
		}
		break;
	case in_nature_condition:
		{
			strength_description = &ground_description->strength_description_in_nature_condition;
		}
		break;
	};


	switch (value_type)
	{
	case name:
		{
			v = atof(my_key.c_str());
			return true;
		}
		break;
/*	case sand_type:
		{
			if (this->m_ground_type == CGround::ground_type::Sand)
			{
				if (this->m_ground && this->m_ground->m_type == CGround::ground_type::Sand)
				{
					CSand * sand = dynamic_cast<CSand *>(this->m_ground);
					if(sand)
					{
						v = double(int(sand->GetSandType()));
						return true;
					}
				}
			}
			return false;
		}
		break;*/
	case specific_gravity_of_ground_particles:
		{
			if (ground_description->specific_gravity_of_ground_particles_defined)
			{
				v = ground_description->specific_gravity_of_ground_particles;
				return true;
			}
			return false;
		}
		break;
	case specific_gravity_of_ground:
		{
			if (ground_description->specific_gravity_of_ground_defined)
			{
				v = ground_description->specific_gravity_of_ground;
				return true;
			}
			return false;
		}
		break;
	case specific_gravity_of_dry_ground:
		{
			if (ground_description->specific_gravity_of_dry_ground_defined)
			{
				v = ground_description->specific_gravity_of_dry_ground;
				return true;
			}
			return false;
		}
		break;
	case specific_gravity_of_water_saturated_ground:
		{
			if (ground_description->specific_gravity_of_water_saturated_ground_defined)
			{
				v = ground_description->specific_gravity_of_water_saturated_ground;
				return true;
			}
			return false;
		}
		break;
	case specific_gravity_of_suspended_in_water_ground:
		{
			if (ground_description->specific_gravity_of_suspended_in_water_ground_defined)
			{
				v = ground_description->specific_gravity_of_suspended_in_water_ground;
				return true;
			}
			return false;
		}
		break;
	case porosity:
		{
			if (ground_description->porosity_defined)
			{
				v = ground_description->porosity;
				return true;
			}
			return false;
		}
		break;
	case natural_constitution_porosity_factor:
		{
			if (ground_description->natural_constitution_porosity_factor_defined)
			{
				v = ground_description->natural_constitution_porosity_factor;
				return true;
			}
			return false;
		}
		break;
	case natural_moisture:
		{
			if (ground_description->natural_moisture_defined)
			{
				v = ground_description->natural_moisture;
				return true;
			}
			return false;
		}
		break;
	case water_saturated_moisture:
		{
			if (ground_description->water_saturated_moisture_defined)
			{
				v = ground_description->water_saturated_moisture;
				return true;
			}
			return false;
		}
		break;
	case degree_of_moisture:
		{
			if (ground_description->degree_of_moisture_defined)
			{
				v = ground_description->degree_of_moisture;
				return true;
			}
			return false;
		}
		break;
	case lack_of_water_saturating:
		{
			if (ground_description->lack_of_water_saturating_defined)
			{
				v = ground_description->lack_of_water_saturating;
				return true;
			}
			return false;
		}
		break;
	case full_moisture_capacity:
		{
			if (ground_description->full_moisture_capacity_defined)
			{
				v = ground_description->full_moisture_capacity;
				return true;
			}
			return false;
		}
		break;
	case fluidity_index:
		{
			if (ground_description->fluidity_index_defined)
			{
				v = ground_description->fluidity_index;
				return true;
			}
			return false;
		}
		break;
	case fluidity_index_of_water_saturated_ground:
		{
			if (ground_description->fluidity_index_of_water_saturated_ground_defined)
			{
				v = ground_description->fluidity_index_of_water_saturated_ground;
				return true;
			}
			return false;
		}
		break;
	case plasticity_index:
		{
			if (ground_description->plasticity_index_defined)
			{
				v = ground_description->plasticity_index;
				return true;
			}
			return false;
		}
		break;
	case moisture_on_fluidity_border:
		{
			if (ground_description->moisture_on_fluidity_border_defined)
			{
				v = ground_description->moisture_on_fluidity_border;
				return true;
			}
			return false;
		}
		break;
	case moisture_on_plasticity_border:
		{
			if (ground_description->moisture_on_plasticity_border_defined)
			{
				v = ground_description->moisture_on_plasticity_border;
				return true;
			}
			return false;
		}
		break;
	case deformation_modulus:
		{
			if (strength_description && strength_description->deformation_modulus_defined)
			{
				v = strength_description->deformation_modulus;
				return true;
			}
			return false;
		}
		break;
	case internal_friction_angle:
		{
			if (strength_description && strength_description->internal_friction_angle_defined)
			{
				v = strength_description->internal_friction_angle;
				return true;
			}
			return false;
		}
		break;
	case specific_cohesion:
		{
			if (strength_description && strength_description->specific_cohesion_defined)
			{
				v = strength_description->specific_cohesion;
				return true;
			}
			return false;
		}
		break;
	default:
		return false;
	}
	return false;
}



bool EngineerGeoElement::SetValue(EngineerGeoElement::ValueType value_type,
								  EngineerGeoElement::GroundDescriptionType ground_description_type,
								  EngineerGeoElement::StrengthDescriptionType strength_description_type, 
								  double v, bool defined)
{
	GroundDescription  * ground_description = NULL;
	if (!this->m_ground) return false;
	/*
	//нормативные значения характеристик 
	GroundDescription normative_description;
	//расчетные значения характеристик
	// при расчетах оснований:          
	// по деформациям:
	GroundDescription calculated_on_deformations_description;
	// по несущей способности   
	GroundDescription calculated_on_carry_ability_description;
*/
	switch( ground_description_type )
	{
	case normative:
		{
			//нормативные значения характеристик 
			ground_description = &this->m_ground->normative_description;
		}
		break;
		//расчетные значения характеристик
		// при расчетах оснований:          
	case calculated_on_deformations:
		{
			// по деформациям:
			ground_description = &this->m_ground->calculated_on_deformations_description;
		}
		break;
	case calculated_on_carry_ability:
		{
			// по несущей способности   
			ground_description = &this->m_ground->calculated_on_carry_ability_description;
		}
		break;		
	};

	if (!ground_description) return false;

	StrengthDescription * strength_description = NULL;
	switch ( strength_description_type )
	{
	case simple:
		{
			strength_description = &ground_description->strength_description;
		}
		break;
	case on_snip:
		{
			strength_description = &ground_description->strength_description_on_snip;
		}
		break;
	case water_saturated:
		{
			strength_description = &ground_description->strength_description_water_saturated;
		}
		break;
	case in_task_condition:
		{
			strength_description = &ground_description->strength_description_in_task_condition;
		}
		break;
	case in_nature_condition:
		{
			strength_description = &ground_description->strength_description_in_nature_condition;
		}
		break;
	};


	switch (value_type)
	{
/*	case name:
		{
			v = atof(my_key.c_str());
			return true;
		}
		break;
	case sand_type:
		{
			if (this->m_ground_type == CGround::ground_type::Sand)
			{
				if (this->m_ground && this->m_ground->m_type == CGround::ground_type::Sand)
				{
					CSand * sand = dynamic_cast<CSand *>(this->m_ground);
					if(sand)
					{
						v = double(int(sand->GetSandType()));
						return true;
					}
				}
			}
			return false;
		}
		break;*/
	case specific_gravity_of_ground_particles:
		{
			ground_description->specific_gravity_of_ground_particles_defined = defined;
			ground_description->specific_gravity_of_ground_particles = v;
			return true;
		}
		break;
	case specific_gravity_of_ground:
		{
			ground_description->specific_gravity_of_ground_defined = defined;
			ground_description->specific_gravity_of_ground = v;
			return true;
		}
		break;
	case specific_gravity_of_dry_ground:
		{
			ground_description->specific_gravity_of_dry_ground_defined = defined;
			ground_description->specific_gravity_of_dry_ground = v;
			return true;
		}
		break;
	case specific_gravity_of_water_saturated_ground:
		{
			ground_description->specific_gravity_of_water_saturated_ground_defined = defined;
			ground_description->specific_gravity_of_water_saturated_ground = v;
			return true;
		}
		break;
	case specific_gravity_of_suspended_in_water_ground:
		{
			ground_description->specific_gravity_of_suspended_in_water_ground_defined = defined;
			ground_description->specific_gravity_of_suspended_in_water_ground = v;
			return true;
		}
		break;
	case porosity:
		{
			ground_description->porosity_defined = defined;				
			ground_description->porosity = v;
			return true;
		}
		break;
	case natural_constitution_porosity_factor:
		{
			ground_description->natural_constitution_porosity_factor_defined = defined;
			ground_description->natural_constitution_porosity_factor = v;
			return true;
		}
		break;
	case natural_moisture:
		{
			ground_description->natural_moisture_defined = defined;
			ground_description->natural_moisture = v;
			return true;
		}
		break;
	case water_saturated_moisture:
		{
			ground_description->water_saturated_moisture_defined = defined;
			ground_description->water_saturated_moisture = v;
			return true;
		}
		break;
	case degree_of_moisture:
		{
			ground_description->degree_of_moisture_defined = defined;
			ground_description->degree_of_moisture = v;
			return true;
		}
		break;
	case lack_of_water_saturating:
		{
			ground_description->lack_of_water_saturating_defined = defined;
			ground_description->lack_of_water_saturating = v;
			return true;
		}
		break;
	case full_moisture_capacity:
		{
			ground_description->full_moisture_capacity_defined = defined;
			ground_description->full_moisture_capacity = v;
			return true;
		}
		break;
	case fluidity_index:
		{
			ground_description->fluidity_index_defined = defined;
			ground_description->fluidity_index = v;
			return true;
		}
		break;
	case fluidity_index_of_water_saturated_ground:
		{
			ground_description->fluidity_index_of_water_saturated_ground_defined = defined;
			ground_description->fluidity_index_of_water_saturated_ground = v;
			return true;
		}
		break;
	case plasticity_index:
		{
			ground_description->plasticity_index_defined = defined;
			ground_description->plasticity_index = v;
			return true;
		}
		break;
	case moisture_on_fluidity_border:
		{
			ground_description->moisture_on_fluidity_border_defined = defined;
			ground_description->moisture_on_fluidity_border = v;
			return true;
		}
		break;
	case moisture_on_plasticity_border:
		{
			ground_description->moisture_on_plasticity_border_defined = defined;
			ground_description->moisture_on_plasticity_border = v;
			return true;
		}
		break;
	case deformation_modulus:
		{
			if (strength_description)
			{
				strength_description->deformation_modulus_defined = defined;
				strength_description->deformation_modulus = v;
				return true;
			}
			return false;
		}
		break;
	case internal_friction_angle:
		{
			if (strength_description)
			{
				strength_description->internal_friction_angle_defined = defined;
				strength_description->internal_friction_angle = v;
				return true;
			}
			return false;
		}
		break;
	case specific_cohesion:
		{
			if (strength_description)
			{
				strength_description->specific_cohesion_defined = defined;
				strength_description->specific_cohesion = v;
				return true;
			}
			return false;
		}
		break;
	default:
		return false;
	}
	return false;
}



bool EngineerGeoElement::ReadKey(char *szBuff)
{
	// ключ - имя инж-гео элемента

	char substr[] = "инженерно-геологический элемент\0";
	char * p = ParseSubStrings(szBuff, substr);
	if (p)
	{
		this->my_key = p;
		this->my_key_read = true;

		CharToOem(p,p);
		printf("this->my_key = \"%s\"\n", p);
		return true;
	}
	return false;
}



EngineerGeoElement::Typ_Shtrihovki EngineerGeoElement::Get_Typ_Shtrihovki()
{
	Typ_Shtrihovki m_ts = ts_unknown;

	CGround::ground_type _ground_type = this->GetGroungType();

	// показатель текучести
	double fluidity_index; bool ws = false; 
	bool fluidity_index_defined = false;
	if (this->GetNormativeFluidityIndex(ws, fluidity_index))
	{
		fluidity_index_defined = true;
	}

	// степень влажности 
	double degree_of_moisture;
	bool degree_of_moisture_defined = false;
	if (this->GetNormativeDegreeOfMoisture(degree_of_moisture))
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
	return m_ts;
}



int EngineerGeoElement::ParseFileLine(char* szBuff, int type_line)
{
	//printf("ParseEGEFileLine(szBuff = \"%s\", type_line = %d)\)\n", szBuff, type_line);

	switch(type_line)
	{
		// ключ - имя инж-гео элемента
	case 1:
		{
			char substr[] = "инженерно-геологический элемент\0";
			char * p = ParseSubStrings(szBuff, substr);
			if (p)
			{
				this->my_key = p;
				this->my_key_read = true;

				CharToOem(p,p);
				printf("this->my_key = \"%s\"\n", p);
				return 0;
			}
		}
		break;
		// литология - пески, супеси, суглинки, глины
	case 2:
		{
			char substr[] = "пески\0";
			char * p = ParseSubStrings(szBuff, substr);
			if (p)
			{				
				this->m_ground_type = CGround::ground_type::Sand;
				this->m_ground = new CSand();
				CharToOem(p,p);
				printf("this->m_ground_type = CGround::ground_type::Sand\"%s\"\n", p);
				cout << p << endl;
				return 2;
			}
		}
		break;
	case 3:
		{
			char substr[] = "супеси\0";
			char * p = ParseSubStrings(szBuff, substr);
			if (p)
			{				
				this->m_ground_type = CGround::ground_type::SandyLoam;
				this->m_ground = new CSandyLoam();
				CharToOem(p,p);
				printf("this->m_ground_type = CGround::ground_type::SandyLoam;\"%s\"\n", p);
				cout << p << endl;
				return 2;
			}
		}
		break;
	case 4:
		{
			char substr[] = "суглинки\0";
			char * p = ParseSubStrings(szBuff, substr);
			if (p)
			{				
				this->m_ground_type = CGround::ground_type::Loam;
				this->m_ground = new CLoam();
				CharToOem(p,p);
				printf("this->m_ground_type = CGround::ground_type::Loam;\"%s\"\n", p);
				cout << p << endl;
				return 2;
			}
		}
		break;
	case 5:
		{
			char substr[] = "глины\0";
			char * p = ParseSubStrings(szBuff, substr);
			if (p)
			{				
				this->m_ground_type = CGround::ground_type::Clay;
				this->m_ground = new CClay();
				CharToOem(p,p);
				printf("this->m_ground_type = CGround::ground_type::Clay;\"%s\"\n", p);
				cout << p << endl;
				return 2;
			}
		}
		break;
	case 6:
		{
			char substr[] = "нормативные значения характеристик\0";
			char * p = ParseSubStrings(szBuff, substr);
			if (p)
			{				
				return 0;
			}
		}
		break;
	default :
		return 1;
	}

	return -1;
}
extern bool UseStrStr;		

int EngineerGeoElement::ReadingFile(FILE * stream,  char* szBuff, int n)
{
#if LOG_UNPARSED
	FILE * log = fopen("unparsed.log","wt");
#endif
	char * ch;
	bool to_read_by_ground_object = false;

	while (!feof(stream))
	{
		ch = fgets(szBuff,n,stream);
		if( ch != NULL && strlen(szBuff) > 1)
		{	
			DeleteCenterNullTerminator(szBuff, n);

			bool to_parse_line = true;
			bool to_break_read_file = false;

			UseStrStr = false;	
			
			for (int type_line = 1; to_parse_line; type_line++) 
			{                
				int res = ParseFileLine(szBuff, type_line);
				if (res == -1)
				{
					// неудачный разбор строки
#if LOG_UNPARSED
					if (log) fprintf(log,szBuff);
#endif
				}
				else if (res == 0)
				{
					// удачный разбор строки
					to_parse_line = false;
					cout << szBuff << endl;
				}
				else if (res == 1)
				{
					//перебраны все возможные варианты
					to_parse_line = false;
				}				
				else if (res == 2)
				{
					// создан объект грунта
					// передаём чтение файла ему
					to_parse_line = false;
					to_break_read_file = true;
					to_read_by_ground_object = true;
					cout << szBuff << endl;
				}
			}
			if(to_break_read_file)
				break;
		}
		else 
		{
			//break;
		}
	}
	int result = 1;

#if LOG_UNPARSED
	if (log) fclose(log);
#endif

	if(to_read_by_ground_object && this->m_ground)
		result = this->m_ground->ReadingFile(stream,  szBuff, n);
	
	return result;
}


bool EngineerGeoElement::ReadFile(const char *file)
{
	printf("EngineerGeoElement::ReadFile(\"%s\")\n",file);

	const int n=16384; // length of buffer string line
	char* szBuff; // buffer string line
	if ((szBuff = (char *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,n*sizeof(char))) == NULL)
	{
		MessageBox(0, "vX - Not enough memory",
			"importExcelCommonFileParam()", 0);
		return false;
	}

	FILE *stream;
	if ((stream = fopen(file,"rt")) == NULL)
	{
		char errstr[2048];
		sprintf(errstr, "SurfDoc::ReadZondFile:fopen(%s)", file);
		ErrorExit(errstr);
		return false;
	}
	int res = 1;

	EngineerGeoElement * geo_element = this;

	bool f1,f2,f3,f4,f5;
	f1 = f2 = f3 = f4 = f5 = false;

	if ( (res = geo_element->ReadingFile(stream, szBuff, n)) == 2)
	{
		do
		{
			
			geo_element = new EngineerGeoElement(my_geo_colomn->GetNewKeyID());
			if (geo_element && 
				(f1 = geo_element->ReadKey(szBuff)) && 
				(res = geo_element->ReadingFile(stream, szBuff, n)) > 0 && 
				(f2 = geo_element->KeyRead()) && 
				(f3 = my_geo_colomn != NULL) && 
				(f4 = my_geo_colomn->geo_elements.find(geo_element->GetKey()) == my_geo_colomn->geo_elements.end()) &&
				(f5 = my_geo_colomn->AddNewGeoElement(geo_element->GetKey(), geo_element) != NULL)
				)
			{
				my_geo_colomn->ReDrawItem_OnTree(my_geo_colomn->m_pSurfDoc ? my_geo_colomn->m_pSurfDoc->hwndTV : NULL);
			}
			else
			{
				long id_key = geo_element->GetKeyID();
				GeoElement::operator delete (geo_element, this->m_type, id_key);
				printf("4 res = %d f1 = %d f2 = %d f3 = %d f4 = %d f5 = %d\n", res, f1,f2,f3,f4,f5);
			}
		}
		while(res == 2);
	}

	printf("EngineerGeoElement::ReadFile() end res = %d\n", res);

	fclose(stream);
	HeapFree( GetProcessHeap(), 0, szBuff );
	return res > 0;
}
bool EngineerGeoElement::SaveAs()
{
	bool status = false;
	DWORD nFilterIndex = 0;
	char file[2048];
	file[0] = '\0';
	strcpy(file, this->my_key.c_str());
	if (SaveFileDlg(this->m_pSurfDoc ? this->m_pSurfDoc->hSurfWnd : NULL, file,
		"Ground As Dat(*.dat)\0*.dat\0"
		"All files \0*.*\0", nFilterIndex) == S_OK)
	{	
		switch(nFilterIndex)
		{
		case 1:
			status = SaveGroundAsDat(file);
			break;
		}
		
	}
	return status;
}
bool EngineerGeoElement::SaveGroundAsDat(const char * fn)
{
	FILE * stream;
	if ((stream = fopen(fn,"wt")) == NULL)
	{
		char errstr[1024];
		sprintf(errstr, "Cannot open output file.\n%s", fn);
		MessageBox(0, errstr, "SaveGroundAsDat", 
			MB_OK | MB_ICONINFORMATION);
		return -1;
	}

	if (stream)
	{
		//this->m_ground->Ground_Serialize
				/*ar << m_irrigation_type;
				//нормативные значения характеристик 
				ar << normative_description;
				//расчетные значения характеристик
				// при расчетах оснований:          
				// по деформациям:
				ar << calculated_on_deformations_description;
				// по несущей способности   
				ar << calculated_on_carry_ability_description;*/

		if (this->m_ground)
			this->m_ground->SavingAsDat(stream);


		fclose (stream);
	}
	return false;
}
Archive& operator <<(Archive& ar, GeoElement::type & tp)
{
	int t = int  (tp);
	ar << t;

	return ar;
}
Archive& operator >>(Archive& ar, GeoElement::type & tp)
{
	int t;
	ar >> t;

	tp = (GeoElement::type) t;

	return ar;
}

Archive& operator <<(Archive& ar, CGround::ground_type & tp)
{
	int t = int  (tp);
	ar << t;

	return ar;
}
Archive& operator >>(Archive& ar, CGround::ground_type & tp)
{
	int t;
	ar >> t;

	tp = (CGround::ground_type) t;

	return ar;
}
Archive& operator <<(Archive& ar, CGround::irrigation_type & tp)
{
	int t = int  (tp);
	ar << t;

	return ar;
}
Archive& operator >>(Archive& ar, CGround::irrigation_type & tp)
{
	int t;
	ar >> t;

	tp = (CGround::irrigation_type) t;

	return ar;
}
void CGround::Ground_Serialize(Archive & ar)
{
	//printf("CGround::Ground_Serialize(Archive& ar)\n");
	if (ar.IsStoring())
	{
		ar << m_cground_version;
		switch (m_cground_version)
		{
		case 1:
			{
				ar << m_irrigation_type;
				//нормативные значения характеристик 
				ar << normative_description;
				//расчетные значения характеристик
				// при расчетах оснований:          
				// по деформациям:
				ar << calculated_on_deformations_description;
				// по несущей способности   
				ar << calculated_on_carry_ability_description;
			}
			break;
		default:
			{
				throw VersionException(m_cground_version, VersionException::cannot_store, Object::object_type::undefined);
			}
			break;
		}
	}
	else
	{
		ar >> m_cground_version;
		switch (m_cground_version)
		{
		case 1:
			{
				ar >> m_irrigation_type;
				//нормативные значения характеристик 
				ar >> normative_description;
				//расчетные значения характеристик
				// при расчетах оснований:          
				// по деформациям:
				ar >> calculated_on_deformations_description;
				// по несущей способности   
				ar >> calculated_on_carry_ability_description;
			}
			break;
		default:
			{
				throw VersionException(m_cground_version, VersionException::cannot_load,  Object::object_type::undefined);
			}
			break;
		}
	}
}
Archive& operator <<(Archive& ar, GeoElement * e)
{
	//printf("Archive& operator <<(Archive& ar, GeoElement * e)\n");

	bool allocated = false;

	if (e)
	{
		allocated = true;
		ar << allocated;
		ar << e->m_type;
		if (e) e->Object::Serialize(ar);
		if (e) e->GeoElement_Serialize(ar);
		if (e) e->GeoElementSerialize(ar);
	}
	else
	{
		ar << allocated;
	}
	return ar;
}
Archive& operator >>(Archive& ar, GeoElement *&e)
{
	//printf("Archive& operator >>(Archive& ar, GeoElement * e)\n");
	bool allocated = false;

	ar >> allocated;
	if (allocated)
	{
		GeoElement::type ge_type;
		ar >> ge_type;
		e = reinterpret_cast<GeoElement *> (GeoElement::operator new (sizeof(GeoElement), ge_type, 0));
		if (e) e->Object::Serialize(ar);
		if (e) e->GeoElement_Serialize(ar);
		if (e) e->GeoElementSerialize(ar);
	}
	else
	{
		e = NULL;
	}
	return ar;
}



Archive& operator <<(Archive& ar, CGround * g)
{
	bool allocated = false;

	if (g)
	{
		allocated = true;
		ar << allocated;
		ar << g->m_type;
		if (g) g->Ground_Serialize(ar);
		if (g) g->Serialize(ar);
	}
	else
	{
		ar << allocated;
	}
	return ar;
}
Archive& operator >>(Archive& ar, CGround *&g)
{
	bool allocated = false;

	ar >> allocated;
	if (allocated)
	{
		CGround::ground_type gr_type;
		ar >> gr_type;
		g = reinterpret_cast<CGround *> (CGround::operator new (sizeof(CGround), gr_type));
		if (g) g->Ground_Serialize(ar);
		if (g) g->Serialize(ar);
	}
	else
	{
		g = NULL;
	}
	return ar;
}



void GeoElement::GeoElement_Serialize(Archive& ar)
{
	//printf("GeoElement::GeoElement_Serialize(Archive& ar)\n");
	if (ar.IsStoring())
	{
		ar << m_geoelement_version;
		switch (m_geoelement_version)
		{
		case 3:
			{
				ar << id_umpoz;
			}
		case 2:
			{
				//ar << sub_elements;
				ar << my_id_key;
			}
		case 1:
			{
				ar << my_key;
				ar << my_key_read;
			}
			break;
		default:
			{
				throw VersionException(m_geoelement_version, VersionException::cannot_store, m_object_type);
			}
			break;
		}
	}
	else
	{
		ar >> m_geoelement_version;
		switch (m_geoelement_version)
		{
		case 3:
			{
				ar >> id_umpoz;
			}
		case 2:
			{
				//ar >> sub_elements;
				ar >> my_id_key;
			}
		case 1:
			{
				ar >> my_key;
				ar >> my_key_read;
				m_geoelement_version = GEOELEMENT_VERSION;
			}
			break;
		default:
			{
				throw VersionException(m_geoelement_version, VersionException::cannot_load, m_object_type);
			}
			break;
		}
	}
}


void LithoGeoElement::LithoGeoElement_Serialize(Archive& ar)
{
	//printf("LithoGeoElement::LithoGeoElement_Serialize(Archive& ar)\n");
	if (ar.IsStoring())
	{
		ar << m_litho_geoelement_version;
		switch (m_litho_geoelement_version)
		{
		case 2:
			{
				ar << lith_color;
			}
		case 1:
			{
				ar << m_ground_type;
			}
			break;
		default:
			{
				throw VersionException(m_litho_geoelement_version, VersionException::cannot_store, m_object_type);
			}
			break;
		}
	}
	else
	{
		ar >> m_litho_geoelement_version;
		switch (m_litho_geoelement_version)
		{
		case 2:
			{
				ar >> lith_color;
			}
		case 1:
			{
				ar >> m_ground_type;
				m_litho_geoelement_version = LITHO_GEO_ELEMENT_VERSION;
			}
			break;
		default:
			{
				throw VersionException(m_litho_geoelement_version, VersionException::cannot_load, m_object_type);
			}
			break;
		}
	}
}

void EngineerGeoElement::GeoElementSerialize(Archive& ar)
{
	//printf("EngineerGeoElement::GeoElementSerialize(Archive& ar)\n");
	this->LithoGeoElement::LithoGeoElement_Serialize(ar);
	if (ar.IsStoring())
	{
		DWORD version = m_object_version;

		switch (version)
		{
		case 3:
			{
			}
		case 2:
			{
				ar << WaterSaturation_Checked;
			}
		case 1:
			{
				ar << m_ground;
			}
			break;
		default:
			{
				throw VersionException(version, VersionException::cannot_store, m_object_type);
			}
			break;
		}
	}
	else
	{
		switch (m_object_version)
		{
		case 3:
			{
			}
		case 2:
			{
				ar >> WaterSaturation_Checked;
			}
		case 1:
			{
				ar >> m_ground;
				m_object_version = ENG_GEO_ELEMENT_VERSION;
			}
			break;
		default:
			{
				throw VersionException(m_object_version, VersionException::cannot_load, m_object_type);
			}
			break;
		}
	}
}





void LithoGeoElement::GeoElementSerialize(Archive& ar)
{
	printf("LithoGeoElement::GeoElementSerialize(Archive& ar)\n");
	this->LithoGeoElement::LithoGeoElement_Serialize(ar);
	if (ar.IsStoring())
	{
		DWORD version = m_object_version;

		switch (version)
		{
		case 1:
			{
			}
			break;
		default:
			{
				throw VersionException(version, VersionException::cannot_store, m_object_type);
			}
			break;
		}
	}
	else
	{
		switch (m_object_version)
		{
		case 1:
			{
			}
			break;
		default:
			{
				throw VersionException(m_object_version, VersionException::cannot_load, m_object_type);
			}
			break;
		}
	}
}


void StratigraficalGeoElement::GeoElementSerialize(Archive& ar)
{
	printf("StratigraficalGeoElement::GeoElementSerialize(Archive& ar)\n");
	if (ar.IsStoring())
	{
		DWORD version = m_object_version;

		switch (version)
		{
		case 1:
			{
			}
			break;
		default:
			{
				throw VersionException(version, VersionException::cannot_store, m_object_type);
			}
			break;
		}
	}
	else
	{
		switch (m_object_version)
		{
		case 1:
			{
			}
			break;
		default:
			{
				throw VersionException(m_object_version, VersionException::cannot_load, m_object_type);
			}
			break;
		}
	}
}



void HydroGeoElement::GeoElementSerialize(Archive& ar)
{
	printf("HydroGeoElement::GeoElementSerialize(Archive& ar)\n");
	if (ar.IsStoring())
	{
		DWORD version = m_object_version;

		switch (version)
		{
		case 1:
			{
			}
			break;
		default:
			{
				throw VersionException(version, VersionException::cannot_store, m_object_type);
			}
			break;
		}
	}
	else
	{
		switch (m_object_version)
		{
		case 1:
			{
			}
			break;
		default:
			{
				throw VersionException(m_object_version, VersionException::cannot_load, m_object_type);
			}
			break;
		}
	}
}







void LabGeoElement::GeoElementSerialize(Archive& ar)
{
	printf("LabGeoElement::GeoElementSerialize(Archive& ar)\n");
	if (ar.IsStoring())
	{
		DWORD version = m_object_version;

		switch (version)
		{
		case 1:
			{
			}
			break;
		default:
			{
				throw VersionException(version, VersionException::cannot_store, m_object_type);
			}
			break;
		}
	}
	else
	{
		switch (m_object_version)
		{
		case 1:
			{
			}
			break;
		default:
			{
				throw VersionException(m_object_version, VersionException::cannot_load, m_object_type);
			}
			break;
		}
	}
}









void FieldGeoElement::GeoElementSerialize(Archive& ar)
{
	printf("FieldGeoElement::GeoElementSerialize(Archive& ar)\n");
	if (ar.IsStoring())
	{
		DWORD version = m_object_version;

		switch (version)
		{
		case 1:
			{
			}
			break;
		default:
			{
				throw VersionException(version, VersionException::cannot_store, m_object_type);
			}
			break;
		}
	}
	else
	{
		switch (m_object_version)
		{
		case 1:
			{
			}
			break;
		default:
			{
				throw VersionException(m_object_version, VersionException::cannot_load, m_object_type);
			}
			break;
		}
	}
}


void FaultGeoElement::GeoElementSerialize(Archive& ar)
{
	printf("FaultGeoElement::GeoElementSerialize(Archive& ar)\n");
	if (ar.IsStoring())
	{
		DWORD version = m_object_version;

		switch (version)
		{
		case 1:
			{
			}
			break;
		default:
			{
				throw VersionException(version, VersionException::cannot_store, m_object_type);
			}
			break;
		}
	}
	else
	{
		switch (m_object_version)
		{
		case 1:
			{
			}
			break;
		default:
			{
				throw VersionException(m_object_version, VersionException::cannot_load, m_object_type);
			}
			break;
		}
	}
}


Archive& operator <<(Archive& ar, std::map<string, GeoElement*>& m)
{
	//printf("Archive& operator <<(Archive& ar, std::map<string, GeoElement*>& m)\n");
	ar << m.size();
	map <string, GeoElement*>::iterator m1_Iter;
	for ( m1_Iter = m.begin( ); m1_Iter != m.end( ); m1_Iter++ )
	{
		ar << m1_Iter -> first;
		ar << m1_Iter -> second;
	}
	return ar;
}
Archive& operator >>(Archive& ar, std::map<string, GeoElement*>& m)
{
//	printf("Archive& operator >>(Archive& ar, std::map<string, GeoElement*>& m)\n");
	size_t len;
	ar >> len;
	string key;
	GeoElement * val = NULL;		
	m.clear();
	for ( size_t i = 0; i < len; i++ )
	{
		ar >> key;

		cout << "key = " << key.c_str() << endl;
		ar >> val;
		m.insert( pair <string, GeoElement*>( key, val ) );
		cout << "m.size() = " << (unsigned int)m.size() << "val = " << val << endl;
	}
	return ar;
}






Archive& operator <<(Archive& ar, GeoColomn& ob)
{
printf("operator <<(Archive& ar, GeoColomn& ob))\n");

	DWORD version = ob.Object::Serialize(ar);

	switch (version)
	{
	case 1:
		{
			ar << ob.m_type;
			ar << ob.geo_elements;
		}
		break;
	default:
		{
			throw VersionException(version, VersionException::cannot_store, ob.m_object_type);
		}
		break;
	}
	return ar;
}
Archive& operator >>(Archive& ar, GeoColomn& ob)
{
//printf("operator >>(Archive& ar, GeoColomn& ob))\n");

	ob.Object::Serialize(ar);

	switch (ob.m_object_version)
	{
	case 1:
		{
			ar >> ob.m_type;
			ar >> ob.geo_elements;

			int id = 1;
			for (map<string, GeoElement*>::iterator it = ob.geo_elements.begin();
				it != ob.geo_elements.end(); it++)
			{
				if ((*it).second)
				{
					if((*it).second->my_id_key == 0)
					{
						(*it).second->my_id_key = id;
						id++;
					}					
				}
			}

		}
		break;
	default:
		{
			throw VersionException(ob.m_object_version, VersionException::cannot_load, ob.m_object_type);
		}
		break;
	}
	return ar;
}
