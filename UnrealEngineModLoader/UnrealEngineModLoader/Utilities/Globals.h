#pragma once
#include "UE4.hpp"
#include <map>
#include <iostream>
#include <string>
#include "../Lib.h"
#include "../Mod/Mod.h"
#include "../EventSystem.h"
struct ModInfo
{
	std::wstring ModName;
	std::string ModAuthor = "Unknown Author";
	std::string ModDescription = "No Description";
	std::string ModVersion = "Unknown Version";
	UE4::AActor* CurrentModActor = nullptr;
	UE4::UObject* PersistentObject = nullptr;
	bool IsEnabled = 0;
	bool ContainsButton = 0;
	bool WasInitialized = 0;
	std::vector<std::string> ModButtons;
};

class LOADER_API Global {
public:
	std::vector<ModInfo> ModInfoList;
	std::string GameName;
	bool bIsMenuOpen;
	std::string Version = "2.1.0";
	std::vector<class Mod*> CoreMods;
	EventDispatcher eventSystem;

	static Global* GetGlobals();

	void AddToCoreMods(Mod* mod)
	{
		CoreMods.push_back(mod);
	}
private:
	static Global* glb;
};
