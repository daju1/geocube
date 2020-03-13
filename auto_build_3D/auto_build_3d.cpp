#include "auto_build_3d.h"
#include "ui_auto_build_3d.h"
#include "AutoProfileBuilding.h"
#include <QFileDialog>

#include "Grid.h"


auto_build_3D::auto_build_3D(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::auto_build_3D)
{
    ui->setupUi(this);

    AutoBuildProfile::auto_build_parametrs_Init1();
    abpd1 = new AutoBuildProfileDlg1(true, NULL, AutoBuildProfile::ab);		// ...right after the dialog is closed?
    abpd1->hDlg = this;
}

auto_build_3D::~auto_build_3D()
{
    delete ui;
    delete abpd1;
}

void auto_build_3D::on_pushButton_handle_input_files_clicked()
{
    abpd1->OnButtonOK();
}

void auto_build_3D::on_pushButton_BrowseNumColomn_clicked()
{
    abpd1->OnButtonBrowseNumColomn();
}

void auto_build_3D::on_pushButton_TestImportCube_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, "Open File",
                                                    QDir("../../").absolutePath(),
                                                    "Cube (*.cub)");

    Grid4 cube;

    if (0 == ImportSurfer7Grid4(file.toStdString().c_str(), &cube))
    {
    }
}
