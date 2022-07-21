#pragma once

#if RING_PLATFORM_ANDROID
#include "Android/AndroidCore.hpp"
#endif

#if RING_PLATFORM_WINDOWS || RING_PLATFORM_LINUX

#include "LaunchState.hpp"
#include "Window.hpp"
#include "ModuleEntry.hpp"
#include <memory>

namespace ring {

class DesktopCoreEntry final : public ModuleEntry
{
public:
    [[nodiscard]] static std::unique_ptr<DesktopCoreEntry> Make(LaunchState* launchState);

    DesktopCoreEntry() {}
    ~DesktopCoreEntry() {}

    void Entry(ModuleEntries& moduleEntries) override;

    [[nodiscard]] const Window& GetWindow() const;

private:
    void Initialize();
    void Setup();
    void Start();
    void UpdateScene();
    void Terminate();
    void Finalize();

private:
    std::unique_ptr<Window> m_window;
    ModuleEntries* m_moduleEntries = nullptr;
};

typedef DesktopCoreEntry CoreEntry;

} // namespace ring

#endif
