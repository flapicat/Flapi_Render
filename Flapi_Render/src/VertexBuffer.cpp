#include "VertexBuffer.h"
#include "glad/glad.h"

namespace FL_Render
{
	VertexBuffer::VertexBuffer()
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	VertexBuffer::~VertexBuffer()
	{
		if(m_RendererID)
			glDeleteBuffers(1, &m_RendererID);
	}

	void VertexBuffer::SetData(const std::vector<float>& Vertices)
	{
		glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(float), Vertices.data(), GL_STATIC_DRAW);
	}

	void VertexBuffer::SetData(float* Vertices, uint32_t Size)
	{
		glBufferData(GL_ARRAY_BUFFER, Size * sizeof(float), Vertices, GL_STATIC_DRAW);
	}

	void VertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void VertexBuffer::UnBind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VertexBuffer::Delete()
	{
		glDeleteBuffers(1, &m_RendererID);
	}
}