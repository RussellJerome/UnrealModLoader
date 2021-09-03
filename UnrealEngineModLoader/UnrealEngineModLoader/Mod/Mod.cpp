#include "Mod.h"

Mod* Mod::ModRef;

namespace CallBackHandler
{
	void CallBackBeginPlay(UE4::AActor* Actor)
	{
		Mod::ModRef->BeginPlay(Actor);
	}

	void CallBackInitGameState()
	{
		Mod::ModRef->InitGameState();
	}

	void CallBackDrawImGui()
	{
		Mod::ModRef->DrawImGui();
	}

	void CallBackProcessFunction(UE4::UObject* obj, UE4::FFrame* Frame)
	{
		Mod::ModRef->ProcessFunction(obj, Frame);
	}

	void CallBackPostBeginPlay(std::wstring ModActorName, UE4::AActor* Actor)
	{
		Mod::ModRef->PostBeginPlay(ModActorName, Actor);
	}
}

void Mod::ProcessFunction(UE4::UObject* obj, UE4::FFrame* Frame)
{
}

void Mod::InitGameState()
{
}

void Mod::OnModMenuButtonPressed()
{
}

void Mod::BeginPlay(UE4::AActor* Actor)
{
}

void Mod::PostBeginPlay(std::wstring ModActorName, UE4::AActor* Actor)
{
}

void Mod::DrawImGui()
{
}

void Mod::SetupHooks()
{
	Global::eventSystem.registerEvent(new Event<UE4::AActor*>("BeginPlay", &CallBackHandler::CallBackBeginPlay));
	Global::eventSystem.registerEvent(new Event<>("InitGameState", &CallBackHandler::CallBackInitGameState));
	Global::eventSystem.registerEvent(new Event<UE4::UObject*, UE4::FFrame*>("ProcessFunction", &CallBackHandler::CallBackProcessFunction));
	Global::eventSystem.registerEvent(new Event<std::wstring, UE4::AActor*>("PostBeginPlay", &CallBackHandler::CallBackPostBeginPlay));
	Global::eventSystem.registerEvent(new Event<>("DrawImGui", &CallBackHandler::CallBackDrawImGui));
}

void Mod::CompleteModCreation()
{
	IsFinishedCreating = true;
	Global::AddToCoreMods(ModRef);
	Log::Info("Core Mod Created: %s", ModName.c_str());
	if (ModLoaderVersion != Global::Version)
	{
		Log::Warn("Mod: %s was created with a different version of the Unreal Mod Loader. This mod may be unstable.", ModName.c_str());
	}
	InitializeMod();
}

void Mod::InitializeMod()
{

}