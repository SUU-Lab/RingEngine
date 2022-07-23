#pragma once

#include "ModuleEntryPoint.hpp"
#include <functional>
#include <array>

namespace ring {

class ModuleEntries final
{
public:
    typedef std::function<void()> EntryFunction;

public:
    ModuleEntries();

    void Entry(
        const ModuleEntryPoint moduleEntryPoint,
        const EntryFunction& entryFunction);

    void MainLoop();

    void ExitRequest();

    void Call(const ModuleEntryPoint moduleEntryPoint);

private:
    bool m_exitRequested;
    std::array<EntryFunction, ModuleEntryPointNum> m_entryFunctions;
};

} // namespace ring
