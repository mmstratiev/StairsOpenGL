#include "inputmanager.h"
#include <algorithm>

std::vector<Qt::Key> InputManager::pressedKeys;
std::vector<Qt::MouseButton> InputManager::pressedButtons;
QPoint InputManager::mouseCurrPos;
QPoint InputManager::mousePrevPos;

void InputManager::setKeyPressed(Qt::Key key, bool isPressed)
{
    auto it = std::find(pressedKeys.begin(), pressedKeys.end(), key);
    if(isPressed){
        if(it == pressedKeys.end()){
            pressedKeys.push_back(key);
        }
    }
    else{
        if(it != pressedKeys.end()){
            pressedKeys.erase(it);
        }
    }
}

void InputManager::setButtonPressed(Qt::MouseButton button, bool isPressed)
{
    auto it = std::find(pressedButtons.begin(), pressedButtons.end(), button);

    if(isPressed){
        if(it == pressedButtons.end()){
            pressedButtons.push_back(button);
        }
    }
    else{
        if(it != pressedButtons.end()){
            pressedButtons.erase(it);
        }
    }
}

bool InputManager::isKeyPressed(Qt::Key key)
{
    return std::find(pressedKeys.begin(), pressedKeys.end(), key) != pressedKeys.end();
}

bool InputManager::isButtonPressed(Qt::MouseButton button)
{
    return std::find(pressedButtons.begin(), pressedButtons.end(), button) != pressedButtons.end();
}

void InputManager::update()
{
    mousePrevPos = mouseCurrPos;
    mouseCurrPos = QCursor::pos();
}
