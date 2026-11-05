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
    u32 interval = 10000;
    bool pose(i16 x, i16 y, i16 z, u32 milliseconds) {
        bool requested = false;
        for (u32 i = 0; i < milliseconds * 1000; i += interval) {
            time += interval;
            requested = gesture.update({x, y, z, time, true}, input);
            input.active = input.owned = requested;
        }
        return requested;
    }
    void arm() { require(!pose(0, 1024, 32767, 500), "flat pose must remain silent"); }
    bool sing(u32 milliseconds = 500) { return pose(-18880, -26176, -384, milliseconds); }
};

int main() {
    Driver d;
    require(!d.sing(1000), "booting upright must remain silent");
    d.arm();
    require(!d.sing(100), "brief movement must not activate");
    require(d.sing(400), "measured held singing pose must activate");
    require(d.pose(-14400, -19200, 18000, 400), "middle angle must preserve active state");
    require(!d.pose(0, 1024, 32767, 500), "lowering must release monitoring");
    require(!d.pose(-22912, 24256, -512, 700), "measured opposite tilt must not activate");
    require(!d.pose(-32768, 0, 0, 700), "sideways tilt must not activate");
    require(!d.pose(32767, 0, 0, 700), "other sideways tilt must not activate");
    require(d.sing(), "return to the singing direction must activate");
    require(!d.pose(-22912, 24256, -512, 500), "turning away must release monitoring");
    d.gesture.cancel(); d.input.active = d.input.owned = false;
    require(!d.sing(700), "cancellation must require lowering before rearming");
    d.arm();
    d.input.available = false;
    require(!d.sing(700), "unavailable microphone must remain silent");
    d.input.available = true;
    require(!d.sing(700), "availability recovery must not activate while raised");
    d.arm();
    d.input.active = true; d.input.owned = false;
    require(!d.gesture.update({-18880,-26176,-384,d.time+10000,true}, d.input), "manual monitoring must win");
    d.input.active = d.input.owned = false; d.time += 10000;
    d.arm(); require(d.sing(), "rearmed gesture must activate");
    d.time += 300000;
    require(!d.gesture.update({-18880,-26176,-384,d.time,true}, d.input), "long scheduling gap must release");
    d.input.active = d.input.owned = false;
    d.arm();
    require(!d.gesture.update({0,0,0,d.time+10000,false}, d.input), "invalid motion must release");
    Driver inverted;
    require(!inverted.pose(0,0,-32768,700) && !inverted.sing(), "face-down flat must not arm");
    Driver extreme; extreme.arm();
    require(extreme.pose(-32768,-32768,0,700), "extreme signed axes must not overflow");
    require(!extreme.pose(32767,32767,-32768,700), "extreme wrong direction must release");
    Driver hardware_rate; hardware_rate.interval = 1420; hardware_rate.arm();
    require(!hardware_rate.sing(100) && hardware_rate.sing(300), "dwell time must hold at measured callback rate");
    require(!hardware_rate.pose(0,1024,32767,300), "lowering must release at measured callback rate");
    return 0;
}
