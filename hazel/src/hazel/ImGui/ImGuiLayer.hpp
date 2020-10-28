#pragma once

#include "../core/Layer.hpp"
#include "hazel/events/ApplicationEvent.hpp"
#include "hazel/events/KeyEvent.hpp"
#include "hazel/events/MouseEvent.hpp"

namespace hazel {

class ImGuiLayer : public Layer
{
public:
    ImGuiLayer();
    ~ImGuiLayer();
    void OnEvent(Event& e) override;
    void OnAttach() override;
    void OnDetach() override;

    void Begin();
    void End();
    void BlockEvents(bool block)
    {
        m_BlockEvents = block;
    }
    void SetDarkThemeColors();

private:
    bool m_BlockEvents = true;
};

} // namespace hazel
