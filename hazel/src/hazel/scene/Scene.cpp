
#include "Scene.hpp"

#include <glm/glm.hpp>

#include "Components.hpp"
#include "hazel/renderer/Renderer2D.hpp"

namespace hazel {

static void DoMath(const glm::mat4& transform) {}
static void OnTransformConstruct(entt::registry& regstry, entt::entity entity) {}

Scene::Scene()
{
    // entt::entity entity = m_Registry.create();
    // m_Registry.emplace<TransformComponent>(entity, glm::mat4(1.0f));

    // m_Registry.on_construct<TransformComponent>().connect<&OnTransformConstruct>();

    // if(m_Registry.has<TransformComponent>(entity))
    //     TransformComponent& transform = m_Registry.get<TransformComponent>(entity);

    // auto view = m_Registry.view<TransformComponent>();
    // for(auto entity : view)
    // {
    //     TransformComponent& transform = view.get<TransformComponent>(entity);
    // }

    // auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);

    // for(auto entity : group)
    // {
    //     auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
    // }
}

Scene::~Scene() {}

entt::entity Scene::CreateEntity()
{
    return m_Registry.create();
}

void Scene::OnUpdate(Timestep ts)
{
    auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
    for(auto& entity : group)
    {
        // auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
        auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

        Renderer2D::DrawQuad(transform, sprite.Color);
    }
}

} // namespace hazel