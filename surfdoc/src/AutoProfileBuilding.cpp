#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afx.h>
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <iostream>

#define TRACE              printf

#include "stdafx.h"


#include ".\autoprofilebuilding.h"
#include ".\archive.h"
#include "winsurftree.h"
#include "surfdoc.h"
#include "../../winplot/src/winplot.h"
#include "../../tools/src/errorexit.h"
#include "../../array/src/interp.h"
#include "..\..\array\src\ap.h"
#include "..\..\array\src\fft.h"
#include "..\..\array\src\matrixes.h"

#include "../mylicense.h"


#include "AutoBuildProfileDlg.h"

#include "./../kohonen/src/KohonenDlg.h"

#include "./../array/src/sorting.h"

#include "./../array/src/korrelation.h"


extern char szPath[];
extern char directory[];
char dir_out[1024];
extern HINSTANCE hInst;


	
auto_build_parametrs AutoBuildProfile::ab;

void AutoBuildProfile::auto_build_parametrs_Init()
{
	// �������� �� ������� � ����
	ab.use_min			= true;
	ab.use_max			= true;
	ab.use_min_max		= true;

	// ��� �� ������� �������� �� windows_cicle
	ab.use_min_2		= true;
	ab.use_max_2		= true;
	ab.use_min_max_2	= false;

	ab.use_whole_directory = true;
	ab.use_num_col = true;
	ab.use_time_colomn = false;
	//ab.tcols = 2;  //���� � �������� ����� X � Y
	ab.tcols = 3;  //���� � �������� ����� X, Y � Z

	ab.num_col_filename[0] = '\0';

	//######################################################
	ab.use_window_cycles_algorithm_1 = false;
	ab.use_window_cycles_algorithm_dima = false;
	//######################################################
	ab.use_locals = true;
	/*enum locals_algorithms
	{
		the_simple					= 0,
		on_the_second_derivatives	= 1
	};*/ 
	ab.locals_algorithms_type = auto_build_parametrs::locals_algorithms::on_the_second_derivatives;
	//######################################################
	ab.use_window_cycles_after_locals = true;
	ab.use_window_cycles_algorithm_1_after_locals = false;
	ab.use_window_cycles_algorithm_dima_after_locals = true;
	//######################################################
	//######################################################
	//��������� ���������� �� �������
	ab.start_j1 = 1;//��������� ������� ���������� ��� ������ �������
	ab.start_j2 = 0;//��������� ������� ���������� ��� window_cycles_after_locals
	// �������� ������ "�������" �� ���� ������
	// �� ����� �������� ������ �� �������� � "�������",
	// ������� ����� ����������� ���� �������
	// ��� ������ ��������, ��� ������ ������� ����� �������
	ab.quantil_naklony = 0.50;

	// �������� ������ ����� �������� �� �� ��������
	// �������� ������ ��������� ����������� ������ �����������
	// ���� �������� ������ ����� 0,5 �� �� �������� ��� ������������ ����� ��������
	// ��� ������ �������� ������ ��� ������ ����� �������� �� ���������������,
	// ��� ����� �� ��������� ���� ���� ������ ����� ��������
	ab.peregib_krutizna_quantil = 0.40;
	ab.allow_sd_limit_quantil = true;
	//######################################################
	//######################################################
	//��������� ���������� �������� ��� ��������������� ����������� ��������	
	ab.m_gradient_type = auto_build_parametrs::gradient_type::the_dividitial;

	ab.limit_dima = 0.8, 
	ab.limit_1 = 0.9;
	ab.minimum_of_signal = 0.1;
				

	// ������ ���������� ������������� �����
	ab.use_repeat_points = false; // ���� ������, �� �� �� ��������� ������ ���������� ������������� �����, 
	// ����� - ��������� ������ �� ��������� �����������:
	ab.n = 1;//����� ������� ������� ( ����� 0 � ����)

	//��������� ��������� ����� ����
	// ������������ ����
	ab.win_velonsity  = 0.9;

	//######################################################
	//######################################################

	//######################################################
	//######################################################
	// ��������� ������� ��������� � ������ (��� �����) ����� ��������
	ab.k = 0.75;

	//������������ �������� "�����" �� ���-������
	ab.use_min_max_sticks = true;
	ab.use_min_max_sticks = true;

	ab.delim = ',';
}

void AutoBuildProfile::auto_build_parametrs_Init1()
{
	// �������� �� ������� � ����
	ab.use_min			= true;
	ab.use_max			= true;
	ab.use_min_max		= true;

	// ��� �� ������� �������� �� windows_cicle
	ab.use_min_2		= true;
	ab.use_max_2		= true;
	ab.use_min_max_2	= false;

	ab.use_whole_directory = true;
	ab.use_num_col = true;
	ab.use_time_colomn = false;
	//ab.tcols = 2;  //���� � �������� ����� X � Y
	ab.tcols = 3;  //���� � �������� ����� X, Y � Z

	ab.num_col_filename[0] = '\0';

	//######################################################
	ab.use_window_cycles_algorithm_1 = false;
	ab.use_window_cycles_algorithm_dima = false;
	//######################################################
	ab.use_locals = true;
	/*enum locals_algorithms
	{
		the_simple					= 0,
		on_the_second_derivatives	= 1
	};*/ 
	ab.locals_algorithms_type = auto_build_parametrs::locals_algorithms::on_the_second_derivatives;
	//######################################################
	ab.use_window_cycles_after_locals = true;
	ab.use_window_cycles_algorithm_1_after_locals = false;
	ab.use_window_cycles_algorithm_dima_after_locals = true;
	//######################################################
	//######################################################
	//��������� ���������� �� �������
	ab.start_j1 = 1;//��������� ������� ���������� ��� ������ �������
	ab.start_j2 = 0;//��������� ������� ���������� ��� window_cycles_after_locals
	// �������� ������ "�������" �� ���� ������
	// �� ����� �������� ������ �� �������� � "�������",
	// ������� ����� ����������� ���� �������
	// ��� ������ ��������, ��� ������ ������� ����� �������
	ab.quantil_naklony = 0.50;

	// �������� ������ ����� �������� �� �� ��������
	// �������� ������ ��������� ����������� ������ �����������
	// ���� �������� ������ ����� 0,5 �� �� �������� ��� ������������ ����� ��������
	// ��� ������ �������� ������ ��� ������ ����� �������� �� ���������������,
	// ��� ����� �� ��������� ���� ���� ������ ����� ��������
	ab.peregib_krutizna_quantil = 0.40;
	ab.allow_sd_limit_quantil = true;
	//######################################################
	//######################################################
	//��������� ���������� �������� ��� ��������������� ����������� ��������	
	ab.m_gradient_type = auto_build_parametrs::gradient_type::the_dividitial;

	ab.limit_dima = 0.8, 
	ab.limit_1 = 0.9;
	ab.minimum_of_signal = 0.1;
				

	// ������ ���������� ������������� �����
	ab.use_repeat_points = false; // ���� ������, �� �� �� ��������� ������ ���������� ������������� �����, 
	// ����� - ��������� ������ �� ��������� �����������:
	ab.n = 1;//����� ������� ������� ( ����� 0 � ����)

	//��������� ��������� ����� ����
	// ������������ ����
	ab.win_velonsity  = 0.9;

	//######################################################
	//######################################################

	//######################################################
	//######################################################
	// ��������� ������� ��������� � ������ (��� �����) ����� ��������
	ab.k = 0.75;

	//������������ �������� "�����" �� ���-������
	ab.use_min_max_sticks = true;
	ab.use_min_max_sticks = true;

	ab.delim = ',';
}

AutoBuildProfile::AutoBuildProfile()
{
	m_pSurfDoc = NULL;
	OnCreate();
}

AutoBuildProfile::AutoBuildProfile(SurfDoc* pSurfDoc)
{
	this->m_pSurfDoc				= pSurfDoc;
	OnCreate();
}

void AutoBuildProfile::OnCreate(void)
{
	this->m_object_type = Object::object_type::auto_profile_building;
	this->m_object_version = 1;
	this->m_max_object_version = 1;

	this->m_collections.OnCreate();
}

AutoBuildProfile::AutoBuildProfile(const AutoBuildProfile & bp)
{
	dynamic_cast<Object*>(this)->Init(bp);
	this->Init(bp);
}
AutoBuildProfile& AutoBuildProfile::operator=(const AutoBuildProfile& bp)
{
	if (this == &bp)
	{
		return *this;
	}

	dynamic_cast<Object*>(this)->Init(bp);
	this->Init(bp);

	return *this;
}

AutoBuildProfile::~AutoBuildProfile(void)
{
}
/*
void AutoBuildProfile::AddInput(Primitive3D<CPoint3> * primitive)
{
printf("AutoBuildProfile::AddInput\n");
	if (primitive)
	{
		for (unsigned int i = 0; i < primitive->GetPointsNumber(); i++)
		{
			ThePoint3D point(this->m_pSurfDoc);
			this->m_collections.AddMsg(&point);
			this->m_collections.GetLastMsg().InitPoints(&primitive->GetDocumentPoint(i), 1, primitive->GetColor());
			this->m_collections_ObjectList.Init(this->m_collections, this);
		}
	}
}*/
bool AutoBuildProfile::UpdateExtremums()
{
printf("AutoBuildProfile::UpdateExtremums\n");
	vector<CPoint3> vptmax,vptmin;

	if(this->m_collections.SetCurrentMsgOnFirst())
	{
		do
		{
			if(m_collections.GetCurrentMsg().UpdateExtremums())
			{
				vptmax.push_back(m_collections.GetCurrentMsg().GetMax());
				vptmin.push_back(m_collections.GetCurrentMsg().GetMin());
			}
		}
		while(this->m_collections.IncrementCurrentMsg());
	}
	return this->Object::UpdateExtremums(vptmax,vptmin);
}

void AutoBuildProfile::Zoom(double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean)
{
printf("AutoBuildProfile::Zoom\n");	
	if (this->m_collections.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_collections.GetCurrentMsg().Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,
				y_mean,
				z_mean
				);
		}
		while(this->m_collections.IncrementCurrentMsg());
	}
}
HTREEITEM AutoBuildProfile::AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s)
{
    char szItemText[1024]; // label text of tree-view item 
	//====== ������� ������������� �������
	UINT n = this->m_collections.msgSize();	
	sprintf(szItemText, "AutoBuildProfile %d collections", n);
	Object * pObject = dynamic_cast<Object *> (this);
	//=============================================================
	// Add the item to the tree-view control. 
	//HTREEITEM h2 = AddItemToTree(hwndTV, szItemText, pObject, h1); 
	//=============================================================
	//HTREEITEM h3 = AddObjectListItem(hwndTV, szItemText, &this->m_collections_ObjectList, h2); 
	if (this->m_collections.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_collections.GetCurrentMsg().AddItem_ToTree(hwndTV,	h1);
		}
		while(this->m_collections.IncrementCurrentMsg());
		//return h2;
	}
	return NULL;
}

void AutoBuildProfile::Draw()
{
	if (this->m_collections.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_collections.GetCurrentMsg().Draw();
		}
		while(this->m_collections.IncrementCurrentMsg());
	}
}

void AutoBuildProfile::ReDraw()
{
	if(this->m_pSurfDoc) this->ReDrawItem_OnTree(this->m_pSurfDoc->hwndTV);
	if (this->m_collections.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_collections.GetCurrentMsg().ReDraw();
		}
		while(this->m_collections.IncrementCurrentMsg());
	}
}

bool AutoBuildProfile::IsSelected(CPoint3 selected_view_pt, 
		double search_radius,
		WhatSelected& ws)
{
	search_radius = fabs(search_radius);

	
	if (this->m_collections.SetCurrentMsgOnFirst())
	{
		do
		{
			if(this->m_collections.GetCurrentMsg().IsSelected(
				selected_view_pt, search_radius, ws	))
			{
				return true;
			}
		}
		while(this->m_collections.IncrementCurrentMsg());
	}

	return false;
}

void AutoBuildProfile::EnumObjects(WPARAM wParam, LPARAM lParam, void * p,
		bool (Object::* condition_fun)(),
		void (* callback_fun)(Object*, WPARAM , LPARAM, void * ) )
{
	
	if (this->m_collections.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_collections.GetCurrentMsg().EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		}
		while(this->m_collections.IncrementCurrentMsg());
	}
}
void AutoBuildProfile::SetLayer(const Layer* layer)
{
	this->SetLayer_NonVirtual(layer);
	if (this->m_collections.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_collections.GetCurrentMsg().SetLayer(layer);
		}
		while(this->m_collections.IncrementCurrentMsg());
	}
}

void AutoBuildProfile::PropertiesDialog()
{
	MessageBox(0, "PropertiesDialog", "AutoBuildProfile" , 0);
}

bool AutoBuildProfile::ColorDialog(void)
{
	return false;
}

COLORREF AutoBuildProfile::GetColor(void)
{
	return COLORREF();
}

void AutoBuildProfile::SetColor(COLORREF color)
{
}

void AutoBuildProfile::CutAndDisvisible(bool positive, double a, double b, double c, double d)
{
	if (this->m_collections.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_collections.GetCurrentMsg().CutAndDisvisible(positive, a, b, c, d);
		}
		while(this->m_collections.IncrementCurrentMsg());
	}
}

void AutoBuildProfile::CutXYZandDisvisible(int subcube_number, double X, double Y, double Z)
{
	if (this->m_collections.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_collections.GetCurrentMsg().CutXYZandDisvisible(subcube_number, X, Y, Z);
		}
		while(this->m_collections.IncrementCurrentMsg());
	}
}

Collection* AutoBuildProfile::CreateNewCollection(void)
{
	// ������� ������ 
	Collection collection(this->m_pSurfDoc);
	this->m_collections.AddMsg(&collection);		
	this->m_collections_ObjectList.Init(this->m_collections, this);
	return &this->m_collections.GetLastMsg();
}
Archive& operator <<(Archive& ar, AutoBuildProfile& ob)
{
//printf("Archive& operator <<(Archive& ar, AutoBuildProfile& ob)\n");
	//ar << *dynamic_cast<Object *>(&ob);

	DWORD version = ob.Object::Serialize(ar);

	switch (version)
	{
	case 1:
		{
			// Objects' vectors
			ar << ob.m_collections;			ar << ob.m_collections_ObjectList;
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
Archive& operator >>(Archive& ar, AutoBuildProfile& ob)
{
//printf("Archive& operator >>(Archive& ar, AutoBuildProfile& ob)\n");
	//ar >> *dynamic_cast<Object *>(&ob);
	ob.Object::Serialize(ar);
	switch (ob.m_object_version)
	{
	case 1:
		{
			// Objects' vectors
			ar >> ob.m_collections;			ar >> ob.m_collections_ObjectList;
			ob.m_collections_ObjectList.Init(ob.m_collections, &ob);
		}
		break;
	default:
		{
			throw VersionException(ob.m_object_version, VersionException::cannot_load, ob.m_object_type);
		}
		break;
	}
//printf("Archive& operator >>(Archive& ar, AutoBuildProfile& ob) end\n");
	return ar;
}

#if !VIEW_ONLY_VERSION

bool AutoBuildProfile::init()
{
#if 0
	//return AutoBuildProfile_main(true, NULL);
	AutoBuildProfile::auto_build_parametrs_Init();
	return AutoBuildProfile_main(false, this, AutoBuildProfile::ab);
#else
	AutoBuildProfile::auto_build_parametrs_Init();
	AutoBuildProfileDlg * abpd = new AutoBuildProfileDlg(false, this, AutoBuildProfile::ab);		// ...right after the dialog is closed?
	if (abpd != NULL) delete abpd;		// how to safely release the memory...
#endif
	return true;//????
}
bool AutoBuildProfile::init1()
{
	AutoBuildProfile::auto_build_parametrs_Init1();
	AutoBuildProfileDlg1 * abpd = new AutoBuildProfileDlg1(false, this, AutoBuildProfile::ab);		// ...right after the dialog is closed?
	if (abpd != NULL) delete abpd;		// how to safely release the memory...
	return true;//????
}
void WriteDescription(FILE* stream, auto_build_parametrs & ab)
{
	fprintf(stream, "%s\n",ab.num_col_filename);
}

#include "..\..\array\src\slau.h"
void SaveMyGrid(char * name, long rows, long cols, vector<double> & sol)
{
	long rows_cols = rows*cols;
	// 
	Grid grid;
	grid.gridSection.z = AllocDoubleMat(rows,cols);
	for (long c = 0; c < cols; c++)
	{
		for (long r = 0; r < rows; r++)
		{
			grid.gridSection.z[r][c] = sol[(rows-r-1) * cols + c];
		}
	}

	double min_sol = DBL_MAX;
	double max_sol = -DBL_MAX;

	for (long i = 0; i < rows_cols; i++)
	{
		if (min_sol > sol[i]) min_sol = sol[i];
		if (max_sol < sol[i]) max_sol = sol[i];
	}

	grid.gridSection.nCol = cols;
	grid.gridSection.nRow = rows;
	grid.gridSection.xLL = 0.0;
	grid.gridSection.yLL = 0.0;
	grid.gridSection.xSize = 1.0;
	grid.gridSection.ySize = 1.0;
	grid.gridSection.zMax = max_sol;
	grid.gridSection.zMin = min_sol;

	grid.faultSection.nTraces = 0;
	grid.faultSection.nVertices = 0;
	grid.faultSection.traces = NULL;
	grid.faultSection.vertexes = NULL;

	//
	SaveAsSurfer7Grid(name, &grid);
}


struct slau_add_cond_param
{
	long cols;
	long rows;
	double k_gor;
	double k_vert;

	double alpha_gor;
	double alpha_vert;

};

// ����������� �������������� ������� �� ������� ������� ���������
void SlauAdditionalConditions(vector<double> & x,
							  double & add_F,
							  vector<double> & add_dFdx,
							  vector<double> & add_d2Fdx2,
							  void * _param)
{
	//printf("SlauAdd\t");
	slau_add_cond_param * param = reinterpret_cast<slau_add_cond_param *>(_param);
	long Nj, N0 = x.size();
	long i, r, c, j, k;
	//----------------------------
	// ��������� "���������"
	double sum_xii = 0.0;
	for (i = 0; i < N0; i++)
	{
		sum_xii += x[i]*x[i];
	}
	sum_xii / N0;
	//----------------------------

	// ������� � �����������
	add_F = 0.0;

	for (j = 0; j < param->cols-1; j++)
	{
			
		//----------------------------
		// ��������� "����������"
		double sum_xij = 0.0;
		Nj = param->rows * (param->cols - j);
		for (r = 0; r < param->rows; r++)
		{
			for (c = 0; c < param->cols - j; c++)
			{
				i = r * param->cols + c;
				sum_xij += x[i] * x[i+j];
			}
		}
		sum_xij /= Nj;
		//----------------------------
		// ���������� j-� ������
		double delta_j = sum_xii - sum_xij*exp(param->k_gor*j);
		// ���������� ������� � �����������
		add_F += delta_j*delta_j;
		// ��������� ������ � ������ ����������� ������� � ����������� �� x[k]
		for (r = 0; r < param->rows; r++)
		{
			for (c = 0; c < param->cols; c++)
			{
				k = r * param->cols + c;
				// ����������� j-� ������ �� x[k]
				double D_delta_j_xk = 
					2.0*x[k] / N0 
					- 
					exp(param->k_gor*j) 
					* (c >= j ? x[k-j] : 0.0 + c < param->cols-j ? x[k+j] : 0.0) / Nj;
				
				add_dFdx[k] += 2.0 * delta_j * D_delta_j_xk;

				add_d2Fdx2[k] += 4.0 * delta_j / N0 + 2.0 * D_delta_j_xk * D_delta_j_xk;


			}
		}
	}
	add_F *= param->alpha_gor;
	for (i = 0; i < N0; i++)
	{
		add_dFdx[i] *= param->alpha_gor;
		add_d2Fdx2[i] *= param->alpha_gor;
	}
	//printf("add_F = %e\n", add_F);
}
							  
void SlauAdditionalConditions0(vector<double> & x,
							  double & add_F,
							  vector<double> & add_dFdx,
							  vector<double> & add_d2Fdx2,
							  void * _param)
{
	printf("SlauAdd\t");
	slau_add_cond_param * param = reinterpret_cast<slau_add_cond_param *>(_param);
	long i, Nj, N0 = x.size();

	add_F = 0.0;

	for (i = 0; i < N0; i++)
	{
		add_dFdx[i] = 0.0;
		add_d2Fdx2[i] = 0.0;
	}
	//printf("add_F = %e\n", add_F);
}

void DoMyMethod(vector<double> & X,
				vector<double> & Y,
				vector<double> & signal,
				string name)
{
	printf ( "DoMyMethod %s\n", name.c_str() );
	char buff[BUFF_SIZE];

	long cols = signal.size(); // ����� ������� 
	long rows = cols/4;// � ��� �������
	cout << "cols = " << cols << endl;
	cout << "Enter rows [" << rows << "]\n";
	cin >> rows;


	long rows_cols = rows*cols;

	printf ( "DoMyMethod cols = %ld rows = %ld\n", cols,  rows);

	// ���������� ������������ ������ ������
	vector<sparse_row> m;
	vector<double> b;
	vector<double> sol(rows_cols, 0.0);
	long i, C, l = 1;//+1
	long r, c;



	bool to_fill_matrix = true;
	cout << "to_fill_matrix [0,1]\n";
	cin >> to_fill_matrix;

		
	long r0 = 1;

	if (to_fill_matrix)
	{
		bool is_smoof = false;
		cout << "Enter is_smoof [0,1]\n";
		cin >> is_smoof;

		int smoof_power = 1024;


		if (is_smoof)
		{
			cout << "Enter smoof_power [1024]\n";
			cin >> smoof_power;

			smoof_power /= 2;
			smoof_power *= 2;

			cout << "Smoof_power  = " << smoof_power << endl;

			cout << "Enter r0 [1]\n";
			cin >> r0;

			if (r0 < 1)
				r0 = 1;
		}

		double k1 = 1.0;
		double k2 = 0.01;
	printf("Filling of matrix\n");
		for (c = 0; c < cols; c++)
		{
	printf("Filling of matrix %ld %ld\n", c, cols);
			sparse_row row; row.clear();
			for (r = 0; r < rows; r++)
			{
				if (is_smoof)
				{
					for (C = 0; C < cols; C++)
					{
						i = r * cols + C;
						double len = sqrt((double)((r+r0)*(r+r0) + (C-c)*(C-c) ));
						double phi = acos ((r+r0) / len);
						//double phi_k = pow(sin(2.0 * phi), 1024.0);
						//double phi_k = pow(sin(2.0 * phi), 4.0);
						//double phi_k = pow(sin(2.0 * phi), 64.0);
						//double phi_k = pow(sin(2.0 * phi), 16.0);
						double phi_k = pow(sin(2.0 * phi), smoof_power);
						if (phi_k > 0.05)
							row.put(i, k1 * exp ( - k2 * len) * phi_k);
					}
				}
				else
				{
					C = c + r + l;
					if (C >= 0 && C < cols)
					{
						i = r * cols + C;
						//row.put(i, 1.0); // ��� ����������� ���������� K1 * exp ( - k2 * r )
						row.put(i, k1 * exp ( - k2 * r )); // ��� ����������� ���������� K1 * exp ( - k2 * r )
					}			
					C = c - r - l;
					if (C >= 0 && C < cols)
					{
						i = r * cols + C;
						//row.put(i, 1.0); // ��� ����������� ���������� K1 * exp ( - k2 * r )
						row.put(i, k1 * exp ( - k2 * r )); // ��� ����������� ���������� K1 * exp ( - k2 * r )
					}
				}
			}
			m.push_back(row); b.push_back(signal[c]);
		}
		bool to_store_matrix = true;
		if (to_store_matrix)
		{
			char filename[4096];
			TCHAR filter[] =     
				TEXT("Sparse Martix File (*.smf)\0*.smf\0")
				TEXT("All Files (*.*)\0*.*\0");
			sprintf(filename, "\0");
			DWORD nFilterIndex = 0;
			if (SaveFileDlg(0, filename, filter, nFilterIndex) == S_OK)
			{
				AFile f;
				if ( f.Open( filename, GENERIC_WRITE, OPEN_ALWAYS) )
				{
					Archive ar( &f, Archive::store, BUFF_SIZE, buff );

					ar << cols;
					ar << rows;
					ar << r0;
					for (long c = 0; c < cols; c++)
					{
						ar << m[c];
					}
					ar.Close();
					f.Close();
				}
				else
				{
					MessageBox(0, "Do my method\nUnable to open file" , filename, MB_OK);
				}
			}
 		}	
	}
	else
	{
		bool to_load_matrix = true;

		if ( to_load_matrix)
		{
			char filename[4096];
			TCHAR filter[] =     
				TEXT("Sparse Martix File (*.smf)\0*.smf\0")
				TEXT("All Files (*.*)\0*.*\0");
			sprintf(filename, "\0");
			if (OpenFileDlg(0, filter, filename) == S_OK)
			{
				AFile f;
				if( f.Open( filename, GENERIC_READ, OPEN_EXISTING) ) 
				{
					Archive ar( &f, Archive::load, BUFF_SIZE, buff );
					try
					{
						//ar.ReadString(str2, 255);
						//ar.Read((unsigned char*)m2,sizeof(m2));
						long _cols, _rows, _r0;
						ar >> _cols;
						ar >> rows;
						ar >> r0;

						if (cols != _cols)
						{
							char err[4098];
							sprintf(err, "cols %ld != _cols %ld" , 
								cols, _cols);
							MessageBox(0, err, "Error on reading sparse matrix from file", MB_OK);
							return;
						}
						rows_cols = rows*cols;
						sol.resize(rows_cols);

						m.resize(cols);b.resize(cols);
						for (long c = 0; c < cols; c++)
						{
							ar >> m[c];
							b[c] = signal[c];
						}
					}
					catch(char * str)
					{
						MessageBox(0,str,"",0);
					}
					catch (CException* pe)
					{
						// catch errors from WinINet 
						TCHAR szErr[4098]; 
						pe->GetErrorMessage(szErr, 4098); 
						AfxMessageBox(szErr);
						pe->Delete();
					}
					catch(...)
					{
						MessageBox(0,"unknown error of archive read","",0);
					}
					
					ar.Close();
					f.Close();
				}
				else
				{
					MessageBox(0, "Do my method\nUnable to open file" , filename, MB_OK);
				}

			}
		}
	}
#if 1
#define USE_SLAU_TICHONOV_1 0
#define USE_SLAU_TICHONOV_CYCLE 0
#define USE_SECOND_DER_OF_ADD_FUNCTIONAL 1
	//SaveSparseMatrixAsDat(m, "m");
	//SaveSparseMatrixAsGrid(m, rows_cols, "m");
	// ������ �������
	vector<double> E(cols);

	bool slau1_echo = true;
	cout << "Enter first slau echo [0,1]\n";
	cin >> slau1_echo;

	bool slau_echo_cycle = false;
	cout << "Enter slau echo on cycle [0,1]\n";
	cin >> slau_echo_cycle;

	int slau1_maxq = 10000;
	cout << "Enter first slau maxq [10000]\n";
	cin >> slau1_maxq;

	int slau_maxq_cycle = 1000;
	cout << "Enter slau maxq on cycle [1000]\n";
	cin >> slau_maxq_cycle;

	// ����� �� ����� ��� ������������� �������� �� ����������,
	// ������ ��� ��� ����������� � ������� ��������� 
	// ��������������� ������������ alpha ������� ���������� ��������� 
	// ����������� �� ������������ �����������
#if USE_SLAU_TICHONOV_1
	if(!SLAU_Tichonov(m, rows_cols, 0.01, b, sol))
	{
	}
#endif
	if (!SLAU (m, rows_cols, b, false, false, slau1_maxq, sol, slau1_echo))
	{
	}

	double k_gor = 0.1;
	cout << "Enter k_gor [0.1]\n";
	cin >> k_gor;
	k_gor = fabs(k_gor);


	// ����� ����, ��� �� ������� ���������� ��������� 
	// �������� ������� � ����������� ���������������� ��������
	// ���������, ��������� ������������� ���� ������� 
	// ��������������� ��������� ������������ 
	// �� ��������� ����������� ������� ���� 
	slau_add_cond_param param;

	param.cols = cols;
	param.rows = rows;
	param.k_gor = k_gor;
	param.k_vert = 0.5;

	param.alpha_gor = 1.0;
	param.alpha_vert = 1.0;

	//long Cols = rows_cols / 2;
	long Cols = cols;
	long j = 0;
	double etha = 0.01;

	index_for_sort * vis  = new index_for_sort[rows_cols];
	
	double add_F, sE;
	vector<double> add_dFdx(rows_cols);
	vector<double> add_d2Fdx2(rows_cols);
	SlauAdditionalConditions(sol,add_F,add_dFdx,add_d2Fdx2,&param);
	printf("add_F = %e\n", add_F);
	int q = 0;
	{
		char file[2048];
		sprintf(file, "%s\\MyMethod_of_%s_%03d.grd", directory,name.c_str(),++q);
		char * p;
		while (p=strchr (file,'\"'))
		{
			*p = '_';
		}
		SaveMyGrid(file, rows, cols, sol);
	}
	do
	{
		if (!CheckMyLicense()) break;

		double old_add_F = add_F;
		vector<double> old_sol = sol;
		// ��� �� �������� ���������� ��������������� ��������� ������������ 
		// � ��� ������ � ������ ����������� �� ������� �������

		//printf("add_F = %e\t", add_F);

		// ��������� ����������� ��������������� ����������� �� ������� �������
		for (i = 0; i < rows_cols; i++)
		{
#if USE_SECOND_DER_OF_ADD_FUNCTIONAL
			vis[i].sort_val = fabs(add_dFdx[i]/add_d2Fdx2[i]);
#else
			vis[i].sort_val = fabs(add_dFdx[i]);
#endif
			vis[i].i = i;
		}
		qsort( (void *)vis, (size_t)rows_cols, sizeof(index_for_sort), compare_index_for_sort );
		//qsort( (void *)vis, (size_t)rows_cols, sizeof(index_for_sort), compare_index_for_sort_decrease );

		// ���������� �������� ����������
		vector<int> indexes(rows_cols);
		for (i = 0; i < rows_cols; i++){indexes[vis[i].i] = i;}

		// �������� ��������������: ������������ ������ �� �������� ������� �������,
		// ������� ����� ������������ ������ ������ ����������� ��������������� ����������� � 
		// ���������� ������� ����� ����� ����������� ����� ����� ���������			
		//char test[2048];sprintf(test, "%s\\test%03d_%s.dat", directory, q, name.c_str());
		//FILE * stream = fopen(test, "wt");
		for (i = Cols-j; i < rows_cols-j; i++)
		{
#if USE_SECOND_DER_OF_ADD_FUNCTIONAL
			sol[vis[i].i] -= etha * add_dFdx[vis[i].i] / add_d2Fdx2[vis[i].i];
#else
			sol[vis[i].i] -= etha * add_dFdx[vis[i].i];
#endif
			//if(stream) fprintf(stream, "%d, %d, %f\n", int(vis[i].i%cols), int(rows-vis[i].i/cols-1), fabs(add_dFdx[vis[i].i]));
		}
		//if(stream) fclose(stream);
		// ����� ��������� ���������� ����� ��������� �������������� ����������
		/*SlauAdditionalConditions(sol,add_F,add_dFdx,add_d2Fdx2,&param);
		double delta_add_F_part = add_F - old_add_F; 
		//printf("DaF1=%e ", delta_add_F_part);
		// � ������������ ������ �������  
		for (c = 0; c < cols; c++)
		{
			E[c] = - b[c]; // ������� ������� ������ ������ �� ������ �����
			E[c] += m[c].ScalarProduct(sol);
		}
		double sE = SquareSum(E);*/
		//printf ("a_part_sE = %e, add_F = %e\t", sE, add_F);

		// ������ ��������� ����� "�����" ���������� ������� �� ���������� ��������:
		// �� �������� ������� �������, ������� ���� ������ ��� ���������� �
		// ������������ � ����������� ��������������� ����������� - ����������� � ������ �����

		// � ��������� �������� ������� ������� ����� ���������� ����������� ������� ���������� ������� ���������

		vector<sparse_row> m2(cols);
		vector<double> b2(cols);
		vector<double> sol2(Cols, 0.0);

		// ���������� ���������� �������

		for (c = 0; c < cols; c++)
		{
			b2[c] = b[c];
			m2[c].clear();
			BraidedNode<sparse_row_element<double> > * ni = m[c].root->next();
			while (ni != m[c].root)
			{
				i = ni->val.col;
				if (indexes[i] >= Cols-j && indexes[i] < rows_cols-j)
				{
					// ������� ��������
					// ��������� ������� � ����� �������
					b2[c] -= sol[i]*ni->val.val;
				}
				else
				{
					// ����� ��������
					// ��������� ����� �������
					if (indexes[i] < Cols-j)
					{
						m2[c].put(indexes[i], ni->val.val);
						sol2[indexes[i]] = sol[i];
					}
					else // indexes[i] >= rows_cols-j && indexes[i] < rows_cols
					{
						m2[c].put(indexes[i]-rows_cols+Cols, ni->val.val);
						sol2[indexes[i]-rows_cols+Cols] = sol[i];
					}
				}
				ni = ni->next();
			}
		}
		/*double sE2;
		// ������ ������� ��� ���������� �������
		for (c = 0; c < cols; c++)
		{
			E[c] = - b2[c]; // ������� ������� ������ ������ �� �����������
			E[c] += m2[c].ScalarProduct(sol2);
		}
		sE2 = SquareSum(E);
		printf ("bef_dec_sE2 = %e\t", sE2);*/



		// ������� ���������� �������

#if USE_SLAU_TICHONOV_CYCLE
		if (!SLAU_Tichonov(m2, Cols, 0.01, b2, sol2))
		{
		}
#endif
		if (!SLAU (m2, Cols, b2, false, false, slau_maxq_cycle, sol2, slau_echo_cycle))
		{
		}
/*
		// ������ ������� ��� ���������� �������
		for (c = 0; c < cols; c++)
		{
			E[c] = - b2[c]; // ������� ������� ������ ������ �� �����������
			E[c] += m2[c].ScalarProduct(sol2);
		}
		sE2 = SquareSum(E);
		printf ("sE2 = %e\t", sE2);
*/
		// ����������� ����������� ������� ���������� ������� �������� ������ ����������� � ������ ������ ������� 
		for (i = 0; i < Cols-j; i++)				{sol[vis[i].i] = sol2[i];}		
		for (i = rows_cols-j; i < rows_cols; i++)	{sol[vis[i].i] = sol2[i-rows_cols+Cols];}
		SlauAdditionalConditions(sol,add_F,add_dFdx,add_d2Fdx2,&param);
		double delta_add_F = add_F - old_add_F; 
		//printf("add_F = %e\n", add_F);
		// ������ �������
		for (c = 0; c < cols; c++)
		{
			E[c] = - b[c]; // ������� ������� ������ ������ �� �����������
			E[c] += m[c].ScalarProduct(sol);
		}
		sE = SquareSum(E);
		printf ("sE=%e,DaF=%e aF=%e", sE, delta_add_F, add_F);
		if (delta_add_F > 0)
		{
			Cols++;
			//j++;
			sol = old_sol;
			etha *= 0.5;
			add_F = old_add_F;
			SlauAdditionalConditions(sol,add_F,add_dFdx,add_d2Fdx2,&param);
			printf(" et=%e Cols=%ld", etha, Cols);
		}
		else
		{
			char file[2048];
			sprintf(file, "%s\\MyMethod_of_%s_%03d.grd", directory,name.c_str(),q);
			char * p;
			while (p=strchr (file,'\"'))
			{
				*p = '_';
			}
			SaveMyGrid(file, rows, cols, sol);
		}
		printf("\n");
	}
	while (++q < 100);
	delete[] vis;
#else
	slau_add_cond_param param;

	param.cols = cols;
	param.rows = rows;
	param.k_gor = 0.00000;
	param.k_vert = 0.5;

	param.alpha_gor = 0.001;
	param.alpha_vert = 0.05;

	if(!SLAU(m, rows_cols, b, sol, SlauAdditionalConditions, &param))
	{
	}
#endif
#if 1
	// 
	Grid grid;
	grid.gridSection.z = AllocDoubleMat(rows,cols);
	for (long c = 0; c < cols; c++)
	{
		for (long r = 0; r < rows; r++)
		{
			grid.gridSection.z[r][c] = sol[i = (rows-r-1) * cols + c];
		}
	}

	double min_sol = DBL_MAX;
	double max_sol = -DBL_MAX;

	for (long i = 0; i < rows_cols; i++)
	{
		if (min_sol > sol[i]) min_sol = sol[i];
		if (max_sol < sol[i]) max_sol = sol[i];
	}

	grid.gridSection.nCol = cols;
	grid.gridSection.nRow = rows;
	grid.gridSection.xLL = 0.0;
	grid.gridSection.yLL = 0.0;
	grid.gridSection.xSize = 1.0;
	grid.gridSection.ySize = 1.0;
	grid.gridSection.zMax = max_sol;
	grid.gridSection.zMin = min_sol;

	grid.faultSection.nTraces = 0;
	grid.faultSection.nVertices = 0;
	grid.faultSection.traces = NULL;
	grid.faultSection.vertexes = NULL;

	//
	char file[2048];
	sprintf(file, "%s\\MyMethod_of_%s.grd", directory,name.c_str());
	char * p;
	while (p=strchr (file,'\"'))
	{
		*p = '_';
	}
	SaveAsSurfer7Grid(file, &grid);
#endif
	// ������� �������������� �������



}

void
GetProfileDirection(vector<double> & X,
					vector<double> & Y,
					vector<double> & Z,
					double & min__x, double & min__y, double & min__z,
					double & max__x, double & max__y, double & max__z,
					double & delta__x, 
					double & delta__y
					)
{
	min__x = DBL_MAX, min__y = DBL_MAX, min__z = DBL_MAX;
	max__x = -DBL_MAX, max__y = -DBL_MAX, max__z = -DBL_MAX;
	///////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////

	for (size_t i = 0; i < X.size(); i++)
	{
		double 
			x_value = X[i],
			y_value = Y[i],
			z_value = Z[i];

		if (min__x > x_value) min__x = x_value;
		if (min__y > y_value) min__y = y_value;
		if (min__z > z_value) min__z = z_value;

		if (max__x < x_value) max__x = x_value;
		if (max__y < y_value) max__y = y_value;
		if (max__z < z_value) max__z = z_value;

	}

	delta__x = max__x - min__x;
	delta__y = max__y - min__y;
}

bool FillingTheMatrix(double smoof_power,
					  double k_oslablenie,// ����������� ����������
					  double k, // ��������� ������� ��������� � ������ (��� �����) ����� ��������
					  vector<SparseRow> * m,
					  char * filename,
					  long rows, long cols,
					  double x0, double y0, double z0,
					  double delta_x, double delta_y, double delta_z,
					  vector<double> & X,
					  vector<double> & Y,
					  vector<double> & Z)
{
	double xi,yi,zi, len, phi, Zj_zi, Zj_zi2, Yj_yi2, phi_k, value;
	long j,r,C,i;
	long signal_len = X.size(); // ����� ������� 

	double k_phi_max = (PI/2.0)/atan(1.0/2.0*k);

	double k1 = 1.0;// ����������� ������������������
	printf("Filling of matrix\n");
	// ��������� ������� ��������� ������ ������, 
	// ����� ����� ����� ����� ������� 
	// (��� ��������� ����� ���������� �������� - 
	// ���������� �������� �� ����� ���, ��� �����, �� ������ �������)
	// �� ���� ��������� ������� ������������� ��������� 
	// ���������� ���������������� �������
	// �� ������ ��������� ����� �������� ��������� (������) �� ��������
	if (m) // ���� ���� �������, ����� � �� (� ����������� ������)
	{
		(*m).resize(signal_len);
		for (j = 0; j < signal_len; j++)
		{
			printf("Filling of matrix %ld %ld\n", j, signal_len);
			for (r = 0; r < rows; r++)
			{
				//zi = z0 - r * delta_z;// ��� �������!!!
				// �������� ������� �������� ���� ��� ������� ����������� �� ������� delta_z
				zi = z0 - (r+1) * delta_z;

				Zj_zi = (Z[j]-zi);
				Zj_zi2 = Zj_zi * Zj_zi;

				//����� ���� ����, �� ������� ���������� ���������
				double part_of_len = (z0 - zi) / Zj_zi;

				for (C = 0; C < cols; C++)
				{
					// ������ � ������ ������� ��������� ������ ������
					i = r * cols + C;
					// ���������� �������������� ���������
					xi = x0 + C * delta_x;
					yi = y0 + C * delta_y;
					// ���������� �� �������������� ���������
					// �� �������� �� �������
					len = sqrt(
						(X[j]-xi)*(X[j]-xi) + 
						(Y[j]-yi)*(Y[j]-yi) + 
						Zj_zi2 
						);
					// ���� ����������� �� ��������
					phi = acos (Zj_zi / len);
					// ������ ��������� �������� ������������
					phi_k = pow(sin(k_phi_max * phi), smoof_power);
					if (phi_k > 0.1)
						// ���������� �������� � ����������� ������
						(*m)[j].put(i, k1 * exp ( - k_oslablenie * part_of_len * len) * phi_k);
				}
			}
		}
	}
	else // ����� ����� � ����
	{
		AFile f;
		if( !f.Open( filename, GENERIC_WRITE, TRUNCATE_EXISTING) ) 
		{
			if( !f.Open( filename, GENERIC_WRITE, CREATE_NEW) ) 
			{
				MessageBox(0, "Filling the matrix\nUnable to open file" , filename, MB_OK);
				return false;
			}
		}			
		char buff[BUFF_SIZE];
		Archive ar( &f, Archive::store, BUFF_SIZE, buff );

		// ���������� ����������� �������
		//ar << rows; 
		//ar << cols;
		ar << signal_len;
		long rows_cols = rows * cols;
		ar << rows_cols;

		// � ������ ���� ������� - ���������!!

		/*for (long r = 0; r < rows; r++)
		{
			ar << m[r];
		}*/
		for (j = 0; j < signal_len; j++)
		{
			printf("Filling of matrix %ld %ld\n", j, signal_len);
			for (r = 0; r < rows; r++)
			{
				//zi = z0 - r * delta_z;// ��� �������!!!
				// �������� ������� �������� ���� ��� ������� ����������� �� ������� delta_z
				zi = z0 - (r+1) * delta_z;

				Zj_zi = (Z[j]-zi);
				Zj_zi2 = Zj_zi * Zj_zi;

				//����� ���� ����, �� ������� ���������� ���������
				double part_of_len = (z0 - zi) / Zj_zi;


				for (C = 0; C < cols; C++)
				{
					// ������ � ������ ������� ��������� ������ ������
					i = r * cols + C;
					// ���������� �������������� ���������
					xi = x0 + C * delta_x;
					yi = y0 + C * delta_y;
					// ���������� �� �������������� ���������
					// �� �������� �� �������
					len = sqrt(
						(X[j]-xi)*(X[j]-xi) + 
						(Y[j]-yi)*(Y[j]-yi) + 
						Zj_zi2 
						);
					// ���� ����������� �� ��������
					phi = acos (Zj_zi / len);
					// ������ ��������� �������� ������������
					phi_k = pow(sin(k_phi_max * phi), smoof_power);
					if (phi_k > 0.1)
					{
						// ���������� �������� � ����������� ������
						// (*m)[j].put(i, k1 * exp ( - k2 * len) * phi_k);
						value = k1 * exp ( - k_oslablenie * part_of_len * len) * phi_k;
						ar << i;
						ar << value;
					}
				}
			}
			//������� ����� ������ ������
			i = -1;
			value = 0.0;
			ar << i;
			ar << value;
		}
		ar.Close();
		f.Close();

	}
	return true;
}





void FillingTheMatrix_(double smoof_power,
					  double k_oslablenie,// ����������� ����������
					  double k, // ��������� ������� ��������� � ������ (��� �����) ����� ��������
					  vector<sparse_row>& m,
					  vector<double>& b,
					  long rows, long cols,
					  double x0, double y0, double z0,
					  double delta_x, double delta_y, double delta_z,
					  vector<double> & X,
					  vector<double> & Y,
					  vector<double> & Z,
					  vector<double> & signal)
{
	double xi,yi,zi, len, phi, Zj_zi, Zj_zi2, Yj_yi2, phi_k;
	long j,r,C,i, ir, ic, iC;
	long signal_len = signal.size(); // ����� ������� 

	double k_phi_max = (PI/2.0)/atan(1.0/2.0*k);

	double k1 = 1.0;

	vector<long> vr(rows), vc(cols);
	
	index_for_sort * vir  = new index_for_sort[rows];
	for (ir = 0; ir < rows; ir++)
	{
		vir[ir].i = ir;
		vir[ir].sort_val = rand();
	}
	qsort( (void *)vir, (size_t)rows, sizeof(index_for_sort), compare_index_for_sort );
	for (ir = 0; ir < rows; ir++)
	{
		vr[ir] = vir[ir].i;
	}
	delete [] vir;

	index_for_sort * vic  = new index_for_sort[cols];
	for (ic = 0; ic < cols; ic++)
	{
		vic[ic].i = ic;
		vic[ic].sort_val = rand();
	}
	qsort( (void *)vic, (size_t)cols, sizeof(index_for_sort), compare_index_for_sort );
	for (ic = 0; ic < cols; ic++)
	{
		vc[ic] = vic[ic].i;
	}
	delete [] vic;


	printf("Filling of matrix\n");
	// ��������� ������� ��������� ������ ������, 
	// ����� ����� ����� ����� ������� 
	// (��� ��������� ����� ���������� �������� - 
	// ���������� �������� �� ����� ���, ��� �����, �� ������ �������)
	// �� ���� ��������� ������� ������������� ��������� 
	// ���������� ���������������� �������
	// �� ������ ��������� ����� �������� ��������� (������) �� ��������
	m.resize(signal_len);
	b.resize(signal_len);
	for (j = 0; j < signal_len; j++)
	{
		printf("Filling of matrix %ld %ld\n", j, signal_len);
		for (ir = 0; ir < rows; ir++)
		{
			r = vr[ir];

			//zi = z0 - r * delta_z;// ��� �������!!!
			// �������� ������� �������� ���� ��� ������� ����������� �� ������� delta_z
			zi = z0 - (r+1) * delta_z;

			Zj_zi = (Z[j]-zi);
			Zj_zi2 = Zj_zi * Zj_zi;

			//����� ���� ����, �� ������� ���������� ���������
			double part_of_len = (z0 - zi) / Zj_zi;

			for (iC = 0; iC < cols; iC++)
			{
				C = vc[iC];

				// ������ � ������ ������� ��������� ������ ������
				i = r * cols + C;
				// ���������� �������������� ���������
				xi = x0 + C * delta_x;
				yi = y0 + C * delta_y;
				// ���������� �� �������������� ���������
				// �� �������� �� �������
				len = sqrt(
					(X[j]-xi)*(X[j]-xi) + 
					(Y[j]-yi)*(Y[j]-yi) + 
					Zj_zi2 
					);
				// ���� ����������� �� ��������
				phi = acos (Zj_zi / len);
				// ������ ��������� �������� ������������
				phi_k = pow(sin(k_phi_max * phi), smoof_power);
				if (phi_k > 0.1)
					// ���������� �������� � ����������� ������
					m[j].put(i, k1 * exp ( - k_oslablenie * part_of_len * len) * phi_k);
			}
		}
		b[j] = signal[j];
	}
}
double Chislitel_Integral(
	int noise_color,
	double a,//distance
	double b,// ����������� ������������������ ����� ������ �� ������� � ��������� ��� ������������ ���������
	double omega)
{
	double I = 0;
	double ab = a*b;
	double sqw = sqrt(omega);
	double M = - 2.0 * exp(-ab*sqw) / ab;
	// noise color: 1 blue, 2 blue-white 3 white 4 pink-white
	switch (noise_color)
	{
	case 1://blue
		{
			I = M * ((omega * sqw) + (3.0 * omega / ab) + (6.0 * sqw / (ab*ab)) + (6.0 / (ab*ab*ab)));
		}
		break;
	case 2://blue - white
		{
			I = M * ((2.0 * omega) + (2.0 * sqw / ab) + (2.0 / (ab*ab)));
		}
		break;
	case 3://white
		{
			I = M * (sqw + (1.0/ab));
		}
		break;
	case 4://pink-white
		{
			I = M;
		}
		break;
	}
	return I;
}
double Znamenatel_Integral(
	int noise_color,
	double omega_min,
	double omega_max)
{
	double I = 0;
	// noise color: 1 blue, 2 blue-white 3 white 4 pink-white
	switch (noise_color)
	{
	case 1://blue
		{
			I = (1.0/2.0) * (omega_max*omega_max - omega_min*omega_min);
		}
		break;
	case 2://blue - white
		{
			I = (2.0/3.0) * (omega_max*sqrt(omega_max) - omega_min*sqrt(omega_min));
		}
		break;
	case 3://white
		{
			I = (omega_max - omega_min);
		}
		break;
	case 4://pink-white
		{
			I = 2.0 * (sqrt(omega_max) - sqrt(omega_min));
		}
		break;
	}
	return I;
}
bool FillingTheMatrix3D_with_napravlennosty_diagramm_assume_tgdelta_much_more_than_one(
	int noise_color,
	double omega_min,
	double omega_max,
	double sigma,
	vector<SparseRow> * m,
	char * filename,
	long rows, long cols, long pages,
	double x0, double y0, double z0,
	double delta_x, double delta_y, double delta_z,
	vector<double> & X,
	vector<double> & Y,
	vector<double> & Z,
	vector<vector<anten_direction> > & A,
	double pw_dnp,// ������� ��������� �������������� ��������
	double min_value,
	int wave_type,
	sourse_power_model spm
	)
{
	double c = 3.0e+8; // light veloncity
	double e0 = 8.85e-12;
	double mju = 1.0;
	double b = (1.0 / c) * sqrt(mju*sigma/(2.*e0));
	b *= pw_dnp;
	double norm = 1.0 / Znamenatel_Integral(noise_color, omega_min, omega_max);


	/*
������ � �������� ������ � �����

1)	����������� �������� ������ X, Y � Z �������� ��� ������� �������: 
AX(1,0,0), AY(0,1,0) � AZ(0,0,1) ��������������.
2)	���������� ��������� ��������� xi, yi, zi
3)	��� �������� W
4)	��� ��������� ����������� ������� ���������� �������� ���������� ��������� ������� ������������ ����������� ����������� ���������� ���� � ��� ��������� ���������� PEW/NS. 
5)	���������� ��������� ��������� x, y, z
6)	�������� ������ ���� �� ��������� � ����� ��������� L (x-xi, y-yi, z-zi)
7)	������ ������� ���� |L| ��� ����������, ���������� ��������
8)	���������� ������� ��������� ����� ����������� ���������� k_oslablenie : exp ( - k_oslablenie * |L|)

����� ������� ��� ������������ ������ �������, �������� ��������� �������������� ������ � ��������� 
����������� ����������������� ����. ��������� ����������� ���������� �� ������� ������������ 
��������� ����������� ���������� ����, ����������� �� �����. 

��������, ��� �� ����� �� ��������� ��������� xi, yi, zi 
���������������� ����� ����� �����������, � ������� ������� AZ(0,0,1) 
���� ����������� �����������. ����� ���������������� �������� ��� ��������� ����� 
(��������� ���������� ������ ������� ��������), ��������� �������� ������������ 
���������� ���� ���������������� ���� � ���� �������������� ������ �� ����� 
���������� ������, ������� ����������� ������ ������� ����� ����� ����. 

���������� �������������� ���� �� ����� � �������� AX(1,0,0), 
������� ������� ����������� ����� ��� X, �� ���� �� ������. ������ 
���� ������� ����� ��������� (��� ������ �����) ��������� ������� (��������) 
����������� ���������� ����������� ���������������� ���� �� �����. �.�. 
����������� ������ ������� ����� ����� �������� ���������� ���������� 
�����������, �.�. PEW/NS.

������ ���������� �������������� ��� �� ����� � �������� AY(0,1,0), 
������� ������� ����������� ����� ��� Y, �� ���� �� �������. ������ ���� ������� 
����� ��������� ��������� ��������� (���������) ����������� ���������� ����������� 
���������������� ���� �� �����. �.�. ����������� ������ ������� ����� ����� 1.0 / PEW/NS.

9)	��������� ��������� ��������������. ��� ���������, ��� ���������������� ��� �� 
�����������, ��������� ����� ���������������� �������� ��� �������, ������ ����������� 
������ sin(phi) � ������� n, ��� n ����� 1 ��� 2, � phi � ���� ����� ��������� ���� � 
�������� ������� AX, AY ��� AZ. ���������� ������ cos(phi) ����� ��������� ������������ 
AL �������� ���� L � �������� ������� A (ax,ay,az). 
��������� AL = |A|*|L|* cos(phi) = ax*(x-xi) + ay*(y-yi) + az*(z-zi). 
������ (����, ��� |A| = 1): cos(phi) = (ax*(x-xi) + ay*(y-yi) + az*(z-zi)) / |L|.

����������� ����������������� ���� ��������� ���������� ����� ��������� 
������������� ������������� �������� ����������� � ������������. 
�� �� ��� ����������� ���������� ������ ����������� ��������� ������ �����.



��������� ��������� ������������� �������� ���������� ������ ������ 
��� ���������� ��� �������-���������������� ���������� ������� (IDX IDY IDZ).

�� ��� ����� �������� ������� ����� ����� ��������� �������� 
�������� ��������, ��� ��� �������� (���� ��� �� ��������, 
�� ��� ��������� �������� ������������ �� ������ ������� ����) 
�������������� �������������� �� ��� �������-���������������� 
���������� ������� (IDX IDY IDZ) � ��� �������-���������������� 
���������� �������� (IHX IHY IHZ). ������� �� � ���� ������� 
�������� ������ ����� ������ ������������� � ������������ ������ 
������ ���������� �������� (IHX IHY IHZ), � ������� �� ��� � 
��������� ���������� ���������� ������� ����������� �������-���������������.

��� ������ �����������, ��� �� ����� ���� � ����� ���������� ��������.

��������� �������������� ����������� �������?

��������� �������������� ���� ����������� � ������������ ��������?



	*/
	double xi,yi,zi, len, phi, Zj_zi, Zj_zi2, Yj_yi2, phi_k, value;
	long j,p,r,C,i;
	long signal_len = X.size(); // ����� ������� 

	int a; //����� ������ 
	//AX(1,0,0),		a = 0
	//AY(0,1,0)			a = 1
	//� AZ(0,0,1)		a = 2

	// ������� ��������� �������������� ��������
	//int pw_dnp = 2;

    //����������� ��������, ������� �������� � �������� ������ ������    
	//double min_value = 1e-16;

	//double k_phi_max = (PI/2.0)/atan(1.0/2.0*k);

	double k1 = 1.0;
	printf("Filling of matrix\n");
	// ��������� ������� ��������� ������ ������, 
	// ����� ����� ����� ��������� ����� �������, 
	// �.�. �� ���� �������� ������ ������ ��� �Ш� �����
	// (��� ��������� ����� ���������� �������� - 
	// ���������� �������� �� ����� ���, ��� �����, �� ������ �������)
	// �� ���� ��������� ������� ������������� ��������� 
	// ���������� ���������������� �������
	// �� ������ ��������� ����� �������� ��������� (������) �� ��������
	// �� ������� AX(1,0,0), AY(0,1,0) � AZ(0,0,1) 

	// �������� ������� �������� ���� ��� ������� ����������� �� ������� delta_z
	double z_min = z0 - pages * delta_z;

	double sum_operator_value_x = 0.0;
	double sum_operator_value_y = 0.0;
	double sum_operator_value_z = 0.0;

	double hi, w, sum_operator_z_per_xy;

	if (m) // ���� ���� �������, ����� � �� (� ����������� ������)
	{
		(*m).resize(signal_len * 3);
		for (a = 0; a < 3; a++)// ���������� 3 ������
		{
			//int ax = a == 0;
			//int ay = a == 1;
			//int az = a == 2;
			for (j = 0; j < signal_len; j++)
			{
				double ax = A[a][j].ax;
				double ay = A[a][j].ay;
				double az = A[a][j].az;
				printf("Filling of matrix %ld %ld a=%d ax=%f ay=%f az=%f\n", j + a * signal_len, signal_len * 3, a, ax, ay, az);		


				int putted_in_row = 0;
				
				for (p = 0; p < pages; p++)
				{						
				//printf("Filling of matrix \t%ld %ld     %d\n", p, pages, putted_in_row);
					
					//zi = z0 - p * delta_z;// ��� �������!!!
					// �������� ������� �������� ���� ��� ������� ����������� �� ������� delta_z
					//zi = z0 - (p+1) * delta_z;
					zi = z_min + p * delta_z;
					hi = z0 - zi; w = spm.Apply(hi);

					Zj_zi = (Z[j]-zi);
					Zj_zi2 = Zj_zi * Zj_zi;

					//����� ���� ����, �� ������� ���������� ���������
					double part_of_len = (z0 - zi) / Zj_zi;
					
					for (r = 0; r < rows; r++)
					{
						
						yi = y0 + r * delta_y;
						Yj_yi2 = (Y[j]-yi)*(Y[j]-yi);
						
						for (C = 0; C < cols; C++)
						{
							// ������ � ������ ������� ��������� ������ ������
							i = p * rows * cols + r * cols + C;
							// ���������� �������������� ���������
							xi = x0 + C * delta_x;
							// ���������� �� �������������� ���������
							// �� �������� �� �������
							len = sqrt(
								(X[j]-xi)*(X[j]-xi) + 
								Yj_yi2 + 
								Zj_zi2 
								);

							// ���� ����� ������������ �� �������� � �������� � ������
							phi = acos((ax*(X[j]-xi) + ay*(Y[j]-yi) + az*(Z[j]-zi)) / len);
							// ����������� ������ ��������� ��������������
							phi_k = pow(sin(phi), pw_dnp);
							// 
							if (wave_type == 1)	k1 = (1.0 / pow(len, pw_dnp));
							//value = k1 * exp ( - k_oslablenie * part_of_len * len) * phi_k;
							double d = part_of_len * len;
							value = k1 * norm * phi_k * ( 
								Chislitel_Integral(noise_color, d, b, omega_max) -
								Chislitel_Integral(noise_color, d, b, omega_min));

							if (fabs(value) > min_value)
							{
								// ���������� �������� � ����������� ������
								(*m)[j].put(i, value);
								sum_operator_value_x += ax * value * w ;
								sum_operator_value_y += ay * value * w;
								sum_operator_value_z += az * value * w;
								putted_in_row++;
							}
						}
					}
				}
			}
		}
	}
	else
	{
		AFile f;
		if( !f.Open( filename, GENERIC_WRITE, TRUNCATE_EXISTING) ) 
		{
			if( !f.Open( filename, GENERIC_WRITE, CREATE_NEW) ) 
			{
				MessageBox(0, "Filling the matrix 3D with napravlennosty diagramm\nUnable to open file" , filename, MB_OK);
				return false;
			}
		}			
		char buff[BUFF_SIZE];
		Archive ar( &f, Archive::store, BUFF_SIZE, buff );

		// ���������� ����������� �������
		//ar << rows; 
		//ar << cols;
		ar << signal_len * 3;
		long rows_cols_pages = pages * rows * cols;
		ar << rows_cols_pages;

		// � ������ ���� ������� - ���������!!

		/*for (long r = 0; r < rows; r++)
		{
			ar << m[r];
		}*/
		for (a = 0; a < 3; a++)// ���������� 3 ������
		{
			//int ax = a == 0;
			//int ay = a == 1;
			//int az = a == 2;
			for (j = 0; j < signal_len; j++)
			{
				double ax = A[a][j].ax;
				double ay = A[a][j].ay;
				double az = A[a][j].az;
				printf("Filling of matrix %ld %ld a=%d ax=%f ay=%f az=%f\n", j + a * signal_len, signal_len * 3, a, ax, ay, az);		

			
				for (p = 0; p < pages; p++)
				{						
					
					//zi = z0 - p * delta_z;// ��� �������!!!
					// �������� ������� �������� ���� ��� ������� ����������� �� ������� delta_z
					//zi = z0 - (p+1) * delta_z;
					zi = z_min + p * delta_z;
					hi = z0 - zi; w = spm.Apply(hi);
					
					Zj_zi = (Z[j]-zi);
					Zj_zi2 = Zj_zi * Zj_zi;
					
					//����� ���� ����, �� ������� ���������� ���������
					double part_of_len = (z0 - zi) / Zj_zi;

					for (r = 0; r < rows; r++)
					{
						
						yi = y0 + r * delta_y;
						Yj_yi2 = (Y[j]-yi)*(Y[j]-yi);
						
						for (C = 0; C < cols; C++)
						{
							// ������ � ������ ������� ��������� ������ ������
							i = p * rows * cols + r * cols + C;
							// ���������� �������������� ���������
							xi = x0 + C * delta_x;
							// ���������� �� �������������� ���������
							// �� �������� �� �������
							len = sqrt(
								(X[j]-xi)*(X[j]-xi) + 
								Yj_yi2 + 
								Zj_zi2 
								);

							// ���� ����� ������������ �� �������� � �������� � ������
							phi = acos((ax*(X[j]-xi) + ay*(Y[j]-yi) + az*(Z[j]-zi)) / len);
							// ����������� ������ ��������� ��������������
							phi_k = pow(sin(phi), pw_dnp);
							// 
							if (wave_type == 1)	k1 = (1.0 / pow(len, pw_dnp));
							//value = k1 * exp ( - k_oslablenie * part_of_len * len) * phi_k;
							double d = part_of_len * len;
							value = k1 * norm * phi_k * ( 
								Chislitel_Integral(noise_color, d, b, omega_max) -
								Chislitel_Integral(noise_color, d, b, omega_min));
							if (fabs(value) > min_value)
							{
								// ���������� �������� � ����������� ������
								///(*m)[j].put(i, K);
								ar << i;
								ar << value;

								sum_operator_value_x += ax * value * w;
								sum_operator_value_y += ay * value * w;
								sum_operator_value_z += az * value * w;
							}
						}
					}
				}
				//������� ����� ������ ������
				i = -1;
				value = 0.0;
				ar << i;
				ar << value;
			}
		}
		ar.Close();
		f.Close();
	}
	printf("sum_operator_value_x = %e\n", sum_operator_value_x);
	printf("sum_operator_value_y = %e\n", sum_operator_value_y);
	printf("sum_operator_value_z = %e\n", sum_operator_value_z);

	sum_operator_z_per_xy = 2. * sum_operator_value_z / (sum_operator_value_x + sum_operator_value_y);
	printf("sum_operator_z_per_xy = %f\n", sum_operator_z_per_xy);
}










bool FillingTheMatrix3D_with_napravlennosty_diagramm(
					  double k_oslablenie,// ����������� ����������
					  vector<SparseRow> * m,
					  char * filename,
					  long rows, long cols, long pages,
					  double x0, double y0, double z0,
					  double delta_x, double delta_y, double delta_z,
					  vector<double> & X,
					  vector<double> & Y,
					  vector<double> & Z,
					  vector<vector<anten_direction> > & A,
					  double pw_dnp,// ������� ��������� �������������� ��������
					  double min_value,
					  int wave_type,
					  sourse_power_model spm
					  )
{

	/*
������ � �������� ������ � �����

1)	����������� �������� ������ X, Y � Z �������� ��� ������� �������: 
AX(1,0,0), AY(0,1,0) � AZ(0,0,1) ��������������.
2)	���������� ��������� ��������� xi, yi, zi
3)	��� �������� W
4)	��� ��������� ����������� ������� ���������� �������� ���������� ��������� ������� ������������ ����������� ����������� ���������� ���� � ��� ��������� ���������� PEW/NS. 
5)	���������� ��������� ��������� x, y, z
6)	�������� ������ ���� �� ��������� � ����� ��������� L (x-xi, y-yi, z-zi)
7)	������ ������� ���� |L| ��� ����������, ���������� ��������
8)	���������� ������� ��������� ����� ����������� ���������� k_oslablenie : exp ( - k_oslablenie * |L|)

����� ������� ��� ������������ ������ �������, �������� ��������� �������������� ������ � ��������� 
����������� ����������������� ����. ��������� ����������� ���������� �� ������� ������������ 
��������� ����������� ���������� ����, ����������� �� �����. 

��������, ��� �� ����� �� ��������� ��������� xi, yi, zi 
���������������� ����� ����� �����������, � ������� ������� AZ(0,0,1) 
���� ����������� �����������. ����� ���������������� �������� ��� ��������� ����� 
(��������� ���������� ������ ������� ��������), ��������� �������� ������������ 
���������� ���� ���������������� ���� � ���� �������������� ������ �� ����� 
���������� ������, ������� ����������� ������ ������� ����� ����� ����. 

���������� �������������� ���� �� ����� � �������� AX(1,0,0), 
������� ������� ����������� ����� ��� X, �� ���� �� ������. ������ 
���� ������� ����� ��������� (��� ������ �����) ��������� ������� (��������) 
����������� ���������� ����������� ���������������� ���� �� �����. �.�. 
����������� ������ ������� ����� ����� �������� ���������� ���������� 
�����������, �.�. PEW/NS.

������ ���������� �������������� ��� �� ����� � �������� AY(0,1,0), 
������� ������� ����������� ����� ��� Y, �� ���� �� �������. ������ ���� ������� 
����� ��������� ��������� ��������� (���������) ����������� ���������� ����������� 
���������������� ���� �� �����. �.�. ����������� ������ ������� ����� ����� 1.0 / PEW/NS.

9)	��������� ��������� ��������������. ��� ���������, ��� ���������������� ��� �� 
�����������, ��������� ����� ���������������� �������� ��� �������, ������ ����������� 
������ sin(phi) � ������� n, ��� n ����� 1 ��� 2, � phi � ���� ����� ��������� ���� � 
�������� ������� AX, AY ��� AZ. ���������� ������ cos(phi) ����� ��������� ������������ 
AL �������� ���� L � �������� ������� A (ax,ay,az). 
��������� AL = |A|*|L|* cos(phi) = ax*(x-xi) + ay*(y-yi) + az*(z-zi). 
������ (����, ��� |A| = 1): cos(phi) = (ax*(x-xi) + ay*(y-yi) + az*(z-zi)) / |L|.

����������� ����������������� ���� ��������� ���������� ����� ��������� 
������������� ������������� �������� ����������� � ������������. 
�� �� ��� ����������� ���������� ������ ����������� ��������� ������ �����.



��������� ��������� ������������� �������� ���������� ������ ������ 
��� ���������� ��� �������-���������������� ���������� ������� (IDX IDY IDZ).

�� ��� ����� �������� ������� ����� ����� ��������� �������� 
�������� ��������, ��� ��� �������� (���� ��� �� ��������, 
�� ��� ��������� �������� ������������ �� ������ ������� ����) 
�������������� �������������� �� ��� �������-���������������� 
���������� ������� (IDX IDY IDZ) � ��� �������-���������������� 
���������� �������� (IHX IHY IHZ). ������� �� � ���� ������� 
�������� ������ ����� ������ ������������� � ������������ ������ 
������ ���������� �������� (IHX IHY IHZ), � ������� �� ��� � 
��������� ���������� ���������� ������� ����������� �������-���������������.

��� ������ �����������, ��� �� ����� ���� � ����� ���������� ��������.

��������� �������������� ����������� �������?

��������� �������������� ���� ����������� � ������������ ��������?



	*/
	double xi,yi,zi, len, phi, Zj_zi, Zj_zi2, Yj_yi2, phi_k, value;
	long j,p,r,C,i;
	long signal_len = X.size(); // ����� ������� 

	int a; //����� ������ 
	//AX(1,0,0),		a = 0
	//AY(0,1,0)			a = 1
	//� AZ(0,0,1)		a = 2

	// ������� ��������� �������������� ��������
	//int pw_dnp = 2;

    //����������� ��������, ������� �������� � �������� ������ ������    
	//double min_value = 0.03;
	//double min_value = 1e-16;

	//double k_phi_max = (PI/2.0)/atan(1.0/2.0*k);

	double k1 = 1.0;
	printf("Filling of matrix\n");
	// ��������� ������� ��������� ������ ������, 
	// ����� ����� ����� ��������� ����� �������, 
	// �.�. �� ���� �������� ������ ������ ��� �Ш� �����
	// (��� ��������� ����� ���������� �������� - 
	// ���������� �������� �� ����� ���, ��� �����, �� ������ �������)
	// �� ���� ��������� ������� ������������� ��������� 
	// ���������� ���������������� �������
	// �� ������ ��������� ����� �������� ��������� (������) �� ��������
	// �� ������� AX(1,0,0), AY(0,1,0) � AZ(0,0,1) 

	// �������� ������� �������� ���� ��� ������� ����������� �� ������� delta_z
	double z_min = z0 - pages * delta_z;

	double sum_operator_value_x = 0.0;
	double sum_operator_value_y = 0.0;
	double sum_operator_value_z = 0.0;
	double hi, w, sum_operator_z_per_xy;
	if (m) // ���� ���� �������, ����� � �� (� ����������� ������)
	{
		(*m).resize(signal_len * 3);
		for (a = 0; a < 3; a++)// ���������� 3 ������
		{
			int ax = a == 0;
			int ay = a == 1;
			int az = a == 2;
			for (j = 0; j < signal_len; j++)
			{
				printf("Filling of matrix %ld %ld\n", j + a * signal_len, signal_len * 3);		


				int putted_in_row = 0;
				
				for (p = 0; p < pages; p++)
				{						
				//printf("Filling of matrix \t%ld %ld     %d\n", p, pages, putted_in_row);
					
					//zi = z0 - p * delta_z;// ��� �������!!!
					// �������� ������� �������� ���� ��� ������� ����������� �� ������� delta_z
					//zi = z0 - (p+1) * delta_z;
					zi = z_min + p * delta_z;
					hi = z0 - zi; w = spm.Apply(hi);

					Zj_zi = (Z[j]-zi);
					Zj_zi2 = Zj_zi * Zj_zi;

					//����� ���� ����, �� ������� ���������� ���������
					double part_of_len = (z0 - zi) / Zj_zi;
					
					for (r = 0; r < rows; r++)
					{
						
						yi = y0 + r * delta_y;
						Yj_yi2 = (Y[j]-yi)*(Y[j]-yi);
						
						for (C = 0; C < cols; C++)
						{
							// ������ � ������ ������� ��������� ������ ������
							i = p * rows * cols + r * cols + C;
							// ���������� �������������� ���������
							xi = x0 + C * delta_x;
							// ���������� �� �������������� ���������
							// �� �������� �� �������
							len = sqrt(
								(X[j]-xi)*(X[j]-xi) + 
								Yj_yi2 + 
								Zj_zi2 
								);
	#if 1
							// ���� ����� ������������ �� �������� � �������� � ������
							phi = acos((ax*(X[j]-xi) + ay*(Y[j]-yi) + az*(Z[j]-zi)) / len);
							// ����������� ������ ��������� ��������������
							phi_k = pow(sin(phi), pw_dnp);
							// 
							if (wave_type == 1)	k1 = (1.0 / pow(len, pw_dnp));
							value = k1 * exp ( - k_oslablenie * pw_dnp * part_of_len * len) * phi_k;
							if (fabs(value) > min_value)
							{
								// ���������� �������� � ����������� ������
								(*m)[j].put(i, value);
								putted_in_row++;

								sum_operator_value_x += ax * value * w;
								sum_operator_value_y += ay * value * w;
								sum_operator_value_z += az * value * w;
							}
	#else
							// ���� ����������� �� ��������
							phi = acos (Zj_zi / len);
							// ��������� ������� �����������
							k_phi = k_phi_max * phi;
							if (fabs(k_phi) > PI) k_phi = 0.0;
							// ������ ��������� �������� ������������
							phi_k = pow(sin(k_phi), smoof_power);
							if (phi_k > 0.1)
							{
								// ���������� �������� � ����������� ������
								(*m)[j].put(i, k1 * exp ( - k_oslablenie * part_of_len * len) * phi_k);
								putted_in_row++;
							}
	#endif
						}
					}
				}
			}
		}
	}
	else
	{
		AFile f;
		if( !f.Open( filename, GENERIC_WRITE, TRUNCATE_EXISTING) ) 
		{
			if( !f.Open( filename, GENERIC_WRITE, CREATE_NEW) ) 
			{
				MessageBox(0, "Filling the matrix 3D with napravlennosty diagramm\nUnable to open file" , filename, MB_OK);
				return false;
			}
		}			
		char buff[BUFF_SIZE];
		Archive ar( &f, Archive::store, BUFF_SIZE, buff );

		// ���������� ����������� �������
		//ar << rows; 
		//ar << cols;
		ar << signal_len * 3;
		long rows_cols_pages = pages * rows * cols;
		ar << rows_cols_pages;

		// � ������ ���� ������� - ���������!!

		/*for (long r = 0; r < rows; r++)
		{
			ar << m[r];
		}*/
		for (a = 0; a < 3; a++)// ���������� 3 ������
		{
			int ax = a == 0;
			int ay = a == 1;
			int az = a == 2;
			for (j = 0; j < signal_len; j++)
			{
				printf("Filling of matrix %ld %ld\n", j + a * signal_len, signal_len * 3);		

			
				for (p = 0; p < pages; p++)
				{						
					
					//zi = z0 - p * delta_z;// ��� �������!!!
					// �������� ������� �������� ���� ��� ������� ����������� �� ������� delta_z
					//zi = z0 - (p+1) * delta_z;
					zi = z_min + p * delta_z;
					hi = z0 - zi; w = spm.Apply(hi);
					
					Zj_zi = (Z[j]-zi);
					Zj_zi2 = Zj_zi * Zj_zi;
					
					//����� ���� ����, �� ������� ���������� ���������
					double part_of_len = (z0 - zi) / Zj_zi;

					for (r = 0; r < rows; r++)
					{
						
						yi = y0 + r * delta_y;
						Yj_yi2 = (Y[j]-yi)*(Y[j]-yi);
						
						for (C = 0; C < cols; C++)
						{
							// ������ � ������ ������� ��������� ������ ������
							i = p * rows * cols + r * cols + C;
							// ���������� �������������� ���������
							xi = x0 + C * delta_x;
							// ���������� �� �������������� ���������
							// �� �������� �� �������
							len = sqrt(
								(X[j]-xi)*(X[j]-xi) + 
								Yj_yi2 + 
								Zj_zi2 
								);
	#if 1
							// ���� ����� ������������ �� �������� � �������� � ������
							phi = acos((ax*(X[j]-xi) + ay*(Y[j]-yi) + az*(Z[j]-zi)) / len);
							// ����������� ������ ��������� ��������������
							phi_k = pow(sin(phi), pw_dnp);
							// 
							if (wave_type == 1)	k1 = (1.0 / pow(len, pw_dnp));
							value = k1 * exp ( - k_oslablenie * pw_dnp * part_of_len * len) * phi_k;
							if (fabs(value) > min_value)
							{
								// ���������� �������� � ����������� ������
								///(*m)[j].put(i, K);
								ar << i;
								ar << value;

								sum_operator_value_x += ax * value * w;
								sum_operator_value_y += ay * value * w;
								sum_operator_value_z += az * value * w;
							}
	#else
							// ���� ����������� �� ��������
							phi = acos (Zj_zi / len);
							// ��������� ������� �����������
							k_phi = k_phi_max * phi;
							if (fabs(k_phi) > PI) k_phi = 0.0;
							// ������ ��������� �������� ������������
							phi_k = pow(sin(k_phi), smoof_power);
							if (phi_k > 0.1)
							{
								// ���������� �������� � ����������� ������
								//(*m)[j].put(i, k1 * exp ( - k2 * part_of_len * len) * phi_k);
								if (wave_type == 1)	k1 = (1.0 / pow(len, pw_dnp));
								value = k1 * exp ( - k_oslablenie * pw_dnp * part_of_len * len) * phi_k;
								ar << i;
								ar << value;
							}
	#endif
						}
					}
				}
				//������� ����� ������ ������
				i = -1;
				value = 0.0;
				ar << i;
				ar << value;
			}
		}
		ar.Close();
		f.Close();
	}
	printf("sum_operator_value_x = %e\n", sum_operator_value_x);
	printf("sum_operator_value_y = %e\n", sum_operator_value_y);
	printf("sum_operator_value_z = %e\n", sum_operator_value_z);

	sum_operator_z_per_xy = 2. * sum_operator_value_z / (sum_operator_value_x + sum_operator_value_y);
	printf("sum_operator_z_per_xy = %f\n", sum_operator_z_per_xy);

}








bool FillingTheMatrix3D_with_napravlennosty_diagramm_assume_tgdelta_much_more_than_one(
	int noise_color,
	double omega_min,
	double omega_max,
	double sigma,
	char * filename,
	vector<OperatorRow> * m,
	long rows, long cols, long pages,
	double x0, double y0, double z0,
	double delta_x, double delta_y, double delta_z,
	vector<double> & X,
	vector<double> & Y,
	vector<double> & Z,
	vector<vector<anten_direction> > & A,
	double pw_dnp,// ������� ��������� �������������� ��������
	double min_value,
	int wave_type,
	sourse_power_model spm
	)
{
	double c = 3.0e+8; // light veloncity
	double e0 = 8.85e-12;
	double mju = 1.0;
	double b = (1.0 / c) * sqrt(mju*sigma/(2.*e0));
	b *= pw_dnp;
	double norm = 1.0 / Znamenatel_Integral(noise_color, omega_min, omega_max);


	/*
������ � �������� ������ � �����

1)	����������� �������� ������ X, Y � Z �������� ��� ������� �������: 
AX(1,0,0), AY(0,1,0) � AZ(0,0,1) ��������������.
2)	���������� ��������� ��������� xi, yi, zi
3)	��� �������� W
4)	��� ��������� ����������� ������� ���������� �������� ���������� ��������� ������� ������������ ����������� ����������� ���������� ���� � ��� ��������� ���������� PEW/NS. 
5)	���������� ��������� ��������� x, y, z
6)	�������� ������ ���� �� ��������� � ����� ��������� L (x-xi, y-yi, z-zi)
7)	������ ������� ���� |L| ��� ����������, ���������� ��������
8)	���������� ������� ��������� ����� ����������� ���������� k_oslablenie : exp ( - k_oslablenie * |L|)

����� ������� ��� ������������ ������ �������, �������� ��������� �������������� ������ � ��������� 
����������� ����������������� ����. ��������� ����������� ���������� �� ������� ������������ 
��������� ����������� ���������� ����, ����������� �� �����. 

��������, ��� �� ����� �� ��������� ��������� xi, yi, zi 
���������������� ����� ����� �����������, � ������� ������� AZ(0,0,1) 
���� ����������� �����������. ����� ���������������� �������� ��� ��������� ����� 
(��������� ���������� ������ ������� ��������), ��������� �������� ������������ 
���������� ���� ���������������� ���� � ���� �������������� ������ �� ����� 
���������� ������, ������� ����������� ������ ������� ����� ����� ����. 

���������� �������������� ���� �� ����� � �������� AX(1,0,0), 
������� ������� ����������� ����� ��� X, �� ���� �� ������. ������ 
���� ������� ����� ��������� (��� ������ �����) ��������� ������� (��������) 
����������� ���������� ����������� ���������������� ���� �� �����. �.�. 
����������� ������ ������� ����� ����� �������� ���������� ���������� 
�����������, �.�. PEW/NS.

������ ���������� �������������� ��� �� ����� � �������� AY(0,1,0), 
������� ������� ����������� ����� ��� Y, �� ���� �� �������. ������ ���� ������� 
����� ��������� ��������� ��������� (���������) ����������� ���������� ����������� 
���������������� ���� �� �����. �.�. ����������� ������ ������� ����� ����� 1.0 / PEW/NS.

9)	��������� ��������� ��������������. ��� ���������, ��� ���������������� ��� �� 
�����������, ��������� ����� ���������������� �������� ��� �������, ������ ����������� 
������ sin(phi) � ������� n, ��� n ����� 1 ��� 2, � phi � ���� ����� ��������� ���� � 
�������� ������� AX, AY ��� AZ. ���������� ������ cos(phi) ����� ��������� ������������ 
AL �������� ���� L � �������� ������� A (ax,ay,az). 
��������� AL = |A|*|L|* cos(phi) = ax*(x-xi) + ay*(y-yi) + az*(z-zi). 
������ (����, ��� |A| = 1): cos(phi) = (ax*(x-xi) + ay*(y-yi) + az*(z-zi)) / |L|.

����������� ����������������� ���� ��������� ���������� ����� ��������� 
������������� ������������� �������� ����������� � ������������. 
�� �� ��� ����������� ���������� ������ ����������� ��������� ������ �����.



��������� ��������� ������������� �������� ���������� ������ ������ 
��� ���������� ��� �������-���������������� ���������� ������� (IDX IDY IDZ).

�� ��� ����� �������� ������� ����� ����� ��������� �������� 
�������� ��������, ��� ��� �������� (���� ��� �� ��������, 
�� ��� ��������� �������� ������������ �� ������ ������� ����) 
�������������� �������������� �� ��� �������-���������������� 
���������� ������� (IDX IDY IDZ) � ��� �������-���������������� 
���������� �������� (IHX IHY IHZ). ������� �� � ���� ������� 
�������� ������ ����� ������ ������������� � ������������ ������ 
������ ���������� �������� (IHX IHY IHZ), � ������� �� ��� � 
��������� ���������� ���������� ������� ����������� �������-���������������.

��� ������ �����������, ��� �� ����� ���� � ����� ���������� ��������.

��������� �������������� ����������� �������?

��������� �������������� ���� ����������� � ������������ ��������?



	*/
	double xi,yi,zi, len, phi, Zj_zi, Zj_zi2, Yj_yi2, phi_k, value;
	long j,p,r,C,i;
	long signal_len = X.size(); // ����� ������� 

	int a; //����� ������ 
	//AX(1,0,0),		a = 0
	//AY(0,1,0)			a = 1
	//� AZ(0,0,1)		a = 2

	// ������� ��������� �������������� ��������
	//int pw_dnp = 2;

    //����������� ��������, ������� �������� � �������� ������ ������    
	//double min_value = 1e-16;

	//double k_phi_max = (PI/2.0)/atan(1.0/2.0*k);

	double k1 = 1.0;
	printf("Filling of matrix\n");
	// ��������� ������� ��������� ������ ������, 
	// ����� ����� ����� ��������� ����� �������, 
	// �.�. �� ���� �������� ������ ������ ��� �Ш� �����
	// (��� ��������� ����� ���������� �������� - 
	// ���������� �������� �� ����� ���, ��� �����, �� ������ �������)
	// �� ���� ��������� ������� ������������� ��������� 
	// ���������� ���������������� �������
	// �� ������ ��������� ����� �������� ��������� (������) �� ��������
	// �� ������� AX(1,0,0), AY(0,1,0) � AZ(0,0,1) 

	// �������� ������� �������� ���� ��� ������� ����������� �� ������� delta_z
	double z_min = z0 - pages * delta_z;

	double sum_operator_value_x = 0.0;
	double sum_operator_value_y = 0.0;
	double sum_operator_value_z = 0.0;

	double hi, w, sum_operator_z_per_xy;

	if (m) // ���� ���� �������, ����� � �� (� ����������� ������)
	{
		(*m).resize(signal_len * 3);
		for (a = 0; a < 3; a++)// ���������� 3 ������
		{
			int ax = a == 0;
			int ay = a == 1;
			int az = a == 2;
			for (j = 0; j < signal_len; j++)
			{
				printf("Filling of matrix %ld %ld\n", j + a * signal_len, signal_len * 3);		


				int putted_in_row = 0;
				
				for (p = 0; p < pages; p++)
				{						
				//printf("Filling of matrix \t%ld %ld     %d\n", p, pages, putted_in_row);
					
					//zi = z0 - p * delta_z;// ��� �������!!!
					// �������� ������� �������� ���� ��� ������� ����������� �� ������� delta_z
					//zi = z0 - (p+1) * delta_z;
					zi = z_min + p * delta_z;
					hi = z0 - zi; w = spm.Apply(hi);

					Zj_zi = (Z[j]-zi);
					Zj_zi2 = Zj_zi * Zj_zi;

					//����� ���� ����, �� ������� ���������� ���������
					double part_of_len = (z0 - zi) / Zj_zi;
					
					for (r = 0; r < rows; r++)
					{
						
						yi = y0 + r * delta_y;
						Yj_yi2 = (Y[j]-yi)*(Y[j]-yi);
						
						for (C = 0; C < cols; C++)
						{
							// ������ � ������ ������� ��������� ������ ������
							i = p * rows * cols + r * cols + C;
							// ���������� �������������� ���������
							xi = x0 + C * delta_x;
							// ���������� �� �������������� ���������
							// �� �������� �� �������
							len = sqrt(
								(X[j]-xi)*(X[j]-xi) + 
								Yj_yi2 + 
								Zj_zi2 
								);

							// ���� ����� ������������ �� �������� � �������� � ������
							phi = acos((ax*(X[j]-xi) + ay*(Y[j]-yi) + az*(Z[j]-zi)) / len);
							// ����������� ������ ��������� ��������������
							phi_k = pow(sin(phi), pw_dnp);
							// 
							if (wave_type == 1)	k1 = (1.0 / pow(len, pw_dnp));
							//value = k1 * exp ( - k_oslablenie * part_of_len * len) * phi_k;
							double d = part_of_len * len;
							value = k1 * norm * phi_k * ( 
								Chislitel_Integral(noise_color, d, b, omega_max) -
								Chislitel_Integral(noise_color, d, b, omega_min));

							if (fabs(value) > min_value)
							{
								// ���������� �������� � ����������� ������
								(*m)[j].put(i, value);
								sum_operator_value_x += ax * value * w ;
								sum_operator_value_y += ay * value * w;
								sum_operator_value_z += az * value * w;
								putted_in_row++;
							}
						}
					}
				}
			}
		}
	}
	else
	{
		AFile f;
		if( !f.Open( filename, GENERIC_WRITE, TRUNCATE_EXISTING) ) 
		{
			if( !f.Open( filename, GENERIC_WRITE, CREATE_NEW) ) 
			{
				MessageBox(0, "Filling the matrix 3D with napravlennosty diagramm\nUnable to open file" , filename, MB_OK);
				return false;
			}
		}			
		char buff[BUFF_SIZE];
		Archive ar( &f, Archive::store, BUFF_SIZE, buff );

		// ���������� ����������� �������
		//ar << rows; 
		//ar << cols;
		ar << signal_len * 3;
		long rows_cols_pages = pages * rows * cols;
		ar << rows_cols_pages;

		// � ������ ���� ������� - ���������!!

		/*for (long r = 0; r < rows; r++)
		{
			ar << m[r];
		}*/
		for (a = 0; a < 3; a++)// ���������� 3 ������
		{
			int ax = a == 0;
			int ay = a == 1;
			int az = a == 2;
			for (j = 0; j < signal_len; j++)
			{
				printf("Filling of matrix %ld %ld\n", j + a * signal_len, signal_len * 3);		

			
				for (p = 0; p < pages; p++)
				{						
					
					//zi = z0 - p * delta_z;// ��� �������!!!
					// �������� ������� �������� ���� ��� ������� ����������� �� ������� delta_z
					//zi = z0 - (p+1) * delta_z;
					zi = z_min + p * delta_z;
					hi = z0 - zi; w = spm.Apply(hi);
					
					Zj_zi = (Z[j]-zi);
					Zj_zi2 = Zj_zi * Zj_zi;
					
					//����� ���� ����, �� ������� ���������� ���������
					double part_of_len = (z0 - zi) / Zj_zi;

					for (r = 0; r < rows; r++)
					{
						
						yi = y0 + r * delta_y;
						Yj_yi2 = (Y[j]-yi)*(Y[j]-yi);
						
						for (C = 0; C < cols; C++)
						{
							// ������ � ������ ������� ��������� ������ ������
							i = p * rows * cols + r * cols + C;
							// ���������� �������������� ���������
							xi = x0 + C * delta_x;
							// ���������� �� �������������� ���������
							// �� �������� �� �������
							len = sqrt(
								(X[j]-xi)*(X[j]-xi) + 
								Yj_yi2 + 
								Zj_zi2 
								);

							// ���� ����� ������������ �� �������� � �������� � ������
							phi = acos((ax*(X[j]-xi) + ay*(Y[j]-yi) + az*(Z[j]-zi)) / len);
							// ����������� ������ ��������� ��������������
							phi_k = pow(sin(phi), pw_dnp);
							// 
							if (wave_type == 1)	k1 = (1.0 / pow(len, pw_dnp));
							//value = k1 * exp ( - k_oslablenie * part_of_len * len) * phi_k;
							double d = part_of_len * len;
							value = k1 * norm * phi_k * ( 
								Chislitel_Integral(noise_color, d, b, omega_max) -
								Chislitel_Integral(noise_color, d, b, omega_min));
							if (fabs(value) > min_value)
							{
								// ���������� �������� � ����������� ������
								///(*m)[j].put(i, K);
								ar << i;
								ar << value;

								sum_operator_value_x += ax * value * w;
								sum_operator_value_y += ay * value * w;
								sum_operator_value_z += az * value * w;
							}
						}
					}
				}
				//������� ����� ������ ������
				i = -1;
				value = 0.0;
				ar << i;
				ar << value;
			}
		}
		ar.Close();
		f.Close();
	}
	printf("sum_operator_value_x = %e\n", sum_operator_value_x);
	printf("sum_operator_value_y = %e\n", sum_operator_value_y);
	printf("sum_operator_value_z = %e\n", sum_operator_value_z);

	sum_operator_z_per_xy = 2. * sum_operator_value_z / (sum_operator_value_x + sum_operator_value_y);
	printf("sum_operator_z_per_xy = %f\n", sum_operator_z_per_xy);
}

void ddet_dbeta_domega_div_det(double beta, double omega, 
					double rx, double ry, double rz, 
					double ax, double ay, double az,

					double & ddet_dbeta_div_det,
					double & ddet_domega_div_det,

					double & d2det_dbeta2_div_det,
					double & d2det_domega2_div_det					
					)
{
	double Det_fi = ax*sin(beta)*cos(omega)*rz-ax*cos(beta)*ry+sin(beta)*sin(omega)*ry*az-sin(beta)*sin(omega)*ay*rz+rx*ay*cos(beta)-rx*sin(beta)*cos(omega)*az;
	double ddet_dbeta = ax*cos(beta)*cos(omega)*rz+ax*sin(beta)*ry+cos(beta)*sin(omega)*ry*az-cos(beta)*sin(omega)*ay*rz-rx*ay*sin(beta)-rx*cos(beta)*cos(omega)*az;
	double ddet_domega = -sin(beta)*(ax*sin(omega)*rz-cos(omega)*ry*az+cos(omega)*ay*rz-rx*sin(omega)*az);

	double d2det_dbeta2 = -ax*sin(beta)*cos(omega)*rz+ax*cos(beta)*ry-sin(beta)*sin(omega)*ry*az+sin(beta)*sin(omega)*ay*rz-rx*ay*cos(beta)+rx*sin(beta)*cos(omega)*az;
	double d2det_domega2 = -sin(beta)*(ax*cos(omega)*rz+sin(omega)*ry*az-sin(omega)*ay*rz-rx*cos(omega)*az);


	ddet_dbeta_div_det = ddet_dbeta / Det_fi;
	ddet_domega_div_det = ddet_domega / Det_fi;
	d2det_dbeta2_div_det = d2det_dbeta2 / Det_fi;
	d2det_domega2_div_det = d2det_domega2 / Det_fi;
}


// ����������� ������ ��������� ��������������
double nju_phi_calc(double beta, double omega, 
					double rx, double ry, double rz, 
					double ax, double ay, double az)
{
	/*
	double px, py, pz;

	// ����������� ������� �������������� ������ ��������� ���������
	pz = cos(beta);
	px = sin(beta) * sin(omega);
	py = sin(beta) * cos(omega);


	//������� ���������� ������� � 
	//(��� ����������� ��������������� �� ������ � 
	//��� ������ ����� ����, ������� ��� ����������� 
	//������� � ��� ���������� ����� ��������� 
	//������������ px,py,pz �� (X[j]-xi),(Y[j]-yi),(Z[j]-zi))

	//hx = py*rz � pz*ry;
	//hy = pz*rx � px*rz;
	//hz = px*ry � py*rx;

	double hx = py*rz - pz*ry;
	double hy = pz*rx - px*rz;
	double hz = px*ry - py*rx;
*/
	// ����������� ������ ��������� ��������������
	//nju_phi = pow(sin(theta)*cos(alpha), pw_dnp);
	//sin(theta)*cos(alpha) = 
	//sin(theta)*(a,h)/(|a|*|h|) = 
	//sin(theta)*(a,h)/(|a|*|P|*|r|*|sin(theta)|) = 
	//(a,h)/|r| = 
	//(a,[P,r])/|r| =
	//det(M)/|r|

	double Det_fi = ax*sin(beta)*cos(omega)*rz-ax*cos(beta)*ry+sin(beta)*sin(omega)*ry*az-sin(beta)*sin(omega)*ay*rz+rx*ay*cos(beta)-rx*sin(beta)*cos(omega)*az;
	double len = sqrt(rx*rx + ry*ry + rz*rz);

	double det_fi_len = Det_fi / len;
	return det_fi_len * det_fi_len;
}

void FillingTheMatrix3D_with_napravlennosty_diagramm_dipol(
					  double k_oslablenie,// ����������� ����������
					  double **** m,// ��������� �� ��� ������� njuXr, njuYr, njuZr
					  double **** R,// ��������� �� ��� ������� rx, ry, rz
					  long rows, long cols, long pages,
					  double x0, double y0, double z0,
					  double delta_x, double delta_y, double delta_z,
					  vector<double> & X,
					  vector<double> & Y,
					  vector<double> & Z,
					  vector<vector<anten_direction> > & A,
	double pw_dnp,// ������� ��������� �������������� ��������
	double min_value,
	int wave_type,
	sourse_power_model spm
					  )
{

	/*
������ � �������� ������ � �����

1)	����������� �������� ������ X, Y � Z �������� ��� ������� �������: 
AX(1,0,0), AY(0,1,0) � AZ(0,0,1) ��������������.
2)	���������� ��������� ��������� xi, yi, zi
3)	��� �������� W
4)	��� ��������� ����������� ������� ���������� �������� ���������� ��������� ������� ������������ ����������� ����������� ���������� ���� � ��� ��������� ���������� PEW/NS. 
5)	���������� ��������� ��������� x, y, z
6)	�������� ������ ���� �� ��������� � ����� ��������� L (x-xi, y-yi, z-zi)
7)	������ ������� ���� |L| ��� ����������, ���������� ��������
8)	���������� ������� ��������� ����� ����������� ���������� k_oslablenie : exp ( - k_oslablenie * |L|)

����� ������� ��� ������������ ������ �������, �������� ��������� �������������� ������ � ��������� 
����������� ����������������� ����. ��������� ����������� ���������� �� ������� ������������ 
��������� ����������� ���������� ����, ����������� �� �����. 

��������, ��� �� ����� �� ��������� ��������� xi, yi, zi 
���������������� ����� ����� �����������, � ������� ������� AZ(0,0,1) 
���� ����������� �����������. ����� ���������������� �������� ��� ��������� ����� 
(��������� ���������� ������ ������� ��������), ��������� �������� ������������ 
���������� ���� ���������������� ���� � ���� �������������� ������ �� ����� 
���������� ������, ������� ����������� ������ ������� ����� ����� ����. 

���������� �������������� ���� �� ����� � �������� AX(1,0,0), 
������� ������� ����������� ����� ��� X, �� ���� �� ������. ������ 
���� ������� ����� ��������� (��� ������ �����) ��������� ������� (��������) 
����������� ���������� ����������� ���������������� ���� �� �����. �.�. 
����������� ������ ������� ����� ����� �������� ���������� ���������� 
�����������, �.�. PEW/NS.

������ ���������� �������������� ��� �� ����� � �������� AY(0,1,0), 
������� ������� ����������� ����� ��� Y, �� ���� �� �������. ������ ���� ������� 
����� ��������� ��������� ��������� (���������) ����������� ���������� ����������� 
���������������� ���� �� �����. �.�. ����������� ������ ������� ����� ����� 1.0 / PEW/NS.

9)	��������� ��������� ��������������. ��� ���������, ��� ���������������� ��� �� 
�����������, ��������� ����� ���������������� �������� ��� �������, ������ ����������� 
������ sin(phi) � ������� n, ��� n ����� 1 ��� 2, � phi � ���� ����� ��������� ���� � 
�������� ������� AX, AY ��� AZ. ���������� ������ cos(phi) ����� ��������� ������������ 
AL �������� ���� L � �������� ������� A (ax,ay,az). 
��������� AL = |A|*|L|* cos(phi) = ax*(x-xi) + ay*(y-yi) + az*(z-zi). 
������ (����, ��� |A| = 1): cos(phi) = (ax*(x-xi) + ay*(y-yi) + az*(z-zi)) / |L|.

����������� ����������������� ���� ��������� ���������� ����� ��������� 
������������� ������������� �������� ����������� � ������������. 
�� �� ��� ����������� ���������� ������ ����������� ��������� ������ �����.



��������� ��������� ������������� �������� ���������� ������ ������ 
��� ���������� ��� �������-���������������� ���������� ������� (IDX IDY IDZ).

�� ��� ����� �������� ������� ����� ����� ��������� �������� 
�������� ��������, ��� ��� �������� (���� ��� �� ��������, 
�� ��� ��������� �������� ������������ �� ������ ������� ����) 
�������������� �������������� �� ��� �������-���������������� 
���������� ������� (IDX IDY IDZ) � ��� �������-���������������� 
���������� �������� (IHX IHY IHZ). ������� �� � ���� ������� 
�������� ������ ����� ������ ������������� � ������������ ������ 
������ ���������� �������� (IHX IHY IHZ), � ������� �� ��� � 
��������� ���������� ���������� ������� ����������� �������-���������������.

��� ������ �����������, ��� �� ����� ���� � ����� ���������� ��������.

��������� �������������� ����������� �������?

��������� �������������� ���� ����������� � ������������ ��������?



	*/
	double 
		xi,yi,zi, 

		rx, rx2, 
		ry, ry2, 
		rz, rz2,

		len, phi, 

		phi_k, value;
	long j,p,r,C,i;
	long signal_len = X.size(); // ����� ������� 

	int a; //����� ������ 
	//AX(1,0,0),		a = 0
	//AY(0,1,0)			a = 1
	//� AZ(0,0,1)		a = 2

	// ������� ��������� �������������� ��������
	//int pw_dnp = 2;

    //����������� ��������, ������� �������� � �������� ������ ������    
	//double min_value = 0.03;
	//double min_value = 1e-16;

	//double k_phi_max = (PI/2.0)/atan(1.0/2.0*k);

	double k1 = 1.0;
	printf("Filling of matrix\n");
	// ��������� ������� ��������� ������ ������, 
	// ����� ����� ����� ��������� ����� �������, 
	// �.�. �� ���� �������� ������ ������ ��� �Ш� �����
	// (��� ��������� ����� ���������� �������� - 
	// ���������� �������� �� ����� ���, ��� �����, �� ������ �������)
	// �� ���� ��������� ������� ������������� ��������� 
	// ���������� ���������������� �������
	// �� ������ ��������� ����� �������� ��������� (������) �� ��������
	// �� ������� AX(1,0,0), AY(0,1,0) � AZ(0,0,1) 

	// �������� ������� �������� ���� ��� ������� ����������� �� ������� delta_z
	double z_min = z0 - pages * delta_z;

	double sum_operator_value_x = 0.0;
	double sum_operator_value_y = 0.0;
	double sum_operator_value_z = 0.0;
	double hi, w, sum_operator_z_per_xy;
	if (m && R) // ���� ���� �������, ����� � �� (� ����������� ������)
	{
		//(*m).resize(signal_len * 3);
		//template <class T> T ***Alloc3DMat (size_t npages, size_t nrows, size_t ncols) 

		*m = Alloc3DMat<double>(3, signal_len, rows * cols * pages);
		*R = Alloc3DMat<double>(3, signal_len, rows * cols * pages);

		for (a = 0; a < 3; a++)// ���������� 3 ������
		{
			//int ax = a == 0;
			//int ay = a == 1;
			//int az = a == 2;
			for (j = 0; j < signal_len; j++)
			{
				double ax = A[a][j].ax;
				double ay = A[a][j].ay;
				double az = A[a][j].az;

				printf("Filling of matrix %ld %ld a=%d ax=%f ay=%f az=%f\n", j + a * signal_len, signal_len * 3, a, ax, ay, az);		


				int putted_in_row = 0;
				
				for (p = 0; p < pages; p++)
				{						
				//printf("Filling of matrix \t%ld %ld     %d\n", p, pages, putted_in_row);

				
					//zi = z0 - p * delta_z;// ��� �������!!!
					// �������� ������� �������� ���� ��� ������� ����������� �� ������� delta_z
					//zi = z0 - (p+1) * delta_z;
					zi = z_min + p * delta_z;

					hi = z0 - zi; w = spm.Apply(hi);

					rz = (Z[j]-zi);
					rz2 = rz * rz;

					//����� ���� ����, �� ������� ���������� ���������
					double part_of_len = (z0 - zi) / rz;
					
					for (r = 0; r < rows; r++)
					{
						
						yi = y0 + r * delta_y;
						ry = Y[j]-yi;
						ry2 = ry*ry;
						
						for (C = 0; C < cols; C++)
						{
							// ������ � ������ ������� ��������� ������ ������
							i = p * rows * cols + r * cols + C;
							// ���������� �������������� ���������
							xi = x0 + C * delta_x;
							rx = (X[j]-xi);
							rx2 = rx * rx;
							// ���������� �� �������������� ���������
							// �� �������� �� �������
							len = sqrt(
								rx2 + 
								ry2 + 
								rz2 
								);

							// ���� ����� ������������ �� �������� � �������� � ������
							//phi = acos((ax*rx + ay*ry + az*rz) / len);
							// ����������� ������ ��������� �������������� nju_fi
							//phi_k = pow(sin(phi), pw_dnp);
							// 
							if (wave_type == 1)	k1 = (1.0 / pow(len, pw_dnp));
							value = k1 * exp ( - k_oslablenie * pw_dnp * part_of_len * len);
							//value = k1 * phi_k;
							//if (fabs(value) > min_value)
							{
								//if (value == 0.0)
								//{
								//	value = DBL_MIN;
								//}

								// ���������� �������� � ����������� ������
								//(*m)[j].put(i, value);
								(*m)[a][j][i] = value;
								(*R)[0][j][i] = rx;
								(*R)[1][j][i] = ry;
								(*R)[2][j][i] = rz;

								putted_in_row++;

								sum_operator_value_x += ax * value * w;
								sum_operator_value_y += ay * value * w;
								sum_operator_value_z += az * value * w;
							}

						}
					}
				}
			}
		}
	}


	printf("sum_operator_value_x = %e\n", sum_operator_value_x);
	printf("sum_operator_value_y = %e\n", sum_operator_value_y);
	printf("sum_operator_value_z = %e\n", sum_operator_value_z);

	sum_operator_z_per_xy = 2. * sum_operator_value_z / (sum_operator_value_x + sum_operator_value_y);
	printf("sum_operator_z_per_xy = %f\n", sum_operator_z_per_xy);
}














bool FillingTheMatrix3D_with_napravlennosty_diagramm(
					  double k_oslablenie,// ����������� ����������
					  char * filename,
					  double **** m,// ��������� �� ��� ������� njuX, njuY, njuZ
					  long rows, long cols, long pages,
					  double x0, double y0, double z0,
					  double delta_x, double delta_y, double delta_z,
					  vector<double> & X,
					  vector<double> & Y,
					  vector<double> & Z,
					  vector<vector<anten_direction> > & A,
	double pw_dnp,// ������� ��������� �������������� ��������
	double min_value,
	int wave_type,
	sourse_power_model spm
					  )
{

	/*
������ � �������� ������ � �����

1)	����������� �������� ������ X, Y � Z �������� ��� ������� �������: 
AX(1,0,0), AY(0,1,0) � AZ(0,0,1) ��������������.
2)	���������� ��������� ��������� xi, yi, zi
3)	��� �������� W
4)	��� ��������� ����������� ������� ���������� �������� ���������� ��������� ������� ������������ ����������� ����������� ���������� ���� � ��� ��������� ���������� PEW/NS. 
5)	���������� ��������� ��������� x, y, z
6)	�������� ������ ���� �� ��������� � ����� ��������� L (x-xi, y-yi, z-zi)
7)	������ ������� ���� |L| ��� ����������, ���������� ��������
8)	���������� ������� ��������� ����� ����������� ���������� k_oslablenie : exp ( - k_oslablenie * |L|)

����� ������� ��� ������������ ������ �������, �������� ��������� �������������� ������ � ��������� 
����������� ����������������� ����. ��������� ����������� ���������� �� ������� ������������ 
��������� ����������� ���������� ����, ����������� �� �����. 

��������, ��� �� ����� �� ��������� ��������� xi, yi, zi 
���������������� ����� ����� �����������, � ������� ������� AZ(0,0,1) 
���� ����������� �����������. ����� ���������������� �������� ��� ��������� ����� 
(��������� ���������� ������ ������� ��������), ��������� �������� ������������ 
���������� ���� ���������������� ���� � ���� �������������� ������ �� ����� 
���������� ������, ������� ����������� ������ ������� ����� ����� ����. 

���������� �������������� ���� �� ����� � �������� AX(1,0,0), 
������� ������� ����������� ����� ��� X, �� ���� �� ������. ������ 
���� ������� ����� ��������� (��� ������ �����) ��������� ������� (��������) 
����������� ���������� ����������� ���������������� ���� �� �����. �.�. 
����������� ������ ������� ����� ����� �������� ���������� ���������� 
�����������, �.�. PEW/NS.

������ ���������� �������������� ��� �� ����� � �������� AY(0,1,0), 
������� ������� ����������� ����� ��� Y, �� ���� �� �������. ������ ���� ������� 
����� ��������� ��������� ��������� (���������) ����������� ���������� ����������� 
���������������� ���� �� �����. �.�. ����������� ������ ������� ����� ����� 1.0 / PEW/NS.

9)	��������� ��������� ��������������. ��� ���������, ��� ���������������� ��� �� 
�����������, ��������� ����� ���������������� �������� ��� �������, ������ ����������� 
������ sin(phi) � ������� n, ��� n ����� 1 ��� 2, � phi � ���� ����� ��������� ���� � 
�������� ������� AX, AY ��� AZ. ���������� ������ cos(phi) ����� ��������� ������������ 
AL �������� ���� L � �������� ������� A (ax,ay,az). 
��������� AL = |A|*|L|* cos(phi) = ax*(x-xi) + ay*(y-yi) + az*(z-zi). 
������ (����, ��� |A| = 1): cos(phi) = (ax*(x-xi) + ay*(y-yi) + az*(z-zi)) / |L|.

����������� ����������������� ���� ��������� ���������� ����� ��������� 
������������� ������������� �������� ����������� � ������������. 
�� �� ��� ����������� ���������� ������ ����������� ��������� ������ �����.



��������� ��������� ������������� �������� ���������� ������ ������ 
��� ���������� ��� �������-���������������� ���������� ������� (IDX IDY IDZ).

�� ��� ����� �������� ������� ����� ����� ��������� �������� 
�������� ��������, ��� ��� �������� (���� ��� �� ��������, 
�� ��� ��������� �������� ������������ �� ������ ������� ����) 
�������������� �������������� �� ��� �������-���������������� 
���������� ������� (IDX IDY IDZ) � ��� �������-���������������� 
���������� �������� (IHX IHY IHZ). ������� �� � ���� ������� 
�������� ������ ����� ������ ������������� � ������������ ������ 
������ ���������� �������� (IHX IHY IHZ), � ������� �� ��� � 
��������� ���������� ���������� ������� ����������� �������-���������������.

��� ������ �����������, ��� �� ����� ���� � ����� ���������� ��������.

��������� �������������� ����������� �������?

��������� �������������� ���� ����������� � ������������ ��������?



	*/
	double xi,yi,zi, len, phi, Zj_zi, Zj_zi2, Yj_yi2, phi_k, value;
	long j,p,r,C,i;
	long signal_len = X.size(); // ����� ������� 

	int a; //����� ������ 
	//AX(1,0,0),		a = 0
	//AY(0,1,0)			a = 1
	//� AZ(0,0,1)		a = 2

	// ������� ��������� �������������� ��������
	//int pw_dnp = 2;

    //����������� ��������, ������� �������� � �������� ������ ������    
	//double min_value = 0.03;
	//double min_value = 1e-16;

	//double k_phi_max = (PI/2.0)/atan(1.0/2.0*k);

	double k1 = 1.0;
	printf("Filling of matrix\n");
	// ��������� ������� ��������� ������ ������, 
	// ����� ����� ����� ��������� ����� �������, 
	// �.�. �� ���� �������� ������ ������ ��� �Ш� �����
	// (��� ��������� ����� ���������� �������� - 
	// ���������� �������� �� ����� ���, ��� �����, �� ������ �������)
	// �� ���� ��������� ������� ������������� ��������� 
	// ���������� ���������������� �������
	// �� ������ ��������� ����� �������� ��������� (������) �� ��������
	// �� ������� AX(1,0,0), AY(0,1,0) � AZ(0,0,1) 

	// �������� ������� �������� ���� ��� ������� ����������� �� ������� delta_z
	double z_min = z0 - pages * delta_z;

	double sum_operator_value_x = 0.0;
	double sum_operator_value_y = 0.0;
	double sum_operator_value_z = 0.0;
	double hi, w, sum_operator_z_per_xy;
	if (m) // ���� ���� �������, ����� � �� (� ����������� ������)
	{
		//(*m).resize(signal_len * 3);
		//template <class T> T ***Alloc3DMat (size_t npages, size_t nrows, size_t ncols) 

		*m = Alloc3DMat<double>(3, signal_len, rows * cols * pages);

		for (a = 0; a < 3; a++)// ���������� 3 ������
		{
			//int ax = a == 0;
			//int ay = a == 1;
			//int az = a == 2;
			for (j = 0; j < signal_len; j++)
			{
				double ax = A[a][j].ax;
				double ay = A[a][j].ay;
				double az = A[a][j].az;

				printf("Filling of matrix %ld %ld a=%d ax=%f ay=%f az=%f\n", j + a * signal_len, signal_len * 3, a, ax, ay, az);		


				int putted_in_row = 0;
				
				for (p = 0; p < pages; p++)
				{						
				//printf("Filling of matrix \t%ld %ld     %d\n", p, pages, putted_in_row);
					
					//zi = z0 - p * delta_z;// ��� �������!!!
					// �������� ������� �������� ���� ��� ������� ����������� �� ������� delta_z
					//zi = z0 - (p+1) * delta_z;
					zi = z_min + p * delta_z;
					hi = z0 - zi; w = spm.Apply(hi);

					Zj_zi = (Z[j]-zi);
					Zj_zi2 = Zj_zi * Zj_zi;

					//����� ���� ����, �� ������� ���������� ���������
					double part_of_len = (z0 - zi) / Zj_zi;
					
					for (r = 0; r < rows; r++)
					{
						
						yi = y0 + r * delta_y;
						Yj_yi2 = (Y[j]-yi)*(Y[j]-yi);
						
						for (C = 0; C < cols; C++)
						{
							// ������ � ������ ������� ��������� ������ ������
							i = p * rows * cols + r * cols + C;
							// ���������� �������������� ���������
							xi = x0 + C * delta_x;
							// ���������� �� �������������� ���������
							// �� �������� �� �������
							len = sqrt(
								(X[j]-xi)*(X[j]-xi) + 
								Yj_yi2 + 
								Zj_zi2 
								);
	#if 1
							// ���� ����� ������������ �� �������� � �������� � ������
							phi = acos((ax*(X[j]-xi) + ay*(Y[j]-yi) + az*(Z[j]-zi)) / len);
							// ����������� ������ ��������� �������������� nju_fi
							phi_k = pow(sin(phi), pw_dnp);
							// 
							if (wave_type == 1)	k1 = (1.0 / pow(len, pw_dnp));
							value = k1 * exp ( - k_oslablenie * pw_dnp * part_of_len * len) * phi_k;
							//value = k1 * phi_k;
							//if (fabs(value) > min_value)
							{
								//if (value == 0.0)
								//{
								//	value = DBL_MIN;
								//}

								// ���������� �������� � ����������� ������
								//(*m)[j].put(i, value);
								(*m)[a][j][i] = value;
								putted_in_row++;

								sum_operator_value_x += ax * value * w;
								sum_operator_value_y += ay * value * w;
								sum_operator_value_z += az * value * w;
							}
	#else
							// ���� ����������� �� ��������
							phi = acos (Zj_zi / len);
							// ��������� ������� �����������
							k_phi = k_phi_max * phi;
							if (fabs(k_phi) > PI) k_phi = 0.0;
							// ������ ��������� �������� ������������
							phi_k = pow(sin(k_phi), smoof_power);
							if (phi_k > 0.1)
							{
								// ���������� �������� � ����������� ������
								(*m)[j].put(i, k1 * exp ( - k_oslablenie * part_of_len * len) * phi_k);
								putted_in_row++;
							}
	#endif
						}
					}
				}
			}
		}
	}
	else
	{
		AFile f;
		if( !f.Open( filename, GENERIC_WRITE, TRUNCATE_EXISTING) ) 
		{
			if( !f.Open( filename, GENERIC_WRITE, CREATE_NEW) ) 
			{
				MessageBox(0, "Filling the matrix 3D with napravlennosty diagramm\nUnable to open file" , filename, MB_OK);
				return false;
			}
		}			
		char buff[BUFF_SIZE];
		Archive ar( &f, Archive::store, BUFF_SIZE, buff );

		// ���������� ����������� �������
		//ar << rows; 
		//ar << cols;
		ar << signal_len * 3;
		long rows_cols_pages = pages * rows * cols;
		ar << rows_cols_pages;

		// � ������ ���� ������� - ���������!!

		/*for (long r = 0; r < rows; r++)
		{
			ar << m[r];
		}*/
		for (a = 0; a < 3; a++)// ���������� 3 ������
		{
			//int ax = a == 0;
			//int ay = a == 1;
			//int az = a == 2;
			for (j = 0; j < signal_len; j++)
			{
				double ax = A[a][j].ax;
				double ay = A[a][j].ay;
				double az = A[a][j].az;

				printf("Filling of matrix %ld %ld a=%d ax=%f ay=%f az=%f\n", j + a * signal_len, signal_len * 3, a, ax, ay, az);		

			
				for (p = 0; p < pages; p++)
				{						
					
					//zi = z0 - p * delta_z;// ��� �������!!!
					// �������� ������� �������� ���� ��� ������� ����������� �� ������� delta_z
					//zi = z0 - (p+1) * delta_z;
					zi = z_min + p * delta_z;
					hi = z0 - zi; w = spm.Apply(hi);
					
					Zj_zi = (Z[j]-zi);
					Zj_zi2 = Zj_zi * Zj_zi;
					
					//����� ���� ����, �� ������� ���������� ���������
					double part_of_len = (z0 - zi) / Zj_zi;

					for (r = 0; r < rows; r++)
					{
						
						yi = y0 + r * delta_y;
						Yj_yi2 = (Y[j]-yi)*(Y[j]-yi);
						
						for (C = 0; C < cols; C++)
						{
							// ������ � ������ ������� ��������� ������ ������
							i = p * rows * cols + r * cols + C;
							// ���������� �������������� ���������
							xi = x0 + C * delta_x;
							// ���������� �� �������������� ���������
							// �� �������� �� �������
							len = sqrt(
								(X[j]-xi)*(X[j]-xi) + 
								Yj_yi2 + 
								Zj_zi2 
								);
	#if 1
							// ���� ����� ������������ �� �������� � �������� � ������
							phi = acos((ax*(X[j]-xi) + ay*(Y[j]-yi) + az*(Z[j]-zi)) / len);
							// ����������� ������ ��������� ��������������
							phi_k = pow(sin(phi), pw_dnp);
							// 
							if (wave_type == 1)	k1 = (1.0 / pow(len, pw_dnp));
							//value = k1 * exp ( - k_oslablenie * pw_dnp * part_of_len * len) * phi_k;
							value = k1 * phi_k;
							//if (fabs(value) > min_value)
							{
								// ���������� �������� � ����������� ������
								///(*m)[j].put(i, K);
								ar << i;
								ar << value;

								sum_operator_value_x += ax * value * w;
								sum_operator_value_y += ay * value * w;
								sum_operator_value_z += az * value * w;
							}
	#else
							// ���� ����������� �� ��������
							phi = acos (Zj_zi / len);
							// ��������� ������� �����������
							k_phi = k_phi_max * phi;
							if (fabs(k_phi) > PI) k_phi = 0.0;
							// ������ ��������� �������� ������������
							phi_k = pow(sin(k_phi), smoof_power);
							if (phi_k > 0.1)
							{
								// ���������� �������� � ����������� ������
								//(*m)[j].put(i, k1 * exp ( - k2 * part_of_len * len) * phi_k);
								if (wave_type == 1)	k1 = (1.0 / pow(len, pw_dnp));
								value = k1 * exp ( - k_oslablenie * pw_dnp * part_of_len * len) * phi_k;
								ar << i;
								ar << value;
							}
	#endif
						}
					}
				}
				//������� ����� ������ ������
				i = -1;
				value = 0.0;
				ar << i;
				ar << value;
			}
		}
		ar.Close();
		f.Close();
	}
	printf("sum_operator_value_x = %e\n", sum_operator_value_x);
	printf("sum_operator_value_y = %e\n", sum_operator_value_y);
	printf("sum_operator_value_z = %e\n", sum_operator_value_z);

	sum_operator_z_per_xy = 2. * sum_operator_value_z / (sum_operator_value_x + sum_operator_value_y);
	printf("sum_operator_z_per_xy = %f\n", sum_operator_z_per_xy);
	return true;

}








bool FillingTheMatrix3D(double smoof_power,
					  double k_oslablenie,// ����������� ����������
					  double k, // ��������� ������� ��������� � ������ (��� �����) ����� ��������
					  vector<SparseRow> * m,
					  char * filename,
					  long rows, long cols, long pages,
					  double x0, double y0, double z0,
					  double delta_x, double delta_y, double delta_z,
					  vector<double> & X,
					  vector<double> & Y,
					  vector<double> & Z,
					  double pw_dnp,
					  int wave_type
					  )
{
	double xi,yi,zi, len, phi, Zj_zi, Zj_zi2, Yj_yi2, k_phi, phi_k, value;
	long j,p,r,C,i;
	long signal_len = X.size(); // ����� ������� 

	double k_phi_max = (PI/2.0)/atan(1.0/2.0*k);

	double k1 = 1.0;
	printf("Filling of matrix\n");
	// ��������� ������� ��������� ������ ������, 
	// ����� ����� ����� ����� ������� 
	// (��� ��������� ����� ���������� �������� - 
	// ���������� �������� �� ����� ���, ��� �����, �� ������ �������)
	// �� ���� ��������� ������� ������������� ��������� 
	// ���������� ���������������� �������
	// �� ������ ��������� ����� �������� ��������� (������) �� ��������

	// �������� ������� �������� ���� ��� ������� ����������� �� ������� delta_z
	double z_min = z0 - pages * delta_z;


	if (m) // ���� ���� �������, ����� � �� (� ����������� ������)
	{
		(*m).resize(signal_len);
		for (j = 0; j < signal_len; j++)
		{
			printf("Filling of matrix %ld %ld\n", j, signal_len);		


			int putted_in_row = 0;
			
			for (p = 0; p < pages; p++)
			{						
			//printf("Filling of matrix \t%ld %ld     %d\n", p, pages, putted_in_row);
				
				//zi = z0 - p * delta_z;// ��� �������!!!
				// �������� ������� �������� ���� ��� ������� ����������� �� ������� delta_z
				//zi = z0 - (p+1) * delta_z;
				zi = z_min + p * delta_z;
				//hi = z0 - zi; w = w0 + hi * w1 + hi * hi * w2;

				Zj_zi = (Z[j]-zi);
				Zj_zi2 = Zj_zi * Zj_zi;
				
				//����� ���� ����, �� ������� ���������� ���������
				double part_of_len = (z0 - zi) / Zj_zi;

				for (r = 0; r < rows; r++)
				{
					
					yi = y0 + r * delta_y;
					Yj_yi2 = (Y[j]-yi)*(Y[j]-yi);
					
					for (C = 0; C < cols; C++)
					{
						// ������ � ������ ������� ��������� ������ ������
						i = p * rows * cols + r * cols + C;
						// ���������� �������������� ���������
						xi = x0 + C * delta_x;
						// ���������� �� �������������� ���������
						// �� �������� �� �������
						len = sqrt(
							(X[j]-xi)*(X[j]-xi) + 
							Yj_yi2 + 
							Zj_zi2 
							);
						// ���� ����������� �� ��������
						phi = acos (Zj_zi / len);
						// ��������� ������� �����������
						k_phi = k_phi_max * phi;
						if (fabs(k_phi) > PI) k_phi = 0.0;
						// ������ ��������� �������� ������������
						phi_k = pow(sin(k_phi), smoof_power);
						if (phi_k > 0.1)
						{
							// ���������� �������� � ����������� ������
							if (wave_type == 1)	k1 = (1.0 / pow(len, pw_dnp));
							(*m)[j].put(i, k1 * exp ( - k_oslablenie * pw_dnp * part_of_len * len) * phi_k);
							putted_in_row++;
						}
					}
				}
			}
		}
	}
	else
	{
		AFile f;
		if( !f.Open( filename, GENERIC_WRITE, TRUNCATE_EXISTING) ) 
		{
			if( !f.Open( filename, GENERIC_WRITE, CREATE_NEW) ) 
			{
				MessageBox(0, "Filling the matrix 3D\nUnable to open file" , filename, MB_OK);
				return false;
			}
		}			
		char buff[BUFF_SIZE];
		Archive ar( &f, Archive::store, BUFF_SIZE, buff );

		// ���������� ����������� �������
		//ar << rows; 
		//ar << cols;
		ar << signal_len;
		long rows_cols_pages = pages * rows * cols;
		ar << rows_cols_pages;

		// � ������ ���� ������� - ���������!!

		/*for (long r = 0; r < rows; r++)
		{
			ar << m[r];
		}*/
		for (j = 0; j < signal_len; j++)
		{
			printf("Filling of matrix %ld %ld\n", j, signal_len);	

		
			for (p = 0; p < pages; p++)
			{						
				
				//zi = z0 - p * delta_z;// ��� �������!!!
				// �������� ������� �������� ���� ��� ������� ����������� �� ������� delta_z
				//zi = z0 - (p+1) * delta_z;
				zi = z_min + p * delta_z;
				//hi = z0 - zi; w = w0 + hi * w1 + hi * hi * w2;

				Zj_zi = (Z[j]-zi);
				Zj_zi2 = Zj_zi * Zj_zi;
				
				//����� ���� ����, �� ������� ���������� ���������
				double part_of_len = (z0 - zi) / Zj_zi;

				for (r = 0; r < rows; r++)
				{
					
					yi = y0 + r * delta_y;
					Yj_yi2 = (Y[j]-yi)*(Y[j]-yi);
					
					for (C = 0; C < cols; C++)
					{
						// ������ � ������ ������� ��������� ������ ������
						i = p * rows * cols + r * cols + C;
						// ���������� �������������� ���������
						xi = x0 + C * delta_x;
						// ���������� �� �������������� ���������
						// �� �������� �� �������
						len = sqrt(
							(X[j]-xi)*(X[j]-xi) + 
							Yj_yi2 + 
							Zj_zi2 
							);
						// ���� ����������� �� ��������
						phi = acos (Zj_zi / len);
						// ��������� ������� �����������
						k_phi = k_phi_max * phi;
						if (fabs(k_phi) > PI) k_phi = 0.0;
						// ������ ��������� �������� ������������
						phi_k = pow(sin(k_phi), smoof_power);
						if (phi_k > 0.1)
						{
							// ���������� �������� � ����������� ������
							//(*m)[j].put(i, k1 * exp ( - k2 * len) * phi_k);
							if (wave_type == 1)	k1 = (1.0 / pow(len, pw_dnp));
							value = k1 * exp ( - k_oslablenie * pw_dnp * part_of_len * len) * phi_k;
							ar << i;
							ar << value;
						}
					}
				}
			}
			//������� ����� ������ ������
			i = -1;
			value = 0.0;
			ar << i;
			ar << value;
		}
		ar.Close();
		f.Close();
	}
}





void FillingTheMatrix3D_(double smoof_power,
					  double k_oslablenie,// ����������� ����������
					  double k, // ��������� ������� ��������� � ������ (��� �����) ����� ��������
					  vector<sparse_row>& m,
					  vector<double>& b,
					  long rows, long cols, long pages,
					  double x0, double y0, double z0,
					  double delta_x, double delta_y, double delta_z,
					  vector<double> & X,
					  vector<double> & Y,
					  vector<double> & Z,
					  vector<double> & signal)
{
	double xi,yi,zi, len, phi, Zj_zi, Zj_zi2, Yj_yi2, phi_k;
	long j,p,r,C,i, ip, ir, iC, ic;
	long signal_len = signal.size(); // ����� ������� 

	double k_phi_max = (PI/2.0)/atan(1.0/2.0*k);

	double k1 = 1.0;

	vector<long> vp(pages), vr(rows), vc(cols);
	
	index_for_sort * vip  = new index_for_sort[pages];
	for (ip = 0; ip < pages; ip++)
	{
		vip[ip].i = ip;
		vip[ip].sort_val = rand();
	}
	qsort( (void *)vip, (size_t)pages, sizeof(index_for_sort), compare_index_for_sort );
	for (ip = 0; ip < pages; ip++)
	{
		vp[ip] = vip[ip].i;
	}
	delete [] vip;

	index_for_sort * vir  = new index_for_sort[rows];
	for (ir = 0; ir < rows; ir++)
	{
		vir[ir].i = ir;
		vir[ir].sort_val = rand();
	}
	qsort( (void *)vir, (size_t)rows, sizeof(index_for_sort), compare_index_for_sort );
	for (ir = 0; ir < rows; ir++)
	{
		vr[ir] = vir[ir].i;
	}
	delete [] vir;

	index_for_sort * vic  = new index_for_sort[cols];
	for (ic = 0; ic < cols; ic++)
	{
		vic[ic].i = ic;
		vic[ic].sort_val = rand();
	}
	qsort( (void *)vic, (size_t)cols, sizeof(index_for_sort), compare_index_for_sort );
	for (ic = 0; ic < cols; ic++)
	{
		vc[ic] = vic[ic].i;
	}
	delete [] vic;

	printf("Filling of matrix\n");
	// ��������� ������� ��������� ������ ������, 
	// ����� ����� ����� ����� ������� 
	// (��� ��������� ����� ���������� �������� - 
	// ���������� �������� �� ����� ���, ��� �����, �� ������ �������)
	// �� ���� ��������� ������� ������������� ��������� 
	// ���������� ���������������� �������
	// �� ������ ��������� ����� �������� ��������� (������) �� ��������
	m.resize(signal_len);
	b.resize(signal_len);
	for (j = 0; j < signal_len; j++)
	{
		printf("Filling of matrix %ld %ld\n", j, signal_len);		


		int putted_in_row = 0;
		
		for (ip = 0; ip < pages; ip++)
		{			
			p = vp[ip];
		//printf("Filling of matrix \t%ld %ld     %d\n", p, pages, putted_in_row);
			
			//zi = z0 - p * delta_z;// ��� �������!!!
			// �������� ������� �������� ���� ��� ������� ����������� �� ������� delta_z
			zi = z0 - (p+1) * delta_z;

			Zj_zi = (Z[j]-zi);
			Zj_zi2 = Zj_zi * Zj_zi;

			//����� ���� ����, �� ������� ���������� ���������
			double part_of_len = (z0 - zi) / Zj_zi;

			
			for (ir = 0; ir < rows; ir++)
			{
				r = vr[ir];
				
				yi = y0 + r * delta_y;
				Yj_yi2 = (Y[j]-yi)*(Y[j]-yi);
				
				for (iC = 0; iC < cols; iC++)
				{
					C = vc[iC];
					// ������ � ������ ������� ��������� ������ ������
					i = p * rows * cols + r * cols + C;
					// ���������� �������������� ���������
					xi = x0 + C * delta_x;
					// ���������� �� �������������� ���������
					// �� �������� �� �������
					len = sqrt(
						(X[j]-xi)*(X[j]-xi) + 
						Yj_yi2 + 
						Zj_zi2 
						);
					// ���� ����������� �� ��������
					phi = acos (Zj_zi / len);
					// ������ ��������� �������� ������������
					phi_k = pow(sin(k_phi_max * phi), smoof_power);
					if (phi_k > 0.1)
					{
						// ���������� �������� � ����������� ������
						m[j].put(i, k1 * exp ( - k_oslablenie * part_of_len * len) * phi_k);
						putted_in_row++;
					}
				}
			}
		}

		b[j] = signal[j];
	}
}





bool StoringTheMatrix(vector<SparseRow>& m, long cols)
{
	char buff[BUFF_SIZE];
	char filename[4096];
	TCHAR filter[] =     
		TEXT("Sparse Martix File (*.smf)\0*.smf\0")
		TEXT("All Files (*.*)\0*.*\0");
	sprintf(filename, "\0");
	DWORD nFilterIndex = 0;
	if (SaveFileDlg(0, filename, filter, nFilterIndex) == S_OK)
	{
		AFile f;
		if( !f.Open( filename, GENERIC_WRITE, TRUNCATE_EXISTING) ) 
		{
			if( !f.Open( filename, GENERIC_WRITE, CREATE_NEW) ) 
			{
				MessageBox(0, "Storing the matrix\nUnable to open file" , filename, MB_OK);
				return false;
			}
		}
		Archive ar( &f, Archive::store, BUFF_SIZE, buff );

		long rows = m.size();

		ar << rows;
		ar << cols;

		for (long r = 0; r < rows; r++)
		{
			ar << m[r];
		}
		ar.Close();
		f.Close();

	}
	return true;
}
bool StoringTheMatrix(vector<sparse_row>& m, long cols)
{
	char buff[BUFF_SIZE];
	char filename[4096];
	TCHAR filter[] =     
		TEXT("Sparse Martix File (*.smf)\0*.smf\0")
		TEXT("All Files (*.*)\0*.*\0");
	sprintf(filename, "\0");
	DWORD nFilterIndex = 0;
	if (SaveFileDlg(0, filename, filter, nFilterIndex) == S_OK)
	{
		AFile f;
		if( !f.Open( filename, GENERIC_WRITE, TRUNCATE_EXISTING) ) 
		{
			if( !f.Open( filename, GENERIC_WRITE, CREATE_NEW) ) 
			{
				MessageBox(0, "Storing the matrix\nUnable to open file" , filename, MB_OK);
				return false;
			}
		}
		Archive ar( &f, Archive::store, BUFF_SIZE, buff );

		long rows = m.size();

		ar << rows;
		ar << cols;

		for (long r = 0; r < rows; r++)
		{
			ar << m[r];
		}
		ar.Close();
		f.Close();

	}
	return true;
}
void LoadingTheMatrix(vector<SparseRow>& m, long & cols)
{
	char buff[BUFF_SIZE];
	char filename[4096];
	TCHAR filter[] =     
		TEXT("Sparse Martix File (*.smf)\0*.smf\0")
		TEXT("All Files (*.*)\0*.*\0");
	sprintf(filename, "\0");
	if (OpenFileDlg(0, filter, filename) == S_OK)
	{
		AFile f;
		if( f.Open( filename, GENERIC_READ, OPEN_EXISTING) ) 
		{
			Archive ar( &f, Archive::load, BUFF_SIZE, buff );
			try
			{
				//ar.ReadString(str2, 255);
				//ar.Read((unsigned char*)m2,sizeof(m2));
				long _cols, _rows;
				ar >> _rows;
				ar >> _cols;

				m.resize(_rows);
				for (long r = 0; r < _rows; r++)
				{
					ar >> m[r];
				}
				cols = _cols;
			}
			catch(char * str)
			{
				MessageBox(0,str,"",0);
			}
			catch (CException* pe)
			{
				// catch errors from WinINet 
				TCHAR szErr[4098]; 
				pe->GetErrorMessage(szErr, 4098); 
				AfxMessageBox(szErr);
				pe->Delete();
			}
			catch(...)
			{
				MessageBox(0,"unknown error of archive read","",0);
			}
			
			ar.Close();
			f.Close();
		}
		else
		{
			MessageBox(0, "Loas The Matrix\nUnable to open file" , filename, MB_OK);
		}

	}
}
bool StoreMatrixHeader(char * filename, long rows, long cols, bool ByColomns)
{
	if (rows <= 0)
	{
		return false;
	}
	if (cols <= 0)
	{
		return false;
	}

	AFile f;
	if( !f.Open( filename, GENERIC_WRITE, TRUNCATE_EXISTING) ) 
	{
		if( !f.Open( filename, GENERIC_WRITE, CREATE_NEW) ) 
		{
			MessageBox(0, "Store Matrix Header\nUnable to open file" , filename, MB_OK);
			return false;
		}
	}
	char buff[BUFF_SIZE];
	Archive ar( &f, Archive::store, BUFF_SIZE, buff );

	ar << rows;
	ar << cols;
	ar << ByColomns;

	ar.Close();
	f.Close();
	return true;
}
bool StoreMatrixHeader(char * filename, long rows, long cols)
{
	if (rows <= 0)
	{
		return false;
	}
	if (cols <= 0)
	{
		return false;
	}

	AFile f;
	if( !f.Open( filename, GENERIC_WRITE, TRUNCATE_EXISTING) ) 
	{
		if( !f.Open( filename, GENERIC_WRITE, CREATE_NEW) ) 
		{
			MessageBox(0, "Store Matrix Header\nUnable to open file" , filename, MB_OK);
			return false;
		}
	}
	char buff[BUFF_SIZE];
	Archive ar( &f, Archive::store, BUFF_SIZE, buff );

	ar << rows;
	ar << cols;

	ar.Close();
	f.Close();
	return true;
}
bool StoreMatrix(char * filename, vector<vector<double> > & m, bool ByColomns)
{
	long rows = m.size();
	if (rows <= 0)
	{
		return false;
	}
	long cols = m[0].size();
	if (cols <= 0)
	{
		return false;
	}

	AFile f;
	if( !f.Open( filename, GENERIC_WRITE, TRUNCATE_EXISTING) ) 
	{
		if( !f.Open( filename, GENERIC_WRITE, CREATE_NEW) ) 
		{
			MessageBox(0, "Store Matrix\nUnable to open file" , filename, MB_OK);
			return false;
		}
	}
	char buff[BUFF_SIZE];
	Archive ar( &f, Archive::store, BUFF_SIZE, buff );

	ar << rows;
	ar << cols;
	ar << ByColomns;

	if (ByColomns)
	{
		for (long c = 0; c < cols; c++)
		{
			for (long r = 0; r < rows; r++)
			{
				ar << m[r][c];
			}
		}
	}
	else
	{
		for (long r = 0; r < rows; r++)
		{
			for (long c = 0; c < cols; c++)
			{
				ar << m[r][c];
			}
		}
	}

	ar.Close();
	f.Close();
	return true;
}
bool LoadMatrix(char * filename, vector<vector<double> > & m)
{
	bool result = false;
	AFile f;
	if( !f.Open( filename, GENERIC_READ, OPEN_EXISTING) ) 
	{
		MessageBox(0, "Load Matrix\nUnable to open file" , filename, MB_OK);
		return false;
	}

	char buff[BUFF_SIZE];
	Archive ar( &f, Archive::load, BUFF_SIZE, buff );

	try
	{
		long rows, cols;
		bool ByColomns;
		ar >> rows;
		ar >> cols;
		ar >> ByColomns;

		m.resize(rows);
		for (long r = 0; r < rows; r++)
		{
			m[r].resize(cols);
		}
		if (ByColomns)
		{
			for (long c = 0; c < cols; c++)
			{
				for (long r = 0; r < rows; r++)
				{
					ar >> m[r][c];
				}
			}
		}
		else
		{
			for (long r = 0; r < rows; r++)
			{
				for (long c = 0; c < cols; c++)
				{
					ar >> m[r][c];
				}
			}
		}

		result = true;
	}
	catch(char * str)
	{
		MessageBox(0,str,"",0);
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();
	}
	catch(...)
	{
		MessageBox(0,"unknown error of archive read","",0);
	}
	
	ar.Close();
	f.Close();

	return result;
}
bool ApplyOperator(long signal_len, 
				   long q,
				   vector<double> & sol,
				   char * filename_in, 
				   vector<vector<double> > & mw
				   )
{
	// �� ������ ������� ��������� ���������� ������ ������
	// � �������� q-��� ������� ����� �������
	// ������� ����� �������� �������� ������ ������ � ��������� �������

	bool result = false;
	AFile f;
	if( f.Open( filename_in, GENERIC_READ, OPEN_EXISTING) ) 
	{
		char buff[BUFF_SIZE];
		Archive ar( &f, Archive::load, BUFF_SIZE, buff );
		try
		{
			long _cols, _rows;
			ar >> _rows; //signal_len
			ar >> _cols;

			for (long j = 0; j < signal_len; j++)
			{
				double product = 0.0;
				size_t sol_size = sol.size();

				long cc;
				double value;
				do 
				{
					ar >> cc;
					ar >> value;
					if (cc >= 0)
					{
						if (cc < sol_size)
						{
							product += value * sol[cc];
						}
					}
					else
						break;
				}
				while(true);

				mw[j][q] = product;
			}
			result = true;
		}
		catch(char * str)
		{
			MessageBox(0,str,"",0);
		}
		catch (CException* pe)
		{
			// catch errors from WinINet 
			TCHAR szErr[4098]; 
			pe->GetErrorMessage(szErr, 4098); 
			AfxMessageBox(szErr);
			pe->Delete();
		}
		catch(...)
		{
			MessageBox(0,"unknown error of archive read","",0);
		}
		
		ar.Close();
		f.Close();
	}
	else
	{
		MessageBox(0, "Apply Operator\nUnable to open file" , filename_in, MB_OK);
		result = false;
	}
	return result;
}

bool ApplyOperator(long signal_len, 
				   vector<double> & sol,
				   char * filename_in, 
				   char * filename_out 
				   )
{
	// �� ������ ������� ��������� ���������� ������ ������
	// � �������� q-��� ������� ����� �������
	// ������� ����� �������� �������� ������ ������ � ��������� �������

	bool result = false;

	AFile f;
	if( !f.Open( filename_in, GENERIC_READ, OPEN_EXISTING) ) 
	{
		MessageBox(0, "Apply Operator\nUnable to open file" , filename_in, MB_OK);
		result = false;
	}

	char buff[BUFF_SIZE];
	Archive ar( &f, Archive::load, BUFF_SIZE, buff );
	
	AFile f2;
	if( !f2.Open( filename_out, GENERIC_WRITE, OPEN_EXISTING) ) 
	{
		MessageBox(0, "Apply Operator\nUnable to open file" , filename_out, MB_OK);
		ar.Close();
		f.Close();
		result = false;
	}	
	f2.SeekToEnd();
	
	char buff2[BUFF_SIZE];
	Archive ar2( &f2, Archive::store, BUFF_SIZE, buff2 );
	
	try
	{
		long _cols, _rows;
		ar >> _rows; //signal_len
		ar >> _cols;


		for (long j = 0; j < signal_len; j++)
		{
			double product = 0.0;
			size_t sol_size = sol.size();

			long cc;
			double value;
			do 
			{
				ar >> cc;
				ar >> value;
				if (cc >= 0)
				{
					if (cc < sol_size)
					{
						product += value * sol[cc];
					}
				}
				else
					break;
			}
			while(true);

			ar2 << product;

		}
		result = true;
	}
	catch(char * str)
	{
		MessageBox(0,str,"",0);
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();
	}
	catch(...)
	{
		MessageBox(0,"unknown error of archive read","",0);
	}
	
	ar2.Close();
	f2.Close();

	ar.Close();
	f.Close();


	return result;
}
	
bool ApplyOperator(long signal_len, 
				   double * sol, size_t sol_size,
				   char * filename_in, 
				   char * filename_out 
				   )
{
	// �� ������ ������� ��������� ���������� ������ ������
	// � �������� q-��� ������� ����� �������
	// ������� ����� �������� �������� ������ ������ � ��������� �������

	bool result = false;

	AFile f;
	if( !f.Open( filename_in, GENERIC_READ, OPEN_EXISTING) ) 
	{
		MessageBox(0, "Apply operator\nUnable to open file" , filename_in, MB_OK);
		result = false;
	}

	char buff[BUFF_SIZE];
	Archive ar( &f, Archive::load, BUFF_SIZE, buff );
	
	AFile f2;
	if( !f2.Open( filename_out, GENERIC_WRITE, OPEN_EXISTING) ) 
	{
		MessageBox(0, "Apply operator\nUnable to open file" , filename_out, MB_OK);
		ar.Close();
		f.Close();
		result = false;
	}	
	f2.SeekToEnd();
	
	char buff2[BUFF_SIZE];
	Archive ar2( &f2, Archive::store, BUFF_SIZE, buff2 );
	
	try
	{
		long _cols, _rows;
		ar >> _rows; //signal_len
		ar >> _cols;


		for (long j = 0; j < signal_len; j++)
		{
			double product = 0.0;
			//size_t sol_size = sol.size();

			long cc;
			double value;
			do 
			{
				ar >> cc;
				ar >> value;
				if (cc >= 0)
				{
					if (cc < sol_size)
					{
						product += value * sol[cc];
					}
				}
				else
					break;
			}
			while(true);

			ar2 << product;

		}
		result = true;
	}
	catch(char * str)
	{
		MessageBox(0,str,"",0);
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();
	}
	catch(...)
	{
		MessageBox(0,"unknown error of archive read","",0);
	}
	
	ar2.Close();
	f2.Close();

	ar.Close();
	f.Close();


	return result;
}
bool ApplyOperator_SparseOut(long signal_len, 
				   double * sol, size_t sol_size,
				   char * filename_in, 
				   char * filename_out 
				   )
{
	// �� ������ ������� ��������� ���������� ������ ������
	// � �������� q-��� ������� ����� �������
	// ������� ����� �������� �������� ������ ������ � ��������� �������

	bool result = false;

	AFile f;
	if( !f.Open( filename_in, GENERIC_READ, OPEN_EXISTING) ) 
	{
		char str[4098];
		sprintf(str,"Apply Oprator Sparse Out\nUnable to open file\nfilename_in = %s", filename_in);
		MessageBox(0, str, filename_in, MB_OK);
		return false;
	}

	char buff[BUFF_SIZE];
	Archive ar( &f, Archive::load, BUFF_SIZE, buff );
	
	AFile f2;
	if( !f2.Open( filename_out, GENERIC_WRITE, OPEN_EXISTING) ) 
	{
		char str[4098];
		sprintf(str,"Apply Oprator Sparse Out\nUnable to open file\nfilename_out = %s", filename_out);
		MessageBox(0, str , filename_out, MB_OK);
		ar.Close();
		f.Close();
		return false;
	}	
	f2.SeekToEnd();
	
	char buff2[BUFF_SIZE];
	Archive ar2( &f2, Archive::store, BUFF_SIZE, buff2 );
	
	try
	{
		long _cols, _rows;
		ar >> _rows; //signal_len
		ar >> _cols;


		for (long j = 0; j < signal_len; j++)
		{
			double product = 0.0;
			//size_t sol_size = sol.size();

			long cc;
			double value;
			do 
			{
				ar >> cc;
				ar >> value;
				if (cc >= 0)
				{
					if (cc < sol_size)
					{
						product += value * sol[cc];
					}
				}
				else
					break;
			}
			while(true);

			if (product)
			{
				ar2 << j;
				ar2 << product;
			}
		}
		long c_1 = -1;
		double zero = 0.0;
		ar2 << c_1;
		ar2 << zero;

		result = true;
	}
	catch(char * str)
	{
		MessageBox(0,str,"",0);
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();
	}
	catch(...)
	{
		MessageBox(0,"unknown error of archive read","",0);
	}
	
	ar2.Close();
	f2.Close();

	ar.Close();
	f.Close();


	return result;
}
void GetWaveletFilters(Wavelet2D& w2)
{
#if 0
	double m00_r;
	int n00_r, nd1_r, nd2_r, ngd1_r, ngd2_r, nr1_r, nr2_r, ngr1_r, ngr2_r;


	WaveletFilters(wf_r,order_r,orderBiorthogonalDecomposition_r,
		nd1_r,nd2_r,dh_r,
		ngd1_r,ngd2_r,dg_r,
		nr1_r,nr2_r,rh_r,
		ngr1_r,ngr2_r,rg_r,
		n00_r,m00_r);

	int len_h_r = dh_r.Length();
	
	left_h_r = len_h_r - 2;
	right_h_r = 0;
#else
	WaveletGetLeftRight(
		w2.wf_r, // ���� ��������
		w2.order_r, // ������� ��������
		w2.orderBiorthogonalDecomposition_r,
		w2.dh_r,
		w2.dg_r, 
		w2.rh_r,
		w2.rg_r,
		w2.left_h_r,
		w2.right_h_r,
		w2.left_g_r,
		w2.right_g_r);
#endif


	// Selection of wavelet C


#if 0
	double m00_c;
	int n00_c, nd1_c, nd2_c, ngd1_c, ngd2_c, nr1_c, nr2_c, ngr1_c, ngr2_c;


	WaveletFilters(wf_c,order_c,orderBiorthogonalDecomposition_c,
		nd1_c,nd2_c,dh_c,
		ngd1_c,ngd2_c,dg_c,
		nr1_c,nr2_c,rh_c,
		ngr1_c,ngr2_c,rg_c,
		n00_c,m00_c);

	int len_h_c = dh_c.Length();
	
	left_h_c = len_h_c - 2;
	right_h_c = 0;

#else
	WaveletGetLeftRight(
		w2.wf_c, // ���� ��������
		w2.order_c, // ������� ��������
		w2.orderBiorthogonalDecomposition_c,
		w2.dh_c,
		w2.dg_c, 
		w2.rh_c,
		w2.rg_c,
		w2.left_h_c,
		w2.right_h_c,
		w2.left_g_c,
		w2.right_g_c);

#endif
}
void GetWaveletFilters(Wavelet3D& w3)
{

	WaveletGetLeftRight(
		w3.wf_p, // ���� ��������
		w3.order_p, // ������� ��������
		w3.orderBiorthogonalDecomposition_p,
		w3.dh_p,
		w3.dg_p, 
		w3.rh_p,
		w3.rg_p,
		w3.left_h_p,
		w3.right_h_p,
		w3.left_g_p,
		w3.right_g_p);


	WaveletGetLeftRight(
		w3.wf_r, // ���� ��������
		w3.order_r, // ������� ��������
		w3.orderBiorthogonalDecomposition_r,
		w3.dh_r,
		w3.dg_r, 
		w3.rh_r,
		w3.rg_r,
		w3.left_h_r,
		w3.right_h_r,
		w3.left_g_r,
		w3.right_g_r);


	WaveletGetLeftRight(
		w3.wf_c, // ���� ��������
		w3.order_c, // ������� ��������
		w3.orderBiorthogonalDecomposition_c,
		w3.dh_c,
		w3.dg_c, 
		w3.rh_c,
		w3.rg_c,
		w3.left_h_c,
		w3.right_h_c,
		w3.left_g_c,
		w3.right_g_c);


}
void w_fi(vdouble& fh, int d, vdouble& FI)
{
printf("w_fi(vdouble& fh, int d = %d, vdouble& FI)\n", d);
	vdouble P;
	FI = fh*2; 
	int lenh = fh.Length();
printf("w_fi lenh = %d\n", lenh);
	if (d==1)
	{
	}
	else if (d==2)
	{
		P.resize(2*lenh - 1, 0.0);
		for (int i = 0; i < lenh;i++)
			P[2*i] = fh[i];
		FI=2*conv(P,FI);
	}
	else
	{
		for (int j=2; j < d; j++)
		{
			int pow_two = (int)pow(2.0, (j-1));
			P.resize(pow_two*(lenh - 1) + 1, 0.0);
			for (int i = 0; i < lenh;i++)
				P[pow_two*i] = fh[i];
			FI=2*conv(P,FI);
		}

		int pow_two = (int)pow(2.0, (d-1));

		P.resize(pow_two*(lenh - 1) + 1, 0.0);
		for (int i = 0; i < lenh;i++)
			P[pow_two*i] = fh[i];
		
		FI=2*conv(P,FI);

	}
printf("w_fi end\n", d);
}
Grid * InverseWaveletImage2D(Wavelet2D& w2, int d, MyMethodsData& mmd)
{
	Grid * wavSimage = new Grid;

	vdouble FI_r, FI_c;

	w_fi(w2.rh_r, d, FI_r);
	w_fi(w2.rh_c, d, FI_c);

	wavSimage->gridSection.nRow = FI_r.Length();
	wavSimage->gridSection.nCol = FI_c.Length();

#if 0
	wavSimage->gridSection.xLL = 0;
	wavSimage->gridSection.xSize = 1;

	wavSimage->gridSection.yLL = 0;
	wavSimage->gridSection.ySize = 1;			  
#else
	// ���������� ������ ������� �� X � �� Y �
	// � �������� �������������� ���������� �������� ��, �� ������� ������ ������
	if (mmd.delta__x > mmd.delta__y)
	{
		//������� �� x
		wavSimage->gridSection.xLL = mmd.x0;
		wavSimage->gridSection.xSize = mmd.delta_x;
	}
	else
	{
		//������� �� y
		wavSimage->gridSection.xLL = mmd.y0;
		wavSimage->gridSection.xSize = mmd.delta_y;
	}

	wavSimage->gridSection.yLL = mmd.z0 - (wavSimage->gridSection.nRow - 1) * mmd.delta_z;
	wavSimage->gridSection.ySize = mmd.delta_z;					  
#endif
	wavSimage->gridSection.z = AllocDoubleMat(wavSimage->gridSection.nRow, wavSimage->gridSection.nCol);
	wavSimage->gridSection.BlankValue = BLANK_VALUE;//1.70141e38;// nodes are blanked if greater or equal to this value
	
	double min_z = DBL_MAX;
	double max_z = -DBL_MAX;
	
	for (long c = 0; c < wavSimage->gridSection.nCol; c++)
	{
		for (long r = 0; r < wavSimage->gridSection.nRow; r++)
		{
			wavSimage->gridSection.z[r][c] = FI_r[wavSimage->gridSection.nRow-r-1]*FI_c[c];
			if (min_z > wavSimage->gridSection.z[r][c]) min_z = wavSimage->gridSection.z[r][c];
			if (max_z < wavSimage->gridSection.z[r][c]) max_z = wavSimage->gridSection.z[r][c];
		}
	}

	wavSimage->gridSection.zMin = min_z;
	wavSimage->gridSection.zMax = max_z;

	wavSimage->faultSection.nTraces = 0;
	wavSimage->faultSection.nVertices = 0;
	wavSimage->faultSection.traces = NULL;
	wavSimage->faultSection.vertexes = NULL;
	printf("The grid is created\n");
	return wavSimage;
}


Grid4 * ShowCube(MyMethodsData3& mmd)
{
	//Grid * wavSimage = new Grid;
	Grid4 * cube = new Grid4;


	cube->grid4Section.nRow = mmd.rows;
	cube->grid4Section.nCol = mmd.cols;
	cube->grid4Section.nPag = mmd.pages;

	cube->grid4Section.xLL = mmd.x0;
	cube->grid4Section.xSize = mmd.delta_x;

	cube->grid4Section.yLL = mmd.y0;
	cube->grid4Section.ySize = mmd.delta_y;

	cube->grid4Section.zLL = mmd.z0 - (mmd.pages - 1) * mmd.delta_z;
	cube->grid4Section.zSize = mmd.delta_z;

//	wavSimage->gridSection.z = AllocDoubleMat(wavSimage->gridSection.nRow, wavSimage->gridSection.nCol);
//	wavSimage->gridSection.BlankValue = BLANK_VALUE;//1.70141e38;// nodes are blanked if greater or equal to this value
		
	
	cube->grid4Section.v = Alloc3DMat<double>(cube->grid4Section.nPag, cube->grid4Section.nRow, cube->grid4Section.nCol);
	cube->grid4Section.BlankValue = BLANK_VALUE;//1.70141e38;// nodes are blanked if greater or equal to this value

	double min_v = DBL_MAX;
	double max_v = -DBL_MAX;

	for (long p = 0; p < cube->grid4Section.nPag; p++)				
	{
		for (long c = 0; c < cube->grid4Section.nCol; c++)
		{
			for (long r = 0; r < cube->grid4Section.nRow; r++)
			{
				cube->grid4Section.v[p][r][c] = p;//FI_p[wavSimage->grid4Section.nPag-p-1]*FI_r[r]*FI_c[c];
				if (min_v > cube->grid4Section.v[p][r][c]) min_v = cube->grid4Section.v[p][r][c];
				if (max_v < cube->grid4Section.v[p][r][c]) max_v = cube->grid4Section.v[p][r][c];
			}
		}
	}

	cube->grid4Section.vMin = min_v;
	cube->grid4Section.vMax = max_v;

//	wavSimage->faultSection.nTraces = 0;
//	wavSimage->faultSection.nVertices = 0;
//	wavSimage->faultSection.traces = NULL;
//	wavSimage->faultSection.vertexes = NULL;
	printf("The cube is created\n");
	return cube;
}


Grid4 * InverseWaveletImage3D(Wavelet3D& w3, int d, MyMethodsData3& mmd)
{
printf("Grid4 * InverseWaveletImage3D(Wavelet3D& w3, int d = %d, MyMethodsData3& mmd)\n", d);
	//Grid * wavSimage = new Grid;
	Grid4 * wavSimage = new Grid4;

	vdouble FI_r, FI_c, FI_p;

printf("w_fi(w3.rh_r, d, FI_r)\n", d);
	w_fi(w3.rh_r, d, FI_r);

printf("w_fi(w3.rh_c, d, FI_c)\n", d);
	w_fi(w3.rh_c, d, FI_c);

printf("w_fi(w3.rh_p, d, FI_p)\n", d);
	w_fi(w3.rh_p, d, FI_p);

	wavSimage->grid4Section.nRow = FI_r.Length();
	wavSimage->grid4Section.nCol = FI_c.Length();
	wavSimage->grid4Section.nPag = FI_p.Length();

#if 1
	wavSimage->grid4Section.xLL = mmd.x0;
	wavSimage->grid4Section.xSize = mmd.delta_x;

	wavSimage->grid4Section.yLL = mmd.y0;
	wavSimage->grid4Section.ySize = mmd.delta_y;

	wavSimage->grid4Section.zLL = mmd.z0 - (wavSimage->grid4Section.nPag - 1) * mmd.delta_z;
	wavSimage->grid4Section.zSize = mmd.delta_z;

printf("mmd.x0 = %f\n", mmd.x0);
printf("mmd.y0 = %f\n", mmd.y0);
printf("mmd.z0 = %f\n", mmd.z0);

printf("wavSimage->grid4Section.xLL = %f\n",wavSimage->grid4Section.xLL);
printf("wavSimage->grid4Section.yLL = %f\n",wavSimage->grid4Section.yLL);
printf("wavSimage->grid4Section.zLL = %f\n",wavSimage->grid4Section.zLL);

printf("wavSimage->grid4Section.xSize = %f\n",wavSimage->grid4Section.xSize);
printf("wavSimage->grid4Section.ySize = %f\n",wavSimage->grid4Section.ySize);
printf("wavSimage->grid4Section.zSize = %f\n",wavSimage->grid4Section.zSize);

#else
	// ���������� ������ ������� �� X � �� Y �
	// � �������� �������������� ���������� �������� ��, �� ������� ������ ������
	if (mmd.delta__x > mmd.delta__y)
	{
		//������� �� x
		wavSimage->gridSection.xLL = mmd.x0;
		wavSimage->gridSection.xSize = mmd.delta_x;
	}
	else
	{
		//������� �� y
		wavSimage->gridSection.xLL = mmd.y0;
		wavSimage->gridSection.xSize = mmd.delta_y;
	}

	wavSimage->gridSection.yLL = mmd.z0 - (wavSimage->gridSection.nRow - 1) * mmd.delta_z;
	wavSimage->gridSection.ySize = mmd.delta_z;					  
#endif
//	wavSimage->gridSection.z = AllocDoubleMat(wavSimage->gridSection.nRow, wavSimage->gridSection.nCol);
//	wavSimage->gridSection.BlankValue = BLANK_VALUE;//1.70141e38;// nodes are blanked if greater or equal to this value
		
	
	wavSimage->grid4Section.v = Alloc3DMat<double>(wavSimage->grid4Section.nPag, wavSimage->grid4Section.nRow, wavSimage->grid4Section.nCol);
	wavSimage->grid4Section.BlankValue = BLANK_VALUE;//1.70141e38;// nodes are blanked if greater or equal to this value

	double min_v = DBL_MAX;
	double max_v = -DBL_MAX;

	for (long p = 0; p < wavSimage->grid4Section.nPag; p++)				
	{
		for (long c = 0; c < wavSimage->grid4Section.nCol; c++)
		{
			for (long r = 0; r < wavSimage->grid4Section.nRow; r++)
			{
				wavSimage->grid4Section.v[p][r][c] = FI_p[wavSimage->grid4Section.nPag-p-1]*FI_r[r]*FI_c[c];
				if (min_v > wavSimage->grid4Section.v[p][r][c]) min_v = wavSimage->grid4Section.v[p][r][c];
				if (max_v < wavSimage->grid4Section.v[p][r][c]) max_v = wavSimage->grid4Section.v[p][r][c];
			}
		}
	}

	wavSimage->grid4Section.vMin = min_v;
	wavSimage->grid4Section.vMax = max_v;

//	wavSimage->faultSection.nTraces = 0;
//	wavSimage->faultSection.nVertices = 0;
//	wavSimage->faultSection.traces = NULL;
//	wavSimage->faultSection.vertexes = NULL;
	printf("The grid is created\n");
	return wavSimage;
}


			
void InverseWaveletTransform2D(Wavelet2D& w2, Grid * grid, long increaser_pw, long len_r, long len_c)
{
	long r,c;
	for (long J = 0; J < increaser_pw; J++)
	{
		vdouble current_s;
		vdouble temp;
		// �������� �� ���� �������
		for (r = 0; r < len_r; r++)
		{
			//printf("r = %d\t", r);
			// ��������� ������� ������� � ������ S-�������������
			current_s.resize(len_c);
			for (c = 0; c < len_c; c++)
			{
				current_s[c] = grid->gridSection.z[r][c];

				/*if (current_s[c])
				{
					printf("1");
				}
				else
				{
					printf("0");
				}*/
			}
			//printf("\t");
			//���������� ������� ��������������
			temp.idwt(w2.left_h_c, w2.right_h_c, w2.rh_c, current_s);
			// ������� ��������� ������� � ������� �������
			for (c = 0; c < 2*len_c; c++)
			{
				grid->gridSection.z[r][c] = temp[c];
				/*if (temp[c])
				{
					printf(1", temp[c]);
				}
				else
				{
					printf("0");
				}*/
			}
			//printf("\n");
		}

		// �������� �� ���� ��������
		for (c = 0; c < 2*len_c; c++)
		{
			//printf("c = %d\n", c);
			// ��������� ������� ������ � ������ S-�������������
			current_s.resize(len_r);
			for (r = 0; r < len_r; r++)
			{
				current_s[r] = grid->gridSection.z[r][c];
			}
			//���������� ������� ��������������
			temp.idwt(w2.left_h_r, w2.right_h_r, w2.rh_r, current_s);
			// ������� ��������� ������� � ������� ������
			for (r = 0; r < 2*len_r; r++)
			{
				grid->gridSection.z[r][c] = temp[r];
			}
		}

		len_r *= 2;
		len_c *= 2;
	}
}

void InverseWaveletTransform3D(Wavelet3D& w3, Grid4 * grid, long increaser_pw, long len_p, long len_r, long len_c)
{
	long p,r,c;
	for (long J = 0; J < increaser_pw; J++)
	{
		vdouble current_s;
		vdouble temp;

		for (p = 0; p < len_p; p++)
		{
			// �������� �� ���� �������
			for (r = 0; r < len_r; r++)
			{
				// ��������� ������� ������� � ������ S-�������������
				current_s.resize(len_c);
				for (c = 0; c < len_c; c++)
				{
					current_s[c] = grid->grid4Section.v[p][r][c];
				}
				//���������� ������� ��������������
				temp.idwt(w3.left_h_c, w3.right_h_c, w3.rh_c, current_s);
				// ������� ��������� ������� � ������� �������
				for (c = 0; c < 2*len_c; c++)
				{
					grid->grid4Section.v[p][r][c] = temp[c];
				}
			}

			// �������� �� ���� ��������
			for (c = 0; c < 2*len_c; c++)
			{
				// ��������� ������� ������ � ������ S-�������������
				current_s.resize(len_r);
				for (r = 0; r < len_r; r++)
				{
					current_s[r] = grid->grid4Section.v[p][r][c];
				}
				//���������� ������� ��������������
				temp.idwt(w3.left_h_r, w3.right_h_r, w3.rh_r, current_s);
				// ������� ��������� ������� � ������� ������
				for (r = 0; r < 2*len_r; r++)
				{
					grid->grid4Section.v[p][r][c] = temp[r];
				}
			}		
		}
		
		// �������� �� ���� �������
		for (r = 0; r < 2*len_r; r++)
		{
			// �������� �� ���� ��������
			for (c = 0; c < 2*len_c; c++)
			{
				// ��������� ������� ������ � ������ S-�������������
				current_s.resize(len_p);
				for (p = 0; p < len_p; p++)
				{
					current_s[p] = grid->grid4Section.v[p][r][c];
				}
				//���������� ������� ��������������
				temp.idwt(w3.left_h_p, w3.right_h_p, w3.rh_p, current_s);
				// ������� ��������� ������� � ������� ������
				for (p = 0; p < 2*len_p; p++)
				{
					grid->grid4Section.v[p][r][c] = temp[p];
				}
			}
		}	
		
		len_p *= 2;
		len_r *= 2;
		len_c *= 2;
	}
}

void FastFourierTransform2D(Grid * grid, ap::real_1d_array & a, bool inversefft, long r1)
{
	// ����� ��������� �� ���� �������, ���� � �������� ������� ������ ���� ������� ���������?
	// ���������� ������ ������ ������ ���� �� ������, ���������� ���� ��������� �������
	long jj = r1;
	{
		// ������������ �������������� ������� ������
		for (long ii = 0; ii < grid->gridSection.nCol; ii++)
		{
			a(ii) = grid->gridSection.z[jj][ii];
		}
		realfastfouriertransform(a, grid->gridSection.nCol, inversefft);
		for (long ii = 0; ii < grid->gridSection.nCol; ii++)
		{
			grid->gridSection.z[jj][ii] = a(ii);
		}
	}
	// � �����
	// �������� �� ���� ��������
	// ��������� � ������ ������� �������� ���� ��������� �������
	for (long ii = 0; ii < grid->gridSection.nCol; ii++)
	{
		// ������������ �������������� ������� �������
		for (long jj = 0; jj < grid->gridSection.nRow; jj++)
		{
			a(jj) = grid->gridSection.z[jj][ii];
		}
		realfastfouriertransform(a, grid->gridSection.nRow, inversefft);
		for (long jj = 0; jj < grid->gridSection.nRow; jj++)
		{
			grid->gridSection.z[jj][ii] = a(jj);
		}
	}

}
void FastFourierTransform2D(Grid * grid, ap::real_1d_array & a, bool inversefft)
{
	// �������� �� ���� �������
	for (long jj = 0; jj < grid->gridSection.nRow; jj++)
	{
		// ������������ �������������� ������� ������
		for (long ii = 0; ii < grid->gridSection.nCol; ii++)
		{
			a(ii) = grid->gridSection.z[jj][ii];
		}
		realfastfouriertransform(a, grid->gridSection.nCol, inversefft);
		for (long ii = 0; ii < grid->gridSection.nCol; ii++)
		{
			grid->gridSection.z[jj][ii] = a(ii);
		}
	}
	// �������� �� ���� ��������
	for (long ii = 0; ii < grid->gridSection.nCol; ii++)
	{
		// ������������ �������������� ������� �������
		for (long jj = 0; jj < grid->gridSection.nRow; jj++)
		{
			a(jj) = grid->gridSection.z[jj][ii];
		}
		realfastfouriertransform(a, grid->gridSection.nRow, inversefft);
		for (long jj = 0; jj < grid->gridSection.nRow; jj++)
		{
			grid->gridSection.z[jj][ii] = a(jj);
		}
	}

}
void FastFourierTransform3D(Grid4 * grid, ap::real_1d_array & a, bool inversefft)
{
	// �������� �� ���� ���������� (���������)
	for (long pp = 0; pp < grid->grid4Section.nPag; pp++)
	{
		// �������� �� ���� ������� ������� ���������
		for (long jj = 0; jj < grid->grid4Section.nRow; jj++)
		{
			// ������������ �������������� ������� ������ ������� ���������
			for (long ii = 0; ii < grid->grid4Section.nCol; ii++)
			{
				a(ii) = grid->grid4Section.v[pp][jj][ii];
			}
			realfastfouriertransform(a, grid->grid4Section.nCol, inversefft);
			for (long ii = 0; ii < grid->grid4Section.nCol; ii++)
			{
				grid->grid4Section.v[pp][jj][ii] = a(ii);
			}
		}
		// �������� �� ���� �������� ������� ���������
		for (long ii = 0; ii < grid->grid4Section.nCol; ii++)
		{
			// ������������ �������������� ������� ������� ������� ���������
			for (long jj = 0; jj < grid->grid4Section.nRow; jj++)
			{
				a(jj) = grid->grid4Section.v[pp][jj][ii];
			}
			realfastfouriertransform(a, grid->grid4Section.nRow, inversefft);
			for (long jj = 0; jj < grid->grid4Section.nRow; jj++)
			{
				grid->grid4Section.v[pp][jj][ii] = a(jj);
			}
		}
	}
    // �������� �� ���� �������
	for (long jj = 0; jj < grid->grid4Section.nRow; jj++)						  
	{
		// �������� �� ���� �������� ������� ������
		for (long ii = 0; ii < grid->grid4Section.nCol; ii++)
		{
			// ������������ �������������� ������� ������� ������� ������ ����� ��� �������
			for (long pp = 0; pp < grid->grid4Section.nPag; pp++)
			{
				a(pp) = grid->grid4Section.v[pp][jj][ii];
			}
			realfastfouriertransform(a, grid->grid4Section.nPag, inversefft);
			for (long pp = 0; pp < grid->grid4Section.nPag; pp++)
			{
				grid->grid4Section.v[pp][jj][ii] = a(pp);
			}
		}
	}
}



void FastFourierTransform3D(Grid4 * grid, ap::real_1d_array & a, bool inversefft, long p1, long r1)
{
	// �������� �� ���� ���������� (���������)
	long pp = p1;
	{
		// �������� �� ���� ������� ������� ���������
		long jj = r1;
		{
			// ������������ �������������� ������� ������ ������� ���������
			for (long ii = 0; ii < grid->grid4Section.nCol; ii++)
			{
				a(ii) = grid->grid4Section.v[pp][jj][ii];
			}
			realfastfouriertransform(a, grid->grid4Section.nCol, inversefft);
			for (long ii = 0; ii < grid->grid4Section.nCol; ii++)
			{
				grid->grid4Section.v[pp][jj][ii] = a(ii);
			}
		}
		// �������� �� ���� �������� ������� ���������
		for (long ii = 0; ii < grid->grid4Section.nCol; ii++)
		{
			// ������������ �������������� ������� ������� ������� ���������
			for (long jj = 0; jj < grid->grid4Section.nRow; jj++)
			{
				a(jj) = grid->grid4Section.v[pp][jj][ii];
			}
			realfastfouriertransform(a, grid->grid4Section.nRow, inversefft);
			for (long jj = 0; jj < grid->grid4Section.nRow; jj++)
			{
				grid->grid4Section.v[pp][jj][ii] = a(jj);
			}
		}
	}
    // �������� �� ���� �������
	for (long jj = 0; jj < grid->grid4Section.nRow; jj++)						  
	{
		// �������� �� ���� �������� ������� ������
		for (long ii = 0; ii < grid->grid4Section.nCol; ii++)
		{
			// ������������ �������������� ������� ������� ������� ������ ����� ��� �������
			for (long pp = 0; pp < grid->grid4Section.nPag; pp++)
			{
				a(pp) = grid->grid4Section.v[pp][jj][ii];
			}
			realfastfouriertransform(a, grid->grid4Section.nPag, inversefft);
			for (long pp = 0; pp < grid->grid4Section.nPag; pp++)
			{
				grid->grid4Section.v[pp][jj][ii] = a(pp);
			}
		}
	}
}
void ErrorOfInverseProblemSolving(vector<vector<double> > & m, size_t rows, size_t cols, vector<double> & t, vector<double> & b, vector<double> & sol, string name)
{
	vector <double> e(rows);
	vector <double> b_rec(rows);
	for (size_t r = 0; r < rows; r++)
	{
		b_rec[r] = 0.0;
		for (size_t c = 0; c < cols; c++)
		{
			b_rec[r] += m[r][c] * sol[c];
		}
		e[r] = b_rec[r] - b[r];
	}
	printf("e = %f\n", SquareSum(e));

	char bln_name[1024];
	sprintf(bln_name, "%s\\%s.bln", dir_out, name.c_str());
	FILE * bln = fopen (bln_name, "wt");
	if(bln)
	{
		fprintf(bln, "%d,%d,original\n", b.size(), 0);
		for(size_t i = 0; i < b.size(); i++)
		{
			fprintf(bln, "%f,%f\n", t[i],  b[i]);
		}	
		fprintf(bln, "%d,%d, reconstr\n", b.size(), 0);
		for(size_t i = 0; i < b.size(); i++)
		{
			fprintf(bln, "%f,%f\n", t[i],  b_rec[i]);
		}
		fclose(bln);
	}
}

bool InverseProblemSolving(vector<vector<double> > & m, size_t cols, vector<double> & t, vector<double> & b, vector<double> & sol, string name)
{

	size_t c, r, rows = m.size();
	double alpha = 0.00; // ����������������� �����������
	bool rand_not_zero_init = false;
	int maxq = 1000;
    bool res = Tichonov(m, cols, alpha, rand_not_zero_init, maxq, b, sol);

	ErrorOfInverseProblemSolving(m, rows, cols, t, b, sol, name);

	return res;
}

bool InverseProblemSolving(vector<vector<double> > & m, size_t cols, vector<double> & b, vector<double> & sol)
{
#if  1
	size_t c, r, rows = m.size();
	double alpha = 0.00; // ����������������� �����������
	bool rand_not_zero_init = false;
	int maxq = 1000;
    bool res = Tichonov(m, cols, alpha, rand_not_zero_init, maxq, b, sol);
#else
#if 0
	size_t i, c, r, rows = m.size();
	vector<vector<double> > A(cols);
	for (i = 0; i < cols; i++) A[i] .resize(cols);
	vector<double> B(cols);
	for (i = 0; i < cols; i++)
	{
		//B[i]         = at[i].ScalarProduct(b);
		B[i] = 0.0;
		for (r = 0; r < rows; r++)
			B[i] += m[r][i] * b[r];
		// ��������� ������ ���������� ������� ���������
		//row.clear();

		for (c = i; c < cols; c++)
		{
			// A[i][c] = sum(a[r][i]*a[r][c], r=1..rows);
			// B[i]    = sum(a[r][i]*b[r]   , r=1..rows);
			// double A_i_c = at[i].ScalarProduct_fast(at[c]);

			A[i][c] = 0.0;
			for (r = 0; r < rows; r++)
				A[i][c] += m[r][i] * m[r][c];

			/*if (c == i)
			{
				A_i_c += alpha;
			}*/
			//row.put(c, A_i_c);

			A[c][i] = A[i][c];
		}			
		//A.push_back(row);
	}
	// ������� ����� ������ - ����� ����� ����� ����� ��������
//	bool res = lesgausssolve(A,int (cols), B,sol,0.0);
	bool res = lesgausssolve_find_max(A,int (cols),int (cols), B,sol,0.0);
	vector <double> E(cols);
	for (i = 0; i < cols; i++)
	{
		//B[i]         = at[i].ScalarProduct(b);
		E[i] = - B[i];
		for (c = 0; c < cols; c++)
		{
			E[i] += A[i][c] * sol[c];
		}
	}
	printf("E = %f\n", SquareSum(E));
#else
	int i, c, r, rows = m.size();
	vdouble A((int)cols,(int)cols);
	//for (i = 0; i < cols; i++) A[i] .resize(cols);
	vdouble B(cols);
	for (i = 0; i < cols; i++)
	{
		//B[i]         = at[i].ScalarProduct(b);
		B[i] = 0.0;
		for (r = 0; r < rows; r++)
			B[i] += m[r][i] * b[r];
		// ��������� ������ ���������� ������� ���������
		//row.clear();

		for (c = i; c < cols; c++)
		{
			// A[i][c] = sum(a[r][i]*a[r][c], r=1..rows);
			// B[i]    = sum(a[r][i]*b[r]   , r=1..rows);
			// double A_i_c = at[i].ScalarProduct_fast(at[c]);

			A(i,c) = 0.0;
			for (r = 0; r < rows; r++)
				A(i,c) += m[r][i] * m[r][c];

			/*if (c == i)
			{
				A_i_c += alpha;
			}*/
			//row.put(c, A_i_c);

			A(c,i) = A(i,c);
		}			
		//A.push_back(row);
	}
	// ������� ����� ������ - ����� ����� ����� ����� ��������
//	bool res = lesgausssolve(A,int (cols), B,sol,0.0);
//	bool res = lesgausssolve_find_max(A,int (cols),int (cols), B,sol,0.0);
	vdouble x;
	double det;
	A.sls_det(B,x,det);
	for (c = 0; c < cols; c++){sol[c] = x[c];}
	vector <double> E(cols);
	for (i = 0; i < cols; i++)
	{
		//B[i]         = at[i].ScalarProduct(b);
		E[i] = - B[i];
		for (c = 0; c < cols; c++)
		{
			E[i] += A(i,c) * sol[c];
		}
	}
	printf("E = %f\n", SquareSum(E));
	bool res = true;
#endif

#endif
	vector <double> e(rows);
	for (r = 0; r < rows; r++)
	{
		e[r] = - b[r];
		for (c = 0; c < cols; c++)
		{
			e[r] += m[r][c] * sol[c];
		}
	}
	printf("e = %f\n", SquareSum(e));
	return res;
}

void ErrorOfInverseProblemSolving(vector<SparseRow> & a, size_t rows, vector<double> & t, vector<double> & b, vector<double> & sol, string name)
{
	vector <double> e(rows);
	vector <double> b_rec(rows);
	for (size_t r = 0; r < rows; r++)
	{
		b_rec[r] = a[r].ScalarProduct(sol);
		e[r] = b_rec[r] - b[r];
	}
	printf("e = %f\n", SquareSum(e));

	char bln_name[1024];
	sprintf(bln_name, "%s\\%s.bln", dir_out, name.c_str());
	FILE * bln = fopen (bln_name, "wt");
	if(bln)
	{
		fprintf(bln, "%d,%d, origin\n", b.size(), 0);
		for(size_t i = 0; i < b.size(); i++)
		{
			fprintf(bln, "%f,%f\n", t[i],  b[i]);
		}	
		fprintf(bln, "%d,%d, reconstr\n", b.size(), 0);
		for(size_t i = 0; i < b.size(); i++)
		{
			fprintf(bln, "%f,%f\n", t[i],  b_rec[i]);
		}
		fclose(bln);
	}
}

void ErrorOfInverseProblemSolving(char * fn_operator, vector<double> & t, vector<double> & b, vector<double> & sol, string name)
{
	printf("ErrorOfInverseProblemSolving\n");
	
	char buff[BUFF_SIZE];
			
	long _cols, rows;
	vector <double> e;
	vector <double> b_rec;


	AFile f;
	if( f.Open( fn_operator, GENERIC_READ, OPEN_EXISTING) ) 
	{
		Archive ar( &f, Archive::load, BUFF_SIZE, buff );
		try
		{
			//ar.ReadString(str2, 255);
			//ar.Read((unsigned char*)m2,sizeof(m2));
			ar >> rows;
			ar >> _cols;

			e.resize(rows);
			b_rec.resize(rows);

	//printf("ErrorOfInverseProblemSolving rows = %ld cols = %ld\n", rows, _cols);

			//m.resize(_rows);
			sparse_row_simple row_s;
			for (long r = 0; r < rows; r++)
			{
	//printf("ErrorOfInverseProblemSolving r = %ld rows = %ld\n", r, rows);
				row_s.clear();
				ar >> row_s;
	//printf("ErrorOfInverseProblemSolving r = %ld rows = %ld end\n", r, rows);

				b_rec[r] = row_s.ScalarProduct(sol);
				e[r] = b_rec[r] - b[r];

				//printf("b_rec[%d] = %e - b[%d] = %e e[r] = %e\n", r, b_rec[r], r, b[r], e[r]);
			}

		}
		catch(char * str)
		{
			MessageBox(0,str,"",0);
		}
		catch (CException* pe)
		{
			// catch errors from WinINet 
			TCHAR szErr[4098]; 
			pe->GetErrorMessage(szErr, 4098); 
			AfxMessageBox(szErr);
			pe->Delete();
		}
		catch(...)
		{
			MessageBox(0,"unknown error of archive read","",0);
		}
		
		ar.Close();
		f.Close();
	}
	else
	{
		MessageBox(0, "Error of Inverse Problem Solving\nUnable to open file" , fn_operator, MB_OK);
	}

	printf("e = %f\n", SquareSum(e));

	char bln_name[1024];

	sprintf(bln_name, "%s\\%s_origin.bln", dir_out, name.c_str());
	char * p; while (p=strchr (bln_name,'\"')){*p = '_';}
	FILE * bln = fopen (bln_name, "wt");
	if(bln)
	{
		fprintf(bln, "%d,%d, origin\n", b.size(), 0);
		for(size_t i = 0; i < b.size(); i++)
		{
			fprintf(bln, "%f,%f\n", t[i],  b[i]);
		}	
		fclose(bln);
	}
	else
		ErrorPrint("fopen");
	
	sprintf(bln_name, "%s\\%s_reconstr.bln", dir_out, name.c_str());
	while (p=strchr (bln_name,'\"')){*p = '_';}
	bln = fopen (bln_name, "wt");
	if(bln)
	{
		fprintf(bln, "%d,%d, reconstr\n", b.size(), 0);
		for(size_t i = 0; i < b.size(); i++)
		{
			fprintf(bln, "%f,%f\n", t[i],  b_rec[i]);
		}
		fclose(bln);
	}
	else
		ErrorPrint("fopen");
}

void ErrorOfMinSqProblemSolving(const char * fn_operator, vector<double> & b, vector<double> & sol, string name, vector <double> & b_rec)
{
	printf("ErrorOfMinSqProblemSolving\n");
	
	char buff[BUFF_SIZE];
			
	long _cols, rows;
	vector <double> e;
	;


	AFile f;
	if( f.Open( fn_operator, GENERIC_READ, OPEN_EXISTING) ) 
	{
		Archive ar( &f, Archive::load, BUFF_SIZE, buff );
		try
		{
			//ar.ReadString(str2, 255);
			//ar.Read((unsigned char*)m2,sizeof(m2));
			ar >> rows;
			ar >> _cols;

			e.resize(rows);
			b_rec.resize(rows, 0.0);

	//printf("ErrorOfInverseProblemSolving rows = %ld cols = %ld\n", rows, _cols);

			//m.resize(_rows);
			sparse_row_simple row_s;
			for (long r = 0; r < rows; r++)
			{
	//printf("ErrorOfInverseProblemSolving r = %ld rows = %ld\n", r, rows);
				row_s.clear();
				ar >> row_s;
	//printf("ErrorOfInverseProblemSolving r = %ld rows = %ld end\n", r, rows);

				row_s.Reconstruct_b_by_my_as_part_of_symmetric_matrix_row(b_rec, r, sol);
			}
			for (long r = 0; r < rows; r++)
			{
				e[r] = b_rec[r] - b[r];
				//printf("b_rec[%d] = %e - b[%d] = %e e[r] = %e\n", r, b_rec[r], r, b[r], e[r]);
			}

		}
		catch(char * str)
		{
			MessageBox(0,str,"",0);
		}
		catch (CException* pe)
		{
			// catch errors from WinINet 
			TCHAR szErr[4098]; 
			pe->GetErrorMessage(szErr, 4098); 
			AfxMessageBox(szErr);
			pe->Delete();
		}
		catch(...)
		{
			MessageBox(0,"unknown error of archive read","",0);
		}
		
		ar.Close();
		f.Close();
	}
	else
	{
		MessageBox(0, "Error of Min Sq Problem Solving\nUnable to open file" , fn_operator, MB_OK);
	}

	double error = sqrt(SquareSum(e) / e.size());
	double signal = sqrt(SquareSum(b) / b.size());
	printf("e = %f b = %f e/b = %f%%\n", error, signal, 100.0 * error/signal );
}
void ErrorOfInverseProblemSolving(bool to_print, char * fn_operator, vector<double> & b, vector<double> & sol, string name, vector <double> & b_rec)
{
	if (to_print)
		printf("ErrorOfInverseProblemSolving\n");
	
	char buff[BUFF_SIZE];
			
	long _cols, rows;
	vector <double> e;
	;

			
	size_t b_size = b.size();

	AFile f;
	if( f.Open( fn_operator, GENERIC_READ, OPEN_EXISTING) ) 
	{
		Archive ar( &f, Archive::load, BUFF_SIZE, buff );
		try
		{
			//ar.ReadString(str2, 255);
			//ar.Read((unsigned char*)m2,sizeof(m2));
			ar >> rows;
			ar >> _cols;

			e.resize(rows);
			b_rec.resize(rows);


	//printf("ErrorOfInverseProblemSolving rows = %ld cols = %ld\n", rows, _cols);

			//m.resize(_rows);
			sparse_row_simple row_s;
			for (long r = 0; r < rows; r++)
			{
	//printf("ErrorOfInverseProblemSolving r = %ld rows = %ld\n", r, rows);
				row_s.clear();
				ar >> row_s;
	//printf("ErrorOfInverseProblemSolving r = %ld rows = %ld end\n", r, rows);

				b_rec[r] = row_s.ScalarProduct(sol);
				e[r] = b_rec[r] - b[r];

				//printf("b_rec[%d] = %e - b[%d] = %e e[r] = %e\n", r, b_rec[r], r, b[r], e[r]);
			}

		}
		catch(char * str)
		{
			MessageBox(0,str,"",0);
		}
		catch (CException* pe)
		{
			// catch errors from WinINet 
			TCHAR szErr[4098]; 
			pe->GetErrorMessage(szErr, 4098); 
			AfxMessageBox(szErr);
			pe->Delete();
		}
		catch(...)
		{
			MessageBox(0,"unknown error of archive read","",0);
		}
		
		ar.Close();
		f.Close();
	}
	else
	{
		MessageBox(0, "Error of Inverse Problem Solving\nUnable to open file" , fn_operator, MB_OK);
	}

	if (to_print)
	{
		double error = sqrt(SquareSum(e) / e.size());
		double signal = sqrt(SquareSum(b) / b.size());
		printf("e = %f b = %f e/b = %f%%\n", error, signal, 100.0 * error/signal );

		char bln_name[1024];

		sprintf(bln_name, "%s\\origin_%s.bln", dir_out, name.c_str());
		char * p; while (p=strchr (bln_name,'\"')){*p = '_';}
		FILE * bln = fopen (bln_name, "wt");
		if(bln)
		{
			fprintf(bln, "%d,%d, origin\n", b.size(), 0);
			for(size_t i = 0; i < b.size(); i++)
			{
				fprintf(bln, "%f,%f\n", double(i), b[i]);
			}	
			fclose(bln);
		}
		else
			ErrorPrint("fopen");
		
		sprintf(bln_name, "%s\\reconstr_%s.bln", dir_out, name.c_str());
		while (p=strchr (bln_name,'\"')){*p = '_';}
		bln = fopen (bln_name, "wt");
		if(bln)
		{
			fprintf(bln, "%d,%d, reconstr\n", b_rec.size(), 0);
			for(size_t i = 0; i < b_rec.size(); i++)
			{
				fprintf(bln, "%f,%e\n", double(i), b_rec[i]);
			}
			fclose(bln);
		}
		else
			ErrorPrint("fopen");
	}
}

bool FormMinSquareAlphaVector(char * fn_operator_wav, vector<double> & alpha_vector)
{
    //vector<sparse_row_simple> at; ������������� ������� � ����������������� ����
	vector<long> file_pointers;

	long _cols, _rows;
	bool res = false;

	AFile f;
	if( ! f.Open( fn_operator_wav, GENERIC_READ, OPEN_EXISTING) ) 
	{
		MessageBox(0, "FormMinSquareMatrix\nUnable to open file" , fn_operator_wav, MB_OK);
		return false;
	}

	char buff[BUFF_SIZE];
	Archive ar( &f, Archive::load, BUFF_SIZE, buff );
	
	

	try
	{
		ar >> _rows;
		ar >> _cols;

		file_pointers.resize(_rows+1);
		file_pointers[0] = 2*sizeof(long);
		sparse_row_simple row_s;
		for (long r = 0; r < _rows; r++)
		{
			row_s.clear();
			ar >> row_s;
			file_pointers[r+1] = file_pointers[r] + (row_s.size() + 1)*(sizeof(long) + sizeof(double));
		}

		// ������� ����������� ������� ������� ���������� ��������� 
		// � ����������� ����������� ���������� ����������
		//bool res = SLAU3(m, cols, b, sol);

		// ������� ��������� ������� ���������� ���������
		// �� ������������� ����������� ������� 
		// ��������� ���������� ������� ���������
		
		size_t cols = _rows;
		size_t rows = _cols;
		

		size_t i, c;


		alpha_vector.resize(cols);
		

		for (i = 0; i < cols; i++)
		{

			sparse_row_simple at_i;
			at_i.clear();
			f.Seek(file_pointers[i], FILE_BEGIN);ar.ClearReadBuffer();
			ar >> at_i;

			c = i;

			sparse_row_simple at_c;
			at_c.clear();
			f.Seek(file_pointers[c], FILE_BEGIN);ar.ClearReadBuffer();
			ar >> at_c;

			// A[i][c] = sum(a[r][i]*a[r][c], r=1..rows);
			// B[i]    = sum(a[r][i]*b[r]   , r=1..rows);
			double A_i_c = at_i.ScalarProduct_fast(at_c);


			alpha_vector[c] = A_i_c;
		}			
	

		res = true;


	}
	catch(char * str)
	{
		MessageBox(0,str,"",0);
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();
	}
	catch(...)
	{
		MessageBox(0,"unknown error of archive read","",0);
	}
	
	ar.Close();
	f.Close();



	return res;
}

bool FormMinSquareMatrix(char * fn_operator_wav, char * fn_min_sq_mat, double alpha)
{
    //vector<sparse_row_simple> at; ������������� ������� � ����������������� ����
	vector<long> file_pointers;

	long _cols, _rows;
	bool res = false;

	AFile f;
	if( ! f.Open( fn_operator_wav, GENERIC_READ, OPEN_EXISTING) ) 
	{
		MessageBox(0, "FormMinSquareMatrix\nUnable to open file" , fn_operator_wav, MB_OK);
		return false;
	}

	char buff[BUFF_SIZE];
	Archive ar( &f, Archive::load, BUFF_SIZE, buff );
	
	AFile f2;
	if( !f2.Open( fn_min_sq_mat, GENERIC_WRITE, CREATE_NEW) ) 
	{
		MessageBox(0, "FormMinSquareMatrix\nUnable to open file" , fn_min_sq_mat, MB_OK);
		ar.Close();
		f.Close();
		return false;
	}	
	
	char buff2[BUFF_SIZE];
	Archive ar2( &f2, Archive::store, BUFF_SIZE, buff2 );

	try
	{
		ar >> _rows;
		ar >> _cols;

		file_pointers.resize(_rows+1);
		file_pointers[0] = 2*sizeof(long);
		sparse_row_simple row_s;
		for (long r = 0; r < _rows; r++)
		{
			row_s.clear();
			ar >> row_s;
			file_pointers[r+1] = file_pointers[r] + (row_s.size() + 1)*(sizeof(long) + sizeof(double));
		}

		// ������� ����������� ������� ������� ���������� ��������� 
		// � ����������� ����������� ���������� ����������
		//bool res = SLAU3(m, cols, b, sol);

		// ������� ��������� ������� ���������� ���������
		// �� ������������� ����������� ������� 
		// ��������� ���������� ������� ���������
		
		size_t cols = _rows;
		size_t rows = _cols;
		
		printf("FormMinSquareMatrix rows = %u cols = %u\n",  rows, cols);

		size_t i, r, c;


		// ������� ����������
		ar2 << cols;
		ar2 << cols;
		
		vector<long> vc(cols); size_t ic;
		index_for_sort * vic  = new index_for_sort[cols];

		sparse_row_simple row;
		for (i = 0; i < cols; i++)
		{
	printf("FormMinSquareMatrix %u %u ", i, cols);

			sparse_row_simple at_i;
			at_i.clear();
			f.Seek(file_pointers[i], FILE_BEGIN);ar.ClearReadBuffer();
			ar >> at_i;

			// ��������� ������ ���������� ������� ���������
			row.clear();
			size_t row_size = 0;

			for (ic = i; ic < cols; ic++)
			{
				vic[ic-i].i = ic;
				vic[ic-i].sort_val = rand();
			}
			qsort( (void *)vic, (size_t)(cols-i), sizeof(index_for_sort), compare_index_for_sort );
			for (ic = i; ic < cols; ic++)
			{
				vc[ic] = vic[ic-i].i;
			}

			//for (c = i; c < cols; c++)
			for (ic = i; ic < cols; ic++)
			{
				c = vc[ic];

				sparse_row_simple at_c;
				at_c.clear();
				f.Seek(file_pointers[c], FILE_BEGIN);ar.ClearReadBuffer();
				ar >> at_c;

				// A[i][c] = sum(a[r][i]*a[r][c], r=1..rows);
				// B[i]    = sum(a[r][i]*b[r]   , r=1..rows);
				double A_i_c = at_i.ScalarProduct_fast(at_c);
				if (c == i)
				{
					A_i_c += alpha;

					printf ("%u %f ", c, A_i_c);
				}
					//printf ("%u %f ", c, A_i_c);

				// printf(" %f %f \n", A_i_c, B[i]);

				if (row.put(c, A_i_c))
					row_size++;
			}			
	printf("row_size = %u\n",row_size);
			//A.push_back(row);
			ar2 << row;
		}
		
		delete [] vic;

		res = true;


	}
	catch(char * str)
	{
		MessageBox(0,str,"",0);
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();
	}
	catch(...)
	{
		MessageBox(0,"unknown error of archive read","",0);
	}
	
	ar.Close();
	f.Close();

	ar2.Close();
	f2.Close();


	return res;
}

bool FormMinSquareB(const char * fn_operator_transponed, vector<double> & signal, vector<double> & B, double alpha, vector<double> sol_mean)
{
    //vector<sparse_row_simple> at; ������������� ������� � ����������������� ����

	char buff[BUFF_SIZE];
	long _cols, _rows;
	bool res = false;

	AFile f;
	if( !f.Open( fn_operator_transponed, GENERIC_READ, OPEN_EXISTING) ) 
	{
		MessageBox(0, "FormMinSquareB\nUnable to open file" , fn_operator_transponed, MB_OK);
	}
	
	Archive ar( &f, Archive::load, BUFF_SIZE, buff );
	
	try
	{
		ar >> _rows;
		ar >> _cols;

		// ������� ����������� ������� ������� ���������� ��������� 
		// � ����������� ����������� ���������� ����������
		//bool res = SLAU3(m, cols, b, sol);

		// ������� ��������� ������� ���������� ���������
		// �� ������������� ����������� ������� 
		// ��������� ���������� ������� ���������
		
		size_t cols = _rows;
		size_t rows = _cols;
		
		//printf("FormMinSquareB rows = %u cols = %u\n",  rows, cols);

		size_t i, r, c;

		B.resize(cols);

		for (i = 0; i < cols; i++)
		{
	//printf("%u %u\n", i, cols);

			sparse_row_simple at_i;
			at_i.clear();
			ar >> at_i;
		
			B[i]         = at_i.ScalarProduct(signal) + alpha * sol_mean[i];
		}

		res = true;

	}
	catch(char * str)
	{
		MessageBox(0,str,"",0);
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();
	}
	catch(...)
	{
		MessageBox(0,"unknown error of archive read","",0);
	}
	
	ar.Close();
	f.Close();

	return res;
}
bool CorrelationProblem(const char * fn_operator_transponed, vector<double> & signal, vector<double> & v_korr, vector<double> & v_cov)
{
    //vector<sparse_row_simple> at; ������������� ������� � ����������������� ����

	char buff[BUFF_SIZE];
	long _cols, _rows;
	bool res = false;

	AFile f;
	if( !f.Open( fn_operator_transponed, GENERIC_READ, OPEN_EXISTING) ) 
	{
		MessageBox(0, "FormMinSquareB\nUnable to open file" , fn_operator_transponed, MB_OK);
	}
	
	Archive ar( &f, Archive::load, BUFF_SIZE, buff );
	
	try
	{
		ar >> _rows;
		ar >> _cols;

		
		size_t cols = _rows;
		size_t rows = _cols;
		
		//printf("FormMinSquareB rows = %u cols = %u\n",  rows, cols);

		size_t i, r, c;

		v_korr.resize(cols);
		v_cov.resize(cols);

		for (i = 0; i < cols; i++)
		{
	//printf("%u %u\n", i, cols);

			sparse_row_simple at_i;
			at_i.clear();
			ar >> at_i;

			at_i.CorrelationCoefficient(signal, v_korr[i], v_cov[i]);
		}

		res = true;

	}
	catch(char * str)
	{
		MessageBox(0,str,"",0);
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();
	}
	catch(...)
	{
		MessageBox(0,"unknown error of archive read","",0);
	}
	
	ar.Close();
	f.Close();

	return res;
}
bool Holesski(char * fn_min_sq_mat, char * fn_Lt, char * dir)
{
	bool res = false;

	char TempDirName[4098];
	sprintf(TempDirName, "%s\\Temp", dir);		
	if (!CreateDirectory(TempDirName,NULL))
	{
		char err_str[4096];
		sprintf(err_str, "Directory \"%s\" creation failed !!!", TempDirName);
		MessageBox(0, err_str, "Holesski", 0);
		return false;
	}

	char TempFileName[4098];
	sprintf(TempFileName, "%s\\%06d.tmp", TempDirName, 0);

	char buff[BUFF_SIZE];
	long cols, rows;

	AFile f;
	if( ! f.Open( fn_min_sq_mat, GENERIC_READ, OPEN_EXISTING) ) 
	{
		MessageBox(0, "Unable to open file" , fn_min_sq_mat, MB_OK);
		return false;
	}
	
	Archive ar( &f, Archive::load, BUFF_SIZE, buff );
	try
	{
		// ������ ���������
		ar >> rows;
		ar >> cols;

		// �������� ��� ������ (��� ���������) � ������� ��������� ����

		AFile f3;
		if( !f3.Open( TempFileName, GENERIC_WRITE, CREATE_NEW) ) 
		{
			MessageBox(0, "Holesski 0\nUnable to open file" , TempFileName, MB_OK);
			return false;
		}	
		
		char buff3[BUFF_SIZE];
		Archive ar3( &f3, Archive::store, BUFF_SIZE, buff3 );
			
		for(long i = 0; i < rows; i++)
		{
			sparse_row_simple row_s;
			row_s.clear();

			// ����� ������ ������������ � ���������������� ����
			// �������� ������� - ���������� ��������� - ���������������
			// ������� ������ �������� ������ ��������� ������� ������

			ar  >> row_s;
			ar3 << row_s;
		}
		
		ar3.Close();
		f3.Close();
	}
	catch(char * str)
	{
		MessageBox(0,str,"",0);
		return false;
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();
	}
	catch(...)
	{
		MessageBox(0,"unknown error of archive read","",0);
		return false;
	}
	// ��������� �������� ����
	ar.Close();
	f.Close();

	///////////////////////////////////////////////////////////////////////
	// ��������� �������� ����

	AFile f2;
	if( !f2.Open( fn_Lt, GENERIC_WRITE, CREATE_NEW) ) 
	{
		MessageBox(0, "Holesski 1\nUnable to open file" , fn_Lt, MB_OK);
		return false;
	}	
	
	char buff2[BUFF_SIZE];
	Archive ar2( &f2, Archive::store, BUFF_SIZE, buff2 );
	
	DWORD 
		time_eplased,
		time_start = GetCurrentTime(),
		time_current,
		time_pre_current = time_start;

	try
	{	// ��������� ��������� ��������� �����	
		ar2 << rows;		
		ar2 << cols;

		for(long i = 0; i < rows; i++)
		{
			time_current = GetCurrentTime();
			time_eplased = time_current - time_pre_current;
			time_pre_current = time_current;

			printf("Holesski %ld %ld, time_eplased = %0.3f %d sec\n", i,rows, double(time_eplased)/1000.0, (time_current - time_start)/1000);

			sprintf(TempFileName, "%s\\%06d.tmp", TempDirName, i);

			AFile fi;
			if( !fi.Open( TempFileName, GENERIC_READ, OPEN_EXISTING) ) 
			{
				MessageBox(0, "Holesski 2\nUnable to open file" , TempFileName, MB_OK);
				return false;
			}	

			
			char buffi[BUFF_SIZE];
			Archive ari( &fi, Archive::load, BUFF_SIZE, buffi );			

			try
			{
				//��������� ������ �� i-���� tmp ����� 
				sparse_row row_dv;
				row_dv.clear();
				ari >> row_dv;
				// ��������� � �� 
				//1) ���������
				//2) ������ ������� ���������� i == c
				//3) ������������ ������� ������ ����
				BraidedNode<sparse_row_element<double> > * nd = row_dv.root->next();
				if (nd == row_dv.root)
				{
					char err[512];
					sprintf(err, "The matrix is not positively defined\n"
						"As row %u is missed", i);
					MessageBox(0, err, "Holesski", MB_OK);
					return false;
				}
				if (nd->val.col != i)
				{
					char err[512];
					sprintf(err, "The matrix is not positively defined\n"
						"As diagonal element at row %u is missed\n"
						"col of first element is %u\n"						
						, i, nd->val.col);
					MessageBox(0, err, "Holesski", MB_OK);
					return false;
				}
				double d = nd->val.val;
				if (d <= 0.0)
				{
					char err[512];
					sprintf(err, "The matrix is not positively defined\n"
						"As diagonal element at row %u is not positive %e", i, d);
					MessageBox(0, err, "Holesski", MB_OK);
					return false;
				}
				double sqrt_d = sqrt(d);
				// �������� � ������ ������ ������������ ������� �� ��� ������  sqrt_d
				nd->val.val = sqrt_d;
				// ��������� �������� ����� �� sqrt_d
				BraidedNode<sparse_row_element<double> > * n = nd->next();
				while (n != row_dv.root)
				{
					n->val.val /= sqrt_d;
					n = n->next();
				}
				// ��������� ��������������� ������ � �������� ����
				// ��� � ������������� ����
				ar2 << row_dv;

				//////////////////////////////////////////////////////
				//////////////////////////////////////////////////////


				sprintf(TempFileName, "%s\\%06d.tmp", TempDirName, i+1);
				
				AFile fi1;
				if( !fi1.Open( TempFileName, GENERIC_WRITE, CREATE_NEW) ) 
				{
					MessageBox(0, "Holesski 3\nUnable to open file" , TempFileName, MB_OK);
					return false;
				}	
				
				char buffi1[BUFF_SIZE];
				Archive ari1( &fi1, Archive::store, BUFF_SIZE, buffi1 );

				//////////////////////////////////////////////////////
				//////////////////////////////////////////////////////

				for(long r = i+1; r < rows; r++)
				{
					// ��������� ��������� ������ �� i-���� tmp ����� 
					sparse_row row_r;
					row_r.clear();
					ari >> row_r;
					// ���� � ������ row_dv ����, ��� �������� c == r
					BraidedNode<sparse_row_element<double> > * n1 = row_dv.root->rchild();
					// ���� �����
					if (row_dv._find(sparse_row_element<double>((size_t)r,1.0), n1) && n1)
					{
						//size_t c1 = n1->val.col;
						double v1 = n1->val.val;
						BraidedNode<sparse_row_element<double> > * n2 = n1;
						while (n2 != row_dv.root)
						{
							size_t c2 = n2->val.col;
							double v2 = n2->val.val;
							row_r.plus(c2, - v1*v2);
							n2 = n2->next();
						}
					}
					// ��������� row_r � i+1-��� tmp ����
					//  ari1 << row_r;
					// �� ��� � ���������������� ����

					//row_r.SaveDissorted(ari1);
					row_r.SaveDissorted_recursive(ari1);
					

				}
				//////////////////////////////////////////////////////
				//////////////////////////////////////////////////////
				ari1.Close();
				fi1.Close();
				//////////////////////////////////////////////////////
				//////////////////////////////////////////////////////
			}
			catch(char * str)
			{
				MessageBox(0,str,"",0);
				return false;
			}
			catch (CException* pe)
			{
				// catch errors from WinINet 
				TCHAR szErr[4098]; 
				pe->GetErrorMessage(szErr, 4098); 
				AfxMessageBox(szErr);
				pe->Delete();
			}
			catch(...)
			{
				MessageBox(0,"unknown error of archive read","",0);
				return false;
			}

			ari.Close();
			fi.Close();
			// ������� i-��� tmp ����
			sprintf(TempFileName, "%s\\%06d.tmp", TempDirName, i);
			DeleteFile(TempFileName);
		}
		// ������� rows-��� tmp ����
		sprintf(TempFileName, "%s\\%06d.tmp", TempDirName, rows);
		DeleteFile(TempFileName);
	}
	catch(char * str)
	{
		MessageBox(0,str,"",0);
		return false;
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();
	}
	catch(...)
	{
		MessageBox(0,"unknown error of archive read","",0);
		return false;
	}
	// ��������� �������� ����
	ar2.Close();
	f2.Close();

	return true;
}
bool Holesski3(const char * fn_min_sq_mat, const char * fn_Lt, char * dir, long j_start, double alpha)
{
	bool res = false;

	char TempDirName[4098];
	sprintf(TempDirName, "%s\\Temp", dir);	
	if (!CreateDirectory(TempDirName,NULL) && j_start == 0 )
	{
		//char err_str[4096];
		//sprintf(err_str, "Directory \"%s\" creation failed !!!", TempDirName);
		//MessageBox(0, err_str, "Holesski", 0);
		//return false;
	}

	char TempFileName[4098];
	//sprintf(TempFileName, "%s\\%06d.tmp", TempDirName, 0);

	char buff[BUFF_SIZE];
	long cols, rows;

	AFile f;
	if( ! f.Open( fn_min_sq_mat, GENERIC_READ, OPEN_EXISTING) ) 
	{
		MessageBox(0, "Unable to open file" , fn_min_sq_mat, MB_OK);
		return false;
	}
	
	Archive ar( &f, Archive::load, BUFF_SIZE, buff );
	try
	{
		// ������ ���������
		ar >> rows;
		ar >> cols;
	}
	catch(char * str)
	{
		MessageBox(0,str,"",0);
		return false;
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();
	}
	catch(...)
	{
		MessageBox(0,"unknown error of archive read","",0);
		return false;
	}

	DWORD 
		time_eplased,
		time_start = GetCurrentTime(),
		time_current,
		time_pre_current = time_start;

	try
	{	
		for(long j = 0; j < rows; j++)
		{
			time_current = GetCurrentTime();
			time_eplased = time_current - time_pre_current;
			time_pre_current = time_current;

			printf("Holesski3 %ld %ld, time_eplased = %0.3f %d sec\n", j,rows, double(time_eplased)/1000.0, (time_current - time_start)/1000);

			// ��������� ��������� ������ �� �������� �����

			sparse_row row_j; row_j.clear();
			ar >> row_j;

			// if we continue broken calculation
			if (j < j_start) continue;

			//Sleep(5);

			// ��������� � �� ���������, ������� � ��������������� ������������� ��������


			bool alpha_putted = false;
e_start_row_j:
			BraidedNode<sparse_row_element<double> > * nd = row_j.root->next();
			if (nd == row_j.root)
			{
				if (!alpha || alpha_putted)
				{
					char err[512];
					sprintf(err, "The matrix is not positively defined\n"
						"As row %u is missed", j);
					MessageBox(0, err, "Holesski", MB_OK);
					return false;
				}
				else
				{
					row_j.put(size_t(j), alpha);
					alpha_putted = true;
					goto e_start_row_j;
				}
			}
			if (nd->val.col != j)
			{
				if (!alpha || alpha_putted)
				{
					char err[512];
					sprintf(err, "The matrix is not positively defined\n"
						"As diagonal element at row %u is missed\n"
						"col of first element is %u\n"						
						, j, nd->val.col);
					MessageBox(0, err, "Holesski", MB_OK);
					return false;
				}
				else
				{
					row_j.put(size_t(j), alpha);
					alpha_putted = true;
					goto e_start_row_j;
				}
			}
			//printf("nd->val.val = %e nd->val.col = %ld\n", nd->val.val, nd->val.col);
			if (!alpha_putted)
				nd->val.val += alpha;
			//printf("nd->val.val = %e nd->val.col = %ld\n", nd->val.val, nd->val.col);
			double d = nd->val.val;
			if (d <= 0.0)
			{
				char err[512];
				sprintf(err, "The matrix is not positively defined\n"
					"As diagonal element at row %u is not positive %e", j, d);
				MessageBox(0, err, "Holesski3 1", MB_OK);
				return false;
			}

			//printf (" j = %d  d = %e\n",  j, d);
				
			double dd = 0.0;

			for(long k = 0; k < j; k++)
			{
				

				sprintf(TempFileName, "%s\\%06d.isr", TempDirName, k);

				AFile fk;
				if( !fk.Open( TempFileName, GENERIC_READ, OPEN_EXISTING) ) 
				{
					MessageBox(0, "Holesski 2\nUnable to open file" , TempFileName, MB_OK);
					return false;
				}	
				
				char buffk[BUFF_SIZE];
				Archive ark( &fk, Archive::load, BUFF_SIZE, buffk );

				sparse_row_simple row_k;
				long cc;
				double value;
				do 
				{
					ark >> cc;
					ark >> value;

					if (cc >= j)
						row_k.put(cc, value);

					//printf("j = %ld cc = %ld, value = %f\n", j, cc, value);
				}
				while(cc > j);

				//printf("After while j = %ld cc = %ld, value = %f\n", j, cc, value);

				ark.Close();
				fk.Close();


				if (cc = j)
				{
					size_t row_k_size = row_k.size();
					for (size_t i = 0; i < row_k_size; i++)
					{
						if (row_k[i].col == j)
						{
							/*printf("i = %ld j = %ld row_k[i].col = %ld, row_k[i].val = %f value = %f\n", 
								i, j, row_k[i].col, row_k[i].val, value);*/

							dd -= row_k[i].val * value;

						}
						
						row_j.plus(row_k[i].col, - row_k[i].val * value);
					}
				}

			}

			
			//printf ("dd = %e\n", dd);
			//printf("nd->val.val = %e nd->val.col = %ld\n", nd->val.val, nd->val.col);

			nd = row_j.root->next();
			//printf("nd->val.val = %e nd->val.col = %ld\n", nd->val.val, nd->val.col);
			d = nd->val.val;
			if (d <= 0.0)
			{
				char err[512];
				sprintf(err, "The matrix is not positively defined\n"
					"As diagonal element at row %u is not positive %e", j, d);
				MessageBox(0, err, "Holesski3 2", MB_OK);
				return false;
			}
			double sqrt_d = sqrt(d);
			// �������� � ������ ������ ������������ ������� �� ��� ������  sqrt_d
			nd->val.val = sqrt_d;
			// ��������� �������� ����� �� sqrt_d
			BraidedNode<sparse_row_element<double> > * n = nd->next();
			while (n != row_j.root)
			{
				n->val.val /= sqrt_d;
				n = n->next();
			}

			// create j-��� tmp ����
			sprintf(TempFileName, "%s\\%06d.isr", TempDirName, j);
			
			AFile fj;
			if( !fj.Open( TempFileName, GENERIC_WRITE, CREATE_NEW) ) 
			{
				MessageBox(0, "Holesski 0\nUnable to open file" , TempFileName, MB_OK);
				return false;
			}	
			
			char buffj[BUFF_SIZE];
			Archive arj( &fj, Archive::store, BUFF_SIZE, buffj );

			

			row_j.InverseSortedSave(arj);
			
			arj.Close();
			fj.Close();
		}
	}
	catch(char * str)
	{
		MessageBox(0,str,"",0);
		return false;
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();
	}
	catch(...)
	{
		MessageBox(0,"unknown error of archive read","",0);
		return false;
	}
	///////////////////////////////////////////////////////////////////////
	// ��������� �������� ����

	AFile f2;
	if( !f2.Open( fn_Lt, GENERIC_WRITE, CREATE_NEW) ) 
	{
		MessageBox(0, "Holesski 1\nUnable to open file" , fn_Lt, MB_OK);
		return false;
	}	
	
	char buff2[BUFF_SIZE];
	Archive ar2( &f2, Archive::store, BUFF_SIZE, buff2 );
	try{
		// ��������� ��������� ��������� �����	
		ar2 << rows;		
		ar2 << cols;
		
		char buffjs[BUFF_SIZE];
		for(long j = 0; j < rows; j++)
		{
			// open j-��� tmp ����
			sprintf(TempFileName, "%s\\%06d.isr", TempDirName, j);	

			AFile fjs;
			if( ! fjs.Open( TempFileName, GENERIC_READ, OPEN_EXISTING) ) 
			{
				MessageBox(0, "Unable to open file" , TempFileName, MB_OK);
				return false;
			}
			
			Archive arjs( &fjs, Archive::load, BUFF_SIZE, buffjs );

			sparse_row_simple row_js; row_js.clear();
			arjs >> row_js;
			row_js.InverseSave(ar2);
			arjs.Close();
			fjs.Close();

			DeleteFile(TempFileName);

		}
	}
	catch(char * str)
	{
		MessageBox(0,str,"",0);
		return false;
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();
	}
	catch(...)
	{
		MessageBox(0,"unknown error of archive read","",0);
		return false;
	}

	// ��������� �������� ����
	ar2.Close();
	f2.Close();

	return true;
}
bool Holesski3_in_operative_memory(char * fn_min_sq_mat, char * fn_Lt, char * dir, double alpha)
{
	bool res = false;

	//char TempDirName[4098];
	//sprintf(TempDirName, "%s\\Temp", dir);		
	//if (!CreateDirectory(TempDirName,NULL) && j_start == 0 )
	//{
	//	char err_str[4096];
	//	sprintf(err_str, "Directory \"%s\" creation failed !!!", TempDirName);
	//	MessageBox(0, err_str, "Holesski", 0);
	//	return false;
	//}

	//char TempFileName[4098];
	//sprintf(TempFileName, "%s\\%06d.tmp", TempDirName, 0);

	char buff[BUFF_SIZE];
	long cols, rows;

	AFile f;
	if( ! f.Open( fn_min_sq_mat, GENERIC_READ, OPEN_EXISTING) ) 
	{
		MessageBox(0, "Unable to open file" , fn_min_sq_mat, MB_OK);
		return false;
	}
	
	Archive ar( &f, Archive::load, BUFF_SIZE, buff );
	try
	{
		// ������ ���������
		ar >> rows;
		ar >> cols;
	}
	catch(char * str)
	{
		MessageBox(0,str,"",0);
		return false;
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();
	}
	catch(...)
	{
		MessageBox(0,"unknown error of archive read 1","",0);
		return false;
	}

	DWORD 
		time_eplased,
		time_start = GetCurrentTime(),
		time_current,
		time_pre_current = time_start;
    
	vector<sparse_row> m;
	m.clear();

	try
	{	
		for(long j = 0; j < rows; j++)
		{
			time_current = GetCurrentTime();
			time_eplased = time_current - time_pre_current;
			time_pre_current = time_current;

			printf("Holesski3 %ld %ld, time_eplased = %0.3f %d sec\n", j,rows, double(time_eplased)/1000.0, (time_current - time_start)/1000);

			// ��������� ��������� ������ �� �������� �����

			sparse_row row__j; row__j.clear();
			ar >> row__j;

			m.push_back(row__j);

			// if we continue broken calculation
			//if (j < j_start) continue;

			//Sleep(5);

			// ��������� � �� ���������, ������� � ��������������� ������������� ��������


			bool alpha_putted = false;
e_start__row_j:
			BraidedNode<sparse_row_element<double> > * nd = m[j].root->next();
			if (nd == m[j].root)
			{
				if (!alpha || alpha_putted)
				{
					char err[512];
					sprintf(err, "The matrix is not positively defined\n"
						"As row %u is missed", j);
					MessageBox(0, err, "Holesski", MB_OK);
					return false;
				}
				else
				{
					m[j].put(size_t(j), alpha);
					alpha_putted = true;
					goto e_start__row_j;
				}
			}
			if (nd->val.col != j)
			{
				if (!alpha || alpha_putted)
				{
					char err[512];
					sprintf(err, "The matrix is not positively defined\n"
						"As diagonal element at row %u is missed\n"
						"col of first element is %u\n"						
						, j, nd->val.col);
					MessageBox(0, err, "Holesski", MB_OK);
					return false;
				}
				else
				{
					m[j].put(size_t(j), alpha);
					alpha_putted = true;
					goto e_start__row_j;
				}
			}
			//printf("nd->val.val = %e nd->val.col = %ld\n", nd->val.val, nd->val.col);
			if (!alpha_putted)
				nd->val.val += alpha;
			//printf("nd->val.val = %e nd->val.col = %ld\n", nd->val.val, nd->val.col);
			double d = nd->val.val;
			if (d <= 0.0)
			{
				char err[512];
				sprintf(err, "The matrix is not positively defined\n"
					"As diagonal element at row %u is not positive %e", j, d);
				MessageBox(0, err, "Holesski3 1", MB_OK);
				return false;
			}
#if 1

		double sqrt_d = sqrt(d);
		nd->val.val = sqrt_d;
		BraidedNode<sparse_row_element<double> > * n1 = nd->next();
		while (n1 != m[j].root)
		{
			BraidedNode<sparse_row_element<double> > * n2 = n1;
			size_t c1 = n1->val.col;
			double v1 = n1->val.val;
			while (n2 != m[j].root)
			{
				size_t c2 = n2->val.col;
				double v2 = n2->val.val;
				m[c1].plus(c2, - v1*v2/d);
				n2 = n2->next();
			}
			n1->val.val /= sqrt_d;
			n1 = n1->next();
		}

#else
			//printf (" j = %d  d = %e\n",  j, d);
				
			double dd = 0.0;

			for(long k = 0; k < j; k++)
			{
				

				//sprintf(TempFileName, "%s\\%06d.isr", TempDirName, k);

				//AFile fk;
				//if( !fk.Open( TempFileName, GENERIC_READ, OPEN_EXISTING) ) 
				//{
				//	MessageBox(0, "Holesski 2\nUnable to open file" , TempFileName, MB_OK);
				//	return false;
				//}	
				
				//char buffk[BUFF_SIZE];
				//Archive ark( &fk, Archive::load, BUFF_SIZE, buffk );

				//sparse_row_simple row_k;
				long cc;
				double value;
				do 
				{
					ark >> cc;
					ark >> value;

					if (cc >= j)
						row_k.put(cc, value);

					//printf("j = %ld cc = %ld, value = %f\n", j, cc, value);
				}
				while(cc > j);

				//printf("After while j = %ld cc = %ld, value = %f\n", j, cc, value);

				//ark.Close();
				//fk.Close();


				if (cc = j)
				{
					size_t row_k_size = row_k.size();
					for (size_t i = 0; i < row_k_size; i++)
					{
						if (row_k[i].col == j)
						{
							/*printf("i = %ld j = %ld row_k[i].col = %ld, row_k[i].val = %f value = %f\n", 
								i, j, row_k[i].col, row_k[i].val, value);*/

							dd -= row_k[i].val * value;

						}
						
						m[j].plus(row_k[i].col, - row_k[i].val * value);
					}
				}

			}

			
			//printf ("dd = %e\n", dd);
			//printf("nd->val.val = %e nd->val.col = %ld\n", nd->val.val, nd->val.col);

			nd = m[j].root->next();
			//printf("nd->val.val = %e nd->val.col = %ld\n", nd->val.val, nd->val.col);
			d = nd->val.val;
			if (d <= 0.0)
			{
				char err[512];
				sprintf(err, "The matrix is not positively defined\n"
					"As diagonal element at row %u is not positive %e", j, d);
				MessageBox(0, err, "Holesski3 2", MB_OK);
				return false;
			}
			double sqrt_d = sqrt(d);
			// �������� � ������ ������ ������������ ������� �� ��� ������  sqrt_d
			nd->val.val = sqrt_d;
			// ��������� �������� ����� �� sqrt_d
			BraidedNode<sparse_row_element<double> > * n = nd->next();
			while (n != m[j].root)
			{
				n->val.val /= sqrt_d;
				n = n->next();
			}

			// create j-��� tmp ����
			sprintf(TempFileName, "%s\\%06d.isr", TempDirName, j);
			
			AFile fj;
			if( !fj.Open( TempFileName, GENERIC_WRITE, CREATE_NEW) ) 
			{
				MessageBox(0, "Holesski 0\nUnable to open file" , TempFileName, MB_OK);
				return false;
			}	
			
			char buffj[BUFF_SIZE];
			Archive arj( &fj, Archive::store, BUFF_SIZE, buffj );

			

//			row_j.InverseSortedSave(arj);
			
			arj.Close();
			fj.Close();
#endif

		}
	}
	catch(char * str)
	{
		MessageBox(0,str,"",0);
		return false;
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();
	}
	catch(...)
	{
		MessageBox(0,"unknown error of archive read 2","",0);
		return false;
	}

	//if (!Holesski3(m))
	//{
	//	return false;
	//}
	///////////////////////////////////////////////////////////////////////
	// ��������� �������� ����

	AFile f2;
	if( !f2.Open( fn_Lt, GENERIC_WRITE, CREATE_NEW) ) 
	{
		MessageBox(0, "Holesski 1\nUnable to open file" , fn_Lt, MB_OK);
		return false;
	}	
	
	char buff2[BUFF_SIZE];
	Archive ar2( &f2, Archive::store, BUFF_SIZE, buff2 );
	try{
		// ��������� ��������� ��������� �����	
		ar2 << rows;		
		ar2 << cols;
		
		char buffjs[BUFF_SIZE];
		for(long j = 0; j < rows; j++)
		{
			// open j-��� tmp ����
//			sprintf(TempFileName, "%s\\%06d.isr", TempDirName, j);	

			//AFile fjs;
			//if( ! fjs.Open( TempFileName, GENERIC_READ, OPEN_EXISTING) ) 
			//{
			//	MessageBox(0, "Unable to open file" , TempFileName, MB_OK);
			//	return false;
			//}
			
			//Archive arjs( &fjs, Archive::load, BUFF_SIZE, buffjs );

			//sparse_row_simple row_js; row_js.clear();
			//arjs >> row_js;
			//m[j].InverseSave(ar2);
			//m[j].InverseSortedSave(ar2);
			ar2 << m[j];
			//arjs.Close();
			//fjs.Close();

			//DeleteFile(TempFileName);

		}
	}
	catch(char * str)
	{
		MessageBox(0,str,"",0);
		return false;
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();
	}
	catch(...)
	{
		MessageBox(0,"unknown error of archive read","",0);
		return false;
	}

	// ��������� �������� ����
	ar2.Close();
	f2.Close();

	return true;
}
//����������� ���������� ������� ������� ������ � ������� �������� �������� �� ������� 
/* Subroutine */ bool afg1d_c(double *a, int *p, int *n)
{
    /* Initialized data */

    //static double zero = 0.;

    /* System generated locals */
    int ind, N = *n;
    double d__1;

    /* Local variables */
    static int f, row, j, l, pivot;
    static double pivotValue, bn;
    static double bx, tk, pr;


#define a_ref(a_1,a_2) a[(a_1)*N + a_2]

    /* Parameter adjustments */

    /* Function Body */
    for (f = 0; f < N; f++)
	{
		p[f]=f;
	}
    if (N == 1) 
	{
        return true;
    }

	for (f = 0; f < N; f++)
	{
		//f;// ����� ������������� �������� - ��������� � ���������� ������������� ��������
		pivot = f;
		pivotValue = fabs(a_ref(f, f));
		//�������� ������������ �� ������ ������� � �������
		//����� �������� ��������

		for (row = f; row < N; ++row) 
		{
			bn = (d__1 = a_ref(row, f), fabs(d__1));
			//d__1 = a_ref(row, f);
			//bn = fabs(d__1);
			if (pivotValue < bn) 
			{
				pivotValue = bn;
				pivot = row;
			}
		}

		// ������������ ������� ������
		for (j = 0; j < N; ++j) 
		{
			bx = a_ref(pivot, j);
			a_ref(pivot, j) = a_ref(f, j);
			a_ref(f, j) = bx;
		}
		ind = p[pivot];
		p[pivot] = p[f];
		p[f] = ind;


		l = f + 1;
		tk = (d__1 = a_ref(f, f), fabs(d__1));
		if (tk == 0.) 
		{
            printf("error(������� ���������)\n");
			printf ("error bad matrix\n");
			return false;
			// ���� ������������ �� ������ � ������� ������� �� �� �������� ����
			// ��������� � ���������� ������� ��� �����-���� ��������������
			continue;
		}

		// ����� ���� ������� �� u(i,i) ������������ �������, 
		// ������� � �������� ������� ��������� ��� ������������ ���������
		pr = 1. / a_ref(f, f);
		for (row = l; row < N; ++row) {
			a_ref(row, f) = pr * a_ref(row, f);
		}

		// ��������� ���������� ���� - �������� �� ���������� 
		// ������������ ��������, ������������ �� �������� ������������� ��������
		for (j = l; j < N; ++j) {
			for (row = l; row < N; ++row) {
				a_ref(row, j) -= a_ref(f, j) * a_ref(row, f);
			}
		}

    }
    return true;
} /* afg1d_c */

bool LUP_in_operative_memory(const char * fn_min_sq_mat, const char * fn_L, const char * fn_U, const char * fn_P, const char * dir, double alpha)
{
	bool res = false;

	char buff[BUFF_SIZE];
	long cols, rows;

	AFile f;
	if( ! f.Open( fn_min_sq_mat, GENERIC_READ, OPEN_EXISTING) ) 
	{
		MessageBox(0, "Unable to open file" , fn_min_sq_mat, MB_OK);
		return false;
	}
		
	
	Archive ar( &f, Archive::load, BUFF_SIZE, buff );
	try
	{
		// ������ ���������
		ar >> rows;
		ar >> cols;
	}
	catch(char * str)
	{
		MessageBox(0,str,"",0);
		return false;
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();
	}
	catch(...)
	{
		MessageBox(0,"unknown error of archive read 1","",0);
		return false;
	}

	DWORD 
		time_eplased,
		time_start = GetCurrentTime(),
		time_current,
		time_pre_current = time_start;
    

	int rows_rows = rows*rows;
	double * a = new double[rows*rows];
	for (int i = 0; i < rows_rows; i++)	a[i]=0.0;

#define a_ref(a_1,a_2) a[(a_1)*rows + a_2]


	try
	{	
		for(long r = 0; r < rows; r++)
		{
			// ��������� ��������� ������ �� �������� �����
			sparse_row row__j; row__j.clear();
			ar >> row__j;

			for (row__j.first(); !row__j.isHead(); row__j.next())
			{
				long c = row__j.val().col;
				double value = row__j.val().val;
				a_ref(r,c) = value;
				a_ref(c,r) = value;
			}
			a_ref(r,r) += alpha;

		}
	}
	catch(char * str)
	{
		MessageBox(0,str,"",0);
		return false;
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();
	}
	catch(...)
	{
		MessageBox(0,"unknown error of archive read 2","",0);
		return false;
	}

	int n = rows;

	int * p = new int[n];


	if (!afg1d_c(a, p, &n))
	{
		printf ("afg1d_c return false\n");
		return false;
	}

	printf("P = \n");
	for (int i = 0; i < n; i++)
	{
		printf("\t%d", p[i]);
	}
	printf("\n");
	///////////////////////////////////////////////////////////////////////
	// ��������� �������� ����

	AFile f4;
	if( !f4.Open( fn_L, GENERIC_WRITE, CREATE_NEW) ) 
	{
		MessageBox(0, "Holesski 1\nUnable to open file" , fn_L, MB_OK);
		return false;
	}	
	
	char buff4[BUFF_SIZE];
	Archive ar4( &f4, Archive::store, BUFF_SIZE, buff4 );
	try{
		// ��������� ��������� ��������� �����	
		ar4 << rows;		
		ar4 << cols;
		
		for(long j = 0; j < rows; j++)
		{
			sparse_row_simple row_jL; row_jL.clear();
			for (int i = 0; i < j; i++)
			{
				row_jL.push_back(sparse_row_element<double>(i,a_ref(j,i)));
			}
			row_jL.push_back(sparse_row_element<double>(j,1.0));
			ar4 << row_jL;
		}
	}
	catch(char * str)
	{
		MessageBox(0,str,"",0);
		return false;
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();
	}
	catch(...)
	{
		MessageBox(0,"unknown error of archive read","",0);
		return false;
	}

	// ��������� �������� ����
	ar4.Close();
	f4.Close();
	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////
	// ��������� �������� ����

	AFile f3;
	if( !f3.Open( fn_U, GENERIC_WRITE, CREATE_NEW) ) 
	{
		MessageBox(0, "Holesski 1\nUnable to open file" , fn_U, MB_OK);
		return false;
	}	
	
	char buff3[BUFF_SIZE];
	Archive ar3( &f3, Archive::store, BUFF_SIZE, buff3 );
	try{
		// ��������� ��������� ��������� �����	
		ar3 << rows;		
		ar3 << cols;
		
		for(long j = 0; j < rows; j++)
		{
			sparse_row_simple row_jU; row_jU.clear();
			for (int i = j; i < rows; i++)
			{
				row_jU.push_back(sparse_row_element<double>(i,a_ref(j,i)));
			}
			ar3 << row_jU;
		}
	}
	catch(char * str)
	{
		MessageBox(0,str,"",0);
		return false;
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();
	}
	catch(...)
	{
		MessageBox(0,"unknown error of archive read","",0);
		return false;
	}

	// ��������� �������� ����
	ar3.Close();
	f3.Close();
	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////
	// ��������� �������� ����

	AFile f2;
	if( !f2.Open( fn_P, GENERIC_WRITE, CREATE_NEW) ) 
	{
		MessageBox(0, "Holesski 1\nUnable to open file" , fn_P, MB_OK);
		return false;
	}	
	
	char buff2[BUFF_SIZE];
	Archive ar2( &f2, Archive::store, BUFF_SIZE, buff2 );
	try{
		// ��������� ��������� ��������� �����	
		ar2 << rows;		
		
		char buffjs[BUFF_SIZE];
		for(long j = 0; j < rows; j++)
		{
			ar2 << p[j];
		}
	}
	catch(char * str)
	{
		MessageBox(0,str,"",0);
		return false;
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();
	}
	catch(...)
	{
		MessageBox(0,"unknown error of archive read","",0);
		return false;
	}

	// ��������� �������� ����
	ar2.Close();
	f2.Close();
	///////////////////////////////////////////////////////////////////////

	delete[] a;
	delete[] p;
	return true;
}
bool InverseProblem_Solving (bool to_print, const char * fn_operator_transponed, 
							 const char * fn_min_sq_mat, 
							 const char * fn_L, 
							 const char * fn_U, 
							 const char * fn_P, 
							 vector<double> b, vector<double> & sol, double alpha, vector<double> sol_mean)
{
	//printf("InverseProblemSolving by:\n%s\n%s\n\n", fn_operator_transponed, fn_Lt);
	bool res = false;


	char buff[BUFF_SIZE];
	long pivots;

	AFile f;
	if( ! f.Open( fn_P, GENERIC_READ, OPEN_EXISTING) ) 
	{
		MessageBox(0, "Unable to open file" , fn_P, MB_OK);
		return false;
	}
	vector<int> p;
	
	Archive ar( &f, Archive::load, BUFF_SIZE, buff );
	try
	{
		// ������ ���������
		ar >> pivots;
		int pivot;
		for (long r = 0; r < pivots; r++)
		{
			ar >> pivot;
			p.push_back(pivot);
		}
	}
	catch(char * str)
	{
		MessageBox(0,str,"",0);
		return false;
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();
	}
	catch(...)
	{
		MessageBox(0, "unknown error of archive read 1","",0);
		return false;
	}


	vector<double> B;
	if(FormMinSquareB(fn_operator_transponed, b, B, alpha, sol_mean))
	{
		vector<double> pB(pivots);
		for (long r = 0; r < pivots; r++)
		{
			pB[r] = B[p[r]];
		}

		//for (long i = 0; i < B.size(); i++)
		//	printf ("B[%u] = %f\n", i, B[i]);

		bool result = tria_solve_of_down_and_up(fn_L, fn_U, pB, sol);

		if (to_print)
		{
			vector<double> rec_signal_;
			printf("Error of solve the min sq mat in tria_solve_of_down_and_up\n");
			ErrorOfMinSqProblemSolving(fn_min_sq_mat, B, sol, " tria_solve_of_down_and_up", rec_signal_);
		}
		//printf("rec_signal\n");

		//for (long i = 0; i <  rec_signal_.size();i++)
		//	printf ("%d\tB = %f\tB rec = %f\n", i, B[i], rec_signal_[i]);


		return result;

	}

	return res;
}

bool InverseProblem_Solving (bool to_print, const char * fn_operator_transponed, 
							 const char * fn_min_sq_mat, 
							 const char * fn_Lt, 
							 vector<double> b, vector<double> & sol, double alpha, vector<double> sol_mean)
{
	//printf("InverseProblemSolving by:\n%s\n%s\n\n", fn_operator_transponed, fn_Lt);
	bool res = false;

	vector<double> B;
	if(FormMinSquareB(fn_operator_transponed, b, B, alpha, sol_mean))
	{
		//for (long i = 0; i < B.size(); i++)
		//	printf ("B[%u] = %f\n", i, B[i]);
#if 0
		vector<double> y;

		long cols;
		vector<sparse_row> Lt;
		LoadMatrix<sparse_row>(fn_Lt, Lt, cols);

		if (tria_solve_of_down(Lt, B, y))
		{
			if (tria_solve_of_up(Lt, y, sol))
			{
				return true;
			}
		}
#else
		bool result = tria_solve_of_down_and_up(fn_Lt, B, sol);

		if (to_print)
		{
			vector<double> rec_signal_;
			printf("Error of solve the min sq mat in tria_solve_of_down_and_up\n");
			ErrorOfMinSqProblemSolving(fn_min_sq_mat, B, sol, " tria_solve_of_down_and_up", rec_signal_);
		}
		//printf("rec_signal\n");

		//for (long i = 0; i <  rec_signal_.size();i++)
		//	printf ("%d\tB = %f\tB rec = %f\n", i, B[i], rec_signal_[i]);


		return result;

#endif
	}

	return res;
}

bool InverseProblemSolving_(char * fn_operator_wav, vector<double> & t, vector<double> & b, vector<double> & sol, string name)
{
    //vector<sparse_row_simple> at; ������������� ������� � ����������������� ����
	vector<long> file_pointers;


	char buff[BUFF_SIZE];
	long _cols, _rows;
	bool res = false;

	AFile f;
	if( f.Open( fn_operator_wav, GENERIC_READ, OPEN_EXISTING) ) 
	{
		Archive ar( &f, Archive::load, BUFF_SIZE, buff );
		try
		{
			ar >> _rows;
			ar >> _cols;

			file_pointers.resize(_rows+1);
			file_pointers[0] = 2*sizeof(long);
			sparse_row_simple row_s;
			for (long r = 0; r < _rows; r++)
			{
				row_s.clear();
				ar >> row_s;
				file_pointers[r+1] = file_pointers[r] + (row_s.size() + 1)*(sizeof(long) + sizeof(double));
			}

			// ������� ����������� ������� ������� ���������� ��������� 
			// � ����������� ����������� ���������� ����������
			//bool res = SLAU3(m, cols, b, sol);

			// ������� ��������� ������� ���������� ���������
			// �� ������������� ����������� ������� 
			// ��������� ���������� ������� ���������
			
			size_t cols = _rows;
			size_t rows = _cols;
			
			printf("InverseProblemSolving rows = %u cols = %u\n",  rows, cols);

			size_t i, r, c;

			vector<sparse_row > A;
			vector<double> B(cols);
			
			vector<long> vc(cols); size_t ic;
			index_for_sort * vic  = new index_for_sort[cols];

			sparse_row row;
			for (i = 0; i < cols; i++)
			{
		printf("%u %u ", i, cols);

				sparse_row_simple at_i;
				at_i.clear();
				f.Seek(file_pointers[i], FILE_BEGIN);ar.ClearReadBuffer();
				ar >> at_i;

				// ��������� ������ ���������� ������� ���������
				row.clear();
				size_t row_size = 0;

				for (ic = i; ic < cols; ic++)
				{
					vic[ic-i].i = ic;
					vic[ic-i].sort_val = rand();
				}
				qsort( (void *)vic, (size_t)(cols-i), sizeof(index_for_sort), compare_index_for_sort );
				for (ic = i; ic < cols; ic++)
				{
					vc[ic] = vic[ic-i].i;
				}

				//for (c = i; c < cols; c++)
				for (ic = i; ic < cols; ic++)
				{
					c = vc[ic];

					sparse_row_simple at_c;
					at_c.clear();
					f.Seek(file_pointers[c], FILE_BEGIN);ar.ClearReadBuffer();
					ar >> at_c;

					// A[i][c] = sum(a[r][i]*a[r][c], r=1..rows);
					// B[i]    = sum(a[r][i]*b[r]   , r=1..rows);
					double A_i_c = at_i.ScalarProduct_fast(at_c);
					if (c == i)
					{
						printf ("%u %f ", c, A_i_c);
					}

					// printf(" %f %f \n", A_i_c, B[i]);

					if (row.put(c, A_i_c))
						row_size++;
				}			
				B[i]         = at_i.ScalarProduct(b);
		printf("%u\n",row_size);
				A.push_back(row);
			}
			
			delete [] vic;

				
			/*vector<sparse_row > AA;
			size_t __cols;
			LoadMatrix(filename_out, ms, __cols);*/


			res = solve_using_Holesski_tria_matrixes(A, B, sol); 	
				
			//vector<SparseRow> a = Transponate(at, rows);	
			//ErrorOfInverseProblemSolving(a, rows, t, b, sol, name);

		}
		catch(char * str)
		{
			MessageBox(0,str,"",0);
		}
		catch (CException* pe)
		{
			// catch errors from WinINet 
			TCHAR szErr[4098]; 
			pe->GetErrorMessage(szErr, 4098); 
			AfxMessageBox(szErr);
			pe->Delete();
		}
		catch(...)
		{
			MessageBox(0,"unknown error of archive read","",0);
		}
		
		ar.Close();
		f.Close();
	}
	else
	{
		MessageBox(0, "Unable to open file" , fn_operator_wav, MB_OK);
	}

	return res;
}

bool InverseProblemSolving(vector<SparseRow> & at, vector<double> & t, vector<double> & b, vector<double> & sol, string name)
{
    //vector<sparse_row_simple> at ������������� ������� � ����������������� ����
	
	// ������� ����������� ������� ������� ���������� ��������� 
	// � ����������� ����������� ���������� ����������
	//bool res = SLAU3(m, cols, b, sol);

	// ������� ��������� ������� ���������� ���������
	// �� ������������� ����������� ������� 
	// ��������� ���������� ������� ���������
	
	size_t cols = at.size();
	size_t rows = b.size();
	
	printf("InverseProblemSolving rows = %u cols = %u\n",  rows, cols);


	size_t i, r, c;

	vector<sparse_row > A;
	vector<double> B(cols);
	
	vector<long> vc(cols); size_t ic;
	index_for_sort * vic  = new index_for_sort[cols];

	sparse_row row;
	for (i = 0; i < cols; i++)
	{
printf("%u %u ", i, cols);
		// ��������� ������ ���������� ������� ���������
		row.clear();
		size_t row_size = 0;

		for (ic = i; ic < cols; ic++)
		{
			vic[ic-i].i = ic;
			vic[ic-i].sort_val = rand();
		}
		qsort( (void *)vic, (size_t)(cols-i), sizeof(index_for_sort), compare_index_for_sort );
		for (ic = i; ic < cols; ic++)
		{
			vc[ic] = vic[ic-i].i;
		}


		//for (c = i; c < cols; c++)
		for (ic = i; ic < cols; ic++)
		{
			c = vc[ic];
			// A[i][c] = sum(a[r][i]*a[r][c], r=1..rows);
			// B[i]    = sum(a[r][i]*b[r]   , r=1..rows);
			double A_i_c = at[i].ScalarProduct_fast(at[c]);
			if (c == i)
			{
				printf ("%u %f ", c, A_i_c);
			}

			// printf(" %f %f \n", A_i_c, B[i]);

			if (row.put(c, A_i_c))
				row_size++;
		}			
		B[i]         = at[i].ScalarProduct(b);
printf("%u\n",row_size);
		A.push_back(row);
	}
	
	delete [] vic;

	bool res = solve_using_Holesski_tria_matrixes(A, B, sol); 	
		
	vector<SparseRow> a;
	Transponate(at, rows, a);	
	ErrorOfInverseProblemSolving(a, rows, t, b, sol, name);

	return res;
}

Grid * CreateProfileGrid2D( MyMethodsData & mmd )
{        
	//����� ��������� ����
	// ���� �� ������� ������������� ���������
	Grid * grid = new Grid;
    
	grid->gridSection.nRow = mmd.rows;
	grid->gridSection.nCol = mmd.cols;

	// ���������� ������ ������� �� X � �� Y �
	// � �������� �������������� ���������� �������� ��, �� ������� ������ ������
	if (mmd.delta__x > mmd.delta__y)
	{
		//������� �� x
		grid->gridSection.xLL = mmd.x0;
		grid->gridSection.xSize = mmd.delta_x;
	}
	else
	{
		//������� �� y
		grid->gridSection.xLL = mmd.y0;
		grid->gridSection.xSize = mmd.delta_y;
	}

	grid->gridSection.yLL = mmd.z0 - (mmd.rows - 1) * mmd.delta_z;
	grid->gridSection.ySize = mmd.delta_z;					  
					  
	grid->gridSection.z = AllocDoubleMat(grid->gridSection.nRow, grid->gridSection.nCol);
	grid->gridSection.BlankValue = BLANK_VALUE;//1.70141e38;// nodes are blanked if greater or equal to this value

	grid->faultSection.nTraces = 0;
	grid->faultSection.nVertices = 0;
	grid->faultSection.traces = NULL;
	grid->faultSection.vertexes = NULL;

	printf("The grid is created\n");

	return grid;
}

Grid4 * CreateProfileGrid3D( MyMethodsData3 & mmd )
{        
	//����� ��������� ����
	// ���� �� ������� ������������� ���������
	Grid4 * grid = new Grid4;
    
	grid->grid4Section.nRow = mmd.rows;
	grid->grid4Section.nCol = mmd.cols;
	grid->grid4Section.nPag = mmd.pages;


	grid->grid4Section.xLL = mmd.x0;
	grid->grid4Section.xSize = mmd.delta_x;

	grid->grid4Section.yLL = mmd.y0;
	grid->grid4Section.ySize = mmd.delta_y;

	// grid->grid4Section.zLL = mmd.z0 - (mmd.pages - 1) * mmd.delta_z;// 
	// �������� ������� �������� ���� ��� ������� ����������� �� ������� delta_z
	grid->grid4Section.zLL = mmd.z0 - mmd.pages * mmd.delta_z;
	grid->grid4Section.zSize = mmd.delta_z;					  
					  
	grid->grid4Section.v = Alloc3DMat<double>(grid->grid4Section.nPag, grid->grid4Section.nRow, grid->grid4Section.nCol);
	grid->grid4Section.BlankValue = BLANK_VALUE;//1.70141e38;// nodes are blanked if greater or equal to this value

	printf("The grid4 is created\n");

	return grid;
}

#define ON_THE_FLY_STORING 1
#define SPARSE_OUT_W 1
void DoMyMethod2(FILE * description, 
				 MyMethodsData& mmd,				 
				 auto_build_parametrs& ab,
				 vector<double> & X,
				 vector<double> & Y,
				 vector<double> & Z, // ��������� ��������� - ����� �������
				 vector<double> & signal,
				 string name)
{
	printf ( "DoMyMethod %s\n", name.c_str() );

	long signal_len = signal.size(); // ����� ������� 

	// ��������� ����� � ��������
	// int pw_rcd = 2;
	//cout << "Enter pw_rcd rows/cols deviation pw (0,1,2,...)?\n";
	//cin >> pw_rcd;
	int rcd = pow(2.0, mmd.pw_rcd);

	// rows = cols / rcd;
	// rows * cols > signal_len
	// cols * cols / rcd > signal_len
	// cols > sqrt( signal_len * rcd )
	// cols is power of 2
	// 


	//long Nr=1, Nc=1;

	// ����� ����������� ������������� ����� ������� 2*Nr * 2*Nc
	// ����� ��������� signal_len

	// ���������� �������� ������� 2*Nr * 2*Nc ~ signal_len
	//  Nr * Nc ~ signal_len / 4
	//  as   (rows = cols / rcd) and (rcd = pow(2,pw_rcd)) so  Nc = Nr + pw_rcd;
	//  Nr * (Nr + pw_rcd) ~ signal_len / 4
	//  Nr * Nr + Nr * pw_rcd - signal_len / 4 ~ 0

	// D = pw_rcd * pw_rcd - 4 * 1 * (-signal_len / 4);
	// D = pw_rcd * pw_rcd + signal_len;

	// 

	//  Nr = Nc ~ sqrt(signal_len / 4)
#if 0
	// ��� ����� ����, ��� �� ��������� � ����������� 
	// ������ ����� ������ � ��� ������, ���� �� ����� 
	// �������� ������������ � �������������� �������
	double near_Nr = sqrt(double(signal_len) / 4.0);
	// ���� � ���� �������� ��������������� �������
	Nc = Nr = ceil(near_Nr);

	// ���� � ���� �������� ��������������� �������
	// Nr = Nc = floor(near_Nr);
#else
	// � ������ ����, ��� �� ��������� � ����������� 
	// ������ ����� ������ � ��� ������, ���� �� ����� 
	// �������� ������������ � �������������� �������
	double D = mmd.pw_rcd * mmd.pw_rcd + signal_len;
	double near_Nr = ( - mmd.pw_rcd + sqrt(D)) / 2.0;
	// ���� � ���� �������� ��������������� �������
	mmd.Nr = ceil(near_Nr);

	// ���� � ���� �������� ��������������� �������
	// Nr = floor(near_Nr);

	mmd.Nc = mmd.Nr + mmd.pw_rcd;
#endif

	// ��������� ����� ������
	long Nq = 2*mmd.Nr * 2*mmd.Nc;

	//long increaser_pw = 2;
	cout << "Enter increaser_pw (0,1,2,...)?\n";
	cin >> mmd.increaser_pw;
	long increaser = pow(2.0, mmd.increaser_pw);


	double near_cols = sqrt( double(signal_len * rcd) );

	// ������ ����� - ������� ������
	mmd.cols = increaser * pow(2.0, ceil(log10(double(near_cols))/log10(2.0))); // ����� ������� 
	mmd.rows = mmd.cols / rcd;// � ��� �������


	cout << "cols = " << mmd.cols << endl;
	cout << "rows [" << mmd.rows << "]\n";
	cout << "Do you want reenter?\n";

	char answer;
	cin >> answer;
	if (answer == 'y' || answer == 'Y')
	{
		cout << "cols?\n";
		cin >> mmd.cols;
		cout << "rows?\n";
		cin >> mmd.rows;
	}

	if (mmd.cols < 2*mmd.Nc+2)
	{
		printf("Error: (cols (%ld)) < (2*Nc(%d)+2)(%ld)\n", mmd.cols, mmd.Nc, 2*mmd.Nc+2);
		return;
	}	
	if (mmd.rows < 2*mmd.Nr+2)
	{
		printf("Error: (rows (%ld)) < (2*Nr(%d)+2)(%ld)\n", mmd.rows, mmd.Nr, 2*mmd.Nr+2);
		return;
	}

	double min__x, min__y, min__z;
	double max__x, max__y, max__z;
	//double delta__x;
	//double delta__y;

	GetProfileDirection(X, Y, Z,
		min__x, min__y, min__z,
		max__x, max__y, max__z,
		mmd.delta__x, mmd.delta__y);

	mmd.x0 = min__x;
	mmd.y0 = min__y;

	mmd.delta_x = mmd.delta__x / mmd.cols;
	mmd.delta_y = mmd.delta__y / mmd.cols;

	mmd.delta_z = sqrt(mmd.delta_x*mmd.delta_x + mmd.delta_y*mmd.delta_y);

	long rows_cols = mmd.rows*mmd.cols;

	printf ( "DoMyMethod cols = %ld rows = %ld\n", mmd.cols,  mmd.rows);

	// ���������� ������������ ������ ������

	bool the_martix_on_memory = false;

	char spm_filename[4096];
	sprintf(spm_filename, "%s\\operator.spm", dir_out);

	//vector<SparseRow> * m = the_martix_on_memory ? new vector<SparseRow> : NULL;

	vector<double> sol(rows_cols, 0.0);

	bool to_fill_matrix = true;

	if (to_fill_matrix)
	{
		int smoof_power = 1024;

		smoof_power /= 2;
		smoof_power *= 2;

		printf("Filling of matrix\n");
		// ��������� ������� ��������� ������ ������, 
		// ����� ����� ����� ����� ������� 
		// (��� ��������� ����� ���������� �������� - 
		// ���������� �������� �� ����� ���, ��� �����, �� ������ �������)
		// �� ���� ��������� ������� ������������� ��������� 
		// ���������� ���������������� �������
		// �� ������ ��������� ����� �������� ��������� (������) �� ��������
		FillingTheMatrix(smoof_power, mmd.k_oslablenie, ab.k, NULL, spm_filename, mmd.rows, mmd.cols, 
			mmd.x0, mmd.y0, mmd.z0,
			mmd.delta_x, mmd.delta_y, mmd.delta_z,
			X, Y, Z);
	}

		
	printf("The matrix is filled!!!\n");

    
	if (!CheckMyLicense()) return;

        
	// ����� ��������� ����
	// ���� �� ������� ������������� ���������
	Grid * grid = CreateProfileGrid2D(mmd);


	printf("Creating the matrix in Frequency region\n");
#if !ON_THE_FLY_STORING
	//������� ��������� ������ ������ � ��������� �������
	vector<vector<double> > mw(signal_len);
	for (long j = 0; j < signal_len; j++)
		mw[j].resize(Nq);
#endif

	
	ap::real_1d_array a;
	a.setbounds( 0, max(mmd.cols, mmd.rows) );
	bool inversefft = true;

	printf("Start of filling the matrix in Frequency region %ld %ld\n", 2*mmd.Nr, 2*mmd.Nc);
	//char vvd_filename[4096];
	sprintf(mmd.fn_operator_wav, "%s\\operator_freq.vvd", dir_out);

#if ON_THE_FLY_STORING
	StoreMatrixHeader(mmd.fn_operator_wav, signal_len, Nq, true);
#endif
	/*DWORD 
		time_eplased1 = 0,
		time_start = GetCurrentTime();*/
	// ���������� ������������ ���������� ���������������� ������
	for(long rw = 2, q = 0; rw <= 1 + 2*mmd.Nr; rw++)
	{
		printf("Filling the matrix in Frequency region %ld %ld\n", rw, 1 + 2*mmd.Nr);
		for(long cw = 2; cw <= 1 + 2*mmd.Nc; cw++)
		{
			// ������� ��������� ���������������� "������" �� ������� �������
			ZeroDoubleMat(grid->gridSection.z, grid->gridSection.nRow, grid->gridSection.nCol);

			//printf("rw = %ld, cw = %ld\n", rw, cw);
			
			grid->gridSection.z[rw][cw] = 1.0;

	//DWORD time_start1 = GetCurrentTime();
			FastFourierTransform2D(grid, a, inversefft, rw);
	//time_eplased1 += GetCurrentTime() - time_start1;

			// �������������� ������ ������� ������� ������� � ������ �������
			for (long jj = 0; jj < grid->gridSection.nRow; jj++)
			{
				for (long ii = 0; ii < grid->gridSection.nCol; ii++)
				{
					// ������ � ������ ������� ��������� ������ ������
					long i = jj * mmd.cols + ii;
					sol[i] = grid->gridSection.z[jj][ii];
				}
			}

			// �� ������ ������� ��������� ���������� ������ ������
			// � �������� q-��� ������� ����� �������
			// ������� ����� �������� �������� ������ ������ � ��������� �������
			/*if (m)
			{
				for (long j = 0; j < signal_len; j++)
				{
					mw[j][q] = (*m)[j].ScalarProduct(sol);
				}
			}
			else
			{*/
#if ON_THE_FLY_STORING
				if(!ApplyOperator(signal_len, sol, spm_filename, mmd.fn_operator_wav))
				{
					printf("Error while ApplyOperator()\n");
					return;
				}
#else
				if(!ApplyOperator(signal_len, q, sol, spm_filename, mw))
				{
					printf("Error while ApplyOperator()\n");
					return;
				}
#endif

			//}
			q++;
		}
	}

	//DWORD time_stop = GetCurrentTime();
	//printf("TimeEplased = %d %d\n",  time_stop - time_start, time_eplased1);

#if !ON_THE_FLY_STORING
	StoreMatrix(vvd_filename, mw, true);
#endif

	printf("The matrix in Frequency region if filled!!!\n");
/*
}
void DoMyMethod2D_part2()
{*/
	printf("Start of solve the inverse problem\n");
#if ON_THE_FLY_STORING
	//������� ��������� ������ ������ � ��������� �������
	vector<vector<double> > mw;
#endif
	LoadMatrix(mmd.fn_operator_wav, mw);
	// ������� ������� �������� ������ � ��������� �������
	vector<double> solw(Nq);

	if(!InverseProblemSolving(mw, Nq, signal, solw))
	{
	}

	printf("The inverse problem is solved!!!\n");
	printf("Form the frequency matrix from the inverse problem solving!!!\n");

	// ��������� ��������� �������
	ZeroDoubleMat(grid->gridSection.z, grid->gridSection.nRow, grid->gridSection.nCol);
	for(long rw = 2, q = 0; rw <= 1 + 2*mmd.Nr; rw++)
	{
		for(long cw = 2; cw <= 1 + 2*mmd.Nc; cw++)
		{
			grid->gridSection.z[rw][cw] = solw[q];
			q++;
		}
	}

	printf("Form the razrez matrix by fft\n");
			
	// �������, ��������� ���������������� "������" �� ��������� �������
	FastFourierTransform2D(grid, a, inversefft);

	printf("Save the razrez matrix\n");


	double min_z = DBL_MAX;
	double max_z = -DBL_MAX;

	double z_value;

	for (long ii = 0; ii < grid->gridSection.nCol; ii++)
	{
		for (long jj = 0; jj < grid->gridSection.nRow; jj++)
		{
			z_value = grid->gridSection.z[jj][ii];
			if (max_z < z_value) max_z = z_value;
			if (min_z > z_value) min_z = z_value;
		}
	}

	// ���� ��� ����� ��������

	for (long ii = 0; ii < grid->gridSection.nCol; ii++)
	{
		long k = grid->gridSection.nRow/2;
		long L = grid->gridSection.nRow-1;
		for (long jj = 0; jj < k; jj++)
		{
			z_value = grid->gridSection.z[L][ii];
			grid->gridSection.z[L][ii] = grid->gridSection.z[jj][ii];
			grid->gridSection.z[jj][ii] = z_value;
			L--;
		}
	}

	grid->gridSection.zMax = max_z;
	grid->gridSection.zMin = min_z;
	
	grid->faultSection.nTraces = 0;
	grid->faultSection.nVertices = 0;
	grid->faultSection.traces = NULL;
	grid->faultSection.vertexes = NULL;
	//-----------------------------------

	char file[2048];
	sprintf(file, "%s\\MyMethod2_of_%s.grd", dir_out, name.c_str());
	char * p;
	while (p=strchr (file,'\"'))
	{
		*p = '_';
	}
	SaveAsSurfer7Grid(file, grid);

	FreeDoubleMat(grid->gridSection.z);
	delete grid;
	printf("Yes!!!\n");
}


void DoMyMethod3(int type, // ��� ������ ������
				 FILE * description,
				 double k_oslablenie,
				 auto_build_parametrs& ab, 
				 vector<double> & X,
				 vector<double> & Y,
				 vector<double> & Z, // ��������� ��������� - ����� �������
				 vector<vector<anten_direction> > & A,
				 double z0,// ��������� ������ �����������
				 vector<double> & signal,
				 string name)
{
	printf ( "DoMyMethod %s\n", name.c_str() );

	long signal_len = signal.size(); // ����� ������� 

	// ��������� ����� � ��������
	int pw_pcd = 1;
	cout << "Enter pw_pcd pages/cols deviation pw (0,1,2,...)?\n";
	cin >> pw_pcd;
	int pcd = pow(2.0, pw_pcd);
	// pages = cols / pcd;
	// rows ~ cols
	// pages * rows * cols > signal_len
	// cols * cols * cols / pcd > signal_len
	// cols > sqrt3( signal_len * rcd ) = pow(double(signal_len * pcd), 1.0/3.0)
	// cols is power of 2
	// 

	long Np=1, Nr=1, Nc=1;

	// ����� ����������� ������������� ����� ������� 2*Np * 2*Nr * 2*Nc
	// ����� ��������� signal_len

	// ���������� �������� ������� 2*Np * 2*Nr * 2*Nc ~ signal_len
	//  Np * Nr * Nc ~ signal_len / 8
	//			Np ~ pow(signal_len / 8, 1 / 3)
	//  as   (pages = cols / pcd, rows = cols) and (pcd = pow(2,pw_pcd)) so Nr = Nc = Np + pw_pcd;
	//  Np * (Np + pw_pcd) * (Np + pw_pcd) ~ signal_len / 8

#if 1
	// ��� ����� ����, ��� �� ��������� � ����������� 
	// ������ ����� ������ � ��� ������, ���� �� ����� 
	// �������� ������������ � �������������� �������
	double near_Np = pow(double(signal_len) / 8.0, 1.0/3.0);
	// ���� � ���� �������� ��������������� �������
	Np = Nr = Nc = ceil(near_Np);

	// ���� � ���� �������� ��������������� �������
	// Np = Nr = Nc = floor(near_Np);
#else
	// � ������ ����, ��� �� ��������� � ����������� 
	// ������ ����� ������ � ��� ������, ���� �� ����� 
	// �������� ������������ � �������������� �������
	double D = pw_rcd * pw_rcd + signal_len;
	double near_Np = ( - pw_rcd + sqrt(D)) / 2.0;
	// ���� � ���� �������� ��������������� �������
	Np = ceil(near_Np);

	// ���� � ���� �������� ��������������� �������
	// Np = floor(near_Np);

	Nr = Nc = Np + pw_pcd;
#endif

	// ��������� ����� ������
	long Nq = 2*Np * 2*Nr * 2*Nc;


	long increaser_pw = 2;
	cout << "Enter increaser_pw (0,1,2,...)?\n";
	cin >> increaser_pw;
	long increaser = pow(2.0, increaser_pw);

	double near_cols = pow(double(signal_len * pcd), 1.0/3.0);

	// ������ ����� - ������� ������
	long cols = increaser * pow(2.0, ceil(log10(double(near_cols))/log10(2.0))); // ����� ������� 
	long rows = cols;
	long pages = cols / pcd;// � ��� �������

	cout << "cols = " << cols << endl;
	cout << "rows [" << rows << "]\n";
	cout << "pages [" << pages << "]\n";
	cout << "Do you want reenter?\n";

	char answer;
	cin >> answer;
	if (answer == 'y' || answer == 'Y')
	{
		cout << "cols?\n";
		cin >> cols;
		cout << "rows?\n";
		cin >> rows;
		cout << "pages?\n";
		cin >> pages;
	}

	
	if (pages < 2*Np+2)
	{
		printf("Error: (pages (%ld)) < (2*Np(%d)+2)(%ld)\n", pages, Np, 2*Np+2);
		return;
	}	
	if (rows < 2*Nr+2)
	{
		printf("Error: (rows (%ld)) < (2*Nr(%d)+2)(%ld)\n", rows, Nr, 2*Nr+2);
		return;
	}
	if (cols < 2*Nc+2)
	{
		printf("Error: (cols (%ld)) < (2*Nc(%d)+2)(%ld)\n", cols, Nc, 2*Nc+2);
		return;
	}

	double min__x, min__y, min__z;
	double max__x, max__y, max__z;
	double delta__x;
	double delta__y;

	GetProfileDirection(X, Y, Z,
		min__x, min__y, min__z,
		max__x, max__y, max__z,
		delta__x, delta__y);

	double delta__z = max__z - min__z;

	double x0 = min__x;
	double y0 = min__y;

	double delta_x = delta__x / cols;
	double delta_y = delta__y / rows;
	double delta_z = delta__y / pages;

	long rows_cols_pages = rows*cols*pages;

	printf ( "DoMyMethod cols = %ld rows = %ld pages = %ld\n", cols,  rows, pages);

	// ���������� ������������ ������ ������

	char spm_filename[4096];
	sprintf(spm_filename, "%s\\operator.spm", dir_out);

	vector<double> sol(rows_cols_pages, 0.0);

	bool to_fill_matrix = true;

	double pw_dnp = 2,
		min_value = 0.03;
	int wave_type = 1;

	sourse_power_model spm;


	if (to_fill_matrix)
	{
		//int smoof_power = 1024;
		int smoof_power = 4096;

		smoof_power /= 2;
		smoof_power *= 2;

		printf("Filling of matrix\n");
		// ��������� ������� ��������� ������ ������, 
		// ����� ����� ����� ����� ������� 
		// (��� ��������� ����� ���������� �������� - 
		// ���������� �������� �� ����� ���, ��� �����, �� ������ �������)
		// �� ���� ��������� ������� ������������� ��������� 
		// ���������� ���������������� �������
		// �� ������ ��������� ����� �������� ��������� (������) �� ��������
		switch(type)
		{
		case 0:
			{
				FillingTheMatrix3D(smoof_power, k_oslablenie, ab.k, NULL, spm_filename, 
					rows, cols, pages,
					x0, y0, z0,
					delta_x, delta_y, delta_z,
					X, Y, Z, pw_dnp, wave_type);
			}
			break;
		case 1:
			{
				FillingTheMatrix3D_with_napravlennosty_diagramm(
					k_oslablenie, 
					NULL, spm_filename, 
					rows, cols, pages,
					x0, y0, z0,
					delta_x, delta_y, delta_z,
					X, Y, Z, A,
					pw_dnp,
					min_value,
					wave_type,
					spm);
			}
			break;
		}
	}

		
	printf("The matrix is filled!!!\n");

	if (!CheckMyLicense()) return;


        
	//����� ��������� ����
	Grid4 * grid = new Grid4;
    
	grid->grid4Section.nRow = rows;
	grid->grid4Section.nCol = cols;
	grid->grid4Section.nPag = pages;


	grid->grid4Section.xLL = x0;
	grid->grid4Section.xSize = delta_x;

	grid->grid4Section.yLL = y0;
	grid->grid4Section.ySize = delta_y;

	grid->grid4Section.zLL = z0 - (pages - 1) * delta_z;
	grid->grid4Section.zSize = delta_z;					  
					  
	grid->grid4Section.v = Alloc3DMat<double>(grid->grid4Section.nPag, grid->grid4Section.nRow, grid->grid4Section.nCol);
	grid->grid4Section.BlankValue = BLANK_VALUE;//1.70141e38;// nodes are blanked if greater or equal to this value

	printf("The grid4 is created\n");

	printf("Creating the matrix in Frequency region\n");
#if !ON_THE_FLY_STORING
	//������� ��������� ������ ������ � ��������� �������
	vector<vector<double> > mw(signal_len);
	for (long j = 0; j < signal_len; j++)
		mw[j].resize(Nq);
#endif

	
	ap::real_1d_array a;
	a.setbounds( 0, max(max(cols, rows), pages) );
	bool inversefft = true;

		
	printf("Start of filling the matrix in Frequency region %ld %ld\n", 2*Nr, 2*Nc);
	char vvd_filename[4096];
	sprintf(vvd_filename, "%s\\operator3_freq.vvd", dir_out);

#if ON_THE_FLY_STORING
	StoreMatrixHeader(vvd_filename, signal_len, Nq, true);
#endif
	// ���������� ������������ ���������� ���������������� ������
	for(long pw = 2, q = 0; pw <= 1 + 2*Np; pw++)
	{
printf("Filling the matrix in Frequency region %ld %ld\n", pw, 1 + 2*Np);
		for(long rw = 2; rw <= 1 + 2*Nr; rw++)
		{
			for(long cw = 2; cw <= 1 + 2*Nc; cw++)
			{
				// ������� ��������� ���������������� "������" �� ������� �������
				Zero3DMat<double>(grid->grid4Section.v, grid->grid4Section.nPag, grid->grid4Section.nRow, grid->grid4Section.nCol);
				grid->grid4Section.v[pw][rw][cw] = 1.0;

				FastFourierTransform3D(grid, a, inversefft, pw, rw);

				// �������������� ������ ������� ������� ������� � ������ �������
				for (long pp = 0; pp < grid->grid4Section.nPag; pp++)
				{
					for (long jj = 0; jj < grid->grid4Section.nRow; jj++)
					{
						for (long ii = 0; ii < grid->grid4Section.nCol; ii++)
						{
							// ������ � ������ ������� ��������� ������ ������
							long i = pp * rows * cols + jj * cols + ii;
							sol[i] = grid->grid4Section.v[pp][jj][ii];
						}
					}
				}

				// �� ������ ������� ��������� ���������� ������ ������
				// � �������� q-��� ������� ����� �������
				// ������� ����� �������� �������� ������ ������ � ��������� �������
				/*for (long j = 0; j < signal_len; j++)
				{
					mw[j][q] = m[j].ScalarProduct(sol);
				}*/
#if ON_THE_FLY_STORING
				if(!ApplyOperator(signal_len, sol, spm_filename, vvd_filename))
				{
					printf("Error while ApplyOperator()\n");
					return;
				}
#else
				if(!ApplyOperator(signal_len, q, sol, spm_filename, mw))
				{
					printf("Error while ApplyOperator()\n");
					return;
				}
#endif
				q++;
			}
		}
	}

#if !ON_THE_FLY_STORING
	StoreMatrix(vvd_filename, mw, true);
#endif

	printf("The matrix in Frequency region if filled!!!\n");
/*
}
void DoMyMethod2D_part2()
{*/
	printf("Start of solve the inverse problem\n");
#if ON_THE_FLY_STORING
	//������� ��������� ������ ������ � ��������� �������
	vector<vector<double> > mw;
#endif
	LoadMatrix(vvd_filename, mw);
	// ������� ������� �������� ������ � ��������� �������
	vector<double> solw(Nq);

	if(!InverseProblemSolving(mw, Nq, signal, solw))
	{
	}

	printf("The inverse problem is solved!!!\n");
	printf("Form the frequency matrix from the inverse problem solving!!!\n");

	// ��������� ��������� �������
	Zero3DMat<double>(grid->grid4Section.v, grid->grid4Section.nPag, grid->grid4Section.nRow, grid->grid4Section.nCol);
	for(long pw = 2, q = 0; pw <= 1 + 2*Np; pw++)
	{
		for(long rw = 2; rw <= 1 + 2*Nr; rw++)
		{
			for(long cw = 2; cw <= 1 + 2*Nc; cw++)
			{
				grid->grid4Section.v[pw][rw][cw] = solw[q];
				q++;
			}
		}
	}

	printf("Form the razrez matrix by fft\n");
			
	// �������, ��������� ���������������� "������" �� ��������� �������
	FastFourierTransform3D(grid, a, inversefft);

	printf("Save the razrez matrix\n");


	double min_v = DBL_MAX;
	double max_v = -DBL_MAX;

	double v_value;

	for (long pp = 0; pp < grid->grid4Section.nPag; pp++)
	{
		for (long ii = 0; ii < grid->grid4Section.nCol; ii++)
		{
			for (long jj = 0; jj < grid->grid4Section.nRow; jj++)
			{
				v_value = grid->grid4Section.v[pp][jj][ii];
				if (max_v < v_value) max_v = v_value;
				if (min_v > v_value) min_v = v_value;
			}
		}
	}
#if 0
	// ���� ��� ����� ��������

	for (long ii = 0; ii < grid->grid4Section.nCol; ii++)
	{
		for (long jj = 0; jj < grid->grid4Section.nRow; jj++)
		{
			long k = grid->grid4Section.nPag/2;
			long L = grid->grid4Section.nPag-1;
			for (long pp = 0; pp < k; pp++)
			{
				v_value = grid->grid4Section.v[L][jj][ii];
				grid->grid4Section.v[L][jj][ii] = grid->grid4Section.v[pp][jj][ii];
				grid->grid4Section.v[pp][jj][ii] = v_value;
				L--;
			}
		}
	}
#endif
	grid->grid4Section.vMax = max_v;
	grid->grid4Section.vMin = min_v;
	
	//-----------------------------------

	char file[2048];
	sprintf(file, "%s\\MyMethod3_of_%s.cub", dir_out, name.c_str());
	char * p;
	while (p=strchr (file,'\"'))
	{
		*p = '_';
	}
	SaveAsSurfer7Grid4(file, grid);

	Free3DMat<double>(grid->grid4Section.v);
	delete grid;
	printf("Yes!!!\n");
}




void DoMyMethod2W(FILE * description, 
				  MyMethodsData& mmd,
				  Wavelet2D& w2,
				  auto_build_parametrs& ab,
				  vector<double> & X,
				  vector<double> & Y,
				  vector<double> & Z, // ��������� ��������� - ����� �������
				  //string name,
				  bool to_fill_matrix)
{
	fprintf (description, "DoMyMethod \n" );

	long signal_len = X.size(); // ����� ������� 

	// ��������� ����� � ��������
	// int pw_rcd = 2;
	int rcd = pow(2.0, mmd.pw_rcd);
	// rows = cols / rcd;
	// rows * cols > signal_len
	// cols * cols / rcd > signal_len
	// cols > sqrt( signal_len * rcd )
	// cols is power of 2
	// 
	fprintf (description, "pw_rcd = %d rcd = %d\n", mmd.pw_rcd, rcd);

	//bool have_pereopredelen_system = false;
	bool have_pereopredelen_system = true;

	// Nr ����� S ������������� �� ���������
	// Nc ����� S ������������� �� �����������
	// long Nr=1, Nc=1;

	// ����� ����������� S ������������� Nr * Nc
	// ����� ��������� signal_len

	// ���������� �������� ������� Nr * Nc ~ signal_len
	//  Nr * Nc ~ signal_len
	//  as   (rows = cols / rcd) and (rcd = pow(2,pw_rcd)) so  Nc = Nr * rcd;
	//  Nr * Nr * rcd ~ signal_len 
	//  Nr * Nr ~ signal_len / rcd

#if 0
	// ��� ����� ����, ��� �� ��������� � ����������� 
	// ������ ����� ������ � ��� ������, ���� �� ����� 
	// �������� ������������ � �������������� �������
	double near_Nr = sqrt(double(signal_len));
	if (have_pereopredelen_system)
	{
		// ���� � ���� �������� ��������������� �������
		Nr = Nc = floor(near_Nr);
	}
	else
	{
		// ���� � ���� �������� ��������������� �������
		Nc = Nr = ceil(near_Nr);
	}

#else
	// � ������ ����, ��� �� ��������� � ����������� 
	// ������ ����� ������ � ��� ������, ���� �� ����� 
	// �������� ������������ � �������������� �������
	double near_Nr = sqrt( double(signal_len) / rcd);
	
	if (have_pereopredelen_system)
	{
		// ���� � ���� �������� ��������������� �������
		mmd.Nr = floor(near_Nr);
	}
	else
	{
		// ���� � ���� �������� ��������������� �������
		mmd.Nr = ceil(near_Nr);
	}
	// ����� ������������� ������ � 2^n ��� , ��� �� ���������
	mmd.Nc = mmd.Nr * rcd;

#endif
	//Nr *= 4;
	//Nc *= 4;

	// ��������� ����� s �������������
	long Ns = mmd.Nr * mmd.Nc;

	fprintf (description, "Nr = %ld Nc = %ld Ns = %ld\n", mmd.Nr, mmd.Nc, Ns);

	//double near_cols = sqrt( double(signal_len * rcd) );


	long increaser = pow(2.0, mmd.increaser_pw);

	fprintf (description, "increaser_pw = %ld increaser = %ld\n", mmd.increaser_pw, increaser);

	// ������ ����� - ������� ������
	mmd.cols = increaser * mmd.Nc; // ����� ����� ������������� ��������� �� ����������� 
	mmd.rows = increaser * mmd.Nr; // ------------//--------------------- �� ������� (���������)

	fprintf (description, "rows = %ld cols = %ld\n", mmd.rows, mmd.cols);

	cout << "rows = " << mmd.rows << "\n";
	cout << "cols = " << mmd.cols << endl;

	cout << "Nr = " << mmd.Nr << endl;
	cout << "Nc = " << mmd.Nc << "\n";

/*	cout << "Do you want reenter?\n";

	char answer;
	cin >> answer;
	if (answer == 'y' || answer == 'Y')
	{
		cout << "cols?\n";
		cin >> cols;
		cout << "rows?\n";
		cin >> rows;
	}*/

	// ������������� �������� �������������� ��������� �������
	double min__x, min__y, min__z;
	double max__x, max__y, max__z;
	// ������ ������� �� X � �� Y
	//double delta__x;
	//double delta__y;

	GetProfileDirection(X, Y, Z,
		min__x, min__y, min__z,
		max__x, max__y, max__z,
		mmd.delta__x, mmd.delta__y);

	mmd.x0 = min__x;
	mmd.y0 = min__y;

	// ��� ����� ������� �� X � �� Y
	mmd.delta_x = mmd.delta__x / mmd.cols;
	mmd.delta_y = mmd.delta__y / mmd.cols;

	// ��� ����� ������������� ��������� �� z (�������)
	mmd.delta_z = sqrt(mmd.delta_x*mmd.delta_x + mmd.delta_y*mmd.delta_y);

	fprintf (description, "x0 = %f y0 = %f\n", mmd.x0, mmd.y0);
	fprintf (description, "delta_x = %f delta_y = %f delta_z = %f\n", mmd.delta_x, mmd.delta_y, mmd.delta_z);


	// ����� ����� ������������� ���������
	long rows_cols = mmd.rows*mmd.cols;

	printf ( "DoMyMethod cols = %ld rows = %ld\n", mmd.cols,  mmd.rows);

	// ���������� ������������ ������ ������
	
	bool the_martix_on_memory = false;

	

	//vector<double> sol(rows_cols, 0.0);

	if (to_fill_matrix)
	{
		sprintf(mmd.fn_operator_spm, "%s\\operator.spm", dir_out);
		
		int smoof_power = 1024;

		smoof_power /= 2;
		smoof_power *= 2;

	fprintf (description, "smoof_power = %d\n", smoof_power);

		printf("Filling of matrix\n");
		// ��������� ������� ��������� ������ ������, 
		// ����� ����� ����� ����� ������� 
		// (��� ��������� ����� ���������� �������� - 
		// ���������� �������� �� ����� ���, ��� �����, �� ������ �������)
		// �� ���� ��������� ������� ������������� ��������� 
		// ���������� ���������������� �������
		// �� ������ ��������� ����� �������� ��������� (������) �� ��������
		FillingTheMatrix(smoof_power, mmd.k_oslablenie, ab.k, NULL, mmd.fn_operator_spm, mmd.rows, mmd.cols, 
			mmd.x0, mmd.y0, mmd.z0,
			mmd.delta_x, mmd.delta_y, mmd.delta_z,
			X, Y, Z);
	}
		
	printf("The matrix is filled!!!\n");

	if (!CheckMyLicense()) return;

	bool to_fill_matrix_2 = to_fill_matrix;

	if (to_fill_matrix_2)
	{
		// ����� ������ ����
		// ���� �� ������� ������������� ���������
		Grid * grid = CreateProfileGrid2D(mmd);

		printf("Creating the matrix in S-Coefficient region\n");

	#if !ON_THE_FLY_STORING
		//������� ��������� ������ ������ � S �������
		vector<vector<double> > ms(signal_len);
		for (long j = 0; j < signal_len; j++)
			ms[j].resize(Ns);
	#endif
			
		printf("Start of filling the matrix in S-Coefficient region %ld %ld\n", mmd.Nr, mmd.Nc);
		
#if SPARSE_OUT_W
		sprintf(mmd.fn_operator_wav, "%s\\operator_wav.spm", dir_out);
#else
		sprintf(mmd.vvd_filename, "%s\\operator_wav.vvd", dir_out);
#endif
	#if ON_THE_FLY_STORING
#if SPARSE_OUT_W
		//������� ��������� � ����������������� ����
		StoreMatrixHeader(mmd.fn_operator_wav, Ns, signal_len);
#else
		StoreMatrixHeader(mmd.vvd_filename, signal_len, Ns, true);
#endif
	#endif

		Grid * wavSimage = InverseWaveletImage2D(w2, mmd.increaser_pw, mmd);

		char fn[1024]; 
		sprintf(fn, "%s\\iwsi.grd", 
			dir_out);
		
		// ���� ��� ����� ��������

		for (long ii = 0; ii < wavSimage->gridSection.nCol; ii++)
		{
			long k = wavSimage->gridSection.nRow/2;
			long L = wavSimage->gridSection.nRow-1;
			for (long jj = 0; jj < k; jj++)
			{
				double w_value = wavSimage->gridSection.z[L][ii];
				wavSimage->gridSection.z[L][ii] = wavSimage->gridSection.z[jj][ii];
				wavSimage->gridSection.z[jj][ii] = w_value;
				L--;
			}
		}
		SaveAsSurfer7Grid(fn, wavSimage);

		double * psol = new double[rows_cols];
		memset(psol, 0, rows_cols*sizeof(double));
		long shift_c = 2 * (w2.right_h_c/2 - (w2.rh_c.Length()-2)/2);
		long shift_r = 2 * (w2.right_h_r/2 - (w2.rh_r.Length()-2)/2);

		// ���������� ������������ ���������� ���������������� ������
		long q = 0;
		for(long rs = 0; rs < mmd.Nr; rs++)
		{
			printf("Filling the matrix in S-Coefficient region %ld %ld\n", rs, mmd.Nr);
			for(long cs = 0; cs < mmd.Nc; cs++)
			{
				{
	#if 0
				// ������� ��������� ���������������� "������" �� ������� �������
				ZeroDoubleMat(grid->gridSection.z, grid->gridSection.nRow, grid->gridSection.nCol);
				grid->gridSection.z[rs][cs] = 1.0;

				InverseWaveletTransform2D(w2, grid, mmd.increaser_pw, mmd.Nr, mmd.Nc);

				// �������������� ������ ������� ������� ������� � ������ �������
				for (long rr = 0; rr < grid->gridSection.nRow; rr++)
				{
					for (long cc = 0; cc < grid->gridSection.nCol; cc++)
					{
						// ������ � ������ ������� ��������� ������ ������
						long i = rr * mmd.cols + cc;
						sol[i] = grid->gridSection.z[rr][cc];
					}
				}
	#endif

	#if 0
				double min_w = 0, max_w = 0;
				long r_begin = 0, c_begin = 0, r_end = 0, c_end = 0;
				bool began = false;
				for (long jj = 0; jj < grid->gridSection.nRow; jj++)
				{
					for (long ii = 0; ii < grid->gridSection.nCol; ii++)
					{
						double w = grid->gridSection.z[jj][ii];
						// ������ � ������ ������� ��������� ������ ������
						if(w != 0.0) 
						{
							r_end = jj;
							c_end = ii;
							if (!began)
							{
								began = true;
								r_begin = r_end;
								c_begin = c_end;
							}
						}
						if (min_w > w) min_w = w;
						if (max_w < w) max_w = w;
					}
				}

				grid->gridSection.zMax = max_w;
				grid->gridSection.zMin = min_w;

				char fn[1024]; 
				sprintf(fn, "%s\\iwsi %02ld %02ld r_begin = %ld r_end = %ld c_begin = %ld c_end = %ld.grd", 
					dir_out,
					rs,cs,
					r_begin, r_end, c_begin, c_end);
				
				// ���� ��� ����� ��������

				for (long ii = 0; ii < grid->gridSection.nCol; ii++)
				{
					long k = grid->gridSection.nRow/2;
					long L = grid->gridSection.nRow-1;
					for (long jj = 0; jj < k; jj++)
					{
						double w_value = grid->gridSection.z[L][ii];
						grid->gridSection.z[L][ii] = grid->gridSection.z[jj][ii];
						grid->gridSection.z[jj][ii] = w_value;
						L--;
					}
				}
				SaveAsSurfer7Grid(fn, grid);
	#endif
				}
				memset(psol,0,rows_cols*sizeof(double));
				
				long i0r = rs; long i0c = cs;
				for (long J = 0; J < mmd.increaser_pw; J++)
				{
					i0r *= 2; i0r += shift_r;
					i0c *= 2; i0c += shift_c;
				}
				printf("i0r = %d i0c = %d\n", i0r, i0c);
				// �������������� ������ ������� ������� ������� � ������ �������
				for (long r = 0; r < wavSimage->gridSection.nRow; r++)
				{
					for (long c = 0; c < wavSimage->gridSection.nCol; c++)
					{
						long rr_ = r + i0r;
						long cc_ = c + i0c;
						if (rr_ >= 0 && cc_ >= 0 && rr_ < grid->gridSection.nRow && cc_ < grid->gridSection.nCol )
						{
							// ������ � ������ ������� ��������� ������ ������
							long i = rr_ * mmd.cols + cc_;
							psol[i] = wavSimage->gridSection.z[r][c];
						}
					}
				}
				{
	#if 0
				double sum_err = 0.0;
				for (int i = 0; i < rows_cols; i++)
				{
					sum_err += fabs(psol[i]-sol[i]);
				}
				printf("sum_err = %e\n", sum_err);
				//if (sum_err != 0.0)
				//	MessageBox(0,"sum_err != 0.0","sum_err != 0.0",0);
				ZeroDoubleMat(grid->gridSection.z, grid->gridSection.nRow, grid->gridSection.nCol);
				min_w = 0, max_w = 0;
				r_begin = 0, c_begin = 0, r_end = 0, c_end = 0;
				began = false;

				for (long r = 0; r < wavSimage->gridSection.nRow; r++)
				{
					for (long c = 0; c < wavSimage->gridSection.nCol; c++)
					{
						long rr__ = r + i0r;
						long cc__ = c + i0c;

						double w = wavSimage->gridSection.z[r][c];
						
						if (rr__ >= 0 && cc__ >= 0 && rr__ < grid->gridSection.nRow && cc__ < grid->gridSection.nCol )
						{
							// ������ � ������ ������� ��������� ������ ������
							//long i = rr * mmd.cols + cc;
							//psol[i] = wavSimage->gridSection.z[r][c];

							grid->gridSection.z[rr__][cc__] = w;
							if(w != 0.0) 
							{
								r_end = rr__;
								c_end = cc__;
								if (!began)
								{
									began = true;
									r_begin = r_end;
									c_begin = c_end;
								}
							}
						
							if (min_w > w) min_w = w;
							if (max_w < w) max_w = w;
						}
					}
				}
				grid->gridSection.zMax = max_w;
				grid->gridSection.zMin = min_w;

				//char fn[1024]; 
				sprintf(fn, "%s\\iwsi %02ld %02ld r_begin = %ld r_end = %ld c_begin = %ld c_end = %ld .grd", 
					dir_out,
					rs,cs,
					r_begin, r_end, c_begin, c_end);
				
				// ���� ��� ����� ��������

				for (long ii = 0; ii < grid->gridSection.nCol; ii++)
				{
					long k = grid->gridSection.nRow/2;
					long L = grid->gridSection.nRow-1;
					for (long jj = 0; jj < k; jj++)
					{
						double w_value = grid->gridSection.z[L][ii];
						grid->gridSection.z[L][ii] = grid->gridSection.z[jj][ii];
						grid->gridSection.z[jj][ii] = w_value;
						L--;
					}
				}
				SaveAsSurfer7Grid(fn, grid);
	#endif
				}
				// �� ������ ������� ��������� ���������� ������ ������
				// � �������� q-��� ������� ����� �������
				// ������� ����� �������� �������� ������ ������ � ��������� �������

	#if ON_THE_FLY_STORING
	#if 1
#if SPARSE_OUT_W
				if(!ApplyOperator_SparseOut(signal_len, psol,(size_t)rows_cols, mmd.fn_operator_spm, mmd.fn_operator_wav))
				{
					printf("Error while ApplyOperator()\n");
					return;
				}
#else
				if(!ApplyOperator(signal_len, psol,(size_t)rows_cols, spm_filename, mmd.vvd_filename))
				{
					printf("Error while ApplyOperator()\n");
					return;
				}
#endif
	#else
				if(!ApplyOperator(signal_len, sol, spm_filename, mmd.vvd_filename))
				{
					printf("Error while ApplyOperator()\n");
					return;
				}
	#endif
	#else
				if(!ApplyOperator(signal_len, q, sol, spm_filename, ms))
				{
					printf("Error while ApplyOperator()\n");
					return;
				}
	#endif

				q++;
			}
		}

		delete psol;

		//if (m) delete m;
	#if !ON_THE_FLY_STORING
		StoreMatrix(vvd_filename, ms, true);
	#endif

		printf("The matrix in S-Coefficient region if filled!!!\n");
		FreeDoubleMat(wavSimage->gridSection.z);
		delete wavSimage;

		FreeDoubleMat(grid->gridSection.z);
		delete grid;


	}
}
#define printf_vector(v) printf("printf_vector size = %u\n", v.size()); for(size_t __i = 0; __i < v.size(); __i++) printf("%f\t", v[__i]); printf("\n");
void DoInverseAndFillGrid2W(MyMethodsData& mmd,
							Wavelet2D& w2,
							vector<double> & t,
							vector<double> & signal,
							string name
							)
{
	printf("DoInverseAndFillGrid2W %s\n", name.c_str());

	//printf_vector(signal)
	// ����� ������ ����
	// ���� �� ������� ������������� ���������
	Grid * grid = CreateProfileGrid2D(mmd);

	// ��������� ����� s �������������
	long Ns = mmd.Nr * mmd.Nc;

	printf("Start of solve the inverse problem\n");


	// ������� ������� �������� ������ � ��������� �������
	vector<double> sols(Ns);
	vector<double> sols_mean(Ns, 0.0);
	double alpha = 0.0;
#if SPARSE_OUT_W
	if (!InverseProblem_Solving(true, mmd.fn_operator_wav, mmd.fn_min_sq_mat, mmd.fn_Lt, 
		signal, sols, alpha, sols_mean))
	{
	}

#endif

	//printf_vector(signal)

	printf("The inverse problem is solved!!!\n");
	printf("Form the frequency matrix from the inverse problem solving!!!\n");

	// ��������� ��������� �������
	ZeroDoubleMat(grid->gridSection.z, grid->gridSection.nRow, grid->gridSection.nCol);
	long q = 0;
	for(long rs = 0; rs < mmd.Nr; rs++)
	{
		for(long cs = 0; cs < mmd.Nc; cs++)
		{
			grid->gridSection.z[rs][cs] = sols[q];
			q++;
		}
	}

	printf("Form the razrez matrix by fft\n");
			
	// �������, ��������� ���������������� "������" �� ��������� �������
	InverseWaveletTransform2D(w2, grid, mmd.increaser_pw, mmd.Nr, mmd.Nc);

	printf("Save the razrez matrix\n");


	double min_z = DBL_MAX;
	double max_z = -DBL_MAX;

	double z_value;

	vector<double> sol(grid->gridSection.nCol * grid->gridSection.nRow);

	for (long ii = 0; ii < grid->gridSection.nCol; ii++)
	{
		for (long jj = 0; jj < grid->gridSection.nRow; jj++)
		{

			z_value = grid->gridSection.z[jj][ii];
			if (max_z < z_value) max_z = z_value;
			if (min_z > z_value) min_z = z_value;
            
			// ������ � ������ ������� ��������� ������ ������
			//i = r * cols + C;
			long i = jj * grid->gridSection.nCol + ii;
			sol[i] = z_value;
		}
	}

	ErrorOfInverseProblemSolving(mmd.fn_operator_spm, t, signal, sol, name);

	// ���� ��� ����� ��������

	for (long ii = 0; ii < grid->gridSection.nCol; ii++)
	{
		long k = grid->gridSection.nRow/2;
		long L = grid->gridSection.nRow-1;
		for (long jj = 0; jj < k; jj++)
		{
			z_value = grid->gridSection.z[L][ii];
			grid->gridSection.z[L][ii] = grid->gridSection.z[jj][ii];
			grid->gridSection.z[jj][ii] = z_value;
			L--;
		}
	}

	grid->gridSection.zMax = max_z;
	grid->gridSection.zMin = min_z;
	
	//-----------------------------------

	char file[2048];
	sprintf(file, "%s\\MyMethod2_of_%s.grd", dir_out, name.c_str());
	char * p; while (p=strchr (file,'\"')){*p = '_';}
	SaveAsSurfer7Grid(file, grid);

	FreeDoubleMat(grid->gridSection.z);
	delete grid;

	printf("Yes!!!\n");
}





void DoMyMethod3W(int type, // ��� ������ ������
				  bool granicy_kak_glubina,
				  FILE * description,
				  MyMethodsData3& mmd,
				  Wavelet3D& w3,
				 auto_build_parametrs& ab, 
				 vector<double> & X,
				 vector<double> & Y,
				 vector<double> & Z, // ��������� ��������� - ����� �������
				 vector<vector<anten_direction> > & A,
				 //double z0,// ��������� ������ �����������
				 //vector<double> & signal,
				 //string name,
				 bool to_fill_matrix)
{
	printf ( "DoMyMethod3W\n" );

	long signal_len = X.size(); // ����� ������� 
#if 0
	// ��������� ����� � ��������
	int pw_pcd = 1;
	cout << "Enter pw_pcd pages/cols deviation pw (0,1,2,...)?\n";
	cin >> pw_pcd;
	int pcd = pow(2.0, pw_pcd);
#else
	// ��������� ����� � ��������
	// int pw_rcd = 2;
	int pcd = pow(2.0, mmd.pw_pcd);
#endif
	// pages = cols / pcd;
	// rows ~ cols
	// pages * rows * cols > signal_len
	// cols * cols * cols / pcd > signal_len
	// cols > sqrt3( signal_len * rcd ) = pow(double(signal_len * pcd), 1.0/3.0)
	// cols is power of 2
	// 

	//bool have_pereopredelen_system = true;

	// Np ����� S ������������� �� ���������
	// Nr ����� S ������������� �� �����������
	// Nc ����� S ������������� �� �����������
	//long Np=1, Nr=1, Nc=1;

	// ����� ����������� S ������������� Nr * Nc * Np
	// ����� ��������� signal_len

	// ���������� �������� ������� Nr * Nc * Np ~ signal_len
	//  Nr * Nr * Np ~ signal_len
	//  as   (pages = cols / rcd) and (rcd = pow(2,pw_rcd)) so  Nr = Nc = Np + pw_pcd;;
	//  (Np + pw_pcd) * (Np + pw_pcd) * Np ~ signal_len 



#if 0
	// ��� ����� ����, ��� �� ��������� � ����������� 
	// ������ ����� ������ � ��� ������, ���� �� ����� 
	// �������� ������������ � �������������� �������
	double near_Np = pow(double(signal_len), 1.0/3.0);

	if (have_pereopredelen_system)
	{
		// ���� � ���� �������� ��������������� �������
		mmd.Np = mmd.Nr = mmd.Nc = floor(near_Np);
	}
	else
	{
		// ���� � ���� �������� ��������������� �������
		mmd.Np = mmd.Nr = mmd.Nc = ceil(near_Np);
	}
#else
	// � ������ ����, ��� �� ��������� � ����������� 
	// ������ ����� ������ � ��� ������, ���� �� ����� 
	// �������� ������������ � �������������� �������

	// ���� ������ ���������� ���������

	//double D = pw_rcd * pw_rcd + signal_len;

	double near_Np = 0;

	vdouble den(4);
	den[0] = 1.0;
	den[1] = 2*mmd.pw_pcd;
	den[2] = mmd.pw_pcd*mmd.pw_pcd;
	den[3] = -signal_len;

	vdouble droots; // �������������� �����
	Vector<complex> croots; //����������� ����� �����������
	// ============== Roots of denominator ==========================
	Vector<int> order_dr, order_cr;
	int res = den.roots(droots, croots, order_dr, order_cr);

	for (int i = 0; i < droots.Length(); i++)
	{
		// �������������� ������
		near_Np = droots[i];
	}

	if (mmd.have_pereopredelen_system)
	{
		// ���� � ���� �������� ��������������� �������
		mmd.Np = floor(near_Np);
	}
	else
	{
		// ���� � ���� �������� ��������������� �������
		mmd.Np = ceil(near_Np);
	}

	mmd.Nr = mmd.Nc = mmd.Np + mmd.pw_pcd;
#endif

	// ��������� ����� s �������������
	long Ns = mmd.Np * mmd.Nr * mmd.Nc;

	fprintf (description, "Np = %ld Nr = %ld Nc = %ld Ns = %ld\n", mmd.Np, mmd.Nr, mmd.Nc, Ns);
#if 0
	long increaser_pw = 2;
	cout << "Enter increaser_pw (0,1,2,...)?\n";
	cin >> increaser_pw;
#endif
	long increaser = pow(2.0, mmd.increaser_pw);

	fprintf (description, "increaser_pw = %ld increaser = %ld\n", mmd.increaser_pw, increaser);


	mmd.cols = increaser * mmd.Nc; 
	mmd.rows = increaser * mmd.Nr;
	mmd.pages = increaser * mmd.Np;// � ��� �������

	cout << "cols = " << mmd.cols << endl;
	cout << "rows [" << mmd.rows << "]\n";
	cout << "pages [" << mmd.pages << "]\n";
	/*cout << "Do you want reenter?\n";

	char answer;
	cin >> answer;
	if (answer == 'y' || answer == 'Y')
	{
		cout << "cols?\n";
		cin >> cols;
		cout << "rows?\n";
		cin >> rows;
		cout << "pages?\n";
		cin >> pages;
	}*/

	
	/*if (pages < 2*Np+2)
	{
		printf("Error: (pages (%ld)) < (2*Np(%d)+2)(%ld)\n", pages, Np, 2*Np+2);
		return;
	}	
	if (rows < 2*Nr+2)
	{
		printf("Error: (rows (%ld)) < (2*Nr(%d)+2)(%ld)\n", rows, Nr, 2*Nr+2);
		return;
	}
	if (cols < 2*Nc+2)
	{
		printf("Error: (cols (%ld)) < (2*Nc(%d)+2)(%ld)\n", cols, Nc, 2*Nc+2);
		return;
	}*/

	double min__x, min__y, min__z;
	double max__x, max__y, max__z;
	//double delta__x;
	//double delta__y;

	GetProfileDirection(X, Y, Z,
		min__x, min__y, min__z,
		max__x, max__y, max__z,
		mmd.delta__x, mmd.delta__y);

	mmd.delta__z = mmd.z0 - mmd.z_min;

	if (granicy_kak_glubina)
	{
		// ����� �� ������ ���� ��������� �� �������� �������

		mmd.x0 = min__x + mmd.delta__z;
		mmd.y0 = min__y + mmd.delta__z;

		// ��� ����� ������� �� X � �� Y
		mmd.delta_x = (mmd.delta__x - 2.0 * mmd.delta__z) / (mmd.cols - 1);
		mmd.delta_y = (mmd.delta__y - 2.0 * mmd.delta__z) / (mmd.rows - 1);
	}
	else
	{
		mmd.x0 = min__x;
		mmd.y0 = min__y;

		// ��� ����� ������� �� X � �� Y
		mmd.delta_x = mmd.delta__x / (mmd.cols - 1);
		mmd.delta_y = mmd.delta__y / (mmd.rows - 1);
	}


	// ��� ����� ������������� ��������� �� z (�������)
	//mmd.delta_z = mmd.delta__z / (mmd.pages - 1);// ��� �������!!!
	// �������� ������� �������� ���� ��� ������� ����������� �� ������� delta_z
	mmd.delta_z = mmd.delta__z / mmd.pages;

	long rows_cols_pages = mmd.rows * mmd.cols * mmd.pages;

	printf ( "DoMyMethod cols = %ld rows = %ld pages = %ld\n", mmd.cols, mmd.rows, mmd.pages);

	// ���������� ������������ ������ ������
#if 0
	char spm_filename[4096];
	sprintf(spm_filename, "%s\\operator.spm", dir_out);

	vector<double> sol(rows_cols_pages, 0.0);
#endif
	//bool to_fill_matrix = true;

	if (to_fill_matrix)
	{
		sprintf(mmd.fn_operator_spm, "%s\\operator.spm", dir_out);

		//int smoof_power = 1024;
		//int smoof_power = 4096;
		//int smoof_power = 8;
		int smoof_power = mmd.smoof_power;

		smoof_power /= 2;
		smoof_power *= 2;

	printf ("mmd.fn_operator_spm = %s\n", mmd.fn_operator_spm);
	fprintf (description, "smoof_power = %d\n", smoof_power);

		printf("Filling of matrix\n");
		// ��������� ������� ��������� ������ ������, 
		// ����� ����� ����� ����� ������� 
		// (��� ��������� ����� ���������� �������� - 
		// ���������� �������� �� ����� ���, ��� �����, �� ������ �������)
		// �� ���� ��������� ������� ������������� ��������� 
		// ���������� ���������������� �������
		// �� ������ ��������� ����� �������� ��������� (������) �� ��������
		switch(type)
		{
		case 0:
			{
				FillingTheMatrix3D(smoof_power, mmd.k_oslablenie, ab.k, NULL, mmd.fn_operator_spm, 
					mmd.rows, mmd.cols, mmd.pages,
					mmd.x0, mmd.y0, mmd.z0,
					mmd.delta_x, mmd.delta_y, mmd.delta_z,
					X, Y, Z, mmd.pw_dnp, mmd.wave_type);
			}
			break;
		case 1:
			{
				FillingTheMatrix3D_with_napravlennosty_diagramm(
					mmd.k_oslablenie, 
					NULL, mmd.fn_operator_spm, 
					mmd.rows, mmd.cols, mmd.pages,
					mmd.x0, mmd.y0, mmd.z0,
					mmd.delta_x, mmd.delta_y, mmd.delta_z,
					X, Y, Z, A,
					mmd.pw_dnp,
					mmd.min_value,
					mmd.wave_type,
					mmd.spm);
			}
			break;
		}

		/*Grid4 * cube = ShowCube(mmd);
		char fn[1024]; 
		sprintf(fn, "%s\\cube.cub", 
			dir_out);
		SaveAsSurfer7Grid4(fn, cube);*/

	}

		
	printf("The matrix is filled!!!\n");

	if (!CheckMyLicense()) return;        

	// ���� �� ������� ������������� ���������
	Grid4 * grid = CreateProfileGrid3D(mmd);

	printf("Creating the matrix in Frequency region\n");
#if !ON_THE_FLY_STORING
	//������� ��������� ������ ������ � ��������� �������
	vector<vector<double> > ms(signal_len);
	for (long j = 0; j < signal_len; j++)
		ms[j].resize(Ns);
#endif

	
	//ap::real_1d_array a;
	//a.setbounds( 0, max(max(mmd.cols, rows), pages) );
	//bool inversefft = true;

		
	printf("Start of filling the matrix in S-Coefficient region %ld %ld %ld\n", mmd.Nr, mmd.Nc, mmd.Np);
	//printf("Start of filling the matrix in Frequency region %ld %ld\n", 2*Nr, 2*Nc);
	//char vvd_filename[4096];
	//sprintf(vvd_filename, "%s\\operator3_freq.vvd", dir_out);

#if SPARSE_OUT_W
	sprintf(mmd.fn_operator_wav, "%s\\operator3_wav.spm", dir_out);
#else
	sprintf(mmd.vvd_filename, "%s\\operator3_wav.vvd", dir_out);
#endif

#if ON_THE_FLY_STORING
	//StoreMatrixHeader(vvd_filename, signal_len, Nq, true);
	#if SPARSE_OUT_W
		//������� ��������� � ����������������� ����
		StoreMatrixHeader(mmd.fn_operator_wav, Ns, signal_len);
	#else
		StoreMatrixHeader(mmd.vvd_filename, signal_len, Ns, true);
	#endif
#endif

		Grid4 * wavSimage = InverseWaveletImage3D(w3, mmd.increaser_pw, mmd);

		char fn[1024]; 
		sprintf(fn, "%s\\iwsi.cub", 
			dir_out);
		
		// ���� ��� ����� ��������

		for (long rr = 0; rr < wavSimage->grid4Section.nRow; rr++)
		{
			for (long cc = 0; cc < wavSimage->grid4Section.nCol; cc++)
			{
				long k = wavSimage->grid4Section.nPag/2;
				long L = wavSimage->grid4Section.nPag-1;
				for (long pp = 0; pp < k; pp++)
				{
					double w_value = wavSimage->grid4Section.v[L][rr][cc];
					wavSimage->grid4Section.v[L][rr][cc] = wavSimage->grid4Section.v[pp][rr][cc];
					wavSimage->grid4Section.v[pp][rr][cc] = w_value;
					L--;
				}
			}
		}
		SaveAsSurfer7Grid4(fn, wavSimage);

		double * psol = new double[rows_cols_pages];
		memset(psol, 0, rows_cols_pages*sizeof(double));
		long shift_c = 2 * (w3.right_h_c/2 - (w3.rh_c.Length()-2)/2);
		long shift_r = 2 * (w3.right_h_r/2 - (w3.rh_r.Length()-2)/2);
		long shift_p = 2 * (w3.right_h_p/2 - (w3.rh_p.Length()-2)/2);

		// ���������� ������������ ���������� ���������������� ���������� �������
		long q = 0;
		for(long ps = 0; ps < mmd.Np; ps++)
		{
			printf("Filling the matrix in S-Coefficient region %ld %ld\n", ps, mmd.Np);
			for(long rs = 0; rs < mmd.Nr; rs++)
			{
				for(long cs = 0; cs < mmd.Nc; cs++)
				{

					memset(psol, 0, rows_cols_pages*sizeof(double));
					
					long i0p = ps; long i0r = rs; long i0c = cs;
					for (long J = 0; J < mmd.increaser_pw; J++)
					{
						i0p *= 2; i0p += shift_p;
						i0r *= 2; i0r += shift_r;
						i0c *= 2; i0c += shift_c;
					}
					//printf("i0p = %d i0r = %d i0c = %d\n", i0p, i0r, i0c);
					// �������������� ������ ������� ������� ������� � ������ �������
					for (long p = 0; p < wavSimage->grid4Section.nPag; p++)
					{
						for (long r = 0; r < wavSimage->grid4Section.nRow; r++)
						{
							for (long c = 0; c < wavSimage->grid4Section.nCol; c++)
							{
								long pp_ = p + i0p;
								long rr_ = r + i0r;
								long cc_ = c + i0c;
								if (pp_ >= 0 && rr_ >= 0 && cc_ >= 0 && pp_ < grid->grid4Section.nPag && rr_ < grid->grid4Section.nRow && cc_ < grid->grid4Section.nCol )
								{
									// ������ � ������ ������� ��������� ������ ������
									//long i = rr_ * mmd.cols + cc_;
									long i = pp_ * mmd.rows * mmd.cols + rr_ * mmd.cols + cc_;
									psol[i] = wavSimage->grid4Section.v[p][r][c];
								}
							}
						}
					}

					// �� ������ ������� ��������� ���������� ������ ������
					// � �������� q-��� ������� ����� �������
					// ������� ����� �������� �������� ������ ������ � S �������

		#if ON_THE_FLY_STORING
		//#if 1
	#if SPARSE_OUT_W
					if(!ApplyOperator_SparseOut(signal_len, psol,(size_t)rows_cols_pages, mmd.fn_operator_spm, mmd.fn_operator_wav))
					{
						printf("Error while ApplyOperator()\n");
						return;
					}
	#else
					if(!ApplyOperator(signal_len, psol,(size_t)rows_cols_pages, spm_filename, mmd.vvd_filename))
					{
						printf("Error while ApplyOperator()\n");
						return;
					}
	#endif
		//#else
		//			if(!ApplyOperator(signal_len, sol, spm_filename, mmd.vvd_filename))
		//			{
		//				printf("Error while ApplyOperator()\n");
		//				return;
		//			}
		//#endif
		#else
					if(!ApplyOperator(signal_len, q, sol, spm_filename, ms))
					{
						printf("Error while ApplyOperator()\n");
						return;
					}
		#endif

					q++;
				}
			}

		}
		delete psol;

#if !ON_THE_FLY_STORING
	StoreMatrix(vvd_filename, ms, true);
#endif

	printf("The matrix in Frequency region if filled!!!\n");

}

void DoInverseAndFillGrid3W(MyMethodsData3& mmd,
							Wavelet3D& w3,
							vector<double> & signal,
							string name,
							vector<double> & rec_signal
							)
{
	// ���� �� ������� ������������� ���������
	Grid4 * grid = CreateProfileGrid3D(mmd);

	// ��������� ����� s �������������
	long Ns = mmd.Np * mmd.Nr * mmd.Nc;

	printf("Start of solve the inverse problem in S region\n");

	// ������� ������� �������� ������ � S �������
	vector<double> sol_S(Ns);
	vector<double> sol_S_mean(Ns, 0.0);
	double alpha = 0.0;
#if SPARSE_OUT_W
	if (!InverseProblem_Solving(true, mmd.fn_operator_wav, mmd.fn_min_sq_mat, mmd.fn_Lt, 
		signal, sol_S, alpha, sol_S_mean))
	{
	}
#endif
	printf("The inverse problem is solved!!!\n");
	printf("Form the frequency matrix from the inverse problem solving!!!\n");

	//vector<double> rec_signal_S;
	//printf("Error of solve the inverse problem in S region\n");
	//ErrorOfInverseProblemSolving(mmd.fn_operator_wav, signal, sol_S, name, rec_signal_S);



	// ��������� ��������� �������
	Zero3DMat<double>(grid->grid4Section.v, grid->grid4Section.nPag, grid->grid4Section.nRow, grid->grid4Section.nCol);
	long q = 0;
	for(long ps = 0; ps < mmd.Np; ps++)
	{
		for(long rs = 0; rs < mmd.Nr; rs++)
		{
			for(long cs = 0; cs < mmd.Nc; cs++)
			{
				grid->grid4Section.v[ps][rs][cs] = sol_S[q];
				q++;
			}
		}
	}


	printf("Form the razrez matrix by fft\n");
			
	// �������, ��������� ���������������� "������" �� S �������
	InverseWaveletTransform3D(w3, grid, mmd.increaser_pw, mmd.Np, mmd.Nr, mmd.Nc);

	printf("Save the razrez matrix\n");


	double min_v = DBL_MAX;
	double max_v = -DBL_MAX;

	double v_value;

	vector<double> sol(grid->grid4Section.nCol * grid->grid4Section.nRow * grid->grid4Section.nPag);

	for (long pp = 0; pp < grid->grid4Section.nPag; pp++)
	{
		for (long cc = 0; cc < grid->grid4Section.nCol; cc++)
		{
			for (long rr = 0; rr < grid->grid4Section.nRow; rr++)
			{
				v_value = grid->grid4Section.v[pp][rr][cc];
				if (max_v < v_value) max_v = v_value;
				if (min_v > v_value) min_v = v_value;

				// ������ � ������ ������� ��������� ������ ������
				//long i = rr_ * mmd.cols + cc_;
				long i = pp * mmd.rows * mmd.cols + rr * mmd.cols + cc;
				sol[i] = v_value;
			}
		}
	}
	ErrorOfInverseProblemSolving(true, mmd.fn_operator_spm, signal, sol, name, rec_signal);
#if 1
	// ���� ��� ����� ��������

	for (long ii = 0; ii < grid->grid4Section.nCol; ii++)
	{
		for (long jj = 0; jj < grid->grid4Section.nRow; jj++)
		{
			long k = grid->grid4Section.nPag/2;
			long L = grid->grid4Section.nPag-1;
			for (long pp = 0; pp < k; pp++)
			{
				v_value = grid->grid4Section.v[L][jj][ii];
				grid->grid4Section.v[L][jj][ii] = grid->grid4Section.v[pp][jj][ii];
				grid->grid4Section.v[pp][jj][ii] = v_value;
				L--;
			}
		}
	}
#endif
	grid->grid4Section.vMax = max_v;
	grid->grid4Section.vMin = min_v;
	
	//-----------------------------------

	char file[2048];
	sprintf(file, "%s\\MyMethod3_of_%s.cub", dir_out, name.c_str());
	char * p;
	while (p=strchr (file,'\"'))
	{
		*p = '_';
	}
	SaveAsSurfer7Grid4(file, grid);

	Free3DMat<double>(grid->grid4Section.v);
	delete grid;
	printf("Yes!!!\n");
}





bool SaveParameters (char * filename, MyMethodsData& mmd)
{
	char buff[BUFF_SIZE];
	AFile f;
	if( !f.Open( filename, GENERIC_WRITE, TRUNCATE_EXISTING) ) 
	{
		if( !f.Open( filename, GENERIC_WRITE, CREATE_NEW) ) 
		{
			MessageBox(0, "Unable to open file" , filename, MB_OK);
			return false;
		}
	}
	Archive ar( &f, Archive::store, BUFF_SIZE, buff );

	ar << mmd.increaser_pw;
	ar << mmd.pw_rcd;
	ar << mmd.z0;
	ar << mmd.k_oslablenie;

	ar.Close();
	f.Close();

	return true;

}

void LoadParameters (MyMethodsData& mmd)
{
	char buff[BUFF_SIZE];
	char filename[4096];
	TCHAR filter[] =     
		TEXT("Parameters File (*.par)\0*.par\0")
		TEXT("All Files (*.*)\0*.*\0");
	sprintf(filename, "\0");
	if (OpenFileDlg(0, filter, filename) == S_OK)
	{
		AFile f;
		if( f.Open( filename, GENERIC_READ, OPEN_EXISTING) ) 
		{
			Archive ar( &f, Archive::load, BUFF_SIZE, buff );
			try
			{
				ar >> mmd.increaser_pw;
				ar >> mmd.pw_rcd;
				ar >> mmd.z0;
				ar >> mmd.k_oslablenie;

			}
			catch(char * str)
			{
				MessageBox(0,str,"",0);
			}
			catch (CException* pe)
			{
				// catch errors from WinINet 
				TCHAR szErr[4098]; 
				pe->GetErrorMessage(szErr, 4098); 
				AfxMessageBox(szErr);
				pe->Delete();
			}
			catch(...)
			{
				MessageBox(0,"unknown error of archive read","",0);
			}
			
			ar.Close();
			f.Close();
		}
		else
		{
			MessageBox(0, "Unable to open file" , filename, MB_OK);
		}

	}
}


bool SaveParameters (char * filename, MyMethodsData3& mmd)
{
	char buff[BUFF_SIZE];
	AFile f;
	if( !f.Open( filename, GENERIC_WRITE, TRUNCATE_EXISTING) ) 
	{
		if( !f.Open( filename, GENERIC_WRITE, CREATE_NEW) ) 
		{
			MessageBox(0, "Unable to open file" , filename, MB_OK);
			return false;
		}
	}
	Archive ar( &f, Archive::store, BUFF_SIZE, buff );

	ar << mmd.increaser_pw;
	ar << mmd.pw_pcd;
	ar << mmd.z0;
	ar << mmd.z_min;
	ar << mmd.k_oslablenie;
	ar << mmd.have_pereopredelen_system;

	ar.Close();
	f.Close();

	return true;

}

void LoadParameters (MyMethodsData3& mmd)
{
	char buff[BUFF_SIZE];
	char filename[4096];
	TCHAR filter[] =     
		TEXT("Parameters File (*.par3)\0*.par3\0")
		TEXT("All Files (*.*)\0*.*\0");
	sprintf(filename, "\0");
	if (OpenFileDlg(0, filter, filename) == S_OK)
	{
		AFile f;
		if( f.Open( filename, GENERIC_READ, OPEN_EXISTING) ) 
		{
			Archive ar( &f, Archive::load, BUFF_SIZE, buff );
			try
			{
				ar >> mmd.increaser_pw;
				ar >> mmd.pw_pcd;
				ar >> mmd.z0;
				ar >> mmd.z_min;
				ar >> mmd.k_oslablenie;
				ar >> mmd.have_pereopredelen_system;


			}
			catch(char * str)
			{
				MessageBox(0,str,"",0);
			}
			catch (CException* pe)
			{
				// catch errors from WinINet 
				TCHAR szErr[4098]; 
				pe->GetErrorMessage(szErr, 4098); 
				AfxMessageBox(szErr);
				pe->Delete();
			}
			catch(...)
			{
				MessageBox(0,"unknown error of archive read","",0);
			}
			
			ar.Close();
			f.Close();
		}
		else
		{
			MessageBox(0, "Unable to open file" , filename, MB_OK);
		}

	}
}


void SparseStructureToMetafile(char * fn_spm, char * fn_emf)
{
	char buff[BUFF_SIZE];
	long cols, rows;

	AFile f;
	if( !f.Open( fn_spm, GENERIC_READ, OPEN_EXISTING) ) 
	{
		MessageBox(0, "FormMinSquareB\nUnable to open file" , fn_spm, MB_OK);
	}
	
	Archive ar( &f, Archive::load, BUFF_SIZE, buff );

	try
	{
		ar >> rows;
		ar >> cols;
	}
	catch(char * str)
	{
		MessageBox(0,str,"",0);
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();
	}
	catch(...)
	{
		MessageBox(0,"unknown error of archive read","",0);
	}
	HDC hDC;

	PRINTDLG pd;
	
	// Initialize PRINTDLG
	ZeroMemory(&pd, sizeof(pd));
	pd.lStructSize = sizeof(pd);
	pd.hwndOwner   = NULL;
	pd.hDevMode    = NULL;     // Don't forget to free or store hDevMode
	pd.hDevNames   = NULL;     // Don't forget to free or store hDevNames

	pd.Flags       = 
		PD_RETURNDEFAULT
	; 
	
	if (PrintDlg(&pd)!=TRUE) 
	{
		// GDI calls to render output.
		// ��� ������ ��������... 
		// BeginPrinting(hwnd, &pd);
		return;
	}	

	DOCINFO di;
	
	if(!pd.hDevNames)
	{
		MessageBox(0,"!psd->hDevNames","BeginPrinting", 0);
		return ;
	}

	if(!pd.hDevMode)
	{
		MessageBox(0,"!psd->hDevMode","BeginPrinting", 0);
		return ;
	}

	// �������� ��������� �� ��� ��������� � �����������.
	DEVNAMES FAR *lpDevNames =
		(DEVNAMES FAR *)::GlobalLock(pd.hDevNames);
	
	DEVMODE FAR *lpDevMode =
		(DEVMODE FAR *)::GlobalLock(pd.hDevMode);

	
	LPSTR szPrinterName = (LPTSTR)lpDevNames +
		lpDevNames->wDeviceOffset;
	
	LPSTR szDriverName = (LPTSTR)lpDevNames +
		lpDevNames->wDriverOffset;

	LPSTR szOutputPortName = (LPTSTR)lpDevNames +
		lpDevNames->wOutputOffset;

	// ������� �������� ���������� ��� ��������, 
	// �� ������� ������ ���� ��������� ������.
	//........................................
	hDC = CreateDC( 
		szDriverName,//"WINSPOOL", 
		szPrinterName,
		szOutputPortName, 
		lpDevMode			//pDevModeUser 
		);	

	int  iWidthMM, iHeightMM, iWidthPels, iHeightPels;
	double  iMMPerPelX, iMMPerPelY;

	// ��������� ������ ���������� ������� � �������� 
	// ����� 0,01 ��.
	//................................................
	iWidthMM    = GetDeviceCaps(hDC, HORZSIZE);
	iHeightMM   = GetDeviceCaps(hDC, VERTSIZE);
	iWidthPels  = GetDeviceCaps(hDC, HORZRES);
	iHeightPels = GetDeviceCaps(hDC, VERTRES);

	printf("iWidthMM %d, iHeightMM %d, iWidthPels %d, iHeightPels %d\n", iWidthMM, iHeightMM, iWidthPels, iHeightPels);

	iMMPerPelX = double(iWidthMM * 100)/iWidthPels;
	iMMPerPelY = double(iHeightMM * 100)/iHeightPels;

	printf("iMMPerPelX %f, iMMPerPelY %f\n", iMMPerPelX, iMMPerPelY);

	int m = 10, m_2 = m/2;

	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = (cols+1)*m * iMMPerPelX;
	rect.bottom = (rows+1)*m * iMMPerPelY;

	printf("lf %d rt %d tp %d bt %d", rect.left,rect.right,rect.top,rect.bottom);

	// ������� ����������� ��������.
	//.............................
	HENHMETAFILE hMetaFile = NULL;
	HDC  hMetaDC;
	hMetaDC = CreateEnhMetaFile( hDC, fn_emf, &rect,  "Sparse Matrix Structure" );
	if  (!hMetaDC)
	{
		TCHAR filter[] =
							TEXT("Metafiles (*.emf)\0*.emf\0")
							TEXT("All Files (*.*)\0*.*\0");
		char fn_emf_[4098];
		DWORD nFilterIndex = 0;
		if (S_OK == SaveFileDlg(NULL, fn_emf_, filter,nFilterIndex))
		{
			hMetaDC = CreateEnhMetaFile( hDC, fn_emf_, &rect,  "Sparse Matrix Structure" );
		}
		//else
		//	hMetaDC = CreateEnhMetaFile( hDC, NULL, &rect,  "Sparse Matrix Structure" );
	}



	if ( hMetaDC )
	{
		HFONT font = CreateFont(1,0,0,0,100,0,0,0,DEFAULT_CHARSET,
				OUT_RASTER_PRECIS, CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY,FF_DONTCARE,"Times New Roman");

		SelectObject (hMetaDC, font);
		
		char s[31];
		try
		{
			for (long r = 0; r < rows; r++)
			{
				printf("r  = %ld %ld\n", r, rows);							
				long cc;
				double value;

				do 
				{
					ar >> cc;
					ar >> value;

					if (cc >= 0)
					{
						//x.push_back(cc);
						//y.push_back(r);
#if 0
						sprintf(s,"%d*%d", int(r), int(cc));
						TextOut(hMetaDC, m_2+cc*m - ((int)strlen(s))/2, m_2+r*m + 1, s, (int)strlen(s));
#endif
						SetPixel(hMetaDC, m_2+cc*m,  m_2+r*m, RGB(255,0,0));
					}
					else
						break;
				}
				while(true);
			}
		}
		catch(char * str)
		{
			MessageBox(0,str,"",0);
		}
		catch (CException* pe)
		{
			// catch errors from WinINet 
			TCHAR szErr[4098]; 
			pe->GetErrorMessage(szErr, 4098); 
			AfxMessageBox(szErr);
			pe->Delete();
		}
		catch(...)
		{
			MessageBox(0,"unknown error of archive read","",0);
		}

		hMetaFile = CloseEnhMetaFile( hMetaDC );
	}
	else
		ErrorExit("CreateEnhMetaFile",false);
	
	ar.Close();
	f.Close();
	
	if (fn_emf == NULL)
		SavePlot( NULL, hMetaFile, "000" );

	if(hMetaFile)
		DeleteEnhMetaFile(hMetaFile);
}
void SparseStructureToSurferGrid(char * fn_spm, char * fn_grd)
{
	char buff[BUFF_SIZE];
	long cols, rows;

	AFile f;
	if( !f.Open( fn_spm, GENERIC_READ, OPEN_EXISTING) ) 
	{
		MessageBox(0, "FormMinSquareB\nUnable to open file" , fn_spm, MB_OK);
	}
	
	Archive ar( &f, Archive::load, BUFF_SIZE, buff );

	try
	{
		ar >> rows;
		ar >> cols;
	}
	catch(char * str)
	{
		MessageBox(0,str,"",0);
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();
	}
	catch(...)
	{
		MessageBox(0,"unknown error of archive read","",0);
	}




	Grid * grid = new Grid;
    
	grid->gridSection.nRow = rows;
	grid->gridSection.nCol = cols;


	grid->gridSection.xLL = 0.0;
	grid->gridSection.xSize = 1.0;


	grid->gridSection.yLL = 0.0;
	grid->gridSection.ySize = 1.0;					  
					  
	grid->gridSection.z = AllocDoubleMat(grid->gridSection.nRow, grid->gridSection.nCol);
	ZeroDoubleMat(grid->gridSection.z, grid->gridSection.nRow, grid->gridSection.nCol);
	grid->gridSection.BlankValue = BLANK_VALUE;//1.70141e38;// nodes are blanked if greater or equal to this value

	grid->faultSection.nTraces = 0;
	grid->faultSection.nVertices = 0;
	grid->faultSection.traces = NULL;
	grid->faultSection.vertexes = NULL;

	//printf("The grid is created\n");

	try
	{
		for (long r = 0; r < rows; r++)
		{
			//printf("r  = %ld %ld\n", r, rows);							
			long cc;
			double value;

			do 
			{
				ar >> cc;
				ar >> value;

				if (cc >= 0)
				{
					if (cc < cols)
						grid->gridSection.z[r][cc] = value;

				}
				else
					break;
			}
			while(true);
		}
	}
	catch(char * str)
	{
		MessageBox(0,str,"",0);
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();
	}
	catch(...)
	{
		MessageBox(0,"unknown error of archive read","",0);
	}

	UpdateExtremums(grid->gridSection);
	SaveAsSurfer7Grid(fn_grd, grid);
	FreeDoubleMat(grid->gridSection.z);
	delete grid;

	
	ar.Close();
	f.Close();
}
#define WITH_FOURIER 0
void UseOneOfMyMethods(int type, // ��� ������ ������
					   bool granicy_kak_glubina, 
#if WITH_2D
					   bool use_only_2D,
#endif
					   int & cols,
					   auto_build_parametrs& ab,
					   vector<double> & X,
					   vector<double> & Y,
					   vector<double> & Z, // ��������� ��������� - ����� �������
					   vector<vector<anten_direction> > & A,
					   vector<double> & vModul,
					   vector<vector<double> > & v,
					   vector<string> & names_of_colomns,
					   vector<size_t> & original_col_numbers,

					   vector<vector <double> > & rec_signals,
					   vector <double> & rec_modul
					   )
{
#if WITH_2D
	int ansD = use_only_2D ? IDYES : MessageBox(0, "2D(Yes) or 3D(No)", "Select method!!!", MB_YESNOCANCEL);
#endif
#if WITH_FOURIER
	int ansWF = MessageBox(0, "Wavelet(Yes) or Fourier(No)", "Select basis!!!", MB_YESNOCANCEL);
#endif
	int ans_OP = MessageBox(0, "Calculy(Yes) or Load(No) Forward Operator", "Select operator!!!", MB_YESNO);
	
double inv_k_oslablenie;	MyMethodsData3 mmd3; 
#if WITH_2D
	MyMethodsData mmd; 
	switch (ansD)
	{
	case IDYES:
		{
			if (ans_OP == IDYES)
			{
				// enter parameters
				mmd.increaser_pw = 2;

				cout << "Do you want reenter increaser_pw = " << mmd.increaser_pw << "?\n";

				char answer;
				cin >> answer;
				if (answer == 'y' || answer == 'Y')
				{
					cout << "increaser_pw?\n";
					cin >> mmd.increaser_pw;
				}
				
				// ��������� ����� � ��������	
				mmd.pw_rcd = 2;
				cout << "pw_rcd rows/cols deviation pw = " << mmd.pw_rcd << "\n";
				cout << "Do you want reenter pw_rcd rows/cols deviation pw (0,1,2,...)?\n";
				cin >> answer;
				if (answer == 'y' || answer == 'Y')
				{
					cout << "Enter pw_rcd rows/cols deviation pw?\n";
					cin >> mmd.pw_rcd;
				}

				///////////////////////////////////
				cout << "Enter Altitude z0, (m)" << endl;
				cin >> mmd.z0;
				cout << "z0 = " << mmd.z0 << " m" << endl;

			#if 1
				mmd.k_oslablenie = 0.0;
				cout << "Enter k_oslablenie, (m^-1)" << endl;
				cin >> mmd.k_oslablenie;
				inv_k_oslablenie = 1.0 / mmd.k_oslablenie;
			#else
				inv_k_oslablenie = 100;
				cout << "Enter inv_k_oslablenie, m" << endl;
				cin >> inv_k_oslablenie;
				mmd.k_oslablenie = 1.0 / inv_k_oslablenie;
			#endif
				cout << "k_oslablenie = " << mmd.k_oslablenie << " m^-1" << endl;


				cout << "Enter smoof_power" << endl;
				cin >> mmd.smoof_power;
				

				// save parameters
				char filename_parameters[4096];
				sprintf(filename_parameters, "%s\\parameters.par", dir_out);
				SaveParameters (filename_parameters, mmd);
			}
			else
			{
				// load parameters
				LoadParameters (mmd);
				inv_k_oslablenie = 1.0 / mmd.k_oslablenie;
			}
		}
		break;
	case IDNO:
		{
#endif //#if WITH_2D

			if (ans_OP == IDYES)
			{
				// enter parameters
				mmd3.increaser_pw = 2;

				cout << "Do you want reenter increaser_pw = " << mmd3.increaser_pw << "?\n";

				char answer;
				cin >> answer;
				if (answer == 'y' || answer == 'Y')
				{
					cout << "increaser_pw?\n";
					cin >> mmd3.increaser_pw;
				}
				
				// ��������� ����� � ��������	
				mmd3.pw_pcd = 2;
				cout << "pw_pcd pages/cols deviation pw = " << mmd3.pw_pcd << "\n";
				cout << "Do you want reenter pw_pcd pages/cols deviation pw (0,1,2,...)?\n";
				cin >> answer;
				if (answer == 'y' || answer == 'Y')
				{
					cout << "Enter pw_pcd pages/cols deviation pw?\n";
					cin >> mmd3.pw_pcd;
				}

				///////////////////////////////////
				cout << "Enter Altitude z0, (m)" << endl;
				cin >> mmd3.z0;
				cout << "z0 = " << mmd3.z0 << " m" << endl;

				cout << "Enter Altitude z_min, (m)" << endl;
				cin >> mmd3.z_min;
				cout << "z_min = " << mmd3.z_min << " m" << endl;

			#if 1
				mmd3.k_oslablenie = 0.0;
				cout << "Enter k_oslablenie, (m^-1)" << endl;
				cin >> mmd3.k_oslablenie;
				inv_k_oslablenie = 1.0 / mmd3.k_oslablenie;
			#else
				inv_k_oslablenie = 100;
				cout << "Enter inv_k_oslablenie, m" << endl;
				cin >> inv_k_oslablenie;
				mmd3.k_oslablenie = 1.0 / inv_k_oslablenie;
			#endif
				cout << "inv_k_oslablenie = " << inv_k_oslablenie << " m" << endl;
				cout << "k_oslablenie = " << mmd3.k_oslablenie << " m^-1" << endl;

				bool have_pereopredelen_system = false;
				cout << "Enter have_pereopredelen_system (0)" << endl;
				cin >> have_pereopredelen_system;
				mmd3.have_pereopredelen_system = have_pereopredelen_system;


				// save parameters
				char filename_parameters[4096];
				sprintf(filename_parameters, "%s\\parameters.par3", dir_out);
				SaveParameters (filename_parameters, mmd3);
			}
			else
			{
				// load parameters
				LoadParameters (mmd3);
				inv_k_oslablenie = 1.0 / mmd3.k_oslablenie;
			}
#if WITH_2D
		}
		break;
	}
#endif //#if WITH_2D
	//**********************************************
	//��������� ���� �������� ������ ������
	char filename_description[4096];
	sprintf(filename_description, "%s\\description2.txt", dir_out);		
	FILE * description = fopen(filename_description,"wt");

	//**********************************************
#if WITH_2D
	switch (ansD)
	{
	case IDYES:
		{
			if (description)
			{
				fprintf(description, "Altitude z0 = %f m\n", mmd.z0);
				fprintf(description, "inv_k_oslablenie = %f m\n", inv_k_oslablenie);
				fprintf(description, "k_oslablenie = %f m^-1\n", mmd.k_oslablenie);
				fprintf(description, "ab.k = %f\n", ab.k);
				fclose(description);
			}
		}
		break;
	case IDNO:
		{
#endif //#if WITH_2D
			if (description)
			{
				fprintf(description, "Altitude z0 = %f m\n", mmd3.z0);
				fprintf(description, "Altitude z_min = %f m\n", mmd3.z_min);
				fprintf(description, "inv_k_oslablenie = %f m\n", inv_k_oslablenie);
				fprintf(description, "k_oslablenie = %f m^-1\n", mmd3.k_oslablenie);


				fprintf(description, "k_oslablenie (po polju) = %f m^-1", mmd3.k_oslablenie);
				fprintf(description, "k_oslablenie (po moschnosti) = %f m^-1", mmd3.k_oslablenie * mmd3.pw_dnp);
				
				fprintf(description, "k_oslablenie (po polju) = %f dB/km", 1000. * mmd3.k_oslablenie / (0.1 * log(10.)) );
				fprintf(description, "k_oslablenie (po moschnosti) = %f dB/km", 1000. * mmd3.k_oslablenie * mmd3.pw_dnp / (0.1 * log(10.)) );

				fprintf(description, "ab.k = %f\n", ab.k);
				fprintf(description, "have_pereopredelen_system = %d\n", mmd3.have_pereopredelen_system);
				fclose(description);
			}
#if WITH_2D
		}
		break;
	}
#endif //#if WITH_2D
#if WITH_2D
	///////////////////////////////////
	switch (ansD)
	{
	case IDYES:
		{
#if WITH_FOURIER
			switch(ansWF)
			{
			case IDYES:
				{	
#endif//#if WITH_FOURIER

					bool to_fill_matrix = true;

					Wavelet2D w2;
					w2.wf_r = WF_DAUBECHIES; // ���� ��������
					w2.wf_r = WF_COIFLETS; // ���� ��������
					w2.order_r = 2; // ������� ��������
					w2.orderBiorthogonalDecomposition_r = 0; // ������� ��������
					w2.wf_c = WF_COIFLETS; // ���� ��������
					w2.order_c = 1; // ������� ��������
					w2.orderBiorthogonalDecomposition_c = 0; // ������� ��������	
					
					if (ans_OP == IDYES)
					{
						to_fill_matrix = true;
						// enter wav parameters

						// save wav parameters
					}
					else
					{
						// load wav parameters
						to_fill_matrix = false;

						// load mmd.vvd_filename of operator in wavelet space
						TCHAR filter[] =     
							TEXT("Matrix File of Operator(*.spm)\0*.spm\0")
							TEXT("All Files (*.*)\0*.*\0");
						sprintf(mmd.fn_operator_wav, "\0");
						if (OpenFileDlg(0, filter, mmd.fn_operator_spm) != S_OK)
						{
							return;
						}
						// load mmd.vvd_filename of operator in wavelet space
						TCHAR filter2[] =     
							TEXT("Matrix File of Wav Operator(*.spm)\0*.spm\0")
							TEXT("All Files (*.*)\0*.*\0");
						sprintf(mmd.fn_operator_wav, "\0");
						if (OpenFileDlg(0, filter2, mmd.fn_operator_wav) != S_OK)
						{
							return;
						}					
					}

					GetWaveletFilters(w2);

					DoMyMethod2W(description, mmd, w2, ab, X, Y, Z, A, to_fill_matrix);

					if (description)
					{
						WriteDescription(description, AutoBuildProfile::ab);
						fclose(description);
						description = NULL;
					}

					bool to_calculi_min_sq_mat = 
						ans_OP == IDYES 
						|| 
						IDYES == MessageBox(0, "Calculy(Yes) or Load(No) MinSquare Matrix", "Select MinSquare Matrix!!!", MB_YESNO);

					if (to_calculi_min_sq_mat)
					{
						double alpha = 0.0;
						cout << "Enter alpha - regularization koefficient" << endl;
						cin >> alpha;

						description = fopen(filename_description,"at");
						fprintf(description, "alpha on calculi_min_sq_mat = %f\n", alpha);
						fclose(description);

						sprintf(mmd.fn_min_sq_mat, "%s\\op_wav_min_sq_%f.spm", dir_out, alpha);					
						if (!FormMinSquareMatrix(mmd.fn_operator_wav, mmd.fn_min_sq_mat, alpha))
						{
						}
					}
					else
					{
						// load mmd.vvd_filename of operator in wavelet space
						TCHAR filter[] =     
							TEXT("Min Square Matrix File(*.spm)\0*.spm\0")
							TEXT("All Files (*.*)\0*.*\0");
						sprintf(mmd.fn_min_sq_mat, "\0");
						if (OpenFileDlg(0, filter, mmd.fn_min_sq_mat) != S_OK)
						{
							return;
						}
					}

					bool to_calculi_holesski = 
						to_calculi_min_sq_mat 
						|| 
						IDYES == MessageBox(0, "Calculy(Yes) or Load(No) HOLESSKI Matrix", "Select HOLESSKI Matrix!!!", MB_YESNO);

			
					if (to_calculi_holesski)
					{
#if 0
						//SparseStructureToMetafile(mmd.fn_min_sq_mat);
						SparseStructureToMetafile(mmd.fn_min_sq_mat, "min_sq_mat_struct.emf");
#endif
						double alpha = 0.0;
						cout << "Enter alpha - regularization koefficient" << endl;
						cin >> alpha;

						description = fopen(filename_description,"at");
						fprintf(description, "alpha on calculi_holesski = %f\n", alpha);
						fclose(description);

						sprintf(mmd.fn_Lt, "%s\\Lt_%f.spm", dir_out, alpha);
						//if (!Holesski(mmd.fn_min_sq_mat, mmd.fn_Lt, dir_out))

						long j_start = 0;
						cout << "Enter j_start > 0 - if previous calculations were broken" << endl;
						cout << "Else Enter j_start = 0" << endl;
						cin >> j_start;

						fprintf(description, "j_start on calculi_holesski = %ld\n", j_start);

						if (j_start > 0)
						{
													
							TCHAR filter[] =     
								TEXT("Description file of broken calc (*.txt)\0*.txt\0")
								TEXT("All Files (*.*)\0*.*\0");
							char fn[4098];
							sprintf(fn, "\0");
							if (OpenFileDlg(0, filter, fn) == S_OK)
							{
								strcpy(dir_out, fn);
								char *p1, *p2;
								p1 = strrchr(dir_out,'\\');
								p2 = strrchr(dir_out,'/');
								if(p1)
									*p1 = '\0';
								if(p2)
									*p2 = '\0';

								printf ("dir_out = %s\n", dir_out);
							}
						}

						if (!Holesski3(mmd.fn_min_sq_mat, mmd.fn_Lt, dir_out, alpha, j_start))
						{
						}
					}
					else
					{
						// load mmd.vvd_filename of operator in wavelet space
						TCHAR filter[] =     
							TEXT("Holesski Matrix File(*.spm)\0*.spm\0")
							TEXT("All Files (*.*)\0*.*\0");
						sprintf(mmd.fn_Lt, "\0");
						if (OpenFileDlg(0, filter, mmd.fn_Lt) != S_OK)
						{
							return;
						}
					}

					vector<double> * t = NULL;


					if (mmd.delta__x > mmd.delta__y)
					{
						//������� �� x
						t = &X;
					}
					else
					{
						//������� �� y
						t = &Y;
					}

					for(size_t c = 0; c < cols; c++) // ��� ������ ������� - ���� ��� ������� ���������
					{
						//printf_vector(v[c])
						DoInverseAndFillGrid2W(mmd, w2, *t, v[c],names_of_colomns[original_col_numbers[c]]);
					}	
					DoInverseAndFillGrid2W(mmd, w2, *t, vModul,"modul");
#if WITH_FOURIER
				}
				break;
			case IDNO:
				{
					DoMyMethod2(description, mmd, ab,X,Y,Z,vModul,"modul");

					for(size_t c = 0; c < cols; c++) // ��� ������ ������� - ���� ��� ������� ���������
					{
						
						DoMyMethod2(description, mmd, ab,X,Y,Z, v[c],names_of_colomns[original_col_numbers[c]]);
					}	
				}
				break;
			}
#endif //#if WITH_FOURIER
		}
		break;	
	case IDNO:
		{
#endif //#if WITH_2D
#if WITH_FOURIER
			switch(ansWF)
			{
			case IDYES:
				{
#endif //#if WITH_FOURIER
					
					/*DoMyMethod3W(description,k_oslablenie, ab,vX,vY,vZ,z0,vModul,"modul");

					for(size_t c = 0; c < cols; c++) // ��� ������ ������� - ���� ��� ������� ���������
					{
						DoMyMethod3W(description,k_oslablenie, ab,vX,vY,vZ, z0, v[c],names_of_colomns[original_col_numbers[c]]);
					}	*/
					bool to_fill_matrix = true;

					Wavelet3D w3;
#if 0
					w3.wf_p = WF_DAUBECHIES; // ���� ��������
					w3.order_p = 2; // ������� ��������
					w3.orderBiorthogonalDecomposition_p = 0; // ������� ��������	
					
					w3.wf_r = WF_DAUBECHIES; // ���� ��������
					w3.order_r = 3; // ������� ��������
					w3.orderBiorthogonalDecomposition_r = 0; // ������� ��������
					
					w3.wf_c = WF_DAUBECHIES; // ���� ��������
					w3.order_c = 3; // ������� ��������
					w3.orderBiorthogonalDecomposition_c = 0; // ������� ��������	
#else
#if 0
					w3.wf_p = WF_SYMLETS; // ���� ��������
					w3.order_p = 2; // ������� ��������
					w3.orderBiorthogonalDecomposition_p = 0; // ������� ��������	
					
					w3.wf_r = WF_SYMLETS; // ���� ��������
					w3.order_r = 3; // ������� ��������
					w3.orderBiorthogonalDecomposition_r = 0; // ������� ��������
					
					w3.wf_c = WF_SYMLETS; // ���� ��������
					w3.order_c = 3; // ������� ��������
					w3.orderBiorthogonalDecomposition_c = 0; // ������� ��������	
#else
					w3.wf_p = WF_COIFLETS; // ���� ��������
					w3.order_p = 1; // ������� ��������
					w3.orderBiorthogonalDecomposition_p = 0; // ������� ��������	
					
					w3.wf_r = WF_COIFLETS; // ���� ��������
					w3.order_r = 3; // ������� ��������
					w3.orderBiorthogonalDecomposition_r = 0; // ������� ��������
					
					w3.wf_c = WF_COIFLETS; // ���� ��������
					w3.order_c = 3; // ������� ��������
					w3.orderBiorthogonalDecomposition_c = 0; // ������� ��������	
#endif
					
#endif


					if (ans_OP == IDYES)
					{
						to_fill_matrix = true;
						// enter wav parameters

						// save wav parameters
					}
					else
					{
						// load wav parameters
						to_fill_matrix = false;

						// load mmd.vvd_filename of operator in wavelet space
						TCHAR filter[] =     
							TEXT("Matrix File of Operator(*.spm)\0*.spm\0")
							TEXT("All Files (*.*)\0*.*\0");
						sprintf(mmd3.fn_operator_spm, "\0");
						if (OpenFileDlg(0, filter, mmd3.fn_operator_spm) != S_OK)
						{
							return;
						}
						// load mmd.vvd_filename of operator in wavelet space
						TCHAR filter2[] =     
							TEXT("Matrix File of Wav Operator(*.spm)\0*.spm\0")
							TEXT("All Files (*.*)\0*.*\0");
						sprintf(mmd3.fn_operator_wav, "\0");
						if (OpenFileDlg(0, filter2, mmd3.fn_operator_wav) != S_OK)
						{
							return;
						}					
					}

					bool to_calculi_min_sq_mat = 
						ans_OP == IDYES 
						|| 
						IDYES == MessageBox(0, "Calculy(Yes) or Load(No) MinSquare Matrix", "Select MinSquare Matrix!!!", MB_YESNO);
					
					double alpha_min_sq = 0.001;
					if (to_calculi_min_sq_mat)
					{
						cout << "Enter alpha_min_sq - regularization koefficient [0.001]" << endl;
						cin >> alpha_min_sq;

						description = fopen(filename_description,"at");
						fprintf(description, "alpha on calculi_min_sq_mat = %f\n", alpha_min_sq);
						fclose(description);
					}
					else
					{
						// load mmd.vvd_filename of operator in wavelet space
						TCHAR filter[] =     
							TEXT("Min Square Matrix File(*.spm)\0*.spm\0")
							TEXT("All Files (*.*)\0*.*\0");
						sprintf(mmd3.fn_min_sq_mat, "\0");
						if (OpenFileDlg(0, filter, mmd3.fn_min_sq_mat) != S_OK)
						{
							return;
						}
					}

					bool to_calculi_holesski = 
						to_calculi_min_sq_mat 
						|| 
						IDYES == MessageBox(0, "Calculy(Yes) or Load(No) HOLESSKI Matrix", "Select HOLESSKI Matrix!!!", MB_YESNO);

			
					double alpha_holesski = 0.001;
					long j_start = 0;
					if (to_calculi_holesski)
					{
						cout << "Enter alpha_holesski - regularization koefficient" << endl;
						cin >> alpha_holesski;

						cout << "Enter j_start > 0 - if previous calculations of Holesski were broken" << endl;
						cout << "Else Enter j_start = 0" << endl;
						cin >> j_start;

						fprintf(description, "alpha on calculi_holesski = %f\n", alpha_holesski);
						fprintf(description, "j_start on calculi_holesski = %ld\n", j_start);


						if (j_start > 0)
						{													
							TCHAR filter[] =     
								TEXT("Description file of broken calc (*.txt)\0*.txt\0")
								TEXT("All Files (*.*)\0*.*\0");
							char fn[4098];
							sprintf(fn, "\0");
							if (OpenFileDlg(0, filter, fn) == S_OK)
							{
								strcpy(dir_out, fn);
								char *p1, *p2;
								p1 = strrchr(dir_out,'\\');
								p2 = strrchr(dir_out,'/');
								if(p1)
									*p1 = '\0';
								if(p2)
									*p2 = '\0';

								printf ("dir_out = %s\n", dir_out);
							}
						}
					}
					else
					{
						// load mmd.vvd_filename of operator in wavelet space
						TCHAR filter[] =     
							TEXT("Holesski Matrix File(*.spm)\0*.spm\0")
							TEXT("All Files (*.*)\0*.*\0");
						sprintf(mmd3.fn_Lt, "\0");
						if (OpenFileDlg(0, filter, mmd3.fn_Lt) != S_OK)
						{
							return;
						}
					}

					if (type == 0)
					{
						cout << "Enter smoof_power" << endl;
						cin >> mmd3.smoof_power;
					}

					GetWaveletFilters(w3);


					// ������ ���������� �����
					DoMyMethod3W(type, granicy_kak_glubina, description, mmd3, w3, ab, X, Y, Z, A, to_fill_matrix);

					if (description)
					{
						WriteDescription(description, AutoBuildProfile::ab);
						fclose(description);
						description = NULL;
					}


					if (to_calculi_min_sq_mat)
					{
						sprintf(mmd3.fn_min_sq_mat, "%s\\op_wav_min_sq_%f.spm", dir_out, alpha_min_sq);					
						if (!FormMinSquareMatrix(mmd3.fn_operator_wav, mmd3.fn_min_sq_mat, alpha_min_sq))
						{
							printf("Error while FormMinSquareMatrix()\n");
							return;
						}
					}
			
					if (to_calculi_holesski)
					{
#if 0
						//SparseStructureToMetafile(mmd3.fn_min_sq_mat);
						SparseStructureToMetafile(mmd3.fn_min_sq_mat, "min_sq_mat_struct.emf");
#endif

#if 0
						sprintf(mmd3.fn_Lt, "%s\\Lt.spm", dir_out);
						if (!Holesski(mmd3.fn_min_sq_mat, mmd3.fn_Lt, dir_out))
						{
							printf("Error while Holesski()\n");
							return;
						}
#else
						sprintf(mmd3.fn_Lt, "%s\\Lt_%f.spm", dir_out, alpha_holesski);
						if (!Holesski3(mmd3.fn_min_sq_mat, mmd3.fn_Lt, dir_out, j_start, 0.0))
						{
							printf("Error while Holesski3()\n");
							return;
						}
#endif
					}

					switch (type)
					{
					case 0:
						{
							rec_signals.resize(cols);
							for(size_t c = 0; c < cols; c++) // ��� ������ ������� - ���� ��� ������� ���������
							{
								//printf_vector(v[c])
								DoInverseAndFillGrid3W(mmd3, w3, v[c], names_of_colomns[original_col_numbers[c]], rec_signals[c]);
							}	
							DoInverseAndFillGrid3W(mmd3, w3, vModul, "modul", rec_modul);
						}
						break;
					case 1:
						{
							vector<vector<double> > new_v;
							vector<string> new_names_of_colomns;
							int cols_3 = cols / 3;//2
							new_v.resize(cols_3);
							new_names_of_colomns.resize(cols_3);

							// for debug ///////////////////////////////////////////////
							size_t len_v = 0, size_v = v.size();
							if (size_v) len_v = v[0].size();
							// for debug ///////////////////////////////////////////////

							for (int cc = 0; cc < cols_3; cc++)
							{
								for(size_t c = cc * 3; c < (cc+1) * 3; c++) 
								{								
									for (int i = 0; i < X.size(); i++)
									{
										double value_v_c_i = v[c][i];
										new_v[cc].push_back(value_v_c_i);
									}
									new_names_of_colomns[cc] += 
										names_of_colomns[original_col_numbers[c]];
									new_names_of_colomns[cc] += "_";
								}
							}

							rec_signals.resize(cols_3);
							for (int cc = 0; cc < cols_3; cc++) // ��� ������ ������� - ���� ��� ������� ���������
							{
								//printf_vector(v[c])
								DoInverseAndFillGrid3W(mmd3, w3, new_v[cc], 
									new_names_of_colomns[cc], 
									rec_signals[cc]);
							}	
						}
						break;
					case -1:
						{
							//vector<vector<double> > new_v;
							vector<string> new_names_of_colomns;
							int cols_3 = cols / 3;//2
							//new_v.resize(cols_3);
							new_names_of_colomns.resize(cols_3);

							// for debug ///////////////////////////////////////////////
							size_t len_v = 0, size_v = v.size();
							if (size_v) len_v = v[0].size();
							// for debug ///////////////////////////////////////////////

							for (int cc = 0; cc < cols_3; cc++)
							{
								for(size_t c = cc * 3; c < (cc+1) * 3; c++) 
								{								
									/*for (int i = 0; i < X.size(); i++)
									{
										double value_v_c_i = v[c][i];
										new_v[cc].push_back(value_v_c_i);
									}*/
									new_names_of_colomns[cc] += 
										names_of_colomns[original_col_numbers[c]];
									new_names_of_colomns[cc] += "_";
								}
							}

							rec_signals.resize(cols_3);
							for (int cc = 0; cc < cols_3; cc++) // ��� ������ ������� - ���� ��� ������� ���������
							{
								//printf_vector(v[c])
								DoInverseAndFillGrid3W(mmd3, w3, v[cc], 
									new_names_of_colomns[cc], 
									rec_signals[cc]);
							}	
						}
						break;
					}
					
#if WITH_FOURIER
				}
				break;
			case IDNO:
				{
					DoMyMethod3(description,mmd3.k_oslablenie, ab,X,Y,Z,mmd.z0,vModul,"modul");

					for(size_t c = 0; c < cols; c++) // ��� ������ ������� - ���� ��� ������� ���������
					{
						DoMyMethod3(description,mmd3.k_oslablenie, ab,X,Y,Z, mmd.z0, v[c],names_of_colomns[original_col_numbers[c]]);
					}	
				}
				break;
			}
#endif //#if WITH_FOURIER
#if WITH_2D
		}
		break;
	}
#endif //#if WITH_2D

	description = fopen(filename_description,"at");
	if (description)
	{
		WriteDescription(description, AutoBuildProfile::ab);
		fclose(description);
		description = NULL;
	}
}

void UseOneOfMyMethods3W_preparing(int type, // ��� ������ ������
					   int & ans_OP,
					   double z0, double z_min, double & DZ,
					   int & cols,
					   MyMethodsData3 & mmd3,					   
					   Wavelet3D & w3,
					   auto_build_parametrs & ab
					   )
{
	
	double inv_k_oslablenie;	

	if (ans_OP == IDYES)
	{
		// enter parameters
		mmd3.increaser_pw = 2;

		cout << "Do you want reenter increaser_pw = " << mmd3.increaser_pw << "?\n";

		char answer;
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			cout << "increaser_pw?\n";
			cin >> mmd3.increaser_pw;
		}
		
		// ��������� ����� � ��������	
		mmd3.pw_pcd = 2;
		cout << "pw_pcd pages/cols deviation pw = " << mmd3.pw_pcd << "\n";
		cout << "Do you want reenter pw_pcd pages/cols deviation pw (0,1,2,...)?\n";
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			cout << "Enter pw_pcd pages/cols deviation pw?\n";
			cin >> mmd3.pw_pcd;
		}

		//////////////////////////////////
#if 1
		mmd3.z0 = z0;
		mmd3.z_min = z_min;
#else
		cout << "Enter Altitude z0, (m)" << endl;
		cin >> mmd3.z0;
		cout << "z0 = " << mmd3.z0 << " m" << endl;

		cout << "Enter Altitude z_min, (m)" << endl;
		cin >> mmd3.z_min;
		cout << "z_min = " << mmd3.z_min << " m" << endl;
#endif
		mmd3.k_oslablenie = 0.0; inv_k_oslablenie = 0.0;
		if (type == 0 || type == 1)
		{
		}
		else if (type == 2)
		{
			cout << "Enter noise color: 1 blue, 2 blue-white 3 white 4 pink-white" << endl;
			cin >> mmd3.noise_color;
			cout << "Enter nju_min Hz" << endl;
			cin >> mmd3.nju_min;
			cout << "Enter nju_max Hz" << endl;
			cin >> mmd3.nju_max;
		}
		cout << "Enter wave_type 0 - plane wave 1 - spherical wave" << endl;
		cin >> mmd3.wave_type;

		cout << "Enter pw_dnp - power or diargamm napravlennosty priyomnika (2 recommended)" << endl;
		cin >> mmd3.pw_dnp;

		cout << "Enter min_value (small positive, for example from 1e-16 to 0.03)" << endl;
		cin >> mmd3.min_value;

		cout << "Enter dx/DZ=dy/DZ (for example 2)" << endl;
		cin >> mmd3.dx_and_dy_per_DZ;

		cout << "Enter granicy_kak_glubina?  0 - no 1 - yes" << endl;
		cin >> mmd3.granicy_kak_glubina;


// here calculi operator  by mean[c]

		cout << "Enter rows" << endl;
		cin >> mmd3.rows;

		cout << "Enter cols" << endl;
		cin >> mmd3.cols;

		cout << "Enter pages" << endl;
		cin >> mmd3.pages;

		cout << "Enter iter_save" << endl;
		cin >> mmd3.iter_save;

		cout << "Parameters of power distribution model (w0 w05 w1 w2)" << endl;
		cout << "number means W ~ w0*h^0 + w05*h^0.5 + w1*h^1 + w2*h^2" << endl;
		cout << "recomended w0 = 1 w05 = 0 w1 = 0 w2 = 0" << endl;
		cout << "Enter w0" << endl;
		cin >> mmd3.spm.w0;

		cout << "Enter w05" << endl;
		cin >> mmd3.spm.w05;

		cout << "Enter w1" << endl;
		cin >> mmd3.spm.w1;

		cout << "Enter w2" << endl;
		cin >> mmd3.spm.w2;

		if (type == 0 || type == 1)
		{
		#if 1
			mmd3.k_oslablenie = 0.0;
			cout << "Enter k_oslablenie (po naprjazhonnosti polja, for example 0.00023025 -> 1.999 dB/km by power), (m^-1)" << endl;
			cin >> mmd3.k_oslablenie;
			inv_k_oslablenie = 1.0 / mmd3.k_oslablenie;
		#else
			inv_k_oslablenie = 100;
			cout << "Enter inv_k_oslablenie, m" << endl;
			cin >> inv_k_oslablenie;
			mmd3.k_oslablenie = 1.0 / inv_k_oslablenie;
		#endif
			cout << "inv_k_oslablenie = " << inv_k_oslablenie << " m" << endl;
			cout << "k_oslablenie (po polju) = " << mmd3.k_oslablenie << " m^-1" << endl;
			cout << "k_oslablenie (po moschnosti) = " << mmd3.k_oslablenie * mmd3.pw_dnp   << " m^-1" << endl;
			
			cout << "k_oslablenie (po polju) = " << 1000. * mmd3.k_oslablenie / (0.1 * log(10.)) << " dB/km" << endl;
			cout << "k_oslablenie (po moschnosti) = " << 1000. * mmd3.k_oslablenie * mmd3.pw_dnp / (0.1 * log(10.)) << " dB/km" << endl;
			
		}
		else if (type == 2)
		{
			cout << "Enter ro Om*m" << endl;
			cin >> mmd3.ro;
		}

		

		cout << "Enter save_operator_grid" << endl;
		cin >> mmd3.save_operator_grid;

		cout << "Enter save_min_sq_grid" << endl;
		cin >> mmd3.save_min_sq_grid;

		cout << "Enter to_calculi_holesski (1 - holesski 0 - LUP-recomended)" << endl;
		cin >> mmd3.to_calculi_holesski;

		cout << "Enter use_norm_w" << endl <<
			"(1 - initialisation by using of power distribution model (w) scaling on mean level of signals X,Y and Z)" << endl <<
			"(0 - initialisation by (holesski or LUP) every light colomn decision)" << endl
			;
		cin >> mmd3.use_norm_w;

		cout << "Enter use_norm_k " << endl <<
			"0 - use MinSqure method for reconstructed signal matrix (MREC) " << endl <<
			"0 - if you chose use_norm_w = 1 that you should enter 1:" << endl <<
			"1 - use norm_k - to use koefficient for scalling of power distribution model on mean level of signals" << endl;

		cin >> mmd3.use_norm_k;

		cout << "Enter norm_k_part (0 .. 1)" << endl <<
			"you can enter 1 or 0.9 or 0.8" << endl <<
			"to slightly decreese initial power distribution model" << endl
			;
		cin >> mmd3.norm_k_part;

		cout << "Enter use_norm_k_on_every_iteration experimental (0 - no 1 - yes 0 - recommended)" << endl;
		cin >> mmd3.use_norm_k_on_every_iteration;

		cout << "Enter dXYZ_part (0 .. 1)" << endl <<
			"you can enter 1 or 0.9 or 0.8" << endl <<
			"to slightly decreese input for very micro iteration" << endl
			;
		cin >> mmd3.dXYZ_part;

		bool have_pereopredelen_system = false;
		cout << "Enter have_pereopredelen_system (0)" << endl;
		cin >> have_pereopredelen_system;
		mmd3.have_pereopredelen_system = have_pereopredelen_system;





		cout << "Enter alpha_mode 0 - single (1 - vector diagonal proporcionally - not jet realised)" << endl;
		cin >> mmd3.alpha_mode;

		cout << "Enter alpha_min_sq - regularization koefficient [0.001]" << endl;
		cin >> mmd3.alpha_min_sq;

		cout << "Enter n_alpha - number of regularization koefficients" << endl;
		cin >> mmd3.n_alpha;

		mmd3.v_alpha.resize(mmd3.n_alpha);
		for (int i_alpha = 0; i_alpha < mmd3.n_alpha; i_alpha++)
		{
			cout << "Enter alpha[" << i_alpha << "]" << endl;
			cin >> mmd3.v_alpha[i_alpha];
		}

	//	cout << "Enter alpha_holesski - regularization koefficient" << endl;
	//	cin >> mmd3.alpha_holesski;

		// save parameters
		char filename_parameters[4096];
		sprintf(filename_parameters, "%s\\parameters.par3", dir_out);
		SaveParameters (filename_parameters, mmd3);
	}
	else
	{
		// load parameters
		LoadParameters (mmd3);
		inv_k_oslablenie = 1.0 / mmd3.k_oslablenie;
		DZ = mmd3.z0 - mmd3.z_min;
	}
	//**********************************************
	//��������� ���� �������� ������ ������
	char filename_description[4096];
	sprintf(filename_description, "%s\\description.txt", dir_out);		
	FILE * description = fopen(filename_description,"wt");

	//**********************************************

	if (description)
	{
		fprintf(description, "Altitude z0 = %f m\n", mmd3.z0);
		fprintf(description, "Altitude z_min = %f m\n", mmd3.z_min);
		fprintf(description, "inv_k_oslablenie = %f m\n", inv_k_oslablenie);
		fprintf(description, "k_oslablenie = %f m^-1\n", mmd3.k_oslablenie);
		fprintf(description, "ab.k = %f\n", ab.k);
		fprintf(description, "have_pereopredelen_system = %d\n", mmd3.have_pereopredelen_system);

		fprintf(description, "\n");
		fprintf(description, "noise_color = %d\n", mmd3.noise_color);
		switch (mmd3.noise_color)
		{
		case 1://blue
			{
				fprintf(description, "noise_color = blue\n");
			}
			break;
		case 2://blue-white
			{
				fprintf(description, "noise_color = blue-white\n");
			}
			break;
		case 3://white
			{
				fprintf(description, "noise_color = white\n");
			}
			break;
		case 4://pink-white
			{
				fprintf(description, "noise_color = pink-white\n");
			}
			break;
		}
		fprintf(description, "ro = %f\n", mmd3.ro);
		fprintf(description, "nju_min = %f\n", mmd3.nju_min);
		fprintf(description, "nju_max = %f\n\n", mmd3.nju_max);

		fprintf(description, "pw_dnp = %f\n", mmd3.pw_dnp);
		fprintf(description, "min_value = %e\n\n", mmd3.min_value);

		fprintf(description, "dx_and_dy_per_DZ = %f\n", mmd3.dx_and_dy_per_DZ);
		fprintf(description, "granicy_kak_glubina = %d\n", mmd3.granicy_kak_glubina);

		fprintf(description, "rows = %d\n", mmd3.rows);
		fprintf(description, "cols = %d\n", mmd3.cols);
		fprintf(description, "pages = %d\n", mmd3.pages);

		fprintf(description, "w0 = %f\n", mmd3.spm.w0);
		fprintf(description, "w05 = %f\n", mmd3.spm.w05);
		fprintf(description, "w1 = %f\n", mmd3.spm.w1);
		fprintf(description, "w2 = %f\n", mmd3.spm.w2);



		

		fprintf(description, "alpha_mode = %d\n", mmd3.alpha_mode);

		fprintf(description, "save_min_sq_grid = %d\n", mmd3.save_min_sq_grid);
		fprintf(description, "save_operator_grid = %d\n", mmd3.save_operator_grid);
		fprintf(description, "to_calculi_holesski = %d\n", mmd3.to_calculi_holesski);

		fprintf(description, "use_norm_w = %d\n", mmd3.use_norm_w);
		fprintf(description, "use_norm_k = %d\n", mmd3.use_norm_k);
		fprintf(description, "norm_k_part = %f\n", mmd3.norm_k_part);
		fprintf(description, "use_norm_k_on_every_iteration = %d\n", mmd3.use_norm_k_on_every_iteration);
		fprintf(description, "dXYZ_part = %f\n", mmd3.dXYZ_part);

		fprintf(description, "wave_type = %d\n", mmd3.wave_type);

		switch (mmd3.wave_type)
		{
		case 0:
			{
				fprintf(description, "wave_type = plane\n");
			}
			break;
		case 1:
			{
				fprintf(description, "wave_type = spherical\n");
			}
			break;
		}
		fclose(description);
	}

#if 0
	w3.wf_p = WF_DAUBECHIES; // ���� ��������
	w3.order_p = 2; // ������� ��������
	w3.orderBiorthogonalDecomposition_p = 0; // ������� ��������	
	
	w3.wf_r = WF_DAUBECHIES; // ���� ��������
	w3.order_r = 3; // ������� ��������
	w3.orderBiorthogonalDecomposition_r = 0; // ������� ��������
	
	w3.wf_c = WF_DAUBECHIES; // ���� ��������
	w3.order_c = 3; // ������� ��������
	w3.orderBiorthogonalDecomposition_c = 0; // ������� ��������	
#else
#if 0
	w3.wf_p = WF_SYMLETS; // ���� ��������
	w3.order_p = 2; // ������� ��������
	w3.orderBiorthogonalDecomposition_p = 0; // ������� ��������	
	
	w3.wf_r = WF_SYMLETS; // ���� ��������
	w3.order_r = 3; // ������� ��������
	w3.orderBiorthogonalDecomposition_r = 0; // ������� ��������
	
	w3.wf_c = WF_SYMLETS; // ���� ��������
	w3.order_c = 3; // ������� ��������
	w3.orderBiorthogonalDecomposition_c = 0; // ������� ��������	
#else
	w3.wf_p = WF_COIFLETS; // ���� ��������
	w3.order_p = 1; // ������� ��������
	w3.orderBiorthogonalDecomposition_p = 0; // ������� ��������	
	
	w3.wf_r = WF_COIFLETS; // ���� ��������
	w3.order_r = 3; // ������� ��������
	w3.orderBiorthogonalDecomposition_r = 0; // ������� ��������
	
	w3.wf_c = WF_COIFLETS; // ���� ��������
	w3.order_c = 3; // ������� ��������
	w3.orderBiorthogonalDecomposition_c = 0; // ������� ��������	
#endif
	
#endif

	cout << "Enter j_start > 0 - if previous calculations of Holesski were broken" << endl;
	cout << "Else Enter j_start = 0" << endl;
	cin >> mmd3.j_start;
}
void UseOneOfMyMethods3W(int type, // ��� ������ ������
					   bool granicy_kak_glubina, 
					   int & ans_OP,
					   double z0, double z_min,
					   int & cols,
					   MyMethodsData3 & mmd3,
					   Wavelet3D & w3,
					   auto_build_parametrs & ab,
					   vector<double> & X,
					   vector<double> & Y,
					   vector<double> & Z, // ��������� ��������� - ����� �������
					   vector<vector<anten_direction> > & A,
					   vector<double> & vModul,
					   vector<vector<double> > & v,
					   vector<string> & names_of_colomns,
					   vector<size_t> & original_col_numbers,

					   vector<vector <double> > & rec_signals,
					   vector <double> & rec_modul
					   )
{
	//**********************************************
	//��������� ���� �������� ������ ������
	char filename_description[4096];
	sprintf(filename_description, "%s\\description3W.txt", dir_out);		
	FILE * description = fopen(filename_description,"wt");

	/*DoMyMethod3W(description,k_oslablenie, ab,vX,vY,vZ,z0,vModul,"modul");

	for(size_t c = 0; c < cols; c++) // ��� ������ ������� - ���� ��� ������� ���������
	{
		DoMyMethod3W(description,k_oslablenie, ab,vX,vY,vZ, z0, v[c],names_of_colomns[original_col_numbers[c]]);
	}	*/

	bool to_fill_matrix = true;



	if (ans_OP == IDYES)
	{
		to_fill_matrix = true;
		// enter wav parameters

		// save wav parameters
	}
	else
	{
		// load wav parameters
		to_fill_matrix = false;

		// load mmd.vvd_filename of operator in wavelet space
		TCHAR filter[] =     
			TEXT("Matrix File of Operator(*.spm)\0*.spm\0")
			TEXT("All Files (*.*)\0*.*\0");
		sprintf(mmd3.fn_operator_spm, "\0");
		if (OpenFileDlg(0, filter, mmd3.fn_operator_spm) != S_OK)
		{
			return;
		}
		// load mmd.vvd_filename of operator in wavelet space
		TCHAR filter2[] =     
			TEXT("Matrix File of Wav Operator(*.spm)\0*.spm\0")
			TEXT("All Files (*.*)\0*.*\0");
		sprintf(mmd3.fn_operator_wav, "\0");
		if (OpenFileDlg(0, filter2, mmd3.fn_operator_wav) != S_OK)
		{
			return;
		}					
	}

	bool to_calculi_min_sq_mat = 
		ans_OP == IDYES 
		|| 
		IDYES == MessageBox(0, "Calculy(Yes) or Load(No) MinSquare Matrix", "Select MinSquare Matrix!!!", MB_YESNO);
	
	if (to_calculi_min_sq_mat)
	{

		description = fopen(filename_description,"at");
		fprintf(description, "alpha on calculi_min_sq_mat = %f\n", mmd3.alpha_min_sq);
		fclose(description);
	}
	else
	{
		// load mmd.vvd_filename of operator in wavelet space
		TCHAR filter[] =     
			TEXT("Min Square Matrix File(*.spm)\0*.spm\0")
			TEXT("All Files (*.*)\0*.*\0");
		sprintf(mmd3.fn_min_sq_mat, "\0");
		if (OpenFileDlg(0, filter, mmd3.fn_min_sq_mat) != S_OK)
		{
			return;
		}
	}

	bool to_calculi_holesski = 
		to_calculi_min_sq_mat 
		|| 
		IDYES == MessageBox(0, "Calculy(Yes) or Load(No) HOLESSKI Matrix", "Select HOLESSKI Matrix!!!", MB_YESNO);


	if (to_calculi_holesski)
	{

//		fprintf(description, "alpha on calculi_holesski = %f\n", mmd3.alpha_holesski);
		fprintf(description, "j_start on calculi_holesski = %ld\n", mmd3.j_start);


		if (mmd3.j_start > 0)
		{													
			TCHAR filter[] =     
				TEXT("Description file of broken calc (*.txt)\0*.txt\0")
				TEXT("All Files (*.*)\0*.*\0");
			char fn[4098];
			sprintf(fn, "\0");
			if (OpenFileDlg(0, filter, fn) == S_OK)
			{
				strcpy(dir_out, fn);
				char *p1, *p2;
				p1 = strrchr(dir_out,'\\');
				p2 = strrchr(dir_out,'/');
				if(p1)
					*p1 = '\0';
				if(p2)
					*p2 = '\0';

				printf ("dir_out = %s\n", dir_out);
			}
		}
	}
	else
	{
		// load mmd.vvd_filename of operator in wavelet space
		TCHAR filter[] =     
			TEXT("Holesski Matrix File(*.spm)\0*.spm\0")
			TEXT("All Files (*.*)\0*.*\0");
		sprintf(mmd3.fn_Lt, "\0");
		if (OpenFileDlg(0, filter, mmd3.fn_Lt) != S_OK)
		{
			return;
		}
	}

	if (type == 0)
	{
		cout << "Enter smoof_power" << endl;
		cin >> mmd3.smoof_power;
	}

	GetWaveletFilters(w3);


	// ������ ���������� �����
	DoMyMethod3W(type, granicy_kak_glubina, description, mmd3, w3, ab, X, Y, Z, A, to_fill_matrix);

	if (description)
	{
		WriteDescription(description, AutoBuildProfile::ab);
		fclose(description);
		description = NULL;
	}


	if (to_calculi_min_sq_mat)
	{
		sprintf(mmd3.fn_min_sq_mat, "%s\\op_wav_min_sq_%f.spm", dir_out, mmd3.alpha_min_sq);					
		if (!FormMinSquareMatrix(mmd3.fn_operator_wav, mmd3.fn_min_sq_mat, mmd3.alpha_min_sq))
		{
			printf("Error while FormMinSquareMatrix()\n");
			return;
		}
	}

	if (to_calculi_holesski)
	{
#if 0
		//SparseStructureToMetafile(mmd3.fn_min_sq_mat);
		SparseStructureToMetafile(mmd3.fn_min_sq_mat, "min_sq_mat_struct.emf");
#endif


		sprintf(mmd3.fn_Lt, "%s\\Lt.spm", dir_out);
		if (!Holesski3(mmd3.fn_min_sq_mat, mmd3.fn_Lt, dir_out, mmd3.j_start, 0.0))
		{
			printf("Error while Holesski3()\n");
			return;
		}

	}

	switch (type)
	{
	case 0:
		{
			rec_signals.resize(cols);
			for(size_t c = 0; c < cols; c++) // ��� ������ ������� - ���� ��� ������� ���������
			{
				//printf_vector(v[c])
				DoInverseAndFillGrid3W(mmd3, w3, v[c], names_of_colomns[original_col_numbers[c]], rec_signals[c]);
			}	
			DoInverseAndFillGrid3W(mmd3, w3, vModul, "modul", rec_modul);
		}
		break;
	case 1:
		{
			vector<vector<double> > new_v;
			vector<string> new_names_of_colomns;
			int cols_3 = cols / 3;//2
			new_v.resize(cols_3);
			new_names_of_colomns.resize(cols_3);

			// for debug ///////////////////////////////////////////////
			size_t len_v = 0, size_v = v.size();
			if (size_v) len_v = v[0].size();
			// for debug ///////////////////////////////////////////////

			for (int cc = 0; cc < cols_3; cc++)
			{
				for(size_t c = cc * 3; c < (cc+1) * 3; c++) 
				{								
					for (int i = 0; i < X.size(); i++)
					{
						double value_v_c_i = v[c][i];
						new_v[cc].push_back(value_v_c_i);
					}
					new_names_of_colomns[cc] += 
						names_of_colomns[original_col_numbers[c]];
					new_names_of_colomns[cc] += "_";
				}
			}

			rec_signals.resize(cols_3);
			for (int cc = 0; cc < cols_3; cc++) // ��� ������ ������� - ���� ��� ������� ���������
			{
				//printf_vector(v[c])
				DoInverseAndFillGrid3W(mmd3, w3, new_v[cc], 
					new_names_of_colomns[cc], 
					rec_signals[cc]);
			}	
		}
		break;
	case -1:
		{
			//vector<vector<double> > new_v;
			vector<string> new_names_of_colomns;
			int cols_3 = cols / 3;//2
			//new_v.resize(cols_3);
			new_names_of_colomns.resize(cols_3);

			// for debug ///////////////////////////////////////////////
			size_t len_v = 0, size_v = v.size();
			if (size_v) len_v = v[0].size();
			// for debug ///////////////////////////////////////////////

			for (int cc = 0; cc < cols_3; cc++)
			{
				for(size_t c = cc * 3; c < (cc+1) * 3; c++) 
				{								
					/*for (int i = 0; i < X.size(); i++)
					{
						double value_v_c_i = v[c][i];
						new_v[cc].push_back(value_v_c_i);
					}*/
					new_names_of_colomns[cc] += 
						names_of_colomns[original_col_numbers[c]];
					new_names_of_colomns[cc] += "_";
				}
			}

			rec_signals.resize(cols_3);
			for (int cc = 0; cc < cols_3; cc++) // ��� ������ ������� - ���� ��� ������� ���������
			{
				//printf_vector(v[c])
				DoInverseAndFillGrid3W(mmd3, w3, v[cc], 
					new_names_of_colomns[cc], 
					rec_signals[cc]);
			}	
		}
		break;
	}
	

	description = fopen(filename_description,"at");
	if (description)
	{
		WriteDescription(description, AutoBuildProfile::ab);
		fclose(description);
		description = NULL;
	}
}
#if 0
bool AutoBuildProfile_main(
						   bool consol, 
						   AutoBuildProfile * p_auto_build_profile, 
						   auto_build_parametrs& ab)
{
	int answer = MessageBox(0, "2 - X,Y (Yes) or 3 X,Y,Z(No)", "How Many Geo coordinate colomns?", MB_YESNOCANCEL);
	switch (answer)
	{
	case IDYES:
		{
			AutoBuildProfile::ab.tcols = 2;
		}
		break;	
	case IDNO:
		{
			AutoBuildProfile::ab.tcols = 3;
		}
		break;
	default :
		return false;
	}

	// double quantil_naklony = 0.50;
	// �������� ������ "�������" �� ���� ������
	// �� ����� �������� ������ �� �������� � "�������",
	// ������� ����� ����������� ���� �������
	// ��� ������ ��������, ��� ������ ������� ����� �������

	//bool allow_sd_limit = true;
	//double peregib_krutizna_quantil = 0.40;
	// �������� ������ ����� �������� �� �� ��������
	// �������� ������ ��������� ����������� ������ �����������
	// ���� �������� ������ ����� 0,5 �� �� �������� ��� ������������ ����� ��������
	// ��� ������ �������� ������ ��� ������ ����� �������� �� ���������������,
	// ��� ����� �� ��������� ���� ���� ������ ����� ��������

	//double limit = 0.5;	
	//double limit_dima = 0.8, double limit_1 = 0.9;
	//double minimum_of_signal = 0.1;
				
	//size_t start_j1 = 1;//��������� ������� ���������� ��� ������ �������
	//size_t start_j2 = 0;//��������� ������� ���������� ��� window_cycles_after_locals

	//bool use_repeat_points = true;
	//bool use_repeat_points = false;
	//int n = 1;//����� ������� ������� ( ����� 0 � ����)
		
	//int delim = ',';

	int num_col = -1;

	//##############################################################
	//���� ������ ����� � �������� �������
	vector<bool> use_col;

#if 0
	char * num_col_filename;
	int delim;
	if (ab) 
	{
		num_col_filename = ab->num_col_filename;
		delim = ab->delim;

	}
	else
	{
		if (OpenFileDlg(NULL, 
			"Col Num Data File(*.dat)\0*.dat\0"
			"CSV (*.csv)\0*.csv\0"
			"All files \0*.*\0") != S_OK)
		{
			return false;
		}
		num_col_filename = szPath;

		cout << "Enter file delimiter:\n";
		cout << "\t 1 - ','\n";
		cout << "\t 2 - ';'\n";
		cout << "\t 3 - 'tab'\n";
		cout << "\t 4 - 'spase'\n";
		int ans;
		cin >> ans;
		switch(ans)
		{
		case 1:
			delim = ',';
			break;
		case 2:
			delim = ';';
			break;
		case 3:
			delim = '\t';
			break;
		case 4:
			delim = ' ';
			break;
		default :
			delim = ',';
		}
	}
#endif
	if (!ReadColomnNumbers(ab,use_col,num_col,ab.delim))
	{
		return false;
	}
	if (OpenFileDlg(NULL, 
		"CSV (*.csv)\0*.csv\0"
		"Data (*.dat)\0*.dat\0"
		"All files \0*.*\0") == S_OK)
	{
		int rows, cols;
		vector<vector<vector<vert_korr_points> > > vvvvkp;
		vvvvkp.clear();

		vector<profile_interval> profile_intervals;
		profile_intervals.clear();		

		char filename[256];
		vector<size_t> original_col_numbers;
		vector<vector<double> > v;
		vector<vector<double> > w;
#if SOURCE_COORDINATES_3D
		vector<double> X;
		vector<double> Y;
		vector<double> Z;
#else
		vector<double> t;
#endif
		vector<string> names_of_colomns;

		if (!ReadProfileFile( 
				  szPath, directory, filename, 
				  consol, 
				  p_auto_build_profile,
				  ab,
				  rows, cols,
				  use_col,
				  original_col_numbers,
				  &names_of_colomns,
				  v,
				  w,
#if SOURCE_COORDINATES_3D
				  X,
				  Y,
				  Z,
#else
				  t,
#endif
				  num_col,
				  ab.delim))
		{
			return false;
		}
#if 1
		if (1)
		{		
			sprintf(dir_out, "%s\\raz_of_%s", directory, filename);
			int n = 0;
			while (!CreateDirectory(dir_out,NULL))
			{
				sprintf(dir_out, "%s\\raz_of_%s(%d)", directory, filename, n++);
			}
		}

		vector<double> vvv(rows, 0.0);
		
		for(size_t c = 0; c < cols; c++) // ��� ������ ������� - ���� ��� ������� ���������
		{
			for (size_t r = 0; r < rows; r++)
			{
				vvv[r] += v[c][r]*v[c][r];
			}
		}

		vector<vector <double> > rec_signals;
		vector <double> rec_modul;
			
		int type = 0; // ��� ������ ������
		cout << "Enter type of prjamoj zadachi" << endl;
		cout << "0 - simple" << endl;
		cout << "1 - with diagramm of 3 antenns and nonpolarized sources" << endl;
		cin >> type;


		bool granicy_kak_glubina = true;
		cout << "Enter granicy_kak_glubina?  0 - no 1 - yes" << endl;
		cin >> granicy_kak_glubina;

		UseOneOfMyMethods(type, granicy_kak_glubina, 
#if WITH_2D
			true, 
#endif
			cols,AutoBuildProfile::ab,X,Y,Z,vvv,v,names_of_colomns,original_col_numbers,
			rec_signals, rec_modul
			);

#else
		
		bool is_reverse = false;
		int shoulder = 50;// ����� -  ����� ���� - ��� ��� ����� ���� ����
		int step = 5;
		int wlen_base = 20;
		int wlen_auto = 10;

		cout << "Enter is_reverse[0/1]:" << endl;
		cin  >> is_reverse;

		cout << "Enter shoulder[50]:" << endl;
		cin  >> shoulder;

		cout << "Enter step[5]:" << endl;
		cin  >> step;

		cout << "Enter wlen_base[20]:" << endl;
		cin  >> wlen_base;

		cout << "Enter wlen_auto[10]:" << endl;
		cin  >> wlen_auto;


		if (!BuildingProfile(vvvvkp,profile_intervals,
			consol, 
			p_auto_build_profile,
			ab,
			v, w, X, Y,
			&names_of_colomns, original_col_numbers, 
			rows, cols, 
			ab.delim, directory, filename,
			is_reverse, shoulder, step, wlen_auto))
		{
			return false;
		}


		if (!BuildingProfile2(vvvvkp, profile_intervals,
					 consol, 
					 p_auto_build_profile,
					 ab,
					 &names_of_colomns,
					 original_col_numbers, 
					 cols, 
					 ab.delim, 
					 directory,
					 filename,
					 is_reverse,
					 wlen_base
				  ))
		{
			return false;
		}


#endif
		return true;
	}
printf("the end!!!\n");

#if _USE_WINSURF_
	return true;
#else
	return false;
#endif
}
#endif
bool ReadColomnNumbers(
					   auto_build_parametrs& ab,
					   vector<bool>& use_col,
					   int& num_col,
					   int delim)
{
	if (ab.use_num_col)
	{
		vector<vector<cell> > * pcells_num_col = new vector<vector<cell> >;
		vector<string> * pnames_of_colomns_num_col = new vector<string>;
		char* filename_num_col = NULL;
		ReadCellFile(NULL, ab.num_col_filename, filename_num_col, pcells_num_col, pnames_of_colomns_num_col, delim );
		int rows = pcells_num_col->size();
		int _cols = pnames_of_colomns_num_col->size();

		for (size_t c = 0; c < _cols; c++)
			printf("col[%d] = %s\n", c, (*pnames_of_colomns_num_col).operator [](c).c_str());

		printf("rows = %d _cols = %d\n", rows, _cols);
		if (rows > 0)
		{
			_cols = pcells_num_col->operator [](0).size();
			printf("rows = %d _cols = %d\n", rows, _cols);
		}	
		num_col = rows;
		use_col.resize(num_col);

		if (_cols < 2)
		{
			char str[255];
			sprintf(str, "_cols %d < 2", _cols);
			MessageBox(0, str, "Num col", 0);
			return false;
		}

		for(int i = 0; i < num_col; i++)
		{
			use_col[i] = (*pcells_num_col).operator [](i)[1].value != 0;
		}

		delete pcells_num_col;
		delete pnames_of_colomns_num_col;
	}

}

bool ReadProfileFile( 
				  char * sz_path_to_file, char * current_directory, char* filename, 
				  bool consol, 
				  AutoBuildProfile * p_auto_build_profile,
				  auto_build_parametrs& ab,
				  int& rows, int& cols,
				  vector<bool>& use_col,
				  vector<size_t>& original_col_numbers,
				  vector<string> * pnames_of_colomns,
				  vector<vector<double> >& v,
				  vector<vector<double> >& w,
#if SOURCE_COORDINATES_3D
				  vector<double>& X,
				  vector<double>& Y,
				  vector<double>& Z,
#else
				  vector<double>& t,
#endif
				  int num_col,
				  int delim)
{

	pnames_of_colomns->clear();
	original_col_numbers.clear();
	//##############################################################
	//���� ������ �����
	vector<vector<cell> > * pcells = new vector<vector<cell> >;
	
printf("ReadProfileFile sz_path_to_file = %s, current_directory = %s\n", sz_path_to_file, current_directory);

	ReadCellFile(NULL, sz_path_to_file, filename, pcells, pnames_of_colomns, delim );


	//���� ������ �����
	//##############################################################

	rows = pcells->size();
	int _cols = pnames_of_colomns->size();

	for (size_t c = 0; c < _cols; c++)
		printf("col[%d] = %s\n", c, (*pnames_of_colomns).operator [](c).c_str());

	printf("rows = %d _cols = %d\n", rows, _cols);
	if (rows > 0)
	{
		_cols = pcells->operator [](0).size();
		printf("rows = %d _cols = %d\n", rows, _cols);
	}		
		
	int tcols, use_time_col = 0;
	int miss_cols = 0;

	if (ab.use_num_col)
	{
		if (_cols != num_col)
		{
			char str[255];
			sprintf(str, "_cols %d != num_col %d", _cols, num_col);
			MessageBox(0, str, "", 0);
			return false;
		}
		tcols = ab.tcols;
		use_time_col = ab.use_time_colomn;
		for(int i = tcols; i < num_col; i++)
		{
			if (!use_col[i]) miss_cols++;
		}
	}
	else
	{
		tcols = 1;
	}

	cols = _cols - tcols - miss_cols - use_time_col;

printf("cols = %d\n", cols);




#if !SOURCE_COORDINATES_3D
	t.resize(rows);
#endif
	X.resize(rows);
	Y.resize(rows);
	Z.resize(rows, 0.0);

	//����� �������
	//double profile_size = t.back() - (*t.begin());
	//double one_point_size = profile_size / (rows-1);






	if (cols > 0)
	{
		//##############################################################
		//���� ���������� ������� ��������� � ������� ������
		v.resize(cols);
		w.resize(cols);
		original_col_numbers.resize(cols);
		size_t cc = 0;
		for (size_t c = 0; c < _cols; c++)
		{						
			if (c < tcols+use_time_col)
			{
				if (!ab.use_num_col)
				{
#if !SOURCE_COORDINATES_3D
					for (size_t r = 0; r < rows; r++)
					{
						t[r] = (*pcells).operator [](r)[c].value;
					}
#endif
				}
				else
				{								
					if (use_col[c])
					{
#if !SOURCE_COORDINATES_3D
						for (size_t r = 0; r < rows; r++)
						{
							t[r] = (*pcells).operator [](r)[c].value;
						}
#endif
					}
					switch(c)
					{
					case 0:		
						{  
							for (size_t r = 0; r < rows; r++)
							{
								X[r] = (*pcells).operator [](r)[c].value;
							}
						}
						break;
					case 1:
						{
							for (size_t r = 0; r < rows; r++)
							{
								Y[r] = (*pcells).operator [](r)[c].value;
							}
						}
						break;
					case 2:
						{
							for (size_t r = 0; r < rows; r++)
							{
								Z[r] = (*pcells).operator [](r)[c].value;
							}
						}
						break;
#if 0
					case 3:
						{
							for (size_t r = 0; r < rows; r++)
							{
								time[r] = (*pcells).operator [](r)[c].value;
							}
						}
						break;
#endif
					}
				}
			}
			else
			{
				if (!ab.use_num_col)
				{
					original_col_numbers[c-tcols] = c;

					v[c-tcols-use_time_col].resize(rows);
					w[c-tcols-use_time_col].resize(rows);
					for (size_t r = 0; r < rows; r++)
					{
						v[c-tcols-use_time_col][r] = (*pcells).operator [](r)[c].value;
						w[c-tcols-use_time_col][r] = (*pcells).operator [](r)[c].value;
					}
				}
				else
				{
					if (use_col[c])
					{
	printf("cc %d c+1= %d\n", cc, c+1);
						original_col_numbers[cc] = c;
						v[cc].resize(rows);
						w[cc].resize(rows);
						for (size_t r = 0; r < rows; r++)
						{
							v[cc][r] = (*pcells).operator [](r)[c].value;
							w[cc][r] = (*pcells).operator [](r)[c].value;
						}
						cc++;
					}
				}
			}
		}

		pcells->clear();
		delete pcells;
		//���� ���������� ������� ��������� � ������� ������
		//##############################################################
		return true;
	}
	return false;
}

bool BuildingProfile_old(vector<vector<vector<vert_korr_points> > >& vvvvkp,
					 vector<profile_interval> & profile_intervals,
					 bool consol, 
					 AutoBuildProfile * p_auto_build_profile,
					 auto_build_parametrs& ab,
					 vector<vector<double> >& v, 
					 vector<vector<double> >& w, 
					 vector<double>& X, 
					 vector<double>& Y,
					 vector<string> * pnames_of_colomns,
					 vector<size_t>& original_col_numbers, 
					 int rows, int cols, 
					 int delim, 
					 char * current_directory,
					 char * filename,
					 bool is_reverse,
					 int shoulder,// = 50;// ����� -  ����� ���� - ��� ��� ����� ���� ����
					 int step)
{
	double k = ab.k;

	sprintf(dir_out, "%s\\raz_of_%s", current_directory, filename);
	int n = 0;
	while (!CreateDirectory(dir_out,NULL))
	{
		sprintf(dir_out, "%s\\raz_of_%s(%d)", current_directory, filename, n++);
	}

	//**********************************************
	//��������� ���� �������� ������ ������
	char filename_description[4096];
	sprintf(filename_description, "%s\\description_old.txt", dir_out);
	FILE *stream;
	stream = fopen(filename_description,"wt");
	if (stream)
	{
		WriteDescription(stream, AutoBuildProfile::ab);
		fclose(stream);
	}
	//**********************************************
	if (!CheckMyLicense()) return false;
	//##############################################################
	//��� ���� ���������� �������������� �������
	bool vertical_korr_on_base_wnd = true;
	bool vertical_auto_korr = true;
	bool gorizontal_korr = true;
	if (vertical_korr_on_base_wnd)
		// ���� ��������� �������� ����� � ����������� �� ������������ ��������
		// ����� �� ������������������ � ����������� �������������� ������� �� ������������ ��������
		// ����������� �� ����� ������� ���������� ��������� � ������������� ����
	{
		// ����� ����������� �� ����� �������� (-1, +1) ����������� ������� 
		// �� ������� �� ����
		// ��� ������� ��������������� ������������
		int reverse1 = +1, reverse2 = +1;

		profile_interval prof_interval;
		prof_interval.i1 = 0;

		for (size_t j = 0; j < 2; j++)
		{
			if (!j)
			{
				reverse1 = +1, reverse2 = -1;
			}
			else
			{
				reverse1 = +1, reverse2 = +1;
			}

			vvvvkp.resize(cols);
			// ���������� �������������� ������ �� �������� ������ ������� � ������
			for(size_t c1 = 0; c1 < cols; c1++)
			{		
				vvvvkp[c1].resize(cols);
				for(size_t c2 = 0; c2 < cols; c2++)
				{
					// ����� ������� ����� �� ��������� ������� �� ������� ������� 
					// BuildProfile
					//  � ����� �� ������� ���� ������� ������� �������������� ��������� ���� �������, 
					// ����� ������������ ���������� ������� �� ���� ������� ������,
					// � ����� ��� ������� � ������� UseWholeDirectory

					DoGorizontalCorrilation(k, shoulder,step,&vvvvkp[c1][c2],
						v, X, Y, pnames_of_colomns, original_col_numbers, 
						rows, c1, c2, reverse1, reverse2, delim);	

					BuildGrid(0,//short crd_type,
								// 0 - x, 1 - y, 2 - profile_len
						1, 		// short value_type,
								// 1 - korr_k;  // ����������� �������������� ����������
								// 2 - korr_k2; // ����������� ������������ ���������� � �������������� �������� �������
								// 3 - korr_k3; // ����������� ������������ ��������������
						NULL, //pcollection,
						&vvvvkp[c1][c2],
						profile_intervals,
						pnames_of_colomns,
						original_col_numbers,
						5, 5, 200, //double xSize, double ySize, double max_glubina, 
						c1, c2,
						reverse1, reverse2);

				}
			}
		}
		if (vvvvkp.size() > 0)
			if (vvvvkp[0].size() > 0)
				prof_interval.i2 = vvvvkp[0][0].size()-1;

		prof_interval.layer = NULL;					
		SurfDoc * doc = NULL;
		if (p_auto_build_profile)
			doc = (SurfDoc*)p_auto_build_profile->GetDoc();
		if (doc)
		{
			prof_interval.layer = doc->AddNewLayer(filename);
		}

		strcpy(prof_interval.dir, dir_out);
		profile_intervals.push_back(prof_interval);
		prof_interval.i1 = prof_interval.i2+1;
	}
	if (vertical_auto_korr)// ���� ��������� �������� ����� � ����������� �� ������������ ��������
	{
		// ����� ����������� �� ����� �������� (-1, +1) ����������� ������� 
		// �� ������� �� ����
		// ��� ������� ��������������� ������������
		int reverse1 = +1, reverse2 = +1;

		for (size_t j = 0; j < 2; j++)
		{
			if (!j)
			{
				reverse1 = +1, reverse2 = -1;
			}
			else
			{
				reverse1 = +1, reverse2 = +1;
			}
			// ���������� �������������� ������ �� �������� ������ ������� � ������
			for(size_t c1 = 0; c1 < cols; c1++)
			{			
				for(size_t c2 = 0; c2 < cols; c2++)
				{	
					TCHAR lpstrFile[1024];
					FILE * stream_corr_ivan = NULL;
					sprintf(lpstrFile, "%s\\corr_ivan_%s_%s_sym_%d.dat", dir_out,
						(*pnames_of_colomns)[original_col_numbers[c1]].c_str(),
						(*pnames_of_colomns)[original_col_numbers[c2]].c_str(),
						reverse1 * reverse2
						);
					
					char *p;
					while (p=strchr (lpstrFile,'\"'))
					{
						*p = '_';
					}
					printf("try to open file: \n%s\n", lpstrFile);
					stream_corr_ivan = fopen(lpstrFile, "wt");

											
					TCHAR blnFile[1024];
					FILE * bln = NULL;
					sprintf(blnFile, "%s\\corr_ivan_%s_%s_sym_%d.bln", dir_out,
						(*pnames_of_colomns)[original_col_numbers[c1]].c_str(),
						(*pnames_of_colomns)[original_col_numbers[c2]].c_str(),
						reverse1 * reverse2
						);

					while (p=strchr (blnFile,'\"'))
					{
						*p = '_';
					}

					bln = fopen(blnFile, "wt");

					if (stream_corr_ivan && bln) 
					{	
						printf("start of filling file: \n%s\n", lpstrFile);


						//������ �� ������������ ������� ��������� ������������ �����

						double max_z = 10000.0;
						double profile_len = 0.0;
						for (size_t r = 1; r < rows; r++)
						{
							profile_len += sqrt(
								(X[r]-X[r-1])*(X[r]-X[r-1])
								+
								(Y[r]-Y[r-1])*(Y[r]-Y[r-1])
								);                
						}
						double row_step = profile_len/rows;
						double h_step = row_step*ab.k;
						size_t max_delta_rows = max_z/h_step;
						printf("max_delta_rows = %u\n", max_delta_rows);
						int max_shoulder = max_delta_rows/2;


						int shoulder = 90;// ����� -  ����� ���� - ��� ��� ����� ���� ����
						//int step = shoulder+1;
						int step = 5;



						vector<vector<korr_point> > vvkp;
						vvkp.clear();


						// ���������� ����� �������
						//for (int r = max_shoulder; r < rows-max_shoulder; r++)
						//for (int r = 0; r < rows; r++)
						for (int r = 0; r < rows; r+=step)
						{		
							vector<korr_point> vkp;
							vkp.clear();

			printf("r = %u rows = %d\n", r, rows);
							for (int sh = 0; sh < max_shoulder; sh++)
							{	
								int r1 = r - sh, r2 = r + sh;
								if (r1 >= 0 && r2 >= 0 && r1 < rows && r2 < rows)
								{		
									// ��������� ����������� � ������ �� ����
									double m1 = 0.0, m2 = 0.0;
									int n1 = 0, n2 = 0;
									for (int sh = -shoulder; sh <= shoulder; sh++)
									{	
										int i1 = r1 + sh, i2 = r2 + sh;
										if (i1 >= 0 && i1 < rows)
										{
											m1 += v[c1][i1];n1++;
										}								
										if (i2 >= 0 && i2 < rows)
										{
											m2 += v[c2][i2];n2++;
										}
									}
									if (n1) m1 /= n1;
									if (n2) m2 /= n2;
									// ��������� ��������� � ������������������ ���������� � ������ �� ����
									double D1 = 0.0, D2 = 0.0;
									n1=0,n2=0;
									for (int sh = -shoulder; sh <= shoulder; sh++)
									{	
										int i1 = r1 + sh, i2 = r2 + sh;
										if (i1 >= 0 && i1 < rows)
										{
											D1 += (v[c1][i1]-m1)*(v[c1][i1]-m1);
											n1++;
										}								
										if (i2 >= 0 && i2 < rows)
										{
											D2 += (v[c2][i2]-m2)*(v[c2][i2]-m2);
											n2++;
										}
									}
									if (n1) D1 /= n1;
									if (n2) D2 /= n2;
									double sigma1 = sqrt(D1);
									double sigma2 = sqrt(D2);
									// ������������ �������������� �����������
									double K_r1_r2_c1_c2 = 0.0;
									int n = 0;
									for (int sh = -shoulder; sh <= shoulder; sh++)
									{	
										int i1 = r1 + reverse1*sh, i2 = r2 + reverse2*sh;
										if (i1 >= 0 && i2 >= 0 && i1 < rows && i2 < rows)
										{
											K_r1_r2_c1_c2 += (v[c1][i1] - m1) * (v[c2][i2] - m2);
											n++;
										}
									}
									if(n) K_r1_r2_c1_c2 /= n;

									double k_r1_r2_c1_c2 = K_r1_r2_c1_c2 / (sigma1*sigma2);

									// ���������� �������� � ��������� �������
									double x1 = X[r1];
									double x2 = X[r2];
									double y1 = Y[r1];
									double y2 = Y[r2];

									double x = (x1 + x2)/2.0;
									double y = (y1 + y2)/2.0;
									double z = -ab.k*sqrt( 
										(x1 - x2)*(x1 - x2) 
										+
										(y1 - y2)*(y1 - y2) 
										);

									if (stream_corr_ivan) 
										fprintf(stream_corr_ivan, 
										"%7.3f%c%7.3f%c%4.3f"
										"%c%f"
										"\n",
										x, delim, y, delim, z
										, delim, k_r1_r2_c1_c2
										);

									korr_point kp;
									kp.x = x;
									kp.y = y;
									kp.z = z;

									kp.korr_k = k_r1_r2_c1_c2;

									vkp.push_back(kp);
								}
							}
							vvkp.push_back(vkp);
						}
						fclose(stream_corr_ivan);
						printf("file closed:\n%s\n", lpstrFile);



						TCHAR lpstrFile[1024];
						FILE * corr_v3 = NULL;
						sprintf(lpstrFile, "%s\\corr_v3_%s_%s_sym_%d.dat", dir_out,
							(*pnames_of_colomns)[original_col_numbers[c1]].c_str(),
							(*pnames_of_colomns)[original_col_numbers[c2]].c_str(),
							reverse1 * reverse2
							);
						
						char *p;
						while (p=strchr (lpstrFile,'\"'))
						{
							*p = '_';
						}
						printf("try to open file: \n%s\n", lpstrFile);
						corr_v3 = fopen(lpstrFile, "wt");



						//TCHAR lpstrFile[1024];
						FILE * corr_v_3 = NULL;
						sprintf(lpstrFile, "%s\\corr_v_3_%s_%s_sym_%d.dat", dir_out,
							(*pnames_of_colomns)[original_col_numbers[c1]].c_str(),
							(*pnames_of_colomns)[original_col_numbers[c2]].c_str(),
							reverse1 * reverse2
							);
						
						//char *p;
						while (p=strchr (lpstrFile,'\"'))
						{
							*p = '_';
						}
						printf("try to open file: \n%s\n", lpstrFile);
						corr_v_3 = fopen(lpstrFile, "wt");




						// �������� ���������� ����� ���������

						int wlen = 10;//����� ���� ����������
#define AUTO_KORR 1
#if !AUTO_KORR
						for (size_t R = 1; R < vvkp.size(); R++)
						{
							//����� ���� �������� ��������
							size_t len0 = vvkp[R-1].size();
							size_t len1 = vvkp[R].size();

							// ������ �� �������� �������
							vector<korr_point>& vkp_0  = vvkp[R-1];
							vector<korr_point>& vkp_1  = vvkp[R];
#else
						for (size_t R = 0; R < vvkp.size(); R++)
						{
							//����� ���� �������� ��������
							size_t len0 = vvkp[R].size();
							size_t len1 = vvkp[R].size();

							// ������ �� �������� �������
							vector<korr_point>& vkp_0  = vvkp[R];
							vector<korr_point>& vkp_1  = vvkp[R];
#endif

							// �������� ����� ���� ���� ���� 
							// �������� ����������� �������������� ������� 
							// ������� �� ������ ������ ���������� 
							// ��� ������ ��������� ���������� 
							// ����� ��������� ���������

							int len_0 = len0-wlen+1;
							int len_1 = len1-wlen+1;

                            // ���� ����������� �������������� ������� �������
							if (len_0 > 0 && len_1 > 0)
							{
								// �������� ������ ��� �������������� �������
								double **M = AllocDoubleMat(len_0,len_1);

								double min_k = DBL_MAX;
								double max_k = -DBL_MAX;

								int i_0_max, i_1_max, i_0_min, i_1_min;

								//������������ ���������� �������������� ������� 
								// � ���� ������
								for (int i_0 = 0; i_0 < len_0; i_0++)
								{
									for (int i_1 = 0; i_1 < len_1; i_1++)
									{
										// �������� ������ ��������������� ������������											
										//
										// ��������� ����������� � ������ �� ����
										double m_0 = 0.0, m_1 = 0.0;
										//int n_0 = 0, n_1 = 0;
										for (int w = 0; w < wlen; w++)
										{	
											m_0 += vkp_0[w+i_0].korr_k;		
											m_1 += vkp_1[w+i_1].korr_k;		
										}
										m_0 /= wlen;
										m_1 /= wlen;

										// ��������� ��������� � ������������������ ���������� � ������ �� ����
										double D_0 = 0.0, D_1 = 0.0;										
										for (int w = 0; w < wlen; w++)
										{
											D_0 += (vkp_0[w+i_0].korr_k-m_0)*(vkp_0[w+i_0].korr_k-m_0);                                            
											D_1 += (vkp_1[w+i_1].korr_k-m_1)*(vkp_1[w+i_1].korr_k-m_1);
										}
										D_0 /= wlen;
										D_1 /= wlen;

										double sigma_0 = sqrt(D_0);
										double sigma_1 = sqrt(D_1);
										// ������������ �������������� �����������
										double K_0_1 = 0.0;
										for (int w = 0; w < wlen; w++)
										{
											K_0_1 += (vkp_0[w+i_0].korr_k-m_0)*(vkp_1[w+i_1].korr_k-m_1);
										}
										K_0_1 /= wlen;
										double k_0_1 = K_0_1 / (sigma_0*sigma_1);
										M[i_0][i_1] = k_0_1;

										if (k_0_1 > max_k)
										{
											max_k = k_0_1;
											i_0_max = i_0;
											i_1_max = i_1;
										}

										if (k_0_1 < min_k)
										{
											min_k = k_0_1;
											i_0_min = i_0;
											i_1_min = i_1;
										}

									}
								}


								fprintf(bln,"%d,%d, %f\n", 2, 0, max_k);
								fprintf(bln,"%f,%f\n", vkp_0[wlen/2+i_0_max].x, vkp_0[wlen/2+i_0_max].z);
								fprintf(bln,"%f,%f\n", vkp_1[wlen/2+i_1_max].x, vkp_0[wlen/2+i_1_max].z);


								// � ����� ������� ���������� ����� ��� �������� 
								// (� ������ �������������� ������� �����������, 
								// ��� ��� �� �����) ���� � ������ 
								// � ������� ��������� �������� ������� ����

								// �������� ������ ��� �������������� �������
								double **M2 = AllocDoubleMat(len_0,len_0);

								double min_k2 = DBL_MAX;
								double max_k2 = -DBL_MAX;

								for (int i_00 = 0; i_00 < len_0; i_00++)
								{								
									for (int i_01 = 0; i_01 < len_0; i_01++)
									{
										double k = korr_koeff(len_1, M[i_00], M[i_01]);
										M2[i_00][i_01] = k;
										if (k > max_k2)
											max_k2 = k;
										if (k < min_k2)
											min_k2 = k;
									}
								}

								double **M3 = AllocDoubleMat(len_0,len_0);

								double min_k3 = DBL_MAX;
								double max_k3 = -DBL_MAX;

								for (int i_00 = 0; i_00 < len_0; i_00++)
								{								
									for (int i_01 = 0; i_01 < len_0; i_01++)
									{
										double k = korr_koeff(len_1, M2[i_00], M2[i_01]);
										M3[i_00][i_01] = k;
										if (k > max_k3)
											max_k3 = k;
										if (k < min_k3)
											min_k3 = k;
									}
								}

								double **M4 = AllocDoubleMat(len_0,len_0);

								double min_k4 = DBL_MAX;
								double max_k4 = -DBL_MAX;

								for (int i_00 = 0; i_00 < len_0; i_00++)
								{								
									for (int i_01 = 0; i_01 < len_0; i_01++)
									{
										double k = korr_koeff(len_1, M3[i_00], M3[i_01]);
										M4[i_00][i_01] = k;
										if (k > max_k4)
											max_k4 = k;
										if (k < min_k4)
											min_k4 = k;
									}
								}
								// ����� ������ ������ ���������� ���������� �� �������� 
								// ��� ����������� �������� 

								// ������ �������� ������ ��� ������ �������������� ��������

								double * vk3 = new double[len_0];

								// �������� � ���� ������ ������ ������ �������

								for (int i_01 = 0; i_01 < len_0; i_01++)
								{		
									vk3[i_01] = M4[0][i_01];
								}

								if (false)
								{
									// ��������� � ��� ��������� � ����� ������������ ����������

									for (int i_00 = 1; i_00 < len_0; i_00++)
									{
										double k = korr_koeff(len_1, M4[i_00], vk3);								
										for (int i_01 = 0; i_01 < len_0; i_01++)
										{
											vk3[i_01] += k*M4[i_00][i_01];										
										}
									}

									// ������ ��������� �� �������� -1 +1
									double min_k5 = DBL_MAX;
									double max_k5 = -DBL_MAX;
									for (int i_01 = 0; i_01 < len_0; i_01++)
									{		
										double k = vk3[i_01];
										if (k > max_k5)
											max_k5 = k;
										if (k < min_k5)
											min_k5 = k;
									}

									//���� ����������
									for (int i_01 = 0; i_01 < len_0; i_01++)
									{		
										double k = vk3[i_01];
										vk3[i_01] = -1.0 + 2.0 * (k - min_k5) / (max_k5 - min_k5);
									}
								}

								// ������� ��������� � �������

								for (int i_01 = 0; i_01 < len_0; i_01++)
								{
									vkp_0[wlen/2+i_01].korr_k3 = vk3[i_01];
									if (corr_v3) 
										fprintf(corr_v3, 
										"%7.3f%c%7.3f%c%4.3f"
										"%c%f"
										"\n",
										vkp_0[wlen/2+i_01].x, delim, 
										vkp_0[wlen/2+i_01].y, delim, 
										vkp_0[wlen/2+i_01].z, delim, 
										vkp_0[wlen/2+i_01].korr_k3
										);
								}

								//������ ����������� � ����

								for (int i_01 = 1; i_01 < len_0; i_01++)
								{
									if(vkp_0[wlen/2+i_01].korr_k3 * vkp_0[wlen/2+i_01-1].korr_k3 < 0.0)
									{
										if (corr_v_3) 
											fprintf(corr_v_3, 
											"%7.3f%c%7.3f%c%4.3f"
											"%c%f"
											"\n",
											vkp_0[wlen/2+i_01].x, delim, 
											vkp_0[wlen/2+i_01].y, delim, 
											vkp_0[wlen/2+i_01].z, delim, 
											vkp_0[wlen/2+i_01].korr_k3
											);
									}
								}
								if (vk3) delete [] vk3;

								
#if 0 // ����� �� ������ ������������� �����
#if 1
								{
								// 
								Grid grid;
								grid.gridSection.z = M;
								grid.gridSection.nCol = len_1;
								grid.gridSection.nRow = len_0;
								grid.gridSection.xLL = 0.0;
								grid.gridSection.yLL = 0.0;
								grid.gridSection.xSize = 1.0;
								grid.gridSection.ySize = 1.0;
								grid.gridSection.zMax = max_k;
								grid.gridSection.zMin = min_k;

								grid.faultSection.nTraces = 0;
								grid.faultSection.nVertices = 0;
								grid.faultSection.traces = NULL;
								grid.faultSection.vertexes = NULL;


								//
								char file[2048];
								sprintf(file, "%s\\corr_ivan_%s_%s_sym_%d R = %04d.grd", dir_out,
									(*pnames_of_colomns)[original_col_numbers[c1]].c_str(),
									(*pnames_of_colomns)[original_col_numbers[c2]].c_str(),
									reverse1 * reverse2,
									R
									);

								SaveAsSurferGrid7(file, &grid);
								}
#endif
#if 1
								{
								// 
								Grid grid2;
								grid2.gridSection.z = M2;
								grid2.gridSection.nCol = len_0;
								grid2.gridSection.nRow = len_0;
								grid2.gridSection.xLL = 0.0;
								grid2.gridSection.yLL = 0.0;
								grid2.gridSection.xSize = 1.0;
								grid2.gridSection.ySize = 1.0;
								grid2.gridSection.zMax = max_k2;
								grid2.gridSection.zMin = min_k2;

								grid2.faultSection.nTraces = 0;
								grid2.faultSection.nVertices = 0;
								grid2.faultSection.traces = NULL;
								grid2.faultSection.vertexes = NULL;


								//
								char file2[2048];
								sprintf(file2, "%s\\corr_ivan_%s_%s_sym_%d R = %04d 2.grd", dir_out,
									(*pnames_of_colomns)[original_col_numbers[c1]].c_str(),
									(*pnames_of_colomns)[original_col_numbers[c2]].c_str(),
									reverse1 * reverse2,
									R
									);

								SaveAsSurferGrid7(file2, &grid2);
								}
#endif
#if 1
								{
								// 
								Grid grid3;
								grid3.gridSection.z = M3;
								grid3.gridSection.nCol = len_0;
								grid3.gridSection.nRow = len_0;
								grid3.gridSection.xLL = 0.0;
								grid3.gridSection.yLL = 0.0;
								grid3.gridSection.xSize = 1.0;
								grid3.gridSection.ySize = 1.0;
								grid3.gridSection.zMax = max_k3;
								grid3.gridSection.zMin = min_k3;

								grid3.faultSection.nTraces = 0;
								grid3.faultSection.nVertices = 0;
								grid3.faultSection.traces = NULL;
								grid3.faultSection.vertexes = NULL;


								//
								char file3[2048];
								sprintf(file3, "%s\\corr_ivan_%s_%s_sym_%d R = %04d 3.grd", dir_out,
									(*pnames_of_colomns)[original_col_numbers[c1]].c_str(),
									(*pnames_of_colomns)[original_col_numbers[c2]].c_str(),
									reverse1 * reverse2,
									R
									);

								SaveAsSurferGrid7(file3, &grid3);
								}
#endif
#if 1
								{
								// 
								Grid grid4;
								grid4.gridSection.z = M4;
								grid4.gridSection.nCol = len_0;
								grid4.gridSection.nRow = len_0;
								grid4.gridSection.xLL = 0.0;
								grid4.gridSection.yLL = 0.0;
								grid4.gridSection.xSize = 1.0;
								grid4.gridSection.ySize = 1.0;
								grid4.gridSection.zMax = max_k4;
								grid4.gridSection.zMin = min_k4;

								grid4.faultSection.nTraces = 0;
								grid4.faultSection.nVertices = 0;
								grid4.faultSection.traces = NULL;
								grid4.faultSection.vertexes = NULL;


								//
								char file4[2048];
								sprintf(file4, "%s\\corr_ivan_%s_%s_sym_%d R = %04d 4.grd", dir_out,
									(*pnames_of_colomns)[original_col_numbers[c1]].c_str(),
									(*pnames_of_colomns)[original_col_numbers[c2]].c_str(),
									reverse1 * reverse2,
									R
									);

								SaveAsSurferGrid7(file4, &grid4);
								}
#endif
#endif
								// ������� �������������� �������
								if (M) FreeDoubleMat(M);
								if (M2) FreeDoubleMat(M2);
								if (M3) FreeDoubleMat(M3);
								if (M4) FreeDoubleMat(M4);
							}
						}

						if (bln) fclose(bln);
						if (corr_v3) fclose (corr_v3);
						if (corr_v_3) fclose (corr_v_3);

					}
					else
					{
						printf("can not open file: \n%s\n", lpstrFile);
						ErrorPrint("fopen");
					}

					BuildGrid(0,//short crd_type,
								// 0 - x, 1 - y, 2 - profile_len
						3, 		// short value_type,
								// 1 - korr_k;  // ����������� �������������� ����������
								// 2 - korr_k2; // ����������� ������������ ���������� � �������������� �������� �������
								// 3 - korr_k3; // ����������� ������������ ��������������
						NULL, //pcollection,
						&vvvvkp[c1][c2],
						profile_intervals,
						pnames_of_colomns,
						original_col_numbers,
						20, 5, 200, //double xSize, double ySize, double max_glubina, 
						c1, c2,
						reverse1, reverse2);
				}
				////

			}
		}
	}


	if (gorizontal_korr)
		// ���� ��������� �������� ����� � ����������� �� ������������ ��������
		// ����� �� ������������������ � ����������� �������������� ������� �� ������������ ��������
		// ����������� �� ����� ������� ���������� ��������� � ������������� ����
	{
		// ����� ����������� �� ����� �������� (-1, +1) ����������� ������� 
		// �� ������� �� ����
		// ��� ������� ��������������� ������������
		int reverse1 = +1, reverse2 = +1;

		for (size_t j = 0; j < 2; j++)
		{
			if (!j)
			{
				reverse1 = +1, reverse2 = -1;
			}
			else
			{
				reverse1 = +1, reverse2 = +1;
			}
			// ���������� �������������� ������ �� �������� ������ ������� � ������
			for(size_t c1 = 0; c1 < cols; c1++)
			{			
				for(size_t c2 = 0; c2 < cols; c2++)
				{	
					TCHAR lpstrFile[1024];
					FILE * stream_corr_ivan = NULL;
					sprintf(lpstrFile, "%s\\corr_ivan_%s_%s_sym_%d.dat", dir_out,
						(*pnames_of_colomns)[original_col_numbers[c1]].c_str(),
						(*pnames_of_colomns)[original_col_numbers[c2]].c_str(),
						reverse1 * reverse2
						);
					
					char *p;
					while (p=strchr (lpstrFile,'\"'))
					{
						*p = '_';
					}
					printf("try to open file: \n%s\n", lpstrFile);
					stream_corr_ivan = fopen(lpstrFile, "wt");

					if (stream_corr_ivan) 
					{	
						printf("start of filling file: \n%s\n", lpstrFile);


						//������ �� ������������ ������� ��������� ������������ �����

						double max_z = 10000.0;
						double profile_len = 0.0;
						for (size_t r = 1; r < rows; r++)
						{
							profile_len += sqrt(
								(X[r]-X[r-1])*(X[r]-X[r-1])
								+
								(Y[r]-Y[r-1])*(Y[r]-Y[r-1])
								);                
						}
						double row_step = profile_len/rows;
						double h_step = row_step*ab.k;
						size_t max_delta_rows = max_z/h_step;
						printf("max_delta_rows = %u\n", max_delta_rows);
						int max_shoulder = max_delta_rows/2;


						int shoulder = 90;// ����� -  ����� ���� - ��� ��� ����� ���� ����
						//int step = shoulder+1;
						int step = 5;


						// ����� ������� ����� �� ��������� ������� �� ������� ������� 
						// BuildProfile
						//  � ����� �� ������� ���� ������� ������� �������������� ��������� ���� �������, 
						// ����� ������������ ���������� ������� �� ���� ������� ������,
						// � ����� ��� ������� � ������� UseWholeDirectory
						vector<vector<korr_point> > vvkp;
						vvkp.clear();


						// ���������� ����� �������
						//for (int r = max_shoulder; r < rows-max_shoulder; r++)
						//for (int r = 0; r < rows; r++)
						for (int r = 0; r < rows; r+=step)
						{		
							vector<korr_point> vkp;
							vkp.clear();

			printf("r = %u rows = %d\n", r, rows);
							for (int sh = 0; sh < max_shoulder; sh++)
							{	
								int r1 = r - sh, r2 = r + sh;
								if (r1 >= 0 && r2 >= 0 && r1 < rows && r2 < rows)
								{		
									// ��������� ����������� � ������ �� ����
									double m1 = 0.0, m2 = 0.0;
									int n1 = 0, n2 = 0;
									for (int sh = -shoulder; sh <= shoulder; sh++)
									{	
										int i1 = r1 + sh, i2 = r2 + sh;
										if (i1 >= 0 && i1 < rows)
										{
											m1 += v[c1][i1];n1++;
										}								
										if (i2 >= 0 && i2 < rows)
										{
											m2 += v[c2][i2];n2++;
										}
									}
									if (n1) m1 /= n1;
									if (n2) m2 /= n2;
									// ��������� ��������� � ������������������ ���������� � ������ �� ����
									double D1 = 0.0, D2 = 0.0;
									n1=0,n2=0;
									for (int sh = -shoulder; sh <= shoulder; sh++)
									{	
										int i1 = r1 + sh, i2 = r2 + sh;
										if (i1 >= 0 && i1 < rows)
										{
											D1 += (v[c1][i1]-m1)*(v[c1][i1]-m1);
											n1++;
										}								
										if (i2 >= 0 && i2 < rows)
										{
											D2 += (v[c2][i2]-m2)*(v[c2][i2]-m2);
											n2++;
										}
									}
									if (n1) D1 /= n1;
									if (n2) D2 /= n2;
									double sigma1 = sqrt(D1);
									double sigma2 = sqrt(D2);
									// ������������ �������������� �����������
									double K_r1_r2_c1_c2 = 0.0;
									int n = 0;
									for (int sh = -shoulder; sh <= shoulder; sh++)
									{	
										int i1 = r1 + reverse1*sh, i2 = r2 + reverse2*sh;
										if (i1 >= 0 && i2 >= 0 && i1 < rows && i2 < rows)
										{
											K_r1_r2_c1_c2 += (v[c1][i1] - m1) * (v[c2][i2] - m2);
											n++;
										}
									}
									if(n) K_r1_r2_c1_c2 /= n;

									double k_r1_r2_c1_c2 = K_r1_r2_c1_c2 / (sigma1*sigma2);

									// ���������� �������� � ��������� �������
									double x1 = X[r1];
									double x2 = X[r2];
									double y1 = Y[r1];
									double y2 = Y[r2];

									double x = (x1 + x2)/2.0;
									double y = (y1 + y2)/2.0;
									double z = -ab.k*sqrt( 
										(x1 - x2)*(x1 - x2) 
										+
										(y1 - y2)*(y1 - y2) 
										);

									if (stream_corr_ivan) 
										fprintf(stream_corr_ivan, 
										"%7.3f%c%7.3f%c%4.3f"
										"%c%f"
										"\n",
										x, delim, y, delim, z
										, delim, k_r1_r2_c1_c2
										);

									korr_point kp;
									kp.x = x;
									kp.y = y;
									kp.z = z;

									kp.korr_k = k_r1_r2_c1_c2;

									vkp.push_back(kp);
								}
							}
							vvkp.push_back(vkp);
						}
						fclose(stream_corr_ivan);
						printf("file closed:\n%s\n", lpstrFile);

						// �������� ���������� ����� ���������
#if 0 // ���� ����, ������ �� ������� ���� ����� �� ������� �������
						// ��� ��������� �� ����� ������� �� ������ ���� �������
						{
							int wlen = 50;//����� ���� ����������
							int max_size = 0;
							
							for (size_t R = 0; R < vvkp.size(); R++)
							{
								//����� ��������
								size_t len0 = vvkp[R].size();

								// ������ �� �������
								vector<korr_point>& vkp_0  = vvkp[R];

								// �������� ����� ���� ���� ���� 
								// �������� ����������� �������������� ������� 
								// ������� �� ������ ������ ���������� 
								// ��� ������ ��������� ���������� 
								// ����� ���������

								int len_0 = len0-wlen+1;
								// ���� ����������� �������������� ������� �������
								if (len_0 > max_size)
								{
									max_size = len_0;
								}
							}

							// ������� �������, ��� �����
							vector<korr_point>& vkp_1  = vvkp[vvkp.size()/2];
							size_t len1 = vkp_1.size();
							int len_1 = len1-wlen+1;

							// ����� �� ������������� ������� ������� ������� ����������

							for (int i_1 = 0; i_1 < len_1; i_1++)
							//int i_1 = 0;
							//int i_1 = len_1/2;
							{										
								char file_dat[2048];
								sprintf(file_dat, "%s\\corr_ivan_%s_%s sym %d i_1 = %04d.dat", dir_out,
									(*pnames_of_colomns)[original_col_numbers[c1]].c_str(),
									(*pnames_of_colomns)[original_col_numbers[c2]].c_str(),
									reverse1 * reverse2,
									i_1
									);
								char * p;
								while (p=strchr (file_dat,'\"'))
								{
									*p = '_';
								}
								FILE * dat = NULL;
								dat = fopen(file_dat, "wt");
								// �������� ������ ��� �������������� �������
								double **M = AllocDoubleMat(max_size, vvkp.size());
								double BlankValue = BLANK_VALUE;//1.70141e38;// nodes are blanked if greater or equal to this value

								for (size_t R = 0; R < vvkp.size(); R++)
								{
									for (size_t i_0 = 0; i_0 < max_size; i_0++)
									{
										M[i_0][R] = BlankValue;
									}
								}
								double min_k = DBL_MAX;
								double max_k = -DBL_MAX;

								for (size_t R = 0; R < vvkp.size(); R++)
								{
									// ������ �� �������
									vector<korr_point>& vkp_0  = vvkp[R];

									//����� ��������
									size_t len0 = vkp_0.size();	


									// �������� ����� ���� ���� ���� 
									// �������� ����������� �������������� ������� 
									// ������� �� ������ ������ ���������� 
									// ��� ������ ��������� ���������� 
									// ����� ��������� ���������

									int len_0 = len0-wlen+1;
									
									// ���� ����������� �������������� ������� �������
									if (len_0 > 0 && len_1 > 0)
									{
										//������������ ���������� �������������� ������� 
										// � ���� ������
										for (int i_0 = 0; i_0 < len_0; i_0++)
										{
											// �������� ������ ��������������� ������������											
											//
											// ��������� ����������� � ������ �� ����
											double m_0 = 0.0, m_1 = 0.0;
											//int n_0 = 0, n_1 = 0;
											for (int w = 0; w < wlen; w++)
											{	
												m_0 += vkp_0[w+i_0].korr_k;		
												m_1 += vkp_1[w+i_1].korr_k;		
											}
											m_0 /= wlen;
											m_1 /= wlen;

											// ��������� ��������� � ������������������ ���������� � ������ �� ����
											double D_0 = 0.0, D_1 = 0.0;										
											for (int w = 0; w < wlen; w++)
											{
												D_0 += (vkp_0[w+i_0].korr_k-m_0)*(vkp_0[w+i_0].korr_k-m_0);                                            
												D_1 += (vkp_1[w+i_1].korr_k-m_1)*(vkp_1[w+i_1].korr_k-m_1);
											}
											D_0 /= wlen;
											D_1 /= wlen;

											double sigma_0 = sqrt(D_0);
											double sigma_1 = sqrt(D_1);
											// ������������ �������������� �����������
											double K_0_1 = 0.0;
											for (int w = 0; w < wlen; w++)
											{
												K_0_1 += (vkp_0[w+i_0].korr_k-m_0)*(vkp_1[w+i_1].korr_k-m_1);
											}
											K_0_1 /= wlen;
											double k_0_1 = K_0_1 / (sigma_0*sigma_1);
											M[max_size-i_0-1][R] = k_0_1;

											fprintf(dat, "%f,%f,%f,%f\n",
												vkp_0[wlen/2+i_0].x,
												vkp_0[wlen/2+i_0].y,
												vkp_0[wlen/2+i_0].z,

												k_0_1);

											if (k_0_1 > max_k)
											{
												max_k = k_0_1;
											}

											if (k_0_1 < min_k)
											{
												min_k = k_0_1;
											}					

										}
									}
								}



#if 1
								// 
								Grid grid;
								grid.gridSection.z = M;
								grid.gridSection.nCol = vvkp.size();
								grid.gridSection.nRow = max_size;
								grid.gridSection.xLL = 0.0;
								grid.gridSection.yLL = 0.0;
								grid.gridSection.xSize = 1.0;
								grid.gridSection.ySize = 1.0;
								grid.gridSection.zMax = max_k;
								grid.gridSection.zMin = min_k;

								grid.faultSection.nTraces = 0;
								grid.faultSection.nVertices = 0;
								grid.faultSection.traces = NULL;
								grid.faultSection.vertexes = NULL;


								//
								char file[2048];
								sprintf(file, "%s\\corr_ivan_%s_%s_sym_%d i_1 = %04d.grd", dir_out,
									(*pnames_of_colomns)[original_col_numbers[c1]].c_str(),
									(*pnames_of_colomns)[original_col_numbers[c2]].c_str(),
									reverse1 * reverse2,
									i_1
									);
								while (p=strchr (file,'\"'))
								{
									*p = '_';
								}
								SaveAsSurferGrid7(file, &grid);
#endif
								// ������� �������������� �������
								if (M) FreeDoubleMat(M);
								if (dat) fclose(dat);
							}

						}
#endif
					}
					else
					{
						printf("can not open file: \n%s\n", lpstrFile);
						ErrorPrint("fopen");
					}
				}
			}
		}
	}

	if (false)// ���� ��������� �������� ����� ���������������� � ����� ��������
	{
		// ����� ����������� �� ����� �������� (-1, +1) ����������� ������� 
		// �� ������� �� ����
		// ��� ������� ��������������� ������������
		int reverse1 = +1, reverse2 = +1;

		for (size_t j = 0; j < 2; j++)
		{
			if (!j)
			{
				reverse1 = +1, reverse2 = -1;
			}
			else
			{
				reverse1 = +1, reverse2 = +1;
			}

			// ���������� �������������� ������ �� �������� ������ ������� � ������
			for(size_t c1 = 0; c1 < cols; c1++)
			{			
				for(size_t c2 = 0; c2 < cols; c2++)
				{	

					int shoulder = 90;// ����� -  ����� ���� - ��� ��� ����� ���� ����
					//int step = shoulder+1;
					int step = 5;

					//=======================================
					//���������� ������ ��� ���������� ��������� ���� ��������
					bool bScale = true;

					vector<vector<double> > MM;
					vector<double> vX;
					vector<double> vY;
					vector<double> vZ;

					int i_example = 0;

					vector<double> W;
					W.resize(2*(2*shoulder+1));
					//=======================================



					TCHAR lpstrFile[1024];
					FILE * stream_corr_ivan = NULL;
					sprintf(lpstrFile, "%s\\corr_ivan_%s_%s_sym_%d.dat", dir_out,
						(*pnames_of_colomns)[original_col_numbers[c1]].c_str(),
						(*pnames_of_colomns)[original_col_numbers[c2]].c_str(),
						reverse1 * reverse2
						);
					
					char *p;
					while (p=strchr (lpstrFile,'\"'))
					{
						*p = '_';
					}
					printf("try to open file: \n%s\n", lpstrFile);

					if (IDYES == MessageBox(0, lpstrFile, "Apply Kohonen?", MB_YESNO))
					{
						stream_corr_ivan = fopen(lpstrFile, "wt");

						if (stream_corr_ivan) 
						{	
							printf("start of filling file: \n%s\n", lpstrFile);
							for (int r1 = 0 + shoulder; r1 < rows-shoulder; r1+=step)
							{					
								for (int r2 = r1 + shoulder; r2 < rows-shoulder; r2+=step)
								{		
									// ��������� ����������� � ������ �� ����
									double m1 = 0.0, m2 = 0.0;
									int n1 = 0, n2 = 0;
									for (int sh = -shoulder; sh <= shoulder; sh++)
									{	
										int i1 = r1 + sh, i2 = r2 + sh;
										if (i1 >= 0 && i1 < rows)
										{
											m1 += v[c1][i1];n1++;
										}								
										if (i2 >= 0 && i2 < rows)
										{
											m2 += v[c2][i2];n2++;
										}
									}
									if (n1) m1 /= n1;
									if (n2) m2 /= n2;
									// ��������� ��������� � ������������������ ���������� � ������ �� ����
									double D1 = 0.0, D2 = 0.0;
									n1=0,n2=0;
									for (int sh = -shoulder; sh <= shoulder; sh++)
									{	
										int i1 = r1 + sh, i2 = r2 + sh;
										if (i1 >= 0 && i1 < rows)
										{
											D1 += (v[c1][i1]-m1)*(v[c1][i1]-m1);
											n1++;
										}								
										if (i2 >= 0 && i2 < rows)
										{
											D2 += (v[c2][i2]-m2)*(v[c2][i2]-m2);
											n2++;
										}
									}
									if (n1) D1 /= n1;
									if (n2) D2 /= n2;
									double sigma1 = sqrt(D1);
									double sigma2 = sqrt(D2);
									// ������������ �������������� �����������
									double K_r1_r2_c1_c2 = 0.0;
									int n = 0;
									for (int sh = -shoulder; sh <= shoulder; sh++)
									{	
										int i1 = r1 + reverse1*sh, i2 = r2 + reverse2*sh;
										if (i1 >= 0 && i2 >= 0 && i1 < rows && i2 < rows)
										{
											K_r1_r2_c1_c2 += (v[c1][i1] - m1) * (v[c2][i2] - m2);
											n++;
										}
									}
									if(n) K_r1_r2_c1_c2 /= n;

									double k_r1_r2_c1_c2 = K_r1_r2_c1_c2 / (sigma1*sigma2);

									// ���������� �������� � ��������� �������
									double x1 = X[r1];
									double x2 = X[r2];
									double y1 = Y[r1];
									double y2 = Y[r2];

									double x = (x1 + x2)/2.0;
									double y = (y1 + y2)/2.0;
									double z = -ab.k*sqrt( 
										(x1 - x2)*(x1 - x2) 
										+
										(y1 - y2)*(y1 - y2) 
										);

									if (stream_corr_ivan) 
										fprintf(stream_corr_ivan, 
										"%7.3f%c%7.3f%c%4.3f"
										"%c%f"
										"\n",
										x, delim, y, delim, z
										, delim, k_r1_r2_c1_c2
										);

									{


										vX.push_back(x);
										vY.push_back(y);
										vZ.push_back(z);

										int n = 0;

										double mult = 1.0 / sqrt(sigma1*sigma2);

										for (int sh = -shoulder; sh <= shoulder; sh++)
										{	
											int i1 = r1 + reverse1*sh, i2 = r2 + reverse2*sh;
											//if (i1 >= 0 && i2 >= 0 && i1 < rows && i2 < rows)
											{
												//K_r1_r2_c1_c2 += (v[c1][i1] - m1) * (v[c2][i2] - m2);
												W[2*n    ] = mult * (v[c1][i1] - m1);
												W[2*n + 1] = mult * (v[c2][i2] - m2);

												n++;
											}
										}
										if (bScale) Scale(W);
										MM.push_back(W);
										
										i_example++;
									}						


								}
							}


							fclose(stream_corr_ivan);
							printf("file closed:\n%s\n", lpstrFile);
						}
						else
						{
							printf("can not open file: \n%s\n", lpstrFile);
							ErrorPrint("fopen");
						}
						static KohonenDlg * khd = new KohonenDlg(vX, vY, vZ, MM, filename, true);		// ...right after the dialog is closed?

						if (khd != NULL) delete khd;
					}
				}
			}
		}
	}
	if (false)// ���� ��������� �������� �����
	{
		// ����� ����������� �� ����� �������� (-1, +1) ����������� ������� 
		// �� ������� �� ����
		// ��� ������� ��������������� ������������
		int reverse1 = +1, reverse2 = +1;

		for (size_t j = 0; j < 2; j++)
		{
			if (!j)
			{
				reverse1 = +1, reverse2 = -1;
			}
			else
			{
				reverse1 = +1, reverse2 = +1;
			}
			// ���������� �������������� ������ �� �������� ������ ������� � ������
			for(size_t c1 = 0; c1 < cols; c1++)
			{			
				for(size_t c2 = 0; c2 < cols; c2++)
				{	
					TCHAR lpstrFile[1024];
					FILE * stream_corr_ivan = NULL;
					sprintf(lpstrFile, "%s\\corr_ivan_%s_%s_sym_%d.dat", dir_out,
						(*pnames_of_colomns)[original_col_numbers[c1]].c_str(),
						(*pnames_of_colomns)[original_col_numbers[c2]].c_str(),
						reverse1 * reverse2
						);
					
					char *p;
					while (p=strchr (lpstrFile,'\"'))
					{
						*p = '_';
					}
					printf("try to open file: \n%s\n", lpstrFile);
					stream_corr_ivan = fopen(lpstrFile, "wt");

					if (stream_corr_ivan) 
					{	
						printf("start of filling file: \n%s\n", lpstrFile);

						int shoulder = 90;// ����� -  ����� ���� - ��� ��� ����� ���� ����
						//int step = shoulder+1;
						int step = 5;
						for (int r1 = 0 + shoulder; r1 < rows-shoulder; r1+=step)
						{					
							for (int r2 = r1 + shoulder; r2 < rows-shoulder; r2+=step)
							{		
								// ��������� ����������� � ������ �� ����
								double m1 = 0.0, m2 = 0.0;
								int n1 = 0, n2 = 0;
								for (int sh = -shoulder; sh <= shoulder; sh++)
								{	
									int i1 = r1 + sh, i2 = r2 + sh;
									if (i1 >= 0 && i1 < rows)
									{
										m1 += v[c1][i1];n1++;
									}								
									if (i2 >= 0 && i2 < rows)
									{
										m2 += v[c2][i2];n2++;
									}
								}
								if (n1) m1 /= n1;
								if (n2) m2 /= n2;
								// ��������� ��������� � ������������������ ���������� � ������ �� ����
								double D1 = 0.0, D2 = 0.0;
								n1=0,n2=0;
								for (int sh = -shoulder; sh <= shoulder; sh++)
								{	
									int i1 = r1 + sh, i2 = r2 + sh;
									if (i1 >= 0 && i1 < rows)
									{
										D1 += (v[c1][i1]-m1)*(v[c1][i1]-m1);
										n1++;
									}								
									if (i2 >= 0 && i2 < rows)
									{
										D2 += (v[c2][i2]-m2)*(v[c2][i2]-m2);
										n2++;
									}
								}
								if (n1) D1 /= n1;
								if (n2) D2 /= n2;
								double sigma1 = sqrt(D1);
								double sigma2 = sqrt(D2);
								// ������������ �������������� �����������
								double K_r1_r2_c1_c2 = 0.0;
								int n = 0;
								for (int sh = -shoulder; sh <= shoulder; sh++)
								{	
									int i1 = r1 + reverse1*sh, i2 = r2 + reverse2*sh;
									if (i1 >= 0 && i2 >= 0 && i1 < rows && i2 < rows)
									{
										K_r1_r2_c1_c2 += (v[c1][i1] - m1) * (v[c2][i2] - m2);
										n++;
									}
								}
								if(n) K_r1_r2_c1_c2 /= n;

								double k_r1_r2_c1_c2 = K_r1_r2_c1_c2 / (sigma1*sigma2);

								// ���������� �������� � ��������� �������
								double x1 = X[r1];
								double x2 = X[r2];
								double y1 = Y[r1];
								double y2 = Y[r2];

								double x = (x1 + x2)/2.0;
								double y = (y1 + y2)/2.0;
								double z = -ab.k*sqrt( 
									(x1 - x2)*(x1 - x2) 
									+
									(y1 - y2)*(y1 - y2) 
									);

								if (stream_corr_ivan) 
									fprintf(stream_corr_ivan, 
									"%7.3f%c%7.3f%c%4.3f"
									"%c%f"
									"\n",
									x, delim, y, delim, z
									, delim, k_r1_r2_c1_c2
									);


							}
						}


						fclose(stream_corr_ivan);
						printf("file closed:\n%s\n", lpstrFile);
					}
					else
					{
						printf("can not open file: \n%s\n", lpstrFile);
						ErrorPrint("fopen");
					}
				}
			}
		}
	}

	if (false)
	{
		// ��������� ����� ����� ���� ������ �������������� ������� � ������ �������
		// ������ ��������, ���� ��������� ��� �� � �������-�����������,
		// � ��������������� � ������� ��� � ����������
		TCHAR lpstrFile[1024];
		FILE * stream_corr_c = NULL;
		sprintf(lpstrFile, "%s\\corr_c.dat", dir_out);
		stream_corr_c = fopen(lpstrFile, "wt");
			
		double max_z = 10000.0;
		double profile_len = 0.0;
		for (size_t r = 1; r < rows; r++)
		{
			profile_len += sqrt(
				(X[r]-X[r-1])*(X[r]-X[r-1])
				+
				(Y[r]-Y[r-1])*(Y[r]-Y[r-1])
				);                
		}
		double row_step = profile_len/rows;
		double h_step = row_step*ab.k;
		size_t max_delta_rows = max_z/h_step;
		printf("max_delta_rows = %u\n", max_delta_rows);
		int shoulder = max_delta_rows/2;
		// ���������� ����������� ������ �������
		vector<double> mc;
		mc.resize(cols);
		for (size_t c = 0; c < cols; c++)
		{
			mc[c] = 0.0;
			for(size_t r = 0; r < rows; r++) mc[c] += v[c][r];
			mc[c] /= rows;
		}
		// ��������� ����� ����� ���� ������ �������������� ������� � ������ �������
		// ������ ��������, ���� ��������� ��� �� � �������-�����������,
		// � ��������������� � ������� ��� � ����������
		for (int r = shoulder; r < rows-shoulder; r++)
		{			
printf("r = %u rows = %d\n", r, rows);
			for(size_t c = 0; c < cols; c++)
			{
				vector<double> v_K_r1_r2_c;
				v_K_r1_r2_c.resize(shoulder);	
				
				double K_r1_r2_c = 0.0;
				double D1 = 0.0, D2 = 0.0;
				for (int sh = 0; sh < shoulder; sh++)
				{	
					int r1 = r - sh, r2 = r + sh;
					if (r1 >= 0 && r2 >= 0 && r1 < rows && r2 < rows)
					{
						D1 += (v[c][r1] - mc[c]) * (v[c][r1] - mc[c]);
						D2 += (v[c][r2] - mc[c]) * (v[c][r2] - mc[c]);
						K_r1_r2_c += (v[c][r1] - mc[c]) * (v[c][r2] - mc[c]);

						// ����������� ����������
						v_K_r1_r2_c[sh] = K_r1_r2_c/(sh+1);
						// ����������� ����������
						/*v_K_r1_r2_c[sh] = 
							(K_r1_r2_c/(sh+1))
							/
							( sqrt(D1/(sh+1)) * sqrt(D2/(sh+1)) );
							//*/
					}
				}
				int start_i = 1;
				if (shoulder > start_i+1)
				{
					double max_K_r1_r2_c = v_K_r1_r2_c[start_i];
					int sh_max = start_i;
					for (int sh = start_i+1; sh < shoulder; sh++)
					{
						if (max_K_r1_r2_c < v_K_r1_r2_c[sh])
						{
							max_K_r1_r2_c = v_K_r1_r2_c[sh];
							sh_max = sh;
						}
					}
					int r1 = r - sh_max, r2 = r + sh_max;
					if (r1 >= 0 && r2 >= 0 && r1 < rows && r2 < rows)
					{
						double x1 = X[r1];
						double x2 = X[r2];
						double y1 = Y[r1];
						double y2 = Y[r2];

						double x = (x1 + x2)/2.0;
						double y = (y1 + y2)/2.0;
						double z = -ab.k*sqrt( 
							(x1 - x2)*(x1 - x2) 
							+
							(y1 - y2)*(y1 - y2) 
							);

						if (stream_corr_c && max_K_r1_r2_c > 0.0) 
							fprintf(stream_corr_c, 
							"%7.3f%c%7.3f%c%4.3f"
							"%c%f"
							"\n",
							x, delim, y, delim, z
							, delim, max_K_r1_r2_c
							);
					}
				}
			}
		}
		if (stream_corr_c) fclose(stream_corr_c);

	}
	if (false)		
	{
		TCHAR lpstrFile[1024];	

		FILE * stream_correlation = NULL;
		sprintf(lpstrFile, "%s\\correlation.dat", dir_out);
//			if (ab.use_correlation_algorithm) 
			stream_correlation = fopen(lpstrFile, "wt");

		FILE * corr_loc_max = NULL;
		sprintf(lpstrFile, "%s\\corr_loc_max.dat", dir_out);
//			if (ab.use_correlation_algorithm) 
			corr_loc_max = fopen(lpstrFile, "wt");

		FILE * corr_loc_min = NULL;
		sprintf(lpstrFile, "%s\\corr_loc_min.dat", dir_out);
//			if (ab.use_correlation_algorithm) 
			corr_loc_min = fopen(lpstrFile, "wt");

		FILE * sum_corr_loc_max = NULL;
		sprintf(lpstrFile, "%s\\sum_corr_loc_max.dat", dir_out);
//			if (ab.use_correlation_algorithm) 
			sum_corr_loc_max = fopen(lpstrFile, "wt");

		FILE * sum_corr_loc_min = NULL;
		sprintf(lpstrFile, "%s\\sum_corr_loc_min.dat", dir_out);
//			if (ab.use_correlation_algorithm) 
			sum_corr_loc_min = fopen(lpstrFile, "wt");

		size_t files = 20;
		double k_step = 0.01;

		FILE ** corrs = new FILE*[files];

		for (size_t f = 0; f < files; f++)
		{
			sprintf(lpstrFile, "%s\\correlation_%.02f-%.02f.dat", dir_out, 1.0-k_step*(f+1), 1.0-k_step*f);
			corrs[f] = fopen(lpstrFile,"wt");
		}

		// �� ����� ������������� ������ ������� ��� ���������� ��������� �������
		// ��� ���� ���� ����� ������������ ������� �� ������� �������
		bool to_nornalize_on_cols = true;
		double max_z = 10000.0;
		double profile_len = 0.0;
		for (size_t r = 1; r < rows; r++)
		{
			profile_len += sqrt(
				(X[r]-X[r-1])*(X[r]-X[r-1])
				+
				(Y[r]-Y[r-1])*(Y[r]-Y[r-1])
				);
            
		}
		double row_step = profile_len/rows;
		double h_step = row_step*ab.k;
		size_t max_delta_rows = max_z/h_step;
		printf("max_delta_rows = %u\n", max_delta_rows);

		// ������� ���������� ���������� �� ��������
		if (to_nornalize_on_cols)
		{
			for(size_t c = 0; c < cols; c++)
				Center_And_Scale(w[c]);
		}

		// �� ����� ��������� ����������� ����� ��������� �������
		vector<double> m;
		m.resize(rows);
		for (size_t r = 0; r < rows; r++)
		{
			m[r] = 0.0;
			for(size_t c = 0; c < cols; c++) m[r] += w[c][r];
			m[r] /= cols;
		}			
		
		// ����� �� ����� ��������� ��������� ����� ��������� �������
		vector<double> D;
		vector<double> sigma;
		D.resize(rows);
		sigma.resize(rows);
		for (size_t r = 0; r < rows; r++)
		{
			D[r] = 0.0;
			for(size_t c = 0; c < cols; c++) 
				D[r] += (w[c][r] - m[r]) * (w[c][r] - m[r]);
			D[r] /= cols;
			sigma[r] = sqrt(D[r]);
		}

		// ����� �� ������ ����� �������������� (������������������) ������� 
		// ������� ������������� ������� ����������� ����� ��������� (��������)
		// ��������� �������, ������������ � ��������� t (������ ����� �������)
/*#if 0
		// �� ����� ��������� �������������� ������� �������� rows x rows
		vector<vector<double> > K;
		//  ������������� �������������� �������
		vector<vector<double> > nk;
		K.resize(rows);
		nk.resize(rows);
		for (size_t r1 = 0; r1 < rows; r1++)
		{
printf("r1 = %u rows = %d\n", r1, rows);
			K[r1].resize(rows);
			nk[r1].resize(rows);
			for (size_t r2 = r1+1; r2 < rows && r2 < r1 + max_delta_rows; r2++)
			{
				//K[r1][r2] = M[ (X(r1)-m[r1)) * (X(r1)-m[r1)) ];
				K[r1][r2] = 0.0;
				for(size_t c = 0; c < cols; c++) 
					K[r1][r2] += (w[c][r1] - m[r1]) * (w[c][r2] - m[r2]);

				K[r1][r2] /= cols;

				nk[r1][r2] = K[r1][r2] / (sigma[r1]*sigma[r2]);
			}
		}
printf("K 5\n");

		for (size_t r1 = 0; r1 < rows; r1++)
		{
printf("r1 = %u rows = %d\n", r1, rows);
			for (size_t r2 = r1+1; r2 < rows && r2 < r1 + max_delta_rows; r2++)
			{
				double x1 = X[r1];
				double x2 = X[r2];
				double y1 = Y[r1];
				double y2 = Y[r2];

				double x = (x1 + x2)/2.0;
				double y = (y1 + y2)/2.0;
				double z = -ab.k*sqrt( 
					(x1 - x2)*(x1 - x2) 
					+
					(y1 - y2)*(y1 - y2) 
					);

				if (stream_correlation) 
					fprintf(stream_correlation, 
					"%7.3f%c%7.3f%c%4.3f"
					"%c%f"
					"%c%f"
					"\n",
					x, delim, y, delim, z
					, delim, K[r1][r2]
					, delim, nk[r1][r2]
					);



			}
		}
printf("K 6\n");
#else*/
//#if 0
//			for (size_t r1 = 0; r1 < rows; r1++)
//			{
//printf("r1 = %u rows = %d\n", r1, rows);
//				for (size_t r2 = r1+1; r2 < rows && r2 < r1 + max_delta_rows; r2++)
//				{
//#else
		int shoulder = max_delta_rows/2;
		for (int r = shoulder; r < rows-shoulder; r+=30)
		{
printf("r = %u rows = %d\n", r, rows);
			double sum_of_k_r1_r2 = 0.0;

			vector<double> v_sum_of_k_r1_r2;
			v_sum_of_k_r1_r2.resize(shoulder);

			vector<double> v_k_r1_r2;
			v_k_r1_r2.resize(shoulder);

			vector<double> v_x;
			v_x.resize(shoulder);

			vector<double> v_y;
			v_y.resize(shoulder);

			vector<double> v_z;
			v_z.resize(shoulder);

			for (int sh = 0; sh < shoulder; sh++)
			{
				int r1 = r - sh, r2 = r+sh;
//#endif
				if (r1 >= 0 && r2 >= 0 && r1 < rows && r2 < rows)
				{
					//K[r1][r2] = M[ (X(r1)-m[r1)) * (X(r1)-m[r1)) ];
					double K_r1_r2 = 0.0;
					for(size_t c = 0; c < cols; c++) 
						K_r1_r2 += (w[c][r1] - m[r1]) * (w[c][r2] - m[r2]);

					K_r1_r2 /= cols;

					double k_r1_r2 = K_r1_r2 / (sigma[r1]*sigma[r2]);


					double x1 = X[r1];
					double x2 = X[r2];
					double y1 = Y[r1];
					double y2 = Y[r2];

					double x = (x1 + x2)/2.0;
					double y = (y1 + y2)/2.0;
					double z = -ab.k*sqrt( 
						(x1 - x2)*(x1 - x2) 
						+
						(y1 - y2)*(y1 - y2) 
						);

					sum_of_k_r1_r2 += k_r1_r2;

					v_sum_of_k_r1_r2[sh] = sum_of_k_r1_r2/(sh+1);
					v_k_r1_r2[sh] = k_r1_r2;
					v_x[sh] = x;
					v_y[sh] = y;
					v_z[sh] = z;

					if (stream_correlation) 
						fprintf(stream_correlation, 
						"%7.3f%c%7.3f%c%4.3f"
						"%c%f"
						"%c%f"
						"%c%f"
						"%c%f"
						"\n",
						x, delim, y, delim, z
						, delim, K_r1_r2
						, delim, k_r1_r2
						, delim, sum_of_k_r1_r2
						, delim, v_sum_of_k_r1_r2[sh]
						);


					if (corrs)	
					{
						for (size_t f = 0; f < files; f++)
						{
							if (k_r1_r2 < 1.0-k_step*f && k_r1_r2 > 1.0-k_step*(f+1))
							{
								if (corrs[f]) 
									fprintf(corrs[f], 
									"%7.3f%c%7.3f%c%4.3f"
									"%c%f"
									"%c%f"
									"%c%f"
									"%c%f"
									"\n",
									x, delim, y, delim, z
									, delim, K_r1_r2
									, delim, k_r1_r2
									, delim, sum_of_k_r1_r2
									, delim, v_sum_of_k_r1_r2[sh]
									);
							}
						}
					}
				}
			}
			vector<size_t> vi_lock_min;
			vector<size_t> vi_lock_max;
			GetLocalExtremums(v_k_r1_r2, &vi_lock_min, &vi_lock_max);
			for (size_t i = 0; i < vi_lock_max.size(); i++)
			{
				if (corr_loc_max) 
					fprintf(corr_loc_max, 
					"%7.3f%c%7.3f%c%4.3f"
					"%c%f"
					"\n",
					v_x[vi_lock_max[i]], 
					delim, 
					v_y[vi_lock_max[i]], 
					delim, 
					v_z[vi_lock_max[i]]
					, delim, v_k_r1_r2[vi_lock_max[i]]
					);
			}
			for (size_t i = 0; i < vi_lock_min.size(); i++)
			{
				if (sum_corr_loc_min) 
					fprintf(sum_corr_loc_min, 
					"%7.3f%c%7.3f%c%4.3f"
					"%c%f"
					"\n",
					v_x[vi_lock_min[i]], 
					delim, 
					v_y[vi_lock_min[i]], 
					delim, 
					v_z[vi_lock_min[i]]
					, delim, v_k_r1_r2[vi_lock_min[i]]
					);
			}
			GetLocalExtremums(v_sum_of_k_r1_r2, &vi_lock_min, &vi_lock_max);
			for (size_t i = 0; i < vi_lock_max.size(); i++)
			{
				if (corr_loc_max) 
					fprintf(corr_loc_max, 
					"%7.3f%c%7.3f%c%4.3f"
					"%c%f"
					"\n",
					v_x[vi_lock_max[i]], 
					delim, 
					v_y[vi_lock_max[i]], 
					delim, 
					v_z[vi_lock_max[i]]
					, delim, v_sum_of_k_r1_r2[vi_lock_max[i]]
					);
			}
			for (size_t i = 0; i < vi_lock_min.size(); i++)
			{
				if (sum_corr_loc_min) 
					fprintf(sum_corr_loc_min, 
					"%7.3f%c%7.3f%c%4.3f"
					"%c%f"
					"\n",
					v_x[vi_lock_min[i]], 
					delim, 
					v_y[vi_lock_min[i]], 
					delim, 
					v_z[vi_lock_min[i]]
					, delim, v_sum_of_k_r1_r2[vi_lock_min[i]]
					);
			}
		}


//#endif


		if (stream_correlation) fclose(stream_correlation);
		if (corrs)
		{
			for (size_t f = 0; f < files; f++)
			{
				fclose(corrs[f]);
			}
		}
		if (corr_loc_max) fclose (corr_loc_max);
		if (corr_loc_min) fclose (corr_loc_min);
		if (sum_corr_loc_max) fclose (sum_corr_loc_max);
		if (sum_corr_loc_min) fclose (sum_corr_loc_min);


		if (false)// ������������� ����� �������� �������, ���������� � ������� ���� �����
		{
			bool bScale = true;

			vector<vector<double> > MM;
			vector<double> vX;
			vector<double> vY;
			vector<double> vZ;

			int i_example = 0;

			vector<double> v;
			v.resize(2*cols);

			for (int r = shoulder; r < rows-shoulder; r+=30)
			{
printf("r = %u rows = %d\n", r, rows);
				for (int sh = 0; sh < shoulder; sh++)
				{
					int r1 = r - sh, r2 = r+sh;
					if (r1 >= 0 && r2 >= 0 && r1 < rows && r2 < rows)
					{
						double K_r1_r2 = 0.0;
						for(size_t c = 0; c < cols; c++) 
							K_r1_r2 += (w[c][r1] - m[r1]) * (w[c][r2] - m[r2]);

						K_r1_r2 /= cols;

						double k_r1_r2 = K_r1_r2 / (sigma[r1]*sigma[r2]);	

						//if (k_r1_r2 > 0.8)
						{
							double x1 = X[r1];
							double x2 = X[r2];
							double y1 = Y[r1];
							double y2 = Y[r2];

							double x = (x1 + x2)/2.0;
							double y = (y1 + y2)/2.0;
							double z = -ab.k*sqrt( 
								(x1 - x2)*(x1 - x2) 
								+
								(y1 - y2)*(y1 - y2) 
								);	

							vX.push_back(x);
							vY.push_back(y);
							vZ.push_back(z);

							for(size_t c = 0; c < cols; c++)
							{
								v[2*c    ] = (w[c][r1] - m[r1]);
								v[2*c + 1] = (w[c][r2] - m[r2]);

							}
							if (bScale) Scale(v);
							MM.push_back(v);
							
							i_example++;
						}						
					}
				}
			}

			static KohonenDlg * khd = new KohonenDlg(vX, vY, vZ, MM, filename, true);		// ...right after the dialog is closed?

			if (khd != NULL) delete khd;

		}
	}
	//����� ����� ���������� �������������� �������
	//##############################################################
	if (false)
	{

#if 1
		size_t start_window_len		= rows/2;
		size_t end_window_len		= 40;
		//size_t end_window_len		= 100/one_point_size;
		//size_t step_vindow_len		= 10/one_point_size;
#else
		size_t start_window_len		= 400;
		size_t end_window_len		= 40;
		size_t step_vindow_len		= 20;

		//size_t start_window_len	= 2000;
		//size_t end_window_len		= 200;
		//size_t step_vindow_len	= 100;
#endif
		if (!CheckMyLicense())
		{
			start_window_len = rows+rand();
			//printf("start_window_len = %u\n", start_window_len);
			//return;
		}

		if (rows <= max(start_window_len, end_window_len))
		{
			char str[1024];
			sprintf(str, "Error rows (%u) <= max_window_len (%u)", 
				rows, max(start_window_len, end_window_len));
			MessageBox(0, str, "Error",0);
			return false;
		}
		//� ���� ����� ��������� ����� �����
		TCHAR lpstrFile[1024];		
		//##############################################################
		//FILE * stream_common_razez = NULL;
		//sprintf(lpstrFile, "%s\\raz_com_%d_%d.dat", dir_out, start_window_len, step_vindow_len, end_window_len, use_repeat_points);
		//stream_common_razez = fopen(lpstrFile, "wt");

		//============================================================================
		//============================================================================
		//FILE * stream_common_negative_dima = NULL;
		//sprintf(lpstrFile, "%s\\negative_dima_%d_%d_%d %d.dat", dir_out, start_window_len, step_vindow_len, end_window_len, use_repeat_points);
		//stream_common_negative_dima = fopen(lpstrFile, "wt");

		//FILE * stream_common_positive_dima = NULL;
		//sprintf(lpstrFile, "%s\\positive_dima_%d_%d_%d %d.dat", dir_out, start_window_len, step_vindow_len, end_window_len, use_repeat_points);
		//stream_common_positive_dima = fopen(lpstrFile, "wt");

		FILE * stream_common_razez_positive_dima = NULL;
		sprintf(lpstrFile, "%s\\razez_positive_dima_%d_%d %d.dat", dir_out, start_window_len, end_window_len, ab.use_repeat_points);
		if (ab.use_window_cycles_algorithm_dima) stream_common_razez_positive_dima = fopen(lpstrFile, "wt");

		FILE * stream_common_razez_negative_dima = NULL;
		sprintf(lpstrFile, "%s\\razez_negative_dima_%d_%d %d.dat", dir_out, start_window_len, end_window_len, ab.use_repeat_points);
		if (ab.use_window_cycles_algorithm_dima) stream_common_razez_negative_dima = fopen(lpstrFile, "wt");

		//============================================================================
		//============================================================================

		//FILE * stream_common_negative = NULL;
		//sprintf(lpstrFile, "%s\\negative_%d_%d_%d %d.dat", dir_out, start_window_len, step_vindow_len, end_window_len, use_repeat_points);
		//stream_common_negative = fopen(lpstrFile, "wt");

		//FILE * stream_common_positive = NULL;
		//sprintf(lpstrFile, "%s\\positive_%d_%d_%d %d.dat", dir_out, start_window_len, step_vindow_len, end_window_len, use_repeat_points);
		//stream_common_positive = fopen(lpstrFile, "wt");

		FILE * stream_common_razez_positive = NULL;
		sprintf(lpstrFile, "%s\\razez_positive_%d_%d %d.dat", dir_out, start_window_len, end_window_len, ab.use_repeat_points);
		if (ab.use_window_cycles_algorithm_1) 
			stream_common_razez_positive = fopen(lpstrFile, "wt");

		FILE * stream_common_razez_negative = NULL;
		sprintf(lpstrFile, "%s\\razez_negative_%d_%d %d.dat", dir_out, start_window_len, end_window_len, ab.use_repeat_points);
		if (ab.use_window_cycles_algorithm_1) 
			stream_common_razez_negative = fopen(lpstrFile, "wt");
		//============================================================================
		//##############################################################
		//##############################################################
		//============================================================================
		FILE * stream_common_razez_local_max_less = NULL;
		sprintf(lpstrFile, "%s\\razez_positive_local_max_less_%0.1f.dat", dir_out, ab.quantil_naklony);
		if (ab.use_locals && ab.use_max) 
			stream_common_razez_local_max_less = fopen(lpstrFile, "wt");

		FILE * stream_common_razez_local_min_less = NULL;
		sprintf(lpstrFile, "%s\\razez_negative_local_min_less_%0.1f.dat", dir_out, ab.quantil_naklony);
		if (ab.use_locals && ab.use_min) 
			stream_common_razez_local_min_less = fopen(lpstrFile, "wt");

		FILE * stream_common_razez_local_min_max_less = NULL;
		sprintf(lpstrFile, "%s\\razez_positive_local_min_max_less_%0.1f.dat", dir_out, ab.quantil_naklony);
		if (ab.use_locals && ab.use_min_max) 
			stream_common_razez_local_min_max_less = fopen(lpstrFile, "wt");
		//============================================================================
		//============================================================================
		FILE * stream_common_razez_local_max_more = NULL;
		sprintf(lpstrFile, "%s\\razez_positive_local_max_more_%0.1f.dat", dir_out, ab.quantil_naklony);
		if (ab.use_locals && ab.use_max) 
			stream_common_razez_local_max_more = fopen(lpstrFile, "wt");

		FILE * stream_common_razez_local_min_more = NULL;
		sprintf(lpstrFile, "%s\\razez_negative_local_min_more_%0.1f.dat", dir_out, ab.quantil_naklony);
		if (ab.use_locals && ab.use_min) 
			stream_common_razez_local_min_more = fopen(lpstrFile, "wt");

		FILE * stream_common_razez_local_min_max_more = NULL;
		sprintf(lpstrFile, "%s\\razez_positive_local_min_max_more_%0.1f.dat", dir_out, ab.quantil_naklony);
		if (ab.use_locals && ab.use_min_max) 
			stream_common_razez_local_min_max_more = fopen(lpstrFile, "wt");
		//============================================================================
		//##############################################################
		//##############################################################
		//============================================================================
		//FILE * stream_common_razez_positive_dima_min = NULL;
		//sprintf(lpstrFile, "%s\\razez_positive_dima_min.dat", dir_out);
		//stream_common_razez_positive_dima_min = fopen(lpstrFile, "wt");

		FILE * stream_common_razez_negative_dima_min = NULL;
		sprintf(lpstrFile, "%s\\razez_negative_dima_min.dat", dir_out);
		if (ab.use_window_cycles_algorithm_dima_after_locals && ab.use_min_2) 
			stream_common_razez_negative_dima_min = fopen(lpstrFile, "wt");
		//============================================================================
		//============================================================================
		/*FILE * stream_common_razez_positive_min = NULL;
		sprintf(lpstrFile, "%s\\razez_positive_min.dat", dir_out);
		stream_common_razez_positive_min = fopen(lpstrFile, "wt");*/

		FILE * stream_common_razez_negative_min = NULL;
		sprintf(lpstrFile, "%s\\razez_negative_min.dat", dir_out);
		if (ab.use_window_cycles_algorithm_1_after_locals && ab.use_min_2) 
			stream_common_razez_negative_min = fopen(lpstrFile, "wt");
		
		//============================================================================
		//##############################################################
		//##############################################################
		//============================================================================
		FILE * stream_common_razez_positive_dima_max = NULL;
		sprintf(lpstrFile, "%s\\razez_positive_dima_max.dat", dir_out);
		if (ab.use_window_cycles_algorithm_dima_after_locals && ab.use_max_2) 
			stream_common_razez_positive_dima_max = fopen(lpstrFile, "wt");

		/*FILE * stream_common_razez_negative_dima_max = NULL;
		sprintf(lpstrFile, "%s\\razez_negative_dima_max.dat", dir_out);
		stream_common_razez_negative_dima_max = fopen(lpstrFile, "wt");*/
		//============================================================================
		//============================================================================
		FILE * stream_common_razez_positive_max = NULL;
		sprintf(lpstrFile, "%s\\razez_positive_max.dat", dir_out);
		if (ab.use_window_cycles_algorithm_1_after_locals && ab.use_max_2) 
			stream_common_razez_positive_max = fopen(lpstrFile, "wt");

		/*FILE * stream_common_razez_negative_max = NULL;
		sprintf(lpstrFile, "%s\\razez_negative_max.dat", dir_out);
		stream_common_razez_negative_max = fopen(lpstrFile, "wt");*/
		//============================================================================
		//##############################################################
		//##############################################################
		//============================================================================
		FILE * stream_common_razez_positive_dima_min_max = NULL;
		sprintf(lpstrFile, "%s\\razez_positive_dima_min_max.dat", dir_out);
		if (ab.use_window_cycles_algorithm_dima_after_locals && ab.use_min_max_2)
			stream_common_razez_positive_dima_min_max = fopen(lpstrFile, "wt");

		FILE * stream_common_razez_negative_dima_min_max = NULL;
		sprintf(lpstrFile, "%s\\razez_negative_dima_min_max.dat", dir_out);
		if (ab.use_window_cycles_algorithm_dima_after_locals && ab.use_min_max_2)
			stream_common_razez_negative_dima_min_max = fopen(lpstrFile, "wt");
		//============================================================================
		//============================================================================
		FILE * stream_common_razez_positive_min_max = NULL;
		sprintf(lpstrFile, "%s\\razez_positive_min_max.dat", dir_out);
		if (ab.use_window_cycles_algorithm_1_after_locals && ab.use_min_max_2)
			stream_common_razez_positive_min_max = fopen(lpstrFile, "wt");

		FILE * stream_common_razez_negative_min_max = NULL;
		sprintf(lpstrFile, "%s\\razez_negative_min_max.dat", dir_out);
		if (ab.use_window_cycles_algorithm_1_after_locals && ab.use_min_max_2)
			stream_common_razez_negative_min_max = fopen(lpstrFile, "wt");
		//============================================================================
		//============================================================================
		//##############################################################
		//����� ����� �������� ����� ������
		//##############################################################

		

#if _USE_WINSURF_

		SurfDoc * doc = NULL;
#if _USE_WINSURF_ON_CONSOL_
		win_app * app;
#endif
		if (consol)
		{
#if _USE_WINSURF_ON_CONSOL_
			//������� ������ ��� 3D ������������
			singleton_cleaner<win_app> app_cleaner;
			app = win_app::GetInstance();  
			app_cleaner.SetInstance(app);
			app->GetWinProject()->SetApp(app);
			doc = (SurfDoc *)app->GetWinProject();

			if (!doc)
			{
				MessageBox(0, "!doc","",0);
				return false;
			}

			AutoBuildProfile auto_build_profile(doc);
			doc->m_auto_build_profiles.AddMsg(&auto_build_profile);
			doc->m_auto_build_profiles_ObjectList.Init(doc->m_auto_build_profiles, doc);

			p_auto_build_profile = &doc->m_auto_build_profiles.GetLastMsg();
#endif
		}
		else
		{
			doc = (SurfDoc *)p_auto_build_profile->GetDoc();
		}

		if (!p_auto_build_profile)
		{
			MessageBox(0, "!p_auto_build_profile","",0);
			return false;
		}
		//create 5 root collections

		//1-st
		Collection *pcollection_graphics = p_auto_build_profile->CreateNewCollection();
		p_auto_build_profile->m_collections.GetLastMsg().SetName("Graphics");
		//2-nd
		Collection *pcollection_pos_dima = p_auto_build_profile->CreateNewCollection();
		p_auto_build_profile->m_collections.GetLastMsg().SetName("Positives dima");
		//3-d
		Collection *pcollection_neg_dima = p_auto_build_profile->CreateNewCollection();
		p_auto_build_profile->m_collections.GetLastMsg().SetName("Negatives dima");
		//4-th
		Collection *pcollection_pos = p_auto_build_profile->CreateNewCollection();
		p_auto_build_profile->m_collections.GetLastMsg().SetName("Positives");
		//5-th
		Collection *pcollection_neg = p_auto_build_profile->CreateNewCollection();
		p_auto_build_profile->m_collections.GetLastMsg().SetName("Negatives");
		//6-th
		Collection *pcollection_anomalies = p_auto_build_profile->CreateNewCollection();
		p_auto_build_profile->m_collections.GetLastMsg().SetName("Anomalies");
#endif

		for(size_t c = 0; c < cols; c++)
		{
#if _USE_WINSURF_
			//p_auto_build_profile->CreateNewCollection();
			Collection current_colomn_collection(doc);
			current_colomn_collection.SetName((*pnames_of_colomns).operator [](c+tcols));
			Collection * pcurrent_colomn_graphics_collection = 
				dynamic_cast<Collection *>(pcollection_graphics->AddObject(&current_colomn_collection));

			COLLECTION collection_pda(doc);
			collection_pda.SetName("positive dima anomalies");
			COLLECTION * pcollection_pda = 
				dynamic_cast<COLLECTION *>(pcurrent_colomn_graphics_collection->AddObject(&collection_pda));
			
			COLLECTION collection_nda(doc);
			collection_nda.SetName("negative dima anomalies");
			COLLECTION * pcollection_nda = 
				dynamic_cast<COLLECTION *>(pcurrent_colomn_graphics_collection->AddObject(&collection_nda));

			COLLECTION collection_pa(doc);
			collection_pa.SetName("positive anomalies");
			COLLECTION * pcollection_pa = 
				dynamic_cast<COLLECTION *>(pcurrent_colomn_graphics_collection->AddObject(&collection_pa));
			
			COLLECTION collection_na(doc);
			collection_na.SetName("negative anomalies");
			COLLECTION * pcollection_na = 
				dynamic_cast<COLLECTION *>(pcurrent_colomn_graphics_collection->AddObject(&collection_na));
			
			Collection collection_(doc);
			collection_.SetName("new");
			Collection * pcollection_ = 
				dynamic_cast<Collection *>(pcurrent_colomn_graphics_collection->AddObject(&collection_));
#endif

			printf("Begin %d colomn handling\n", c);
			// ����������� �������� ������ ���������� ��� ������ �������
			//double k = 1.0;
			

			//##############################################################
			//���� ������ ������������ �������� � ������ ������� ������
			double min_v; 
			bool start = true;
			for (size_t i = 0; i < rows; i++)
			{
				double f = v[c][i];
				if (start)
				{
					min_v = f;
					start = false;
				}
				else
				{
					if (min_v > f) min_v = f;
				}
			}
			//���� ������ ������������ �������� � ������ ������� ������
			//##############################################################
#if _DRAW_LINES_OF_GRAPHICS_
			vector<double> vX,vY,vZ;
			vX.resize(rows);
			vY.resize(rows);
			vZ.resize(rows);
#endif
			//##############################################################
			//���� ���������������� ������ ������ ������� �������,
			//����� ����������� �������� ���� 1.0 
			for (size_t i = 0; i < rows; i++)
			{
				v[c][i]+=ab.minimum_of_signal-min_v;
				//fill line
#if _DRAW_LINES_OF_GRAPHICS_
#if SOURCE_COORDINATES_3D
				vX[i] = X[i];
				vY[i] = Y[i];
				vZ[i] = 1000*v[c][i];
#else
				vX[i] = t[i];
				vY[i] = c;
				vZ[i] = 1000*v[c][i];
#endif
#endif
			}
			//���� ���������������� ������ ������ ������� �������,
			//����� ����������� �������� ���� 1.0 
			//##############################################################
printf("start of locals block\n");

			//##############################################################
			//���� ���������� �� ��������� �����������
			vector<vector<size_t> > vvi_lock_min;
			vector<vector<size_t> > vvi_lock_max; 
			//size_t nMaxLevels = 5;
			if (ab.locals_algorithms_type == auto_build_parametrs::locals_algorithms::on_the_second_derivatives)
			{
				Filtration(
					ab.allow_sd_limit_quantil, 
					ab.peregib_krutizna_quantil, 
#if SOURCE_COORDINATES_3D
					X, Y,
#else
					t, 
#endif
					v[c], 
					vvi_lock_min, 
					vvi_lock_max);
			}
			else
			{
				Filtration(
					v[c], 
					vvi_lock_min, 
					vvi_lock_max);
			}

printf("end  of Filtration() \n");
			if (ab.use_max)
			{
				for (size_t j = ab.start_j1; j < vvi_lock_max.size(); j++)
				{
	#if _USE_WINSURF_
					COLLECTION collection_(doc);
					char name[255]; sprintf(name, "new %d %s",j,(*pnames_of_colomns).operator [](c+tcols).c_str());				
					collection_.SetName(name);
					COLLECTION * pcollection_ = 
						dynamic_cast<COLLECTION *>(pcurrent_colomn_graphics_collection->AddObject(&collection_));
	#endif
					LocalsMaker(ab.quantil_naklony, 
#if SOURCE_COORDINATES_3D
#if SOURCE_COORDINATES_3D_ICOL_J1_J2
						original_col_numbers[c], //����� �������
						/* size_t level =*/ j, // ������� ����������
#endif
						X, Y,
#else
						t, 
#endif						
						v[c],
						vvi_lock_max[j],
						ab.k, delim,
	#if _USE_WINSURF_
						doc, pcollection_,RGB(255,0,0),
	#endif
						stream_common_razez_local_max_less,
						stream_common_razez_local_max_more
						);
				}
			}
			if (ab.use_max_2)
			{
				for (size_t j = ab.start_j2; j < vvi_lock_max.size(); j++)
				{
					Window_Cycle_Of_Signal_which_Done_By_Indexes(
						ab.m_gradient_type,
						ab.limit_dima, ab.limit_1,
#if SOURCE_COORDINATES_3D_ICOL_J1_J2
						original_col_numbers[c], //����� �������
#endif

#if SOURCE_COORDINATES_3D
						X,Y,
#else
						t, 
#endif
						
						v[c],
						vvi_lock_max[j],
						ab.win_velonsity,
						ab.use_repeat_points,  ab.n,//����� ������� ������� ( ����� 0 � ����)
						ab.minimum_of_signal, 
						
						ab.k,	delim,
						j, "max",
	#if _USE_WINSURF_
						doc, 
						pcurrent_colomn_graphics_collection,
	#endif
						stream_common_razez_positive_dima_max,
						NULL,//stream_common_razez_negative_dima_max,
						stream_common_razez_positive_max,
						NULL//stream_common_razez_negative_max
						);

				}
			}
printf("end of locals cycle 1\n");
			if (ab.use_min)
			{
				for (size_t j = ab.start_j1; j < vvi_lock_min.size(); j++)
				{
	#if _USE_WINSURF_
					COLLECTION collection_(doc);
					char name[255]; sprintf(name, "new %d %s",j,(*pnames_of_colomns).operator [](c+tcols).c_str());				
					collection_.SetName(name);
					COLLECTION * pcollection_ = 
						dynamic_cast<COLLECTION *>(pcurrent_colomn_graphics_collection->AddObject(&collection_));
	#endif
					LocalsMaker(ab.quantil_naklony, 
#if SOURCE_COORDINATES_3D
#if SOURCE_COORDINATES_3D_ICOL_J1_J2
						original_col_numbers[c], //����� �������
						/* size_t level =*/ j, // ������� ����������
#endif
						X, Y,
#else
						t, 
#endif						
						v[c],
						vvi_lock_min[j],
						ab.k, delim,
	#if _USE_WINSURF_
						doc, pcollection_, RGB(0,0,255),
	#endif
						stream_common_razez_local_min_less,
						stream_common_razez_local_min_more
						);

				}
			}
			if (ab.use_min_2)
			{
				for (size_t j = ab.start_j2; j < vvi_lock_min.size(); j++)
				{
	printf(" pre Window_Cycle_Of_Signal_which_Done_By_Indexes\n");
					Window_Cycle_Of_Signal_which_Done_By_Indexes(
						ab.m_gradient_type,
						ab.limit_dima, ab.limit_1,
#if SOURCE_COORDINATES_3D_ICOL_J1_J2
						original_col_numbers[c], //����� �������
#endif

#if SOURCE_COORDINATES_3D
						X,Y,
#else
						t, 
#endif						
						v[c],
						vvi_lock_min[j],
						ab.win_velonsity,
						ab.use_repeat_points,  ab.n,//����� ������� ������� ( ����� 0 � ����)
						ab.minimum_of_signal, 
						
						ab.k,	delim,
						j, "min",
	#if _USE_WINSURF_
						doc, 
						pcurrent_colomn_graphics_collection,
	#endif
						NULL,//stream_common_razez_positive_dima_min,
						stream_common_razez_negative_dima_min,
						NULL,//stream_common_razez_positive_min,
						stream_common_razez_negative_min
						);		
	printf(" post Window_Cycle_Of_Signal_which_Done_By_Indexes\n");
				}
			}
printf("end of locals cycle 2\n");
			if (ab.use_min_max || ab.use_min_max_2 || ab.use_min_max_sticks)
			{
				for (size_t j = ab.start_j1+1; j < vvi_lock_min.size(); j++)
				{
	#if _USE_WINSURF_
					COLLECTION collection_(doc);
					char name[255]; sprintf(name, "new %d %s",j,(*pnames_of_colomns).operator [](c+tcols).c_str());				
					collection_.SetName(name);
					COLLECTION * pcollection_ = 
						dynamic_cast<COLLECTION *>(pcurrent_colomn_graphics_collection->AddObject(&collection_));
	#endif
					size_t imin = 0, imax = 0;

					vector<size_t> vi; vi.clear();

					while(imin < vvi_lock_min[j].size() && imax < vvi_lock_max[j].size())
					{
						if (vvi_lock_min[j][imin] < vvi_lock_max[j][imax])
						{
							vi.push_back(vvi_lock_min[j][imin]);
							imin++;
						}
						else
						{
							vi.push_back(vvi_lock_max[j][imax]);
							imax++;
						}
					}

					if(vi.size() > 1)
					{
						if (ab.use_min_max_sticks)
						{
							SticksMaker(
								ab.quantil_naklony, 
#if SOURCE_COORDINATES_3D
#if SOURCE_COORDINATES_3D_ICOL_J1_J2
								original_col_numbers[c], //����� �������
								/* size_t level =*/ j, // ������� ����������
#endif
								X, Y,
#else
								t, 
#endif						
								v[c],
								vi,
								ab.k, delim,
	#if _USE_WINSURF_
								doc, pcollection_, RGB(0,255,0),
	#endif
								stream_common_razez_local_min_max_less,
								stream_common_razez_local_min_max_more
								);
						}
						if (ab.use_min_max_2)
						{
							Window_Cycle_Of_Signal_which_Done_By_Indexes(
								ab.m_gradient_type,
								ab.limit_dima, ab.limit_1,
#if SOURCE_COORDINATES_3D_ICOL_J1_J2
								original_col_numbers[c], //����� �������
#endif

#if SOURCE_COORDINATES_3D
								X,Y,
#else
								t, 
#endif								
								v[c],
								vi,
								ab.win_velonsity,
								ab.use_repeat_points,  ab.n,//����� ������� ������� ( ����� 0 � ����)
								ab.minimum_of_signal, 
								
								ab.k,	delim,
								j, "min_max",
		#if _USE_WINSURF_
								doc, 
								pcurrent_colomn_graphics_collection,
		#endif
								stream_common_razez_positive_dima_min_max,
								stream_common_razez_negative_dima_min_max,
								stream_common_razez_positive_min_max,
								stream_common_razez_negative_min_max
								);
						}

						if (ab.use_min_max)
						{
							LocalsMaker(ab.quantil_naklony, 
#if SOURCE_COORDINATES_3D
#if SOURCE_COORDINATES_3D_ICOL_J1_J2
								original_col_numbers[c], //����� �������
								/* size_t level =*/ j, // ������� ����������
#endif
								X, Y,
#else
								t, 
#endif						
								v[c],
								vi,
								ab.k, delim,
	#if _USE_WINSURF_
								doc, pcollection_, RGB(0,255,0),
	#endif
								stream_common_razez_local_min_max_less,
								stream_common_razez_local_min_max_more
								);
						}
					}
					printf("j = %u end\n",j);
				}

			}
			//����� ����� ���������� �� ��������� �����������
			//##############################################################
printf("\nend of local extremums block\n\n");
			if(ab.use_window_cycles_algorithm_dima || ab.use_window_cycles_algorithm_1)
				Window_Cycle(
					ab.m_gradient_type,
					ab.limit_dima, ab.limit_1,
#if SOURCE_COORDINATES_3D_ICOL_J1_J2
					original_col_numbers[c], //����� �������
#endif

#if SOURCE_COORDINATES_3D
					X,Y,
#else
					t, 
#endif
					
					v[c], 				  

					start_window_len, end_window_len, //step_vindow_len,
					ab.win_velonsity,
						
					ab.use_repeat_points,  ab.n,//����� ������� ������� ( ����� 0 � ����)
					ab.minimum_of_signal,
						
					ab.k,	
					delim, 
#if _USE_WINSURF_				  
					doc,			  
					pcollection_pda,	
					pcollection_nda,
					pcollection_pa,
					pcollection_na,
#endif				  
					stream_common_razez_positive_dima,
					stream_common_razez_negative_dima,
					stream_common_razez_positive,
					stream_common_razez_negative

					);
printf("\nend of Window_Cycle block\n\n");


#if _USE_WINSURF_
#if _DRAW_LINES_OF_GRAPHICS_
			// ���������� ���������� � SufDoc
			{

				Line3D line(doc);
				line.InitPoints(vX,vY,vZ,0);
				line.SetColor(RGB(0,255,255));
				if (pcurrent_colomn_graphics_collection) 
					pcurrent_colomn_graphics_collection->AddObject(&line);
			}
#endif
#endif
		}
		//����� ����������� ����� �� ��������
		//##############################################################
//			fclose (stream_common_negative_dima);
//			fclose (stream_common_positive_dima);
		if (stream_common_razez_positive_dima) fclose (stream_common_razez_positive_dima);
		if (stream_common_razez_negative_dima) fclose (stream_common_razez_negative_dima);
		//##############################################################
//			fclose (stream_common_negative);
//			fclose (stream_common_positive);
		if (stream_common_razez_positive) fclose (stream_common_razez_positive);
		if (stream_common_razez_negative) fclose (stream_common_razez_negative);
		//##############################################################

		if (stream_common_razez_local_max_less) fclose (stream_common_razez_local_max_less);
		if (stream_common_razez_local_min_less) fclose (stream_common_razez_local_min_less);
		if (stream_common_razez_local_min_max_less) fclose (stream_common_razez_local_min_max_less);
		if (stream_common_razez_local_max_more) fclose (stream_common_razez_local_max_more);
		if (stream_common_razez_local_min_more) fclose (stream_common_razez_local_min_more);
		if (stream_common_razez_local_min_max_more) fclose (stream_common_razez_local_min_max_more);
//			fclose (stream_common_razez);

		//##############################################################
//			fclose (stream_common_razez_positive_dima_min);
		if (stream_common_razez_negative_dima_min) fclose (stream_common_razez_negative_dima_min);
		//##############################################################
//			fclose (stream_common_razez_positive_min);
		if (stream_common_razez_negative_min) fclose (stream_common_razez_negative_min);
		//##############################################################

		//##############################################################
		if (stream_common_razez_positive_dima_max) fclose (stream_common_razez_positive_dima_max);
//			fclose (stream_common_razez_negative_dima_max);
		//##############################################################
		if (stream_common_razez_positive_max) fclose (stream_common_razez_positive_max);
//			fclose (stream_common_razez_negative_max);
		//##############################################################

		//##############################################################
		if (stream_common_razez_positive_dima_min_max)
			fclose (stream_common_razez_positive_dima_min_max);
		if (stream_common_razez_negative_dima_min_max)
			fclose (stream_common_razez_negative_dima_min_max);
		//##############################################################
		if (stream_common_razez_positive_min_max)
			fclose (stream_common_razez_positive_min_max);
		if (stream_common_razez_negative_min_max)
			fclose (stream_common_razez_negative_min_max);
		//##############################################################

printf("files closed!!!\n");

#if _USE_WINSURF_
#if _USE_WINSURF_ON_CONSOL_
		if (consol)
		{
			app->GetWinProject()->ZoomView();
			app->GetWinProject()->Draw();
			//������ 3D ������������
			return StartWinSurfLoop();
		}

#endif
#endif
	}
}

bool BuildingProfile(vector<vector<vector<vert_korr_points> > >& vvvvkp,
					 vector<profile_interval> & profile_intervals,
					 bool consol, 
					 AutoBuildProfile * p_auto_build_profile,
					 auto_build_parametrs& ab,
					 vector<vector<double> >& v, 
					 vector<vector<double> >& w, 
					 vector<double>& X, 
					 vector<double>& Y,
					 vector<string> * pnames_of_colomns,
					 vector<size_t>& original_col_numbers, 
					 int rows, int cols, 
					 int delim, 
					 char * current_directory,
					 char * filename,
					 bool is_reverse,
					 int shoulder,// = 50;// ����� -  ����� ���� - ��� ��� ����� ���� ����
					 int step,
					 int wlen_auto)
{
	double k = ab.k;

	sprintf(dir_out, "%s\\raz_of_%s", current_directory, filename);
	int n = 0;
	while (!CreateDirectory(dir_out,NULL))
	{
		sprintf(dir_out, "%s\\raz_of_%s(%d)", current_directory, filename, n++);
	}

	//**********************************************
	//��������� ���� �������� ������ ������
	char filename_description[4096];
	sprintf(filename_description, "%s\\description_ivan.txt", dir_out);
	FILE *stream;
	stream = fopen(filename_description,"wt");
	if (stream)
	{
		WriteDescription(stream, AutoBuildProfile::ab);
		fclose(stream);
	}
	//**********************************************
	if (!CheckMyLicense()) return false;
	//##############################################################
	//��� ���� ���������� �������������� �������
	bool vertical_korr_on_base_wnd = true;
	if (vertical_korr_on_base_wnd)
		// ���� ��������� �������� ����� � ����������� �� ������������ ��������
		// ����� �� ������������������ � ����������� �������������� ������� �� ������������ ��������
		// ����������� �� ����� ������� ���������� ��������� � ������������� ����
	{
		// ����� ����������� �� ����� �������� (-1, +1) ����������� ������� 
		// �� ������� �� ����
		// ��� ������� ��������������� ������������
		int reverse1 = +1, reverse2 = +1;

		profile_interval prof_interval;
		prof_interval.i1 = 0;

		int jend = is_reverse ? 2 : 1;
		for (int j = 0; j < jend; j++)
		{
			if (!j)
			{
				reverse1 = +1, reverse2 = +1;
			}
			else
			{
				reverse1 = +1, reverse2 = -1;
			}

			vvvvkp.resize(cols);
			// ���������� �������������� ������ �� �������� ������ ������� � ������
			for(size_t c1 = 0; c1 < cols; c1++)
			{		
				vvvvkp[c1].resize(cols);
				for(size_t c2 = 0; c2 < cols; c2++)
				{
					// ����� ������� ����� �� ��������� ������� �� ������� ������� 
					// BuildProfile
					//  � ����� �� ������� ���� ������� ������� �������������� ��������� ���� �������, 
					// ����� ������������ ���������� ������� �� ���� ������� ������,
					// � ����� ��� ������� � ������� UseWholeDirectory

					DoGorizontalCorrilation(k, shoulder,step,&vvvvkp[c1][c2],
						v, X, Y, pnames_of_colomns, original_col_numbers, 
						rows, c1, c2, reverse1, reverse2, delim);	

					DoVerticalAutoCorrelation(
						shoulder,step,wlen_auto,
						//pcollection,
						&vvvvkp[c1][c2],
						profile_intervals,
						pnames_of_colomns,
						original_col_numbers, 
						c1, c2,
						reverse1, reverse2,
						delim
						);

					BuildGrid(0,//short crd_type,
								// 0 - x, 1 - y, 2 - profile_len
						1, 		// short value_type,
								// 1 - korr_k;  // ����������� �������������� ����������
								// 2 - korr_k2; // ����������� ������������ ���������� � �������������� �������� �������
								// 3 - korr_k3; // ����������� ������������ ��������������
						NULL, //pcollection,
						&vvvvkp[c1][c2],
						profile_intervals,
						pnames_of_colomns,
						original_col_numbers,
						5, 5, 200, //double xSize, double ySize, double max_glubina, 
						c1, c2,
						reverse1, reverse2);

				}
			}
		}
		if (vvvvkp.size() > 0)
			if (vvvvkp[0].size() > 0)
				prof_interval.i2 = vvvvkp[0][0].size()-1;

		prof_interval.layer = NULL;					
		SurfDoc * doc = NULL;
		if (p_auto_build_profile)
			doc = (SurfDoc*)p_auto_build_profile->GetDoc();
		if (doc)
		{
			prof_interval.layer = doc->AddNewLayer(filename);
		}

		strcpy(prof_interval.dir, dir_out);
		profile_intervals.push_back(prof_interval);
		prof_interval.i1 = prof_interval.i2+1;
	}

}

bool BuildingProfile2(vector<vector<vector<vert_korr_points> > >& vvvvkp,
					  vector<profile_interval> & profile_intervals,
					 bool consol, 
					 AutoBuildProfile * p_auto_build_profile,
					 auto_build_parametrs& ab,
					 vector<string> * pnames_of_colomns,
					 vector<size_t>& original_col_numbers, 
					 int cols, 
					 int delim, 
					 char * current_directory,
					 char * filename,
					 bool is_reverse,
					 int wlen
				  )
{
#define MANY_COLLECTIONS_ON_EACH_COL 1
#if !MANY_COLLECTIONS_ON_EACH_COL
	Collection *pcollection = NULL;
	if (p_auto_build_profile)
	{
		pcollection = p_auto_build_profile->CreateNewCollection();
		p_auto_build_profile->m_collections.GetLastMsg().SetName("Sloi");
	}
#endif


			
	//**********************************************
	//##############################################################
	//��� ���� ���������� �������������� �������

	// ���� ��������� �������� ����� � ����������� �� ������������ ��������
	// ����� �� ������������������ � ����������� �������������� ������� �� ������������ ��������
	// ����������� �� ����� ������� ���������� ��������� � ������������� ����

	// ����� ����������� �� ����� �������� (-1, +1) ����������� ������� 
	// �� ������� �� ����
	// ��� ������� ��������������� ������������
	int reverse1 = +1, reverse2 = +1;

	int jend = is_reverse ? 2 : 1;
	for (int j = 0; j < jend; j++)
	{
		if (!j)
		{
			reverse1 = +1, reverse2 = +1;
		}
		else
		{
			reverse1 = +1, reverse2 = -1;
		}

		// ���������� �������������� ������ �� �������� ������ ������� � ������
		for(size_t c1 = 0; c1 < cols; c1++)
		{	
			for(size_t c2 = 0; c2 < cols; c2++)
			{
				// ����� ������� ����� �� ��������� ������� �� ������� ������� 
				// BuildProfile
				//  � ����� �� ������� ���� ������� ������� �������������� ��������� ���� �������, 
				// ����� ������������ ���������� ������� �� ���� ������� ������,
				// � ����� ��� ������� � ������� UseWholeDirectory
				//vector<vector<korr_point> > vvkp;
				//vvkp.clear();
#if MANY_COLLECTIONS_ON_EACH_COL
				Collection *pcollection = NULL;
				if (p_auto_build_profile)
				{
					char name[2048];

					sprintf(name, "%s_%s sym %d", 	
						(*pnames_of_colomns)[original_col_numbers[c1]].c_str(),
						(*pnames_of_colomns)[original_col_numbers[c2]].c_str(),
						reverse1 * reverse2
						);
					pcollection = p_auto_build_profile->CreateNewCollection();
					p_auto_build_profile->m_collections.GetLastMsg().SetName(name);
				}
#endif

				// �������� ���������� ����� ���������
				// ��� ��������� �� ����� ������� �� ������ ���� �������
				DoVerticalCorrelation(
					wlen,
					pcollection,
					&vvvvkp[c1][c2],
					profile_intervals,
					pnames_of_colomns,
					original_col_numbers, 
					c1, c2,
					reverse1, reverse2,
					delim
					);

				BuildGrid(0,//short crd_type,
							// 0 - x, 1 - y, 2 - profile_len
					2, 		// short value_type,
							// 1 - korr_k;  // ����������� �������������� ����������
							// 2 - korr_k2; // ����������� ������������ ���������� � �������������� �������� �������
							// 3 - korr_k3; // ����������� ������������ ��������������
					pcollection,
					&vvvvkp[c1][c2],
					profile_intervals,
					pnames_of_colomns,
					original_col_numbers,
					20, 5, 200, //double xSize, double ySize, double max_glubina, 
					c1, c2,
					reverse1, reverse2);

			}
		}
	}

	//����� ����� ���������� �������������� �������
	//##############################################################

	return true;
}


#if _USE_WINSURF_
void MakeLinePointPair(
#if SOURCE_COORDINATES_3D
				 vector<double>& X, 
				 vector<double>& Y, 
#else
				 vector<double>& t, 
#endif
				vector<double> v, 
				size_t i1, size_t i2,				   
				double x, double y, 
#if SOURCE_COORDINATES_3D
				 double z,
#endif
				char *name, COLORREF color, 
				COLLECTION * pcollection_,
				SurfDoc* doc
				)
{
	if (pcollection_)
	{
#if 0
		Collection collection_0(doc);
						
		collection_0.SetName(name);
		Collection * pcollection_0 = 
			dynamic_cast<Collection *>(pcollection_->AddObject(&collection_0));
		if (pcollection_0)
		{	
			Line3D line(doc);
			/*line.m_bChecked = false;
			char name[255];
			sprintf(name, "min_= %f, max_ = %f", min_, max_);
			line.SetName(name);*/
			line.SetColor(color);
#if SOURCE_COORDINATES_3D
			line.PushBack(CPoint3(X[i1], Y[i1], 1000*v[i1]));
			line.PushBack(CPoint3(X[i2], Y[i2], 1000*v[i2]));
#else
			line.PushBack(CPoint3(t[i1],0,1000*v[i1]));
			line.PushBack(CPoint3(t[i2],0,1000*v[i2]));
#endif
			pcollection_0->AddObject(&line);
			ThePoint3D sph(doc);
#if SOURCE_COORDINATES_3D
			sph.InitPoint(CPoint3(x, y, z, true, 0), color);
#else
			sph.InitPoint(CPoint3(x, 0.0, y, true, 0), color);
#endif
			pcollection_0->AddObject(&sph);
		}
#else
		ThePoint3D sph(doc);
#if SOURCE_COORDINATES_3D
		sph.InitPoint(CPoint3(x, y, z, true, 0), color);
#else
		sph.InitPoint(CPoint3(x, 0.0, y, true, 0), color);
#endif
		pcollection_->AddObject(&sph);
#endif
	}
}

#endif


void Window_Cycle(auto_build_parametrs::gradient_type m_gradient_type, 
				  double limit_dima, double limit_1,
#if SOURCE_COORDINATES_3D_ICOL_J1_J2
				  size_t icol, //����� �������
#endif

#if SOURCE_COORDINATES_3D
				  vector<double>& X, 
				  vector<double>& Y, 
#else
				  vector<double>& t, 
#endif
				  
				  vector<double>& in, 				  

				  size_t start_window_len,
				  size_t end_window_len,
				  //size_t step_vindow_len,
				  double win_velonsity,
				  
				  bool use_repeat_points,  int n,//����� ������� ������� ( ����� 0 � ����)
				  double minimum_of_signal, 
				   
				  double k,	
				  int delim,
#if _USE_WINSURF_
				  SurfDoc * doc, 				  
				  COLLECTION * pcollection_pda,	
				  COLLECTION * pcollection_nda,
				  COLLECTION * pcollection_pa,
				  COLLECTION * pcollection_na,
#endif
				  FILE * stream_common_razez_positive_dima,
				  FILE * stream_common_razez_negative_dima,
				  FILE * stream_common_razez_positive,
				  FILE * stream_common_razez_negative

				  )
{
printf("Window_Cycle start\n");
#if SOURCE_COORDINATES_3D
	int rows = X.size();
	if (rows != Y.size())
	{
		char str[255];
		sprintf(str, "X.size (%d) != Y.size(%d)", rows, Y.size());
		MessageBox(0, str, "Window_Cycle", 0);
		return;
	}
#else
	int rows = t.size();
#endif
	if (rows != in.size())
	{
		char str[255];
		sprintf(str, "t.size (%d) != in.size(%d)", rows, in.size());
		MessageBox(0, str, "Window_Cycle", 0);
		return;
	}

	//##############################################################
	//���� ������������ ������ ��������� �� ������� �������
#if !_USE_MIN_IN_WINDOW_
	// relative gradient
	vector<double> rg; rg.resize(rows-1);
#endif
	// free flag ���� ��-������������� �����
	vector<bool> ff; ff.resize(rows-1);
	if (rows > 1)
	{
		for (size_t i = 0; i < rows-1; i++)
		{
			ff[i] = true;
#if !_USE_MIN_IN_WINDOW_
			switch (m_gradient_type)
			{
			case auto_build_parametrs::gradient_type::the_dividitial:
				{
					rg[i] =  v[c][i+1]/v[c][i];
				}
				break;
			case auto_build_parametrs::gradient_type::the_differential:
				{
					rg[i] = (v[c][i+1]-v[c][i]) / (t[i+1]-t[i]);
				}
				break;
			}
#endif
		}
	}
	//���� ������������ ������ ��������� �� ������� �������
	//##############################################################

///*
	vector<double> vx_p, vy_p, vz_p;
	vector<double> vx_n, vy_n, vz_n;

	vector<double> vx_pd, vy_pd, vz_pd;
	vector<double> vx_nd, vy_nd, vz_nd;
//*/
	bool continue_cycle_on_window_len = true;

	size_t level = 0;


	//##############################################################
	//����������� ����� �� ������ ����
	size_t window_len = start_window_len;
	size_t step_win_len = max(1.0, end_window_len * ((1.0-win_velonsity) + win_velonsity*double(start_window_len - window_len)/double(start_window_len - end_window_len)));
	//for (size_t window_len = start_window_len; window_len <= end_window_len; window_len+=step_vindow_len)
	for (window_len = start_window_len; 
		continue_cycle_on_window_len && window_len >= end_window_len; 
		window_len-=step_win_len)
	{
		if (window_len < end_window_len)
			window_len = end_window_len;

		printf("window_len = %d = step_vindow_len = %d\n", window_len, step_win_len);
		
		step_win_len = max(1.0, 
			end_window_len * ((1.0-win_velonsity) + win_velonsity*double(start_window_len - window_len)/double(start_window_len - end_window_len)));
		//step_vindow_len+=2;
		/*if (window_len > start_window_len/2)
			step_vindow_len = 10;
		else
			step_vindow_len = end_window_len;
			*/



		size_t start_of_window = 0;
/*
		FILE * stream;
		FILE * stream_max;
		FILE * stream_min;

		sprintf(lpstrFile, "%s\\max_min_gradient_%d.dat", dir_out, window_len);
		stream = fopen(lpstrFile, "wt");
		sprintf(lpstrFile, "%s\\max_gradient_%d.dat", dir_out, window_len);
		stream_max = fopen(lpstrFile, "wt");
		sprintf(lpstrFile, "%s\\min_gradient_%d.dat", dir_out, window_len);
		stream_min = fopen(lpstrFile, "wt");
*/
		/**fprintf(stream, "\"%s_of_max_gradient_window_len_%d\"%c\"%s_of_min_gradient_window_len_%d\"%c\n",
			pnames_of_colomns->operator [](0).c_str(), window_len, delim,
			pnames_of_colomns->operator [](0).c_str(), window_len, delim);*/
/*
		fprintf(stream_max, "%s%c\"max_gradient_%d\"\n",
			pnames_of_colomns->operator [](0).c_str(), delim, window_len);
		fprintf(stream_min, "%s%c\"min_gradient_%d\"\n",
			pnames_of_colomns->operator [](0).c_str(), delim, window_len);
*/

		//##############################################################
		//������� ����� �������� �������� ��������� ������������� ���������� � ���������
		vector<size_t> vi_max_grad, vi_min_grad;
		vi_max_grad.clear(), vi_min_grad.clear();
		vector<double> v_max_grad, v_min_grad;
		v_max_grad.clear(), v_min_grad.clear();
		//##############################################################
		//����������� ����� ����������� ����
		while (start_of_window + window_len < rows)
		{
			//vector<double> vg;
			//vg.clear();
#if _USE_MIN_IN_WINDOW_
			//##############################################################
			//���� ������ ������������ �������� � ������� ����
			double min_v; 
			bool start = true;
			for (size_t i = start_of_window; i < start_of_window + window_len; i++)
			{
				double f = in[i];
				if (start)
				{
					min_v = f;
					start = false;
				}
				else
				{
					if (min_v > f) min_v = f;
				}
			}
			//����� ����� ������ ������������ �������� � ������� ����
			//##############################################################
#endif
			//##############################################################
			//������� ����� ������ ��������� � �������� ��������� ������ ����
			double max_grad, min_grad;
			size_t i_max_grad, i_min_grad;
			start = true;

			//##############################################################
			//����������� ����� ������ ����
			for (size_t i = start_of_window; i < -1 + start_of_window + window_len; i++)
			{
				//##############################################################
				//���� ���� �� ������������ ��� ����� ��� ���������� ����� ���������� ������������� �����
				if (ff[i] || use_repeat_points)
				{
#if _USE_MIN_IN_WINDOW_
					double grad = (in[i+1]+minimum_of_signal-min_v)/(in[i]+minimum_of_signal-min_v);
					switch (m_gradient_type)
					{
					case auto_build_parametrs::gradient_type::the_dividitial:
						{
							//rg[i] =  v[c][i+1]/v[c][i];
							grad = (in[i+1]+minimum_of_signal-min_v)/(in[i]+minimum_of_signal-min_v);
						}
						break;
					case auto_build_parametrs::gradient_type::the_differential:
						{
							//rg[i] = (v[c][i+1]-v[c][i]) / (t[i+1]-t[i]);
#if SOURCE_COORDINATES_3D
							grad = (in[i+1]-in[i]) / sqrt(pow(X[i+1]-X[i], 2.0) + pow(Y[i+1]-Y[i], 2.0));
#else
							grad = (in[i+1]-in[i]) / (t[i+1]-t[i]);
#endif
						}
						break;
					}					
					if (grad <= 0.0)
					{
						char str[255];
						sprintf(str, "grad (%f) <= 0 [%d %d]", grad, i, i+1 );
						MessageBox(0, str, "", 0);
					}								
					if (grad == 0.0)
					{
						char str[255];
						sprintf(str, "grad (%f) == 0 [%d %d]", grad, i, i+1 );
						MessageBox(0, str, "", 0);
					}
#else
					double grad = rg[i];
#endif
					//##############################################################
					//���� �������� � ������� ������ ��������� � �� ��������� ������ ����
					if (start)
					{
						max_grad = min_grad = grad;
						i_max_grad = i_min_grad = i;

						start = false;
					}
					else
					{
						if (max_grad < grad) {max_grad = grad; i_max_grad = i;}
						if (min_grad > grad) {min_grad = grad; i_min_grad = i;}
					}
					//���� �������� � ������� ������ ��������� � �� ��������� ������ ����
					//##############################################################
				}
				//���� ���� �� ������������ ��� ����� ��� ���������� ����� ���������� ������������� �����
				//##############################################################
			}
			if (start) 
			{
				//MessageBox(0, "start!!!!", "min_grad & max_grad not determined", 0);
				printf( "start!!!! min_grad & max_grad not determined\n");
				//����� �� ����� �� ������ ����
				continue_cycle_on_window_len = false;
			}
			else
			{
				if (min_grad <= 0)
				{
					char str[255];
					sprintf(str, "min_grad (%f) <= 0", min_grad);
					MessageBox(0, str, "", 0);
				}

				if (min_grad == 0)
				{
					char str[255];
					sprintf(str, "min_grad (%f) <= 0", min_grad);
					MessageBox(0, str, "", 0);
				}

				//����������� ����� ������ ����
				//##############################################################
				//printf("i_max_grad = %d i_min_grad = %d\n",i_max_grad, i_min_grad);
				vi_max_grad.push_back(i_max_grad);
				vi_min_grad.push_back(i_min_grad);
				v_max_grad.push_back(max_grad);
				v_min_grad.push_back(min_grad);
				//����� �� ��� �������� ���� ������ ��������� � �������� ��������� ������ ����
				//� ����� ����� �� ���������
				//##############################################################

				//##############################################################
				//���������� ���� ��������������� �����
				if (i_max_grad < start_of_window + window_len/2 || start_of_window + 3*window_len/2 > rows) 
				{
					
					for (int jj = i_max_grad - n; jj <= i_max_grad + n; jj++)
					{
						if (jj >= 0 && jj < rows-1)
							ff[jj] = false;
					}
				}
				if (i_min_grad < start_of_window + window_len/2 || start_of_window + 3*window_len/2 > rows) 
				{
					for (int jj = i_min_grad - n; jj <= i_min_grad + n; jj++)
					{
						if (jj >= 0 && jj < rows-1)
							ff[jj] = false;
					}
				}
				//�������� ���� ��������������� �����
				//##############################################################
			}

			//��� ����������� ����
			start_of_window += window_len/2;
		}
		//����� ����������� ����� ����������� ����
		//##############################################################
//printf("Window_Cycle end of inter window cycle \n");

		//����� �� ��� ������� ������� ��������� ������������� ���������� � ���������
		//vector<size_t> vi_max_grad, vi_min_grad;
		//##############################################################

		//##############################################################
		//���� ������������ �������� ������
		//����������� ���������� � ��������� � ����
		OutputDimaAlgorithm(limit_dima, 
#if SOURCE_COORDINATES_3D
#if SOURCE_COORDINATES_3D_ICOL_J1_J2
			icol, //����� �������
			level, // ������� ����������
#endif
			X,Y,
#else
			t, 
#endif
			in, vi_max_grad, vi_min_grad,
				v_max_grad, v_min_grad,
				
				k,	
				delim,

#if _USE_WINSURF_
				doc, 
				pcollection_nda,
				pcollection_pda,
#endif
				stream_common_razez_positive_dima,
				stream_common_razez_negative_dima

				);
//printf("Window_Cycle end of OutputDimaAlgorithm \n");

		OutputFirstAlgorithm(limit_1, 
#if SOURCE_COORDINATES_3D
#if SOURCE_COORDINATES_3D_ICOL_J1_J2
				icol, //����� �������
				level, // ������� ����������
#endif

				X,Y,
#else
				t, 
#endif				
				in,
				vi_max_grad, vi_min_grad,
				v_max_grad, v_min_grad,
				
				k,	
				delim,
#if _USE_WINSURF_

				doc, 
				pcollection_na,
				pcollection_pa,
#endif

				stream_common_razez_positive,
				stream_common_razez_negative

				);
		//����� ����� ������������ �������� ������
		//##############################################################
		level++;
	}
	//����� ����������� ����� �� ������ ����
	//##############################################################
printf("Window_Cycle end !!! \n");
}

void OutputDimaAlgorithm(double limit_dima,
#if SOURCE_COORDINATES_3D_ICOL_J1_J2
						 size_t icol, //����� �������
						 size_t level, // ������� ����������
#endif
#if SOURCE_COORDINATES_3D
						 vector<double>& X, 
						 vector<double>& Y, 
#else
						 vector<double>& t, 
#endif
						 
						 vector<double>& in,
						 vector<size_t>& vi_max_grad, vector<size_t>& vi_min_grad,
						 vector<double>& v_max_grad, vector<double>& v_min_grad,
						 
						 double k,	
						 int delim,
#if _USE_WINSURF_
						 SurfDoc * doc, 
						 COLLECTION * pcollection_nda,
						 COLLECTION * pcollection_pda,
#endif
						 FILE * stream_com_raz_pos,
						 FILE * stream_com_raz_neg

						 )
{
	//##############################################################
	//��������, ������� ��������� ����:
	//--------------------------------------
	//� 1-� ���� ���� ������ ��������, 
	//�� 2-� ���� ���� ������ �������
	//���������� �� � ���� - ��� ���� ������������ ������������� ��������
	//---------------------------------------
	//�� 1-� ���� ���� ������ ��������, 
	//� 3-� ���� ���� ������ �������
	//���������� �� � ���� - � �.�.
	//---------------------------------------

	if(vi_max_grad.size() > 0 && vi_min_grad.size() > 0)
	{
		for(size_t j = 0; j < vi_max_grad.size()-1 && j < vi_min_grad.size()-1; j++)
		{
			{
				//work with positive anomalies
				size_t i_max = vi_max_grad[j];
				double g_max = v_max_grad[j];
#if SOURCE_COORDINATES_3D
				double x_max = X[i_max+1];
				double y_max = Y[i_max+1];
#else
				double t_max = t[i_max+1];
#endif
				size_t i_min = vi_min_grad[j+1];
				double g_min = v_min_grad[j+1];
#if SOURCE_COORDINATES_3D
				double x_min = X[i_min];
				double y_min = Y[i_min];
#else
				double t_min = t[i_min];
#endif

				if (g_min == 0)
				{
					MessageBox(0, "g_min == 0", "dima positive",0);
				}

#if SOURCE_COORDINATES_3D
				double x, y, z;
#else
				double x, y;
#endif
				double min_ = g_min != 0 ? min(g_max, 1.0/g_min) : g_max;
				double max_ = g_min != 0 ? max(g_max, 1.0/g_min) : g_max;
				double r_ = min_/max_;

				if (r_ > limit_dima)
				{
#if SOURCE_COORDINATES_3D
					SourcesCoordinates_Calcule_AndSave(
#if SOURCE_COORDINATES_3D_ICOL_J1_J2
						icol, i_max+1, i_min, // ����� �������, ������� ������ � ����� ��������
						level, // ������� ����������	
#endif
						x_max, y_max, x_min, y_min, k, 
						stream_com_raz_pos, delim, r_ , max_, x, y, z);//j ???

	#if _USE_WINSURF_
					char name[255]; sprintf(name, "min_= %f, max_ = %f", min_, max_);
					MakeLinePointPair(X, Y, in, i_max, i_min, x,y,z, name, RGB(255,0,0), pcollection_pda, doc);
	#endif
#else
					SourcesCoordinates_Calcule_AndSave(t_max, t_min, k, 
						stream_com_raz_pos, delim, r_ , max_, x, y);//j ???

	#if _USE_WINSURF_
					char name[255]; sprintf(name, "min_= %f, max_ = %f", min_, max_);
					MakeLinePointPair(t, in, i_max, i_min, x,y,name, RGB(255,0,0), pcollection_pda, doc);
	#endif
#endif
				}
			}
			{
				//work with negative anomalies
				size_t i_max = vi_max_grad[j+1];
				double g_max = v_max_grad[j+1];
#if SOURCE_COORDINATES_3D
				double x_max = X[i_max];
				double y_max = Y[i_max];
#else
				double t_max = t[i_max];
#endif
				size_t i_min = vi_min_grad[j];
				double g_min = v_min_grad[j];
#if SOURCE_COORDINATES_3D
				double x_min = X[i_min+1];
				double y_min = Y[i_min+1];
#else
				double t_min = t[i_min+1];
#endif

				if (g_min == 0)
				{
					MessageBox(0, "g_min == 0", "dima negative",0);
				}

#if SOURCE_COORDINATES_3D
				double x, y, z;
#else
				double x, y;
#endif
				double min_ = g_min != 0 ? min(g_max, 1.0/g_min) : g_max;
				double max_ = g_min != 0 ? max(g_max, 1.0/g_min) : g_max;
				double r_ = min_/max_;

				if (r_ > limit_dima)
				{
#if SOURCE_COORDINATES_3D
					SourcesCoordinates_Calcule_AndSave(
#if SOURCE_COORDINATES_3D_ICOL_J1_J2
						icol, i_max, i_min+1, // ����� �������, ������� ������ � ����� ��������
						level, // ������� ����������	
#endif
						
						x_max, y_max, x_min, y_min, k, 
						stream_com_raz_neg, delim, r_ , max_, x, y, z);//j ???

	#if _USE_WINSURF_
					char name[255]; sprintf(name, "min_= %f, max_ = %f", min_, max_);
					MakeLinePointPair(X, Y, in, i_max, i_min, x,y,z, name, RGB(0,0,255), pcollection_nda, doc);
	#endif
#else
					SourcesCoordinates_Calcule_AndSave(t_max, t_min, k, 
						stream_com_raz_neg, delim, r_ , max_, x, y);//j ???

	#if _USE_WINSURF_
					char name[255]; sprintf(name, "min_= %f, max_ = %f", min_, max_);
					MakeLinePointPair(t, in, i_max, i_min, x,y,name, RGB(0,0,255), pcollection_nda, doc);
	#endif
#endif
				}

			}
		}
	}
	//����� ���������, ������� ��������� ����
	//##############################################################
}
void OutputFirstAlgorithm(double limit_1,
#if SOURCE_COORDINATES_3D_ICOL_J1_J2
						 size_t icol, //����� �������
						 size_t level, // ������� ����������
#endif
#if SOURCE_COORDINATES_3D
						  vector<double>& X, 
						  vector<double>& Y, 
#else
						  vector<double>& t, 
#endif
						 
						 vector<double>& in,
						 vector<size_t>& vi_max_grad, vector<size_t>& vi_min_grad,
						 vector<double>& v_max_grad, vector<double>& v_min_grad,
						 
						 double k,	
						 int delim,
#if _USE_WINSURF_
						 SurfDoc * doc, 
						 COLLECTION * pcollection_na,
						 COLLECTION * pcollection_pa,
#endif
						 FILE * stream_com_raz_pos,
						 FILE * stream_com_raz_neg

						 )
{
	//##############################################################
	//�������� 1 
	//--------------------------------------
	//�������� � ������� ���� �� ������� ������ � ���� �� ����
	//���������� �� � ���� - 
	//����� ��� ���� ����� �� ������������� ��� ������������� ��������
	//�� ��������: ���� �������� �����, �� �������� �������������
	//---------------------------------------

	bool pre_positive_anomaly=false;;

	if(vi_max_grad.size() > 0 && vi_min_grad.size() > 0)
	{
		for(size_t j = 0; j < vi_max_grad.size() && j < vi_min_grad.size(); j++)
		{
			//work with positive anomalies
			size_t i_max = vi_max_grad[j];
			size_t i_min = vi_min_grad[j];


			bool positive_anomaly = i_max < i_min;
			//if (positive_anomaly != pre_positive_anomaly || j==0)

			if (positive_anomaly)
			{
				double g_max = v_max_grad[j];
#if SOURCE_COORDINATES_3D
				double x_max = X[i_max+1];
				double y_max = Y[i_max+1];
#else
				double t_max = t[i_max+1];
#endif
				double g_min = v_min_grad[j];
#if SOURCE_COORDINATES_3D
				double x_min = X[i_min];
				double y_min = Y[i_min];
#else
				double t_min = t[i_min];
#endif


				if (g_min == 0)
				{
					MessageBox(0, "g_min == 0", "�������� 1",0);
				}

#if SOURCE_COORDINATES_3D
				double x, y, z;
#else
				double x, y;
#endif
				double min_ = g_min != 0 ? min(g_max, 1.0/g_min) : g_max;
				double max_ = g_min != 0 ? max(g_max, 1.0/g_min) : g_max;
				double r_ = min_/max_;
				if (r_ > limit_1)
				{
#if SOURCE_COORDINATES_3D
					SourcesCoordinates_Calcule_AndSave(
#if SOURCE_COORDINATES_3D_ICOL_J1_J2
						icol, i_max+1, i_min, // ����� �������, ������� ������ � ����� ��������
						level, // ������� ����������	
#endif						
						x_max, y_max, x_min, y_min, k, 
						stream_com_raz_pos, delim, r_ , max_, x, y, z);//j ???

#if _USE_WINSURF_
					char name[255]; sprintf(name, "min_= %f, max_ = %f", min_, max_);
					MakeLinePointPair(X,Y, in, i_max, i_min, x,y,z, name, RGB(255,0,0), pcollection_pa, doc);
#endif
#else
					SourcesCoordinates_Calcule_AndSave(t_max, t_min, k, 
						stream_com_raz_pos, delim, r_ , max_, x, y);//j ???

#if _USE_WINSURF_
					char name[255]; sprintf(name, "min_= %f, max_ = %f", min_, max_);
					MakeLinePointPair(t, in, i_max, i_min, x,y,name, RGB(255,0,0), pcollection_pa, doc);
#endif
#endif
				}
			}
			else
			{
				double g_max = v_max_grad[j];
#if SOURCE_COORDINATES_3D
				double x_max = X[i_max];
				double y_max = Y[i_max];
#else
				double t_max = t[i_max];
#endif
				double g_min = v_min_grad[j];
#if SOURCE_COORDINATES_3D
				double x_min = X[i_min+1];
				double y_min = Y[i_min+1];
#else
				double t_min = t[i_min+1];
#endif


				if (g_min == 0)
				{
					MessageBox(0, "g_min == 0", "�������� 1",0);
				}

#if SOURCE_COORDINATES_3D
				double x, y, z;
#else
				double x, y;
#endif
				double min_ = g_min != 0 ? min(g_max, 1.0/g_min) : g_max;
				double max_ = g_min != 0 ? max(g_max, 1.0/g_min) : g_max;
				double r_ = min_/max_;
				if (r_ > limit_1)
				{
#if SOURCE_COORDINATES_3D

					SourcesCoordinates_Calcule_AndSave(
#if SOURCE_COORDINATES_3D_ICOL_J1_J2
						icol, i_max, i_min+1, // ����� �������, ������� ������ � ����� ��������
						level, // ������� ����������	
#endif
						
						x_max, y_max, x_min, y_min, k, 
					stream_com_raz_neg, delim, r_ , max_, x, y, z);//j ???

#if _USE_WINSURF_
					char name[255]; sprintf(name, "min_= %f, max_ = %f", min_, max_);
					MakeLinePointPair(X, Y, in, i_max, i_min, x,y,z, name, RGB(0,0,255), pcollection_na, doc);
#endif
#else
					SourcesCoordinates_Calcule_AndSave(t_max, t_min, k, 
					stream_com_raz_neg, delim, r_ , max_, x, y);//j ???

#if _USE_WINSURF_
					char name[255]; sprintf(name, "min_= %f, max_ = %f", min_, max_);
					MakeLinePointPair(t, in, i_max, i_min, x,y,name, RGB(0,0,255), pcollection_na, doc);
#endif
#endif
				}
			}
		}
	}
	//����� ��������� 1
	//##############################################################
}

void Window_Cycle_Of_Signal_which_Done_By_Indexes(
		auto_build_parametrs::gradient_type m_gradient_type,
		double limit_dima, double limit_1,
#if SOURCE_COORDINATES_3D_ICOL_J1_J2
		size_t icol, //����� �������
#endif

#if SOURCE_COORDINATES_3D
		vector<double>& X, 
		vector<double>& Y, 
#else
		vector<double>& t, 
#endif
	
		vector<double>& v,
		 vector<size_t>& vi,
		 double win_velonsity,
		 
		 bool use_repeat_points,  int n,//����� ������� ������� ( ����� 0 � ����)
		 double minimum_of_signal, 

		 double k,	
		 int delim,

		 size_t level_of_signal, 
		 char * name_suffics,

#if _USE_WINSURF_
		 SurfDoc * doc, 
		 Collection * pcurrent_colomn_graphics_collection,
#endif
		 FILE * stream_com_raz_pos_dima_,
		 FILE * stream_com_raz_neg_dima_,
		 FILE * stream_com_raz_pos_,
		 FILE * stream_com_raz_neg_
		 )
{
	if(vi.size() >= 40)
	{
#if SOURCE_COORDINATES_3D
		vector<double> xx, yy, in;
		xx.resize(vi.size());
		yy.resize(vi.size());
#else
		vector<double> tt, in;
		tt.resize(vi.size());
#endif
		in.resize(vi.size());
		for (size_t i = 0; i < vi.size(); i++)
		{
#if SOURCE_COORDINATES_3D
			xx[i] = X[vi[i]];
			yy[i] = Y[vi[i]];
#else
			tt[i] = t[vi[i]];
#endif
			in[i] = v[vi[i]];
		}
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#if _USE_WINSURF_
		char name[256]; 
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		COLLECTION * pcollection_pda_;
		if (stream_com_raz_pos_dima_)
		{
			COLLECTION collection_pda_(doc);
			sprintf(name, "pos dima anomal of %s %u filt-level",name_suffics, level_of_signal);
			collection_pda_.SetName(name);
			pcollection_pda_ = 
				dynamic_cast<COLLECTION *>(pcurrent_colomn_graphics_collection->AddObject(&collection_pda_));
		}
		else
		{
			pcollection_pda_ = NULL;
		}

		COLLECTION * pcollection_nda_;
		if (stream_com_raz_neg_dima_)
		{
			COLLECTION collection_nda_(doc);
			sprintf(name, "neg dima anomal of %s %u filt-level", name_suffics, level_of_signal);
			collection_nda_.SetName(name);
			pcollection_nda_ = 
				dynamic_cast<COLLECTION *>(pcurrent_colomn_graphics_collection->AddObject(&collection_nda_));
		}
		else
		{
			pcollection_nda_ = NULL;
		}
		
		COLLECTION * pcollection_pa_;
		if(stream_com_raz_pos_)
		{
			COLLECTION collection_pa_(doc);
			sprintf(name, "pos anomal of %s %u filt-level", name_suffics, level_of_signal);
			collection_pa_.SetName(name);
			pcollection_pa_ = 
				dynamic_cast<COLLECTION *>(pcurrent_colomn_graphics_collection->AddObject(&collection_pa_));
		}
		else
		{
			pcollection_pa_ = NULL;
		}
		
		COLLECTION * pcollection_na_ ;
		if(stream_com_raz_neg_)
		{
			COLLECTION collection_na_(doc);
			sprintf(name, "neg anomal of %s %u filt-level", name_suffics, level_of_signal);
			collection_na_.SetName(name);
			pcollection_na_ = 
				dynamic_cast<COLLECTION *>(pcurrent_colomn_graphics_collection->AddObject(&collection_na_));
		}
		else
		{
			pcollection_na_ = NULL;
		}
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#endif
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

		Window_Cycle(
			m_gradient_type,
			limit_dima, limit_1,
#if SOURCE_COORDINATES_3D_ICOL_J1_J2
			icol, //����� �������
#endif
#if SOURCE_COORDINATES_3D
			xx, yy, 
#else
			tt, 
#endif
			in, 	
			//start_window_len, end_window_len, step_vindow_len,                            
			in.size()/2, in.size()/10, //in.size()/20,   
			win_velonsity,
			use_repeat_points,  n,//����� ������� ������� ( ����� 0 � ����)
			minimum_of_signal,
			k,	
			delim, 
#if _USE_WINSURF_	
			doc,
			pcollection_pda_,
			pcollection_nda_,
			pcollection_pa_,
			pcollection_na_,
#endif				  
			stream_com_raz_pos_dima_,
			stream_com_raz_neg_dima_,
			stream_com_raz_pos_,
			stream_com_raz_neg_
			);
	}
}
#if SOURCE_COORDINATES_3D

void SourcesCoordinates_Calcule_AndSave(
#if SOURCE_COORDINATES_3D_ICOL_J1_J2
	size_t icol, size_t j1, size_t j2, // ����� �������, ������� ������ � ����� ��������
	size_t level, // ������� ����������	
#endif
	double x1, double y1, 
	double x2, double y2,
	double k, FILE * stream, int delim, double r_ , double max_, 
	double& x, double& y, double& z)
{
	//���������� ��������� � ������ ����������
	x = (x1 + x2)/2.0;
	y = (y1 + y2)/2.0;
	z = -k*sqrt( 
		(x1 - x2)*(x1 - x2) 
		+
		(y1 - y2)*(y1 - y2) 
		);

	if (stream) 
		fprintf(stream, 
		"%7.3f%c%7.3f%c%7.3f%c%1.6f%c%3.5f"
#if SOURCE_COORDINATES_3D_ICOL_J1_J2
		"%c%u%c%u%c%u"
		"%c%d"
#endif
		"\n",
		x, delim, y, delim, z, delim, r_, delim, max_
#if SOURCE_COORDINATES_3D_ICOL_J1_J2
		, delim, icol, delim, j1, delim, j2
		, delim, level	// ������� ����������			
#endif
		);
}
#else /*SOURCE_COORDINATES_3D*/
void SourcesCoordinates_Calcule_AndSave(double t1, double t2, double k, FILE * stream, int delim, double r_ , double max_, double& x, double& y)
{
	//���������� ��������� � ������ ����������
	x = (t1 + t2)/2.0;
	y = -k*fabs(t1 - t2);

	if (stream) 
		fprintf(stream, 
		"%7.3f%c%7.3f%c%1.6f%c%3.5f"
		//"%c%d"
		"\n",
		x, delim, y, delim, r_, delim, max_
		//, delim, j				
		);
}
#endif /*SOURCE_COORDINATES_3D*/

void LocalsMaker(
				 double quantil_naklony, 
#if SOURCE_COORDINATES_3D_ICOL_J1_J2
				 size_t icol, //����� �������
				 size_t level, // ������� ����������
#endif
#if SOURCE_COORDINATES_3D
				 vector<double>& X, 
				 vector<double>& Y, 
#else
				 vector<double>& t, 
#endif
				 vector<double>& in,
				 vector<size_t>& vi,
				 double k,	
				 int delim,
#if _USE_WINSURF_
				 SurfDoc * doc, 
				 COLLECTION * pcollection_,
				 COLORREF color,
#endif
				 FILE *stream_less,
				 FILE *stream_more
				 )

{
	// quantil_naklony
	// �������� ������ "�������" �� ���� ������
	// �� ����� �������� ������ �� �������� � "�������",
	// ������� ����� ����������� ���� �������

	if (vi.size() > 1)
	{
		vector <double> v_naklony;
		v_naklony.clear();
		for (size_t i = 0; i < vi.size()-1; i++)
		{
			size_t i1 = vi[i];
			size_t i2 = vi[i+1];

			// ������� �������� �������
			double r_ = fabs(in[i1] - in[i2]);
			//double max_ = max(in[i1], in[i2]);
			// ������� � ����������� 
#if SOURCE_COORDINATES_3D
			double delta_t = sqrt(
				(X[i1] - X[i2])*(X[i1] - X[i2]) 
				+
				(Y[i1] - Y[i2])*(Y[i1] - Y[i2]) 
				);
#else
			double delta_t = fabs(t[i1] - t[i2]);
#endif /*SOURCE_COORDINATES_3D*/
			
			double naklon = r_/delta_t;	
			v_naklony.push_back(naklon);
		}	
		sort(v_naklony.begin(), v_naklony.end());
		size_t len = v_naklony.size();
		size_t dlen = size_t(quantil_naklony*len);

		//double naklon_limit = v_naklony[len-dlen];
		double naklon_limit = v_naklony[dlen > 0 ? dlen-1 : 0];
//for(size_t i = 0; i < v_naklony.size(); i++)
//	printf("v_naklony[%d] = %f\n",i, v_naklony[i]);

//printf("v_naklony[0] %f naklon_limit %f v_naklony[len-1] %f len %d dlen %d\n", v_naklony[0], naklon_limit, v_naklony[len-1], len, dlen);
					    
		for (size_t i = 0; i < vi.size()-1; i++)
		{
			size_t i1 = vi[i];
			size_t i2 = vi[i+1];

			// ������� �������� �������
			double r_ = fabs(in[i1] - in[i2]);
			double max_ = max(in[i1], in[i2]);
			// ������� � ����������� 
#if SOURCE_COORDINATES_3D
			double delta_t = sqrt(
				(X[i1] - X[i2])*(X[i1] - X[i2]) 
				+
				(Y[i1] - Y[i2])*(Y[i1] - Y[i2]) 
				);
#else
			double delta_t = fabs(t[i1] - t[i2]);
#endif /*SOURCE_COORDINATES_3D*/
			double naklon = r_/delta_t;

			int ans = IDYES;

			if (false)
			{
				WinPlot(X,in, i1, i2);
				ans = MessageBox(0, "Add This?","LocalsMaker", MB_YESNOCANCEL);
			}

			if (ans == IDCANCEL)
				return;

			if (ans == IDYES)
			{
				if (naklon < naklon_limit)
				{
	#if SOURCE_COORDINATES_3D
					double x, y, z;
					SourcesCoordinates_Calcule_AndSave(
#if SOURCE_COORDINATES_3D_ICOL_J1_J2
						icol, i1, i2, // ����� �������, ������� ������ � ����� ��������
						level, // ������� ����������	
#endif
						X[i1], Y[i1], 
						X[i2], Y[i2], 
						k, 
						stream_less, delim, r_ , max_, x, y, z);//j ???
	#if _USE_WINSURF_
					char name[255]; sprintf(name, "i1=%u i2=%u", i1, i2);
					MakeLinePointPair(X, Y, in, i1, i2, x,y,z, name, color, pcollection_, doc);
	#endif

	#else /*SOURCE_COORDINATES_3D*/
					double x, y;
					SourcesCoordinates_Calcule_AndSave(t[i1], t[i2], k, 
						stream_less, delim, r_ , max_, x, y);//j ???
	#if _USE_WINSURF_
					char name[255]; sprintf(name, "i1=%u i2=%u t1=%f t2=%f", i1, i2, t[i1], t[i2]);
					MakeLinePointPair(t, in, i1, i2, x,y,name, color, pcollection_, doc);
	#endif

	#endif /*SOURCE_COORDINATES_3D*/
				}
				else
				{
	#if SOURCE_COORDINATES_3D
					double x, y, z;
					SourcesCoordinates_Calcule_AndSave(
#if SOURCE_COORDINATES_3D_ICOL_J1_J2
						icol, i1, i2, // ����� �������, ������� ������ � ����� ��������
						level, // ������� ����������	
#endif
						X[i1], Y[i1], 
						X[i2], Y[i2], 
						k, 
						stream_more, delim, r_ , max_, x, y, z);//j ???
	#if _USE_WINSURF_
					char name[255]; sprintf(name, "i1=%u i2=%u", i1, i2);
					MakeLinePointPair(X, Y, in, i1, i2, x,y,z, name, color, pcollection_, doc);
	#endif

	#else /*SOURCE_COORDINATES_3D*/
					double x, y;
					SourcesCoordinates_Calcule_AndSave(t[i1], t[i2], k, 
						stream_more, delim, r_ , max_, x, y);//j ???
	#if _USE_WINSURF_
					char name[255]; sprintf(name, "i1=%u i2=%u t1=%f t2=%f", i1, i2, t[i1], t[i2]);
					MakeLinePointPair(t, in, i1, i2, x,y, name, color, pcollection_, doc);
	#endif

	#endif /*SOURCE_COORDINATES_3D*/

				}
			}
		}
	}
}



void SticksMaker(
				 double quantil_naklony, 
#if SOURCE_COORDINATES_3D_ICOL_J1_J2
				 size_t icol, //����� �������
				 size_t level, // ������� ����������
#endif
#if SOURCE_COORDINATES_3D
				 vector<double>& X, 
				 vector<double>& Y, 
#else
				 vector<double>& t, 
#endif
				 vector<double>& in,
				 vector<size_t>& vi,
				 double k,	
				 int delim,
#if _USE_WINSURF_
				 SurfDoc * doc, 
				 COLLECTION * pcollection_,
				 COLORREF color,
#endif
				 FILE *stream_less,
				 FILE *stream_more
				 )

{
	// quantil_naklony
	// �������� ������ "�������" �� ���� ������
	// �� ����� �������� ������ �� �������� � "�������",
	// ������� ����� ����������� ���� �������

	if (vi.size() > 1)
	{
		vector <double> v_naklony;
		v_naklony.clear();
		for (size_t i = 0; i < vi.size()-1; i++)
		{
			size_t i1 = vi[i];
			size_t i2 = vi[i+1];

			// ������� �������� �������
			double r_ = fabs(in[i1] - in[i2]);
			//double max_ = max(in[i1], in[i2]);
			// ������� � ����������� 
#if SOURCE_COORDINATES_3D
			double delta_t = sqrt(
				(X[i1] - X[i2])*(X[i1] - X[i2]) 
				+
				(Y[i1] - Y[i2])*(Y[i1] - Y[i2]) 
				);
#else
			double delta_t = fabs(t[i1] - t[i2]);
#endif /*SOURCE_COORDINATES_3D*/
			
			double naklon = r_/delta_t;	
			v_naklony.push_back(naklon);
		}	
		sort(v_naklony.begin(), v_naklony.end());
		size_t len = v_naklony.size();
		size_t dlen = size_t(quantil_naklony*len);

		//double naklon_limit = v_naklony[len-dlen];
		double naklon_limit = v_naklony[dlen > 0 ? dlen-1 : 0];
//for(size_t i = 0; i < v_naklony.size(); i++)
//	printf("v_naklony[%d] = %f\n",i, v_naklony[i]);

//printf("v_naklony[0] %f naklon_limit %f v_naklony[len-1] %f len %d dlen %d\n", v_naklony[0], naklon_limit, v_naklony[len-1], len, dlen);
					    
		for (size_t i = 0; i < vi.size()-1; i++)
		{
			size_t i1 = vi[i];
			size_t i2 = vi[i+1];

			// ������� �������� �������
			double r_ = fabs(in[i1] - in[i2]);
			double max_ = max(in[i1], in[i2]);
			// ������� � ����������� 
#if SOURCE_COORDINATES_3D
			double delta_t = sqrt(
				(X[i1] - X[i2])*(X[i1] - X[i2]) 
				+
				(Y[i1] - Y[i2])*(Y[i1] - Y[i2]) 
				);
#else
			double delta_t = fabs(t[i1] - t[i2]);
#endif /*SOURCE_COORDINATES_3D*/
			double naklon = r_/delta_t;

			int ans = IDYES;

			if (false)
			{
				WinPlot(X,in, i1, i2);
				ans = MessageBox(0, "Add This?","LocalsMaker", MB_YESNOCANCEL);
			}

			if (ans == IDCANCEL)
				return;

			if (ans == IDYES)
			{
				if (naklon < naklon_limit)
				{
	#if SOURCE_COORDINATES_3D
					double x, y, z;
					SourcesCoordinates_Calcule_AndSave(
#if SOURCE_COORDINATES_3D_ICOL_J1_J2
						icol, i1, i2, // ����� �������, ������� ������ � ����� ��������
						level, // ������� ����������	
#endif
						X[i1], Y[i1], 
						X[i2], Y[i2], 
						k, 
						stream_less, delim, r_ , max_, x, y, z);//j ???
	#if _USE_WINSURF_
					char name[255]; sprintf(name, "i1=%u i2=%u", i1, i2);
					MakeLinePointPair(X, Y, in, i1, i2, x,y,z, name, color, pcollection_, doc);
	#endif

	#else /*SOURCE_COORDINATES_3D*/
					double x, y;
					SourcesCoordinates_Calcule_AndSave(t[i1], t[i2], k, 
						stream_less, delim, r_ , max_, x, y);//j ???
	#if _USE_WINSURF_
					char name[255]; sprintf(name, "i1=%u i2=%u t1=%f t2=%f", i1, i2, t[i1], t[i2]);
					MakeLinePointPair(t, in, i1, i2, x,y,name, color, pcollection_, doc);
	#endif

	#endif /*SOURCE_COORDINATES_3D*/
				}
				else
				{
	#if SOURCE_COORDINATES_3D
					double x, y, z;
					SourcesCoordinates_Calcule_AndSave(
#if SOURCE_COORDINATES_3D_ICOL_J1_J2
						icol, i1, i2, // ����� �������, ������� ������ � ����� ��������
						level, // ������� ����������	
#endif
						X[i1], Y[i1], 
						X[i2], Y[i2], 
						k, 
						stream_more, delim, r_ , max_, x, y, z);//j ???
	#if _USE_WINSURF_
					char name[255]; sprintf(name, "i1=%u i2=%u", i1, i2);
					MakeLinePointPair(X, Y, in, i1, i2, x,y,z, name, color, pcollection_, doc);
	#endif

	#else /*SOURCE_COORDINATES_3D*/
					double x, y;
					SourcesCoordinates_Calcule_AndSave(t[i1], t[i2], k, 
						stream_more, delim, r_ , max_, x, y);//j ???
	#if _USE_WINSURF_
					char name[255]; sprintf(name, "i1=%u i2=%u t1=%f t2=%f", i1, i2, t[i1], t[i2]);
					MakeLinePointPair(t, in, i1, i2, x,y, name, color, pcollection_, doc);
	#endif

	#endif /*SOURCE_COORDINATES_3D*/

				}
			}
		}
	}
}
#define COLLEC_TION FastCollection


void DoVerticalAutoCorrelation(int shoulder,// = 50;// ����� -  ����� ���� - ��� ��� ����� ���� ����
							   int step,
							   int wlen,// = 10;//����� ���� ����������
							   //Collection * pcollection,
							   vector<vert_korr_points> * vvkp, 
							   vector<profile_interval> & profile_intervals,
							   vector<string> * pnames_of_colomns,
							   vector<size_t>& original_col_numbers, 
							   size_t c1, size_t c2,
							   int reverse1, int reverse2,
							   int delim)
{

	vector<double> vX, vY, vZ, vK;

	char *p;
	TCHAR blnFile[1024];
	FILE * bln = NULL;
#if 0
	sprintf(blnFile, "%s\\auto_vert_%s_%s_sym_%d.bln", dir_out,
		(*pnames_of_colomns)[original_col_numbers[c1]].c_str(),
		(*pnames_of_colomns)[original_col_numbers[c2]].c_str(),
		reverse1 * reverse2
		);

	while (p=strchr (blnFile,'\"'))
	{
		*p = '_';
	}

	bln = fopen(blnFile, "wt");
#endif

	//������ �� ������������ ������� ��������� ������������ �����
/*
	double max_z = 10000.0;
	double profile_len = 0.0;
	for (size_t r = 1; r < rows; r++)
	{
		profile_len += sqrt(
			(X[r]-X[r-1])*(X[r]-X[r-1])
			+
			(Y[r]-Y[r-1])*(Y[r]-Y[r-1])
			);                
	}
	double row_step = profile_len/rows;
	double h_step = row_step*ab.k;
	size_t max_delta_rows = max_z/h_step;
	printf("max_delta_rows = %u\n", max_delta_rows);
	int max_shoulder = max_delta_rows/2;
*/

	TCHAR lpstrFile[1024];
	FILE * corr_v3 = NULL;
	sprintf(lpstrFile, "%s\\auto_vert_%d_%d_%d_%s_%s_sym_%d.dat", dir_out,
		2*shoulder+1, step, wlen,
		(*pnames_of_colomns)[original_col_numbers[c1]].c_str(),
		(*pnames_of_colomns)[original_col_numbers[c2]].c_str(),
		reverse1 * reverse2
		);
	
	while (p=strchr (lpstrFile,'\"'))
	{
		*p = '_';
	}
	printf("try to open file: \n%s\n", lpstrFile);
	corr_v3 = fopen(lpstrFile, "wt");



	//TCHAR lpstrFile[1024];
	FILE * corr_v_3 = NULL;
#if 0
	sprintf(lpstrFile, "%s\\auto0_vert_%d_%d_%d_%s_%s_sym_%d.dat", dir_out,
		2*shoulder+1, step, wlen,
		(*pnames_of_colomns)[original_col_numbers[c1]].c_str(),
		(*pnames_of_colomns)[original_col_numbers[c2]].c_str(),
		reverse1 * reverse2
		);
	
	//char *p;
	while (p=strchr (lpstrFile,'\"'))
	{
		*p = '_';
	}
	printf("try to open file: \n%s\n", lpstrFile);
	corr_v_3 = fopen(lpstrFile, "wt");
#endif


	// �������� ���������� ����� ���������

#define AUTO_KORR 1
#if !AUTO_KORR
	for (size_t R = 1; R < (*vvkp).size(); R++)
	{
		//����� ���� �������� ��������
		size_t len0 = (*vvkp)[R-1].vkp.size();
		size_t len1 = (*vvkp)[R].vkp.size();

		// ������ �� �������� �������
		vector<korr_point>& vkp_0  = (*vvkp)[R-1].vkp;
		vector<korr_point>& vkp_1  = (*vvkp)[R].vkp;
#else
	for (size_t R = 0; R < (*vvkp).size(); R++)
	{
		//����� ���� �������� ��������
		size_t len0 = (*vvkp)[R].vkp.size();
		size_t len1 = (*vvkp)[R].vkp.size();

		// ������ �� �������� �������
		vector<korr_point>& vkp_0  = (*vvkp)[R].vkp;
		vector<korr_point>& vkp_1  = (*vvkp)[R].vkp;
#endif

		// �������� ����� ���� ���� ���� 
		// �������� ����������� �������������� ������� 
		// ������� �� ������ ������ ���������� 
		// ��� ������ ��������� ���������� 
		// ����� ��������� ���������

		int len_0 = len0-wlen+1;
		int len_1 = len1-wlen+1;

        // ���� ����������� �������������� ������� �������
		if (len_0 > 0 && len_1 > 0)
		{
			// �������� ������ ��� �������������� �������
			double **M = AllocDoubleMat(len_0,len_1);

			double min_k = DBL_MAX;
			double max_k = -DBL_MAX;

			int i_0_max, i_1_max, i_0_min, i_1_min;

			//������������ ���������� �������������� ������� 
			// � ���� ������
			for (int i_0 = 0; i_0 < len_0; i_0++)
			{
				for (int i_1 = 0; i_1 < len_1; i_1++)
				{
					// �������� ������ ��������������� ������������											
					//
					// ��������� ����������� � ������ �� ����
					double m_0 = 0.0, m_1 = 0.0;
					//int n_0 = 0, n_1 = 0;
					for (int w = 0; w < wlen; w++)
					{	
						m_0 += vkp_0[w+i_0].korr_k;		
						m_1 += vkp_1[w+i_1].korr_k;		
					}
					m_0 /= wlen;
					m_1 /= wlen;

					// ��������� ��������� � ������������������ ���������� � ������ �� ����
					double D_0 = 0.0, D_1 = 0.0;										
					for (int w = 0; w < wlen; w++)
					{
						D_0 += (vkp_0[w+i_0].korr_k-m_0)*(vkp_0[w+i_0].korr_k-m_0);                                            
						D_1 += (vkp_1[w+i_1].korr_k-m_1)*(vkp_1[w+i_1].korr_k-m_1);
					}
					D_0 /= wlen;
					D_1 /= wlen;

					double sigma_0 = sqrt(D_0);
					double sigma_1 = sqrt(D_1);
					// ������������ �������������� �����������
					double K_0_1 = 0.0;
					for (int w = 0; w < wlen; w++)
					{
						K_0_1 += (vkp_0[w+i_0].korr_k-m_0)*(vkp_1[w+i_1].korr_k-m_1);
					}
					K_0_1 /= wlen;
					double k_0_1 = K_0_1 / (sigma_0*sigma_1);
					M[i_0][i_1] = k_0_1;

					if (k_0_1 > max_k)
					{
						max_k = k_0_1;
						i_0_max = i_0;
						i_1_max = i_1;
					}

					if (k_0_1 < min_k)
					{
						min_k = k_0_1;
						i_0_min = i_0;
						i_1_min = i_1;
					}

				}
			}

			if (bln)
			{
				fprintf(bln,"%d,%d, %f\n", 2, 0, max_k);
				fprintf(bln,"%f,%f\n", vkp_0[wlen/2+i_0_max].x, vkp_0[wlen/2+i_0_max].z);
				fprintf(bln,"%f,%f\n", vkp_1[wlen/2+i_1_max].x, vkp_0[wlen/2+i_1_max].z);
			}


			// � ����� ������� ���������� ����� ��� �������� 
			// (� ������ �������������� ������� �����������, 
			// ��� ��� �� �����) ���� � ������ 
			// � ������� ��������� �������� ������� ����

			// �������� ������ ��� �������������� �������
			double **M2 = AllocDoubleMat(len_0,len_0);

			double min_k2 = DBL_MAX;
			double max_k2 = -DBL_MAX;

			for (int i_00 = 0; i_00 < len_0; i_00++)
			{								
				for (int i_01 = 0; i_01 < len_0; i_01++)
				{
					double k = korr_koeff(len_1, M[i_00], M[i_01]);
					M2[i_00][i_01] = k;
					if (k > max_k2)
						max_k2 = k;
					if (k < min_k2)
						min_k2 = k;
				}
			}

			double **M3 = AllocDoubleMat(len_0,len_0);

			double min_k3 = DBL_MAX;
			double max_k3 = -DBL_MAX;

			for (int i_00 = 0; i_00 < len_0; i_00++)
			{								
				for (int i_01 = 0; i_01 < len_0; i_01++)
				{
					double k = korr_koeff(len_1, M2[i_00], M2[i_01]);
					M3[i_00][i_01] = k;
					if (k > max_k3)
						max_k3 = k;
					if (k < min_k3)
						min_k3 = k;
				}
			}

			double **M4 = AllocDoubleMat(len_0,len_0);

			double min_k4 = DBL_MAX;
			double max_k4 = -DBL_MAX;

			for (int i_00 = 0; i_00 < len_0; i_00++)
			{								
				for (int i_01 = 0; i_01 < len_0; i_01++)
				{
					double k = korr_koeff(len_1, M3[i_00], M3[i_01]);
					M4[i_00][i_01] = k;
					if (k > max_k4)
						max_k4 = k;
					if (k < min_k4)
						min_k4 = k;
				}
			}
			// ����� ������ ������ ���������� ���������� �� �������� 
			// ��� ����������� �������� 

			// ������ �������� ������ ��� ������ �������������� ��������

			double * vk3 = new double[len_0];

			// �������� � ���� ������ ������ ������ �������

			for (int i_01 = 0; i_01 < len_0; i_01++)
			{		
				vk3[i_01] = M4[0][i_01];
			}

			if (false)
			{
				// ��������� � ��� ��������� � ����� ������������ ����������

				for (int i_00 = 1; i_00 < len_0; i_00++)
				{
					double k = korr_koeff(len_1, M4[i_00], vk3);								
					for (int i_01 = 0; i_01 < len_0; i_01++)
					{
						vk3[i_01] += k*M4[i_00][i_01];										
					}
				}

				// ������ ��������� �� �������� -1 +1
				double min_k5 = DBL_MAX;
				double max_k5 = -DBL_MAX;
				for (int i_01 = 0; i_01 < len_0; i_01++)
				{		
					double k = vk3[i_01];
					if (k > max_k5)
						max_k5 = k;
					if (k < min_k5)
						min_k5 = k;
				}

				//���� ����������
				for (int i_01 = 0; i_01 < len_0; i_01++)
				{		
					double k = vk3[i_01];
					vk3[i_01] = -1.0 + 2.0 * (k - min_k5) / (max_k5 - min_k5);
				}
			}

			// ������� ��������� � �������

			for (int i_01 = 0; i_01 < len_0; i_01++)
			{
				vkp_0[wlen/2+i_01].korr_k3 = vk3[i_01];
				if (corr_v3) 
					fprintf(corr_v3, 
					"%7.3f%c%7.3f%c%4.3f"
					"%c%f"
					"\n",
					vkp_0[wlen/2+i_01].x, delim, 
					vkp_0[wlen/2+i_01].y, delim, 
					vkp_0[wlen/2+i_01].z, delim, 
					vkp_0[wlen/2+i_01].korr_k3
					);

				vX.push_back(vkp_0[wlen/2+i_01].x);
				vY.push_back(vkp_0[wlen/2+i_01].y);
				vZ.push_back(vkp_0[wlen/2+i_01].z);
				vK.push_back(vkp_0[wlen/2+i_01].korr_k3);
			}

			//������ ����������� � ����

			for (int i_01 = 1; i_01 < len_0; i_01++)
			{
				if(vkp_0[wlen/2+i_01].korr_k3 * vkp_0[wlen/2+i_01-1].korr_k3 < 0.0)
				{
					if (corr_v_3) 
						fprintf(corr_v_3, 
						"%7.3f%c%7.3f%c%4.3f"
						"%c%f"
						"\n",
						vkp_0[wlen/2+i_01].x, delim, 
						vkp_0[wlen/2+i_01].y, delim, 
						vkp_0[wlen/2+i_01].z, delim, 
						vkp_0[wlen/2+i_01].korr_k3
						);
				}
			}
			if (vk3) delete [] vk3;

			
#if 0 // ����� �� ������ ������������� �����
#if 1
			{
			// 
			Grid grid;
			grid.gridSection.z = M;
			grid.gridSection.nCol = len_1;
			grid.gridSection.nRow = len_0;
			grid.gridSection.xLL = 0.0;
			grid.gridSection.yLL = 0.0;
			grid.gridSection.xSize = 1.0;
			grid.gridSection.ySize = 1.0;
			grid.gridSection.zMax = max_k;
			grid.gridSection.zMin = min_k;

			grid.faultSection.nTraces = 0;
			grid.faultSection.nVertices = 0;
			grid.faultSection.traces = NULL;
			grid.faultSection.vertexes = NULL;


			//
			char file[2048];
			sprintf(file, "%s\\corr_ivan_%s_%s_sym_%d R = %04d.grd", dir_out,
				(*pnames_of_colomns)[original_col_numbers[c1]].c_str(),
				(*pnames_of_colomns)[original_col_numbers[c2]].c_str(),
				reverse1 * reverse2,
				R
				);

			SaveAsSurferGrid7(file, &grid);
			}
#endif
#if 1
			{
			// 
			Grid grid2;
			grid2.gridSection.z = M2;
			grid2.gridSection.nCol = len_0;
			grid2.gridSection.nRow = len_0;
			grid2.gridSection.xLL = 0.0;
			grid2.gridSection.yLL = 0.0;
			grid2.gridSection.xSize = 1.0;
			grid2.gridSection.ySize = 1.0;
			grid2.gridSection.zMax = max_k2;
			grid2.gridSection.zMin = min_k2;

			grid2.faultSection.nTraces = 0;
			grid2.faultSection.nVertices = 0;
			grid2.faultSection.traces = NULL;
			grid2.faultSection.vertexes = NULL;


			//
			char file2[2048];
			sprintf(file2, "%s\\corr_ivan_%s_%s_sym_%d R = %04d 2.grd", dir_out,
				(*pnames_of_colomns)[original_col_numbers[c1]].c_str(),
				(*pnames_of_colomns)[original_col_numbers[c2]].c_str(),
				reverse1 * reverse2,
				R
				);

			SaveAsSurferGrid7(file2, &grid2);
			}
#endif
#if 1
			{
			// 
			Grid grid3;
			grid3.gridSection.z = M3;
			grid3.gridSection.nCol = len_0;
			grid3.gridSection.nRow = len_0;
			grid3.gridSection.xLL = 0.0;
			grid3.gridSection.yLL = 0.0;
			grid3.gridSection.xSize = 1.0;
			grid3.gridSection.ySize = 1.0;
			grid3.gridSection.zMax = max_k3;
			grid3.gridSection.zMin = min_k3;

			grid3.faultSection.nTraces = 0;
			grid3.faultSection.nVertices = 0;
			grid3.faultSection.traces = NULL;
			grid3.faultSection.vertexes = NULL;


			//
			char file3[2048];
			sprintf(file3, "%s\\corr_ivan_%s_%s_sym_%d R = %04d 3.grd", dir_out,
				(*pnames_of_colomns)[original_col_numbers[c1]].c_str(),
				(*pnames_of_colomns)[original_col_numbers[c2]].c_str(),
				reverse1 * reverse2,
				R
				);

			SaveAsSurferGrid7(file3, &grid3);
			}
#endif
#if 1
			{
			// 
			Grid grid4;
			grid4.gridSection.z = M4;
			grid4.gridSection.nCol = len_0;
			grid4.gridSection.nRow = len_0;
			grid4.gridSection.xLL = 0.0;
			grid4.gridSection.yLL = 0.0;
			grid4.gridSection.xSize = 1.0;
			grid4.gridSection.ySize = 1.0;
			grid4.gridSection.zMax = max_k4;
			grid4.gridSection.zMin = min_k4;

			grid4.faultSection.nTraces = 0;
			grid4.faultSection.nVertices = 0;
			grid4.faultSection.traces = NULL;
			grid4.faultSection.vertexes = NULL;


			//
			char file4[2048];
			sprintf(file4, "%s\\corr_ivan_%s_%s_sym_%d R = %04d 4.grd", dir_out,
				(*pnames_of_colomns)[original_col_numbers[c1]].c_str(),
				(*pnames_of_colomns)[original_col_numbers[c2]].c_str(),
				reverse1 * reverse2,
				R
				);

			SaveAsSurferGrid7(file4, &grid4);
			}
#endif
#endif
			// ������� �������������� �������
			if (M) FreeDoubleMat(M);
			if (M2) FreeDoubleMat(M2);
			if (M3) FreeDoubleMat(M3);
			if (M4) FreeDoubleMat(M4);
		}
	}

	if (bln) fclose(bln);
	if (corr_v3) fclose (corr_v3);
	if (corr_v_3) fclose (corr_v_3);


	TCHAR file_grd[1024];
	sprintf(file_grd, "%s\\auto_vert_%d_%d_%d_%s_%s_sym_%d_.grd", dir_out,
		2*shoulder+1, step, wlen,
		(*pnames_of_colomns)[original_col_numbers[c1]].c_str(),
		(*pnames_of_colomns)[original_col_numbers[c2]].c_str(),
		reverse1 * reverse2
		);

				
	double xSize = 20;
	double ySize = 20;
	double max_glubina = 2000; 

	BuildGrid(file_grd,
				vX,			
				vY,			
				vZ,			
				vK,			
				xSize, ySize, max_glubina, 
				NULL// pcollection
				);

/*	BuildGrid(0,//short crd_type,
				// 0 - x, 1 - y, 2 - profile_len
		3, 		// short value_type,
				// 1 - korr_k;  // ����������� �������������� ����������
				// 2 - korr_k2; // ����������� ������������ ���������� � �������������� �������� �������
				// 3 - korr_k3; // ����������� ������������ ��������������
		NULL, //pcollection,
		vvkp,
		profile_intervals,
		pnames_of_colomns,
		original_col_numbers,
		20, 5, 200, //double xSize, double ySize, double max_glubina, 
		c1, c2,
		reverse1, reverse2);*/
}
void DoVerticalCorrelation(	int wlen,// = 100;//����� ���� ����������
						   Collection * pcollection,
						   vector<vert_korr_points> * vvkp, 
						   vector<profile_interval> & profile_intervals,
						   vector<string> * pnames_of_colomns,
						   vector<size_t>& original_col_numbers, 
						   size_t c1, size_t c2,
						   int reverse1, int reverse2,
						   int delim)
{
// �������� ���������� ����� ���������
// ��� ��������� �� ����� ������� �� ������ ���� �������
	//int wlen = 50;//����� ���� ����������
	/*int max_size = 0;
	
	for (size_t R = 0; R < (*vvkp).size(); R++)
	{
		//����� ��������
		size_t len0 = (*vvkp)[R].vkp.size();

		// ������ �� �������
		vert_korr_points& vkp_0  = (*vvkp)[R];

		// �������� ����� ���� ���� ���� 
		// �������� ����������� �������������� ������� 
		// ������� �� ������ ������ ���������� 
		// ��� ������ ��������� ���������� 
		// ����� ���������

		int len_0 = len0-wlen+1;
		// ���� ����������� �������������� ������� �������
		if (len_0 > max_size)
		{
			max_size = len_0;
		}
	}*/




	// ������� �������, ��� �����
	size_t R_base = (*vvkp).size()/2;
	vert_korr_points& vkp_1  = (*vvkp)[R_base];
	size_t len1 = vkp_1.vkp.size();
	int len_1 = len1-wlen+1;

	// ����� �� ������������� ������� ������� ������� ����������

	//int i_1 = 0;
	int i_1 = len_1/2;
	for (int i_1 = 0; i_1 < len_1; i_1 += len_1/2)
	{		

		// ��������� ����������� � ������� ������� ������� ����������
		double m_1 = 0.0;
		for (int w = 0; w < wlen; w++)
		{	
			m_1 += vkp_1.vkp[w+i_1].korr_k;		
		}
		m_1 /= wlen;

		// ��������� ��������� � ������������������ ���������� � ������� ������� ������� ����������
		double D_1 = 0.0;										
		for (int w = 0; w < wlen; w++)
		{
			D_1 += (vkp_1.vkp[w+i_1].korr_k-m_1)*(vkp_1.vkp[w+i_1].korr_k-m_1);
		}
		D_1 /= wlen;

		double sigma_1 = sqrt(D_1);


		profile_interval * current_profile_interval = NULL;
		int current_profile_number = 0;
		if (current_profile_number < profile_intervals.size())
			current_profile_interval = &profile_intervals[current_profile_number];


		COLLEC_TION * pcurrent_fast_collection = NULL;


		CPoint3 pt;
		pt.bVisible = true;
		//Sphere3D prim;
		ThePoint3D prim;


		// �������� ������ ��� �������������� �������
		//double **M = AllocDoubleMat(max_size, (*vvkp).size());
		//double BlankValue = BLANK_VALUE;//1.70141e38;// nodes are blanked if greater or equal to this value

		/*for (size_t R = 0; R < (*vvkp).size(); R++)
		{
			for (size_t i_0 = 0; i_0 < max_size; i_0++)
			{
				M[i_0][R] = BlankValue;
			}
		}
		double min_k = DBL_MAX;
		double max_k = -DBL_MAX;
*/

		///////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////
		FILE * dat = NULL;

		char file_dat[2048];

		sprintf(file_dat, "%s\\base_vert_%d_%s_%s sym %d i_1 = %04d.dat", 	
			current_profile_interval ? current_profile_interval->dir : dir_out,
			wlen,
			(*pnames_of_colomns)[original_col_numbers[c1]].c_str(),
			(*pnames_of_colomns)[original_col_numbers[c2]].c_str(),
			reverse1 * reverse2,
			i_1
			);
		char * p;
		while (p=strchr (file_dat,'\"'))
		{
			*p = '_';
		}
		printf("try to open file %s\n", file_dat);
		dat = fopen(file_dat, "wt");

		if (pcollection)
		{			
			COLLEC_TION current_fast_collection;
			SurfDoc * doc = (SurfDoc*)pcollection->GetDoc();
			current_fast_collection.InitDoc(doc);
			current_fast_collection.SetName(file_dat);
			if (current_profile_interval)
				current_fast_collection.
				SetLayer(current_profile_interval->layer);
			pcurrent_fast_collection = 
				dynamic_cast<COLLEC_TION *>(pcollection->AddObject(&current_fast_collection));

		}
		else
			printf("NOT pcollection on DoVerticalCorrelation !!!!!!!!!!!!!!!\n");
		if (pcurrent_fast_collection)
			prim.InitDoc((SurfDoc*)pcurrent_fast_collection->GetDoc());
		///////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////

		size_t ROWS = (*vvkp).size();
		int printed_progress = 0;
		double progress_len = 80;
		printf("\n");
		for (size_t R = 0; R < ROWS; R++)
		{
			//printf("R = %d ROWS = %d\n", R, ROWS);
			double progress_part =  progress_len * double(R) / double(ROWS);
			int to_print_progress = int(progress_part - printed_progress);
			for(int pp = 0; pp < to_print_progress; pp++)
			{
				printed_progress++;
				printf("#");
			}

			// �������� ���� ��� ������ � ��������� ��� 3� ���� �� ��������� �� ����� �������
			if (current_profile_interval)
			{
				if (R == current_profile_interval->i2)
				{
					current_profile_number++;

					if (current_profile_number < profile_intervals.size())
					{
						if (dat) fclose(dat);
						dat = NULL;

						current_profile_interval = &profile_intervals[current_profile_number];

						sprintf(file_dat, "%s\\base_vert_%d_%s_%s sym %d i_1 = %04d.dat", 	
							current_profile_interval ? current_profile_interval->dir : dir_out,
							wlen,
							(*pnames_of_colomns)[original_col_numbers[c1]].c_str(),
							(*pnames_of_colomns)[original_col_numbers[c2]].c_str(),
							reverse1 * reverse2,
							i_1
							);
						char * p;
						while (p=strchr (file_dat,'\"'))
						{
							*p = '_';
						}
						printf("try to open file %s\n", file_dat);
						dat = fopen(file_dat, "wt");

						if (pcollection)
						{			
							COLLEC_TION current_fast_collection;
							SurfDoc * doc = (SurfDoc*)pcollection->GetDoc();
							current_fast_collection.InitDoc(doc);
							current_fast_collection.SetName(file_dat);
							if (current_profile_interval)
								current_fast_collection.
								SetLayer(current_profile_interval->layer);
							pcurrent_fast_collection = 
								dynamic_cast<COLLEC_TION *>(pcollection->AddObject(&current_fast_collection));
						}
						else
							printf("NOT pcollection on DoVerticalCorrelation !!!!!!!!!!!!!!!\n");
					}
				}
			}

			// ������ �� �������
			vert_korr_points& vkp_0  = (*vvkp)[R];

			//����� ��������
			size_t len0 = vkp_0.vkp.size();	


			// �������� ����� ���� ���� ���� 
			// �������� ����������� �������������� ������� 
			// ������� �� ������ ������ ���������� 
			// ��� ������ ��������� ���������� 
			// ����� ��������� ���������

			int len_0 = len0-wlen+1;
			
			// ���� ����������� �������������� ������� �������
			if (len_0 > 0 && len_1 > 0)
			{
				//������������ ���������� �������������� ������� 
				for (int i_0 = 0; i_0 < len_0; i_0++)
				{
					// �������� ������ ��������������� ������������											
					//
					// ��������� ����������� � ������ �� ����
					double m_0 = 0.0;
					for (int w = 0; w < wlen; w++)
					{	
						m_0 += vkp_0.vkp[w+i_0].korr_k;		
					}
					m_0 /= wlen;

					// ��������� ��������� � ������������������ ���������� � ������ �� ����
					double D_0 = 0.0;										
					for (int w = 0; w < wlen; w++)
					{
						D_0 += (vkp_0.vkp[w+i_0].korr_k-m_0)*(vkp_0.vkp[w+i_0].korr_k-m_0);                                            
					}
					D_0 /= wlen;

					double sigma_0 = sqrt(D_0);


					// ������������ �������������� �����������
					double K_0_1 = 0.0;
					for (int w = 0; w < wlen; w++)
					{
						K_0_1 += (vkp_0.vkp[w+i_0].korr_k-m_0)*(vkp_1.vkp[w+i_1].korr_k-m_1);
					}
					K_0_1 /= wlen;
					double k_0_1 = K_0_1 / (sigma_0*sigma_1);
					//M[max_size-i_0-1][R] = k_0_1;

					int ind = wlen/2+i_0;
					vkp_0.vkp[ind].korr_k2 = k_0_1;

					if(dat) 
						fprintf(dat, "%f,%f,%f,%f\n",
							vkp_0.vkp[ind].x,
							vkp_0.vkp[ind].y,
							vkp_0.vkp[ind].z,

							k_0_1);
#if 0
					if (pcurrent_fast_collection)
					{
						COLORREF color = 0;
						// ����� �� ��������� ��������� ��������
						double color_part = (k_0_1 + 1.0) / 2.0;

						if(pcurrent_fast_collection->GetDoc())
						{
							color = ((SurfDoc*)pcurrent_fast_collection->GetDoc())->m_palette.GetColor(color_part);
						}

						pt.x = vkp_0.vkp[ind].x;
						pt.y = vkp_0.vkp[ind].y;
						pt.z = vkp_0.vkp[ind].z;

						prim.InitPoint(pt,color);
						pcurrent_fast_collection->AddObject(&prim);
					}
#endif
					/*if (k_0_1 > max_k)
					{
						max_k = k_0_1;
					}

					if (k_0_1 < min_k)
					{
						min_k = k_0_1;
					}*/					

				}
			}
			// ���� ����������� �������������� ������� �������
			if (len_0 > 0 && len_1 > 0)
			{
				//������������ ���������� �������������� ������� 
				for (int i_0 = 1; i_0 < len_0 -1; i_0++)
				{
					int ind = wlen/2+i_0;
					if(
						vkp_0.vkp[ind+1].korr_k2 * vkp_0.vkp[ind-1].korr_k2 < 0.0 
						/*||	
						(vkp_0.vkp[ind+1].korr_k2 > vkp_0.vkp[ind].korr_k2 && vkp_0.vkp[ind-1].korr_k2 > vkp_0.vkp[ind].korr_k2)
						||						
						(vkp_0.vkp[ind+1].korr_k2 < vkp_0.vkp[ind].korr_k2 && vkp_0.vkp[ind-1].korr_k2 < vkp_0.vkp[ind].korr_k2)*/
						)
					{
						if (pcurrent_fast_collection)
						{
							COLORREF color = 0;
							// ����� �� ��������� ��������� ��������
							double color_part = (vkp_0.vkp[ind].korr_k2 + 1.0) / 2.0;

							if(pcurrent_fast_collection->GetDoc())
							{
								color = ((SurfDoc*)pcurrent_fast_collection->GetDoc())->m_palette.GetColor(color_part);
							}

							pt.x = vkp_0.vkp[ind].x;
							pt.y = vkp_0.vkp[ind].y;
							pt.z = vkp_0.vkp[ind].z;

							prim.InitPoint(pt,color);
							pcurrent_fast_collection->AddObject(&prim);
						}
					}
				}
			}
		}



		printf("\n");
		if (pcurrent_fast_collection)
			pcurrent_fast_collection->InitObjectList();
#if 0
		// 
		Grid grid;
		grid.gridSection.z = M;
		grid.gridSection.nCol = (*vvkp).size();
		grid.gridSection.nRow = max_size;
		grid.gridSection.xLL = 0.0;
		grid.gridSection.yLL = 0.0;
		grid.gridSection.xSize = 1.0;
		grid.gridSection.ySize = 1.0;
		grid.gridSection.zMax = max_k;
		grid.gridSection.zMin = min_k;

		grid.faultSection.nTraces = 0;
		grid.faultSection.nVertices = 0;
		grid.faultSection.traces = NULL;
		grid.faultSection.vertexes = NULL;


		//
		char file[2048];
		sprintf(file, "%s\\base_vert_%d_%s_%s_sym_%d i_1 = %04d.grd", dir_out,
			wlen,
			(*pnames_of_colomns)[original_col_numbers[c1]].c_str(),
			(*pnames_of_colomns)[original_col_numbers[c2]].c_str(),
			reverse1 * reverse2,
			i_1
			);
		while (p=strchr (file,'\"'))
		{
			*p = '_';
		}
		SaveAsSurferGrid7(file, &grid);
#endif
		// ������� �������������� �������
		//if (M) FreeDoubleMat(M);
		if (dat) fclose(dat);
	}

}


void DoGorizontalCorrilation(double k,
							 int shoulder,// = 50;// ����� -  ����� ���� - ��� ��� ����� ���� ����
							 int step,
							 vector<vert_korr_points> * vvkp,
							 vector<vector<double> >& v, 
							 vector<double>& X, 
							 vector<double>& Y,
							 vector<string> * pnames_of_colomns,
							 vector<size_t>& original_col_numbers, 
							 int rows, size_t c1, size_t c2,
							 int reverse1, int reverse2,
							 int delim)
{	
	TCHAR lpstrFile[1024];
	FILE * stream_corr_ivan = NULL;
	sprintf(lpstrFile, "%s\\gor_kor_%d_%d_%s_%s_sym_%d.dat", dir_out,
		2*shoulder+1, step,
		(*pnames_of_colomns)[original_col_numbers[c1]].c_str(),
		(*pnames_of_colomns)[original_col_numbers[c2]].c_str(),
		reverse1 * reverse2
		);
	
	char *p;
	while (p=strchr (lpstrFile,'\"'))
	{
		*p = '_';
	}
	printf("try to open file: \n%s\n", lpstrFile);
	stream_corr_ivan = fopen(lpstrFile, "wt");

	if (stream_corr_ivan) 
	{	
		printf("start of filling file: \n%s\n", lpstrFile);


		//������ �� ������������ ������� ��������� ������������ �����

		double max_z = 10000.0;
		double profile_len = 0.0;
		for (size_t r = 1; r < rows; r++)
		{
			profile_len += sqrt(
				(X[r]-X[r-1])*(X[r]-X[r-1])
				+
				(Y[r]-Y[r-1])*(Y[r]-Y[r-1])
				);                
		}
		double row_step = profile_len/rows;
		double h_step = row_step*k;
		size_t max_delta_rows = max_z/h_step;
		printf("max_delta_rows = %u\n", max_delta_rows);
		int max_shoulder = max_delta_rows/2;



		// ������� �������� ������� ����� ���� � ���������� 
		// � ����������� �� ���������� ����
		if (c1 == 0 && c2 == 0)
		{
			TCHAR testFile[1024];
			FILE * test_x = NULL;
			FILE * test_y = NULL;
			sprintf(testFile, "%s\\test_x.bln", dir_out);
			test_x = fopen(testFile, "wt");
			sprintf(testFile, "%s\\test_y.bln", dir_out);
			test_y = fopen(testFile, "wt");

			int len = 0;
			for (int r = 0; r < rows; r+=step)
			{		
				int r1 = r - shoulder, r2 = r + shoulder;
				if (r1 >= 0 && r2 >= 0 && r1 < rows && r2 < rows)
				{	
					len++;
				}
			}
			if (test_x) fprintf(test_x, "%d,0\n", len);
			if (test_y) fprintf(test_y, "%d,0\n", len);

			for (int r = 0; r < rows; r+=step)
			{		
				int r1 = r - shoulder, r2 = r + shoulder;
				if (r1 >= 0 && r2 >= 0 && r1 < rows && r2 < rows)
				{		
					//��������� ����� ������� ���� � ����������
					double dx = X[r1]-X[r2];
					double dy = Y[r1]-Y[r1];
					double dw = sqrt(dx*dx + dy*dy);

					if (test_x) 
						fprintf(test_x, 
						"%7.3f%c"
						"%4.3f"
						"\n",
						X[r], delim, 
						dw					
						);					
					
					if (test_y) 
						fprintf(test_y, 
						"%7.3f%c"
						"%4.3f"
						"\n",
						Y[r], delim, 
						dw					
						);
				}
			}
			if(test_x) fclose(test_x);
			if(test_y) fclose(test_y);
		}


		// ���������� ����� �������
		//for (int r = max_shoulder; r < rows-max_shoulder; r++)
		//for (int r = 0; r < rows; r++)

		for (int r = 0; r < rows; r+=step)
		{		
			vert_korr_points vkp;
			vkp.vkp.clear();

printf("r = %u rows = %d\n", r, rows);
			for (int sh = 0; sh < max_shoulder; sh++)
			{	
				int r1 = r - sh, r2 = r + sh;
				if (r1 >= 0 && r2 >= 0 && r1 < rows && r2 < rows)
				{		
					//��������� ����� ������� ���� � ����������
					/*double dx1 = X[r1 + shoulder]-X[r1 - shoulder];
					double dy1 = Y[r1 + shoulder]-Y[r1 - shoulder];

					double dx2 = X[r2 + shoulder]-X[r2 - shoulder];
					double dy2 = Y[r2 + shoulder]-Y[r2 - shoulder];

					double d1 = sqrt(dx1*dx1 + dy1*dy1);
					double d2 = sqrt(dx2*dx2 + dy2*dy2);*/


					// ��������� ����������� � ������ �� ����
					double m1 = 0.0, m2 = 0.0;
					int n1 = 0, n2 = 0;
					for (int sh = -shoulder; sh <= shoulder; sh++)
					{	
						int i1 = r1 + sh, i2 = r2 + sh;
						if (i1 >= 0 && i1 < rows)
						{
							m1 += v[c1][i1];n1++;
						}								
						if (i2 >= 0 && i2 < rows)
						{
							m2 += v[c2][i2];n2++;
						}
					}
					if (n1) m1 /= n1;
					if (n2) m2 /= n2;

					// ��������� ��������� � ������������������ ���������� � ������ �� ����
					double D1 = 0.0, D2 = 0.0;
					n1=0,n2=0;
					for (int sh = -shoulder; sh <= shoulder; sh++)
					{	
						int i1 = r1 + sh, i2 = r2 + sh;
						if (i1 >= 0 && i1 < rows)
						{
							D1 += (v[c1][i1]-m1)*(v[c1][i1]-m1);
							n1++;
						}								
						if (i2 >= 0 && i2 < rows)
						{
							D2 += (v[c2][i2]-m2)*(v[c2][i2]-m2);
							n2++;
						}
					}
					if (n1) D1 /= n1;
					if (n2) D2 /= n2;

					double sigma1 = sqrt(D1);
					double sigma2 = sqrt(D2);
					// ������������ �������������� �����������
					double K_r1_r2_c1_c2 = 0.0;
					int n = 0;
					for (int sh = -shoulder; sh <= shoulder; sh++)
					{	
						int i1 = r1 + reverse1*sh, i2 = r2 + reverse2*sh;
						if (i1 >= 0 && i2 >= 0 && i1 < rows && i2 < rows)
						{
							K_r1_r2_c1_c2 += (v[c1][i1] - m1) * (v[c2][i2] - m2);
							n++;
						}
					}
					if(n) K_r1_r2_c1_c2 /= n;

					double k_r1_r2_c1_c2 = K_r1_r2_c1_c2 / (sigma1*sigma2);

					// ���������� �������� � ��������� �������
					double x1 = X[r1];
					double x2 = X[r2];
					double y1 = Y[r1];
					double y2 = Y[r2];

					double x = (x1 + x2)/2.0;
					double y = (y1 + y2)/2.0;
					double z = -k*sqrt( 
						(x1 - x2)*(x1 - x2) 
						+
						(y1 - y2)*(y1 - y2) 
						);

					if (stream_corr_ivan) 
						fprintf(stream_corr_ivan, 
						"%7.3f%c%7.3f%c%4.3f"
						"%c%f"
						"\n",
						x, delim, y, delim, z
						, delim, k_r1_r2_c1_c2
						);

					korr_point kp;
					kp.x = x;
					kp.y = y;
					kp.z = z;

					kp.korr_k = k_r1_r2_c1_c2;

					vkp.vkp.push_back(kp);
				}
			}
			(*vvkp).push_back(vkp);
		}
		fclose(stream_corr_ivan);
		printf("file closed:\n%s\n", lpstrFile);

	}
	else
	{
		printf("can not open file: \n%s\n", lpstrFile);
		ErrorPrint("fopen");
	}
}

void BuildGrid(char * file_grd,
			   vector<double> &vX,			
			   vector<double> &vY,			
			   vector<double> &vZ,			
			   vector<double> &vK,			
			   double xSize, double ySize, double max_glubina, 
			   Collection * pcollection
			   )
{
	//return;
//	profile_interval * current_profile_interval = NULL;
//	int current_profile_number = 0;
//	if (current_profile_number < profile_intervals.size())
//		current_profile_interval = &profile_intervals[current_profile_number];


	COLLEC_TION * pcurrent_fast_collection = NULL;


	CPoint3 pt;
	pt.bVisible = true;
	//Sphere3D prim;
	ThePoint3D prim;


	// �������� ������ ��� �������������� �������
	//double **M = AllocDoubleMat(max_size, (*vvkp).size());
	//double BlankValue = BLANK_VALUE;//1.70141e38;// nodes are blanked if greater or equal to this value

	/*for (size_t R = 0; R < (*vvkp).size(); R++)
	{
		for (size_t i_0 = 0; i_0 < max_size; i_0++)
		{
			M[i_0][R] = BlankValue;
		}
	}
	double min_k = DBL_MAX;
	double max_k = -DBL_MAX;
*/

	vector<double> VX, VY, VZ;// ������� ��� ���������� ������
	double min__x = DBL_MAX, min__y = DBL_MAX, min__z = DBL_MAX;
	double max__x = -DBL_MAX, max__y = -DBL_MAX, max__z = -DBL_MAX;
	///////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////

	for (size_t i = 0; i < vX.size(); i++)
	{
		double 
			x_value = vX[i],
			y_value = vY[i],
			z_value = vZ[i];

		if (z_value > - max_glubina)
		{
			if (min__x > x_value) min__x = x_value;
			if (min__y > y_value) min__y = y_value;
			if (min__z > z_value) min__z = z_value;

			if (max__x < x_value) max__x = x_value;
			if (max__y < y_value) max__y = y_value;
			if (max__z < z_value) max__z = z_value;
		}
	}

	double delta__x = max__x - min__x;
	double delta__y = max__y - min__y;

	vector<double> *pVX;
	double min_x, min_y;
	double max_x, max_y;

	if (delta__x > delta__y)
	{
		//������� �� x
		max_x = max__x;
		min_x = min__x;
		pVX = &vX;
	}
	else
	{
		//������� �� y
		max_x = max__y;
		min_x = min__y;
		pVX = &vY;
	}

	max_y = max__z;
	min_y = min__z;


/*	sprintf(file_grd, "%s\\corr_ivan_%s_%s sym %d.grd", 	
		current_profile_interval ? current_profile_interval->dir : dir_out,
		(*pnames_of_colomns)[original_col_numbers[c1]].c_str(),
		(*pnames_of_colomns)[original_col_numbers[c2]].c_str(),
		reverse1 * reverse2
		);

	char * p;
	while (p=strchr (file_grd,'\"'))
	{
		*p = '_';
	}*/
	printf("try to open file %s\n", file_grd);

	if (pcollection)
	{			
		COLLEC_TION current_fast_collection;
		SurfDoc * doc = (SurfDoc*)pcollection->GetDoc();
		current_fast_collection.InitDoc(doc);
		current_fast_collection.SetName(file_grd);
//		if (current_profile_interval)
//			current_fast_collection.
//			SetLayer(current_profile_interval->layer);
		pcurrent_fast_collection = 
			dynamic_cast<COLLEC_TION *>(pcollection->AddObject(&current_fast_collection));
	}
	else
		printf("NOT pcollection on DoVerticalCorrelation !!!!!!!!!!!!!!!\n");
	if (pcurrent_fast_collection)
		prim.InitDoc((SurfDoc*)pcurrent_fast_collection->GetDoc());
	///////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////


	//����� ��������� ����
	Grid grid;
	grid.gridSection.nCol = (long)(max_x-min_x)/xSize + 1;
	grid.gridSection.nRow = (long)(max_y-min_y)/ySize + 1;
	grid.gridSection.xLL = min_x;
	grid.gridSection.yLL = min_y;

	grid.gridSection.xSize = (max_x-min_x) / (grid.gridSection.nCol - 1);
	grid.gridSection.ySize = (max_y-min_y) / (grid.gridSection.nRow - 1);
#if 1
	griddata_2_param param;
	param.max_len = 8;
	param.dist_fun_number = 2;
	param.pw = 3.0;
	param.delta_phi = 45.0;

	griddata_2(NULL, *pVX, vZ, vK, &grid, &param);
#else
	griddata_3_param param;
	FillDefaultParam(param);
	griddata_3(NULL, VX, VY, VZ, &grid, &param);

#endif
	SaveAsSurfer7Grid(file_grd, &grid);
	FreeDoubleMat(grid.gridSection.z);


#if 0
if (pcurrent_fast_collection)
{
	COLORREF color = 0;
	// ����� �� ��������� ��������� ��������
	double color_part = (k_0_1 + 1.0) / 2.0;

	if(pcurrent_fast_collection->GetDoc())
	{
		color = ((SurfDoc*)pcurrent_fast_collection->GetDoc())->m_palette.GetColor(color_part);
	}

	pt.x = vkp_0.vkp[ind].x;
	pt.y = vkp_0.vkp[ind].y;
	pt.z = vkp_0.vkp[ind].z;

	prim.InitPoint(pt,color);
	pcurrent_fast_collection->AddObject(&prim);
}
#endif



	printf("\n");
	if (pcurrent_fast_collection)
		pcurrent_fast_collection->InitObjectList();

}



void BuildGrid(short crd_type,// 0 - x, 1 - y, 2 - profile_len
			   short value_type,// 1 - korr_k;  // ����������� �������������� ����������
								// 2 - korr_k2; // ����������� ������������ ���������� � �������������� �������� �������
								// 3 - korr_k3; // ����������� ������������ ��������������				
			   Collection * pcollection,
			   vector<vert_korr_points> * vvkp,
			   vector<profile_interval> & profile_intervals,
			   vector<string> * pnames_of_colomns,
			   vector<size_t>& original_col_numbers, 
			   double xSize, double ySize, double max_glubina, 
			   size_t c1, size_t c2,
			   int reverse1, int reverse2)
{
	return;
	profile_interval * current_profile_interval = NULL;
	int current_profile_number = 0;
	if (current_profile_number < profile_intervals.size())
		current_profile_interval = &profile_intervals[current_profile_number];


	COLLEC_TION * pcurrent_fast_collection = NULL;


	CPoint3 pt;
	pt.bVisible = true;
	//Sphere3D prim;
	ThePoint3D prim;


	// �������� ������ ��� �������������� �������
	//double **M = AllocDoubleMat(max_size, (*vvkp).size());
	//double BlankValue = BLANK_VALUE;//1.70141e38;// nodes are blanked if greater or equal to this value

	/*for (size_t R = 0; R < (*vvkp).size(); R++)
	{
		for (size_t i_0 = 0; i_0 < max_size; i_0++)
		{
			M[i_0][R] = BlankValue;
		}
	}
	double min_k = DBL_MAX;
	double max_k = -DBL_MAX;
*/

	vector<double> VX, VY, VZ;// ������� ��� ���������� ������
	double min_x = DBL_MAX, min_y = DBL_MAX;
	double max_x = -DBL_MAX, max_y = -DBL_MAX;
	///////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////

	char file_grd[2048];

	sprintf(file_grd, "%s\\corr_ivan_%s_%s sym %d.grd", 	
		current_profile_interval ? current_profile_interval->dir : dir_out,
		(*pnames_of_colomns)[original_col_numbers[c1]].c_str(),
		(*pnames_of_colomns)[original_col_numbers[c2]].c_str(),
		reverse1 * reverse2
		);

	char * p;
	while (p=strchr (file_grd,'\"'))
	{
		*p = '_';
	}
	printf("try to open file %s\n", file_grd);

	if (pcollection)
	{			
		COLLEC_TION current_fast_collection;
		SurfDoc * doc = (SurfDoc*)pcollection->GetDoc();
		current_fast_collection.InitDoc(doc);
		current_fast_collection.SetName(file_grd);
		if (current_profile_interval)
			current_fast_collection.
			SetLayer(current_profile_interval->layer);
		pcurrent_fast_collection = 
			dynamic_cast<COLLEC_TION *>(pcollection->AddObject(&current_fast_collection));
	}
	else
		printf("NOT pcollection on DoVerticalCorrelation !!!!!!!!!!!!!!!\n");
	if (pcurrent_fast_collection)
		prim.InitDoc((SurfDoc*)pcurrent_fast_collection->GetDoc());
	///////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////

	size_t ROWS = (*vvkp).size();
	int printed_progress = 0;
	double progress_len = 80;
	printf("\n");
	for (size_t R = 0; R < ROWS; R++)
	{
		//printf("R = %d ROWS = %d\n", R, ROWS);
		double progress_part =  progress_len * double(R) / double(ROWS);
		int to_print_progress = int(progress_part - printed_progress);
		for(int pp = 0; pp < to_print_progress; pp++)
		{
			printed_progress++;
			printf("#");
		}

		// �������� ���� ��� ������ � ��������� ��� 3� ���� �� ��������� �� ����� �������
		if (current_profile_interval)
		{
			if (R == current_profile_interval->i2)
			{
				//����� ��������� ����
				Grid grid;
				grid.gridSection.nCol = (long)(max_x-min_x)/xSize;
				grid.gridSection.nRow = (long)(max_y-min_y)/ySize;
				grid.gridSection.xLL = min_x;
				grid.gridSection.yLL = min_y;

				grid.gridSection.xSize = (max_x-min_x) / grid.gridSection.nCol;
				grid.gridSection.ySize = (max_y-min_y) / grid.gridSection.nRow;
#if 1
				griddata_2_param param;
				param.max_len = 8;
				param.dist_fun_number = 2;
				param.pw = 3.0;
				param.delta_phi = 45.0;

				griddata_2(NULL, VX, VY, VZ, &grid, &param);
#else
				griddata_3_param param;
				param.ftf = 0;
				param.order_t = 3;
				param.order_c = 2;

				//param.row_weight = 1.0;
				param.alpha_t0 = 0.0;
				param.alpha_t1 = 0.0;					
				param.alpha_c0 = 0.0;
				param.alpha_c1 = 0.0;					
				param.dij = 0;

				griddata_3(NULL, VX, VY, VZ, &grid, &param);

#endif
				SaveAsSurfer7Grid(file_grd, &grid);
				FreeDoubleMat(grid.gridSection.z);

				current_profile_number++;

				VX.clear(), VY.clear(), VZ.clear();// ������� ��� ���������� ������
				min_x = DBL_MAX, min_y = DBL_MAX;
				max_x = -DBL_MAX, max_y = -DBL_MAX;

				if (current_profile_number < profile_intervals.size())
				{
					current_profile_interval = &profile_intervals[current_profile_number];

					sprintf(file_grd, "%s\\corr_ivan_%s_%s sym %d i_1 = %04d.dat", 	
						current_profile_interval ? current_profile_interval->dir : dir_out,
						(*pnames_of_colomns)[original_col_numbers[c1]].c_str(),
						(*pnames_of_colomns)[original_col_numbers[c2]].c_str(),
						reverse1 * reverse2
						);

					char * p;
					while (p=strchr (file_grd,'\"'))
					{
						*p = '_';
					}

					if (pcollection)
					{			
						COLLEC_TION current_fast_collection;
						SurfDoc * doc = (SurfDoc*)pcollection->GetDoc();
						current_fast_collection.InitDoc(doc);
						current_fast_collection.SetName(file_grd);
						if (current_profile_interval)
							current_fast_collection.
							SetLayer(current_profile_interval->layer);
						pcurrent_fast_collection = 
							dynamic_cast<COLLEC_TION *>(pcollection->AddObject(&current_fast_collection));
					}
					else
						printf("NOT pcollection on DoVerticalCorrelation !!!!!!!!!!!!!!!\n");
				}
			}
		}

		// ������ �� �������
		vert_korr_points& vkp_0  = (*vvkp)[R];

		//����� ��������
		size_t len0 = vkp_0.vkp.size();	

		//������������ ���������� �������������� ������� 
		for (int i = 0; i < len0; i++)
		{
			double y_value = vkp_0.vkp[i].z;
			if (y_value > - max_glubina)
			{
				VY.push_back(y_value);

				double value = 0.0;
				switch(value_type)
				{
				case 1:
					value = vkp_0.vkp[i].korr_k;
					break;
				case 2:
					value = vkp_0.vkp[i].korr_k2;
					break;
				case 3:
					value = vkp_0.vkp[i].korr_k3;
					break;
				}
				VZ.push_back(value);

				double x_value;

				switch(crd_type)
				{
				case 0://x
					{
						x_value = vkp_0.vkp[i].x;
					}
					break;
				case 1://y
					{
						x_value = vkp_0.vkp[i].y;
					}
					break;
				}

				VX.push_back(x_value);

				if (min_x > x_value) min_x = x_value;
				if (min_y > y_value) min_y = y_value;

				if (max_x < x_value) max_x = x_value;
				if (max_y < y_value) max_y = y_value;
			}

#if 0
			if (pcurrent_fast_collection)
			{
				COLORREF color = 0;
				// ����� �� ��������� ��������� ��������
				double color_part = (k_0_1 + 1.0) / 2.0;

				if(pcurrent_fast_collection->GetDoc())
				{
					color = ((SurfDoc*)pcurrent_fast_collection->GetDoc())->m_palette.GetColor(color_part);
				}

				pt.x = vkp_0.vkp[ind].x;
				pt.y = vkp_0.vkp[ind].y;
				pt.z = vkp_0.vkp[ind].z;

				prim.InitPoint(pt,color);
				pcurrent_fast_collection->AddObject(&prim);
			}
#endif
		}
	}



	printf("\n");
	if (pcurrent_fast_collection)
		pcurrent_fast_collection->InitObjectList();
#if 0
	// 
	Grid grid;
	grid.gridSection.z = M;
	grid.gridSection.nCol = (*vvkp).size();
	grid.gridSection.nRow = max_size;
	grid.gridSection.xLL = 0.0;
	grid.gridSection.yLL = 0.0;
	grid.gridSection.xSize = 1.0;
	grid.gridSection.ySize = 1.0;
	grid.gridSection.zMax = max_k;
	grid.gridSection.zMin = min_k;

	grid.faultSection.nTraces = 0;
	grid.faultSection.nVertices = 0;
	grid.faultSection.traces = NULL;
	grid.faultSection.vertexes = NULL;


	//
	char file[2048];
	sprintf(file, "%s\\corr_ivan_%s_%s_sym_%d i_1 = %04d.grd", dir_out,
		(*pnames_of_colomns)[original_col_numbers[c1]].c_str(),
		(*pnames_of_colomns)[original_col_numbers[c2]].c_str(),
		reverse1 * reverse2,
		i_1
		);
	while (p=strchr (file,'\"'))
	{
		*p = '_';
	}
	SaveAsSurferGrid7(file, &grid);
#endif
	// ������� �������������� �������


}
#endif /*!VIEW_ONLY_VERSION*/
