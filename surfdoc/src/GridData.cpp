#include "../../surfer_connect/StdAfx.h"
#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>			// MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT
#include "../../surfer_connect/mysurfer.h"
#include "StdAfx.h"
#include ".\griddata.h"
#include "ThePoint3D.h"
#include "..\..\array\src\vdouble.h"
#include "surfdoc.h"
#include "..\..\wintools\src\winsurf.h"
#include "..\..\array\src\interp.h"
#include "winsurftree.h"
#include "DrawScene.h"
#include ".\whatselected.h"
#include ".\Distance3D.h"
#include "../../lab/lab/labdoc.h"


extern char szPath[];
extern HINSTANCE hInst;	
// current instance

#include "srf.h"

size_t GridData::s_number_line_interpolated_points = 5;
bool GridData::line_to_interpolate_points = true;
BOOL CALLBACK GridData::DlgProc( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static char str[1024];
	switch( uMsg )
	{
    case WM_INITDIALOG :
		{

			CheckDlgButton(hDlg, IDC_CHECK_GRIDDATA__USE_LINE_INTERPOLATION,	GridData::line_to_interpolate_points);
			ShowWindow(GetDlgItem(hDlg, IDC_EDIT_GRIDDATA_NPOINTS_OF_LINE_INTERPOLATION), GridData::line_to_interpolate_points);
			sprintf(str, "%u", GridData::s_number_line_interpolated_points);
			SetDlgItemText(hDlg, IDC_EDIT_GRIDDATA_NPOINTS_OF_LINE_INTERPOLATION, str);
		}
		break;
	case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{
		case IDC_CHECK_GRIDDATA__USE_LINE_INTERPOLATION:
			{
				GridData::line_to_interpolate_points = IsDlgButtonChecked( hDlg, IDC_CHECK_GRIDDATA__USE_LINE_INTERPOLATION) == BST_CHECKED;
				ShowWindow(GetDlgItem(hDlg, IDC_EDIT_GRIDDATA_NPOINTS_OF_LINE_INTERPOLATION), GridData::line_to_interpolate_points);
			}
			break;
		case IDOK :
			{                 
				GetDlgItemText(hDlg, IDC_EDIT_GRIDDATA_NPOINTS_OF_LINE_INTERPOLATION, str, 1023);
				if (strlen(str) && ISNUM(str))
				{
					int n = atoi(str);
					if (n > 0)
					{
						GridData::s_number_line_interpolated_points = n;
					}
				}
				sprintf(str, "%u", GridData::s_number_line_interpolated_points);
				SetDlgItemText(hDlg, IDC_EDIT_GRIDDATA_NPOINTS_OF_LINE_INTERPOLATION, str);
			}
			break;
			
		case IDCANCEL :
			EndDialog( hDlg, IDCANCEL );
			break;
		}
		break;
		
		default :
			
			return( FALSE );
	}
	return( TRUE );
}

LRESULT CALLBACK GridData::DlgProcGriddata(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static griddata_dialog * dlg;
	int wmId, wmEvent;

	switch (message) 
	{
		case WM_INITDIALOG :
			{
				dlg = reinterpret_cast<griddata_dialog *>(lParam);
				if (dlg)
					dlg->InitGriddataDialog(hDlg, true);
			}
			break;
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
			case IDC_RADIO_GRIDDATA_APPLICATION_1:
			case IDC_RADIO_GRIDDATA_APPLICATION_2:
			case IDC_RADIO_GRIDDATA_APPLICATION_3:
				{
					if (dlg)
						dlg->RadioButtonHandler(hDlg, IDC_RADIO_GRIDDATA_APPLICATION_1, wmId);
				}
				break;
			case IDC_COMBO_GRIDDATA_FUN:
				{
					if (dlg)
						dlg->GridDataFunComboHandler(hDlg);
				}
				break;
			case IDC_BUTTON_DRID_DATA_FILE_BROSE:
				{
				}
				break;
			case IDOK:
				{
					if (dlg)
						dlg->OkButtonHandler(hDlg);
					EndDialog( hDlg, IDOK );
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
griddata_dialog::griddata_dialog(bool & to_allocate, SurfDoc * p1, GridData * p2, HWND hW, griddata_application griddata_app, GeoSurface * pGeoSurface, bool do_loop, bool unvisible
								 , Grid * pgrid, vector<double> * pvx, vector<double> * pvy, vector<double> * pvz)
	:  m_to_allocate (to_allocate)
{
	may_quit_surfer = true; 

	this->m_grid = pgrid;
	this->m_pvx = pvx;
	this->m_pvy = pvy;
	this->m_pvz = pvz;


	this->m_pSurfDoc = p1; 
	this->m_pGridData = p2;
	this->hWnd = hW;
	this->m_griddata_application = griddata_app;
	this->m_pGeoSurface = pGeoSurface;
	this->m_do_loop = do_loop;
	this->m_unvisible = unvisible;

	have_dat_file = false;

	CreateDirectory(griddata_dialog::temp_directory.c_str(), NULL);

	if (!this->m_unvisible)
	{
		if (IDOK == DialogBoxParam(hInst, 
			MAKEINTRESOURCE(IDD_DIALOG_GRIDDATA_GRIDDATA), 
			(HWND)NULL, (DLGPROC)GridData::DlgProcGriddata, (LPARAM) this)==IDOK) 
		{
		}
	}
}

griddata_dialog::~griddata_dialog(void)
{
}
string griddata_dialog::temp_directory = CLabDoc::GetWorkDir() + "Temp";
void griddata_dialog::InitGriddataDialog(HWND hDlg, bool first_time)
{
	if (this->m_pGridData)
	{
		if (this->m_pGridData->z_flag == 0)
		{
			CheckDlgButton( hDlg, IDC_CHECK_GRIDDATA_THIS_IS_RAZLOM, false);
		}
		else
		{
			CheckDlgButton( hDlg, IDC_CHECK_GRIDDATA_THIS_IS_RAZLOM, true);
		}
	}
	switch(this->m_griddata_application)
	{
	case griddata_dialog::griddata_application::unknown:
		//this->InitDialog_unk(hDlg);
		break;
	case griddata_dialog::griddata_application::gstat_dll:
		{
			if (first_time) CheckRadioButton( hDlg, IDC_RADIO_GRIDDATA_APPLICATION_1, IDC_RADIO_GRIDDATA_APPLICATION_5, IDC_RADIO_GRIDDATA_APPLICATION_1);
			this->InitDialog_gstat(hDlg);
		}
		break;
	case griddata_dialog::griddata_application::surfer_ole:
		{
			if (first_time) CheckRadioButton( hDlg, IDC_RADIO_GRIDDATA_APPLICATION_1, IDC_RADIO_GRIDDATA_APPLICATION_5, IDC_RADIO_GRIDDATA_APPLICATION_2);
            this->InitDialog_surfer(hDlg);
		}
		break;
	case griddata_dialog::griddata_application::this_app:
		{
			if (first_time) CheckRadioButton( hDlg, IDC_RADIO_GRIDDATA_APPLICATION_1, IDC_RADIO_GRIDDATA_APPLICATION_5, IDC_RADIO_GRIDDATA_APPLICATION_3);
			this->InitDialog_my(hDlg);
		}
		break;
	}
}

void griddata_dialog::InitDialog_my(HWND hDlg)
{
	griddata_fun_number = -1;
	//**************************************
	/*cout << "griddata_fun_number [1,2,3]" << endl;
	cout << "0 - griddata_v4" << endl;
	cout << "1 - griddata_v4 with GreenFun" << endl;
	cout << "2 - griddata_2 with any dist_fun" << endl;
	cout << "3 - griddata_3 with triangulation and interpolation" << endl;
	cout << "4 - griddata_3 with triangulation and interpolation with default parameters" << endl;
	cout << "5 - griddata_3 with triangulation and interpolation with default parameters use contour" << endl;
	cin >> griddata_fun_number;*/
	SendDlgItemMessage( hDlg, IDC_COMBO_GRIDDATA_FUN, CB_RESETCONTENT, 0, (LPARAM)0);
		
	SendDlgItemMessage( hDlg, IDC_COMBO_GRIDDATA_FUN, CB_ADDSTRING, 0,
			(LPARAM)(LPCTSTR)"0 - griddata_v4");
	SendDlgItemMessage( hDlg, IDC_COMBO_GRIDDATA_FUN, CB_ADDSTRING, 0,
			(LPARAM)(LPCTSTR)"1 - griddata_v4 with GreenFun");
	SendDlgItemMessage( hDlg, IDC_COMBO_GRIDDATA_FUN, CB_ADDSTRING, 0,
			(LPARAM)(LPCTSTR)"2 - griddata_2 with GreenFun dist_fun");
	SendDlgItemMessage( hDlg, IDC_COMBO_GRIDDATA_FUN, CB_ADDSTRING, 0,
			(LPARAM)(LPCTSTR)"3 - griddata_3 with triangulation and interpolation with default parameters");
	SendDlgItemMessage( hDlg, IDC_COMBO_GRIDDATA_FUN, CB_ADDSTRING, 0,
			(LPARAM)(LPCTSTR)"4 - griddata_3 with triangulation and interpolation with default parameters use contour");
//	SendDlgItemMessage( hDlg, IDC_COMBO_GRIDDATA_FUN, CB_ADDSTRING, 0,
//			(LPARAM)(LPCTSTR)"5 - griddata_3 with triangulation and interpolation");
}
void griddata_dialog::Start_my(HWND hDlg)
{
	// #############################################################
	// #############################################################
	// #############################################################
	// #############################################################
	if (!this->m_do_loop)
	{
		if (this->m_pGridData)
		{
			InitVectors();
		}
		else
		{
			if (OpenFileDlg(hDlg, "Surfer 7 (*.dat)\0*.dat\0All files \0*.*\0", dat_path) == S_OK)
			{	
				vector<vector<double> > * vectors = new vector<vector<double> >;
				if (ReadDatFile(hDlg, dat_path, dat_filename, vectors, NULL) == 0)
				{
					//double min_x = DBL_MAX, min_y = DBL_MAX;
					//double max_x = -DBL_MAX, max_y = -DBL_MAX;
					for (size_t i = 0; i < vectors->size(); i++)
					{
						if ((*vectors)[i].size() < 3)
						{
							char error_str[1024];
							sprintf(error_str, 
								"There must be at least 3 elements in each row\n"
								"But at %u row there are %u elements", i, vectors[i].size());
							MessageBox(hDlg, error_str, "Grid->Data", MB_OK | MB_ICONEXCLAMATION);
							return;
						}
						double X = (*vectors)[i][0];
						double Y = (*vectors)[i][1];
						double Z = (*vectors)[i][2];
						
						VX.push_back(X);
						VY.push_back(Y);
						VZ.push_back(Z);
						
						//if (min_x > X) min_x = X;
						//if (min_y > Y) min_y = Y;
						//if (max_x < X) max_x = X;
						//if (max_y < Y) max_y = Y;
					}
				}
				delete vectors;
			}
		}
	}
}
void griddata_dialog::InitVectors()
{
	size_t i=0, len = this->m_pGridData ? this->m_pGridData->m_input_points.msgSize() : 0;
	VX.resize(len);
	VY.resize(len);
	VZ.resize(len);

	if (this->m_pGridData)
	{
		if(this->m_pGridData->m_input_points.SetCurrentMsgOnFirst())
		{
			do
			{
				switch (this->m_pGridData->z_flag)
				{
				case 0:
				case 3:
					{
						VX[i] = this->m_pGridData->m_input_points.GetCurrentMsg().GetFirstDocumentPoint().x;
						VY[i] = this->m_pGridData->m_input_points.GetCurrentMsg().GetFirstDocumentPoint().y;
						VZ[i] = this->m_pGridData->m_input_points.GetCurrentMsg().GetFirstDocumentPoint().z;
					}
					break;
				case 1:
					{
						VZ[i] = this->m_pGridData->m_input_points.GetCurrentMsg().GetFirstDocumentPoint().x;
						VY[i] = this->m_pGridData->m_input_points.GetCurrentMsg().GetFirstDocumentPoint().y;
						VX[i] = this->m_pGridData->m_input_points.GetCurrentMsg().GetFirstDocumentPoint().z;
					}
					break;
				case 2:
					{
						VX[i] = this->m_pGridData->m_input_points.GetCurrentMsg().GetFirstDocumentPoint().x;
						VZ[i] = this->m_pGridData->m_input_points.GetCurrentMsg().GetFirstDocumentPoint().y;
						VY[i] = this->m_pGridData->m_input_points.GetCurrentMsg().GetFirstDocumentPoint().z;
					}
					break;
				}			
				i++;		
			}
			while(this->m_pGridData->m_input_points.IncrementCurrentMsg());
		}
	}
}
void griddata_dialog::InitDialog_surfer(HWND hDlg)
{
	griddata_fun_number = 1;
	//**************************************
	/*cout << "griddata_fun_number [1,2,3]" << endl;
	cout << "0 - griddata_v4" << endl;
	cout << "1 - griddata_v4 with GreenFun" << endl;
	cout << "2 - griddata_2 with any dist_fun" << endl;
	cout << "3 - griddata_3 with triangulation and interpolation" << endl;
	cout << "4 - griddata_3 with triangulation and interpolation with default parameters" << endl;
	cout << "5 - griddata_3 with triangulation and interpolation with default parameters use contour" << endl;
	cin >> griddata_fun_number;*/
	SendDlgItemMessage( hDlg, IDC_COMBO_GRIDDATA_FUN, CB_RESETCONTENT, 0, (LPARAM)0);

	for (enum SrfGridAlgorithm alg = srfInverseDistance;
		alg <= srfLocalPolynomial; alg++)
	{
		SendDlgItemMessage( hDlg, IDC_COMBO_GRIDDATA_FUN, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)SrfGridAlgorithm_toStr(alg));
	}

	SendDlgItemMessage( hDlg, IDC_COMBO_GRIDDATA_FUN, CB_SETCURSEL, griddata_fun_number, (LPARAM)0);
}
void griddata_dialog::Start_surfer(HWND hDlg)
{
	// #############################################################
	// #############################################################
	// #############################################################
	// #############################################################
	if (!this->m_do_loop)
	{
		if (this->m_pGridData || (this->m_pvx && this->m_pvy && this->m_pvz))
		{
			WriteTempDat();
		}
		else
		{
			if (OpenFileDlg(hDlg, "Surfer 7 (*.dat)\0*.dat\0All files \0*.*\0", dat_path) == S_OK)
			{	
			}
		}
	}
}
void griddata_dialog::InitDialog_gstat(HWND hDlg)
{

	griddata_fun_number = 1;
	//**************************************
	SendDlgItemMessage( hDlg, IDC_COMBO_GRIDDATA_FUN, CB_RESETCONTENT, 0, (LPARAM)0);
		
	SendDlgItemMessage( hDlg, IDC_COMBO_GRIDDATA_FUN, CB_ADDSTRING, 0,
			(LPARAM)(LPCTSTR)"method:  gs; # Gaussian simulation instead of kriging");
	SendDlgItemMessage( hDlg, IDC_COMBO_GRIDDATA_FUN, CB_ADDSTRING, 0,
			(LPARAM)(LPCTSTR)"blocksize: dx=40, dy=40;# 40 $times$ 40 block averages");
	// #############################################################
	// #############################################################
	// #############################################################
	// #############################################################
}
void griddata_dialog::Start_gstat(HWND hDlg)
{
	if (!this->m_do_loop)
	{
		if (this->m_pGridData || (this->m_pvx && this->m_pvy && this->m_pvz))
		{
			this->write_surfer_anscii_mask_file(this->m_pGridData ? this->m_pGridData->z_flag : 0);
			this->WriteTempEas();
			this->WriteTempCmd_002();
			this->ApplyGstatDll();
			if (this->ParseLog())
			{
				SetDlgItemText(hDlg, IDC_EDIT_VARIOGRAM, this->variogram_str);
				//this->WriteTempCmd_003();
				//this->ApplyGstatDll();
			}
		}
		else
		{
			if (OpenFileDlg(hDlg, "GStat Eas files (*.eas)\0*.eas\0All files \0*.*\0", eas_path) == S_OK)
			{	
			}
		}
	}
}

void griddata_dialog::write_surfer_anscii_mask_file(short zflag)
{
	sprintf(msk_path, "%s\\mask.grd", griddata_dialog::temp_directory.c_str());

	FILE *f;
	int i, n, row, col;
	f = fopen(msk_path, "w");
	fprintf(f, "DSAA\n");		/* DSAA */
	switch(zflag)
	{
	case 3:
	case 0:
		{
			fprintf(f, "%d %d\n", this->m_pSurfDoc->m_cube_size.nCol, this->m_pSurfDoc->m_cube_size.nRow);//m->cols, m->rows);	/* nx ny */
			fprintf(f, "%g %g\n", this->m_pSurfDoc->m_cube_size.xLL, this->m_pSurfDoc->m_cube_size.xMax());	/* xlo xhi */
			fprintf(f, "%g %g\n", this->m_pSurfDoc->m_cube_size.yLL, this->m_pSurfDoc->m_cube_size.yMax());	/* ylo yhi */
			fprintf(f, "%g %g\n", 0.0, 1.0);	/* zlo zhi */
			n = this->m_pSurfDoc->m_cube_size.nCol * this->m_pSurfDoc->m_cube_size.nRow;
		}
		break;
	case 1: // x - z
		{
			fprintf(f, "%d %d\n", this->m_pSurfDoc->m_cube_size.nPag, this->m_pSurfDoc->m_cube_size.nRow);//m->cols, m->rows);	/* nx ny */
			fprintf(f, "%g %g\n", this->m_pSurfDoc->m_cube_size.zLL, this->m_pSurfDoc->m_cube_size.zMax());	/* xlo xhi */
			fprintf(f, "%g %g\n", this->m_pSurfDoc->m_cube_size.yLL, this->m_pSurfDoc->m_cube_size.yMax());	/* ylo yhi */
			fprintf(f, "%g %g\n", 0.0, 1.0);	/* zlo zhi */
			n = this->m_pSurfDoc->m_cube_size.nPag * this->m_pSurfDoc->m_cube_size.nRow;
		}
		break;
	case 2: // y - z
		{
			fprintf(f, "%d %d\n", this->m_pSurfDoc->m_cube_size.nCol, this->m_pSurfDoc->m_cube_size.nPag);//m->cols, m->rows);	/* nx ny */
			fprintf(f, "%g %g\n", this->m_pSurfDoc->m_cube_size.xLL, this->m_pSurfDoc->m_cube_size.xMax());	/* xlo xhi */
			fprintf(f, "%g %g\n", this->m_pSurfDoc->m_cube_size.zLL, this->m_pSurfDoc->m_cube_size.zMax());	/* ylo yhi */
			fprintf(f, "%g %g\n", 0.0, 1.0);	/* zlo zhi */
			n = this->m_pSurfDoc->m_cube_size.nCol * this->m_pSurfDoc->m_cube_size.nPag;
		}
		break;
	}
	for (i = 0; i < n; i++) {
		//row = m->rows - (i / m->cols) - 1;	/* from bottom to top */
		//col = i % m->cols;
		//if (map_cell_is_mv(m, row, col))
		//	fprintf(f, "%g", m->cellmin < -9999.0 ?
		//			m->cellmin * 1.1 : -9999.0);
		//else
		//	fprintf(f, "%g", m->grid[row][col]);
		fprintf(f, "%g", 1.0);
		fprintf(f, ((i + 1) % 5 == 0) ? "\n" : " ");
	}
	fclose(f);
}


#if 0
void griddata_dialog::WriteTempCmd_001()
{
	sprintf(est_path, "%s\\%s.est", griddata_dialog::temp_directory.c_str(),
		this->m_pGridData->GetNameTranslit().c_str());

	sprintf(cmd_path, "%s\\%s_001.cmd", griddata_dialog::temp_directory.c_str(),
		this->m_pGridData->GetNameTranslit().c_str());
	
	FILE *f;
	f = fopen(cmd_path, "w");
	fprintf(f, "#\n");
	fprintf(f, "# One variable definition:\n");
	fprintf(f, "# to start the variogram modelling user interface.\n");
	fprintf(f, "#\n");
	fprintf(f, "data(%s): '%s', x=1, y=2, v=3;\n", this->m_pGridData->GetNameTranslit().c_str(), eas_path);
	fprintf(f, "set fit = 1;\n");
	fprintf(f, "variogram(%s): '%s';\n", this->m_pGridData->GetNameTranslit().c_str(), est_path);
	fclose(f);

//ex001.cmd

	/*
#
# One variable definition:
# to start the variogram modelling user interface.
#
data(zinc): 'zinc.eas', x=1, y=2, v=3;
method: semivariogram;
set fit = 1;
variogram(zinc): 'zinc.est';
*/

//zinc.est

	/*
#gstat Win32/msc 2.4.0 (03 March 2003) [C:\Documents and Settings\Admin\Мои документы\C++\Win32_90.16\gstat-2.4.0\gstat-2.4.0\cmd\gstat.exe ex002.cmd]
#sample semivariogram
#Mon Jun 13 16:49:03 2011
#data(zinc): 'zinc.eas', x=1, y=2, v=3;
#[1] mean: 5.88578 variance: 0.521112
#cutoff: 1596.61 interval width: 106.44
#direction: total 
#   from       to  n_pairs  av_dist semivariogram
       0   106.44       57  79.2924 0.123448
  106.44  212.881      299  163.974 0.216218
 212.881  319.321      419  267.365 0.302786
 319.321  425.762      457  372.735 0.412145
 425.762  532.202      547  478.477 0.463413
 532.202  638.643      533  585.341 0.564693
 638.643  745.083      574  693.145 0.568968
 745.083  851.524      564  796.184 0.618677
 851.524  957.964      589  903.146 0.647148
 957.964   1064.4      543  1011.29  0.69157
  1064.4  1170.84      500  1117.86 0.703398
 1170.84  1277.29      477  1221.33 0.603877
 1277.29  1383.73      452  1329.16 0.651716
 1383.73  1490.17      457  1437.26 0.566532
 1490.17  1596.61      415   1543.2 0.574823
*/
}
#endif
void griddata_dialog::WriteTempCmd_002()
{
	sprintf(est_path, "%s\\%s.est", griddata_dialog::temp_directory.c_str(),
		this->m_pGridData->GetNameTranslit().c_str());
	//sprintf(est_path, "%s.est", //griddata_dialog::temp_directory.c_str(),
	//	this->m_pGridData->GetNameTranslit().c_str());

	sprintf(cmd_path, "%s\\%s_002.cmd", griddata_dialog::temp_directory.c_str(),
		this->m_pGridData->GetNameTranslit().c_str());
	
	sprintf(log_path, "%s\\%s.log", griddata_dialog::temp_directory.c_str(),
		this->m_pGridData->GetNameTranslit().c_str());
	
	FILE *f;
	f = fopen(cmd_path, "w");
	fprintf(f, "#\n");
	fprintf(f, "# One variable definition:\n");
	fprintf(f, "# to start the variogram modelling user interface.\n");
	fprintf(f, "#\n");
	fprintf(f, "data(%s): '%s', x=1, y=2, v=3;\n", this->m_pGridData ? this->m_pGridData->GetNameTranslit().c_str() : "tmp", eas_path);
	fprintf(f, "method: semivariogram;");
	fprintf(f, "set fit = 1;\n");
	fprintf(f, "variogram(%s): '%s': 1 Nug() + 1 Sph(1000);\n", this->m_pGridData ? this->m_pGridData->GetNameTranslit().c_str() : "tmp", est_path);
	fprintf(f, "set logfile='%s';\n", log_path);

	fclose(f);

//ex002.cmd	

	/*
#
# One variable definition:
# to start the variogram modelling user interface.
#
data(zinc): 'zinc.eas', x=1, y=2, v=3;
method: semivariogram;
set fit = 1;
variogram(zinc): 'zinc.est': 1 Nug() + 1 Sph(1000);
set logfile='gstat.log';
*/
	//gstat.log
/*
using Marsaglia's random number generator
data(zinc):          zinc.eas     (GeoEAS file)
attribute:     log(zinc, ppm)     [x:] xcoord, m  : [    178605,    181390]
n:                        155     [y:] ycoord, m  : [    329714,    333611]
sample mean:          5.88578     sample std.:          .721881     
[calculating sample variogram]
variogram(zinc): 'zinc.est': 0.0651255 Nug(0) + 0.571106 Sph(911.041);
# model: 0 type: Nug (nugget) sill: 0.0651255 range: 0
# model: 1 type: Sph (spherical) sill: 0.571106 range: 911.041
# sum sills 0.636231, max 0.636231, min 0, flat at distance 911.041
*/

	//ex004.cmd

	/*

#
# One variable definition:
# to start the variogram modelling user interface.
#
data(zinc): 'zinc.eas', x=1, y=2, v=3, log;
variogram(zinc): 0.0651255 Nug(0) + 0.571106 Sph(911.041);
data(): 'locs.eas', x=1, y=2; # prediction locations
set output = 'zincok.out';    # ascii output file
*/


	//map_convert
}
void griddata_dialog::WriteTempCmd_003()
{
	if (strlen(this->variogram_str) == 0)
		sprintf(this->variogram_str, "1.0000 Nug(0) + 10.0000 Sph(40.0000);");

	sprintf(msk_path, "%s\\mask", griddata_dialog::temp_directory.c_str());
	sprintf(cmd_path, "%s\\%s_003.cmd", griddata_dialog::temp_directory.c_str(),
		this->m_pGridData ? this->m_pGridData->GetNameTranslit().c_str() : "tmp");
	sprintf(grd_path, "%s\\%s", griddata_dialog::temp_directory.c_str(),
		this->m_pGridData ? this->m_pGridData->GetNameTranslit().c_str() : "tmp");
/*
#
# One variable definition:
# to start the variogram modelling user interface.
#
data(zinc): 'zinc.eas', x=1, y=2, v=3, log;
variogram(zinc): 0.0651255 Nug(0) + 0.571106 Sph(911.041);
mask:                 'mask_map';

predictions(zinc): 'zn_skpr.grd';
#variances(zinc):   'zn_skvr';
*/

	FILE *f;
	f = fopen(cmd_path, "w");
	fprintf(f, "#\n");
	fprintf(f, "# One variable definition:\n");
	fprintf(f, "# to start the variogram modelling user interface.\n");
	fprintf(f, "#\n");
	fprintf(f, "data(%s): '%s', x=1, y=2, v=3;\n", this->m_pGridData ? this->m_pGridData->GetNameTranslit().c_str() : "tmp", eas_path);
	fprintf(f, "variogram(%s): %s\n", this->m_pGridData ? this->m_pGridData->GetNameTranslit().c_str() : "tmp", this->variogram_str);
	fprintf(f, "mask: '%s';\n", this->msk_path);

	if (griddata_fun_number == 0)
		fprintf(f, "method:  gs; # Gaussian simulation instead of kriging\n");
	if (griddata_fun_number == 1)
		fprintf(f, "blocksize: dx=40, dy=40;      # 40 $times$ 40 block averages\n");

	fprintf(f, "predictions(%s): '%s';\n", this->m_pGridData ? this->m_pGridData->GetNameTranslit().c_str() : "tmp", this->grd_path);

	fclose(f);

}
static void converting_null_to_space(char *cp, const char *fname, const FILE *stream) {
	//static const char *fn = NULL;

	/* convert null characters */
	if (*cp == '\0') {
		*cp = ' ';
		//if (fname == NULL)
		//	fname = stream_name(stream);
		//if (fn != fname) { /* print only once: */
		//	//pr_warning("converted null-character(s) in `%s' to space", fname);
		//	fn = fname;
		//}
	}
	return;
}


char *getting_line(char **s, int *size, FILE *stream) {
/* 
 * read line in *s, return number of chars read;
 * resize s and adjust *size if neccesary;
 * PRE: *s is a char *, pointing to NULL or dynamically allocated memory
 * return NULL on EOF and empty string;
 * after last line read.
 */
#define INCR 64
	int c;
	char cr;
	int n = 0;

	if (s == NULL || size == NULL || stream == NULL)
	{
		//ErrMsg(ER_NULL, "get_line()");
		return NULL;
	}
	if (*size == 0 || *s == (char *) NULL) {
		*s = (char *) malloc(INCR * sizeof(char));
		*size = INCR;
	}
	while ((c = fgetc(stream)) != EOF) {
		cr = c;
		converting_null_to_space(&cr, NULL, stream);
		/* printf("char:[%c],int[%d]\n", c, c); */
		(*s)[n] = c;
		n++;
		if (n == *size - 1) { /* resize: leave space for '\0' */
			*size += INCR;
			*s = (char *)realloc(*s, *size);
		}
		if (c == '\n') { /* end-of-line */
			(*s)[n] = '\0'; /* terminate string */
			return *s;
		}
	}
	/* at EOF: */
	(*s)[n] = '\0';
	if (n > 0) /* we've had character(s): */
		return *s;
	return NULL; /* EOF */
}


bool griddata_dialog::ParseLog()
{
	char *buf = NULL;
	int buf_size = 0;
	FILE * f = fopen(this->log_path, "r");
	if (f)
	{
		while (true)
		{
			if (getting_line(&buf, &buf_size, f) == NULL)	/* i.e., at EOF */
				return NULL;

			if (strncmp(buf, "variogram(", 10) == 0)
			{
				char * p = buf;
				p = strrchr(p, ':');
				if (p)
				{
					strcpy(this->variogram_str, p+1);
					fclose(f);
					return true;
				}
			}
		}
	}
	return false;
}
void griddata_dialog::WriteTempEas()
{
			//write eas

				/*
% write_eas : writes a GEO EAS formatted file into Matlab.
%
% Call write_eas(filename,data,header,title);
%
% filename [string]
% data [ndata,natts] 
% header [structure{natts}] : header values for data columns
% title [string] : optional title for EAS file
%
% TMH (tmh@gfy.ku.dk)
%
function write_eas(filename,data,header,line1);
  
  if nargin<1,
    help write_eas;
    return;
  end
  
  if nargin==1,
    data=filename;
    filename='dummy.eas';;
    mgstat_verbose(sprintf('%s : Filename not set, using ''%s''.',mfilename,filename),0)
  end
 
  if nargin<3,
    for i=1:size(data,2);
      header{i}=sprintf('col%d, unknown',i);
    end
  end
  
  if nargin<4,
    line1=sprintf('Data written by mGstat %s',date);
  end
  
  nd=size(data,2);
  
  fid=fopen(filename,'w');
  
  fprintf(fid,'%s\n',line1);
  fprintf(fid,'%d\n',nd);
  for ih=1:nd,
    fprintf(fid,'%s\n',header{ih});
  end
  
  if size(data,2)==1
      fprintf(fid,'%18.12g\n',data(:));
  elseif size(data,2)==2
      d=data';
      fprintf(fid,'%18.12g   %18.12g\n',d(:));
  elseif size(data,2)==3
      d=data';
      fprintf(fid,'%18.12g   %18.12g   %18.12g\n',d(:));
  elseif size(data,2)==4
      d=data';
      fprintf(fid,'%18.12g   %18.12g   %18.12g   %18.12g\n',d(:));
  elseif size(data,2)==5
      d=data';
      fprintf(fid,'%18.12g   %18.12g   %18.12g   %18.12g   %18.12g\n',d(:));
  else
      
      for id=1:size(data,1),
          %fprintf(fid,'%7.4g   %7.4g   %7.4g ',data(id,:));
          fprintf(fid,'%18.12g   %18.12g   %18.12g ',data(id,:));
          fprintf(fid,'\n');
      end
  end
  fclose(fid);
  
  
  
  return*/
  
 
	sprintf(eas_path, "%s\\%s.eas", griddata_dialog::temp_directory.c_str(),
		this->m_pGridData ? this->m_pGridData->GetNameTranslit().c_str() : "tmp");

	
	char line1[1024];
	sprintf(line1, "Data written by mGstat");

	int nd = 3;



	FILE * stream = fopen(eas_path, "wt");
	if (stream)
	{
		fprintf(stream,"%s\n",line1);
		fprintf(stream,"%d\n",nd);
		//header
		fprintf(stream,"X\n");
		fprintf(stream,"Y\n");
		fprintf(stream,"Z\n");

		double X,Y,Z;
		if (this->m_pGridData)
		{
			if(this->m_pGridData->m_input_points.SetCurrentMsgOnFirst())
			{
				do
				{
					switch (this->m_pGridData->z_flag)
					{
					case 0:
					case 3:
						{
							X = this->m_pGridData->m_input_points.GetCurrentMsg().GetFirstDocumentPoint().x;
							Y = this->m_pGridData->m_input_points.GetCurrentMsg().GetFirstDocumentPoint().y;
							Z = this->m_pGridData->m_input_points.GetCurrentMsg().GetFirstDocumentPoint().z;
						}
						break;
					case 1:
						{
							Z = this->m_pGridData->m_input_points.GetCurrentMsg().GetFirstDocumentPoint().x;
							Y = this->m_pGridData->m_input_points.GetCurrentMsg().GetFirstDocumentPoint().y;
							X = this->m_pGridData->m_input_points.GetCurrentMsg().GetFirstDocumentPoint().z;
						}
						break;
					case 2:
						{
							X = this->m_pGridData->m_input_points.GetCurrentMsg().GetFirstDocumentPoint().x;
							Z = this->m_pGridData->m_input_points.GetCurrentMsg().GetFirstDocumentPoint().y;
							Y = this->m_pGridData->m_input_points.GetCurrentMsg().GetFirstDocumentPoint().z;
						}
						break;
					}
					fprintf(stream, "%18.12g   %18.12g   %18.12g\n", X, Y, Z);
				}
				while(this->m_pGridData->m_input_points.IncrementCurrentMsg());
			}

		}
		else if (this->m_pvx && this->m_pvy && this->m_pvz)
		{
			for (size_t i = 0; i < this->m_pvx->size() && i < this->m_pvy->size() && i < this->m_pvz->size(); i++)
			{
				X = this->m_pvx->operator [](i);
				Y = this->m_pvy->operator [](i);
				Z = this->m_pvz->operator [](i);
					
				fprintf(stream, "%18.12g   %18.12g   %18.12g\n", X, Y, Z);
			}
		}		
		fclose(stream);
	}			
}
void griddata_dialog::WriteTempDat()
{
	sprintf(dat_path, "%s\\%s.dat", griddata_dialog::temp_directory.c_str(),
		this->m_pGridData ? this->m_pGridData->GetName().c_str() : "tmp_xyz");

	FILE * dat;
	dat = fopen(dat_path, "wt");

	if (dat)
	{
		double X,Y,Z;
		if (this->m_pGridData)
		{
			if (this->m_pGridData->m_input_points.SetCurrentMsgOnFirst())
			{
				do
				{
					switch (this->m_pGridData->z_flag)
					{
					case 0:
					case 3:
					default:
						{
							X = this->m_pGridData->m_input_points.GetCurrentMsg().GetFirstDocumentPoint().x;
							Y = this->m_pGridData->m_input_points.GetCurrentMsg().GetFirstDocumentPoint().y;
							Z = this->m_pGridData->m_input_points.GetCurrentMsg().GetFirstDocumentPoint().z;
						}
						break;
					case 1:
						{
							Z = this->m_pGridData->m_input_points.GetCurrentMsg().GetFirstDocumentPoint().x;
							Y = this->m_pGridData->m_input_points.GetCurrentMsg().GetFirstDocumentPoint().y;
							X = this->m_pGridData->m_input_points.GetCurrentMsg().GetFirstDocumentPoint().z;
						}
						break;
					case 2:
						{
							X = this->m_pGridData->m_input_points.GetCurrentMsg().GetFirstDocumentPoint().x;
							Z = this->m_pGridData->m_input_points.GetCurrentMsg().GetFirstDocumentPoint().y;
							Y = this->m_pGridData->m_input_points.GetCurrentMsg().GetFirstDocumentPoint().z;
						}
						break;
					}
					fprintf(dat, "%f\t%f\t%f\n", X,Y,Z);
				}
				while(this->m_pGridData->m_input_points.IncrementCurrentMsg());
			}
		}
		else if (this->m_pvx && this->m_pvy && this->m_pvz)
		{
			for (size_t i = 0; i < this->m_pvx->size() && i < this->m_pvy->size() && i < this->m_pvz->size(); i++)
			{
				X = this->m_pvx->operator [](i);
				Y = this->m_pvy->operator [](i);
				Z = this->m_pvz->operator [](i);
				fprintf(dat, "%f\t%f\t%f\n", X,Y,Z);
			}
		}
		have_dat_file = true;
		fclose(dat);
	}
}

void griddata_dialog::GridDataFunComboHandler(HWND hDlg)
{
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	griddata_fun_number = (int)SendDlgItemMessage( hDlg, IDC_COMBO_GRIDDATA_FUN, CB_GETCURSEL,
		0,(LPARAM)0 );		
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
}
void griddata_dialog::RadioButtonHandler(HWND hDlg, int id_group, int id)
{
	this->m_griddata_application = griddata_dialog::griddata_application(griddata_dialog::griddata_application::gstat_dll + id - id_group);
	this->InitGriddataDialog(hDlg, false);
}

void griddata_dialog::OkButtonHandler(HWND hDlg)
{
	if (this->m_griddata_application == griddata_dialog::griddata_application::unknown)
	{
		MessageBox(this->hWnd, "Select griddata application", "Griddata", MB_OK);
		return;
	}

	short zflag = 0;
	if (this->m_unvisible)
	{
		zflag = this->m_pGridData ? this->m_pGridData->z_flag : 0;
	}
	else
	{
		this_is_razlom = IsDlgButtonChecked( hDlg, 
			IDC_CHECK_GRIDDATA_THIS_IS_RAZLOM) == BST_CHECKED;

		if (this_is_razlom)
		{
			zflag = this->m_pGridData ? this->m_pGridData->DetermineRazlomZflag() : 3;
		}
	}
	

	if (this->m_do_loop)
	{
		//GridData * pGridData = NULL;
		if (this->m_pSurfDoc->m_grid_data.SetCurrentMsgOnFirst())
		{
			do
			{
				this->m_pGridData = &this->m_pSurfDoc->m_grid_data.GetCurrentMsg();
				this->m_pGeoSurface = this->m_pSurfDoc->FindGeoSurface(m_pGridData->GetName().c_str());


				if (m_pGridData->m_input_points.msgSize() > 2)
				{
					this->m_pGridData->built = 1;
					this->m_pGridData->griddata_app = (short)this->m_griddata_application;
					this->m_pGridData->griddata_fun_number = this->griddata_fun_number;

					switch(this->m_griddata_application)
					{
					case griddata_dialog::griddata_application::gstat_dll:
						{
							this->write_surfer_anscii_mask_file(this->m_pGridData->z_flag);
							this->WriteTempEas();
							this->WriteTempCmd_002();
							this->ApplyGstatDll();
							this->ParseLog();
							this->WriteTempCmd_003();
							this->ApplyGstatDll();

							this->OkButtonHandler_gstat(hDlg);
						}
						break;
					case griddata_dialog::griddata_application::surfer_ole:
						{
							this->WriteTempDat();
							this->OkButtonHandler_surfer(hDlg, this->m_pGridData->z_flag);
						}
						break;
					case griddata_dialog::griddata_application::this_app:
						{
							this->InitVectors();
							this->OkButtonHandler_my(hDlg, this->m_pGridData->z_flag);
						}
						break;
					}
				}
			}
			while(this->m_pSurfDoc->m_grid_data.IncrementCurrentMsg());
		}
	}
	else
	{
		if (this->m_pGridData)
		{
			this->m_pGridData->built = 1;
			this->m_pGridData->griddata_app = (short)this->m_griddata_application;
			this->m_pGridData->griddata_fun_number = this->griddata_fun_number;

			if (!this->m_unvisible)
				this->m_pGridData->z_flag = zflag;
		}

		switch(this->m_griddata_application)
		{
		case griddata_dialog::griddata_application::gstat_dll:
			{
				this->Start_gstat(hDlg);
				this->OkButtonHandler_gstat(hDlg);
			}
			break;
		case griddata_dialog::griddata_application::surfer_ole:
			{
				this->Start_surfer(hDlg);
				this->OkButtonHandler_surfer(hDlg, zflag);
			}
			break;
		case griddata_dialog::griddata_application::this_app:
			{
				this->Start_my(hDlg);
				this->OkButtonHandler_my(hDlg, zflag);
			}
			break;
		}
	}
}



void griddata_dialog::OkButtonHandler_my(HWND hDlg, short zflag)
{
	if (this->m_pSurfDoc)
	{
		if (!this->m_pSurfDoc->m_cube_size.Defined())
		{
			MessageBox(0, "!cube_size.Defined()", "GridData::griddata", 0);
		}
		else
		{

			int ( *griddata_fun)(HWND, vector<double>&, vector<double>&, vector<double>&,  Grid *, void *, bool);

			griddata_3_param param3;                                  
			FillDefaultParam(param3);	
			param3.len_biss = 
				(
				(this->m_pSurfDoc->m_cube_size.xMax() - this->m_pSurfDoc->m_cube_size.xLL)
				+
				(this->m_pSurfDoc->m_cube_size.yMax() - this->m_pSurfDoc->m_cube_size.yLL)
				)
				/
				2.0;
			param3.slau_method = 2;

			griddata_2_param param2;                                  
			FillDefaultParam(param2);	

			void * _param = NULL;
			switch (griddata_fun_number)
			{
			case 0:
				griddata_fun = ::griddata;
				break;		
			case 1:
				griddata_fun = griddata_v4;
				break;
			case 2:
				griddata_fun = griddata_2;
				_param = &param2;
				break;
			case 3:
				param3.use_contour = false;
				_param = &param3;									  
				griddata_fun = griddata_3;
				break;
			case 4:
				param3.use_contour = true;
				_param = &param3;									  
				griddata_fun = griddata_3;
				break;
			case 5:
				_param = NULL;
				griddata_fun = griddata_3;
				return;
				break;
			default:
				return;
			}

			//здесь вычисляем грид

			Grid * grid = this->m_grid ? this->m_grid : new Grid;

			grid->gridSection.InitSize(this->m_pSurfDoc->m_cube_size, zflag);			                



			if (this->m_pvx && this->m_pvy && this->m_pvz)
			{
				if (griddata_fun(NULL, *this->m_pvx, *this->m_pvy, *this->m_pvz, grid, _param, m_to_allocate) == 0) 
				{
					//SaveAsSurfer7Grid(grd_file, grid);
					//-----------------------------------
					if (!this->m_grid) this->LoadGrid(grid);
					//-----------------------------------
					if (!this->m_grid) FreeDoubleMat(grid->gridSection.z);
				}
			}
			else
			{
				if (griddata_fun(NULL, VX, VY, VZ, grid, _param, m_to_allocate) == 0) 
				{
					//SaveAsSurfer7Grid(grd_file, grid);
					//-----------------------------------
					if (!this->m_grid) this->LoadGrid(grid);
					//-----------------------------------
					if (!this->m_grid) FreeDoubleMat(grid->gridSection.z);
				}
			}
			if (!this->m_grid) delete grid;
		}
	}
}



void griddata_dialog::OkButtonHandler_surfer(HWND hDlg, short zflag)
{
	if (this->m_pSurfDoc)
	{
		if (!this->m_pSurfDoc->m_cube_size.Defined())
		{
			MessageBox(0, "!cube_size.Defined()", "GridData::griddata", 0);
		}
		else
		{
			//здесь вычисляем грид
			if (SurferGridData(hDlg, zflag))
			{
				//загружаем грид
				Grid * grid = this->m_grid ? this->m_grid : new Grid;
				if (0 == ImportSurfer7Grid(grd_path, grid, this->m_to_allocate)) 
				{
					//-----------------------------------
					if (!this->m_grid) this->LoadGrid(grid);
					//-----------------------------------
					if (!this->m_grid) FreeDoubleMat(grid->gridSection.z);
				}
				if (!this->m_grid) delete grid;
			}
			else
			{
				if (this->m_unvisible)
				{
					// if surfer not installed
					// we must load empty grids

					Grid * grid = this->m_grid ? this->m_grid : new Grid;
					grid->faultSection.nTraces = 0;
					grid->faultSection.nVertices = 0;
					grid->faultSection.traces = NULL;
					grid->faultSection.vertexes = NULL;

					grid->gridSection.BlankValue = BLANK_VALUE;

					grid->gridSection.xSize = this->m_pSurfDoc->m_cube_size.xSize;
					grid->gridSection.ySize = this->m_pSurfDoc->m_cube_size.ySize;
					grid->gridSection.nRow = this->m_pSurfDoc->m_cube_size.nRow;
					grid->gridSection.nCol = this->m_pSurfDoc->m_cube_size.nCol;

					grid->gridSection.xLL = this->m_pSurfDoc->m_cube_size.xLL;
					grid->gridSection.yLL = this->m_pSurfDoc->m_cube_size.yLL;
					grid->gridSection.zMin = BLANK_VALUE;
					grid->gridSection.zMax = BLANK_VALUE;

					if (this->m_to_allocate) 
						grid->gridSection.z = AllocDoubleMat(grid->gridSection.nRow, grid->gridSection.nCol);
					for (long c = 0; c < grid->gridSection.nCol; c++)
					{
						for (long r = 0; r < grid->gridSection.nRow; r++)
						{
							grid->gridSection.z[r][c] = BLANK_VALUE;
						}
					}

					if (!this->m_grid) this->LoadGrid(grid);
					if (!this->m_grid) FreeDoubleMat(grid->gridSection.z);
					if (!this->m_grid) delete grid;

				}
			}
		}
	}
}

#include <errno.h>
enum Gstat_errno {
	ER_NOERROR     =  0 /* no error */,
	ER_NULL        =  1 /* internal error: should not occur */,
	ER_VARNOTSET   =  2 /* a required variable was not set by the user */,
	ER_RANGE       =  3 /* range error (outside permitted values) */,
	ER_IMPOSVAL    =  4 /* a variable was set to an illegal value */,
	ER_NOFILE      =  5 /* no input file specified */,
	ER_WRITE       =  6 /* write error on file */,
	ER_READ        =  7 /* read error on file */,
	ER_RDFLT       =  8 /* error while converting a string to a float */,
	ER_RDINT       =  9 /* error while converting a string to an int */,
	ER_SYNTAX      = 10 /* syntax error */,
	ER_ARGOPT      = 11 /* error in command line option arguments */,
	ER_DOMAIN      = 12 /* math error */,
	ER_MEMORY      = 13 /* memory exhausted */,
	ER_IO          = 14 /* i/o conflict (e.g. redirection not permitted) */,
	ER_NOCMD       = 15 /* no command file specified */,
	ER_NOCURSES    = 16 /* no curses user interface compiled in */,
	ER_PWRITE      = 17 /* error while writing to a pipe */,
	ER_PREAD       = 18 /* error while reading from a pipe */,
	ER_SECURE      = 19 /* secure mode: operation not allowed */,
	ER_MESCHACH    = 20 /* error happened somewhere in meschach matrix lib */
};

#define ErrMsg NULL
#define message printf
/* some famous beware-of-side-effects macro's ! */
#ifndef MAX
# define MAX(a,b) (((a) > (b)) ? (a) : (b))
#endif
#ifndef MIN
# define MIN(a,b) (((a) < (b)) ? (a) : (b))
#endif
#ifndef ABS
#define ABS(a)   (((a) >= 0) ? (a) : (-(a)))
#endif

char *gl_mv_string;

#ifndef HUGE_VAL
#  define HUGE_VAL    1.7976931348623157e+308
#endif

int read_float(const char *s, float *f);
int read_double(const char *s, double *d);
int read_int(const char *s, int *i);
int read_uint(const char *s, unsigned int *u);
int read_long(const char *s, long *l);
int read_ulong(const char *s, unsigned long *l);
void set_mv_float(float *f) {
#ifdef HAVE_LIBCSF /* csftypes.h was included: */
	SET_MV_REAL4(f);
#else
	memset(f, 0xFF, sizeof(float));
#endif
}

void set_mv_double(double *d) {
#ifdef HAVE_LIBCSF
	SET_MV_REAL8(d);
#else
	memset(d, 0xFF, sizeof(double));
#endif
}

int is_mv_float(const float *f) {
#ifdef HAVE_LIBCSF
	return IS_MV_REAL4(f);
#else
	const unsigned char u[sizeof(float)] = { 0xFF, 0xFF, 0xFF, 0xFF };
	/* will choke if sizeof(float) != 4 */
	return (memcmp(f, u, sizeof(float)) == 0);
#endif
}

int is_mv_double(const double *d) {
#ifdef HAVE_LIBCSF
	return IS_MV_REAL8(d);
#else
	const unsigned char u[sizeof(double)] =
		{ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
	/* will choke if sizeof(double) != 8 */
	return (memcmp(d, &u, sizeof(double)) == 0);
#endif
}

int cpu_is_little_endian(void) {
/*
 * returns 0 if the current cpu is not little-endian,
 * returns 1 if it is. NOTE: VMS-order is not evaluated (don't know it!)
 */
#ifdef HAVE_CONFIG_H /* configure did the work... */
# ifdef WORDS_BIGENDIAN 
	return 0;
# else
	return 1;
# endif
#else /* do it self: */
	unsigned long u = 1;
	char *cp;

	cp = (char *) (&u);
	return (cp[0] == 1); /* are we little-endian? */
#endif
}


int read_float(const char *s, float *f) {
/* return 1 on error, 0 on no error */
	double d = 0, min = (double) FLT_MIN, max = (double) FLT_MAX;
	int warning = 0;

	warning = read_double(s, &d);
	if (is_mv_double(&d)) {
		set_mv_float(f);
		return 0;
	}
	if (fabs(d) > max || (fabs(d) < min && d != 0.0)) {
		message("value outside valid range +/-[%g, %g]\n", min, max);
		ErrMsg(ER_RANGE, s);
	}
	*f = (float) d;
	return warning;
}

int read_double(const char *s, double *d) {
/* return 1 on error, 0 on no error */
	char *cp;

	if (s == NULL)
		ErrMsg(ER_NULL, "read_double()");
	if (s[0] == '\0') 
		ErrMsg(ER_IMPOSVAL, "read_double(): empty string");
	if (strcmp(s, gl_mv_string) == 0) {
		set_mv_double(d);
		return 0;
	}
	*d = strtod(s, &cp);
	if (errno == ERANGE) {
		message("value outside valid range +/-[%g, %g]\n", DBL_MIN, DBL_MAX);
		ErrMsg(ER_RANGE, s);
	}
	if (*cp == '\0')
		return 0;
	else {
#ifdef READ_WARNING
		pr_warning("read_double(): unconverted suffix: `%s'", cp);
#endif
		return 1;
	}
}

int read_int(const char *s, int *i) {
/* return 1 on error, 0 on no error */
	long l;
	int warning = 0;

	warning = read_long(s, &l);
	if (warning) 
		return warning;
	if (l > INT_MAX || l < INT_MIN) {
		message("value outside valid range [%d, %d]\n", INT_MIN, INT_MAX);
		ErrMsg(ER_RANGE, s);
	}
	*i = (int) l;
	return warning;
}

int read_uint(const char *s, unsigned int *u) {
/* return 1 on error, 0 on no error */
	unsigned long ul;
	int warning = 0;

	warning = read_ulong(s, &ul);
	if (warning) 
		return warning;
	if (ul > UINT_MAX) {
		message("value outside valid range [0, %u]\n", UINT_MAX);
		ErrMsg(ER_RANGE, s);
	}
	*u = (unsigned int) ul;
	return warning;
}

int read_long(const char *s, long *l) {
/* return 1 on error, 0 on no error */
	char *cp;

	if (s == NULL)
		ErrMsg(ER_NULL, "read_long()");
	if (s[0] == '\0') 
		ErrMsg(ER_IMPOSVAL, "read_long(): empty string");
	*l = strtol(s, &cp, 10);
	if (errno == ERANGE) {
		message("value outside valid range [%ld, %ld]\n", LONG_MIN, LONG_MAX);
		ErrMsg(ER_RANGE, s);
	}
	if (*cp == '\0')
		return 0;
	else  {
#ifdef READ_WARNING
		pr_warning("read_long(): unconverted suffix: `%s'", cp);
#endif
		return 1;
	}
}

int read_ulong(const char *s, unsigned long *u) {
/* return 1 on error, 0 on no error */
	char *cp;

	if (s == NULL)
		ErrMsg(ER_NULL, "read_long()");
	if (s[0] == '\0') 
		ErrMsg(ER_IMPOSVAL, "read_long(): empty string");
	*u = strtoul(s, &cp, 10);
	if (errno == ERANGE) {
		message("value outside valid range [0, %lu]\n", ULONG_MAX);
		ErrMsg(ER_RANGE, s);
	}
	if (*cp == '\0')
		return 0;
	else  {
#ifdef READ_WARNING
		pr_warning("read_long(): unconverted suffix: `%s'", cp);
#endif
		return 1;
	}
}

static int read_surfer_header(Grid * pgrid, FILE * f)
{
	char *buf = 0, *tok1, *tok2;
	int i, buf_size = 0, nx, ny;
	float xlo, xhi, ylo, yhi, zlo, zhi;

	/*
	   DSAA
	   nx ny
	   xlo xhi
	   ylo yhi
	   zlo zhi
	   values ... (row order; starting at ylo ending at yhi)
	 */

//	DUMP("well...");
	for (i = 0; i < 5; i++) {
		if (getting_line(&buf, &buf_size, f) == NULL)	/* i.e., at EOF */
			return 1;
		tok1 = strtok(buf, " \t\n\r");
		tok2 = strtok(NULL, " \t\n\r");
		if (i == 0) {
			/* DSAA */
			if (tok1 == NULL || tok2 != NULL || strcmp(buf, "DSAA"))
				return 1;
//			DUMP("line 1 OK\n");
		} else if (i == 1) {	/* nx ny */
			if (tok1 == NULL || tok2 == NULL || read_int(tok1, &nx) ||
				read_int(tok2, &ny))
				return 1;
//			DUMP("line 2 OK\n");
		} else if (i == 2) {	/* xlo xhi */
			if (tok1 == NULL || tok2 == NULL || read_float(tok1, &xlo) ||
				read_float(tok2, &xhi))
				return 1;
//			DUMP("line 3 OK\n");
		} else if (i == 3) {	/* ylo yhi */
			if (tok1 == NULL || tok2 == NULL || read_float(tok1, &ylo) ||
				read_float(tok2, &yhi))
				return 1;
//			DUMP("line 4 OK\n");
		} else if (i == 4) {	/* zlo zhi */
			if (tok1 == NULL || tok2 == NULL || read_float(tok1, &zlo) ||
				read_float(tok2, &zhi))
				return 1;
//			DUMP("line 5 OK\n");
		}
	}
/*	m->cellsizex = (xhi - xlo) / (nx - 1);	/* [xy]hi/lo point to grid centres */
/*	m->cellsizey = (yhi - ylo) / (ny - 1);
	m->rows = ny;
	m->cols = nx;
	m->x_ul = xlo - 0.5 * m->cellsizex;
	m->y_ul = yhi + 0.5 * m->cellsizey;
	m->cellmin = zlo;
	m->cellmax = zhi;*/

	pgrid->gridSection.xSize = (xhi - xlo) / (nx - 1);
	pgrid->gridSection.ySize = (yhi - ylo) / (ny - 1);
	pgrid->gridSection.nRow = ny;
	pgrid->gridSection.nCol = nx;

	pgrid->gridSection.xLL = xlo;
	pgrid->gridSection.yLL = ylo;
	pgrid->gridSection.zMin = zlo;
	pgrid->gridSection.zMax = zhi;

	pgrid->gridSection.BlankValue = BLANK_VALUE;//1.70141e38;// nodes are blanked if greater or equal to this value

	pgrid->faultSection.nTraces = 0;
	pgrid->faultSection.nVertices = 0;
	pgrid->faultSection.traces = NULL;
	pgrid->faultSection.vertexes = NULL;

	if (buf_size)
		free(buf);
//	DUMP("surfer DSAA header ok...");
	return 0;
}


static int read_ascii_grid(char *file, Grid * pgrid, FILE * f, int first_line_in_buffer, bool to_allocate)
{
static char *line_buf = NULL;
static int line_size = 0;
	unsigned int cells = 0, ok = 1, row, col, at_start;
	char *tok;

	cells = 0;
	//alloc_mv_grid(m);
	if (to_allocate)
		pgrid->gridSection.z = AllocDoubleMat(pgrid->gridSection.nRow, pgrid->gridSection.nCol);

	if (!first_line_in_buffer)
		getting_line(&line_buf, &line_size, f);
	if (line_size <= 0)
		return 1;
	do {
		at_start = 1;			/* we're at a new line */
		while (ok && (tok = strtok(at_start ? line_buf : NULL, " \n\r"))
			   != NULL) {
			at_start = 0;
			row = cells / pgrid->gridSection.nCol;
			col = cells % pgrid->gridSection.nCol;
			if (cells >= pgrid->gridSection.nRow * pgrid->gridSection.nCol ||
				read_double(tok, &(pgrid->gridSection.z[row][col])))
				ok = 0;
			if (ok && pgrid->gridSection.z[row][col] == pgrid->gridSection.BlankValue)
				set_mv_double(&(pgrid->gridSection.z[row][col]));
			else {
				if (pgrid->gridSection.zMin == FLT_MAX)
					pgrid->gridSection.zMin = pgrid->gridSection.zMax = pgrid->gridSection.z[row][col];
				else {
					pgrid->gridSection.zMin = MIN(pgrid->gridSection.zMin, pgrid->gridSection.z[row][col]);
					pgrid->gridSection.zMax = MAX(pgrid->gridSection.zMax, pgrid->gridSection.z[row][col]);
				}
			}
			cells++;
		}
	} while (ok && getting_line(&line_buf, &line_size, f) != NULL);
	if (!ok || cells != pgrid->gridSection.nRow * pgrid->gridSection.nCol) {
		if (cells > 0)
			/*pr_warning*/printf("`%s' has too %s values (read: %u, expected: %u)\n",
					   file,
					   cells < pgrid->gridSection.nRow * pgrid->gridSection.nCol ? "few" : "many", 
					   cells, pgrid->gridSection.nRow * pgrid->gridSection.nCol);
		return 1;
	}
	return 0;
}



bool read_surfer(char *file, Grid * pgrid, bool to_allocate)
{
	FILE *f = NULL;
	int i, j, size;
	float *buf;

	#define DEF_mv_string       "NA"
	gl_mv_string     = DEF_mv_string;

	f = fopen(file, "r");
	if (f)
	{
		if (read_surfer_header(pgrid, f) || read_ascii_grid(file, pgrid, f, 0, to_allocate)) {
			fclose(f);
			return false;
		}
		fclose(f);
		return true;
	}
	else
	{
		char str[1024];
		sprintf(str, "file %s not found", file);
		MessageBox(0, str, "read_surfer", MB_OK);
	}
	return false;
}


void griddata_dialog::OkButtonHandler_gstat(HWND hDlg)
{
	if (this->m_pSurfDoc)
	{
		if (!this->m_pSurfDoc->m_cube_size.Defined())
		{
			MessageBox(0, "!cube_size.Defined()", "GridData::griddata", 0);
		}
		else
		{
			//здесь вычисляем грид
			//this->write_surfer_anscii_mask_file();
			//this->WriteTempEas();
			//this->WriteTempCmd_002();
			//this->ApplyGstatDll();
			//if (this->ParseLog())

			GetDlgItemText(hDlg, IDC_EDIT_VARIOGRAM, this->variogram_str, 1024);

			{

				this->WriteTempCmd_003();
				if (ApplyGstatDll())
				{
					//загружаем грид
					Grid * grid = this->m_grid ? this->m_grid : new Grid;

					sprintf(grd_path, "%s\\%s.grd", griddata_dialog::temp_directory.c_str(),
						this->m_pGridData->GetNameTranslit().c_str());

					if (read_surfer(grd_path, grid, this->m_to_allocate)) 
					{
						//-----------------------------------
						if (!this->m_grid) this->LoadGrid(grid);
						//-----------------------------------
						if (!this->m_grid) FreeDoubleMat(grid->gridSection.z);
					}
					if (!this->m_grid) delete grid;
				}
			}
		}
	}
}
bool griddata_dialog::ApplyGstatDll()
{
#ifdef _DEBUG
	HMODULE hGstat = LoadLibrary("gstat_d.dll");
#else
	HMODULE hGstat = LoadLibrary("gstat.dll");
#endif
    if (hGstat!=NULL)
	{
		//#define WINAPI      __stdcall 
		// __cdecl
		// pascal

		typedef  int (MEGS1)(int, char *argv[]);
		MEGS1* me1 = (MEGS1*)::GetProcAddress((HMODULE)hGstat, "gstat_main");
		
		if (me1 != NULL)
		{
		//printf ("fun loaded\n");
			int argc=2;
			int result;

			bool res = true;

			typedef char* PTR_CHAR;
			char ** argv = new PTR_CHAR[argc];
#ifdef _DEBUG
			argv[0] = "gstat_d.dll";
#else
			argv[0] = "gstat.dll";
#endif
			argv[1] = this->cmd_path;
			try
			{
				result=(*me1)(argc, argv);
			}
			catch (...)
			{
				MessageBox(0, "Gstat Erased an Error", "ApplyGstatDll", 0);
				res = false;
			}
			

			printf ("dll loaded\n");
			::FreeLibrary(hGstat); 

			return res;
		}
		else cout << "Error Load function" << endl;

	}
	else cout << "error load Dll" << endl;

	/*char *argv[1024];
	sprintf (*argv, "ex001.cmd");
	//gstat_main(1, "ex001.cmd");
	gstat_main(1, argv);

	void parse_gstatrc(void);
	
	parse_gstatrc();*/

	return false;

			
}

bool griddata_dialog::SurferGridData(HWND hDlg, short zflag)
{
	sprintf(grd_path, "%s\\%s.grd", griddata_dialog::temp_directory.c_str(),
		this->m_pGridData ? this->m_pGridData->GetName().c_str() : "tmp_xyz");

	SrfGridAlgorithm alg = SrfGridAlgorithm(griddata_fun_number+1);

	LPCTSTR DataFile = this->dat_path;
	//xCol  Long  optional, column containing X values, Column A = 1
	//yCol  Long  optional, column containing Y values, Column B = 2
	//zCol  Long  optional, column containing Z values, Column C = 3
	long xCol = 1; long yCol = 2; long zCol = 3; 
	// ExclusionFilter  Variant  optional, Boolean search to exclude values
	VARIANT ExclusionFilter = COleVariant(long(false)); 
	///VARIANT ExclusionFilter = COleVariant(long(true)); 
	//DupMethod  Variant  optional, method for eliminating duplicates, the SrfDupMethod enumeration can be used for this parameter
	///VARIANT DupMethod = COleVariant(long(srfDupAvg)); 
	VARIANT DupMethod = COleVariant(long(srfDupMinZ)); //берём минимальное Z координату, чтобы строить старшие слои
	//xDupTol  Variant  optional, separation distance of X values to be considered duplicates 
	//yDupTol  Variant  optional, separation distance of Y values to be considered duplicates
	VARIANT xDupTol = COleVariant(double(1.0e-6));
	VARIANT yDupTol = COleVariant(double(1.0e-6));
	//NumCols  Variant  optional, grid line geometry number of columns 
	//NumRows  Variant  optional, grid line geometry number of rows 
	//x - col
	//y - row
	//z - page
	VARIANT NumCols;  
	VARIANT NumRows; 
	switch (zflag)
	{
	case 0:
	case 3:
		{
			NumCols = COleVariant(long(this->m_pSurfDoc->m_cube_size.nCol));  
			NumRows = COleVariant(long(this->m_pSurfDoc->m_cube_size.nRow)); 
		}
		break;

	case 1: // x - z
		{
			NumCols = COleVariant(long(this->m_pSurfDoc->m_cube_size.nPag));  
			NumRows = COleVariant(long(this->m_pSurfDoc->m_cube_size.nRow)); 
		}
		break;

	case 2: // y - z
		{
			NumCols = COleVariant(long(this->m_pSurfDoc->m_cube_size.nCol));  
			NumRows = COleVariant(long(this->m_pSurfDoc->m_cube_size.nPag)); 
		}
		break;
	}
	//xMin  Variant  optional, grid line geometry minimum X value
	//xMax  Variant  optional, grid line geometry maximum X value
	//yMin  Variant  optional, grid line geometry minimum Y value
	//yMax  Variant  optional, grid line geometry maximum Y value
	VARIANT xMin;
	VARIANT xMax;
	VARIANT yMin;
	VARIANT yMax;
	switch (zflag)
	{
	case 0:
	case 3:
		{
			xMin = COleVariant(double(this->m_pSurfDoc->m_cube_size.xLL));
			xMax = COleVariant(double(this->m_pSurfDoc->m_cube_size.xMax()));
			yMin = COleVariant(double(this->m_pSurfDoc->m_cube_size.yLL));
			yMax = COleVariant(double(this->m_pSurfDoc->m_cube_size.yMax()));
		}
		break;

	case 1: // x - z
		{
			xMin = COleVariant(double(this->m_pSurfDoc->m_cube_size.zLL));
			xMax = COleVariant(double(this->m_pSurfDoc->m_cube_size.zMax()));
			yMin = COleVariant(double(this->m_pSurfDoc->m_cube_size.yLL));
			yMax = COleVariant(double(this->m_pSurfDoc->m_cube_size.yMax()));
		}
		break;

	case 2: // y - z
		{
			xMin = COleVariant(double(this->m_pSurfDoc->m_cube_size.xLL));
			xMax = COleVariant(double(this->m_pSurfDoc->m_cube_size.xMax()));
			yMin = COleVariant(double(this->m_pSurfDoc->m_cube_size.zLL));
			yMax = COleVariant(double(this->m_pSurfDoc->m_cube_size.zMax()));
		}
		break;
	}
	//Algorithm  Variant  optional, gridding method (kriging, etc.), the SrfGridAlgorithm enumeration can be used for this parameter
	VARIANT Algorithm = COleVariant(long(alg)); 
	//ShowReport  Variant optional, show grid report, the report is only shown if ShowReport is true and Surfer is visible.
	VARIANT ShowReport = COleVariant(long(false)); 

	//SearchEnable  Variant  optional, no search (use all of the data)
	VARIANT SearchEnable = COleVariant(long(true)); 
	//SearchNumSectors  Variant  optional, number of sectors to search 
	VARIANT SearchNumSectors = COleVariant(long(1)); // up to 32
	//SearchRad1  Variant  optional, search ellipse radius 1 
	//SearchRad2  Variant  optional, search ellipse radius 2 
	VARIANT SearchRad1 = COleVariant(double(0));
	VARIANT SearchRad2 = COleVariant(double(0));
	//SearchAngle  Variant  optional, search ellipse angle 
	VARIANT SearchAngle = COleVariant(double(0));
	//SearchMinData  Variant  optional, minimum number of data in all sectors (node is blanked if the data surrounding the node are less than this number)
	VARIANT SearchMinData;
	//SearchDataPerSect  Variant  optional, maximum number of data to use from each sector 
	VARIANT SearchDataPerSect;
	//SearchMaxEmpty  Variant  optional, blank node if more than this many sectors are empty 
	VARIANT SearchMaxEmpty;
	//FaultFileName  Variant  optional, file containing fault traces
	VARIANT FaultFileName;
	//BreakFileName  Variant  optional, file containing breaklines 
	VARIANT BreakFileName;
	//AnisotropyRatio  Variant  optional, anisotropy ratio used for various algorithms
	VARIANT AnisotropyRatio = COleVariant(double(1));
	//AnisotropyAngle  Variant  optional, anisotropy angle used for various algorithms
	VARIANT AnisotropyAngle = COleVariant(double(0));
	//IDPower  Variant  optional, inverse distance to a power, power number
	VARIANT IDPower;
	//IDSmoothing  Variant  optional, inverse distance to a power smoothing factor
	VARIANT IDSmoothing;
	//KrigType  Variant  optional, kriging type (point or block), the SrfKrigType enumeration can be used for this parameter
	VARIANT KrigType;
	//KrigDriftType  Variant  optional, kriging drift type (none, linear, or quadratic), the SrfDriftType enumeration can be used for this parameter
	VARIANT KrigDriftType;
	//KrigStdDevGrid  Variant  optional, output grid of kriging standard deviations 
	VARIANT KrigStdDevGrid;
	//KrigVariogram  Variant  optional, kriging variogram model, KrigVariogram may contain an array of VarioComponent objects. If this parameter is not specified the default Linear variogram is used.
	VARIANT KrigVariogram;
	//MCMaxResidual  Variant  optional, minimum curvature maximum residual
	VARIANT MCMaxResidual;
	//MCMaxIterations  Variant  optional, minimum curvature maximum number of iterations
	VARIANT MCMaxIterations;
	//MCInternalTension  Variant  optional, minimum curvature internal tension factor

	VARIANT MCInternalTension;
	//MCBoundaryTension  Variant  optional, minimum curvature boundary tension factor

	VARIANT MCBoundaryTension;
	//MCRelaxationFactor  Variant  optional, minimum curvature relaxation factor

	VARIANT MCRelaxationFactor;
	//ShepSmoothFactor  Variant  optional, modified Shepard's method smoothing factor
	VARIANT ShepSmoothFactor; 
	//ShepQuadraticNeighbors  Variant  optional, modified Shepard's method quadratic neighbors

	VARIANT ShepQuadraticNeighbors;
	//ShepWeightingNeighbors  Variant  optional, modified Shepard's method weighting neighbors

	VARIANT ShepWeightingNeighbors;
	//ShepRange1  Variant  optional, modified Shepard's method anisotropy range 1
	//ShepRange2  Variant  optional, modified Shepard's method anisotropy range 2
	VARIANT ShepRange1;
	VARIANT ShepRange2;
	//RegrMaxXOrder  Variant  optional, polynomial regression maximum X order
	//RegrMaxYOrder  Variant  optional, polynomial regression maximum Y order

	VARIANT RegrMaxXOrder;
	VARIANT RegrMaxYOrder;
	//RegrMaxTotalOrder  Variant  optional, polynomial regression maximum total order

	VARIANT RegrMaxTotalOrder;
	//RBBasisType  Variant  optional, radial basis function type (inverse multiquadric, multilog, multiquadric, natural cubic spline, or thin plate spline), the SrfBasisType enumeration can be used for this parameter

	VARIANT RBBasisType;
	//RBRSquared  Variant  optional, radial basis function correlation coefficient

	VARIANT RBRSquared;
	//OutGrid  String  optional, default="", output grid file name

	LPCTSTR OutGrid = this->grd_path;
	//OutFmt  SrfGridFormat  optional, default=srfGridFmtS7, output grid file format, 

	long OutFmt = srfGridFmtS7;
	//SearchMaxData  Variant  optional, maximum number of data to use from all sectors

	VARIANT SearchMaxData;
	//KrigStdDevFormat  Variant  optional, standard deviation grid file format, the SrfGridFormat enumeration can be used for this parameter 

	VARIANT KrigStdDevFormat;
	//DataMetric  Variant  optional, one of the data metric options, the SrfDataMetric enumeration can be used for this parameter

	VARIANT DataMetric;
	//LocalPolyOrder  Variant  optional, local polynomial order (1,2, or 3)
	//LocalPolyPower  Variant  optional, local polynomial power

	VARIANT LocalPolyOrder;
	VARIANT LocalPolyPower;
	// TriangleFileName  Variant  optional, name of the file to contain the triangulation - the format is determined by the file name extension
	VARIANT TriangleFileName;

   // http://www.goldensoftware.com/forum/viewtopic.php?f=23&p=103651
   //Surf.GridData(OutputFile$, xCol=0, yCol=(ColumnArray(8)-1), 
   //zCol=SpeciesVar, xMin=0, xMax=16.1, yMin=-6.5, yMax=0, 
   //GridMethod=1, VarioType1=4,VarioRatio1=4)

	bool res = false;

	MySurfer m_surfer;
	if (m_surfer.SurferOleLoad() && m_surfer.IsApplicationDispatch())
	{
		try
		{
			//m_surfer.SurferOleExecute(NULL);
#if 1
			res = m_surfer.m_app.GridData(
				DataFile,
				xCol, yCol, zCol, 
				ExclusionFilter,
				DupMethod, 
				xDupTol, 
				yDupTol, 
				NumCols, 
				NumRows, 
				xMin,
				xMax,
				yMin,
				yMax,
				Algorithm,
				ShowReport);
#else
			res = m_surfer.m_app.GridData(
				DataFile,
				xCol, yCol, zCol, 
				ExclusionFilter,
				DupMethod, 
				xDupTol, 
				yDupTol, 
				NumCols, 
				NumRows, 
				xMin,
				xMax,
				yMin,
				yMax,
				Algorithm,
				ShowReport,
				SearchEnable,
				SearchNumSectors,
				SearchRad1,
				SearchRad2,
				SearchAngle,
				SearchMinData,
				SearchDataPerSect,
				SearchMaxEmpty,
				FaultFileName,
				BreakFileName,
				AnisotropyRatio,
				AnisotropyAngle,
				IDPower,
				IDSmoothing,
				KrigType,
				KrigDriftType,
				KrigStdDevGrid,
				KrigVariogram,
				MCMaxResidual,
				MCMaxIterations,
				MCInternalTension,
				MCBoundaryTension,
				MCRelaxationFactor,
				ShepSmoothFactor,
				ShepQuadraticNeighbors,
				ShepWeightingNeighbors,
				ShepRange1,
				ShepRange2,
				RegrMaxXOrder,
				RegrMaxYOrder,
				RegrMaxTotalOrder,
				RBBasisType,
				RBRSquared,
				OutGrid,
				OutFmt,
				SearchMaxData,
				KrigStdDevFormat,
				DataMetric,
				LocalPolyOrder,
				LocalPolyPower,
				TriangleFileName);
#endif

		}
		catch (CException* pe) {
			// catch errors from WinINet 
			TCHAR szErr[4098]; 
			pe->GetErrorMessage(szErr, 4098); 
			AfxMessageBox(szErr);
			pe->Delete();
			return false;

		}

		if (may_quit_surfer && !m_surfer.GotActiveSurferWindow())
			m_surfer.m_app.Quit();

		m_surfer.SurferOleRelease();
	}
	else
		printf("!!!!! m_surfer.IsApplicationDispatch()\n");
					
	return res;				
}



void griddata_dialog::LoadGrid(Grid * grid)
{
	//-----------------------------------
	COLORREF color = RGB(255,255,0); 
	short zflag = 0;

	char name[4098];;
	if (this->m_pGridData)
	{
		sprintf(name, "%s\0", this->m_pGridData->GetName().c_str());
		color = this->m_pGridData->GetColor();

		zflag = this->m_pGridData->z_flag;
	}
	else
	{
		sprintf(name, "%s\0", dat_filename);
	}

	long id_surf = this->m_pGridData ? this->m_pGridData->id_surf : -1;
	BYTE podoshva = this->m_pGridData ? this->m_pGridData->podoshva : 0;
	long id_ige = this->m_pGridData ? this->m_pGridData->id_ige : -1;
	if (m_pGeoSurface == NULL)
	{
		this->m_pSurfDoc->AddSurf(id_surf, podoshva, id_ige, zflag, grid, color, name);
		this->m_pSurfDoc->m_surfaces.GetLastMsg().id_umpoz = this->m_pGridData ? this->m_pGridData->id_umpoz : 0;
		DrawNewSurf(this->m_pSurfDoc);
	}
	else
	{
		m_pGeoSurface->Init(id_surf, podoshva, -1, zflag, grid, color);
		m_pGeoSurface->id_umpoz = this->m_pGridData ? this->m_pGridData->id_umpoz : 0;
		m_pGeoSurface->id_umpoz = this->m_pGridData ? this->m_pGridData->id_ige : -1;

		//m_pGeoSurface->SetName(name);
		m_pGeoSurface->ReDraw();
	}

	if (this->m_pSurfDoc && this->m_pSurfDoc->GetLabDoc() && !this->m_unvisible)
	{
		long id_obj = this->m_pSurfDoc->Get_ID_OBJ();
		//BYTE USE_SURFER = this->useSurfer ? 2 : 1;
		BYTE GRIDDATA_APP = (BYTE) this->m_griddata_application;
		long ID_ALG = (long)griddata_fun_number;
		this->m_pSurfDoc->GetLabDoc()->DefineGridDataUsedAlgorothm(id_obj, id_surf, GRIDDATA_APP, ID_ALG);
		this->m_pSurfDoc->GetLabDoc()->DefineGridDataZflag(id_obj, id_surf, zflag);
	}
	//====== Перерисовываем Вид с учетом изменений
	RECT rect;
	GetClientRect(this->m_pSurfDoc->hSurfWnd,&rect);
	InvalidateRect(this->m_pSurfDoc->hSurfWnd,&rect, true);
}
GridData::GridData()
{

	m_pSurfDoc = NULL;
	OnCreate();
}

GridData::GridData(SurfDoc* pSurfDoc)
{
	this->m_pSurfDoc				= pSurfDoc;
	OnCreate();
}
#define GRIDDATA_VERSION 5
void GridData::OnCreate(void)
{
	this->m_object_type = Object::object_type::grid_data;
	this->m_object_version = GRIDDATA_VERSION;
	this->m_max_object_version = GRIDDATA_VERSION;

	this->m_input_points.OnCreate();

	this->m_color = 0;
	m_to_draw_here = false;
	id_umpoz = 0;
	id_surf = -1;
	podoshva = 0;
	id_ige = -1;

	built = 0;
	griddata_fun_number = -1;
	griddata_app = -1;/// = use_surfer;
}

GridData::GridData(const GridData & bp)
{
	dynamic_cast<Object*>(this)->Init(bp);
	this->Init(bp);
}
GridData& GridData::operator=(const GridData& bp)
{
	if (this == &bp)
	{
		return *this;
	}

	dynamic_cast<Object*>(this)->Init(bp);
	this->Init(bp);

	return *this;
}

GridData::~GridData(void)
{
}
void GridData::AddLineToInput(Line3D * line)
{
	if (GridData::line_to_interpolate_points)
	{
		AddLineToInput_with_interpolation(line);
	}
	else
	{
		AddLineToInput_without_interpolation(line);
	}
}

#pragma warning (disable:4005)
#define INTERPOLATION 1
#define _AddLineToInput_ AddLineToInput_with_interpolation
#include "GriddataAddLine.h"
#define INTERPOLATION 0
#define _AddLineToInput_ AddLineToInput_without_interpolation
#include "GriddataAddLine.h"
#pragma warning (default:4005)

void GridData::AddInput(Primitive3D<CPoint3> * primitive)
{
	if (primitive)
	{
		long id_point = this->m_input_points.SetCurrentMsgOnLast() ? this->m_input_points.GetCurrentMsg().id_point + 1 : 1;
		for (unsigned int i = 0; i < primitive->GetPointsNumber(); i++)
		{
			ThePoint3D point(this->m_pSurfDoc);
			this->m_input_points.AddMsg(&point);
			this->m_input_points.GetLastMsg().InitPoints(&primitive->GetDocumentPoint(i), 1, primitive->GetColor());
			this->m_input_points.GetLastMsg().id_point = id_point++;
		}
		this->m_input_points_ObjectList.Init(this->m_input_points, this);
	}
}

ThePoint3D * GridData::AddInput(CPoint3 &pt, COLORREF color)
{
	long id_point = this->m_input_points.SetCurrentMsgOnLast() ? this->m_input_points.GetCurrentMsg().id_point + 1 : 1;
	ThePoint3D point(this->m_pSurfDoc);
	this->m_input_points.AddMsg(&point);
	this->m_input_points.GetLastMsg().InitPoints(&pt, 1, color);
	this->m_input_points.GetLastMsg().id_point = id_point;
	this->m_input_points_ObjectList.Init(this->m_input_points, this);
	return &this->m_input_points.GetLastMsg();
}

void GridData::AddDataFromDatFile()
{
	vector<double> x,y,z;
	if (OpenFileDlg(NULL, "Surfer 7 (*.dat)\0*.dat\0All files \0*.*\0") == S_OK)
	{
		if (ReadDatFile(szPath, x, y, z) == 0)
		{
			COLORREF color = this->GetColor();
			for (size_t i = 0; i < x.size() && i < y.size() && i < z.size(); i++)
			{
				this->AddInput(CPoint3(x[i], y[i], z[i]), color);
			}

			this->GrDtSaveToDB(podoshva);

			this->m_pSurfDoc->Zoom<GridData>(this->m_pSurfDoc->m_grid_data);
			ReDrawGridData(this->m_pSurfDoc);
			this->m_pSurfDoc->UpdateAllViews();
		}
		else
		{
			MessageBox(0, "Data file was not read", "ReadDatFile", 0);
		}
	}
}

bool GridData::UpdateExtremums()
{
	vector<CPoint3> vptmax,vptmin;

	if(this->m_input_points.SetCurrentMsgOnFirst())
	{
		do
		{
			if(m_input_points.GetCurrentMsg().UpdateExtremums())
			{
				vptmax.push_back(m_input_points.GetCurrentMsg().GetMax());
				vptmin.push_back(m_input_points.GetCurrentMsg().GetMin());
			}
		}
		while(this->m_input_points.IncrementCurrentMsg());
	}
	return this->Object::UpdateExtremums(vptmax,vptmin);
}

void GridData::Zoom(double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean)
{
	if (this->m_input_points.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_input_points.GetCurrentMsg().Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,
				y_mean,
				z_mean
				);
		}
		while(this->m_input_points.IncrementCurrentMsg());
	}
}
HTREEITEM GridData::AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s)
{
    char szItemText[1024]; // label text of tree-view item 
	//====== Размеры изображаемого объекта
	size_t	
		n_points = this->m_input_points.msgSize();	

	sprintf(szItemText, "\"%s\" id_surf=%d id_ige=%d", this->GetName().c_str(), this->id_surf, this->id_ige);
	Object * pObject = dynamic_cast<Object *> (this);
	//=============================================================
	// Add the item to the tree-view control. 
	HTREEITEM h2 = AddItemToTree(hwndTV, szItemText, pObject, h1); 
	//=============================================================
	sprintf(szItemText, "Grid Data points = %d", n_points);
	HTREEITEM h3 = AddObjectListItem(hwndTV, szItemText, &this->m_input_points_ObjectList, h2); 
	if (this->m_input_points.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_input_points.GetCurrentMsg().AddItem_ToTree(hwndTV,	h3, "");
		}
		while(this->m_input_points.IncrementCurrentMsg());
		return h2;
	}
	return NULL;
}
void GridData::Draw()
{
	if (this->m_input_points.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_input_points.GetCurrentMsg().Draw();
		}
		while(this->m_input_points.IncrementCurrentMsg());
	}
}

void GridData::ReDraw()
{
	if(this->m_pSurfDoc) this->ReDrawItem_OnTree(this->m_pSurfDoc->hwndTV);
	if (this->m_input_points.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_input_points.GetCurrentMsg().ReDraw();
		}
		while(this->m_input_points.IncrementCurrentMsg());
	}
}
void GridData::SetToDraw()
{
	if (this->m_pSurfDoc)
	{
		this->m_pSurfDoc->SetGridDataForDraw(this);
		if (this->m_pSurfDoc->m_grid_data.SetCurrentMsgOnFirst())
		{
			do
			{
				this->m_pSurfDoc->m_grid_data.GetCurrentMsg().m_to_draw_here = false;
			}
			while (this->m_pSurfDoc->m_grid_data.IncrementCurrentMsg());
		}
	}
	m_to_draw_here = true;
}
void GridData::UnsetToDraw()
{
	this->m_pSurfDoc->SetGridDataForDraw(NULL);
	m_to_draw_here = false;
}
#include "../../wintools\src\project.h"
#include "../../wintools\src\win32_map_views.h"
ThePoint3D * GridData::FindThePoint3D(long id_point)
{	
	ThePoint3D * found  = NULL;
	if (this->m_input_points.SetCurrentMsgOnFirst())
	{
		do
		{
			if (this->m_input_points.GetCurrentMsg().id_point == id_point)
			{
				found = &this->m_input_points.GetCurrentMsg();
				break;
			}

		}
		while(this->m_input_points.IncrementCurrentMsg());
	}
	return found;
}
void GridData::DrawGDIplus(Graphics ** select_buffer, Graphics& graphics, map_view * v, Profile3D * on)
{	
	double epsilon = 1.0e-2;
//	double epsilon = 3.0;

	fGL x; fGL y;

	v->PreConvertingFromWorldToScreen();


	fGL r = v->lines_points_radius;

	COLORREF color = m_color;
	Color gdi_color(255, GetRValue(color),GetGValue(color),GetBValue(color));
	Pen      pen(gdi_color);

	double dist_to_plane;
	CPoint2 profile;

	if (this->m_input_points.SetCurrentMsgOnFirst())
	{
		do
		{
			if (this->m_input_points.GetCurrentMsg().IsCheckedEx() 
				&& this->m_input_points.GetCurrentMsg().GetPointsNumber())
			{
				//this->m_input_points.GetCurrentMsg().DrawGDIplus(select_buffer, graphics, v, on);
				CPoint3 in = this->m_input_points.GetCurrentMsg().m_vdPoints[0];
				//Convert3D_To_2D
				on->Projection(in, profile, dist_to_plane);
				if(fabs(dist_to_plane) <= epsilon)
				{
					v->ConvertingFromWorldToScreen(profile.x, profile.y, x, y);
					if (m_to_draw_here)
						DrawCircle(&graphics, x, y, r, gdi_color);
					else
						FillCircle(&graphics, x, y, r, gdi_color);
				}
			}
		}
		while(this->m_input_points.IncrementCurrentMsg());
	}
}


bool GridData::IsSelectedGridDataPoint(gdiplus_map_view * gv, Profile3D * on, int mouse_x, int mouse_y, double & dist_to_line_object, WhatSelected& ws)
{
	bool result = false;
	if (!this->IsCheckedEx()) return result;
	double search_radius = fabs(gv->lines_points_radius);
	gv->PreConvertingFromWorldToScreen();
	double dist_to_plane;
	CPoint2 profile;		
	fGL x, y;

	//if (ws.m_what_to_select == WhatSelected::selected_objects_element_type::sel_point
	//	||
	//	ws.m_what_to_select == WhatSelected::selected_objects_element_type::sel_no_element)
	//{
	if (this->m_input_points.SetCurrentMsgOnFirst())
	{
		do
		{
			if (this->m_input_points.GetCurrentMsg().IsCheckedEx() 
				&& this->m_input_points.GetCurrentMsg().OnProfile(on)
				&& this->m_input_points.GetCurrentMsg().GetPointsNumber()
				)
			{
				//this->m_input_points.GetCurrentMsg().DrawGDIplus(select_buffer, graphics, v, on);
				CPoint3 in = this->m_input_points.GetCurrentMsg().m_vdPoints[0];
	

				//Convert3D_To_2D
				on->Projection(in, profile, dist_to_plane);
				gv->ConvertingFromWorldToScreen(profile.x, profile.y, x, y);	
				double dist_to_point = Distance(mouse_x, mouse_y, x, y);

				bool select = dist_to_line_object > dist_to_point;
				

				if (select)
				{
					if (dist_to_line_object > dist_to_point)
						dist_to_line_object = dist_to_point;
					ws.Init(dynamic_cast<Object*>(&this->m_input_points.GetCurrentMsg()), 
						WhatSelected::sel_point,
						0,-1,
						in
						//,	this->GetDocumentPoint(i)
						);

					result = true;
				}

			}
		}
		while(this->m_input_points.IncrementCurrentMsg());
	}


	//}
	return result;
}

bool GridData::IsSelected(CPoint3 selected_view_pt, 
		double search_radius,
		WhatSelected& ws)
{
	search_radius = fabs(search_radius);

	
	if (this->m_input_points.SetCurrentMsgOnFirst())
	{
		do
		{
			if(this->m_input_points.GetCurrentMsg().IsSelected(
				selected_view_pt, search_radius, ws	))
			{
				return true;
			}
		}
		while(this->m_input_points.IncrementCurrentMsg());
	}

	return false;
}

void GridData::EnumObjects(WPARAM wParam, LPARAM lParam, void * p,
		bool (Object::* condition_fun)(),
		void (* callback_fun)(Object*, WPARAM , LPARAM, void * ) )
{
	
	if (this->m_input_points.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_input_points.GetCurrentMsg().EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		}
		while(this->m_input_points.IncrementCurrentMsg());
	}
}
void GridData::SetLayer(const Layer* layer)
{
	this->SetLayer_NonVirtual(layer);
	if (this->m_input_points.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_input_points.GetCurrentMsg().SetLayer(layer);
		}
		while(this->m_input_points.IncrementCurrentMsg());
	}
}

void GridData::PropertiesDialog()
{
	MessageBox(0, "PropertiesDialog", "GridData" , 0);
}

bool GridData::ColorDialog(void)
{
	return false;
}

COLORREF GridData::GetColor(void)
{
	return m_color;
}

void GridData::SetColor(COLORREF color)
{
	this->m_color = color;
	if (this->m_input_points.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_input_points.GetCurrentMsg().SetColor(color);
		}
		while(this->m_input_points.IncrementCurrentMsg());
	}
}

void GridData::CutAndDisvisible(bool positive, double a, double b, double c, double d)
{
	if (this->m_input_points.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_input_points.GetCurrentMsg().CutAndDisvisible(positive, a, b, c, d);
		}
		while(this->m_input_points.IncrementCurrentMsg());
	}
}

void GridData::CutXYZandDisvisible(int subcube_number, double X, double Y, double Z)
{
	if (this->m_input_points.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_input_points.GetCurrentMsg().CutXYZandDisvisible(subcube_number, X, Y, Z);
		}
		while(this->m_input_points.IncrementCurrentMsg());
	}
}

Archive& operator <<(Archive& ar, GridData& ob)
{
//printf("Archive& operator <<(Archive& ar, GridData& ob)\n");
	//ar << *dynamic_cast<Object *>(&ob);
	DWORD version = ob.Object::Serialize(ar);
	switch (version)
	{
	case 5:
		{
			ar << ob.id_ige;
		}
	case 4:
		{
			ar << ob.z_flag;
		}
	case 3:
		{
			ar << ob.id_umpoz;
			ar << ob.id_surf;
			ar << ob.podoshva;
		}
	case 2:
		{
			ar << ob.m_color;
		}
	case 1:
		{
			// Objects' vectors
			ar << ob.m_input_points;			ar << ob.m_input_points_ObjectList;
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
Archive& operator >>(Archive& ar, GridData& ob)
{
//printf("Archive& operator >>(Archive& ar, GridData& ob)\n");
	//ar >> *dynamic_cast<Object *>(&ob);
	ob.Object::Serialize(ar);
	switch (ob.m_object_version)
	{
	case 5:
		{
			ar >> ob.id_ige;
		}
	case 4:
		{
			ar >> ob.z_flag;
		}
	case 3:
		{
			ar >> ob.id_umpoz;
			ar >> ob.id_surf;
			ar >> ob.podoshva;
		}
	case 2:
		{
			ar >> ob.m_color;
		}
	case 1:
		{
			// Objects' vectors
			ar >> ob.m_input_points;			ar >> ob.m_input_points_ObjectList;
			ob.m_input_points_ObjectList.Init(ob.m_input_points, &ob);
			
			ob.m_object_version = GRIDDATA_VERSION;
		}
		break;
	default:
		{
			throw VersionException(ob.m_object_version, VersionException::cannot_load, ob.m_object_type);
		}
		break;
	}
//printf("Archive& operator >>(Archive& ar, GridData& ob) end\n");
	return ar;
}

void GridData::FillContextMenu(HMENU& hMenu)
{
printf("GridData::FillContextMenu(HMENU& hMenu)\n");
#if !VIEW_ONLY_VERSION
	AppendMenu( hMenu, MFT_STRING, ID_TREE_GRIDDATA_GRIDDATA, "&Griddata" );
	//AppendMenu( hMenu, MFT_STRING, ID_TREE_GRIDDATA_GRIDDATAWITHOLESURFER, "Griddata by &Surfer" );
	
	AppendMenu( hMenu, MFT_SEPARATOR, 0, NULL );
	AppendMenu( hMenu, MFT_STRING, ID_TREE_GRIDDATA_SETTODRAW, "Set to draw" );
	AppendMenu( hMenu, MFT_STRING, ID_TREE_GRIDDATA_UNSETTODRAW, "Unset to draw" );
	
	AppendMenu( hMenu, MFT_SEPARATOR, 0, NULL );
	AppendMenu( hMenu, MFT_STRING, ID_TREE_GRIDDATA_ADDDATAFROMDATFILE, "Add Data From Dat File" );
	
	AppendMenu( hMenu, MFT_SEPARATOR, 0, NULL );
#endif /*#if !VIEW_ONLY_VERSION*/
	this->Object::FillContextMenu(hMenu);
}
bool GridData::SaveAs()
{
	bool status = false;
	TCHAR lpstrFile[256]; lpstrFile[0] = '\0';
	TCHAR filter[] =     
		TEXT("Golden Software Data (*.dat)\0*.dat\0")
		TEXT("Golden Software Blanking (*.bln)\0*.bln\0")
		TEXT("All Files (*.*)\0*.*\0");

	//sprintf(lpstrFile, "%s\\razrez", directory);
	sprintf(lpstrFile, "%s", this->GetName().c_str());
	DWORD nFilterIndex = 0;
	if (SaveFileDlg(0, lpstrFile, filter, nFilterIndex) != S_OK)
		return status;
	FILE *stream;
	stream = fopen(lpstrFile,"wt");
	if (!stream)
	{
		return status;
	}
	switch (nFilterIndex)
	{
	case 1:
		if(this->m_input_points.SetCurrentMsgOnFirst())
		{
			do
			{
				status = this->m_input_points.GetCurrentMsg().SaveAsDat(stream);
			}
			while(this->m_input_points.IncrementCurrentMsg());
		}
		break;
	case 2:
		if(this->m_input_points.SetCurrentMsgOnFirst())
		{
			do
			{
				status = this->m_input_points.GetCurrentMsg().SaveAsBln(stream);
			}
			while(this->m_input_points.IncrementCurrentMsg());
		}
		break;
	}
	fclose (stream);
	return status;
}

//bool GridData::griddata_by_surfer(void)
//{
//	// modal dialog
//	griddata_dialog(this->m_pSurfDoc, this, this->m_pSurfDoc->hSurfWnd, true, NULL, false, false);
//	return false;
//}

bool GridData::griddata(void)
{
	/*if (this->m_pSurfDoc)
		return this->griddata(this->m_pSurfDoc->m_cube_size);
*/
	// modal dialog
	bool to_allocate = true;
	griddata_dialog(to_allocate, this->m_pSurfDoc, this, this->m_pSurfDoc->hSurfWnd, griddata_dialog::griddata_application::unknown, NULL, false, false);
	

	return false;
}
bool GridData::griddata(CubeSize & cube_size)
{
	if (!cube_size.Defined())
	{
		MessageBox(0, "!cube_size.Defined()", "GridData::griddata", 0);
		return false;
	}
	if (!this->m_pSurfDoc)
	{
		MessageBox(0, "!cube_size.Defined()", "GridData::griddata", 0);
	}
	vdouble xi,yi,zi;
	//vdouble x,y,z;
	vector<double> x,y,z;
	vdouble visible;
	HWND hWnd = NULL;
	if (this->m_pSurfDoc)
		hWnd = this->m_pSurfDoc->hSurfWnd;

	size_t i=0, len = this->m_input_points.msgSize();
	x.resize(len);
	y.resize(len);
	z.resize(len);

	if(this->m_input_points.SetCurrentMsgOnFirst())
	{
		do
		{
			x[i] = this->m_input_points.GetCurrentMsg().GetFirstDocumentPoint().x;
			y[i] = this->m_input_points.GetCurrentMsg().GetFirstDocumentPoint().y;
			z[i] = this->m_input_points.GetCurrentMsg().GetFirstDocumentPoint().z;
			
			i++;		
		}
		while(this->m_input_points.IncrementCurrentMsg());
	}

	short zflag = 0;
	COLORREF color = RGB(0,255,0);

/*	if (Dz < Dx && Dz < Dy)
	{
		zflag = 0;
	}
	else
	{
		color = RGB(255,0,0);
		if (Dx < Dy)
			zflag = 2;
		else
			zflag = 1;
	}
*/
	zflag = 0;

	switch (zflag)
	{
	case 0:
		{
			xi = dsequence(double(cube_size.xLL), double(cube_size.xSize), long(cube_size.nCol));
			yi = dsequence(double(cube_size.yLL), double(cube_size.ySize), long(cube_size.nRow));
			zi.resize(xi.Length(), yi.Length(), 0.0 );
			correct_dublicate(x, y, z);
			if (::griddata(hWnd, x, y, z, NULL, &xi, &yi, &zi) != 0)
			{
				return false;
			}
		}
		break;
	case 1:
		{
			xi = dsequence(double(cube_size.zLL), double(cube_size.zSize), long(cube_size.nPag));
			yi = dsequence(double(cube_size.yLL), double(cube_size.ySize), long(cube_size.nRow));
			zi.resize(xi.Length(), yi.Length(), 0.0 );
			//visible.resize(xi.Length(), yi.Length(), 1.0 );
			correct_dublicate(z, y, x);
			if (::griddata(hWnd, z, y, x, NULL, &xi, &yi, &zi) != 0)
			{
				return false;
			}
		}
		break;
	case 2:
		{
			xi = dsequence(double(cube_size.xLL), double(cube_size.xSize), long(cube_size.nCol));
			yi = dsequence(double(cube_size.zLL), double(cube_size.zSize), long(cube_size.nPag));
			zi.resize(xi.Length(), yi.Length(), 0.0 );
			//visible.resize(xi.Length(), yi.Length(), 1.0 );
			correct_dublicate(x, z, y);
			if (::griddata(hWnd, x, z, y, NULL, &xi, &yi, &zi) != 0)
			{
				return false;
			}
		}
		break;
	}

	//Surface3D surf;
	//surf.Init(zflag,xi,yi,zi,visible,color);

	strcpy(szPath, this->GetName().c_str());

	if (zflag == 0)
	{
		if (IDYES == MessageBox(0, "Это разлом?", "Определите тип поверхности", MB_YESNO))
		{
			zflag = 3;
			color = RGB(255,0,0);
		}			
	}

	long id_surf = m_pSurfDoc->GetIDSurfForNewGridDataOrSurface();
	BYTE podoshva = 0;
	this->m_pSurfDoc->AddSurf(id_surf, podoshva, zflag,xi,yi,zi,visible,color);
	if (zflag == 0)
	{
		this->m_pSurfDoc->m_surfaces.GetLastMsg().Zooming();		
		this->m_pSurfDoc->m_surfaces.GetLastMsg().Draw();

		if (this->m_pSurfDoc->m_surfaces_ObjectList.myTreeItem == NULL)
		{
			HTREEITEM h1 = AddObjectListItem(this->m_pSurfDoc->hwndTV, "Surfaces", &this->m_pSurfDoc->m_surfaces_ObjectList);
		}
		this->m_pSurfDoc->m_surfaces.GetLastMsg().AddItem_ToTree(this->m_pSurfDoc->hwndTV, this->m_pSurfDoc->m_surfaces_ObjectList.myTreeItem);
	}
	/*
	if (zflag == 1 || zflag == 2 || zflag == 3)
	{
		{
			void * pBrokenPlane = NULL;

			short type_of_cutline = 6;//blank line

			CPoint2 *pt1 = NULL, *pt2 = NULL;
			int surf_number = 0;

			int cutting_number = 0;
			bool toDrawPoligones = true;
			bool positive = false; 

			this->m_pSurfDoc->m_faults.GetLastMsg().m_surface.Cutting(0.0, 0.0, 1.0, -zmax, 
				toDrawPoligones, positive, 
				type_of_cutline, cutting_number, surf_number, 
				pt1, pt2, pBrokenPlane, (void *) &this->m_pSurfDoc->m_faults.GetLastMsg());

			this->m_pSurfDoc->m_faults.GetLastMsg().m_surface.Cutting(0.0, 0.0, 1.0, -zmin, 
				toDrawPoligones, positive, 
				type_of_cutline, cutting_number, surf_number, 
				pt1, pt2, pBrokenPlane, (void *) &this->m_pSurfDoc->m_faults.GetLastMsg());

			this->m_pSurfDoc->m_faults.GetLastMsg().m_surface.CutLine( type_of_cutline, cutting_number, pBrokenPlane,  
				(void *) &this->m_pSurfDoc->m_faults.GetLastMsg(), surf_number );

			CPoint3 ptmax, ptmin;
			this->m_pSurfDoc->m_faults.GetLastMsg().BlankWithOwnBlankLines(true, true, &mean_pt);


		}

		this->m_pSurfDoc->m_faults.GetLastMsg().Zooming();
		this->m_pSurfDoc->m_faults.GetLastMsg().Draw();


	}*/
	return true;
}

short GridData::DetermineRazlomZflag()
{
	short zflag = 0;
	double x, y, z;
	double xmin = DBL_MAX, ymin = DBL_MAX, zmin = DBL_MAX;
	double xmax = -DBL_MAX, ymax = -DBL_MAX, zmax = -DBL_MAX;

	if (this->m_input_points.SetCurrentMsgOnFirst())
	{
		do
		{
			x = this->m_input_points.GetCurrentMsg().GetFirstDocumentPoint().x;
			y = this->m_input_points.GetCurrentMsg().GetFirstDocumentPoint().y;
			z = this->m_input_points.GetCurrentMsg().GetFirstDocumentPoint().z;

			if (xmin > x) xmin = x;
			if (xmax < x) xmax = x;

			if (ymin > y) ymin = y;
			if (ymax < y) ymax = y;

			if (zmin > z) zmin = z;
			if (zmax < z) zmax = z;

		}
		while (this->m_input_points.IncrementCurrentMsg());
	}


	double Dx = xmax - xmin;
	double Dy = ymax - ymin;
	double Dz = zmax - zmin;

	/*if (Dz < Dx && Dz < Dy)
	{
		zflag = 3;
	}
	else*/
	{
		if (Dx < Dy)
			zflag = 2;
		else
			zflag = 1;
	}
	return zflag;
}

bool GridData::griddata_old()
{
	vdouble xi,yi,zi;
	//vdouble x,y,z;
	vector<double> x,y,z;
	vdouble visible;
	HWND hWnd = NULL;
	if (this->m_pSurfDoc)
		hWnd = this->m_pSurfDoc->hSurfWnd;

	size_t i=0, len = this->m_input_points.msgSize();
	x.resize(len);
	y.resize(len);
	z.resize(len);

	double xmin = DBL_MAX, ymin = DBL_MAX, zmin = DBL_MAX;
	double xmax = -DBL_MAX, ymax = -DBL_MAX, zmax = -DBL_MAX;
	double xmean = 0.0, ymean = 0.0, zmean = 0.0;
	if(this->m_input_points.SetCurrentMsgOnFirst())
	{
		do
		{
			x[i] = this->m_input_points.GetCurrentMsg().GetFirstDocumentPoint().x;
			y[i] = this->m_input_points.GetCurrentMsg().GetFirstDocumentPoint().y;
			z[i] = this->m_input_points.GetCurrentMsg().GetFirstDocumentPoint().z;

			if (xmin > x[i]) xmin = x[i];
			if (xmax < x[i]) xmax = x[i];

			if (ymin > y[i]) ymin = y[i];
			if (ymax < y[i]) ymax = y[i];

			if (zmin > z[i]) zmin = z[i];
			if (zmax < z[i]) zmax = z[i];

			xmean += x[i];
			ymean += y[i];
			zmean += z[i];



		printf("%d [%f %f %f]\n", i, x[i], y[i], z[i]);
			i++;
		}
		while(this->m_input_points.IncrementCurrentMsg());
	}

	xmean /= len;
	ymean /= len;
	zmean /= len;



	double Dx = xmax - xmin;
	double Dy = ymax - ymin;
	double Dz = zmax - zmin;

	CPoint3 mean_pt = CPoint3(xmean, ymean, zmean);

	short zflag = 0;
	COLORREF color = RGB(0,255,0);

	if (Dz < Dx && Dz < Dy)
	{
		zflag = 0;
	}
	else
	{
		color = RGB(255,0,0);
		if (Dx < Dy)
			zflag = 2;
		else
			zflag = 1;
	}

zflag = 0;

	switch (zflag)
	{
	case 0:
		{
			xi = dsequence(double(xmin), long(60), double(xmax));
			yi = dsequence(double(ymin), long(50), double(ymax));
			//xi = dsequence(double(x.Min()), double(40), double(x.Max()));
			//yi = dsequence(double(y.Min()), double(40), double(y.Max()));
			zi.resize(xi.Length(), yi.Length(), 0.0 );
			//visible.resize(xi.Length(), yi.Length(), 1.0 );
			if (::griddata(hWnd, x, y, z, NULL, &xi, &yi, &zi) != 0)
			{
				return false;
			}
		}
		break;
	case 1:
		{
		//if(zflag == 1)
			xi = dsequence(double(zmin), long(50), double(zmax));
			yi = dsequence(double(ymin), long(50), double(ymax));
			//xi = dsequence(double(z.Min()), double(50), double(z.Max()));
			//yi = dsequence(double(y.Min()), double(50), double(y.Max()));
			zi.resize(xi.Length(), yi.Length(), 0.0 );
			//visible.resize(xi.Length(), yi.Length(), 1.0 );
			if (::griddata(hWnd, z, y, x, NULL, &xi, &yi, &zi) != 0)
			{
				return false;
			}
		}
		break;
	case 2:
		{
		//if(zflag == 2)
			xi = dsequence(double(xmin), long(50), double(xmax));
			yi = dsequence(double(zmin), long(50), double(zmax));
			//xi = dsequence(double(x.Min()), double(50), double(x.Max()));
			//yi = dsequence(double(z.Min()), double(50), double(z.Max()));
			zi.resize(xi.Length(), yi.Length(), 0.0 );
			//visible.resize(xi.Length(), yi.Length(), 1.0 );
			if (::griddata(hWnd, x, z, y, NULL, &xi, &yi, &zi) != 0)
			{
				return false;
			}
		}
		break;
	}

	//Surface3D surf;
	//surf.Init(zflag,xi,yi,zi,visible,color);

	strcpy(szPath, this->GetName().c_str());

	if (zflag == 0)
	{
		if (IDYES == MessageBox(0, "Это разлом?", "Определите тип поверхности", MB_YESNO))
		{
			zflag = 3;
			color = RGB(255,0,0);
		}			
	}

	long id_surf = m_pSurfDoc->GetIDSurfForNewGridDataOrSurface();
	BYTE podoshva = 0;
	this->m_pSurfDoc->AddSurf(id_surf, podoshva, zflag,xi,yi,zi,visible,color);
	if (zflag == 0)
	{
		this->m_pSurfDoc->m_surfaces.GetLastMsg().Zooming();
		this->m_pSurfDoc->m_surfaces.GetLastMsg().Draw();
	}
	if (zflag == 1 || zflag == 2 || zflag == 3)
	{
		{
			void * pBrokenPlane = NULL;

			short type_of_cutline = 6;//blank line

			CPoint2 *pt1 = NULL, *pt2 = NULL;
			int surf_number = 0;

			int cutting_number = 0;
			bool toDrawPoligones = true;
			bool positive = false; 

			this->m_pSurfDoc->m_faults.GetLastMsg().m_surface.Cutting(0.0, 0.0, 1.0, -zmax, 
				toDrawPoligones, positive, 
				type_of_cutline, cutting_number, surf_number, 
				pt1, pt2, pBrokenPlane, 
				&this->m_pSurfDoc->m_faults.GetLastMsg(),
				&this->m_pSurfDoc->m_faults.GetLastMsg().m_blank_polygon_matrix,
				&this->m_pSurfDoc->m_faults.GetLastMsg().m_cutplane_polygones_ObjectList,
				&this->m_pSurfDoc->m_faults.GetLastMsg().m_cutplane_polygones);

			this->m_pSurfDoc->m_faults.GetLastMsg().m_surface.Cutting(0.0, 0.0, 1.0, -zmin, 
				toDrawPoligones, positive, 
				type_of_cutline, cutting_number, surf_number, 
				pt1, pt2, pBrokenPlane, 
				&this->m_pSurfDoc->m_faults.GetLastMsg(), 
				&this->m_pSurfDoc->m_faults.GetLastMsg().m_blank_polygon_matrix, 
				&this->m_pSurfDoc->m_faults.GetLastMsg().m_cutplane_polygones_ObjectList,
				&this->m_pSurfDoc->m_faults.GetLastMsg().m_cutplane_polygones);

			this->m_pSurfDoc->m_faults.GetLastMsg().m_surface.CutLine( type_of_cutline, cutting_number, pBrokenPlane,  
				this->m_pSurfDoc->m_faults.GetLastMsg(), surf_number );

			CPoint3 ptmax, ptmin;
			this->m_pSurfDoc->m_faults.GetLastMsg().BlankWithOwnBlankLines(true, true, &mean_pt);


		}

		this->m_pSurfDoc->m_faults.GetLastMsg().Zooming();
		this->m_pSurfDoc->m_faults.GetLastMsg().Draw();
	}
	return true;
}



void GridData::SetName(string s)
{
	this->Object::SetName(s);
	if (this->m_pSurfDoc && this->m_pSurfDoc->GetLabDoc())
	{
		long id_obj = this->m_pSurfDoc->Get_ID_OBJ();
		CString nazva = this->GetName().c_str();
		this->m_pSurfDoc->GetLabDoc()->ReNameGridDataSurface(id_obj, id_surf, nazva);
	}

	if (this->m_pSurfDoc)
	{
		if(this->m_pSurfDoc->m_surfaces.SetCurrentMsgOnFirst())
		{
			do
			{
				if (this->id_surf == this->m_pSurfDoc->m_surfaces.GetCurrentMsg().id_surf)
				{
					this->m_pSurfDoc->m_surfaces.GetCurrentMsg().SetName(s);
					this->m_pSurfDoc->m_surfaces.GetCurrentMsg().ReDrawItem_OnTree(this->m_pSurfDoc->hwndTV);
				}				
			}
			while(this->m_pSurfDoc->m_surfaces.IncrementCurrentMsg());
		}

		for (vector<surface_blank_functions_list_item *>::iterator 
			it = GeoSurface::surface_blank_functions_list.begin();
			it != GeoSurface::surface_blank_functions_list.end(); it++)
		{
			this->m_pSurfDoc->InitSurfaceBlankFinctionNames(*it);
		}

	}
	for (vector<surface_order_list_item *>::iterator 
		it = GeoSurface::surface_order_list.begin();
		it != GeoSurface::surface_order_list.end(); it++)
	{
		if (*it && (*it)->id_surf == this->id_surf)
		{
			(*it)->my_name = s;
		}
	}
}

bool GridData::GrDtSaveToDB(BYTE podosva)
{
	//podosva = 1 - подошва 
	//        = 2 - кровля
	//		  = 3 - вода

	if (this->m_pSurfDoc && this->m_pSurfDoc->GetLabDoc())
	{
		long id_obj = this->m_pSurfDoc->Get_ID_OBJ();
		this->m_pSurfDoc->GetLabDoc()->ClearGridData(id_obj, id_surf);

		CString nazva = this->GetName().c_str();

		;

		this->m_pSurfDoc->GetLabDoc()->AddGridDataSurface(id_obj, id_surf, nazva, podosva, this->GetColor(), this->id_umpoz);
		

		if(this->m_input_points.SetCurrentMsgOnFirst())
		{
			do
			{
				long id_point = this->m_input_points.GetCurrentMsg().id_point;
				double X = this->m_input_points.GetCurrentMsg().GetFirstDocumentPoint().x;
				double Y = this->m_input_points.GetCurrentMsg().GetFirstDocumentPoint().y;
				double Z = this->m_input_points.GetCurrentMsg().GetFirstDocumentPoint().z;
				
				this->m_pSurfDoc->GetLabDoc()->AddGridData(id_obj, id_surf, id_point, X, Y, Z);
			}
			while(this->m_input_points.IncrementCurrentMsg());
		}
		return true;
	}
	return false;
}


int GridData::ClearFromDB(bool msg)
{
	int ans = IDYES;
	if (this->m_pSurfDoc && this->m_pSurfDoc->GetLabDoc())
	{
		bool to_clear = true;
		if (msg)
		{
			ans = MessageBox(0, "Удалить объект гриддаты также и из базы?", "GridData::ClearFromDB", MB_YESNOCANCEL);
			to_clear = IDYES == ans;
		}
		if (to_clear)
		{
			long id_obj = this->m_pSurfDoc->Get_ID_OBJ();
			this->m_pSurfDoc->GetLabDoc()->ClearGridData(id_obj, id_surf);	
			this->m_pSurfDoc->GetLabDoc()->ClearSurfIgeMappingItem(id_obj, id_surf);	
			this->m_pSurfDoc->GetLabDoc()->ClearSurfLitoMappingItem(id_obj, id_surf);	
			this->m_pSurfDoc->ClearSurfIgeMappingItem(id_surf);	
			this->m_pSurfDoc->ClearSurfLitoMappingItem(id_surf);	
		}
	}
	return ans;
}

int GridData::ClearPointFromDB(bool msg, long id_point)
{
	int ans = IDYES;
	if (this->m_pSurfDoc && this->m_pSurfDoc->GetLabDoc())
	{
		ans = MessageBox(0, "Удалить точку гриддаты также и из базы?", "ClearPointFromDB", MB_YESNOCANCEL);
		bool to_clear = msg ? IDYES == ans : true;
		if (to_clear)
		{
			long id_obj = this->m_pSurfDoc->Get_ID_OBJ();
			this->m_pSurfDoc->GetLabDoc()->ClearGridDataPoint(id_obj, id_surf, id_point);	
		}
	}
	return ans;
}