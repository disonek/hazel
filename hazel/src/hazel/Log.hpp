#pragma once

#include "Core.hpp"
#include "spdlog/spdlog.h"
#include <memory>

namespace hazel
{ 

class HAZEL_API Log
{
public:
	static void init();
	inline static std::shared_ptr<spdlog::logger>& getCoreLogger();
	inline static std::shared_ptr<spdlog::logger>& getClientLogger();

private:
	static std::shared_ptr<spdlog::logger> coreLogger;
	static std::shared_ptr<spdlog::logger> clientLogger;
};

}

#define HZ_CORE_TRACE(...)  ::hazel::Log::getCoreLogger()->trace(__VA_ARGS__)
#define HZ_CORE_INFO(...)	::hazel::Log::getCoreLogger()->info(__VA_ARGS__)
#define HZ_CORE_WARN(...)	::hazel::Log::getCoreLogger()->warn(__VA_ARGS__)
#define HZ_CORE_ERROR(...)  ::hazel::Log::getCoreLogger()->error(__VA_ARGS__)
#define HZ_CORE_FATAL(...)  ::hazel::Log::getCoreLogger()->trace(__VA_ARGS__)

#define HZ_CLIENT_TRACE(...)  ::hazel::Log::getClientLogger()->trace(__VA_ARGS__)
#define HZ_CLIENT_INFO(...)	  ::hazel::Log::getClientLogger()->info(__VA_ARGS__)
#define HZ_CLIENT_WARN(...)	  ::hazel::Log::getClientLogger()->warn(__VA_ARGS__)
#define HZ_CLIENT_ERROR(...)  ::hazel::Log::getClientLogger()->error(__VA_ARGS__)
#define HZ_CLIENT_FATAL(...)  ::hazel::Log::getClientLogger()->trace(__VA_ARGS__)