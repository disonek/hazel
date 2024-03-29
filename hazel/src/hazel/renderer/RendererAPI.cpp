#include "hazel/renderer/RendererAPI.hpp"

#include "platform/OpenGL/OpenGLRendererAPI.hpp"

namespace hazel {

Scope<RendererAPI> RendererAPI::Create()
{
    switch(s_API)
    {
        case RendererAPI::API::None:
            HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateScope<OpenGLRendererAPI>();
    }

    HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

} // namespace hazel