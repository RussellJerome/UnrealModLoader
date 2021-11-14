#include "Globals.h"
// Global defines

std::vector<ModInfo> Global::ModInfoList;
std::string Global::GameName;
bool Global::bIsMenuOpen;
std::string Global::Version = "2.0.2";
EventDispatcher Global::eventSystem;
std::vector<class Mod*> Global::CoreMods;