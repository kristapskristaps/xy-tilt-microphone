#pragma once
#include <opxy/extension.hpp>

namespace tiltmic {
using namespace opxy;

// OP-XY hardware calibration: face-up flat is +Z; the measured singing pose
// points approximately along (-3,-4,0). Keep a directional cone around that pose.
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
        // Scale before squaring: even 3*dot*dot fits signed 32-bit at every
        // signed-16-bit input, without target 64-bit multiplication helpers.
        const i32 x = x_ / 16, y = y_ / 16, z = z_ / 16;
        const i32 horizontal = x * x + y * y, vertical = z * z;
        const i32 dot = -3 * x - 4 * y, side = 4 * x - 3 * y;
        if (horizontal + vertical < 16 * 16) { cancel(); return false; }
        const bool flat = z > 0 && horizontal <= vertical;
        const bool raised = dot > 0 && dot * dot >= side * side && horizontal >= 3 * vertical;
        const bool keep = dot > 0 && 3 * dot * dot >= side * side && horizontal > vertical;
        if (!armed_) {
            if (held(flat, motion.time, 250000)) { armed_ = true; timing_ = false; }
            return false;
        }
        if (!active_) {
            if (held(raised, motion.time, 200000)) { active_ = true; timing_ = false; }
        } else if (held(!keep, motion.time, 150000)) {
            active_ = false; timing_ = false;
        }
        return active_;
    }
};
}
