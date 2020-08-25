#include "RenderCommand.hpp"

#include "platform/OpenGL/OpenGLRendererAPI.hpp"

namespace hazel {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}
