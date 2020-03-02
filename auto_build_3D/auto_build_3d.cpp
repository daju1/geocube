#include "auto_build_3d.h"
#include "ui_auto_build_3d.h"
#include "AutoProfileBuilding.h"


auto_build_3D::auto_build_3D(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::auto_build_3D)
{
    ui->setupUi(this);

    AutoBuildProfile::auto_build_parametrs_Init1();
    abpd1 = new AutoBuildProfileDlg1(true, NULL, AutoBuildProfile::ab);		// ...right after the dialog is closed?
}

auto_build_3D::~auto_build_3D()
{
    delete ui;
    delete abpd1;
}

void auto_build_3D::on_pushButton_clicked()
{
    abpd1->HandlingOfInputFiles();

}
