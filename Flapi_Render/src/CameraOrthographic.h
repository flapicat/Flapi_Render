#pragma once
#include "Camera.h"

namespace FL_Render
{
	class CameraOrthographic
	{
	public:
		CameraOrthographic() = default;
		CameraOrthographic(float left, float right, float bottom, float top);

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }

		float GetRotation() const { return m_Rotation; }
		void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }
		
		Camera& GetCamera() { return m_Camera; }

		void SetProjectionMatrix(float AspectRatio);
	private:
		void RecalculateViewMatrix();
	private:
		Camera m_Camera;
		glm::vec3 m_Position = {0.0f,0.0f,0.0f};
		float m_Rotation = 0.0f;
	};

}
