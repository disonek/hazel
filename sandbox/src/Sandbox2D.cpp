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

    m_Particle.ColorBegin = {254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f};
    m_Particle.ColorEnd = {254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f};
    m_Particle.SizeBegin = 0.5f, m_Particle.SizeVariation = 0.3f, m_Particle.SizeEnd = 0.0f;
    m_Particle.LifeTime = 5.0f;
    m_Particle.Velocity = {0.0f, 0.0f};
    m_Particle.VelocityVariation = {3.0f, 1.0f};
    m_Particle.Position = {0.0f, 0.0f};
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
        hazel::Renderer2D::DrawRotatedQuad({1.0f, 0.0f}, {0.8f, 0.8f}, glm::radians(-45.0f), {0.8f, 0.2f, 0.3f, 1.0f});
        hazel::Renderer2D::DrawQuad({-1.0f, 0.0f}, {0.8f, 0.8f}, {0.8f, 0.2f, 0.3f, 1.0f});
        hazel::Renderer2D::DrawQuad({0.5f, -0.5f}, {2.5f, 0.75f}, m_SquareColor);
        hazel::Renderer2D::DrawQuad({0.0f, 0.0f, -0.1f}, {20.0f, 20.0f}, m_CheckerboardTexture, 10.0f);
        hazel::Renderer2D::DrawRotatedQuad(
            {-2.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, glm::radians(rotation), m_CheckerboardTexture, 20.0f);
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

        if(hazel::Input::IsMouseButtonPressed(HZ_MOUSE_BUTTON_LEFT))
        {
            auto [x, y] = hazel::Input::GetMousePosition();
            auto width = hazel::Application::Get().GetWindow().GetWidth();
            auto height = hazel::Application::Get().GetWindow().GetHeight();

            auto bounds = m_CameraController.GetBounds();
            auto pos = m_CameraController.GetCamera().GetPosition();
            x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
            y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();
            m_Particle.Position = {x + pos.x, y + pos.y};
            for(int i = 0; i < 50; i++)
                m_ParticleSystem.Emit(m_Particle);
        }

        m_ParticleSystem.OnUpdate(ts);
        m_ParticleSystem.OnRender(m_CameraController.GetCamera());
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
