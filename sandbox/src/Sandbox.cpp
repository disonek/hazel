#include "Hazel.hpp"
#include "spdlog\spdlog.h"

class Sandbox : public hazel::Application
{
public:
	Sandbox()
	{
	}
	~Sandbox()
	{
	}

};

hazel::Application* hazel::CreateApplication()
{
	return new Sandbox();
}