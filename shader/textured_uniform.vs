#version 300 es

in vec3 aPos;   // the position variable has attribute position 0
in vec2 aTexture; // the texture variable has attribute position 2
  
out vec3 ourColor;
out vec2 TexCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0f);

    ourColor = vec3(1.0); // set ourColor to the input color we got from the vertex data
    TexCoord = aTexture;
}