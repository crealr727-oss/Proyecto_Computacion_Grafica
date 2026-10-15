#version 330 core

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
out vec4 color;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;
uniform sampler2D texture_diffuse1;
uniform int hasTexture;
uniform int enableOutline; // 0: normal, 1: contorno suave silueta, 2: pase exterior plano
uniform vec3 outlineColor;

void main()
{
    // Modo 2: pase exterior de contorno (inverted hull)
    if (enableOutline == 2)
    {
        color = vec4(outlineColor, 1.0f);
        return;
    }

    // Color base: textura (o blanco si la malla no tiene textura)
    vec4 texColor = (hasTexture == 1) ? texture(texture_diffuse1, TexCoords) : vec4(1.0f);
    
    // Descartar fragmentos transparentes (hojas y flores de árboles)
    if (hasTexture == 1 && texColor.a < 0.25f)
        discard;

    vec3 base = texColor.rgb;

    // Ambiental
    vec3 ambient = light.ambient * material.ambient * base;

    // Difusa
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = light.diffuse * diff * material.diffuse * base;

    // Especular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
    vec3 specular = light.specular * spec * material.specular;

    vec3 finalColor = ambient + diffuse + specular;

    // Modo 1: acabado de contorno en bordes (rim/silhouette edge enhancement)
    if (enableOutline == 1)
    {
        float edge = abs(dot(norm, viewDir));
        if (edge < 0.28f)
        {
            float t = edge / 0.28f;
            vec3 edgeCol = (length(outlineColor) > 0.01f) ? outlineColor : vec3(0.06f, 0.06f, 0.08f);
            finalColor = mix(edgeCol, finalColor, t * t);
        }
    }

    color = vec4(finalColor, texColor.a);
}
