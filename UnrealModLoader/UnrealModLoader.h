#pragma once
#include <string>
#include "GameInfo.h"

namespace UML
{
	static const std::string LoaderVersion = "3.0.0";

	static std::string LoaderPath;

	//Setup UML
	void StartUML();
	//CleanUp UML
	void CleanUp();
	
	class GameInfo* GetGameInfo();
};