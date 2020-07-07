#include "Hazel.hpp"

#include "imgui/imgui.h"

class ExampleLayer : public hazel::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		if (hazel::Input::IsKeyPressed(HZ_KEY_TAB))
			HZ_TRACE("Tab key is pressed (poll)!");
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}


	void OnEvent(hazel::Event& event) override
	{
		if (event.GetEventType() == hazel::EventType::KeyPressed)
		{
			hazel::KeyPressedEvent& e = (hazel::KeyPressedEvent&)event;
			if (e.GetKeyCode() == HZ_KEY_TAB)
				HZ_TRACE("Tab key is pressed (event)!");
			HZ_TRACE("{0}", (char)e.GetKeyCode());
		}
	}

};

class Sandbox : public hazel::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox()
	{
	}

};

hazel::Application* hazel::CreateApplication()
{
	return new Sandbox();
}