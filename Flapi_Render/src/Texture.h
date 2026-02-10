#pragma once
#include <memory>
#include <string>

namespace FL_Render
{
	class Texture
	{
	public:
		Texture(int32_t Width, int32_t Height, unsigned char* data, int32_t Format = 4);
		Texture(const std::string& TexturePath);
		~Texture();

		void Bind(uint32_t index = 0);
		void UnBind();
		void Delete();

		uint32_t GetRawTexture() { return m_Texture; };
		uint32_t GetBindedIndex() { return m_BindedIndex; }
	private:
		uint32_t m_Texture;
		int32_t m_Width, m_Height, m_Format;
		uint32_t m_BindedIndex = -1;
	};

}