//PrintDlgBox.h
#ifndef PRINT_DLG_BOX_H
#define PRINT_DLG_BOX_H
void Print(HWND hwnd);
void PrintDefault(HWND hwnd);
void DisplayPrintSurfDialogBox(HWND hwnd);
unsigned int  CALLBACK PaintHook(HWND hwndDlg, UINT uMsg, WPARAM wParam,
    LPARAM lParam);
void SurfPrintedPageSetup(HWND hwnd);
void PrintPreview(HWND hwnd);
#if 0 // (_WIN32_WINNT >= 0x501)

HRESULT DisplayPrintPropertySheet(
    HWND hWnd  // Window that owns the property sheet
);
#endif
#endif