#pragma once

#include "Base.hpp"
#include "spdlog/fmt/ostr.h"
#include "spdlog/spdlog.h"

namespace hazel {

class Log
{
public:
    static void init();
    static std::shared_ptr<spdlog::logger>& getCoreLogger()
    {
        return coreLogger;
    }
    static std::shared_ptr<spdlog::logger>& getClientLogger()
    {
        return clientLogger;
    };

private:
    static std::shared_ptr<spdlog::logger> coreLogger;
    static std::shared_ptr<spdlog::logger> clientLogger;
};

} // namespace hazel

#define HZ_CORE_TRACE(...) ::hazel::Log::getCoreLogger()->trace(__VA_ARGS__)
#define HZ_CORE_INFO(...) ::hazel::Log::getCoreLogger()->info(__VA_ARGS__)
#define HZ_CORE_WARN(...) ::hazel::Log::getCoreLogger()->warn(__VA_ARGS__)
#define HZ_CORE_ERROR(...) ::hazel::Log::getCoreLogger()->error(__VA_ARGS__)
#define HZ_CORE_CRITICAL(...) ::hazel::Log::getCoreLogger()->critical(__VA_ARGS__)

#define HZ_TRACE(...) ::hazel::Log::getClientLogger()->trace(__VA_ARGS__)
#define HZ_INFO(...) ::hazel::Log::getClientLogger()->info(__VA_ARGS__)
#define HZ_WARN(...) ::hazel::Log::getClientLogger()->warn(__VA_ARGS__)
#define HZ_ERROR(...) ::hazel::Log::getClientLogger()->error(__VA_ARGS__)
#define HZ_CRITICAL(...) ::hazel::Log::getClientLogger()->critical(__VA_ARGS__)