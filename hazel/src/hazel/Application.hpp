#pragma once

#include "Core.hpp"
#include "Window.hpp"
#include "hazel/events/ApplicationEvent.hpp"
#include "hazel/events/Event.hpp"
#include "hazel/LayerStack.hpp"

#include "hazel/ImGui/ImGuiLayer.hpp"

#include "hazel/renderer/Shader.hpp"
#include "hazel/renderer/Buffer.hpp"
#include "hazel/renderer/VertexArray.hpp"
#include "hazel/renderer/OrthographicCamera.hpp"

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
	ImGuiLayer* m_ImGuiLayer;
	bool m_Running = true;
	LayerStack m_LayerStack;

	std::shared_ptr<Shader> m_Shader;
	std::shared_ptr<VertexArray> m_VertexArray;

	std::shared_ptr<Shader> m_BlueShader;
	std::shared_ptr<VertexArray> m_SquareVA;

	OrthographicCamera m_Camera;
private:
	static Application* s_Instance;
};

//To be defined in client;
Application* CreateApplication();
}

