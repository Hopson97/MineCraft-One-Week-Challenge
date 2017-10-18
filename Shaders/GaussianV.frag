#version 330

out vec4 outColour;

in vec2 passTextureCoord;

uniform sampler2D texSampler;

uniform float target;

float offset[3] = float[]( 0.0, 1.3846153846, 3.2307692308 );
float weight[3] = float[]( 0.2270270270, 0.3162162162, 0.0702702703 );


void main(void){
    vec3 tc = vec3(1.0, 0.0, 0.0);
    vec2 uv = passTextureCoord.xy;
    
    //Blur vertical
    tc = texture(texSampler, uv).rgb * weight[0];
    
    for (int i=1; i<3; i++) {
        tc += texture(texSampler, uv + vec2(0.0, offset[i])/target).rgb * weight[i];
        tc += texture(texSampler, uv - vec2(0.0, offset[i])/target).rgb * weight[i];
    }

    outColour = vec4(tc, 1.0);
}