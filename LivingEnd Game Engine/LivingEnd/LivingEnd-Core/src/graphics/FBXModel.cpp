#include "FBXModel.h"

namespace LivingEnd { namespace Graphics {

	void create_OpenGL_Buffers(FBXFile* fbx);
	void cleanup_OpenGl_Buffers(FBXFile* fbx);

	FBXModel::FBXModel(const char* model_path, const char* shader_path)
	{
		Init(model_path);
		m_Shader = new Shader("data/Shaders/FBXVertexShader.vs", "data/Shaders/FBXFragmentShader.fs");
	}


	FBXModel::~FBXModel()
	{
		cleanup_OpenGl_Buffers(m_FBX);
		delete m_FBX;
	}

	void FBXModel::Init(const char* path)
	{
		m_FBX = new FBXFile();
		m_FBX->load(path);
		create_OpenGL_Buffers(m_FBX);
	}

	void FBXModel::Render()
	{
		m_Shader->enable();
		for (uint i = 0; i < m_FBX->getMeshCount(); ++i)
		{
			FBXMeshNode* mesh = m_FBX->getMeshByIndex(i);
			uint* glData = (uint*)mesh->m_userData;
			glBindVertexArray(glData[0]);
			glDrawElements(GL_TRIANGLES, (uint)mesh->m_indices.size(), GL_UNSIGNED_INT, 0);
		}
	}

	void create_OpenGL_Buffers(FBXFile* fbx)
	{
		//Creating the OpenGL buffers for each mesh
		for (uint i = 0; i < fbx->getMeshCount(); ++i)
		{
			FBXMeshNode* mesh = fbx->getMeshByIndex(i);
			uint* glData = new uint[3];
			glGenVertexArrays(1, &glData[0]);
			glBindVertexArray(glData[0]);

			glGenBuffers(1, &glData[1]);
			glGenBuffers(1, &glData[2]);

			glBindBuffer(GL_ARRAY_BUFFER, glData[1]);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glData[2]);

			glBufferData(GL_ARRAY_BUFFER, mesh->m_vertices.size() * sizeof(FBXVertex), mesh->m_vertices.data(), GL_STATIC_DRAW);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->m_indices.size() * sizeof(uint), mesh->m_indices.data(), GL_STATIC_DRAW);
			//Position data
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), 0);
			//Normal
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), ((char*)0) + FBXVertex::NormalOffset);

			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

			mesh->m_userData = glData;
			delete[] glData;
		}
	}

	void cleanup_OpenGl_Buffers(FBXFile* fbx)
	{
		for(uint i = 0; i < fbx->getMeshCount(); ++i)
		{
			FBXMeshNode* mesh = fbx->getMeshByIndex(i);

			uint* glData = (uint*)mesh->m_userData;

			glDeleteVertexArrays(1, &glData[0]);
			glDeleteBuffers(1, &glData[1]);
			glDeleteBuffers(1, &glData[2]);

			delete[] glData;
		}
	}
}
}
