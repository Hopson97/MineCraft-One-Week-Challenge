#version 330

in vec2 passTextureCoord;

out vec4 outColour;

uniform sampler2D flareTexture;
uniform float brightness;

void main(void){
    outColour = texture(flareTexture, passTextureCoord);
    outColour.a *= brightness;
}