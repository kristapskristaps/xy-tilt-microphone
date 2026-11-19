#include <opxy/extension.hpp>
#include "gesture.hpp"

namespace opxy { namespace extensions { namespace tiltmic {
namespace {
::tiltmic::Gesture gesture;
void motion(const Motion& position, const InputMonitor& input, const MotionActions& actions) {
    const bool requested = gesture.update(position, input);
    if (!actions.monitor_input(requested) && requested) gesture.cancel();
}
}
constexpr InputMonitorText monitor_text = {
    "tilt mic", {"off", "auto"}, "tilt mic idle", "tilt mic live", "tilt mic save failed",
};
extern constexpr Hooks hooks = Hooks();
extern constexpr MotionHooks motion_hooks = {motion, &monitor_text};
}}}
