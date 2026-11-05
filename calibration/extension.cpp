#include <opxy/extension.hpp>

namespace opxy { namespace extensions { namespace tiltcal {
namespace {
Motion latest = {};
InputMonitor monitor = {};
u32 interval, maximum;
bool status;
char message[32];

char* number(char* out, i32 value) {
    if (value < 0) { *out++ = '-'; value = -value; }
    char digits[10];
    u32 count = 0;
    do { digits[count++] = '0' + value % 10; value /= 10; } while (value);
    while (count) *out++ = digits[--count];
    return out;
}
void motion(const Motion& position, const InputMonitor& input, const Actions&) {
    if (latest.time && position.time >= latest.time) {
        const Time delta = position.time - latest.time;
        interval = delta > 999999 ? 999999 : static_cast<u32>(delta);
        if (interval > maximum) maximum = interval;
    }
    latest = position;
    monitor = input;
}
void control(const Context& context, const Control& key, const Actions& actions) {
    if (context.playing || key.key != keys::record || key.pressed || !key.accepted || !key.unmodified) return;
    char* out = message;
    if (!status) {
        *out++ = 'X'; out = number(out, latest.x);
        *out++ = ' '; *out++ = 'Y'; out = number(out, latest.y);
        *out++ = ' '; *out++ = 'Z'; out = number(out, latest.z);
    } else {
        *out++ = 'd'; out = number(out, interval);
        *out++ = ' '; *out++ = 'm'; out = number(out, maximum);
        *out++ = ' '; *out++ = 'V'; *out++ = latest.valid ? '1' : '0';
        *out++ = ' '; *out++ = 'M'; *out++ = monitor.active ? '1' : '0';
        *out++ = ' '; *out++ = 'A'; *out++ = monitor.available ? '1' : '0';
        maximum = 0;
    }
    *out = 0;
    actions.notify(message);
    status = !status;
}
}
extern constexpr Hooks hooks = Hooks().with_motion(motion).with_queued_control(control);
}}}
