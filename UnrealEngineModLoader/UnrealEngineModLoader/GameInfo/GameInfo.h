#pragma once
#include <string>
#include <vector>
#include <Windows.h>
#include "Memory/mem.h"

struct Offsets {
	struct {
		uint16_t Index = 0;
		uint16_t Class = 0;
		uint16_t Name = 0;
		uint16_t Outer = 0;
	} UObject;
	struct {
		uint16_t Next = 0;
	} UField;
	struct {
		uint16_t SuperStruct = 0;
		uint16_t Children = 0;
		uint16_t PropertiesSize = 0;
		uint16_t OverallUStructSize = 0;
	} UStruct;
	struct {
		uint16_t FunctionFlags = 0;
		uint16_t Func = 0;
	} UFunction;
	struct {
		uint16_t PersistentLevel = 0x0;
		uint16_t AuthorityGameMode = 0x0;
	}UWorld;
	struct {
		uint16_t WorldArray = 0x0;
	}ULevel;
};

extern Offsets defs;

class GameProfile
{
public:
	std::string LoaderPath;
	int UsesFNamePool;
	std::string BeginPlayOverwrite = "Class Engine.PlayerController";

	bool IsGInfoPatterns;
	DWORD64 GName;
	DWORD64 GObject;
	DWORD64 GWorld;
	bool IsUsingDeferedSpawn;
	bool IsUsingFChunkedFixedUObjectArray;
	bool IsUsing4_22;

	bool IsFunctionPatterns;
	DWORD64 ProcessEvent;
	DWORD64 CreateDefualtObject;
	DWORD64 GameStateInit;
	DWORD64 BeginPlay;
	DWORD64 Say;
	DWORD64 StaticLoadObject;
	DWORD64 SpawnActorFTrans;
	DWORD64 CallFunctionByNameWithArguments;

	bool IsEngineDefsMissing;
	bool IsUWorldMissing;

	static GameProfile SelectedGameProfile;
	static void CreateGameProfile();
};