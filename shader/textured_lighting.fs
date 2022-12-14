#version 300 es
precision mediump float;

out vec4 FragColor;

in vec3 Normal;
in vec2 TexCoord;
in vec3 FragPos;

uniform vec3 light_pos;
uniform vec3 viewPos;
uniform float ambientStrength;

uniform sampler2D ma_texture;
uniform sampler2D shadowMap;

float ShadowCalculation(vec4 fragPosLightSpace, vec3 lightDir)
{
	// perform perspective divide
	vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
	// transform to [0,1] range
	projCoords = projCoords * 0.5 + 0.5;

	// get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
	float closestDepth = texture(shadowMap, projCoords.xy).r;

	
	// get depth of current fragment from light's perspective
	float currentDepth = projCoords.z;
	// check whether current frag pos is in shadow
	
	float bias = max(0.05 * (1.0 - dot(Normal, lightDir)), 0.005) / fragPosLightSpace.w;
	float shadow = step(closestDepth, currentDepth - bias) * step(projCoords.z, 1.0);

	return shadow;
}

float ShadowCalculation2(vec4 fragPosLightSpace, vec3 lightDir)
{
	// perform perspective divide
	vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
	// transform to [0,1] range
	projCoords = projCoords * 0.5 + 0.5;

	// get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
	float closestDepth = texture(shadowMap, projCoords.xy).r; 
	// get depth of current fragment from light's perspective
	float currentDepth = projCoords.z;
	// check whether current frag pos is in shadow

	float shadow = 0.0;
	float bias = max(0.05 * (1.0 - dot(Normal, lightDir)), 0.005) / fragPosLightSpace.w;
	vec2 texelSize = 1.0 / vec2(textureSize(shadowMap, 0));
	for(int x = -1; x <= 1; ++x)
	{
		for(int y = -1; y <= 1; ++y)
		{
			float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
			shadow += step(pcfDepth, currentDepth - bias);       
		}    
	}
	shadow = (shadow / 9.0) * step(projCoords.z, 1.0);
	return shadow;
}

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

	float shadow = 0.0; //ShadowCalculation2(FragPosLightSpace, lightDir);       
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular));

	vec3 result = lighting;
	FragColor = texture(ma_texture, TexCoord) * vec4(result, 1.0);
}