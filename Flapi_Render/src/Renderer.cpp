#include "Renderer.h"
#include "RenderCommands.h"

#include "Shader.h"
#include "Texture.h"
#include <iostream>

namespace FL_Render
{
	struct RendererData 
	{
		//Config
		uint32_t maxTexturesBoundAtTheTime = 0;
		glm::vec4 ClearColor = glm::vec4(0.0f);

		//DATA
		uint32_t VertOffset = 0;
		uint32_t IndiOffset = 0;

		float* vertices;
		uint32_t VertMaxCount = 1'000'000;
		uint32_t* indices;
		uint32_t IndiMaxCount = 1'000'000;

		//Textures
		std::shared_ptr<Texture> WhiteTexture;
		uint32_t WhiteTextureID = 0;
		std::vector<std::shared_ptr<Texture>> TextureSlots;
		uint32_t TextureSlotIndex = 1; // 0 = white texture

		//OBJ
		std::shared_ptr<FL_Render::Shader> Shader;
		std::shared_ptr<FL_Render::Shader> TexShader;
		std::shared_ptr<FL_Render::VertexArray> VertexArray;
	};
	RendererData data;

	void Renderer::Init()
	{
		glEnable(GL_DEPTH_TEST);
		GLint maxFragmentTextures = 0;
		glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxFragmentTextures);
		data.maxTexturesBoundAtTheTime = maxFragmentTextures;
		data.TextureSlots.resize(data.maxTexturesBoundAtTheTime);

		data.vertices = new float[data.VertMaxCount];
		data.indices = new uint32_t[data.IndiMaxCount];

		data.Shader.reset(new FL_Render::Shader("../Flapi_Render/Assets/Shaders/default.vert", "../Flapi_Render/Assets/Shaders/default.frag"));
		data.TexShader.reset(new FL_Render::Shader("../Flapi_Render/Assets/Shaders/texture.vert", "../Flapi_Render/Assets/Shaders/texture.frag"));

		data.VertexArray.reset(new FL_Render::VertexArray());

		std::shared_ptr<FL_Render::VertexBuffer>VB;
		VB.reset(new FL_Render::VertexBuffer());
		VB->SetData(nullptr, 0);
		data.VertexArray->SetVertexBuff(VB);

		std::shared_ptr<FL_Render::IndexBuffer>IB;
		IB.reset(new FL_Render::IndexBuffer());
		IB->SetData(nullptr, 0);
		data.VertexArray->SetIndexBuff(IB);

		data.VertexArray->SetAttribPointer(0, 3, GL_FLOAT, false, 6 * sizeof(float), 0);
		data.VertexArray->SetAttribPointer(1, 2, GL_FLOAT, false, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		data.VertexArray->SetAttribPointer(2, 1, GL_FLOAT, false, 6 * sizeof(float), (void*)(5 * sizeof(float)));

		data.VertexArray->UnBind();

	
		unsigned char WhiteTextureData[4] = { 255,255,255,255 };
		data.WhiteTexture.reset(new Texture(1, 1, WhiteTextureData));
		data.WhiteTextureID = 0;
		data.TextureSlots[0] = data.WhiteTexture;

		std::vector<int> samplers;
		samplers.resize(data.maxTexturesBoundAtTheTime);
		for (uint32_t i = 0; i < data.maxTexturesBoundAtTheTime; i++)
			samplers[i] = i;

		data.TexShader->Use();
		data.TexShader->setIntArray("u_Textures", samplers.data(), data.maxTexturesBoundAtTheTime);
	}

	void Renderer::Terminate()
	{
		delete[] data.vertices;
		delete[] data.indices;
	}

	void Renderer::SetClearColor(const glm::vec4& color)
	{
		data.ClearColor = color;
	}

	void Renderer::BeginScene(Camera& camera)
	{
		RenderCommands::ClearColor(data.ClearColor);
		RenderCommands::ClearBuffers();
		data.TexShader->Use();
		data.TexShader->setMat4("u_ViewProjectionMatrix", camera.GetViewProjectionMatrix());

		BeginBatch();
	}

	void Renderer::BeginBatch()
	{
		data.VertOffset = 0;
		data.IndiOffset = 0;
		data.TextureSlotIndex = 1;
	}

	void Renderer::EndScene()
	{
		EndBatch();
	}

	void Renderer::EndBatch()
	{
		data.VertexArray->GetVertexBuff()->SetData(data.vertices, data.VertOffset);
		data.VertexArray->GetIndexBuff()->SetData(data.indices,   data.IndiOffset);

		for (uint32_t i = 0; i < data.TextureSlotIndex; i++) {

			data.TextureSlots[i]->Bind(i);
		}

		data.TexShader->Use();
		FL_Render::RenderCommands::DrawFromVertexArray(data.VertexArray);
	}

	void Renderer::SubmitData(
		std::vector<Vertex>& Vertices, 
		const std::vector<uint32_t>& Indices, 
		const std::shared_ptr<Texture> texture,
		const glm::vec3& position, 
		const glm::vec3& size)
	{
		if (data.VertOffset + Vertices.size() > data.VertMaxCount ||
			data.IndiOffset + Indices.size() > data.IndiMaxCount ||
			data.maxTexturesBoundAtTheTime <= data.TextureSlotIndex)
		{
			EndBatch();
			BeginBatch();
		}
	
		float textureIndex = 0.0f;
		if (texture != nullptr && texture != data.WhiteTexture)
		{
			for (uint32_t i = 1; i < data.TextureSlotIndex; i++)
			{
				if (data.TextureSlots[i] && data.TextureSlots[i]->GetRawTexture() == texture->GetRawTexture())
				{
					textureIndex = (float)i;
					break;
				}
			}
	
			if (textureIndex == 0.0f) 
			{
				textureIndex = (float)data.TextureSlotIndex;
				data.TextureSlots[data.TextureSlotIndex] = texture;
				data.TextureSlotIndex++;
			}
		}
	
		std::vector<Vertex> transformedVertices = Vertices;
	
		for (auto& vertex : transformedVertices)
		{
			vertex.Position.x = (vertex.Position.x * size.x) + position.x;
			vertex.Position.y = (vertex.Position.y * size.y) + position.y;
			vertex.Position.z = (vertex.Position.z * size.z) + position.z;
	
			vertex.TextureID = textureIndex;
		}
	
		memcpy(data.vertices + data.VertOffset,
			transformedVertices.data(),
			transformedVertices.size() * sizeof(Vertex));
	
		uint32_t NumberOfCurrentVertexes = Vertices.size() * (data.VertOffset / sizeof(Vertex));
		for (uint32_t i = 0; i < Indices.size(); i++)
		{
			data.indices[data.IndiOffset + i] = Indices[i] + NumberOfCurrentVertexes;
		}
	
		data.VertOffset += ((uint32_t)transformedVertices.size() * sizeof(Vertex)) / sizeof(float);
		data.IndiOffset += (uint32_t)Indices.size();
	}
}