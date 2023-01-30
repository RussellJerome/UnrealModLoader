#pragma once
#include <cstdint>
#include <optional>
#include <string>
#include <variant>

namespace GameSettings
{

struct ExtendedPattern
{
    std::string Pattern = "";
    uint32_t FirstOpCodes = 0;
    uint32_t TotalByteInstruction = 0;
};

struct GInfoPatterns
{
    std::optional<ExtendedPattern> GName = {};
    std::optional<ExtendedPattern> GObject = {};
    std::optional<ExtendedPattern> GWorld = {};
};

struct GInfoOffsets
{
    std::optional<uint32_t> GName = {};
    std::optional<uint32_t> GObject = {};
    std::optional<uint32_t> GWorld = {};
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
    std::optional<std::string> GameStateInit = {};
    std::optional<std::string> BeginPlay = {};
    std::optional<std::string> StaticLoadObject = {};
    std::optional<std::string> SpawnActorFTrans = {};
    std::optional<std::string> CallFunctionByNameWithArguments = {};
    std::optional<std::string> ProcessEvent = {};
    std::optional<std::string> CreateDefaultObject = {};
};

struct FunctionInfoOffsets
{
    std::optional<uint32_t> GameStateInit = {};
    std::optional<uint32_t> BeginPlay = {};
    std::optional<uint32_t> StaticLoadObject = {};
    std::optional<uint32_t> SpawnActorFTrans = {};
    std::optional<uint32_t> CallFunctionByNameWithArguments = {};
    std::optional<uint32_t> ProcessEvent = {};
    std::optional<uint32_t> CreateDefaultObject = {};
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