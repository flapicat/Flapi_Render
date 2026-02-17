#pragma once
#include "Camera.h"

namespace FL_Render
{
	class CameraPerspective
	{
	public:
		CameraPerspective() = default;
		CameraPerspective(float fov, float AspectRatio);

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }

		float GetRotation() const { return m_Rotation; }
		void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

		Camera& GetCamera() { return m_Camera; }

		glm::vec3& GetUp() { return m_up; }
		glm::vec3& GetFront() { return m_front; }
		glm::vec3& GetRight() { return m_right; }

		void SetProjectionMatrix(float AspectRatio);
		void SetRotation(float yaw, float pitch);
		void AddRotation(float deltaYaw, float deltaPitch);

		void OnMouseMoved(float xpos, float ypos);

		float& GetLastMouseX() { return m_LastMouseX; }
		float& GetLastMouseY() { return m_LastMouseY; }
		bool& GetFirstMouse() { return m_FirstMouse; }
	private:
		void RecalculateViewMatrix();
	private:
		Camera m_Camera;
		float m_Fov = 0.0f;
		glm::vec3 m_Position = { 0.0f,0.0f,0.0f };
		float m_Rotation = 0.0f;

		glm::vec3 m_up = { 0.0f, 1.0f, 0.0f};
		glm::vec3 m_front = { 0.0f, 0.0f, -1.0f };
		glm::vec3 m_right = { 1.0f, 0.0f, 0.0f };

		float m_Yaw = -90.0f;
		float m_Pitch = 0.0f;

		float m_MouseSensitivity = 0.1f;

		bool  m_FirstMouse = true;
		float m_LastMouseX = 0.0f;
		float m_LastMouseY = 0.0f;
	};

}