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

out float f_brightness;
out float f_gamma;
out float f_contrast;

void main()
{
    gl_Position = projViewMatrix * vec4(inVertexPosition, 1.0);

    passTextureCoord    = inTextureCoord;
    passCardinalLight   = inCardinalLight;
    f_brightness        = brightness;
    f_contrast          = contrast;
    f_gamma             = gamma;
}
