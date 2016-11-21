#include "graphics\window.h"
#include "graphics\shader.h"

#include "graphics\Camera\FlyCamera.h"

#include "graphics\FBXModel.h"
#include "graphics\Grid.h"

#include "graphics\Texture.h"

#include "imgui\imgui.h"
#include"imgui\imgui_impl_glfw_gl3.h"
int main()
{
	using namespace LivingEnd;
	using namespace Graphics;

	//Create window
	Window window(960, 540, "LivingEnd Test Screen");
	glClearColor(0.28f, 0.28f, 0.28f, 1.0f);

	//Create GUI
	ImGui_ImplGlfwGL3_Init(window.getWindow(), true);
	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize.x = window.getWidth();
	io.DisplaySize.y = window.getHeight();

	enum SceneSelect
	{
		Terrain,
		Model
	};
	bool RenderMode = false;
	
	//
	// Setup Camera
	//
	FlyCamera camera(10.0f, 0.5f);
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
	//perlin data
	Grid perlinGrid(64, 64);
	//perlinGrid.GenerateGrid();
	perlinGrid.GeneratePerlin();
	FBXModel model("data/FBXModels/soulspear.fbx");
	//model.LoadTextureFromFile("data/FBXModels/soulspear_diffuse.tga");
	model.LoadTextureFromFBX(0);
	//
	// Create DeltaTime
	// TODO: Put this somewhere
	float oldtime = 0.f;
	float newtime = 0.f;
	//TODO: put this somehwere
	float DeltaTime = 0.f;

	//Game loop
	//if false render generation
	glm::vec3 m_ClearColor(0.28f);
	while (!window.closed())
	{
		window.clear();
		glClearColor(m_ClearColor.r, m_ClearColor.g, m_ClearColor.b, 1.0f);
		ImGui_ImplGlfwGL3_NewFrame();
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//calculate dt
		oldtime = newtime;
		newtime = glfwGetTime();
		DeltaTime = (newtime - oldtime);
		camera.Update(DeltaTime);

		/*switch (RenderMode)
		{
		case Terrain:
			perlinGrid.Render(camera);
			break;
		case Model:
			model.Render(&camera);
			break;
		default:
			break;
		}*/
		if (RenderMode == true)
		{
			perlinGrid.Render(camera);
		}
		else
		{
			model.Render(&camera);
		}
		//ImGui::ColorEdit3("Clear Color", glm::value_ptr(m_ClearColor));
		ImGui::Checkbox("Display Terrain", &RenderMode);
		
		ImGui::Render();
		window.update();
	}
	ImGui_ImplGlfwGL3_Shutdown();
	return 0;
}