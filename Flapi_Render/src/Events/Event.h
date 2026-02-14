#pragma once
#include <cstdint>

namespace FL_Render
{
	enum class EventType
	{
		WindowClose, FramebufferSize, ReSize,
		Key, MouseButton, CursorPos, Scroll, Char
	};

	class Event
	{
	public:
		Event(EventType type)
			:m_Type(type)
		{
		}
		virtual ~Event() = default;

		void SetEventType(EventType type) { m_Type = type; }
		EventType GetEventType() { return m_Type; }
	private:
		EventType m_Type;
	};
}