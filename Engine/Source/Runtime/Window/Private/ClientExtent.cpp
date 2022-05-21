#include "ClientExtent.hpp"

namespace ring {

ClientExtent::ClientExtent(const std::uint32_t width, const std::uint32_t height)
    : width_(width)
    , height_(height)
{}

std::uint32_t ClientExtent::Width() const
{
    return width_;
}

std::uint32_t ClientExtent::Height() const
{
    return height_;
}

} // namespace ring
