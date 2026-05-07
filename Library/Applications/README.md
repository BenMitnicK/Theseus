# Applications

On Xbox hardware, this is where homebrew applications live (file managers, tools, utilities), each in its own subfolder containing a `default.xbe`.

This folder is intentionally empty in the public repo. It exists so the desktop build's `E:\` filesystem virtualization has the standard Xbox layout to enumerate at boot. Drop application folders here on desktop to see them in the launcher. On Xbox hardware your real `E:\Applications\` is what gets read.
