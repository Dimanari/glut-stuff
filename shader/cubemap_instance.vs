#version 300 es
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in mat4 aInstanceMatrix;

out vec4 FragPos; // FragPos from GS (output per emitvertex)

uniform mat4 projection;
uniform mat4 view;

void main()
{
    gl_Position =  projection * view * aInstanceMatrix * vec4(aPos, 1.0f);
	FragPos = aInstanceMatrix * vec4(aPos, 1.0);
}
