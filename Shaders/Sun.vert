#version 330

layout(location = 0) in vec3  inVertexPosition;
layout(location = 1) in vec2  inTextureCoord;

uniform mat4 projViewMatrix;
uniform mat4 modelMatrix;
uniform float dayTime;

out vec2 passTextureCoord;

mat4 rotationX( in float angle ) {
	return mat4(	1.0,		0,			0,			0,
			 		0, 	cos(angle),	-sin(angle),		0,
					0, 	sin(angle),	 cos(angle),		0,
					0, 			0,			  0, 		1);
}

void main(){
    gl_Position = projViewMatrix * modelMatrix * rotationX(dayTime) * vec4(inVertexPosition, 1.0);

    passTextureCoord = inTextureCoord;
}