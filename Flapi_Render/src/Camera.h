#pragma once

#include <glm/glm.hpp>

namespace FL_Render
{
	class Camera
	{
		friend class CameraOrthographic;
	public:
		Camera() = default;

		const glm::mat4& GetViewMatrix() { return m_ViewMatrix; }
		const glm::mat4& GetProjectionMatrix() { return m_ProjectionMatrix; }
		const glm::mat4& GetViewProjectionMatrix() { return m_ViewProjectionMatrix; }
	protected:
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewProjectionMatrix;
		float m_Near, m_Far;
	};
}
