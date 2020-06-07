#pragma once

#ifdef HZ_PLATFORM_WINDOWS

extern hazel::Application* hazel::CreateApplication();

int main(int argc, char** argv)
{
	auto app = hazel::CreateApplication();
	app->run();
	delete app;
}
#endif
