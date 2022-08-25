#pragma once

#include "LostSouls/Renderer/GraphicsContext.h"

// Forward declaration to avoid having to import the class
struct GLFWwindow;

namespace LostSouls {

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual	void Init() override;
		virtual	void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}