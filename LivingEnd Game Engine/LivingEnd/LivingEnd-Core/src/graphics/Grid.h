#pragma once
#include "Mesh.h"

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

			inline float* GetPerlinData() const { return m_PerlinData; };

		private:
			//Perlin noise varriables
			float * m_PerlinData;
			//Texture * m_PerlinTexture;
			//Shader * m_PerlinShader;

			uint m_Rows;
			uint m_Cols;
			float m_SeaLevel;
			VertexArray m_VertexArray;
			API::Buffer* m_VBO;
			API::Buffer* m_IBO;
			MeshVertex* m_aoVerts;
			uint* m_auIndicies;

			

		};
	}
}

