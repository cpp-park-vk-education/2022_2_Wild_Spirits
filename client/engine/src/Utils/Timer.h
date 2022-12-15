#pragma once

#include <chrono>

namespace LM {

    using Tick = float;

    class Timer {
    public:
        Timer() {}
        ~Timer() {}

        Tick getElapsed() { return 0.0f; }
    private:
        std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
        std::chrono::time_point<std::chrono::steady_clock> m_EndTimepoint;
    };

}    // namespace LM
