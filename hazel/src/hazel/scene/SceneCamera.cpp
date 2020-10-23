#include "SceneCamera.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace hazel {
SceneCamera::SceneCamera()
{
    RecalculateProjection();
}

void SceneCamera::SetOrthographic(float size, float nearClip, float farClip)
{
    m_ProjectionType = ProjectionType::Orthographic;
    m_OrthographicSize = size;
    m_OrthographicNear = nearClip;
    m_OrthographicFar = farClip;
    RecalculateProjection();
}

void SceneCamera::SetPerscpective(float verticalFOV, float nearClip, float farClip)
{
    m_ProjectionType = ProjectionType::Perspective;
    m_PerspectiveFOV = verticalFOV;
    m_PerspectiveNear = nearClip;
    m_PerspectiveFar = farClip;
    RecalculateProjection();
}

void SceneCamera::SetViewportSize(uint32_t width, uint32_t height)
{
    m_AspectRatio = static_cast<float>(width) / static_cast<float>(height);
    RecalculateProjection();
}

float SceneCamera::GetPerspectiveVerticalFOV() const
{
    return m_PerspectiveFOV;
}
void SceneCamera::SetPerspectiveVerticalFOV(float verticalFov)
{
    m_PerspectiveFOV = verticalFov;
    RecalculateProjection();
}
float SceneCamera::GetPerspectiveNearClip() const
{
    return m_PerspectiveNear;
}
void SceneCamera::SetPerspectiveNearClip(float nearClip)
{
    m_PerspectiveNear = nearClip;
    RecalculateProjection();
}
float SceneCamera::GetPerspectiveFarClip() const
{
    return m_PerspectiveFar;
}
void SceneCamera::SetPerspectiveFarClip(float farClip)
{
    m_PerspectiveFar = farClip;
    RecalculateProjection();
}

float SceneCamera::GetOrthographicSize() const
{
    return m_OrthographicSize;
}
void SceneCamera::SetOrthographicSize(float size)
{
    m_OrthographicSize = size;
    RecalculateProjection();
}
float SceneCamera::GetOrthographicNearClip() const
{
    return m_OrthographicNear;
}
void SceneCamera::SetOrthographicNearClip(float nearClip)
{
    m_OrthographicNear = nearClip;
    RecalculateProjection();
}
float SceneCamera::GetOrthographicFarClip() const
{
    return m_OrthographicFar;
}
void SceneCamera::SetOrthographicFarClip(float farClip)
{
    m_OrthographicFar = farClip;
    RecalculateProjection();
}

SceneCamera::ProjectionType SceneCamera::GetProjectionType() const
{
    return m_ProjectionType;
}

void SceneCamera::SetProjectionType(ProjectionType type)
{
    m_ProjectionType = type;
    RecalculateProjection();
}

void SceneCamera::RecalculateProjection()
{
    if(m_ProjectionType == ProjectionType::Perspective)
    {
        m_Projection = glm::perspective(m_PerspectiveFOV, m_AspectRatio, m_PerspectiveNear, m_PerspectiveFar);
    }
    else
    {
        float orthoLeft = -m_OrthographicSize * m_AspectRatio * 0.5f;
        float orthoRight = m_OrthographicSize * m_AspectRatio * 0.5f;
        float orthoBottom = -m_OrthographicSize * 0.5f;
        float orthoTop = m_OrthographicSize * 0.5f;

        m_Projection = glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop, m_OrthographicNear, m_OrthographicFar);
    };
}

} // namespace hazel