#version 330

out vec4 outColour;
in  vec2 passTextureCoord;
in float passCardinalLight;

uniform sampler2D texSampler;

in float f_brightness;
in float f_gamma;
in float f_contrast;

vec3 brightnessContrast(vec3 value, float brightness, float contrast){
    return (value - 0.5) * contrast + 0.5 + (brightness-1);
}

vec4 color;

vec3 gamma(vec3 value, float param)
{
    return vec3(pow(abs(value.r), param),pow(abs(value.g), param),pow(abs(value.b), param));
}

void main()
{
    color = texture(texSampler, passTextureCoord);
    color = vec4(brightnessContrast(color.xyz, f_brightness, f_contrast), color.w);
    color = vec4(gamma(color.xyz, f_gamma),color.w);

    outColour = color * passCardinalLight;
    if (outColour.a == 0) discard;
}
