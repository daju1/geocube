// PropDlg.cpp : implementation file
//

#include "stdafx.h"
//#include "OG.h"
#include "OGView.h"
#include "PropDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropDlg dialog

#if 0
CPropDlg::CPropDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPropDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPropDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}
#else
CPropDlg::CPropDlg(COGView* p)
	: CDialog(CPropDlg::IDD, p)
{
	//====== Запоминаем адрес Вида
	m_pView = p;
}
#endif



void CPropDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

IMPLEMENT_DYNAMIC(CPropDlg, CDialog)

BEGIN_MESSAGE_MAP(CPropDlg, CDialog)
	//{{AFX_MSG_MAP(CPropDlg)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_FILENAME, OnFilename)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropDlg message handlers


int CPropDlg::GetSliderNum(HWND hwnd, UINT& nID)
{
	//====== GetDlgCtrlID по известному hwnd определяет
	//====== и возвращает идентификатор элемента управления
	switch (::GetDlgCtrlID(hwnd))
	{
	//====== Выясняем идентификатор окна справа
	case IDC_XPOS:
		nID = IDC_XPOS_TEXT;
		return 0;
	case IDC_YPOS:
		nID = IDC_YPOS_TEXT;
		return 1;
	case IDC_ZPOS:
		nID = IDC_ZPOS_TEXT;
		return 2;
	case IDC_AMBIENT:
		nID = IDC_AMB_TEXT;
		return 3;
	case IDC_DIFFUSE:
		nID = IDC_DIFFUSE_TEXT;
		return 4;
	case IDC_SPECULAR:
		nID = IDC_SPECULAR_TEXT;
		return 5;
	case IDC_AMBMAT:
		nID = IDC_AMBMAT_TEXT;
		return 6;
	case IDC_DIFFMAT:
		nID = IDC_DIFFMAT_TEXT;
		return 7;
	case IDC_SPECMAT:
		nID = IDC_SPECMAT_TEXT;
		return 8;
	case IDC_SHINE:
		nID = IDC_SHINE_TEXT;
		return 9;
	case IDC_EMISSION:
		nID = IDC_EMISSION_TEXT;
		return 10;
	}
	return 0;
}

/*
void CPropDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
*/
void CPropDlg::OnHScroll(UINT nSBCode, UINT nPos,
					CScrollBar* pScrollBar)
{
	//====== Windows-описатель окна активного ползунка
	HWND hwnd = pScrollBar->GetSafeHwnd();

	UINT nID;

	//=== Определяем индекс в массиве позиций ползунков
	int num = GetSliderNum(hwnd, nID);
	int delta, newPos;

	//====== Анализируем код события
	switch (nSBCode)
	{
	case SB_THUMBTRACK:
	case SB_THUMBPOSITION:		// Управление мышью
		m_Pos[num] = nPos;
		break;
	case SB_LEFT:					// Клавиша Home
		delta = -100;
		goto New_Pos;
	case SB_RIGHT:				// Клавиша End
		delta = +100;
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
		m_Pos[num] = newPos<0 ? 0 : newPos>100 ? 100 : newPos;
		break;
	case SB_ENDSCROLL:
	default:
		return;
	}

	//====== Синхронизируем текстовый аналог позиции
	char s[8];
	sprintf (s,"%d",m_Pos[num]);
	SetDlgItemText(nID, (LPCTSTR)s);

	//====== Передаем изменение в класс Вида
	m_pView->SetLightParam (num, m_Pos[num]);
}



BOOL CPropDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	//====== Заполняем массив текущих параметров света
	m_pView->GetLightParams(m_Pos);

	//====== Массив идентификаторов ползунков
	UINT IDs[] = 
	{
		IDC_XPOS,		IDC_YPOS,		IDC_ZPOS,
		IDC_AMBIENT,
		IDC_DIFFUSE,
		IDC_SPECULAR,
		IDC_AMBMAT,
		IDC_DIFFMAT,
		IDC_SPECMAT,
		IDC_SHINE,
		IDC_EMISSION
	};

	//====== Цикл прохода по всем регуляторам
	for (int i=0; i<sizeof(IDs)/sizeof(IDs[0]); i++)
	{
		//=== Добываем Windows-описатель окна ползунка
		HWND hwnd = GetDlgItem(IDs[i])->GetSafeHwnd();
		UINT nID;

		//====== Определяем его идентификатор
		int num = GetSliderNum(hwnd, nID);

		// Требуем установить ползунок в положение m_Pos[i]
		::SendMessage(hwnd, TBM_SETPOS, TRUE,
						(LPARAM)m_Pos[i]);
		char s[8];
		//====== Готовим текстовый аналог текущей позиции
		sprintf (s,"%d",m_Pos[i]);
		//====== Помещаем текст в окно справа от ползунка
		SetDlgItemText(nID, (LPCTSTR)s);
	}
	ShowWindow(1);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPropDlg::OnClose() 
{
	//=== Обнуляем указатель на объект своего класса
	m_pView->m_pDlg = 0;
	//====== Уничтожаем окно
	CDialog::OnClose();
	//====== Освобождаем память
	delete this;
}

void CPropDlg::OnFilename() 
{

	//=== Открываем файловый диалог и читаем данные
//	m_pView->ReadData();
}

