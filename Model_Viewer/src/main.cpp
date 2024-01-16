#include "stdafx.h"
#include "ModelViewer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication applicationObj(argc, argv);
    ModelViewer modelViewerObj;
    modelViewerObj.show();
    return applicationObj.exec();
}
