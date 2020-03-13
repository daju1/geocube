#ifndef AUTO_BUILD_3D_H
#define AUTO_BUILD_3D_H

#include <QMainWindow>
#include "AutoBuildProfileDlg.h"

namespace Ui {
class auto_build_3D;
}

class auto_build_3D : public QMainWindow
{
    Q_OBJECT

public:
    explicit auto_build_3D(QWidget *parent = 0);
    ~auto_build_3D();

    AutoBuildProfileDlg1 * abpd1;

private slots:
    void on_pushButton_handle_input_files_clicked();

    void on_pushButton_BrowseNumColomn_clicked();

    void on_pushButton_TestImportCube_clicked();

private:
    Ui::auto_build_3D *ui;
};

#endif // AUTO_BUILD_3D_H
