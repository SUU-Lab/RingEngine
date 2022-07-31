#include "WindowExtent.hpp"
#include "googletest.hpp"

TEST(WindowExtent, Construction)
{
    const ring::WindowExtent windowExtent = { 640, 480 };

    EXPECT_EQ(640, windowExtent.Width());
    EXPECT_EQ(480, windowExtent.Height());
}
