#pragma once

#include <array>
#include <glm/glm.hpp>

#include "Texture.hpp"

namespace hazel {

class SubTexture2D
{
public:
    SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max);
    static Ref<SubTexture2D> CreateFromCoords(const Ref<Texture2D>& texture,
                                              const glm::vec2& coords,
                                              const glm::vec2& cellSize,
                                              const glm::vec2& spriteSize = {1, 1});

    const Ref<Texture2D> GetTexture() const
    {
        return m_Texture;
    }
    const std::array<glm::vec2, 4> GetTexCoords() const
    {
        return m_TexCoords;
    }

private:
    Ref<Texture2D> m_Texture;

    std::array<glm::vec2, 4> m_TexCoords;
};
} // namespace hazel