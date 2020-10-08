#pragma once

#include "hazel/Core/Timestep.hpp"
#include "hazel/Events/ApplicationEvent.hpp"
#include "hazel/Events/MouseEvent.hpp"
#include "hazel/Renderer/OrthographicCamera.hpp"

namespace hazel {

struct OrthographicCameraBounds
{
    float Left, Right;
    float Bottom, Top;

    float GetWidth()
    {
        return Right - Left;
    }
    float GetHeight()
    {
        return Top - Bottom;
    }
};

class OrthographicCameraController
{
public:
    OrthographicCameraController(float aspectRatio, bool rotation = false);

    void OnUpdate(Timestep ts);
    void OnEvent(Event& e);

    OrthographicCamera& GetCamera()
    {
        return m_Camera;
    }
    const OrthographicCamera& GetCamera() const
    {
        return m_Camera;
    }
    float GetZoomLevel() const
    {
        return m_ZoomLevel;
    }
    void SetZoomLevel(float level)
    {
        m_ZoomLevel = level;
    }

    const OrthographicCameraBounds& GetBounds() const
    {
        return m_Bounds;
    }

private:
    bool OnMouseScrolled(MouseScrolledEvent& e);
    bool OnWindowResized(WindowResizeEvent& e);

    float m_AspectRatio;
    float m_ZoomLevel = 1.0f;
    OrthographicCameraBounds m_Bounds;
    OrthographicCamera m_Camera;

    bool m_Rotation;

    glm::vec3 m_CameraPosition = {0.0f, 0.0f, 0.0f};
    float m_CameraRotation = 0.0f;
    float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
};

} // namespace hazel
