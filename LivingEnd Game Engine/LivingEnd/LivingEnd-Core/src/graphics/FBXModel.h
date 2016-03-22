#pragma once
#include "Types.h"
#include "IRenderable.h"
#include "FBXLoader\FBXFile.h"
#include "shader.h"
#include "Buffers\OpenGLBuffer.h"
#include "Camera\FlyCamera.h"
namespace LivingEnd { namespace Graphics {

	class FBXModel /*: public IRenderable*/
	{
	public:
		FBXModel(const char* model_path);
		~FBXModel();
		void Init(const char* path);
		void Render(FlyCamera* a_pCamera);
	private:
		uint* m_GLData;
		Shader* m_Shader;
		FBXFile* m_FBX;
	};
}
}

