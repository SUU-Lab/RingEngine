#pragma once

#include <cstdint>

namespace ring {

class ClientExtent
{
public:
    ClientExtent(const std::uint32_t width, const std::uint32_t height);

    std::uint32_t Width() const;
    std::uint32_t Height() const;

private:
    const std::uint32_t width_;
    const std::uint32_t height_;
};

} // namespace ring
