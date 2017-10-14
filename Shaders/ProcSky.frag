#version 330

in vec3 passColor;
out vec4 outColour;

void main(){
    //Process the color later
    outColour = vec4(passColor, 1.0f);
    if (outColour.a == 0) discard;
}