#version 330

out vec4 outColour;
in  vec2 passTextureCoord;

uniform sampler2D tex;
uniform sampler2D other;
void main()
{
    vec4 color = texture(tex, passTextureCoord);
    vec4 other = texture(other, passTextureCoord);
    
    outColour = color + other;
}
