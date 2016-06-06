#include "Mesh.h"
#include <iostream>

namespace LivingEnd {
	namespace Graphics {

		Mesh::Mesh(VertexArray* vertexArray, uint count)
			: m_VertexArray(vertexArray), m_IndexCount(count)
		{		
			m_RenderMode = RenderAPI;
		}
		Mesh::Mesh(VertexArray* vertexArray, IndexBuffer* indexBuffer)
			: m_VertexArray(vertexArray), m_IndexBuffer(indexBuffer)
		{
			m_RenderMode = Manual;
		}
		Mesh::~Mesh()
		{
			delete m_VertexArray;
			delete m_IndexBuffer;
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
				GLenum error = glGetError();
				if (error != GL_NO_ERROR)
					std::cout << "OpenGL error: " << error << std::endl;
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