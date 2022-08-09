#pragma once

#ifdef LS_PLATFORM_WINDOWS

extern LostSouls::Application* LostSouls::CreateApplication();

int main(int argc, char** argv)
{
	int a = 5;
	LostSouls::Log::Init();
	LS_CORE_WARN("Initialized log!");
	LS_INFO("Hello Var={0}", a);

	auto app = LostSouls::CreateApplication();
	app->Run();
	delete app;
}
#endif