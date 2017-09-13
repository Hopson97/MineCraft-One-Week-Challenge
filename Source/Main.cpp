#include "Application.h"

#include <fstream>
#include <iostream>

#include "Config.h"

#ifdef __WIN32
    extern "C"
    {
        //Enable dedicated graphics
        __declspec(dllexport) bool NvOptimusEnablement = true;
        __declspec(dllexport) bool AmdPowerXpressRequestHighPerformance = true;
    }
#endif // __WIN32

int main()
{
    std::ifstream configFile("config.txt");
    std::string key;
    Config config;

    if (configFile.is_open())
    {
        while (configFile >> key)
        {
            if (key == "renderdistance")
            {
                configFile >> config.renderDistance;
                std::cout   << "Config: Render Distance: "
                            << config.renderDistance << '\n';
            }
            else if (key == "fullscreen")
            {
                configFile >> config.isFullscreen;
                std::cout   << "Config: Full screen mode: "
                            << std::boolalpha <<  config.isFullscreen << '\n';
            }
            else if (key == "windowsize")
            {
                configFile >> config.windowX >> config.windowY;
                std::cout   << "Config: Window Size: "
                            << config.windowX << " x " << config.windowY << '\n';
            }
            else if (key == "fov")
            {
                configFile >> config.fov;
                std::cout   << "Config: Field of Vision: "
                            << config.fov << '\n';
            }
            else if (key == "gamma"){
                configFile >> config.gamma;
                std::cout << "Config: Gamma: " << config.gamma << std::endl;
            }
            else if (key == "brightness"){
                configFile >> config.brightness;
                std::cout << "Config: Brightness: " << config.brightness << std::endl;
            }
            else if (key == "contrast"){
                configFile >> config.contrast;
                std::cout << "Config: Contrast: " << config.contrast << std::endl;
            }
            else if (key == "fog"){
                configFile >> config.fog;
                std::cout << "Config: Fog: " << config.fog << std::endl;
            }
        }
    }
    else
    {
        std::cerr << "Error: Could not find config.txt file! Using defaults.\n";
    }

    Application app(config);
    app.runLoop();
}
