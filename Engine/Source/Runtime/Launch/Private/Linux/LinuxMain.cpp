
#include "LaunchState.hpp"

namespace ring {

void Main(LaunchState*);

} // namespace ring

int main(int, const char*[])
{
    ring::LaunchState launchState = {};
    ring::Main(&launchState);
    return 0;
}
