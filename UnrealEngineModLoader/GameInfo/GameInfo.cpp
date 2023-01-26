#include "GameInfo.h"
#include "GameSettings.h"
#include "Log/Log.h"
#include "Utilities/Pattern.h"
#include "Utilities/Version.h"
#include <INI.h>
#include <Shared/Hooks.h>
#include <UE4/Ue4.hpp>
#include <filesystem>
#include <iostream>
#include <string>

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

            auto GName = (DWORD64)Pattern::Find(GInfoPatterns.GName.c_str());
            auto GNamesOffset = *reinterpret_cast<uint32_t *>(GName + GInfoPatterns.GNameFirstOpCodes);
            GameProfile::SelectedGameProfile.GName = GName + GInfoPatterns.GNameTotalByteInstruction + GNamesOffset;

            auto GObject = (DWORD64)Pattern::Find(GInfoPatterns.GObject.c_str());
            auto GObjectOffset = *reinterpret_cast<uint32_t *>(GObject + GInfoPatterns.GObjectFirstOpCodes);
            GameProfile::SelectedGameProfile.GObject =
                GObject + GInfoPatterns.GobjectTotalByteInstruction + GObjectOffset;

            auto GWorld = (DWORD64)Pattern::Find(GInfoPatterns.GWorld.c_str());
            auto GWorldOffset = *reinterpret_cast<uint32_t *>(GWorld + GInfoPatterns.GWorldFirstOpCodes);
            GameProfile::SelectedGameProfile.GWorld = GWorld + GInfoPatterns.GWorldTotalByteInstruction + GWorldOffset;

            LOG_INFO("GStuff Patterns Loaded!");
        }
        else
        {
            GameSettings::GInfoOffsets GInfoOffsets = std::get<GameSettings::GInfoOffsets>(GInfoSettings.Info);

            GameProfile::SelectedGameProfile.GName = (DWORD64)GetModuleHandleW(0) + GInfoOffsets.GName;
            GameProfile::SelectedGameProfile.GObject = (DWORD64)GetModuleHandleW(0) + GInfoOffsets.GObject;
            GameProfile::SelectedGameProfile.GWorld = (DWORD64)GetModuleHandleW(0) + GInfoOffsets.GWorld;

            LOG_INFO("GStuff Offsets Loaded!");
        }
    }
    else
    {
        if (GameProfile::SelectedGameProfile.UsesFNamePool)
        {
            auto FPoolPat = Pattern::Find("74 09 48 8D 15 ? ? ? ? EB 16");
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
            auto GNamePat = Pattern::Find("E8 ? ? ? ? 48 8B C3 48 89 1D ? ? ? ? 48 8B 5C 24");
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

        auto GObjectPat = Pattern::Find("8B 46 10 3B 46 3C 75 0F 48 8B D6 48 8D 0D ? ? ? ? E8");
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

        auto GWorldPat = Pattern::Find("0F 2E ? 74 ? 48 8B 1D ? ? ? ? 48 85 DB 74");
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

            GameProfile::SelectedGameProfile.GameStateInit =
                (DWORD64)Pattern::Find(FunctionInfoPatterns.GameStateInit.c_str());
            GameProfile::SelectedGameProfile.BeginPlay = (DWORD64)Pattern::Find(FunctionInfoPatterns.BeginPlay.c_str());
            GameProfile::SelectedGameProfile.StaticLoadObject =
                (DWORD64)Pattern::Find(FunctionInfoPatterns.StaticLoadObject.c_str());
            GameProfile::SelectedGameProfile.SpawnActorFTrans =
                (DWORD64)Pattern::Find(FunctionInfoPatterns.SpawnActorFTrans.c_str());
            GameProfile::SelectedGameProfile.CallFunctionByNameWithArguments =
                (DWORD64)Pattern::Find(FunctionInfoPatterns.CallFunctionByNameWithArguments.c_str());
            GameProfile::SelectedGameProfile.ProcessEvent =
                (DWORD64)Pattern::Find(FunctionInfoPatterns.ProcessEvent.c_str());
            GameProfile::SelectedGameProfile.CreateDefaultObject =
                (DWORD64)Pattern::Find(FunctionInfoPatterns.CreateDefaultObject.c_str());

            LOG_INFO("Function Patterns Set!");
        }
        else
        {
            GameSettings::FunctionInfoOffsets FunctionInfoOffsets =
                std::get<GameSettings::FunctionInfoOffsets>(FunctionInfoSettings.Info);

            GameProfile::SelectedGameProfile.GameStateInit =
                (DWORD64)GetModuleHandleW(0) + FunctionInfoOffsets.GameStateInit;
            GameProfile::SelectedGameProfile.BeginPlay = (DWORD64)GetModuleHandleW(0) + FunctionInfoOffsets.BeginPlay;
            GameProfile::SelectedGameProfile.StaticLoadObject =
                (DWORD64)GetModuleHandleW(0) + FunctionInfoOffsets.StaticLoadObject;
            GameProfile::SelectedGameProfile.SpawnActorFTrans =
                (DWORD64)GetModuleHandleW(0) + FunctionInfoOffsets.SpawnActorFTrans;
            GameProfile::SelectedGameProfile.CallFunctionByNameWithArguments =
                (DWORD64)GetModuleHandleW(0) + FunctionInfoOffsets.CallFunctionByNameWithArguments;
            GameProfile::SelectedGameProfile.ProcessEvent =
                (DWORD64)GetModuleHandleW(0) + FunctionInfoOffsets.ProcessEvent;
            GameProfile::SelectedGameProfile.CreateDefaultObject =
                (DWORD64)GetModuleHandleW(0) + FunctionInfoOffsets.CreateDefaultObject;

            LOG_INFO("Function Offsets Set!");
        }
    }
    else
    {
        GameProfile::SelectedGameProfile.GameStateInit =
            (DWORD64)Pattern::Find("40 53 48 83 EC 20 48 8B 41 10 48 8B D9 48 8B 91");
        LOG_INFO("GameStateInit: 0x{:x}", (void *)GameProfile::SelectedGameProfile.GameStateInit);
        if (!GameProfile::SelectedGameProfile.GameStateInit)
        {
            LOG_ERROR("GameStateInit NOT FOUND!");
        }

        auto BeginPlay = Pattern::Find("48 8B D9 E8 ?? ?? ?? ?? F6 83 ?? ?? ?? ?? ?? 74 12 48 8B 03");
        BeginPlay += 0x3;
        if (BeginPlay != nullptr)
        {
            GameProfile::SelectedGameProfile.BeginPlay = (DWORD64)MEM::GetAddressPTR(BeginPlay, 0x1, 0x5);
            LOG_INFO("AActor::BeginPlay: 0x{:x}", (void *)GameProfile::SelectedGameProfile.BeginPlay);
        }
        else
        {
            LOG_ERROR("AActor::BeginPlay NOT FOUND!");
        }

        auto StaticLoadObject = Pattern::Find("89 64 24 ? 48 8B C8 E8 ? ? ? ? 41 BE ? ? ? ? EB 05 E8"); // Sig 1
        if (StaticLoadObject != nullptr)
        {
            StaticLoadObject += 0x7;
        }
        else
        {
            StaticLoadObject = Pattern::Find(
                "C7 44 24 ? ? ? ? ? E8 ? ? ? ? 48 8B 8D ? ? ? ? 48 85 C9 74 05 E8 ? ? ? ? 45 33 C9 ? 89 74 24");
            if (StaticLoadObject != nullptr)
            {
                StaticLoadObject += 0x8;
            }
            else
            {
                StaticLoadObject =
                    Pattern::Find("89 6C 24 20 48 8B C8 E8 ? ? ? ? 48 8B 4C 24 ? 48 8B F0 48 85 C9 74 05");
                if (StaticLoadObject != nullptr)
                {
                    StaticLoadObject += 0x7;
                }
                else
                {
                    if (StaticLoadObject = Pattern::Find("48 8B C8 89 5C 24 20 E8 ? ? ? ? 48"))
                    {
                        StaticLoadObject += 0x7;
                    }
                    else
                    {
                        LOG_ERROR("StaticLoadObject NOT FOUND!");
                    }
                }
            }
        }
        GameProfile::SelectedGameProfile.StaticLoadObject = (DWORD64)MEM::GetAddressPTR(StaticLoadObject, 0x1, 0x5);

        LOG_INFO("StaticLoadObject: 0x{:x}", (void *)GameProfile::SelectedGameProfile.StaticLoadObject);

        auto SpawnActorFTrans = Pattern::Find("4C 8B C6 48 8B C8 48 8B D3 E8 ? ? ? ? 48 8B 5C 24 ? 48 8B 74 24");
        if (SpawnActorFTrans != nullptr)
        {
            SpawnActorFTrans += 0x9;
        }
        else
        {
            SpawnActorFTrans =
                Pattern::Find("4C 8B CE 4C 8D 44 24 ? 48 8B D7 48 8B CB E8 ? ? ? ? 48 8B 4C 24 ? 48 33 CC");
            if (SpawnActorFTrans != nullptr)
            {
                SpawnActorFTrans += 0xE;
            }
            else
            {
                LOG_ERROR("SpawnActorFTrans NOT FOUND!");
            }
        }

        GameProfile::SelectedGameProfile.SpawnActorFTrans = (DWORD64)MEM::GetAddressPTR(SpawnActorFTrans, 0x1, 0x5);
        LOG_INFO("UWorld::SpawnActor: 0x{:x}", (void *)GameProfile::SelectedGameProfile.SpawnActorFTrans);

        auto CallFunctionByNameWithArguments = Pattern::Find("8B ? E8 ? ? ? ? ? 0A ? FF ? EB 9E ? 8B");
        if (CallFunctionByNameWithArguments != nullptr)
        {
            CallFunctionByNameWithArguments += 0x2;
            GameProfile::SelectedGameProfile.CallFunctionByNameWithArguments =
                (DWORD64)MEM::GetAddressPTR(CallFunctionByNameWithArguments, 0x1, 0x5);
        }
        else
        {
            CallFunctionByNameWithArguments = Pattern::Find("49 8B D4 E8 ? ? ? ? 44 0A F8 FF C3 EB 9A");
            if (CallFunctionByNameWithArguments != nullptr)
            {
                CallFunctionByNameWithArguments += 0x3;
                GameProfile::SelectedGameProfile.CallFunctionByNameWithArguments =
                    (DWORD64)MEM::GetAddressPTR(CallFunctionByNameWithArguments, 0x1, 0x5);
            }
            else
            {
                LOG_ERROR("CallFunctionByNameWithArguments NOT FOUND!");
            }
        }
        LOG_INFO("CallFunctionByNameWithArguments: 0x{:x}",
                 (void *)GameProfile::SelectedGameProfile.CallFunctionByNameWithArguments);

        auto ProcessEvent =
            Pattern::Find("75 0E ? ? ? 48 ? ? 48 ? ? E8 ? ? ? ? 48 8B ? 24 ? 48 8B ? 24 38 48 8B ? 24 40");
        ProcessEvent += 0xB;
        if (ProcessEvent != nullptr)
        {
            GameProfile::SelectedGameProfile.ProcessEvent = (DWORD64)MEM::GetAddressPTR(ProcessEvent, 0x1, 0x5);
            LOG_INFO("UObject::ProcessEvent: 0x{:x}", (void *)GameProfile::SelectedGameProfile.ProcessEvent);
        }
        else
        {
            LOG_ERROR("ProcessEvent NOT FOUND!");
        }

        GameProfile::SelectedGameProfile.CreateDefaultObject =
            (DWORD64)Pattern::Find("4C 8B DC 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 48 "
                                   "83 B9 ? ? ? ? ? 48 8B F9 ");
        if (!GameProfile::SelectedGameProfile.CreateDefaultObject)
        {
            // FallBack 1
            GameProfile::SelectedGameProfile.CreateDefaultObject =
                (DWORD64)Pattern::Find("4C 8B DC 55 53 49 8D AB ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 "
                                       "48 89 85 ? ? ? ? 48 83 B9 ? ? ? ? ? 48 8B D9 0F 85");
            if (!GameProfile::SelectedGameProfile.CreateDefaultObject)
            {
                // FallBack 2
                GameProfile::SelectedGameProfile.CreateDefaultObject = (DWORD64)Pattern::Find(
                    "4C 8B DC 53 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 48 83 B9");
                if (!GameProfile::SelectedGameProfile.CreateDefaultObject)
                {
                    // Final FallBack
                    GameProfile::SelectedGameProfile.CreateDefaultObject = (DWORD64)Pattern::Find(
                        "4C 8B DC ?? ?? ?? ?? ?? ? ? ? ? ?? ?? ?? ? ? ? ? ?? ?? ?? ? ? ? ? ?? ?? ?? 48 ?? ?? ? ? ? "
                        "? ?? ?? ?? ? ? ? ? ? ?? ?? ?? ?? ?? ? ? ? ? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? "
                        "?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ? ? ? ? ?? 8B ?? ? ? ? ? ?? ?? ?? ?? ?? ?? 8B ?? ?? ?? "
                        "?? ?? ?? ? ? ? ? ?? ?? ?? ? ? ? ? ?? ?? ?? ?? ?? ?? ? ? ? ? ?? ?? ?? ?? ?? ? ? ? ? ?? ?? "
                        "? ? ? ? ?? ?? ?? 48");
                    if (!GameProfile::SelectedGameProfile.CreateDefaultObject)
                    {
                        GameProfile::SelectedGameProfile.bIsDefaultObjectArrayed = true;
                        LOG_WARN("CreateDefualtObject NOT FOUND!, Will Use Object Array Instead!");
                    }
                }
            }
        }
        LOG_INFO("UClass::CreateDefualtObject: 0x{:x}", (void *)GameProfile::SelectedGameProfile.CreateDefaultObject);
    }

    if (Settings.ProcessInternalFunctionSettings.has_value())
    {
        GameSettings::ProcessInternalFunction ProcessInternalFunctionSettings =
            *Settings.ProcessInternalFunctionSettings;

        GameProfile::SelectedGameProfile.ProcessInternals =
            (DWORD64)Pattern::Find(ProcessInternalFunctionSettings.ProcessInternal.c_str());
        LOG_INFO("ProcessInternalFunction: 0x{:x}", (void *)GameProfile::SelectedGameProfile.ProcessInternals);
    }
    else
    {
        if (GameProfile::SelectedGameProfile.UsesFNamePool || GameProfile::SelectedGameProfile.IsUsing4_22)
        {
            DWORD64 ProcessAddy = (DWORD64)Pattern::Find("41 F6 C7 02 74 ? 4C 8B C7 48 8B ? ? 8B ? E8");
            if (ProcessAddy)
            {
                auto ProcessAddyOffset = *reinterpret_cast<uint32_t *>(ProcessAddy + 16);
                GameProfile::SelectedGameProfile.ProcessInternals = (ProcessAddy + 20 + ProcessAddyOffset);
                LOG_INFO("ProcessInternalFunction: 0x{:x}", (void *)GameProfile::SelectedGameProfile.ProcessInternals);
            }
        }
    }

    if (Settings.StaticConstructObject_InternalInfoSettings)
    {
        GameSettings::StaticConstructObject_InternalInfo StaticConstructObject_InternalInfoSettings =
            *Settings.StaticConstructObject_InternalInfoSettings;

        GameProfile::SelectedGameProfile.IsUsingUpdatedStaticConstruct =
            StaticConstructObject_InternalInfoSettings.IsUsingUpdatedStaticConstruct;
        GameProfile::SelectedGameProfile.StaticConstructObject_Internal = (DWORD64)Pattern::Find(
            StaticConstructObject_InternalInfoSettings.StaticConstructObject_InternalFunction.c_str());
    }
    else
    {
        auto StaticConstructObject_Internal =
            Pattern::Find("48 8B 84 24 ?? ?? 00 00 48 89 44 24 ?? C7 44 24 ?? 00 00 00 00 E8"); // Sig 1
        if (StaticConstructObject_Internal != nullptr)
        {
            StaticConstructObject_Internal += 0x15;
        }
        else
        {
            StaticConstructObject_Internal = Pattern::Find("48 8B C8 89 7C 24 ?? E8");
            if (StaticConstructObject_Internal != nullptr)
            {
                StaticConstructObject_Internal += 0x7;
            }
            else
            {
                GameProfile::SelectedGameProfile.IsUsingUpdatedStaticConstruct = true;
                StaticConstructObject_Internal = Pattern::Find("E8 ? ? ? ? 45 8B 47 70");
                if (!StaticConstructObject_Internal)
                {
                    StaticConstructObject_Internal = Pattern::Find("89 6C 24 38 48 89 74 24 ? E8");
                    if (StaticConstructObject_Internal != nullptr)
                    {
                        StaticConstructObject_Internal += 0x9;
                    }
                    else
                    {
                        LOG_WARN("StaticConstructObject_Internal Not Found! This will prevent Mods using the "
                                 "ModObjectInstance from working properly.");
                    }
                }
            }
        }
        GameProfile::SelectedGameProfile.StaticConstructObject_Internal =
            (DWORD64)MEM::GetAddressPTR(StaticConstructObject_Internal, 0x1, 0x5);
        LOG_INFO("StaticConstructObject_Internal 0x{:x}",
                 (void *)GameProfile::SelectedGameProfile.StaticConstructObject_Internal);
    }
    LOG_INFO("Setting up hooks!");
    Hooks::SetupHooks();
}