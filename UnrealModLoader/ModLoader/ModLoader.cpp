#include "ModLoader.h"
#include "Utility.h"
#include "MinHook.h"
#include "../UnrealModLoader.h"
#include <iostream>
#include "../UE4/Ue4.hpp"
namespace ModLoader
{
	namespace Hooks
	{
		PVOID(*origInitGameState)(void*);
		PVOID hookInitGameState(void* Ret)
		{
			LOG_INFO("AGameModeBase::InitGameState");
			return origInitGameState(Ret);
		}

		PVOID(*origBeginPlay)(void*);
		PVOID hookBeginPlay(void* Actor)
		{
			LOG_INFO("AActor::BeginPlay");
			return origBeginPlay(Actor);
		}
	};
	void Init()
	{

		MinHook::Init();
		LOG_INFO("MinHook Initialized");
		LOG_INFO("Loading Core Mods");
		MinHook::Add(UML::GetGameInfo()->GameStateInit, &Hooks::hookInitGameState, &Hooks::origInitGameState, "AGameModeBase::InitGameState");
		MinHook::Add(UML::GetGameInfo()->BeginPlay, &Hooks::hookBeginPlay, &Hooks::origBeginPlay, "AActor::BeginPlay");
	}

	void CleanUp()
	{
		MH_DisableHook(MH_ALL_HOOKS);
		MH_Uninitialize();
	}
};