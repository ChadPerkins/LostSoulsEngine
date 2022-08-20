#pragma once
#include "Core.h"

#include "Window.h"
#include "LayerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

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
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;

		bool m_Running = true;
		// Create the layer stack within the application to share its life span
		LayerStack m_LayerStack;
	};

	// To be define in the client
	Application* CreateApplication();

}
