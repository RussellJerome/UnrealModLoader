#pragma once
#include "UE4.hpp"
#include <map>
#include <iostream>
#include <string>

class Global {
public:
	static std::vector<std::wstring> modnames;
	static std::vector<UE4::AActor*> ModActors;
	static UE4::AActor* ModLoaderActor;
	static std::string GameName;
};
