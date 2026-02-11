#pragma once
#include <memory>
#include <vector>
#include <string>

#include "GLFW/glfw3.h"
#include "glad/glad.h"

#include "Events/Event.h"

namespace FL_Render
{
	class Window
	{
	public:
		Window(uint32_t width, uint32_t height, const std::string& title);
		~Window();

		void Update();
		GLFWwindow*& GetNativeWindow() { return m_Window; }

		uint32_t GetWidth() const { return m_WinData.Width; }
		uint32_t GetHeight() const { return m_WinData.Height; }

		std::vector<std::unique_ptr<Event>>& GetEventsQueue() { return m_EventsQueue; }
	private:
		void CreateWindow(uint32_t width, uint32_t height, const std::string& title);
	private:
		GLFWwindow* m_Window;

		struct WinData
		{
			uint32_t Width;
			uint32_t Height;
			std::string Title;
		};
		WinData m_WinData;

		std::vector<std::unique_ptr<Event>> m_EventsQueue;
	};
}