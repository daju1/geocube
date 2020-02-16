#include "StdAfx.h"
#include ".\interwellsline3d.h"
#include "SurfDoc.h"
#include "winsurftree.h"

InterWellsLine3D::InterWellsLine3D(void)
{
	m_pSurfDoc = NULL;
	OnCreate();
}
InterWellsLine3D::InterWellsLine3D(SurfDoc *pSurfDoc)
{
	m_pSurfDoc = pSurfDoc;
	OnCreate();
}

void InterWellsLine3D::OnCreate(void)
{
	this->m_object_type = Object::object_type::inter_wells_line_3d;
	this->m_object_version = 1;
	this->m_max_object_version = 1;
	// если -1 значит параметры не были инициализированы при триангуляции скважин
	glub_deviation = -1.0;
	tolsch_deviation = -1.0;
}
HTREEITEM InterWellsLine3D::AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s)
{
    char szItemText[1024]; // label text of tree-view item 
	// Add the item to the tree-view control
	sprintf(szItemText, "\"%s\" len = %d color = %u glub_deviation = %f tolsch_deviation = %f", GetName().c_str(), GetPointsNumber(), m_color, glub_deviation, tolsch_deviation);
	Object * pObject = dynamic_cast<Object *> (this);
	//=============================================================
	// Add the item to the tree-view control. 
	return AddItemToTree(hwndTV, szItemText, pObject, h1); 
	//=============================================================
}
InterWellsLine3D::~InterWellsLine3D(void)
{
}


int GetInterWellsLineToPaintSliderNum(HWND hwnd, UINT& nID)
{
	//====== GetDlgCtrlID по известному hwnd определяет
	//====== и возвращает идентификатор элемента управления
	switch (GetDlgCtrlID(hwnd))
	{
	//====== Выясняем идентификатор окна справа
	case IDC_SLIDER_INTER_WELLS_PARAM:
		nID = IDC_EDIT_INTER_WELLS_PARAM;
		return 0;
	case IDC_SLIDER_INTER_WELLS_PARAM2:
		nID = IDC_EDIT_INTER_WELLS_PARAM2;
		return 1;
	}
	return 0;
}

LRESULT CALLBACK DlgProcInterWellsLineToPaint( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static SurfDoc * lpSurfDoc;
	static UINT m_Pos[11]; 			// Массив позиций ползунков
	static UINT nObjects;
	static int and_or;
	

	switch( uMsg )
	{
    case WM_INITDIALOG :
		{
			lpSurfDoc = (SurfDoc *)lParam;
			nObjects = 101;
			and_or = 0;

			SendMessage(hDlg,WM_COMMAND,IDC_INIT_SURF_ALPHA_SLIDER,0);			
			//##########################################################
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			// SET RADIO 
			switch (and_or)
			{
			case 0:
				CheckRadioButton( hDlg,
					IDC_RADIO_INTER_WELL_PARAM_AND,
					IDC_RADIO_INTER_WELL_PARAM_OR,
					IDC_RADIO_INTER_WELL_PARAM_AND);
				break;
			case 1:
				CheckRadioButton( hDlg,
					IDC_RADIO_INTER_WELL_PARAM_AND,
					IDC_RADIO_INTER_WELL_PARAM_OR,
					IDC_RADIO_INTER_WELL_PARAM_OR);
				break;
			}
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		}
		break;
	case WM_HSCROLL :
		{
			if (lParam)
			{
				int nPos = HIWORD (wParam);
				//====== Windows-описатель окна активного ползунка
				HWND hwnd = reinterpret_cast<HWND> (lParam);

				UINT nID;

				//=== Определяем индекс в массиве позиций ползунков
				int num = GetInterWellsLineToPaintSliderNum(hwnd, nID);
				int delta;
				UINT newPos;

				//====== Анализируем код события
				switch ( LOWORD( wParam ) )
				{
				case SB_THUMBTRACK:
				case SB_THUMBPOSITION:		// Управление мышью
					m_Pos[num] = nPos;
					break;
				case SB_LEFT:					// Клавиша Home
					delta = -255;
					goto New_Pos;
				case SB_RIGHT:				// Клавиша End
					delta = +255;
					goto New_Pos;
				case SB_LINELEFT:			// Клавиша <-
					delta = -1;
					goto New_Pos;
				case SB_LINERIGHT:			// Клавиша ->
					delta = +1;
					goto New_Pos;
				case SB_PAGELEFT:			// Клавиша PgUp
					delta = -20;
					goto New_Pos;
				case SB_PAGERIGHT:			// Клавиша PgDn
					delta = +20;
					goto New_Pos;

				New_Pos:						// Общая ветвь
					//====== Устанавливаем новое значение регулятора
					newPos = m_Pos[num] + delta;
					//====== Ограничения
					m_Pos[num] = newPos<0 ? 0 : newPos>(nObjects-1) ? (nObjects-1) : newPos;
					break;
				case SB_ENDSCROLL:
				default:
					return (TRUE);
				}

				//====== Синхронизируем параметр lp и
				//====== устанавливаем его в положение nPos
				//lpSurfDlgMem->pSurfDoc->m_DrawListArray.SetObjectToPaint(m_Pos[num]);
				SendMessage(hDlg, WM_COMMAND, IDOK, m_Pos[num]);

				//====== Синхронизируем текстовый аналог позиции
				char s[1024];
				sprintf (s,"%u", m_Pos[num]);
				SetDlgItemText(hDlg, nID, (LPCTSTR)s);

				//====== Перерисовываем Вид с учетом изменений
				RECT rect;
				GetClientRect(lpSurfDoc->hSurfWnd,&rect);
				InvalidateRect(lpSurfDoc->hSurfWnd,&rect, true);
				
			}
		}
		break;
	case WM_COMMAND :
	{
		switch( LOWORD( wParam ) )
		{
		case IDC_INIT_SURF_ALPHA_SLIDER :
			{
				//=== Добываем Windows-описатель окна ползунка
				/*HWND hwnd = GetDlgItem(hDlg, IDC_SLIDER_INTER_WELLS_PARAM);

				SendMessage(				// returns LRESULT in lResult
				(HWND) hwnd,				// handle to destination control
				(UINT) TBM_SETRANGE,		// message ID
				(WPARAM) true,				// = (WPARAM) (BOOL) fRedraw
				(LPARAM) MAKELONG (0, WORD(nObjects-1))	// = (LPARAM) MAKELONG (lMinimum, lMaximum)
				);*/
				int i;
				//====== Проход по всем регулировкам
				/*for (int i=0; i<1; i++)
					//====== Заполняем транспортный массив pPos
					m_Pos[i] = 0;
*/
				//====== Массив идентификаторов ползунков
				UINT IDs[] = 
				{
					IDC_SLIDER_INTER_WELLS_PARAM,
					IDC_SLIDER_INTER_WELLS_PARAM2
				};
				
				char s[1024];
				//====== Цикл прохода по всем регуляторам
				for (i=0; i<sizeof(IDs)/sizeof(IDs[0]); i++)
				{
					
					//=== Добываем Windows-описатель окна ползунка
					HWND hwnd = GetDlgItem(hDlg, IDs[i]);
					UINT nID;

					//====== Определяем его идентификатор
					int num = GetInterWellsLineToPaintSliderNum(hwnd, nID);

					// Требуем установить ползунок в положение m_Pos[i]
					::SendMessage(hwnd, TBM_SETPOS, TRUE,
									(LPARAM)m_Pos[i]);
					
					//====== Готовим текстовый аналог текущей позиции
					sprintf (s,"%u",m_Pos[i]);
					//====== Помещаем текст в окно справа от ползунка
					SetDlgItemText(hDlg, nID, (LPCTSTR)s);					
				}
				//sprintf(s,"%u",nObjects);
				//SetDlgItemText(hDlg, IDC_STATIC_SURF_TOPAINT_MAX, s);
			}
			break;
		case IDC_RADIO_INTER_WELL_PARAM_AND:
			{
				and_or = 0;
			}
			break;
		case IDC_RADIO_INTER_WELL_PARAM_OR:
			{
				and_or = 1;
			}
			break;
		case IDOK :
			{
				printf("IDOK\n");
				if (lpSurfDoc->m_tria_grid.SetCurrentMsgOnFirst())
				{
					do
					{
						if (lpSurfDoc->m_tria_grid.GetCurrentMsg().m_lines.SetCurrentMsgOnFirst())
						{
							do
							{
								InterWellsLine3D * pline = &lpSurfDoc->m_tria_grid.GetCurrentMsg().m_lines.GetCurrentMsg();

								if (pline)
								{
									double tolsch_deviation = pline->tolsch_deviation;
									bool tolsch_deviation_test;
									if (tolsch_deviation > 0.0 && tolsch_deviation < ((double)m_Pos[0] / 100.0) )
									{
										tolsch_deviation_test = true;
									}
									else
									{
										tolsch_deviation_test = false;
									}
									//===============================================
									double glub_deviation = pline->glub_deviation;
									bool glub_deviation_test;
									if (glub_deviation > 0.0 && glub_deviation < ((double)m_Pos[1] / 100.0) )
									{
										glub_deviation_test = true;
									}
									else
									{
										glub_deviation_test = false;
									}
									//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
									// GET RADIO 
									switch (and_or)
									{
									case 0:
										//===============================================
										pline->m_bChecked = tolsch_deviation_test && glub_deviation_test;
										//===============================================
										break;
									case 1:
										//===============================================
										pline->m_bChecked = tolsch_deviation_test || glub_deviation_test;
										//===============================================
										break;
									}
									printf("TreeView_MySetCheckState pline->m_bChecked = %d tolsch_deviation = %f glub_deviation = %f\n", pline->m_bChecked, tolsch_deviation, glub_deviation);
									//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
									TreeView_MySetCheckState(lpSurfDoc->hwndTV, pline->myTreeItem, pline->m_bChecked);
									//===============================================

								}
							}
							while(lpSurfDoc->m_tria_grid.GetCurrentMsg().m_lines.IncrementCurrentMsg());
						}
					}
					while (lpSurfDoc->m_tria_grid.IncrementCurrentMsg());
				}
				SendMessage(hDlg,WM_COMMAND,IDC_INIT_SURF_ALPHA_SLIDER,0);

				//====== Перерисовываем Вид с учетом изменений
				RECT rect;
				GetClientRect(lpSurfDoc->hSurfWnd,&rect);
				InvalidateRect(lpSurfDoc->hSurfWnd,&rect, true);

			}
			break;
		case IDCANCEL :
//			lpSurfDlgMem->pSurfDoc->m_DrawListArray.SetPaintMode(DrawListArray::all);
			EndDialog( hDlg, IDCANCEL );
			break;
		}
	}
	break;
    case WM_DESTROY: 
		{
			// Free any resources used by the bitmaps. 
		}
		break;		
		default :			
			return( FALSE );
	}
	return( TRUE );
}


DWORD InterWellsLine3D::Serialize(Archive& ar)
{
	if (ar.IsStoring())
	{
		ar << *this;
	}
	else
	{
		ar >> *this;
	}
	return 0;
}
#define NOT_OLD_VERSION_OF_TriangulatedGrid3D 1
Archive& operator <<(Archive& ar, InterWellsLine3D& ob)
{
	//ar << *dynamic_cast<Object *>(&ob);
	//dynamic_cast<Primitive3D<CPoint3> *>(&ob)->Primitive_Serialize(ar);
	ar << *dynamic_cast<Line3D *>(&ob);

	DWORD version = ob.m_object_version;
	switch (version)
	{
	case 1:
		{
			ar << ob.delta_x;
			ar << ob.delta_y;
			ar << ob.glub_deviation;
			ar << ob.glub_deviation_x;
			ar << ob.glub_deviation_y;
			ar << ob.tolsch_deviation;
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
Archive& operator >>(Archive& ar, InterWellsLine3D& ob)
{
	//ar >> *dynamic_cast<Object *>(&ob);
	//dynamic_cast<Primitive3D<CPoint3> *>(&ob)->Primitive_Serialize(ar);
	ar >> *dynamic_cast<Line3D *>(&ob);
#if NOT_OLD_VERSION_OF_TriangulatedGrid3D
	switch (ob.m_object_version)
	{
	case 1:
		{
			ar >> ob.delta_x;
			ar >> ob.delta_y;
			ar >> ob.glub_deviation;
			ar >> ob.glub_deviation_x;
			ar >> ob.glub_deviation_y;
			ar >> ob.tolsch_deviation;
		}
		break;
	default:
		{
			throw VersionException(ob.m_object_version, VersionException::cannot_load, ob.m_object_type);
		}
		break;
	}
#endif
	return ar;
}


