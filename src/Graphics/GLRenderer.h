#pragma once

#include "IRenderer.h"

namespace GameGraphics
{
    class IWindow;

    class GLRenderer : IRenderer
    {
    public:
        explicit GLRenderer(IWindow &win) : _win(win) {}
        bool initialize() override;
        void resize(int w, int h) override;
        void beginFrame() override;
        void draw() override;
        void endFrame() override;

    private:
        IWindow &_win;
    };
}