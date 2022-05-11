#pragma once

#include "ClientExtent.hpp"
#include "WindowExtent.hpp"
#include <string_view>
#include <string>
#include <X11/Xlib.h>

namespace Ring {

class X11Window
{
public:
    X11Window(const ClientExtent& clientExtent, std::string_view title);
    ~X11Window();

    bool Update();

    void SetTitle(std::string_view title);

    std::string GetTitle() const;

    ClientExtent GetClientExtent() const;

    WindowExtent GetWindowExtent() const;

private:
    void Destroy();

    Display* m_display;
    ::Window m_window;
};

typedef X11Window Window;

} // namespace Ring
