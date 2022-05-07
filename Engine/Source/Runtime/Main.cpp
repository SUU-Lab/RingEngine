#include <iostream>

#if __cplusplus != 202002L
#error "C++ version is not 20."
#endif

int main(int, const char* [])
{
    std::cout << "Hello RingEngine!!\n";
    return 0;
}
