#pragma once

#include <cstdint>
#include <Windows.h>

#define VAMPIRE_STEAM_DLLINIT_OFFSET 0x11A0C0
#define VAMPIRE_STEAM_GPGLOBALS_OFFSET 0x70B228
#define VAMPIRE_STEAM_BLOCKEDFRAMES_OFFSET 0xF3A6D
#define VAMPIRE_STEAM_ANGULARMOVESPEED_OFFSET 0x1C189A
#define VAMPIRE_STEAM_CROTDOOR_VTABLE_OFFSET 0x454B94

namespace Vampire {

// (vampire.dll)
uint8_t* VampireBase = nullptr;

struct CGlobalVarsBase {
    float realtime;
    int framecount;
    float absoluteframetime;
    float curtime;
    float frametime;
};
CGlobalVarsBase* gpGlobals = nullptr;

// (tier0.dll)
uint8_t* Tier0Base = nullptr;

typedef void (*MsgFn)(const char* pMsgFormat, ...);
MsgFn Msg = nullptr;

} // namespace Vampire
