#include "shader.h"

namespace LivingEnd {
	namespace Graphics {

		Shader::Shader(const char * vertPath, const char * fragPath)
			: m_VertPath(vertPath), m_FragPath(fragPath)
		{
			m_ShaderID = load();
		}
		Shader::~Shader()
		{

		}
		GLuint Shader::load()
		{
			//
			//create variables
			//
			GLuint program = glCreateProgram();
			int success = GL_FALSE;
			GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
			GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
			//
			//Bind file paths
			//
			std::string vSource = FileUtilities::read_file(m_VertPath);
			std::string fSource = FileUtilities::read_file(m_FragPath);
			//
			//Create Vertex Shader
			//

			const char* p_vSource = vSource.c_str();
			glShaderSource(vertexShader, 1, (const char**)&p_vSource, 0);
			glCompileShader(vertexShader);
			glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
			if (success == GL_FALSE)
			{
				int infoLogLength = 0;
				glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &infoLogLength);
				char* infoLog = new char[infoLogLength];

				glGetShaderInfoLog(vertexShader, infoLogLength, 0, infoLog);
				printf("Error: Failed to compile Vertex Shader! \n");
				printf("%s\n", infoLog);
				delete[] infoLog;
				glDeleteShader(vertexShader);
				return 0;
			}
			//
			//Create Fragment Shader
			//
			const char* p_fSource = fSource.c_str();
			glShaderSource(fragmentShader, 1, (const char**)&p_fSource, 0);
			glCompileShader(fragmentShader);
			if (success == GL_FALSE)
			{
				int infoLogLength = 0;
				glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &infoLogLength);
				char* infoLog = new char[infoLogLength];

				glGetShaderInfoLog(vertexShader, infoLogLength, 0, infoLog);
				printf("Error: Failed to compile Fragment Shader! \n");
				printf("%s\n", infoLog);
				delete[] infoLog;
				glDeleteShader(vertexShader);
				return 0;
			}
			//
			//Link the program
			//
			glAttachShader(program, vertexShader);
			glAttachShader(program, fragmentShader);
			glLinkProgram(program);

			glGetProgramiv(program, GL_LINK_STATUS, &success);
			if (success == GL_FALSE)
			{
				int infoLogLength = 0;
				glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
				char* infoLog = new char[infoLogLength];

				glGetProgramInfoLog(program, infoLogLength, 0, infoLog);
				printf("Error: Failed to link shaders! \n");
				printf("%s\n", infoLog);
				delete[] infoLog;
			}
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
			return program;
		}
		GLint Shader::getUniformLocation(const GLchar * name)
		{
			return glGetUniformLocation(m_ShaderID, name);
		}
		void Shader::setUnifrom1f(const GLchar * name, float value)
		{
			glUniform1f(getUniformLocation(name), value);
		}
		void Shader::setUnifrom1i(const GLchar * name, int value)
		{
			glUniform1i(getUniformLocation(name), value);
		}
		void Shader::setUnifrom2f(const GLchar * name, const glm::vec2 vec2 )
		{
			glUniform2f(getUniformLocation(name), vec2.x, vec2.y);
		}
		void Shader::setUnifrom3f(const GLchar * name, const glm::vec3 vec3)
		{
			glUniform3f(getUniformLocation(name), vec3.x, vec3.y, vec3.z);
		}
		void Shader::setUnifrom4f(const GLchar * name, const glm::vec4 vec4)
		{
			glUniform4f(getUniformLocation(name), vec4.x, vec4.y, vec4.z, vec4.w);
		}
		void Shader::setUnifromMat4(const GLchar * name, const glm::mat4& mat4)
		{
			glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, value_ptr(mat4));
		}
		void Shader::enable() const
		{
			glUseProgram(m_ShaderID);
		}
		void Shader::disable() const
		{
			glUseProgram(0);
		}
	}
}