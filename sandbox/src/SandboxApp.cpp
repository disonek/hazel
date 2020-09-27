#include <Hazel.hpp>
#include <hazel/Core/EntryPoint.hpp>
#include <platform/OpenGL/OpenGLShader.hpp>

#include "ExampleLayer.hpp"
#include "Sandbox2D.hpp"

class Sandbox : public hazel::Application
{
public:
    Sandbox()
        : Application()
    {
        // PushLayer(new ExampleLayer());
        PushLayer(new Sandbox2D());
    }
    ~Sandbox() {}
};

hazel::Application* hazel::CreateApplication()
{
    return new Sandbox();
}