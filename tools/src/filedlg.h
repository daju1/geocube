#ifndef FILE_DLG_INCLUDED
#define FILE_DLG_INCLUDED
#if defined (_MSC_VER)
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

HRESULT OpenFileDlg(HWND hWnd, LPCTSTR lpstrFilter, LPTSTR lpstrFile = NULL);
HRESULT SaveFileDlg(HWND hWnd, LPTSTR lpstrFile, TCHAR filter[], DWORD& nFilterIndex);
#if defined (_MSC_VER)
HRESULT SavePlot(HWND hWnd, HENHMETAFILE hMetaFile, LPCTSTR lpstrFile);
#endif
bool BroseDirDlg(HWND hWnd, char * dir);

#endif
