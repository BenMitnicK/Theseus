// udata_synth.h: synthesize Library/UDATA/ entries from Title Maker games.
//
// Without this, the dashboard's Memory section is empty unless the user
// mounts a qcow2 of their actual Xbox HDD -- which most desktop users
// don't have, and which conflicts with xemu wanting exclusive access to
// the same image file. By writing a TitleMeta.xbx (and eventually
// TitleImage.xbx) into Library/UDATA/<TitleID>/ for every entry in
// games.ini, the dashboard's existing CSavedGameGrid loader sees them
// as ordinary Xbox titles and renders the same title pods.
//
// Real Xbox UDATA folders (if the user copies them in) coexist
// alongside synthetic ones; the synthesizer skips any title where a
// TitleMeta.xbx already exists, so user-imported saves win.

#pragma once

// Walks every entry in g_vgames and ensures Library/UDATA/<TitleID>/
// exists with a TitleMeta.xbx written in UTF-16 LE INI format. Safe
// to call multiple times; existing TitleMeta.xbx files are left
// alone so user-supplied save metadata isn't overwritten.
//
// Returns the count of titles whose UDATA folder was newly created
// or refreshed.
int UDataSynth_RebuildAll();
