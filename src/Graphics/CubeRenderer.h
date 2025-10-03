#pragma once

#include "../GL/VertexArray.h"
#include "../GL/VertexBuffer.h"
#include "../GL/ShaderProgram.h"

#include <glm/glm.hpp>

/*
Class used for rendering cubes outside of chunks. Simply give a location texture and rotation
*/

namespace GameGraphics
{
    class CubeRenderer
    {
        public:
            CubeRenderer();
            ~CubeRenderer();

            void renderCube(const glm::vec3 &position);
        private:

            ShaderProgram _defaultProgram;

            VertexArray _vao;
            VertexBuffer _vbo;
    };
}