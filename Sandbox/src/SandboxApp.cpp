#include <LostSouls.h>

class ExampleLayer : public LostSouls::Layer
{
public:
	ExampleLayer() :Layer("Example")
	{

	}

	void OnUpdate() override
	{
		LS_INFO("ExampleLayer::Update");
	}

	void OnEvent(LostSouls::Event& event) override
	{
		LS_TRACE("{0}", event);
	}
};

class Sandbox : public LostSouls::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox()
	{

	}
};

LostSouls::Application* LostSouls::CreateApplication()
{
	return new Sandbox();
}