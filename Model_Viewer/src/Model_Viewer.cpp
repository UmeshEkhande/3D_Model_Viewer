#include "stdafx.h"
#include "Model_Viewer.h"
#include "OpenGLWindow.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
using namespace std;

Model_Viewer::Model_Viewer(QWindow* parent) : QMainWindow(nullptr)
{
    setupUi();
}

Model_Viewer::~Model_Viewer()
{
}

void Model_Viewer::setupUi()
{
    resize(800, 600);
    mCentralWidget = new QWidget(this);
    QVBoxLayout* mVbuttonsLayout = new QVBoxLayout();
    QGridLayout* mBaseLayout = new QGridLayout(mCentralWidget);
    QTabWidget* mTabWidget = new QTabWidget(this);
    mTabWidget->setFixedSize(900, 720);

    QWidget* Tab1 = new QWidget(mTabWidget);
    QWidget* Tab2 = new QWidget(mTabWidget);

    mRenderer = new OpenGLWindow(QColor(0, 0, 0), this);
    mVbuttonsLayout->addWidget(mRenderer, 1);
    Tab1->setLayout(mVbuttonsLayout);
    Tab2->setLayout(mVbuttonsLayout);

    mTabWidget->addTab(Tab2, "Tab2");
    setWindowTitle(QCoreApplication::translate("3D Model Viewer", "3D Model Viewer", nullptr));
}

void Model_Viewer::readSTL()
{
    std::string filePath = "Resources/cube1.stl";

    std::ifstream dataFile;
    dataFile.open(filePath);
    if (!dataFile.is_open())
    {
        std::cout << "File not exist" << std::endl;
        return;
    }

    std::string line;
    int count = 0;
    while (std::getline(dataFile, line))
    {

        if (line.find("vertex") != std::string::npos)
        {
            std::istringstream iss(line);
            std::string token;
            double x, y, z;
            iss >> token >> x >> y >> z;
            mVertices << x * 10 << y * 10 << z * 10;
            mColors << 1.0f << 0.0f << 0.0f;

            std::getline(dataFile, line);
            std::istringstream iss1(line);
            std::string token1;
            double x1, y1, z1;
            iss1 >> token1 >> x1 >> y1 >> z1;
            mVertices << x1 * 10 << y1 * 10 << z1 * 10;
            mColors << 1.0f << 0.0f << 0.0f;

            std::getline(dataFile, line);
            std::istringstream iss2(line);
            std::string token2;
            double x2, y2, z2;
            iss2 >> token2 >> x2 >> y2 >> z2;
            mVertices << x2 * 10 << y2 * 10 << z2 * 10;
            mColors << 1.0f << 0.0f << 0.0f;
            mVertices << x * 10 << y * 10 << z * 10;
            mColors << 1.0f << 0.0f << 0.0f;
        }
    }
    mRenderer->setVectorOfLines(mVertices);
    mRenderer->setColorOfLines(mColors);
    mRenderer->updateData(mVertices, mColors);
    mVertices.clear();
    mColors.clear();
    dataFile.close();
}
