// Grid.cpp: implementation of the CGrid class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
#include <cderr.h>
#endif
#include "../../array/src/Vdouble.h"
#include "../../array/src/matrixes.h"
#include "Archive.h"
#include "../../tools/src/filedlg.h"

#include <fstream>
#include <iostream>
using namespace std;


#include "Grid.h"
extern int ReadContourBlnFile(vdouble& x, vdouble& y);


extern HINSTANCE hInst;   // текущий экземпляр
extern char szPath[];

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//#if !FAST_GRID_LOADING
CGrid::CGrid(Widget hwnd)
{
	hwndParent = hwnd;
}

CGrid::CGrid()
{
	hwndParent = NULL;
}

CGrid::~CGrid()
{

}

void CGrid::Init(Grid* pGrid)
{
printf ("CGrid::Init(Grid* pGrid)\n");
	xi = dsequence(pGrid->gridSection.xLL, pGrid->gridSection.xSize, pGrid->gridSection.nCol);
	yi = dsequence(pGrid->gridSection.yLL, pGrid->gridSection.ySize, pGrid->gridSection.nRow);
    zi.resize((const int)pGrid->gridSection.nRow, (const int)pGrid->gridSection.nCol);
	visible.resize(pGrid->gridSection.nRow, pGrid->gridSection.nCol, 1.0);
	
	//MessageBox(0,"1","",0);

	//FILE * stream;
	//stream = fopen("d://-.txt","wt");
	//fclose(stream);

	for (uint32_t r = 0; r < pGrid->gridSection.nRow; r++)
	{
		for (uint32_t c = 0; c < pGrid->gridSection.nCol; c++)
		{
			//stream = fopen("d://-.txt","at");
			//fprintf(stream, "r = %d c = %d ", r,c);
			//fclose(stream);

			zi(r,c) = pGrid->gridSection.z[r][c];
			if (pGrid->gridSection.z[r][c] > pGrid->gridSection.zMax)
			{
				visible(r,c) = 0.0;
				zi(r,c) = pGrid->gridSection.zMin;
			}


			//stream = fopen("d://-.txt","at");
			//fprintf(stream, "z = %lf\n", pGrid->z[r][c]);
			//fprintf(stream, "\n");
			//fclose(stream);
		}
	}
	//MessageBox(0,"end","CGrid::Init",0);
printf ("CGrid::Init(Grid* pGrid) end\n");

}

int CGrid::ReadContourBlnFile()
{
	return ::ReadContourBlnFile(xc, yc);
}

int CGrid::SetVisiblePointsInContour()
{
	return ::SetVisiblePointsInContour(hwndParent,xi, yi, xc, yc, visible);
}

int CGrid::SaveAsSurferGrid7(LPTSTR lpstrFile)
{
	return ::SaveAsSurferGrid7(hwndParent, lpstrFile, xi, yi, zi, visible);
}

double CGrid::GetXMin()
{
	return xi.Min();
}

double CGrid::GetXMax()
{
	return xi.Max();
}

double CGrid::GetYMin()
{
	return yi.Min();
}

double CGrid::GetYMax()
{
	return yi.Max();
}

//#endif /*!FAST_GRID_LOADING*/



int SaveAsSurferGrid7(Widget hWnd, LPTSTR lpstrFile,
					  uint32_t nRow, 
					  uint32_t nCol, 
					  double xLL, // X coordinate of the lower left corner of the grid
					  double yLL, // Y coordinate of the lower left corner of the grid
					  double xSize, // spacing between adjacent nodes in the X direction (between columns)
					  double ySize, // spacing between adjacent nodes in the Y direction (between rows)
					  double zMin, // minimum Z value within the grid
					  double zMax, // maximum Z value within the grid
					  double ** z, int ** visible)
{
    HRESULT hr = S_OK;

    static TCHAR file[256];
    static TCHAR szFilepath[256];
    static TCHAR fileTitle[256];
    static TCHAR filter[] =
                           TEXT("Surfer 7 (*.grd)\0*.grd\0")
                           TEXT("All Files (*.*)\0*.*\0");
    strcpy( file, lpstrFile);
    strcpy( fileTitle, TEXT(""));
    //strcpy( fileTitle, lpstrFile);

    DWORD nFilterIndex;
    if (SaveFileDlg(hWnd, lpstrFile, filter, nFilterIndex) != S_OK)
        return -1;
#if 0 //defined (_MSC_VER)
//    SSavePlotData spdData;
    OPENFILENAME ofn;


    memset( &ofn, 0, sizeof(ofn) );
    ofn.lStructSize       = sizeof(OPENFILENAME);
    ofn.hwndOwner         = hWnd;
    ofn.hInstance         = hInst;
    ofn.lpstrFilter       = filter;
    ofn.lpstrCustomFilter = NULL;
    ofn.nMaxCustFilter    = 0L;
    ofn.nFilterIndex      = 1L;
    ofn.lpstrFile         = file;
    ofn.nMaxFile          = sizeof(file);
    ofn.lpstrFileTitle    = fileTitle;
    ofn.nMaxFileTitle     = sizeof(fileTitle);
    ofn.lpstrInitialDir   = NULL;
    ofn.lpstrDefExt       = NULL;
//    ofn.lCustData         = (LPARAM)&spdData;
//    ofn.lpfnHook          = DlgProcSaveMesh;
    ofn.lpTemplateName    = MAKEINTRESOURCE(IDD_SAVEPLOT);
    ofn.Flags = OFN_OVERWRITEPROMPT | OFN_EXPLORER | OFN_ENABLETEMPLATE | OFN_ENABLEHOOK;

//    spdData.bSaveSelectedOnly = FALSE;
//    spdData.bSaveHierarchy = TRUE;
//    spdData.bSaveAnimation = TRUE;
//    spdData.xFormat = 0;//D3DXF_FILEFORMAT_TEXT;


    if ( ! GetSaveFileName( &ofn) )
    {
        char s[40];
        DWORD dwErr = CommDlgExtendedError();
		switch(dwErr)
		{
		case CDERR_DIALOGFAILURE :
			MessageBox(0,"The dialog box could not be created. ","CommDlgExtendedError",0);
			break;
		case CDERR_FINDRESFAILURE :
			MessageBox(0,"The common dialog box function failed to find a specified resource.","CommDlgExtendedError",0);
			break;
		case CDERR_INITIALIZATION :
			MessageBox(0,"The common dialog box function failed during initialization. This error often occurs when sufficient memory is not available","CommDlgExtendedError",0);
			break;
		case CDERR_LOADRESFAILURE :
			MessageBox(0,"The common dialog box function failed to load a specified resource.","CommDlgExtendedError",0);
			break;
		case CDERR_LOADSTRFAILURE :
			MessageBox(0,"The common dialog box function failed to load a specified string.","CommDlgExtendedError",0);
			break;
		case CDERR_LOCKRESFAILURE :
			MessageBox(0,"The common dialog box function failed to lock a specified resource.","CommDlgExtendedError",0);
			break;
		case CDERR_MEMALLOCFAILURE :
			MessageBox(0,"The common dialog box function was unable to allocate memory for internal structures.","CommDlgExtendedError",0);
			break;
		case CDERR_MEMLOCKFAILURE :
			MessageBox(0,"The common dialog box function was unable to lock the memory associated with a handle.","CommDlgExtendedError",0);
			break;
		case CDERR_NOHINSTANCE :
			MessageBox(0,"The ENABLETEMPLATE flag was set in the Flags member of the initialization structure for the corresponding common dialog box, but you failed to provide a corresponding instance handle.","CommDlgExtendedError",0);
			break;
		case CDERR_NOHOOK :
			MessageBox(0,"The ENABLEHOOK flag was set in the Flags member of the initialization structure for the corresponding common dialog box, but you failed to provide a pointer to a corresponding hook procedure.","CommDlgExtendedError",0);
			break;
		case CDERR_NOTEMPLATE :
			MessageBox(0,"The ENABLETEMPLATE flag was set in the Flags member of the initialization structure for the corresponding common dialog box, but you failed to provide a corresponding template.","CommDlgExtendedError",0);
			break;
		case CDERR_REGISTERMSGFAIL :
			MessageBox(0,"The RegisterWindowMessage function returned an error code when it was called by the common dialog box function.","CommDlgExtendedError",0);
			break;
		case CDERR_STRUCTSIZE :
			MessageBox(0,"The lStructSize member of the initialization structure for the corresponding common dialog box is invalid.","CommDlgExtendedError",0);
			break;
		case FNERR_BUFFERTOOSMALL :
			MessageBox(0,"The buffer pointed to by the lpstrFile member of the OPENFILENAME structure is too small for the file name specified by the user. The first two bytes of the lpstrFile buffer contain an integer value specifying the size, in TCHARs, required to receive the full name. ","CommDlgExtendedError",0);
			break;
		case FNERR_INVALIDFILENAME :
			{
				char err_str[255];
				sprintf(err_str, "A file name is invalid.\n%s", ofn.lpstrFile );
				MessageBox(0,err_str,"CommDlgExtendedError",0);
			}
			break;
		case FNERR_SUBCLASSFAILURE :
			MessageBox(0,"An attempt to subclass a List box failed because sufficient memory was not available.","CommDlgExtendedError",0);
			break;

		}
        if ( 0 != dwErr )
        {
            memset( &ofn, 0, sizeof(OPENFILENAME) );
            ofn.lStructSize       = 1024;//sizeof(OPENFILENAME_NT4W);
            ofn.hwndOwner         = hWnd;
            ofn.hInstance         = hInst;
            ofn.lpstrFilter       = filter;
            ofn.lpstrCustomFilter = NULL;
            ofn.nMaxCustFilter    = 0L;
            ofn.nFilterIndex      = 1L;
            ofn.lpstrFile         = file;
            ofn.nMaxFile          = sizeof(file);
            ofn.lpstrFileTitle    = fileTitle;
            ofn.nMaxFileTitle     = sizeof(fileTitle);
            ofn.lpstrInitialDir   = NULL;
            ofn.lpstrDefExt       = NULL;
//            ofn.lCustData         = (LPARAM)&spdData;
//            ofn.lpfnHook          = DlgProcSaveMesh;
            ofn.lpTemplateName    = MAKEINTRESOURCE(IDD_SAVEPLOT);
            ofn.Flags = OFN_OVERWRITEPROMPT | OFN_EXPLORER | OFN_ENABLETEMPLATE | OFN_ENABLEHOOK;

            if ( ! GetSaveFileName( &ofn) )
            {
                dwErr = CommDlgExtendedError();
                if ( 0 != dwErr )
                {
                    sprintf( s, "GetOpenFileName failed with %x", dwErr );
                    MessageBox( hWnd, s, "TexWin", MB_OK | MB_SYSTEMMODAL );
                }

				if (FAILED(hr))
				{
					MessageBox( hWnd, "Unabled to save the specified file!", "Save failed!", MB_OK);
				}

				return -1;
            }
        }
        else  // just a cancel, return
        {
			if (FAILED(hr))
			{
				MessageBox( hWnd, "Unabled to save the specified file!", "Save failed!", MB_OK);
			}

			return -1;
        }
    }
#endif
    if (nFilterIndex == 1)
		strcat(file, ".grd");


	char *p, ext[255];
	FILE *stream;

	p = strrchr(file,'.');
	if (p)
	{
		if (p && strcmp(ext, "grd") == 0)
		{
		}
		else
		{
			strcpy(p, ".grd");
		}
	}
	else
	{
		strcat(file, ".grd");
	}

	if ((stream = fopen(file,"wb")) == NULL)
	{
		char errstr[1024];
		sprintf(errstr, "Cannot open output file.\n%s", szPath);
		MessageBox(0, errstr, "SaveAsSurferGrid7", 
			MB_OK | MB_ICONINFORMATION);
		return -1;
	}

	size_t wrote;

	// Записываем
	uint32_t headerID = 0x42525344;
	wrote = fwrite(&headerID, sizeof(uint32_t), 1, stream);

	uint32_t headerSize = 4;
	wrote = fwrite(&headerSize, sizeof(uint32_t), 1, stream);

	uint32_t Version = 4;
	wrote = fwrite(&Version, sizeof(uint32_t), 1, stream);
		
	uint32_t gridID = 0x44495247;
	wrote = fwrite(&gridID, sizeof(uint32_t), 1, stream);
	
	uint32_t gridSize = 72;
	wrote = fwrite(&gridSize, sizeof(uint32_t), 1, stream);


//	uint32_t nRow = yi.Length();// number of rows in the grid
	wrote = fwrite(&nRow, sizeof(uint32_t), 1, stream);


//	uint32_t nCol = xi.Length();// number of columns in the grid
	wrote = fwrite(&nCol, sizeof(uint32_t), 1, stream);


//	double xLL = xi[0];// X coordinate of the lower left corner of the grid
	wrote = fwrite(&xLL, sizeof(double), 1, stream);


//	double yLL = yi[0];// Y coordinate of the lower left corner of the grid
	wrote = fwrite(&yLL, sizeof(double), 1, stream);


//	double xSize = xi[1] - xi[0];// spacing between adjacent nodes in the X direction (between columns)
	wrote = fwrite(&xSize, sizeof(double), 1, stream);


//	double ySize = yi[1] - yi[0];// spacing between adjacent nodes in the Y direction (between rows)
	wrote = fwrite(&ySize, sizeof(double), 1, stream);


//	double zMin = zi.Min();// minimum Z value within the grid
	wrote = fwrite(&zMin, sizeof(double), 1, stream);


//	double zMax = zi.Max();// maximum Z value within the grid
	wrote = fwrite(&zMax, sizeof(double), 1, stream);


	double Rotation = 0.0;// not currently used
	wrote = fwrite(&Rotation, sizeof(double), 1, stream);


	double BlankValue = BLANK_VALUE;//1.70141e38;// nodes are blanked if greater or equal to this value
	wrote = fwrite(&BlankValue, sizeof(double), 1, stream);

	uint32_t dataID = 0x41544144;
	wrote = fwrite(&dataID, sizeof(uint32_t), 1, stream);

	uint32_t dataSize = nRow*nCol*sizeof(double);
	wrote = fwrite(&dataSize, sizeof(uint32_t), 1, stream);

	uint32_t r, c;


	for (r = 0; r < nRow; r++)
	{
		for (c = 0; c < nCol; c++)
		{
			if (visible[r][c] == 0)
				z[r][c] = BlankValue;
			wrote = fwrite(&z[r][c], sizeof(double), 1, stream);

		}
		//wrote = fwrite(z[r], sizeof(double), nCol, stream);
	}
#if 0
	//wrote = fwrite(zi_.pD, sizeof(double), nRow*nCol, stream);
		for (uint32_t r = 0; r < nRow; r++)
		{
#if 1
			double z;
			for (uint32_t c = 0; c < nCol; c++)
			{

				z = zi_(c,r);

				wrote = fwrite(&z, sizeof(double), 1, stream);


			}
#else
			wrote = fwrite(zi_.pD + r*nCol,  sizeof(double), nCol, stream);
#endif
		}
#endif
	fclose(stream);



	return 0;
}



int SaveAsSurferGrid7(Widget hWnd, LPTSTR lpstrFile, vdouble& xi, vdouble& yi, vdouble& zi, vdouble& visible)
{
    HRESULT hr = S_OK;

    static TCHAR file[256];
    static TCHAR szFilepath[256];
    static TCHAR fileTitle[256];
    static TCHAR filter[] =
                           TEXT("Surfer 7 (*.grd)\0*.grd\0")
                           TEXT("All Files (*.*)\0*.*\0");
    strcpy( file, lpstrFile);
    strcpy( fileTitle, TEXT(""));
    //strcpy( fileTitle, lpstrFile);

    DWORD nFilterIndex;
    if (SaveFileDlg(hWnd, lpstrFile, filter, nFilterIndex) != S_OK)
        return -1;

#if 0 //defined (_MSC_VER)
//    SSavePlotData spdData;
    OPENFILENAME ofn;



    memset( &ofn, 0, sizeof(ofn) );
    ofn.lStructSize       = sizeof(OPENFILENAME);
    ofn.hwndOwner         = hWnd;
    ofn.hInstance         = hInst;
    ofn.lpstrFilter       = filter;
    ofn.lpstrCustomFilter = NULL;
    ofn.nMaxCustFilter    = 0L;
    ofn.nFilterIndex      = 1L;
    ofn.lpstrFile         = file;
    ofn.nMaxFile          = sizeof(file);
    ofn.lpstrFileTitle    = fileTitle;
    ofn.nMaxFileTitle     = sizeof(fileTitle);
    ofn.lpstrInitialDir   = NULL;
    ofn.lpstrDefExt       = NULL;
//    ofn.lCustData         = (LPARAM)&spdData;
//    ofn.lpfnHook          = DlgProcSaveMesh;
    ofn.lpTemplateName    = MAKEINTRESOURCE(IDD_SAVEPLOT);
    ofn.Flags = OFN_OVERWRITEPROMPT | OFN_EXPLORER | OFN_ENABLETEMPLATE | OFN_ENABLEHOOK;

//    spdData.bSaveSelectedOnly = FALSE;
//    spdData.bSaveHierarchy = TRUE;
//    spdData.bSaveAnimation = TRUE;
//    spdData.xFormat = 0;//D3DXF_FILEFORMAT_TEXT;


    if ( ! GetSaveFileName( &ofn) )
    {
        char s[40];
        DWORD dwErr = CommDlgExtendedError();
		switch(dwErr)
		{
		case CDERR_DIALOGFAILURE :
			MessageBox(0,"The dialog box could not be created. ","CommDlgExtendedError",0);
			break;
		case CDERR_FINDRESFAILURE :
			MessageBox(0,"The common dialog box function failed to find a specified resource.","CommDlgExtendedError",0);
			break;
		case CDERR_INITIALIZATION :
			MessageBox(0,"The common dialog box function failed during initialization. This error often occurs when sufficient memory is not available","CommDlgExtendedError",0);
			break;
		case CDERR_LOADRESFAILURE :
			MessageBox(0,"The common dialog box function failed to load a specified resource.","CommDlgExtendedError",0);
			break;
		case CDERR_LOADSTRFAILURE :
			MessageBox(0,"The common dialog box function failed to load a specified string.","CommDlgExtendedError",0);
			break;
		case CDERR_LOCKRESFAILURE :
			MessageBox(0,"The common dialog box function failed to lock a specified resource.","CommDlgExtendedError",0);
			break;
		case CDERR_MEMALLOCFAILURE :
			MessageBox(0,"The common dialog box function was unable to allocate memory for internal structures.","CommDlgExtendedError",0);
			break;
		case CDERR_MEMLOCKFAILURE :
			MessageBox(0,"The common dialog box function was unable to lock the memory associated with a handle.","CommDlgExtendedError",0);
			break;
		case CDERR_NOHINSTANCE :
			MessageBox(0,"The ENABLETEMPLATE flag was set in the Flags member of the initialization structure for the corresponding common dialog box, but you failed to provide a corresponding instance handle.","CommDlgExtendedError",0);
			break;
		case CDERR_NOHOOK :
			MessageBox(0,"The ENABLEHOOK flag was set in the Flags member of the initialization structure for the corresponding common dialog box, but you failed to provide a pointer to a corresponding hook procedure.","CommDlgExtendedError",0);
			break;
		case CDERR_NOTEMPLATE :
			MessageBox(0,"The ENABLETEMPLATE flag was set in the Flags member of the initialization structure for the corresponding common dialog box, but you failed to provide a corresponding template.","CommDlgExtendedError",0);
			break;
		case CDERR_REGISTERMSGFAIL :
			MessageBox(0,"The RegisterWindowMessage function returned an error code when it was called by the common dialog box function.","CommDlgExtendedError",0);
			break;
		case CDERR_STRUCTSIZE :
			MessageBox(0,"The lStructSize member of the initialization structure for the corresponding common dialog box is invalid.","CommDlgExtendedError",0);
			break;
		case FNERR_BUFFERTOOSMALL :
			MessageBox(0,"The buffer pointed to by the lpstrFile member of the OPENFILENAME structure is too small for the file name specified by the user. The first two bytes of the lpstrFile buffer contain an integer value specifying the size, in TCHARs, required to receive the full name. ","CommDlgExtendedError",0);
			break;
		case FNERR_INVALIDFILENAME :
			{
				char err_str[255];
				sprintf(err_str, "A file name is invalid.\n%s", ofn.lpstrFile );
				MessageBox(0,err_str,"CommDlgExtendedError",0);
			}
			break;
		case FNERR_SUBCLASSFAILURE :
			MessageBox(0,"An attempt to subclass a List box failed because sufficient memory was not available.","CommDlgExtendedError",0);
			break;

		}
        if ( 0 != dwErr )
        {
            memset( &ofn, 0, sizeof(OPENFILENAME) );
            ofn.lStructSize       = 1024;//sizeof(OPENFILENAME_NT4W);
            ofn.hwndOwner         = hWnd;
            ofn.hInstance         = hInst;
            ofn.lpstrFilter       = filter;
            ofn.lpstrCustomFilter = NULL;
            ofn.nMaxCustFilter    = 0L;
            ofn.nFilterIndex      = 1L;
            ofn.lpstrFile         = file;
            ofn.nMaxFile          = sizeof(file);
            ofn.lpstrFileTitle    = fileTitle;
            ofn.nMaxFileTitle     = sizeof(fileTitle);
            ofn.lpstrInitialDir   = NULL;
            ofn.lpstrDefExt       = NULL;
//            ofn.lCustData         = (LPARAM)&spdData;
//            ofn.lpfnHook          = DlgProcSaveMesh;
            ofn.lpTemplateName    = MAKEINTRESOURCE(IDD_SAVEPLOT);
            ofn.Flags = OFN_OVERWRITEPROMPT | OFN_EXPLORER | OFN_ENABLETEMPLATE | OFN_ENABLEHOOK;

            if ( ! GetSaveFileName( &ofn) )
            {
                dwErr = CommDlgExtendedError();
                if ( 0 != dwErr )
                {
                    sprintf( s, "GetOpenFileName failed with %x", dwErr );
                    MessageBox( hWnd, s, "TexWin", MB_OK | MB_SYSTEMMODAL );
                }

				if (FAILED(hr))
				{
					MessageBox( hWnd, "Unabled to save the specified file!", "Save failed!", MB_OK);
				}

				return -1;
            }
        }
        else  // just a cancel, return
        {
			if (FAILED(hr))
			{
				MessageBox( hWnd, "Unabled to save the specified file!", "Save failed!", MB_OK);
			}

			return -1;
        }
    }
#endif
    if (nFilterIndex == 1)
		strcat(file, ".grd");

	char *p, ext[255];
	FILE *stream;

	p = strrchr(file,'.');
	if (p)
	{
		if (p && strcmp(ext, "grd") == 0)
		{
		}
		else
		{
			strcpy(p, ".grd");
		}
	}
	else
	{
		strcat(file, ".grd");
	}

	if ((stream = fopen(file,"wb")) == NULL)
	{
		char errstr[1024];
        sprintf(errstr, "Cannot open output file.\n%s", file);
		MessageBox(0, errstr, "SaveAsSurferGrid7", 
			MB_OK | MB_ICONINFORMATION);
		return -1;
	}
	size_t wrote;

	// Записываем
	uint32_t headerID = 0x42525344;
	wrote = fwrite(&headerID, sizeof(uint32_t), 1, stream);

	uint32_t headerSize = 4;
	wrote = fwrite(&headerSize, sizeof(uint32_t), 1, stream);

	uint32_t Version = 4;
	wrote = fwrite(&Version, sizeof(uint32_t), 1, stream);
		
	uint32_t gridID = 0x44495247;
	wrote = fwrite(&gridID, sizeof(uint32_t), 1, stream);
	
	uint32_t gridSize = 72;
	wrote = fwrite(&gridSize, sizeof(uint32_t), 1, stream);


	uint32_t nRow = yi.Length();// number of rows in the grid
	wrote = fwrite(&nRow, sizeof(uint32_t), 1, stream);


	uint32_t nCol = xi.Length();// number of columns in the grid
	wrote = fwrite(&nCol, sizeof(uint32_t), 1, stream);


	double xLL = xi[0];// X coordinate of the lower left corner of the grid
	wrote = fwrite(&xLL, sizeof(double), 1, stream);


	double yLL = yi[0];// Y coordinate of the lower left corner of the grid
	wrote = fwrite(&yLL, sizeof(double), 1, stream);


	double xSize = xi[1] - xi[0];// spacing between adjacent nodes in the X direction (between columns)
	wrote = fwrite(&xSize, sizeof(double), 1, stream);


	double ySize = yi[1] - yi[0];// spacing between adjacent nodes in the Y direction (between rows)
	wrote = fwrite(&ySize, sizeof(double), 1, stream);


	double zMin = zi.Min();// minimum Z value within the grid
	wrote = fwrite(&zMin, sizeof(double), 1, stream);


	double zMax = zi.Max();// maximum Z value within the grid
	wrote = fwrite(&zMax, sizeof(double), 1, stream);


	double Rotation = 0.0;// not currently used
	wrote = fwrite(&Rotation, sizeof(double), 1, stream);


	double BlankValue = BLANK_VALUE;//1.70141e38;// nodes are blanked if greater or equal to this value
	wrote = fwrite(&BlankValue, sizeof(double), 1, stream);

	uint32_t dataID = 0x41544144;
	wrote = fwrite(&dataID, sizeof(uint32_t), 1, stream);

	uint32_t dataSize = nRow*nCol*sizeof(double);
	wrote = fwrite(&dataSize, sizeof(uint32_t), 1, stream);

	vdouble zi_ = zi;
	// zi_[Find(visible == 0.0)] = BlankValue;

	if (visible.Length() == zi_.Length())
	{
		for (int i = 0; i < zi_.Length(); i++)
		{
			if (visible[i] == 0.0) 
				zi_[i] = BlankValue;
		}
	}

	//wrote = fwrite(zi_.pD, sizeof(double), nRow*nCol, stream);
	for (uint32_t r = 0; r < nRow; r++)
	{
#if 1
		double z;
		for (uint32_t c = 0; c < nCol; c++)
		{

			z = zi_(r,c);

			wrote = fwrite(&z, sizeof(double), 1, stream);


		}
#else
		wrote = fwrite(zi_.pD + r*nCol,  sizeof(double), nCol, stream);
#endif
	}

	fclose(stream);



	return 0;
}

int ImportDigitalModelHeader(uint32_t& nRow, uint32_t& nCol, double& xLeft, double& xRight, double& yLow, double& yHigh, double& zMin, double& zMax)
{
	return 0;
}
int ImportDigitalModel(Grid* pgrid,
	uint32_t nRow,
	uint32_t nCol,

	double xLL,
	double yLL,

	double xSize,
	double ySize,

	double zMin,
	double zMax)
{
	ifstream ifile;
	ifile.open(szPath, ios::in);
	
	if (ifile.fail())
	{
		cout << "failed!!!" << endl;
		
		ifile.close();
		return -1;
	}

	cout << "ok!!!" << endl;

	double BlankValue = BLANK_VALUE;//1.70141e38;// nodes are blanked if greater or equal to this value
	double Rotation = 0.0;// not currently used

	pgrid->gridSection.nRow		= nRow;
	pgrid->gridSection.nCol		= nCol;
	pgrid->gridSection.xLL		= xLL;
	pgrid->gridSection.yLL		= yLL;
	pgrid->gridSection.xSize	= xSize;
	pgrid->gridSection.ySize	= ySize;

	pgrid->gridSection.zMin		= zMin;
	pgrid->gridSection.zMax		= zMax;

	pgrid->gridSection.Rotation	= Rotation;
	pgrid->gridSection.BlankValue = BlankValue;

	pgrid->gridSection.z = AllocDoubleMat(nRow, nCol);

	pgrid->faultSection.nTraces	= 0;
	pgrid->faultSection.nVertices = 0;
	pgrid->faultSection.traces = NULL;
	pgrid->faultSection.vertexes = NULL;


	for (uint32_t r = 0; r < nRow; r++)
	{
		for (uint32_t c = 0; c < nCol; c++)
		{
			double z;
			ifile >> z;
			pgrid->gridSection.z[r][c] = z;
		}
	}
	ifile.close();
	return 0;
}

void FreeGrid(Grid* pgrid)
{
	if (pgrid)
	{
		// free 
		if (pgrid->gridSection.z) 
		{
			FreeDoubleMat(pgrid->gridSection.z);
			pgrid->gridSection.z = NULL;
		}
		if (pgrid->faultSection.traces)
		{
			delete[] pgrid->faultSection.traces;
			pgrid->faultSection.traces = NULL; 
			pgrid->faultSection.nTraces = 0;
		}								
		if (pgrid->faultSection.vertexes)
		{
			delete[] pgrid->faultSection.vertexes;
			pgrid->faultSection.vertexes = NULL; 
			pgrid->faultSection.nVertices = 0;
		}
		if (pgrid)
		{
			delete pgrid;
			pgrid = NULL;
		}
	}
}



void FreeGrid(Grid & pgrid)
{
	// free 
	if (pgrid.gridSection.z) 
	{
		FreeDoubleMat(pgrid.gridSection.z);
		pgrid.gridSection.z = NULL;
	}
	if (pgrid.faultSection.traces)
	{
		delete[] pgrid.faultSection.traces;
		pgrid.faultSection.traces = NULL; 
		pgrid.faultSection.nTraces = 0;
	}								
	if (pgrid.faultSection.vertexes)
	{
		delete[] pgrid.faultSection.vertexes;
		pgrid.faultSection.vertexes = NULL; 
		pgrid.faultSection.nVertices = 0;
	}

}



int ImportSurfer7Grid(const char *file, Grid* pgrid, bool to_allocate)
{
printf("ImportSurfer7Grid\n");
    const char *p;
    char ext[255];
	FILE *stream;

	p = strrchr(file,'.');
	if (p)
		strcpy(ext, p+1);

	if (p && (strcmp(ext, "grd") == 0 || strcmp(ext, "GRD") == 0) )
	{
		//MessageBox(0, ext, "grd",0);
		// open the file
		if ((stream = fopen(file,"rb")) == NULL)
		{
			MessageBox(0, "Cannot open input file.\n", "Import", 
				MB_OK | MB_ICONINFORMATION);
			return -1;
		}
		// считываем 
		size_t read;
		uint32_t headerID;
		read = fread(&headerID, sizeof(uint32_t), 1, stream);
		if (headerID != 0x42525344)
		{
			MessageBox(0, "This is not Surfer 7 Grid file", "ImportSurfer7Grid", 0);
			fclose(stream);
			return -1;
		}
		//else
		//	MessageBox(0, "This is Surfer 7 Grid file", "ImportSurfer7Grid", 0);

		uint32_t headerSize;
		read = fread(&headerSize, sizeof(uint32_t), 1, stream);

		//char str[255];
		//sprintf(str, "headerSize = %d bytes", headerSize);
		//MessageBox(0, str, "ImportSurfer7Grid", 0);

		if (headerSize > 0)
			fseek( stream, headerSize, SEEK_CUR );

		uint32_t gridID;
		read = fread(&gridID, sizeof(uint32_t), 1, stream);
		if (gridID != 0x44495247)
		{
			MessageBox(0, "This is not Grid Section of file", "ImportSurfer7Grid", 0);
			fclose(stream);
			return -1;
		}
		//else
		//	MessageBox(0, "This is Grid Section of file", "ImportSurfer7Grid", 0);

		uint32_t gridSize;
		read = fread(&gridSize, sizeof(uint32_t), 1, stream);

		//sprintf(str, "gridSize = %d bytes", gridSize);
		//MessageBox(0, str, "ImportSurfer7Grid", 0);

		uint32_t nRow;// number of rows in the grid
		read = fread(&nRow, sizeof(uint32_t), 1, stream);

		printf("number of rows in the grid nRow = %d \n", nRow);
		//MessageBox(0, str, "ImportSurfer7Grid", 0);

		uint32_t nCol;// number of columns in the grid
		read = fread(&nCol, sizeof(uint32_t), 1, stream);

		printf("number of columns in the grid nCol = %d \n", nCol);
		//MessageBox(0, str, "ImportSurfer7Grid", 0);
 
		double xLL;// X coordinate of the lower left corner of the grid
		read = fread(&xLL, sizeof(double), 1, stream);

		printf("X coordinate of the lower left corner of the grid xLL = %lf \n", xLL);
		//MessageBox(0, str, "ImportSurfer7Grid", 0);
 
		double yLL;// Y coordinate of the lower left corner of the grid
		read = fread(&yLL, sizeof(double), 1, stream);

		printf("Y coordinate of the lower left corner of the grid yLL = %lf \n", yLL);
		//MessageBox(0, str, "ImportSurfer7Grid", 0);
 
		double xSize;// spacing between adjacent nodes in the X direction (between columns)
		read = fread(&xSize, sizeof(double), 1, stream);

		printf("spacing between adjacent nodes in the X direction (between columns) xSize = %lf \n", xSize);
		//MessageBox(0, str, "ImportSurfer7Grid", 0);
  
		double ySize;// spacing between adjacent nodes in the Y direction (between rows)
		read = fread(&ySize, sizeof(double), 1, stream);

		printf("spacing between adjacent nodes in the Y direction (between rows) ySize = %lf \n", ySize);
		//MessageBox(0, str, "ImportSurfer7Grid", 0);
  
		double zMin;// minimum Z value within the grid
		read = fread(&zMin, sizeof(double), 1, stream);

		printf("minimum Z value within the grid zMin = %e \n", zMin);
		//MessageBox(0, str, "ImportSurfer7Grid", 0);
 
		double zMax;// maximum Z value within the grid
		read = fread(&zMax, sizeof(double), 1, stream);

		printf("maximum Z value within the grid zMax = %e \n", zMax);
		//MessageBox(0, str, "ImportSurfer7Grid", 0);
 
		double Rotation;// not currently used
		read = fread(&Rotation, sizeof(double), 1, stream);

		printf("not currently used Rotation = %lf \n", Rotation);
		//MessageBox(0, str, "ImportSurfer7Grid", 0);
 
		double BlankValue;// nodes are blanked if greater or equal to this value
		read = fread(&BlankValue, sizeof(double), 1, stream);

		printf("nodes are blanked if greater or equal to this value = %lf \n", BlankValue);
		//MessageBox(0, str, "ImportSurfer7Grid", 0);

		uint32_t dataID;
		read = fread(&dataID, sizeof(uint32_t), 1, stream);
		if (dataID != 0x41544144)
		{
			MessageBox(0, "This is not Data Section of file", "ImportSurfer7Grid", 0);
			fclose(stream);
			return -1;
		}
		//else
		//	MessageBox(0, "This is Data Section of file", "ImportSurfer7Grid", 0);

		uint32_t dataSize;
		read = fread(&dataSize, sizeof(uint32_t), 1, stream);

		//sprintf(str, "dataSize = %d bytes", dataSize);
		//MessageBox(0, str, "ImportSurfer7Grid", 0);

		pgrid->gridSection.nRow		= nRow;
		pgrid->gridSection.nCol		= nCol;
		pgrid->gridSection.xLL		= xLL;
		pgrid->gridSection.yLL		= yLL;
		pgrid->gridSection.xSize	= xSize;
		pgrid->gridSection.ySize	= ySize;
		pgrid->gridSection.zMin		= zMin;
		pgrid->gridSection.zMax		= zMax;
		pgrid->gridSection.Rotation	= Rotation;
		pgrid->gridSection.BlankValue = BlankValue;

		if (to_allocate)
			pgrid->gridSection.z = AllocDoubleMat(nRow, nCol);

		if (pgrid->gridSection.z == NULL)
		{
			printf("Error AllocDoubleMat return NULL\n");
			return -1;
		}

		pgrid->faultSection.nTraces	= 0;
		pgrid->faultSection.nVertices = 0;
		pgrid->faultSection.traces = NULL;
		pgrid->faultSection.vertexes = NULL;


		for (uint32_t r = 0; r < nRow; r++)
		{
			read = fread(pgrid->gridSection.z[r], sizeof(double), nCol, stream);
#if 1
			for (uint32_t c = 0; c < nCol; c++)
				printf("%e\t", pgrid->gridSection.z[r][c]);
			printf("\n");
#endif
		}


		uint32_t faultID;
		read = fread(&faultID, sizeof(uint32_t), 1, stream);
		if (!read || faultID != 0x49544c46)
		{
			//MessageBox(0, "This is not Fault Section of file", "ImportSurfer7Grid", 0);
			fclose(stream);
			return 0;
		}
//		else
//			MessageBox(0, "This is Fault Section of file", "ImportSurfer7Grid", 0);

		//A Fault Info section describes the fault geometry used to create the grid. 
		//Fault Info sections have the following format:
		//	uint32_t nTraces		number of fault traces (polylines)
		//	uint32_t nVertices		total number of vertices in all the traces
		
		//data section
		//variable-sized data block consisting of an array of Trace structures 
		//immediately followed by the array of vertices
		// A Data section containing an array of Trace structures 
		//and an array of Vertex structures must immediately follow a Fault Info section. 
		//The number of Trace structures in the array is nTraces, 
		//and the number of Vertex structures is nVertices.


		// Trace structure:
		//	uint32_t iFirst			0-based index into the vertex array for the first vertex of this trace
		//	uint32_t nPts			number of vertices in this trace
 

		//Vertex structure:
		//	double x			X coordinate of the vertex
		//	double y			Y coordinate of the vertex

		uint32_t faultSize = 0;
		read = fread(&faultSize, sizeof(uint32_t), 1, stream);
		printf("read %u, faultSize %d\n", read, faultSize);

		size_t read_traces = fread(&pgrid->faultSection.nTraces, sizeof(uint32_t), 1, stream);
		printf("read %u, nTraces %d\n", read_traces, pgrid->faultSection.nTraces);

		size_t read_vertices = fread(&pgrid->faultSection.nVertices, sizeof(uint32_t), 1, stream);
		printf("read %u, nVertices %d\n", read_vertices, pgrid->faultSection.nVertices);

		uint32_t faultDataID;
		read = fread(&faultDataID, sizeof(uint32_t), 1, stream);

		if (!read || faultDataID != 1096040772)
		{
			MessageBox(0, "This is not faultDataID Section of file", "ImportSurfer7Grid", 0);
			fclose(stream);
			return -1;
		}

		uint32_t faultDataSize;
		read = fread(&faultDataSize, sizeof(uint32_t), 1, stream);
		printf("read %u, faultDataSize %d \n", read, faultDataSize);

		if (faultDataID == 1096040772
			&& read_traces && read_vertices)
		{
			//FILE *bln;
			//bln = fopen("faults_test.bln", "wt");
			pgrid->faultSection.traces = new Trace[pgrid->faultSection.nTraces];
			fread(pgrid->faultSection.traces, sizeof(Trace), pgrid->faultSection.nTraces, stream);
/*
			//Trace tr;
			for (uint32_t n = 0; n < pgrid->faultSection.nTraces; n++)
			{
				//fread(&tr.iFirst, sizeof(uint32_t), 1, stream);
				//fread(&tr.nPts, sizeof(uint32_t), 1, stream);

				printf(
					"tr.iFirst %d, tr.nPts %d\n", 
					pgrid->faultSection.traces[n].iFirst, 
					pgrid->faultSection.traces[n].nPts);
			}*/


			pgrid->faultSection.vertexes = new Vertex[pgrid->faultSection.nVertices];
			fread(pgrid->faultSection.vertexes, sizeof(Vertex), pgrid->faultSection.nVertices, stream);
			//Vertex vx;
			/*for (uint32_t n = 0; n < pgrid->faultSection.nVertices; n++)
			{
				//fread(&vx.x, sizeof(double), 1, stream);
				//fread(&vx.y, sizeof(double), 1, stream);

				//printf("vx.x %f, vx.y %f\n", pgrid->faultSection.vertexes[n].x, pgrid->faultSection.vertexes[n].y);
			}

			for (uint32_t n = 0; n < pgrid->faultSection.nTraces; n++)
			{
				//fread(&tr.iFirst, sizeof(uint32_t), 1, stream);
				//fread(&tr.nPts, sizeof(uint32_t), 1, stream);

				printf(
					"tr.iFirst %d, tr.nPts %d\n", 
					pgrid->faultSection.traces[n].iFirst, 
					pgrid->faultSection.traces[n].nPts);

				fprintf(bln, "%d, %d\n", pgrid->faultSection.traces[n].nPts, 0);

				for (uint32_t ii = pgrid->faultSection.traces[n].iFirst;
					ii < pgrid->faultSection.traces[n].iFirst + pgrid->faultSection.traces[n].nPts;
					ii++)
				{
					if (ii < pgrid->faultSection.nVertices)
						fprintf(bln, "%f, %f\n", pgrid->faultSection.vertexes[ii].x, pgrid->faultSection.vertexes[ii].y);
				}
					
			}

			fclose(bln);*/
		}

		fclose(stream);
		return 0;

	}
	return -1;
}


int SaveAsSurfer7Grid(const char *file, Grid* pgrid)
{
	printf("SaveAsSurferGrid7 %s\n", file);

	FILE * stream;
	if ((stream = fopen(file,"wb")) == NULL)
	{
		char errstr[1024];
		sprintf(errstr, "Cannot open output file.\n%s", file);
		MessageBox(0, errstr, "SaveAsSurferGrid7", 
			MB_OK | MB_ICONINFORMATION);
		return -1;
	}

	size_t wrote;

	// Записываем
	uint32_t headerID = 0x42525344;
	wrote = fwrite(&headerID, sizeof(uint32_t), 1, stream);

	uint32_t headerSize = 4;
	wrote = fwrite(&headerSize, sizeof(uint32_t), 1, stream);

	uint32_t Version = 4;
	wrote = fwrite(&Version, sizeof(uint32_t), 1, stream);
		
	uint32_t gridID = 0x44495247;
	wrote = fwrite(&gridID, sizeof(uint32_t), 1, stream);
	
	uint32_t gridSize = 72;
	wrote = fwrite(&gridSize, sizeof(uint32_t), 1, stream);

	wrote = fwrite(&pgrid->gridSection.nRow, sizeof(uint32_t), 1, stream);
	wrote = fwrite(&pgrid->gridSection.nCol, sizeof(uint32_t), 1, stream);
	wrote = fwrite(&pgrid->gridSection.xLL, sizeof(double), 1, stream);
	wrote = fwrite(&pgrid->gridSection.yLL, sizeof(double), 1, stream);
	wrote = fwrite(&pgrid->gridSection.xSize, sizeof(double), 1, stream);
	wrote = fwrite(&pgrid->gridSection.ySize, sizeof(double), 1, stream);
	wrote = fwrite(&pgrid->gridSection.zMin, sizeof(double), 1, stream);
	wrote = fwrite(&pgrid->gridSection.zMax, sizeof(double), 1, stream);

	double Rotation = 0.0;// not currently used
	wrote = fwrite(&Rotation, sizeof(double), 1, stream);

	double BlankValue = BLANK_VALUE;//1.70141e38;// nodes are blanked if greater or equal to this value
	wrote = fwrite(&BlankValue, sizeof(double), 1, stream);

	uint32_t dataID = 0x41544144;
	wrote = fwrite(&dataID, sizeof(uint32_t), 1, stream);

	uint32_t dataSize = pgrid->gridSection.nRow * pgrid->gridSection.nCol * sizeof(double);
	wrote = fwrite(&dataSize, sizeof(uint32_t), 1, stream);

	uint32_t r, c;
	for (r = 0; r < pgrid->gridSection.nRow; r++)
	{
		wrote = fwrite(pgrid->gridSection.z[r], sizeof(double), pgrid->gridSection.nCol, stream);
	}

	if (pgrid->faultSection.nTraces && 
		pgrid->faultSection.nVertices &&
		pgrid->faultSection.traces && 
		pgrid->faultSection.vertexes)
	{
		uint32_t faultID = 0x49544c46;
		wrote = fwrite(&faultID, sizeof(uint32_t), 1, stream);
		uint32_t faultSize = 8;
		wrote = fwrite(&faultSize, sizeof(uint32_t), 1, stream);
		wrote = fwrite(&pgrid->faultSection.nTraces, sizeof(uint32_t), 1, stream);
		wrote = fwrite(&pgrid->faultSection.nVertices, sizeof(uint32_t), 1, stream);

		uint32_t faultDataID = 1096040772;
		wrote = fwrite(&faultDataID, sizeof(uint32_t), 1, stream);
		uint32_t faultDataSize = 
			pgrid->faultSection.nTraces   * sizeof(Trace) + 
			pgrid->faultSection.nVertices * sizeof(Vertex);
		wrote = fwrite(&faultDataSize, sizeof(uint32_t), 1, stream);
		wrote = fwrite(pgrid->faultSection.traces, sizeof(Trace), pgrid->faultSection.nTraces, stream);
		wrote = fwrite(pgrid->faultSection.vertexes, sizeof(Vertex), pgrid->faultSection.nVertices, stream);
	}

	fclose(stream);

	return 0;
}




int ImportSurfer7Grid4(const char *file, Grid4* pgrid)
{
printf("ImportSurfer7Grid4 %s\n", file);
printf("sizeof(long) %d\n", sizeof(long));
printf("sizeof(uint32_t) %d\n", sizeof(uint32_t));
printf("sizeof(double) %d\n", sizeof(double));

    const char *p;
    char ext[255];
	FILE *stream;

	p = strrchr(file,'.');
	if (p)
		strcpy(ext, p+1);

	if (p && (strcmp(ext, "cub") == 0 || strcmp(ext, "CUB") == 0) )
	{
		//MessageBox(0, ext, "grd",0);
		// open the file
		if ((stream = fopen(file,"rb")) == NULL)
		{
			MessageBox(0, "Cannot open input file.\n", "Import", 
				MB_OK | MB_ICONINFORMATION);
			return -1;
		}
		// считываем 
		size_t read;
		uint32_t headerID;
		read = fread(&headerID, sizeof(uint32_t), 1, stream);
		if (headerID != 0x42525377)
		{
            printf("ImportSurfer7Grid4 headerID 0x%x != 0x42525377\n", headerID);
			MessageBox(0, "This is not Surfer 7 Grid file", "ImportSurfer7Grid4", 0);
			fclose(stream);
			return -1;
		}
		//else
		//	MessageBox(0, "This is Surfer 7 Grid file", "ImportSurfer7Grid4", 0);

		uint32_t headerSize;
		read = fread(&headerSize, sizeof(uint32_t), 1, stream);

		//char str[255];
		printf("headerSize = %d bytes", headerSize);
		//MessageBox(0, str, "ImportSurfer7Grid", 0);

		if (headerSize > 0)
			fseek( stream, headerSize, SEEK_CUR );

		uint32_t gridID;
		read = fread(&gridID, sizeof(uint32_t), 1, stream);
		if (gridID != 0x47524433)
		{
            printf("ImportSurfer7Grid4 gridID 0x%x != 0x47524433\n", gridID);
			MessageBox(0, "This is not Grid Section of file", "ImportSurfer7Grid4", 0);
			fclose(stream);
			return -1;
		}
		//else
		//	MessageBox(0, "This is Grid Section of file", "ImportSurfer7Grid4", 0);

		uint32_t gridSize;
		read = fread(&gridSize, sizeof(uint32_t), 1, stream);

		printf("gridSize = %d bytes", gridSize);
		//MessageBox(0, str, "ImportSurfer7Grid4", 0);

		uint32_t nPag;// number of columns in the grid
		read = fread(&nPag, sizeof(uint32_t), 1, stream);

		printf("number of pages in the grid nPag = %d \n", nPag);
		//MessageBox(0, str, "ImportSurfer7Grid4", 0);
 
		uint32_t nRow;// number of rows in the grid
		read = fread(&nRow, sizeof(uint32_t), 1, stream);

		printf("number of rows in the grid nRow = %d \n", nRow);
		//MessageBox(0, str, "ImportSurfer7Grid4", 0);

		uint32_t nCol;// number of columns in the grid
		read = fread(&nCol, sizeof(uint32_t), 1, stream);

		printf("number of columns in the grid nCol = %d \n", nCol);
		//MessageBox(0, str, "ImportSurfer7Grid4", 0);
 
		double xLL;// X coordinate of the lower left corner of the grid
		read = fread(&xLL, sizeof(double), 1, stream);

		printf("X coordinate of the lower left corner of the grid xLL = %lf \n", xLL);
		//MessageBox(0, str, "ImportSurfer7Grid4", 0);
 
		double yLL;// Y coordinate of the lower left corner of the grid
		read = fread(&yLL, sizeof(double), 1, stream);

		printf("Y coordinate of the lower left corner of the grid yLL = %lf \n", yLL);
		//MessageBox(0, str, "ImportSurfer7Grid4", 0);
 
		double zLL;// Z coordinate of the lower left corner of the grid
		read = fread(&zLL, sizeof(double), 1, stream);

		printf("Z coordinate of the lower left corner of the grid zLL = %lf \n", zLL);
		//MessageBox(0, str, "ImportSurfer7Grid4", 0);
 
		double xSize;// spacing between adjacent nodes in the X direction (between columns)
		read = fread(&xSize, sizeof(double), 1, stream);

		printf("spacing between adjacent nodes in the X direction (between columns) xSize = %lf \n", xSize);
		//MessageBox(0, str, "ImportSurfer7Grid", 0);
  
		double ySize;// spacing between adjacent nodes in the Y direction (between rows)
		read = fread(&ySize, sizeof(double), 1, stream);

		printf("spacing between adjacent nodes in the Y direction (between rows) ySize = %lf \n", ySize);
		//MessageBox(0, str, "ImportSurfer7Grid", 0);
  
		double zSize;// spacing between adjacent nodes in the Z direction (between rows)
		read = fread(&zSize, sizeof(double), 1, stream);

		printf("spacing between adjacent nodes in the Z direction (between rows) zSize = %lf \n", zSize);
		//MessageBox(0, str, "ImportSurfer7Grid", 0);
  
		double vMin;// minimum V value within the grid
		read = fread(&vMin, sizeof(double), 1, stream);

		printf("minimum V value within the grid vMin = %lf \n", vMin);
		//MessageBox(0, str, "ImportSurfer7Grid", 0);
 
		double vMax;// maximum V value within the grid
		read = fread(&vMax, sizeof(double), 1, stream);

		printf("maximum V value within the grid vMax = %lf \n", vMax);
		//MessageBox(0, str, "ImportSurfer7Grid", 0);
 
		double Rotation;// not currently used
		read = fread(&Rotation, sizeof(double), 1, stream);

		printf("not currently used Rotation = %lf \n", Rotation);
		//MessageBox(0, str, "ImportSurfer7Grid", 0);
 
		double BlankValue;// nodes are blanked if greater or equal to this value
		read = fread(&BlankValue, sizeof(double), 1, stream);

		printf("nodes are blanked if greater or equal to this value = %lf \n", BlankValue);
		//MessageBox(0, str, "ImportSurfer7Grid", 0);

		uint32_t dataID;
		read = fread(&dataID, sizeof(uint32_t), 1, stream);
		if (dataID != 0x44415441)
		{
            printf("ImportSurfer7Grid4 dataID 0x%x != 0x44415441\n", dataID);
            MessageBox(0, "This is not Data Section of file", "ImportSurfer7Grid", 0);
			fclose(stream);
			return -1;
		}
		//else
		//	MessageBox(0, "This is Data Section of file", "ImportSurfer7Grid", 0);

		uint32_t dataSize;
		read = fread(&dataSize, sizeof(uint32_t), 1, stream);

		//sprintf(str, "dataSize = %d bytes", dataSize);
		//MessageBox(0, str, "ImportSurfer7Grid", 0);

		pgrid->grid4Section.nPag		= nPag;
		pgrid->grid4Section.nRow		= nRow;
		pgrid->grid4Section.nCol		= nCol;
		pgrid->grid4Section.xLL		= xLL;
		pgrid->grid4Section.yLL		= yLL;
		pgrid->grid4Section.zLL		= zLL;
		pgrid->grid4Section.xSize	= xSize;
		pgrid->grid4Section.ySize	= ySize;
		pgrid->grid4Section.zSize	= zSize;
		pgrid->grid4Section.vMin		= vMin;
		pgrid->grid4Section.vMax		= vMax;
		pgrid->grid4Section.Rotation	= Rotation;
		pgrid->grid4Section.BlankValue = BlankValue;

		pgrid->grid4Section.v = Alloc3DMat<double>(nPag, nRow, nCol);

		if (pgrid->grid4Section.v == NULL)
		{
			printf("Error AllocDoubleMat return NULL\n");
			return -1;
		}

		for (uint32_t p = 0; p < nPag; p++)
		{
			for (uint32_t r = 0; r < nRow; r++)
			{
				read = fread(pgrid->grid4Section.v[p][r], sizeof(double), nCol, stream);
#if 0
				for (uint32_t c = 0; c < nCol; c++)
					printf("%f\t", pgrid->grid4Section.v[p][r][c]);
				printf("\n");
#endif
			}
		}

#if 0

		uint32_t faultID;
		read = fread(&faultID, sizeof(uint32_t), 1, stream);
		if (!read || faultID != 0x49544c46)
		{
			//MessageBox(0, "This is not Fault Section of file", "ImportSurfer7Grid", 0);
			fclose(stream);
			return 0;
		}
//		else
//			MessageBox(0, "This is Fault Section of file", "ImportSurfer7Grid", 0);
		//A Fault Info section describes the fault geometry used to create the grid. 
		//Fault Info sections have the following format:
		//	uint32_t nTraces		number of fault traces (polylines)
		//	uint32_t nVertices		total number of vertices in all the traces
		
		//data section
		//variable-sized data block consisting of an array of Trace structures 
		//immediately followed by the array of vertices
		// A Data section containing an array of Trace structures 
		//and an array of Vertex structures must immediately follow a Fault Info section. 
		//The number of Trace structures in the array is nTraces, 
		//and the number of Vertex structures is nVertices.


		// Trace structure:
		//	uint32_t iFirst			0-based index into the vertex array for the first vertex of this trace
		//	uint32_t nPts			number of vertices in this trace
 

		//Vertex structure:
		//	double x			X coordinate of the vertex
		//	double y			Y coordinate of the vertex

		uint32_t faultSize = 0;
		read = fread(&faultSize, sizeof(uint32_t), 1, stream);
		printf("read %u, faultSize %d\n", read, faultSize);

		size_t read_traces = fread(&pgrid->faultSection.nTraces, sizeof(uint32_t), 1, stream);
		printf("read %u, nTraces %d\n", read_traces, pgrid->faultSection.nTraces);

		size_t read_vertices = fread(&pgrid->faultSection.nVertices, sizeof(uint32_t), 1, stream);
		printf("read %u, nVertices %d\n", read_vertices, pgrid->faultSection.nVertices);

		uint32_t faultDataID;
		read = fread(&faultDataID, sizeof(uint32_t), 1, stream);

		if (!read || faultDataID != 1096040772)
		{
			MessageBox(0, "This is not faultDataID Section of file", "ImportSurfer7Grid", 0);
			fclose(stream);
			return -1;
		}

		uint32_t faultDataSize;
		read = fread(&faultDataSize, sizeof(uint32_t), 1, stream);
		printf("read %u, faultDataSize %d \n", read, faultDataSize);

		if (faultDataID == 1096040772
			&& read_traces && read_vertices)
		{
			//FILE *bln;
			//bln = fopen("faults_test.bln", "wt");
			pgrid->faultSection.traces = new Trace[pgrid->faultSection.nTraces];
			fread(pgrid->faultSection.traces, sizeof(Trace), pgrid->faultSection.nTraces, stream);
/*
			//Trace tr;
			for (uint32_t n = 0; n < pgrid->faultSection.nTraces; n++)
			{
				//fread(&tr.iFirst, sizeof(uint32_t), 1, stream);
				//fread(&tr.nPts, sizeof(uint32_t), 1, stream);

				printf(
					"tr.iFirst %d, tr.nPts %d\n", 
					pgrid->faultSection.traces[n].iFirst, 
					pgrid->faultSection.traces[n].nPts);
			}*/


			pgrid->faultSection.vertexes = new Vertex[pgrid->faultSection.nVertices];
			fread(pgrid->faultSection.vertexes, sizeof(Vertex), pgrid->faultSection.nVertices, stream);
			//Vertex vx;
			/*for (uint32_t n = 0; n < pgrid->faultSection.nVertices; n++)
			{
				//fread(&vx.x, sizeof(double), 1, stream);
				//fread(&vx.y, sizeof(double), 1, stream);

				//printf("vx.x %f, vx.y %f\n", pgrid->faultSection.vertexes[n].x, pgrid->faultSection.vertexes[n].y);
			}

			for (uint32_t n = 0; n < pgrid->faultSection.nTraces; n++)
			{
				//fread(&tr.iFirst, sizeof(uint32_t), 1, stream);
				//fread(&tr.nPts, sizeof(uint32_t), 1, stream);

				printf(
					"tr.iFirst %d, tr.nPts %d\n", 
					pgrid->faultSection.traces[n].iFirst, 
					pgrid->faultSection.traces[n].nPts);

				fprintf(bln, "%d, %d\n", pgrid->faultSection.traces[n].nPts, 0);

				for (uint32_t ii = pgrid->faultSection.traces[n].iFirst;
					ii < pgrid->faultSection.traces[n].iFirst + pgrid->faultSection.traces[n].nPts;
					ii++)
				{
					if (ii < pgrid->faultSection.nVertices)
						fprintf(bln, "%f, %f\n", pgrid->faultSection.vertexes[ii].x, pgrid->faultSection.vertexes[ii].y);
				}
					
			}

			fclose(bln);*/
		}
#endif
		fclose(stream);
		return 0;

	}
	return -1;
}

inline void Swap8Bytes(void* p)
{
	char one_byte;
	char* data = static_cast<char*>(p);
	one_byte = data[0]; data[0] = data[7]; data[7] = one_byte;
    one_byte = data[1]; data[1] = data[6]; data[6] = one_byte;
    one_byte = data[2]; data[2] = data[5]; data[5] = one_byte;
    one_byte = data[3]; data[3] = data[4]; data[4] = one_byte;
}
int SaveAsVTK(const char *file, Grid4* pgrid, bool view)
{
	printf("SaveAsVTK %s\n", file);

	FILE * stream;
	if ((stream = fopen(file,"wb")) == NULL)
	{
		char errstr[1024];
        sprintf(errstr, "Cannot open output file.\n%s", file);
		MessageBox(0, errstr, "SaveAsVTK", 
			MB_OK | MB_ICONINFORMATION);
		return -1;
	}
	/*% prec = menu('What Precision of Vtk File?', 'unsigned char', 'double');
	prec = 2;
	stream = fopen(filename,'w');

	% # vtk DataFile Version 1.0
	% Created by Golden Software ioVtk.dll
	% 
	% BINARY
	% 
	% DATASET STRUCTURED_POINTS
	% DIMENSIONS 128 128 128
	% ASPECT_RATIO 1.0 1.0 1.0
	% ORIGIN 2.0 5.0 1.0
	% 
	% POINT_DATA 2097152
	% SCALARS scalar1of1 unsigned_char
	% LOOKUP_TABLE default*/



	uint32_t nCol = pgrid->grid4Section.nCol;
	uint32_t nRow = pgrid->grid4Section.nRow;
	uint32_t nPag = pgrid->grid4Section.nPag;

	double xLL, yLL, zLL;
	double xSize, ySize, zSize;
	if(view)
	{
		xLL = pgrid->grid4Zoom.xLL;
		yLL = pgrid->grid4Zoom.yLL;
		zLL = pgrid->grid4Zoom.zLL;

		xSize = pgrid->grid4Zoom.xSize;
		ySize = pgrid->grid4Zoom.ySize;
		zSize = pgrid->grid4Zoom.zSize;
	}
	else
	{
		xLL = pgrid->grid4Section.xLL;
		yLL = pgrid->grid4Section.yLL;
		zLL = pgrid->grid4Section.zLL;

		xSize = pgrid->grid4Section.xSize;
		ySize = pgrid->grid4Section.ySize;
		zSize = pgrid->grid4Section.zSize;

	}

	fprintf(stream, "# vtk DataFile Version 2.0\n");
	fprintf(stream, "Created by SurfCube\n");
	fprintf(stream, "\n");
	fprintf(stream, "BINARY\n");
	fprintf(stream, "\n");
	fprintf(stream, "DATASET STRUCTURED_POINTS\n");
	fprintf(stream, "DIMENSIONS %d %d %d\n", nCol, nRow, nPag);
	fprintf(stream, "ORIGIN %f %f %f\n", xLL, yLL, zLL);
	fprintf(stream, "SPACING %f %f %f\n", xSize, ySize, zSize);
	//% fprintf(stream, "ASPECT_RATIO 1.0 1.0 1.0\n");
	fprintf(stream, "\n");
	fprintf(stream, "POINT_DATA %d\n", nPag * nRow * nCol);
	//switch(prec)
		//case 1, fprintf(stream, "SCALARS scalar1of1 unsigned_char\n");
		/*case 2,*/ fprintf(stream, "SCALARS scalar1of1 double\n");
	//end

	fprintf(stream, "LOOKUP_TABLE default\n");


	size_t wrote;

	uint32_t r, c, p;
	double value;
	for (p = 0; p < pgrid->grid4Section.nPag; p++)
	{
		for (r = 0; r < pgrid->grid4Section.nRow; r++)
		{		
			for (c = 0; c < pgrid->grid4Section.nCol; c++)
			{
				value = pgrid->grid4Section.v[p][r][c];
				if (value == pgrid->grid4Section.BlankValue)
				{
					value = pgrid->grid4Section.vMin;
				}
				Swap8Bytes((void * )&value);
				wrote = fwrite(&value, sizeof(double), 1, stream);
			}
		}
	}
	fclose(stream);
	return 0;
}



int SaveAsSurfer7Grid4(const char *file, Grid4* pgrid)
{
	printf("SaveAsSurferGrid7 %s\n", file);

	FILE * stream;
	if ((stream = fopen(file,"wb")) == NULL)
	{
		char errstr[1024];
        sprintf(errstr, "Cannot open output file.\n%s", file);
        MessageBox(0, errstr, "SaveAsSurferGrid7",
            MB_OK | MB_ICONINFORMATION);
		return -1;
	}

	size_t wrote;

	// Записываем
	uint32_t headerID = 0x42525377;
	wrote = fwrite(&headerID, sizeof(uint32_t), 1, stream);

	uint32_t headerSize = 4;
	wrote = fwrite(&headerSize, sizeof(uint32_t), 1, stream);

	uint32_t Version = 4;
	wrote = fwrite(&Version, sizeof(uint32_t), 1, stream);
		
	uint32_t gridID = 0x47524433;
	wrote = fwrite(&gridID, sizeof(uint32_t), 1, stream);
	
	uint32_t gridSize = 3*sizeof(uint32_t) + 10*sizeof(double);//72;
	wrote = fwrite(&gridSize, sizeof(uint32_t), 1, stream);

	wrote = fwrite(&pgrid->grid4Section.nPag, sizeof(uint32_t), 1, stream);
	wrote = fwrite(&pgrid->grid4Section.nRow, sizeof(uint32_t), 1, stream);
	wrote = fwrite(&pgrid->grid4Section.nCol, sizeof(uint32_t), 1, stream);
	wrote = fwrite(&pgrid->grid4Section.xLL, sizeof(double), 1, stream);
	wrote = fwrite(&pgrid->grid4Section.yLL, sizeof(double), 1, stream);
	wrote = fwrite(&pgrid->grid4Section.zLL, sizeof(double), 1, stream);
	wrote = fwrite(&pgrid->grid4Section.xSize, sizeof(double), 1, stream);
	wrote = fwrite(&pgrid->grid4Section.ySize, sizeof(double), 1, stream);
	wrote = fwrite(&pgrid->grid4Section.zSize, sizeof(double), 1, stream);
	wrote = fwrite(&pgrid->grid4Section.vMin, sizeof(double), 1, stream);
	wrote = fwrite(&pgrid->grid4Section.vMax, sizeof(double), 1, stream);

	double Rotation = 0.0;// not currently used
	wrote = fwrite(&Rotation, sizeof(double), 1, stream);

	double BlankValue = BLANK_VALUE;//1.70141e38;// nodes are blanked if greater or equal to this value
	wrote = fwrite(&BlankValue, sizeof(double), 1, stream);

	uint32_t dataID = 0x44415441;
	wrote = fwrite(&dataID, sizeof(uint32_t), 1, stream);

	uint32_t dataSize = pgrid->grid4Section.nPag * pgrid->grid4Section.nRow * pgrid->grid4Section.nCol * sizeof(double);
	wrote = fwrite(&dataSize, sizeof(uint32_t), 1, stream);

	uint32_t r, c, p;
	for (p = 0; p < pgrid->grid4Section.nPag; p++)
	{
		for (r = 0; r < pgrid->grid4Section.nRow; r++)
		{
			wrote = fwrite(pgrid->grid4Section.v[p][r], sizeof(double), pgrid->grid4Section.nCol, stream);
		}
	}

	fclose(stream);

	return 0;
}

void UpdateExtremums(SURFER7GRIDSECTION & grid)
{
	grid.zMax = -DBL_MAX;
	grid.zMin = DBL_MAX;
	uint32_t r, c;
	for (r = 0; r < grid.nRow; r++)
	{
		for (c = 0; c < grid.nCol; c++)
		{
			if (grid.BlankValue != grid.z[r][c])
			{
				if(grid.zMin > grid.z[r][c]) grid.zMin = grid.z[r][c];
				if(grid.zMax < grid.z[r][c]) grid.zMax = grid.z[r][c];
			}
		}
	}
}
void CubeSize::Define(double minx, double miny, double minz, double maxx, double maxy, double maxz)
{
	double dx, dy, dz;
	int nx,ny,nz;

	char str[1023];
	bool extract_cube = false;
	cout << "extract_cube [0,1] ?" << endl;
	cin >> extract_cube;

	if (extract_cube)
	{
		double len_extract_cube = 0.0;
		cout << "len_extract_cube ?" << endl;
		cin >> len_extract_cube;

		minx -= len_extract_cube;
		miny -= len_extract_cube;

		maxx += len_extract_cube;
		maxy += len_extract_cube;
	}

	bool enter_nx_ny_nz = false;
	cout << "enter [nx,ny,nz] 1 or enter [dx,dy,dz] 0 ?" << endl;
	cin >> enter_nx_ny_nz;

	if (enter_nx_ny_nz)
	{					
		cout << "nx?" << endl;
		cin >> nx;
		cout << "ny?" << endl;
		cin >> ny;
		cout << "nz?" << endl;
		cin >> nz;

		dx = (maxx - minx) / nx;
		dy = (maxy - miny) / ny;
		dz = (maxz - minz) / nz;
	}
	else
	{
		cout << "dx?" << endl;
		cin >> dx;
		cout << "dy?" << endl;
		cin >> dy;
		cout << "dz?" << endl;
		cin >> dz;
	}

	uint32_t npag;
	uint32_t nrow;
	uint32_t ncol;
	double xll;
	double yll;
	double zll;
	double xsize;
	double ysize;
	double zsize;

	ncol = (uint32_t)(maxx-minx)/dx + 1;
	nrow = (uint32_t)(maxy-miny)/dy + 1;
	npag = (uint32_t)(maxz-minz)/dz + 1;

	zll = minz;
	xll = minx;
	yll = miny;

	xsize = (maxx-minx) / (ncol - 1);
	ysize = (maxy-miny) / (nrow - 1);
	zsize = (maxz-minz) / (npag - 1);

	this->Define(npag, nrow, ncol, xll, yll, zll, xsize, ysize, zsize);

}

void CubeSize::Printf()
{
	cout << "CubeSize::Printf()" << endl;
	cout << endl;
	cout << "nPag = " << nPag << endl;	
	cout << "nRow = " << nRow << endl;	
	cout << "nCol = " << nCol << endl;	
	cout << endl;
	cout << "xLL = " << xLL << endl;	
	cout << "yLL = " << yLL << endl;	
	cout << "zLL = " << zLL << endl;	
	cout << endl;
	cout << "xSize = " << xSize << endl;	
	cout << "ySize = " << ySize << endl;	
	cout << "zSize = " << zSize << endl;	
	cout << endl;
}


Archive& operator <<(Archive& ar, CubeSize& ob)
{

	uint32_t Version = 1;
	ar << Version;

	ar << ob.defined;

	ar << ob.nPag;
	ar << ob.nRow;
	ar << ob.nCol;
	ar << ob.xLL;
	ar << ob.yLL;
	ar << ob.zLL;
	ar << ob.xSize;
	ar << ob.ySize;
	ar << ob.zSize;

	return ar;
}
Archive& operator >>(Archive& ar, CubeSize& ob)
{
	uint32_t Version;
	ar >> Version;

	ar >> ob.defined;

	ar >> ob.nPag;
	ar >> ob.nRow;
	ar >> ob.nCol;
	ar >> ob.xLL;
	ar >> ob.yLL;
	ar >> ob.zLL;
	ar >> ob.xSize;
	ar >> ob.ySize;
	ar >> ob.zSize;

	return ar;
}
Archive& operator <<(Archive& ar, key_grid& ob)
{
	uint32_t version = KEY_GRID_VERSION;
	ar << version;

	switch (version)
	{
	case 2:
		{
			ar << ob.id_surf;
			ar << ob.podoshva;
		}
	case 1:
		{
			ar << ob.key;
			ar << ob.surfname;
		}
		break;
	}

	return ar;
}
Archive& operator >>(Archive& ar, key_grid& ob)
{
	uint32_t version = KEY_GRID_VERSION;
	ar >> version;

	switch(version)
	{
	case 2:
		{
			ar >> ob.id_surf;
			ar >> ob.podoshva;
		}
	case 1:
		{
			ar >> ob.key;
			ar >> ob.surfname;

			if (version == 1)
			{
				ob.id_surf = -1;
			}
		}
		break;
	}


	return ar;
}

Archive& operator <<(Archive& ar, Grid4& ob)
{
//int SaveAsSurfer7Grid4(char *file, Grid4* pgrid)
//{
//	printf("SaveAsSurferGrid7 %s\n", file);

//	FILE * stream;
//	if ((stream = fopen(file,"wb")) == NULL)
//	{
//		char errstr[1024];
//		sprintf(errstr, "Cannot open output file.\n%s", szPath);
//		MessageBox(0, errstr, "SaveAsSurferGrid7", 
//			MB_OK | MB_ICONINFORMATION);
//		return -1;
//	}

//	size_t wrote;

	// Записываем
	uint32_t headerID = 0x42525377;
	//wrote = fwrite(&headerID, sizeof(uint32_t), 1, stream);
	ar << headerID;

	uint32_t headerSize = 4;
	//wrote = fwrite(&headerSize, sizeof(uint32_t), 1, stream);
	ar << headerSize;

	uint32_t Version = 4;
	//wrote = fwrite(&Version, sizeof(uint32_t), 1, stream);
	ar << Version;
		
	uint32_t gridID = 0x47524433;
	//wrote = fwrite(&gridID, sizeof(uint32_t), 1, stream);
	ar << gridID;
	
	uint32_t gridSize = 3*sizeof(uint32_t) + 10*sizeof(double);//72;
	//wrote = fwrite(&gridSize, sizeof(uint32_t), 1, stream);
	ar << gridSize;

	//wrote = fwrite(&pgrid->grid4Section.nPag, sizeof(uint32_t), 1, stream);
	ar << ob.grid4Section.nPag;
	//wrote = fwrite(&pgrid->grid4Section.nRow, sizeof(uint32_t), 1, stream);
	ar << ob.grid4Section.nRow;
	//wrote = fwrite(&pgrid->grid4Section.nCol, sizeof(uint32_t), 1, stream);
	ar << ob.grid4Section.nCol;
	//wrote = fwrite(&pgrid->grid4Section.xLL, sizeof(double), 1, stream);
	ar << ob.grid4Section.xLL;
	//wrote = fwrite(&pgrid->grid4Section.yLL, sizeof(double), 1, stream);
	ar << ob.grid4Section.yLL;
	//wrote = fwrite(&pgrid->grid4Section.zLL, sizeof(double), 1, stream);
	ar << ob.grid4Section.zLL;
	//wrote = fwrite(&pgrid->grid4Section.xSize, sizeof(double), 1, stream);
	ar << ob.grid4Section.xSize;
	//wrote = fwrite(&pgrid->grid4Section.ySize, sizeof(double), 1, stream);
	ar << ob.grid4Section.ySize;
	//wrote = fwrite(&pgrid->grid4Section.zSize, sizeof(double), 1, stream);
	ar << ob.grid4Section.zSize;
	//wrote = fwrite(&pgrid->grid4Section.vMin, sizeof(double), 1, stream);
	ar << ob.grid4Section.vMin;
	//wrote = fwrite(&pgrid->grid4Section.vMax, sizeof(double), 1, stream);
	ar << ob.grid4Section.vMax;

	double Rotation = 0.0;// not currently used
	//wrote = fwrite(&Rotation, sizeof(double), 1, stream);
	ar << Rotation;

	double BlankValue = BLANK_VALUE;//1.70141e38;// nodes are blanked if greater or equal to this value
	//wrote = fwrite(&BlankValue, sizeof(double), 1, stream);
	ar << BlankValue;

	uint32_t dataID = 0x44415441;
	//wrote = fwrite(&dataID, sizeof(uint32_t), 1, stream);
	ar << dataID;

	uint32_t dataSize = ob.grid4Section.nPag * ob.grid4Section.nRow * ob.grid4Section.nCol * sizeof(double);
	//wrote = fwrite(&dataSize, sizeof(uint32_t), 1, stream);
	ar << dataSize;

	uint32_t r, c, p;
	for (p = 0; p < ob.grid4Section.nPag; p++)
	{
		for (r = 0; r < ob.grid4Section.nRow; r++)
		{
			//wrote = fwrite(pgrid->grid4Section.v[p][r], sizeof(double), pgrid->grid4Section.nCol, stream);
			ar.Write((unsigned char *)ob.grid4Section.v[p][r], sizeof(double) * ob.grid4Section.nCol);
		}
	}

	//fclose(stream);

	//return 0;
//}

	return ar;
}
Archive& operator >>(Archive& ar, Grid4& ob)
{
//int ImportSurfer7Grid4(char *file, Grid4* pgrid)
//{
//printf("ImportSurfer7Grid4 %s\n", file);
//	char *p, ext[255];
//	FILE *stream;

//	p = strrchr(file,'.');
//	if (p)
//		strcpy(ext, p+1);

//	if (p && (strcmp(ext, "cub") == 0 || strcmp(ext, "CUB") == 0) )
//	{
		//MessageBox(0, ext, "grd",0);
		// open the file
//		if ((stream = fopen(file,"rb")) == NULL)
//		{
//			MessageBox(0, "Cannot open input file.\n", "Import", 
//				MB_OK | MB_ICONINFORMATION);
//			return -1;
//		}
		// считываем 
//		size_t read;
		uint32_t headerID;
		//read = fread(&headerID, sizeof(uint32_t), 1, stream);
		ar >> headerID;
		if (headerID != 0x42525377)
		{
			MessageBox(0, "This is not Surfer 7 Grid file", "ImportSurfer7Grid4", 0);
///			fclose(stream);
			return ar;
		}
		//else
		//	MessageBox(0, "This is Surfer 7 Grid file", "ImportSurfer7Grid4", 0);

		uint32_t headerSize;
		//read = fread(&headerSize, sizeof(uint32_t), 1, stream);
		ar >> headerSize;

		//char str[255];
		printf("headerSize = %d bytes", headerSize);
		//MessageBox(0, str, "ImportSurfer7Grid", 0);

		//if (headerSize > 0)
		//	fseek( stream, headerSize, SEEK_CUR );
		uint32_t Version;
		//wrote = fwrite(&Version, sizeof(uint32_t), 1, stream);
		ar >> Version;


		uint32_t gridID;
		//read = fread(&gridID, sizeof(uint32_t), 1, stream);
		ar >> gridID;
		if (gridID != 0x47524433)
		{
			MessageBox(0, "This is not Grid Section of file", "ImportSurfer7Grid4", 0);
			//fclose(stream);
			return ar;
		}
		//else
		//	MessageBox(0, "This is Grid Section of file", "ImportSurfer7Grid4", 0);

		uint32_t gridSize;
		//read = fread(&gridSize, sizeof(uint32_t), 1, stream);
		ar >> gridSize;

		printf("gridSize = %d bytes", gridSize);
		//MessageBox(0, str, "ImportSurfer7Grid4", 0);

		uint32_t nPag;// number of columns in the grid
		//read = fread(&nPag, sizeof(uint32_t), 1, stream);
		ar >> nPag;

		printf("number of pages in the grid nPag = %d \n", nPag);
		//MessageBox(0, str, "ImportSurfer7Grid4", 0);
 
		uint32_t nRow;// number of rows in the grid
		//read = fread(&nRow, sizeof(uint32_t), 1, stream);
		ar >> nRow;

		printf("number of rows in the grid nRow = %d \n", nRow);
		//MessageBox(0, str, "ImportSurfer7Grid4", 0);

		uint32_t nCol;// number of columns in the grid
		//read = fread(&nCol, sizeof(uint32_t), 1, stream);
		ar >> nCol;

		printf("number of columns in the grid nCol = %d \n", nCol);
		//MessageBox(0, str, "ImportSurfer7Grid4", 0);
 
		double xLL;// X coordinate of the lower left corner of the grid
		//read = fread(&xLL, sizeof(double), 1, stream);
		ar >> xLL;

		printf("X coordinate of the lower left corner of the grid xLL = %lf \n", xLL);
		//MessageBox(0, str, "ImportSurfer7Grid4", 0);
 
		double yLL;// Y coordinate of the lower left corner of the grid
		//read = fread(&yLL, sizeof(double), 1, stream);				
		ar >> yLL;


		printf("Y coordinate of the lower left corner of the grid yLL = %lf \n", yLL);
		//MessageBox(0, str, "ImportSurfer7Grid4", 0);
 
		double zLL;// Z coordinate of the lower left corner of the grid
		//read = fread(&zLL, sizeof(double), 1, stream);
		ar >> zLL;

		printf("Z coordinate of the lower left corner of the grid zLL = %lf \n", zLL);
		//MessageBox(0, str, "ImportSurfer7Grid4", 0);
 
		double xSize;// spacing between adjacent nodes in the X direction (between columns)
		//read = fread(&xSize, sizeof(double), 1, stream);
		ar >> xSize;

		printf("spacing between adjacent nodes in the X direction (between columns) xSize = %lf \n", xSize);
		//MessageBox(0, str, "ImportSurfer7Grid", 0);
  
		double ySize;// spacing between adjacent nodes in the Y direction (between rows)
		//read = fread(&ySize, sizeof(double), 1, stream);
		ar >> ySize;

		printf("spacing between adjacent nodes in the Y direction (between rows) ySize = %lf \n", ySize);
		//MessageBox(0, str, "ImportSurfer7Grid", 0);
  
		double zSize;// spacing between adjacent nodes in the Z direction (between rows)
		//read = fread(&zSize, sizeof(double), 1, stream);
		ar >> zSize;

		printf("spacing between adjacent nodes in the Z direction (between rows) zSize = %lf \n", zSize);
		//MessageBox(0, str, "ImportSurfer7Grid", 0);
  
		double vMin;// minimum V value within the grid
		//read = fread(&vMin, sizeof(double), 1, stream);
		ar >> vMin;

		printf("minimum V value within the grid vMin = %lf \n", vMin);
		//MessageBox(0, str, "ImportSurfer7Grid", 0);
 
		double vMax;// maximum V value within the grid
		//read = fread(&vMax, sizeof(double), 1, stream);
		ar >> vMax;

		printf("maximum V value within the grid vMax = %lf \n", vMax);
		//MessageBox(0, str, "ImportSurfer7Grid", 0);
 
		double Rotation;// not currently used
		//read = fread(&Rotation, sizeof(double), 1, stream);
		ar >> Rotation;

		printf("not currently used Rotation = %lf \n", Rotation);
		//MessageBox(0, str, "ImportSurfer7Grid", 0);
 
		double BlankValue;// nodes are blanked if greater or equal to this value
		//read = fread(&BlankValue, sizeof(double), 1, stream);
		ar >> BlankValue;

		printf("nodes are blanked if greater or equal to this value = %lf \n", BlankValue);
		//MessageBox(0, str, "ImportSurfer7Grid", 0);

		uint32_t dataID;
		//read = fread(&dataID, sizeof(uint32_t), 1, stream);
		ar >> dataID;
		if (dataID != 0x44415441)
		{
			MessageBox(0, "This is not Data Section of file", "ImportSurfer7Grid", 0);
			//fclose(stream);
			return ar;
		}
		//else
		//	MessageBox(0, "This is Data Section of file", "ImportSurfer7Grid", 0);

		uint32_t dataSize;
		//read = fread(&dataSize, sizeof(uint32_t), 1, stream);
		ar >> dataSize;

		//sprintf(str, "dataSize = %d bytes", dataSize);
		//MessageBox(0, str, "ImportSurfer7Grid", 0);

		ob.grid4Section.nPag		= nPag;
		ob.grid4Section.nRow		= nRow;
		ob.grid4Section.nCol		= nCol;
		ob.grid4Section.xLL		= xLL;
		ob.grid4Section.yLL		= yLL;
		ob.grid4Section.zLL		= zLL;
		ob.grid4Section.xSize	= xSize;
		ob.grid4Section.ySize	= ySize;
		ob.grid4Section.zSize	= zSize;
		ob.grid4Section.vMin		= vMin;
		ob.grid4Section.vMax		= vMax;
		ob.grid4Section.Rotation	= Rotation;
		ob.grid4Section.BlankValue = BlankValue;

		ob.grid4Section.v = Alloc3DMat<double>(nPag, nRow, nCol);

		if (ob.grid4Section.v == NULL)
		{
			printf("Error AllocDoubleMat return NULL\n");
			return ar;
		}

		for (uint32_t p = 0; p < nPag; p++)
		{
			for (uint32_t r = 0; r < nRow; r++)
			{
				//read = fread(pgrid->grid4Section.v[p][r], sizeof(double), nCol, stream);
				ar.Read((unsigned char *)ob.grid4Section.v[p][r], sizeof(double) * nCol);
#if 0
				for (uint32_t c = 0; c < nCol; c++)
					printf("%f\t", ob.grid4Section.v[p][r][c]);
				printf("\n");
#endif
			}
		}

//		fclose(stream);
//		return 0;
//
//	}
//	return -1;
//}


	return ar;
}



int ReadContourBlnFile(vdouble& x, vdouble& y)
{
	char *p, ext[255];
	FILE *stream;
	const unsigned int n = 1023;
	char szBuff[n];

	p = strrchr(szPath,'.');
	if (p)
		strcpy(ext, p+1);

	if (p && strcmp(ext, "bln") == 0)
	{
		//MessageBox(0, ext, "bln",0);
		// open the file
		if ((stream = fopen(szPath,"rt")) == NULL)
		{
			MessageBox(0, "Cannot open input file.\n", "Import", 
				MB_OK | MB_ICONINFORMATION);
			return -1;
		}
		int len;
		if (!feof(stream))
		{
			char * ch;
			ch = fgets(szBuff,n,stream);
			if( ch != NULL && strlen(szBuff) > 1)
			{
				len = atoi(szBuff);
			}
		}
		double X,Y;
		int i = 0;
		x.resize(len);
		y.resize(len);
		while (!feof(stream) && i < len)
		{
			char * ch;
			ch = fgets(szBuff,n,stream);
			if( ch != NULL && strlen(szBuff) > 1)
			{
				int rez = sscanf(szBuff,"%lf,%lf",
								&X, &Y);
				if (rez == 2 && rez != EOF)
				{
					x[i] = X;
					y[i] = Y;
					i++;
				}

			}
		}
		fclose(stream);
		if (i == len && i > 2)
			return 0;
		if (!(x[0] == x.End() && y[0] == y.End()))
		{
			MessageBox(0, "The contour is not closed!", "Warning", 0);
			return 1;
		}										
	}
	return -1;
}
int SetVisiblePointsInContour(Widget hwndParent, vdouble& xi, vdouble & yi, vdouble& xc, vdouble& yc, vdouble& visible)
{
	if ( xc.Length() != yc.Length() )
	{
		char errstr[1024];
		sprintf(errstr, 
			"lengthes of vectors xc(%d), yc(%d) must be equial",
			xc.Length(), yc.Length());
		MessageBox(0, errstr,"Error using SetVisiblePointsInContour",0);
		return -1;
	}
	int i,j,q, ind,
		m = xi.Length(), 
		n = yi.Length(), 
		lenc = xc.Length();


	RECT rcClient;  // Client area of parent window 
	int cyVScroll;  // Height of scroll bar arrow 
	HWND hwndPB;    // Handle of progress bar 
	DWORD cb,		// Size of file and count of
	  cb_read = 0,  // bytes read 
	  cb_disp = 0;  // bytes displayed


#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
	// Ensure that the common control DLL is loaded
	// and create a progress bar along the bottom of
	// the client area of the parent window. 
	// Base the height of the progress bar on the
	// height of a scroll bar arrow. 
	InitCommonControls(); 
	GetClientRect(hwndParent, &rcClient); 
	GetWindowRect(hwndParent, &rcClient); 
	cyVScroll = GetSystemMetrics(SM_CYVSCROLL); 
	hwndPB = CreateWindowEx(WS_EX_TOPMOST, PROGRESS_CLASS,
			 (LPSTR) NULL, 
			 //WS_CHILD | WS_VISIBLE,
			 WS_POPUPWINDOW,
			 //0, 0,
			 rcClient.left, rcClient.bottom-cyVScroll,
			 rcClient.right, cyVScroll, 
			 //hwndParent, 
			 NULL,
			 
			 (HMENU) 0, hInst, NULL); 

	ShowWindow(hwndPB,1);
#endif
	// Gets the file descriptor associated with a stream.
	//int fd = _fileno(stream);
	// Get the length of a file in bytes
	cb = lenc;



	// Set the range and increment of the progress
	// bar. 
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
	SendMessage(hwndPB, PBM_SETRANGE, 0,
				MAKELPARAM(0, cb)); 
	SendMessage(hwndPB, PBM_SETSTEP, (WPARAM) 1, 0); 
#endif




	vdouble angle,angle1,angle2, dangle, sum_dangle;

	visible.resize(n, m, 0.0);
	angle.resize(n, m);
	angle1.resize(n, m);
	angle2.resize(n, m);
	dangle.resize(n, m, 0.0);
	sum_dangle.resize(n, m, 0.0);
	for (q = 0; q < lenc; q++)
	{
		if(q > 0)
		{
			angle1 = angle;
		}
		for ( i = 0; i < m; i++)
		{
			for (j = 0; j < n; j++)
			{												
				angle(j,i) = atan2(
					yc[q] - yi[j], 
					xc[q] - xi[i]);			
			}
		}
		if(q > 0)
		{
			angle2 = angle;
			dangle = angle2 - angle1;
			Vector <int> indexes = Find(dangle > 1.9*PI);
			for (ind = 0; ind < indexes.Size(); ind++)
			{
				if (angle1[indexes[ind]] * angle2[indexes[ind]] < 0.0)
					dangle[indexes[ind]] -= 2*PI;
			}
			indexes = Find(dangle < -1.9*PI);
			for (ind = 0; ind < indexes.Size(); ind++)
			{
				if (angle1[indexes[ind]] * angle2[indexes[ind]] < 0.0)
					dangle[indexes[ind]] += 2*PI;
			}
			sum_dangle += dangle;
		}
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
		SendMessage(hwndPB, PBM_STEPIT, 0, 0); 
#endif
	}
/*	q = 0; 
	{
			angle1 = angle;
		for ( i = 0; i < m; i++)
		{
			for (j = 0; j < n; j++)
			{												
				angle(i,j) = atan2(
					yc[q] - yi[j], 
					xc[q] - xi[i]);
			}
		}
			angle2 = angle;
			dangle = angle2 - angle1;
			Vector <int> indexes = Find(dangle > 4.*PI/3.);
			for (int ind = 0; ind < indexes.Size(); ind++)
			{
				if (angle1[indexes[ind]] * angle2[indexes[ind]] < 0.0)
					dangle[indexes[ind]] -= 2*PI;
			}
			indexes = Find(dangle < -4.*PI/3.);
			for (ind = 0; ind < indexes.Size(); ind++)
			{
				if (angle1[indexes[ind]] * angle2[indexes[ind]] < 0.0)
					dangle[indexes[ind]] += 2*PI;
			}
			sum_dangle += dangle;
		SendMessage(hwndPB, PBM_STEPIT, 0, 0); 
//				RECT rect;
//				GetClientRect(hwndParent,&rect);
//				InvalidateRect(hwndParent,&rect, true);
//MessageBox(0,"","",0);

	}*/
	// 
	Vector <int> indexes = Find(sum_dangle > 1.9*PI || sum_dangle < -1.9*PI);
	for (int ind = 0; ind < indexes.Size(); ind++)
	{
		visible[indexes[ind]] = 1.0;
	}

#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
	DestroyWindow(hwndPB);
#endif
	return 0;
}
#if !FAST_GRID_LOADING
DWORD WINAPI SetVisiblePointsInContour(void * p)
{
	CGrid* pThis;
	MessageBox(0,"SetVisiblePointsInContour(void * p)","",0);
	if (p)
		pThis = reinterpret_cast<CGrid*>(p);
	else
	{
		pThis = NULL;
		return 1;
	}

	if (pThis->SetVisiblePointsInContour() == 0)
	{
		SendMessage(pThis->hwndParent, WM_COMMAND, ID_WINSURF_DRAW, 0);
		SendMessage(pThis->hwndParent, WM_COMMAND, ID_WINSURF_FILE_SAVEAS_SURFER7_GRID,0);
	}
	return 0;
}
#endif
