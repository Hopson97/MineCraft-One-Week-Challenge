#version 330

out vec4 outColour;

in  vec2 passTextureCoord;
in float passCardinalLight;
in vec3  passNormal;

uniform sampler2D texSampler;
vec4 color;
uniform float lighting;

in float visibility; 
void main()
{
    color = texture(texSampler, passTextureCoord);
    //Lighting Calculations
    outColour = vec4(color.rgb * lighting * passCardinalLight, color.a);
    outColour = vec4(mix(vec3(0.5f, 0.5f, 0.6f) * (lighting*0.8),outColour.rgb, visibility),outColour.a);
    outColour.xyz += lighting * (0.04, 0.03, 0.02);
    if (outColour.a == 0) discard;
}
