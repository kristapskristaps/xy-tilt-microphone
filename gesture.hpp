#pragma once
#include <opxy/extension.hpp>

namespace tiltmic {
using namespace opxy;

// Initial pose classifier: either short/long edge upright. Device QA must
// establish the mic-side axis/sign before narrowing it to the singing pose.
class Gesture {
    i32 x_ = 0, y_ = 0, z_ = 0;
    extensions::Time last_ = 0, since_ = 0;
    bool initialized_ = false, armed_ = false, active_ = false, timing_ = false;

    bool held(bool condition, extensions::Time now, u32 duration) {
        if (!condition) { timing_ = false; return false; }
        if (!timing_) { since_ = now; timing_ = true; }
        return now - since_ >= duration;
    }

public:
    void cancel() { armed_ = active_ = timing_ = false; }

    bool update(const extensions::Motion& motion, const extensions::InputMonitor& input) {
        const bool gap = initialized_ && (motion.time < last_ || motion.time - last_ > 250000);
        last_ = motion.time;
        if (!motion.valid || !input.available || (input.active && !input.owned) || gap) {
            initialized_ = false;
            cancel();
            return false;
        }
        if (!initialized_) {
            x_ = motion.x; y_ = motion.y; z_ = motion.z;
            initialized_ = true;
        } else {
            x_ += (static_cast<i32>(motion.x) - x_) / 4;
            y_ += (static_cast<i32>(motion.y) - y_) / 4;
            z_ += (static_cast<i32>(motion.z) - z_) / 4;
        }
        // Divide before squaring: every sum and 3*vertical fits signed 32-bit,
        // including saturated sensor input, without target 64-bit multiplies.
        const i32 x = x_ / 4, y = y_ / 4, z = z_ / 4;
        const i32 horizontal = x * x + y * y;
        const i32 vertical = z * z;
        if (horizontal + vertical < 64 * 64) { cancel(); return false; }
        const bool flat = horizontal <= vertical;
        if (!armed_) {
            if (held(flat, motion.time, 250000)) { armed_ = true; timing_ = false; }
            return false;
        }
        if (!active_) {
            if (held(horizontal >= 3 * vertical, motion.time, 200000)) {
                active_ = true; timing_ = false;
            }
        } else if (held(flat, motion.time, 150000)) {
            active_ = false; timing_ = false;
        }
        return active_;
    }
};
}
