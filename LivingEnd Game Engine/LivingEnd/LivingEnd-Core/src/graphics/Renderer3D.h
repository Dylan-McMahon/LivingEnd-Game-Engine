#pragma once
#include "Mesh.h"

namespace LivingEnd {
	namespace Graphics {

		typedef std::vector<RenderCommand> CommandQueue;
		typedef std::vector<RendererUniform> SystemUniformList;

		//
		// Base class for all 3D renderers.
		// 
		// Implementations:
		//		- ForwardRenderer.h  (WIP)
		//		- DeferredRenderer.h (TBA)
		//


		class Renderer3D
		{
		protected:
			CommandQueue m_CommandQueue;
			SystemUniformList m_SystemUniforms;
		public:
			virtual void Init() = 0;
			virtual void Begin() = 0;
			// TODO: Submit needs to be replaced by some sort of macro
			virtual void Submit(const RenderCommand& command) = 0;
			virtual void SubmitMesh(Camera* camera, Mesh* mesh, const maths::mat4& transform) = 0;
			virtual void SubmitLightSetup(const LightSetup& lightSetup) = 0;
			virtual void End() = 0;
			virtual void Present() = 0;

		};

	}
}