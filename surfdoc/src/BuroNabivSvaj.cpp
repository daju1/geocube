#include "BuroNabivSvaj.h"

//#include <iostream> 
//using namespace std;

#include "SurfDoc.h"
#include "../../wintools/src/win32_project.h"
#include "../../resource.h"

extern HINSTANCE hInst;								// current instance

const char * ZabivnSvaj::ParamTypeToString(ZabivnSvaj::ParamType param_type)
{
	switch(param_type)
	{
	case h:
		return "h, м";
	case h_from_rostverk:
		return "h_from_rostverk, м";
	case V:
		return "V svai, м3";
	case R:
		return "R, тс/м^2";
	case RA:
		return "RA, тс";
	case f_i:
		return "f_i, тс/м^2";		
	case gamma_cf:
		return "gamma_cf";
	case sum_gamma_cf_fi_hi:
		return "sum_gamma_cf_fi_hi, тс/м";
	case u_sum_gamma_cf_fi_hi:
		return "u_sum_gamma_cf_fi_hi, тс";
	case RA_plus_u_sum_gamma_cf_fi_hi:
		return "RA_plus_u_sum_gamma_cf_fi_hi, тс";
	case gamma_c:
		return "gamma_c";
	case Fd:
		return "Fd, тс";
	case Fd_per_V:
		return "Fd/V, тс/м3";
	case N:
		return "N, тс";
	case N_per_V:
		return "N/V, тс/м3";
	default:
		return "";
	}
}



const char * BuroNabivSvaj::ParamTypeToString(BuroNabivSvaj::ParamType param_type)
{
	switch(param_type)
	{
	case h:
		return "h, м";
	case h_per_d:
		return "h_per_d";
	case h_from_rostverk:
		return "h_from_rostverk, м";
	case V:
		return "V svai, м3";
	case alpha1:
		return "alpha1";
	case alpha2:
		return "alpha2";
	case alpha3:
		return "alpha3";
	case alpha4:
		return "alpha4";
	case gamma_:
		return "gamma_, kH/м3";
	case sum_gamma_h:
		return "sum_gamma_h, kH/м2";
	case R:
		return "R, тс/м^2";
	case RA:
		return "RA, тс";
	case f_i:
		return "f_i, тс/м^2";		
	case gamma_cf:
		return "gamma_cf";		
	case integral_gamma_cf_fi_hi:
		return "integral_gamma_cf_fi_hi, тс/м";
	case sum_gamma_cf_fi_hi:
		return "sum_gamma_cf_fi_hi, тс/м";
	case u_sum_gamma_cf_fi_hi:
		return "u_sum_gamma_cf_fi_hi, тс";
	case RA_plus_u_sum_gamma_cf_fi_hi:
		return "RA_plus_u_sum_gamma_cf_fi_hi, тс";
	case gamma_c:
		return "gamma_c";
	case Fd:
		return "Fd, тс";
	case Fd_per_V:
		return "Fd/V, тс/м3";
	case N:
		return "N, тс";
	case N_per_V:
		return "N/V, тс/м3";
	default:
		return "";
	}
}


const char * BuroNabivSvaj::SvaiTypeToString(BuroNabivSvaj::SvaiType svai_type, double v_custom_gamma_cf[4])
{
	switch(svai_type)
	{
	case nabivn_2_5a_pri_zabivke_inventarnoj_truby_s_nakonechnikom:
		return "1) Набивные по п.2.5а при набивке инвертарной трубы с наконечником";
	case nabivn_vibroshtampovan:
		return "2) Набивные виброштампованные";
	case burov_betonir_bez_vody_ili_s_obsadnoj_truboj:
		return "3а) Буровые бетонируемые без воды или с обсадной трубой";
	case burov_betonir_pod_vodoj_ili_pod_glin_rr:
		return "3б) Буровые бетонируемые под водой или под глинистым р-ром";
	case burov_betonir_zhestk_beton_glub_vibrac_suhim_sposobom:
		return "3в) Буров.бетонир.жёстк.бет.смесями,укл.с пом.глубин.вибр.(сух.сп.)";
	case buronabivn_polye_kruglue_bez_vody_s_vibro_serdechnik:
		return "4) Буронабивные полые круглые устр. без воды с пом. вибросердечника";
	case svai_obolochki_pogr_vibrir_s_vyemkoj_grunta:
		return "5) Сваи-оболочки, погруж. вибрир. с выемкой грунта";
	case svai_stolby:
		return "6) Сваи-стойки";
	case buroinjekcion_pod_zaschitoj_obsad_trub_ili_betonit_rr_s_opressovkoj:
		return "7) Буроинъекционные изг.под защ.обс.труб или бетонит.р-ра с опрессовкой давл 2-4 атм";
	case custom:
		{
			static string s = "custom\0";
			char str[1024];
			sprintf(str, " %1.1f %1.1f %1.1f %1.1f\0", v_custom_gamma_cf[0], v_custom_gamma_cf[1], v_custom_gamma_cf[2], v_custom_gamma_cf[3]);
			s += str;
			return s.c_str();
		}
	default:
		return "";
	}
}
const char * BuroNabivSvaj::SvaiTypeToString(BuroNabivSvaj::SvaiType svai_type)
{
	switch(svai_type)
	{
	case nabivn_2_5a_pri_zabivke_inventarnoj_truby_s_nakonechnikom:
		return "1) Набивные по п.2.5а при набивке инвертарной трубы с наконечником";
	case nabivn_vibroshtampovan:
		return "2) Набивные виброштампованные";
	case burov_betonir_bez_vody_ili_s_obsadnoj_truboj:
		return "3а) Буровые бетонируемые без воды или с обсадной трубой";
	case burov_betonir_pod_vodoj_ili_pod_glin_rr:
		return "3б) Буровые бетонируемые под водой или под глинистым р-ром";
	case burov_betonir_zhestk_beton_glub_vibrac_suhim_sposobom:
		return "3в) Буров.бетонир.жёстк.бет.смесями,укл.с пом.глубин.вибр.(сух.сп.)";
	case buronabivn_polye_kruglue_bez_vody_s_vibro_serdechnik:
		return "4) Буронабивные полые круглые устр. без воды с пом. вибросердечника";
	case svai_obolochki_pogr_vibrir_s_vyemkoj_grunta:
		return "5) Сваи-оболочки, погруж. вибрир. с выемкой грунта";
	case svai_stolby:
		return "6) Сваи-стойки";
	case buroinjekcion_pod_zaschitoj_obsad_trub_ili_betonit_rr_s_opressovkoj:
		return "7) Буроинъекционные изг.под защ.обс.труб или бетонит.р-ра с опрессовкой давл 2-4 атм";
	case custom:
		{
			static string s = "custom\0";
			return s.c_str();
		}
	default:
		return "";
	}
}

#if 0
const char * BuroNabivSvaj::SvaiTypeToString(BuroNabivSvaj::SvaiType svai_type, double v_custom_gamma_cf[4])
{
	switch(svai_type)
	{
	case nabivn_2_5a_pri_zabivke_inventarnoj_truby_s_nakonechnikom:
		return "nabivn_2_5a_pri_zabivke_inventarnoj_truby_s_nakonechnikom";
	case nabivn_vibroshtampovan:
		return "nabivn_vibroshtampovan";
	case burov_betonir_bez_vody_ili_s_obsadnoj_truboj:
		return "burov_betonir_bez_vody_ili_s_obsadnoj_truboj";
	case burov_betonir_pod_vodoj_ili_pod_glin_rr:
		return "burov_betonir_pod_vodoj_ili_pod_glin_rr";
	case burov_betonir_zhestk_beton_glub_vibrac_suhim_sposobom:
		return "burov_betonir_zhestk_beton_glub_vibrac_suhim_sposobom";
	case buronabivn_polye_kruglue_bez_vody_s_vibro_serdechnik:
		return "buronabivn_polye_kruglue_bez_vody_s_vibro_serdechnik";
	case svai_obolochki_pogr_vibrir_s_vyemkoj_grunta:
		return "svai_obolochki_pogr_vibrir_s_vyemkoj_grunta";
	case svai_stolby:
		return "svai_stolby";
	case buroinjekcion_pod_zaschitoj_obsad_trub_ili_betonit_rr_s_opressovkoj:
		return "buroinjekcion_pod_zaschitoj_obsad_trub_ili_betonit_rr_s_opressovkoj";
	case custom:
		{
			static string s = "custom\0";
			char str[1024];
			sprintf(str, " %1.1f %1.1f %1.1f %1.1f\0", v_custom_gamma_cf[0], v_custom_gamma_cf[1], v_custom_gamma_cf[2], v_custom_gamma_cf[3]);
			s += str;
			return s.c_str();
		}
	default:
		return "";
	}
}

const char * BuroNabivSvaj::SvaiTypeToString(BuroNabivSvaj::SvaiType svai_type)
{
	switch(svai_type)
	{
	case nabivn_2_5a_pri_zabivke_inventarnoj_truby_s_nakonechnikom:
		return "nabivn_2_5a_pri_zabivke_inventarnoj_truby_s_nakonechnikom";
	case nabivn_vibroshtampovan:
		return "nabivn_vibroshtampovan";
	case burov_betonir_bez_vody_ili_s_obsadnoj_truboj:
		return "burov_betonir_bez_vody_ili_s_obsadnoj_truboj";
	case burov_betonir_pod_vodoj_ili_pod_glin_rr:
		return "burov_betonir_pod_vodoj_ili_pod_glin_rr";
	case burov_betonir_zhestk_beton_glub_vibrac_suhim_sposobom:
		return "burov_betonir_zhestk_beton_glub_vibrac_suhim_sposobom";
	case buronabivn_polye_kruglue_bez_vody_s_vibro_serdechnik:
		return "buronabivn_polye_kruglue_bez_vody_s_vibro_serdechnik";
	case svai_obolochki_pogr_vibrir_s_vyemkoj_grunta:
		return "svai_obolochki_pogr_vibrir_s_vyemkoj_grunta";
	case svai_stolby:
		return "svai_stolby";
	case buroinjekcion_pod_zaschitoj_obsad_trub_ili_betonit_rr_s_opressovkoj:
		return "buroinjekcion_pod_zaschitoj_obsad_trub_ili_betonit_rr_s_opressovkoj";
	case custom:
		{
			static string s = "custom\0";
			return s.c_str();
		}
	default:
		return "";
	}
}

#endif
WNDPROC wpOrigWaterSaturationTabWndProc2; 

// Subclass procedure 
LRESULT APIENTRY WaterSaturationTabWndSubclassProc2(
    HWND hwnd, 
    UINT uMsg, 
    WPARAM wParam, 
    LPARAM lParam) 
{ 
	static BuroNabivSvaj * me;
	static HWND hwndWaterSaturationList   = NULL;
//	int wmId, wmEvent;

    if (uMsg == WM_GETDLGCODE) 
	{
        return DLGC_WANTALLKEYS ;  // 0x0004      // Control wants all keys - All keyboard input     
	} 
	switch (uMsg) 
	{
		case WM_INITDIALOG :
			{
				PROPSHEETPAGE *lPage = (PROPSHEETPAGE*)lParam;
				me = (BuroNabivSvaj *)lPage->lParam;
				//**************************************
				// #############################################################
				// #############################################################
				if (me->pSurfDoc)
				{
					 if (me->pSurfDoc->m_WaterSaturationListViewTab.Init(hwnd, (LPVOID)me->pSurfDoc, 0.0, 0.0, 0.0, 0.0))
					 {
						 hwndWaterSaturationList = me->pSurfDoc->m_WaterSaturationListViewTab.GetWnd();
#if USE_LISTVIEW_STANDART_WSL 
						 me->pSurfDoc->m_WaterSaturationListViewTab.SetCols(2);
#else
						 me->pSurfDoc->m_WaterSaturationListViewTab.SetCols(3);
#endif
						 						
						me->pSurfDoc->m_WaterSaturationListViewTab.SetHeaderString(0, "степень влажности");
						me->pSurfDoc->m_WaterSaturationListViewTab.SetHeaderString(1, "ИГЭ");
						GeoColomn * colomn = me->pSurfDoc->FindGeoColomn(GeoElement::type::engineer_geological);
						if (colomn) 
						{
							for (map<string, GeoElement*>::iterator it = colomn->geo_elements.begin(); it != colomn->geo_elements.end(); it++)
							{		
								if (it->second)
								{
									GeoElement::type t = it->second->m_type;
									
									if (t != colomn->m_type)
									{
										printf("warning: element type  = \"%s\" (%d) not eqial colomn type = \"%s\"(%d)\n",
											GeoElement::GeoElementTypeToString(t), int(t),
											GeoElement::GeoElementTypeToString(colomn->m_type), int(colomn->m_type)
											);
									}

									char str[1024];


									GeoElement * geo = it->second;
									EngineerGeoElement * eng = dynamic_cast<EngineerGeoElement *>(geo);
									if (eng)
									{
										me->pSurfDoc->m_WaterSaturationListViewTab.AddRow(LPARAM(0), &eng->WaterSaturation_Checked);
										size_t r = me->pSurfDoc->m_WaterSaturationListViewTab.Rows()-1;
										
										sprintf(str, "ИГЭ-%s\0", eng->GetKey().c_str());
										me->pSurfDoc->m_WaterSaturationListViewTab.SetItemString(r, 1, str);

										double v;
										if(eng->GetValue(EngineerGeoElement::ValueType::degree_of_moisture,
											EngineerGeoElement::GroundDescriptionType::normative,
											EngineerGeoElement::StrengthDescriptionType::simple, 
											v))
										{
											sprintf(str, "%f\0", v);
											me->pSurfDoc->m_WaterSaturationListViewTab.SetItemString(r, 0, str);
										}
									}
								}
							}
						}
					 }
				}				 

				// #############################################################
				// #############################################################
			}
			break;

#if !USE_LISTVIEW_STANDART_WSL 
		case WM_USER + 3:
			{
				if (me->pSurfDoc)
				{
					me->pSurfDoc->m_WaterSaturationListViewTab.OnEndEdit();
					//me->pSurfDoc->UpdateLayersNames();
					//me->pSurfDoc->UpdateKarotazhNames();
					me->pSurfDoc->UpdateWaterSaturation();
				}
			}
			break; 
#endif

        case WM_MEASUREITEM: 
			{
				LPMEASUREITEMSTRUCT lpmis = (LPMEASUREITEMSTRUCT) lParam; 
				// Set the height of the list box items. 
				lpmis->itemHeight = YBITMAP3; 	/// А здесь сработало!!!!!!!!!			
				lpmis->itemWidth = 100; 				

				return TRUE; 
			}
			break;
#if !USE_LISTVIEW_STANDART_WSL 
        case WM_DRAWITEM: 
			{	
				LPDRAWITEMSTRUCT lpdis = (LPDRAWITEMSTRUCT) lParam; 				
				// If there are no list box items, skip this message. 
				if (lpdis->itemID == -1) 
				{ 
					break; 
				} 
				if (lpdis->hwndItem == hwndWaterSaturationList)
				{
					//LONG_PTR userdata = GetWindowLongPtr(hWnd,GWLP_USERDATA);
					//win_project* pwin_project = (win_project*)userdata;
					if (me->pSurfDoc)
					{
						me->pSurfDoc->m_WaterSaturationListViewTab.OnDrawItem(lpdis);
					}
				}
			}
			break;
#endif
		case WM_NOTIFY:
			{
				if (((LPNMHDR) lParam)->hwndFrom == hwndWaterSaturationList)
				{
					win_project* pwin_project = dynamic_cast<win_project*>(me->pSurfDoc);
					if (pwin_project)
					{
						pwin_project->m_WaterSaturationListViewTab.OnNotify(lParam);
						//pwin_project->UpdateAllViews();
#if USE_LISTVIEW_STANDART_WSL 
						if (((LPNMHDR) lParam)->code == LVN_ENDLABELEDIT)
							pwin_project->UpdateWaterSaturation();

#endif
					}
/*					if (
						((LPNMHDR) lParam)->code == NM_CLICK
						||
						((LPNMHDR) lParam)->code == NM_DBLCLK
						)
					{
						RECT rect;
						GetClientRect(hSurfWnd,&rect);
						InvalidateRect(hSurfWnd,&rect, true);
					}*/
				}
			}
			break;
		case WM_CLOSE:
			{
				return DefWindowProc(hwnd, uMsg, wParam, lParam);
			}
			break;
   }
   return CallWindowProc(wpOrigWaterSaturationTabWndProc2, hwnd, uMsg, 
	   wParam, lParam); 
} 
BOOL CALLBACK BuroNabivSvaj::DlgProcAdditionals( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static BuroNabivSvaj * me;
	switch( uMsg )
	{
    case WM_INITDIALOG :
		{	
			PROPSHEETPAGE *lPage = (PROPSHEETPAGE*)lParam;
			me = (BuroNabivSvaj *)lPage->lParam;


		
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			CheckDlgButton( hDlg, IDC_CHECK_DECREASE_CLAY_R_IF_POROSTY,
				me->decrease_clay_R_if_porosty ? BST_CHECKED : BST_UNCHECKED );
			CheckDlgButton( hDlg, IDC_CHECK_INCREASE_FI_IF_DENSE_SAND,
				me->increase_fi_if_dense_sand ? BST_CHECKED : BST_UNCHECKED );
			CheckDlgButton( hDlg, IDC_CHECK_INCREASE_FI_IF_NOT_POROSTY_CLAY,
				me->increase_fi_if_not_porosty_clay ? BST_CHECKED : BST_UNCHECKED );			
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		}
		break;
	case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{
		case IDC_CHECK_DECREASE_CLAY_R_IF_POROSTY:
			{
				me->decrease_clay_R_if_porosty = IsDlgButtonChecked( hDlg, IDC_CHECK_DECREASE_CLAY_R_IF_POROSTY) == BST_CHECKED;
				//PropSheet_Changed(::GetParent(hDlg),hDlg);
			}
			break;
		case IDC_CHECK_INCREASE_FI_IF_DENSE_SAND:
			{
				me->increase_fi_if_dense_sand = IsDlgButtonChecked( hDlg, IDC_CHECK_INCREASE_FI_IF_DENSE_SAND) == BST_CHECKED;
				//PropSheet_Changed(::GetParent(hDlg),hDlg);
			}
			break;
		case IDC_CHECK_INCREASE_FI_IF_NOT_POROSTY_CLAY:
			{
				me->increase_fi_if_not_porosty_clay = IsDlgButtonChecked( hDlg, IDC_CHECK_INCREASE_FI_IF_NOT_POROSTY_CLAY) == BST_CHECKED;
				//PropSheet_Changed(::GetParent(hDlg),hDlg);
			}
			break;
		}
		break;	
	case WM_NOTIFY:
		{
			if (((LPNMHDR) lParam)->hwndFrom == ::GetParent(hDlg))
			{
				switch (((LPNMHDR) lParam)->code)
				{
				case PSN_SETACTIVE:
					{
						//printf("PSN_SETACTIVE\n");
					}
					break;
				case PSN_KILLACTIVE:
					{
						//printf("PSN_KILLACTIVE\n");
					}
					break;
				case PSN_APPLY:
					{
						//me->Apply();
						//printf("PSN_APPLY\n");
						//me->ReDraw();
						//====== Перерисовываем Вид с учетом изменений
						//RECT rect;
						//GetClientRect(me->m_pSurfDoc->hSurfWnd,&rect);
						//InvalidateRect(me->m_pSurfDoc->hSurfWnd,&rect, true);
					}
					break;
				case PSN_RESET:
					{
						//printf("PSN_RESET\n");
					}
					break;
				case PSN_HELP:
					{
						//printf("PSN_HELP\n");
					}
					break;
				case PSN_WIZBACK:
					{
						//printf("PSN_WIZBACK\n");
					}
					break;
				case PSN_WIZNEXT:
					{
						//printf("PSN_WIZNEXT\n");
					}
					break;
				case PSN_WIZFINISH:
					{
						//printf("PSN_WIZFINISH\n");
					}
					break;
				case PSN_QUERYCANCEL:
					{
						//printf("PSN_QUERYCANCEL\n");
						DestroyWindow(::GetParent(hDlg));
					}
					break;
				case PSN_GETOBJECT:
					{
						//printf("PSN_GETOBJECT\n");
					}
					break;
				case (PSN_FIRST-11):
					{
						//printf("(PSN_FIRST-11)\n");
						//DestroyWindow(::GetParent(hDlg));
					}
					break;
				case PSN_TRANSLATEACCELERATOR:
					{
						//printf("PSN_TRANSLATEACCELERATOR\n");
					}
					break;
				case PSN_QUERYINITIALFOCUS:
					{
						//printf("PSN_QUERYINITIALFOCUS\n");
					}
					break;
				default:
					{
						//printf("((LPNMHDR) lParam)->code %x\n", ((LPNMHDR) lParam)->code);
					}
					break;
				}
			}
		}
		break;
	default :	
		return( FALSE );
	}
	return( TRUE );
}

BOOL CALLBACK BuroNabivSvaj::DlgProcSvaiBuroNabivnie( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static BuroNabivSvaj * me;
	static char str [1024];

	static HWND hWndWaterSaturationTab;	
		
	switch( uMsg )
	{
    case WM_INITDIALOG :
		{
			PROPSHEETPAGE *lPage = (PROPSHEETPAGE*)lParam;
			me = (BuroNabivSvaj *)lPage->lParam;

			me->decrease_clay_R_if_porosty = true;
			me->increase_fi_if_dense_sand = true;
			me->increase_fi_if_not_porosty_clay = true;


			me->index_cub_internal_friction_angle = -1;
			me->index_cub_specific_gravity_of_ground = -1;
			me->index_surface_of_relief = -1;
			me->index_surface_of_rostverk = -1;
			me->index_cub_fluidity_index = -1;
			me->index_buro_nabiv_svaj_param_type = -1;
			me->index_buro_nabiv_svaj_svai_type = -1;

			me->use_rostverk_altituda = false;

			me->use_water_saturation = false;
			me->index_cub_specific_gravity_of_suspended_in_water_ground = -1;
			me->index_cub_fluidity_index_of_water_saturated_ground = -1;

			me->use_cub_specific_gravity_of_ground = false;
			me->use_cub_fluidity_index = false;

			//me->d = 0.8;
			//me->gamma_k = 1.4;


			SetDlgItemText(hDlg, IDC_EDIT_D, "0.8\0");
			SetDlgItemText(hDlg, IDC_EDIT_GAMMA_K, "1.4\0");
			
			CheckRadioButton( hDlg,
				IDC_RADIO_SVAI_TYPE_ZABIVNYE,
				IDC_RADIO_SVAI_TYPE_4,
				IDC_RADIO_SVAI_TYPE_BUROVYE);

			me->s_buro_nabiv_svaj_param_type = BuroNabivSvaj::ParamType::none;
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_BURO_NABIV_SVAJ_SVAI_TYPE, CB_RESETCONTENT,0,0);
			SendDlgItemMessage( hDlg, IDC_COMBO_BURO_NABIV_SVAJ_SVAI_TYPE, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"Select svai type");

			for( BuroNabivSvaj::SvaiType svai_type = BuroNabivSvaj::SvaiType(BuroNabivSvaj::SvaiType::undefined + 1); 
				svai_type < BuroNabivSvaj::SvaiType::last;
				svai_type++ )
			{
					SendDlgItemMessage( hDlg, IDC_COMBO_BURO_NABIV_SVAJ_SVAI_TYPE, CB_ADDSTRING, 0,
						(LPARAM)(LPCTSTR)BuroNabivSvaj::SvaiTypeToString(svai_type));
			}
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_BURO_NABIV_SVAJ_SVAI_TYPE, CB_SETCURSEL,
				me->index_buro_nabiv_svaj_svai_type+1, (LPARAM)0 );
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			me->s_buro_nabiv_svaj_svai_type = BuroNabivSvaj::SvaiType::undefined;
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_BURO_NABIV_SVAJ_PARAM, CB_RESETCONTENT,0,0);
			SendDlgItemMessage( hDlg, IDC_COMBO_BURO_NABIV_SVAJ_PARAM, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"Select result");

			for( BuroNabivSvaj::ParamType param_type = BuroNabivSvaj::ParamType(BuroNabivSvaj::ParamType::none + 1); 
				param_type < BuroNabivSvaj::ParamType::end;
				param_type++ )
			{
					SendDlgItemMessage( hDlg, IDC_COMBO_BURO_NABIV_SVAJ_PARAM, CB_ADDSTRING, 0,
						(LPARAM)(LPCTSTR)BuroNabivSvaj::ParamTypeToString(param_type));
			}
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_BURO_NABIV_SVAJ_PARAM, CB_SETCURSEL,
				me->index_buro_nabiv_svaj_param_type+1, (LPARAM)0 );
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_INTERNAL_FRICTION_ANGLE, CB_RESETCONTENT,0,0);
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_INTERNAL_FRICTION_ANGLE, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"Select int fric angle cube");
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			if (me->pSurfDoc->m_cubes.SetCurrentMsgOnFirst())
			{
				do
				{
					SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_INTERNAL_FRICTION_ANGLE, CB_ADDSTRING, 0,
						(LPARAM)(LPCTSTR)me->pSurfDoc->m_cubes.GetCurrentMsg().GetName().c_str());
				}
				while (me->pSurfDoc->m_cubes.IncrementCurrentMsg());
			}
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_INTERNAL_FRICTION_ANGLE, CB_SETCURSEL,
				me->index_cub_internal_friction_angle+1, (LPARAM)0 );
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

			
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_SPECIFIC_GRAVITY_OF_GROUND, CB_RESETCONTENT,0,0);
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_SPECIFIC_GRAVITY_OF_GROUND, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"Select spec grav of ground cube");
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			if (me->pSurfDoc->m_cubes.SetCurrentMsgOnFirst())
			{
				do
				{
					SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_SPECIFIC_GRAVITY_OF_GROUND, CB_ADDSTRING, 0,
						(LPARAM)(LPCTSTR)me->pSurfDoc->m_cubes.GetCurrentMsg().GetName().c_str());
				}
				while (me->pSurfDoc->m_cubes.IncrementCurrentMsg());
			}
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_SPECIFIC_GRAVITY_OF_GROUND, CB_SETCURSEL,
				me->index_cub_specific_gravity_of_ground+1, (LPARAM)0 );
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

			
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_SURFACE_RELIEF, CB_RESETCONTENT,0,0);
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_SURFACE_RELIEF, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"Select surface of relief");
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

			if (me->pSurfDoc->m_surfaces.SetCurrentMsgOnFirst())
			{
				do
				{
					SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_SURFACE_RELIEF, CB_ADDSTRING, 0,
						(LPARAM)(LPCTSTR)me->pSurfDoc->m_surfaces.GetCurrentMsg().GetName().c_str());
				}
				while (me->pSurfDoc->m_surfaces.IncrementCurrentMsg());
			}
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_SURFACE_RELIEF, CB_SETCURSEL,
				me->index_surface_of_relief+1, (LPARAM)0 );
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

			
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_SURFACE_ROSTVERK, CB_RESETCONTENT,0,0);
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_SURFACE_ROSTVERK, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"Select surface of rostverk");
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

			if (me->pSurfDoc->m_surfaces.SetCurrentMsgOnFirst())
			{
				do
				{
					SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_SURFACE_ROSTVERK, CB_ADDSTRING, 0,
						(LPARAM)(LPCTSTR)me->pSurfDoc->m_surfaces.GetCurrentMsg().GetName().c_str());
				}
				while (me->pSurfDoc->m_surfaces.IncrementCurrentMsg());
			}
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_SURFACE_ROSTVERK, CB_SETCURSEL,
				me->index_surface_of_rostverk+1, (LPARAM)0 );
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@	

			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_FLUIDITY_INDEX, CB_RESETCONTENT,0,0);
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_FLUIDITY_INDEX, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"Select fluidity index cube");
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			if (me->pSurfDoc->m_cubes.SetCurrentMsgOnFirst())
			{
				do
				{
					SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_FLUIDITY_INDEX, CB_ADDSTRING, 0,
						(LPARAM)(LPCTSTR)me->pSurfDoc->m_cubes.GetCurrentMsg().GetName().c_str());
				}
				while (me->pSurfDoc->m_cubes.IncrementCurrentMsg());
			}
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_FLUIDITY_INDEX, CB_SETCURSEL,
				me->index_cub_fluidity_index+1, (LPARAM)0 );
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				

			CheckDlgButton(hDlg, IDC_CHECK_ROSTVERK_ALTITUDA,	me->use_rostverk_altituda);
			EnableWindow(GetDlgItem(hDlg, IDC_COMBO_SELECT_SURFACE_ROSTVERK), !me->use_rostverk_altituda );
			EnableWindow(GetDlgItem(hDlg,IDC_EDIT_ROSTVERK_ALTITUDA), me->use_rostverk_altituda );



			// Retrieve the handle to the Map control. 
			hWndWaterSaturationTab = GetDlgItem(hDlg, IDC_STATIC_WATER_SATURATION_TAB); 

			// Subclass the picture control. 
			wpOrigWaterSaturationTabWndProc2 = (WNDPROC) SetWindowLongPtr(hWndWaterSaturationTab, 
				GWLP_WNDPROC, (LONG_PTR) WaterSaturationTabWndSubclassProc2); 

			SendMessage(hWndWaterSaturationTab, WM_INITDIALOG, wParam, lParam);

			CheckDlgButton(hDlg, IDC_CHECK_USE_WATER_SATURATION,	me->use_water_saturation);
			ShowWindow(GetDlgItem(hDlg,IDC_STATIC_WATER_SATURATION), me->use_water_saturation);
			ShowWindow(GetDlgItem(hDlg,IDC_STATIC_WATER_SATURATION_TAB), me->use_water_saturation);
			ShowWindow(GetDlgItem(hDlg,IDC_STATIC_USE_WATER_SATURATION), me->use_water_saturation);

			
			
			ShowWindow(GetDlgItem(hDlg,IDC_STATIC_SPECIFIC_GRAVITY_OF_SUSPENDED_IN_WATER_GROUND), me->use_water_saturation);
			ShowWindow(GetDlgItem(hDlg,IDC_COMBO_SELECT_CUBE_SPECIFIC_GRAVITY_OF_SUSPENDED_IN_WATER_GROUND), me->use_water_saturation);
			
			ShowWindow(GetDlgItem(hDlg,IDC_STATIC_FLUIDITY_INDEX_OF_WATER_SATURATED_GROUND), me->use_water_saturation);
			ShowWindow(GetDlgItem(hDlg,IDC_COMBO_SELECT_CUBE_FLUIDITY_INDEX_OF_WATER_SATURATED_GROUND), me->use_water_saturation);
			
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_SPECIFIC_GRAVITY_OF_SUSPENDED_IN_WATER_GROUND, CB_RESETCONTENT,0,0);
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_SPECIFIC_GRAVITY_OF_SUSPENDED_IN_WATER_GROUND, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"Select spec grav of susp in wat ground cube");
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			if (me->pSurfDoc->m_cubes.SetCurrentMsgOnFirst())
			{
				do
				{
					SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_SPECIFIC_GRAVITY_OF_SUSPENDED_IN_WATER_GROUND, CB_ADDSTRING, 0,
						(LPARAM)(LPCTSTR)me->pSurfDoc->m_cubes.GetCurrentMsg().GetName().c_str());
				}
				while (me->pSurfDoc->m_cubes.IncrementCurrentMsg());
			}
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_SPECIFIC_GRAVITY_OF_SUSPENDED_IN_WATER_GROUND, CB_SETCURSEL,
				me->index_cub_specific_gravity_of_suspended_in_water_ground+1, (LPARAM)0 );
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_FLUIDITY_INDEX_OF_WATER_SATURATED_GROUND, CB_RESETCONTENT,0,0);
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_FLUIDITY_INDEX_OF_WATER_SATURATED_GROUND, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"Select fluidity index of wat sat ground cube");
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			if (me->pSurfDoc->m_cubes.SetCurrentMsgOnFirst())
			{
				do
				{
					SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_FLUIDITY_INDEX_OF_WATER_SATURATED_GROUND, CB_ADDSTRING, 0,
						(LPARAM)(LPCTSTR)me->pSurfDoc->m_cubes.GetCurrentMsg().GetName().c_str());
				}
				while (me->pSurfDoc->m_cubes.IncrementCurrentMsg());
			}
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_FLUIDITY_INDEX_OF_WATER_SATURATED_GROUND, CB_SETCURSEL,
				me->index_cub_fluidity_index_of_water_saturated_ground+1, (LPARAM)0 );
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

			CheckDlgButton(hDlg, IDC_CHECK_SELECT_CUBE_SPECIFIC_GRAVITY_OF_GROUND,	me->use_cub_specific_gravity_of_ground);
			CheckDlgButton(hDlg, IDC_CHECK_SELECT_CUBE_FLUIDITY_INDEX,	me->use_cub_fluidity_index);
			
			ShowWindow(GetDlgItem(hDlg,IDC_COMBO_SELECT_CUBE_SPECIFIC_GRAVITY_OF_GROUND), me->use_cub_specific_gravity_of_ground);
			ShowWindow(GetDlgItem(hDlg,IDC_COMBO_SELECT_CUBE_FLUIDITY_INDEX), me->use_cub_fluidity_index);
			ShowWindow(GetDlgItem(hDlg,IDC_COMBO_SELECT_CUBE_SPECIFIC_GRAVITY_OF_SUSPENDED_IN_WATER_GROUND), me->use_cub_specific_gravity_of_ground);
			ShowWindow(GetDlgItem(hDlg,IDC_COMBO_SELECT_CUBE_FLUIDITY_INDEX_OF_WATER_SATURATED_GROUND), me->use_cub_fluidity_index);

			ShowWindow(GetDlgItem(hDlg,IDOK), false);
			ShowWindow(GetDlgItem(hDlg,IDCANCEL), false);

			SetDlgItemText(hDlg, IDC_EDIT_SAND_GAMMA_CF, "0.7\0");
			SetDlgItemText(hDlg, IDC_EDIT_SANDY_LOAM_GAMMA_CF, "0.7\0");
			SetDlgItemText(hDlg, IDC_EDIT_LOAM_GAMMA_CF, "0.7\0");
			SetDlgItemText(hDlg, IDC_EDIT_CLAY_GAMMA_CF, "0.7\0");

			ShowWindow(GetDlgItem(hDlg,IDC_EDIT_SAND_GAMMA_CF), false);
			ShowWindow(GetDlgItem(hDlg,IDC_EDIT_SANDY_LOAM_GAMMA_CF), false);
			ShowWindow(GetDlgItem(hDlg,IDC_EDIT_LOAM_GAMMA_CF), false);
			ShowWindow(GetDlgItem(hDlg,IDC_EDIT_CLAY_GAMMA_CF), false);	

				
		}
		break;
	case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{				
		case IDC_RADIO_SVAI_TYPE_ZABIVNYE:
			{
			}
			break;
		case IDC_RADIO_SVAI_TYPE_BUROVYE:
			{
			}
			break;
		case IDC_CHECK_SELECT_CUBE_SPECIFIC_GRAVITY_OF_GROUND:
			{
				me->use_cub_specific_gravity_of_ground = IsDlgButtonChecked( hDlg, 
					IDC_CHECK_SELECT_CUBE_SPECIFIC_GRAVITY_OF_GROUND) == BST_CHECKED;
				ShowWindow(GetDlgItem(hDlg,IDC_COMBO_SELECT_CUBE_SPECIFIC_GRAVITY_OF_GROUND), me->use_cub_specific_gravity_of_ground);
				ShowWindow(GetDlgItem(hDlg,IDC_COMBO_SELECT_CUBE_SPECIFIC_GRAVITY_OF_SUSPENDED_IN_WATER_GROUND), me->use_water_saturation && me->use_cub_specific_gravity_of_ground);
				if (me->EnableApply()) PropSheet_Changed(::GetParent(hDlg),hDlg);
			}
			break;
		case IDC_CHECK_SELECT_CUBE_FLUIDITY_INDEX:
			{
				me->use_cub_fluidity_index = IsDlgButtonChecked( hDlg, 
					IDC_CHECK_SELECT_CUBE_FLUIDITY_INDEX) == BST_CHECKED;
				ShowWindow(GetDlgItem(hDlg,IDC_COMBO_SELECT_CUBE_FLUIDITY_INDEX), me->use_cub_fluidity_index);
				ShowWindow(GetDlgItem(hDlg,IDC_COMBO_SELECT_CUBE_FLUIDITY_INDEX_OF_WATER_SATURATED_GROUND), me->use_water_saturation && me->use_cub_fluidity_index);
				if (me->EnableApply()) PropSheet_Changed(::GetParent(hDlg),hDlg);
			}
			break;


		case IDC_CHECK_USE_WATER_SATURATION:
			{
				me->use_water_saturation = IsDlgButtonChecked( hDlg, 
					IDC_CHECK_USE_WATER_SATURATION) == BST_CHECKED;

				ShowWindow(GetDlgItem(hDlg,IDC_STATIC_WATER_SATURATION), me->use_water_saturation);
				ShowWindow(GetDlgItem(hDlg,IDC_STATIC_WATER_SATURATION_TAB), me->use_water_saturation);
				ShowWindow(GetDlgItem(hDlg,IDC_STATIC_USE_WATER_SATURATION), me->use_water_saturation);
				ShowWindow(GetDlgItem(hDlg,IDC_STATIC_SPECIFIC_GRAVITY_OF_SUSPENDED_IN_WATER_GROUND), me->use_water_saturation);
				ShowWindow(GetDlgItem(hDlg,IDC_COMBO_SELECT_CUBE_SPECIFIC_GRAVITY_OF_SUSPENDED_IN_WATER_GROUND), me->use_water_saturation && me->use_cub_specific_gravity_of_ground);
				ShowWindow(GetDlgItem(hDlg,IDC_STATIC_FLUIDITY_INDEX_OF_WATER_SATURATED_GROUND), me->use_water_saturation);
				ShowWindow(GetDlgItem(hDlg,IDC_COMBO_SELECT_CUBE_FLUIDITY_INDEX_OF_WATER_SATURATED_GROUND), me->use_water_saturation && me->use_cub_fluidity_index);
				if (me->EnableApply()) PropSheet_Changed(::GetParent(hDlg),hDlg);
			}
			break;
		case IDC_CHECK_ROSTVERK_ALTITUDA:
			{
				me->use_rostverk_altituda = IsDlgButtonChecked( hDlg, 
					IDC_CHECK_ROSTVERK_ALTITUDA) == BST_CHECKED;

				EnableWindow(GetDlgItem(hDlg, IDC_COMBO_SELECT_SURFACE_ROSTVERK), !me->use_rostverk_altituda );
				EnableWindow(GetDlgItem(hDlg,IDC_EDIT_ROSTVERK_ALTITUDA), me->use_rostverk_altituda );
				if (me->EnableApply()) PropSheet_Changed(::GetParent(hDlg),hDlg);
			}
			break;
		case IDC_COMBO_BURO_NABIV_SVAJ_PARAM:
			{
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				me->index_buro_nabiv_svaj_param_type = -1 + (int)SendDlgItemMessage( hDlg, IDC_COMBO_BURO_NABIV_SVAJ_PARAM, CB_GETCURSEL,
							0,(LPARAM)0 );
				if (me->index_buro_nabiv_svaj_param_type > -1)
				{
					me->s_buro_nabiv_svaj_param_type = 
						(BuroNabivSvaj::ParamType) (me->index_buro_nabiv_svaj_param_type+1);
				}
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@	
				if (me->EnableApply()) PropSheet_Changed(::GetParent(hDlg),hDlg);
			}
			break;
		case IDC_COMBO_BURO_NABIV_SVAJ_SVAI_TYPE:
			{
				if (HIWORD(wParam) == CBN_SELCHANGE)
				{
					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					me->index_buro_nabiv_svaj_svai_type = -1 + (int)SendDlgItemMessage( hDlg, IDC_COMBO_BURO_NABIV_SVAJ_SVAI_TYPE, CB_GETCURSEL,
								0,(LPARAM)0 );
					if (me->index_buro_nabiv_svaj_svai_type > -1)
					{
						me->s_buro_nabiv_svaj_svai_type = 
							(BuroNabivSvaj::SvaiType) (me->index_buro_nabiv_svaj_svai_type+1);

						if (me->s_buro_nabiv_svaj_svai_type != BuroNabivSvaj::SvaiType::custom)
						{
							ShowWindow(GetDlgItem(hDlg,IDC_EDIT_SAND_GAMMA_CF), false);
							ShowWindow(GetDlgItem(hDlg,IDC_EDIT_SANDY_LOAM_GAMMA_CF), false);
							ShowWindow(GetDlgItem(hDlg,IDC_EDIT_LOAM_GAMMA_CF), false);
							ShowWindow(GetDlgItem(hDlg,IDC_EDIT_CLAY_GAMMA_CF), false);	
							ShowWindow(GetDlgItem(hDlg,IDC_STATIC_GAMMA_CF), true);	

							string s = "";
							char str[512];

							for( CGround::ground_type gt = CGround::ground_type::Sand; 
								gt <= CGround::ground_type::Clay;
								gt++ )
							{
								double gamma_cf;
								if (GetGammaCF(me->s_buro_nabiv_svaj_svai_type, me->v_custom_gamma_cf, gt, gamma_cf))
								{
									sprintf(str, "%1.2f                    \0", gamma_cf);
									s += str;
								}
									
							}	
							SetDlgItemText(hDlg, IDC_STATIC_GAMMA_CF, s.c_str());
						}
						else
						{
							ShowWindow(GetDlgItem(hDlg,IDC_EDIT_SAND_GAMMA_CF), true);
							ShowWindow(GetDlgItem(hDlg,IDC_EDIT_SANDY_LOAM_GAMMA_CF), true);
							ShowWindow(GetDlgItem(hDlg,IDC_EDIT_LOAM_GAMMA_CF), true);
							ShowWindow(GetDlgItem(hDlg,IDC_EDIT_CLAY_GAMMA_CF), true);	
							ShowWindow(GetDlgItem(hDlg,IDC_STATIC_GAMMA_CF), false);	
						}

					}
					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@			
				}
				if (me->EnableApply()) PropSheet_Changed(::GetParent(hDlg),hDlg);
			}
			break;
		case IDC_EDIT_SAND_GAMMA_CF:
			{
				if (HIWORD( wParam ) == EN_CHANGE)
				{
					GetDlgItemText(hDlg, IDC_EDIT_SAND_GAMMA_CF, str, 1023);
					if (strlen(str) && ISNUM(str))
					{
						me->v_custom_gamma_cf[0] = atof(str);
						if (me->EnableApply()) PropSheet_Changed(::GetParent(hDlg),hDlg);
					}
				}
			}
			break;
		case IDC_EDIT_SANDY_LOAM_GAMMA_CF:
			{
				if (HIWORD( wParam ) == EN_CHANGE)
				{
					GetDlgItemText(hDlg, IDC_EDIT_SANDY_LOAM_GAMMA_CF, str, 1023);
					if (strlen(str) && ISNUM(str))
					{
						me->v_custom_gamma_cf[1] = atof(str);
						if (me->EnableApply()) PropSheet_Changed(::GetParent(hDlg),hDlg);
					}
				}
			}
			break;
		case IDC_EDIT_LOAM_GAMMA_CF:
			{
				if (HIWORD( wParam ) == EN_CHANGE)
				{
					GetDlgItemText(hDlg, IDC_EDIT_LOAM_GAMMA_CF, str, 1023);
					if (strlen(str) && ISNUM(str))
					{
						me->v_custom_gamma_cf[2] = atof(str);
						if (me->EnableApply()) PropSheet_Changed(::GetParent(hDlg),hDlg);
					}
				}
			}
			break;
		case IDC_EDIT_CLAY_GAMMA_CF:
			{
				if (HIWORD( wParam ) == EN_CHANGE)
				{
					GetDlgItemText(hDlg, IDC_EDIT_CLAY_GAMMA_CF, str, 1023);
					if (strlen(str) && ISNUM(str))
					{
						me->v_custom_gamma_cf[3] = atof(str);
						if (me->EnableApply()) PropSheet_Changed(::GetParent(hDlg),hDlg);
					}
				}
			}
			break;
		case IDC_COMBO_SELECT_CUBE_FLUIDITY_INDEX:
			{
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				me->index_cub_fluidity_index = -1 + (int)SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_FLUIDITY_INDEX, CB_GETCURSEL,
							0,(LPARAM)0 );
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@		
				if (me->EnableApply()) PropSheet_Changed(::GetParent(hDlg),hDlg);
			}
			break;
		case IDC_COMBO_SELECT_CUBE_FLUIDITY_INDEX_OF_WATER_SATURATED_GROUND:
			{
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				me->index_cub_fluidity_index_of_water_saturated_ground = -1 + (int)SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_FLUIDITY_INDEX_OF_WATER_SATURATED_GROUND, CB_GETCURSEL,
							0,(LPARAM)0 );
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@	
				if (me->EnableApply()) PropSheet_Changed(::GetParent(hDlg),hDlg);
			}
			break;
		case IDC_COMBO_SELECT_SURFACE_RELIEF:
			{
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				me->index_surface_of_relief = -1 + (int)SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_SURFACE_RELIEF, CB_GETCURSEL,
							0,(LPARAM)0 );
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@		
				if (me->EnableApply()) PropSheet_Changed(::GetParent(hDlg),hDlg);
			}
			break;		
		case IDC_COMBO_SELECT_SURFACE_ROSTVERK:
			{
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				me->index_surface_of_rostverk = -1 + (int)SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_SURFACE_ROSTVERK, CB_GETCURSEL,
							0,(LPARAM)0 );
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@	
				if (me->EnableApply()) PropSheet_Changed(::GetParent(hDlg),hDlg);
			}
			break;
		case IDC_COMBO_SELECT_CUBE_SPECIFIC_GRAVITY_OF_GROUND:
			{
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				me->index_cub_specific_gravity_of_ground = -1 + (int)SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_SPECIFIC_GRAVITY_OF_GROUND, CB_GETCURSEL,
							0,(LPARAM)0 );
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@	
				if (me->EnableApply()) PropSheet_Changed(::GetParent(hDlg),hDlg);
			}
			break;
		case IDC_COMBO_SELECT_CUBE_SPECIFIC_GRAVITY_OF_SUSPENDED_IN_WATER_GROUND:
			{
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				me->index_cub_specific_gravity_of_suspended_in_water_ground = -1 + (int)SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_SPECIFIC_GRAVITY_OF_SUSPENDED_IN_WATER_GROUND, CB_GETCURSEL,
							0,(LPARAM)0 );
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@		
				if (me->EnableApply()) PropSheet_Changed(::GetParent(hDlg),hDlg);
			}
			break;
		case IDC_COMBO_SELECT_CUBE_INTERNAL_FRICTION_ANGLE:
			{
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				me->index_cub_internal_friction_angle = -1 + (int)SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_INTERNAL_FRICTION_ANGLE, CB_GETCURSEL,
							0,(LPARAM)0 );
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@	
				if (me->EnableApply()) PropSheet_Changed(::GetParent(hDlg),hDlg);
			}
			break;
		case IDC_EDIT_D:
			{
				if (HIWORD( wParam ) == EN_CHANGE)
				{
					GetDlgItemText(hDlg, IDC_EDIT_D, str, 1023);
					if (strlen(str) && ISNUM(str))
					{
						me->d = atof(str);
						if (me->EnableApply()) PropSheet_Changed(::GetParent(hDlg),hDlg);
					}
				}
			}
			break;
		case IDC_EDIT_ROSTVERK_ALTITUDA:
			{
				if (HIWORD( wParam ) == EN_CHANGE)
				{
					GetDlgItemText(hDlg, IDC_EDIT_ROSTVERK_ALTITUDA, str, 1023);
					if (strlen(str) && ISNUM(str))
					{
						me->rostverk_altituda = atof(str);
						if (me->EnableApply()) PropSheet_Changed(::GetParent(hDlg),hDlg);
					}
				}
			}
			break;
		case IDC_EDIT_GAMMA_K:
			{
				if (HIWORD( wParam ) == EN_CHANGE)
				{
					GetDlgItemText(hDlg, IDC_EDIT_GAMMA_K, str, 1023);
					if (strlen(str) && ISNUM(str))
					{
						me->gamma_k = atof(str);
						if (me->EnableApply()) PropSheet_Changed(::GetParent(hDlg),hDlg);
					}
				}
			}
			break;
		}
		break;
	case WM_NOTIFY:
		{
			if (((LPNMHDR) lParam)->hwndFrom == ::GetParent(hDlg))
			{
				switch (((LPNMHDR) lParam)->code)
				{
				case PSN_SETACTIVE:
					{
						//printf("PSN_SETACTIVE\n");
					}
					break;
				case PSN_KILLACTIVE:
					{
						//printf("PSN_KILLACTIVE\n");
					}
					break;
				case PSN_APPLY:
					{
						me->Apply();
						//printf("PSN_APPLY\n");
						//me->ReDraw();
						//====== Перерисовываем Вид с учетом изменений
						//RECT rect;
						//GetClientRect(me->m_pSurfDoc->hSurfWnd,&rect);
						//InvalidateRect(me->m_pSurfDoc->hSurfWnd,&rect, true);
					}
					break;
				case PSN_RESET:
					{
						//printf("PSN_RESET\n");
					}
					break;
				case PSN_HELP:
					{
						//printf("PSN_HELP\n");
					}
					break;
				case PSN_WIZBACK:
					{
						//printf("PSN_WIZBACK\n");
					}
					break;
				case PSN_WIZNEXT:
					{
						//printf("PSN_WIZNEXT\n");
					}
					break;
				case PSN_WIZFINISH:
					{
						//printf("PSN_WIZFINISH\n");
					}
					break;
				case PSN_QUERYCANCEL:
					{
						//printf("PSN_QUERYCANCEL\n");
						DestroyWindow(::GetParent(hDlg));
					}
					break;
				case PSN_GETOBJECT:
					{
						//printf("PSN_GETOBJECT\n");
					}
					break;
				case (PSN_FIRST-11):
					{
						//printf("(PSN_FIRST-11)\n");
						//DestroyWindow(::GetParent(hDlg));
					}
					break;
				case PSN_TRANSLATEACCELERATOR:
					{
						//printf("PSN_TRANSLATEACCELERATOR\n");
					}
					break;
				case PSN_QUERYINITIALFOCUS:
					{
						//printf("PSN_QUERYINITIALFOCUS\n");
					}
					break;
				default:
					{
						//printf("((LPNMHDR) lParam)->code %x\n", ((LPNMHDR) lParam)->code);
					}
					break;
				}
			}
		}
		break;
		default :
			
			return( FALSE );
	}
	return( TRUE );
}




int CALLBACK BuroNabivSvaj::PropSheetProc(HWND hwndDlg,
								   UINT uMsg,
								   LPARAM lParam)
{
//	printf("Cube4D::PropSheetProc HWND hwndDlg = %x, UINT uMsg = %d, LPARAM lParam %d)\n", hwndDlg, uMsg, lParam);
	switch (uMsg)
	{
	case PSCB_PRECREATE:
		{
			//Indicates that the property sheet is about to be created. The hwndDlg parameter is NULL, and the lParam parameter is the address of a dialog template in memory. This template is in the form of a DLGTEMPLATE or DLGTEMPLATEEX structure followed by one or more DLGITEMTEMPLATE structures. 
		}
		break;
	case PSCB_INITIALIZED:
		{
			//Indicates that the property sheet is being initialized. The lParam value is zero for this message. 

		}
		break;
	case 3://PSCB_BUTTONPRESSED:
		{
			switch (lParam)
			{
			case PSBTN_OK:
				{
					DestroyWindow(hwndDlg);
				}
				break;
			case PSBTN_CANCEL:
				{
					DestroyWindow(hwndDlg);
				}
				break;			
			case PSBTN_APPLYNOW:
				{
					//DestroyWindow(hwndDlg);
				}
				break;
			case PSBTN_FINISH:
				{
					DestroyWindow(hwndDlg);
				}
				break;
			}
		}
		break;
	}
	return 0;
}

void BuroNabivSvaj::Dialog(SurfDoc * doc)
{
	pSurfDoc = doc;

    // Ensure that the common control DLL is loaded. 
	// InitCommonControls(); 
	// Инициализируем страницы блокнота  

	psheetPage[0].dwSize = sizeof(PROPSHEETPAGE);
	psheetPage[0].hInstance = hInst;
//	psheetPage[0].pszIcon = MAKEINTRESOURCE(IDI_TAB);
	psheetPage[0].pszIcon = NULL;
	psheetPage[0].dwFlags = PSP_USETITLE/* | PSP_USEICONID*/;
	psheetPage[0].pszTemplate = MAKEINTRESOURCE(IDD_DIALOG_SVAI_BURO_NABIVNIE);
	psheetPage[0].pfnDlgProc = BuroNabivSvaj::DlgProcSvaiBuroNabivnie;
	psheetPage[0].pszTitle = "Main";
	psheetPage[0].lParam = (LPARAM)this;
	hPage[0] = CreatePropertySheetPage(&psheetPage[0]);

	psheetPage[1].dwSize = sizeof(PROPSHEETPAGE);
	psheetPage[1].hInstance = hInst;
//	psheetPage[1].pszIcon = MAKEINTRESOURCE(IDI_TAB);
	psheetPage[1].pszIcon = NULL;
	psheetPage[1].dwFlags = PSP_USETITLE/* | PSP_USEICONID*/;
	psheetPage[1].pszTemplate = MAKEINTRESOURCE(IDD_DIALOG_SVAI_BURO_NABIVNIE_ADDITIONAL);
	psheetPage[1].pfnDlgProc = BuroNabivSvaj::DlgProcAdditionals;
	psheetPage[1].pszTitle = "Additionals";
	psheetPage[1].lParam = (LPARAM)this;
	// Добавляем страницу в блокнот, сохраняя ее
	// идентификатор в массиве hPage
	hPage[1] = CreatePropertySheetPage(&psheetPage[1]);





	// Инициализируем заголовок блокнота
	psheetHeader.dwSize = sizeof(PROPSHEETHEADER);
	psheetHeader.hInstance = hInst;
	psheetHeader.pszIcon = MAKEINTRESOURCE(IDI_APPICONSM);
	psheetHeader.dwFlags = PSH_USEICONID;
	psheetHeader.dwFlags = PSH_DEFAULT | PSH_MODELESS;// | PSH_USECALLBACK;
	//psheetHeader.pfnCallback = BuroNabivSvaj::PropSheetProc;
	psheetHeader.hwndParent = this->pSurfDoc->hwndTV;
	psheetHeader.hwndParent = this->pSurfDoc->hSurfWnd;
	psheetHeader.pszCaption = "BuroNabivSvaj";
	psheetHeader.nPages = 
		sizeof(psheetPage) / sizeof(PROPSHEETPAGE);
	psheetHeader.phpage = (HPROPSHEETPAGE FAR  *)&hPage[0];

	// Создаем и отображаем блокнот
	PropertySheet(&psheetHeader);

	//For a modeless property sheet, your message loop should use 
	//PSM_ISDIALOGMESSAGE to pass messages to the property sheet dialog box. 
	//Your message loop should use PSM_GETCURRENTPAGEHWND to determine when 
	//to destroy the dialog box. When the user clicks the OK or Cancel button, 
	//PSM_GETCURRENTPAGEHWND returns NULL. You can then use the DestroyWindow 
	//function to destroy the dialog box.


}
bool BuroNabivSvaj::EnableApply()
{
	if (index_cub_internal_friction_angle < 0) return false;
	if (use_cub_specific_gravity_of_ground && index_cub_specific_gravity_of_ground < 0) return false;
	if (index_surface_of_relief < 0) return false;
	if (index_surface_of_rostverk < 0 && !use_rostverk_altituda) return false;
	if (use_cub_fluidity_index && index_cub_fluidity_index < 0) return false;

	if (use_water_saturation)
	{
		if (use_cub_specific_gravity_of_ground && index_cub_specific_gravity_of_suspended_in_water_ground < 0) return false;
		if (use_cub_fluidity_index && index_cub_fluidity_index_of_water_saturated_ground < 0) return false;
	}
	return true;
}
void BuroNabivSvaj::Apply()
{

	this->pSurfDoc->SvaiBuroNabivnie(
		index_cub_internal_friction_angle,
		use_cub_specific_gravity_of_ground,
		index_cub_specific_gravity_of_ground,
		index_surface_of_relief,
		index_surface_of_rostverk,
		use_rostverk_altituda,
		rostverk_altituda,
		use_cub_fluidity_index,
		index_cub_fluidity_index,
		d, 
		s_buro_nabiv_svaj_svai_type, 
		v_custom_gamma_cf,
		s_buro_nabiv_svaj_param_type,
		use_water_saturation,
		index_cub_specific_gravity_of_suspended_in_water_ground,
		index_cub_fluidity_index_of_water_saturated_ground,
		gamma_k,
		decrease_clay_R_if_porosty,
		increase_fi_if_dense_sand,
		increase_fi_if_not_porosty_clay);
}
const char * Svaj::SvaiTypeToString(Svaj::SvaiType svai_type)
{
	switch(svai_type)
	{
	case zabivn:
		return "zabivn";
	case buro_nabiv:
		return "buro_nabiv";
	case type_3:
		return "type_3";
	case type_4:
		return "type_4";
	default:
		return "";
	}
}
