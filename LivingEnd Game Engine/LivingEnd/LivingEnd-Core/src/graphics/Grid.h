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
		protected:
			void GenerateGrid();
		private:
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

