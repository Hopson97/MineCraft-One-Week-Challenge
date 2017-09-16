#version 330

out vec4 outColour;
in  vec2 passTextureCoord;

uniform sampler2D texSampler;

void main()
{
    vec4 color = texture(texSampler, passTextureCoord);
    
    outColour = color;
}
