# Tilt microphone

An optional Open-XY extension that temporarily monitors the internal microphone
when OP-XY is held upright. It requires the SDK's `codex/tilt-microphone` branch
([SDK pull request](https://github.com/etcetc000/open-xy/pull/424)).

On the **external-audio Aux track**, press **Shift + M1** to open **tilt mic**.
Choose **auto** to enable the gesture or **off** for ordinary manual monitoring.
Off is the default. Confirming remembers this device preference across reboots;
cancelling the selector leaves it unchanged. Select **mic** as the input and set
its gain, level, mix and effects as usual. Begin testing with headphones and a
low input level.

Lay the device face-up flat for 250 ms to arm it, then hold it sufficiently
upright for 200 ms. Any upright direction works: turn it around or pass it to
another singer without lowering it. The approximate activation angle is
60 degrees from flat; lowering below about 45 degrees for 150 ms releases it.
The stock motion channels clip at full scale, so these are thresholds in sensor
units rather than calibrated physical angles. Starting upright or face-down
flat does not arm the gesture.

The SDK fades automatic monitoring in over 50 ms and out over 200 ms. On the
Aux input track, short native popups confirm live/idle transitions. It keeps
the selected input, gain, levels, FX, sequencer and project controls intact.
Sampling, project changes, unavailable input, a manual monitoring stop or a
long controller gap cancel the request. Already-active manual monitoring is
never acquired or switched off. A cancelled gesture needs a flat pose before
it can activate again. Stock microphone feedback protections still apply.

The previous one-direction prototype passed an initial headphone listening test.
This version's direction changes, menu, persistence and fades need a new hardware
pass; see [QA.md](QA.md). Host tests and a firmware build do not establish device
acceptance.

## Develop

The extension's source and tests live here; stock calls, settings, UI and audio
integration belong to the separate SDK change. Run:

```sh
python3 ../open-xy-tilt-microphone/sdk.py test --extension .
```

Build with `--extension /absolute/path/to/xy-tilt-microphone` alongside the
intended machine collection and its current layout. Use fresh firmware output
folders outside every checkout. The SDK build guide describes installation.
The optional [calibration extension](calibration/README.md) observes motion
without requesting microphone monitoring.
