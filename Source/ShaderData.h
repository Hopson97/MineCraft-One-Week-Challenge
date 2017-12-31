#ifndef SHADER_DATA_H
#define SHADER_DATA_H

struct ShaderData{
    //FXAA
    bool fxaa;

    //Bloom
    bool bloom;

    //Motion Blur
    bool motionblur;
    
    bool aniso;

    //GodRays
    bool godrays;
};

extern ShaderData g_ShaderSettings;

#endif