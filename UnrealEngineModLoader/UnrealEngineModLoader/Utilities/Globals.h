#pragma once
#include "UE4.hpp"
#include <map>
#include <iostream>
#include <string>

struct Mod
{
	std::wstring ModName;
	UE4::AActor* CurrentModActor;
	bool IsEnabled;
	bool ContainsButton;
	bool WasInitialized;
};

class Global {
public:
	static std::vector<Mod> ModInfo;
	static UE4::AActor* ModLoaderActor;
	static std::string GameName;
	static bool bIsMenuOpen;
	static std::string Version;
};
