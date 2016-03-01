#include "graphics\window.h"
#include "graphics\shader.h"

#include "graphics\VertexBuffer.h"
#include "graphics\IndexBuffer.h"
#include "graphics\VertexArray.h"

#include "graphics\Renderable2d.h"
#include "graphics\Simple2DRenderer.h"

int main()
{
	using namespace LivingEnd;
	using namespace Graphics;
	using namespace glm;

	//Create window
	Window window(960, 540, "LivingEnd Test Screen");
	//glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	//set shader
	mat4 m_ortho = glm::ortho(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
	Shader shader("data/BasicVertexShader.vs", "data/BasicFragmentShader.fs");
	shader.enable();
	shader.setUnifromMat4("projection_matrix", m_ortho);
	shader.setUnifromMat4("model_matrix", glm::translate(vec3(4, 3, 0)));
	shader.setUnifrom2f("light_pos", vec2(4.0f, 1.5f));
	shader.setUnifrom4f("Colour", vec4(0.2f, 0.3f, 0.8f, 1.0f));

	//create sprite
	Renderable2D sprite1(vec3(5, 5, 0), vec2(4, 4), vec4(1, 0, 1, 1), shader);
	Renderable2D sprite2(vec3(1, 5, 0), vec2(2, 3), vec4(0, 1, 1, 1), shader);
	Simple2DRenderer renderer;

	//Game loop
	while (!window.closed())
	{
		window.clear();
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		vec2 mousePos;
		window.getMousePostion(mousePos);
		shader.setUnifrom2f("light_pos", vec2((float)(mousePos.x * 16.0f / 960.0f), (float)(9.0f - mousePos.y * 9.0f / 540.0f)));
		renderer.submit(&sprite1);
		renderer.submit(&sprite2);
		renderer.flush();
		window.update();
	}
	system("pause");
	return 0;
}