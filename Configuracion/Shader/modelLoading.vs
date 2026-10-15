#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in ivec4 boneIds;
layout (location = 4) in vec4 weights;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 bones[55];

void main()
{
    mat4 skin = mat4(0.0f);
    float totalWeight = weights.x + weights.y + weights.z + weights.w;
    if (totalWeight > 0.0f)
    {
        skin += bones[boneIds.x] * weights.x;
        skin += bones[boneIds.y] * weights.y;
        skin += bones[boneIds.z] * weights.z;
        skin += bones[boneIds.w] * weights.w;
        skin /= totalWeight;
    }
    else
    {
        skin = mat4(1.0f);
    }

    vec4 skinnedPosition = skin * vec4(position, 1.0f);
    gl_Position = projection * view * model * skinnedPosition;
    FragPos = vec3(model * skinnedPosition);
    Normal = mat3(transpose(inverse(model * skin))) * normal;
    TexCoords = texCoords;
}
