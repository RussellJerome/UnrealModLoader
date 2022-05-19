#pragma once
#include "GameFramework/Actor.h"

namespace ModLoader
{
	/*
	NOTE
	====
	THIS IS WHERE WE WILL HANDLE THE ACTUAL MODLOADER LOGIC FOR THE HOOKED FUNCTIONS
	*/
	void InitGameState(void* GameMode);
	void BeginPlay(UE4::AActor* Actor);
	void Tick(int ELevelTick, float Delta);
};