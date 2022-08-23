#include <LostSouls.h>

class ExampleLayer : public LostSouls::Layer
{
public:
	ExampleLayer() :Layer("Example")
	{

	}

	void OnUpdate() override
	{
		if(LostSouls::Input::IsKeyPressed(LS_KEY_TAB))
			LS_TRACE("Tab key is pressed...");
	}

	void OnEvent(LostSouls::Event& event) override
	{
		if (event.GetEventType() == LostSouls::EventType::KeyPressed)
		{
			LostSouls::KeyPressedEvent& e = (LostSouls::KeyPressedEvent&)event;
			LS_TRACE("{0}", (char)e.GetKeyCode());
		}
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