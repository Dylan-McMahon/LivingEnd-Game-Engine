#include "Batch2DRenderer.h"

namespace LivingEnd {
	namespace Graphics {

		Batch2DRenderer::Batch2DRenderer()
		{
			init();
		}
		Batch2DRenderer::~Batch2DRenderer()
		{
			delete m_IBO;
			glDeleteBuffers(1, &m_VBO);
		}
		void Batch2DRenderer::init()
		{
			glGenVertexArrays(1, &m_VAO);
			glGenBuffers(1, &m_VBO);
			
			glBindVertexArray(m_VAO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			
			glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, 0, GL_DYNAMIC_DRAW);
			
			glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
			glEnableVertexAttribArray(SHADER_COLOR_INDEX);
			glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
			glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(3 * GL_FLOAT));
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			
			GLushort indicies[RENDERER_INDICIES_SIZE];
			
			int offset = 0;
			for (int i = 0; i < RENDERER_INDICIES_SIZE; i += 6)
			{
				indicies[  i  ] = offset + 0;
				indicies[i + 1] = offset + 1;
				indicies[i + 2] = offset + 2;
			
				indicies[i + 3] = offset + 2;
				indicies[i + 4] = offset + 3;
				indicies[i + 5] = offset + 0;
			
				offset += 4;
			}
			m_IBO = new IndexBuffer(indicies, RENDERER_INDICIES_SIZE);
			glBindVertexArray(0);
		}
		void Batch2DRenderer::submit(const Renderable2D* renderable)
		{

		}
		void Batch2DRenderer::flush()
		{

		}
	}
}