#pragma once
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "imgui.h"
#include "stb/stb_image.h"

#include "Flapi_Render.h"

class App
{
public:
	App();
	~App();
	void Init();
	void Run();
	void Close();
	void CheckEvents();
private:
	void Input();
private:
	float m_DeltaTime = 0.0f;
	float m_CurrentTime = glfwGetTime();
	float m_LastFrameTime = m_CurrentTime;
	
	bool m_Running = true;
	bool switchCursor = false;
	glm::vec2 CursorPreviousPosition = {0,0};

	std::unique_ptr<FL_Render::Window> m_Window;
	std::unordered_map<std::string, std::shared_ptr<FL_Render::Texture>> m_Textures;
	//FL_Render::CameraOrthographic m_OrthoCam;
	FL_Render::CameraPerspective m_PerspCam;
};
