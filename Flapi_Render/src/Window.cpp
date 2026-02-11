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
		glfwSetWindowUserPointer(m_Window, this);
		glfwMakeContextCurrent(m_Window);

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
				Window* win = (Window*)glfwGetWindowUserPointer(window);
				win->m_EventsQueue.push_back(std::make_unique<EventWindowClose>());
			});

		glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int Width, int Height)
			{
				glViewport(0, 0, Width, Height);
				Window* win = (Window*)glfwGetWindowUserPointer(window);
				win->m_EventsQueue.push_back(std::make_unique<EventFramebufferSize>(Width, Height));
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
