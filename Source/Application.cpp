#include "Application.h"

#include "States/PlayingState.h"
#include "World/Block/BlockDatabase.h"

Application::Application(const Config& config)
:   m_context   (config)
,   m_camera    (config)
,   m_config (config)
{
    BlockDatabase::get();
    pushState<StatePlaying>(*this, config);
}

void Application::runLoop()
{
    sf::Clock dtTimer;
    m_masterRenderer.setConfig(m_config);

    if(m_config.fog){
        GLfloat fogColor[4] = {1.0f,1.0f,1.0f,1.0f}; 
        glEnable(GL_FOG);
        glFogi(GL_FOG_MODE, GL_EXP2);
        glFogfv(GL_FOG_COLOR, fogColor);
        glFogf(GL_FOG_DENSITY, 1.0f);
        glFogf(GL_FOG_START, 32.0f); //2 Chunks before render distance
        glFogf(GL_FOG_END, 128.0f); //Render distance 
        glHint(GL_FOG_HINT, GL_NICEST);
    }

    while (m_context.window.isOpen() && !m_states.empty())
    {
        auto deltaTime = dtTimer.restart();
        auto& state = *m_states.back();

        state.handleInput();
        state.update(deltaTime.asSeconds());
        m_camera.update();

        state.render(m_masterRenderer);
        m_masterRenderer.finishRender(m_context.window, m_camera);

        handleEvents();
        if (m_isPopState)
        {
            m_isPopState = false;
            m_states.pop_back();
        }

    }
}

void Application::handleEvents()
{
    sf::Event e;
    while (m_context.window.pollEvent(e))
    {
        switch(e.type)
        {
            case sf::Event::Closed:
                m_context.window.close();
                break;

            case sf::Event::KeyPressed:
                switch(e.key.code)
                {
                    case sf::Keyboard::Escape:
                        m_context.window.close();
                        break;

                    default:
                        break;
                }
                break;

            default:
                break;
        }
    }
}


void Application::popState()
{
    m_isPopState = true;
}

void Application::turnOffMouse()
{
    m_context.window.setMouseCursorVisible(false);
}

void Application::turnOnMouse()
{
    m_context.window.setMouseCursorVisible(true);
}

