// DlgLabElements.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "DlgLabElements.h"
#include "LabView.h"

#include <vector>
#include <algorithm>
#include <map>
using namespace std;

#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLabElements dialog


CDlgLabElements::CDlgLabElements(CLabView * pLabView, LabElements * lab_elements, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLabElements::IDD, pParent), m_list_lab_elements(this, lab_elements)
{
	//{{AFX_DATA_INIT(CDlgLabElements)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT


	this->m_lab_elements = lab_elements;
	this->m_pLabView = pLabView;
}


void CDlgLabElements::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLabElements)
	DDX_Control(pDX, IDC_COMBO_SOIL_DESCRIPTION_SORT_MODE, m_combo_soil_description_sort_mode);
	DDX_Control(pDX, IDC_LIST_LAB_ELEMENTS, m_list_lab_elements);
	DDX_Control(pDX, IDC_LIST_LAB_ELEMENT, m_list_lab_element);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLabElements, CDialog)
	//{{AFX_MSG_MAP(CDlgLabElements)
	ON_WM_DRAWITEM()
	ON_BN_CLICKED(IDC_BUTTON_DIVIDE_LAB_ELEMENT_BY_SVYAZNOST, OnButtonDivideLabElementBySvyaznost)
	ON_BN_CLICKED(IDC_BUTTON_DIVIDE_LAB_ELEMENT, OnButtonDivideLabElement)
	ON_BN_CLICKED(IDC_BUTTON_PREPARE__DIVIDE_LAB_ELEMENT, OnButtonPrepareDivideLabElement)
	ON_BN_CLICKED(IDC_BUTTON_SORT_LAB_ELEMENT, OnButtonSortLabElement)
	ON_BN_CLICKED(IDC_BUTTON_PREPARE__DIVIDE_LAB_ELEMENT_ALL, OnButtonPrepareDivideLabElementAll)
	ON_BN_CLICKED(IDC_BUTTON_PCK_KORRELATION_1, OnButtonPckKorrelation1)
	ON_BN_CLICKED(IDC_BUTTON_PCK_KORRELATION_2, OnButtonPckKorrelation2)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LIST_LAB_ELEMENTS, OnEndlabeleditListLabElements)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLabElements message handlers

BOOL CDlgLabElements::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_list_lab_elements.OnInitCtrl();
	m_list_lab_element.OnInitCtrl();
	
	// TODO: Add extra initialization here
	if (this->m_lab_elements && this->m_lab_elements->vle.size())
		m_list_lab_element.SetLabElement(&this->m_lab_elements->vle.back());

	m_list_lab_element.FillCtrlList();
	m_list_lab_elements.FillCtrlList();

	this->m_combo_soil_description_sort_mode.ResetContent();
	for (SoilDescriptionPtr::compare_mode cm = SoilDescriptionPtr::compare_mode::by_ground_type;
		cm <= SoilDescriptionPtr::compare_mode::by_zond_type; cm++)
	{
		this->m_combo_soil_description_sort_mode.AddString(SoilDescriptionPtr::CompareModeToString(cm));
	}
	this->m_combo_soil_description_sort_mode.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgLabElements::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	switch(nIDCtl)
	{
	case IDC_LIST_LAB_ELEMENTS:
		this->m_list_lab_elements.OnDrawItem(nIDCtl, lpDrawItemStruct);
		break;
	case IDC_LIST_LAB_ELEMENT:
		this->m_list_lab_element.OnDrawItem(nIDCtl, lpDrawItemStruct);
		break;
	}
	//CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
	
}
bool IsSvyaznye(CGround::ground_type gt)
{
	return gt == CGround::ground_type::Clay || gt == CGround::ground_type::Loam || gt == CGround::ground_type::SandyLoam;
}
void Divide(LabElement * undivided, double & t_max,	int & i_t_max)
{
	size_t N = undivided->vsdp.size();
	double t_alpha;
	int K = N - 2; //n1+n2 -2;			
	alpha_value av = av_095;
	Get_t_alpha(av, K, t_alpha);
	for (size_t j = 0; j < N; j++)
	{
		undivided->vsdp[j].GetValue().t = 0.0;
	}
	for (size_t j = 1; j < N-2; j++)
	{
		double X1 = 0.0;
		int n1 = 0;
		for (size_t i = 0; i <= j; i++)
		{
			if (undivided->vsdp[i].GetValue().f)
			{
				X1 += undivided->vsdp[i].GetValue().v;
				n1++;
			}
		}
		X1 /= n1;
		double XX1 = 0.0;
		for (size_t i = 0; i <= j; i++)
		{
			if (undivided->vsdp[i].GetValue().f)
			{
				double d = (undivided->vsdp[i].GetValue().v - X1);
				XX1 += d * d;
			}
		}
		double S1_2 = XX1 / (n1 - 1.0);

		double X2 = 0.0;
		int n2 = 0;
		for (size_t i = j+1; i < N; i++)
		{
			if (undivided->vsdp[i].GetValue().f)
			{
				X2 += undivided->vsdp[i].GetValue().v;
				n2++;
			}
		}
		X2 /= n2;
		double XX2 = 0.0;
		for (size_t i = j+1; i < N; i++)
		{
			if (undivided->vsdp[i].GetValue().f)
			{
				double d = (undivided->vsdp[i].GetValue().v - X2);
				XX2 += d * d;
			}
		}
		double S2_2 = XX2 / (n2 - 1.0);

		if (n1+n2 > 2)
		{
			double k = sqrt(double(n1*n2*(n1+n2-2)/(n1+n2)));
			double zn = sqrt ( n1 * S1_2 + n2 * S2_2);
			double t = fabs(X1-X2) * k / zn;

			undivided->vsdp[j].GetValue().t = t;
		}
	}
	for (size_t j = 0; j < N; j++)
	{
		undivided->vsdp[j].GetValue().t -=  t_alpha;
	}


	t_max = -DBL_MAX;
	i_t_max = -1;
	for (size_t j = 0; j < N; j++)
	{
		if (t_max < undivided->vsdp[j].GetValue().t)
		{
			t_max = undivided->vsdp[j].GetValue().t;
			i_t_max = int(j);
		}
	}

}
void CDlgLabElements::OnButtonDivideLabElementBySvyaznost() 
{
	int i = this->m_list_lab_elements.GetSelected();
	if (i < 0)
	{
		AfxMessageBox("Не выбран лабораторный элемент");
		return;
	}

	this->m_lab_elements->vle.push_back(LabElement(LabElement::type::nesvyaznye));
	this->m_lab_elements->vle.push_back(LabElement(LabElement::type::svyaznye));


	LabElement * undivided = &this->m_lab_elements->vle[i];
	LabElement * nesvyaznye = &this->m_lab_elements->vle[i+1];
	LabElement * svyaznye = &this->m_lab_elements->vle[i+2];

	SoilDescriptionPtr::s_compare_mode = SoilDescriptionPtr::compare_mode::by_ground_type;

	std::sort(undivided->vsdp.begin(), undivided->vsdp.end());

	for(vector<SoilDescriptionPtr>::iterator it = undivided->vsdp.begin();
		it != undivided->vsdp.end(); )
	{

		if ((*it).psd->m_ground_type == CGround::ground_type::Sand)
		{
			nesvyaznye->vsdp.push_back(*it);
			it = undivided->vsdp.erase(it);
		}
		else if (IsSvyaznye((*it).psd->m_ground_type))
		{
			svyaznye->vsdp.push_back(*it);
			it = undivided->vsdp.erase(it);
		}
		else
		{
			it++;
		}

	}

	undivided->m_type = LabElement::type::with_undefined_svyaznost;
	m_list_lab_elements.FillCtrlList();
	m_list_lab_element.SetLabElement(undivided);
	m_list_lab_element.FillCtrlList();
}
void CDlgLabElements::OnButtonSortLabElement() 
{
	int ii = this->m_list_lab_elements.GetSelected();
	if (ii < 0)
	{
		AfxMessageBox("Не выбран лабораторный элемент");
		return;
	}
	LabElement * undivided = &this->m_lab_elements->vle[ii];
	SoilDescriptionPtr::compare_mode cm = (SoilDescriptionPtr::compare_mode)this->m_combo_soil_description_sort_mode.GetCurSel();
	SoilDescriptionPtr::s_compare_mode = cm; //SoilDescriptionPtr::compare_mode::by_plasticity_index;		
	std::sort(undivided->vsdp.begin(), undivided->vsdp.end());	
	m_list_lab_element.SetLabElement(undivided);
	m_list_lab_element.FillCtrlList();
}

void CDlgLabElements::OnButtonPrepareDivideLabElement() 
{
	int ii = this->m_list_lab_elements.GetSelected();
	if (ii < 0)
	{
		AfxMessageBox("Не выбран лабораторный элемент");
		return;
	}
	LabElement * undivided = &this->m_lab_elements->vle[ii];
	SoilDescriptionPtr::compare_mode cm = (SoilDescriptionPtr::compare_mode)this->m_combo_soil_description_sort_mode.GetCurSel();
#if 0
	SoilDescriptionPtr::s_compare_mode = cm; //SoilDescriptionPtr::compare_mode::by_plasticity_index;		
	std::sort(undivided->vsdp.begin(), undivided->vsdp.end());
#endif
	double t_max; int i_t_max;

	if (SoilDescriptionPtr::Is_Trial_T_Value(cm))
	{	
		SoilDescriptionPtr::s_calculation_mode = cm;//SoilDescriptionPtr::compare_mode::by_plasticity_index;
		Divide(undivided, t_max, i_t_max);
	}
	else
	{
		CString s;
		s.Format("Разделение по выбранному признаку = %s не реализовано",
			SoilDescriptionPtr::CompareModeToString(cm));
		AfxMessageBox(s);
		return;
	}


	
	m_list_lab_element.SetLabElement(undivided);
	m_list_lab_element.FillCtrlList();

//	m_list_lab_element.SetSelectionMark(i_t_max);	
//	m_list_lab_element.SetSelectionMark(0);	

	CString s;
	s.Format("i_t_max = %d t_max - t_alpha = %f",i_t_max, t_max);
	if (t_max > 0)
	{
		int ans = MessageBox(s, "Разделить?", MB_YESNO);
		if (ans == IDYES)
		{
			this->m_lab_elements->vle.push_back(LabElement(this->m_lab_elements->vle[ii].m_type));
			LabElement * undivided = &this->m_lab_elements->vle[ii];
			LabElement * divided = &this->m_lab_elements->vle.back();

			for(vector<SoilDescriptionPtr>::iterator it = undivided->vsdp.begin() + i_t_max + 1;
				it != undivided->vsdp.end(); )
			{
				if (true)
				{
					divided->vsdp.push_back(*it);
					it = undivided->vsdp.erase(it);
				}
				else
				{
					it++;
				}
			}

			m_list_lab_elements.FillCtrlList();
			m_list_lab_element.SetLabElement(undivided);
			m_list_lab_element.FillCtrlList();
		}
	}
	else
		MessageBox(s, "", 0);

}


void CDlgLabElements::OnButtonPrepareDivideLabElementAll() 
{
	int ii = this->m_list_lab_elements.GetSelected();
	if (ii < 0)
	{
		AfxMessageBox("Не выбран лабораторный элемент");
		return;
	}
	LabElement * undivided = &this->m_lab_elements->vle[ii];
	
	double t_max; int i_t_max;

	switch(undivided->m_type)
	{
	case LabElement::type::nesvyaznye:
		{
			SoilDescriptionPtr::s_calculation_mode = SoilDescriptionPtr::compare_mode::by_m_minimum_krupnosti_chastic;
			Divide(undivided, t_max, i_t_max);
			SoilDescriptionPtr::s_calculation_mode = SoilDescriptionPtr::compare_mode::by_m_soderzhanie_chastic;
			Divide(undivided, t_max, i_t_max);
			SoilDescriptionPtr::s_calculation_mode = SoilDescriptionPtr::compare_mode::by_C_u;
			Divide(undivided, t_max, i_t_max);
			SoilDescriptionPtr::s_calculation_mode = SoilDescriptionPtr::compare_mode::by_S;
			Divide(undivided, t_max, i_t_max);
		}
		break;
	case LabElement::type::svyaznye:
		{
			SoilDescriptionPtr::s_calculation_mode = SoilDescriptionPtr::compare_mode::by_plasticity_index;
			Divide(undivided, t_max, i_t_max);
			SoilDescriptionPtr::s_calculation_mode = SoilDescriptionPtr::compare_mode::by_fluidity_index_nature;
			Divide(undivided, t_max, i_t_max);
			SoilDescriptionPtr::s_calculation_mode = SoilDescriptionPtr::compare_mode::by_fluidity_index_water_saturated;
			Divide(undivided, t_max, i_t_max);
			SoilDescriptionPtr::s_calculation_mode = SoilDescriptionPtr::compare_mode::by_e;
			Divide(undivided, t_max, i_t_max);
			SoilDescriptionPtr::s_calculation_mode = SoilDescriptionPtr::compare_mode::by_organic;
			Divide(undivided, t_max, i_t_max);
			SoilDescriptionPtr::s_calculation_mode = SoilDescriptionPtr::compare_mode::by_nachalnoe_prosadochnoe_davlenie;
			Divide(undivided, t_max, i_t_max);
			SoilDescriptionPtr::s_calculation_mode = SoilDescriptionPtr::compare_mode::by_svobodnoe_otnositelnoe_nabuhanie;
			Divide(undivided, t_max, i_t_max);
		}
		break;
	}
	m_list_lab_element.SetLabElement(undivided);
	m_list_lab_element.FillCtrlList();
}
void CDlgLabElements::OnButtonDivideLabElement() 
{
	// TODO: Add your control notification handler code here
	int ii = this->m_list_lab_elements.GetSelected();
	if (ii < 0)
	{
		AfxMessageBox("Не выбран лабораторный элемент");
		return;
	}

	int i = this->m_list_lab_element.GetSelected();
	if (i < 0)
	{
		AfxMessageBox("Не выбран лабораторный номер - нижняя граница раздела");
		return;
	}
	LabElement * undivided = &this->m_lab_elements->vle[ii];

	this->m_lab_elements->vle.push_back(LabElement(undivided->m_type));
	undivided = &this->m_lab_elements->vle[ii];
	LabElement * divided = &this->m_lab_elements->vle.back();

	for(vector<SoilDescriptionPtr>::iterator it = undivided->vsdp.begin() + i + 1;
		it != undivided->vsdp.end(); )
	{
		if (true)
		{
			divided->vsdp.push_back(*it);
			it = undivided->vsdp.erase(it);
		}
		else
		{
			it++;
		}
	}

	m_list_lab_elements.FillCtrlList();
	m_list_lab_element.SetLabElement(undivided);
	m_list_lab_element.FillCtrlList();
}



void PckKorrelationObject::SetSizeAndPosOfContextWindow(HWND hWnd, int CX, int CY)
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
bool MinSqLinear(int min_n, vector<x_compression> & x, vector<trial_got_value> & y, int i0, int n, bool donot_shift, trial_value & a0, trial_value & a1, int & m, trial_value & Sy, bool to_printf = false);
void Get_V_alpha_lambda_095(double K, double lambda, double & V);
bool GetNju_0_95(int n, double &nju);

bool PckKorrelationObject::MinSqLinearStat(LabTrialValueType & vt, vector<x_compression> & x, vector<trial_got_value> & y, bool donot_shift, trial_value & a0, trial_value & a1, int & m, trial_value & Sy, MinSqLinearStatParameters & param)
{

	int n = int(y.size());
	m = n;	

	while (m >= 6)
	{
		if (MinSqLinear(6, x, y, 0, 0, donot_shift, a0, a1, m, Sy))
		{
		}

		double nju;// статистический критерий исключения возможных ошибок
		if(!GetNju_0_95(m, nju))
		{
			return false;
		}

		bool excluded = false;

		for (int i = 0; i < n; i ++)
		{
			if (fabs(y[i].v - (a0.v + a1.v * x[i].x)) > nju * Sy)
				// если выполняется условие исключения
			{	
				if (y[i].pf)
				{		
					if (*y[i].pf == TRIAL_VALUE_DEFINED_CAN_EXCLUDED_ONLY_BY_MINSQLIN)  // если значение ранее не исключено
					{
						// исключаем
						*y[i].pf = TRIAL_VALUE_EXCLUDED_BY_MINSQLIN;
						excluded = true;

						/*if (!this->excluded_list_filled)
						{
							excluded_lab_trial exlt;

							char s[128];
							sprintf(s, "%s\0", this->layer_number.c_str());
#if !CHAR_LAYER_NUMBER_ID
							OemToChar(s, s);						
#endif

							exlt.lab_layer_number = s;
							exlt.labnumer_ID = y[i].lab_number ? y[i].lab_number->ID : "undefined";
							exlt.depth = y[i].lab_number ? y[i].lab_number->depth : 0.0;
							exlt.m_mine_working_type = y[i].lab_number ? y[i].lab_number->m_mine_working_type : LabNumber::mine_working_type::undefined;
							exlt.mine_working_number = y[i].lab_number ? y[i].lab_number->mine_working_number : "undefined";

							exlt.pf = y[i].pf;
							exlt.v = y[i].v;
							exlt.vt = vt;

							exlt.vt.cut_pressure = x[i].x;

							exlt.trial = y[i].trial;

							Laboratory::excluded_trials.push_back(exlt);
						}*/
					}

				}
			}
		}

		// заново рассчитываем количество неисключённых значений
		m = 0;
		param.x_mean = 0.0;
		param.x_min = DBL_MAX;
		param.x_max = -DBL_MAX;
		for (int i = 0; i < n; i ++)
		{
			if (y[i].pf)
				if (*y[i].pf == TRIAL_VALUE_DEFINED || *y[i].pf == TRIAL_VALUE_INCLUDED || *y[i].pf == TRIAL_VALUE_DEFINED_CANNOT_EXCLUDED || *y[i].pf == TRIAL_VALUE_DEFINED_CAN_EXCLUDED_ONLY_BY_MINSQLIN || *y[i].pf == TRIAL_VALUE_INCLUDED_TO_MINSQLIN)
				{
					m++;
					param.x_mean += x[i].x;

					if (param.x_min > x[i].x)
						param.x_min = x[i].x;

					if (param.x_max < x[i].x)
						param.x_max = x[i].x;
				}
		}
		param.x_mean /= m;
		param.SumCentralSqX = 0.0;
		for (int i = 0; i < n; i ++)
		{
			if (y[i].pf)
				if (*y[i].pf == TRIAL_VALUE_DEFINED || *y[i].pf == TRIAL_VALUE_INCLUDED || *y[i].pf == TRIAL_VALUE_DEFINED_CANNOT_EXCLUDED || *y[i].pf == TRIAL_VALUE_DEFINED_CAN_EXCLUDED_ONLY_BY_MINSQLIN || *y[i].pf == TRIAL_VALUE_INCLUDED_TO_MINSQLIN)
				{
					param.SumCentralSqX += (x[i].x - param.x_mean)*(x[i].x - param.x_mean);
				}
		}
		param.G = (param.x_min - param.x_mean) / sqrt(param.SumCentralSqX);
		param.D = (param.x_max - param.x_mean) / sqrt(param.SumCentralSqX);
		param.lambda = 
			sqrt
			(
				0.5 * 
				(
					1.0 - 
						(1.0 + m * param.G * param.D) 
						/ 
						(
							sqrt(
								(1.0 + m * param.G * param.G) * (1.0 + m * param.D * param.D)
							)
						)
				)
			);

		param.Kx_min = sqrt(1.0 + 
				m * (param.x_min - param.x_mean) * (param.x_min - param.x_mean)
				/
				param.SumCentralSqX
			);

		param.Kx_max = sqrt(1.0 + 
				m * (param.x_max - param.x_mean) * (param.x_max - param.x_mean)
				/
				param.SumCentralSqX
			);

		if (!excluded)
		{
//			vn = vmean;
//			S = sigma;
//			V = S / vn;			
			return true;
		}
	}
	return false;

}


void PckKorrelationObject_PrintfHeader(PckKorrelationObject * korr_object, vector<fmtstr> * text, vector<LabData> * labdata)
{
	if (text)
	{
		char str[4098];
		sprintf(str, "Корреляция pck и физческих параметров:");
		text->push_back(fmtstr(str, NULL, true, false));
	}
}

void PckKorrelationObject_PrintfProperties(PckKorrelationObject * korr_object, vector<fmtstr> * text, vector<LabData> * labdata)
{
	switch (korr_object->work_mode)
	{
	case 1:
		{
			korr_object->Correlation(text, labdata, "Модуль деформации", korr_object->v_pck_E);
			korr_object->Correlation(text, labdata, "Удельное сцепление", korr_object->v_pck_C);
			korr_object->Correlation(text, labdata, "Угол внутреннего трения", korr_object->v_pck_Fi);
			korr_object->Correlation(text, labdata, "Тангенс угла внутреннего трения", korr_object->v_pck_tgFi);
		}
		break;
	case 2:
		{
			korr_object->Correlation(text, labdata, SoilDescriptionPtr::CompareModeToString(korr_object->m_cm), korr_object->v_pck_val);
		}
		break;
	}
}

void PckKorrelationObject::Correlation(vector<fmtstr> *& text, vector<LabData> * labdata, const char * title, vector<PckKorrelationItem> & vpckkorr)
{
	// нормативные и расчётные значения 
	// коэффициентов линейной зависимости
	// модуля деформации E
	// от pck 
	// путём статистической обработки всех пар опытных значений

	vector<x_compression> vx;
	vector<trial_got_value> vy;
	vx.clear();
	vy.clear();

	char s[1024];
	sprintf(s,"\0");

	for (int i = 0; i < vpckkorr.size(); i++)
	{
		vx.push_back(vpckkorr[i].m_pck);
	
		trial_got_value y;
		y = vpckkorr[i].m_tv;
		y.lab_number = vpckkorr[i].m_lab_number;
		y.trial = NULL;
		vy.push_back(y);
	}

	
	trial_value c;
	trial_value tgfi;
	double fi;
	trial_value Stau;
	int m;		
	LabTrialValueType vt;
	vt.m_indication = LabTrial::indication::undefined_lab_trial_indication;
	vt.is_result = false;
	vt.m_lablayer = NULL;

	//vt.vt_CutLabTrial = CutLabTrial::value_type::vt_cut_resistance ;

		
	MinSqLinearStatParameters param; 
	if (MinSqLinearStat(vt, vx, vy, false, c, tgfi, m, Stau, param) && m)							
	{
		fi = atan(tgfi.v)/PI*180.;
			
		// расчётные значения 
		double tau_n_min = c.v + tgfi.v * param.x_min;
		double tau_n_max = c.v + tgfi.v * param.x_max;

		double V;
		Get_V_alpha_lambda_095(double(m-2), param.lambda, V);



		double delta_tau_min = V * Stau.v * param.Kx_min / sqrt(double(m));
		double delta_tau_max = V * Stau.v * param.Kx_max / sqrt(double(m));

		double tau_min = tau_n_min - delta_tau_min;
		double tau_max = tau_n_max - delta_tau_max;

		double gamma_g_tgfi_c;

		bool use_formula_21 = ((tau_min / param.x_min) < (tau_max / param.x_max));

		if (use_formula_21)
		{
			gamma_g_tgfi_c = (tau_n_min + tau_n_max) * param.x_max / (tau_max * (param.x_min + param.x_max));
		}
		else
		{
			gamma_g_tgfi_c = (tau_n_min + tau_n_max) / (tau_min + tau_max);
		}

		double c_95 = c.v / gamma_g_tgfi_c;
		double tgfi_95 = tgfi.v / gamma_g_tgfi_c;
		
		double fi_95 = atan(tgfi_95)/PI*180.;

		char str[4098];
		sprintf (str, "%s", title);			
		
		if (text) text->push_back(fmtstr(str, NULL, true, true));

		if (labdata)
		{
			// plot
			labdata->back().plot_data.use_plot = true;
			labdata->back().plot_data.title = title;//str;
			labdata->back().plot_data.xlabel = "pck, МПа";
			labdata->back().plot_data.ylabel = "Параметр";

			labdata->back().plot_data.lin_interp.push_back(LinInterp());
			labdata->back().plot_data.lin_interp.back().m_a0 = c.v;
			labdata->back().plot_data.lin_interp.back().m_a1 = tgfi.v;				

			labdata->back().plot_data.lin_interp.push_back(LinInterp());
			labdata->back().plot_data.lin_interp.back().m_a0 = c_95;
			labdata->back().plot_data.lin_interp.back().m_a1 = tgfi_95;
			labdata->back().plot_data.lin_interp.back().line_style = PS_DOT;

			labdata->back().plot_data.plot_lines.push_back(plot_line());

			labdata->back().plot_data.plot_lines.back().line_plot = false;


			for (size_t j = 0; j < vx.size() && j < vy.size(); j++)
			{
				labdata->back().plot_data.plot_lines.back().data.push_back(plot_data_2d(vx[j].x, vy[j].v));
			}



			labdata->push_back(LabData());
			text = &labdata->back().text;
		}
		{
			sprintf (str, "Свободный коэффициент");
			if (text) text->push_back(fmtstr(str, NULL, false, true));

			sprintf (str, "%d", m);
			if (text) text->push_back(fmtstr(str, NULL, false, true));

			sprintf (str, "%f", c.v);
			DeleteEndZeros(str);
			if (text) text->push_back(fmtstr(str, NULL, false, true));

			sprintf (str, "lambda=%f", param.lambda);
			DeleteEndZeros(str);
			if (text) text->push_back(fmtstr(str, NULL, false, true));

			sprintf (str, "V_95=%f", V);
			DeleteEndZeros(str);
			if (text) text->push_back(fmtstr(str, NULL, false, true));

			if (text) text->push_back(fmtstr("", NULL, false, true));

			sprintf (str, "%f", c_95);
			DeleteEndZeros(str);
			if (text) text->push_back(fmtstr(str, NULL, false, true));

			if (text) text->push_back(fmtstr("", NULL, false, true));
		}

		if (text) text->push_back(fmtstr("", NULL, true, true));

		{
			sprintf (str, "Тангенс угла наклона");
			if (text) text->push_back(fmtstr(str, NULL, false, true));

			sprintf (str, "%d", m);
			if (text) text->push_back(fmtstr(str, NULL, false, true));

			sprintf (str, "%f", tgfi.v);
			DeleteEndZeros(str);
			if (text) text->push_back(fmtstr(str, NULL, false, true));

			sprintf (str, "Stau=%f", Stau.v);
			DeleteEndZeros(str);
			if (text) text->push_back(fmtstr(str, NULL, false, true));

			if (text) text->push_back(fmtstr("", NULL, false, true));

			if (text) text->push_back(fmtstr("", NULL, false, true));

			sprintf (str, "%f", tgfi_95);
			DeleteEndZeros(str);
			if (text) text->push_back(fmtstr(str, NULL, false, true));

			if (text) text->push_back(fmtstr("", NULL, false, true));
		}

		if (text) text->push_back(fmtstr("", NULL, true, true));

		{
			sprintf (str, "Угол наклона лин.зав-сти");
			if (text) text->push_back(fmtstr(str, NULL, false, true));

			sprintf (str, "%d", m);
			if (text) text->push_back(fmtstr(str, NULL, false, true));

			sprintf (str, "%f", fi);
			DeleteEndZeros(str);
			if (text) text->push_back(fmtstr(str, NULL, false, true));

			sprintf (str, "g_95=%f", gamma_g_tgfi_c);
			DeleteEndZeros(str);
			if (text) text->push_back(fmtstr(str, NULL, false, true));

			sprintf (str, "F2%d", use_formula_21);
			if (text) text->push_back(fmtstr(str, NULL, false, true));

			if (text) text->push_back(fmtstr("", NULL, false, true));

			sprintf (str, "%f", fi_95);
			DeleteEndZeros(str);
			if (text) text->push_back(fmtstr(str, NULL, false, true));

			if (text) text->push_back(fmtstr("", NULL, true, true));
		}
		if (text)
		{
			if (text) text->push_back(fmtstr("", NULL, false, true));

			if (text) text->push_back(fmtstr("", NULL, false, true));

			if (text) text->push_back(fmtstr("", NULL, false, true));

			sprintf (str, "tau_n_min=%f", tau_n_min);
			DeleteEndZeros(str);
			if (text) text->push_back(fmtstr(str, NULL, false, true));

			sprintf (str, "tau_n_max=%f", tau_n_max);
			DeleteEndZeros(str);
			if (text) text->push_back(fmtstr(str, NULL, false, true));

			if (text) text->push_back(fmtstr("", NULL, false, true));

			if (text) text->push_back(fmtstr("", NULL, true, true));
		}

		if (text)
		{
			if (text) text->push_back(fmtstr("", NULL, false, true));

			if (text) text->push_back(fmtstr("", NULL, false, true));

			if (text) text->push_back(fmtstr("", NULL, false, true));

			sprintf (str, "delta_tau_min=%f", delta_tau_min);
			DeleteEndZeros(str);
			if (text) text->push_back(fmtstr(str, NULL, false, true));

			sprintf (str, "delta_tau_max=%f", delta_tau_max);
			DeleteEndZeros(str);
			if (text) text->push_back(fmtstr(str, NULL, false, true));

			if (text) text->push_back(fmtstr("", NULL, false, true));

			if (text) text->push_back(fmtstr("", NULL, true, true));
		}

		if (text)
		{
			if (text) text->push_back(fmtstr("", NULL, false, true));

			if (text) text->push_back(fmtstr("", NULL, false, true));

			if (text) text->push_back(fmtstr("", NULL, false, true));

			sprintf (str, "param.Kx_min=%f", param.Kx_min);
			DeleteEndZeros(str);
			if (text) text->push_back(fmtstr(str, NULL, false, true));

			sprintf (str, "param.Kx_max=%f", param.Kx_max);
			DeleteEndZeros(str);
			if (text) text->push_back(fmtstr(str, NULL, false, true));

			if (text) text->push_back(fmtstr("", NULL, false, true));

			if (text) text->push_back(fmtstr("", NULL, true, true));
		}

		if (text) text->push_back(fmtstr("", NULL, true, true));

	}
	else
	{
	}
}
void PckKorrelationObject::PrintfProperties(vector<LabData> & labdata)
{
	labdata.push_back(LabData());
	PckKorrelationObject_PrintfHeader(this, &labdata.back().text, &labdata);
	labdata.push_back(LabData());
	PckKorrelationObject_PrintfProperties(this, &labdata.back().text, &labdata);
}
void PckKorrelationObject::PrintfProperties(vector<fmtstr> & text)
{
	PckKorrelationObject_PrintfHeader(this, &text, NULL);
	PckKorrelationObject_PrintfProperties(this, &text, NULL);
}

void CDlgLabElements::OnButtonPckKorrelation1() 
{
	int ii = this->m_list_lab_elements.GetSelected();
	if (ii < 0)
	{
		AfxMessageBox("Не выбран лабораторный элемент");
		return;
	}
	LabElement * undivided = &this->m_lab_elements->vle[ii];
	//SoilDescriptionPtr::compare_mode cm = (SoilDescriptionPtr::compare_mode)this->m_combo_soil_description_sort_mode.GetCurSel();
	//SoilDescriptionPtr::s_compare_mode = cm; //SoilDescriptionPtr::compare_mode::by_plasticity_index;		
	//std::sort(undivided->vsdp.begin(), undivided->vsdp.end());	
	//m_list_lab_element.SetLabElement(undivided);
	//m_list_lab_element.FillCtrlList();

	this->my_object.clear();
	this->my_object.work_mode = 1;


	for (vector<SoilDescriptionPtr>::iterator it = undivided->vsdp.begin(); 
		it != undivided->vsdp.end(); it++)
	{
		SoilDescriptionPtr::s_calculation_mode =  SoilDescriptionPtr::compare_mode::by_pck;
		trial_t_value pck = (*it).GetValue();
		
		SoilDescriptionPtr::s_calculation_mode =  SoilDescriptionPtr::compare_mode::by_gurvich_shtamp_deformation_module_in_01_02_interval;
		trial_t_value E = (*it).GetValue();
		
		// Срез
		SoilDescriptionPtr::s_calculation_mode =  SoilDescriptionPtr::compare_mode::by_c;
		trial_t_value c = (*it).GetValue();
		SoilDescriptionPtr::s_calculation_mode =  SoilDescriptionPtr::compare_mode::by_fi;
		trial_t_value fi = (*it).GetValue();
		SoilDescriptionPtr::s_calculation_mode =  SoilDescriptionPtr::compare_mode::by_tgfi;
		trial_t_value tgfi = (*it).GetValue();

		if (pck.f && E.f)
		{
			this->my_object.v_pck_E.push_back(PckKorrelationItem(pck.v, E.v, (*it).psd->lab_number));
		}

		if (pck.f && fi.f)
		{
			this->my_object.v_pck_Fi.push_back(PckKorrelationItem(pck.v, fi.v, (*it).psd->lab_number));
		}

		if (pck.f && tgfi.f)
		{
			this->my_object.v_pck_tgFi.push_back(PckKorrelationItem(pck.v, tgfi.v, (*it).psd->lab_number));
		}

		if (pck.f && c.f)
		{
			this->my_object.v_pck_C.push_back(PckKorrelationItem(pck.v, c.v, (*it).psd->lab_number));
		}

	}

	if (this->m_pLabView)
		this->m_pLabView->PropertyWindow(true, NULL/*this->m_pLabView->GetWindow()*/, &my_object);

}

	


void CDlgLabElements::OnButtonPckKorrelation2() 
{
	int ii = this->m_list_lab_elements.GetSelected();
	if (ii < 0)
	{
		AfxMessageBox("Не выбран лабораторный элемент");
		return;
	}
	LabElement * undivided = &this->m_lab_elements->vle[ii];
	SoilDescriptionPtr::compare_mode cm = (SoilDescriptionPtr::compare_mode)this->m_combo_soil_description_sort_mode.GetCurSel();

	this->my_object.clear();
	this->my_object.work_mode = 2;
	this->my_object.m_cm = cm;


	for (vector<SoilDescriptionPtr>::iterator it = undivided->vsdp.begin(); 
		it != undivided->vsdp.end(); it++)
	{
		SoilDescriptionPtr::s_calculation_mode =  SoilDescriptionPtr::compare_mode::by_pck;
		trial_t_value pck = (*it).GetValue();
		
		SoilDescriptionPtr::s_calculation_mode =  cm;
		trial_t_value val = (*it).GetValue();		

		if (pck.f && val.f)
		{
			this->my_object.v_pck_val.push_back(PckKorrelationItem(pck.v, val.v, (*it).psd->lab_number));
		}
	}

	if (this->m_pLabView)
		this->m_pLabView->PropertyWindow(true, NULL/*this->m_pLabView->GetWindow()*/, &my_object);
	
}

void CDlgLabElements::OnEndlabeleditListLabElements(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	

	*pResult = 0;
}
