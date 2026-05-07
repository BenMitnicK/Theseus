# TDATA

Title data. Each Xbox title gets a folder here named by its 8-character title ID, holding save games, per-title configuration, and any persistent state the title writes through `T:\`. On Xbox hardware the kernel maps `T:\` to `E:\TDATA\<currentTitleId>\` automatically when a title is launched.

This folder is mostly empty in the public repo. The dashboard's own state lives under `fffe0000` (the dashboard's title ID); see that subfolder's README. On Xbox hardware your real `E:\TDATA\` is what gets read.
