#version 300 es

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec2 aTexCoords;

layout (location = 3) in mat4 aInstanceMatrix;


out vec3 Normal;
out vec2 TexCoord;
out vec3 FragPos;
out vec4 FragPosLightSpace;


uniform mat4 projection;
uniform mat4 view;
uniform mat4 lightSpaceMatrix;

void main()
{
    gl_Position =  projection * view * aInstanceMatrix * vec4(aPos, 1.0f);

    TexCoord = aTexCoords;

    FragPos = vec3(aInstanceMatrix * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(aInstanceMatrix))) * aNorm;
    FragPosLightSpace = lightSpaceMatrix * vec4(FragPos, 1.0);
}
