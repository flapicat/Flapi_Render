#pragma once
#include <string>

#include "GLFW/glfw3.h"
#include "glad/glad.h"

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
	};

}