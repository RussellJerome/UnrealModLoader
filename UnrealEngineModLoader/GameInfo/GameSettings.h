#pragma once
#include <cstdint>
#include <optional>
#include <string>
#include <variant>

namespace GameSettings
{

struct GInfoPatterns
{
    std::string GName = "";
    uint32_t GNameFirstOpCodes = 0;
    uint32_t GNameTotalByteInstruction = 0;

    std::string GObject = "";
    uint32_t GObjectFirstOpCodes = 0;
    uint32_t GobjectTotalByteInstruction = 0;

    std::string GWorld = "";
    uint32_t GWorldFirstOpCodes = 0;
    uint32_t GWorldTotalByteInstruction = 0;
};

struct GInfoOffsets
{
    uint32_t GName = 0;
    uint32_t GObject = 0;
    uint32_t GWorld = 0;
};

struct GInfo
{
    std::variant<GInfoPatterns, GInfoOffsets> Info;
};

struct UObjectDef
{
    uint32_t Index = 0;
    uint32_t Class = 0;
    uint32_t Name = 0;
    uint32_t Outer = 0;
};

struct UFieldDef
{
    uint32_t Next = 0;
};

struct UStructDef
{
    uint32_t SuperStruct = 0;
    uint32_t Children = 0;
    uint32_t PropertiesSize = 0;
};

struct UFunctionDef
{
    uint32_t FunctionFlags = 0;
    uint32_t Func = 0;
};

struct FField
{
    uint32_t Name = 0;
    uint32_t Next = 0;
};

struct Property
{
    uint32_t ArrayDim = 0;
    uint32_t Offset = 0;
    std::optional<FField> FProperty;
};

struct FunctionInfoPatterns
{
    std::string GameStateInit = "";
    std::string BeginPlay = "";
    std::string StaticLoadObject = "";
    std::string SpawnActorFTrans = "";
    std::string CallFunctionByNameWithArguments = "";
    std::string ProcessEvent = "";
    std::string CreateDefaultObject = "";
};

struct FunctionInfoOffsets
{
    uint32_t GameStateInit = 0;
    uint32_t BeginPlay = 0;
    uint32_t StaticLoadObject = 0;
    uint32_t SpawnActorFTrans = 0;
    uint32_t CallFunctionByNameWithArguments = 0;
    uint32_t ProcessEvent = 0;
    uint32_t CreateDefaultObject = 0;
};

struct FunctionInfo
{
    std::variant<FunctionInfoPatterns, FunctionInfoOffsets> Info;
};

struct ProcessInternalFunction
{
    std::string ProcessInternal = "";
};

struct StaticConstructObject_InternalInfo
{
    bool IsUsingUpdatedStaticConstruct = false;
    std::string StaticConstructObject_InternalFunction = "";
};

struct GameSettings
{
    // Set to true if the game engine version is 4.18 and up
    bool IsUsingFChunkedFixedUObjectArray = false;
    // Set to true if the game engine version is 4.23 and up
    bool UsesFNamePool = false;
    // Fallback if Spawn Actor can't be found or refuses to work. You should almost NEVER use.
    bool IsUsingDeferedSpawn = false;
    // Set to true if the game is 4.22
    bool IsUsing4_22 = false;
    // ?
    bool IsDefaultObjectArrayed = false;
    // If you get any Direct X errors such as resizing, enable this to delay the hook and prevent most issues.
    bool DelayGUISpawn = false;
    // Overwrites the BeginPlay hook which calls PostBeginPlay and PostLoaderStart. To use PlayerController default
    // leave empty.
    std::optional<std::string> BeginPlayOverwrite = {};

    std::optional<GInfo> GInfoSettings = {};
    std::optional<UObjectDef> UObjectDefSettings = {};
    std::optional<UFieldDef> UFieldDefSettings = {};
    std::optional<UStructDef> UStructDefSettings = {};
    std::optional<UFunctionDef> UFunctionDefSettings = {};
    std::optional<Property> PropertySettings = {};
    std::optional<FunctionInfo> FunctionInfoSettings = {};
    std::optional<ProcessInternalFunction> ProcessInternalFunctionSettings = {};
    std::optional<StaticConstructObject_InternalInfo> StaticConstructObject_InternalInfoSettings = {};

    static GameSettings GetBakedSettings();
};

} // namespace GameSettings