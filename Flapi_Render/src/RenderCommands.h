#pragma once
#include <glm/glm.hpp>
#include "VertexArray.h"

namespace FL_Render
{
	class RenderCommands
	{
	public:
		static void ClearBuffers();
		static void ClearColor(const glm::vec4& color);
		static void DrawFromVertexArray(std::shared_ptr<FL_Render::VertexArray> vertexArray);
	};
}
