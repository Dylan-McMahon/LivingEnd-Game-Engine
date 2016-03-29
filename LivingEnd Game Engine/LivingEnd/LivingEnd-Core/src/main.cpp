#include "graphics\window.h"
#include "graphics\shader.h"

#include "graphics\Camera\FlyCamera.h"

#include "graphics\FBXModel.h"
#include "graphics\Grid.h"

int main()
{
	using namespace LivingEnd;
	using namespace Graphics;

	//Create window
	Window window(960, 540, "LivingEnd Test Screen");
	glClearColor(0.28f, 0.28f, 0.28f, 1.0f);
	//
	// Setup Camera
	//
	FlyCamera camera;
	camera.SetInputWindow(window.getWindow());
	camera.LookAt(glm::vec3(10), glm::vec3(0), glm::vec3(0, 1, 0));
	camera.SetupPerspective(glm::pi<float>() * 0.25f, (float)window.getWidth() / (float)window.getHeight(), 0.1f, 1000.f);
	//
	// Set Shader
	//
	Shader shader("data/Shaders/BasicVertexShader.vs", "data/Shaders/BasicFragmentShader.fs");
	shader.enable();
	shader.setUnifromMat4("ProjectionView_matrix", camera.GetProjectionView());
	shader.setUnifrom4f("Colour", glm::vec4(0.2f, 0.3f, 0.8f, 1.0f));
	shader.disable();
	//
	// Create models
	//
	Grid grid(20, 20);
	grid.GenerateGrid();

	Grid perlinGrid(20, 0);
	perlinGrid.GeneratePerlin();

	FBXModel model("data/FBXModels/soulspear.fbx");
	//
	// Create DeltaTime
	// TODO: Put this somewhere
	float oldtime = 0.f;
	float newtime = 0.f;
	//TODO: put this somehwere
	float DeltaTime = 0.f;

	//Game loop
	while (!window.closed())
	{
		window.clear();
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		//calculate dt
		oldtime = newtime;
		newtime = glfwGetTime();
		DeltaTime = (newtime - oldtime);
		camera.Update(DeltaTime);

		shader.enable();
		shader.setUnifromMat4("ProjectionView_matrix", camera.GetProjectionView());
		//grid.Render(camera);
		perlinGrid.Render(camera);
		shader.disable();

		model.Render(&camera);
		
window.update();
	}
	system("pause");
	return 0;
}