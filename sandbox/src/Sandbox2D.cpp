#include "Sandbox2D.hpp"

#include <chrono>
#include <functional>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"

class Timer
{
public:
    Timer(const char* name, std::function<void(Sandbox2D::ProfileResult)> func)
        : m_Name(name)
        , m_Func(func)
        , m_Stopped(false)
    {
        m_StartTimepoint = std::chrono::high_resolution_clock::now();
    }

    ~Timer()
    {
        if(!m_Stopped)
        {
            Stop();
        }
    }

    void Stop()
    {
        auto endTimepoint = std::chrono::high_resolution_clock::now();

        long long start =
            std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
        long long end =
            std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

        m_Stopped = true;

        float duration = (end - start) * 0.001f;
        m_Func({m_Name, duration});
    }

private:
    const char* m_Name;
    std::function<void(Sandbox2D::ProfileResult)> m_Func;
    std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
    bool m_Stopped;
};

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D")
    , m_CameraController(1280.0f / 720.0f, true)
{
}

void Sandbox2D::OnAttach()
{
    m_CheckerboardTexture = hazel::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach() {}

void Sandbox2D::OnUpdate(hazel::Timestep ts)
{
    Timer timer1("Sandbox2D::OnUpdate",
                 [&](ProfileResult profileResult) { m_ProfileResults.push_back(profileResult); });
    // Update
    {
        Timer timer2("CameraController::OnUpdate",
                     [&](ProfileResult profileResult) { m_ProfileResults.push_back(profileResult); });
        m_CameraController.OnUpdate(ts);
    }

    // Render
    {
        Timer timer3("Renderer Prepare",
                     [&](ProfileResult profileResult) { m_ProfileResults.push_back(profileResult); });
        hazel::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
        hazel::RenderCommand::Clear();
    }

    {
        Timer timer4("Renderer Draw", [&](ProfileResult profileResult) { m_ProfileResults.push_back(profileResult); });
        hazel::Renderer2D::BeginScene(m_CameraController.GetCamera());
        hazel::Renderer2D::DrawQuad({-1.0f, 0.0f}, {0.8f, 0.8f}, {0.8f, 0.2f, 0.3f, 1.0f});
        hazel::Renderer2D::DrawQuad({0.5f, -0.5f}, {0.5f, 0.75f}, {0.2f, 0.3f, 0.8f, 1.0f});
        hazel::Renderer2D::DrawQuad({0.0f, 0.0f, -0.1f}, {10.0f, 10.0f}, m_CheckerboardTexture);
        hazel::Renderer2D::EndScene();
    }
}

void Sandbox2D::OnImGuiRender()
{
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

    for(auto& result : m_ProfileResults)
    {
        char label[50];
        strcpy(label, "%.3fms ");
        strcat(label, result.Name);
        ImGui::Text(label, result.Time);
    }

    m_ProfileResults.clear();
    ImGui::End();
}

void Sandbox2D::OnEvent(hazel::Event& e)
{
    m_CameraController.OnEvent(e);
}
