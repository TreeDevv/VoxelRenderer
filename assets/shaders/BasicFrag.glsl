#version 330 core

in vec2 vColor;

out vec4 FragColor;

void main()
{
    FragColor = vec4(vColor.x, vColor.y, 0.5f, 1.0f);
}