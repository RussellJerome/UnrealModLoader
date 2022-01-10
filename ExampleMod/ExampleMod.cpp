#include "ExampleMod.h"
#include "Utilities/MinHook.h"

// Only Called Once, if you need to hook shit, declare some global non changing values
void ExampleMod::InitializeMod()
{
	UE4::InitSDK();
	SetupHooks();
	//UseMenuButton = true; // Allows Mod Loader To Show Button
}

void ExampleMod::ProcessFunction(UE4::UObject* obj, UE4::FFrame* Frame)
{
	if (obj)
	{
		//if(obj == ModActor) // Checks If the actor calling this function is your Mod Actor Function
	}
}

void ExampleMod::InitGameState()
{
}

void ExampleMod::BeginPlay(UE4::AActor* Actor)
{
}

void ExampleMod::PostBeginPlay(std::wstring ModActorName, UE4::AActor* Actor)
{
	// Filters Out All Mod Actors Not Related To Your Mod
	std::wstring TmpModName(ModName.begin(), ModName.end());
	if (ModActorName == TmpModName)
	{
		//Sets ModActor Ref
		ModActor = Actor;
	}
}

void ExampleMod::OnModMenuButtonPressed()
{
}

void ExampleMod::DrawImGui()
{
}