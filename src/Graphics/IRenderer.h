#pragma once

namespace GameGraphics
{
    class IRenderer
    {
    public:
        virtual ~IRenderer() = default;

        virtual bool initialize() = 0;
        virtual void resize(int w, int h) = 0;
        virtual void beginFrame() = 0;
        virtual void draw() = 0; // Eventually pass scene to draw function
        virtual void endFrame() = 0;

    private:
    };
}