#ifndef COLORMAP_H
#define COLORMAP_H

extern LPCSTR colormaps[];

extern LPCSTR colormap_strings[];


#define XBITMAP2 16 
#define YBITMAP2 16 
 
#define BUFFER MAX_PATH 

extern WNDPROC wpOrigListBoxProc2; 
 
// Subclass procedure 
LRESULT APIENTRY ListBoxPaletteSubclassProc(
    HWND hwnd, 
    UINT uMsg, 
    WPARAM wParam, 
    LPARAM lParam) ;

void AddCheckedPaletteItem(HWND hwndList, LPSTR lpstr, LPARAM check) ;

#endif