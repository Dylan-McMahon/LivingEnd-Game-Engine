#pragma once
#include "gl_core_4_4.h"
#include "glfw\include\GLFW\glfw3.h"
namespace LivingEnd { namespace Graphics {

	class VertexBuffer
	{
	private:
		GLuint m_BufferID;
		GLuint m_componentCount;
	public:
		VertexBuffer(GLfloat * data, GLsizei count, GLuint componentCount);
		~VertexBuffer();
		void bind();
		void unbind();
		inline GLuint getComponentCount() const { return m_componentCount; };
	};
}
}