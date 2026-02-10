#include "VertexArray.h"

namespace FL_Render
{
	VertexArray::VertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
		glBindVertexArray(m_RendererID);
	}

	VertexArray::~VertexArray()
	{
		if (m_RendererID)
		{
			m_VertexBuffer->Delete();
			m_IndexBuffer->Delete();
			glDeleteVertexArrays(1, &m_RendererID);
		}
	}

	void VertexArray::Bind()
	{
		glBindVertexArray(m_RendererID);
	}

	void VertexArray::UnBind()
	{
		glBindVertexArray(m_RendererID);
	}

	void VertexArray::Delete()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void VertexArray::SetAttribPointer(
		uint32_t index, 
		int32_t size, 
		GLenum type, 
		bool normalized, 
		size_t stride, 
		const void* pointer)
	{
		glVertexAttribPointer(index,size,type,normalized,stride,pointer);
		glEnableVertexAttribArray(index);
	}

}