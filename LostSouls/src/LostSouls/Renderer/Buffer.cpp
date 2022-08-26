#include "lspch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace LostSouls {

	///////////////////////////////////
	//		   Vertex Buffer		//
	//////////////////////////////////

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::none:		LS_CORE_ASSERT(false, "RendererAPI::none is currently not supported."); return nullptr;
		case RendererAPI::OpenGL:	return new OpenGLVertexBuffer(vertices, size);
		}
		
		LS_CORE_ASSERT(false, "Unkown rendererAPI.");
		return nullptr;
	}

	///////////////////////////////////
	//		   Index Buffer			//
	//////////////////////////////////

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::none:		LS_CORE_ASSERT(false, "RendererAPI::none is currently not supported."); return nullptr;
		case RendererAPI::OpenGL:	return new OpenGLIndexBuffer(indices, size);
		}

		LS_CORE_ASSERT(false, "Unkown rendererAPI.");
		return nullptr;
	}

}