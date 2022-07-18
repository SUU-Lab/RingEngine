#pragma once

#include "ClientExtent.hpp"
#include "WindowExtent.hpp"
#include <string_view>
#include <string>
#include <X11/Xlib.h>

namespace ring {

class X11Window
{
public:
    X11Window(const ClientExtent& clientExtent, std::string_view title);
    ~X11Window();

    [[nodiscard]] bool Update();

    void SetTitle(std::string_view title);

    [[nodiscard]] std::string GetTitle() const;

    [[nodiscard]] ClientExtent GetClientExtent() const;

    [[nodiscard]] WindowExtent GetWindowExtent() const;

    [[nodiscard]] Display* GetDisplay() const;

    [[nodiscard]] ::Window GetWindow() const;

private:
    void Destroy();

    Display* m_display;
    ::Window m_window;
};

typedef X11Window Window;

} // namespace ring
