#include "Core.hpp"
#include "ModuleEntries.hpp"
#include <cassert>

namespace ring {

std::unique_ptr<DesktopCoreEntry> CoreEntry::Make(LaunchState*)
{
    return std::make_unique<DesktopCoreEntry>();
}

void DesktopCoreEntry::Entry(ModuleEntries& moduleEntries)
{
    m_moduleEntries = &moduleEntries;

    moduleEntries.Entry(
        ModuleEntryPoint::Core_Initialize,
        std::bind(&DesktopCoreEntry::Initialize, this));

    moduleEntries.Entry(
        ModuleEntryPoint::Core_Setup,
        std::bind(&DesktopCoreEntry::Setup, this));

    moduleEntries.Entry(
        ModuleEntryPoint::Core_Start,
        std::bind(&DesktopCoreEntry::Start, this));

    moduleEntries.Entry(
        ModuleEntryPoint::UpdateScene,
        std::bind(&DesktopCoreEntry::UpdateScene, this));

    moduleEntries.Entry(
        ModuleEntryPoint::Core_Terminate,
        std::bind(&DesktopCoreEntry::Terminate, this));

    moduleEntries.Entry(
        ModuleEntryPoint::Core_Finalize,
        std::bind(&DesktopCoreEntry::Finalize, this));
}

const Window& DesktopCoreEntry::GetWindow() const
{
    return *m_window;
}

void DesktopCoreEntry::Initialize()
{
    m_window = std::make_unique<Window>(
        ClientExtent{ 640, 480 }, "RingRuntime");
}

void DesktopCoreEntry::Setup()
{

}

void DesktopCoreEntry::Start()
{

}

void DesktopCoreEntry::UpdateScene()
{
    assert(m_window);
    assert(m_moduleEntries);

    if (!m_window->Update())
    {
        m_moduleEntries->ExitRequest();
    }
}

void DesktopCoreEntry::Terminate()
{

}

void DesktopCoreEntry::Finalize()
{
    m_window.reset();
}

} // namespace ring
