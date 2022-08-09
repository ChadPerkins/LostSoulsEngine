#pragma once
#include "Core.h"

namespace LostSouls {
	
	class LOSTSOULS_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be define in the client
	Application* CreateApplication();

}
