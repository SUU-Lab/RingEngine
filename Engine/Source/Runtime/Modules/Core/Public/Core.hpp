#pragma once

#ifndef RING_PLATFORM_ANDROID
#include "Window.hpp"
#endif

#include "ModuleEntry.hpp"
#include <memory>

namespace ring {

class CoreEntry final : public ModuleEntry
{
public:
    CoreEntry() {}
    ~CoreEntry() {}

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

} // namespace ring
