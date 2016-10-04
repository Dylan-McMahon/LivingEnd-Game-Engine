#pragma once
#include "Buffers\VertexArray.h"
#include "Buffers\IndexBuffer.h"
#include "Texture.h"
#include "shader.h"

#include "IRenderable.h"
#include "glm\glm\ext.hpp"


namespace LivingEnd 
{
	namespace Graphics
	{
		enum MeshMode
		{
			Manual, RenderAPI, NotInit
		};
		struct MeshVertex
		{
			glm::vec4 Position;
			//glm::vec3 normal;
			glm::vec2 uv;
		};
		class Mesh : public IRenderable
		{
		public :
			//Uses the RenderAPI method to render
			Mesh(VertexArray* vertexArray, uint count);
			//Uses the manual buffer generation method to render
			Mesh(VertexArray* vertexArray, IndexBuffer* indexBuffer);
			~Mesh();
			virtual void Render(FlyCamera& camera) override;
			inline Texture* GetTexture() { return m_Texture; };
			inline Shader* GetShader() { return m_Shader; };
		protected:
			VertexArray* m_VertexArray = nullptr;
			IndexBuffer* m_IndexBuffer = nullptr;
			MeshMode m_RenderMode = NotInit;
			uint m_IndexCount;
			Shader* m_Shader;
			Texture* m_Texture;
			//TODO: Material
		};
	}
}