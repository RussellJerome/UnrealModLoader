#pragma once
#include <Windows.h>
#include <Psapi.h>
#include "Utilities/EngineDefFinder.h"
#include "Basic.hpp"
#include "Utilities//Pattern.h"
#include "CoreUObject_classes.hpp"
namespace UE4
{
	static void InitSDK()
	{
		DWORD64   Names_offset = NULL;
		if (!FName::IsUsingNamePool())
		{
			Names_offset = (*(DWORD64*)(GameProfile::SelectedGameProfile.GName));
			FName::GNames = (DWORD*)Names_offset;
		}
		else
		{
			Names_offset = (DWORD64)(GameProfile::SelectedGameProfile.GName);
			FName::GNames = (DWORD*)Names_offset;
		}

		DWORD64   GObjObjects_offset = NULL;
		GObjObjects_offset = (DWORD64)(GameProfile::SelectedGameProfile.GObject);
		UObject::GObjects = (FUObjectArray*)GObjObjects_offset;

		DWORD64   GWorldObjects = NULL;
		GWorldObjects = (DWORD64)(GameProfile::SelectedGameProfile.GWorld);
		UWorld::GWorld = (UWorld**)GWorldObjects;

		#ifdef UNREALENGINEMODLOADER_EXPORTS //Stops dumb errors from the ExampleMod shit
		if (GameProfile::SelectedGameProfile.IsEngineDefsMissing)
		{
			if (ClassDefFinder::FindEngineClasses())
			{
				Log::Info("All Engine Classes Found");
				GameProfile::SelectedGameProfile.IsEngineDefsMissing = false;
			}
		}
		#endif

	}
}