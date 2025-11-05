#version 330 core

in vec3 vNormal;
in vec3 vFragPos;
in float vAO;
in vec3 randomColor;

out vec4 FragColor;

uniform vec3 u_LightPos;
uniform vec3 u_LightColor;
uniform vec3 u_ViewPos;

void main()
{   
    vec3 norm = normalize(vNormal);
    vec3 lightDir = normalize(u_LightPos - vFragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * u_LightColor;

    float specularStrength = 0.5;
    vec3 viewDir = normalize(u_ViewPos - vFragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * u_LightColor;

    vec3 color = normalize(randomColor);

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * color;

    float aoFactor = 1.0;

    vec3 result = (ambient + diffuse + specular) * color;
    FragColor = vec4(result * aoFactor, 1.0f);
}