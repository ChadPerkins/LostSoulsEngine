#pragma once
#include "Event.h"

namespace LostSouls {

	class LOSTSOULS_API KeyEvent : public Event
	{
	public:
		// Getter to get the keyboard key that was pressed
		inline int GetKeyCode() const { return m_KeyCode; }

		// Tell which category the information is stored
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		// Constructor to store which keyborad key was pressed
		KeyEvent(int keycode) : m_KeyCode(keycode) {}

		int m_KeyCode;
	};

	class LOSTSOULS_API KeyPressedEvent : public KeyEvent
	{
	public:
		// Constructor to store which keyborad key was pressed
		// and how many times it should repeat
		KeyPressedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		// Getter for the repeat count of the button press
		inline int GetRepeatCount() const { return m_RepeatCount; }

		// Print the keyboard key pressed event with the key and repeat ammount
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		// Implement the key pressed class type
		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_RepeatCount;
	};

	class LOSTSOULS_API KeyReleasedEvent : public KeyEvent
	{
	public:
		// Constructor to store which keyborad key was released
		KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}

		// Print the keyboard key released event with the key
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		// Implement the key released class type
		EVENT_CLASS_TYPE(KeyReleased)
	};


	class LOSTSOULS_API KeyTypedEvent : public KeyEvent
	{
	public:
		// Constructor to store which key was pressed
		KeyTypedEvent(int keycode)
			: KeyEvent(keycode) {}


		// Print the keyboard key typed event with the key
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}

		// Implement the key typed class type
		EVENT_CLASS_TYPE(KeyTyped)
	};
}