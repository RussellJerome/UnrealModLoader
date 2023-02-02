#pragma once
#include <cstdint>
#include <nlohmann/json.hpp>
#include <optional>
#include <string>
#include <variant>

namespace GameSettings
{

#define OPTIONAL_GET(Json, Type, Name, Dest)                                                                           \
    if (Json.contains(Name) && !Json.at(Name).is_null())                                                               \
    {                                                                                                                  \
        Type Variable = {};                                                                                            \
        j.at(Name).get_to(Variable);                                                                                   \
        Dest = Variable;                                                                                               \
    }

struct ExtendedPattern
{
    std::string Pattern = "";
    uint32_t FirstOpCodes = 0;
    uint32_t TotalByteInstruction = 0;
};

static void from_json(const nlohmann::json &j, ExtendedPattern &Pattern)
{
    j.at("pattern").get_to(Pattern.Pattern);
    j.at("first_op_codes").get_to(Pattern.FirstOpCodes);
    j.at("total_byte_instruction").get_to(Pattern.TotalByteInstruction);
}

struct GInfoPatterns
{
    std::optional<ExtendedPattern> GName = {};
    std::optional<ExtendedPattern> GObject = {};
    std::optional<ExtendedPattern> GWorld = {};
};

static void from_json(const nlohmann::json &j, GInfoPatterns &Patterns)
{
    OPTIONAL_GET(j, ExtendedPattern, "g_name", Patterns.GName)
    OPTIONAL_GET(j, ExtendedPattern, "g_object", Patterns.GObject)
    OPTIONAL_GET(j, ExtendedPattern, "g_world", Patterns.GWorld)
}

struct GInfoOffsets
{
    std::optional<uint32_t> GName = {};
    std::optional<uint32_t> GObject = {};
    std::optional<uint32_t> GWorld = {};
};

static void from_json(const nlohmann::json &j, GInfoOffsets &Offsets)
{
    OPTIONAL_GET(j, uint32_t, "g_name", Offsets.GName)
    OPTIONAL_GET(j, uint32_t, "g_object", Offsets.GObject)
    OPTIONAL_GET(j, uint32_t, "g_world", Offsets.GWorld)
}

struct GInfo
{
    std::variant<GInfoPatterns, GInfoOffsets> Info;
};

static void from_json(const nlohmann::json &j, GInfo &Info)
{
    if (j.contains("Patterns"))
    {
        GInfoPatterns Patterns = {};
        j.at("Patterns").get_to(Patterns);
        Info.Info = Patterns;
    }
    else if (j.contains("Offsets"))
    {
        GInfoOffsets Offsets = {};
        j.at("Offsets").get_to(Offsets);
        Info.Info = Offsets;
    }
}

struct UObjectDef
{
    uint32_t Index = 0;
    uint32_t Class = 0;
    uint32_t Name = 0;
    uint32_t Outer = 0;
};

static void from_json(const nlohmann::json &j, UObjectDef &ObjectDef)
{
    j.at("index").get_to(ObjectDef.Index);
    j.at("class").get_to(ObjectDef.Class);
    j.at("Name").get_to(ObjectDef.Name);
    j.at("Outer").get_to(ObjectDef.Outer);
}

struct UFieldDef
{
    uint32_t Next = 0;
};

static void from_json(const nlohmann::json &j, UFieldDef &FieldDef)
{
    j.at("next").get_to(FieldDef.Next);
}

struct UStructDef
{
    uint32_t SuperStruct = 0;
    uint32_t Children = 0;
    uint32_t PropertiesSize = 0;
};

static void from_json(const nlohmann::json &j, UStructDef &StructDef)
{
    j.at("super_struct").get_to(StructDef.SuperStruct);
    j.at("children").get_to(StructDef.Children);
    j.at("properties_size").get_to(StructDef.PropertiesSize);
}

struct UFunctionDef
{
    uint32_t FunctionFlags = 0;
    uint32_t Func = 0;
};

static void from_json(const nlohmann::json &j, UFunctionDef &FunctionDef)
{
    j.at("function_flags").get_to(FunctionDef.FunctionFlags);
    j.at("func").get_to(FunctionDef.Func);
}

struct FField
{
    uint32_t Name = 0;
    uint32_t Next = 0;
};

static void from_json(const nlohmann::json &j, FField &Field)
{
    j.at("name").get_to(Field.Name);
    j.at("next").get_to(Field.Next);
}

struct Property
{
    uint32_t ArrayDim = 0;
    uint32_t Offset = 0;
    std::optional<FField> FProperty;
};

static void from_json(const nlohmann::json &j, Property &Prop)
{
    j.at("array_dim").get_to(Prop.ArrayDim);
    j.at("offset").get_to(Prop.Offset);

    OPTIONAL_GET(j, FField, "fproperty", Prop.FProperty)
}

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

static void from_json(const nlohmann::json &j, FunctionInfoPatterns &FunctionPatterns)
{
    OPTIONAL_GET(j, std::string, "game_state_init", FunctionPatterns.GameStateInit)
    OPTIONAL_GET(j, std::string, "begin_play", FunctionPatterns.BeginPlay)
    OPTIONAL_GET(j, std::string, "static_load_object", FunctionPatterns.StaticLoadObject)
    OPTIONAL_GET(j, std::string, "spawn_actor_ftrans", FunctionPatterns.SpawnActorFTrans)
    OPTIONAL_GET(j, std::string, "call_function_by_name_with_arguments",
                 FunctionPatterns.CallFunctionByNameWithArguments)
    OPTIONAL_GET(j, std::string, "process_event", FunctionPatterns.ProcessEvent)
    OPTIONAL_GET(j, std::string, "create_default_object", FunctionPatterns.CreateDefaultObject)
}

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

static void from_json(const nlohmann::json &j, FunctionInfoOffsets &FunctionOffsets)
{
    OPTIONAL_GET(j, uint32_t, "game_state_init", FunctionOffsets.GameStateInit)
    OPTIONAL_GET(j, uint32_t, "begin_play", FunctionOffsets.BeginPlay)
    OPTIONAL_GET(j, uint32_t, "static_load_object", FunctionOffsets.StaticLoadObject)
    OPTIONAL_GET(j, uint32_t, "spawn_actor_ftrans", FunctionOffsets.SpawnActorFTrans)
    OPTIONAL_GET(j, uint32_t, "call_function_by_name_with_arguments", FunctionOffsets.CallFunctionByNameWithArguments)
    OPTIONAL_GET(j, uint32_t, "process_event", FunctionOffsets.ProcessEvent)
    OPTIONAL_GET(j, uint32_t, "create_default_object", FunctionOffsets.CreateDefaultObject)
}

struct FunctionInfo
{
    std::variant<FunctionInfoPatterns, FunctionInfoOffsets> Info;
};

static void from_json(const nlohmann::json &j, FunctionInfo &Function)
{
    if (j.contains("Patterns"))
    {
        FunctionInfoPatterns Patterns = {};
        j.at("Patterns").get_to(Patterns);
        Function.Info = Patterns;
    }
    else if (j.contains("Offsets"))
    {
        FunctionInfoOffsets Offsets = {};
        j.at("Offsets").get_to(Offsets);
        Function.Info = Offsets;
    }
}

struct ProcessInternalFunction
{
    std::string ProcessInternal = "";
};

static void from_json(const nlohmann::json &j, ProcessInternalFunction &ProcessInternal)
{
    j.at("process_internal").get_to(ProcessInternal.ProcessInternal);
}

struct StaticConstructObject_InternalInfo
{
    bool IsUsingUpdatedStaticConstruct = false;
    std::string StaticConstructObject_InternalFunction = "";
};

static void from_json(const nlohmann::json &j, StaticConstructObject_InternalInfo &StaticConstructObject)
{
    j.at("is_using_updated_static_construct").get_to(StaticConstructObject.IsUsingUpdatedStaticConstruct);
    j.at("static_construct_object_internal_function")
        .get_to(StaticConstructObject.StaticConstructObject_InternalFunction);
}

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

static void from_json(const nlohmann::json &j, GameSettings &Settings)
{
    j.at("is_using_fchunked_fixed_uobject_array").get_to(Settings.IsUsingFChunkedFixedUObjectArray);
    j.at("uses_fname_pool").get_to(Settings.UsesFNamePool);
    j.at("is_using_deferred_spawn").get_to(Settings.IsUsingDeferedSpawn);
    j.at("is_using_4_22").get_to(Settings.IsUsing4_22);
    j.at("is_default_object_arrayed").get_to(Settings.IsDefaultObjectArrayed);
    j.at("delay_gui_spawn").get_to(Settings.DelayGUISpawn);

    OPTIONAL_GET(j, std::string, "begin_play_overwrite", Settings.BeginPlayOverwrite);
    OPTIONAL_GET(j, GInfo, "g_info_settings", Settings.GInfoSettings);
    OPTIONAL_GET(j, UObjectDef, "uobject_def_settings", Settings.UObjectDefSettings);
    OPTIONAL_GET(j, UFieldDef, "ufield_def_settings", Settings.UFieldDefSettings);
    OPTIONAL_GET(j, UStructDef, "ustruct_def_settings", Settings.UStructDefSettings);
    OPTIONAL_GET(j, UFunctionDef, "ufunction_def_settings", Settings.UFunctionDefSettings);
    OPTIONAL_GET(j, Property, "property_settings", Settings.PropertySettings);
    OPTIONAL_GET(j, FunctionInfo, "function_info_settings", Settings.FunctionInfoSettings);
    OPTIONAL_GET(j, ProcessInternalFunction, "process_internal_function_settings",
                 Settings.ProcessInternalFunctionSettings);
    OPTIONAL_GET(j, StaticConstructObject_InternalInfo, "static_construct_object_internal_info",
                 Settings.StaticConstructObject_InternalInfoSettings);
}

} // namespace GameSettings
