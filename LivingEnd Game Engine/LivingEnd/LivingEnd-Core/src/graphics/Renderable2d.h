#pragma once
#include "Buffers\VertexBuffer.h"
#include "Buffers\IndexBuffer.h"
#include "Buffers\VertexArray.h"
#include "Buffers\OpenGLBuffer.h"
#include "glm\glm\glm.hpp"
#include "glm\glm\ext.hpp"
#include "shader.h"
namespace LivingEnd { namespace Graphics {

		class Renderable2D
		{
		public:
			Renderable2D(glm::vec3 position, glm::vec2 size, glm::vec4 color, Shader& shader)
				: m_Position(position), m_Size(size), m_Colour(color), m_Shader(shader)
			{
				m_VertexArray = new VertexArray();
				GLfloat verticies[] =
				{
					0,		0,		0,
					0,		size.y, 0,
					size.x,	size.y, 0,
					size.x, 0,		0
				};
				GLfloat colors[] =
				{
					color.r, color.g, color.b, color.a,
					color.r, color.g, color.b, color.a,
					color.r, color.g, color.b, color.a,
					color.r, color.g, color.b, color.a
				};
				API::Buffer vertBuffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
				vertBuffer.SetData(4 * 3, (void*)verticies);
				API::Buffer colorBuffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
				colorBuffer.SetData(4 * 4, (void*)colors);
				m_VertexArray->PushBuffer(&vertBuffer);
				m_VertexArray->PushBuffer(&colorBuffer);
				GLushort indicies[] = { 0, 1, 2, 2, 3, 0 };
				m_IndexBuffer = new IndexBuffer(indicies, 6);
			}

			~Renderable2D()
			{
				delete m_VertexArray;
				delete m_IndexBuffer;
			}
		protected:
			glm::vec3 m_Position;
			glm::vec2 m_Size;
			glm::vec4 m_Colour;

			VertexArray* m_VertexArray;
			IndexBuffer* m_IndexBuffer;

			Shader& m_Shader;
		public:
			inline const VertexArray* getVAO() const { return m_VertexArray; };
			inline const IndexBuffer* getIBO() const { return m_IndexBuffer; };
			inline Shader& getShader() const { return m_Shader; };
			inline const glm::vec3& getPosition() const { return m_Position; };
			inline const glm::vec2& getSize() const { return m_Size; };
			inline const glm::vec4& getColor() const { return m_Colour; };
		};
}
}