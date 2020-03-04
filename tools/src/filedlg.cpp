//#include <stdio.h>
#include "../stdafx.h"
#include "filedlg.h"
#include "../../resource.h"
#include "../../mylicense.h"

//extern /*UINT_PTR*/unsigned int CALLBACK DlgProcSaveMesh(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
extern HINSTANCE hInst;   // текущий экземпляр



char szPath[PATH_STRING_SIZE];
char directory[255];


unsigned int CALLBACK DlgProcSaveMesh(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    SSavePlotData *pspdData;
    LPOPENFILENAME lpOFN;

    switch (message)
    {
        case WM_INITDIALOG:
            // Save off the long pointer to the OPENFILENAME structure.
            SetWindowLongPtr(hDlg, DWLP_USER /*DWL_USER*/, lParam);

            lpOFN = (LPOPENFILENAME)lParam;
            pspdData = (SSavePlotData *)lpOFN->lCustData;
/*            SendDlgItemMessage(hDlg, IDC_SAVESELECTEDONLY, BM_SETCHECK, psmdData->bSaveSelectedOnly ? BST_CHECKED : BST_UNCHECKED, 0);
            SendDlgItemMessage(hDlg, IDC_SAVEHIERARCHY, BM_SETCHECK, psmdData->bSaveHierarchy ? BST_CHECKED : BST_UNCHECKED, 0);
            SendDlgItemMessage(hDlg, IDC_SAVEANIMATION, BM_SETCHECK, psmdData->bSaveAnimation ? BST_CHECKED : BST_UNCHECKED, 0);

            switch (psmdData->xFormat)
            {
                case D3DXF_FILEFORMAT_BINARY:
                    CheckRadioButton(hDlg,IDC_TEXT,IDC_BINARYCOMPRESSED,IDC_BINARY);
                    break;

                case D3DXF_FILEFORMAT_TEXT:
                    CheckRadioButton(hDlg,IDC_TEXT,IDC_BINARYCOMPRESSED,IDC_TEXT);
                    break;

                case D3DXF_FILEFORMAT_BINARY | D3DXF_FILEFORMAT_COMPRESSED:
                    CheckRadioButton(hDlg,IDC_TEXT,IDC_BINARYCOMPRESSED,IDC_BINARYCOMPRESSED);
                    break;
            }*/

            break;

        case WM_DESTROY:
            lpOFN = (LPOPENFILENAME)GetWindowLongPtr(hDlg, DWLP_USER /*DWL_USER*/);
            pspdData = (SSavePlotData *)lpOFN->lCustData;

/*            
			psmdData->bSaveSelectedOnly = (BST_CHECKED == IsDlgButtonChecked(hDlg, IDC_SAVESELECTEDONLY));
            psmdData->bSaveHierarchy = (BST_CHECKED == IsDlgButtonChecked(hDlg, IDC_SAVEHIERARCHY));
            psmdData->bSaveAnimation = (BST_CHECKED == IsDlgButtonChecked(hDlg, IDC_SAVEANIMATION));

            if (BST_CHECKED == IsDlgButtonChecked(hDlg, IDC_TEXT))
                psmdData->xFormat = D3DXF_FILEFORMAT_TEXT;
            else if (BST_CHECKED == IsDlgButtonChecked(hDlg, IDC_BINARY))
                psmdData->xFormat = D3DXF_FILEFORMAT_BINARY;
            else if (BST_CHECKED == IsDlgButtonChecked(hDlg, IDC_BINARYCOMPRESSED))
                psmdData->xFormat = D3DXF_FILEFORMAT_BINARY | D3DXF_FILEFORMAT_COMPRESSED;
*/
            break;

        default:
            return FALSE;
    }
    return TRUE;
}
UINT_PTR CALLBACK DlgProcSaveProf(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    SSaveProfData *psprData;
    LPOPENFILENAME lpOFN;

    switch (message)
    {
        case WM_INITDIALOG:
            // Save off the long pointer to the OPENFILENAME structure.
            SetWindowLongPtr(hDlg, DWLP_USER /*DWL_USER*/, lParam);

            lpOFN = (LPOPENFILENAME)lParam;
            psprData = (SSaveProfData *)lpOFN->lCustData;
/*            SendDlgItemMessage(hDlg, IDC_SAVESELECTEDONLY, BM_SETCHECK, psmdData->bSaveSelectedOnly ? BST_CHECKED : BST_UNCHECKED, 0);
            SendDlgItemMessage(hDlg, IDC_SAVEHIERARCHY, BM_SETCHECK, psmdData->bSaveHierarchy ? BST_CHECKED : BST_UNCHECKED, 0);
            SendDlgItemMessage(hDlg, IDC_SAVEANIMATION, BM_SETCHECK, psmdData->bSaveAnimation ? BST_CHECKED : BST_UNCHECKED, 0);
            }*/
			switch (psprData->export_coordinate_type)
			{
			case SAVE_PROFILE_3D_XYZ:
				{
					CheckRadioButton( hDlg,					
						IDC_RADIO_3D_XYZ,
						IDC_RADIO_AUTO_NORTH_OR_EAST_OR_GORIZONTAL_PROJECTION,
						IDC_RADIO_3D_XYZ);	
				}
				break;
			case SAVE_PROFILE_WITH_PROFILE_LEN:
				{
					CheckRadioButton( hDlg,					
						IDC_RADIO_3D_XYZ,
						IDC_RADIO_AUTO_NORTH_OR_EAST_OR_GORIZONTAL_PROJECTION,
						IDC_RADIO_PROFILE_LEN);
				}
				break;
			case SAVE_PROFILE_WITH_NORTH_PROJECTION:
				{
					CheckRadioButton( hDlg,
						IDC_RADIO_3D_XYZ,
						IDC_RADIO_AUTO_NORTH_OR_EAST_OR_GORIZONTAL_PROJECTION,
						IDC_RADIO_NORTH_PROJECTION);
				}
				break;
			case SAVE_PROFILE_WITH_EAST_PROJECTION:
				{
					CheckRadioButton( hDlg,
						IDC_RADIO_3D_XYZ,
						IDC_RADIO_AUTO_NORTH_OR_EAST_OR_GORIZONTAL_PROJECTION,
						IDC_RADIO_EAST_PROJECTION);
				}
				break;
			case SAVE_PROFILE_WITH_GORIZONTAL_PROJECTION:
				{
					CheckRadioButton( hDlg,
						IDC_RADIO_3D_XYZ,
						IDC_RADIO_AUTO_NORTH_OR_EAST_OR_GORIZONTAL_PROJECTION,
						IDC_RADIO_GORIZONTAL_PROJECTION);
				}
				break;
			case SAVE_PROFILE_AUTO_SELECT_PROJECTION:
				{
					CheckRadioButton( hDlg,
						IDC_RADIO_3D_XYZ,
						IDC_RADIO_AUTO_NORTH_OR_EAST_OR_GORIZONTAL_PROJECTION,
						IDC_RADIO_AUTO_NORTH_OR_EAST_OR_GORIZONTAL_PROJECTION);
				}
				break;
			}
            break;

        case WM_DESTROY:
            lpOFN = (LPOPENFILENAME)GetWindowLongPtr(hDlg, DWLP_USER/*DWL_USER*/);
            psprData = (SSaveProfData *)lpOFN->lCustData;

/*            
			psmdData->bSaveSelectedOnly = (BST_CHECKED == IsDlgButtonChecked(hDlg, IDC_SAVESELECTEDONLY));
            psmdData->bSaveHierarchy = (BST_CHECKED == IsDlgButtonChecked(hDlg, IDC_SAVEHIERARCHY));
            psmdData->bSaveAnimation = (BST_CHECKED == IsDlgButtonChecked(hDlg, IDC_SAVEANIMATION));
*/
            if (BST_CHECKED == IsDlgButtonChecked(hDlg, IDC_RADIO_3D_XYZ))
                psprData->export_coordinate_type = SAVE_PROFILE_3D_XYZ;

            else if (BST_CHECKED == IsDlgButtonChecked(hDlg, IDC_RADIO_PROFILE_LEN))
                psprData->export_coordinate_type = SAVE_PROFILE_WITH_PROFILE_LEN;

            else if (BST_CHECKED == IsDlgButtonChecked(hDlg, IDC_RADIO_NORTH_PROJECTION))
                psprData->export_coordinate_type = SAVE_PROFILE_WITH_NORTH_PROJECTION;

            else if (BST_CHECKED == IsDlgButtonChecked(hDlg, IDC_RADIO_EAST_PROJECTION))
                psprData->export_coordinate_type = SAVE_PROFILE_WITH_EAST_PROJECTION;

            else if (BST_CHECKED == IsDlgButtonChecked(hDlg, IDC_RADIO_GORIZONTAL_PROJECTION))
                psprData->export_coordinate_type = SAVE_PROFILE_WITH_GORIZONTAL_PROJECTION;

            else if (BST_CHECKED == IsDlgButtonChecked(hDlg, IDC_RADIO_AUTO_NORTH_OR_EAST_OR_GORIZONTAL_PROJECTION))
                psprData->export_coordinate_type = SAVE_PROFILE_AUTO_SELECT_PROJECTION;

            break;

        default:
            return FALSE;
    }
    return TRUE;
}
HRESULT SaveProfDlg(HWND hWnd, LPTSTR lpstrFile, TCHAR filter[], DWORD& nFilterIndex, SSaveProfData &sprData)
{
    HRESULT hr = S_OK;
	int iext;
    
    OPENFILENAME ofn;

    static TCHAR file[256];
    static TCHAR szFilepath[256];
    static TCHAR fileTitle[256];

    strcpy( file, lpstrFile);
    strcpy( fileTitle, TEXT(""));
    strcpy( fileTitle, lpstrFile);

    memset( &ofn, 0, sizeof(ofn) );
    ofn.lStructSize       = sizeof(OPENFILENAME);
    ofn.hwndOwner         = hWnd;
    ofn.hInstance         = hInst;
    ofn.lpstrFilter       = filter;
    ofn.lpstrCustomFilter = NULL;
    ofn.nMaxCustFilter    = 0L;
	if (nFilterIndex)
		ofn.nFilterIndex      = nFilterIndex;
	else
		ofn.nFilterIndex      = 0L;
    ofn.lpstrFile         = file;
    ofn.nMaxFile          = sizeof(file);
    ofn.lpstrFileTitle    = fileTitle;
    ofn.nMaxFileTitle     = sizeof(fileTitle);
    ofn.lpstrInitialDir   = NULL;
    ofn.lpstrDefExt       = NULL;
    ofn.lCustData         = (LPARAM)&sprData;
    ofn.lpfnHook          = DlgProcSaveProf;
    ofn.lpTemplateName    = MAKEINTRESOURCE(IDD_SAVE_PROFILE);
    ofn.Flags = OFN_OVERWRITEPROMPT | OFN_EXPLORER | OFN_ENABLETEMPLATE | OFN_ENABLEHOOK;

/*    spdData.bSaveSelectedOnly = FALSE;
    spdData.bSaveHierarchy = TRUE;
    spdData.bSaveAnimation = TRUE;
    spdData.xFormat = 0;//D3DXF_FILEFORMAT_TEXT;
*/

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
			MessageBox(0,"An attempt to subclass a list box failed because sufficient memory was not available.","CommDlgExtendedError",0);
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
			if (nFilterIndex)
				ofn.nFilterIndex      = nFilterIndex;
			else
				ofn.nFilterIndex      = 1L;
            ofn.lpstrFile         = file;
            ofn.nMaxFile          = sizeof(file);
            ofn.lpstrFileTitle    = fileTitle;
            ofn.nMaxFileTitle     = sizeof(fileTitle);
            ofn.lpstrInitialDir   = NULL;
            ofn.lpstrDefExt       = NULL;
            ofn.lCustData         = (LPARAM)&sprData;
			ofn.lpfnHook          = DlgProcSaveProf;
			ofn.lpTemplateName    = MAKEINTRESOURCE(IDD_SAVE_PROFILE);
			ofn.Flags = OFN_OVERWRITEPROMPT | OFN_EXPLORER | OFN_ENABLETEMPLATE | OFN_ENABLEHOOK;

            if ( ! GetSaveFileName( &ofn) )
            {
                dwErr = CommDlgExtendedError();
                if ( 0 != dwErr )
                {
                    sprintf( s, "GetOpenFileName failed with %x", dwErr );
                    MessageBox( hWnd, s, "TexWin", MB_OK | MB_SYSTEMMODAL );
                }
				hr = S_FALSE;
                goto e_Exit;
            }
        }
        else  // just a cancel, return
        {
			hr = S_FALSE;
            goto e_Exit;
        }
    }
	//===============================================================
	//===============================================================
	//===============================================================
	nFilterIndex = ofn.nFilterIndex;
	//===============================================================
	//===============================================================
	//===============================================================
	char *p, ext[16];
	p = filter;
	for (iext = 0; iext < 2*((int)ofn.nFilterIndex-1)+1; iext++)
	{
		p = strchr(p,'\0');
		p = p+1;
	}
	if (p) p = p+1;
	if (p && strcmp(p,".*") != 0)
		strcpy(ext,p);
	else
		strcpy(ext,"\0");
	//===============================================================
	//===============================================================
	//===============================================================
	p = strrchr(file,'.');
	if (strcmp(ext, "\0") != 0)
	{
		if (p)
		{
			if (p && strcmp(ext, p) == 0)
			{
			}
			else
			{
				if (strlen(p) <= strlen(ext) || strrchr(p,'/') || strrchr(p,'\\'))
					strcpy(p, ext);
				else
					strcat(file, ext);
			}
		}
		else
		{
			strcat(file, ext);
		}
	}
	strcpy(lpstrFile, file);
	strcpy(directory, file);
	p = strrchr(directory,'\\');
	if(p)
		*p = '\0';
	else
	{
		p = strrchr(directory,'/');
		if(p)
			*p = '\0';
	}
	//===============================================================
	//===============================================================
	//===============================================================
e_Exit:
	if (!CheckMyLicense())
	{        
		MessageBox( hWnd, "Unabled to save the specified file!", "Save failed!", MB_OK);
		hr = S_FALSE;
	} 
    if (FAILED(hr))
    {
        MessageBox( hWnd, "Unabled to save the specified file!", "Save failed!", MB_OK);
    }

    return hr;
}


HRESULT SaveFileDlg(HWND hWnd, LPTSTR lpstrFile, TCHAR filter[], DWORD& nFilterIndex)
{
/*  Example:
 *			TCHAR filter[] =
 *                          TEXT("Bitmap files (*.bmp)\0*.bmp\0")
 *                          TEXT("Metafiles (*.emf)\0*.emf\0")
 *                          TEXT("All Files (*.*)\0*.*\0");
 */
    HRESULT hr = S_OK;
	int iext;
    SSavePlotData spdData;
    OPENFILENAME ofn;

    static TCHAR file[256];
    static TCHAR szFilepath[256];
    static TCHAR fileTitle[256];

    strcpy( file, lpstrFile);
    strcpy( fileTitle, TEXT(""));
    strcpy( fileTitle, lpstrFile);

    memset( &ofn, 0, sizeof(ofn) );
    ofn.lStructSize       = sizeof(OPENFILENAME);
    ofn.hwndOwner         = hWnd;
    ofn.hInstance         = hInst;
    ofn.lpstrFilter       = filter;
    ofn.lpstrCustomFilter = NULL;
    ofn.nMaxCustFilter    = 0L;
	if (nFilterIndex)
		ofn.nFilterIndex      = nFilterIndex;
	else
		ofn.nFilterIndex      = 0L;
    ofn.lpstrFile         = file;
    ofn.nMaxFile          = sizeof(file);
    ofn.lpstrFileTitle    = fileTitle;
    ofn.nMaxFileTitle     = sizeof(fileTitle);
    ofn.lpstrInitialDir   = NULL;
    ofn.lpstrDefExt       = NULL;
//    ofn.lCustData         = NULL;
//    ofn.lpfnHook          = NULL;
    ofn.lCustData         = (LPARAM)&spdData;
//    ofn.lpfnHook          = DlgProcSaveMesh;
//    ofn.lpTemplateName    = MAKEINTRESOURCE(IDD_SAVEPLOT);
    ofn.Flags = OFN_OVERWRITEPROMPT | OFN_EXPLORER /*| OFN_ENABLETEMPLATE | OFN_ENABLEHOOK*/;

    spdData.bSaveSelectedOnly = FALSE;
    spdData.bSaveHierarchy = TRUE;
    spdData.bSaveAnimation = TRUE;
    spdData.xFormat = 0;//D3DXF_FILEFORMAT_TEXT;


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

				if (ofn.lpstrFile) sprintf(ofn.lpstrFile, "\0");
			}
			break;
		case FNERR_SUBCLASSFAILURE :
			MessageBox(0,"An attempt to subclass a list box failed because sufficient memory was not available.","CommDlgExtendedError",0);
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
			if (nFilterIndex)
				ofn.nFilterIndex      = nFilterIndex;
			else
				ofn.nFilterIndex      = 1L;
            ofn.lpstrFile         = file;
            ofn.nMaxFile          = sizeof(file);
            ofn.lpstrFileTitle    = fileTitle;
            ofn.nMaxFileTitle     = sizeof(fileTitle);
            ofn.lpstrInitialDir   = NULL;
            ofn.lpstrDefExt       = NULL;
            ofn.lCustData         = (LPARAM)&spdData;
 //           ofn.lpfnHook          = DlgProcSaveMesh;
   //         ofn.lpTemplateName    = MAKEINTRESOURCE(IDD_SAVEPLOT);
            ofn.Flags = OFN_OVERWRITEPROMPT | OFN_EXPLORER /*| OFN_ENABLETEMPLATE | OFN_ENABLEHOOK*/;

            if ( ! GetSaveFileName( &ofn) )
            {
                dwErr = CommDlgExtendedError();
                if ( 0 != dwErr )
                {
                    sprintf( s, "GetOpenFileName failed with %x", dwErr );
                    MessageBox( hWnd, s, "TexWin", MB_OK | MB_SYSTEMMODAL );
                }
				hr = S_FALSE;
                goto e_Exit;
            }
        }
        else  // just a cancel, return
        {
			hr = S_FALSE;
            goto e_Exit;
        }
    }
	//===============================================================
	//===============================================================
	//===============================================================
	nFilterIndex = ofn.nFilterIndex;
	//===============================================================
	//===============================================================
	//===============================================================
	char *p, ext[16];
	p = filter;
	for (iext = 0; iext < 2*((int)ofn.nFilterIndex-1)+1; iext++)
	{
		p = strchr(p,'\0');
		p = p+1;
	}
	if (p) p = p+1;
	if (p && strcmp(p,".*") != 0)
		strcpy(ext,p);
	else
		strcpy(ext,"\0");
	//===============================================================
	//===============================================================
	//===============================================================
	p = strrchr(file,'.');
	if (strcmp(ext, "\0") != 0)
	{
		if (p)
		{
			if (p && strcmp(ext, p) == 0)
			{
			}
			else
			{
				if (strlen(p) <= strlen(ext) || strrchr(p,'/') || strrchr(p,'\\'))
					strcpy(p, ext);
				else
					strcat(file, ext);
			}
		}
		else
		{
			strcat(file, ext);
		}
	}
	strcpy(lpstrFile, file);
	strcpy(directory, file);
	p = strrchr(directory,'\\');
	if(p)
		*p = '\0';
	else
	{
		p = strrchr(directory,'/');
		if(p)
			*p = '\0';
	}
	//===============================================================
	//===============================================================
	//===============================================================
e_Exit:
	if (!CheckMyLicense())
	{
		hr = S_FALSE;
        MessageBox( hWnd, "Unabled to save the specified file!", "Save failed!", MB_OK);
	} 
    if (FAILED(hr))
    {
        MessageBox( hWnd, "Unabled to save the specified file!", "Save failed!", MB_OK);
    }

    return hr;
}

HRESULT OpenFileDlg(HWND hWnd, LPCTSTR lpstrFilter, LPTSTR lpstrFile)
{
    HRESULT hr = S_OK;
	OPENFILENAME ofn;       // common dialog box structure
	char szFile[4098];       // buffer for file name


	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	//
	// Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
	// use the contents of szFile to initialize itself.
	//
	ofn.lpstrFile[0] = '\0';

	ofn.lpstrFilter = lpstrFilter;
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	if (lpstrFile && strlen(lpstrFile))
		ofn.lpstrInitialDir = lpstrFile;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Display the Open dialog box. 

	if (GetOpenFileName(&ofn)==TRUE)
	{
		if (ofn.lpstrFile != NULL)
		{
			strcpy(szPath, ofn.lpstrFile);
			if (lpstrFile)				
				strcpy(lpstrFile, ofn.lpstrFile);


			strcpy(directory, ofn.lpstrFile);
			char *p1, *p2;
			p1 = strrchr(directory,'\\');
			p2 = strrchr(directory,'/');
			if(p1)
				*p1 = '\0';
			if(p2)
				*p2 = '\0';
		}

		/*FILE *stream;
		if ((stream = fopen(ofn.lpstrFile,"rt")) == NULL)
		{
			MessageBox(0, "Cannot open input file.\n", "Open Plot", 
				MB_OK | MB_ICONINFORMATION);
			return 0;
		}

		fclose(stream);*/
	}
	else
	{
//        char s[40];
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
			short size;
			memcpy(&size, ofn.lpstrFile, 2);
			char str[1024];
			sprintf(str, "The buffer pointed to by the lpstrFile member of the OPENFILENAME structure is too small for the file name specified by the user. The first two bytes of the lpstrFile buffer contain an integer value specifying the size = %d, in TCHARs, required to receive the full name. ", size);
			MessageBox(0, str,"CommDlgExtendedError",0);
			break;
		case FNERR_INVALIDFILENAME :
			{
				char err_str[255];
				sprintf(err_str, "A file name is invalid.\n%s", ofn.lpstrFile );
				MessageBox(0,err_str,"CommDlgExtendedError",0);
			}
			break;
		case FNERR_SUBCLASSFAILURE :
			MessageBox(0,"An attempt to subclass a list box failed because sufficient memory was not available.","CommDlgExtendedError",0);
			break;

		}
		hr = S_FALSE ;
	}

    if (FAILED(hr))
    {
        MessageBox( hWnd, "Unabled to open the specified file!", "Open failed!", MB_OK);
    }

    return hr;

}

#include <shlobj.h>
#include <shtypes.h>

bool BroseDirDlg(HWND hWnd, char * dir)
{	
	ITEMIDLIST idl;
	LPITEMIDLIST  pidl = &idl;
   LPSHELLFOLDER pDesktopFolder;
   OLECHAR       olePath[4098];
   ULONG         chEaten;
   ULONG         dwAttributes;
   HRESULT       hr = S_FALSE;

   // 
   // Get the path to the file we need to convert.
   // 
   //GetCurrentDirectory(4098, cur_dir);

   // 
   // Get a pointer to the Desktop's IShellFolder interface.
   // 
   if (SUCCEEDED(SHGetDesktopFolder(&pDesktopFolder)))
   {
       // 
       // IShellFolder::ParseDisplayName requires the file name be in
       // Unicode.
       // 
       MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, dir, -1,
                           olePath, 4098);

       // 
       // Convert the path to an ITEMIDLIST.
       // 
       hr = pDesktopFolder->/*lpVtbl->*/ParseDisplayName(//pDesktopFolder,
                                                     NULL,
                                                     NULL,
                                                     olePath,
                                                     &chEaten,
                                                     &pidl,
                                                     &dwAttributes);
       if (FAILED(hr))
       {
           // Handle error.
       }

       // 
       // pidl now contains a pointer to an ITEMIDLIST for .\readme.txt.
       // This ITEMIDLIST needs to be freed using the IMalloc allocator
       // returned from SHGetMalloc().
       // 

       //release the desktop folder object
         pDesktopFolder->/*lpVtbl->*/Release();
   } 

   char folder[4098];

	BROWSEINFO bi;
	bi.hwndOwner = hWnd;
	bi.pidlRoot = NULL;
	if (hr == S_OK ) 
		bi.pidlRoot = pidl;
	bi.pszDisplayName = folder;
	bi.lpszTitle = dir;
    bi.ulFlags = 0;
    bi.ulFlags = BIF_USENEWUI;
    bi.lpfn = NULL;
    bi.lParam = 0;
    bi.iImage = 0;

	CoInitialize(NULL);

	if (pidl = SHBrowseForFolder(&bi))
	{
		//SHGetPathFromIDListW(pidl, olePath);   // Make sure it is a path
		if (SHGetPathFromIDListA(pidl, dir))   // Make sure it is a path
			return true;
	}
	return false;
}

HRESULT SavePlot(HWND hWnd, HENHMETAFILE hMetaFile, LPCTSTR lpstrFile)
{
    HRESULT hr = S_OK;

    SSavePlotData spdData;
    OPENFILENAME ofn;
	const size_t n = 1024;

    static TCHAR file[n];
    static TCHAR szFilepath[n];
    static TCHAR fileTitle[n];
    static TCHAR filter[] =
                           //TEXT("Bitmap files (*.bmp)\0*.bmp\0")
                           TEXT("Metafiles (*.emf)\0*.emf\0")
                           TEXT("All Files (*.*)\0*.*\0");
    strcpy( file, lpstrFile);
    strcpy( fileTitle, TEXT(""));
    //strcpy( fileTitle, lpstrFile);

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
    ofn.lCustData         = (LPARAM)&spdData;
 //   ofn.lpfnHook          = DlgProcSaveMesh;
 //   ofn.lpTemplateName    = MAKEINTRESOURCE(IDD_SAVEPLOT);
    ofn.Flags = OFN_OVERWRITEPROMPT | OFN_EXPLORER /*| OFN_ENABLETEMPLATE | OFN_ENABLEHOOK*/;

    spdData.bSaveSelectedOnly = FALSE;
    spdData.bSaveHierarchy = TRUE;
    spdData.bSaveAnimation = TRUE;
    spdData.xFormat = 0;//D3DXF_FILEFORMAT_TEXT;


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
				SavePlot(hWnd, hMetaFile, "");
				goto e_Exit;
			}
			break;
		case FNERR_SUBCLASSFAILURE :
			MessageBox(0,"An attempt to subclass a list box failed because sufficient memory was not available.","CommDlgExtendedError",0);
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
            ofn.lCustData         = (LPARAM)&spdData;
//            ofn.lpfnHook          = DlgProcSaveMesh;
//            ofn.lpTemplateName    = MAKEINTRESOURCE(IDD_SAVEPLOT);
            ofn.Flags = OFN_OVERWRITEPROMPT | OFN_EXPLORER/* | OFN_ENABLETEMPLATE | OFN_ENABLEHOOK*/;

            if ( ! GetSaveFileName( &ofn) )
            {
                dwErr = CommDlgExtendedError();
                if ( 0 != dwErr )
                {
                    sprintf( s, "GetOpenFileName failed with %x", dwErr );
                    MessageBox( hWnd, s, "TexWin", MB_OK | MB_SYSTEMMODAL );
                }

                goto e_Exit;
            }
        }
        else  // just a cancel, return
        {
            goto e_Exit;
        }
    }
	if (ofn.nFilterIndex == 1)
		strcat(file, ".emf");

     if ( CopyEnhMetaFile( hMetaFile, file ) )
        MessageBox( hWnd, szFilepath, "Meta file saved",
                    MB_OK | MB_ICONINFORMATION );
     else
        MessageBox( hWnd, szFilepath, "Meta file NOT saved Error",
                    MB_OK | MB_ICONINFORMATION );

e_Exit:
    if (FAILED(hr))
    {
        MessageBox( hWnd, "Unabled to save the specified file!", "Save failed!", MB_OK);
    }

    return hr;
}
