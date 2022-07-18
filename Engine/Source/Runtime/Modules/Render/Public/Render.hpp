#pragma once

#include "Renderer.hpp"
#include "Core.hpp"


namespace ring {

class RenderEntry final : public ModuleEntry
{
public:
    RenderEntry(const CoreEntry& coreEntry);
    ~RenderEntry() {}

    void Entry(ModuleEntries& moduleEntries) override;

private:
    void Initialize();
    void Setup();
    void Start();
    void BeginRendering();
    void DrawMesh();
    void EndRendering();
    void Terminate();
    void Finalize();

private:
    const CoreEntry& m_coreEntry;
    std::unique_ptr<Renderer> m_renderer;
};

} // namespace ring
