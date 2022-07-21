#include "Android/AndroidCore.hpp"
#include "ModuleEntries.hpp"
#include <cassert>

namespace ring {

std::unique_ptr<AndroidCoreEntry> AndroidCoreEntry::Make(LaunchState* launchState)
{
    return std::make_unique<AndroidCoreEntry>(launchState->window);
}

AndroidCoreEntry::AndroidCoreEntry(ANativeWindow* window)
    : m_window(window)
{}

void AndroidCoreEntry::Entry(ModuleEntries& moduleEntries)
{
    m_moduleEntries = &moduleEntries;

    moduleEntries.Entry(
            ModuleEntryPoint::Core_Initialize,
            std::bind(&AndroidCoreEntry::Initialize, this));

    moduleEntries.Entry(
            ModuleEntryPoint::Core_Setup,
            std::bind(&AndroidCoreEntry::Setup, this));

    moduleEntries.Entry(
            ModuleEntryPoint::Core_Start,
            std::bind(&AndroidCoreEntry::Start, this));

    moduleEntries.Entry(
            ModuleEntryPoint::UpdateScene,
            std::bind(&AndroidCoreEntry::UpdateScene, this));

    moduleEntries.Entry(
            ModuleEntryPoint::Core_Terminate,
            std::bind(&AndroidCoreEntry::Terminate, this));

    moduleEntries.Entry(
            ModuleEntryPoint::Core_Finalize,
            std::bind(&AndroidCoreEntry::Finalize, this));
}

ANativeWindow* AndroidCoreEntry::GetWindow() const
{
    return m_window;
}

    void AndroidCoreEntry::Initialize()
{

}

void AndroidCoreEntry::Setup()
{

}

void AndroidCoreEntry::Start()
{

}

void AndroidCoreEntry::UpdateScene()
{
    assert(m_moduleEntries);

}

void AndroidCoreEntry::Terminate()
{

}

void AndroidCoreEntry::Finalize()
{

}

} // namespace ring
