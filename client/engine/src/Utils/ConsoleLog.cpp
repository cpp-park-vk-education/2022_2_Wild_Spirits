#include "ConsoleLog.h"

#if defined(WIN32)
#include <Windows.h>
#endif

namespace LM {

    void ConsoleLog::SetColor(ConsoleColorType _TXT, ConsoleColorType _BG) {
#ifdef _WIN32
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hStdOut, static_cast<WORD>((static_cast<int>(_BG) << 4) | static_cast<int>(_TXT)));
#else
        std::string Style = "\033[" + std::to_string(static_cast<int16_t>(_BG)) + ";" +
            std::to_string(static_cast<int16_t>(_TXT)) + "m";
        std::cerr << Style;
#endif
    }

}    // namespace LM
