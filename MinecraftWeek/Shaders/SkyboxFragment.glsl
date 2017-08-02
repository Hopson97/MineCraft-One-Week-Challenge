#version 330

out vec4 outColour;
in  vec3 passTextureCoord;

uniform samplerCube texSampler;

void main()
{
    outColour = texture(texSampler, passTextureCoord);
}
