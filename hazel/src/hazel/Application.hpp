#pragma once

#include "Core.hpp"
#include "Window.hpp"
#include "hazel/events/ApplicationEvent.hpp"
#include "hazel/events/Event.hpp"
#include "hazel/LayerStack.hpp"

#include "hazel/core/Timestep.hpp"

#include "hazel/ImGui/ImGuiLayer.hpp"


namespace hazel
{

class Application
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
	bool OnWindowResize(WindowResizeEvent& e);

	Scope<Window> m_Window;
	ImGuiLayer* m_ImGuiLayer;
	bool m_Running = true;
	bool m_Minimized = false;
	LayerStack m_LayerStack;
	float m_LastFrameTime = 0.0f;

private:
	static Application* s_Instance;
};

//To be defined in client;
Application* CreateApplication();
}

