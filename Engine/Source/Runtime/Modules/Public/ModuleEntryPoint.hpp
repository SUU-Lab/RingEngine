#pragma once

#include <cstddef>

namespace ring {

enum class ModuleEntryPoint
{
    //--------------------------------------------------
    // Initialize モジュール単体の初期化
    Core_Initialize,
    Render_Initialize,
    //--------------------------------------------------

    //--------------------------------------------------
    // Setup 他モジュールに依存する初期化
    Core_Setup,
    Render_Setup,
    //--------------------------------------------------

    //--------------------------------------------------
    // Start Play毎に呼ばれる初期化
    Core_Start,
    Render_Start,
    //--------------------------------------------------

    //--------------------------------------------------
    // Update モジュール更新（毎フレーム呼ばれる）
    UpdateScene,

    BeginRendering,
    DrawMesh,
    EndRendering,
    //--------------------------------------------------

    //--------------------------------------------------
    // Terminate 他モジュールに依存する解放処理
    Render_Terminate,
    Core_Terminate,
    //--------------------------------------------------

    //--------------------------------------------------
    // Finalize モジュール単体の解放処理
    Render_Finalize,
    Core_Finalize,
    //--------------------------------------------------

    Num
};

static constexpr std::size_t ModuleEntryPointNum = static_cast<std::size_t>(ModuleEntryPoint::Num);

} // namespace ring
