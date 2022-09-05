#version 310 es

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec2 aTexCoords;

layout (location = 3) in mat4 aInstanceMatrix;

layout (location = 0) out vec3 Normal;
layout (location = 1) out vec2 TexCoord;
layout (location = 2) out vec3 FragPos;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    gl_Position =  projection * view * aInstanceMatrix * vec4(aPos, 1.0f);

    TexCoord = aTexCoords;

    FragPos = vec3(aInstanceMatrix * vec4(aPos, 0.0));
    Normal = mat3(transpose(inverse(aInstanceMatrix))) * aNorm;
}
