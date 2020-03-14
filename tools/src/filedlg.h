#ifndef FILE_DLG_INCLUDED
#define FILE_DLG_INCLUDED
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
#include <windows.h>
#else
#include <mywindows.h>
#endif
struct SSavePlotData
{
    BOOL bSaveSelectedOnly;
    BOOL bSaveHierarchy;
    BOOL bSaveAnimation;
    DWORD xFormat;
};
#define SAVE_PROFILE_3D_XYZ							0
#define SAVE_PROFILE_WITH_PROFILE_LEN				1
#define SAVE_PROFILE_WITH_NORTH_PROJECTION			2
#define SAVE_PROFILE_WITH_EAST_PROJECTION			3
#define SAVE_PROFILE_WITH_GORIZONTAL_PROJECTION		4
#define SAVE_PROFILE_AUTO_SELECT_PROJECTION			5
class SSaveProfData
{
public:
	short export_coordinate_type;
	SSaveProfData()
	{
		export_coordinate_type = SAVE_PROFILE_WITH_PROFILE_LEN;
	}

};
HRESULT SaveProfDlg(HWND hWnd, LPTSTR lpstrFile, TCHAR filter[], DWORD& nFilterIndex, SSaveProfData &sprData);
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
HRESULT OpenFileDlg(HWND hWnd, const TCHAR filter[], LPTSTR lpstrFile = NULL);
HRESULT SaveFileDlg(HWND hWnd, LPTSTR lpstrFile, const TCHAR filter[], DWORD& nFilterIndex);

HRESULT SavePlot(HWND hWnd, HENHMETAFILE hMetaFile, LPCTSTR lpstrFile);
#else
HRESULT OpenFileDlg(QWidget* hWnd, const TCHAR filter[], LPTSTR lpstrFile = NULL);
HRESULT SaveFileDlg(QWidget* hWnd, LPTSTR lpstrFile, const TCHAR filter[], DWORD& nFilterIndex);
#endif
bool BroseDirDlg(HWND hWnd, char * dir);

#endif
