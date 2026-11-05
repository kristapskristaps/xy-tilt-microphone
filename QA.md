# Device checklist

Hardware validation is pending. Record the exact SDK commit, extension commit,
firmware SHA-256 and device layout before testing this build.
Rebuild with the intended collection and the current device's `layout.json`
before installation; the minimal FM2op development package is not a replacement
for the user's installed collection.

- Confirm motion axes/signs with a diagnostic build in flat, mic-side-up,
  opposite-side-up and inverted poses. Check stationary readings and update rate.
- With headphones, mic selected and low gain, verify that playback continues
  while raising/lowering starts/stops live mic monitoring without clicks.
- Check the angle thresholds and dwell times; waving, transport vibration,
  startup while raised and a brief lift must not activate the mic.
- Confirm that manually enabled monitoring stays active after lowering.
- Turn monitoring off manually while raised; it must stay off until lowered
  and raised again.
- Change input source, enter/exit sampling and load/new a project while active;
  check that temporary monitoring releases and saved input settings stay intact.
- Disconnect/reconnect headphones and verify stock speaker-feedback protection.
- Exercise the stock motion LFO and punch-in effects alongside the extension.
- Save/reload a project and reboot. Verify project routing is unchanged.
- Compare a build omitting the extension: extension hook sites must remain stock.

Device installation and this checklist need the user's separate authorization.
