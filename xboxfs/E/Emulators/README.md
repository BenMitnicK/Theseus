# Emulators

On Xbox hardware, this is where emulator apps (Surreal64, FCE Ultra, ScummVM-X, etc.) live, each in its own subfolder containing a `default.xbe` plus its ROM library.

This folder is intentionally empty in the public repo. It exists so the desktop build's `E:\` filesystem virtualization has the standard Xbox layout to enumerate at boot. Drop emulator folders here on desktop to see them in the launcher. On Xbox hardware your real `E:\Emulators\` is what gets read.
