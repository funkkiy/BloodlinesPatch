#pragma once

#include <Windows.h>

#define VAMPIRE_STEAM_GPGLOBALS_OFFSET 0x70B228
#define VAMPIRE_STEAM_BASEDOORBLOCKED_OFFSET 0xF14A0
#define VAMPIRE_STEAM_ROTDOORBLOCKED_OFFSET 0xF3900
#define VAMPIRE_STEAM_BLOCKEDFRAMES_OFFSET 0xF3A6D

namespace Vampire {

// (vampire.dll)
struct CGlobalVarsBase {
    float realtime;
    int framecount;
    float absoluteframetime;
    float curtime;
    float frametime;
};
CGlobalVarsBase* gpGlobals = nullptr;

typedef void (*BaseDoorBlockedFn)(uintptr_t _this, uintptr_t pOther);
BaseDoorBlockedFn BaseDoorBlocked = nullptr;

// (tier0.dll)
typedef void (*MsgFn)(const char* pMsgFormat, ...);
MsgFn Msg = nullptr;

} // namespace Vampire
