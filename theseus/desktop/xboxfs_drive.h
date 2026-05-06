// xboxfs_drive.h: shared Xbox-drive-letter to runtime-folder helper. Tiny
// header with no other dependencies so it can be pulled in early by
// platform_shim.h, xboxfs.h, virtual_games.h, etc. before the rest of
// the platform layer comes online.
//
// On real Xbox the dashboard sees C:, Q:, E: (and optional F: G: R: S:
// for HDD partitions). On desktop those collapse to three runtime folders
// next to the binary:
//
//   C: -> Configs/
//   Q: -> Data/
//   E: -> Library/
//
// F:, G:, R:, etc. have no analog. The helper returns NULL for them so
// callers' stat()/opendir() fail naturally and any XAP code that walks
// drives just produces empty results for the missing ones.

#pragma once

static inline const char* XboxFS_DriveToPrefix(char drive) {
    if (drive == 'C' || drive == 'c') return "Configs";
    if (drive == 'Q' || drive == 'q') return "Data";
    if (drive == 'E' || drive == 'e') return "Library";
    return 0;
}
