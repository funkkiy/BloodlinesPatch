#include <Windows.h>
#include <cstdint>

#include "VampireGame.h"
#include "safetyhook.hpp"

SafetyHookMid g_blockedFramesHook {};
void BlockedFramesHook(SafetyHookContext& ctx)
{
    // Troika's implementation takes a specific path for unblocking doors when it detects they have been blocked by an entity for
    // more than 15 frames. I've seen no difference with the original behavior yet by disabling this path by making sure the frame
    // counter is always 2.
    ctx.ecx = 2;
}

SafetyHookMid g_toggleAngularMoveHook {};
void ToggleAngularMoveHook(SafetyHookContext& ctx)
{
    // Check if the CBaseToggle is a CRotDoor to make sure we are not affecting any other entities.
    if (*reinterpret_cast<uint8_t**>(ctx.esi) == Vampire::VampireBase + VAMPIRE_STEAM_CROTDOOR_VTABLE_OFFSET) {
        // Multiply the `flSpeed` by a framerate-dependent factor in the velocity determination logic inside
        // CBaseToggle::AngularMove.
        float* flSpeed = reinterpret_cast<float*>(reinterpret_cast<uint8_t*>(ctx.esp) + 0x38);
        *flSpeed *= (1.0f / Vampire::gpGlobals->frametime) / 60.0f;
    }
}

SafetyHookInline g_dllInitHook {};
bool DllInitHook(uintptr_t engine, uintptr_t physics, uintptr_t filesystem, Vampire::CGlobalVarsBase* pGlobals)
{
    Vampire::gpGlobals = pGlobals;
    g_dllInitHook.call<bool>(engine, physics, filesystem, pGlobals);
}

extern "C" __declspec(dllexport) bool loaded_vampire()
{
    // Initialize Vampire addresses.
    Vampire::VampireBase = reinterpret_cast<uint8_t*>(GetModuleHandleA("vampire.dll"));
    Vampire::Tier0Base = reinterpret_cast<uint8_t*>(GetModuleHandleA("tier0.dll"));

    // Abort before patching if the module base addresses are invalid.
    if (!Vampire::VampireBase || !Vampire::Tier0Base) {
        return 0;
    }

    // Grab gpGlobals from DLLInit.
    g_dllInitHook = safetyhook::create_inline(Vampire::VampireBase + VAMPIRE_STEAM_DLLINIT_OFFSET, DllInitHook);

    // Initialize Door FPS Fix.
    g_blockedFramesHook = safetyhook::create_mid(Vampire::VampireBase + VAMPIRE_STEAM_BLOCKEDFRAMES_OFFSET, BlockedFramesHook);
    g_toggleAngularMoveHook
        = safetyhook::create_mid(Vampire::VampireBase + VAMPIRE_STEAM_ANGULARMOVESPEED_OFFSET, ToggleAngularMoveHook);

    return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) { return TRUE; }
