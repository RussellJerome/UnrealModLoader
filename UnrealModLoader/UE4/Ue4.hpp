#pragma once
#include "../UnrealModLoader.h"
#include "UObject/Object.h"
#include "UObject/NameType.h"
#include "Engine/World.h"
#include "../Memory/EngineDefFinder.h"
#include <Windows.h>
#include <Psapi.h>

namespace UE4
{
	static void InitSDK()
	{
		DWORD64 Names_offset = NULL;
		if (!FName::IsUsingNamePool())
		{
			Names_offset = (*(DWORD64*)(UML::GetGameInfo()->GName));
			FName::GNames = (DWORD*)Names_offset;
		}
		else
		{
			Names_offset = (DWORD64)(UML::GetGameInfo()->GName);
			FName::GNames = (DWORD*)Names_offset;
		}

		DWORD64   GObjObjects_offset = NULL;
		GObjObjects_offset = (DWORD64)(UML::GetGameInfo()->GObject);
		UObject::GObjects = (FUObjectArray*)GObjObjects_offset;


		DWORD64   GWorldObjects = NULL;
		GWorldObjects = (DWORD64)(UML::GetGameInfo()->GWorld);
		UWorld::GWorld = (UWorld**)GWorldObjects;

		#ifdef UNREALMODLOADER_EXPORTS //Stops dumb errors from the ExampleMod shit
		if (UML::GetGameInfo()->IsUObjectMissing)
		{
			LOG_WARNING("UObject Not Defined. Scanning for def.");
			UML::EngineDefFinder::FindUObjectDefs();
			UML::GetGameInfo()->IsUObjectMissing = false;
		}

		if (UML::GetGameInfo()->IsUFieldMissing)
		{
			LOG_WARNING("UField Not Defined. Scanning for def.");
			UML::EngineDefFinder::FindUFieldDefs();
			UML::GetGameInfo()->IsUFieldMissing = false;
		}
		if (UML::GetGameInfo()->IsUStructMissing)
		{
			LOG_WARNING("UStruct Not Defined. Scanning for def.");
			UML::EngineDefFinder::FindUStructDefs();
			UML::GetGameInfo()->IsUStructMissing = false;
		}
		if (UML::GetGameInfo()->IsUFunctionMissing)
		{
			LOG_WARNING("UFunction Not Defined. Scanning for def.");
			UML::EngineDefFinder::FindUFunctionDefs();
			UML::GetGameInfo()->IsUFunctionMissing = false;
		}

		if (UML::GetGameInfo()->IsPropertyMissing)
		{
			UML::EngineDefFinder::FindUEProperty();
		}
		LOG_INFO("All Engine Classes Found");
		#endif

	}
}