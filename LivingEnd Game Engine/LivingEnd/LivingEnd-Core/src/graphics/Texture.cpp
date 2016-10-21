#include "Texture.h"
#include <iostream>

namespace LivingEnd
{
	namespace Graphics
	{
		Texture::Texture()
		{
			m_ImageWidth = 0;
			m_ImageHeight = 0;
			m_ImageFormat = 0;
			m_ImageData = nullptr;
			m_Shader = nullptr;
			m_TextureSlot = 0;

		}
		Texture::~Texture()
		{
			delete m_ImageData;
			delete m_Shader;
		}
		void Texture::Bind()
		{
			API::SetActiveTexture(GL_TEXTURE0 + m_TextureSlot);
			API::BindTexture(GL_TEXTURE_2D, m_Texture);
		}
		void Texture::UnBind()
		{
			API::BindTexture(GL_TEXTURE_2D, 0);
		}
		void Texture::LoadTexture(char* filePath)
		{
			if (m_ImageData == nullptr)
			{
				if (m_Shader == nullptr)
				{
					m_Shader = new Shader("data/Shaders/TextureVertexShader.vs", "data/Shaders/TextureFragmentShader.fs");
				}
				m_Shader->enable();
				m_ImageData = stbi_load(filePath, &m_ImageWidth, &m_ImageHeight, &m_ImageFormat, STBI_default);
				m_Texture = API::CreateTexture();
				API::BindTexture(GL_TEXTURE_2D, m_Texture);
				API::SetTextureData(GL_TEXTURE_2D, GL_RGB, m_ImageWidth, m_ImageHeight, m_ImageFormat, GL_UNSIGNED_BYTE, m_ImageData);
				API::SetTextureParameter(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				API::SetTextureParameter(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				stbi_image_free(m_ImageData);
				API::SetActiveTexture(m_TextureSlot);
			}
		}
		void Texture::GeneratePerlinTexture(int width, int height, int format, float* data, float sealevel)
		{
			if (m_ImageData == nullptr)
			{
				if (m_Shader == nullptr)
				{
					m_Shader = new Shader("data/Shaders/TerrainVertexShader.vs", "data/Shaders/TerrainFragmentShader.fs");
				}
				m_Shader->enable();

				m_Texture = API::CreateTexture();
				API::SetActiveTexture(GL_TEXTURE0 + m_TextureSlot);
				API::BindTexture(GL_TEXTURE_2D, m_Texture);
				API::SetTextureData(GL_TEXTURE_2D, GL_R32F, width, height, format, GL_FLOAT, data);
				API::SetTextureParameter(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				API::SetTextureParameter(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				API::SetTextureParameter(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				API::SetTextureParameter(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

				m_Shader->setUnifrom1i("perlin_texture", m_TextureSlot);
				m_Shader->setUnifrom1f("SeaLevel", sealevel);
				m_Shader->disable();
				////GLenum error = glGetError();
				//if (error != GL_NO_ERROR)
				//	std::cout << "OpenGL error: " << error << std::endl;
			}
		}
	}
}