#include "hzpch.hpp"

#include "Log.hpp"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace hazel
{
	std::shared_ptr<spdlog::logger> Log::coreLogger;
	std::shared_ptr<spdlog::logger> Log::clientLogger;

	void Log::init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		coreLogger = spdlog::stdout_color_mt("HAZEL");
		coreLogger->set_level(spdlog::level::trace);

		clientLogger = spdlog::stdout_color_mt("APP");
		clientLogger->set_level(spdlog::level::trace);
	}

	inline std::shared_ptr<spdlog::logger>& Log::getCoreLogger()
	{
		return coreLogger;
	}
	
	inline std::shared_ptr<spdlog::logger>& Log::getClientLogger()
	{
		return clientLogger;
	}
}