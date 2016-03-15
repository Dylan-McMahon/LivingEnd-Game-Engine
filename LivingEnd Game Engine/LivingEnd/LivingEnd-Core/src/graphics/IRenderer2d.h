#pragma once
#include "Renderable2d.h"
#include "gl_core_4_4.h"
#include "glfw\include\GLFW\glfw3.h"
#include "glm\glm\glm.hpp"
#include "glm\glm\ext.hpp"
namespace LivingEnd {
	namespace Graphics {

		class Renderer2D
		{
		public:
			virtual void submit(const Renderable2D* renderable) = 0;
			virtual void flush() = 0;
		};
	}
}
