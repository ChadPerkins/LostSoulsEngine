#pragma once
#include "Core.h"

#include "Window.h"
#include "LayerStack.h"

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

#include "LostSouls/Core/Timestep.h"

#include "LostSouls/ImGui/ImGuiLayer.h"

#include "LostSouls/Renderer/Buffer.h"
#include "LostSouls/Renderer/OrthographicCamera.h"
#include "LostSouls/Renderer/Shader.h"
#include "LostSouls/Renderer/VertexArray.h"

namespace LostSouls {
	
	class LOSTSOULS_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;

		bool m_Running = true;
		// Create the layer stack within the application to share its life span
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
		
	private:
		static Application* s_Instance;
	};

	// To be define in the client
	Application* CreateApplication();

}
