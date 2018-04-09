#include <QDebug>
#include <vector>

#include "openglwidget.h"
OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    setFocusPolicy(Qt::StrongFocus);
    m_camera.setTranslation(-2.0f, 5.0f, 15.0f);
}

OpenGLWidget::~OpenGLWidget()
{
    this->teardownGL();
}

void OpenGLWidget::initializeGL()
{
    //Builds the vertexes of the ObjectToDraw based on it's given parameters
    objectToDraw->buildVertexes();
    //Gets the underlying vector<Vertex> array
    const Vertex *sg_vertexes = objectToDraw->getVertexesArray();

    initializeOpenGLFunctions();
    //Starts the update "loop"
    connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));

    //OpenGL
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    {
        //Setting up the OpenGLShaderProgram
        m_program = new QOpenGLShaderProgram(this);
        m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/simple.vert");
        m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/simple.frag");
        m_program->link();
        m_program->bind();

        // Cache Uniform Locations
        u_modelToWorld = m_program->uniformLocation("modelToWorld");
        u_worldToView = m_program->uniformLocation("worldToView");

        //Setting up the OpenGL buffer(VBO)
        m_vertex.create();
        m_vertex.bind();
        m_vertex.setUsagePattern(QOpenGLBuffer::StaticDraw);
        //Allocates for the vertexes array
        m_vertex.allocate(sg_vertexes, sizeof(Vertex)*objectToDraw->getVertexes().size());

        //Setting up OpenGL VertexArrayObject
        m_object.create();
        m_object.bind();
        m_program->enableAttributeArray(0);
        m_program->enableAttributeArray(1);
        m_program->setAttributeBuffer(0, GL_FLOAT, Vertex::positionOffset(), Vertex::PositionTupleSize, Vertex::stride());
        m_program->setAttributeBuffer(1, GL_FLOAT, Vertex::colorOffset(), Vertex::ColorTupleSize, Vertex::stride());

        //Releasing
        m_object.release();
        m_vertex.release();
        m_program->release();
    }
}

void OpenGLWidget::resizeGL(int width, int height)
{
    m_projection.setToIdentity();
    m_projection.perspective(45.0f, width / float(height), 0.01f, 1000.0f);
}

void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Sets view matrix
    m_program->bind();
    m_program->setUniformValue(u_worldToView, m_projection);
    {
        m_object.bind();
        m_program->setUniformValue(u_modelToWorld, m_camera.toMatrix().inverted(NULL));

        //Draws the objectToDraw
        glDrawArrays(GL_TRIANGLES, 0, objectToDraw->getVertexes().size());
        m_object.release();
    }
    m_program->release();
}

void OpenGLWidget::teardownGL()
{
    makeCurrent();
    //Stops the update() "loop"
    disconnect(this, SIGNAL(frameSwapped()), this, SLOT(update()));

    //destroys and deletes VBO, VertexArrayObject and ShaderProgram
    m_object.destroy();
    m_vertex.destroy();
    delete m_program;
}

void OpenGLWidget::refresh()
{
    //reinitializes the OpenGL window, updating the drawed object with new values
    this->teardownGL();
    this->initializeGL();
}

void OpenGLWidget::resetCamera()
{
    //resets the camera to starting position
    m_camera.setTranslation(-2.0f, 5.0f, 15.0f);
    m_camera.setRotation(0.0f, 0.0f, 0.0f, 0.0f);
}

void OpenGLWidget::update()
{
    //updates the InputManager(getting new mouse pos value)
    InputManager::update();

    //speed of camera movement and rotation
    static const float transSpeed = 0.5f;
    static const float rotSpeed   = 0.5f;

    //Check if right mouse button is pressed and if it is, changes the m_camera object by mouse delta
    if(InputManager::isButtonPressed(Qt::RightButton)){
        m_camera.rotate(-rotSpeed*InputManager::getMouseDelta().x(), Camera3D::LocalUp);
        m_camera.rotate(-rotSpeed*InputManager::getMouseDelta().y(), m_camera.right());
    }

    //Creates a 3D Vector and adds/removes from it based on what key is pressed
    QVector3D translation;
    if(InputManager::isKeyPressed(Qt::Key_W)){
        translation+= m_camera.forward();
    }
    if(InputManager::isKeyPressed(Qt::Key_S)){
        translation-= m_camera.forward();
    }
    if(InputManager::isKeyPressed(Qt::Key_A)){
        translation -= m_camera.right();
    }
    if(InputManager::isKeyPressed(Qt::Key_D)){
        translation += m_camera.right();
    }
    //translates the camera by the movement speed * above created translation(0 if no key is pressed)
    m_camera.translate(transSpeed*translation);

    //Schedule a redraw
    QOpenGLWidget::update();
}

