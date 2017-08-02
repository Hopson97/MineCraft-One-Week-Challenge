#version 330

out vec4 outColour;
in  vec2 passTextureCoord;
in float passCardinalLight;

uniform sampler2D texSampler;

void main()
{
    outColour = texture(texSampler, passTextureCoord) * passCardinalLight;
    if (outColour.a == 0) discard;
}
