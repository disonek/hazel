#pragma once

#include "Core.hpp"
#include "events/Event.hpp"
#include "Window.hpp"
#include "hazel/events/ApplicationEvent.hpp"

namespace hazel
{

class HAZEL_API Application
{
public:
	Application();
	virtual ~Application();

	void OnEvent(Event& e);

	void run();
private:
	bool OnWnidowClose(WindowCloseEvent& e);

	std::unique_ptr<Window> m_Window;
	bool m_Running = true;
};

//To be defined in client;
Application* CreateApplication();
}

