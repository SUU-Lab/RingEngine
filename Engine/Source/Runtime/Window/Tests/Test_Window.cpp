#include <gtest/gtest.h>
#include "Window.hpp"

TEST(Window, Property)
{
    const Ring::Window window({ 640, 480 }, "Test_Window");

    EXPECT_EQ("Test_Window", window.GetTitle());

    const Ring::ClientExtent clientExtent = window.GetClientExtent();
    EXPECT_EQ(640, clientExtent.Width());
    EXPECT_EQ(480, clientExtent.Height());

    const Ring::WindowExtent windowExtent = window.GetWindowExtent();
    EXPECT_LE(clientExtent.Width(), windowExtent.Width());
    EXPECT_LE(clientExtent.Height(), windowExtent.Height());
}
