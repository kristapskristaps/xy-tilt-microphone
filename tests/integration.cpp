#include "extension.cpp"
#include <cstdio>
#include <cstdlib>
using namespace opxy;
using namespace opxy::extensions;

bool permitted = true, requested;
Time now;
void require(bool condition, const char* message) {
    if (!condition) { std::fprintf(stderr, "%s\n", message); std::exit(1); }
}
bool monitor(bool enabled) { requested = permitted && enabled; return permitted; }
const Actions actions = {nullptr, nullptr, nullptr, monitor};
void pose(i16 x, i16 y, i16 z, u32 milliseconds) {
    for (u32 i = 0; i < milliseconds; i += 10) {
        now += 10000;
        const InputMonitor input = {requested, requested, true};
        opxy::extensions::tiltmic::hooks.motion({x,y,z,now,true}, input, actions);
    }
}
int main() {
    pose(0,0,16384,500);
    pose(-18880,-26176,-384,500);
    require(requested, "extension must renew monitoring while raised");
    permitted = false;
    pose(-18880,-26176,-384,100);
    require(!requested, "denied monitoring must cancel the gesture");
    permitted = true;
    pose(-18880,-26176,-384,500);
    require(!requested, "permission recovery must require lowering first");
    pose(0,0,16384,500);
    pose(-18880,-26176,-384,500);
    require(requested, "lowering must allow a new gesture after denial");
    pose(0,0,16384,500);
    require(!requested, "extension must release when lowered");
    return 0;
}
