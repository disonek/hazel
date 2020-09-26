#include "hazel/renderer/GraphicsContext.hpp"

#include "hazel/renderer/Renderer.hpp"
#include "platform/OpenGL/OpenGLContext.hpp"

namespace hazel {

Scope<GraphicsContext> GraphicsContext::Create(void* window)
{
    switch(Renderer::GetAPI())
    {
        case RendererAPI::API::None:
            HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
    }

    HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

} // namespace hazel