#include "Globals.h"
// Global defines

std::vector<ModInfo> Global::ModInfoList;
std::string Global::GameName;
UE4::AActor* Global::ModLoaderActor;
bool Global::bIsMenuOpen;
std::string Global::Version = "2.0.0";
EventDispatcher Global::eventSystem;
std::vector<class Mod*> Global::CoreMods;