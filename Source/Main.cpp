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
void loadConfig(Config &config)
{
    std::ifstream configFile("config.txt");
    std::string key;

    if (configFile.is_open()) {
        while (configFile >> key) {
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
    else {
        std::cerr << "Error: Could not find config.txt file! Using defaults.\n";
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
