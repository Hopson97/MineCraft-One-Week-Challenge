#version 330

layout(location = 0) in vec3 inVertexPosition;

out vec3 passTextureCoord;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

void main()
{
    gl_Position = projectionMatrix * viewMatrix * vec4(inVertexPosition, 1.0);

    passTextureCoord = inVertexPosition;
}
