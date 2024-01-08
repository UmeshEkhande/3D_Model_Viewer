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

OpenGLWindow::OpenGLWindow(const QColor& background, QMainWindow* parent) :mBackground(background) 
{
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


void OpenGLWindow::updateData(const QVector<GLfloat>& vertices, const QVector<GLfloat>& normals)
{
    verticesOfOrignalLine = vertices;
    normalsOriginal = normals;
    update();
}

void OpenGLWindow::clear()
{
    verticesOfOrignalLine.clear();
    normalsOriginal.clear();
    update();
}

void OpenGLWindow::setFlag(bool inVal)
{
    flag = inVal;
    update();
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

void OpenGLWindow::paintGL() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    mProgram->bind();
    QMatrix4x4 matrix_proj;
    QMatrix4x4 matrix_view;
    QMatrix4x4 matrix_model;
    matrix_model.rotate(rotationAngle);
    matrix_proj.ortho(-30.0f * zoomFactor, 30.0f * zoomFactor, -30.0f * zoomFactor, 30.0f * zoomFactor, 0.1f, 100.0f);
    matrix_view.translate(0, 0, -15);

    mProgram->setUniformValue(m_matrixUniform_proj, matrix_proj);
    mProgram->setUniformValue(m_matrixUniform_view, matrix_view);
    mProgram->setUniformValue(m_matrixUniform_model, matrix_model);

    GLfloat* verticesData = verticesOfOrignalLine.data();
    GLfloat* normalData = normalsOriginal.data();

    glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, verticesData);
    glVertexAttribPointer(m_normals, 3, GL_FLOAT, GL_FALSE, 0, normalData);

    glEnableVertexAttribArray(m_posAttr);
    glEnableVertexAttribArray(m_normals);

    if (flag) {
        glDrawArrays(GL_TRIANGLES, 0, verticesOfOrignalLine.size() / 3);
    }
    else {
        glDrawArrays(GL_LINE_LOOP, 0, verticesOfOrignalLine.size() / 3);
    }
}

void OpenGLWindow::initializeGL() {
    initializeOpenGLFunctions();

    QString vertexShaderSource = readShaderSource("./Shaders/vShader.glsl");
    QString fragmentShaderSource = readShaderSource("./Shaders/fShader.glsl");

    setMouseTracking(true);

    mProgram = new QOpenGLShaderProgram(this);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);

    mProgram->link();

    m_posAttr = mProgram->attributeLocation("posAttr");
    m_normals = mProgram->attributeLocation("normalAttr"); 
    m_matrixUniform_proj = mProgram->uniformLocation("u_ProjMatrix");
    m_matrixUniform_view = mProgram->uniformLocation("u_viewMatrix");
    m_matrixUniform_model = mProgram->uniformLocation("u_modelMatrix");
}