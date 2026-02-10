#pragma once
#include <memory>
#include <glm/glm.hpp>
#include "Texture.h"
#include "Camera.h"

namespace FL_Render
{
	struct Vertex
	{
		glm::vec3 Position;
		glm::vec2 TextureCoords;
		float TextureID;
	};

	class Renderer
	{
	public:
		static void Init();
		static void Terminate();
		static void SetClearColor(const glm::vec4& color);

		static void BeginScene(Camera& camera);
		static void EndScene();
		static void BeginBatch();
		static void EndBatch();

		static void SubmitData(
			std::vector<Vertex>& Vertices,
			const std::vector<uint32_t>& Indices,
			const std::shared_ptr<Texture> texture,
			const glm::vec3& position = glm::vec3(0.0f),
			const glm::vec3& size = glm::vec3(1.0f));
	};
}
