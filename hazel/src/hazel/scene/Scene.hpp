#pragma once

#include "entt/entt.hpp"
#include "hazel/core/Timestep.hpp"

namespace hazel {

class Scene
{
public:
    Scene();
    ~Scene();

    entt::entity CreateEntity();

    // TEMP
    entt::registry& Reg()
    {
        return m_Registry;
    }

    void OnUpdate(Timestep ts);

private:
    entt::registry m_Registry;
};

} // namespace hazel