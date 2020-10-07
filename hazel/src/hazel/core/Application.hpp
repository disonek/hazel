#pragma once

#include "hazel/ImGui/ImGuiLayer.hpp"
#include "hazel/core/Core.hpp"
#include "hazel/core/LayerStack.hpp"
#include "hazel/core/Timestep.hpp"
#include "hazel/core/Window.hpp"
#include "hazel/events/ApplicationEvent.hpp"
#include "hazel/events/Event.hpp"

int main(int argc, char** argv);
namespace hazel {

class Application
{
public:
    Application();
    virtual ~Application();

    void OnEvent(Event& e);

    void PushLayer(Layer* layer);
    void PushOverlay(Layer* layer);

    static Application& Get()
    {
        return *s_Instance;
    }
    Window& GetWindow()
    {
        return *m_Window;
    }

private:
    void run();
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
    friend int ::main(int argc, char** argv);
};

// To be defined in client;
Application* CreateApplication();
} // namespace hazel
