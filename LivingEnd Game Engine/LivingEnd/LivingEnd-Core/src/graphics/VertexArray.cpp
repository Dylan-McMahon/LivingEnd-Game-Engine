#include "VertexArray.h"

namespace LivingEnd {
	namespace Graphics {

		VertexArray::VertexArray()
		{
			glGenVertexArrays(1, &m_ArrayID);
		}
		VertexArray::~VertexArray()
		{
			for (int i = 0; i < m_Buffers.size(); ++i)
			{
				delete m_Buffers[i];
			}
			glDeleteVertexArrays(1, &m_ArrayID);
		}
		void VertexArray::addBuffer(VertexBuffer* vertexBuffer, GLuint index)
		{
			bind();
			vertexBuffer->bind();
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, vertexBuffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);

			unbind();
			vertexBuffer->unbind();
		}
		void VertexArray::bind()
		{
			glBindVertexArray(m_ArrayID);
		}
		void VertexArray::unbind()
		{
			glBindVertexArray(0);
		}
	}
}

