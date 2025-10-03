#pragma once

#include <glad/glad.h>
#include <string>

using namespace std;

class ShaderProgram
{
public:
    ShaderProgram(const char* vertPath, const char* fragPath);
    ~ShaderProgram();

    void use();
    void setVec3(const char* name, float x, float y, float z);
private:
    string _getShaderCode(const char* path);

    GLuint _program;
};