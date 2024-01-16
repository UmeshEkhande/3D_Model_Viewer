#pragma once

#include <QtWidgets/QMainWindow>
#include <Qvector>
#include "MaterialFileReader.h"
#include "MaterialReader.h"
#include "ObjFileReader.h"
#include <QGroupBox>
#include "OpenGLWindow.h"
#include "ReadObjFile.h"


class ModelViewer : public QMainWindow
{
    Q_OBJECT

public:
    ModelViewer(QWindow* parent = nullptr);
    ~ModelViewer();

private:
    void setupUi();
    void openFileDialog();
    void clearnScreen();
    void wireFramButtonClicked();
    void coloredButtonClicked();
    void createMenus();
    void readObjFileData(std::string inFileName);
    void updateRenderingData();

private:
    QWidget* mCentralWidget;
    QWidget* settingsLayoutContainer;
    QWidget* ButtonContainer;
    QWidget* modelViewTab;

    OpenGLWindow* mRenderer;
    QOpenGLWidget* cubeRenderer;

    QTabWidget* mTabWidget;

    std::vector<Point3D> vertices;
    std::vector<Point2D> textureCoords;
    std::vector<Point3D> normals;
    std::vector<Face> faces;

    QHBoxLayout* textureLayout;
    QHBoxLayout* modelViewLayout;
    QVBoxLayout* settingsLayout;
    QVBoxLayout* mMainLayout;

    QPushButton* clearButton;
    QPushButton* loadStlButton;
    QPushButton* wireFrameButton;
    QPushButton* coloredButton;
    QPushButton* mpushButton;
    QPushButton* mpushButtonRead;

    QAction* mOpenActionBtn;
    QMenu* fileMenu;

    int mVerticesNo;
    int mNormalsNo;
    int mIndicesNo;

    GLfloat* mVertices;
    GLfloat* mNormals;
    GLuint* mIndices;

    std::vector<MaterialReader::shape_t> shapes;
    std::vector<MaterialReader::material_t> materials;
};
