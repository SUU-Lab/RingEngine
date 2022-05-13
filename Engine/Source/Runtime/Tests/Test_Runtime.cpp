#include <gtest/gtest.h>
#include "Runtime.hpp"

TEST(Runtime, EngineName)
{
    EXPECT_EQ("RingEngine", ring::EngineName());
}
