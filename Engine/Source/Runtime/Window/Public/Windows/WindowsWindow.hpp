#pragma once

#include "ClientExtent.hpp"
#include "WindowExtent.hpp"
#include <string_view>

namespace Ring {

class WindowsWindow
{
public:
    WindowsWindow(const ClientExtent& clientExtent, std::string_view title);

    bool Update();
};

typedef WindowsWindow Window;

} // namespace Ring
