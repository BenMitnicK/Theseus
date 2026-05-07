# Dashboards

On Xbox hardware, this is where alternate dashboards (UnleashX, Evolution X, XBMC4Xbox, etc.) live, each in its own subfolder containing a `default.xbe`. Theseus itself can also live under here.

This folder is intentionally empty in the public repo. It exists so the desktop build's `E:\` filesystem virtualization has the standard Xbox layout to enumerate at boot. Drop dashboard folders here on desktop to see them in the launcher. On Xbox hardware your real `E:\Dashboards\` is what gets read.
