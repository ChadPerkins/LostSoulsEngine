#pragma once

#include "LostSouls/Core.h"
#include <string>
#include <functional>

namespace LostSouls {
	/* Events in the Lost Souls engine are currently set up as blocking, meaning that when an
	   event occurs, it immediately gets dispatched and must be dealt with right then and there.
	   For the future, a better strategy might be to buffer events in an event bus and process
	   them during the "event" part of the update stage	*/

	enum class EventType
	{
		none = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		none = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput       = BIT(1),
		EventCategoryKeyboard    = BIT(2),
		EventCategoryMouse       = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
							   virtual EventType GetEventType() const override { return GetStaticType();  }\
							   virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class LOSTSOULS_API Event
	{
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}

	protected:
		bool m_Handled = false;
	};

	class EventDispatcher
	{
		template<typename T>
		// Create a function that takes in an event type and returns a bool
		using EventFn = std::_Function_args<bool(T&)>;
	public:
		EventDispatcher(Event& event) : m_Event(event)
		{

		}

		// A function that takes in an event and returns weather the event and function type match
		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (mEvent.GetEventType() == T::GetStaticType())
			{
				// If the event matches the type then call the function with that event
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};

	// An output strin operatior used to print out events
	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}

}