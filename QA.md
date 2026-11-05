# Device checklist

The owner approved the centered native Shift popup on an OP-XY on 2026-11-05:
only `tilt mic` and Off/Auto appeared, the dark encoder changed the caption,
and releasing Shift dismissed it cleanly. The stock container and entrance
animation were also accepted. USB telemetry confirmed normal startup, the
monitoring extension and valid motion readings.

Tested firmware:
`c659def080d75e95595790db49a661d66aa36c15a15fbde9d39f8cfb078e6cf5`.
Public SDK `d74d2f1`, private hardware integration `76cd08b`, extension
`7079420`, machine sources `8e45cee`. This combined image retained all 26
Hundekraft/Halo machines, their source hashes and IDs, layout, content,
profiling mode and sweep flag from the device's preceding build.
The remaining checks below cover audio behavior and interactions; approval of
the popup does not establish those results.

Initial motion calibration and a headphone listening test passed on 2026-11-05.
The user confirmed audible mic activation when raised, release when lowered,
and no clicks or feedback. The latest fades with music, manual overrides and
the remaining checklist still need their device pass.
Tested SDK a81579c, extension ede5971, firmware
`e9dacef22bd439aea4bd0c8929d81771944000f2479c245daed8aaf544cb04bf`.
The earlier installed build used one calibrated singing direction. Record the
exact SDK/extension commits, firmware SHA-256 and device layout for each new
hardware pass.
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
- Reopen the popup after leaving and returning to the input page: its native
  animation must restart. Other encoders and unshifted input controls must
  retain their stock behavior.
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
