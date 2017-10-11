#version 330

layout(location = 0) in vec3  inVertexPosition;
layout(location = 1) in vec2  inTextureCoord;
layout(location = 2) in float inCardinalLight;

out vec2 passTextureCoord;
out float passCardinalLight;

uniform mat4 projViewMatrix;
uniform float globalTime;


vec4 getWorldPos()
{
    vec3 inVert = inVertexPosition.xyz;
    inVert.x += sin((globalTime + inVert.z + inVert.y) * 1.8f) / 15.0f;
    inVert.z -= cos((globalTime + inVert.x + inVert.y) * 1.8f) / 15.0f;
    return vec4(inVert, 1);
}

void main()
{
    gl_Position = projViewMatrix * getWorldPos();

    passTextureCoord    = inTextureCoord;
    passCardinalLight   = inCardinalLight;
}
