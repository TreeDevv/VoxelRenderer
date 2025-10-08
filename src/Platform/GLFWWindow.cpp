#include "GLFWWindow.h"
#define GLFW_INCLUDE_NONE // prevent glfw including opengl headers. Glad takes care of this
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cassert>

static void *s_thisFrom(GLFWwindow *w)
{
    return glfwGetWindowUserPointer(w);
}

GamePlatform::GLFWWindow::GLFWWindow() = default;

GamePlatform::GLFWWindow::~GLFWWindow()
{
    if (_win)
    {
        glfwDestroyWindow(_win);
        _win = nullptr;
    }
    glfwTerminate();
}

bool GamePlatform::GLFWWindow::create(const WindowDesc &desc)
{
    if (!glfwInit())
        return false;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    _win = glfwCreateWindow(desc.width, desc.height, desc.title, nullptr, nullptr);
    if (!_win)
        return false;

    glfwMakeContextCurrent(_win);
    glfwSwapInterval(desc.vsync ? 1 : 0);

    // Lock mouse to window
    glfwSetInputMode(_win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Load GL
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        return false;

    glfwSetWindowUserPointer(_win, this);
    glfwSetFramebufferSizeCallback(_win, [](GLFWwindow *w, int width, int height)
                                   { 
        auto *self = static_cast<GLFWWindow *>(s_thisFrom(w)); 
        if (self->_onResize) self->_onResize(width, height); 
        glViewport(0, 0, width, height);
    });
    glfwSetWindowCloseCallback(_win, [](GLFWwindow *w)
                               { 
        auto *self = static_cast<GLFWWindow *>(s_thisFrom(w)); 
        if (self->_onClose) self->_onClose(); });

    // Set opengl state
    glEnable(GL_DEPTH_TEST);

    int fbw, fbh;
    glfwGetFramebufferSize(_win, &fbw, &fbh);

    glViewport(0, 0, fbw, fbh);

    return true;
}

void GamePlatform::GLFWWindow::pollEvents()
{
    glfwPollEvents();
}

void GamePlatform::GLFWWindow::swapBuffers()
{
    glfwSwapBuffers(_win);
}

bool GamePlatform::GLFWWindow::shouldClose() const
{
    return glfwWindowShouldClose(_win);
}

void GamePlatform::GLFWWindow::setVsync(bool enabled)
{
    glfwSwapInterval(enabled ? 1 : 0);
}

void GamePlatform::GLFWWindow::setResizeCallback(ResizeCallback cb)
{
    _onResize = std::move(cb);
}

void GamePlatform::GLFWWindow::setCloseCallback(CloseCallback cb)
{
    _onClose = std::move(cb);
}

void GamePlatform::GLFWWindow::getFrameBufferSize(int &w, int &h) const
{
    glfwGetFramebufferSize(_win, &w, &h);
}

void *GamePlatform::GLFWWindow::nativeHandle() const
{
    return (void *)_win;
}
