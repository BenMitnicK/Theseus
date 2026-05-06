// launcher.h: pluggable launcher contract.
//
// One module per provider (shell, url, xemu, retroarch, steam, ...).
// Each module fills a Launcher struct and registers it with the
// registry at app startup. The dispatcher in launch.cpp consults the
// registry to ask "who owns this spec?" and "how do I build a runnable
// command?" before spawning.
//
// Minimal contract for v1:
//
//   id           short stable identifier ("shell", "url", "xemu")
//   displayName  human-readable label for Title Maker / Settings UI
//   Claims       does this launcher handle the given spec?
//   Build        post-process the spec into a spawn-ready command
//
// Future fields (deferred to follow-up commits as launcher modules
// grow):
//   - field schema for Title Maker forms (per-type input fields)
//   - settings schema for Settings tabs (per-launcher $VARS)
//   - Discover() to enumerate candidates from the host (Steam library,
//     RetroArch cores+ROMs, .iso folder scan)

#pragma once

#include <stddef.h>

struct Launcher {
	// Stable identifier; written to games.ini as `type=<id>` to
	// route stored entries to the right module without re-detecting
	// from the spec string.
	const char* id;

	// Human-readable label for UI surfaces.
	const char* displayName;

	// Returns true if this launcher claims the given spec. Used when
	// games.ini has no explicit `type=` field; the dispatcher walks
	// registered launchers in priority order and the first that
	// claims wins.
	bool (*Claims)(const char* spec);

	// Optional priority for Claims-based ordering. Lower runs first;
	// typical scheme: 0=URL handlers, 100=provider-specific
	// (xemu/steam/retroarch), 1000=shell catch-all.
	int priority;

	// Translate the stored spec into a spawn-ready command string.
	// Identity for most launchers; non-trivial when the launcher
	// stores structured fields (e.g. RetroArch core+rom) that need
	// to be assembled at spawn time.
	//
	// Returns true if outCmd was filled. On false the dispatcher
	// falls back to the unexpanded spec.
	bool (*Build)(const char* spec, char* outCmd, size_t outSize);
};

// Register a launcher. Modules call this from their RegisterFoo()
// function which Launchers_RegisterAll() invokes once at startup.
void Launcher_Register(const Launcher* l);

// Find the launcher for an explicit type id ("shell", "xemu", ...).
// Returns NULL if no module is registered under that id.
const Launcher* Launcher_FindByID(const char* id);

// Find the launcher that claims this spec. Walks registered launchers
// by priority and returns the first that returns true from Claims().
// Returns NULL if no launcher claims (caller should treat the spec
// as a raw shell command via the shell module's defaults).
const Launcher* Launcher_FindForSpec(const char* spec);

// Build a spawn-ready command for `spec`. Looks up the matching
// launcher (by typeHint if non-NULL, else by Claims), calls its
// Build(), and writes into outCmd. If no launcher matches, copies
// spec verbatim. Always succeeds (worst case is identity copy).
void Launcher_Build(const char* spec, const char* typeHint,
                    char* outCmd, size_t outSize);

// Register every built-in launcher module. Called once from
// sdl_main.cpp at startup, before the dispatcher is exercised.
void Launchers_RegisterAll();
