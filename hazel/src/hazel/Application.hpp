#pragma once

#include "Core.hpp"
#include "events/Event.hpp"
#include "Window.hpp"

namespace hazel
{

class HAZEL_API Application
{
public:
	Application();
	virtual ~Application();

	void run();
private:
	std::unique_ptr<Window> m_Window;
	bool m_Running = true;
};

//To be defined in client;
Application* CreateApplication();
}

