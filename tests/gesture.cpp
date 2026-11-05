#include "gesture.hpp"
#include <cstdlib>
#include <cstdio>

using namespace opxy;
void require(bool condition, const char* message) {
    if (!condition) { std::fprintf(stderr, "%s\n", message); std::exit(1); }
}

struct Driver {
    tiltmic::Gesture gesture;
    extensions::Time time = 0;
    extensions::InputMonitor input = {false, false, true};
    bool pose(i16 x, i16 y, i16 z, u32 milliseconds) {
        bool requested = false;
        for (u32 i = 0; i < milliseconds; i += 10) {
            time += 10000;
            requested = gesture.update({x, y, z, time, true}, input);
            input.active = input.owned = requested;
        }
        return requested;
    }
    void arm() { require(!pose(0, 0, 16384, 500), "flat pose must remain silent"); }
};

int main() {
    Driver d;
    require(!d.pose(16384, 0, 0, 1000), "booting upright must remain silent");
    d.arm();
    require(!d.pose(16384, 0, 0, 100), "brief movement must not activate");
    require(d.pose(16384, 0, 0, 400), "held upright pose must activate");
    require(d.pose(12000, 0, 8000, 400), "middle angle must preserve active state");
    require(!d.pose(0, 0, 16384, 500), "lowering must release monitoring");
    require(d.pose(0, 16384, 0, 500), "second edge must work in the broad prototype");
    d.gesture.cancel();
    d.input.active = d.input.owned = false;
    require(!d.pose(0, 16384, 0, 700), "cancellation must require lowering before rearming");
    d.arm();
    d.input.available = false;
    require(!d.pose(16384, 0, 0, 700), "unavailable microphone must remain silent");
    d.input.available = true;
    require(!d.pose(16384, 0, 0, 700), "availability recovery must not activate while raised");
    d.arm();
    d.input.active = true; d.input.owned = false;
    require(!d.gesture.update({16384,0,0,d.time+10000,true}, d.input), "manual monitoring must win");
    d.input.active = d.input.owned = false;
    d.time += 10000;
    d.arm();
    require(d.pose(16384, 0, 0, 500), "rearmed gesture must activate");
    d.time += 300000;
    require(!d.gesture.update({16384,0,0,d.time,true}, d.input), "long scheduling gap must release");
    d.input.active = d.input.owned = false;
    d.arm();
    require(!d.gesture.update({0,0,0,d.time+10000,false}, d.input), "invalid motion must release");
    Driver extreme; extreme.arm();
    require(extreme.pose(-32768,-32768,0,700), "extreme axes must not overflow");
    return 0;
}
