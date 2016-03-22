#include "Grid.h"

namespace LivingEnd {
	namespace Graphics {

		Grid::Grid(uint rows, uint cols)
			: Mesh(&m_VertexArray, (uint)((rows -1) * (cols - 1) * 6)) 
		{
			m_Rows = rows;
			m_Cols = cols;
			m_VertexArray.Bind();
			GenerateGrid();
			m_VertexArray.Unbind();
		}
		Grid::~Grid()
		{
			delete m_VBO;
			delete m_IBO;
			delete[] m_aoVerts;
			delete[] m_auIndicies;
		}

		void Grid::GenerateGrid()
		{
			//
			//Generate vertex positions
			//
			m_VBO = new API::Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
			m_aoVerts = new MeshVertex[m_Rows * m_Cols];
			for (uint r = 0; r < m_Rows; ++r)
			{
				for (uint c = 0; c < m_Cols; ++c)
				{
					m_aoVerts[r * m_Cols + c].Position = glm::vec4((float)c - (m_Cols / 2), 0, (float)r - (m_Rows / 2), 1);
					//TODO: Add color
				}
			}
			m_VBO->Bind();
			m_VBO->SetData((m_Rows * m_Cols) * sizeof(MeshVertex), m_aoVerts);
			m_VBO->layout.Push<glm::vec4>("Position", 1, false);
			//TODO: Push color
			m_VertexArray.PushBuffer(m_VBO);
			//
			// Generate Indicies
			//
			m_IBO = new API::Buffer(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
			m_auIndicies = new uint[(m_Rows - 1) * (m_Cols - 1) * 6];
			uint index = 0;
			for (uint r = 0; r < (m_Rows - 1); ++r)
			{
				for (uint c = 0; c < (m_Cols - 1); ++c)
				{
					//tri 1
					m_auIndicies[index++] = r * m_Cols + c;
					m_auIndicies[index++] = (r + 1) * m_Cols + c;
					m_auIndicies[index++] = (r + 1) * m_Cols + (c + 1);

					m_auIndicies[index++] = r * m_Cols + c;
					m_auIndicies[index++] = (r + 1) * m_Cols + (c + 1);
					m_auIndicies[index++] = r * m_Cols + (c + 1);
				}
			}
			m_IBO->Bind();
			m_IBO->SetData((m_Rows - 1) * (m_Cols - 1) * 6 * sizeof(uint), m_auIndicies);
			m_VertexArray.PushBuffer(m_IBO);
		}
	}
}