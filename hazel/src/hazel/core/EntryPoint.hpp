#pragma once

#ifdef HZ_PLATFORM_WINDOWS

extern hazel::Application* hazel::CreateApplication();

int main(int argc, char** argv)
{
    hazel::Log::init();
    HZ_CORE_WARN("coreLoger init");
    HZ_ERROR("coreLoger init");
    auto app = hazel::CreateApplication();
    app->run();
    delete app;
}
#endif
