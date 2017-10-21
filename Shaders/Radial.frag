#version 330

out vec4 outColour;
in  vec2 passTextureCoord;

uniform sampler2D texSampler;
uniform vec2 resolution;

const float SAMPLES = 8.f;
float hash( vec2 p ){ return fract(sin(dot(p, vec2(41, 289)))*45758.5453); }

void main(){
    vec2 uv = passTextureCoord / resolution;
    
    float decay = 0.97; 
    
    float density = 0.5; 
    
    float weight = 0.1; 
    
    //LIGHT OFFSET
    vec3 l = vec3(0);
    
    vec2 tuv =  uv;

    vec2 dTuv = tuv*density/SAMPLES;
    
    vec4 col = texture(texSampler, uv);
    
  	uv += dTuv*(hash(uv)*2. - 1.);
    
    // The radial blur loop.
    for(float i=0.; i < SAMPLES; i++){
    
        uv -= dTuv;
        col += texture(texSampler, uv) * weight;
        weight *= decay;
    }
    
    outColour = col;
}