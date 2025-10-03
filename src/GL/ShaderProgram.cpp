#include "ShaderProgram.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

ShaderProgram::ShaderProgram(const char *vertPath, const char *fragPath)
{
    string vertCode = _getShaderCode(vertPath);
    string fragCode = _getShaderCode(fragPath);

    GLuint vertexShader, fragmentShader;

    int success;
    char infoLog[512];

    // vertex Shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* cVertCode = vertCode.c_str();
    glShaderSource(vertexShader, 1, &cVertCode, NULL);
    glCompileShader(vertexShader);
    // print compile errors if any
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    };

    // similiar for Fragment Shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* cFragCode = fragCode.c_str();
    glShaderSource(fragmentShader, 1, &cFragCode, NULL);
    glCompileShader(fragmentShader);
    // Compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
    }

    // shader Program
    _program = glCreateProgram();
    glAttachShader(_program, vertexShader);
    glAttachShader(_program, fragmentShader);
    glLinkProgram(_program);
    // print linking errors if any
    glGetProgramiv(_program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(_program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << infoLog << std::endl;
    }

    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

ShaderProgram::~ShaderProgram()
{
}

void ShaderProgram::use()
{
    glUseProgram(_program);
}

void ShaderProgram::setVec3(const char* name, float x, float y, float z)
{
    GLint loc = glGetUniformLocation(_program, name);
    if (loc == -1) return;
    glUseProgram(_program);
    glUniform3f(loc, x, y, z);
}

string ShaderProgram::_getShaderCode(const char *path)
{
    string shaderCode;
    ifstream sShaderFile;

    sShaderFile.exceptions(ifstream::failbit || ifstream::badbit);
    try
    {
        sShaderFile.open(path);
        stringstream shaderStream;
        shaderStream << sShaderFile.rdbuf();

        sShaderFile.close();
        shaderCode = shaderStream.str();
    }
    catch (exception e)
    {
        cout << e.what() << endl;
    }

    return shaderCode;
}
