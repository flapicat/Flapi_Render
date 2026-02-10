#pragma once
#include <vector>

namespace FL_Render
{
	class IndexBuffer
	{
	public:
		IndexBuffer();
		~IndexBuffer();
		void SetData(const std::vector<uint32_t>& Indices);
		void SetData(uint32_t* Indices, uint32_t Size);
		void Bind();
		void UnBind();
		void Delete();

		uint32_t GetCount() { return m_Count; }
	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};

}