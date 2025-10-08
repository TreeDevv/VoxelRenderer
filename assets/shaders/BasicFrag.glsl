#version 330 core

in vec3 randomColor;

out vec4 FragColor;

void main()
{
    FragColor = vec4(normalize(randomColor), 1.0f);
}