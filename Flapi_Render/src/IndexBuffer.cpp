#include "IndexBuffer.h"
#include "glad/glad.h"

namespace FL_Render
{
	IndexBuffer::IndexBuffer()
	{
		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	IndexBuffer::~IndexBuffer()
	{
		if (m_RendererID)
			glDeleteBuffers(1, &m_RendererID);
	}

	void IndexBuffer::SetData(const std::vector<uint32_t>& Indices)
	{
		m_Count = Indices.size();
		if(!Indices.empty())
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(uint32_t), Indices.data(), GL_STATIC_DRAW);
	}

	void IndexBuffer::SetData(uint32_t* Indices, uint32_t Size)
	{
		m_Count = Size;
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(uint32_t), Indices, GL_STATIC_DRAW);
	}

	void IndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void IndexBuffer::UnBind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void IndexBuffer::Delete()
	{
		glDeleteBuffers(1, &m_RendererID);
	}
}