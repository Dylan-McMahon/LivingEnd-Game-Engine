#pragma once
#include "utilities\fileInput.h"
#include "gl_core_4_4.h"
#include "glfw\include\GLFW\glfw3.h"
#include "glm\glm\glm.hpp"
#include "glm\glm\ext.hpp"
namespace LivingEnd { namespace Graphics {

	class Shader
	{
	private:
		const char * m_VertPath;
		const char * m_FragPath;
		GLuint m_ShaderID;

		GLuint load();
		GLint getUniformLocation(const GLchar * name);
	public:
		Shader(const char * vertPath, const char * fragPath);
		~Shader();


		void setUnifrom1f(const GLchar * name, float value);
		void setUnifrom1i(const GLchar * name, int value);
		void setUnifrom2f(const GLchar * name, const glm::vec2 vec2);
		void setUnifrom3f(const GLchar * name, const glm::vec3 vec3);
		void setUnifrom4f(const GLchar * name, const glm::vec4 vec4);
		void setUnifromMat4(const GLchar * name, const glm::mat4& mat4);

		void enable() const;
		void disable() const;
	};



} }