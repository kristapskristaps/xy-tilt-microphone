#include <opxy/extension.hpp>
#include "gesture.hpp"

namespace opxy { namespace extensions { namespace tiltmic {
namespace {
::tiltmic::Gesture gesture;
void motion(const Motion& position, const InputMonitor& input, const Actions& actions) {
    const bool requested = gesture.update(position, input);
    if (!actions.monitor_input(requested) && requested) gesture.cancel();
}
}
extern constexpr Hooks hooks = Hooks().with_motion(motion);
}}}
