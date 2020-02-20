#include "auto_build_3d.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto_build_3D w;
    w.show();

    return a.exec();
}
