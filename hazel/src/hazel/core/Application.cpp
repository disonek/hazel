#include "Application.hpp"

#include <glfw/glfw3.h>

#include "hazel/core/Input.hpp"
#include "hazel/core/Log.hpp"
#include "hazel/renderer/Renderer.hpp"

namespace hazel {

Application* Application::s_Instance = nullptr;

Application::Application(const std::string& name)
{
    HZ_PROFILE_FUNCTION();

    HZ_CORE_ASSERT(!s_Instance, "Application already exists!");
    s_Instance = this;

    m_Window = Window::Create(WindowProps(name));
    m_Window->SetEventCallback(HZ_BIND_EVENT_FN(Application::OnEvent));

    Renderer::Init();

    m_ImGuiLayer = new ImGuiLayer();
    PushOverlay(m_ImGuiLayer);
}

Application::~Application()
{
    HZ_PROFILE_FUNCTION();

    Renderer::ShutDown();
}

void Application::OnEvent(Event& e)
{
    HZ_PROFILE_FUNCTION();

    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(HZ_BIND_EVENT_FN(Application::OnWnidowClose));
    dispatcher.Dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(Application::OnWindowResize));

    for(auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
    {
        (*it)->OnEvent(e);
        if(e.Handled)
            break;
    }
}

void Application::PushLayer(Layer* layer)
{
    HZ_PROFILE_FUNCTION();

    m_LayerStack.PushLayer(layer);
    layer->OnAttach();
}

void Application::PushOverlay(Layer* layer)
{
    HZ_PROFILE_FUNCTION();

    m_LayerStack.PushOverlay(layer);
    layer->OnAttach();
}

void Application::Close()
{
    m_Running = false;
}

void Application::run()
{
    HZ_PROFILE_FUNCTION();

    while(m_Running)
    {
        HZ_PROFILE_SCOPE("RunLoop");

        float time = (float)glfwGetTime();
        Timestep timestep = time - m_LastFrameTime;
        m_LastFrameTime = time;

        if(!m_Minimized)
        {
            {
                HZ_PROFILE_SCOPE("LayerStack OnUpdate");

                for(Layer* layer : m_LayerStack)
                    layer->OnUpdate(timestep);
            }

            m_ImGuiLayer->Begin();
            {
                HZ_PROFILE_SCOPE("LayerStack OnImGuiRender");

                for(Layer* layer : m_LayerStack)
                    layer->OnImGuiRender();
            }
            m_ImGuiLayer->End();
        }

        m_Window->OnUpdate();
    }
}

bool Application::OnWnidowClose(WindowCloseEvent& /*e*/)
{
    m_Running = false;
    return true;
}

bool Application::OnWindowResize(WindowResizeEvent& e)
{
    HZ_PROFILE_FUNCTION();

    if(e.GetWidth() == 0 || e.GetHeight() == 0)
    {
        m_Minimized = true;
        return false;
    }

    m_Minimized = false;
    Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

    return false;
}

} // namespace hazel
