#version 330

out vec4 outColour;
in  vec2 passTextureCoord;
uniform sampler2D texSampler;

const float sampleDist = 1.2;
const float sampleStrength = 1.6/8; 

void main()
{
    float samples[8];
    for(int i = 0; i < 8; i++){
        samples[i] = 0 + (i * -0.02);
    }

    vec2 dir = 0.5 - passTextureCoord; 
    float dist = sqrt(dir.x*dir.x + dir.y*dir.y); 
    dir = dir/dist; 

    vec4 color = texture(texSampler,passTextureCoord); 
    vec4 sum = color;

    for (int i = 0; i < 8; i++)
        sum += texture( texSampler, passTextureCoord + dir * samples[i] * sampleDist );

    sum *= 1.0/11.0;
    float t = dist * sampleStrength;
    t = clamp( t ,0.0,1.0);

    outColour = mix( color, sum, t );

}
