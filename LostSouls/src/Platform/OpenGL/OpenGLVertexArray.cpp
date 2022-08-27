#include "lspch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace LostSouls {

	static GLenum ShaderDataTypeTOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case LostSouls::ShaderDataType::None:		return GL_FLOAT;
		case LostSouls::ShaderDataType::Float:		return GL_FLOAT;
		case LostSouls::ShaderDataType::Int:		return GL_INT;
		case LostSouls::ShaderDataType::Vec2:		return GL_FLOAT;
		case LostSouls::ShaderDataType::Vec3:		return GL_FLOAT;
		case LostSouls::ShaderDataType::Vec4:		return GL_FLOAT;
		case LostSouls::ShaderDataType::Mat3:		return GL_FLOAT;
		case LostSouls::ShaderDataType::Mat4:		return GL_FLOAT;
		case LostSouls::ShaderDataType::Bool:		return GL_BOOL;
		}

		LS_CORE_ASSERT(false, "Unknown ShaderDataType.");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		LS_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex vuffer has no layout.");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeTOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			index++;
		}
		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

}