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

    // If the config file is missing or "bad"
    if(!configFile.good())
    {
        std::cout << "Configuration file invalid,\n";
        std::cout << "writing 'new' configuration." << "\n";
        std::cout << "\n";

        std::ofstream outfile("config.txt");

        if(outfile.is_open())
        {
            outfile << "renderdistance " << "8";
            outfile << "fullscreen " << "0";
            outfile << "windowsize " << "1600 " << "900";
            outfile << "fov " << "105";

            outfile.close();
            configFile.close(); // Close so it can be reopened safely.
        }

        std::cout << "\n";
        std::cout << "New configuration file created." << "\n";
    }

    try
    {
        // Open 'new' config file.
        if(!configFile.is_open())
        {
            configFile.open("config.txt");
        }

        // If the file is still creating errors
        if(configFile.fail())
        {
            std::cout << "Error: The program failed to load the configuration files." << "\n";
            std::cout << "To understand why this error may have occured,\n";
            std::cout << "please examine your 'config.txt' file. Thank you." << "\n";

            // Because this is thrown before runtime, no memory needs to be freed.
            throw "Unable to load configuration file.";
        }

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
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what();
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
} // namespace
