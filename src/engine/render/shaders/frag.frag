#version 330 core

struct PointLight {
    vec3 position; // no longer necessary when using directional lights.
    vec3 direction;

    vec3 diffuse;

    float strength;

    float constant;
    float linear;
    float quadratic;
};

out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture1;
uniform PointLight light;
uniform float ambient;
uniform mat4 view;
uniform float skylight;


void main()
{
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);

    float diff = max(dot(norm, lightDir), 0.0) * light.strength;

    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    float lighting = diff * attenuation + ambient + skylight;

    FragColor = texture(texture1, TexCoord) * lighting;
}

float calculatePointLights(PointLight light, vec3 normal, vec3 fragPos)
{
    float lighting = 0.0f;

    return lighting;
}