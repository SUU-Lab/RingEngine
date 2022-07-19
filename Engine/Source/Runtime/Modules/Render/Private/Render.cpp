#include "Render.hpp"
#include "ModuleEntries.hpp"
#include "GL4/GLRenderer.hpp"
#include <cassert>

namespace ring {

RenderEntry::RenderEntry(const CoreEntry& coreEntry)
    : m_coreEntry(coreEntry)
{}

void RenderEntry::Entry(ModuleEntries& moduleEntries)
{
    moduleEntries.Entry(
        ModuleEntryPoint::Render_Initialize,
        std::bind(&RenderEntry::Initialize, this));

    moduleEntries.Entry(
        ModuleEntryPoint::Render_Setup,
        std::bind(&RenderEntry::Setup, this));

    moduleEntries.Entry(
        ModuleEntryPoint::Render_Start,
        std::bind(&RenderEntry::Start, this));

    moduleEntries.Entry(
        ModuleEntryPoint::BeginRendering,
        std::bind(&RenderEntry::BeginRendering, this));

    moduleEntries.Entry(
        ModuleEntryPoint::DrawMesh,
        std::bind(&RenderEntry::DrawMesh, this));

    moduleEntries.Entry(
        ModuleEntryPoint::EndRendering,
        std::bind(&RenderEntry::EndRendering, this));

    moduleEntries.Entry(
        ModuleEntryPoint::Render_Terminate,
        std::bind(&RenderEntry::Terminate, this));

    moduleEntries.Entry(
        ModuleEntryPoint::Render_Finalize,
        std::bind(&RenderEntry::Finalize, this));
}

void RenderEntry::Initialize()
{

}

void RenderEntry::Setup()
{
    m_renderer = std::make_unique<GLRenderer>(m_coreEntry.GetWindow());
}

void RenderEntry::Start()
{

}

void RenderEntry::BeginRendering()
{
    assert(m_renderer);

    m_renderer->Begin();
}

void RenderEntry::DrawMesh()
{

}

void RenderEntry::EndRendering()
{
    assert(m_renderer);

    m_renderer->End();
}

void RenderEntry::Terminate()
{
    m_renderer.reset();
}

void RenderEntry::Finalize()
{

}

} // namespace ring
