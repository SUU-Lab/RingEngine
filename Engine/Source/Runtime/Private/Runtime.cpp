#include "Runtime.hpp"
#include "ModuleEntries.hpp"
#include "Core.hpp"
#include "Render.hpp"
#include <iostream>

namespace ring {

int Main(LaunchState* launchState)
{
    std::cout << "ring::Main() is called.\n";

    ModuleEntries moduleEntries;

    std::unique_ptr<CoreEntry> coreEntry = CoreEntry::Make(launchState);
    coreEntry->Entry(moduleEntries);

    std::unique_ptr<RenderEntry> renderEntry = RenderEntry::Make(*coreEntry);
    renderEntry->Entry(moduleEntries);

    moduleEntries.MainLoop();

    return 0;
}

} // namespace ring
