#include "ModLoader.h"
#include "Utility.h"
#include "MinHook.h"
#include "../UnrealModLoader.h"
#include <iostream>
#include "../UE4/Ue4.hpp"
#include "UMG/Blueprint/UserWidget.h"
#include "../UEGUI/UEGUI.h"
#include "GameFramework/Actor.h"

namespace ModLoader
{
	namespace Hooks
	{
		PVOID(*origInitGameState)(void*);
		PVOID hookInitGameState(void* Ret)
		{
			LOG_INFO("AGameModeBase::InitGameState");
			UE4::InitSDK();

			
			return origInitGameState(Ret);
		}

		PVOID(*origBeginPlay)(UE4::AActor*);
		PVOID hookBeginPlay(UE4::AActor* Actor)
		{
	/*		if (Actor->IsA(UE4::UObject::FindClass(UML::GetGameInfo()->BeginPlayOverwrite)))
			{
				LOG_INFO("AActor::BeginPlay");
			}*/
			//LOG_INFO("AActor::BeginPlay");
			return origBeginPlay(Actor);
		}
	};


	bool f1_pressed;
	DWORD __stdcall UMLRenderThread(LPVOID)
	{
		while (true)
		{
			if (GetAsyncKeyState(VK_F1) != 0)
				f1_pressed = true;
			else if (f1_pressed)
			{
				f1_pressed = false;
				auto UMLWidget = UEGUI::CreateUEWidget();
			}
			Sleep(1000 / 60);
		}
		return NULL;
	}

	void Init()
	{
		MinHook::Init();
		LOG_INFO("MinHook Initialized");
		LOG_INFO("Loading Core Mods");
		MinHook::Add(UML::GetGameInfo()->GameStateInit, &Hooks::hookInitGameState, &Hooks::origInitGameState, "AGameModeBase::InitGameState");
		MinHook::Add(UML::GetGameInfo()->BeginPlay, &Hooks::hookBeginPlay, &Hooks::origBeginPlay, "AActor::BeginPlay");
		CreateThread(0, 0, UMLRenderThread, 0, 0, 0);
	}

	void CleanUp()
	{
		MH_DisableHook(MH_ALL_HOOKS);
		MH_Uninitialize();
	}
};