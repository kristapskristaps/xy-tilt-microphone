# Tilt microphone prototype

An optional Open-XY extension that temporarily enables stock internal-microphone
monitoring when the device is held upright. This development version requires
the SDK branch `codex/tilt-microphone` in `../open-xy-tilt-microphone`.

Select **mic** on the external-audio auxiliary track and set its gain, level,
mix and effects. Start with headphones and a low input level. Include this
extension in a development build to opt in; omit it to retain stock behavior.

Lay the device face-up flat for 250 ms to arm it, then raise it into the
calibrated singing direction for 200 ms. Hardware measurements on an OP-XY
running OS 1.2.1 gave +Z when face-up flat and approximately (-3,-4,0) in the
singing pose. The direction gate rejects the measured opposite pose and side
lifts. Activation starts around 60 degrees from flat; lowering below around
45 degrees or turning away for 150 ms releases monitoring. These thresholds
use the stock channels, which clip near full scale, rather than measured angles.

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
