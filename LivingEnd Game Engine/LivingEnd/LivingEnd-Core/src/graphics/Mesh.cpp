#include "Mesh.h"
#include <iostream>

namespace LivingEnd {
	namespace Graphics {

		Mesh::Mesh(VertexArray* vertexArray, uint count)
			: m_VertexArray(vertexArray), m_IndexCount(count)
		{		
			m_RenderMode = RenderAPI;
			m_Texture = nullptr;
			m_Shader = nullptr;
		}
		Mesh::Mesh(VertexArray* vertexArray, IndexBuffer* indexBuffer)
			: m_VertexArray(vertexArray), m_IndexBuffer(indexBuffer)
		{
			m_RenderMode = Manual;
			m_Texture = nullptr;
			m_Shader = nullptr;
		}
		Mesh::~Mesh()
		{
			delete m_VertexArray;
			delete m_IndexBuffer;
			delete m_Shader;
			delete m_Texture;
		}

		void Mesh::Render(FlyCamera& camera)
		{
			if (m_RenderMode = Manual)
			{
				m_VertexArray->Bind();
				m_IndexBuffer->Bind();
				m_VertexArray->Draw(m_IndexBuffer->GetCount());
				m_IndexBuffer->Unbind();
				m_VertexArray->Unbind();
			}
			else if (m_RenderMode = RenderAPI)
			{
				m_VertexArray->Bind();
				m_VertexArray->Draw(m_IndexCount);
				m_VertexArray->Unbind();
			}
			else
			{
				//TODO: Name and log
				std::printf("Mesh not initialized");
			}
		}
	}
}