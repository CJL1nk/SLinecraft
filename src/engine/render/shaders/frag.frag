#version 330 core

#define MAX_POINT_LIGHTS 64

struct PointLight {
    vec3 position; // no longer necessary when using directional lights.

    vec3 diffuse;

    float strength;

    float constant;
    float linear;
    float quadratic;
};

struct SkyLight {
    vec3 direction;
    vec3 strength;
};

out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture1;
uniform PointLight[MAX_POINT_LIGHTS] lights;
uniform SkyLight skylight;
uniform int numPointLights;
uniform float ambient;
uniform mat4 view;

vec3 calculateSkyLight(vec3 norm)
{
    vec3 skylightDir = normalize(-skylight.direction);

    float diff = max(dot(norm, skylightDir), 0.0);

    vec3 ambientLight = ambient + skylight.strength;
    return diff * skylight.strength + ambientLight;
}

vec3 calculatePointLights(vec3 norm)
{
    vec3 result = vec3(0.0);

    for (int i = 0; i < numPointLights; i++)
    {
        vec3 lightDir = normalize(lights[i].position - FragPos);
        float distance = length(lights[i].position - FragPos);

        float diff = max(dot(norm, lightDir), 0.0);

        float attenuation = 1.0 / (lights[i].constant + lights[i].linear * distance + lights[i].quadratic * distance * distance);

        result += diff * lights[i].diffuse * lights[i].strength * attenuation;
    }

    return result;
}

void main()
{
    vec3 norm = normalize(Normal);

    vec3 lighting = calculateSkyLight(norm) + calculatePointLights(norm);

    if (lighting[0] > 1.5f) { lighting[0] = 1.5f; }
    if (lighting[1] > 1.5f) { lighting[1] = 1.5f; }
    if (lighting[2] > 1.5f) { lighting[2] = 1.5f; }

    FragColor = texture(texture1, TexCoord) * vec4(lighting, 1.0);
}