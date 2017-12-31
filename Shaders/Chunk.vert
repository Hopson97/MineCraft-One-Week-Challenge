#version 330

layout(location = 0) in vec3  inVertexPosition;
layout(location = 1) in vec2  inTextureCoord;
layout(location = 2) in float inCardinalLight;
layout(location = 3) in vec3  inNormal;

out vec2    passTextureCoord;
out float   passCardinalLight;
out vec3    passNormal;

out float visibility;

const float density = 0.005;
const float gradient = 1.8;

uniform mat4 projMatrix;
uniform mat4 viewMatrix;
uniform mat4 normalMatrix;
uniform float dayTime;

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

void main()
{
    gl_Position = projMatrix * viewMatrix * vec4(inVertexPosition, 1.0);
    vec4 positionRelative = viewMatrix * vec4(inVertexPosition, 1.0);
    passTextureCoord    = inTextureCoord;
    passNormal          = vec3(normalMatrix * vec4(inNormal, 1.0));
    getDirectional(inCardinalLight);

    float distance = length(positionRelative.xyz);
    visibility = exp(-pow((distance*density), gradient));
    visibility = clamp(visibility, 0, 1);
}
