#pragma once

#include <vector>

#include "Layer.hpp"
#include "hazel/core/Core.hpp"


namespace hazel {

class LayerStack
{
public:
    LayerStack();
    ~LayerStack();

    void PushLayer(Layer* layer);
    void PushOverlay(Layer* overlay);
    void PopLayer(Layer* layer);
    void PopOverlay(Layer* overlay);

    // TO DO add cbegin and cend
    std::vector<Layer*>::iterator begin()
    {
        return m_Layers.begin();
    }
    std::vector<Layer*>::iterator end()
    {
        return m_Layers.end();
    }

private:
    std::vector<Layer*> m_Layers;
    unsigned int m_LayerInsertIndex = 0;
};

} // namespace hazel
