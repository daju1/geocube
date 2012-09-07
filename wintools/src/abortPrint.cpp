#include "stdafx.h"
#include "abortPrint.h"

BOOL bAbortPrinting    = FALSE;
HWND hAbortPrintingDlg = NULL;


int CALLBACK AbortPrinting( HDC hdcPrinter, int Code )
{
    MSG msg;

    while ( !bAbortPrinting && PeekMessage( &msg, NULL, 0, 0, PM_REMOVE) )
    {
        if ( !IsDialogMessage( hAbortPrintingDlg, &msg ) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
    }

    // ѕараметр bAbort равен TRUE (возвращаемое значение - FALSE), 
    // только если пользователь отменил операцию печати.
    //..............................................

    return (!bAbortPrinting);
}

LRESULT CALLBACK DlgProcAbortPrinting( HWND hWnd, UINT message,
                           WPARAM wParam, LPARAM lParam )
{
    switch( message )
    {
       case WM_INITDIALOG :
                 ShowWindow( hWnd, SW_NORMAL );
                 SetFocus( hWnd );
                 UpdateWindow( hWnd );
                 return( TRUE );

       case WM_COMMAND    :
                 // была нажата кнопка Cancel;
                 // прекратить печать документа.
                 //...............................
                 if ( LOWORD(wParam) == IDCANCEL )
                 {
                     bAbortPrinting = TRUE;
                     DestroyWindow( hWnd );
                     return( TRUE );
                 }
                 break;
    }

    return( FALSE );
}
