#include "FPSCounter.h"

FPSCounter::FPSCounter()
{ }

float FPSCounter::getFPS()
{
    return m_fps;
}

void FPSCounter::update()
{
    m_frameCount++;

    if (m_delayTimer.getElapsedTime().asSeconds())
    {
        m_fps =* m_frameCount / m_fpsTimer.restart().asMilliseconds() * 1000;

        m_frameCount = 0;
        m_delayTimer.restart();
    }
}


