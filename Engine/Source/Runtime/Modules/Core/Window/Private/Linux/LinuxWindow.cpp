#include "Linux/LinuxWindow.hpp"
#include <cassert>
#include <iostream>

namespace ring {

static void ErrorCallback(const int error, const char* description)
{
	std::cerr << "Error:" << description << '\n';
}

LinuxWindow::LinuxWindow(const ClientExtent& clientExtent, std::string_view title)
{
	::glfwSetErrorCallback(ErrorCallback);

    const int result = ::glfwInit();
	assert(result);

	::glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	::glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	::glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	::glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	::glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 
#ifndef NDEBUG
		GLFW_TRUE
#else
		GLFW_FALSE
#endif
	);

	::glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	m_window = ::glfwCreateWindow(
		clientExtent.Width(),
		clientExtent.Height(),
		title.data(),
		nullptr,
		nullptr);

	::glfwSetWindowUserPointer(m_window, this);
	//::glfwSetWindowPosCallback(m_window, GLFWWindow::OnMove);
	//::glfwSetWindowSizeCallback(m_window, GLFWWindow::OnResize);
	//::glfwSetFramebufferSizeCallback(m_window, GLFWWindow::OnFramebufferSize);
	//::glfwSetWindowContentScaleCallback(m_window, GLFWWindow::OnScalingChange);
	//::glfwSetWindowIconifyCallback(m_window, GLFWWindow::OnIconify);
	//::glfwSetWindowMaximizeCallback(m_window, GLFWWindow::OnMaximize);
	//::glfwSetWindowFocusCallback(m_window, GLFWWindow::OnFocus);

	SetTitle(title);
}

LinuxWindow::~LinuxWindow()
{
	::glfwTerminate();
}

bool LinuxWindow::Update()
{
	//::glfwWaitEvents();

	::glfwPollEvents();

	return ::glfwWindowShouldClose(m_window) == GL_FALSE;
}

void LinuxWindow::SetTitle(std::string_view title)
{
	m_title = title;
	::glfwSetWindowTitle(m_window, title.data());
}

std::string LinuxWindow::GetTitle() const
{
	return m_title;
}

ClientExtent LinuxWindow::GetClientExtent() const
{
	int width = 0, height = 0;

	::glfwGetFramebufferSize(m_window, &width, &height);

	return {
		static_cast<std::uint32_t>(width),
		static_cast<std::uint32_t>(height)
	};
}

WindowExtent LinuxWindow::GetWindowExtent() const
{
	int width = 0, height = 0;

	::glfwGetWindowSize(m_window, &width, &height);

	return {
		static_cast<std::uint32_t>(width),
		static_cast<std::uint32_t>(height)
	};
}

::GLFWwindow* LinuxWindow::GetWindow() const
{
    return m_window;
}

} // namespace ring
