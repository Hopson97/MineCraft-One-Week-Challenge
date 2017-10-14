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
uniform float globalTime;


vec4 getWorldPos()
{
    vec3 inVert = inVertexPosition.xyz;
    inVert.y += sin((globalTime + inVert.x) * 2.3) / 16.8f;
    inVert.y += cos((globalTime + inVert.z) * 2.3) / 16.1f;
    inVert.y -= 0.2;
    return vec4(inVert, 1);
}

void main()
{
    gl_Position = projViewMatrix * getWorldPos();

    passTextureCoord    = inTextureCoord;
    passNormal          = vec3(normalMatrix * vec4(inNormal, 1.0));
    passCardinalLight   = inCardinalLight;
}
