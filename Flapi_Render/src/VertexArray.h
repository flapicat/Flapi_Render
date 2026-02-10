#pragma once
#include <memory>
#include <glad/glad.h>

#include "IndexBuffer.h"
#include "VertexBuffer.h"

namespace FL_Render
{
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void Bind();
		void UnBind();
		void Delete();

		void SetAttribPointer(uint32_t index, int32_t size, GLenum type, bool normalized, size_t stride, const void* pointer);

		void SetVertexBuff(std::shared_ptr<VertexBuffer> VertexBuff) { m_VertexBuffer = VertexBuff; }
		void SetIndexBuff(std::shared_ptr<IndexBuffer> IndexBuff) { m_IndexBuffer = IndexBuff; }
		std::shared_ptr<VertexBuffer>& GetVertexBuff() { return m_VertexBuffer; }
		std::shared_ptr<IndexBuffer>& GetIndexBuff() { return m_IndexBuffer; }
	private:
		uint32_t m_RendererID;
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
	};

}