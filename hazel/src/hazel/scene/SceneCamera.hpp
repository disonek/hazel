#pragma once

#include "hazel/renderer/Camera.hpp"

namespace hazel {
class SceneCamera : public Camera
{
public:
    enum class ProjectionType
    {
        Perspective = 0,
        Orthographic = 1
    };

    SceneCamera();
    virtual ~SceneCamera() = default;

    void SetOrthographic(float size, float nearClip, float farClip);
    void SetPerscpective(float verticapFOV, float neraClip, float farClip);

    void SetViewportSize(uint32_t width, uint32_t height);

    float GetPerspectiveVerticalFOV() const;
    void SetPerspectiveVerticalFOV(float verticalFov);
    float GetPerspectiveNearClip() const;
    void SetPerspectiveNearClip(float nearClip);
    float GetPerspectiveFarClip() const;
    void SetPerspectiveFarClip(float farClip);

    float GetOrthographicSize() const;
    void SetOrthographicSize(float size);
    float GetOrthographicNearClip() const;
    void SetOrthographicNearClip(float nearClip);
    float GetOrthographicFarClip() const;
    void SetOrthographicFarClip(float farClip);

    ProjectionType GetProjectionType() const;
    void SetProjectionType(ProjectionType type);

private:
    void RecalculateProjection();

    ProjectionType m_ProjectionType = ProjectionType::Orthographic;

    float m_PerspectiveFOV = glm::radians(45.0F);
    float m_PerspectiveNear = 0.01F;
    float m_PerspectiveFar = 1000.0F;

    float m_OrthographicSize = 10.0f;
    float m_OrthographicNear = -1.0f;
    float m_OrthographicFar = 1.0f;
    float m_AspectRatio = 0.0f;
};
} // namespace hazel