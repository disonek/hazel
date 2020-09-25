#pragma once

#include <Hazel.hpp>

class Sandbox2D : public hazel::Layer
{
public:
    Sandbox2D();
    virtual ~Sandbox2D() override = default;

    void OnAttach() override;
    void OnDetach() override;
    void OnUpdate(hazel::Timestep ts) override;
    void OnImGuiRender() override;
    void OnEvent(hazel::Event& e) override;

private:
    hazel::OrthographicCameraController m_CameraController;

    // Temp
    hazel::Ref<hazel::VertexArray> m_SquareVA;
    hazel::Ref<hazel::Shader> m_FlatColorShader;

    hazel::Ref<hazel::Texture2D> m_CheckerboardTexture;

    glm::vec4 m_SquareColor = {0.2f, 0.3f, 0.8f, 1.0f};
};
