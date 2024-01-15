#pragma once
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QMainWindow>
#include <QQuaternion>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLVertexArrayObject>
#include "MaterialFileReader.h"
#include "MaterialReader.h"
#include "Point3D.h"

class QOpenGLTexture;
class QOpenGLShader;
class QOpenGLShaderProgram;
class QOpenGLPaintDevice;

class OpenGLWindow : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    OpenGLWindow(const QColor& background, QMainWindow* parent);
    ~OpenGLWindow();

    void updateData(GLfloat* inVert, GLfloat* inNormal, GLuint* inIndices,int inNoOfIndices);

    void clear();
    void setFlag(bool inVal);
    void setColorMode(int inColorModeValue);


protected:
    void paintGL() override;
    void initializeGL() override;

private:
    void reset();
    void shaderWatcher();
    void wheelEvent(QWheelEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    QString readShaderSource(QString filePath);

private:
    QMetaObject::Connection mContextWatchConnection;
    QOpenGLShaderProgram* mProgram;
    QColor mBackground;
   
    GLint mPostAttribute;
    GLint mNormalAttribute;
    GLint mProjectionMatrixUniform;
    GLint mViewMatrixUniform;
    GLint mModelMatrixUniform;

    QMatrix4x4 mProjectionMatrix;
    QMatrix4x4 mViewMatrix;
    QMatrix4x4 mModelMatrix;

    GLfloat* mVertices;
    GLfloat* mNormals;
    GLuint* mIndices;

    QVector3D mPanTranslationFactor;
    QQuaternion mRotationAngle;
    QPoint lastPos;
    QFileSystemWatcher* mShaderWatcher;

    int mLightPositionLocation;
    int mNormalMatrixLocation;
    int mLightEnabled;
    int mColorModel;
    int mNoOfIndices;
    float mZoomFactor;
    bool  mFlag;
};

