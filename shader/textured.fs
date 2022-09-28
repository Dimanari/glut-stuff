#version 300 es
precision mediump float;

out vec4 FragColor;  

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

vec3 hueShift( vec3 color, float hueAdjust )
{
    const vec3  kRGBToYPrime = vec3 (0.299, 0.587, 0.114);
    const vec3  kRGBToI      = vec3 (0.596, -0.275, -0.321);
    const vec3  kRGBToQ      = vec3 (0.212, -0.523, 0.311);

    const vec3  kYIQToR     = vec3 (1.0, 0.956, 0.621);
    const vec3  kYIQToG     = vec3 (1.0, -0.272, -0.647);
    const vec3  kYIQToB     = vec3 (1.0, -1.107, 1.704);

    float   YPrime  = dot (color, kRGBToYPrime);
    float   I       = dot (color, kRGBToI);
    float   Q       = dot (color, kRGBToQ);
    float   hue     = atan (Q, I);
    float   chroma  = sqrt (I * I + Q * Q);

    hue += hueAdjust;

    Q = chroma * sin (hue);
    I = chroma * cos (hue);

    vec3    yIQ   = vec3 (YPrime, I, Q);

    return vec3( dot (yIQ, kYIQToR), dot (yIQ, kYIQToG), dot (yIQ, kYIQToB) );

}

void main()
{
//	vec4 temp = floor(ourColor * RESOLUTION) / RESOLUTION;
//	vec4 tFragColor = vec4((temp.r + ourColor.a),(temp.g + ourColor.a), (temp.b + ourColor.a), 1.0) / 2.0;


	FragColor = vec4(hueShift(vec3(texture(ourTexture, TexCoord)), 3.0), 1.0);

}
