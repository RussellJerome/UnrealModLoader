#include "Utilities/Logger.h"
#include "Utilities/MinHook.h"
#include "GameInfo/GameInfo.h"

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        GameProfile::CreateGameProfile();
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        //MH_DisableHook(MH_ALL_HOOKS);
        //MH_Uninitialize();
        break;
    }
    return TRUE;
}