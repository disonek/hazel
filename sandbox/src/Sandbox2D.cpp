#include "Sandbox2D.hpp"

#include <functional>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D")
    , m_CameraController{1280.0f / 720.0f, true}
    , m_SquareColor{0.2f, 0.3f, 0.8f, 1.0f}
{
}

void Sandbox2D::OnAttach()
{
    HZ_PROFILE_FUNCTION();

    m_CheckerboardTexture = hazel::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
    HZ_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(hazel::Timestep ts)
{
    HZ_PROFILE_FUNCTION();

    // Update
    m_CameraController.OnUpdate(ts);

    // Render
    hazel::Renderer2D::ResetStats();
    {
        HZ_PROFILE_SCOPE("Renderer Prep");
        hazel::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
        hazel::RenderCommand::Clear();
    }

    {
        static float rotation = 0.0f;
        rotation += ts * 50.0f;

        HZ_PROFILE_SCOPE("Renderer Draw");
        hazel::Renderer2D::BeginScene(m_CameraController.GetCamera());
        hazel::Renderer2D::DrawRotatedQuad({1.0f, 0.0f}, {0.8f, 0.8f}, -45.0f, {0.8f, 0.2f, 0.3f, 1.0f});
        hazel::Renderer2D::DrawQuad({-1.0f, 0.0f}, {0.8f, 0.8f}, {0.8f, 0.2f, 0.3f, 1.0f});
        hazel::Renderer2D::DrawQuad({0.5f, -0.5f}, {2.5f, 0.75f}, m_SquareColor);
        hazel::Renderer2D::DrawQuad({0.0f, 0.0f, -0.1f}, {20.0f, 20.0f}, m_CheckerboardTexture, 10.0f);
        hazel::Renderer2D::DrawRotatedQuad({-2.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, rotation, m_CheckerboardTexture, 20.0f);
        hazel::Renderer2D::EndScene();

        hazel::Renderer2D::BeginScene(m_CameraController.GetCamera());
        for(float y = -5.0f; y < 5.0f; y += 0.5f)
        {
            for(float x = -5.0f; x < 5.0f; x += 0.5f)
            {
                glm::vec4 color = {(x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f};
                hazel::Renderer2D::DrawQuad({x, y}, {0.45f, 0.45f}, color);
            }
        }
        hazel::Renderer2D::EndScene();
    }
}

void Sandbox2D::OnImGuiRender()
{
    HZ_PROFILE_FUNCTION();

    ImGui::Begin("Settings");

    auto stats = hazel::Renderer2D::GetStats();
    ImGui::Text("Renderer2D Stats:");
    ImGui::Text("Draw Calls: %d", stats.DrawCalls);
    ImGui::Text("Quads: %d", stats.QuadCount);
    ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
    ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

    ImGui::End();
}

void Sandbox2D::OnEvent(hazel::Event& e)
{
    m_CameraController.OnEvent(e);
}
