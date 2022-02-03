#include "ExampleMod.h"
#include "Utilities/MinHook.h"

// Only Called Once, if you need to hook shit, declare some global non changing values
void ExampleMod::InitializeMod()
{
	UE4::InitSDK();
	SetupHooks();
	//UseMenuButton = true; // Allows Mod Loader To Show Button
}

BPFUNCTION(WriteToFile)
{
	std::cout << "WriteToFile" << std::endl;
	struct InputParams
	{
		UE4::FString NameTest;
	};
	auto Inputs = stack->GetInputParams<InputParams>();

	std::cout << "Inputs: " << Inputs->NameTest.ToString() << std::endl;
	stack->SetOutput<UE4::FString>("OutPutString", L"KboyGang");
	stack->SetOutput<int>("ReturnValue", 67);
}

void ExampleMod::ProcessFunction(UE4::UObject* obj, UE4::FFrame* Frame, void* Result)
{
	REGISTER_FUNCTION(WriteToFile);
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