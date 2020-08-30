#include "RenderCommand.hpp"

#include "platform/OpenGL/OpenGLRendererAPI.hpp"

namespace hazel {

	Scope<RendererAPI> RenderCommand::s_RendererAPI = CreateScope<OpenGLRendererAPI>();
}
