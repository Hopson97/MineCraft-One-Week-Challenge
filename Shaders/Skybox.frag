#version 330

out vec4 outColour;
in  vec3 passTextureCoord;

uniform samplerCube texSampler;

vec3 brightnessContrast(vec3 value, float brightness, float contrast)
{
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
    color = vec4(brightnessContrast(color.xyz, 1.15f, 1.15f), color.w);
    color = vec4(gamma(color.xyz, 4.8f),color.w);

    outColour = color;
    if (outColour.a == 0) discard;
}
