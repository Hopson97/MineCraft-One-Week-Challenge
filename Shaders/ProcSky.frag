#version 330

in vec3 passColor;
out vec4 outColour;

void main(){
    //Process the color later
    vec4 skyColor = vec4(passColor, 1.0f);

    float skyColorBoost = -0.15f;
	
	skyColor.r = skyColor.r * (1.0f + skyColorBoost) - (skyColor.g * skyColorBoost / 2.0f) - (skyColor.b * skyColorBoost / 2.0f);
	skyColor.g = skyColor.g * (1.0f + skyColorBoost) - (skyColor.r * skyColorBoost / 2.0f) - (skyColor.b * skyColorBoost / 2.0f);
	skyColor.b = skyColor.b * (1.0f + skyColorBoost) - (skyColor.r * skyColorBoost / 2.0f) - (skyColor.g * skyColorBoost / 2.0f);
    
    
    outColour = skyColor;
    if (outColour.a == 0) discard;
}