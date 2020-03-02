#include "filedlg.h"
#include <QFileDialog>

#define PATH_STRING_SIZE 1024
char szPath[PATH_STRING_SIZE];
char directory[255];


HRESULT SaveProfDlg(HWND hWnd, LPTSTR lpstrFile, TCHAR filter[], DWORD& nFilterIndex, SSaveProfData &sprData)
{

}


HRESULT OpenFileDlg(HWND hWnd, LPCTSTR lpstrFilter, LPTSTR lpstrFile )
{
    QString fileName = QFileDialog::getOpenFileName(NULL, "Open File",
                                                    "/home",
                                                    lpstrFilter);

    strcpy(lpstrFile, fileName.toStdString().c_str());
}
HRESULT SaveFileDlg(HWND hWnd, LPTSTR lpstrFile, TCHAR filter[], DWORD& nFilterIndex)
{
    QStringList filters;
    //filters << "Image files (*.png *.xpm *.jpg)"
    //        << "Text files (*.txt)"
    //        << "Any files (*)";

    filters << filter;

    QString fileName = QFileDialog::getSaveFileName(NULL, "Save File",
                               lpstrFile,
                               filter);
    strcpy(lpstrFile, fileName.toStdString().c_str());

}

bool BroseDirDlg(HWND hWnd, char * dir)
{
    
}
