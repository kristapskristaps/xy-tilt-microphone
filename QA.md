# Device checklist

The current Off/Auto and fade implementation is ready for a new hardware pass;
the initial result below applies to the earlier one-direction prototype.

Initial motion calibration and a headphone listening test passed on 2026-11-05.
The user confirmed audible mic activation when raised, release when lowered,
and no clicks or feedback; smoother transitions are still requested. Playback
with music, manual overrides and the remaining checklist are not yet accepted.
Tested SDK a81579c, extension ede5971, firmware
`e9dacef22bd439aea4bd0c8929d81771944000f2479c245daed8aaf544cb04bf`.
The earlier installed build used one calibrated singing direction. Record the
exact new SDK commit, extension commit, firmware SHA-256 and device layout
before testing this version.
Rebuild with the intended collection and the current device's `layout.json`
before installation; the minimal FM2op development package is not a replacement
for the user's installed collection.

- Confirm motion axes/signs with a diagnostic build. Direct USB measurements on
  2026-11-05: face-up flat (0,1024,32767), singing (-18880,-26176,-384), opposite
  (-22912,24256,-512), each the median of 60 samples over three seconds.
  Controller callbacks were about 1.4 ms apart; USB telemetry sampled at 20 Hz.
  This does not establish the sensor's own update rate or calibrated degrees.
  Upright activation in both directions and face-down arming rejection still
  need checks on this version.
- With no saved preference, verify Off is the default and raising stays silent.
- On the external-audio Aux input page, hold Shift: confirm the tilt mic
  centered stock send container appears with its native animation, dark encoder
  selects Off/Auto, and releasing Shift hides it. Reopening must replay the
  animation, including after leaving the input page.
  Other encoders and unshifted input controls must retain their stock behavior.
- Open Shift + M1: confirm Off/Auto, cancel a
  changed highlight, confirm Auto, then reboot and verify it is remembered.
  Check the existing CV machine chooser and send-effect menus still work.
- Enable Auto while already upright: it must wait for a flat pose before arming.
- Activate from both measured upright poses, both side lifts, and by passing
  the upright device between two singers. Face-down flat must not arm it.
- Listen for a smooth 50 ms attack and 200 ms release. Raise during release;
  it must fade back in without a jump. Confirm live/idle popups on the Aux track.
- With headphones, mic selected and low gain, verify that playback continues
  while raising/lowering starts/stops live mic monitoring without clicks.
- Check the angle thresholds and dwell times; waving, transport vibration,
  startup while raised and a brief lift must not activate the mic.
- Confirm that manually enabled monitoring stays active after lowering.
- Turn monitoring off manually while raised; it must stay off until lowered
  and raised again.
- Disable Auto while active, and while manually monitoring. Only the automatic
  lease may be switched off; manual monitoring must remain available.
- Change input source, enter/exit sampling and load/new a project while active;
  check that temporary monitoring releases and saved input settings stay intact.
- Disconnect/reconnect headphones and verify stock speaker-feedback protection.
- Exercise the stock motion LFO and punch-in effects alongside the extension.
- Save/reload a project and reboot. Verify project routing is unchanged.
- Compare a build omitting the extension: extension hook sites must remain stock.

Device installation and this checklist need the user's separate authorization.
