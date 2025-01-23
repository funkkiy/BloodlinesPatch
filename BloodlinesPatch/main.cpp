#include <Windows.h>
#include <map>

#include "VampireGame.h"

#include "safetyhook.hpp"

struct CRotDoorTimer {
    float m_unblockTime {0.0f};
};
std::map<uintptr_t, CRotDoorTimer> rotDoorTimers;

void BlockedFramesHook(SafetyHookContext& ctx)
{
    ctx.ecx = 2;
}

DWORD WINAPI BloodlinesPatchThread(LPVOID lpParam)
{
    Vampire::Msg("Initialized Bloodlines Patch.\n");

    SafetyHookMid hook = safetyhook::create_mid(
        reinterpret_cast<char*>(GetModuleHandleA("vampire.dll")) + VAMPIRE_STEAM_BLOCKEDFRAMES_OFFSET, BlockedFramesHook);

    for (;;) {
        ;
    }

    return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    if (fdwReason == DLL_PROCESS_ATTACH) {
        CreateThread(nullptr, 0, BloodlinesPatchThread, nullptr, 0, nullptr);
    }

    return TRUE;
}
