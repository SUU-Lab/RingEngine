#include "Runtime.hpp"

#if RING_PLATFORM_WINDOWS || RING_PLATFORM_LINUX
#include "ModuleEntries.hpp"
#include "Core.hpp"
#include "Render.hpp"
#endif

#include <iostream>

namespace ring {

int Main()
{
    std::cout << "ring::Main() is called.\n";

#if RING_PLATFORM_WINDOWS || RING_PLATFORM_LINUX

    ModuleEntries moduleEntries;

    CoreEntry coreEntry;
    coreEntry.Entry(moduleEntries);

    RenderEntry renderEntry(coreEntry);
    renderEntry.Entry(moduleEntries);

    moduleEntries.MainLoop();

#endif

    return 0;
}

} // namespace ring
