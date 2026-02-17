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
	FL_Render::SetGLFWWindow(m_Window->GetNativeWindow());

	float AspectRatio = (float)m_Window->GetWidth() / (float)m_Window->GetHeight();
	//m_OrthoCam = FL_Render::CameraOrthographic(-AspectRatio, AspectRatio, -1.0f, 1.0f);
	m_PerspCam = FL_Render::CameraPerspective(45.0f, AspectRatio);

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

	m_PerspCam.SetPosition({0.0f,0.0f,5.0f});
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

		//FL_Render::Renderer::BeginScene(m_OrthoCam.GetCamera());

		FL_Render::Renderer::BeginScene(m_PerspCam.GetCamera());

		FL_Render::Renderer::SubmitData(vertices, indices, m_Textures["checkerboard.png"], glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f));
		FL_Render::Renderer::SubmitData(vertices, indices, m_Textures["container.png"], glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(1.0f));
		FL_Render::Renderer::SubmitData(vertices, indices, m_Textures["awesomeface.png"], glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f));

		FL_Render::Renderer::EndScene();

		m_Window->Update();
		CheckEvents();
	}
}

void App::Close()
{
	FL_Render::Renderer::Terminate();
}

void App::CheckEvents()
{
	auto& events = m_Window->GetEventsQueue();

	while (!events.empty())
	{
		auto& event = events.back();

		if (event->GetEventType() == FL_Render::EventType::WindowClose)
		{
			m_Running = false;
		}
		else if (event->GetEventType() == FL_Render::EventType::FramebufferSize)
		{
			auto* resizeEvent = static_cast<FL_Render::EventFramebufferSize*>(event.get());
		}
		else if (event->GetEventType() == FL_Render::EventType::ReSize)
		{
			const FL_Render::EventReSize* resizeEvent = static_cast<const FL_Render::EventReSize*>(event.get());
		}
		else if (event->GetEventType() == FL_Render::EventType::Key)
		{
			const FL_Render::EventKey* keyEvent = static_cast<const FL_Render::EventKey*>(event.get());
		}
		else if (event->GetEventType() == FL_Render::EventType::MouseButton)
		{
			const FL_Render::EventMouseButton* mouseButtonEvent = static_cast<const FL_Render::EventMouseButton*>(event.get());
		}
		else if (event->GetEventType() == FL_Render::EventType::CursorPos)
		{
			const FL_Render::EventCursorPos* cursorPosEvent = static_cast<const FL_Render::EventCursorPos*>(event.get());
			if(switchCursor) m_PerspCam.OnMouseMoved(cursorPosEvent->GetXpos(), cursorPosEvent->GetYpos());
		}
		else if (event->GetEventType() == FL_Render::EventType::Scroll)
		{
			const FL_Render::EventScroll* scrollEvent = static_cast<const FL_Render::EventScroll*>(event.get());
		}
		else if (event->GetEventType() == FL_Render::EventType::Char)
		{
			const FL_Render::EventChar* charEvent = static_cast<const FL_Render::EventChar*>(event.get());
		}

		events.pop_back();
	}
}

void App::Input()
{
	/*
	* ----- CORE -----
	*/
	if (glfwGetKey(m_Window->GetNativeWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		m_Running = false;
	}

	/* 
	* SWITCHING CURSOR MODE 
	* PREVENTING CAMERA FLICKS
	*/
	static bool tabWasPressed = false;
	bool tabPressed = glfwGetKey(m_Window->GetNativeWindow(), GLFW_KEY_TAB) == GLFW_PRESS;
	if (tabPressed && !tabWasPressed)
	{
		if (switchCursor) {
			FL_Render::SetCursorMode(FL_Render::CursorMode::CURSOR_NORMAL);
		}
		else {
			FL_Render::SetCursorMode(FL_Render::CursorMode::CURSOR_DISABLED);

			m_PerspCam.GetLastMouseX() = m_Window->GetWidth() / 2;
			m_PerspCam.GetLastMouseY() = m_Window->GetHeight() / 2;
			FL_Render::SetCursorPos(m_PerspCam.GetLastMouseX(), m_PerspCam.GetLastMouseY());
		}							
		switchCursor = !switchCursor;
		m_PerspCam.GetFirstMouse() = true;
	}
	tabWasPressed = tabPressed; 

	/*
	 * ----- ORTHO CAMERA MOVEMENT -----
	 */
	//glm::vec3 camPos = m_OrthoCam.GetPosition();
	//float camSpeed = 0.7;
	//if (glfwGetKey(m_Window->GetNativeWindow(), GLFW_KEY_A) == GLFW_PRESS)
	//{
	//	camPos.x -= 1 * camSpeed * m_DeltaTime;
	//}
	//if (glfwGetKey(m_Window->GetNativeWindow(), GLFW_KEY_D) == GLFW_PRESS)
	//{
	//	camPos.x += 1 * camSpeed * m_DeltaTime;
	//}
	//if (glfwGetKey(m_Window->GetNativeWindow(), GLFW_KEY_W) == GLFW_PRESS)
	//{
	//	camPos.y += 1 * camSpeed * m_DeltaTime;
	//}
	//if (glfwGetKey(m_Window->GetNativeWindow(), GLFW_KEY_S) == GLFW_PRESS)
	//{
	//	camPos.y -= 1 * camSpeed * m_DeltaTime;
	//}
	//m_OrthoCam.SetPosition(camPos);

	/*
	 * ----- PERSPECTIVE CAMERA MOVEMENT -----
	 */
	glm::vec3 camPos = m_PerspCam.GetPosition();
	float camSpeed = 1.0f;
	if (glfwGetKey(m_Window->GetNativeWindow(), GLFW_KEY_A) == GLFW_PRESS)
	{
		camPos -= m_PerspCam.GetRight() * camSpeed * m_DeltaTime;
	}
	if (glfwGetKey(m_Window->GetNativeWindow(), GLFW_KEY_D) == GLFW_PRESS)
	{
		camPos += m_PerspCam.GetRight() * camSpeed * m_DeltaTime;
	}
	if (glfwGetKey(m_Window->GetNativeWindow(), GLFW_KEY_W) == GLFW_PRESS)
	{
		camPos += m_PerspCam.GetFront() * camSpeed * m_DeltaTime;
	}
	if (glfwGetKey(m_Window->GetNativeWindow(), GLFW_KEY_S) == GLFW_PRESS)
	{
		camPos -= m_PerspCam.GetFront() * camSpeed * m_DeltaTime;
	}
	if (glfwGetKey(m_Window->GetNativeWindow(), GLFW_KEY_Q) == GLFW_PRESS)
	{
		camPos -= m_PerspCam.GetUp() * camSpeed * m_DeltaTime;
	}
	if (glfwGetKey(m_Window->GetNativeWindow(), GLFW_KEY_E) == GLFW_PRESS)
	{
		camPos += m_PerspCam.GetUp() * camSpeed * m_DeltaTime;
	}
	m_PerspCam.SetPosition(camPos);
}