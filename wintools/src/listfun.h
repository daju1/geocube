#ifndef LISTFUN_H
#define LISTFUN_H

#include "commctrl.h"
#include "..\..\tools\src\readfile.h"

#include <vector>
using namespace std;

RECT GetComboBoxRect(RECT * rcHeader);
RECT GetTextRect(RECT * rcHeader);

// Новый отработчик сообщений ListView1 
LRESULT APIENTRY ListViewWndSubclassProc(
    HWND hwnd, 
    UINT uMsg, 
    WPARAM wParam, 
    LPARAM lParam);

LRESULT APIENTRY ComboBoxWndSubclassProc(
    HWND hwnd, 
    UINT uMsg, 
    WPARAM wParam, 
    LPARAM lParam);

LRESULT APIENTRY EditWndSubclassProc(
    HWND hwnd, 
    UINT uMsg, 
    WPARAM wParam, 
    LPARAM lParam);

LRESULT APIENTRY HeaderWndSubclassProc(
    HWND hwnd, 
    UINT uMsg, 
    WPARAM wParam, 
    LPARAM lParam);

BOOL CALLBACK DlgProcDrillsList(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
HWND CreateListView (HWND hwndParent, LPVOID lpParam);
HWND CreateListView (HWND hwndParent, int x, int y, double part_h, double part_v); 
VOID SetView(HWND hWndListView, DWORD dwView);
BOOL InitListViewImageLists(HWND hWndListView);
BOOL InitListViewColumns(HWND hWndListView, vector<string> * headers, bool add_combo);

typedef struct
{
	HWND hWnd;
	vector<vector<cell> > * pdrills;
	vector<string> * pnames_of_colomns;
	vector<int> * types_of_colomns;
	vector<int> * checking_of_rows;
	vector<COLORREF> * colors_of_sloi;
	char* filename;

}	DRILLSDLGDATA, *LPDRILLSDLGDATA;

typedef struct
{
	HWND hwndComboBox;
	COLORREF color;
} COLOMNDATA, *LPCOLOMNDATA;


#define XBITMAP 16 
#define YBITMAP 16 



#endif