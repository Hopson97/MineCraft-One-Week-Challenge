#version 330

out vec4 outColour;
in  vec2 passTextureCoord[11];

uniform sampler2D texSampler;

void main()
{
    outColour = vec4(0.0);
	outColour += texture(texSampler, passTextureCoord[0]) * 0.0093;
    outColour += texture(texSampler, passTextureCoord[1]) * 0.028002;
    outColour += texture(texSampler, passTextureCoord[2]) * 0.065984;
    outColour += texture(texSampler, passTextureCoord[3]) * 0.121703;
    outColour += texture(texSampler, passTextureCoord[4]) * 0.175713;
    outColour += texture(texSampler, passTextureCoord[5]) * 0.198596;
    outColour += texture(texSampler, passTextureCoord[6]) * 0.175713;
    outColour += texture(texSampler, passTextureCoord[7]) * 0.121703;
    outColour += texture(texSampler, passTextureCoord[8]) * 0.065984;
    outColour += texture(texSampler, passTextureCoord[9]) * 0.028002;
    outColour += texture(texSampler, passTextureCoord[10]) * 0.0093;


}
