#include "Log.hpp"

namespace hazel
{
	std::shared_ptr<spdlog::logger> Log::coreLogger;
	std::shared_ptr<spdlog::logger> Log::clietLogger;

	void Log::init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
	}

	inline std::shared_ptr<spdlog::logger>& Log::getCoreLogger()
	{
		return coreLogger;
	}
	
	inline std::shared_ptr<spdlog::logger>& Log::getClietLogger()
	{
		return clietLogger;
	}
}
