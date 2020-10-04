#include "Buffer.hpp"

#include "hazel/renderer/Renderer.hpp"
#include "platform/OpenGL/OpenGLBuffer.hpp"

namespace hazel {

VertexBuffer::~VertexBuffer() = default;
IndexBuffer::~IndexBuffer() = default;

Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
{
    switch(Renderer::GetAPI())
    {
        case RendererAPI::API::None:
            HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLVertexBuffer>(size);
    }

    HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
{
    switch(Renderer::GetAPI())
    {
        case RendererAPI::API::None:
            HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLVertexBuffer>(vertices, size);
    }

    HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size)
{
    switch(Renderer::GetAPI())
    {
        case RendererAPI::API::None:
            HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLIndexBuffer>(indices, size);
    }

    HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}
} // namespace hazel