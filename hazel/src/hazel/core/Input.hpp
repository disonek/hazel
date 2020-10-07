#pragma once

#include "hazel/core/Core.hpp"
#include "hazel/core/KeyCodes.hpp"
#include "hazel/core/MouseCodes.hpp"

namespace hazel {

class Input
{
public:
    virtual ~Input() = default;
    static bool IsKeyPressed(KeyCode keycode)
    {
        return s_Instance->IsKeyPressedImpl(keycode);
    }

    static bool IsMouseButtonPressed(MouseCode button)
    {
        return s_Instance->IsMouseButtonPressedImpl(button);
    }
    static std::pair<float, float> GetMousePosition()
    {
        return s_Instance->GetMousePositionImpl();
    }
    static float GetMouseX()
    {
        return s_Instance->GetMouseXImpl();
    }
    static float GetMouseY()
    {
        return s_Instance->GetMouseYImpl();
    }

    static Scope<Input> Create();

protected:
    virtual bool IsKeyPressedImpl(KeyCode keycode) = 0;

    virtual bool IsMouseButtonPressedImpl(MouseCode button) = 0;
    virtual std::pair<float, float> GetMousePositionImpl() = 0;
    virtual float GetMouseXImpl() = 0;
    virtual float GetMouseYImpl() = 0;

private:
    static Scope<Input> s_Instance;
};

} // namespace hazel
