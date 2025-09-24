#pragma once

#include "IRenderer.h"
#include "../Platform/IWindow.h"

namespace GameGraphics
{
    class GLRenderer : public IRenderer
    {
    public:
        explicit GLRenderer(GamePlatform::IWindow &win) : _win(win) {}
        bool initialize() override;
        void resize(int w, int h) override;
        void beginFrame() override;
        void draw() override;
        void endFrame() override;

    private:
        GamePlatform::IWindow &_win;
    };
}