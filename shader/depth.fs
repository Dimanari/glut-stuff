#version 300 es
precision mediump float;
out vec4 FragColor;

in vec3 Normal;
in vec2 TexCoord;
in vec3 FragPos;

uniform float far_plane;
uniform vec3 light_pos;

void main()
{
    float lightDistance = length(FragPos - light_pos);
    lightDistance = lightDistance / far_plane;
    gl_FragDepth = lightDistance;
    FragColor = vec4(lightDistance);
}