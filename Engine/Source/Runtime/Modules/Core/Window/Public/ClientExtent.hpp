﻿#pragma once

#include <cstdint>

namespace ring {

/**
 * \brief Client size of window
 */
class ClientExtent
{
public:
    ClientExtent(std::uint32_t width, std::uint32_t height);

    [[nodiscard]] std::uint32_t Width() const;
    [[nodiscard]] std::uint32_t Height() const;

private:
    const std::uint32_t width_;
    const std::uint32_t height_;
};

} // namespace ring
