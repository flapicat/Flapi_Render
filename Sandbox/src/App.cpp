#include "App.h"
#include <filesystem>

App::App()
{

}

App::~App()
{

}

void App::Init()
{
	m_Window.reset(new FL_Render::Window(1920, 1080, "Sandbox"));

	float AspectRatio = (float)m_Window->GetWidth() / (float)m_Window->GetHeight();
	m_OrthoCam = FL_Render::CameraOrthographic(-AspectRatio, AspectRatio, -1.0f, 1.0f);
	
	FL_Render::Renderer::Init();
	FL_Render::Renderer::SetClearColor({0.1f,0.1f,0.1f,1.0f});

	//TEXTURES
	std::vector<std::string> TexturesPaths = {
		"Assets/Textures/checkerboard.png",
		"Assets/Textures/container.png",
		"Assets/Textures/awesomeface.png"
	};

	for (int i = 0; i < TexturesPaths.size(); i++)
	{
		std::shared_ptr<FL_Render::Texture> Texture;
		Texture.reset(new FL_Render::Texture(TexturesPaths[i]));
		std::filesystem::path path(TexturesPaths[i]);
		m_Textures[path.filename().string()] = Texture;
	}
}

void App::Run()
{
	static std::vector<FL_Render::Vertex> vertices = {		 
		{{-0.5f, -0.5f, 0.0f},	{0.0f, 0.0f},	0.0f},
		{{0.5f, -0.5f, 0.0f},	{1.0f, 0.0f},	0.0f},
		{{0.5f,  0.5f, 0.0f},	{1.0f, 1.0f},	0.0f},
		{{-0.5f,  0.5f, 0.0f},	{0.0f, 1.0f},	0.0f}
	};
	static std::vector<uint32_t> indices = {
		0,1,2,2,3,0
	};
	 
	while (m_Running)
	{
		m_CurrentTime = glfwGetTime();
		m_DeltaTime = m_CurrentTime - m_LastFrameTime;
		m_LastFrameTime = m_CurrentTime;
		Input();

		FL_Render::Renderer::BeginScene(m_OrthoCam.GetCamera());

		for (size_t x = 0; x < 100; x++)
		{
			for (size_t y = 0; y < 100; y++)
			{
				FL_Render::Renderer::SubmitData(vertices, indices, m_Textures["checkerboard.png"], glm::vec3(x, y, 0.0f), glm::vec3(0.9f));
			}
		}

		FL_Render::Renderer::EndScene();

		m_Window->Update(); 
	}
}

void App::Close()
{
	FL_Render::Renderer::Terminate();
}

void App::Input()
{
	if (glfwGetKey(m_Window->GetNativeWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		m_Running = false;
	}

	/*
	 * CAMERA MOVEMENT 
	 */
	glm::vec3 camPos = m_OrthoCam.GetPosition();
	float camSpeed = 0.7;
	if (glfwGetKey(m_Window->GetNativeWindow(), GLFW_KEY_A) == GLFW_PRESS)
	{
		camPos.x -= 1 * camSpeed * m_DeltaTime;
	}
	if (glfwGetKey(m_Window->GetNativeWindow(), GLFW_KEY_D) == GLFW_PRESS)
	{
		camPos.x += 1 * camSpeed * m_DeltaTime;
	}
	if (glfwGetKey(m_Window->GetNativeWindow(), GLFW_KEY_W) == GLFW_PRESS)
	{
		camPos.y += 1 * camSpeed * m_DeltaTime;
	}
	if (glfwGetKey(m_Window->GetNativeWindow(), GLFW_KEY_S) == GLFW_PRESS)
	{
		camPos.y -= 1 * camSpeed * m_DeltaTime;
	}
	m_OrthoCam.SetPosition(camPos);
}