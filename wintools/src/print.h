// print.h

int BeginPrinting(HWND hWnd, PRINTDLG * pd);
HDC BeginPrintPreview(PAGESETUPDLG * psd);
void EndPrintPreview(HDC hPrintDC, PAGESETUPDLG * psd);
void OnPrint(HWND hWnd, HDC hDC, bool bPreview, HDC hprinterDC = NULL, RECT * rcPreview = NULL);


