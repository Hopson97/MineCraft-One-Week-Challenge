#version 330

out vec4 outColour;
in  vec2 passTextureCoord;

in vec3 normal;
uniform sampler2D texSampler;
vec4 color;

void main()
{
    color = texture(texSampler, passTextureCoord);
    //Lighting Calculations
    outColour = color;
    if (outColour.a == 0) discard;
}
