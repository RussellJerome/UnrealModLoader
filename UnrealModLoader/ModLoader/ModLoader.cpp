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
			UE4::InitSDK();
			LOG_INFO("InitSDK");
			std::cout << UE4::UObject::GObjects << std::endl;
			std::cout << UE4::UObject::GObjects->GetAsTUArray().Num() << std::endl;
			for (size_t i = 0; i < UE4::UObject::GObjects->GetAsTUArray().Num(); i++)
			{
				auto Object = UE4::UObject::GObjects->GetAsTUArray().GetByIndex(i).Object;
				if(Object)
					std::cout << Object->GetName() << std::endl;
			}

			return origInitGameState(Ret);
		}

		PVOID(*origBeginPlay)(void*);
		PVOID hookBeginPlay(void* Actor)
		{
			//LOG_INFO("AActor::BeginPlay");
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