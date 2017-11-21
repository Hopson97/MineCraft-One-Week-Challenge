#version 330

out vec4 outColour;
in  vec2 passTextureCoord;
in vec2 screenSpaceSun;
uniform sampler2D texSampler;

#define SAMPLES 100

vec4 godrays(float density, float weight, float decay, float exposure){
    vec4 fragColor = vec4(0.0,0.0,0.0, 0.0);

	vec2 deltaTextCoord = vec2( passTextureCoord - screenSpaceSun.xy );

	vec2 textCoo = passTextureCoord.xy ;
	deltaTextCoord *= (1.0 /  float(SAMPLES)) * density;
    float illuminationDecay = 1.0;

    for(int i=0; i < 100 ; i++){
	    if(SAMPLES < i) {
            break;
	    }

		textCoo -= deltaTextCoord;
		vec4 samp = texture(texSampler, textCoo);
		samp *= illuminationDecay * weight;
		fragColor += samp;
		illuminationDecay *= decay;
    }

    fragColor *= exposure;

    return fragColor;
}

void main()
{
    vec4 color = godrays(1.15f, 1.0f, 1.0f, 1.0f);
    
    outColour = color;
}
