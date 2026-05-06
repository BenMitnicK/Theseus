// xemu.cpp: Xbox emulator launcher. Claims specs whose first
// whitespace-separated token resolves to an xemu binary -- either
// the literal "$XEMU_PATH" template token or a path whose final
// component matches /xemu(-cli)?(\.exe)?$/. Build is identity for
// now since stored specs are already full command lines, but the
// module exists so:
//
//   - Title Maker can surface "Add Xemu Game" as a first-class
//     action and present a simplified form (just an ISO file
//     picker; the command template is auto-built from $XEMU_PATH
//     and the chosen ISO).
//
//   - Settings can hang an "Xemu" panel off the launcher registry
//     to expose $XEMU_PATH and (eventually) per-launcher options.
//
//   - Future xemu-specific behaviors (closing the qcow2 handle
//     before spawn so xemu can take exclusive access, scanning a
//     configured ISO directory for batch import, etc.) live next
//     to each other in this file rather than scattered through
//     the dispatcher.

#include "launcher.h"

#include <cctype>
#include <cstring>

namespace {

// Returns true if `name` (a basename) matches xemu / xemu-cli with
// optional .exe suffix, case-insensitively.
static bool IsXemuBasename(const char* name, size_t len) {
	if (!name || len == 0) return false;
	// Strip trailing ".exe"/".EXE" if present.
	if (len > 4) {
		const char* tail = name + len - 4;
		if ((tail[0] == '.') &&
		    (tail[1] == 'e' || tail[1] == 'E') &&
		    (tail[2] == 'x' || tail[2] == 'X') &&
		    (tail[3] == 'e' || tail[3] == 'E')) {
			len -= 4;
		}
	}
	if (len == 4 && strncasecmp(name, "xemu", 4) == 0) return true;
	if (len == 8 && strncasecmp(name, "xemu-cli", 8) == 0) return true;
	return false;
}

bool Claims(const char* spec) {
	if (!spec || !*spec) return false;

	// Skip leading whitespace.
	const char* p = spec;
	while (*p == ' ' || *p == '\t') p++;

	// Bare $XEMU_PATH template (PathTemplate_Expand may not have run
	// yet when Claims is called from places other than the dispatcher,
	// e.g. Title Maker's type-detection helper).
	if (strncmp(p, "$XEMU_PATH", 10) == 0) return true;
	if (strncmp(p, "${XEMU_PATH}", 12) == 0) return true;

	// Strip optional opening quote.
	bool quoted = (*p == '"');
	if (quoted) p++;

	// Find end of the program token.
	const char* end = p;
	while (*end && *end != (quoted ? '"' : ' ') && *end != '\t') end++;
	if (end == p) return false;

	// Walk back to last path separator to get basename.
	const char* base = end;
	while (base > p && base[-1] != '/' && base[-1] != '\\') base--;
	return IsXemuBasename(base, (size_t)(end - base));
}

bool Build(const char* spec, char* outCmd, size_t outSize) {
	if (!spec || !outCmd || outSize == 0) return false;
	// Identity passthrough -- specs are stored as full command lines
	// (`$XEMU_PATH -dvd_path "..."`). Future work: support stored
	// `iso=` field with this module assembling the command.
	size_t n = strlen(spec);
	if (n >= outSize) n = outSize - 1;
	memcpy(outCmd, spec, n);
	outCmd[n] = '\0';
	return true;
}

const Launcher kXemuLauncher = {
	"xemu",
	"Xemu (Original Xbox)",
	Claims,
	100,         // priority -- runs ahead of url/shell catch-alls
	Build,
};

} // namespace

void Launcher_RegisterXemu() {
	Launcher_Register(&kXemuLauncher);
}
