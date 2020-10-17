#pragma once

#include "hazel/core/Base.hpp"
#include "hazel/core/KeyCodes.hpp"
#include "hazel/core/MouseCodes.hpp"

namespace hazel {

class Input
{
public:
    static bool IsKeyPressed(KeyCode key);

    static bool IsMouseButtonPressed(MouseCode button);
    static std::pair<float, float> GetMousePosition();
    static float GetMouseX();
    static float GetMouseY();
};

} // namespace hazel
