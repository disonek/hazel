#pragma once

#include <memory>

#ifdef HZ_PLATFORM_WINDOWS
#else
#error Hazel only supports Windows!
#endif

#ifdef HZ_ENABLE_ASSERTS
#define HZ_ASSERT(x, ...)                                   \
    {                                                       \
        if(!(x))                                            \
        {                                                   \
            HZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
            __debugbreak();                                 \
        }                                                   \
    }
#define HZ_CORE_ASSERT(x, ...)                                   \
    {                                                            \
        if(!(x))                                                 \
        {                                                        \
            HZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
            __debugbreak();                                      \
        }                                                        \
    }
#else
#define HZ_ASSERT(x, ...)
#define HZ_CORE_ASSERT(x, ...)
#endif

template <typename T>
constexpr auto BIT(T x)
{
    return (1 << x);
}

#define HZ_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace hazel {

template <typename T>
using Scope = std::unique_ptr<T>;
template <typename T, typename... Args>
constexpr Scope<T> CreateScope(Args&&... args)
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T>
using Ref = std::shared_ptr<T>;
template <typename T, typename... Args>
constexpr Ref<T> CreateRef(Args&&... args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}
} // namespace hazel
