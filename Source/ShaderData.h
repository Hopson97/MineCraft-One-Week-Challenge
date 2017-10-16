#ifndef SHADER_DATA_H
#define SHADER_DATA_H

struct ShaderData{
    //FXAA
    bool fxaa;

    //Shadows
    bool shadow;

    //Bloom
    bool bloom;

    //Motion Blur
    bool motionblur;

    //Color Correction
    bool colorCorrection;

    //Cross Processing
    bool crossProcess;

    //Parallax Mapping
    bool parallaxMap;

    //Tone Mapping
    bool toneMap;

    //Volumetric Clouds
    bool volumetricClouds;

    //GodRays
    bool godrays;

    //MSAA
    bool msaa;
};

extern ShaderData g_ShaderSettings;

#endif