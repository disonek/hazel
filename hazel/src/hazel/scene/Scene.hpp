#pragma once

#include "entt/entt.hpp"
#include "hazel/core/Timestep.hpp"

namespace hazel {
class Entity;

class Scene
{
public:
    Scene();
    ~Scene();

    entt::entity CreateEntity();
    Entity CreateEntity(const std::string& name = std::string());

    void OnUpdate(Timestep ts);

private:
    entt::registry m_Registry;

    friend class Entity;
};

} // namespace hazel