#include "PakLoader.h"
#include "Utilities/MinHook.h"
#include "GameInfo/GameInfo.h"
#include "Ue4.hpp"
#include <filesystem>
#include "Utilities/Pattern.h"
#include "Utilities/Globals.h"
#include "Utilities/Dumper.h"

bool GameStateClassInitNotRan = true;
namespace fs = std::filesystem;
HANDLE                      m_hConsole;
WORD                        m_currentConsoleAttr;
CONSOLE_SCREEN_BUFFER_INFO   csbi;
namespace PakLoader
{
	void ScanLoadedPaks()
	{
		char path_c[MAX_PATH];
		GetModuleFileNameA(NULL, path_c, MAX_PATH);
		std::string path = std::string(path_c);
		path = path.substr(0, path.find_last_of("/\\"));
		path = path.substr(0, path.find_last_of("/\\"));
		path = path.substr(0, path.find_last_of("/\\"));
		path = path + "\\Content\\Paks\\LogicMods\\";
		if (!std::filesystem::exists(path))
		{
			std::filesystem::create_directory(path);
		}
		Global::modnames.empty();
		for (const auto& entry : fs::directory_iterator(path))
		{
			if (entry.path().extension().string() == ".pak")
			{
				std::wstring filename = entry.path().filename().wstring();
				std::wstring modNameW = filename.substr(0, filename.length() - 4);
				if (modNameW.substr(modNameW.length() - 2, 2) == L"_p")
					modNameW = modNameW.substr(0, modNameW.length() - 2);
				if (modNameW.substr(modNameW.length() - 2, 2) == L"_P")
					modNameW = modNameW.substr(0, modNameW.length() - 2);
				std::string str(modNameW.begin(), modNameW.end());
				Log::Info("PakModLoaded: %s", str);
				Global::modnames.push_back(modNameW);
			}
		}
	}

	namespace HookedFunctions
	{
		PVOID(*origInitGameState)(void*);
		PVOID hookInitGameState(void* Ret)
		{
			Log::Info("GameStateHook");
			if (GameStateClassInitNotRan)
			{
				UE4::InitSDK();
				Log::Info("Engine Classes Loaded");
				UE4::FTransform transform = UE4::FTransform::FTransform();
				UE4::FActorSpawnParameters spawnParams = UE4::FActorSpawnParameters::FActorSpawnParameters();
				if (GameProfile::SelectedGameProfile.StaticLoadObject)
				{
					Log::Info("StaticLoadObject Found");
					UE4::UClass* ModActorObject = UE4::UClass::LoadClassFromString(L"/Game/ModLoaderContent/ModLoaderActor.ModLoaderActor_C", false);
					if (ModActorObject)
					{
						Log::Info("Sucessfully Loaded ModLoader Pak");
						if (!GameProfile::SelectedGameProfile.IsUsingDeferedSpawn)
						{
							Global::ModLoaderActor = UE4::UWorld::GetWorld()->SpawnActor(ModActorObject, &transform, &spawnParams);
						}
						else
						{
							auto Gameplay = (UE4::UGameplayStatics*)UE4::UGameplayStatics::StaticClass()->CreateDefaultObject();
							Global::ModLoaderActor = Gameplay->BeginDeferredActorSpawnFromClass(ModActorObject, transform, UE4::ESpawnActorCollisionHandlingMethod::AlwaysSpawn, nullptr);
						}

					}
					else
					{
						Log::Warn("ModLoader Pak Not Found");
					}
				}
				else
				{
					Log::Error("StaticLoadObject Not Found");
				}
				GameStateClassInitNotRan = false;
			}
			for (int i = 0; i < Global::ModActors.size(); i++)
			{
				UE4::AActor* CurrentModActor = Global::ModActors[i];
				if (CurrentModActor->IsA(UE4::AActor::StaticClass()))
				{
					CurrentModActor->CallFunctionByNameWithArguments(L"ModCleanUp", nullptr, NULL, true);
				}
			}
			Global::ModActors.clear();
			if (Global::ModLoaderActor->IsA(UE4::AActor::StaticClass()))
			{
				Global::ModLoaderActor->CallFunctionByNameWithArguments(L"CleanLoader", nullptr, NULL, true);
			}
			if (GameProfile::SelectedGameProfile.StaticLoadObject)
			{
				UE4::FTransform transform;
				transform.Translation = UE4::FVector(0, 0, 0);
				transform.Rotation = UE4::FQuat(0, 0, 0, 0);
				transform.Scale3D = UE4::FVector(1, 1, 1);
				UE4::FActorSpawnParameters spawnParams = UE4::FActorSpawnParameters::FActorSpawnParameters();
				for (int i = 0; i < Global::modnames.size(); i++)
				{
					std::wstring CurrentMod;
					//StartSpawningMods
					CurrentMod = Global::modnames[i];
					if (GameProfile::SelectedGameProfile.StaticLoadObject)
					{
						std::string str(CurrentMod.begin(), CurrentMod.end());
						const std::wstring Path = L"/Game/Mods/" + CurrentMod +  L"/ModActor.ModActor_C";
						UE4::UClass* ModObject = UE4::UClass::LoadClassFromString(Path.c_str(), false);
						if (ModObject)
						{
							UE4::AActor* ModActor = nullptr;
							if (!GameProfile::SelectedGameProfile.IsUsingDeferedSpawn)
							{
								ModActor = UE4::UWorld::GetWorld()->SpawnActor(ModObject, &transform, &spawnParams);
							}
							else
							{
								auto Gameplay = (UE4::UGameplayStatics*)UE4::UGameplayStatics::StaticClass()->CreateDefaultObject();
								ModActor = Gameplay->BeginDeferredActorSpawnFromClass(ModObject, transform, UE4::ESpawnActorCollisionHandlingMethod::AlwaysSpawn, nullptr);
							}
							if (ModActor)
							{
								Global::ModActors.push_back(ModActor);
								ModActor->CallFunctionByNameWithArguments(L"PreBeginPlay", nullptr, NULL, true);
								Log::Info("Sucessfully Loaded %s", str);
							}
						}
						else
						{
							Log::Info("Could not locate ModActor for %s", str);
						}
					}
				}
				Log::Info("Finished Spawning PakMods");
			}
			Log::Info("Returning to GameState --------------------------------------------------------");
			return origInitGameState(Ret);
		}

		PVOID(*origBeginPlay)(UE4::AActor*);
		PVOID hookBeginPlay(UE4::AActor* Actor)
		{
			if (!GameStateClassInitNotRan)
			{
				if (Actor->IsA(UE4::ACustomClass::StaticClass(GameProfile::SelectedGameProfile.BeginPlayOverwrite)))
				{
					Log::Info("Beginplay Called");
					Global::ModLoaderActor->CallFunctionByNameWithArguments(L"PostLoaderStart", nullptr, NULL, true);
					for (int i = 0; i < Global::ModActors.size(); i++)
					{
						UE4::AActor* CurrentModActor = Global::ModActors[i];
						if (CurrentModActor != nullptr)
						{
							CurrentModActor->CallFunctionByNameWithArguments(L"PostBeginPlay", nullptr, NULL, true);
						}
					}
				}
			}
			return origBeginPlay(Actor);
		}

		PVOID(*origSay)(void*, UE4::FString*);
		PVOID hookSay(void* GM, UE4::FString* Message)
		{
			Log::Info("Hook Say Called");
			std::wstring WStrMsg = Message->c_str();
			if (WStrMsg.substr(WStrMsg.length() - 6, 6) == L"/Print") // check if message ends with /Print
			{
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				WStrMsg = WStrMsg.substr(0, WStrMsg.length() - 6); // remove /Print extension
				std::string str(WStrMsg.begin(), WStrMsg.end());
				SetConsoleTextAttribute(hConsole, 13);
				std::cout << "Print: " << str << std::endl;
				SetConsoleTextAttribute(hConsole, 7);
			}
			return origSay(GM, Message);
		}
	};

	DWORD __stdcall InitHooks(LPVOID)
	{
		MinHook::Init();
		Log::Info("MinHook Setup");
		ScanLoadedPaks();
		Log::Info("ScanLoadedPaks Setup");
		MinHook::Add(GameProfile::SelectedGameProfile.GameStateInit, &HookedFunctions::hookInitGameState, &HookedFunctions::origInitGameState, "AGameModeBase::InitGameState");
		MinHook::Add(GameProfile::SelectedGameProfile.BeginPlay, &HookedFunctions::hookBeginPlay, &HookedFunctions::origBeginPlay, "AActor::BeginPlay");
		MinHook::Add(GameProfile::SelectedGameProfile.Say, &HookedFunctions::hookSay, &HookedFunctions::origSay, "AGameMode::Say");
		return NULL;
	}
	void SetupLoader()
	{
		Log::Info("Setting Up Loader");
		CreateThread(0, 0, InitHooks, 0, 0, 0);
		Dumper::BeginKeyThread();
	}
};