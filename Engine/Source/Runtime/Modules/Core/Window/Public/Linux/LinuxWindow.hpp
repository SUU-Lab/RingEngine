#pragma once

#include "ClientExtent.hpp"
#include "WindowExtent.hpp"
#include <string_view>
#include <string>

#include "glew.hpp"
#include "glfw.hpp"

namespace ring {

class LinuxWindow final
{
public:
    LinuxWindow(const ClientExtent& clientExtent, std::string_view title);
    ~LinuxWindow();

    [[nodiscard]] bool Update();

    void SetTitle(std::string_view title);

    [[nodiscard]] std::string GetTitle() const;

    [[nodiscard]] ClientExtent GetClientExtent() const;

    [[nodiscard]] WindowExtent GetWindowExtent() const;

    [[nodiscard]] ::GLFWwindow* GetWindow() const;

//private:
//    static void OnMove(GLFWwindow* window, int xpos, int ypos);
//    static void OnResize(GLFWwindow* window, int width, int height);
//    static void OnFramebufferSize(GLFWwindow* window, int width, int height);
//    static void OnScalingChange(GLFWwindow* window, float xscale, float yscale);
//    static void OnIconify(GLFWwindow* window, int iconified);
//    static void OnMaximize(GLFWwindow* window, int maximized);
//    static void OnFocus(GLFWwindow* window, int focused);

private:
    ::GLFWwindow* m_window;
    std::string m_title;
};

typedef LinuxWindow Window;

} // namespace ring
