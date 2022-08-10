#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Log.h"

namespace LostSouls {
	LostSouls::Application::Application()
	{
	}

	LostSouls::Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1200, 720);
		LS_TRACE(e);

		while (true);
	}

}
