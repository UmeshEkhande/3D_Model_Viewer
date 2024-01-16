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
    mPostAttribute           = 0;
    mNormalAttribute         = 0;
    mProjectionMatrixUniform = 0;
    mViewMatrixUniform       = 0;
    mModelMatrixUniform      = 0;
    mZoomFactor              = 1.0f;
    mLightPositionLocation   = 0;
    mNormalMatrixLocation    = 0;
    mLightEnabled            = 0;
    mColorModel              = 1;
    mFlag                    = true;
    mProgram                 = nullptr;

    const QStringList list = { "VertexShader.glsl","FragmentShader.glsl" };
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
    doneCurrent();
    QObject::disconnect(mContextWatchConnection);
}

//Function to modify the rotation angle and pan factor
void OpenGLWindow::mouseMoveEvent(QMouseEvent* event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton)
    {
        QQuaternion rotX = QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, 0.1f * dx);
        QQuaternion rotY = QQuaternion::fromAxisAndAngle(1.0f, 0.0f, 0.0f, 0.1f * dy);

        mRotationAngle = rotX * rotY * mRotationAngle;
        
    }
    else if (event->buttons() & Qt::RightButton)
    {

        mPanTranslationFactor += QVector3D(0.1f * dx, -0.1f * dy, 0.0f);
    }

    lastPos = event->pos();
    update();
}

//Function to modify the zoom factor when mouse wheel is scrolled
void OpenGLWindow::wheelEvent(QWheelEvent* event) 
{
    int delta = event->angleDelta().y();

    if (delta > 0) {

        mZoomFactor *= 1.1f;
    }
    else {
        mZoomFactor /= 1.1f;
    }
    update();
}  

// Function to update the data required for rendering
void OpenGLWindow::updateData(GLfloat* inVert, GLfloat* inNormal, GLuint* inIndices, int inNoOfIndices)
{
    mVertices = inVert;
    mNormals = inNormal;
    mIndices = inIndices;
    mNoOfIndices = inNoOfIndices;
    update();
}

void OpenGLWindow::clear()
{
    mVertices = nullptr;
    mNormals = nullptr;
    mIndices = nullptr;
    mZoomFactor = 1.0f;
    update();
}

void OpenGLWindow::setFlag(bool inVal)
{
    mFlag = inVal;
    update();
}

// Function to check color mode
void OpenGLWindow::setColorMode(int inColorModeValue)
{
    mColorModel = inColorModeValue;
}

// Function to keep watch over shader files
void OpenGLWindow::shaderWatcher()
{
    QString vertexShaderSource = readShaderSource("./Shaders/FragmentShader.glsl");
    QString fragmentShaderSource = readShaderSource("./Shaders/FragmentShader.glsl");

    mProgram->release();
    mProgram->removeAllShaders();

    mProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);

    mProgram->link();
}

// Function to read the shader data
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

// Function that render the data
void OpenGLWindow::paintGL()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    mProjectionMatrix.setToIdentity();
    mViewMatrix.setToIdentity();
    mModelMatrix.setToIdentity();

    mProgram->bind();
    mModelMatrix.setToIdentity();
    mModelMatrix.rotate(mRotationAngle);
    mModelMatrix.translate(mPanTranslationFactor);
    mModelMatrix.scale(mZoomFactor);

    mProjectionMatrix.ortho(-40.0f, 40.0f, -40.0f, 40.0f, -100.0f, 100.0f);

    mProgram->setUniformValue(mProjectionMatrixUniform, mProjectionMatrix);
    mProgram->setUniformValue(mViewMatrixUniform, mViewMatrix);
    mProgram->setUniformValue(mModelMatrixUniform, mModelMatrix);

    mProgram->setUniformValue(mLightEnabled, mColorModel);

    QMatrix3x3 normalMatrix = mModelMatrix.normalMatrix();
    mProgram->setUniformValue(mNormalMatrixLocation, normalMatrix);
    mProgram->setUniformValue(mLightPositionLocation, QVector3D(0, 0, 90));

    glVertexAttribPointer(mPostAttribute, 3, GL_FLOAT, GL_FALSE, 0, mVertices);
    glVertexAttribPointer(mNormalAttribute, 3, GL_FLOAT, GL_FALSE, 0, mNormals);

    glEnableVertexAttribArray(mPostAttribute);
    glEnableVertexAttribArray(mNormalAttribute);

    if (mFlag) 
    {
        glDrawElements(GL_TRIANGLES, mNoOfIndices, GL_UNSIGNED_INT, mIndices);
    }
    else 
    {
        glDrawElements(GL_LINES, mNoOfIndices, GL_UNSIGNED_INT, mIndices);
    }

    mProgram->release();
}

// OpenGL - Function that read the uniform location
void OpenGLWindow::initializeGL() {
    initializeOpenGLFunctions();

    QString vertexShaderSource = readShaderSource("./Shaders/VertexShader.glsl");
    QString fragmentShaderSource = readShaderSource("./Shaders/FragmentShader.glsl");

    setMouseTracking(true);

    mProgram = new QOpenGLShaderProgram(this);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);

    mProgram->link();

    mPostAttribute = mProgram->attributeLocation("posAttr");
    mNormalAttribute = mProgram->attributeLocation("normalAttr");
    mProjectionMatrixUniform = mProgram->uniformLocation("u_ProjMatrix");
    mViewMatrixUniform = mProgram->uniformLocation("u_viewMatrix");
    mModelMatrixUniform = mProgram->uniformLocation("u_modelMatrix");
    mNormalMatrixLocation = mProgram->uniformLocation("normalMatrix");
    mLightPositionLocation = mProgram->uniformLocation("lightPos");
    mLightEnabled = mProgram->uniformLocation("u_lightingEnabled");

}
