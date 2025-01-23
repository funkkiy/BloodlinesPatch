#include <Windows.h>

#include "VampireGame.h"

#include "safetyhook.hpp"

DWORD WINAPI BloodlinesPatchThread(LPVOID lpParam)
{
    Vampire::Msg("Initialized Bloodlines Patch.");

    return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    if (fdwReason == DLL_PROCESS_ATTACH) {
        CreateThread(nullptr, 0, BloodlinesPatchThread, nullptr, 0, nullptr);
    }

    return TRUE;
}
