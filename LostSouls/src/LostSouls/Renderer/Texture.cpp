#include "lspch.h"
#include "Texture.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGTexture.h"

namespace LostSouls {

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::none:		LS_CORE_ASSERT(false, "RendererAPI::none is currently not supported."); return nullptr;
		case RendererAPI::API::OpenGL:	return std::make_shared<OpenGLTexture2D>(path);
		}

		LS_CORE_ASSERT(false, "Unkown rendererAPI.");
		return nullptr;
	}
}