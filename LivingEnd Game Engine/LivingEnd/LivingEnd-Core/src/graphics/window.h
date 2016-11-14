#pragma once
//GLFW
#include <gl_core_4_4.h>
#include <glfw\include\GLFW\glfw3.h>
//GLM
#include <glm\glm\vec2.hpp>
#include <glm\glm\mat4x4.hpp>
//std strings
#include <iostream>
//GUI
#include "imgui\imgui_impl_glfw_gl3.h"
namespace LivingEnd { namespace Graphics { 

#define MAX_KEYS 1024
#define MAX_BUTTONS 32
	class Window {
		private:
			//Window data
			int m_Width;
			int m_Height;
			const char * m_Title;
			GLFWwindow  * m_Window;
			//is the wondow closed
			bool m_Closed;

			static bool m_Keys[MAX_KEYS];
			static bool m_MouseButtons[MAX_BUTTONS];
			static double mx, my;
			//initialization function and returns false if it failed
			bool init();
			friend static void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods);
			friend static void mouse_button_callback(GLFWwindow * window, int button, int action, int mods);
			friend static void cursor_position_callback(GLFWwindow * window, double xpos, double ypos);
		public:
			Window(int a_Width, int a_Height, char* a_Title);
			~Window();
			void clear() const;
			void update();
			bool closed() const;

			inline int getWidth()const { return m_Width; }
			inline int getHeight()const { return m_Height; }
			inline GLFWwindow* getWindow()const { return m_Window; }

			bool isKeyPressed(GLuint keycode) const;
			bool isMouseButtonPressed(GLuint button) const;
			void getMousePostion(glm::vec2 &mousePos) const;
		};
	}
}

