#pragma once
#include "Mesh.h"
#include "Texture.h"
#include "shader.h"
#include "Camera\FlyCamera.h"

namespace LivingEnd 
{
	namespace Graphics 
	{

		class Grid : public Mesh
		{
		public:
			Grid(uint rows, uint cols);
			~Grid();
			void GenerateGrid();
			void GeneratePerlin();

			void Render(FlyCamera& camera) override;

			inline float* GetPerlinData() const { return m_PerlinData; };

		private:
			//Perlin noise varriables
			float * m_PerlinData;
			//Texture * m_PerlinTexture;
			//Shader * m_PerlinShader;

			uint m_Rows;
			uint m_Cols;
			VertexArray m_VertexArray;
			API::Buffer* m_VBO;
			API::Buffer* m_IBO;
			MeshVertex* m_aoVerts;
			uint* m_auIndicies;

		};
	}
}

