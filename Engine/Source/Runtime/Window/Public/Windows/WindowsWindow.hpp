#pragma once

#include "Windows/Windows.hpp"
#include "ClientExtent.hpp"
#include "WindowExtent.hpp"
#include <string_view>

namespace ring {

/**
 * \brief Window class for WindowsDesktop (Win32 API)
 */
class WindowsWindow
{
public:
    WindowsWindow(const ClientExtent& clientExtent, std::string_view title);
    ~WindowsWindow();
    
    WindowsWindow(const WindowsWindow&) = delete;
    WindowsWindow(WindowsWindow &&) = delete;

    void operator=(const WindowsWindow &) = delete;
    void operator=(WindowsWindow &&) = delete;

    [[nodiscard]] bool Update();

    void SetTitle(std::string_view title);

    [[nodiscard]] std::string GetTitle() const;

    [[nodiscard]] ClientExtent GetClientExtent() const;

    [[nodiscard]] WindowExtent GetWindowExtent() const;

private:
    static LRESULT CALLBACK WndProc(
        HWND windowHandle, UINT msg, WPARAM wParam, LPARAM lParam
    );

    void Destroy();

    HWND m_hWnd = nullptr;
};

typedef WindowsWindow Window;

} // namespace ring
