#version 330

out vec4 outColour;
in  vec2 passTextureCoord;

uniform sampler2D texSampler;
uniform float requestedLuminance;

void main()
{
    vec4 color = texture(texSampler, passTextureCoord);
    float relativeLuminance = sqrt( 0.299*color.r*color.r + 0.587*color.g*color.g + 0.114*color.b*color.b );
    if(relativeLuminance > requestedLuminance){
        outColour = color;
    }else{
        outColour = vec4(0.0);
    }

    outColour.a = 0.0f;
}
