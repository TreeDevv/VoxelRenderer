#include "Input.h"

using namespace GamePlatform;

void Input::_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    Key platformKey = toKey(key);
    if (action == GLFW_PRESS)
    {
        for (auto &cb : _pressedCbs)
        {
            cb(platformKey);
        }

        _pressedKeys[platformKey] = true;
    }
    else if (action == GLFW_RELEASE)
    {
        for (auto &cb : _releasedCbs)
        {
            cb(platformKey);
        }

        _pressedKeys[platformKey] = false;
    }
}

GamePlatform::Input::Input(void *handle)
{
    glfwSetKeyCallback((GLFWwindow *)handle, _key_callback);
}

bool GamePlatform::Input::isKeyDown(Key key)
{
    if (_pressedKeys.contains(key) && _pressedKeys.at(key) == true)
    {
        return true;
    }

    return false;
}

void GamePlatform::Input::onKeyPressed(KeyCallback cb)
{
    _pressedCbs.push_back(cb);
}

void GamePlatform::Input::onKeyReleased(KeyCallback cb)
{
    _releasedCbs.push_back(cb);
}
