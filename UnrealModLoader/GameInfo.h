#pragma once
#include <Windows.h>
#include <string>

struct Offsets {
	struct {
		DWORD Index = 0x0;
		DWORD Class = 0x0;
		DWORD Name = 0x0;
		DWORD Outer = 0x0;
	} UObject;
	struct {
		DWORD Next = 0x0;
	} UField;
	struct {
		DWORD SuperStruct = 0x0;
		DWORD Children = 0x0;
		DWORD PropertiesSize = 0x0;
		DWORD OverallUStructSize = 0x0;
	} UStruct;
	struct {
		DWORD FunctionFlags = 0x0;
		DWORD Func = 0x0;
	} UFunction;
	struct {
		DWORD Next = 0x0;
		DWORD Name = 0x0;
	} FField;
	struct {
		DWORD ArrayDim = 0x0;
		DWORD Offset = 0x0;
	} Property;
};

class GameInfo
{
public:
	GameInfo()
	{
		defs = new Offsets();
	}

	//Handles the engine object defs
	Offsets* defs;

	//Stores the profile name
	std::string ProfileName;

	//Handles the basic game information
	bool IsUsingDeferedSpawn = false;
	bool IsUsingFChunkedFixedUObjectArray = false;
	bool IsUsing4_22 = false;
	int UsesFNamePool = 0;
	bool bIsFProperty = false;
	std::string BeginPlayOverwrite = "Class Engine.PlayerController";

	//Handles GInfo
	bool IsGInfoPatterns = false;
	DWORD64 GName = 0x0;
	DWORD64 GObject = 0x0;
	DWORD64 GWorld = 0x0;
	
	//Handles locations to specific engine functions
	bool IsFunctionPatterns = false;
	DWORD64 GameStateInit = 0x0;
	DWORD64 BeginPlay = 0x0;
	DWORD64 StaticLoadObject = 0x0;
	DWORD64 SpawnActorFTrans = 0x0;
	DWORD64 CallFunctionByNameWithArguments = 0x0;
	DWORD64 ProcessEvent = 0x0;
	DWORD64 CreateDefaultObject = 0x0;
	DWORD64 ProcessInternals = 0x0;

	bool IsUsingUpdatedStaticConstruct = false;
	DWORD64 StaticConstructObject_Internal = 0x0;

	//Keeps track of whether or not Engine Objects defs arn't defined
	bool IsUObjectMissing = true;
	bool IsUFieldMissing = true;
	bool IsUStructMissing = true;
	bool IsUFunctionMissing = true;
	bool IsPropertyMissing = false;
};