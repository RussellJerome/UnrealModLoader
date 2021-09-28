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
	UE4::AActor* CurrentModActor;
	bool IsEnabled;
	bool ContainsButton;
	bool WasInitialized;
	std::vector<std::string> ModButtons;
};

class LOADER_API Global {
public:
	static std::vector<ModInfo> ModInfoList;
	static std::string GameName;
	static bool bIsMenuOpen;
	static std::string Version;
	static std::vector<class Mod*> CoreMods;
	static EventDispatcher eventSystem;

	static void AddToCoreMods(Mod* mod)
	{
		CoreMods.push_back(mod);
	}
};
