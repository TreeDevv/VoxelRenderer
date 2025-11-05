#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in float aAO;
layout (location = 2) in vec3 aNormal;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out float vAO;
out vec3 vNormal;
out vec3 vFragPos;
out vec3 randomColor;

void main()
{
    gl_Position = u_Projection * u_View * u_Model * vec4(aPos, 1.0);
    randomColor = vec3(0.4, 0.3, 0.4);
    vFragPos = vec3(u_Model * vec4(aPos, 1.0));
    vAO = aAO;
    vNormal = mat3(transpose(inverse(u_Model))) * aNormal;
}