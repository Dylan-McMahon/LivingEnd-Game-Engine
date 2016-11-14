#pragma once
#include "stb-master\stb_image.h"
#include "Types.h"
#include "Buffers\OpenGLRenderAPI.h"
#include "shader.h"
#include "Camera\FlyCamera.h"
#include "FBXModel.h"
namespace LivingEnd {
	namespace Graphics
	{
		class Texture
		{
		public:
			Texture();
			~Texture();
			void Bind();
			void UnBind();
			void LoadTexture(char* filePath);
			void LoadFromFBX(FBXFile* fbxFile, int index);
			void GeneratePerlinTexture(int width, int height, int format, float* data, float sealevel);

			inline Shader* GetShader()const { return m_Shader; };
			inline uint GetTextureID()const { return m_Texture; };
			inline Texture GetTexture()const { return *this; };
		private:
			int m_ImageWidth;
			int m_ImageHeight;
			int m_ImageFormat;
			uint m_Texture;
			GLenum m_TextureSlot;
			byte* m_ImageData;
			Shader* m_Shader;
			//int m_TextureSlot;
		};
	}
}