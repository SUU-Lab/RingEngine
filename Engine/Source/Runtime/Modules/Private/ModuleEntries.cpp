#include "ModuleEntries.hpp"
#include <cassert>

namespace ring {

ModuleEntries::ModuleEntries()
    : m_exitRequested(false)
    , m_entryFunctions()
{
    m_entryFunctions.fill(nullptr);
}

void ModuleEntries::Call(const ModuleEntryPoint moduleEntryPoint)
{
    const int index = static_cast<int>(moduleEntryPoint);
    assert(0 <= index && index < m_entryFunctions.size());

    if (m_entryFunctions[index])
    {
        m_entryFunctions[index]();
    }
}

void ModuleEntries::Entry(
    const ModuleEntryPoint moduleEntryPoint,
    const EntryFunction& entryFunction)
{
    const int index = static_cast<int>(moduleEntryPoint);
    assert(0 <= index && index < m_entryFunctions.size());
    assert(!m_entryFunctions[index]);

    m_entryFunctions[index] = entryFunction;
}

void ModuleEntries::MainLoop()
{
    // Initialize モジュール単体の初期化
    Call(ModuleEntryPoint::Core_Initialize);
    Call(ModuleEntryPoint::Render_Initialize);

    // Setup 他モジュールに依存する初期化
    Call(ModuleEntryPoint::Core_Setup);
    Call(ModuleEntryPoint::Render_Setup);

    // Start Play毎に呼ばれる初期化
    Call(ModuleEntryPoint::Core_Start);
    Call(ModuleEntryPoint::Render_Start);

    // Update モジュール更新（毎フレーム呼ばれる）
    while (!m_exitRequested)
    {
        Call(ModuleEntryPoint::UpdateScene);
        Call(ModuleEntryPoint::BeginRendering);
        Call(ModuleEntryPoint::DrawMesh);
        Call(ModuleEntryPoint::EndRendering);
    }

    // Terminate 他モジュールに依存する解放処理
    Call(ModuleEntryPoint::Render_Terminate);
    Call(ModuleEntryPoint::Core_Terminate);

    // Finalize モジュール単体の解放処理
    Call(ModuleEntryPoint::Render_Finalize);
    Call(ModuleEntryPoint::Core_Finalize);
}

void ModuleEntries::ExitRequest()
{
    m_exitRequested = true;
}

} // namespace ring
