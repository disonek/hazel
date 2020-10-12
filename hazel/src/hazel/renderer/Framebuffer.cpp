#include "Framebuffer.hpp"

#include "hazel/Renderer/Renderer.hpp"
#include "platform/OpenGL/OpenGLFramebuffer.hpp"

namespace hazel {

Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
{
    switch(Renderer::GetAPI())
    {
        case RendererAPI::API::None:
            HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLFramebuffer>(spec);
    }

    HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

} // namespace hazel