#pragma once
#include "lspch.h"

#include "LostSouls/Core.h"
#include "LostSouls/Events/Event.h"

namespace LostSouls {

	struct WindowProps
	{
		std::string Title;
		unsigned int Width, Height;

		WindowProps(const std::string& title = "Lost Souls Engine",
					unsigned int width = 1280,
					unsigned int height = 720)
			: Title(title), Width(width), Height(height)
		{

		}
	};

	// Interface representing a desktop system based window
	class LOSTSOULS_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSynq(bool enabled) = 0;
		virtual bool IsVSynq() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};
}