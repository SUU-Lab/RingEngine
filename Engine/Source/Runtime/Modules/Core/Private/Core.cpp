#include "Core.hpp"
#include "ModuleEntries.hpp"
#include <cassert>

namespace ring {

void CoreEntry::Entry(ModuleEntries& moduleEntries)
{
    m_moduleEntries = &moduleEntries;

    moduleEntries.Entry(
        ModuleEntryPoint::Core_Initialize,
        std::bind(&CoreEntry::Initialize, this));

    moduleEntries.Entry(
        ModuleEntryPoint::Core_Setup,
        std::bind(&CoreEntry::Setup, this));

    moduleEntries.Entry(
        ModuleEntryPoint::Core_Start,
        std::bind(&CoreEntry::Start, this));

    moduleEntries.Entry(
        ModuleEntryPoint::UpdateScene,
        std::bind(&CoreEntry::UpdateScene, this));

    moduleEntries.Entry(
        ModuleEntryPoint::Core_Terminate,
        std::bind(&CoreEntry::Terminate, this));

    moduleEntries.Entry(
        ModuleEntryPoint::Core_Finalize,
        std::bind(&CoreEntry::Finalize, this));
}

const Window& CoreEntry::GetWindow() const
{
    return *m_window;
}

void CoreEntry::Initialize()
{
    m_window = std::make_unique<Window>(
        ClientExtent{ 640, 480 }, "RingRuntime");
}

void CoreEntry::Setup()
{

}

void CoreEntry::Start()
{

}

void CoreEntry::UpdateScene()
{
    assert(m_window);
    assert(m_moduleEntries);

    if (!m_window->Update())
    {
        m_moduleEntries->ExitRequest();
    }
}

void CoreEntry::Terminate()
{

}

void CoreEntry::Finalize()
{
    m_window.reset();
}

} // namespace ring
