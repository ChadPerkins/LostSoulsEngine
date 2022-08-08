#pragma once

#ifdef LS_PLATFORM_WINDOWS

extern LostSouls::Application* LostSouls::CreateApplication();

int main(int argc, char** argv)
{
	auto app = LostSouls::CreateApplication();
	app->Run();
	delete app;
}
#endif