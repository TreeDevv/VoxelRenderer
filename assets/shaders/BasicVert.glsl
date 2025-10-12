#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in float aAO;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out float vAO;
out vec3 randomColor;

void main()
{
    gl_Position = u_Projection * u_View * u_Model * vec4(aPos, 1.0);
    randomColor = vec3(aPos);
    vAO = aAO;
}