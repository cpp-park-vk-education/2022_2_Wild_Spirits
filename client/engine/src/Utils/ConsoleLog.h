#pragma once

#include <iostream>
#include <mutex>
#include <utility>

#include <Core/Base.h>

// #define USE_LOG

#if defined(_DEBUG) || defined(USE_LOG) || !defined(NDEBUG)
    #ifndef LOG_ON
        #define LOG_ON true
    #endif
#else
    #ifndef LOG_ON
        #define LOG_ON false
    #endif
#endif

namespace LM {

    class ConsoleLog {
    public:
#ifdef _WIN32
        enum class ConsoleColorType {
            Black = 0,
            Blue = 1,
            Green = 2,
            Cyan = 3,
            Red = 4,
            Magenta = 5,
            LightGray = 7,
            DarkGray = 8,
            LightBlue = 9,
            LightGreen = 10,
            LightCyan = 11,
            LightRed = 12,
            LightMagenta = 13,
            Yellow = 14,
            White = 15
        };
#else
        enum class ConsoleColorType : int16_t {
            Black = 30,
            Blue = 34,
            Green = 32,
            Cyan = 36,
            Red = 31,
            Magenta = 35,
            LightGray = 37,
            DarkGray = 90,
            LightBlue = 94,
            LightGreen = 92,
            LightCyan = 96,
            LightRed = 91,
            LightMagenta = 95,
            Yellow = 33,
            White = 97,
        };
#endif
        typedef ConsoleColorType ConsoleTxtColor;
        typedef ConsoleColorType ConsoleBgColor;

        static void Init() {
            s_Instance = Ref<ConsoleLog>(new ConsoleLog());
            std::unique_lock Lock(s_Instance->m_Mtx);
            // std::system("cls");
        }

        static inline Ref<ConsoleLog> Get() { return s_Instance; }

        void SetColor(ConsoleColorType _TXT = ConsoleTxtColor::White,
                      ConsoleColorType _BG = ConsoleBgColor::Black);

        template <typename... Args>
        void LogInfo(Args&&... _Args) {
            std::unique_lock Lock(m_Mtx);
            SetColor(ConsoleTxtColor::Green);
            std::cerr << "[ INFO ]: ";
            (std::cerr << ... << _Args) << ' ';
            std::cerr << std::endl;
            SetColor();
        }

        template <typename... Args>
        void LogWarning(Args&&... _Args) {
            std::unique_lock Lock(m_Mtx);
            SetColor(ConsoleTxtColor::Yellow);
            std::cerr << "[ WARNING ]: ";
            (std::cerr << ... << _Args) << ' ';
            std::cerr << std::endl;
            SetColor();
        }

        template <typename... Args>
        void LogError(Args&&... _Args) {
            std::unique_lock Lock(m_Mtx);
            SetColor(ConsoleTxtColor::Red);
            std::cerr << "[ ERROR ]: ";
            (std::cerr << ... << _Args) << ' ';
            std::cerr << std::endl;
            SetColor();
        }

        void LogDecorate() {
            std::unique_lock Lock(m_Mtx);
            SetColor(ConsoleTxtColor::LightGray);
            printf("========================================\n");
            SetColor();
        }

    protected:
        ConsoleLog() = default;

    protected:
        static inline Ref<ConsoleLog> s_Instance = nullptr;
        std::mutex m_Mtx;
    };

}    // namespace LM

#if LOG_ON
    #define LOG_INIT() ::LM::ConsoleLog::Get()->Init()
    #define LOGI(...)  ::LM::ConsoleLog::Get()->LogInfo(__VA_ARGS__)
    #define LOGW(...)  ::LM::ConsoleLog::Get()->LogWarning(__VA_ARGS__)
    #define LOGE(...)  ::LM::ConsoleLog::Get()->LogError(__VA_ARGS__)
    #define LOGD()     ::LM::ConsoleLog::Get()->LogDecorate();
#else
    #define LOG_INIT()
    #define LOGI(...)
    #define LOGW(...)
    #define LOGE(...)
    #define LOGD()
#endif    // LOG_ON
