// PolyotyNnetDlg.cpp: implementation of the PolyotyNnetDlg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PolyotyNnetDlg.h"
#include "PolyotyNnetDlg.h"
#include "../../array/src/sorting.h"
#include "../../tools/src/filedlg.h"
#include "../../array/src/vdouble.h"
#include "../../array/src/interp.h"

#include "../../winplot/src/winplot.h"
#include "../../wintools/src/winsurf.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern HINSTANCE hInst;   // текущий экземпляр
extern int importFileForNNet(LPPOLYOTYFILEDLGDATA lpPolyotyDlgData, vector<vector<double> > *pvectors, vector<string> * pnames);
extern char directory[255];
//extern HRESULT SaveFileDlg(HWND hWnd, LPTSTR lpstrFile, const TCHAR filter[], DWORD& nFilterIndex);
extern LRESULT CALLBACK DlgProcPolyoty( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam );

LRESULT CALLBACK DlgProcPolyotyForNnet( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static PolyotyNnetDlg * pol_nnet_dlg;

	switch( uMsg )
		
	{
    case WM_INITDIALOG :
		{
			pol_nnet_dlg = reinterpret_cast<PolyotyNnetDlg *>(lParam);
			pol_nnet_dlg->hDlg = hDlg;
			pol_nnet_dlg->OnInitDialog();
		}
		break;
    case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{
		case IDC_RADIO_POLYOTY_KOHONEN_AND:
			{
				pol_nnet_dlg->m_extremums_filter_type = 0;
			}
			break;
		case IDC_RADIO_POLYOTY_KOHONEN_OR:
			{
				pol_nnet_dlg->m_extremums_filter_type = 1;
			}
			break;
		case IDC_BUTTON_MOVING_AVERANGE:
			{
				pol_nnet_dlg->OnButtonMovingAverange(wParam,lParam);
			}
			break;
		case IDC_BUTTON_VISUALISATION_OF_PROFILES2:
			{
				SendMessage(hDlg, WM_COMMAND, IDC_BUTTON_PROFILES_SUMMING, 1);
			}
			break;
		case IDC_BUTTON_VISUALISATION_OF_PROFILES3:
			{
				pol_nnet_dlg->OnButtonVisualAllProfiles(wParam,lParam);
			}
			break;
		case IDC_BUTTON_VISUALISATION_OF_PROFILES:
			{
				pol_nnet_dlg->OnButtonVisualProfiles(wParam,lParam);
			}
			break;
		case IDC_BUTTON_SORT_PROFILES:
			{
				pol_nnet_dlg->SortProfiles();
			}
			break;
		case IDC_BUTTON_KOHONEN_INPUT2:
			{
				pol_nnet_dlg->OnButtonKohonen2();
			}
			break;
		case IDC_BUTTON_KOHONEN_INPUT3:
			{
				pol_nnet_dlg->OnButtonKohonen4();
			}
			break;
		case IDC_BUTTON_POLYOTY_KOHONEN_1_PARAM_PICK_LEN:
			{
				pol_nnet_dlg->OnButtonKohonen2(1);
			}
			break;
		case IDC_BUTTON_POLYOTY_KOHONEN_3_PARAM_PICK_LEN:
			{
				pol_nnet_dlg->OnButtonKohonen(1);
			}
			break;
		case IDC_BUTTON_KOHONEN_INPUT:
			{
				pol_nnet_dlg->OnButtonKohonen();
			}
			break;
		case IDC_BUTTON1:
			{
				pol_nnet_dlg->Test();
			}
			break;
		case IDC_BUTTON_PROFILES_SUMMING:
			{
				pol_nnet_dlg->OnButtonProfileSumming(wParam,lParam);
			}
			break;			
		case IDOK :
			{
				pol_nnet_dlg->OnButtonOK();
			}
			break;
		case IDCANCEL :
			{
//				hDlgModeless = NULL;
				EndDialog( hDlg, IDCANCEL );
			}
			break;
		}
		break;
		case WM_DESTROY :
			{
				pol_nnet_dlg->OnDestroy();
			}
			break;
		default :
			return( FALSE );
	}
	return( TRUE );
}


PolyotyNnetDlg::PolyotyNnetDlg(LPPOLYOTYFILEDLGDATA lpPolyotyDlgData)
{
	m_lpPolyotyDlgData = lpPolyotyDlgData;
	khd = NULL;
	
	DialogBoxParam( 
	   hInst, 
	   MAKEINTRESOURCE(IDD_DIALOG_FILE_POLYOTY_FOR_NNET), 
	   NULL,
	   (DLGPROC)DlgProcPolyotyForNnet,
	   (LPARAM)this);

}

PolyotyNnetDlg::~PolyotyNnetDlg()
{

}

void PolyotyNnetDlg::OnInitDialog()
{
#if 0
			ix = 0;
			iy = 1;
#else
			ix = 2;
			iy = 3;
#endif
			pvectors = new vector<vector<double> >;
			pdrills = new vector<vector<double> >;
			pline_cutting_vector_sorted = new vector<cut_of_line>;
			pnames = new vector<string>;


			importFileForNNet(m_lpPolyotyDlgData, pvectors, pnames);
			
			m_extremums_filter_type = 0;
			switch (m_extremums_filter_type)
			{
			case 0:
				CheckRadioButton( hDlg,
					IDC_RADIO_POLYOTY_KOHONEN_AND,
					IDC_RADIO_POLYOTY_KOHONEN_OR,
					IDC_RADIO_POLYOTY_KOHONEN_AND);
				break;
			case 1:
				CheckRadioButton( hDlg,
					IDC_RADIO_POLYOTY_KOHONEN_AND,
					IDC_RADIO_POLYOTY_KOHONEN_OR,
					IDC_RADIO_POLYOTY_KOHONEN_OR);
				break;
			}		

			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@			
			SendDlgItemMessage( hDlg, IDC_COMBO_POLYOTY_KOHONEN_NPOINTS, CB_RESETCONTENT, 0,0);
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			for (int j = 3; j < 10; j++)
			{
				string s;s.resize(8);
				sprintf((char *)s.data(), "%d", j);
				SendDlgItemMessage( hDlg, IDC_COMBO_POLYOTY_KOHONEN_NPOINTS, CB_ADDSTRING, 0,
					(LPARAM)(LPCTSTR)s.c_str());
/*				char s[8];;
				sprintf(s, "%d", j);
				SendDlgItemMessage( hDlg, IDC_COMBO_POLYOTY_KOHONEN_NPOINTS, CB_ADDSTRING, 0,
					(LPARAM)(LPCTSTR)s);*/
			}
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_POLYOTY_KOHONEN_NPOINTS, CB_SETCURSEL,
				0,(LPARAM)0 );
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@			
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@			
			SendDlgItemMessage( hDlg, IDC_COMBO_POLYOTY_COLS_NAMES, CB_RESETCONTENT, 0,0);
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			for (size_t j = 0; j < pnames->size(); j++)
			{
				SendDlgItemMessage( hDlg, IDC_COMBO_POLYOTY_COLS_NAMES, CB_ADDSTRING, 0,
					(LPARAM)(LPCTSTR)pnames->operator [](j).c_str());
			}
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_POLYOTY_COLS_NAMES, CB_SETCURSEL,
				4,(LPARAM)0 );
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@			
			// MessageBox(0, lpPolyotyDlgData->filename, "filename", 0);

			char buffer[16];
			// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			for (int i = 1; i < 5; i++)
				SendDlgItemMessage( hDlg, IDC_COMBO_N_SUM_PROFILES, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)itoa(2*i+1,buffer, 10));
			// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_N_SUM_PROFILES, CB_SETCURSEL,
				0,(LPARAM)0 );
			// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		   LRESULT lResult = SendMessage(      // returns LRESULT in lResult 
			   (HWND) GetDlgItem( hDlg, IDC_SPIN_MOVING_AVERANGE),      // handle to destination control  
			   (UINT) UDM_SETBUDDY,      // message ID   
			   (WPARAM) GetDlgItem( hDlg, IDC_EDIT_MOVING_AVERANGE),      // = (WPARAM) (HWND) hwndBuddy; 
			   (LPARAM) 0      // = 0; not used, must be zero 
			   );  
		   //set the min and max range of the up/down or spin control
			SendMessage(
				// returns LRESULT in lResult 
				(HWND) GetDlgItem( hDlg, IDC_SPIN_MOVING_AVERANGE),      // handle to destination control
				(UINT) UDM_SETRANGE32,      // message ID  
				(WPARAM) 1,      // = (WPARAM) (int) iLow;  
				(LPARAM) 100      // = (LPARAM) (int) iHigh; 
				);  
			SendMessage(      // returns LRESULT in lResult   
				(HWND) GetDlgItem( hDlg, IDC_SPIN_MOVING_AVERANGE),      // handle to destination control    
				(UINT) UDM_SETPOS,      // message ID    
				(WPARAM) 0,      // = 0; not used, must be zero   
				(LPARAM) MAKELONG ((short) 5, 0)      // = (LPARAM) MAKELONG ((short) nPos, 0)
				);  
			SendMessage(hDlg, WM_COMMAND, IDC_BUTTON_SORT_PROFILES, 1);

}

void PolyotyNnetDlg::OnButtonMovingAverange(WPARAM wParam, LPARAM lParam)
{

				WinPlot( (*pvectors)[ix],  (*pvectors)[iy]);
				//###########################################################

				int Cols = (*pvectors).size();
				int Len = (*pvectors)[ix].size();
				Vector<Vector<vdouble > > vvv;
				vvv.resize(Cols);
				for (int C = 0; C < Cols; C++)
				{
					vvv[C].resize(n_profiles);
				}
				// base length of moving averange
				BOOL lpTranslated;
				int ma_base = GetDlgItemInt(hDlg, IDC_EDIT_MOVING_AVERANGE, &lpTranslated, false);
				for (int j = 0; j < n_profiles; j++)
				{
					int len = (*pline_cutting_vector_sorted)[j].i_finish 
						- (*pline_cutting_vector_sorted)[j].i_start;

					for (int C = 0; C < Cols; C++)
					{
						vvv[C][j].resize(len - ma_base + 1, 0.0);
					}
					//##############################
					for(int i = 0; i < len - ma_base + 1; i++)
					{
						for (int b = 0; b < ma_base; b++)
						{
							for (int C = 0; C < Cols; C++)
							{
								vvv[C][j][i] += (*pvectors)[C][(*pline_cutting_vector_sorted)[j].i_start+i+b];
							}
						}
						for (int C = 0; C < Cols; C++)
						{
							vvv[C][j][i] /= ma_base;
						}
					}
					//##############################						
				}
				for (int C = iy + 1; C < Cols; C++)
				{
					WinSurf( 
						vvv[ix],  
						vvv[iy],  
						vvv[C]);
				}
				//==============================================
				TCHAR filter[] =     TEXT("Text database file (*.dat)\0*.dat\0")
									 TEXT("Text database file (*.txt)\0*.txt\0")
									 TEXT("All Files (*.*)\0*.*\0");
				TCHAR lpstrFile[512];

				sprintf(lpstrFile, "%s\\%s_ma%d", directory, m_lpPolyotyDlgData->filename, ma_base);
				DWORD nFilterIndex = 0;
				if (SaveFileDlg(0, lpstrFile, filter, nFilterIndex) == S_OK)
				{
					FILE *stream;
					stream = fopen(lpstrFile,"wt");

					for (int j = 0; j < n_profiles; j++)
					{
						for(int i = 0; i < vvv[0][j].Length(); i++)
						{
							for( int C = 0; C < 2; C++)
							{
								fprintf(stream, "%d\t",	int(vvv[C][j][i]));
							}
							for(int C = 2; C < Cols; C++)
							{
								fprintf(stream, "%f\t",	vvv[C][j][i]);
							}
							fprintf(stream, "\n");
						}
					}
					fclose (stream);
				}

}

void PolyotyNnetDlg::OnButtonVisualAllProfiles(WPARAM wParam, LPARAM lParam)
{
				WinSurf(*pline_cutting_vector_sorted, 
					ix,  
					iy,  
					(*pvectors));

}

void PolyotyNnetDlg::OnButtonVisualProfiles(WPARAM wParam, LPARAM lParam)
{
				for (int col = iy + 1; col < pvectors->size(); col++)
				{
					WinSurf(*pline_cutting_vector_sorted, 
						(*pvectors)[ix],  
						(*pvectors)[iy],  
						(*pvectors)[col]);
				}

}

void PolyotyNnetDlg::SortProfiles()
{
				WinPlot( (*pvectors)[ix],  (*pvectors)[iy]);
				//###########################################################
				int u, prof;
				vector<cut_of_line> line_cutting_vector;
				cut_of_line line_cutting;
				line_cutting.i_start = 0;

				if ((*pvectors)[0].size())
				{
					u = int((*pvectors)[0][0]);
					prof = int((*pvectors)[1][0]);
					int i = 0;
					for (; i < (*pvectors)[0].size(); i++)
					{
						if (					
							u != int((*pvectors)[0][i]) ||
							prof != int((*pvectors)[1][i]))
						{
							u = int((*pvectors)[0][i]);
							prof = int((*pvectors)[1][i]);
							//##############################
							//lines_break_indexes.push_back(i);
							line_cutting.i_finish = i;
							line_cutting_vector.push_back(line_cutting);
							line_cutting.i_start = i;
							//##############################
						}
					}
					//==============================================
					line_cutting.i_finish = i;
					line_cutting_vector.push_back(line_cutting);
					//==============================================
				}
				n_profiles = line_cutting_vector.size();
				//###########################################################
				//int Len = (*pvectors)[ix].size();
				vector<double> xmean, ymean;
				for (int j = 0; j < n_profiles; j++)
				{
					int len = line_cutting_vector[j].i_finish 
						- line_cutting_vector[j].i_start;

					vdouble x,y;						
					x.resize(len);
					y.resize(len);

					//##############################
					for(int i = 0, ii = line_cutting_vector[j].i_start; ii < line_cutting_vector[j].i_finish; i++, ii++)
					{
						x[i] = (*pvectors)[ix][ii];
						y[i] = (*pvectors)[iy][ii];
					}
					//##############################
					double 
						maxx = x.Max(),
						minx = x.Min(),
						maxy = y.Max(),
						miny = y.Min(),
						delta_x = maxx-minx,
						delta_y = maxy-miny;

					//##############################
					if (delta_x > delta_y) //may be y = const
					{
						ymean.push_back(y.Median());
					}
					else // may be x = const
					{
						xmean.push_back(x.Median());
					}
					//##############################
				}
				//###########################################################
				index_for_sort * ifs = new index_for_sort[n_profiles];
				if (xmean.size() > ymean.size())
				{
					for (int I = 0; I < n_profiles; I++)
					{
						ifs[I].i		= I;
						ifs[I].sort_val	= xmean[I];
					}	
				}
				else
				{
					for (int I = 0; I < n_profiles; I++)
					{
						ifs[I].i		= I;
						ifs[I].sort_val	= ymean[I];
					}	
				}
				qsort( (void *)ifs, (size_t)n_profiles, sizeof(index_for_sort), compare_index_for_sort );
				//###########################################################
				pline_cutting_vector_sorted->resize(0);
				for (int j = 0; j < n_profiles; j++)
				{
					pline_cutting_vector_sorted->push_back(line_cutting_vector[ifs[j].i]);
				}
				//###########################################################
				delete [] ifs;

}
void PolyotyNnetDlg::OnButtonKohonen4()
{
	// Using only extremums of measure points
	//###########################################################
	int Cols = (*pvectors).size();
	int nParameters = Cols - iy - 1;

	int Len = (*pvectors)[ix].size();

	int cl;

	nParameters = 0;

	int points_per_image = 3 + SendDlgItemMessage( hDlg, IDC_COMBO_POLYOTY_KOHONEN_NPOINTS, CB_GETCURSEL,0,(LPARAM)0 );
	int nnetParameters = points_per_image;
	nnetParameters = 3;

	// число образов
	int nImages = Len;
	
	double * ImX = new double [nImages];
	double * ImY = new double [nImages];
	
	double **M = AllocDoubleMat(nImages, nnetParameters);	

	bool bScale = IsDlgButtonChecked( hDlg, IDC_CHECK_POLYOTY_KOHONEN_TOSCALE) 
		== BST_CHECKED;

	cl = SendDlgItemMessage( hDlg, IDC_COMBO_POLYOTY_COLS_NAMES, CB_GETCURSEL,0,(LPARAM)0 );
	int j = 0;
	for ( int i = 1; i < Len-1; i++ )//fixme
	{
		
		bool take;
		switch(m_extremums_filter_type)
		{
		case 0://and
			{
				take = true;
			}
			break;
		case 1://or
			{
				take = false;
			}
			break;
		}
		
		for (int tcol = cl; tcol < Cols && tcol < cl+3; tcol++)
		{
			bool bmax = (*pvectors)[tcol][i] > (*pvectors)[tcol][i-1] && (*pvectors)[tcol][i] > (*pvectors)[tcol][i+1];
			bool bmin = (*pvectors)[tcol][i] < (*pvectors)[tcol][i-1] && (*pvectors)[tcol][i] < (*pvectors)[tcol][i+1];
			switch(m_extremums_filter_type)
			{
			case 0://and
				{
					take = take && (bmax || bmin);
				}
				break;
			case 1://or
				{
					take = take || (bmax || bmin);
				}
				break;
			}
		}
		if ( take )
		{		
			//###################################################################
			ImX[j] = (*pvectors)[ix][i];
			ImY[j] = (*pvectors)[iy][i];
			for (int c = 0, col = cl; c < nnetParameters && col < Cols; c++, col++)
			{
				M[j][c] = (*pvectors)[col][i];
			}
			if (bScale)
				Scale(nnetParameters, M[j]);
			j++;
		}
	}
	//###################################################################
	string title;

	title = 
		pnames->operator [](cl  )+
		pnames->operator [](cl+1)+
		pnames->operator [](cl+2);

	if (bScale)
		title += "_scaled";
				
	if (khd != NULL) delete khd;		// how to safely release the memory...
	khd = new KohonenDlg(j, ImX, ImY, NULL, nnetParameters, M, title);		// ...right after the dialog is closed?


	if (IsDlgButtonChecked( hDlg, IDC_CHECK_POLYOTY_KOHONEN_IZO_SPHERE) == BST_CHECKED)
	{
		vdouble x,y,z;
		int J = j;
		x.resize(J);
		y.resize(J);
		z.resize(J);
		for (j = 0; j < J; j++)
		{
			x[j] = M[j][0];
			y[j] = M[j][1];
			z[j] = M[j][2];
		}
		WinSurf(x,y,z,1);
	}

	delete [] ImX;
	delete [] ImY;
	FreeDoubleMat(M);

}
void PolyotyNnetDlg::OnButtonKohonen3()
{
	// use all measure points
	//###########################################################
	int Cols = (*pvectors).size();
	int nParameters = Cols - iy - 1;

	int Len = (*pvectors)[ix].size();

	int cl;

	nParameters = 0;

	bool bScale = IsDlgButtonChecked( hDlg, IDC_CHECK_POLYOTY_KOHONEN_TOSCALE) 
		== BST_CHECKED;

	int points_per_image = 3 + SendDlgItemMessage( hDlg, IDC_COMBO_POLYOTY_KOHONEN_NPOINTS, CB_GETCURSEL,0,(LPARAM)0 );
	int nnetParameters = points_per_image;
	nnetParameters = 3;

	// число образов
	int nImages = Len;
	
	double * ImX = new double [nImages];
	double * ImY = new double [nImages];
	
	double **M = AllocDoubleMat(nImages, nnetParameters);

	cl = SendDlgItemMessage( hDlg, IDC_COMBO_POLYOTY_COLS_NAMES, CB_GETCURSEL,0,(LPARAM)0 );
	for ( int i = 0; i < nImages; i++)
	{
		//###################################################################
		ImX[i] = (*pvectors)[ix][i];
		ImY[i] = (*pvectors)[iy][i];
		for (int c = 0, col = cl; c < nnetParameters && col < Cols; c++, col++)
		{
			M[i][c] = (*pvectors)[col][i];
		}		
		if (bScale)
			Scale(nnetParameters, M[i]);
	}
	//###################################################################
				
	if (khd != NULL) delete khd;		// how to safely release the memory...
	khd = new KohonenDlg(nImages, ImX, ImY, NULL, nnetParameters, M, pnames->operator [](cl));		// ...right after the dialog is closed?

	delete [] ImX;
	delete [] ImY;
	FreeDoubleMat(M);
}

void PolyotyNnetDlg::OnButtonKohonen2(int type)
{
	// using shape of picks 
	// cutting picks one parameter
	//###########################################################
	int Cols = (*pvectors).size();
	int nParameters = Cols - iy - 1;

	int Len = (*pvectors)[ix].size();
	bool bScale = IsDlgButtonChecked( hDlg, IDC_CHECK_POLYOTY_KOHONEN_TOSCALE) 
		== BST_CHECKED;


	Vector<vdouble> vx,vy;
	vx.resize(n_profiles);
	vy.resize(n_profiles);
	// складываем отрезки образы для классификации
	vector<vector<cut_of_line> > vv_line_cutting;
	//vector<cut_of_line> v_line_cutting;
	cut_of_line line_cutting;

	vv_line_cutting.resize(nParameters);

	int c = 0, col = iy + 1 + 3;
	nParameters = 0;
	int points_per_image = 3 + SendDlgItemMessage( hDlg, 
		IDC_COMBO_POLYOTY_KOHONEN_NPOINTS, CB_GETCURSEL,0,(LPARAM)0 );

	col = SendDlgItemMessage( hDlg, IDC_COMBO_POLYOTY_COLS_NAMES, CB_GETCURSEL,0,(LPARAM)0 );
	for (int j = 0; j < n_profiles; j++)
	{
		bool start = true;
		//##############################
		for(int i = 0, ii = (*pline_cutting_vector_sorted)[j].i_start;
			ii < (*pline_cutting_vector_sorted)[j].i_finish-1; i++, ii++)
		{
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			if 	(
				( (*pvectors)[col][ii] <= 0 && (*pvectors)[col][ii+1] >= 0.0 )
				||
				( (*pvectors)[col][ii] >= 0 && (*pvectors)[col][ii+1] <= 0.0 )
				)

			{
				if (start)
				{
					start = false;
					line_cutting.i_start = ii;
				}
				else
				{
					start = true;
					line_cutting.i_finish = ii+2;
					if (line_cutting.i_finish - line_cutting.i_start > points_per_image)
					{
//										v_line_cutting.push_back(line_cutting);
						vv_line_cutting[c].push_back(line_cutting);
					}
				}
			}
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		}
		//##############################
	}

	// число образов
	int nImages = vv_line_cutting[c].size();
	double * xIm = new double [nImages];
	double * yIm = new double [nImages];
	double * ImX = new double [nImages];
	double * ImY = new double [nImages];
	
	int nnetParameters = points_per_image;
	double **M = AllocDoubleMat(nImages, nnetParameters);

	for (int j = 0; j < nImages; j++)
	{
		//###################################################################
		int len = vv_line_cutting[c][j].i_finish - vv_line_cutting[c][j].i_start;

		xIm[j] = len;
		double * v = new double [len];
		double * X = new double [len];
		double * Y = new double [len];

		for (int i0 = 0, i = vv_line_cutting[c][j].i_start;
		i < vv_line_cutting[c][j].i_finish; i++, i0++)
		{
			v[i0] = (*pvectors)[col][i];
			X[i0] = (*pvectors)[ix][i];
			Y[i0] = (*pvectors)[iy][i];
		}
		//linterp(int nx, double* py, int nxx, double* pyy)
		linterp(len, v, nnetParameters, M[j]);
		if (bScale) Scale(nnetParameters, M[j]);

		double sum = 0;
		double sumX = 0;
		double sumY = 0;
		for (int i0 = 0; i0 < len; i0++)
		{
			sum  += v[i0];
			sumX += X[i0];
			sumY += Y[i0];
		}
		sum  /= len;
		sumX /= len;
		sumY /= len;

		yIm[j] = sum;
		ImX[j] = sumX;
		ImY[j] = sumY;

		delete [] v;
		delete [] X;
		delete [] Y;
	}
	//###################################################################
				
	if (khd != NULL) delete khd;		// how to safely release the memory...
	switch (type )
	{
	case 0: //shape of picks
		khd = new KohonenDlg(nImages, ImX, ImY, NULL, nnetParameters, M, pnames->operator [](col));		// ...right after the dialog is closed?
		break;
	case 1://lenghes of picks
		khd = new KohonenDlg(nImages, ImX, ImY, NULL, 1, &xIm);		// ...right after the dialog is closed?
		break;
	}
	delete [] xIm;
	delete [] yIm;
	delete [] ImX;
	delete [] ImY;
	FreeDoubleMat(M);
}

void PolyotyNnetDlg::OnButtonKohonen(int type)
{
	// using shape of picks 
	// cutting picks if x or y or z go throu zero
	//###########################################################
	int Cols = (*pvectors).size();
	int nParameters = Cols - iy - 1;

	int Len = (*pvectors)[ix].size();
	int points_per_image = 3 + SendDlgItemMessage( hDlg, IDC_COMBO_POLYOTY_KOHONEN_NPOINTS, CB_GETCURSEL,0,(LPARAM)0 );
	bool bScale = IsDlgButtonChecked( hDlg, IDC_CHECK_POLYOTY_KOHONEN_TOSCALE) 
		== BST_CHECKED;
	int Col = SendDlgItemMessage( hDlg, IDC_COMBO_POLYOTY_COLS_NAMES, CB_GETCURSEL,0,(LPARAM)0 );


	Vector<vdouble> vx,vy;
	vx.resize(n_profiles);
	vy.resize(n_profiles);
	// складываем отрезки образы для классификации
	vector<vector<cut_of_line> > vv_line_cutting;
	vector<cut_of_line> v_line_cutting;
	cut_of_line line_cutting;

	vv_line_cutting.resize(nParameters);
		for (int j = 0; j < n_profiles; j++)
		{
			bool start = true;
			//##############################
			for(int i = 0, ii = (*pline_cutting_vector_sorted)[j].i_start;
				ii < (*pline_cutting_vector_sorted)[j].i_finish-1; i++, ii++)
			{

	for (int c = 0, col = Col; c < 3 && col < Cols; c++, col++)
	{

				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				if 	(
					( (*pvectors)[col][ii] <= 0 && (*pvectors)[col][ii+1] >= 0.0 )
					||
					( (*pvectors)[col][ii] >= 0 && (*pvectors)[col][ii+1] <= 0.0 )
					)

				{
					if (start)
					{
						start = false;
						line_cutting.i_start = ii;
					}
					else
					{
						start = true;
						line_cutting.i_finish = ii+2;
						if (line_cutting.i_finish - line_cutting.i_start > points_per_image)
						{
							v_line_cutting.push_back(line_cutting);
							vv_line_cutting[c].push_back(line_cutting);
						}
					}
				}
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			}
			//##############################
		}

/*					WinSurf(vv_line_cutting[c], 
			ix,  
			iy,  
			(*pvectors));*/

	}
		
		

#if 0
	WinSurf(v_line_cutting, 
		ix,  
		iy,  
		(*pvectors));
#endif
	// число образов
	int nImages = v_line_cutting.size();
	double * xIm = new double [nImages];
	double * yIm = new double [nImages];
	double * ImX = new double [nImages];
	double * ImY = new double [nImages];
	
	nParameters = 1;
	int nnetParameters = points_per_image;
	double **M = AllocDoubleMat(nImages, nnetParameters*3);

	string name;

	for (int j = 0; j < nImages; j++)
	{
		//###################################################################
//					int col = iy + 1 + 3;
		for (int c = 0, col = Col; c < 3 && col < Cols; c++, col++)
//					for (int col = iy + 1; col < cols; col++)
		{
			int len = v_line_cutting[j].i_finish - v_line_cutting[j].i_start;

			xIm[j] = len;
			double * v = new double [len];
			double * X = new double [len];
			double * Y = new double [len];

			for (int i0 = 0, i = v_line_cutting[j].i_start;
			i < v_line_cutting[j].i_finish; i++, i0++)
			{
				v[i0] = (*pvectors)[col][i];
				X[i0] = (*pvectors)[ix][i];
				Y[i0] = (*pvectors)[iy][i];
			}
			//
			linterp(len, v, nnetParameters, &M[j][c*nnetParameters]);
			if (bScale) Scale(nnetParameters, &M[j][c*nnetParameters]);
			double sum = 0;
			double sumX = 0;
			double sumY = 0;
			for (int i0 = 0; i0 < len; i0++)
			{
				sum  += v[i0];
				sumX += X[i0];
				sumY += Y[i0];
			}
			sum  /= len;
			sumX /= len;
			sumY /= len;

			yIm[j] = sum;
			ImX[j] = sumX;
			ImY[j] = sumY;

			delete [] v;
			delete [] X;
			delete [] Y;
			if (j == 0)
			{
				name += pnames->operator [](col);
				if(c != 2) name += "_";
			}
		}
		//###################################################################
	}
	MessageBox(0, name.c_str(), "", 0);

		
	if (khd != NULL) delete khd;		// how to safely release the memory...
//					khd = new KohonenDlg(nImages, ImX, ImY, xIm, yIm);		// ...right after the dialog is closed?

	switch (type )
	{
	case 0: //shape of picks
		khd = new KohonenDlg(nImages, ImX, ImY, NULL, 3*nnetParameters, M, name);		// ...right after the dialog is closed?
		break;
	case 1://lenghes of picks
		khd = new KohonenDlg(nImages, ImX, ImY, NULL, nParameters, &xIm);		// ...right after the dialog is closed?
		break;
	}
	delete [] xIm;
	delete [] yIm;
	delete [] ImX;
	delete [] ImY;
	FreeDoubleMat(M);

}

void PolyotyNnetDlg::Test()
{

				int clusters = 8;     // This many clusters.
				int points = 10;      // Number of points in each cluster.
				// число образов
				int nImages = clusters*points;
				double * xIm = new double [nImages];
				double * yIm = new double [nImages];
				double * ImX = new double [nImages];
				double * ImY = new double [nImages];
				
				int nnetParameters = 10;
				double **M = AllocDoubleMat(nImages, nnetParameters);
				double **C = AllocDoubleMat(clusters, nnetParameters);
				for ( int c = 0; c < clusters; c++)
				{
					for ( int par = 0; par < nnetParameters; par++)
					{
						C[c][par] = Rand(0,1);
					}
				}
				for (int c = 0; c < clusters; c++)
				{
					for ( int par = 0; par < nnetParameters; par++)
					{
						for(int p = 0; p < points; p++)
						{
							M[c*points + p][par] =  C[c][par] + Rand(0.1);
						}
					}
				}
				if (khd != NULL) delete khd;		// how to safely release the memory...
				khd = new KohonenDlg(nImages, ImX, ImY, NULL, nnetParameters, M);		// ...right after the dialog is closed?
				return;
				delete [] xIm;
				delete [] yIm;
				delete [] ImX;
				delete [] ImY;
				FreeDoubleMat(M);
				FreeDoubleMat(C);

}

void PolyotyNnetDlg::OnButtonProfileSumming(WPARAM wParam, LPARAM lParam)
{
				WinPlot( (*pvectors)[ix],  (*pvectors)[iy]);
				//###########################################################
				int Cols = (*pvectors).size();

				int Len = (*pvectors)[ix].size();
				int N = 1+2*(1+SendDlgItemMessage( hDlg, IDC_COMBO_N_SUM_PROFILES, CB_GETCURSEL,0,(LPARAM)0 ));

				Vector<Vector<Vector<double> > > vv;
				vv.resize(n_profiles-N+1);

				for (int J = 0; J < n_profiles-N+1; J++)
				{
						Vector<vdouble> vx,vy;
						vx.resize(2*N);
						vy.resize(2*N);


						int SumLen = 0;
						int u_middle, prof_middle;
						//##############################
						//int i0 = I0;
						for (int j = J, n = 0; j < J+N; j++, n++)
						{
								if (j-J == N/2)
								{
									u_middle	= int ((*pvectors)[0][(*pline_cutting_vector_sorted)[j].i_start]);
									prof_middle = int ((*pvectors)[1][(*pline_cutting_vector_sorted)[j].i_start]);
								}
								int len = (*pline_cutting_vector_sorted)[j].i_finish 
									- (*pline_cutting_vector_sorted)[j].i_start;

								SumLen += len;
								
								vx[n].resize(len);
								vy[n].resize(len);


								//##############################
								for(int i = 0, ii = (*pline_cutting_vector_sorted)[j].i_start; ii < (*pline_cutting_vector_sorted)[j].i_finish; i++, ii++)
								{
									vx[n][i] = (*pvectors)[ix][ii];
									vy[n][i] = (*pvectors)[iy][ii];
								}
								//##############################
								double 
									maxx = vx[n].Max(),
									minx = vx[n].Min(),
									maxy = vy[n].Max(),
									miny = vy[n].Min(),
									delta_x = maxx-minx,
									delta_y = maxy-miny;

								vx[n+N].resize(2);
								vy[n+N].resize(2);

								//##############################
								if (delta_x > delta_y) //may be y = const
								{
									vx[n+N][0] = minx;
									vy[n+N][0] = vy[n].Median();
									vx[n+N][1] = maxx;
									vy[n+N][1] = vy[n+N][0];
								}
								else // may be x = const
								{
									vy[n+N][0] = miny;
									vx[n+N][0] = vx[n].Median();
									vy[n+N][1] = maxy;
									vx[n+N][1] = vx[n+N][0];
								}
								//##############################
						}
						if (lParam == 1)
						{
							WinPlot(vx,vy);
						}
						else
						{
							vv[J].resize( SumLen );
							int I = 0;
							for (; I < SumLen; I++)
							{
								vv[J][I].resize( Cols );
							}
							//##############################
							I = 0;
							for (int j = J, n = 0; j < J+N; j++, n++)
							{
								int len = (*pline_cutting_vector_sorted)[j].i_finish 
									- (*pline_cutting_vector_sorted)[j].i_start;
									
								vx[n].resize(len);
								vy[n].resize(len);


								//##############################
								for(int ii = (*pline_cutting_vector_sorted)[j].i_start; ii < (*pline_cutting_vector_sorted)[j].i_finish; ii++)
								//for(int i = 0; i < len; i++)
								{
									for( int C = 0; C < Cols; C++)
										vv[J][I][C] = (*pvectors)[C][ii];
									//##############################
									vv[J][I][0]		= u_middle;
									vv[J][I][1]		= prof_middle;
									// X as median of middle profile
									vv[J][I][ix]	= vx[N+N/2][0];
									//##############################
									I++;
								}
								//##############################
							}
						}
						//##############################
				}
				if(lParam != 1)
				{
					TCHAR filter[] =     TEXT("Text database file (*.dat)\0*.dat\0")
										 TEXT("Text database file (*.txt)\0*.txt\0")
										 TEXT("All Files (*.*)\0*.*\0");
					TCHAR lpstrFile[512];

					sprintf(lpstrFile, "%s\\%s_sum%dprof", directory, m_lpPolyotyDlgData->filename, N);
					DWORD nFilterIndex = 0;
					if (SaveFileDlg(0, lpstrFile, filter, nFilterIndex) == S_OK)
					{
						FILE *stream;
						stream = fopen(lpstrFile,"wt");

						for (int J = 0; J < n_profiles-N+1; J++)
						{
							int length = vv[J].Size();
							index_for_sort * ifs = new index_for_sort[length];
							int I = 0;
							for (; I < length; I++)
							{
								ifs[I].i		= I;
								ifs[I].sort_val	= vv[J][I][iy];
							}					
							qsort( (void *)ifs, (size_t)length, sizeof(index_for_sort), compare_index_for_sort );
							for ( I = 0; I < length; I++)
							{
								for( int C = 0; C < 2; C++)
								{
									fprintf(stream, "%d\t",	int(vv[J][ifs[I].i][C]));
								}
								for(int C = 2; C < Cols; C++)
								{
									fprintf(stream, "%f\t",	vv[J][ifs[I].i][C]);
								}
								fprintf(stream, "\n");
							}
							delete[] ifs;
						}
						fclose (stream);
					}
				}
//				break;
#if 0
				int i0 = 0;
				for (int j = 0; j < lines_break_indexes.size(); j++)
				{
					if (lines_break_indexes[j] < Len)
					{
						int len = lines_break_indexes[j] - i0;
						vdouble x,y;
						x.resize(len);
						y.resize(len);

						//##############################
						for(int i = 0; i < len; i++)
						{
							y[i] = (*pvectors)[iy][i0+i];
							x[i] = (*pvectors)[ix][i0+i];
						}
						i0 = lines_break_indexes[j];
						//##############################

						double 
							maxx = x.Max(),
							minx = x.Min(),
							maxy = y.Max(),
							miny = y.Min(),
							delta_x = maxx-minx,
							delta_y = maxy-miny;

						vdouble M;
						vdouble v;
						vdouble k;
						M.resize(len,2);
						v.resize(len);
						vdouble X,Y;
						X.resize(2);
						Y.resize(2);

						//##############################
						if (delta_x > delta_y) //may be y = const
						{
#if 0
							for(int i = 0; i < len; i++)
							{
								M(i,0) = x[i];
								M(i,1) = 1.0;
								v[i] =  y[i];
							}
							k = M.Tichonov(v, true);

							// Y = k[0] * X + k[1];
							X[0] = minx;
							Y[0] = k[0] * X[0] + k[1];
							X[1] = maxx;
							Y[1] = k[0] * X[1] + k[1];
#endif
							X[0] = minx;
							Y[0] = y.Median();
							X[1] = maxx;
							Y[1] = Y[0];
						}
						else // may be x = const
						{
#if 0
							for(int i = 0; i < len; i++)
							{
								M(i,0) = y[i];
								M(i,1) = 1.0;
								v[i] =  x[i];
							}
							k = M.Tichonov(v, true);
							// X = k[0] * Y + k[1];
							Y[0] = miny;
							X[0] = k[0] * Y[0] + k[1];
							Y[1] = maxy;
							X[1] = k[0] * Y[1] + k[1];
#endif
							Y[0] = miny;
							X[0] = x.Median();
							Y[1] = maxy;
							X[1] = X[0];
						}
						//##############################
						Vector<vdouble> vx,vy;
						vx.resize(2);
						vy.resize(2);
						vx[0].resize(len);
						vy[0].resize(len);
						for( i = 0; i < len; i++)
						{
							vx[0][i] = x[i];
							vy[0][i] = y[i];
						}
						vx[1].resize(2);
						vy[1].resize(2);
						for( i = 0; i < 2; i++)
						{
							vx[1][i] = X[i];
							vy[1][i] = Y[i];
						}

						WinPlot(vx,vy);

						
					}
				}

				break;


				if (OpenFileDlg(hDlg, "drills\0*.*\0Text\0*.TXT\0") == S_OK)
					DialogBoxParam( hInst, MAKEINTRESOURCE(IDD_DIALOG_FILE_POLYOTY), hDlg,
						(DLGPROC)DlgProcPolyoty,(LPARAM)lpPolyotyDlgData);

				importFileForNNet(lpPolyotyDlgData, pdrills);

				int ndril_colls = (*pdrills).size();
				if (ndril_colls == 0)
				{
					MessageBox(0,"ndril_colls == 0","",0);
					return 0;
				}
#if 0
				int ixd = 2;
				int iyd = 3;
#else
				int ixd = 1;
				int iyd = 2;
#endif



				//======================================================
				//======================================================
				//======================================================
				DelaunayTriangulation dct;
				// Delaunay Triangulation of well coordinates
				dct.main((*pdrills)[ixd],(*pdrills)[iyd]);
				//======================================================
				//======================================================
				//======================================================
#endif

}

void PolyotyNnetDlg::OnButtonOK()
{
				WinPlot( (*pvectors)[ix],  (*pvectors)[iy]);

				if (OpenFileDlg(hDlg, "drills\0*.*\0Text\0*.TXT\0") == S_OK)
					DialogBoxParam( hInst, MAKEINTRESOURCE(IDD_DIALOG_FILE_POLYOTY), hDlg,
						(DLGPROC)DlgProcPolyoty,(LPARAM)m_lpPolyotyDlgData);

				importFileForNNet(m_lpPolyotyDlgData, pdrills, pnames);

				int ndril_colls = (*pdrills).size();
				if (ndril_colls == 0)
				{
					MessageBox(0,"ndril_colls == 0","",0);
					return;
				}
				TCHAR lpstrFile[256];
				TCHAR filter[] = 
					//TEXT("Golden Software Blanking (*.bln) (*.bln)\0*.bln\0")									 
					TEXT("Golden Software Data (*.dat)\0*.dat\0")									
					TEXT("All Files (*.*)\0*.*\0");
				sprintf(lpstrFile, "%s\\NnetInput.dat", directory);
				DWORD nFilterIndex = 0;
				if (SaveFileDlg(hDlg, lpstrFile, filter, nFilterIndex) != S_OK)
					return;
				MessageBox(0, lpstrFile, "", 0);

				FILE *stream;
				stream = fopen(lpstrFile,"wt");
				char delim = '\t';


				int ndrills = (*pdrills)[0].size();

				double //the arm of square
					deltaX = 2500,
					deltaY = 2500,
					deltaX2 = deltaX+500,
					deltaY2 = deltaY+500;
				//==============================================================
				//==============================================================
				//==============================================================
				//==============================================================
				RECT rcClient;  // Client area of parent window 
				int cyVScroll;  // Height of scroll bar arrow 
				HWND hwndPB;    // Handle of progress bar 
				DWORD cb,		// Size of file and count of
				  cb_read = 0,  // bytes read 
				  cb_disp = 0;  // bytes displayed



				// Ensure that the common control DLL is loaded
				// and create a progress bar along the bottom of
				// the client area of the parent window. 
				// Base the height of the progress bar on the
				// height of a scroll bar arrow. 
				InitCommonControls(); 
				GetClientRect(m_lpPolyotyDlgData->hWnd, &rcClient); 
				GetWindowRect(m_lpPolyotyDlgData->hWnd, &rcClient); 
				cyVScroll = GetSystemMetrics(SM_CYVSCROLL); 
				hwndPB = CreateWindowEx(WS_EX_TOPMOST, PROGRESS_CLASS,
						 (LPSTR) NULL, 
						 //WS_CHILD | WS_VISIBLE,
						 WS_POPUPWINDOW,
						 //0, 0,
						 rcClient.left, rcClient.bottom-2*cyVScroll,
						 rcClient.right, cyVScroll, 
						 //hwndParent, 
						 NULL,
						 
						 (HMENU) 0, hInst, NULL); 

				ShowWindow(hwndPB,1);

				// Gets the file descriptor associated with a stream.
				//int fd = _fileno(stream);
				// Get the length of a file in bytes
				cb = ndrills;


				// Set the range and increment of the progress
				// bar. 

				SendMessage(hwndPB, PBM_SETRANGE, 0,
							MAKELPARAM(0, cb)); 
				SendMessage(hwndPB, PBM_SETSTEP, (WPARAM) 1, 0); 
				//==============================================================
				//==============================================================
				//==============================================================
				//==============================================================

				// number of polyot profiles
				int len = (*pvectors)[ix].size();

				COORDINATES * pxyz = new COORDINATES[len];
				// цикл по каждой точке в файле полётов
				for (int i = 0; i < len; i++)
				{
					double 
						xi = (*pvectors)[ix][i],
						yi = (*pvectors)[iy][i],
						zi = 0.0;

						// заносим в массив точки, 
						pxyz[i].x = xi;
						pxyz[i].y = yi;
						pxyz[i].z = zi;
				}
				qsort( (void *)pxyz, (size_t)len, sizeof(COORDINATES), compare_Y );
				qsort( (void *)pxyz, (size_t)len, sizeof(COORDINATES), compare_X );
				//==============================================================
				//==============================================================
				//==============================================================
				//==============================================================

				//цикл по каждой скважине

				for (int ndrill = 0; ndrill < ndrills; ndrill++)
				{
#if 0
					int ixd = 2;
					int iyd = 3;
#else
					int ixd = 1;
					int iyd = 2;
#endif

					int ifirst_sloj = 7, ilast_sloj = 16;

					double X,Y; // coordinates of current drill

					X = (*pdrills)[ixd][ndrill];
					Y = (*pdrills)[iyd][ndrill];

					char str[255];
					sprintf(str, "%d X = %f Y = %f", ndrill, X,Y);
					//MessageBox(0, str, "", 0);

					// цикл интерполяции на сетку квадрата каждого параметра приборов
					// цикл по параметрам

#if 0
					//for (int col = iy + 1+3; col < pvectors->Size(); col++)
					for (int col = iy + 1; col < pvectors->Size(); col++)
#else
					for (int col = iy + 1 + 3; col < iy + 1 + 6 && col < pvectors->size(); col++)
#endif
					{

						//==============================================================
						//==============================================================
						//==============================================================
						//==============================================================
						//sortrows21(x, y, z);
						// цикл по каждой точке в файле полётов
						int j = 0;						
						for (int i = 0; i < len; i++)
						{
							double 
								xi = (*pvectors)[ix][i],
								yi = (*pvectors)[iy][i],
								zi = (*pvectors)[col][i];

							// заносим в массив только те точки, 
							// которые попадают в квадрат
							if (xi > X - deltaX2 && xi < X + deltaX2 &&
								yi > Y - deltaY2 && yi < Y + deltaY2)
							{
								pxyz[j].x = xi;
								pxyz[j].y = yi;
								pxyz[j].z = zi;
								j++;
							}
						}

						int fact_len = j;

						
						// массив фактических точек измерения внутри квадрата
						vector<double> xx,yy,zz;

						xx.resize(fact_len);
						yy.resize(fact_len);
						zz.resize(fact_len);

						//qsort( (void *)pxyz, (size_t)fact_len, sizeof(COORDINATES), compare_Y );
						//qsort( (void *)pxyz, (size_t)fact_len, sizeof(COORDINATES), compare_X );

						//заполняем точки измерения внутри квадрата
						for (int i = 0; i < fact_len; i++)
						{
							xx[i] = pxyz[i].x;
							yy[i] = pxyz[i].y;
							zz[i] = pxyz[i].z;
						}
						//==============================================================
						//==============================================================
						//==============================================================
						//==============================================================
						/*double xmin = (*pvectors)[ix].Min();
						double ymin = (*pvectors)[iy].Min();
						double xmax = (*pvectors)[ix].Max();
						double ymax = (*pvectors)[iy].Max();*/
#define GRIDDATA 1
#if GRIDDATA
						// формируем равномерную сетку квадрата

						double xmin = X - deltaX;
						double ymin = Y - deltaY;
						double xmax = X + deltaX;
						double ymax = Y + deltaY;

						// длиной шириной

						long 
							lenx = 9,
							leny = 9;

						// интерполируем измерения на равномерный квадрат
						vdouble xi,yi,zi;
						xi = dsequence(double(xmin), long(lenx), double(xmax));
						yi = dsequence(double(ymin), long(leny), double(ymax));
						zi.resize(xi.Length(), yi.Length(), 0.0 );
						if (griddata (m_lpPolyotyDlgData->hWnd,
							xx, 
							yy,
							zz,
							NULL, &xi, &yi, &zi) != 0)
						{
							MessageBox(0, "Error: griddata fault", "", 0);
							break;
						}
						//WinSurf(xi,yi,zi);
						for(j = 0; j < zi.Length(); j++)
						{
							fprintf(stream, "%f%c", zi[j],delim);
						}
#endif /*GRIDDATA*/


					}// конец цила по параметрам прибора
					for (int isloj = ifirst_sloj; isloj <= ilast_sloj; isloj++)
					{
						double Altitude_of_sloj  = (*pdrills)[isloj][ndrill];
						sprintf(str, "%d Altitude_of_sloj(%d) = %f",ndrill, isloj, Altitude_of_sloj);
						//MessageBox(0, str, "", 0);

						fprintf(stream, "%f%c", Altitude_of_sloj,delim);

					}
					fprintf(stream, "\n");
					SendMessage(hwndPB, PBM_STEPIT, 0, 0); 
		
				}//конец цикла по каждой скважине
				delete[] pxyz;
				fclose(stream);
				DestroyWindow(hwndPB);

}

void PolyotyNnetDlg::OnDestroy()
{
	//if (tvd != NULL) delete tvd;		// how to safely release the memory...
	if (pvectors) delete pvectors;
	if (pdrills) delete pdrills;
	if (pline_cutting_vector_sorted) delete pline_cutting_vector_sorted;

}


