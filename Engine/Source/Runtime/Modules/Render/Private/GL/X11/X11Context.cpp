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
		GLX_X_RENDERABLE    , True,
		GLX_DRAWABLE_TYPE   , GLX_WINDOW_BIT,
		GLX_RENDER_TYPE     , GLX_RGBA_BIT,
		GLX_X_VISUAL_TYPE   , GLX_TRUE_COLOR,
		GLX_RED_SIZE        , 8,
		GLX_GREEN_SIZE      , 8,
		GLX_BLUE_SIZE       , 8,
		GLX_ALPHA_SIZE      , 8,
		GLX_DEPTH_SIZE      , 24,
		GLX_STENCIL_SIZE    , 8,
		GLX_DOUBLEBUFFER    , True,
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
