#version 330

layout(location = 0) in vec3  inVertexPosition;
layout(location = 1) in vec2  inTextureCoord;
layout(location = 2) in float inCardinalLight;

out vec2 passTextureCoord;
out float passCardinalLight;

uniform mat4 projViewMatrix;
uniform float globalTime;


    float posYbuf = (pos.z / 0.6f + globalTime * 2.5f * 0.6f) + (pos.x / 0.6f + globalTime * 1.5f * 0.6f);
    pos.y -= sin(posYbuf) * 0.06f * 1.2f + sin(posYbuf / -7.0) * 0.06f;

void main()
{
    gl_Position = projViewMatrix * getWorldPos();

    passTextureCoord    = inTextureCoord;
    passCardinalLight   = inCardinalLight;
}
