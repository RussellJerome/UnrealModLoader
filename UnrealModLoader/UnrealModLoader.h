#pragma once
#include <string>
#include "GameInfo.h"

namespace UML
{
	static const std::string LoaderVersion = "3.0.0";

	std::string LoaderPath;

	//Setup UML
	void StartUML();
	//CleanUp UML
	void CleanUp();

	static class GameInfo* GetGameInfo();
};