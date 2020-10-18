#include "Renderer2D.hpp"

#include <algorithm>
#include <array>
#include <glm/gtc/matrix_transform.hpp>

#include "hazel/renderer/RenderCommand.hpp"
#include "hazel/renderer/Shader.hpp"
#include "hazel/renderer/VertexArray.hpp"

namespace hazel {

struct QuadVertex
{
    glm::vec3 Position;
    glm::vec4 Color;
    glm::vec2 TexCoord;
    float TexIndex;
    float TilingFactor;
};

struct Renderer2DData
{
    static const uint32_t MaxQuads = 20000;
    static const uint32_t MaxVertices = MaxQuads * 4;
    static const uint32_t MaxIndices = MaxQuads * 6;
    static const uint32_t MaxTextureSlots = 32; // TODO: RenderCaps

    Ref<VertexArray> QuadVertexArray;
    Ref<VertexBuffer> QuadVertexBuffer;
    Ref<Shader> TextureShader;
    Ref<Texture2D> WhiteTexture;

    uint32_t QuadIndexCount = 0;
    QuadVertex* QuadVertexBufferBase = nullptr;
    QuadVertex* QuadVertexBufferPtr = nullptr;

    std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
    uint32_t TextureSlotIndex = 1; // 0 = white texture
    Renderer2D::Statistics Stats;

    std::array<glm::vec4, 4> QuadVertexPositions;
    const std::array<glm::vec2, 4> textureCoords{
        glm::vec2{0.0f, 0.0f}, glm::vec2{1.0f, 0.0f}, glm::vec2{1.0f, 1.0f}, glm::vec2{0.0f, 1.0f}};
};

static Renderer2DData s_Data;

void Renderer2D::Init()
{
    HZ_PROFILE_FUNCTION();

    s_Data.QuadVertexArray = VertexArray::Create();

    s_Data.QuadVertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex));
    // clang-format off
    s_Data.QuadVertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" },
			{ ShaderDataType::Float2, "a_TexCoord" },
			{ ShaderDataType::Float, "a_TexIndex" },
			{ ShaderDataType::Float, "a_TilingFactor" }
			});
    // clang-format on
    s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

    s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];

    uint32_t* quadIndices = new uint32_t[s_Data.MaxIndices];

    uint32_t offset = 0;
    for(uint32_t i = 0; i < s_Data.MaxIndices; i += 6)
    {
        quadIndices[i + 0] = offset + 0;
        quadIndices[i + 1] = offset + 1;
        quadIndices[i + 2] = offset + 2;

        quadIndices[i + 3] = offset + 2;
        quadIndices[i + 4] = offset + 3;
        quadIndices[i + 5] = offset + 0;

        offset += 4;
    }

    Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, s_Data.MaxIndices);
    s_Data.QuadVertexArray->SetIndexBuffer(quadIB);
    delete[] quadIndices;

    s_Data.WhiteTexture = Texture2D::Create(1, 1);
    uint32_t whiteTextureData = 0xffffffff;
    s_Data.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

    int32_t samplers[s_Data.MaxTextureSlots];
    for(uint32_t i = 0; i < s_Data.MaxTextureSlots; i++)
        samplers[i] = i;

    s_Data.TextureShader = Shader::Create("assets/shaders/Texture.glsl");
    s_Data.TextureShader->Bind();
    s_Data.TextureShader->SetIntArray("u_Textures", samplers, s_Data.MaxTextureSlots);

    // Set all texture slots to 0
    s_Data.TextureSlots[0] = s_Data.WhiteTexture;

    s_Data.QuadVertexPositions[0] = {-0.5f, -0.5f, 0.0f, 1.0f};
    s_Data.QuadVertexPositions[1] = {0.5f, -0.5f, 0.0f, 1.0f};
    s_Data.QuadVertexPositions[2] = {0.5f, 0.5f, 0.0f, 1.0f};
    s_Data.QuadVertexPositions[3] = {-0.5f, 0.5f, 0.0f, 1.0f};
}

void Renderer2D::Shutdown()
{
    HZ_PROFILE_FUNCTION();

    delete[] s_Data.QuadVertexBufferBase;
}

void Renderer2D::BeginScene(const Camera& camera, const glm::mat4& transform)
{
    HZ_PROFILE_FUNCTION();

    glm::mat4 viewProj = camera.GetProjection() * glm::inverse(transform);

    s_Data.TextureShader->Bind();
    s_Data.TextureShader->SetMat4("u_ViewProjection", viewProj);

    s_Data.QuadIndexCount = 0;
    s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

    s_Data.TextureSlotIndex = 1;
}

void Renderer2D::BeginScene(const OrthographicCamera& camera)
{
    HZ_PROFILE_FUNCTION();

    s_Data.TextureShader->Bind();
    s_Data.TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

    s_Data.QuadIndexCount = 0;
    s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

    s_Data.TextureSlotIndex = 1;
}

void Renderer2D::EndScene()
{
    HZ_PROFILE_FUNCTION();

    uint32_t dataSize =
        static_cast<uint32_t>((uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase);
    s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, dataSize);

    Flush();
}

void Renderer2D::Flush()
{
    if(s_Data.QuadIndexCount == 0)
        return; // Nothing to draw

    // Bind textures
    for(uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
        s_Data.TextureSlots[i]->Bind(i);

    RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
    s_Data.Stats.DrawCalls++;
}

void Renderer2D::FlushAndReset()
{
    EndScene();

    s_Data.QuadIndexCount = 0;
    s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

    s_Data.TextureSlotIndex = 1;
}

void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
{
    DrawQuad({position.x, position.y, 0.0f}, size, color);
}

void Renderer2D::DrawQuad(const glm::vec2& position,
                          const glm::vec2& size,
                          const Ref<Texture2D>& texture,
                          float tilingFactor,
                          const glm::vec4& tintColor)
{
    DrawQuad({position.x, position.y, 0.0f}, size, texture, tilingFactor, tintColor);
} // namespace hazel

void Renderer2D::DrawQuad(const glm::vec2& position,
                          const glm::vec2& size,
                          const Ref<SubTexture2D>& subTexture,
                          float tilingFactor,
                          const glm::vec4& tintColor)
{
    DrawQuad({position.x, position.y, 0.0f}, size, subTexture, tilingFactor, tintColor);
}

void Renderer2D::DrawRotatedQuad(const glm::vec2& position,
                                 const glm::vec2& size,
                                 float rotation,
                                 const glm::vec4& color)
{
    DrawRotatedQuad({position.x, position.y, 0.0f}, size, rotation, color);
}

void Renderer2D::DrawRotatedQuad(const glm::vec2& position,
                                 const glm::vec2& size,
                                 float rotation,
                                 const Ref<Texture2D>& texture,
                                 float tilingFactor,
                                 const glm::vec4& tintColor)
{
    DrawRotatedQuad({position.x, position.y, 0.0f}, size, rotation, texture, tilingFactor, tintColor);
}

void Renderer2D::DrawRotatedQuad(const glm::vec2& position,
                                 const glm::vec2& size,
                                 float rotation,
                                 const Ref<SubTexture2D>& subTexture,
                                 float tilingFactor,
                                 const glm::vec4& tintColor)
{
    DrawRotatedQuad({position.x, position.y, 0.0f}, size, rotation, subTexture, tilingFactor, tintColor);
}

void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
{
    HZ_PROFILE_FUNCTION();

    glm::mat4 transform =
        glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

    DrawQuad(transform, color);
}

void Renderer2D::DrawQuad(const glm::vec3& position,
                          const glm::vec2& size,
                          const Ref<Texture2D>& texture,
                          float tilingFactor,
                          const glm::vec4& tintColor)
{
    HZ_PROFILE_FUNCTION();

    glm::mat4 transform =
        glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

    DrawQuad(transform, texture, tilingFactor);
}

void Renderer2D::DrawQuad(const glm::vec3& position,
                          const glm::vec2& size,
                          const Ref<SubTexture2D>& subTexture,
                          float tilingFactor,
                          const glm::vec4& tintColor)
{
    HZ_PROFILE_FUNCTION();

    glm::mat4 transform =
        glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

    DrawQuad(transform, subTexture, tilingFactor);
}

void Renderer2D::DrawRotatedQuad(const glm::vec3& position,
                                 const glm::vec2& size,
                                 float rotation,
                                 const glm::vec4& color)
{
    HZ_PROFILE_FUNCTION();

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
                          glm::rotate(glm::mat4(1.0f), rotation, {0.0f, 0.0f, 1.0f}) *
                          glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

    DrawQuad(transform, color);
}

void Renderer2D::DrawRotatedQuad(const glm::vec3& position,
                                 const glm::vec2& size,
                                 float rotation,
                                 const Ref<Texture2D>& texture,
                                 float tilingFactor,
                                 const glm::vec4& tintColor)
{
    HZ_PROFILE_FUNCTION();

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
                          glm::rotate(glm::mat4(1.0f), rotation, {0.0f, 0.0f, 1.0f}) *
                          glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

    DrawQuad(transform, texture, tilingFactor);
}

void Renderer2D::DrawRotatedQuad(const glm::vec3& position,
                                 const glm::vec2& size,
                                 float rotation,
                                 const Ref<SubTexture2D>& subTexture,
                                 float tilingFactor,
                                 const glm::vec4& tintColor)
{
    HZ_PROFILE_FUNCTION();

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
                          glm::rotate(glm::mat4(1.0f), rotation, {0.0f, 0.0f, 1.0f}) *
                          glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

    DrawQuad(transform, subTexture, tilingFactor);
}

void Renderer2D::DrawQuad(const glm::mat4& transform, const glm::vec4& color)
{
    HZ_PROFILE_FUNCTION();

    if(s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
        FlushAndReset();

    const float textureIndex = 0.0f; // White Texture
    const float tilingFactor = 1.0f;

    std::for_each(s_Data.QuadVertexPositions.cbegin(),
                  s_Data.QuadVertexPositions.cend(),
                  [&](glm::vec4 singleQuadVertexPosition) {
                      s_Data.QuadVertexBufferPtr->Position = transform * singleQuadVertexPosition;
                      s_Data.QuadVertexBufferPtr++;
                  });
    s_Data.QuadVertexBufferPtr -= s_Data.QuadVertexPositions.size();

    std::for_each(s_Data.textureCoords.cbegin(), s_Data.textureCoords.cend(), [&](glm::vec2 singleCoord) {
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TexCoord = singleCoord;
        s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
        s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
        s_Data.QuadVertexBufferPtr++;
    });

    s_Data.QuadIndexCount += 6;

    s_Data.Stats.QuadCount++;
}

void Renderer2D::DrawQuad(const glm::mat4& transform,
                          const Ref<Texture2D>& texture,
                          float tilingFactor,
                          const glm::vec4& tintColor)
{
    HZ_PROFILE_FUNCTION();

    if(s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
        FlushAndReset();

    float textureIndex = 0.0f;
    for(uint32_t i = 1; i < s_Data.TextureSlotIndex; i++)
    {
        if(*s_Data.TextureSlots[i].get() == *texture.get())
        {
            textureIndex = (float)i;
            break;
        }
    }

    if(textureIndex == 0.0f)
    {
        if(s_Data.TextureSlotIndex >= Renderer2DData::MaxTextureSlots)
            FlushAndReset();

        textureIndex = (float)s_Data.TextureSlotIndex;
        s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
        s_Data.TextureSlotIndex++;
    }

    std::for_each(s_Data.QuadVertexPositions.cbegin(),
                  s_Data.QuadVertexPositions.cend(),
                  [&](glm::vec4 singleQuadVertexPosition) {
                      s_Data.QuadVertexBufferPtr->Position = transform * singleQuadVertexPosition;
                      s_Data.QuadVertexBufferPtr++;
                  });

    s_Data.QuadVertexBufferPtr -= s_Data.QuadVertexPositions.size();

    std::for_each(s_Data.textureCoords.cbegin(), s_Data.textureCoords.cend(), [&](glm::vec2 singleCoord) {
        s_Data.QuadVertexBufferPtr->Color = tintColor;
        s_Data.QuadVertexBufferPtr->TexCoord = singleCoord;
        s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
        s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
        s_Data.QuadVertexBufferPtr++;
    });

    s_Data.QuadIndexCount += 6;

    s_Data.Stats.QuadCount++;
}

void Renderer2D::DrawQuad(const glm::mat4& transform,
                          const Ref<SubTexture2D>& subTexture,
                          float tilingFactor,
                          const glm::vec4& tintColor)
{
    HZ_PROFILE_FUNCTION();
    const std::array<glm::vec2, 4> subTextureCoords = subTexture->GetTexCoords();
    const Ref<Texture2D> texture = subTexture->GetTexture();

    if(s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
        FlushAndReset();

    float textureIndex = 0.0f;
    for(uint32_t i = 1; i < s_Data.TextureSlotIndex; i++)
    {
        if(*s_Data.TextureSlots[i].get() == *texture.get())
        {
            textureIndex = (float)i;
            break;
        }
    }

    if(textureIndex == 0.0f)
    {
        if(s_Data.TextureSlotIndex >= Renderer2DData::MaxTextureSlots)
            FlushAndReset();

        textureIndex = (float)s_Data.TextureSlotIndex;
        s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
        s_Data.TextureSlotIndex++;
    }

    std::for_each(s_Data.QuadVertexPositions.cbegin(),
                  s_Data.QuadVertexPositions.cend(),
                  [&](glm::vec4 singleQuadVertexPosition) {
                      s_Data.QuadVertexBufferPtr->Position = transform * singleQuadVertexPosition;
                      s_Data.QuadVertexBufferPtr++;
                  });
    s_Data.QuadVertexBufferPtr -= s_Data.QuadVertexPositions.size();

    std::for_each(subTextureCoords.cbegin(), subTextureCoords.cend(), [&](glm::vec2 singleCoord) {
        s_Data.QuadVertexBufferPtr->Color = tintColor;
        s_Data.QuadVertexBufferPtr->TexCoord = singleCoord;
        s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
        s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
        s_Data.QuadVertexBufferPtr++;
    });

    s_Data.QuadIndexCount += 6;

    s_Data.Stats.QuadCount++;
}

void Renderer2D::ResetStats()
{
    memset(&s_Data.Stats, 0, sizeof(Statistics));
}

Renderer2D::Statistics Renderer2D::GetStats()
{
    return s_Data.Stats;
}

} // namespace hazel