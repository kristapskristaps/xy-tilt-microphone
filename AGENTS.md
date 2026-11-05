# Repository instructions

This repository owns the tilt-microphone gesture and its host tests. It uses
the SDK beside it, currently `../open-xy-tilt-microphone`. Keep firmware addresses,
stock calls and platform support in a separate SDK change. Run
`python3 ../open-xy-tilt-microphone/sdk.py test --extension .` after changes.

Keep firmware and firmware-containing outputs outside every checkout. Device
operations need a separate user instruction. Host checks do not establish
sensor orientation, device timing or hardware acceptance; follow QA.md.
