#include "X11/X11Window.hpp"
#include <X11/Xutil.h>
#include <X11/Xatom.h>

namespace ring {

X11Window::X11Window(const ClientExtent& clientExtent, std::string_view title)
{
    m_display = XOpenDisplay(nullptr);

    m_window = XCreateSimpleWindow(
        m_display,
        RootWindow(m_display, 0),
        0, // X
        0, // Y
        clientExtent.Width(),
        clientExtent.Height(),
        1,	// border_width
        0,	// border
        0);	// background

    SetTitle(title);
    
    XSelectInput(
        m_display,
        m_window,
        StructureNotifyMask);

    XMapWindow(m_display, m_window);
    
    XFlush(m_display);
}

X11Window::~X11Window()
{
    Destroy();
}

bool X11Window::Update()
{
    XEvent xEvent;
    XNextEvent(m_display, &xEvent);

    switch (xEvent.type)
    {
    case DestroyNotify:
        Destroy();
        return false;
    }
    return true;
}

void X11Window::SetTitle(std::string_view title)
{
    XTextProperty text;

    text.value = (unsigned char*)title.data();
    text.encoding = XA_STRING;
    text.format = 8;
    text.nitems = title.length();

    XSetWMName(
        m_display,
        m_window,
        &text);

    XFlush(m_display);
}

std::string X11Window::GetTitle() const
{
    XTextProperty text;
    XGetWMName(m_display, m_window, &text);

    return std::string(reinterpret_cast<const char*>(text.value));
}

ClientExtent X11Window::GetClientExtent() const
{
    ::Window root;
    int x, y;
    unsigned int width, height;
    unsigned int border, depth;

    XGetGeometry(
        m_display,
        m_window,
        &root,
        &x, &y,
        &width, &height,
        &border, &depth);

    return ClientExtent(
        static_cast<std::uint32_t>(width),
        static_cast<std::uint32_t>(height));
}

WindowExtent X11Window::GetWindowExtent() const
{
    // X11でフレームを含むサイズの取得方法がわからないので、クライアントサイズをそのまま返す
    const ClientExtent clientExtent = GetClientExtent();

    return WindowExtent(
        clientExtent.Width(),
        clientExtent.Height());
}

void X11Window::Destroy()
{
    if (!m_display) { return; }

    XSetCloseDownMode(m_display, DestroyAll);
    XCloseDisplay(m_display);
    m_display = nullptr;
}

} // namespace ring
