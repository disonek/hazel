#include "Entity.hpp"

namespace hazel {

Entity::Entity(entt::entity handle, Scene* scene)
    : m_EntityHandle(handle)
    , m_Scene(scene)
{
}

} // namespace hazel