#version 330

layout(location = 0) in vec4  inVertexPosition;
layout(location = 1) in vec3  color;

uniform mat4 projViewMatrix;
uniform mat4 modelMatrix;
uniform float dayTime;

out vec3 passColor;

void main(){
    gl_Position = projViewMatrix * modelMatrix * vec4(inVertexPosition.xyz, 1.0);
}