# Motion calibration

Build this extension instead of `tiltmic` for the first device measurement.
It requests no input monitoring and changes no notes or project parameters.
It claims Record double-tap, so omit Retrospective capture from this build.

With playback stopped and an instrument track selected, hold a pose for one
second, then tap Record once. The popup gives signed `X`, `Y`, `Z` readings.
The next tap gives the last (`d`) and maximum (`m`) controller interval in
microseconds, plus motion validity (`V`), monitoring active (`M`) and internal
automatic-monitor eligibility (`A`, which stays zero in this observer-only build). Readings alternate on subsequent taps. Record keeps
its ordinary stock behavior; do not play keys or start playback while holding it.

Measure face-up flat, microphone-facing singing pose, its opposite, and face-down
flat. Record the readings, stationary variation and the exact firmware hash.
This does not establish which physical axis/sign points toward the microphone.
