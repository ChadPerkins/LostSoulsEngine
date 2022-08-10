#pragma once
#include "Event.h"

#include <sstream>

namespace LostSouls {
	class LOSTSOULS_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_Width(width), m_Height(height) {}

		// Getters for the width and height that the window was resized to
		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }

		// Print the window resize event along with the resized width and height
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		// Impliment the window resize class type and tell which category the information is stored
		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:
		unsigned int m_Width, m_Height;
	};

	class LOSTSOULS_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}

		// Impliment the window resize class type and tell which category the information is stored
		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class LOSTSOULS_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() {}

		// Impliment the app update class type and tell which category the information is stored
		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class LOSTSOULS_API AppTickEvent : public Event
	{
	public:
		AppTickEvent() {}

		// Impliment the app tick class type and tell which category the information is stored
		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class LOSTSOULS_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() {}

		// Impliment the app render class type and tell which category the information is stored
		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	
}