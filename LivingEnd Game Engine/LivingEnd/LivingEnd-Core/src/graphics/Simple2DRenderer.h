#pragma once
#include "IRenderer2d.h"
#include <deque>
namespace LivingEnd {
	namespace Graphics {

		class Simple2DRenderer : Renderer2D
		{
		private:
			std::deque<const Renderable2D*> m_RenderQueue;
		public:
			void submit(const Renderable2D* renderable) override;
			void flush() override;
		};
	}
}