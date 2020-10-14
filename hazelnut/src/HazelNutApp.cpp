#include <Hazel.hpp>
#include <hazel/Core/EntryPoint.hpp>

#include "EditorLayer.hpp"

namespace hazel {

class HazelNutApp : public Application
{
public:
    HazelNutApp()
        : Application("HazelNut App")
    {
        PushLayer(new EditorLayer());
    }
    ~HazelNutApp() {}
};

Application* CreateApplication()
{
    return new HazelNutApp();
}

} // namespace hazel