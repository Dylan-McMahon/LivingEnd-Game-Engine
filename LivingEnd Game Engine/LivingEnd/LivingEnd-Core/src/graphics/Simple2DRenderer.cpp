#include "Simple2DRenderer.h"
#include <iostream>
namespace LivingEnd {
	namespace Graphics {

		void Simple2DRenderer::submit(const Renderable2D* renderable)
		{
			m_RenderQueue.push_back(renderable);
		}
		void Simple2DRenderer::flush()
		{
			while (!m_RenderQueue.empty())
			{
				const Renderable2D* renderable = m_RenderQueue.front();
				VertexArray a_VAO = *renderable->getVAO();
				IndexBuffer a_IBO = *renderable->getIBO();
				a_VAO.bind();
				a_IBO.bind();
				renderable->getShader().setUnifromMat4("model_matrix", glm::translate(renderable->getPosition()));
				glDrawElements(GL_TRIANGLES, a_IBO.getCount(), GL_UNSIGNED_SHORT, 0);
				a_IBO.unbind();
				a_VAO.unbind();
				m_RenderQueue.pop_front(); 
			}
		}

	}
}