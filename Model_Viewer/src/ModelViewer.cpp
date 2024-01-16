#include "stdafx.h"
#include "ModelViewer.h"
#include "OpenGLWindow.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
using namespace std;

ModelViewer::ModelViewer(QWindow* parent) : QMainWindow(nullptr)
{

    setupUi();
    connect(loadStlButton,  &QPushButton::clicked, this, &ModelViewer::openFileDialog);
    connect(clearButton,    &QPushButton::clicked, this, &ModelViewer::clearnScreen);
    connect(wireFrameButton,&QPushButton::clicked, this, &ModelViewer::wireFramButtonClicked);
    connect(coloredButton,  &QPushButton::clicked, this, &ModelViewer::coloredButtonClicked);
}

ModelViewer::~ModelViewer()
{
}

// Function to set up UI elements
void ModelViewer::setupUi()
{
    resize(1920, 1080);
    createMenus();

    mCentralWidget          = new QWidget(this);
    mMainLayout             = new QVBoxLayout(mCentralWidget);
    modelViewTab            = new QWidget(mCentralWidget); 
    modelViewLayout         = new QHBoxLayout(modelViewTab);
    mRenderer               = new OpenGLWindow(QColor(0, 0, 0), this);
    settingsLayoutContainer = new QWidget();
    ButtonContainer         = new QWidget();
    settingsLayout          = new QVBoxLayout();
    loadStlButton           = new QPushButton("Load Obj Model");
    clearButton             = new QPushButton("Clear Screen");
    wireFrameButton         = new QPushButton("Mesh View");
    coloredButton           = new QPushButton("Colored View");

    modelViewLayout->addWidget(mRenderer,1);
    modelViewLayout->setContentsMargins(0, 0, 0, 0);

    settingsLayoutContainer->setFixedHeight(1080);
    settingsLayoutContainer->setFixedWidth(300);
    settingsLayoutContainer->setStyleSheet("background-color: rgb(0, 0, 0);");

    settingsLayout->setContentsMargins(80, 0, 80, 800);
    settingsLayout->setSpacing(0);
    
    loadStlButton->setFont(QFont("Arial", 11));
    loadStlButton->setStyleSheet("background-color: white;");

    clearButton->setFont(QFont("Arial", 11));
    clearButton->setStyleSheet("background-color: white;");

    wireFrameButton->setFont(QFont("Arial", 11));
    wireFrameButton->setStyleSheet("background-color: white;");

    coloredButton->setFont(QFont("Arial", 11));
    coloredButton->setStyleSheet("background-color: white;");

    coloredButton->setFont(QFont("Arial", 11));
    coloredButton->setStyleSheet("background-color: white;");

    settingsLayout->addWidget(loadStlButton);
    settingsLayout->addWidget(clearButton);
    settingsLayout->addWidget(wireFrameButton);
    settingsLayout->addWidget(coloredButton);

    settingsLayoutContainer->setLayout(settingsLayout);
    modelViewLayout->addWidget(settingsLayoutContainer);
    mMainLayout->addWidget(modelViewTab);  

    setCentralWidget(mCentralWidget);
    setWindowTitle(QCoreApplication::translate("3D Model Viewer", "3D Model Viewer", nullptr)); 
}

void ModelViewer::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(tr("&Open..."), QKeySequence::Open, this, &ModelViewer::openFileDialog);
    fileMenu->addAction(tr("E&xit"), QKeySequence::Quit, this, &ModelViewer::close);
}

// Function to read data from obj file
void ModelViewer::readObjFileData(std::string inFileName)
{
    if (!inFileName.empty())
    {
        MaterialFileReader obj(inFileName);
        const char* fileName = inFileName.c_str();
        obj.LoadObj(shapes, materials, fileName, 0);

        mVerticesNo = (int)shapes[0].mesh.positions.size();
        mNormalsNo  = (int)shapes[0].mesh.normals.size();
        mIndicesNo  = (int)shapes[0].mesh.indices.size();

        mVertices = new GLfloat[mVerticesNo];
        mNormals  = new GLfloat[mNormalsNo];
        mIndices  = new GLuint[mIndicesNo];

        for (int i = 0; i < mVerticesNo; i++) {
            mVertices[i] = (shapes[0].mesh.positions[i]);
        }

        for (int i = 0; i < mNormalsNo; i++) {
            mNormals[i] = shapes[0].mesh.normals[i];
        }

        for (int i = 0; i < mIndicesNo; i++) {
            mIndices[i] = shapes[0].mesh.indices[i];
        }

        updateRenderingData();

    }
}

// Sends the data for rendering
void ModelViewer::updateRenderingData()
{
    mRenderer->updateData(mVertices, mNormals, mIndices, mIndicesNo);
}

// Function opens Dialog box
void ModelViewer::openFileDialog()
{
    QString qFileName = QFileDialog::getOpenFileName(this, tr("Open Obj File"), "", tr("obj Files (*.obj);;All Files (*)"));
    if (qFileName.isEmpty())
    {
        QMessageBox::information(this, "Error Opening obj File", "Could not open obj File");
        return;
    }
     std::string fileName = qFileName.toStdString();
     readObjFileData(fileName);
}

// Function to clear the screen
void ModelViewer::clearnScreen()
{
    mRenderer->clear();
}

// Function to enable wireFrameMode
void ModelViewer::wireFramButtonClicked()
{
    mRenderer->setColorMode(2);
    mRenderer->setFlag(false);
}

// Function to set flag for color mode
void ModelViewer::coloredButtonClicked()
{
    mRenderer->setColorMode(1);
    mRenderer->setFlag(true);
}

