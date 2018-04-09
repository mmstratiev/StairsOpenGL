#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H
#include <QtWidgets/QOpenGLWidget>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLBuffer>
#include <QtGui/QOpenGLVertexArrayObject>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QMatrix4x4>
#include <QMouseEvent>

#include "camera3d.h"
#include "vertex.h"
#include "drawableglinterface.h"
#include "stairs.h"
#include "inputmanager.h"

class OpenGLWidget : public QOpenGLWidget,
                     protected QOpenGLFunctions
{
Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = nullptr);
    ~OpenGLWidget();

    //OpenGL methods
    void initializeGL() Q_DECL_OVERRIDE;
    void resizeGL(int width, int height);
    void paintGL() Q_DECL_OVERRIDE;

    void teardownGL();
    void refresh();
    void resetCamera();

    //Setters
    void setObjectToDraw(DrawableGLInterface *objectToDraw);

    //Events
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
protected slots:
    void update();
private:
    DrawableGLInterface *objectToDraw;
    std::vector<Vertex> *initializeVertex();

    GLuint vertexLocation;
    GLuint colorLocation;
    GLuint matrixLocation;

    QOpenGLBuffer m_vertex;
    QOpenGLVertexArrayObject m_object;
    QOpenGLShaderProgram* m_program;

    int u_modelToWorld;
    int u_worldToView;
    QMatrix4x4 m_projection;
    Camera3D m_camera;
};

/*******************************************************************************
 * Inline Implementation
 ******************************************************************************/

//Setters
inline void OpenGLWidget::setObjectToDraw(DrawableGLInterface *objectToDraw) { this->objectToDraw = objectToDraw; }

//Events
inline void OpenGLWidget::mousePressEvent(QMouseEvent *event) { InputManager::setButtonPressed(event->button(), true); }
inline void OpenGLWidget::mouseReleaseEvent(QMouseEvent *event) { InputManager::setButtonPressed(event->button(), false); }
inline void OpenGLWidget::keyPressEvent(QKeyEvent *event) { InputManager::setKeyPressed((Qt::Key)event->key(), true); }
inline void OpenGLWidget::keyReleaseEvent(QKeyEvent *event) { InputManager::setKeyPressed((Qt::Key)event->key(), false); }

#endif // OPENGLWIDGET_H
