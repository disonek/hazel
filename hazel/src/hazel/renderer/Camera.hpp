#pragma once

#include <glm/glm.hpp>

namespace hazel {

class Camera
{
public:
    virtual ~Camera() = default;
    Camera() = default;
    Camera(const glm::mat4& projection)
        : m_Projection(projection)
    {
    }

    const glm::mat4& GetProjection() const
    {
        return m_Projection;
    }

protected:
    glm::mat4 m_Projection = glm::mat4(1.0f);
};

} // namespace hazel