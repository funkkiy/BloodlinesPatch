#pragma once

#include <Windows.h>

#define VAMPIRE_STEAM_GPGLOBALS_OFFSET 0x70B228

namespace Vampire {

// (vampire.dll)
struct CGlobalVarsBase {
    float realtime;
    int framecount;
    float absoluteframetime;
    float curtime;
    float frametime;
};
CGlobalVarsBase* gpGlobals
    = *(CGlobalVarsBase**)(reinterpret_cast<char*>(GetModuleHandleA("vampire.dll")) + VAMPIRE_STEAM_GPGLOBALS_OFFSET);

// (tier0.dll)
typedef void (*MsgFn)(const char* pMsgFormat, ...);
MsgFn Msg = reinterpret_cast<MsgFn>(GetProcAddress(GetModuleHandleA("tier0.dll"), "Msg"));

} // namespace Vampire
