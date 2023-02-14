#include "Hooks.h"

#ifdef ENABLE_GUI
#include "LoaderUI.h"
#endif

#include "Memory/mem.h"
#include "UE4/Ue4.hpp"
#include <GameInfo/GameInfo.h>
#include <Memory/CoreModLoader.h>
#include <Utilities/Dumper.h>
#include <Utilities/Globals.h>
#include <Utilities/MinHook.h>
bool bIsProcessInternalsHooked = false;
bool GameStateClassInitNotRan = true;

namespace Hooks
{
namespace HookedFunctions
{
struct PrintStringParams
{
    UE4::FString Message;
};

struct GetPersistentObject
{
    UE4::FString ModName;
};

PVOID (*origProcessFunction)(UE4::UObject *, UE4::FFrame *, void *const);
PVOID hookProcessFunction(UE4::UObject *obj, UE4::FFrame *Frame, void *const Result)
{
    PVOID ret = nullptr;
    if (!GameStateClassInitNotRan)
    {
        for (const auto &Wrapper : Global::GetGlobals()->GetBPFunctionWrappers())
        {
            if (Frame->Node->GetName() == Wrapper.FunctionName)
            {
                Wrapper.FuncPtr(obj, Frame, Result, origProcessFunction);
                return nullptr;
            }
        }
    }
    return origProcessFunction(obj, Frame, Result);
}

PVOID (*origInitGameState)(void *);
PVOID hookInitGameState(void *Ret)
{
    LOG_INFO("GameStateHook");
    if (GameStateClassInitNotRan)
    {
        UE4::InitSDK();
        LOG_INFO("Engine Classes Loaded");
        if (Global::GetGlobals()->CoreMods.size() > 0)
        {
            for (size_t i = 0; i < Global::GetGlobals()->CoreMods.size(); i++)
            {
                auto CurrentCoreMod = Global::GetGlobals()->CoreMods[i];
                if (CurrentCoreMod->IsFinishedCreating)
                {
                    LOG_INFO("InitializeMod Called For {}", CurrentCoreMod->ModName.c_str());
                    CurrentCoreMod->InitializeMod();
                }
                else
                {
                    LOG_ERROR("Mod {} wasnt setup in time"), CurrentCoreMod->ModName;
                }
            }
        }

        UE4::FTransform transform = UE4::FTransform::FTransform();
        UE4::FActorSpawnParameters spawnParams = UE4::FActorSpawnParameters::FActorSpawnParameters();
        if (GameProfile::SelectedGameProfile.StaticLoadObject)
        {
            LOG_INFO("StaticLoadObject Found");
        }
        else
        {
            LOG_ERROR("StaticLoadObject Not Found");
        }
        GameStateClassInitNotRan = false;
    }

    if (GameProfile::SelectedGameProfile.StaticLoadObject)
    {

        if (GameProfile::SelectedGameProfile.ProcessInternals)
        {
            if (GameProfile::SelectedGameProfile.ProcessInternals)
            {
                MinHook::Add(GameProfile::SelectedGameProfile.ProcessInternals, &HookedFunctions::hookProcessFunction,
                             &HookedFunctions::origProcessFunction, "ProcessBlueprintFunctions");
                LOG_INFO("ProcessBlueprintFunctions hooked!");
            }
            else
            {
                LOG_WARN("ProcessBlueprintFunctions could not be located! Mod Loader "
                         "Functionality Will be Limited!");
            }
        }

        LOG_INFO("StaticLoadObject thing");
        UE4::FTransform transform;
        transform.Translation = UE4::FVector(0, 0, 0);
        transform.Rotation = UE4::FQuat(0, 0, 0, 0);
        transform.Scale3D = UE4::FVector(1, 1, 1);
        UE4::FActorSpawnParameters spawnParams = UE4::FActorSpawnParameters::FActorSpawnParameters();

        Global::GetGlobals()->eventSystem.dispatchEvent("InitGameState");
    }
    LOG_INFO("Returning to GameState --------------------------------------------------------");
    return origInitGameState(Ret);
}

PVOID (*origBeginPlay)(UE4::AActor *);
PVOID hookBeginPlay(UE4::AActor *Actor)
{
    if (!GameStateClassInitNotRan)
    {
        if (Actor->IsA(UE4::ACustomClass::StaticClass(GameProfile::SelectedGameProfile.BeginPlayOverwrite)))
        {
            LOG_INFO("Beginplay Called");
        }
        Global::GetGlobals()->eventSystem.dispatchEvent("BeginPlay", Actor);
    }
    return origBeginPlay(Actor);
}
}; // namespace HookedFunctions

DWORD __stdcall InitHooks(LPVOID)
{
    MinHook::Init();
    LOG_INFO("MinHook Setup");
    LOG_INFO("Loading Core Mods");
    CoreModLoader::LoadCoreMods();

    MinHook::Add(GameProfile::SelectedGameProfile.GameStateInit, &HookedFunctions::hookInitGameState,
                 &HookedFunctions::origInitGameState, "AGameModeBase::InitGameState");
    MinHook::Add(GameProfile::SelectedGameProfile.BeginPlay, &HookedFunctions::hookBeginPlay,
                 &HookedFunctions::origBeginPlay, "AActor::BeginPlay");

#ifdef ENABLE_GUI
    LoaderUI::GetUI()->CreateUILogicThread();
    if (!GameProfile::SelectedGameProfile.bDelayGUISpawn)
    {
        LoaderUI::HookDX();
    }
#endif

    return NULL;
}

void SetupHooks()
{
    LOG_INFO("Setting Up Loader");
    CreateThread(0, 0, InitHooks, 0, 0, 0);
}
}; // namespace Hooks