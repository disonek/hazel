#pragma once

#include "Core.hpp"
#include "Window.hpp"
#include "hazel/events/ApplicationEvent.hpp"
#include "hazel/events/Event.hpp"
#include "hazel/LayerStack.hpp"



namespace hazel
{

class HAZEL_API Application
{
public:
	Application();
	virtual ~Application();

	void run();

	void OnEvent(Event& e);

	void PushLayer(Layer* layer);
	void PushOverlay(Layer* layer);

	inline static Application& Get() { return *s_Instance; }
	inline Window& GetWindow() { return *m_Window; }
private:
	bool OnWnidowClose(WindowCloseEvent& e);

	std::unique_ptr<Window> m_Window;
	bool m_Running = true;
	LayerStack m_LayerStack;

	static Application* s_Instance;
};

//To be defined in client;
Application* CreateApplication();
}

