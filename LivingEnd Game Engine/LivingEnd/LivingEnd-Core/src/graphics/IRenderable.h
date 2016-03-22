#pragma once
#include "glm\glm\ext.hpp"
namespace LivingEnd { namespace Graphics {

	struct Vertex { glm::vec4 position; glm::vec4 color; };
	class FlyCamera;
	class IRenderable { public: virtual void Render(FlyCamera& camera) = 0; };

}
}