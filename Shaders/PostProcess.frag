#version 330

out vec4 outColour;
in  vec2 passTextureCoord;

uniform sampler2D texSampler;
uniform vec2 resolution;

uniform float brightness;
uniform float contrast;
uniform float gamma;


float kernel[9]=float[9]
(2/9, 2/9, 2/9,
 2/9, 16/9 , 2/9,
 2/9, 2/9, 2/9);
vec2 offset[9]=vec2[9]
(
    vec2(-1.0, -1.0),
    vec2( 0.0, -1.0),
    vec2( 1.0, -1.0),
    vec2(-1.0,  0.0),
    vec2( 0.0,  0.0),
    vec2( 1.0,  0.0),
    vec2(-1.0,  1.0),
    vec2( 0.0,  1.0),
    vec2( 1.0,  1.0)

);

vec3 brightnessContrast(vec3 value, float brightness, float contrast)
{
    return (value - 0.5) * contrast + 0.5 + (brightness-1);
}

vec3 gammaCorrect(vec3 value, float param)
{
    return vec3(pow(abs(value.r), param),pow(abs(value.g), param),pow(abs(value.b), param));
}

vec3 rgb2hsv(vec3 c)
{
    vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
    vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
    vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));

    float d = q.x - min(q.w, q.y);
    float e = 1.0e-10;
    return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}

vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

vec3 Uncharted2Tonemap(vec3 x) {
	float A = 0.28;		
	float B = 0.29;		
	float C = 0.10;
	float D = 0.175; //0.04 - 0.35 color boost
	float E = 0.025;
	float F = 0.35;
	return ((x*(A*x+C*B)+D*E)/(x*(A*x+B)+D*F))-E/F;
}

void main()
{
    vec4 color = vec4(0.0);

    //Sharpen
    vec4 result = vec4(0.0);

    vec4 color2 = textureLod(texSampler, passTextureCoord + offset[0]*resolution.xy,0);
    result += color2 * kernel[0];
    color = textureLod(texSampler, passTextureCoord + offset[1]*resolution.xy,0);
    result += color2 * kernel[1];
    color = textureLod(texSampler, passTextureCoord + offset[2]*resolution.xy,0);
    result += color2 * kernel[2];
    color = textureLod(texSampler, passTextureCoord + offset[3]*resolution.xy,0);
    result += color2 * kernel[3];
    color = textureLod(texSampler, passTextureCoord + offset[4]*resolution.xy,0);
    result += color2 * kernel[4];
    color = textureLod(texSampler, passTextureCoord + offset[5]*resolution.xy,0);
    result += color2 * kernel[5];
    color = textureLod(texSampler, passTextureCoord + offset[6]*resolution.xy,0);
    result += color2 * kernel[6];
    color = textureLod(texSampler, passTextureCoord + offset[7]*resolution.xy,0);
    result += color2 * kernel[7];
    color = textureLod(texSampler, passTextureCoord + offset[8]*resolution.xy,0);
    result += color2 * kernel[8];

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
    //Brightness & Contrast
    result = vec4(brightnessContrast(result.xyz, brightness, contrast), 1.0);
    //Gamma
    result = vec4(gammaCorrect(result.xyz, gamma),result.w);

    //Color correct
    result = vec4(rgb2hsv(result.xyz), result.w);
    result.y *= 1.35;
    result.z *= 1.15;
    result = vec4(hsv2rgb(result.xyz), result.w);   

    
    //result.rgb = Uncharted2Tonemap(result.rgb) * 2.21;
	
    float colorBoost = 0.21f;
	
	result.r = result.r * (1.0f + colorBoost) - (result.g * colorBoost / 2.0f) - (result.b * colorBoost / 2.0f);
	result.g = result.g * (1.0f + colorBoost) - (result.r * colorBoost / 2.0f) - (result.b * colorBoost / 2.0f);
	result.b = result.b * (1.0f + colorBoost) - (result.r * colorBoost / 2.0f) - (result.g * colorBoost / 2.0f);
    

	outColour = result;
}
