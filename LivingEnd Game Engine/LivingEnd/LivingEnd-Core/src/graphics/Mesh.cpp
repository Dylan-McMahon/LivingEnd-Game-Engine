#include "Mesh.h"

namespace LivingEnd {
	namespace Graphics {

		Mesh::Mesh(VertexArray* vertexArray, IndexBuffer* indexBuffer)
			: m_VertexArray(vertexArray), m_IndexBuffer(indexBuffer)
		{

		}

		Mesh::~Mesh()
		{
			delete m_VertexArray;
			delete m_IndexBuffer;
		}

		void Mesh::Render(Renderer3D& renderer)
		{
			m_VertexArray->Bind();
			m_IndexBuffer->Bind();
			m_VertexArray->Draw(m_IndexBuffer->GetCount());
			m_IndexBuffer->Unbind();
			m_VertexArray->Unbind();
		}
	}
}