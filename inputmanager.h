#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#include <QPoint>
#include <QCursor>

class InputManager
{
public:
    //Setters
    static void setKeyPressed(Qt::Key key, bool isPressed);
    static void setButtonPressed(Qt::MouseButton button, bool isPressed);

    //Getters
    static bool isKeyPressed(Qt::Key key);
    static bool isButtonPressed(Qt::MouseButton button);
    static QPoint getMousePosition();
    static QPoint getMouseDelta();
private:
    static void update();
    static QPoint mouseCurrPos;
    static QPoint mousePrevPos;
    static std::vector<Qt::Key> pressedKeys;
    static std::vector<Qt::MouseButton> pressedButtons;

    friend class OpenGLWidget;
};

/*******************************************************************************
 * Inline Implementation
 ******************************************************************************/
//Getters
inline QPoint InputManager::getMousePosition() { return QCursor::pos(); }
inline QPoint InputManager::getMouseDelta(){ return mouseCurrPos-mousePrevPos; }

#endif // INPUTMANAGER_H
