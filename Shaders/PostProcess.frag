#version 330

out vec4 outColor; 
in vec2 passTextureCoord;

uniform sampler2D texSampler;

void main()
{
    vec4 color = texture(texSampler, passTextureCoord);
    outColor = vec4(pow(color.xyz,vec3(.454545)),1.); //.454545 is 1.0/2.2, commonly used for gamma correction.
}
