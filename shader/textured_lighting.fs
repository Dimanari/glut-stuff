#version 310 es
precision mediump float;

out vec4 FragColor;

layout (location = 0) in vec3 Normal;
layout (location = 1) in vec2 TexCoord;
layout (location = 2) in vec3 FragPos;

uniform vec3 light_pos;
uniform vec3 viewPos;
uniform float ambientStrength;

uniform sampler2D ma_texture;

void main()
{
    float specularStrength = 0.5;
	vec3 lightColor = vec3(1.0);

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light_pos - FragPos);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;
	
	vec3 ambient = ambientStrength * lightColor;

	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
	vec3 specular = specularStrength * spec * lightColor;

	vec3 result = (ambient + diffuse + specular);
	FragColor = texture(ma_texture, TexCoord) * vec4(result, 1.0);
}