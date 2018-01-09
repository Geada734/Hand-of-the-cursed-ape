#version 330

in vec3 VertexPosition;
in vec3 VertexColor;
in vec3 VertexNormal;
in vec2 VertexTexCoord;

uniform mat4 LightVPMatrix;
uniform mat4 mvpMatrix;
uniform mat4 ModelMatrix;

out vec3 InterpolatedColor;
out vec3 interpolatedNormal;
out vec2 InterpolatedTexCoord;
out vec3 pos;
out vec4 PixelPositionLightSpace;


void main(){
	mat3 NormalMatrix = transpose(inverse(mat3(ModelMatrix)));
	pos = vec3(ModelMatrix * vec4(VertexPosition, 1.0f));
	PixelPositionLightSpace=LightVPMatrix*vec4(pos, 1.0);
	InterpolatedColor = VertexColor;
	gl_Position = mvpMatrix * vec4(VertexPosition, 1.0f);
	interpolatedNormal =  NormalMatrix * VertexNormal;
	InterpolatedTexCoord = VertexTexCoord;
}