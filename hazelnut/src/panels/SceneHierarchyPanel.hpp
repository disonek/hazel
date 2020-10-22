#pragma once

#include "hazel/core/Base.hpp"
#include "hazel/core/Log.hpp"
#include "hazel/scene/Entity.hpp"
#include "hazel/scene/Scene.hpp"

namespace hazel {
class SceneHierarchyPanel
{
public:
    SceneHierarchyPanel() = default;
    explicit SceneHierarchyPanel(const Ref<Scene>& context);

    void SetContext(const Ref<Scene>& context);

    void OnImGuiRender();

private:
    void DrawEntityNode(Entity entity);
    void DrawComponents(Entity entity);

    Ref<Scene> m_Context;
    Entity m_SelectionContext;
};
} // namespace hazel