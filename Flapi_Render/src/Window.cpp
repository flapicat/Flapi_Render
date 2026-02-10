#include "Window.h"
#include <iostream>

namespace FL_Render
{
	Window::Window(uint32_t width, uint32_t height, const std::string& title)
	{
		CreateWindow(width, height, title);
	}

	Window::~Window()
	{
	}

	void Window::Update()
	{
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}

	void Window::CreateWindow(uint32_t width, uint32_t height, const std::string& title)
	{
		m_WinData.Width = width;
		m_WinData.Height = height;
		m_WinData.Title = title;

		if (!glfwInit())
		{
			std::cout << "ERROR::GLFW NOT INITIALIZED!\n";
			exit(0);
		}

		m_Window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		if (!m_Window)
		{
			std::cout << "ERROR::WINDOW NOT CREATED!\n";
			exit(0);
		}
		glfwMakeContextCurrent(m_Window);
		glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int Width, int Height)
			{
				glViewport(0, 0, Width, Height);
			});

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "ERROR::GLAD NOT INITIALIZED!\n";
			exit(0);
		}
		GLenum error = glGetError();
		if (error != GL_NO_ERROR) {
			std::cout << "OpenGL Error: " << error << std::endl;
		}
	}
}