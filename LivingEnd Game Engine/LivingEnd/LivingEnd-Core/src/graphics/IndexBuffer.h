#pragma once
#include "gl_core_4_4.h"
#include "glfw\include\GLFW\glfw3.h"
namespace LivingEnd {
	namespace Graphics {

		class IndexBuffer
		{
		private:
			GLuint m_BufferID;
			GLuint m_Count;
		public:
			IndexBuffer(GLushort * data, GLsizei count);
			~IndexBuffer();
			void bind();
			void unbind();
			inline GLuint getCount() const { return m_Count; };
		};
	}
}

