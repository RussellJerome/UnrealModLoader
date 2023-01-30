#include "GameInfo.h"
#include "GameSettings.h"
#include "Log/Log.h"
#include "Memory/Pattern.h"
#include "Utilities/Version.h"
#include <INI.h>
#include <Shared/Hooks.h>
#include <UE4/Ue4.hpp>
#include <filesystem>
#include <iostream>
#include <string>
#include <tuple>

GameProfile GameProfile::SelectedGameProfile;

void GameProfile::CreateGameProfile()
{
    GameSettings::GameSettings Settings = GameSettings::GameSettings::GetBakedSettings();
    // debug
    if (true)
    {
        ShowWindow(GetConsoleWindow(), SW_SHOW);
        FreeConsole();
        AllocConsole();
        LOG_INFO("Created by ~Russell.J Release V {}", MODLOADER_VERSION);
    }
    LOG_INFO("Loading baked profile");

    GameProfile::SelectedGameProfile.IsUsingFChunkedFixedUObjectArray = Settings.IsUsingFChunkedFixedUObjectArray;
    GameProfile::SelectedGameProfile.UsesFNamePool = Settings.UsesFNamePool;
    GameProfile::SelectedGameProfile.IsUsingDeferedSpawn = Settings.IsUsingDeferedSpawn;
    GameProfile::SelectedGameProfile.IsUsing4_22 = Settings.IsUsing4_22;
    GameProfile::SelectedGameProfile.bIsDefaultObjectArrayed = Settings.IsDefaultObjectArrayed;
    GameProfile::SelectedGameProfile.bDelayGUISpawn = Settings.DelayGUISpawn;

    if (Settings.BeginPlayOverwrite.has_value())
    {
        GameProfile::SelectedGameProfile.BeginPlayOverwrite = *Settings.BeginPlayOverwrite;
    }

    if (Settings.GInfoSettings.has_value())
    {
        GameSettings::GInfo GInfoSettings = *Settings.GInfoSettings;

        if (std::holds_alternative<GameSettings::GInfoPatterns>(GInfoSettings.Info))
        {
            GameSettings::GInfoPatterns GInfoPatterns = std::get<GameSettings::GInfoPatterns>(GInfoSettings.Info);

            auto ExtendedPatternHandler = [](auto &ExtendedPattern) {
                auto Found = (DWORD64)Pattern(ExtendedPattern.Pattern).Get(0).Get<uint8_t>();
                auto Offset = *reinterpret_cast<uint32_t *>(Found + ExtendedPattern.FirstOpCodes);
                return Found + ExtendedPattern.TotalByteInstruction + Offset;
            };

            GameProfile::SelectedGameProfile.GName = GInfoPatterns.GName.transform(ExtendedPatternHandler).value_or(0);
            GameProfile::SelectedGameProfile.GObject =
                GInfoPatterns.GObject.transform(ExtendedPatternHandler).value_or(0);
            GameProfile::SelectedGameProfile.GWorld =
                GInfoPatterns.GWorld.transform(ExtendedPatternHandler).value_or(0);

            LOG_INFO("GStuff Patterns Loaded!");
        }
        else
        {
            GameSettings::GInfoOffsets GInfoOffsets = std::get<GameSettings::GInfoOffsets>(GInfoSettings.Info);

            auto OffsetHandler = [](auto &Offset) { return (DWORD64)GetModuleHandleW(0) + Offset; };

            GameProfile::SelectedGameProfile.GName = GInfoOffsets.GName.transform(OffsetHandler).value_or(0);
            GameProfile::SelectedGameProfile.GObject = GInfoOffsets.GObject.transform(OffsetHandler).value_or(0);
            GameProfile::SelectedGameProfile.GWorld = GInfoOffsets.GWorld.transform(OffsetHandler).value_or(0);

            LOG_INFO("GStuff Offsets Loaded!");
        }
    }

    if (GameProfile::SelectedGameProfile.GName == 0)
    {
        if (GameProfile::SelectedGameProfile.UsesFNamePool)
        {
            auto FPoolPat = Pattern("74 09 48 8D 15 ? ? ? ? EB 16").Get(0).Get<uint8_t>();
            if (FPoolPat != nullptr)
            {
                auto FPoolPatoffset = *reinterpret_cast<uint32_t *>(FPoolPat + 5);
                GameProfile::SelectedGameProfile.GName = (DWORD64)(FPoolPat + 9 + FPoolPatoffset);
                LOG_INFO("FoundNamePool: 0x{:x}", GameProfile::SelectedGameProfile.GName);
            }
            else
            {
                LOG_ERROR("GName Could Not Be Found!");
            }
        }
        else
        {
            auto GNamePat = Pattern("E8 ? ? ? ? 48 8B C3 48 89 1D ? ? ? ? 48 8B 5C 24").Get(0).Get<uint8_t>();
            if (GNamePat != nullptr)
            {
                auto GNamesAddress = *reinterpret_cast<uint32_t *>(GNamePat + 11);
                GameProfile::SelectedGameProfile.GName = (DWORD64)(GNamePat + 15 + GNamesAddress);
                LOG_INFO("GName: 0x{:x}", GameProfile::SelectedGameProfile.GName);
            }
            else
            {
                LOG_ERROR("GName Could Not Be Found!");
            }
        }
    }

    if (GameProfile::SelectedGameProfile.GObject == 0)
    {
        auto GObjectPat = Pattern("8B 46 10 3B 46 3C 75 0F 48 8B D6 48 8D 0D ? ? ? ? E8").Get(0).Get<uint8_t>();
        if (GObjectPat != nullptr)
        {
            auto GObjectOffset = *reinterpret_cast<uint32_t *>(GObjectPat + 14);
            GameProfile::SelectedGameProfile.GObject = (DWORD64)(GObjectPat + 18 + GObjectOffset);
            LOG_INFO("GObject: 0x{:x}", GameProfile::SelectedGameProfile.GObject);
        }
        else
        {
            LOG_ERROR("GObject Could Not Be Found!");
        }
    }

    if (GameProfile::SelectedGameProfile.GWorld == 0)
    {
        auto GWorldPat = Pattern("0F 2E ? 74 ? 48 8B 1D ? ? ? ? 48 85 DB 74").Get(0).Get<uint8_t>();
        if (GWorldPat != nullptr)
        {
            auto GWorldAddress = *reinterpret_cast<uint32_t *>(GWorldPat + 8);
            GameProfile::SelectedGameProfile.GWorld = (DWORD64)(GWorldPat + 12 + GWorldAddress);
            LOG_INFO("GWorld: 0x{:x}", GameProfile::SelectedGameProfile.GWorld);
        }
        else
        {
            LOG_ERROR("GWorld Could Not Be Found!");
        }
    }

    if (Settings.UObjectDefSettings.has_value())
    {
        GameSettings::UObjectDef UObjectDefSettings = *Settings.UObjectDefSettings;

        GameProfile::SelectedGameProfile.IsUObjectMissing = false;
        GameProfile::SelectedGameProfile.defs.UObject.Index = UObjectDefSettings.Index;
        GameProfile::SelectedGameProfile.defs.UObject.Class = UObjectDefSettings.Class;
        GameProfile::SelectedGameProfile.defs.UObject.Name = UObjectDefSettings.Name;
        GameProfile::SelectedGameProfile.defs.UObject.Outer = UObjectDefSettings.Outer;
    }

    if (Settings.UFieldDefSettings.has_value())
    {
        GameSettings::UFieldDef UFieldDefSettings = *Settings.UFieldDefSettings;

        GameProfile::SelectedGameProfile.IsUFieldMissing = false;
        GameProfile::SelectedGameProfile.defs.UField.Next = UFieldDefSettings.Next;
    }

    if (Settings.UStructDefSettings.has_value())
    {
        GameSettings::UStructDef UStructDefSettings = *Settings.UStructDefSettings;

        GameProfile::SelectedGameProfile.IsUStructMissing = false;
        GameProfile::SelectedGameProfile.defs.UStruct.SuperStruct = UStructDefSettings.SuperStruct;
        GameProfile::SelectedGameProfile.defs.UStruct.Children = UStructDefSettings.Children;
        GameProfile::SelectedGameProfile.defs.UStruct.PropertiesSize = UStructDefSettings.PropertiesSize;
    }

    if (Settings.UFunctionDefSettings.has_value())
    {
        GameSettings::UFunctionDef UFunctionDefSettings = *Settings.UFunctionDefSettings;

        GameProfile::SelectedGameProfile.IsUFunctionMissing = false;
        GameProfile::SelectedGameProfile.defs.UFunction.FunctionFlags = UFunctionDefSettings.FunctionFlags;
        GameProfile::SelectedGameProfile.defs.UFunction.Func = UFunctionDefSettings.Func;
    }

    if (Settings.PropertySettings.has_value())
    {
        GameSettings::Property PropertySettings = *Settings.PropertySettings;

        GameProfile::SelectedGameProfile.bIsFProperty = PropertySettings.FProperty.has_value();
        GameProfile::SelectedGameProfile.defs.Property.ArrayDim = PropertySettings.ArrayDim;
        GameProfile::SelectedGameProfile.defs.Property.Offset = PropertySettings.Offset;
        if (PropertySettings.FProperty.has_value())
        {
            GameSettings::FField FFieldSettings = *PropertySettings.FProperty;
            GameProfile::SelectedGameProfile.defs.FField.Name = FFieldSettings.Name;
            GameProfile::SelectedGameProfile.defs.FField.Next = FFieldSettings.Next;
        }
    }
    else
    {
        GameProfile::SelectedGameProfile.IsPropertyMissing = true;
    }

    if (Settings.FunctionInfoSettings.has_value())
    {
        GameSettings::FunctionInfo FunctionInfoSettings = *Settings.FunctionInfoSettings;

        if (std::holds_alternative<GameSettings::FunctionInfoPatterns>(FunctionInfoSettings.Info))
        {
            GameSettings::FunctionInfoPatterns FunctionInfoPatterns =
                std::get<GameSettings::FunctionInfoPatterns>(FunctionInfoSettings.Info);

            auto PatternHandler = [](auto &PatternString) {
                return (DWORD64)Pattern(PatternString).Get(0).Get<uint8_t>();
            };

            GameProfile::SelectedGameProfile.GameStateInit =
                FunctionInfoPatterns.GameStateInit.transform(PatternHandler).value_or(0);

            GameProfile::SelectedGameProfile.BeginPlay =
                FunctionInfoPatterns.BeginPlay.transform(PatternHandler).value_or(0);

            GameProfile::SelectedGameProfile.StaticLoadObject =
                FunctionInfoPatterns.StaticLoadObject.transform(PatternHandler).value_or(0);

            GameProfile::SelectedGameProfile.SpawnActorFTrans =
                FunctionInfoPatterns.SpawnActorFTrans.transform(PatternHandler).value_or(0);

            GameProfile::SelectedGameProfile.CallFunctionByNameWithArguments =
                FunctionInfoPatterns.CallFunctionByNameWithArguments.transform(PatternHandler).value_or(0);

            GameProfile::SelectedGameProfile.ProcessEvent =
                FunctionInfoPatterns.ProcessEvent.transform(PatternHandler).value_or(0);

            GameProfile::SelectedGameProfile.CreateDefaultObject =
                FunctionInfoPatterns.CreateDefaultObject.transform(PatternHandler).value_or(0);

            LOG_INFO("Function Patterns Set!");
        }
        else
        {
            GameSettings::FunctionInfoOffsets FunctionInfoOffsets =
                std::get<GameSettings::FunctionInfoOffsets>(FunctionInfoSettings.Info);

            auto OffsetHandler = [](auto &Offset) { return (DWORD64)GetModuleHandleW(0) + Offset; };

            GameProfile::SelectedGameProfile.GameStateInit =
                FunctionInfoOffsets.GameStateInit.transform(OffsetHandler).value_or(0);
            GameProfile::SelectedGameProfile.BeginPlay =
                FunctionInfoOffsets.BeginPlay.transform(OffsetHandler).value_or(0);
            GameProfile::SelectedGameProfile.StaticLoadObject =
                FunctionInfoOffsets.StaticLoadObject.transform(OffsetHandler).value_or(0);
            GameProfile::SelectedGameProfile.SpawnActorFTrans =
                FunctionInfoOffsets.SpawnActorFTrans.transform(OffsetHandler).value_or(0);
            GameProfile::SelectedGameProfile.CallFunctionByNameWithArguments =
                FunctionInfoOffsets.CallFunctionByNameWithArguments.transform(OffsetHandler).value_or(0);
            GameProfile::SelectedGameProfile.ProcessEvent =
                FunctionInfoOffsets.ProcessEvent.transform(OffsetHandler).value_or(0);
            GameProfile::SelectedGameProfile.CreateDefaultObject =
                FunctionInfoOffsets.CreateDefaultObject.transform(OffsetHandler).value_or(0);

            LOG_INFO("Function Offsets Set!");
        }
    }

    if (!GameProfile::SelectedGameProfile.GameStateInit)
    {
        GameProfile::SelectedGameProfile.GameStateInit =
            (DWORD64)Pattern("40 53 48 83 EC 20 48 8B 41 10 48 8B D9 48 8B 91").Get(0).Get<uint8_t>();
        LOG_INFO("GameStateInit: 0x{:x}", (void *)GameProfile::SelectedGameProfile.GameStateInit);
    }

    if (!GameProfile::SelectedGameProfile.GameStateInit)
    {
        LOG_ERROR("GameStateInit NOT FOUND!");
    }

    if (!GameProfile::SelectedGameProfile.BeginPlay)
    {
        auto BeginPlay = Pattern("48 8B D9 E8 ? ? ? ? F6 83 ? ? ? ? ? 74 12 48 8B 03").Get(0).Get<uint8_t>(3);
        if (BeginPlay != nullptr)
        {
            GameProfile::SelectedGameProfile.BeginPlay = (DWORD64)MEM::GetAddressPTR(BeginPlay, 0x1, 0x5);
            LOG_INFO("AActor::BeginPlay: 0x{:x}", (void *)GameProfile::SelectedGameProfile.BeginPlay);
        }
        else
        {
            LOG_ERROR("AActor::BeginPlay NOT FOUND!");
        }
    }

    std::tuple<std::string, uint8_t> StaticLoadObjectPatterns[] = {
        {"89 64 24 ? 48 8B C8 E8 ? ? ? ? 41 BE ? ? ? ? EB 05 E8", 0x7},
        {"C7 44 24 ? ? ? ? ? E8 ? ? ? ? 48 8B 8D ? ? ? ? 48 85 C9 74 05 E8 ? ? ? ? 45 33 C9 ? 89 74 24", 0x8},
        {"89 6C 24 20 48 8B C8 E8 ? ? ? ? 48 8B 4C 24 ? 48 8B F0 48 85 C9 74 05", 0x7},
        {"48 8B C8 89 5C 24 20 E8 ? ? ? ? 48", 0x7}};

    if (!GameProfile::SelectedGameProfile.StaticLoadObject)
    {
        for (const auto [PatternString, Offset] : StaticLoadObjectPatterns)
        {
            auto Found = Pattern(PatternString).Get(0).Get<uint8_t>(Offset);
            if (Found != nullptr)
            {
                GameProfile::SelectedGameProfile.StaticLoadObject = (DWORD64)MEM::GetAddressPTR(Found, 0x1, 0x5);
                break;
            }
        }
    }

    if (GameProfile::SelectedGameProfile.StaticLoadObject == 0)
    {
        LOG_ERROR("StaticLoadObject NOT FOUND!");
    }

    LOG_INFO("StaticLoadObject: 0x{:x}", (void *)GameProfile::SelectedGameProfile.StaticLoadObject);

    std::tuple<std::string, uint8_t> SpawnActorFTransPatterns[] = {
        {"4C 8B C6 48 8B C8 48 8B D3 E8 ? ? ? ? 48 8B 5C 24 ? 48 8B 74 24", 0x9},
        {"4C 8B CE 4C 8D 44 24 ? 48 8B D7 48 8B CB E8 ? ? ? ? 48 8B 4C 24 ? 48 33 CC", 0xE}};

    if (!GameProfile::SelectedGameProfile.SpawnActorFTrans)
    {
        for (const auto [PatternString, Offset] : SpawnActorFTransPatterns)
        {
            auto Found = Pattern(PatternString).Get(0).Get<uint8_t>(Offset);
            if (Found != nullptr)
            {
                GameProfile::SelectedGameProfile.SpawnActorFTrans = (DWORD64)MEM::GetAddressPTR(Found, 0x1, 0x5);
                break;
            }
        }
    }

    if (GameProfile::SelectedGameProfile.SpawnActorFTrans == 0)
    {
        LOG_ERROR("SpawnActorFTrans NOT FOUND!");
    }

    LOG_INFO("UWorld::SpawnActor: 0x{:x}", (void *)GameProfile::SelectedGameProfile.SpawnActorFTrans);

    std::tuple<std::string, uint8_t> CallFunctionByNameWithArgumentsPatterns[] = {
        {"8B ? E8 ? ? ? ? ? 0A ? FF ? EB 9E ? 8B", 0x2}, {"49 8B D4 E8 ? ? ? ? 44 0A F8 FF C3 EB 9A", 0x3}};

    if (!GameProfile::SelectedGameProfile.CallFunctionByNameWithArguments)
    {
        for (int i = 0; i < 3; i++)
        {
            const auto [PatternString, Offset] = CallFunctionByNameWithArgumentsPatterns[i];

            auto Found = Pattern(PatternString).Get(0).Get<uint8_t>(Offset);
            if (Found != nullptr)
            {
                GameProfile::SelectedGameProfile.CallFunctionByNameWithArguments =
                    (DWORD64)MEM::GetAddressPTR(Found, 0x1, 0x5);
                break;
            }
        }
    }

    if (GameProfile::SelectedGameProfile.CallFunctionByNameWithArguments == 0)
    {
        LOG_ERROR("CallFunctionByNameWithArguments NOT FOUND!");
    }

    LOG_INFO("CallFunctionByNameWithArguments: 0x{:x}",
             (void *)GameProfile::SelectedGameProfile.CallFunctionByNameWithArguments);

    if (!GameProfile::SelectedGameProfile.ProcessEvent)
    {
        auto ProcessEvent = Pattern("75 0E ? ? ? 48 ? ? 48 ? ? E8 ? ? ? ? 48 8B ? 24 ? 48 8B ? 24 38 48 8B ? 24 40")
                                .Get(0)
                                .Get<uint8_t>(0xB);
        if (ProcessEvent != nullptr)
        {
            GameProfile::SelectedGameProfile.ProcessEvent = (DWORD64)MEM::GetAddressPTR(ProcessEvent, 0x1, 0x5);
            LOG_INFO("UObject::ProcessEvent: 0x{:x}", (void *)GameProfile::SelectedGameProfile.ProcessEvent);
        }
        else
        {
            LOG_ERROR("ProcessEvent NOT FOUND!");
        }
    }

    std::string CreateDefaultObjectPatterns[] = {
        "4C 8B DC 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 48 83 B9 ? ? ? ? ? 48 8B F9",

        "4C 8B DC 55 53 49 8D AB ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 48 83 B9 ? ? "
        "? ? ? 48 8B D9 0F 85",

        "4C 8B DC 53 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 48 83 B9",

        "4C 8B DC ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? 48 ? ? ? ? ? "
        "? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? "
        "? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? 8B ? ? ? ? ? ? ? ? ? ? ? 8B ? ? ? "
        "? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? "
        "? ? ? ? ? ? ? 48"};

    if (!GameProfile::SelectedGameProfile.CreateDefaultObject)
    {
        for (const auto PatternString : CreateDefaultObjectPatterns)
        {
            auto Found = Pattern(PatternString).Get(0).Get<uint8_t>();
            if (Found != nullptr)
            {
                GameProfile::SelectedGameProfile.CreateDefaultObject = (DWORD64)Found;
            }
        }
    }

    if (GameProfile::SelectedGameProfile.CreateDefaultObject == 0)
    {
        GameProfile::SelectedGameProfile.bIsDefaultObjectArrayed = true;
        LOG_WARN("CreateDefualtObject NOT FOUND!, Will Use Object Array Instead!");
    }

    LOG_INFO("UClass::CreateDefualtObject: 0x{:x}", (void *)GameProfile::SelectedGameProfile.CreateDefaultObject);

    if (Settings.ProcessInternalFunctionSettings.has_value())
    {
        GameSettings::ProcessInternalFunction ProcessInternalFunctionSettings =
            *Settings.ProcessInternalFunctionSettings;

        GameProfile::SelectedGameProfile.ProcessInternals =
            (DWORD64)Pattern(ProcessInternalFunctionSettings.ProcessInternal).Get(0).Get<uint8_t>();
        LOG_INFO("ProcessInternalFunction: 0x{:x}", (void *)GameProfile::SelectedGameProfile.ProcessInternals);
    }
    else
    {
        if (GameProfile::SelectedGameProfile.UsesFNamePool || GameProfile::SelectedGameProfile.IsUsing4_22)
        {
            DWORD64 ProcessAddy = (DWORD64)Pattern("41 F6 C7 02 74 ? 4C 8B C7 48 8B ? ? 8B ? E8").Get(0).Get<uint8_t>();
            if (ProcessAddy)
            {
                auto ProcessAddyOffset = *reinterpret_cast<uint32_t *>(ProcessAddy + 16);
                GameProfile::SelectedGameProfile.ProcessInternals = (ProcessAddy + 20 + ProcessAddyOffset);
                LOG_INFO("ProcessInternalFunction: 0x{:x}", (void *)GameProfile::SelectedGameProfile.ProcessInternals);
            }
            else
            {
                LOG_ERROR("ProcessInternalFunction not found! BPFUNCTION will not work!");
            }
        }
    }

    if (Settings.StaticConstructObject_InternalInfoSettings)
    {
        GameSettings::StaticConstructObject_InternalInfo StaticConstructObject_InternalInfoSettings =
            *Settings.StaticConstructObject_InternalInfoSettings;

        GameProfile::SelectedGameProfile.IsUsingUpdatedStaticConstruct =
            StaticConstructObject_InternalInfoSettings.IsUsingUpdatedStaticConstruct;
        GameProfile::SelectedGameProfile.StaticConstructObject_Internal =
            (DWORD64)Pattern(StaticConstructObject_InternalInfoSettings.StaticConstructObject_InternalFunction)
                .Get(0)
                .Get<uint8_t>();
    }
    else
    {
        std::tuple<std::string, uint8_t> StaticConstructObject_InternalPatterns[] = {
            {"48 8B 84 24 ? ? 00 00 48 89 44 24 ? C7 44 24 ? 00 00 00 00 E8", 0x15},
            {"48 8B C8 89 7C 24 ? E8", 0x7},
            {"E8 ? ? ? ? 45 8B 47 70", 0x0},
            {"89 6C 24 38 48 89 74 24 ? E8", 0x9}};

        for (const auto [PatternString, Offset] : StaticConstructObject_InternalPatterns)
        {
            auto Found = Pattern(PatternString).Get(0).Get<uint8_t>(Offset);
            if (Found != nullptr)
            {

                GameProfile::SelectedGameProfile.StaticConstructObject_Internal =
                    (DWORD64)MEM::GetAddressPTR(Found, 0x1, 0x5);
                break;
            }
        }

        if (GameProfile::SelectedGameProfile.StaticConstructObject_Internal == 0)
        {
            LOG_WARN("StaticConstructObject_Internal Not Found! This will prevent Mods using the "
                     "ModObjectInstance from working properly.");
        }

        LOG_INFO("StaticConstructObject_Internal 0x{:x}",
                 (void *)GameProfile::SelectedGameProfile.StaticConstructObject_Internal);
    }
    LOG_INFO("Setting up hooks!");
    Hooks::SetupHooks();
}