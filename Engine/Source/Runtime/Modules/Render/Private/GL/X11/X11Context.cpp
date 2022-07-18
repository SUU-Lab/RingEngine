#include "GL/X11/X11Context.hpp"

namespace ring {
inline namespace render {
namespace gl {

X11Context::X11Context(const Window& window)
    : m_display(window.GetDisplay())
    , m_window(window.GetWindow())
{
	const int attributes[] =
	{
		GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
		GLX_RENDER_TYPE,   GLX_RGBA_BIT,
		GLX_DOUBLEBUFFER,  True,  /* Request a double-buffered color buffer with */
		GLX_RED_SIZE,      1,     /* the maximum number of bits per component    */
		GLX_GREEN_SIZE,    1,
		GLX_BLUE_SIZE,     1,
		None
	};

	int fbConfigsNum;
	auto fbConfigs = glXChooseFBConfig(
		m_display,
		DefaultScreen(m_display),
		attributes,
		&fbConfigsNum);

	m_context = glXCreateNewContext(
		m_display,
		fbConfigs[0],
		GLX_RGBA_TYPE,
		NULL,
		True);

	glXMakeContextCurrent(m_display, m_window, m_window, m_context);
}

X11Context::~X11Context()
{
	glXDestroyContext(m_display, m_context);
}

void X11Context::SwapBuffers()
{
	glXSwapBuffers(m_display, m_window);
}

} // namespace gl
} // inline namespace render
} // namespace ring
