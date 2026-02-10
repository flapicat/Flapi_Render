#include "CameraOrthographic.h"

#include <glm/gtc/matrix_transform.hpp>

namespace FL_Render
{
	CameraOrthographic::CameraOrthographic(float left, float right, float bottom, float top)
		:m_Camera(Camera())
	{
		m_Camera.m_Near = -1.0f;
		m_Camera.m_Far = 1.0f;
		m_Camera.m_ProjectionMatrix = glm::ortho(left, right, bottom, top, m_Camera.m_Near, m_Camera.m_Far);
		m_Camera.m_ViewMatrix = glm::mat4(1.0f);
		m_Camera.m_ViewProjectionMatrix = m_Camera.m_ProjectionMatrix * m_Camera.m_ViewMatrix;
	}

	void CameraOrthographic::SetProjectionMatrix(float AspectRatio)
	{
		m_Camera.m_ProjectionMatrix = glm::ortho(-AspectRatio, AspectRatio, -1.0f, 1.0f, m_Camera.m_Near, m_Camera.m_Far);
		m_Camera.m_ViewProjectionMatrix = m_Camera.m_ProjectionMatrix * m_Camera.m_ViewMatrix;
	}

	void CameraOrthographic::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));
		m_Camera.m_ViewMatrix = glm::inverse(transform);
		m_Camera.m_ViewProjectionMatrix = m_Camera.m_ProjectionMatrix * m_Camera.m_ViewMatrix;
	}
}