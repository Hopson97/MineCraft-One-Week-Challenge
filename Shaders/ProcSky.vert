#version 330

layout(location = 0) in vec4  inVertexPosition;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform float dayTime;

out vec3 passColor;

const vec3 zenithColorDay = vec3(0.1, 0.4, 1.0);
const vec3 horizonColorDay = vec3(0.6, 0.85, 1.0);

const vec3 zenithColorNight = vec3(0.03, 0.04, 0.04);
const vec3 horizonColorNight = vec3(0.05, 0.04, 0.08);

const vec3 zenithColorSunRise = vec3(0.5, 0.4, 0.5);
const vec3 horizonColorSunRise = vec3(0.8, 0.55, 0.15);
const vec3 zenithColorMoonRise = vec3(0.4, 0.4, 0.7);
const vec3 horizonColorMoonRise = vec3(0.5, 0.45, 0.65);

vec3 getColor(float time, vec4 vertex){
    if(vertex.w == 1 || vertex.w == 2){
        if(dayTime < 1500){ //6am - 9am sun gets brighter
            return mix(zenithColorMoonRise, zenithColorDay, dayTime / 1500); 
        }
        if(dayTime >= 1500 && dayTime < 10500){ //9am - 3pm sun is brightest
            return zenithColorDay;
        }
        if(dayTime >= 10500 && dayTime < 12000){ //3pm - 6pm sun gets dimmer
            return mix(zenithColorDay, zenithColorSunRise, (dayTime - 10500) / 1500);
        }
        if(dayTime >= 12000 && dayTime < 13500){ //6pm - 9pm sun light fades
            return mix(zenithColorSunRise, zenithColorNight, (dayTime - 12000)/ 1500);
        }
        if(dayTime >= 13500 && dayTime < 22500){//9pm - 3am is night
            return zenithColorNight;
        }
        if(dayTime >= 22500 && dayTime < 24000){
            return mix(zenithColorNight, zenithColorMoonRise,(dayTime-22500) / 1500);
        }
    }else if(vertex.w == 0 || vertex.w == 3){
        if(dayTime < 1500){ //6am - 9am sun gets brighter
            return mix(horizonColorMoonRise, horizonColorDay, dayTime / 1500); 
        }
        if(dayTime >= 1500 && dayTime < 10500){ //9am - 3pm sun is brightest
            return horizonColorDay;
        }
        if(dayTime >= 10500 && dayTime < 12000){ //3pm - 6pm sun gets dimmer
            return mix(horizonColorDay, horizonColorSunRise, (dayTime - 10500) / 1500);
        }
        if(dayTime >= 12000 && dayTime < 13500){ //6pm - 9pm sun light fades
            return mix(horizonColorSunRise, horizonColorNight, (dayTime - 12000)/ 1500);
        }
        if(dayTime >= 13500 && dayTime < 22500){//9pm - 3am is night
            return horizonColorNight;
        }
        if(dayTime >= 22500 && dayTime < 24000){
            return mix(horizonColorNight, horizonColorMoonRise,(dayTime-22500) / 1500);
        }
    }else if(vertex.w == 5 || vertex.w == 6){
        if(dayTime < 1500){ //6am - 9am sun gets brighter
            return mix(zenithColorSunRise, zenithColorDay, dayTime / 1500); 
        }
        if(dayTime >= 1500 && dayTime < 10500){ //9am - 3pm sun is brightest
            return zenithColorDay;
        }
        if(dayTime >= 10500 && dayTime < 12000){ //3pm - 6pm sun gets dimmer
            return mix(zenithColorDay, zenithColorMoonRise, (dayTime - 10500) / 1500);
        }
        if(dayTime >= 12000 && dayTime < 13500){ //6pm - 9pm sun light fades
            return mix(zenithColorMoonRise, zenithColorNight, (dayTime - 12000)/ 1500);
        }
        if(dayTime >= 13500 && dayTime < 22500){//9pm - 3am is night
            return zenithColorNight;
        }
        if(dayTime >= 22500 && dayTime < 24000){
            return mix(zenithColorNight, zenithColorSunRise,(dayTime-22500) / 1500);
        }
    }else if(vertex.w == 4 || vertex.w == 7){
        if(dayTime < 1500){ //6am - 9am sun gets brighter
            return mix(horizonColorSunRise, horizonColorDay, dayTime / 1500); 
        }
        if(dayTime >= 1500 && dayTime < 10500){ //9am - 3pm sun is brightest
            return horizonColorDay;
        }
        if(dayTime >= 10500 && dayTime < 12000){ //3pm - 6pm sun gets dimmer
            return mix(horizonColorDay, horizonColorMoonRise, (dayTime - 10500) / 1500);
        }
        if(dayTime >= 12000 && dayTime < 13500){ //6pm - 9pm sun light fades
            return mix(horizonColorMoonRise, horizonColorNight, (dayTime - 12000)/ 1500);
        }
        if(dayTime >= 13500 && dayTime < 22500){//9pm - 3am is night
            return horizonColorNight;
        }
        if(dayTime >= 22500 && dayTime < 24000){
            return mix(horizonColorNight, horizonColorSunRise,(dayTime-22500) / 1500);
        }
    }
}

void main(){
    gl_Position = projectionMatrix * viewMatrix * vec4(inVertexPosition.xyz, 1.0);
    passColor = getColor(dayTime, inVertexPosition);
}