#pragma once
#include "glm\glm\ext.hpp"
namespace LivingEnd { namespace Graphics {

	struct Vertex { glm::vec4 position; glm::vec4 color; };
	class Renderer3D;
	class IRenderable { public: virtual void Render(Renderer3D& renderer) = 0; };

}
}