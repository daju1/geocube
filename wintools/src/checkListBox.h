#ifndef CHECK_LIST_BOX_H
#define CHECK_LIST_BOX_H


#define XBITMAP 16 
#define YBITMAP 16 
 
#define BUFFER MAX_PATH 


LRESULT APIENTRY ListBoxSubclassProc(
    HWND hwnd, 
    UINT uMsg, 
    WPARAM wParam, 
    LPARAM lParam) ;

void AddCheckedItem(HWND hwndList, LPSTR lpstr, LPARAM check) ;

#endif