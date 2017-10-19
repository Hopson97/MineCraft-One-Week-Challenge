#version 330

out vec4 outColour;
in  vec2 passTextureCoord;

uniform sampler2D texSampler;

void main()
{
    vec4 color = texture(texSampler, passTextureCoord);
    float relativeLuminance = (color.r*0.299 + color.g*0.587 + color.b*0.114);
    if(relativeLuminance > 0.75){
        outColour = color;
    }else{
        outColour = vec4(0.0);
    }

    outColour.a = 0.0f;
}
