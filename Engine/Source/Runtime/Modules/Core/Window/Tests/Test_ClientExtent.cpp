#include "ClientExtent.hpp"
#include "googletest.hpp"

TEST(ClientExtent, Construction)
{
    const ring::ClientExtent clientExtent = { 640, 480 };

    EXPECT_EQ(640, clientExtent.Width());
    EXPECT_EQ(480, clientExtent.Height());
}
