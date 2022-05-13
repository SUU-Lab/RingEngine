#pragma once

#include "Windows/Windows.hpp"
#include "ClientExtent.hpp"
#include "WindowExtent.hpp"
#include <string_view>

namespace ring {

class WindowsWindow
{
public:
    WindowsWindow(const ClientExtent& clientExtent, std::string_view title);
    ~WindowsWindow();

    bool Update();

    std::string GetTitle() const;

    ClientExtent GetClientExtent() const;

    WindowExtent GetWindowExtent() const;

private:
    static LRESULT CALLBACK WndProc(
        HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam
    );

    void Destroy();

    HWND m_hWnd = nullptr;
};

typedef WindowsWindow Window;

} // namespace ring
