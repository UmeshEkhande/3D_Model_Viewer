#include "stdafx.h"
#include "OpenGLWindow.h"
#include <QOpenGLContext>
#include <QOpenGLPaintDevice>
#include <QOpenGLShaderProgram>
#include <QPainter>
#include <tuple>
#include <fstream>
#include <sstream>
#include <iostream>

OpenGLWindow::OpenGLWindow(const QColor& background, QMainWindow* parent) :
    mBackground(background) {
    setParent(parent);
    setMinimumSize(300, 250);

    const QStringList list = { "vShader.glsl","fShader.glsl" };
    mShaderWatcher = new QFileSystemWatcher(list, this);
    connect(mShaderWatcher, &QFileSystemWatcher::fileChanged, this, &OpenGLWindow::shaderWatcher);
}

OpenGLWindow::~OpenGLWindow() {
    reset();
}

void OpenGLWindow::reset() {
    makeCurrent();
    delete mProgram;
    mProgram = nullptr;
    delete mVshader;
    mVshader = nullptr;
    delete mFshader;
    mFshader = nullptr;
    mVbo.destroy();
    doneCurrent();

    QObject::disconnect(mContextWatchConnection);
}

void OpenGLWindow::shaderWatcher()
{
    QString vertexShaderSource = readShaderSource("./Shaders/vShader.glsl");
    QString fragmentShaderSource = readShaderSource("./Shaders/fShader.glsl");

    mProgram->release();
    mProgram->removeAllShaders();

    mProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);

    mProgram->link();
}

QString OpenGLWindow::readShaderSource(QString filePath)
{

    QFile* file = new QFile(filePath);
    if (!file->open(QFile::ReadOnly | QFile::Text))
    {
        std::cerr << "Invalid File !";
        return "Invalid File !";
    }

    QTextStream stream(file);
    QString fileString = stream.readLine();

    while (!stream.atEnd())
    {
        fileString.append(stream.readLine());
    }
    return fileString;
}


void OpenGLWindow::setVectorOfLines(QVector<GLfloat>& vectorOfLines)
{
    verticesOfOrignalLine = vectorOfLines;
}

void OpenGLWindow::setColorOfLines(QVector<GLfloat>& colorOfLines)
{
    colorOfOrignalLine = colorOfLines;
}


void OpenGLWindow::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);

    mProgram->bind();
    QMatrix4x4 matrix;
    matrix.rotate(rotationAngle);
  //  matrix.ortho(-30.0f, 30.0f, -30.0f, 30.0f, 0.1f, 100.0f);
    matrix.ortho(-30.0f * zoomFactor, 30.0f * zoomFactor, -30.0f * zoomFactor, 30.0f * zoomFactor, 0.1f, 100.0f);
    matrix.translate(0, 0, -15);

    mProgram->setUniformValue(m_matrixUniform, matrix);

    GLfloat* verticesData = verticesOfOrignalLine.data();
    GLfloat* colorsData = colorOfOrignalLine.data();

    glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, verticesData);
    glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, colorsData);

    glEnableVertexAttribArray(m_posAttr);
    glEnableVertexAttribArray(m_colAttr);

    glDrawArrays(GL_LINE_LOOP, 0, verticesOfOrignalLine.size() / 3);
}



void OpenGLWindow::mouseMoveEvent(QMouseEvent* event) {
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        QQuaternion rotX = QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, 0.5f * dx);
        QQuaternion rotY = QQuaternion::fromAxisAndAngle(1.0f, 0.0f, 0.0f, 0.5f * dy);

        rotationAngle = rotX * rotY * rotationAngle;

        update();
    }
    lastPos = event->pos();
}

void OpenGLWindow::wheelEvent(QWheelEvent* event) 
{
    int delta = event->angleDelta().y();

    if (delta > 0) {

        zoomFactor *= 1.1f;
    }
    else {

        zoomFactor /= 1.1f;
    }
    update();
}


void OpenGLWindow::updateData(const QVector<GLfloat>& vertices, const QVector<GLfloat>& colors)
{
    verticesOfOrignalLine = vertices;
    colorOfOrignalLine = colors;
    update();
}


void OpenGLWindow::initializeGL() {


    QString vertexShaderSource = readShaderSource("./Shaders/vShader.glsl");
    QString fragmentShaderSource = readShaderSource("./Shaders/fShader.glsl");

    initializeOpenGLFunctions();
    setMouseTracking(true);

    mProgram = new QOpenGLShaderProgram(this);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);

    mProgram->link();

    m_posAttr = mProgram->attributeLocation("posAttr");
    Q_ASSERT(m_posAttr != -1);
    m_colAttr = mProgram->attributeLocation("colAttr");
    Q_ASSERT(m_colAttr != -1);
    m_matrixUniform = mProgram->uniformLocation("matrix");
    Q_ASSERT(m_matrixUniform != -1);


}