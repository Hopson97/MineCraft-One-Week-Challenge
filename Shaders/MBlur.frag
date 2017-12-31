#version 330

out vec4 outColour;
in  vec2 passTextureCoord;

uniform sampler2D texSampler;
uniform sampler2D depth;

uniform mat4 currProjViewMatrix;
uniform mat4 prevProjViewMatrix;
uniform vec2 resolution;

#define SAMPLES 8

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

    float maxVelocity = 0.05;
    vec2 pixel = 1.0 / resolution;
    vec2 velocity = (currentPos.xy - previousPos.xy) * 0.0025;
    velocity = clamp(velocity, vec2(-maxVelocity), vec2(maxVelocity));
    vec2 sampleStep = velocity / SAMPLES;

    vec3 color = texture(texSampler, uv).rgb;
    color *= 0.001;
    
    uv += velocity;

    for(float i = 1.0; i <= SAMPLES; i++) {
		vec2 coord = passTextureCoord - sampleStep * i;
		color += texture(texSampler, 	clamp(coord, pixel, 1.0 - pixel)).rgb;
	}

    outColour = vec4(color /= max(SAMPLES + 1.0, 1.0), 1.0);

}
