#version 330

out vec4 outColour;
in  vec2 passTextureCoord;

uniform sampler2D texSampler;
uniform sampler2D depth;

uniform mat4 currProjViewMatrix;
uniform mat4 prevProjViewMatrix;

#define SAMPLES 60

void main()
{
    vec2 uv = passTextureCoord;
    float zOverw = texture(depth, uv).z / 1.0;
    vec4 h = vec4(uv.x * 2 -1, (1-uv.y) * 2-1, zOverw, 1);
    vec4 d = inverse(currProjViewMatrix) * h;
    vec4 worldPos = d/ d.w;

    vec4 currentPos = h;
    vec4 previousPos = prevProjViewMatrix * worldPos;

    previousPos /= previousPos.w;

    vec2 velocity = (currentPos.xy - previousPos.xy) / (SAMPLES*SAMPLES*SAMPLES/4);

    vec4 color = texture(texSampler, uv);

    uv += velocity;

    for(int i = 1; i<SAMPLES; ++i, uv+=velocity){
        vec4 currentColor = texture(texSampler, uv);
        color += currentColor;
    }

    outColour = color / SAMPLES;
}
