#pragma once

#include "LaunchState.hpp"
#include "ModuleEntry.hpp"
#include <memory>

struct ANativeWindow;

namespace ring {

class AndroidCoreEntry final : public ModuleEntry
{
public:
    [[nodiscard]] static std::unique_ptr<AndroidCoreEntry> Make(LaunchState* launchState);
    AndroidCoreEntry(ANativeWindow* window);
    ~AndroidCoreEntry() {}

    void Entry(ModuleEntries& moduleEntries) override;

    [[nodiscard]] ANativeWindow* GetWindow() const;

private:
    void Initialize();
    void Setup();
    void Start();
    void UpdateScene();
    void Terminate();
    void Finalize();

private:
    ModuleEntries* m_moduleEntries = nullptr;
    ANativeWindow* m_window = nullptr;
};

typedef AndroidCoreEntry CoreEntry;

} // namespace ring
