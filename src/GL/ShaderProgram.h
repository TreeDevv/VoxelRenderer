#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class ShaderProgram
{
public:
    ShaderProgram(const char *vertPath, const char *fragPath);
    ~ShaderProgram();

    void use();

    void setVec3(const char *name, float x, float y, float z);
    void setVec3(const char *name, const glm::vec3 &pos);
    void setMat4(const char *name, const glm::mat4 &mat);

private:
    string _getShaderCode(const char *path);

    GLuint _program;
};