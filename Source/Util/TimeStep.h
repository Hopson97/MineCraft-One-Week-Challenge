#pragma once

#include <SFML/System/Clock.hpp>
#include <functional>

/// Calls a function with a main loop at a fixed rate
class TimeStep
{
  public:
    using UpdateFunction = std::function<void(sf::Time)>;

    TimeStep(int tick_rate)
        : tick_rate_(tick_rate)
    {
    }

    void update(UpdateFunction func)
    {
        sf::Time time = timer_.getElapsedTime();
        sf::Time elapsed = time - last_time_;
        last_time_ = time;
        lag_ += elapsed;
        while (lag_ >= timePerUpdate_)
        {
            lag_ -= timePerUpdate_;
            func(dt_.restart());
        }
    }

    /// How many ticks per second should run for each step
    void set_tick_rate(int new_tick_rate)
    {
        tick_rate_ = new_tick_rate;
        timePerUpdate_ = sf::seconds(1.f / tick_rate_);
    }

  private:
    int tick_rate_ = 50;
    sf::Time timePerUpdate_ = sf::seconds(1.f / tick_rate_);
    sf::Clock timer_;
    sf::Clock dt_;
    sf::Time last_time_ = sf::Time::Zero;
    sf::Time lag_ = sf::Time::Zero;
};