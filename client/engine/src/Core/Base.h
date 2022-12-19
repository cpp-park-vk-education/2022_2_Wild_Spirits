#pragma once

#include <memory>
#include <vector>

#ifdef _DEBUG
    #if defined(WIN32)
        #define DEBUGBREAK() __debugbreak()
    #elif defined(LINUX)
        #include <signal.h>
        #define DEBUGBREAK() raise(SIGTRAP)
    #else
        #define DEBUGBREAK()
    #endif
#endif

#define BIT(x) (1 << x)

namespace LM {

    template <typename T>
    using Vector = std::vector<T>;

    template <typename T>
    using Scope = std::unique_ptr<T>;
    template <typename T, typename... Args>
    constexpr Scope<T> CreateScope(Args&&... args) {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template <typename T>
    using Ref = std::shared_ptr<T>;
    template <typename T, typename... Args>
    constexpr Ref<T> CreateRef(Args&&... args) {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    template <typename T, typename F>
    constexpr Ref<T> StaticRefCast(Ref<F> from) {
        return std::static_pointer_cast<T>(from);
    }

    template <typename T, typename F>
    constexpr Ref<T> DynamicRefCast(Ref<F> from) {
        return std::dynamic_pointer_cast<T>(from);
    }

}    // namespace LM
