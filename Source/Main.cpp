#include <print>

#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Window.hpp>
#include <fstream>
#include <glad/glad.h>
#include <iostream>

#include "Application.h"

#include "GL/GLUtils.h"
#include "GUI.h"
#include "Input/Keyboard.h"
#include "Util/Profiler.h"
#include "Util/TimeStep.h"

#include <SFML/GpuPreference.hpp>

namespace
{
    void handle_event(const sf::Event& event, sf::Window& window, bool& show_debug_info,
                      bool& close_requested);
    void loadConfig(Config& config);
    void displayInfo();

} // namespace

int main()
{

    Config config;
    loadConfig(config);
    displayInfo();

    sf::ContextSettings context_settings;
    context_settings.depthBits = 24;
    context_settings.stencilBits = 8;
    context_settings.antiAliasingLevel = 4;
    context_settings.majorVersion = 4;
    context_settings.minorVersion = 6;
    context_settings.attributeFlags = sf::ContextSettings::Debug;

    sf::Window window;
    if (config.isFullscreen)
    {
        window.create(sf::VideoMode::getDesktopMode(), "MineCraft Week", sf::Style::None,
                      sf::State::Fullscreen, context_settings);
    }
    else
    {
        sf::VideoMode winMode({(unsigned)config.windowX, (unsigned)config.windowY});
        window.create(winMode, "MineCraft Week", sf::State::Windowed, context_settings);
    }

    window.setVerticalSyncEnabled(true);
    if (!window.setActive(true))
    {
        std::println(std::cerr, "Failed to activate the window.");
        return EXIT_FAILURE;
    }

    if (!gladLoadGL())
    {
        std::println(std::cerr, "Failed to initialise OpenGL - Is OpenGL linked correctly?");
        return EXIT_FAILURE;
    }
    glClearColor(50.0f / 255.0f, 205.0f / 255.0f, 250.0f / 255.0f, 0);
    glViewport(0, 0, window.getSize().x, window.getSize().y);
    glCullFace(GL_BACK);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    gl::enable_debugging();

    TimeStep updater{50};
    Profiler profiler;
    bool show_debug_info = false;

    Application app{window, config};

    if (!GUI::init(&window))
    {
        std::println(std::cerr, "Failed to initialise Imgui.");
        return EXIT_FAILURE;
    }

    Keyboard keyboard;

    // -------------------
    // ==== Main Loop ====
    // -------------------
    sf::Clock clock;
    while (window.isOpen())
    {
        GUI::begin_frame();
        bool close_requested = false;
        while (auto event = window.pollEvent())
        {
            GUI::event(window, *event);
            keyboard.update(*event);
            app.on_event(*event);
            handle_event(*event, window, show_debug_info, close_requested);
        }
        auto dt = clock.restart();

        // Update
        {
            auto& update_profiler = profiler.begin_section("Update");
            app.on_update(keyboard, dt);
            update_profiler.end_section();
        }

        // Render
        {
            auto& render_profiler = profiler.begin_section("Render");
            app.on_render(show_debug_info);
            render_profiler.end_section();
        }

        // Show profiler
        profiler.end_frame();
        if (show_debug_info)
        {
            profiler.gui();
        }

        // --------------------------
        // ==== End Frame ====
        // --------------------------
        GUI::render();
        window.display();
        if (close_requested)
        {
            window.close();
        }
    }

    // --------------------------
    // ==== Graceful Cleanup ====
    // --------------------------
    GUI::shutdown();
}

namespace
{
    void handle_event(const sf::Event& event, sf::Window& window, bool& show_debug_info,
                      bool& close_requested)
    {
        if (event.is<sf::Event::Closed>())
        {
            close_requested = true;
        }
        else if (auto* key = event.getIf<sf::Event::KeyPressed>())
        {

            switch (key->code)
            {
                case sf::Keyboard::Key::Escape:
                    close_requested = true;
                    break;

                case sf::Keyboard::Key::F1:
                    show_debug_info = !show_debug_info;
                    break;

                default:
                    break;
            }
        }
    }

    /// @brief Self declared function that loads in configuration files as needed.
    /// @param config
    void loadConfig(Config& config)
    {
        std::ifstream configFile("config.txt");
        std::string key;

        // If the config file is missing or "bad"
        if (!configFile.good())
        {
            std::cout << "Configuration file invalid,\n";
            std::cout << "writing 'new' configuration." << "\n";
            std::cout << "\n";

            std::ofstream outfile("config.txt");

            if (outfile.is_open())
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
            if (!configFile.is_open())
            {
                configFile.open("config.txt");
            }

            // If the file is still creating errors
            if (configFile.fail())
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
                    if (key == "renderdistance")
                    {
                        configFile >> config.renderDistance;
                        std::cout << "Config: Render Distance: " << config.renderDistance << '\n';
                    }
                    else if (key == "fullscreen")
                    {
                        configFile >> config.isFullscreen;
                        std::cout << "Config: Full screen mode: " << std::boolalpha
                                  << config.isFullscreen << '\n';
                    }
                    else if (key == "windowsize")
                    {
                        configFile >> config.windowX >> config.windowY;
                        std::cout << "Config: Window Size: " << config.windowX << " x "
                                  << config.windowY << '\n';
                    }
                    else if (key == "fov")
                    {
                        configFile >> config.fov;
                        std::cout << "Config: Field of Vision: " << config.fov << '\n';
                    }
                }
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what();
        }
    }

    void displayInfo()
    {
        std::ifstream inFile;
        inFile.open("Res/info.txt");
        std::string line;
        while (std::getline(inFile, line))
        {
            std::cout << line << "\n";
        }
    }
} // namespace
