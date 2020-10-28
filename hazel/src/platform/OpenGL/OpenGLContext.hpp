#pragma once

#include "hazel/renderer/GraphicsContext.hpp"

struct GLFWwindow;

namespace hazel {

class OpenGLContext : public GraphicsContext
{
public:
    OpenGLContext(GLFWwindow* windowHandle);

    virtual void Init() override;
    virtual void SwapBuffers() override;

private:
    GLFWwindow* m_WindowHandle;
};

} // namespace hazel
