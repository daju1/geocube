#include "filedlg.h"
#include <QFileDialog>
#include <QDebug>

#define PATH_STRING_SIZE 1024
char szPath[PATH_STRING_SIZE];
char directory[255];


HRESULT SaveProfDlg(HWND hWnd, LPTSTR lpstrFile, TCHAR filter[], DWORD& nFilterIndex, SSaveProfData &sprData)
{
	return S_FALSE;
}

QStringList parse_filter(const TCHAR filter[])
{
    QStringList filters;
    int i = 0;
    for (LPCTSTR pszz = filter; *pszz; pszz += strlen(pszz) + 1, ++i) {
      //From our start to the cursor is our word.
      std::string s = std::string(pszz);
      if (0 == i%2)
          filters.push_back( QString(s.c_str()) );
    }

    return filters;
}


HRESULT OpenFileDlg(QWidget* hWnd, const TCHAR filter[], LPTSTR lpstrFile)
{
#if 0
    QString fileName = QFileDialog::getOpenFileName(hWnd, "Open File",
                                                    QDir("../../").absolutePath(),
                                                    filter);
    qDebug() << fileName;
    if (lpstrFile)
        strcpy(lpstrFile, fileName.toStdString().c_str());
    strcpy(szPath, fileName.toStdString().c_str());
    return S_OK;
#else

    QStringList filters = parse_filter(filter);

    QFileDialog dialog (hWnd);
    dialog.setNameFilters(filters);
    dialog.setDirectory(QDir("../../").absolutePath());
    if(dialog.exec())
    {
        QDir dir = dialog.directory();
        qDebug() << dir;
        QString dirAbsPath = dir.absolutePath();
        std::string dir_abs_path = dirAbsPath.toStdString();
        strcpy(directory, dir_abs_path.c_str());

        QStringList files = dialog.selectedFiles();
        qDebug() << files;
        if (files.size() > 0)
        {
            if (lpstrFile)
                strcpy(lpstrFile, files[0].toStdString().c_str());
            strcpy(szPath, files[0].toStdString().c_str());
        }
        return S_OK;
    }
#endif
    return S_FALSE;
}
HRESULT SaveFileDlg(QWidget* hWnd, LPTSTR lpstrFile, const TCHAR filter[], DWORD& nFilterIndex)
{
    QStringList filters;
    //filters << "Image files (*.png *.xpm *.jpg)"
    //        << "Text files (*.txt)"
    //        << "Any files (*)";

    filters << filter;

    QString fileName = QFileDialog::getSaveFileName(hWnd, "Save File",
                               lpstrFile,
                               filter);
    strcpy(lpstrFile, fileName.toStdString().c_str());
	return S_FALSE;
}

bool BroseDirDlg(HWND hWnd, char * dir)
{
#if 0
    QStringList files = QFileDialog::getOpenFileNames(
                            NULL,
                            "Select one or more files to open",
                            "/home",
                            "Images (*.png *.xpm *.jpg)");
#endif
	return S_FALSE;
}
