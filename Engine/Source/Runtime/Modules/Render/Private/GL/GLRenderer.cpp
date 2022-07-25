#include "GL/GLRenderer.hpp"
#include "Math.hpp"


namespace {

struct HSV
{
	float h;
	float s;
	float v;
};

struct RGB
{
	float r;
	float g;
	float b;
};

inline RGB HSVtoRGB(HSV const& hsv)
{
	float h = hsv.h;
	float s = hsv.s;
	float v = hsv.v;

	float r = v;
	float g = v;
	float b = v;
	if (s > 0.0f)
	{
		h *= 6.0f;
		const int i = (int)h;
		const float f = h - (float)i;
		switch (i)
		{
		default:
		case 0:
			g *= 1 - s * (1 - f);
			b *= 1 - s;
			break;
		case 1:
			r *= 1 - s * f;
			b *= 1 - s;
			break;
		case 2:
			r *= 1 - s;
			b *= 1 - s * (1 - f);
			break;
		case 3:
			r *= 1 - s;
			g *= 1 - s * f;
			break;
		case 4:
			r *= 1 - s * (1 - f);
			g *= 1 - s;
			break;
		case 5:
			g *= 1 - s;
			b *= 1 - s * f;
			break;
		}
	}
	return { r, g, b };
}

}

namespace ring {
inline namespace render {

#if RING_PLATFORM_WINDOWS || RING_PLATFORM_LINUX
GLRenderer::GLRenderer(const Window& window)
    : m_context(std::make_unique<gl::Context>(window))
{}
#endif

#if RING_PLATFORM_ANDROID
GLRenderer::GLRenderer(ANativeWindow* window)
    : m_context(std::make_unique<gl::Context>(window))
{}
#endif

GLRenderer::~GLRenderer()
{}

void GLRenderer::Begin()
{
	static HSV hsv = { 0.0f, 1.0f, 1.0f };

	const RGB rgb = HSVtoRGB(hsv);

    glClearColor(rgb.r, rgb.g, rgb.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

	hsv.h += 0.01f;
	if (hsv.h > 1.0f)
	{
		hsv.h = 0;
	}
}

void GLRenderer::End()
{
    glFlush();
    m_context->SwapBuffers();
}

} // inline namespace render
} // namespace ring
