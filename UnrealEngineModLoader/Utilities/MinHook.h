#pragma once
#include "Globals.h"
#include "Log/Log.h"
#include <MinHook.h>
#include <string>

namespace MinHook
{
static void Init()
{
    if (MH_Initialize() != MH_OK)
    {
        LOG_ERROR("Failed to initialize MinHook");
    }
}

template <typename T> static void Add(DWORD_PTR pTarget, LPVOID pDetour, T **ppOriginal, std::string displayName = "")
{
    MH_STATUS Result = MH_CreateHook((LPVOID)pTarget, pDetour, reinterpret_cast<LPVOID *>(ppOriginal));
    if (Result != MH_OK)
    {
        LOG_ERROR("Failed to create hook: {}, addr: 0x{:x}, reason: {}", displayName.c_str(), pTarget,
                  MH_StatusToString(Result));
        return;
    }

    Result = MH_EnableHook((LPVOID)pTarget);
    if (Result != MH_OK)
    {
        LOG_ERROR("Failed to enable hook: {}, addr: 0x{:x}, reason: {}", displayName.c_str(), pTarget,
                  MH_StatusToString(Result));
        return;
    }
    LOG_INFO("Added hook: {}", displayName.c_str());
}
} // namespace MinHook