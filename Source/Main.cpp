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
            else if (key == "post process"){
                configFile >> config.postProcess;
                std::cout << "Post Processing: " << config.postProcess << std::endl;
            }
        }
    }
    else
    {
        std::cerr << "Error: Could not find config.txt file! Using defaults.\n";
    }

    std::cout   << "\n\n============WELCOME TO MINECRAFT IN A WEEK============\n"
                << "This is a very simple Minecraft clone (mostly) created in one week\n\n"
                << "Because it was made in a week, some major features were missing:\n"
                << "-Level loading (Chunks do not save! So, I wouldn't commit to a build here for now)\n"
                << "-Caves\n"
                << "-Mobs\n"
                << "-Crafting\n\n"
                << "However, I did manage to implement some other important things:\n"
                << "-World generation\n"
                << "-Simple resource collection\n"
                << "-Biomes\n"
                << "-Collision detection\n"
                << "-Block breaking/ placing\n\n"
                << "For now, the game it pretty much entirely a community-driven project.\n"
                << "Source code can be found at https://github.com/Hopson97/MineCraft-One-Week-Challenge\n"
                << "Feel free to contribute!\n\n"
                << "Please view 'controls.txt for controls!\n\n"
                << "============Press enter to begin ============\n";

    std::cin.ignore();
    std::cout << "Loading game...\n";

    Application app(config);
    app.runLoop();
}
