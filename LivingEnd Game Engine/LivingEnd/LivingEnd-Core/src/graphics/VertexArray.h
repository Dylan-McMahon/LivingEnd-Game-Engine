#pragma once
#include "VertexBuffer.h"
#include <vector>
namespace LivingEnd {
	namespace Graphics {

		class VertexArray {
		private:
			GLuint m_ArrayID;
			std::vector<VertexBuffer*> m_Buffers;
		public:
			VertexArray();
			~VertexArray();
			void addBuffer(VertexBuffer* vertexBuffer, GLuint index);
			void bind();
			void unbind();
		};
	}
}

