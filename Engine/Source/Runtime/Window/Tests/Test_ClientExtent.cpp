#include "ClientExtent.hpp"
#include <gtest/gtest.h>

TEST(ClientExtent, Construction)
{
    const ring::ClientExtent clientExtent = { 641, 480 };

    EXPECT_EQ(640, clientExtent.Width());
    EXPECT_EQ(480, clientExtent.Height());
}
