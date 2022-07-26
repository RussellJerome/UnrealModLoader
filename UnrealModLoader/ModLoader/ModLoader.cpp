#include "ModLoader.h"
#include "../Utilities/Utility.h"
#include "Ue4.hpp"
namespace ModLoader
{
	bool isModsLoadedWorld = false;
	void InitGameState(void* GameMode)
	{
		static bool bGameStateClassInitNotRan = true;
		LOG_INFO("GameStateHook");
		isModsLoadedWorld = false;
		if (bGameStateClassInitNotRan)
		{
			UE4::InitSDK();
			LOG_INFO("Engine Classes Loaded");
			bGameStateClassInitNotRan = false;
		}
	}

	void BeginPlay(UE4::AActor* Actor)
	{
	}

	void Tick(int ELevelTick, float Delta)
	{
	}
};