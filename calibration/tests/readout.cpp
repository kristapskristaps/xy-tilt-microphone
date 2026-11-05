#include "extension.cpp"
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace opxy::extensions;
char text[32];
opxy::u32 shown;
void require(bool condition, const char* message) {
    if (!condition) { std::fprintf(stderr, "%s\n", message); std::exit(1); }
}
void notify(const char* message) {
    require(std::strlen(message) < sizeof(text), "readout must fit stock popup");
    std::strcpy(text, message); ++shown;
}
const Actions actions = {nullptr, notify, nullptr, nullptr};
int main() {
    const auto& hooks = opxy::extensions::tiltcal::hooks;
    const Control release = {keys::record, false, true, true, 0};
    Context stopped = {};
    hooks.motion({-32768,32767,-32768,10000,true}, {false,false,true}, actions);
    hooks.queued_control(stopped, release, actions);
    require(std::strcmp(text,"X-32768 Y32767 Z-32768") == 0, "signed axis snapshot");
    hooks.motion({0,0,16384,30000,true}, {false,false,true}, actions);
    hooks.motion({0,0,16384,40000,true}, {false,false,true}, actions);
    hooks.queued_control(stopped, release, actions);
    require(std::strcmp(text,"d10000 m20000 V1 M0 A1") == 0, "timing and input status");
    stopped.playing = true;
    hooks.queued_control(stopped, release, actions);
    require(shown == 2, "ignore Record during playback");
    stopped.playing = false;
    hooks.motion({-32768,-32768,-32768,2000000,false}, {true,false,false}, actions);
    hooks.queued_control(stopped, release, actions);
    hooks.queued_control(stopped, release, actions);
    require(std::strcmp(text,"d999999 m999999 V0 M1 A0") == 0, "bounded gap and invalid status");
}
