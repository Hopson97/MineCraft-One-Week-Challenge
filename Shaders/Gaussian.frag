#version 150

out vec4 out_colour;

in vec2 passTextureCoord[11];

uniform sampler2D originalTexture;

void main(void){
	
	out_colour = vec4(0.0);
	out_colour += texture(originalTexture, passTextureCoord[0]) * 0.0093;
    out_colour += texture(originalTexture, passTextureCoord[1]) * 0.028002;
    out_colour += texture(originalTexture, passTextureCoord[2]) * 0.065984;
    out_colour += texture(originalTexture, passTextureCoord[3]) * 0.121703;
    out_colour += texture(originalTexture, passTextureCoord[4]) * 0.175713;
    out_colour += texture(originalTexture, passTextureCoord[5]) * 0.198596;
    out_colour += texture(originalTexture, passTextureCoord[6]) * 0.175713;
    out_colour += texture(originalTexture, passTextureCoord[7]) * 0.121703;
    out_colour += texture(originalTexture, passTextureCoord[8]) * 0.065984;
    out_colour += texture(originalTexture, passTextureCoord[9]) * 0.028002;
    out_colour += texture(originalTexture, passTextureCoord[10]) * 0.0093;

}