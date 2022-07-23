#include <gtest/gtest.h>
#include "ModuleEntries.hpp"
#include <string>

TEST(ModuleEntries, Construction)
{
    using namespace ring;

    ModuleEntries moduleEntries;

    std::string name = "Name";

    moduleEntries.Entry(
        ModuleEntryPoint::Core_Initialize,
        [&]() {
            name = "Core_Initialize";
        });
    EXPECT_EQ(name, "Name");

    //// 同じエントリに重複できない
    //EXPECT_DEATH_IF_SUPPORTED(
    //    moduleEntries.Entry(
    //        ModuleEntryPoint::Core_Initialize,
    //        []() {}
    //    ),
    //    ""
    //);

    moduleEntries.Call(ModuleEntryPoint::Core_Initialize);
    EXPECT_EQ(name, "Core_Initialize");
}
