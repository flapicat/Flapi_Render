#include "CameraPerspective.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace FL_Render
{
	CameraPerspective::CameraPerspective(float fov, float AspectRatio)
		:m_Camera(Camera()),m_Fov(fov)
	{
		m_Camera.m_Near = 0.1f;
		m_Camera.m_Far = 100.0f;
		m_Camera.m_ProjectionMatrix = glm::perspective(glm::radians(m_Fov), AspectRatio, m_Camera.m_Near, m_Camera.m_Far);
		RecalculateViewMatrix();
	}

	void CameraPerspective::SetProjectionMatrix(float AspectRatio)
	{
		m_Camera.m_ProjectionMatrix = glm::perspective(glm::radians(m_Fov), AspectRatio, m_Camera.m_Near, m_Camera.m_Far);
		m_Camera.m_ViewProjectionMatrix = m_Camera.m_ProjectionMatrix * m_Camera.m_ViewMatrix;
	}

	void CameraPerspective::SetRotation(float yaw, float pitch)
	{
		m_Yaw = yaw;
		m_Pitch = pitch;

		if (m_Pitch > 89.0f)  m_Pitch = 89.0f;
		if (m_Pitch < -89.0f) m_Pitch = -89.0f;

		RecalculateViewMatrix();
	}

	void CameraPerspective::AddRotation(float deltaYaw, float deltaPitch)
	{
		m_Yaw += deltaYaw;
		m_Pitch += deltaPitch;

		if (m_Pitch > 89.0f)  m_Pitch = 89.0f;
		if (m_Pitch < -89.0f) m_Pitch = -89.0f;

		RecalculateViewMatrix();
	}

	void CameraPerspective::RecalculateViewMatrix()
	{
		float yaw = glm::radians(m_Yaw);
		float pitch = glm::radians(m_Pitch);

		glm::vec3 front;
		front.x = cos(yaw) * cos(pitch);
		front.y = sin(pitch);
		front.z = sin(yaw) * cos(pitch);

		m_front = glm::normalize(front);

		m_right = glm::normalize(glm::cross(m_front, glm::vec3(0.0f, 1.0f, 0.0f)));
		m_up = glm::normalize(glm::cross(m_right, m_front));

		m_Camera.m_ViewMatrix =	glm::lookAt(m_Position, m_Position + m_front, m_up);
		m_Camera.m_ViewProjectionMatrix = m_Camera.m_ProjectionMatrix * m_Camera.m_ViewMatrix;
	}

	void CameraPerspective::OnMouseMoved(float xpos, float ypos)
	{
		if (m_FirstMouse)
		{
			m_LastMouseX = xpos;
			m_LastMouseY = ypos;
			m_FirstMouse = false;
		}

		float xoffset = xpos - m_LastMouseX;
		float yoffset = m_LastMouseY - ypos;

		m_LastMouseX = xpos;
		m_LastMouseY = ypos;

		xoffset *= m_MouseSensitivity;
		yoffset *= m_MouseSensitivity;

		m_Yaw += xoffset;
		m_Pitch += yoffset;

		// Prevent camera flip
		if (m_Pitch > 89.0f)  m_Pitch = 89.0f;
		if (m_Pitch < -89.0f) m_Pitch = -89.0f;

		RecalculateViewMatrix();
	}
}