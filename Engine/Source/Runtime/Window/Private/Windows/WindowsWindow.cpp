#include "Windows/WindowsWindow.hpp"
#include <cassert>

#ifdef CreateWindow
#undef CreateWindow
#endif

namespace Ring {

constexpr const CHAR WINDOW_CLASS_NAME[] = "SUU_RUNTIME_WINDOW";
constexpr DWORD WINDOW_STYLE = WS_OVERLAPPEDWINDOW;
constexpr DWORD WINDOW_STYLE_EX = WS_EX_OVERLAPPEDWINDOW;

[[nodiscard]] static bool InitializeDpiAwareness();

[[nodiscard]] static bool RegisterWindowClass(
    WNDPROC lpfnWndProc
);

[[nodiscard]] static WindowExtent CalcWindowExtent(
    BOOL hasMenu,
    const ClientExtent& clientExtent
);

[[nodiscard]] static HWND CreateWindow(
    const WindowExtent& windowExtent,
    std::string_view title,
    WindowsWindow* owner
);

[[nodiscard]] static bool DoSystemEvents(HWND hWnd);


WindowsWindow::WindowsWindow(const ClientExtent& clientExtent, std::string_view title)
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

    return ClientExtent(
        static_cast<std::uint32_t>(rect.right - rect.left),
        static_cast<std::uint32_t>(rect.bottom - rect.top)
    );
}

WindowExtent WindowsWindow::GetWindowExtent() const
{
    RECT rect = {};
    if (!::GetWindowRect(m_hWnd, &rect)) { assert(false); }

    return WindowExtent(
        static_cast<std::uint32_t>(rect.right - rect.left),
        static_cast<std::uint32_t>(rect.bottom - rect.top)
    );
}

LRESULT CALLBACK WindowsWindow::WndProc(
    HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam
)
{
    if (Msg == WM_CREATE)
    {
        const LPCREATESTRUCTA createStruct = reinterpret_cast<LPCREATESTRUCTA>(lParam);
        ::SetWindowLongPtrA(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(createStruct->lpCreateParams));
        if (::GetLastError()) { assert(false); }
        return 0;
    }

    switch (Msg)
    {
    case WM_CLOSE:
    {
        WindowsWindow* self = reinterpret_cast<WindowsWindow*>(::GetWindowLongPtrA(hWnd, GWLP_USERDATA));
        if (::GetLastError()) { assert(false); }
        assert(self);
        self->Destroy();
    }
        return 0;

    case WM_DESTROY:
        ::PostQuitMessage(0);
        break;
    }

    return ::DefWindowProcA(hWnd, Msg, wParam, lParam);
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

[[nodiscard]] static bool GetWindowClassInfo(WNDCLASSEX& windowClassEX, HINSTANCE hInstance)
{
    bool result = ::GetClassInfoEx(hInstance, WINDOW_CLASS_NAME, &windowClassEX) != 0;
    return result;
}

[[nodiscard]] static HICON LoadApplicationIcon(const TCHAR* iconName, HINSTANCE hInstance, int iconSize)
{
    HICON result = reinterpret_cast<HICON>(
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
    WNDPROC lpfnWndProc)
{
    constexpr int largeIconSize = 64;
    constexpr int smallIconSize = 16;

    // 拡張ウィンドウクラスの設定
    WNDCLASSEXA windowClassEX = {};

    const HINSTANCE hInstance = ::GetModuleHandleA(nullptr);

    if (!GetWindowClassInfo(windowClassEX, hInstance))
    {
        windowClassEX.cbSize = sizeof(WNDCLASSEX);
        windowClassEX.style = CS_OWNDC;
        windowClassEX.lpfnWndProc = lpfnWndProc;
        windowClassEX.cbClsExtra = 0;
        windowClassEX.cbWndExtra = 0;
        windowClassEX.hInstance = hInstance;
        windowClassEX.hIcon = LoadApplicationIcon(TEXT(""), hInstance, largeIconSize);
        windowClassEX.hIconSm = LoadApplicationIcon(TEXT(""), hInstance, smallIconSize);
        windowClassEX.hCursor = NULL;
        windowClassEX.hbrBackground = (HBRUSH)::GetStockObject(GRAY_BRUSH);
        windowClassEX.lpszMenuName = NULL;
        windowClassEX.lpszClassName = WINDOW_CLASS_NAME;
    }

    if (!::RegisterClassExA(&windowClassEX))
    {
        return false;
    }

    return true;
}

[[nodiscard]] static WindowExtent CalcWindowExtent(
    BOOL hasMenu,
    const ClientExtent& clientExtent
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
    const WindowExtent& windowExtent,
    std::string_view title,
    WindowsWindow* owner)
{
    HWND hWnd = ::CreateWindowExA(
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
        reinterpret_cast<LPVOID>(owner)
    );

    assert(hWnd);

    ::SetLastError(0);
    ::ShowWindow(hWnd, SW_SHOWNORMAL);
    if (::GetLastError()) { ::DestroyWindow(hWnd); assert(false); }

    ::SetLastError(0);
    ::UpdateWindow(hWnd);
    if (::GetLastError()) { ::DestroyWindow(hWnd); assert(false); }

    ::SetLastError(0);
    ::SetFocus(hWnd);
    if (::GetLastError()) { ::DestroyWindow(hWnd); assert(false); }

    return hWnd;
}

[[nodiscard]] static bool DoSystemEvents(HWND hWnd)
{
    if (::IsWindow(hWnd) != TRUE) { return false; }

    MSG msg = { 0 };
    while (::PeekMessageA(&msg, hWnd, 0, 0, PM_REMOVE) != 0)
    {
        ::TranslateMessage(&msg);
        ::DispatchMessageA(&msg);
    }
    return msg.message != WM_QUIT;
}

} // namespace Ring
