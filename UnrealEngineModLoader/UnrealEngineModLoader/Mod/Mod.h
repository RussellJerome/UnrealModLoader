#pragma once
#include <string>
#include "Utilities/Logger.h"
#include "GameInfo/GameInfo.h"
#include "Utilities/Globals.h"
#include "../LoaderUI.h"
#include "Ue4.hpp"
#define BPFUNCTION(Name, Frame) if(Name == Frame->Node->GetName())

class LOADER_API Mod
{
public:
	// Mod Default Variables
	std::string ModName;
	std::string ModVersion;
	std::string ModDescription;
	std::string ModAuthors;
	std::string ModLoaderVersion;
	bool UseMenuButton;
	//ModInternals
	bool IsFinishedCreating;
	
	//Used Internally to setup Hook Event System
	void SetupHooks();

	//Called after each mod is injected, Looped through via gloabals
	virtual void InitializeMod();

	//Either ProcessInternals or ProcessLocalScriptFunction which you use to communicate between your BPMod and your C++ Mod
	virtual void ProcessFunction(UE4::UObject* obj, UE4::FFrame* Frame);

	//InitGameState Call
	virtual void InitGameState();

	//Call ImGui Here
	virtual void DrawImGui();

	//Beginplay Hook of Every Actor
	virtual void BeginPlay(UE4::AActor* Actor);

	//PostBeginPlay of EVERY Blueprint ModActor
	virtual void PostBeginPlay(std::wstring ModActorName, UE4::AActor* Actor);

	virtual void OnModMenuButtonPressed();

	//Called When Mod Construct Finishes
	void CompleteModCreation();

	static Mod* ModRef;
};