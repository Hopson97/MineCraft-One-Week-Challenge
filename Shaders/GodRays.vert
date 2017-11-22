#version 330

layout(location = 0) in vec3  inVertexPosition;
layout(location = 1) in vec2  inTextureCoord;

uniform mat4 projViewMatrix;
uniform mat4 modelMatrix;
uniform float time;

out vec2 passTextureCoord;

void main(){
    gl_Position = projViewMatrix * modelMatrix * vec4(inVertexPosition, 1.0);

    passTextureCoord = inTextureCoord;
}