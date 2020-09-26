#pragma once

#include "hazel/core/Core.hpp"

#ifdef HZ_PLATFORM_WINDOWS
extern hazel::Application* hazel::CreateApplication();

int main(int /*argc*/, char** /*argv*/)
{
    hazel::Log::init();
    HZ_PROFILE_BEGIN_SESSION("Startup", "HazelProfile-Startup.json");
    auto app = hazel::CreateApplication();
    HZ_PROFILE_END_SESSION();

    HZ_PROFILE_BEGIN_SESSION("Runtime", "HazelProfile-Runtime.json");
    app->run();
    HZ_PROFILE_END_SESSION();

    HZ_PROFILE_BEGIN_SESSION("Startup", "HazelProfile-Shutdown.json");
    delete app;
    HZ_PROFILE_END_SESSION();
}
#endif
