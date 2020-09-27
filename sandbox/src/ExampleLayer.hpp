#pragma once

#include "Hazel.hpp"

class ExampleLayer : public hazel::Layer
{
public:
    ExampleLayer();
    virtual ~ExampleLayer() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;

    void OnUpdate(hazel::Timestep ts) override;
    virtual void OnImGuiRender() override;
    void OnEvent(hazel::Event& e) override;

private:
    hazel::ShaderLibrary m_ShaderLibrary;
    hazel::Ref<hazel::Shader> m_Shader;
    hazel::Ref<hazel::VertexArray> m_VertexArray;

    hazel::Ref<hazel::Shader> m_FlatColorShader;
    hazel::Ref<hazel::VertexArray> m_SquareVA;

    hazel::Ref<hazel::Texture2D> m_Texture, m_ChernoLogoTexture;

    hazel::OrthographicCameraController m_CameraController;
    glm::vec3 m_SquareColor = {0.2f, 0.3f, 0.8f};
};