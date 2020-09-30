#include "Window.hpp"

#ifdef HZ_PLATFORM_WINDOWS
#include "platform/windows/WindowsWindow.hpp"
#endif

namespace hazel {

Scope<Window> Window::Create(const WindowProps& props)
{
#ifdef HZ_PLATFORM_WINDOWS
    return CreateScope<WindowsWindow>(props);
#else
    HZ_CORE_ASSERT(false, "Unknown platform!");
    return nullptr;
#endif
}

} // namespace hazel