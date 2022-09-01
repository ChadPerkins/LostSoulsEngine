#pragma once
#include "LostSouls/Renderer/RendererAPI.h"

namespace LostSouls {

	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndex(const Ref<VertexArray>& vertexArray) override;

	};
}