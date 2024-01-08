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
#include "Point3D.h"

class QOpenGLTexture;
class QOpenGLShader;
class QOpenGLShaderProgram;
class QOpenGLPaintDevice;

class OpenGLWindow : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    OpenGLWindow(const QColor& background, QMainWindow* parent);
    ~OpenGLWindow();

    void updateData(const QVector<GLfloat>& vertices, const QVector<GLfloat>& normals);
    void mouseMoveEvent(QMouseEvent* event);

    void clear();
    void setFlag(bool inVal);


protected:
    void paintGL() override;
    void initializeGL() override;

private:
    void reset();
    void shaderWatcher();
    QString readShaderSource(QString filePath);
    void wheelEvent(QWheelEvent* event);


signals:
    void shapeUpdate();

private:

    QVector2D mousePressPosition;
    QVector3D rotationAxis;
    qreal angularSpeed = 0;
    QQuaternion rotation;

    bool mAnimating = false;
    QOpenGLContext* mContext = nullptr;
    QOpenGLPaintDevice* mDevice = nullptr;

    QOpenGLShader* mVshader = nullptr;
    QOpenGLShader* mFshader = nullptr;
    QOpenGLShaderProgram* mProgram = nullptr;

    QList<QVector3D> mVertices;
    QList<QVector3D> mNormals;
    QOpenGLBuffer mVbo;
    double mVertexAttr;
    double mNormalAttr;
    double mMatrixUniform;
    QColor mBackground;
    QMetaObject::Connection mContextWatchConnection;

    double xMin, yMin, xMax, yMax, inside, rht, lft, bottom, top;
    double startX, startY, endX, endY;

    GLint m_posAttr = 0;
    GLint m_colAttr = 0;
    GLint m_normals = 0;
    GLint m_matrixUniform_proj = 0;
    GLint m_matrixUniform_view = 0;
    GLint m_matrixUniform_model = 0;

    QQuaternion rotationAngle;
    QPoint lastPos;

    QVector<GLfloat> verticesOfOrignalLine;
    QVector<GLfloat> normalsOriginal;
    std::vector<Point3D> vert;
    QVector<GLfloat> colorOfOrignalLine;

    float zoomFactor = 1.0f;

    GLuint m_ambientColorUniform;
    GLuint m_ambientIntensityUniform;
    QFileSystemWatcher* mShaderWatcher;
    QMatrix4x4 matrix;
    QMatrix4x4 panMatrix;
    QVector2D lastPanPos;

    bool flag = true;

    
};

