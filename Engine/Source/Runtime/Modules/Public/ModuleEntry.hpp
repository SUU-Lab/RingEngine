#pragma once

namespace ring {

class ModuleEntries;
class ModuleEntry
{
public:
    virtual ~ModuleEntry() = default;

    /// @brief メインループの各エントリーポイントにモジュールの処理を登録
    virtual void Entry(ModuleEntries& moduleEntries) = 0;
};

} // namespace ring
