#include "hzpch.hpp"

#include "Application.hpp"
#include "hazel/events/ApplicationEvent.hpp"
#include "hazel/Log.hpp"

namespace hazel
{
 

Application::Application()
{
}

Application::~Application()
{
}

void Application::run()
{
	WindowResizeEvent e(1280, 720);
	if (e.IsInCategory(EventCategoryApplication))
	{
		HZ_TRACE(e);
	}
	if (e.IsInCategory(EventCategoryInput))
	{
		HZ_TRACE(e);
	}

	while (true)
	{
	}
}

}
