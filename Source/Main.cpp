#include "Application.h"

#include <fstream>
#include <iostream>
#include "ShaderData.h"
#include "Config.h"

#ifdef __WIN32
extern "C"
{
    //Enable dedicated graphics
    __declspec(dllexport) bool NvOptimusEnablement = true;
    __declspec(dllexport) bool AmdPowerXpressRequestHighPerformance = true;
}
#endif // __WIN32

namespace
{
    void loadConfig(Config& config);
    void loadShaders();
    void displayInfo();
}

int main()
{
    Config config;
    loadConfig(config);
    loadShaders();
    displayInfo();

    std::cin.ignore();
    std::cout << "Loading game...\n";

    Application app(config);
    app.runLoop();
}

namespace
{
void loadConfig(Config& config)
{
    std::ifstream configFile("config.txt");
    std::string key;

    if (configFile.is_open()) {
        while (configFile >> key) {
            if (key == "renderdistance") {
                configFile >> config.renderDistance;
                std::cout   << "Config: Render Distance: "
                            << config.renderDistance << '\n';
            } else if (key == "fullscreen") {
                configFile >> config.isFullscreen;
                std::cout   << "Config: Full screen mode: "
                            << std::boolalpha <<  config.isFullscreen << '\n';
            } else if (key == "windowsize") {
                configFile >> config.windowX >> config.windowY;
                std::cout   << "Config: Window Size: "
                            << config.windowX << " x " << config.windowY << '\n';
            } else if (key == "fov") {
                configFile >> config.fov;
                std::cout   << "Config: Field of Vision: "
                            << config.fov << '\n';
            } else if (key == "gamma") {
                configFile >> config.gamma;
                std::cout << "Config: Gamma: " << config.gamma << std::endl;
            } else if (key == "brightness") {
                configFile >> config.brightness;
                std::cout << "Config: Brightness: " << config.brightness << std::endl;
            } else if (key == "contrast") {
                configFile >> config.contrast;
                std::cout << "Config: Contrast: " << config.contrast << std::endl;
            } else if (key == "post process") {
                configFile >> config.postProcess;
                std::cout << "Post Processing: " << config.postProcess << std::endl;
            }
        }
    } else {
        std::cerr << "Error: Could not find config.txt file! Using defaults.\n";
    }
}

void loadShaders()
{
    std::ifstream shaderFile("shaders.txt");
    std::string key;

    if (shaderFile.is_open()) {
        while (shaderFile >> key) {
            if(key == "fxaa") {
                shaderFile >> g_ShaderSettings.fxaa;
                std::cout << "Shader: FXAA: " << g_ShaderSettings.fxaa << std::endl;
            } else if(key == "bloom") {
                shaderFile >> g_ShaderSettings.bloom;
                std::cout << "Shader: Bloom: " << g_ShaderSettings.bloom << std::endl;
            } else if(key == "motionblur") {
                shaderFile >> g_ShaderSettings.motionblur;
                std::cout << "Shader: Motion Blur: " << g_ShaderSettings.motionblur << std::endl;
            } else if(key == "aniso") {
                shaderFile >> g_ShaderSettings.aniso;
                std::cout << "Shader: Anisotropic Filtering: " << g_ShaderSettings.aniso << std::endl;
            } else if(key == "godrays") {
                shaderFile >> g_ShaderSettings.godrays;
                std::cout << "Shader: Godrays: " << g_ShaderSettings.godrays << std::endl;
            }
        }
    } else {
        std::cerr << "Error: Could not find shaders.txt file! Using defaults.\n";
    }
}

void displayInfo()
{
    std::ifstream inFile;
    inFile.open("Res/info.txt");
    std::string line;
    while (std::getline(inFile, line)) {
        std::cout << line << "\n";
    }
}
}



















