#include "WindowExtent.hpp"

namespace ring {

WindowExtent::WindowExtent(const std::uint32_t width, const std::uint32_t height)
    : width_(width)
    , height_(height)
{}

std::uint32_t WindowExtent::Width() const
{
    return width_;
}

std::uint32_t WindowExtent::Height() const
{
    return height_;
}

} // namespace ring
