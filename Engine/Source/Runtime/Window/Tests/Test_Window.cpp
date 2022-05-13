#include <gtest/gtest.h>
#include "Window.hpp"

TEST(Window, Property)
{
    const ring::Window window({ 640, 480 }, "Test_Window");

    EXPECT_EQ("Test_Window", window.GetTitle());

    const ring::ClientExtent clientExtent = window.GetClientExtent();
    EXPECT_EQ(640, clientExtent.Width());
    EXPECT_EQ(480, clientExtent.Height());

    const ring::WindowExtent windowExtent = window.GetWindowExtent();
    EXPECT_LE(clientExtent.Width(), windowExtent.Width());
    EXPECT_LE(clientExtent.Height(), windowExtent.Height());
}
