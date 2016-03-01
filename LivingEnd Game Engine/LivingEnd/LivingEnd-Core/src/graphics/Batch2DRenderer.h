#pragma once
#include "IRenderer2d.h"

namespace LivingEnd {
	namespace Graphics {
#define RENDERER_MAX_SPRITE 10000
#define RENDERER_VERTEX_SIZE sizeof(Vertex)
#define RENDERER_SPRITE_SIZE (RENDERER_VERTEX_SIZE * 4)
#define RENDERER_BUFFER_SIZE (RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITE)
#define RENDERER_INDICIES_SIZE (RENDERER_MAX_SPRITE * 6)

#define SHADER_VERTEX_INDEX 0
#define SHADER_COLOR_INDEX 1
		class Batch2DRenderer : Renderer2D
		{
		public:
			Batch2DRenderer();
			~Batch2DRenderer();
			void submit(const Renderable2D* renderable) override;
			void flush() override;
		private:
			void init();

			GLuint m_VAO;
			GLuint m_VBO;
			IndexBuffer * m_IBO;
			GLsizei m_IndexCount;
		};
	}
}