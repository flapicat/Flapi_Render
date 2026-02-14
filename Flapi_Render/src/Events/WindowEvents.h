#pragma once
#include "Event.h"

namespace FL_Render
{
	class EventWindowClose : public Event
	{
	public:
		EventWindowClose()
			:Event(EventType::WindowClose)
		{
		}
	};

	class EventFramebufferSize : public Event
	{
	public:
		EventFramebufferSize(int Width, int Height)
			:Event(EventType::FramebufferSize), m_Width(Width), m_Height(Height)
		{
		}

		uint32_t GetWidth() const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }
	private:
		int m_Width, m_Height;
	};

	class EventReSize : public Event
	{
	public:
		EventReSize(int Width, int Height)
			:Event(EventType::ReSize), m_Width(Width), m_Height(Height)
		{
		}

		uint32_t GetWidth() const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }
	private:
		int m_Width, m_Height;
	};
}