# Games

On Xbox hardware, this is where game rips and homebrew games live, each in its own subfolder containing a `default.xbe`. The launcher's title scanner walks this tree at boot, parses each XBE's certificate for its title ID, and populates the games panel.

This folder is intentionally empty in the public repo. It exists so the desktop build's `E:\` filesystem virtualization has the standard Xbox layout to enumerate. Drop game folders here on desktop to see them in the launcher. On Xbox hardware your real `E:\Games\` is what gets read.
