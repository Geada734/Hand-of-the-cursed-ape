#version 330

in vec3 InterpolatedColor;
in vec3 pos;
in vec2 InterpolatedTexCoord;
in vec4 PixelPositionLightSpace;
in vec3 interpolatedNormal;

uniform float luzX;
uniform float luzY;
uniform float luzZ;
uniform sampler2D DiffuseTexture;
uniform sampler2D ShadowMap;
uniform float camaraX;
uniform float camaraY;
uniform float camaraZ;

out vec4 FragColor;

float IsPixelOccluded(vec4 fragPosLightSpace){
	vec3 projCoords=(fragPosLightSpace.xyz/fragPosLightSpace.w)*.5f + .5f;
	float closestDepth=texture2D(ShadowMap, projCoords.xy).r;
	float currentDepth=projCoords.z;
	float shadow=currentDepth-.005f > closestDepth ? 1.0f : 0.0f;
	return shadow;
}

void main()
{
	float shadow=IsPixelOccluded(PixelPositionLightSpace);
	vec3 luz = vec3(luzX,luzY,luzZ);
	vec3 camara = vec3(camaraX,camaraY,camaraZ);
	vec3 l =  normalize(luz-pos);
	vec3 v =  normalize(camara-pos);
	vec3 r = reflect(-l,interpolatedNormal);
	vec3 lightColor =vec3(1.0f,1.0f,1.0f);
	vec3 ambient = 0.1f*lightColor;
	vec3 diffuse = clamp(dot(interpolatedNormal,l),0,1)*lightColor;
	vec3 specular = pow(clamp(dot(v,r),0,1), 32)*lightColor*.5f;
	vec3 phong = (ambient + (1.0f-shadow)*(diffuse + specular));
	FragColor = vec4(phong, 1)* texture2D(DiffuseTexture, InterpolatedTexCoord);	
}