#pragma once

#include <Hazel.hpp>

#include "ParticleSystem.hpp"

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
    void testFunction(hazel::Timestep ts);
    void emitParticle(hazel::Timestep ts);
    void renderMap(hazel::Timestep ts);
    hazel::OrthographicCameraController m_CameraController;

    // Temp
    hazel::Ref<hazel::VertexArray> m_SquareVA;
    hazel::Ref<hazel::Shader> m_FlatColorShader;

    hazel::Ref<hazel::Texture2D> m_CheckerboardTexture;
    hazel::Ref<hazel::Texture2D> m_ChernoLogo;
    hazel::Ref<hazel::Texture2D> m_SpriteSheet;
    hazel::Ref<hazel::SubTexture2D> m_TextureStairs;
    hazel::Ref<hazel::SubTexture2D> m_TextureBarrel;
    hazel::Ref<hazel::SubTexture2D> m_TextureTree;

    hazel::Ref<hazel::SubTexture2D> m_TextureGrass;
    hazel::Ref<hazel::SubTexture2D> m_TextureWater;
    hazel::Ref<hazel::SubTexture2D> m_TextureDirt;

    glm::vec4 m_SquareColor = {0.2f, 0.3f, 0.8f, 1.0f};

    ParticleProps m_Particle;
    ParticleSystem m_ParticleSystem;
};
