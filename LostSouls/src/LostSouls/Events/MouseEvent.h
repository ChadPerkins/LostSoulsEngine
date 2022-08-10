#pragma once
#include "Event.h"

#include <sstream>

namespace LostSouls {

	class LOSTSOULS_API MouseMovedEvent : Event
	{
	public:
		MouseMovedEvent(float x, float y) : m_MouseX(x), m_MouseY(y) {}
		
		// Getters for the mouse's x and y positions
		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }

		// Print the mouse moved event with it's quardinates
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		// Impliment the mouse moved class type and tell which category the information is stored
		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	protected:
		float m_MouseX, m_MouseY;
	};

	class LOSTSOULS_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: m_XOffset(yOffset), m_YOffset(yOffset) {}

		// Getters for the offset of the x and y positions of the scroll
		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }

		// Print the scroll event and its offset positions
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
			return ss.str();
		}

		// Impliment the mouse scrolled class type and tell which category the information is stored
		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_XOffset, m_YOffset;
	};

	class LOSTSOULS_API MouseButtonEvent : public Event
	{
	public:
		// Getter to get the mouse button
		inline int GetMouseButton() const { return m_Button; }

		// Tell which category the information is stored
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	protected:
		MouseButtonEvent(int button) : m_Button(button) {}
		int m_Button;
	};

	class LOSTSOULS_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

		// Print the mouse button pressed event and the button pressed
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}

		// Implement the mouse button pressed class type
		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class LOSTSOULS_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		// Store the current release button
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) {}

		// Print the mouse button released event and the button released
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}

		// Implement the mouse button released class type
		EVENT_CLASS_TYPE(MouseButtonReleased)
	};


}