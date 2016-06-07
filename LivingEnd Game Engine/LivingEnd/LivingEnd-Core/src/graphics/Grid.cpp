#include "Grid.h"

namespace LivingEnd {
	namespace Graphics {

		Grid::Grid(uint rows, uint cols)
			: Mesh(&m_VertexArray, (uint)((rows -1) * (cols - 1) * 6)) 
		{
			m_Rows = rows;
			m_Cols = cols;

			m_PerlinData = nullptr;
		}
		Grid::~Grid()
		{
			delete m_VBO;
			delete m_IBO;
			delete[] m_aoVerts;
			delete[] m_auIndicies;
			delete m_PerlinData;
		}

		void Grid::GenerateGrid()
		{
			m_VertexArray->Bind();
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
			m_VertexArray->PushBuffer(m_VBO);
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
			m_VertexArray.Unbind();
		}

		void Grid::GeneratePerlin()
		{
			m_Shader = new Shader("../data/Shaders/BasicVertexShader.vs", "../data/Shaders/BasicFragmentShader.fs");

			m_VertexArray.Bind();
			uint dims = m_Rows;

			m_VBO = new API::Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
			//
			// Generate Perlin Noise
			//
			m_PerlinData = new float[dims * dims];
			float scale = (1.0f / dims) * 3;
			int octaves = 6;

			for (int x = 0; x < dims; ++x)
			{
				for (int y = 0; y < dims; ++y)
				{
					//Generate Noise
					float amplitude = 1.f;
					float persistence = 0.3f;
					m_PerlinData[y * dims + x] = 0;
					for (int o = 0; o < octaves; ++o)
					{
						float freq = std::powf(2, (float)o);
						float perlin_sample = glm::perlin(glm::vec2((float)x, (float)y) * scale * freq) * 0.5f + 0.5f;
						m_PerlinData[y * dims + x] += perlin_sample * amplitude;
						amplitude *= persistence;
					}
				}
			}
			m_VBO->Bind();
			m_VBO->SetData((dims * dims) * sizeof(float), m_PerlinData);
			m_VBO->layout.Push<glm::vec4>("Position", 1, false);
			//TODO: Push color
			m_VertexArray.PushBuffer(m_VBO);
			//
			// Generate Indicies
			//
			m_IBO = new API::Buffer(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
			m_auIndicies = new uint[(dims - 1) * (dims - 1) * 6];
			uint index = 0;
			for (uint r = 0; r < (dims - 1); ++r)
			{
				for (uint c = 0; c < (dims - 1); ++c)
				{
					//tri 1
					m_auIndicies[index++] = r * dims + c;
					m_auIndicies[index++] = (r + 1) * dims + c;
					m_auIndicies[index++] = (r + 1) * dims + (c + 1);

					m_auIndicies[index++] = r * dims + c;
					m_auIndicies[index++] = (r + 1) * dims + (c + 1);
					m_auIndicies[index++] = r * dims + (c + 1);
				}
			}
			m_IBO->Bind();
			m_IBO->SetData((dims - 1) * (dims - 1) * 6 * sizeof(uint), m_auIndicies);
			m_VertexArray.PushBuffer(m_IBO);
			m_VertexArray.Unbind();

			m_Texture->GeneratePerlinTexture(64, 64, GL_RED, m_PerlinData);
		}

		void Grid::Render(FlyCamera& camera)
		{
			m_Shader->enable();
			m_Shader->setUnifromMat4("ProjectionView_matrix", camera.GetProjectionView());


			if (m_RenderMode = Manual)
			{
				m_VertexArray.Bind();
				m_IndexBuffer->Bind();
				m_Texture->Bind();
				m_VertexArray.Draw(m_IndexBuffer->GetCount());
				m_Texture->UnBind();
				m_IndexBuffer->Unbind();
				m_VertexArray.Unbind();
			}
			else if (m_RenderMode = RenderAPI)
			{
				m_VertexArray.Bind();
				m_Texture->Bind();
				m_VertexArray.Draw(m_IndexCount);
				m_Texture->UnBind();
				m_VertexArray.Unbind();
			}
			else
			{
				//TODO: Name and log
				std::printf("Render Mode Not Initialized");
			}

			m_Shader->disable();
		}
	}
}