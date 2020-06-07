#pragma once

#include "Core.hpp"

namespace hazel
{

class HAZEL_API Application
{
public:
	Application();
	virtual ~Application();

	void run();
};

//To be defined in client;
Application* CreateApplication();
}

