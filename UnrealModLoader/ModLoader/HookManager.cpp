#include "HookManager.h"
#include "Utility.h"
#include "MinHook.h"
#include "../UnrealModLoader.h"
#include "ModLoader.h"
#include <iostream>
#include "../Memory/Memory.h"

namespace HookManager
{
	/*
	NOTE
	====
	THIS IS WHERE WE WILL HOOK ARE NEEDED UE4 FUNCTIONS.
	THE MODLOADER CODE WILL BE HANDLED IN THEIR RESPECTED FUNCTIONS;
	*/

	namespace HookedFunctions
	{
		PVOID(*origInitGameState)(void*);
		PVOID hookInitGameState(void* Ret)
		{
			ModLoader::InitGameState(Ret);
			return origInitGameState(Ret);
		}

		PVOID(*origBeginPlay)(UE4::AActor*);
		PVOID hookBeginPlay(UE4::AActor* Actor)
		{
			ModLoader::BeginPlay(Actor);
			return origBeginPlay(Actor);
		}

		PVOID(*origUWorldTick)(int, float);
		PVOID hookUWorldTick(int ELevelTick, float Delta)
		{
			ModLoader::Tick(ELevelTick, Delta);
			return origUWorldTick(ELevelTick, Delta);
		}
	};

	void Init()
	{
		MinHook::Init();
		LOG_INFO("MinHook Initialized");
		MinHook::Add(UML::GetGameInfo()->GameStateInit, &HookedFunctions::hookInitGameState, &HookedFunctions::origInitGameState, "AGameModeBase::InitGameState");
		MinHook::Add(UML::GetGameInfo()->BeginPlay, &HookedFunctions::hookBeginPlay, &HookedFunctions::origBeginPlay, "AActor::BeginPlay");
		//MinHook::Add(UML::GetGameInfo()->UWorldTick, &HookedFunctions::hookUWorldTick, &HookedFunctions::origUWorldTick, "UWorld::Tick");
	}

	void CleanUp()
	{
		MH_DisableHook(MH_ALL_HOOKS);
		MH_Uninitialize();
	}
}