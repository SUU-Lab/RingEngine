#pragma once

namespace ring {
inline namespace render {

class Renderer
{
public:
    virtual ~Renderer() {}

    virtual void Begin() = 0;
    virtual void End() = 0;
};

} // inline namespace render
} // namespace ring
