#version 330

out vec4 outColour;
in  vec2 passTextureCoord;

uniform sampler2D texSampler;

uniform float brightness;
uniform float contrast;
uniform float postProcess;
uniform float gamma;

vec3 brightnessContrast(vec3 value, float brightness, float contrast){
    return (value - 0.5) * contrast + 0.5 + (brightness-1);
}

vec3 gammaCorrect(vec3 value, float param){
    return vec3(pow(abs(value.r), param),pow(abs(value.g), param),pow(abs(value.b), param));
}

void main()
{
    vec4 color = texture(texSampler, passTextureCoord);
    
    if(postProcess == 1){
        
    }

    color = vec4(brightnessContrast(color.xyz, brightness, contrast), 1.0);
    color = vec4(gammaCorrect(color.xyz, gamma),color.w);

    outColour = color;
}
