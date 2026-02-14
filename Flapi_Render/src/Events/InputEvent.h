#pragma once
#include "Event.h"

namespace FL_Render
{
	class EventKey : public Event
	{
	public:
		EventKey(int key, int scancode, int action, int mods)
			:Event(EventType::Key), m_Key(key), m_Scancode(scancode), m_Action(action), m_Mods(mods)
		{
		}

		int32_t GetKey() const { return m_Key; }
		int32_t GetScancode() const { return m_Scancode; }
		int32_t GetAction() const { return m_Action; }
		int32_t GetMods() const { return m_Mods; }
	private:
		int m_Key, m_Scancode, m_Action, m_Mods;
	};

	class EventMouseButton : public Event
	{
	public:
		EventMouseButton(int button, int action, int mods)
			:Event(EventType::MouseButton), m_Button(button), m_Action(action), m_Mods(mods)
		{
		}

		int32_t GetKey() const { return m_Button; }
		int32_t GetAction() const { return m_Action; }
		int32_t GetMods() const { return m_Mods; }
	private:
		int m_Button, m_Action, m_Mods;
	};

	class EventCursorPos : public Event
	{
	public:
		EventCursorPos(double xpos, double ypos)
			:Event(EventType::CursorPos), m_Xpos(xpos), m_Ypos(ypos)
		{
		}

		int32_t GetXpos() const { return m_Xpos; }
		int32_t GetYpos() const { return m_Ypos; }
	private:
		double m_Xpos, m_Ypos;
	};

	class EventScroll : public Event
	{
	public:
		EventScroll(double xoffset, double yoffset)
			:Event(EventType::Scroll), m_Xoffset(xoffset), m_Yoffset(yoffset)
		{
		}

		int32_t GetXoffset() const { return m_Xoffset; }
		int32_t GetYoffset() const { return m_Yoffset; }
	private:
		double m_Xoffset, m_Yoffset;
	};

	class EventChar : public Event
	{
	public:
		EventChar(unsigned int codepoint)
			:Event(EventType::Char), m_Codepoint(codepoint)
		{
		}

		uint32_t GetCodepoint() const { return m_Codepoint; }
	private:
		unsigned int m_Codepoint;
	};
}