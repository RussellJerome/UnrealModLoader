#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "UnrealModLoader.h"
#include <filesystem>
#include "Utilities/Utility.h"
#include "Memory/VariableGrabber.h"
#include "Memory/FunctionGrabber.h"
#include "ModLoader/ModLoader.h"
#include "INI/INI.h"

namespace UML
{
    class GameInfo* gameInfo;

    void StartUML()
    {
        //Get UML location.
        auto Module = GetModuleHandleA("UnrealModLoader.dll");
        LoaderPath = UML::Utility::GetModuleFilePath(Module);
        LoaderPath = LoaderPath.substr(0, LoaderPath.find_last_of("/\\"));

        //Get Game name and setup profile location.
        char game_c[MAX_PATH];
        GetModuleFileNameA(NULL, game_c, MAX_PATH);
        std::string gamename = std::string(game_c);
        gamename = gamename.substr(0, gamename.find_last_of("."));
        gamename = gamename.substr(gamename.find_last_of("/\\"));
        gamename = gamename.substr(1);
        auto Game = LoaderPath + "\\Profiles\\";
        Game = Game + gamename;

        auto LoaderInfoInI = LoaderPath + "\\ModLoaderInfo.ini";
        std::string Profile = Game + ".profile";

        GetGameInfo()->ProfileName = gamename;

        //Load and read Modloaderinfo.ini.
        INI::PARSE_FLAGS = INI::PARSE_COMMENTS_ALL | INI::PARSE_COMMENTS_SLASH | INI::PARSE_COMMENTS_HASH;
        INI LoaderInfo(LoaderInfoInI, true);

        //Check if console is enabled.
        LoaderInfo.select("DEBUG");
        if (LoaderInfo.getAs<int>("DEBUG", "UseConsole", 0) == 1)
        {
            ShowWindow(GetConsoleWindow(), SW_SHOW);
            FreeConsole();
            AllocConsole();
            auto file = freopen("CON", "w", LOG_STREAM);
            LOG_INFO("Created by ~Russell.J Release V %s", LoaderVersion);
        }

        //Load and read game profile.
        if (std::filesystem::exists(Profile))
        {
            LOG_INFO("Profile Detected: %s", gamename.c_str());
            INI GameInfo(Profile, true);

            //Loads in the "GameInfo" section of the game profile.
            GameInfo.select("GameInfo");
            GetGameInfo()->IsUsingFChunkedFixedUObjectArray = GameInfo.getAs<int>("GameInfo", "IsUsingFChunkedFixedUObjectArray", 0);
            GetGameInfo()->UsesFNamePool = GameInfo.getAs<int>("GameInfo", "UsesFNamePool", 0);
            GetGameInfo()->IsUsingDeferedSpawn = GameInfo.getAs<int>("GameInfo", "IsUsingDeferedSpawn", 0);
            GetGameInfo()->IsUsing4_22 = GameInfo.getAs<int>("GameInfo", "IsUsing4_22", 0);
            
            /*
            NOTE
            ====
            UML calls PostBeginPlay when the games player controller is spawned.
            For some games, (very few) PlayerController is to early in the call chain to effectively execute post beginplay.
            So this should almost never get filled out in a games profile. (Piss Off Fallen Order).
            */
            if (GameInfo.get("GameInfo", "BeginPlayOverwrite", "") != "")
            {
                GetGameInfo()->BeginPlayOverwrite = GameInfo.get("GameInfo", "BeginPlayOverwrite", "");
            }

            //If GInfo is defined, read it into the GameInfo.
            if (GameInfo.select("GInfo"))
            {
                if (GameInfo.getAs<int>("GInfo", "IsGInfoPatterns", 0) == 1)
                {
                    auto GNameGrabber = Memory::VariableGrabber(GameInfo.get("GInfo", "GName", "").c_str(), GameInfo.getAs<int>("GInfo", "GNameFirstOpCodes", 0), GameInfo.getAs<int>("GInfo", "GNameTotalByteInstruction", 0));
                    auto GObjectGrabber = Memory::VariableGrabber(GameInfo.get("GInfo", "GObject", "").c_str(), GameInfo.getAs<int>("GInfo", "GObjectFirstOpCodes", 0), GameInfo.getAs<int>("GInfo", "GObjectTotalByteInstruction", 0));
                    auto GWorldGrabber = Memory::VariableGrabber(GameInfo.get("GInfo", "GWorld", "").c_str(), GameInfo.getAs<int>("GInfo", "GWorldFirstOpCodes", 0), GameInfo.getAs<int>("GInfo", "GWorldTotalByteInstruction", 0));

                    auto GName = GNameGrabber.ripVariable();
                    GetGameInfo()->GName = GName;

                    auto GObject = GObjectGrabber.ripVariable();
                    GetGameInfo()->GObject = GObject;

                    auto GWorld = GWorldGrabber.ripVariable();
                    GetGameInfo()->GWorld = GWorld;

                    LOG_INFO("GName, GObject, and GWorld Patterns Loaded");
                }
                else
                {
                    GetGameInfo()->GName = (DWORD64)GetModuleHandleW(0) + Utility::ConvertStringToDWord(GameInfo.get("GInfo", "GName", ""));
                    GetGameInfo()->GObject = (DWORD64)GetModuleHandleW(0) + Utility::ConvertStringToDWord(GameInfo.get("GInfo", "GObject", ""));
                    GetGameInfo()->GWorld = (DWORD64)GetModuleHandleW(0) + Utility::ConvertStringToDWord(GameInfo.get("GInfo", "GWorld", ""));
                    LOG_INFO("GName, GObject, and GWorld Offsets Loaded");
                }
            }
            else
            {
                //If the GInfo isnt defined, use default AOBs to find them.
                /*
                TODO
                ====
                USE MULTIPLE ALTERNATIVES
                */
                if (GetGameInfo()->UsesFNamePool)
                {
                    auto FNamePoolGrabber = new Memory::VariableGrabber("74 09 48 8D 15 ? ? ? ? EB 16", 5, 9);
                    auto FNamePoolVar = FNamePoolGrabber->ripVariable();
                    if (FNamePoolVar != 0)
                    {
                        GetGameInfo()->GName = FNamePoolVar;
                        LOG_INFO("FoundNamePool: 0x%p", GetGameInfo()->GName);
                    }
                    else
                    {
                        LOG_ERROR("FoundNamePool Could Not Be Found!");
                    }
                }
                else
                {
                    auto GNameGrabber = new Memory::VariableGrabber("E8 ? ? ? ? 48 8B C3 48 89 1D ? ? ? ? 48 8B 5C 24", 11, 15);
                    auto GNameVar = GNameGrabber->ripVariable();
                    if (GNameVar != 0)
                    {
                        GetGameInfo()->GName = GNameVar;
                        LOG_INFO("GName: 0x%p", GetGameInfo()->GName);
                    }
                    else
                    {
                        LOG_ERROR("GName Could Not Be Found!");
                    }
                }
                auto GObjectGrabber = new Memory::VariableGrabber("8B 46 10 3B 46 3C 75 0F 48 8B D6 48 8D 0D ? ? ? ? E8", 14, 18);
                auto GObjectVar = GObjectGrabber->ripVariable();
                if (GObjectVar != 0)
                {
                    GetGameInfo()->GObject = GObjectVar;
                    LOG_INFO("GObject: 0x%p", GetGameInfo()->GObject);
                }
                else
                {
                    LOG_ERROR("GObject Could Not Be Found!");
                }
                auto GWorldGrabber = Memory::VariableGrabber("0F 2E ? 74 ? 48 8B 1D ? ? ? ? 48 85 DB 74", 8, 12);
                auto GWorldVar = GWorldGrabber.ripVariable();
                if (GWorldVar != 0)
                {
                    GetGameInfo()->GWorld = GWorldVar;
                    LOG_INFO("GWorld: 0x%p", GetGameInfo()->GWorld);
                }
                else
                {
                    LOG_ERROR("GWorld Could Not Be Found!");
                }
            }

            /*
            TODO
            ====
            REVIEW THIS CODE AND MAKE SURE IT IS UP TO SNUFF
            */
            if (GameInfo.select("UObjectDef"))
            {
                GetGameInfo()->IsUObjectMissing = false;
                GetGameInfo()->defs->UObject.Index = Utility::ConvertStringToDWord(GameInfo.get("UObjectDef", "Index", ""));
                GetGameInfo()->defs->UObject.Class = Utility::ConvertStringToDWord(GameInfo.get("UObjectDef", "Class", ""));
                GetGameInfo()->defs->UObject.Name = Utility::ConvertStringToDWord(GameInfo.get("UObjectDef", "Name", ""));
                GetGameInfo()->defs->UObject.Outer = Utility::ConvertStringToDWord(GameInfo.get("UObjectDef", "Outer", ""));
            }

            if (GameInfo.select("UFieldDef"))
            {
                GetGameInfo()->IsUFieldMissing = false;
                GameInfo.select("UFieldDef");
                GetGameInfo()->defs->UField.Next = Utility::ConvertStringToDWord(GameInfo.get("UFieldDef", "Next", ""));
            }
            if (GameInfo.select("UStructDef"))
            {
                GetGameInfo()->IsUStructMissing = false;
                GameInfo.select("UStructDef");
                GetGameInfo()->defs->UStruct.SuperStruct = Utility::ConvertStringToDWord(GameInfo.get("UStructDef", "SuperStruct", ""));
                GetGameInfo()->defs->UStruct.Children = Utility::ConvertStringToDWord(GameInfo.get("UStructDef", "Children", ""));
                GetGameInfo()->defs->UStruct.PropertiesSize = Utility::ConvertStringToDWord(GameInfo.get("UStructDef", "PropertiesSize", ""));
            }
            if (GameInfo.select("UFunctionDef"))
            {
                GetGameInfo()->IsUFunctionMissing = false;
                GameInfo.select("UFunctionDef");
                GetGameInfo()->defs->UFunction.FunctionFlags = Utility::ConvertStringToDWord(GameInfo.get("UFunctionDef", "FunctionFlags", ""));
                GetGameInfo()->defs->UFunction.Func = Utility::ConvertStringToDWord(GameInfo.get("UFunctionDef", "Func", ""));
            }

            if (GameInfo.select("Property"))
            {
                GetGameInfo()->bIsFProperty = GameInfo.getAs<int>("Property", "IsFProperty", 0);
                GetGameInfo()->defs->Property.ArrayDim = Utility::ConvertStringToDWord(GameInfo.get("Property", "ArrayDim", ""));
                GetGameInfo()->defs->Property.Offset = Utility::ConvertStringToDWord(GameInfo.get("Property", "Offset", ""));
                if (GetGameInfo()->bIsFProperty)
                {
                    GameInfo.select("FField");
                    GetGameInfo()->defs->FField.Name = Utility::ConvertStringToDWord(GameInfo.get("FField", "Name", ""));
                    GetGameInfo()->defs->FField.Next = Utility::ConvertStringToDWord(GameInfo.get("FField", "Next", ""));
                }
            }
            else
            {
                GetGameInfo()->IsPropertyMissing = true;
            }

            /*
            TODO
            ====
            REWRITE CODE TO NOT BE FORCED TO DEFINE EVERY FUNCTION IF ONLY 1 AOB DIES
            */
            // This code sets the Function information if found in the games profile
            if (GameInfo.select("FunctionInfo"))
            {
                if (GameInfo.getAs<int>("FunctionInfo", "IsFunctionPatterns", 0) == 0)
                {
                    GetGameInfo()->GameStateInit = (DWORD64)GetModuleHandleW(0) + Utility::ConvertStringToDWord(GameInfo.get("FunctionInfo", "GameStateInit", ""));
                    GetGameInfo()->BeginPlay = (DWORD64)GetModuleHandleW(0) + Utility::ConvertStringToDWord(GameInfo.get("FunctionInfo", "BeginPlay", ""));
                    GetGameInfo()->StaticLoadObject = (DWORD64)GetModuleHandleW(0) + Utility::ConvertStringToDWord(GameInfo.get("FunctionInfo", "StaticLoadObject", ""));
                    GetGameInfo()->SpawnActorFTrans = (DWORD64)GetModuleHandleW(0) + Utility::ConvertStringToDWord(GameInfo.get("FunctionInfo", "SpawnActorFTrans", ""));
                    GetGameInfo()->CallFunctionByNameWithArguments = (DWORD64)GetModuleHandleW(0) + Utility::ConvertStringToDWord(GameInfo.get("FunctionInfo", "CallFunctionByNameWithArguments", ""));
                    GetGameInfo()->ProcessEvent = (DWORD64)GetModuleHandleW(0) + Utility::ConvertStringToDWord(GameInfo.get("FunctionInfo", "ProcessEvent", ""));
                    GetGameInfo()->CreateDefaultObject = (DWORD64)GetModuleHandleW(0) + Utility::ConvertStringToDWord(GameInfo.get("FunctionInfo", "CreateDefaultObject", ""));
                    LOG_INFO("Function Offsets Set");
                }
                else
                {
                    GetGameInfo()->GameStateInit = (DWORD64)Utility::FindPattern(GameInfo.get("FunctionInfo", "GameStateInit", "").c_str());
                    GetGameInfo()->BeginPlay = (DWORD64)Utility::FindPattern(GameInfo.get("FunctionInfo", "BeginPlay", "").c_str());
                    GetGameInfo()->StaticLoadObject = (DWORD64)Utility::FindPattern(GameInfo.get("FunctionInfo", "StaticLoadObject", "").c_str());
                    GetGameInfo()->SpawnActorFTrans = (DWORD64)Utility::FindPattern(GameInfo.get("FunctionInfo", "SpawnActorFTrans", "").c_str());
                    GetGameInfo()->CallFunctionByNameWithArguments = (DWORD64)Utility::FindPattern(GameInfo.get("FunctionInfo", "CallFunctionByNameWithArguments", "").c_str());
                    GetGameInfo()->ProcessEvent = (DWORD64)Utility::FindPattern(GameInfo.get("FunctionInfo", "ProcessEvent", "").c_str());
                    GetGameInfo()->CreateDefaultObject = (DWORD64)Utility::FindPattern(GameInfo.get("FunctionInfo", "CreateDefaultObject", "").c_str());
                    LOG_INFO("Function Patterns Set");
                }
            }
            else
            {
                //GameStateInit AOBS
                auto GameStateInit_Grabber = new Memory::FunctionGrabber("40 53 48 83 EC 20 48 8B 41 10 48 8B D9 48 8B 91");
                GetGameInfo()->GameStateInit = GameStateInit_Grabber->ripFunction();
                if (GetGameInfo()->GameStateInit != 0)
                    LOG_INFO("GameStateInit: 0x%p", (void*)GetGameInfo()->GameStateInit);
                else
                    LOG_ERROR("GameStateInit NOT FOUND!");

                //Beginplay AOBS
                auto BeginPlay_Grabber = new Memory::FunctionGrabber("48 8B D9 E8 ?? ?? ?? ?? F6 83 ?? ?? ?? ?? ?? 74 12 48 8B 03", 0x3);
                GetGameInfo()->BeginPlay = BeginPlay_Grabber->ripFunction();
                if (GetGameInfo()->BeginPlay != 0)
                    LOG_INFO("AActor::BeginPlay: 0x%p", (void*)GetGameInfo()->BeginPlay);
                else
                    LOG_ERROR("AActor::BeginPlay NOT FOUND!");

                //StaticLoadObject AOBS
                auto StaticLoadObject_Grabber = new Memory::FunctionGrabber("89 64 24 ? 48 8B C8 E8 ? ? ? ? 41 BE ? ? ? ? EB 05 E8", 0x7);
                StaticLoadObject_Grabber->addAlternativeAob("C7 44 24 ? ? ? ? ? E8 ? ? ? ? 48 8B 8D ? ? ? ? 48 85 C9 74 05 E8 ? ? ? ? 45 33 C9 ? 89 74 24", 0x8);
                StaticLoadObject_Grabber->addAlternativeAob("89 6C 24 20 48 8B C8 E8 ? ? ? ? 48 8B 4C 24 ? 48 8B F0 48 85 C9 74 05", 0x7);
                StaticLoadObject_Grabber->addAlternativeAob("48 8B C8 89 5C 24 20 E8 ? ? ? ? 48", 0x7);
                GetGameInfo()->StaticLoadObject = StaticLoadObject_Grabber->ripFunction();
                if (GetGameInfo()->StaticLoadObject != 0)
                    LOG_INFO("StaticLoadObject: 0x%p", (void*)GetGameInfo()->StaticLoadObject);
                else
                    LOG_ERROR("StaticLoadObject NOT FOUND!");

                //SpawnActorFTrans AOBS
                auto SpawnActorFTrans_Grabber = new Memory::FunctionGrabber("4C 8B C6 48 8B C8 48 8B D3 E8 ? ? ? ? 48 8B 5C 24 ? 48 8B 74 24", 0x9);
                SpawnActorFTrans_Grabber->addAlternativeAob("4C 8B CE 4C 8D 44 24 ? 48 8B D7 48 8B CB E8 ? ? ? ? 48 8B 4C 24 ? 48 33 CC", 0xE);
                GetGameInfo()->SpawnActorFTrans = SpawnActorFTrans_Grabber->ripFunction();
                if (GetGameInfo()->SpawnActorFTrans != 0)
                    LOG_INFO("UWorld::SpawnActor: 0x%p", (void*)GetGameInfo()->SpawnActorFTrans);
                else
                    LOG_ERROR("SpawnActorFTrans NOT FOUND!");
     
                //CallFunctionByNameWithArguments AOBS
                auto CallFunctionByNameWithArguments_Grabber = new Memory::FunctionGrabber("8B ? E8 ? ? ? ? ? 0A E8 FF ? EB 9E ? 8B", 0x2);
                CallFunctionByNameWithArguments_Grabber->addAlternativeAob("49 8B D4 E8 ? ? ? ? 44 0A F8 FF C3 EB 9A", 0x3);
                GetGameInfo()->CallFunctionByNameWithArguments = CallFunctionByNameWithArguments_Grabber->ripFunction();
                if(GetGameInfo()->CallFunctionByNameWithArguments)
                    LOG_INFO("CallFunctionByNameWithArguments: 0x%p", (void*)GetGameInfo()->CallFunctionByNameWithArguments);
                else
                    LOG_ERROR("CallFunctionByNameWithArguments NOT FOUND!");

                //Process AOBS
                auto ProcessEvent_Grabber = new Memory::FunctionGrabber("75 0E ? ? ? 48 ? ? 48 ? ? E8 ? ? ? ? 48 8B ? 24 ? 48 8B ? 24 38 48 8B ? 24 40", 0xB);
                GetGameInfo()->ProcessEvent = ProcessEvent_Grabber->ripFunction();
                if (GetGameInfo()->ProcessEvent != 0)
                    LOG_INFO("UObject::ProcessEvent: 0x%p", (void*)GetGameInfo()->ProcessEvent);
                else
                    LOG_ERROR("ProcessEvent NOT FOUND!");

                //CreateDefaultObject AOBS
                auto CreateDefaultObject_Grabber = new Memory::FunctionGrabber("4C 8B DC 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 48 83 B9 ? ? ? ? ? 48 8B F9 ");
                CreateDefaultObject_Grabber->addAlternativeAob("4C 8B DC 55 53 49 8D AB ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 48 83 B9 ? ? ? ? ? 48 8B D9 0F 85");
                CreateDefaultObject_Grabber->addAlternativeAob("4C 8B DC 53 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 48 83 B9");
                CreateDefaultObject_Grabber->addAlternativeAob("4C 8B DC ?? ?? ?? ?? ?? ? ? ? ? ?? ?? ?? ? ? ? ? ?? ?? ?? ? ? ? ? ?? ?? ?? 48 ?? ?? ? ? ? ? ?? ?? ?? ? ? ? ? ? ?? ?? ?? ?? ?? ? ? ? ? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ? ? ? ? ?? 8B ?? ? ? ? ? ?? ?? ?? ?? ?? ?? 8B ?? ?? ?? ?? ?? ?? ? ? ? ? ?? ?? ?? ? ? ? ? ?? ?? ?? ?? ?? ?? ? ? ? ? ?? ?? ?? ?? ?? ? ? ? ? ?? ?? ? ? ? ? ?? ?? ?? 48");
                GetGameInfo()->CreateDefaultObject = CreateDefaultObject_Grabber->ripFunction();
                if (GetGameInfo()->CreateDefaultObject != 0)
                    LOG_INFO("UClass::CreateDefualtObject: 0x%p", (void*)GetGameInfo()->CreateDefaultObject);
                else
                    LOG_ERROR("CreateDefualtObject NOT FOUND!, Isn't that big of a issue, mostly depreciated");
            }
            // Loads Process Internal Function if defined in the game profile
            if (GameInfo.select("ProcessInternalFunction"))
            {
                auto ProcessInternals_Grabber = new Memory::FunctionGrabber(GameInfo.get("ProcessInternalFunction", "ProcessInternal", "").c_str());
                GetGameInfo()->ProcessInternals = ProcessInternals_Grabber->ripFunction();
                LOG_INFO("ProcessInternalFunction: 0x%p", (void*)GetGameInfo()->ProcessInternals);
            }
            else
            {
                if (GetGameInfo()->UsesFNamePool || GetGameInfo()->IsUsing4_22)
                {
                    auto ProcessInternals_Grabber = new Memory::FunctionGrabber("41 F6 C7 02 74 ? 4C 8B C7 48 8B ? ? 8B ? E8", 0xF);
                    GetGameInfo()->ProcessInternals = ProcessInternals_Grabber->ripFunction();
                    if (GetGameInfo()->ProcessInternals != 0)
                        LOG_INFO("ProcessInternalFunction: 0x%p", (void*)GetGameInfo()->ProcessInternals);
                    else
                        LOG_ERROR("ProcessInternalFunction COULD NOT BE FOUND!");
                }
            }

            //Loads StaticConstructObejct_InternalInfo is present in the game profile
            if (GameInfo.select("StaticConstructObejct_InternalInfo"))
            {
                GetGameInfo()->IsUsingUpdatedStaticConstruct = GameInfo.getAs<int>("StaticConstructObejct_InternalInfo", "IsUsingUpdatedStaticConstruct", 0);
                auto StaticConstructObject_Internal_Grabber = new Memory::FunctionGrabber(GameInfo.get("StaticConstructObejct_InternalInfo", "StaticConstructObject_InternalFunction", "").c_str());
                GetGameInfo()->StaticConstructObject_Internal = StaticConstructObject_Internal_Grabber->ripFunction();
            }
            else
            {
                auto StaticConstructObject_Internal_Grabber = new Memory::FunctionGrabber("48 8B 84 24 ?? ?? 00 00 48 89 44 24 ?? C7 44 24 ?? 00 00 00 00 E8 ?? ?? ?? ?? 48 8B 5C 24", 0x15);
                StaticConstructObject_Internal_Grabber->addAlternativeAob("48 8B C8 89 7C 24 ?? E8 ?? ?? ?? ?? 48 8B 5C 24 ?? 48 83 C4 ?? 5F C3", 0x7);
                GetGameInfo()->StaticConstructObject_Internal = StaticConstructObject_Internal_Grabber->ripFunction();
                if (GetGameInfo()->StaticConstructObject_Internal == 0)
                {
                    GetGameInfo()->IsUsingUpdatedStaticConstruct = true;
                    StaticConstructObject_Internal_Grabber->addAlternativeAob("E8 ? ? ? ? 45 8B 47 70", 0x1);
                    StaticConstructObject_Internal_Grabber->addAlternativeAob("89 6C 24 38 48 89 74 24 ? E8", 0x9);
                    GetGameInfo()->StaticConstructObject_Internal = StaticConstructObject_Internal_Grabber->ripFunction();
                    if(GetGameInfo()->StaticConstructObject_Internal != 0)
                        LOG_INFO("StaticConstructObject_Internal 0x%p", (void*)GetGameInfo()->StaticConstructObject_Internal);
                    else
                        LOG_WARNING("StaticConstructObject_Internal Not Found! This will prevent Mods using the ModObjectInstance from working properly.");
                }
                else
                    LOG_INFO("StaticConstructObject_Internal 0x%p", (void*)GetGameInfo()->StaticConstructObject_Internal);
            }
            LOG_INFO("Setup %s", gamename.c_str());
            ModLoader::Init();
        }
        else
        {
            LOG_ERROR("Profile %s Not Detected!", Profile.c_str());
        }
    }

    class GameInfo* GetGameInfo()
    {
        if (!gameInfo)
        {
            gameInfo = new GameInfo();
        }
        return gameInfo;
    }

    void CleanUp()
    {
        ModLoader::CleanUp();
    }
};

// Loader Dll Entry Point
BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        UML::StartUML();
        break;
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        UML::CleanUp();
        break;
    }
    return TRUE;
}