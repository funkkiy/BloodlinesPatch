#include <Windows.h>

#include "VampireGame.h"

#include "safetyhook.hpp"

void RotDoorBlockedHook(uintptr_t _this, uintptr_t pOther) { Vampire::BaseDoorBlocked(_this, pOther); }

extern "C" __declspec(dllexport) DWORD WINAPI loaded_vampire(LPVOID lpParam)
{
    Vampire::Msg("Initialized Bloodlines Patch.\n");

    SafetyHookInline rotDoorBlockedHk = safetyhook::create_inline(
        reinterpret_cast<char*>(GetModuleHandleA("vampire.dll") + VAMPIRE_STEAM_ROTDOORBLOCKED_OFFSET), RotDoorBlockedHook);

    return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    return TRUE;
}
