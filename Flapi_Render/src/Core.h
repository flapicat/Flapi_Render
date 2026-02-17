#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace FL_Render
{
	static GLFWwindow* s_CoreGLFWwindow;
	static void SetGLFWWindow(GLFWwindow*& window) { s_CoreGLFWwindow = window; }

	enum class CursorMode {
		CURSOR_NORMAL,
		CURSOR_HIDDEN,
		CURSOR_DISABLED
	};

	static void SetCursorMode(CursorMode mode)
	{
		int glfwMode = GLFW_CURSOR_NORMAL;
		switch (mode)
		{
		case FL_Render::CursorMode::CURSOR_NORMAL:	glfwMode = GLFW_CURSOR_NORMAL;	break;
		case FL_Render::CursorMode::CURSOR_HIDDEN:	 glfwMode = GLFW_CURSOR_HIDDEN;	break;
		case FL_Render::CursorMode::CURSOR_DISABLED: glfwMode = GLFW_CURSOR_DISABLED;	break;
		}

		glfwSetInputMode(s_CoreGLFWwindow, GLFW_CURSOR, glfwMode);
	}

	static void SetCursorPos(const glm::vec2& pos) { glfwSetCursorPos(s_CoreGLFWwindow, pos.x, pos.y); }
	static void SetCursorPos(int X, int Y) { glfwSetCursorPos(s_CoreGLFWwindow, X, Y); }
	static glm::vec2 GetCursorPos() {
		int width, height;
		glfwGetWindowSize(s_CoreGLFWwindow, &width, &height);
		return glm::vec2(width, height);
	}

}