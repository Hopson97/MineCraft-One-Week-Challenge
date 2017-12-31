#version 330

layout(location = 0) in vec3  inVertexPosition;
layout(location = 1) in vec2  inTextureCoord;
out vec2 passTextureCoord;

uniform mat4 projViewMatrix;
uniform mat4 normalMatrix;
uniform mat4 modelMatrix;

void main()
{
    vec4 worldPos = modelMatrix * vec4(inVertexPosition, 1.0);
    worldPos.y += 0.5;
    gl_Position = projViewMatrix * worldPos;

    passTextureCoord    = inTextureCoord;
}
