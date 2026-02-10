#pragma once
#include <vector>

namespace FL_Render
{
	class VertexBuffer
	{
	public:
		VertexBuffer();
		~VertexBuffer();

		void SetData(const std::vector<float>& Vertices);
		void SetData(float* Vertices, uint32_t Size);
		void Bind();
		void UnBind();
		void Delete();
	private:
		uint32_t m_RendererID;
	};

}