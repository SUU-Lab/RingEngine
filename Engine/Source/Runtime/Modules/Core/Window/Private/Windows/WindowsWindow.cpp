#include "Windows/WindowsWindow.hpp"
#include <cassert>

#ifdef CreateWindow
#undef CreateWindow
#endif

namespace ring
{
static constexpr CHAR WINDOW_CLASS_NAME[] = "RING_OVERLAPPED_WINDOW";
static constexpr DWORD WINDOW_STYLE = WS_OVERLAPPEDWINDOW;
static constexpr DWORD WINDOW_STYLE_EX = WS_EX_OVERLAPPEDWINDOW;

[[nodiscard]] static bool InitializeDpiAwareness();

[[nodiscard]] static bool RegisterWindowClass(
    WNDPROC windowProc
    );

[[nodiscard]] static WindowExtent CalcWindowExtent(
    BOOL hasMenu,
    const ClientExtent &clientExtent
    );

[[nodiscard]] static HWND CreateWindow(
    const WindowExtent &windowExtent,
    std::string_view title,
    WindowsWindow *owner
    );

[[nodiscard]] static bool DoSystemEvents(HWND windowHandle);


WindowsWindow::WindowsWindow(const ClientExtent &clientExtent, std::string_view title)
{
    if (!InitializeDpiAwareness()) { assert(false); }
    if (!RegisterWindowClass(&WndProc)) { assert(false); }

    m_hWnd = CreateWindow(
        CalcWindowExtent(FALSE, clientExtent),
        title,
        this
        );
    if (!m_hWnd) { assert(false); }
}

WindowsWindow::~WindowsWindow()
{
    Destroy();
}

bool WindowsWindow::Update()
{
    return DoSystemEvents(m_hWnd);
}

void WindowsWindow::SetTitle(std::string_view title)
{
    ::SetWindowTextA(m_hWnd, title.data());
    if (::GetLastError()) { assert(false); }
}

std::string WindowsWindow::GetTitle() const
{
    CHAR title[128];
    ::GetWindowTextA(m_hWnd, title, ARRAYSIZE(title));
    if (::GetLastError()) { assert(false); }
    return title;
}

ClientExtent WindowsWindow::GetClientExtent() const
{
    RECT rect = {};
    if (!::GetClientRect(m_hWnd, &rect)) { assert(false); }

    return {
        static_cast<std::uint32_t>(rect.right - rect.left),
        static_cast<std::uint32_t>(rect.bottom - rect.top)
    };
}

WindowExtent WindowsWindow::GetWindowExtent() const
{
    RECT rect = {};
    if (!::GetWindowRect(m_hWnd, &rect)) { assert(false); }

    return {
        static_cast<std::uint32_t>(rect.right - rect.left),
        static_cast<std::uint32_t>(rect.bottom - rect.top)
    };
}

HWND WindowsWindow::GetNativeHandle() const
{
    return m_hWnd;
}

LRESULT CALLBACK WindowsWindow::WndProc(
    const HWND windowHandle, const UINT msg, const WPARAM wParam, const LPARAM lParam
    )
{
    if (msg == WM_CREATE)
    {
        const LPCREATESTRUCTA createStruct = reinterpret_cast<LPCREATESTRUCTA>(lParam);
        ::SetWindowLongPtrA(windowHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(createStruct->lpCreateParams));
        if (::GetLastError()) { assert(false); }
        return 0;
    }

    switch (msg)
    {
    case WM_CLOSE:
    {
        WindowsWindow *const self = reinterpret_cast<WindowsWindow *>(::GetWindowLongPtrA(windowHandle, GWLP_USERDATA));
        if (::GetLastError()) { assert(false); }
        assert(self);
        self->Destroy();
    }
        return 0;

    case WM_DESTROY:
        ::PostQuitMessage(0);
        break;

    default:
        break;
    }

    return ::DefWindowProcA(windowHandle, msg, wParam, lParam);
}

void WindowsWindow::Destroy()
{
    if (m_hWnd)
    {
        ::DestroyWindow(m_hWnd);
    }
    m_hWnd = nullptr;
}


[[nodiscard]] static bool InitializeDpiAwareness()
{
    return ::SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE) == TRUE;
}

[[nodiscard]] static bool GetWindowClassInfo(WNDCLASSEX &windowClassEx, const HINSTANCE hInstance)
{
    return ::GetClassInfoEx(hInstance, WINDOW_CLASS_NAME, &windowClassEx) != 0;
}

[[nodiscard]] static HICON LoadApplicationIcon(const TCHAR *iconName, const HINSTANCE hInstance, const int iconSize)
{
    const HICON result = static_cast<HICON>(
        ::LoadImageA(
            hInstance,
            iconName,
            IMAGE_ICON,
            iconSize,
            iconSize,
            LR_DEFAULTSIZE | LR_SHARED));

    return result;
}

[[nodiscard]] static bool RegisterWindowClass(
    const WNDPROC windowProc)
{
    // 拡張ウィンドウクラスの設定
    WNDCLASSEXA windowClassEx = {};

    if (const HINSTANCE hInstance = ::GetModuleHandleA(nullptr); !GetWindowClassInfo(windowClassEx, hInstance))
    {
        constexpr int smallIconSize = 16;
        constexpr int largeIconSize = 64;

        windowClassEx.cbSize = sizeof(WNDCLASSEX);
        windowClassEx.style = CS_OWNDC;
        windowClassEx.lpfnWndProc = windowProc;
        windowClassEx.cbClsExtra = 0;
        windowClassEx.cbWndExtra = 0;
        windowClassEx.hInstance = hInstance;
        windowClassEx.hIcon = LoadApplicationIcon(TEXT(""), hInstance, largeIconSize);
        windowClassEx.hIconSm = LoadApplicationIcon(TEXT(""), hInstance, smallIconSize);
        windowClassEx.hCursor = nullptr;
        windowClassEx.hbrBackground = static_cast<HBRUSH>(::GetStockObject(GRAY_BRUSH));
        windowClassEx.lpszMenuName = nullptr;
        windowClassEx.lpszClassName = WINDOW_CLASS_NAME;
    }

    if (!::RegisterClassExA(&windowClassEx))
    {
        return false;
    }

    return true;
}

[[nodiscard]] static WindowExtent CalcWindowExtent(
    const BOOL hasMenu,
    const ClientExtent &clientExtent
    )
{
    RECT rect = {
        0,
        0,
        static_cast<LONG>(clientExtent.Width()),
        static_cast<LONG>(clientExtent.Height())
    };

    if (!::AdjustWindowRectEx(&rect, WINDOW_STYLE, hasMenu, WINDOW_STYLE_EX)) { assert(false); }

    return {
        static_cast<std::uint32_t>(rect.right - rect.left),
        static_cast<std::uint32_t>(rect.bottom - rect.top)
    };
}

[[nodiscard]] static HWND CreateWindow(
    const WindowExtent &windowExtent,
    const std::string_view title,
    WindowsWindow *owner)
{
    const HWND windowHandle = ::CreateWindowExA(
        WINDOW_STYLE_EX,
        WINDOW_CLASS_NAME,
        title.data(),
        WINDOW_STYLE,
        0, // X
        0, // Y
        static_cast<int>(windowExtent.Width()),
        static_cast<int>(windowExtent.Height()),
        nullptr, // ParentWindow
        nullptr, // MenuHandle
        ::GetModuleHandleA(nullptr),
        owner
        );

    assert(windowHandle);

    ::SetLastError(0);
    ::ShowWindow(windowHandle, SW_SHOWNORMAL);
    if (::GetLastError())
    {
        ::DestroyWindow(windowHandle);
        assert(false);
    }

    ::SetLastError(0);
    ::UpdateWindow(windowHandle);
    if (::GetLastError())
    {
        ::DestroyWindow(windowHandle);
        assert(false);
    }

    ::SetLastError(0);
    ::SetFocus(windowHandle);
    if (::GetLastError())
    {
        ::DestroyWindow(windowHandle);
        assert(false);
    }

    return windowHandle;
}

[[nodiscard]] static bool DoSystemEvents(const HWND windowHandle)
{
    if (::IsWindow(windowHandle) != TRUE) { return false; }

    MSG msg = {};
    while (::PeekMessageA(&msg, windowHandle, 0, 0, PM_REMOVE) != 0)
    {
        ::TranslateMessage(&msg);
        ::DispatchMessageA(&msg);
    }
    return msg.message != WM_QUIT;
}

} // namespace ring
