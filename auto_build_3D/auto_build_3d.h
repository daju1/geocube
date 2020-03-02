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

    AutoBuildProfileDlg * abpd;

private:
    Ui::auto_build_3D *ui;
};

#endif // AUTO_BUILD_3D_H
