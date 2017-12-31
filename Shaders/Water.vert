#version 330

layout(location = 0) in vec3  inVertexPosition;
layout(location = 1) in vec2  inTextureCoord;
layout(location = 2) in float inCardinalLight;
layout(location = 3) in vec3  inNormal;

const float PI = 3.1415927;
out vec2    passTextureCoord;
out float   passCardinalLight;
out vec3    passNormal;
#define Water_WaveSpeed1	0.25	
#define Water_WaveSpeed2	0.10
uniform mat4 projViewMatrix;
uniform mat4 normalMatrix;
uniform float globalTime;
uniform float dayTime;

out float visibility;
const float density = 0.005;
const float gradient = 1.8;
uniform mat4 projMatrix;
uniform mat4 viewMatrix;
void getDirectional(float pl){
    if(pl == 0.5){ //bot
        passCardinalLight =  0.5f; //The bottom of a block is never lit
    }else if(pl == 0.6){ //front
        if(dayTime < 1500){
            passCardinalLight =  mix(1.0f, 0.8f, dayTime/1500);
        }
        if(dayTime >= 1500 && dayTime < 22500){
            passCardinalLight = 0.8f;
        }
        if(dayTime >= 22500 && dayTime < 24000){
            passCardinalLight =  mix(0.8f, 1.0f, (dayTime-22500)/1500);
        }
    }else if(pl == 0.8){ //right
        passCardinalLight =  0.8f; //These aren't effected by either side
    }else if(pl == 0.9){ //left
        passCardinalLight =  0.8f; //These aren't effected by either side
    }else if(pl == 1.0){ //top
        if(dayTime < 6000){
            passCardinalLight =  mix(0.8f, 1.0f, dayTime/6000);
        }
        if(dayTime >= 6000 && dayTime < 12000){
            passCardinalLight =  mix(1.0f, 0.8f, (dayTime-6000)/6000);
        }
        if(dayTime >= 12000 && dayTime < 18000){
            passCardinalLight =  0.8f;
        }
        if(dayTime >= 18000 && dayTime < 24000){
            passCardinalLight =  0.8f;
        }
    }else if(pl == 0.7){ 
        if(dayTime < 10500 || dayTime >= 13500){
            passCardinalLight = 0.8f;
        }
        if(dayTime >= 10500 && dayTime < 12000){
            passCardinalLight = mix(0.8f, 1.0f, (dayTime-10500)/1500);
        }
        if(dayTime >= 12000 && dayTime < 13500){
            passCardinalLight = mix(1.0f, 0.8f, (dayTime-12000)/1500);
        }
    }
}


vec4 getWorldPos()
{
    vec3 inVert = inVertexPosition.xyz;
    
    float fy = fract(inVert.y + 0.001);
    float wave = 0.05 * sin(2 * PI * (globalTime*2 * Water_WaveSpeed1 - inVert.x /  7.0 - inVert.z / 13.0))
				   + 0.05 * sin(2 * PI * (globalTime * Water_WaveSpeed2 - inVert.x / 11.0 - inVert.z /  5.0));
		

    inVert.y += sin((globalTime + inVert.x) * 2.3) / 64.8f;
    inVert.y += cos((globalTime + inVert.z) * 2.3) / 64.1f;
    float displacement = clamp(wave, -fy, 1.0-fy);
	float Dynamic_wavingWater = 1.0f;

    inVert.y += displacement * 1.0 * Dynamic_wavingWater;
    inVert.y += displacement * 1.8 * 0.25;
    inVert.y -= 0.15f;
    return vec4(inVert, 1);

}

void main()
{
    gl_Position = projViewMatrix * getWorldPos();
    vec4 positionRelative = viewMatrix * vec4(inVertexPosition, 1.0);
    passTextureCoord    = inTextureCoord;
    passNormal          = vec3(normalMatrix * vec4(inNormal, 1.0));
    getDirectional(inCardinalLight);
    

    float distance = length(positionRelative.xyz);
    visibility = exp(-pow((distance*density), gradient));
    visibility = clamp(visibility, 0, 1);
}
