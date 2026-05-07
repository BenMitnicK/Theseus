// shell.cpp: catch-all launcher. Claims any spec that no other
// launcher has claimed first; passes the spec through unchanged
// for the dispatcher to spawn via cmd /S /C (Windows) or
// fork+execl /bin/sh (Unix).
//
// This is the fallback module -- shell.cpp's Claims always returns
// true, but with the highest priority value so any other launcher
// that recognizes the spec wins first. Removing the shell module
// would break every entry that's just a raw command line.

#include "launcher.h"

#include <cstring>

namespace {

bool Claims(const char* /*spec*/) {
	return true; // catch-all
}

bool Build(const char* spec, char* outCmd, size_t outSize) {
	if (!spec || !outCmd || outSize == 0) return false;
	size_t n = strlen(spec);
	if (n >= outSize) n = outSize - 1;
	memcpy(outCmd, spec, n);
	outCmd[n] = '\0';
	return true;
}

const Launcher kShellLauncher = {
	"shell",            // id
	"Shell command",    // displayName
	Claims,
	1000,               // priority -- highest, runs last
	Build,
};

} // namespace

void Launcher_RegisterShell() {
	Launcher_Register(&kShellLauncher);
}
