#pragma once

#include <deque>
#include <map>
#include <string>

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

template <typename T, int S>
struct CircularQueue
{
    void push_back(const T& new_data)
    {
        data.push_back(new_data);
        if (data.size() > 50)
        {
            data.pop_front();
        }
    }

    std::deque<T> data;
};

struct ProfilerSection
{
    std::string name;
    sf::Clock clock;
    CircularQueue<sf::Time, 50> times;
    sf::Time average;

    void end_section();
};

class Profiler
{
  public:
    ProfilerSection& begin_section(const std::string& section);
    void end_frame();

    void gui();

  private:
    std::map<std::string, ProfilerSection> profiler_sections_;
    CircularQueue<sf::Time, 50> frame_times_;
    sf::Clock frame_time_clock_;
    sf::Clock updater_timer_;
    int frames_ = 0;
    sf::Time average_;
};