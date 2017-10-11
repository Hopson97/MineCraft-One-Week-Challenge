#version 330

out vec4 outColour;
in  vec2 passTextureCoord;

uniform sampler2D texSampler;
uniform vec2 resolution;

uniform float brightness;
uniform float contrast;
uniform float postProcess;
uniform float gamma;

vec3 brightnessContrast(vec3 value, float brightness, float contrast)
{
    return (value - 0.5) * contrast + 0.5 + (brightness-1);
}

vec3 gammaCorrect(vec3 value, float param)
{
    return vec3(pow(abs(value.r), param),pow(abs(value.g), param),pow(abs(value.b), param));
}

#define FXAA_REDUCE_MIN (1.0/128.0)
#define FXAA_REDUCE_MUL (1.0/4.0) // ?x antialiasing. Switch values to get higher/lower default is 4x FXAA
#define FXAA_SPAN_MAX 8.0

vec3 fxaa(vec2 resolution, sampler2D sampler0, vec2 texcoord)
{
    vec2 inverse_resolution=vec2(1.0/resolution.x,1.0/resolution.y);
    vec3 rgbNW = texture(sampler0, texcoord.xy + (vec2(-1.0,-1.0)) * inverse_resolution).xyz;
    vec3 rgbNE = texture(sampler0, texcoord.xy + (vec2(1.0,-1.0)) * inverse_resolution).xyz;
    vec3 rgbSW = texture(sampler0, texcoord.xy + (vec2(-1.0,1.0)) * inverse_resolution).xyz;
    vec3 rgbSE = texture(sampler0, texcoord.xy + (vec2(1.0,1.0)) * inverse_resolution).xyz;
    vec3 rgbM  = texture(sampler0,  texcoord.xy).xyz;
    vec3 luma = vec3(0.299, 0.587, 0.114);
    float lumaNW = dot(rgbNW, luma);
    float lumaNE = dot(rgbNE, luma);
    float lumaSW = dot(rgbSW, luma);
    float lumaSE = dot(rgbSE, luma);
    float lumaM  = dot(rgbM,  luma);
    float lumaMin = min(lumaM, min(min(lumaNW, lumaNE), min(lumaSW, lumaSE)));
    float lumaMax = max(lumaM, max(max(lumaNW, lumaNE), max(lumaSW, lumaSE)));
    vec2 dir;
    dir.x = -((lumaNW + lumaNE) - (lumaSW + lumaSE));
    dir.y =  ((lumaNW + lumaSW) - (lumaNE + lumaSE));
    float dirReduce = max((lumaNW + lumaNE + lumaSW + lumaSE) * (0.25 * FXAA_REDUCE_MUL),FXAA_REDUCE_MIN);
    float rcpDirMin = 1.0/(min(abs(dir.x), abs(dir.y)) + dirReduce);
    dir = min(vec2( FXAA_SPAN_MAX,  FXAA_SPAN_MAX),max(vec2(-FXAA_SPAN_MAX, -FXAA_SPAN_MAX),dir * rcpDirMin)) * inverse_resolution;
    vec3 rgbA = 0.5 * (texture(sampler0,   texcoord.xy   + dir * (1.0/3.0 - 0.5)).xyz + texture(sampler0,   texcoord.xy   + dir * (2.0/3.0 - 0.5)).xyz);
    vec3 rgbB = rgbA * 0.5 + 0.25 * (texture(sampler0,  texcoord.xy   + dir *  - 0.5).xyz + texture(sampler0,  texcoord.xy   + dir * 0.5).xyz);
    float lumaB = dot(rgbB, luma);
    vec3 res;
    if((lumaB < lumaMin) || (lumaB > lumaMax))
    {
        res = rgbA;
    }
    else
    {
        res = rgbB;
    }
    return res;
}

void main()
{
    vec4 color = texture(texSampler, passTextureCoord);

    if(postProcess == 1)
    {

        color = vec4(fxaa(resolution, texSampler, passTextureCoord), color.w);
    }

    color = vec4(brightnessContrast(color.xyz, brightness, contrast), 1.0);
    color = vec4(gammaCorrect(color.xyz, gamma),color.w);

/*
//Spooky Shader
    color.b = 0;
    color.g *= 0.5;
*/

    /*
    color.r = 1 - color.r;
    color.g = 1 - color.g;
    color.b = 1 - color.b;
*/
/*
    float col = max(color.r, max(color.g, color.b));
    color.r = col;
    color.g = col;
    color.b = col;
*/
    outColour = color;
}
