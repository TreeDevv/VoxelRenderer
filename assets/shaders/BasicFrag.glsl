#version 330 core

in float vAO;
in vec3 randomColor;

out vec4 FragColor;

void main()
{
    float aoFactor = (1.0 - vAO) * 0.8;
    FragColor = vec4(normalize(randomColor) * vAO, 1.0f);
}