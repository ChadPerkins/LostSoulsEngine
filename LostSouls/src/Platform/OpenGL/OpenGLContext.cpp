#include "lspch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace LostSouls {

	LostSouls::OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		LS_CORE_ASSERT(windowHandle, "Window handle is null.")
	}
	
	void LostSouls::OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		LS_CORE_ASSERT(status, "Failed to initialize Glad.");
	}
	
	void LostSouls::OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}
