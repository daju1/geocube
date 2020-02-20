#include "auto_build_3d.h"
#include "ui_auto_build_3d.h"

auto_build_3D::auto_build_3D(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::auto_build_3D)
{
    ui->setupUi(this);
}

auto_build_3D::~auto_build_3D()
{
    delete ui;
}
