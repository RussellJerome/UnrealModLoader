#include "Globals.h"
// Global defines

std::vector<ModInfo> Global::ModInfoList;
std::string Global::GameName;
bool Global::bIsMenuOpen;
std::string Global::Version = "2.1.0";
EventDispatcher Global::eventSystem;
std::vector<class Mod*> Global::CoreMods;