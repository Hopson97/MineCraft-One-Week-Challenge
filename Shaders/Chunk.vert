#version 330

layout(location = 0) in vec3  inVertexPosition;
layout(location = 1) in vec2  inTextureCoord;
layout(location = 2) in float inCardinalLight;
layout(location = 3) in vec3  inNormal;

out vec2    passTextureCoord;
out float   passCardinalLight;
out vec3    passNormal;

uniform mat4 projViewMatrix;
uniform mat4 normalMatrix;

void main()
{
    gl_Position = projViewMatrix * vec4(inVertexPosition, 1.0);

    passTextureCoord    = inTextureCoord;
    passNormal          = vec3(normalMatrix * vec4(inNormal, 1.0));
    passCardinalLight   = inCardinalLight;
}
