// url.cpp: URL-scheme launcher. Claims specs of the form
// "<scheme>://..." (steam:, com.epicgames.launcher:, http(s):, file:,
// xdg-open targets generally) so the dispatcher routes them to the
// platform's URL opener (ShellExecute / open / xdg-open / steam binary)
// instead of cmd /S /C.
//
// Build is identity -- URLs are already in their final form. The
// platform-specific spawn dispatch (Launch_DoSpawn in launch.cpp)
// detects URLs separately via IsUrl() to pick ShellExecute vs
// CreateProcess; this module exists so Title Maker / Settings can
// surface "URL" as a first-class launcher type and so future steam:
// or epic:-aware modules can claim those specific schemes ahead of
// the generic URL handler by registering at a lower priority.

#include "launcher.h"

#include <cctype>
#include <cstring>

namespace {

bool IsScheme(const char* spec) {
	if (!spec) return false;
	const char* p = spec;
	// Scheme = ALPHA *( ALPHA / DIGIT / "+" / "-" / "." )
	if (!*p || !isalpha((unsigned char)*p)) return false;
	while (*p && (isalnum((unsigned char)*p) ||
	              *p == '+' || *p == '-' || *p == '.')) {
		p++;
	}
	return p > spec && p[0] == ':' && p[1] == '/' && p[2] == '/';
}

bool Claims(const char* spec) {
	return IsScheme(spec);
}

bool Build(const char* spec, char* outCmd, size_t outSize) {
	if (!spec || !outCmd || outSize == 0) return false;
	size_t n = strlen(spec);
	if (n >= outSize) n = outSize - 1;
	memcpy(outCmd, spec, n);
	outCmd[n] = '\0';
	return true;
}

const Launcher kUrlLauncher = {
	"url",              // id
	"URL handler",      // displayName
	Claims,
	500,                // priority -- runs after provider-specific (xemu/steam),
	                    // before shell catch-all
	Build,
};

} // namespace

void Launcher_RegisterUrl() {
	Launcher_Register(&kUrlLauncher);
}
