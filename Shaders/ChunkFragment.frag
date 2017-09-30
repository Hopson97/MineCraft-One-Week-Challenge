#version 330

out vec4 outColour;
in  vec2 passTextureCoord;

uniform sampler2D texSampler;

in vec3 normal;

vec4 color;

void main()
{
    color = texture(texSampler, passTextureCoord);
    //Lighting calculations
    outColour = color;
    if (outColour.a == 0) discard;
}
