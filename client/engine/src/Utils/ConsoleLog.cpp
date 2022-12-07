#include "ConsoleLog.h"

#if defined(WIN32)
#include <Windows.h>
#endif

namespace LM {

    void ConsoleLog::SetColor(ConsoleColorType _TXT, ConsoleColorType _BG) {
#ifdef _WIN32
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hStdOut, (WORD)(((int)_BG << 4) | ((int)_TXT)));
#else
        std::string Style = "\033[" + std::to_string((short)_BG) + ";" + std::to_string((short)_TXT) + "m";
        std::cerr << Style;
        //std::cerr << "\033[0m \n"; // To reset atr
#endif
    }

}
