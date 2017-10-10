#version 330

layout(location = 0) in vec3  inVertexPosition;
layout(location = 1) in vec2  inTextureCoord;
layout(location = 2) in vec3  inNormal;

out vec2 passTextureCoord;
out vec3 normal;

uniform mat4 projViewMatrix;
uniform mat4 normalMatrix;

void main()
{
    gl_Position = projViewMatrix * vec4(inVertexPosition, 1.0);

    passTextureCoord    = inTextureCoord;
    normal              = vec3(normalMatrix * vec4(inNormal, 1.0));
}
