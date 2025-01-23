#include <Windows.h>

#include "VampireGame.h"

#include "safetyhook.hpp"

SafetyHookMid blockedFramesHook {};
void BlockedFramesHook(SafetyHookContext& ctx) { ctx.ecx = 2; }

extern "C" __declspec(dllexport) bool loaded_vampire()
{
    // Initialize Vampire addresses.
    Vampire::gpGlobals
        = *(Vampire::CGlobalVarsBase**)(reinterpret_cast<char*>(GetModuleHandleA("vampire.dll")) + VAMPIRE_STEAM_GPGLOBALS_OFFSET);
    Vampire::BaseDoorBlocked = reinterpret_cast<Vampire::BaseDoorBlockedFn>(
        reinterpret_cast<char*>(GetModuleHandleA("vampire.dll") + VAMPIRE_STEAM_BASEDOORBLOCKED_OFFSET));
    Vampire::Msg = reinterpret_cast<Vampire::MsgFn>(GetProcAddress(GetModuleHandleA("tier0.dll"), "Msg"));

    // Initialize Door FPS Fix.
    blockedFramesHook = safetyhook::create_mid(
        reinterpret_cast<char*>(GetModuleHandleA("vampire.dll")) + VAMPIRE_STEAM_BLOCKEDFRAMES_OFFSET, BlockedFramesHook);

    return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) { return TRUE; }
