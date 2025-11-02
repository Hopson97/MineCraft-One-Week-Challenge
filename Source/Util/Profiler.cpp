#include "Profiler.h"

#include <imgui.h>

namespace
{
    template <int S>
    auto calculate_average(const CircularQueue<sf::Time, S>& times)
    {
        auto sum = sf::Time::Zero;
        for (auto time : times.data)
        {
            sum += time;
        }
        return sf::seconds(sum.asSeconds() / static_cast<float>(times.data.size()));
    }
} // namespace

ProfilerSection& Profiler::begin_section(const std::string& section)
{
    auto itr = profiler_sections_.find(section);
    if (itr == profiler_sections_.end())
    {
        itr = profiler_sections_.emplace(section, ProfilerSection{}).first;
    }

    itr->second.clock.restart();
    return itr->second;
}

void ProfilerSection::end_section()
{
    times.push_back(clock.getElapsedTime());
}

void Profiler::end_frame()
{
    frame_times_.push_back(frame_time_clock_.restart());
    frames_++;

    if (updater_timer_.getElapsedTime() > sf::seconds(0.25f))
    {
        updater_timer_.restart();

        for (auto& [name, section] : profiler_sections_)
        {
            section.average = calculate_average(section.times);
        }
        average_ = calculate_average(frame_times_);
    }
}

void Profiler::gui()
{
    if (ImGui::Begin("Profiler"))
    {
        ImGui::Text("Frame: %.3fms", average_.asSeconds() * 1000.0f);
        sf::Time total = sf::Time::Zero;
        for (auto& [name, section] : profiler_sections_)
        {
            total += section.average;
            ImGui::Text("%s: %.3fms", name.c_str(), section.average.asSeconds() * 1000.0f);
        }
        ImGui::Text("Total: %.3fms", total.asSeconds() * 1000.0f);
    }
    ImGui::End();
}