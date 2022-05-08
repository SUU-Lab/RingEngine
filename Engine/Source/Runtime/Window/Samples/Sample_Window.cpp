#include "Window.hpp"

int main(int, const char* [])
{
    Ring::Window window({ 640, 480 }, "Sample_Window");

    while (window.Update())
    {
    }

    return 0;
}
