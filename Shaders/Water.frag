#version 330

out vec4 outColour;

in  vec2 passTextureCoord;
in float passCardinalLight;
in vec3  passNormal;

uniform sampler2D texSampler;
vec4 color;
uniform float lighting;

void main()
{
    color = texture(texSampler, passTextureCoord);
    //Lighting Calculations
    outColour = vec4(color.rgb * lighting, color.a) * passCardinalLight;;
    if (outColour.a == 0) discard;
}
