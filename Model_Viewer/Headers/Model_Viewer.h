#pragma once

#include <QtWidgets/QMainWindow>
#include <Qvector>
#include "OpenGLWindow.h"
#include "ReadObjFile.h"


class Model_Viewer : public QMainWindow
{
    Q_OBJECT

public:
    Model_Viewer(QWindow* parent = nullptr);
    ~Model_Viewer();

private:
    void setupUi();
    void openFileDialog();
    void clearnScreen();
    void wireFramButtonClicked();
    void ColoredButtonClicked();

private:
    QWidget* mCentralWidget;
    OpenGLWindow* mRenderer;
    QOpenGLWidget* cubeRenderer;

    QVector<GLfloat> ver;
    QVector<GLfloat> nor;

    QPushButton* mpushButton;
    QPushButton* mpushButtonRead;

    QVector<GLfloat>mVertices;
    QVector<GLfloat>mColors;

    std::vector<Point3D> vertices;
    std::vector<Point2D> textureCoords;
    std::vector<Point3D> normals;
    std::vector<Face> faces;

    QVBoxLayout* mMainLayout;
    QTabWidget* mTabWidget;

    QWidget* modelViewTab;
    QHBoxLayout* modelViewLayout;
    QVBoxLayout* settingsLayout;
    QPushButton* clearButton;
    QPushButton* loadStlButton;
    QPushButton* wireFrameButton;
    QPushButton* coloredButton;

    QHBoxLayout* textureLayout;
};
