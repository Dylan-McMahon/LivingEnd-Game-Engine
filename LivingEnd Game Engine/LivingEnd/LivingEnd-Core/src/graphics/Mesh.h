#pragma once
#include "Buffers\VertexArray.h"
#include "Buffers\IndexBuffer.h"

#include "IRenderable.h"
#include "glm\glm\ext.hpp"
namespace LivingEnd {
	namespace Graphics
	{
		struct MeshVertex
		{
			glm::vec3 position;
			glm::vec3 normal;
			glm::vec2 uv;
		};

		class Mesh : public IRenderable
		{
		public :
			Mesh(VertexArray* vertexArray, IndexBuffer* indexBuffer);
			~Mesh();

			void Render(Renderer3D& renderer) override;
		private:
			VertexArray * m_VertexArray;
			IndexBuffer * m_IndexBuffer;
			//TODO: Material
		};
	}
}