#include "GL/GLFW/GLFWContext.hpp"

namespace ring {
inline namespace render {
namespace gl {

GLFWContext::GLFWContext(const Window& window)
	: m_window(window.GetWindow())
{
	::glfwMakeContextCurrent(m_window);
	::glfwSwapInterval(1);

	::glewExperimental = GL_TRUE;
	::glewInit();

	//::glfwSwapInterval(1);
}

GLFWContext::~GLFWContext()
{
	
}

void GLFWContext::SwapBuffers()
{
	::glfwSwapBuffers(m_window);
}

} // namespace gl
} // inline namespace render
} // namespace ring
