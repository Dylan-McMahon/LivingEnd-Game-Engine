#include "window.h"
namespace LivingEnd {
	namespace Graphics {

		bool Window::m_Keys[MAX_KEYS];
		bool Window::m_MouseButtons[MAX_BUTTONS];
		double Window::mx;
		double Window::my;
		void window_resize(GLFWwindow * window, int width, int height);
		
		Window::Window(int a_Width, int a_Height, char* a_Title)
		{
			m_Width = a_Width;
			m_Height = a_Height;
			m_Title = a_Title;
			if (init() == false)
			{
				glfwTerminate();
			}

			for(int i = 0; i < MAX_KEYS; ++i)
			{
				m_Keys[i] = false;
			}
			for(int i = 0; i < MAX_BUTTONS; ++i)
			{
				m_MouseButtons[i] = false;
			}
		}
		Window::~Window()
		{
			glfwTerminate();
		}
		bool Window::init()
		{
			if (!glfwInit())
			{
				std::cout << "Failed to initialize OpenGL." << std::endl;
				return false;
			}
			m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
			if (m_Window == nullptr)
			{
				std::cout << "Failed to create window." << std::endl;
				return false;
			}
			glfwMakeContextCurrent(m_Window);
			glfwSetWindowUserPointer(m_Window, this);
			glfwSetWindowSizeCallback(m_Window, window_resize);
			glfwSetKeyCallback(m_Window, key_callback);
			glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
			glfwSetCursorPosCallback(m_Window, cursor_position_callback);
			if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
			{
				glfwDestroyWindow(m_Window);
				std::cout << "Failed to load window." << std::endl;
				return false;
			}
			return true;
		}

		bool Window::isKeyPressed(GLuint keycode) const
		{
			//TODO:LOG
			if (keycode >= MAX_KEYS)
				return false;
			return m_Keys[keycode];
		}
		bool Window::isMouseButtonPressed(GLuint button) const
		{
			if (button >= MAX_BUTTONS)
				return false;
			return m_MouseButtons[button];
		}
		void Window::getMousePostion(glm::vec2 &mousePos) const
		{
			mousePos.x = (float)mx;
			mousePos.y = (float)my;
		}
		void Window::clear() const
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			ImGui_ImplGlfwGL3_NewFrame();
		}
		void Window::update()
		{
			glfwGetFramebufferSize(m_Window, &m_Width, &m_Height);
			glViewport(0, 0, m_Width, m_Height); 
			GLenum error = glGetError();
			if (error != GL_NO_ERROR)
				std::cout << "OpenGL error: " << error << std::endl;
			glfwSwapBuffers(m_Window);
			glfwPollEvents();
		}
		bool Window::closed() const
		{
			return glfwWindowShouldClose(m_Window) == 1;
		}
		//
		//callbacks
		//
		void window_resize(GLFWwindow * window, int width, int height)
		{
			glViewport(0, 0, width, height);
		}
		void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
		{
			Window * win = (Window*)glfwGetWindowUserPointer(window);
			win->m_Keys[key] = action != GLFW_RELEASE;
		}
		void mouse_button_callback(GLFWwindow * window, int button, int action, int mods)
		{
			Window * win = (Window*)glfwGetWindowUserPointer(window);
			win->m_MouseButtons[button] = action != GLFW_RELEASE;
		}
		void cursor_position_callback(GLFWwindow * window, double xpos, double ypos)
		{
			Window * win = (Window*)glfwGetWindowUserPointer(window);
			win->mx = xpos;
			win->my = ypos;
		}
	}
}