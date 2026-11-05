# Tilt microphone prototype

An optional Open-XY extension that temporarily enables stock internal-microphone
monitoring when the device is held upright. This development version requires
the SDK branch `codex/tilt-microphone` in `../open-xy-tilt-microphone`.

Select **mic** on the external-audio auxiliary track and set its gain, level,
mix and effects. Start with headphones and a low input level. Include this
extension in a development build to opt in; omit it to retain stock behavior.

Lay the device flat for 250 ms to arm it, then tilt it beyond approximately
60 degrees for 200 ms. Lower it below approximately 45 degrees for 150 ms to
release monitoring. These angles assume the third stock channel is the plane
normal: the physical axis mapping, sensor scale and timing need hardware QA.
The prototype intentionally accepts either edge; the final mic-side direction
must be selected after measuring the sensor axes on the device.

The extension changes only the stock monitoring enable flag. It leaves the
selected input, gain, levels, FX, sequencer and project parameters under stock
control. Sampling, project changes, unavailable input, a manual monitoring stop
or a long controller gap cancel the request. Already-active manual monitoring
is never acquired or switched off. A cancelled gesture needs a flat pose before
it can activate again. Stock microphone feedback protections still apply.

This prototype does not provide a persistent device setting, an active-mic
overlay or its own fade. Native audio transitions follow stock behavior. A
host test or successful firmware build does not establish hardware acceptance.

Test:

```sh
python3 ../open-xy-tilt-microphone/sdk.py test --extension .
```

Build with `--extension /absolute/path/to/xy-tilt-microphone` alongside a
machine, using fresh firmware output folders outside every checkout. Follow
the SDK build guide and the device checklist in QA.md.
