#include <cstdint>

namespace FL_Render
{
	enum class EventType
	{
		WindowClose, FramebufferSize
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
}