#include "ClientExtent.hpp"
#include <gtest/gtest.h>

TEST(ClientExtent, Construction)
{
    Ring::ClientExtent clientExtent = { 640, 480 };

    EXPECT_EQ(640, clientExtent.Width());
    EXPECT_EQ(480, clientExtent.Height());
}