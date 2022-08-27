#include "lspch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace LostSouls {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::none:		LS_CORE_ASSERT(false, "RendererAPI::none is currently not supported."); return nullptr;
		case RendererAPI::OpenGL:	return new OpenGLVertexArray();
		}

		LS_CORE_ASSERT(false, "Unkown rendererAPI.");
		return nullptr;
	}
}