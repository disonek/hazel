#pragma once

#include "hazel/renderer/OrthographicCamera.hpp"
#include "hazel/renderer/RenderCommand.hpp"
#include "hazel/renderer/Shader.hpp"

namespace hazel {

class Renderer
{
public:
    static void Init();
    static void ShutDown();
    static void OnWindowResize(uint32_t width, uint32_t height);
    static void BeginScene(OrthographicCamera& camera);
    static void EndScene();

    static void Submit(Ref<Shader>& shader,
                       const Ref<VertexArray>& vertexArray,
                       const glm::mat4& transform = glm::mat4(1.0f));

    static RendererAPI::API GetAPI()
    {
        return RendererAPI::GetAPI();
    }

private:
    struct SceneData
    {
        glm::mat4 ViewProjectionMatrix;
    };

    static Scope<SceneData> s_SceneData;
};

} // namespace hazel
