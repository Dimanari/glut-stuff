#version 300 es
precision mediump float;

out vec4 FragColor;  

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
//	vec4 temp = floor(ourColor * RESOLUTION) / RESOLUTION;
//	vec4 tFragColor = vec4((temp.r + ourColor.a),(temp.g + ourColor.a), (temp.b + ourColor.a), 1.0) / 2.0;


	FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 0.3);
}