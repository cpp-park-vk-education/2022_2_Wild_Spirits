#pragma once

#include <Utils/ConsoleLog.h>

#ifdef _DEBUG
#define CORE_ASSERT(x, ...) { if (!(x)) { LOGE(__VA_ARGS__); DEBUGBREAK(); } }
#else
#define CORE_ASSERT(x, ...) 
#endif
