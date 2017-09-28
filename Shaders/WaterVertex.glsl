#version 330

layout(location = 0) in vec3  inVertexPosition;
layout(location = 1) in vec2  inTextureCoord;
layout(location = 2) in float inCardinalLight;

out vec2 passTextureCoord;
out float passCardinalLight;

uniform mat4 projViewMatrix;
uniform float brightness;
uniform float gamma;
uniform float contrast;

uniform float globalTime;

void main()
{
    vec4 pos = vec4(inVertexPosition, 1.0);
    pos.y -= 0.2f;

    float posYbuf = (pos.z / 0.6f + globalTime * 5f * 0.6f);
    pos.y -= sin(posYbuf) * 0.06f * 1.2f + sin(posYbuf / -7.0) * 0.06f;

    gl_Position = projViewMatrix * pos;

    passTextureCoord    = inTextureCoord;
    passCardinalLight   = inCardinalLight;
}
