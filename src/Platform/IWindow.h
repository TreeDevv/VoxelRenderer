#pragma once

#include <functional>

namespace GamePlatform
{
    struct WindowDesc
    {
        int width = 1280;
        int height = 720;
        const char *title = "Minecraft";
        bool vsync = true;
    };

    class IWindow
    {
    public:
        using ResizeCallback = std::function<void(int, int)>;
        using CloseCallback = std::function<void()>;

        virtual ~IWindow() = default;
        virtual bool create(const WindowDesc &desc) = 0;
        virtual void pollEvents() = 0;
        virtual void swapBuffers() = 0;
        virtual bool shouldClose() const = 0;
        virtual void setVsync(bool enabled) = 0;
        virtual void setResizeCallback(ResizeCallback cb) = 0;
        virtual void setCloseCallback(CloseCallback cb) = 0;
        virtual void getFrameBufferSize(int &w, int &h) const = 0;
        // Returns a pointer to native window handle for platform independance
        virtual void *nativeHandle() const = 0;
    };
}