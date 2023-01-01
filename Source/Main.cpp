#include "Application.h"

#include <fstream>
#include <iostream>

#include "Config.h"

#ifdef __WIN32
extern "C" {
// Enable dedicated graphics
__declspec(dllexport) bool NvOptimusEnablement = true;
__declspec(dllexport) bool AmdPowerXpressRequestHighPerformance = true;
}
#endif // __WIN32

namespace {
void loadConfig(Config &config);
void displayInfo();
} // namespace

int main()
{
    Config config;
    loadConfig(config);
    displayInfo();

    std::cin.ignore();
    std::cout << "Loading game...\n";

    Application app(config);
    app.runLoop();
}

namespace {
/// @brief Self declared function that loads in configuration files as needed.
/// @param config 
void loadConfig(Config &config)
{
    std::ifstream configFile("config.txt");
    std::string key;

    try
    {
        if (configFile.is_open())
        {
            while (configFile >> key)
            {
                if (key == "renderdistance") {
                    configFile >> config.renderDistance;
                    std::cout << "Config: Render Distance: "
                            << config.renderDistance << '\n';
                }
                else if (key == "fullscreen") {
                    configFile >> config.isFullscreen;
                    std::cout << "Config: Full screen mode: " << std::boolalpha
                            << config.isFullscreen << '\n';
                }
                else if (key == "windowsize") {
                    configFile >> config.windowX >> config.windowY;
                    std::cout << "Config: Window Size: " << config.windowX << " x "
                            << config.windowY << '\n';
                }
                else if (key == "fov") {
                    configFile >> config.fov;
                    std::cout << "Config: Field of Vision: " << config.fov << '\n';
                }
            }
        }
        else
        {
            std::cout << "Error: The program requires a configuration file to operate properly." << "\n";
            std::cout << "Please find or clone the relevant config.txt file!" << "\n";
            std::cout << "Terminating sequence..." << "\n";
            throw "Unable to load configuration file. This process cannot continue.";
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what();
    }

    //else {

        //std::cerr << "Error: Could not find config.txt file! Using defaults.\n";
    //}
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
} // namespace
