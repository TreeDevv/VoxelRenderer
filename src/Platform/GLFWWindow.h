#pragma once

#include "IWindow.h"
#define GLFW_INCLUDE_NONE // prevent glfw including opengl headers. Glad takes care of this
#include <GLFW/glfw3.h>

namespace GamePlatform
{

    class GLFWWindow : IWindow
    {
    public:
        GLFWWindow();
        ~GLFWWindow() override;

        bool create(const WindowDesc &desc) override;
        void pollEvents() override;
        void swapBuffers() override;
        bool shouldClose() const override;
        void setVsync(bool enabled) override;
        void setResizeCallback(ResizeCallback cb) override;
        void setCloseCallback(CloseCallback cb) override;
        void getFrameBufferSize(int &w, int &h) const override;
        // Returns a pointer to native window handle for platform independance
        void *nativeHandle() const override;

    private:
        GLFWwindow *_win = nullptr;
        ResizeCallback _onResize;
        CloseCallback _onClose;
    };
}