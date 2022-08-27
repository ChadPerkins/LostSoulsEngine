#include "lspch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace LostSouls {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}