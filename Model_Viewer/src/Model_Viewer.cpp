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

    resize(1024, 768);
    mCentralWidget = new QWidget(this);
    mMainLayout = new QVBoxLayout(mCentralWidget);
    mTabWidget = new QTabWidget(this);
    mTabWidget->setFixedSize(1024, 768);

    modelViewTab = new QWidget(mTabWidget);

    modelViewLayout = new QHBoxLayout(modelViewTab);
    mRenderer = new OpenGLWindow(QColor(0, 0, 0), this);
    modelViewLayout->addWidget(mRenderer, 3);  

    settingsLayout = new QVBoxLayout();

    loadStlButton = new QPushButton("Load Obj");
    settingsLayout->addWidget(loadStlButton);
    connect(loadStlButton, &QPushButton::clicked, this, &Model_Viewer::openFileDialog);

    clearButton = new QPushButton("Clear");
    settingsLayout->addWidget(clearButton);
    connect(clearButton, &QPushButton::clicked, this, &Model_Viewer::clearnScreen);

    wireFrameButton = new QPushButton("WireFrame View");
    settingsLayout->addWidget(wireFrameButton);
    connect(wireFrameButton, &QPushButton::clicked, this, &Model_Viewer::wireFramButtonClicked);

    coloredButton = new QPushButton("Colored View");
    settingsLayout->addWidget(coloredButton);
    connect(coloredButton, &QPushButton::clicked, this, &Model_Viewer::ColoredButtonClicked);


    modelViewLayout->addLayout(settingsLayout, 0);  
    mTabWidget->addTab(modelViewTab, "Model View");
    mMainLayout->addWidget(mTabWidget);
    setCentralWidget(mCentralWidget);
    setWindowTitle(QCoreApplication::translate("3D Model Viewer", "3D Model Viewer", nullptr));
}


void Model_Viewer::openFileDialog()
{
    QString qFileName = QFileDialog::getOpenFileName(this, tr("Open Obj File"), "", tr("obj Files (*.obj);;All Files (*)"));

    if (!qFileName.isEmpty()) {
        std::string fileName = qFileName.toStdString();

        ReadObjFile objReader;
        objReader.readObjFile(fileName);

        vertices = objReader.getVertices();
        textureCoords = objReader.getTextureCoords();
        normals = objReader.getNormals();
        faces = objReader.getFaces();

        for (int i = 0; i < vertices.size(); i++) {
            ver << vertices[i].x() << vertices[i].y() << vertices[i].z();
        }

        for (int i = 0; i < normals.size(); i++)
        {
            nor << normals[i].x() << normals[i].y() << normals[i].z();

        }

        mRenderer->updateData(ver, nor);

    }
}

void Model_Viewer::clearnScreen()
{
    ver.clear();
    nor.clear();
    mRenderer->updateData(ver, nor);
}

void Model_Viewer::wireFramButtonClicked()
{
    mRenderer->setFlag(false);
}

void Model_Viewer::ColoredButtonClicked()
{
    mRenderer->setFlag(true);
}

