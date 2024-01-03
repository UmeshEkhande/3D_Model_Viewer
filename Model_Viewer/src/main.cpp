#include "stdafx.h"
#include "Model_Viewer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Model_Viewer w;
    w.readSTL();
    w.show();
    return a.exec();
}
