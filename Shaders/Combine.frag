#version 330

out vec4 outColour;
in  vec2 passTextureCoord;

uniform sampler2D tex;
uniform sampler2D other;
void main()
{
    vec4 color = texture(tex, passTextureCoord);
    vec4 color2 = texture(other, passTextureCoord);
    
    outColour = vec4(color.rgb + color2.rgb, 1.0);
}
