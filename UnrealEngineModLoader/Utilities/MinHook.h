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
    if (MH_CreateHook((LPVOID)pTarget, pDetour, reinterpret_cast<LPVOID *>(ppOriginal)) != MH_OK)
    {
        LOG_ERROR("Failed to create hook: {}", displayName.c_str());
        return;
    }

    if (MH_EnableHook((LPVOID)pTarget) != MH_OK)
    {
        LOG_ERROR("Failed to enable hook: {}", displayName.c_str());
        return;
    }
    LOG_INFO("Added hook: {}", displayName.c_str());
}
} // namespace MinHook