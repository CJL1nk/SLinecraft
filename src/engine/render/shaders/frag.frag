#version 330 core

struct Light {
    vec3 position; // no longer necessary when using directional lights.
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture1;
uniform Light light;

float ambientStrength = 0.15;
float lightStrength = 1.5;

void main()
{
    vec3 lightDir = normalize(-light.direction);
    vec3 norm = normalize(Normal);

    float diff = max(dot(norm, lightDir), 0.0) * lightStrength;

    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (1.0 + 0.09 * distance + 0.032 * (distance * distance));

    float lighting = diff * attenuation + ambientStrength;

    FragColor = texture(texture1, TexCoord) * lighting;
}