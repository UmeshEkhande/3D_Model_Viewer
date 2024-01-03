#pragma once

#include <QtWidgets/QMainWindow>
#include <Qvector>
#include "OpenGLWindow.h"


class Model_Viewer : public QMainWindow
{
    Q_OBJECT

public:
    Model_Viewer(QWindow* parent = nullptr);
    ~Model_Viewer();

private:
    void setupUi();

public:
    void readSTL();

private:
    QWidget* mCentralWidget;
    OpenGLWindow* mRenderer;


    QPushButton* mpushButton;
    QPushButton* mpushButtonRead;

    QVector<GLfloat>mVertices;
    QVector<GLfloat>mColors;

};
