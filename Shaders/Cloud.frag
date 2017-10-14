#version 330

out vec4 outColour;
in  vec2 passTextureCoord;

uniform sampler2D texSampler;
vec4 color;
uniform float lighting;

void main()
{
    color = texture(texSampler, passTextureCoord);
    //Lighting Calculations
    outColour = vec4(color.rgb * lighting, color.a * 0.6);
    if (outColour.a == 0) discard;
}
