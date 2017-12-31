#version 330

layout(location = 0) in vec3 inVertexPosition;
layout(location = 1) in vec2 inTextureCoord;

out vec2 passTextureCoord[11];

uniform mat4 projViewMatrix;
uniform mat4 modelMatrix;
uniform float target;
void main()
{
    gl_Position = projViewMatrix * modelMatrix * vec4(inVertexPosition, 1.0);
    vec2 center = inVertexPosition.xy * 0.5 + 0.5;
    float pixelSize = 1.0 / target;
    for(int i = -5; i<=5; i++){
        passTextureCoord[i+5] = inVertexPosition.xy + vec2(pixelSize*i, 0.0f);
    }
}
