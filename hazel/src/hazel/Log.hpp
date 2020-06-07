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
	inline static std::shared_ptr<spdlog::logger>& getClietLogger();

private:
	static std::shared_ptr<spdlog::logger> coreLogger;
	static std::shared_ptr<spdlog::logger> clietLogger;
};

}