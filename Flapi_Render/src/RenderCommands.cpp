#include "RenderCommands.h"
#include <glad/glad.h>

namespace FL_Render
{
	void RenderCommands::ClearBuffers()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void RenderCommands::ClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void RenderCommands::DrawFromVertexArray(std::shared_ptr<FL_Render::VertexArray> vertexArray)
	{
		vertexArray->Bind();
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuff()->GetCount(), GL_UNSIGNED_INT, 0);
	}
}