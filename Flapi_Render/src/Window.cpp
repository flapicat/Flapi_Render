#include "Window.h"
#include <iostream>

#include "Events/InputEvent.h"
#include "Events/WindowEvents.h"

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

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
				Window* win = (Window*)glfwGetWindowUserPointer(window);
				win->m_EventsQueue.push_back(std::make_unique<EventReSize>(width, height));
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
				Window* win = (Window*)glfwGetWindowUserPointer(window);
				win->m_EventsQueue.push_back(std::make_unique<EventKey>(key, scancode, action, mods));
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
				Window* win = (Window*)glfwGetWindowUserPointer(window);
				win->m_EventsQueue.push_back(std::make_unique<EventMouseButton>(button, action, mods));
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos) {
				Window* win = (Window*)glfwGetWindowUserPointer(window);
				win->m_EventsQueue.push_back(std::make_unique<EventCursorPos>(xpos, ypos));
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset) {
				Window* win = (Window*)glfwGetWindowUserPointer(window);
				win->m_EventsQueue.push_back(std::make_unique<EventScroll>(xoffset, yoffset));
			});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int codepoint) {
				Window* win = (Window*)glfwGetWindowUserPointer(window);
				win->m_EventsQueue.push_back(std::make_unique<EventChar>(codepoint));
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
