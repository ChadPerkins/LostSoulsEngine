#include <LostSouls.h>

class Sandbox : public LostSouls::Application
{
public:
	Sandbox()
	{

	}
	~Sandbox()
	{

	}
};

LostSouls::Application* LostSouls::CreateApplication()
{
	return new Sandbox();
}