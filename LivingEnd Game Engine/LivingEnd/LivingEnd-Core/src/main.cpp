#include "graphics\window.h"
#include "graphics\shader.h"

#include "graphics\Camera\FlyCamera.h"

#include "graphics\Buffers\VertexArray.h"
#include "graphics\Buffers\OpenGLBuffer.h"

#include "graphics\FBXModel.h"

int main()
{
	using namespace LivingEnd;
	using namespace Graphics;

	//Create window
	Window window(960, 540, "LivingEnd Test Screen");
	glClearColor(0.28f, 0.28f, 0.28f, 1.0f);
	FlyCamera camera;
	camera.SetInputWindow(window.getWindow());
	//
	//Temp Buffers
	//
	VertexArray temp;
	temp.Bind();
	API::Buffer * vbo = new API::Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
	uint m_rows = 20;
	uint m_cols = 20;
	LivingEnd::Graphics::Vertex* aoVerts = new LivingEnd::Graphics::Vertex[m_rows * m_cols];
	for (uint r = 0; r < m_rows; ++r)
	{
		for (uint c = 0; c < m_cols; ++c)
		{
			aoVerts[r * m_cols + c].position = glm::vec4((float)c, 0, (float)r, 1);

			glm::vec3 colour = glm::vec3(sinf((c / (float)(m_cols - 1))*(r / (float)(m_rows - 1))));
			aoVerts[r * m_cols + c].color = glm::vec4(colour, 1);
		}
	}
	vbo->Bind();
	vbo->SetData((m_rows * m_cols) * sizeof(Vertex), aoVerts);
	temp.PushBuffer(vbo);
	API::Buffer * ibo = new API::Buffer(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
	uint* auIndicies = new uint[(m_rows - 1) * (m_cols - 1) * 6];
	uint index = 0;
	for (uint r = 0; r < (m_rows - 1); ++r)
	{
		for (uint c = 0; c < (m_cols - 1); ++c)
		{
			//tri 1
			auIndicies[index++] = r * m_cols + c;
			auIndicies[index++] = (r + 1) * m_cols + c;
			auIndicies[index++] = (r + 1) * m_cols + (c + 1);

			auIndicies[index++] = r * m_cols + c;
			auIndicies[index++] = (r + 1) * m_cols + (c + 1);
			auIndicies[index++] = r * m_cols + (c + 1);
		}
	}
	ibo->Bind();
	ibo->SetData((m_rows - 1) * (m_cols - 1) * 6 * sizeof(uint), auIndicies);
	temp.PushBuffer(ibo);
	temp.Unbind();

	camera.LookAt(glm::vec3(10), glm::vec3(0), glm::vec3(1));
	camera.SetupPerspective(glm::pi<float>() * 0.25, 16 / 9.f);
	//
	//Set Shader
	//
	Shader shader("data/Shaders/BasicVertexShader.vs", "data/Shaders/BasicFragmentShader.fs");
	shader.enable();
	shader.setUnifromMat4("ProjectionView_matrix", camera.GetProjectionView());
	shader.setUnifrom4f("Colour", glm::vec4(0.2f, 0.3f, 0.8f, 1.0f));
	shader.disable();
	//create model
	//FBXModel model("data/FBXModels/soulspear.fbx");
	//TODO: put this somehwere
	float oldtime = 0.f;
	float newtime = 0.f;

	uint indexcount = (m_rows - 1) * (m_cols - 1) * 6;
	//Game loop
	while (!window.closed())
	{
		window.clear();
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		oldtime = newtime;
		newtime = glfwGetTime();
		camera.Update(newtime - oldtime);

		shader.enable();
		temp.Bind();
		temp.Draw(indexcount);
		temp.Unbind();
		shader.disable();

		//model.Render();

		window.update();
	}
	system("pause");
	delete[] aoVerts;
	delete[] auIndicies;
	delete ibo;
	delete vbo;
	return 0;
}