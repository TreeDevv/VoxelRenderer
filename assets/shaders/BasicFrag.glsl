#version 330 core

in vec3 vNormal;
in vec3 vFragPos;
in vec2 vTexPos;
in float vAO;
in vec3 randomColor;

out vec4 FragColor;

uniform sampler2D u_TextureAtlas;
uniform vec2 u_TextureAtlasSize;

uniform vec3 u_LightPos;
uniform vec3 u_LightColor;
uniform vec3 u_ViewPos;

float map(float value, float inMin, float inMax, float outMin, float outMax) {
    return outMin + (value - inMin) * (outMax - outMin) / (inMax - inMin);
}


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

    vec2 normalizedTexCoord = vTexPos / u_TextureAtlasSize;
    vec4 colorVec4 = texture(u_TextureAtlas, normalizedTexCoord);
    vec3 color = vec3(colorVec4.x, colorVec4.y, colorVec4.z);

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * color;

    float aoFactor = 1.0;

    vec3 result = (ambient + diffuse + specular) * color;
    FragColor = vec4(result * aoFactor, 1.0); // colorVec4; //vec4(result * aoFactor, 1.0f);
}
