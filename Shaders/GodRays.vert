#version 330

layout(location = 0) in vec3  inVertexPosition;
layout(location = 1) in vec2  inTextureCoord;

uniform mat4 projViewMatrix;
uniform mat4 modelMatrix;
uniform float time;

out vec2 passTextureCoord;
out vec2 screenSpaceSun;

uniform vec2 resolution;
uniform mat4 CPVM;
uniform mat4 sunMat;

mat4 rotationX( in float angle ) {
	return mat4(	1.0,		0,			0,			0,
			 		0, 	cos(angle),	-sin(angle),		0,
					0, 	sin(angle),	 cos(angle),		0,
					0, 			0,			  0, 		1);
}

vec2 getSunPos(){
    vec4 spos = rotationX(time) * vec4(0.0, 0.0, 400.0 ,1.0); //Sun Pos
    spos *= sunMat; // Move to proper sun space.

    vec4 clipPos = CPVM * vec4(spos.xyz, 1.0); //Discard w

    if(clipPos.w <= 0){
        return vec2(-1, -1);
    }

    vec3 ndc = clipPos.xyz / clipPos.w;

    vec2 windowPos = ((ndc.xy + 1.0) / 2.0) * resolution;
    return windowPos;
}

void main(){
    gl_Position = projViewMatrix * modelMatrix * vec4(inVertexPosition, 1.0);
    screenSpaceSun = getSunPos();


    passTextureCoord = inTextureCoord;
}